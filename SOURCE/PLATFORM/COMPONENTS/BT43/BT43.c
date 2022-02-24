/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2015, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : BT43.c                                                                          */
/* \Author      : SANTHOSH                                                                        */
/* \Version 	:                                                                                 */
/* \Date        : 06-05-2018                                                                     */
/*                                                                                                */
/* @Description : BT43 Frame Work                                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "DATACONV.h"

#include "GPIO.h"
#include "UART.h"

#include "GPIO.h"
//#include "TBUS.h"

#include "BT43.h"
#include "BT43_Priv.h"

#include "MSG4_App.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Buffer for to Process BT43 MAC and Name */
INT8U au8_gBT43CmdRespBuf[BT43_CMD_BUFFER_LENGTH]={0,};

/* TBUS Receive Data Buffer */
INT8U u8_gBTRxBuffer[BT43_BUFFER_SIZE] = {0, };

/* Bluetooth Searchable strings */
const INT8U au8_gConnectReqResp1[20] = "AT-AB ConnectionUp\r";
const INT8U au8_gConnectReqResp2[20] = "AT-AB -BypassMode-\r";
const INT8U au8_gDisonnectReqResp1[27] = "AT-AB SPPConnectionClosed\r";
const INT8U au8_gDisonnectReqResp2[22] = "AT-AB ConnectionDown\r";
const INT8U au8_gErrorReqResp1[17] = "AT-AB ErrFormat\r";
	
const INT8U au8_gMacSearchString[31] = "var02 BD_ADDR               = ";
const INT8U au8_gMacSearchString2[31] = "var03 DeviceName            = ";
const INT8U au8_gBTCommandMode[22] = "AT-AB -CommandMode-\r\n";
INT8U au8_gBT_NameBuffer[60] = "AT+AB config DeviceName = ";

/* Buffer for to Store the BT43 MAC Address */
INT8U u8_gMAC_ADDRESS[17] = {0, };

/* */
INT32U u32_gDataRcvdIndex = 0x00;

/* */
INT8U u8_gBT43CmdRespIndex = 0;

/*  BT Handle Responce */
EN_BT_HANDLE_RESP_t en_gBTRespType = BT_CRLF;

/* Flag for to Process  BT43 MAC and Name */
volatile INT8U u8_gBT43CmdMode = 0;

/* Variable for to check the Data */
volatile INT8U u8_gisDataFromBT = 0;

/* Initialize the GPIO  */
ST_GPIO_PARAMS_t st_gBT43_UART_TX_Data =
{
    .en_mPortSel = GPIO_PORT_A,
    .en_mPinSel = GPIO_PIN_4,
    .en_mPinDir = GPIO_DIR_OUTPUT,
    .en_mPinType = GPIO_PULL_LVL_DIS,
    .en_mPinPeriph = GPIO_PERIPHERAL_D,
    .en_mDriverStrenght	= GPIO_DRIV_STRENGTH_NORMAL
};

/* Structure for GPIO Configuration */
ST_GPIO_PARAMS_t st_gBT43_UART_RX_Data = 
{
    .en_mPortSel = GPIO_PORT_A,
    .en_mPinSel = GPIO_PIN_5,
    .en_mPinDir = GPIO_DIR_INPUT,
    .en_mPinType = GPIO_PULL_LVL_DIS,
    .en_mPinPeriph = GPIO_PERIPHERAL_D,
    .en_mDriverStrenght	= GPIO_DRIV_STRENGTH_NORMAL
};

/* Structure to Configure UART */
ST_UART_CONFIG_PARAMS_t st_gBT43_UartParams = 
{
    .en_mSERCOMChnl	= SERCOM_CH_0,
    .en_mDataBits =	USART_CH_SIZE_8_BITS,
    .en_mStopBits = USART_ONE_STOP_BIT,
    .en_mParity = USART_PARITY_DISABLE,
    .u32_mBaudrate = 115200,
    .en_mTXPad = SERCOM_TX_PAD0,
    .en_mRXPad = SERCOM_RX_PAD1,
    .fp_USERHANDLER	= BT43_RxHandler,
};

/**************************************************************************************************/
/* Function Name   : void BT43_RxHandler( INT8U u8_fData)                                         */
/*                                                                                                */
/* Description     :  Bluetooth Rx HANDLER                                                        */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void BT43_RxHandler( INT8U u8_fData)
{
    /* Check For the Command Mode Data */
    if(1 == u8_gBT43CmdMode)
    {
        /* Accumilating The Data for to use BT43 Mac And Name Change */
        au8_gBT43CmdRespBuf[u8_gBT43CmdRespIndex] = u8_fData;
        u8_gBT43CmdRespIndex = u8_gBT43CmdRespIndex + 1;
        
        if(u8_gBT43CmdRespIndex > BT43_CMD_BUFFER_LENGTH)
        {
            /* Index is Maximum Then Make it Zero */
            u8_gBT43CmdRespIndex = 0;
        }
    }	
    else
    {
        /* Copy the Data */
        u8_gBTRxBuffer[u32_gDataRcvdIndex] = u8_fData;
        
        switch(en_gBTRespType)
        {
            case BT_CRLF:
            {
                if(('\n' == u8_gBTRxBuffer[u32_gDataRcvdIndex]) && \
                                    ('\r' ==  u8_gBTRxBuffer[u32_gDataRcvdIndex-1]))
                {
                   
                    /* Make the BT Data  received Flag to 1 */
                    u8_gisDataFromBT = 0x01;
                    
                }
                else
                {
                    /* No Action */
                }
            }
            break;
            case BT_STNFLASH:
            {
                if((0x04 ==  u8_gBTRxBuffer[u32_gDataRcvdIndex]) && \
                                        (0x05 !=  u8_gBTRxBuffer[u32_gDataRcvdIndex-1]))
                {
                     /* Make the BT Data  received Flag to 1 */
                    u8_gisDataFromBT = 0x01;
                }
                else if((':' == u8_gBTRxBuffer[0]) && ('\n' == \
                        u8_gBTRxBuffer[u32_gDataRcvdIndex]) && ('\r' == \
                                            u8_gBTRxBuffer[u32_gDataRcvdIndex-1]))
                {
                     /* Make the BT Data  received Flag to 1 */
                    u8_gisDataFromBT = 0x01;
                }
                else
                {
                    /* No Action */
                }
            }
            break;
        }
        
        /* */
        u32_gDataRcvdIndex = u32_gDataRcvdIndex + 1;
    }
    
    if(u32_gDataRcvdIndex >= BT43_BUFFER_SIZE)
    {
         /* Index is MAximum Then Make it Zero */
        u32_gDataRcvdIndex = 0;
    }
    else
    {
        /* No Action */
    }
}

/**************************************************************************************************/
/* Function Name   : void BT43_Init(void)                                                         */
/*                                                                                                */
/* Description     : Initialize the Bluetooth                                                     */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void BT43_Init(void)
{
    /* Update the Baudrate*/
    st_gBT43_UartParams.u32_mBaudrate= 460800;

    /* Configuring BT43 Pins */
    GPIO_Init((ST_GPIO_PARAMS_t*)&st_gBT43_UART_TX_Data);
    GPIO_Init((ST_GPIO_PARAMS_t*)&st_gBT43_UART_RX_Data);

    /* Configure the BT43 UART */
    UART_Init(&st_gBT43_UartParams);
}

/**************************************************************************************************/
/* Function Name   : void BT43_Transmit(INT8U * p_fData, INT32U u32_fLength)                      */
/*                                                                                                */
/* Description     : Transmit the Data from BT43                                                  */
/*                                                                                                */
/* In Params       : Data, Length                                                                 */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void BT43_Transmit(INT8U * p_fData, INT32U u32_fLength)
{
    /* For Loop Purpose */
    INT32U u32_lIndex = 0;
    
    INT32U u32_lIndex1 = 0;
     
   /* Send 1024 Bytes BT support at a time 1024 Bytes only */
   while(1024 < u32_fLength)
   {
        /* Send char by char to Bluetooth */
        for(u32_lIndex = 0x00; u32_lIndex < 1024; u32_lIndex++)
        {
            /* Transmit char by char to Bluetooth*/
           UART_TransmitChar(st_gBT43_UartParams.en_mSERCOMChnl, p_fData[u32_lIndex + u32_lIndex1]);
        }
        
        /* Send 1024 Bytes BT support at a time 1024 Bytes only */
        u32_lIndex1 = u32_lIndex1 + 1024;
        u32_fLength = u32_fLength -1024;
        
        u32_g1ms_Countr = 0x00;
        while(u32_g1ms_Countr <= 75);
   }
   
   /* if below 1024 Bytes send data */
   if(1024 >= u32_fLength && 0!= u32_fLength)
   {
        /* Send char by char to Bluetooth */
        for(u32_lIndex = 0x00; u32_lIndex < u32_fLength; u32_lIndex++)
        {
            /* Transmit char by char to Bluetooth*/
           UART_TransmitChar(st_gBT43_UartParams.en_mSERCOMChnl, p_fData[u32_lIndex + u32_lIndex1]);
           
        }
   }
   
//    /* send Character by Character */
//    for(u32_lIndex = 0; u32_lIndex < u32_fLength; u32_lIndex++)
//    {
//        /* Send Character by Character */
//        UART_TransmitChar(st_gBT43_UartParams.en_mSERCOMChnl, p_fData[u32_lIndex]);
//        
//        /* Charecter To Charecter Delay */
//        for(int i = 0x00 ;i < 2000 ;i++);
//    }
}

/**************************************************************************************************/
/* Function Name   : void BT43_ResetCmdRespBuffer(void)                                           */
/*                                                                                                */
/* Description     : Reset the Buffer                                                             */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void BT43_ResetCmdRespBuffer(void)
{
    /* Reset the Commandresponse Buffer */
    memset(&au8_gBT43CmdRespBuf[0], 0x00, BT43_CMD_BUFFER_LENGTH);
    
    /* Reset the Receive Index */
    u8_gBT43CmdRespIndex = 0;
}

/**************************************************************************************************/
/* Function Name   : BT43_RESULT_t BT43_ProcessMAC(INT8U * p_fOutBuffer)                          */
/*                                                                                                */
/* Description     : Get The BT43 MAC Address                                                     */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : p_fOutBuffer                                                                 */
/*                                                                                                */
/* Return Value    : en_lResult                                                                   */
/**************************************************************************************************/

EN_BT43_RESULT_t BT43_ProcessMAC(INT8U * p_fOutBuffer)
{    
    /* Enum to hold Result */
    EN_BT43_RESULT_t en_lResult = BT43_SUCCESS;
	INT32U u32_lIndex;

    /* Pointer for To Find Location */
    INT8U * p_lTemp1 = 0;

    /* Reset the CmdRespbuffer Buffer */
	BT43_ResetCmdRespBuffer();
	
	/* Aquire the MAC Address */
	BT43_Transmit((INT8U*)"AT+AB config BD_ADDR\r\n",strlen("AT+AB config BD_ADDR\r\n"));
	
	/* Little delay 2sec */
	for(u32_lIndex = 0; u32_lIndex < 1000000; u32_lIndex++);
	
	/* Search String */
	p_lTemp1 = (INT8U *)strstr((const char *)&au8_gBT43CmdRespBuf[0], \
				     (const char *)&au8_gMacSearchString[0]);	
    /* Search String */
    if(NULL != p_lTemp1)
    {
        /* Seek the pointer to the MAC start Address */
        p_lTemp1 = (p_lTemp1 + strlen((const char *)&au8_gMacSearchString[0]));
        
        if('\r' == p_lTemp1[12])
        {
			/* Copy MAC into Buffer */
			memcpy(&u8_gMAC_ADDRESS[0], &p_lTemp1[0], 12);
        }
        else
        {
            /* Update Error Status */
            en_lResult = BT43_ERROR;
        }
    }
    else
    {
        /* Update Error Status */
        en_lResult = BT43_ERROR;
    }
	
    /* */
    return en_lResult;
}

/******************************************************************************/
/* Function Name   : void BT43_FirstBoot(void)                                */
/*                                                                            */
/* Description     : Setting BT43 Basic Settings                              */
/*                                                                            */
/* In Params       : None                                                     */
/*                                                                            */
/* Out Params      : None                                                     */
/*                                                                            */
/* Return Value    : void                                                     */
/******************************************************************************/

void BT43_FirstBoot(void)
{
	INT8U u8_lResult = 0;
	INT32U u32_lIndex = 0;
	
    /* Updating default baudrate */
    st_gBT43_UartParams.u32_mBaudrate = 460800;

    /* Intialization of usart of channel 0 */
    UART_Init(&st_gBT43_UartParams);	

    /* Initialization of Tx Pin of UART Channel 0 */
    GPIO_Init((ST_GPIO_PARAMS_t*)&st_gBT43_UART_TX_Data);

    /* Initialization of Rx Pin of UART Channel 0 */
    GPIO_Init((ST_GPIO_PARAMS_t*)&st_gBT43_UART_RX_Data);
	
	for(u32_lIndex = 0; u32_lIndex < 40000000; u32_lIndex++);
	
	while(1)
	{
		/* Setting the BT Name */
		u8_lResult = BT43_CheckCmdResponse(\
		      (INT8U*)("AT+AB config DeviceName = MSG4_BT\r\n"),(INT8U*)("AT-AB ConfigOk\r\n"));
		
		if(!u8_lResult)
		{
			break;
		}
		else
		{
			/* No Action */
		}
	}
	
	/* Reset buffer after  Command Complete*/
	BT43_ResetFifo();
	
     while(1)
    {
        /* Setting the Bluetooth Baudrate  to 460800*/
        u8_lResult = BT43_CheckCmdResponse((INT8U *)("AT+AB config CpuMHz = 42\r\n"), \
                                                                   (INT8U *)("AT-AB ConfigOk\r\n"));

        if(!u8_lResult)
        {
            break;
        }
        else
        {
            /* No Action */
        }
    }
    
    /* Reset buffer after Command Complete*/
    BT43_ResetFifo();
    
	while(1)
	{
		/* Setting the Bluetooth Baudrate  to 921600*/
		u8_lResult = BT43_CheckCmdResponse((INT8U *)("AT+AB config UartBaudrate = 460800\r\n"), \
                                                                   (INT8U *)("AT-AB ConfigOk\r\n"));
		
		if(!u8_lResult)
		{
			break;
		}
		else
		{
			/* No Action */
		}
	}
	
	/* Rset buffer after Command Complete */
	BT43_ResetFifo();
	
	/* Some Delay */
	for(u32_lIndex = 0; u32_lIndex < 200000; u32_lIndex++);
	
	while(1)
	{
		/* Send a reset  command for Baudrate update*/
		u8_lResult = BT43_CheckCmdResponse((INT8U *)("AT+AB reset\r\n"), (INT8U *)("AT-AB"));
		
		if(!u8_lResult)
		{
			break;
		}
		else
		{
			/* No Action */
		}
	}
	
    /*  Delay for to update written values */
    for(u32_lIndex = 0; u32_lIndex < 40000000; u32_lIndex++);

    /* Rset buffer after Command Complete */
    BT43_ResetFifo();
	

    /* Baud Rate Update */
    st_gBT43_UartParams.u32_mBaudrate = 460800;

    /* Intialization of usart of channel 0 */
    UART_Init(&st_gBT43_UartParams);	
}

/**************************************************************************************************/
/* Function Name   : BT43_STATUS_t BT43_CheckConnectionStatus(void)                               */
/*                                                                                                */
/* Description     : Checking BT43 Connection Status                                              */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : en_lStatus                                                                   */
/**************************************************************************************************/

EN_BT43_STATUS_t BT43_CheckConnectionStatus(void)
{
	EN_BT43_STATUS_t en_lStatus = BT43_STATUS_ERROR;
	
	/* Checking For Connection and Disconnection String Status */
	if((NULL != strstr((const char *)&u8_gBTRxBuffer[0],"AT-AB")))
	{
		if((NULL != strstr((const char *)&u8_gBTRxBuffer[0],\
		                                (const char *)&au8_gConnectReqResp1[0]))|| \
                                           (NULL != strstr((const char *)&u8_gBTRxBuffer[0],\
							                               (const char *)&au8_gConnectReqResp2[0])))
		{
			/* Make BT Status flag to 1 */                
			en_lStatus = BT43_STATUS_CONNECTED;
			
			/* */
            memset(&u8_gBTRxBuffer[0], 0x00 , BT43_BUFFER_SIZE);
			BT43_ResetFifo();
            u8_gisDataFromBT = 0x00;
		}
		else if((NULL != strstr((const char *)&u8_gBTRxBuffer[0] , \
	                       (const char *)&au8_gDisonnectReqResp1[0])) || \
                                  (NULL != strstr((const char *)&u8_gBTRxBuffer[0],\
								                         (const char *)&au8_gDisonnectReqResp2[0])))
		{
			/* Make BT Status flag to 0 */
			en_lStatus = BT43_STATUS_DISCONNECTED;
			
			/* */
            memset(&u8_gBTRxBuffer[0], 0x00 , BT43_BUFFER_SIZE);
			BT43_ResetFifo();
            u8_gisDataFromBT = 0x00;
		}
		else if(NULL != strstr((const char *)&u8_gBTRxBuffer[0], \
                                                              (const char *)&au8_gErrorReqResp1[0]))
		{
			/* Make BT Status flag to 0 */
			en_lStatus = BT43_STATUS_DISCONNECTED;
			
			/* */
             memset(&u8_gBTRxBuffer[0], 0x00 , BT43_BUFFER_SIZE);
			BT43_ResetFifo();
            u8_gisDataFromBT = 0x00;
		}
		else
		{
			/* No action */
		}
	}
	else
	{
		/* No Action */
	}
    
    /* Return the Result */
	return en_lStatus;
}

/**************************************************************************************************/
/* Function Name   : void BT43_ChangeName(INT8U * p_fBuff)                                        */
/*                                                                                                */
/* Description     : Changing The BT43 Name                                                       */
/*                                                                                                */
/* In Params       : p_fBuff                                                                      */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void BT43_ChangeName(INT8U * p_fBuff)
{
	INT32U u32_lCmndDelay = 30000000;
	INT32U u32_lIndex = 0;
	INT32U u32_lMnmDelay = 300000;
	INT8U u8_lBTNameBuf[15] = {0x00, };
	
	/* Enable Command Mode */
	u8_gBT43CmdMode = 1;
	
	/* Copy te Bluetooth name into the local buffer */
	memcpy(&u8_lBTNameBuf[0],&p_fBuff[0], 15);
	
	/* Name Chnage Command Forming */
	strcat((char *)&au8_gBT_NameBuffer[0],(const char *)&u8_lBTNameBuf[0]);
	strcat((char *)&au8_gBT_NameBuffer[0],"\r\n");
	
	/* Reset the CmdRespbuffer Buffer */
	BT43_ResetCmdRespBuffer();
	
	/* Sending Escape Sequence To BT43 */
	BT43_Transmit((INT8U *)"^#^$^%", strlen((const char *)("^#^$^%")));
	for(u32_lIndex=0; u32_lIndex < u32_lCmndDelay; u32_lIndex++);
	
	/* Reset BT43 Commabd Response Buffer */
	BT43_ResetCmdRespBuffer();
	
	/* Transmitting Name Change Coommand with New Name */
	BT43_Transmit((INT8U *)&au8_gBT_NameBuffer, strlen((const char *)&au8_gBT_NameBuffer[0]));
	for(u32_lIndex=0;u32_lIndex < u32_lMnmDelay;u32_lIndex++);
	
	/* Checking Whether Name Changed or not */
	while(NULL == strstr((const char *)&au8_gBT43CmdRespBuf[0],(const char *)"AT-AB ConfigOk\r\n"));
	
	/* Reset BT43 Commabd Response Buffer */
	BT43_ResetCmdRespBuffer();
	
	/* Setting The BT43 Into the Bypass Mode */
	BT43_Transmit((INT8U *)"AT+AB Bypass\r\n", strlen((const char *)"AT+AB Bypass\r\n"));
	for(u32_lIndex=0; u32_lIndex < u32_lCmndDelay; u32_lIndex++);
	
	/* Rest BT43 Commabd Response Buffer */
	BT43_ResetCmdRespBuffer();
	
	/* Rest BT43 Commabd Response Buffer */
	BT43_ResetCmdRespBuffer();
	
	/* Reset the Name Buffer with null from Index 26 to 60 */
	memset(&au8_gBT_NameBuffer[26],0x00,60);
	
	/* Disable Command Mode */
	u8_gBT43CmdMode = 0;
}

/**************************************************************************************************/
/* Function Name   : void BT43_GetMacAddr(INT8U *p_fBuffer)                                       */
/*                                                                                                */
/* Description     : Getting BT43 Mac Address                                                     */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : p_fBuffer                                                                    */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void BT43_GetMacAddr(INT8U *p_fBuffer)
{
	INT32U u32_lCmndDelay = 30000000,u32_lIndex;
	INT32U u32_lMnmDelay = 300000;
	
	/* Enable Command Mode */
	u8_gBT43CmdMode = 1;
	
	/* Reset the CmdRespbuffer Buffer */
	BT43_ResetCmdRespBuffer();
	
	/* Sending Escape Sequence To BT43 */
	BT43_Transmit((INT8U *)"^#^$^%", strlen((const char *)("^#^$^%")));
	for(u32_lIndex=0;u32_lIndex < u32_lCmndDelay;u32_lIndex++);
	
	if(NULL != strstr((const char *)&au8_gBT43CmdRespBuf[0], "CommandMode"))
	{
		/* Processing MAC Address */
		BT43_ProcessMAC(&u8_gMAC_ADDRESS[0]);

		/* Setting The BT43 Into the Bypass Mode */
		BT43_Transmit((INT8U *)"AT+AB Bypass\r\n", strlen((const char *)"AT+AB Bypass\r\n"));
		for(u32_lIndex=0;u32_lIndex < u32_lMnmDelay ;u32_lIndex++);

		/* Copyong The Mac Addres to Destination Buffer */
		strcpy((char *)&p_fBuffer[0], (char *)&u8_gMAC_ADDRESS[0]);

        /* Disable Command Mode */
        u8_gBT43CmdMode = 0;
    }
    else
    {
        /* Transmitting The Successful NACk to User */
        BT43_Transmit((INT8U *)"Bluetooth MAC Address not Received\r\n", 37);
    }
}

/**************************************************************************************************/
/* Function Name   : EN_BT43_STATUS_t BT43_Ioctrl(EN_BT43_IOCTRL_ID_t en_fID, INT8U *pu8_fInData, */
/*						INT32U u32_fInDataLen, INT8U *pu8_fOutData, INT32U u32_fOutDataLen);      */
/*                                                                                                */
/* Description     : Function to Control the BT43 Settings                                         */
/*                                                                                                */
/* In Params       : en_fID, p_fInData, u32_fInDataLen                                            */
/*                                                                                                */
/* Out Params      : p_fOutData, u32_fOutDataLen                                                  */
/*                                                                                                */
/* Return Value    : EN_BT43_STATUS_t                                                              */
/**************************************************************************************************/

EN_BT43_RESULT_t BT43_Ioctrl(EN_BT43_IOCTRL_ID_t en_fID, void *p_fInData, INT32U u32_fInDataLen, \
						void *p_fOutData, INT32U *pu32_fOutDataLen)
{
	EN_BT43_RESULT_t en_lStnStatus = BT43_SUCCESS;
	
	switch(en_fID)
	{
	case BT43_IOCTRL_RESET_FIFO:
	{
		/* Reset the Fifo */
		BT43_ResetFifo();
	}
	break;
	
	case BT43_IOCTRL_GET_FIFO_REF:
	{
		/* Return Fifo Reference */
		*((INT8U **)p_fOutData) = BT43_GetFifoRef((INT32U *)pu32_fOutDataLen);
		//*pu32_fOutDataLen = 1;
		
		/* Reset FIFO */
		BT43_ResetFifo();
	}
	break;
	
	case BT43_CALL_BACK_REGISTER:
	{
		//BT43_CallBackUpdate((void (*)(INT32U))p_fInData);
	}
	break;
	
	case BT43_IOCTRL_CHANGE_SELF_BAUD:
	{
		/* Change the Controller UART baudrate */
		//en_lStnStatus = BT43_ChangeSelfBaud(*((INT32U *)p_fInData));
	}
	break;
	
	case BT43_IOCTRL_CHANGE_BT43_BAUD:
	{
		/* Change the BT43 BaudRate */
		//en_lStnStatus = BT43_ChangeBaud(*((INT32U *)p_fInData));
	}
	break;

    case BT_SET_RESTYPE:
    {
        en_gBTRespType = *((EN_BT_HANDLE_RESP_t *)p_fInData);
    }
    break;
    
    
	default:
	{
		/* Update status */
		en_lStnStatus = BT43_ERROR;
	}
	break;
	}

	return en_lStnStatus;
}

/**************************************************************************************************/
/* Function Name   : void BT43_ResetFifo(void)                                                    */
/*                                                                                                */
/* Description     : Function to Reset the fifo                                                   */
/*                                                                                                */
/* In Params       : void                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

INT8U* BT43_GetFifoRef(INT32U *u32_fDatalength)
{
    *u32_fDatalength  = u32_gDataRcvdIndex;
    return u8_gBTRxBuffer;
}

/**************************************************************************************************/
/* Function Name   : void BT43_ResetFifo(void)                                                    */
/*                                                                                                */
/* Description     : Function to Reset the fifo                                                   */
/*                                                                                                */
/* In Params       : void                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void BT43_ResetFifo(void)
{
    //memset(&u8_gBTRxBuffer[0], 0x00 ,BT43_BUFFER_SIZE);
    u32_gDataRcvdIndex = 0x00;
    
}

/**************************************************************************************************/
/* Function Name   : INT8U GL6B_CheckCmdResponse(INT8U * p_fCmdInput, INT8U * p_fCmdResponse)     */
/*                                                                                                */
/* Description     : Processing the Response                                                      */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : p_fBuffer                                                                    */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

INT8U BT43_CheckCmdResponse(INT8U * p_fCmdInput, INT8U * p_fCmdResponse)
{
	char * p_lTemp = 0;
	INT32U u32_lIndex = 0;
	
	/* Rset buffer before sending Command */
	BT43_ResetFifo();
	
	/* Transmit the Packed buffer */
	UART_TransmitString(st_gBT43_UartParams.en_mSERCOMChnl, (INT8U *)p_fCmdInput);
	
	/* Wait For Farme Receive */	
	for(u32_lIndex = 0; u32_lIndex < 100000; u32_lIndex++);

    /* Check Either For Command  Mode Response or COnfiguration Response */
    if(1 == u8_gBT43CmdMode)
    {
       p_lTemp = strstr((const char *)&au8_gBT43CmdRespBuf[0],
                                              (const char *)p_fCmdResponse);
    }
    else
    {
       p_lTemp = strstr((const char *)&u8_gBTRxBuffer[0],
                                              (const char *)p_fCmdResponse);
    }
   
    /* Return 1 if There is no Data */
    if(NULL == p_lTemp)
    {
        return 1;
    }
    else
    {
        /* No Action */
    }

    return 0;
}

/**************************************************************************************************/
/* End of BT43.c                                                                                  */
/**************************************************************************************************/
