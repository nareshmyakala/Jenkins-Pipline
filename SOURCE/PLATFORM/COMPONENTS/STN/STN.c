/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2018, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/*  File Name   : STN.c                                                                           */
/*  Author      : SANTHOSH                                                                        */
/*  Version 	: V1.0                                                                            */
/*  Date        : 16-05-2019                                                                      */
/*                                                                                                */
/* @Description : STN Interface frame work                                                        */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <stdio.h>
#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "GPIO.h"
#include "UART.h"

#include "MSG4_App.h"

#include "STN.h"
#include "STN_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/* STN Tx Port Pin config */
#define STN_TX_PORT					( GPIO_PORT_A )
#define STN_TX_PIN					( GPIO_PIN_9 )
#define STN_TX_PERIPH				( GPIO_PERIPHERAL_D )

/* STN Rx Port pin Config */
#define STN_RX_PORT					( GPIO_PORT_A )
#define STN_RX_PIN					( GPIO_PIN_8 )
#define STN_RX_PERIPH				( GPIO_PERIPHERAL_D )

/* STN Rx Port pin Config */
#define STN_STB_PORT			    ( GPIO_PORT_A )
#define STN_STB_PIN					( GPIO_PIN_14 )
#define STN_STB_PERIPH				( GPIO_GENERAL_PURPOSE )

/* STN Reset Port Pin Cconfig */
#define STN_RESET_PORT				( GPIO_PORT_B )
#define STN_RESET_PIN				( GPIO_PIN_9 )
#define STN_RESET_PERIPH			( GPIO_GENERAL_PURPOSE )

/* STN Uart Channel config */
#define STN_UART_CH					( SERCOM_CH_2 )
#define STN_UART_TX_PAD				( SERCOM_TX_PAD0 )
#define STN_UART_RX_PAD				( SERCOM_RX_PAD1 ) 
#define STN_UART_DEFAULT_BAUD		( 9600 )
#define STN_UART_USER_RX_HANDLER	( STN_RxHandler ) 

/* STN RX FIFO Size */
#define STN_RX_FIFO_SIZE			( 4096 )

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Stn Call back register function pointer */
static void (*pf_gStnCallBackRegister)(INT32U u32_fDataLen);

EN_STN_HANDLE_RESP_t en_gStnRespType = STN_PROMPT;

/* Stn Delay counter */
static INT32U u32_gSTNDelayCounter = 0;

/* STN Fifo variables */
static volatile INT32U u32_gSTNRxFifoFront = 0;
static volatile INT32U u32_gSTNRxFifoRare = 0;
static volatile INT32U u32_gSTNRxFifoAvail = 0;

static INT8U au8_gSTNRxFifo[STN_RX_FIFO_SIZE] = {0, };

/* Last charected backup */
static INT8U u8_gStnLastChar = 0;

/**************************************************************************************************/
/* Function Name   : void STN_Delay(INT32U u32_fDelay)                                            */
/*                                                                                                */
/* Description     : To Give delay                                                                */
/*                                                                                                */
/* In Params       : u32_fDelay                                                                   */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

static void STN_WaitingDelay(INT32U u32_fDelay)
{
	/* Reset Delay counter */
	u32_gSTNDelayCounter = 0;
	
	/* Wait till delay */
	while(u32_gSTNDelayCounter < u32_fDelay);
}

/**************************************************************************************************/
/* Function Name   : INT32U STN_ReadFifoLength(void)                                              */
/*                                                                                                */
/* Description     : Function to Read the fifo length                                             */
/*                                                                                                */
/* In Params       : void                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : INT32U                                                                       */
/**************************************************************************************************/

static INT32U STN_ReadFifoLength(void)
{
	/* Return available data length in fifo */
	return u32_gSTNRxFifoAvail;
}

/**************************************************************************************************/
/* Function Name   : void STN_ResetFifo(void)                                                     */
/*                                                                                                */
/* Description     : Function to Reset the fifo                                                   */
/*                                                                                                */
/* In Params       : void                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

static void STN_ResetFifo(void)
{
	/* Resetting Fifo variables */
	u32_gSTNRxFifoFront = 0;
    u32_gSTNRxFifoRare = 0;
    u32_gSTNRxFifoAvail = 0;
}

/**************************************************************************************************/
/* Function Name   : EN_STN_STATUS_t STN_WriteFifo(INT8U u8_fData)                                */
/*                                                                                                */
/* Description     : To write to FIFO                                                             */
/*                                                                                                */
/* In Params       : u8_fData                                                                     */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_STN_STATUS_t                                                              */
/**************************************************************************************************/

static EN_STN_STATUS_t STN_WriteFifo(INT8U u8_fData)
{
	EN_STN_STATUS_t en_lStnStatus = STN_SUCCESS;
	
	/* Check for Fifo over flow */
	if(u32_gSTNRxFifoAvail < STN_RX_FIFO_SIZE)
	{
		/* Write data to FIFO */
		au8_gSTNRxFifo[u32_gSTNRxFifoRare] = u8_fData;
		u32_gSTNRxFifoRare = u32_gSTNRxFifoRare + 1;
		u32_gSTNRxFifoAvail = u32_gSTNRxFifoAvail + 1;

		/* Check for rare value */
		if(u32_gSTNRxFifoRare == STN_RX_FIFO_SIZE)
		{
			u32_gSTNRxFifoRare = 0;
		}
		else
		{
			/* No Action */
		}
	}
	else
	{
		/* Update status */
		en_lStnStatus = STN_FAIL;
	}
		
	return en_lStnStatus;
}

/**************************************************************************************************/
/* Function Name   : INT8U STN_ReadFifo(void)                                                     */
/*                                                                                                */
/* Description     : To Read data from Queue                                                      */
/*                                                                                                */
/* In Params       : void                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : INT8U                                                                        */
/**************************************************************************************************/

static INT8U STN_ReadFifo(void)
{
	INT8U u8_lData = 0;
	
	/* Check for Fifo over flow */
	if(u32_gSTNRxFifoAvail > 0)
	{
		/* Read Data from the Queue */
		u8_lData = au8_gSTNRxFifo[u32_gSTNRxFifoFront];
		u32_gSTNRxFifoFront = u32_gSTNRxFifoFront + 1;
		u32_gSTNRxFifoAvail = u32_gSTNRxFifoAvail - 1;

		/* Check for Frot */
		if(u32_gSTNRxFifoFront == STN_RX_FIFO_SIZE)
		{
			u32_gSTNRxFifoFront = 0;
		}
		else
		{
			/* No Action */
		}
		
		return u8_lData;
	}
	else
	{
		/* Reset FIFO */
		STN_ResetFifo();
		
		/* Update status */
		return u8_lData;
	}
}

/**************************************************************************************************/
/* Function Name   : void STN_ResetFifo(void)                                                     */
/*                                                                                                */
/* Description     : Function to Reset the fifo                                                   */
/*                                                                                                */
/* In Params       : void                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

static INT8U* STN_GetFifoRef(void)
{
	return au8_gSTNRxFifo;
}

/**************************************************************************************************/
/* Function Name   : void STN_CallBackUpdate(void (*pf_fCallBack)(INT32U u32_fLength))            */
/*                                                                                                */
/* Description     : Function to Update call back                                                 */
/*                                                                                                */
/* In Params       : pf_fCallBack                                                                 */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

static void STN_CallBackUpdate(void (*pf_fCallBack)(INT32U u32_fLength))
{
	pf_gStnCallBackRegister = pf_fCallBack;
}

/**************************************************************************************************/
/* Function Name   :                                                                              */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

static void STN_RxHandler(INT8U u8_fData)
{
    if(STN_NO_RECEIVE != en_gStnRespType && 0x00 == u8_gSTNMntrFlag)
    {
        /* Write data to FIFO */
        STN_WriteFifo(u8_fData);
        
        switch(en_gStnRespType)
        {
        case STN_PROMPT:
        {
            if(u8_fData == '>' && 0x00 == u8_gSTNMntrFlag)
            {
                /* Check for Call register */
                if(pf_gStnCallBackRegister != PNULL)
                {
                    /* Trigger User Call Back */
                    (*pf_gStnCallBackRegister)(STN_ReadFifoLength());
                }
                else
                {
                    /* No Action */
                }
            }
            else
            {
                /* No Action */
            }
        }
        break;
        case STN_FLASHING:
        {
            /* Check for Call back condition */
            if((u8_fData == 0x04) && (u8_gStnLastChar != 0x05))
            {
                /* Check for Call register */
                if(pf_gStnCallBackRegister != PNULL)
                {
                    /* Trigger User Call Back */
                    (*pf_gStnCallBackRegister)(STN_ReadFifoLength());
                }
                else
                {
                    /* No Action */
                }
            }
            else
            {
                /* Back up last char */
                u8_gStnLastChar = u8_fData;
            }
        }
        default:
        {
            /* No Action */
            
        }
        break;
        }
    }
    else if(0x01 == u8_gSTNMntrFlag)  // for contineos monitor
    {
       UART_TransmitChar(SERCOM_CH_0, u8_fData);
    }
    else
    {
        /* No Action */
    }
}

/**************************************************************************************************/
/* Function Name   : EN_STN_STATUS_t STN_ChangeSelfBaud(INT32U u32_fBaudRate)                     */
/*                                                                                                */
/* Description     : To change controller Uart baudrate                                           */
/*                                                                                                */
/* In Params       : u32_fBaudRate                                                                */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_STN_STATUS_t                                                              */
/**************************************************************************************************/

static EN_STN_STATUS_t STN_ChangeSelfBaud(INT32U u32_fBaudRate)
{
	EN_STN_STATUS_t en_lStnStatus = STN_SUCCESS;
	
	/* Structure to Configure UART */
	ST_UART_CONFIG_PARAMS_t st_lSTNUartConfig = 
	{
		.en_mSERCOMChnl	= STN_UART_CH,
		.en_mDataBits =	USART_CH_SIZE_8_BITS,
		.en_mStopBits = USART_ONE_STOP_BIT,
		.en_mParity = USART_PARITY_DISABLE,
		.u32_mBaudrate = STN_UART_DEFAULT_BAUD,
		.en_mTXPad = STN_UART_TX_PAD,
		.en_mRXPad = STN_UART_RX_PAD,
		.fp_USERHANDLER	= STN_UART_USER_RX_HANDLER
	};
	
	/* Check for Invalid baudrate*/
	if(u32_fBaudRate > 0)
	{
		/* Change UART Baud Rate */
		st_lSTNUartConfig.u32_mBaudrate = u32_fBaudRate;
		UART_Init(&st_lSTNUartConfig);
	}
	else
	{
		/* Init Uart */
		UART_Init(&st_lSTNUartConfig);
		
		/* Update status */
		en_lStnStatus = STN_FAIL;
	}
	
	return en_lStnStatus;
}

/**************************************************************************************************/
/* Function Name   : EN_STN_STATUS_t STN_ChangeBaud(INT32U u32_fBaudRate)                         */
/*                                                                                                */
/* Description     : TO change STN baudrate                                                       */
/*                                                                                                */
/* In Params       : u32_fBaudRate                                                                */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_STN_STATUS_t                                                              */
/**************************************************************************************************/

static EN_STN_STATUS_t STN_ChangeBaud(INT32U u32_fBaudRate)
{
	EN_STN_STATUS_t en_lStnStatus = STN_SUCCESS;
	void (*pf_gBackUpCallBack)(INT32U u32_fDataLen);
	INT8U au8_lTempBuffer[25] = {0, };
	
	/* Take Call Back Up of Call back */
	pf_gBackUpCallBack = pf_gStnCallBackRegister;
	
	/* Make User call back Null */
	pf_gStnCallBackRegister = PNULL;

	/* Send ATZ and wait for Some time */
	STN_WriteData((INT8U *)"ATZ\r\n", strlen("ATZ\r\n"));
	STN_WaitingDelay(1500);
	
	/* Send Echo off and wait for some delay */
	STN_WriteData((INT8U *)"ATE0\r\n", strlen("ATE0\r\n"));
	STN_WaitingDelay(500);
	
	/* Check for Valid baudrate */
	if(u32_fBaudRate > 0)
	{
		/* Send change baud rate command and waite */
		sprintf((char *)au8_lTempBuffer, "STSBR %u\r\n", u32_fBaudRate);
		STN_WriteData(au8_lTempBuffer, strlen((const char *)au8_lTempBuffer));
		STN_WaitingDelay(500);

		/* Change controller baudrate */
		STN_ChangeSelfBaud(u32_fBaudRate);

		/* Save Baud rate */
		STN_WriteData((INT8U *)"STWBR\r\n", strlen("STWBR\r\n"));
		STN_WaitingDelay(1000);
	}
	else
	{
		/* Update the Status */
		en_lStnStatus = STN_FAIL; 
	}
	
	/* Reset the FIFO */
	STN_ResetFifo();
	
	/* Re register call back */
	pf_gStnCallBackRegister = pf_gBackUpCallBack;
	
	return en_lStnStatus;
}

/**************************************************************************************************/
/* Function Name   : EN_STN_STATUS_t STN_EnterBootLoader(void)                                    */
/*                                                                                                */
/* Description     : Function to Send STN to Bootloader                                           */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_STN_STATUS_t                                                              */
/**************************************************************************************************/

static EN_STN_STATUS_t STN_EnterBootLoader(void)
{
    EN_STN_STATUS_t en_lStnStatus = STN_SUCCESS;
    void (*pf_gBackUpCallBack)(INT32U u32_fDataLen);

    INT8U au8_lEnterBootCommand[8] = {0x55, 0x55, 0x03, 0x00, 0x00, 0x59, 0x50, 0x04};

    /* Take Call Back Up of Call back */
	pf_gBackUpCallBack = pf_gStnCallBackRegister;
    
    /* Make User call back Null */
	pf_gStnCallBackRegister = PNULL;
    
    /* Reset the STN  */
    STN_WriteData((INT8U *)"atz\r\n", strlen("atz\r\n"));
    STN_WaitingDelay(100);

    /* Reset the FIFO */
	STN_ResetFifo();
    
    for(INT8U u8_lIndex = 0; u8_lIndex < 3; u8_lIndex++)
    {
        /* Enter Boot Loader */
        STN_WriteData(au8_lEnterBootCommand, 8);
        STN_WaitingDelay(200);
        
        if((au8_gSTNRxFifo[0] == 0x55) && (au8_gSTNRxFifo[2] == 0x43))
        {
            STN_ResetFifo();
            break;
        }
        else
        {
            STN_ResetFifo();
            
            en_lStnStatus = STN_FAIL;
        }
    }

    /* Re register call back */
    pf_gStnCallBackRegister = pf_gBackUpCallBack;
    
    return en_lStnStatus;
}

/**************************************************************************************************/
/* Function Name   : void COMMON_Dec2Ascii(INT8U * P_fDst, INT32U u32_fSrc, INT8U u8_fLength)     */
/*                                                                                                */
/* Description     : Parse and Process the Received Command.                                      */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : METER_BUS_RESULT ( return 1 for Success, 0 for Failure )                     */
/**************************************************************************************************/

static EN_STN_STATUS_t  CAN_TestCheck(void)
{
    EN_STN_STATUS_t en_lStnStatus = STN_SUCCESS;
     
    void (*pf_gBackUpCallBack)(INT32U u32_fDataLen);  /* Take Call Back Up of Call back */

    INT8U *u8_lCANChekPointr = 0x00;
    
     pf_gBackUpCallBack = pf_gStnCallBackRegister;
    
    /* Make User call back Null */
	pf_gStnCallBackRegister = PNULL;
    
    /* echo Off */
    STN_WriteData((INT8U *)"ate0\r\n" , strlen("ate0\r\n"));
   /* Wait for delay */
	STN_WaitingDelay(200);

	/* Reset FIFO */
    STN_ResetFifo();

    /* echo Off */
    STN_WriteData((INT8U *)"atsp6\r\n", strlen("atsp6\r\n"));
    /* Wait for delay */
	STN_WaitingDelay(100);

    /* Reset FIFO */
    STN_ResetFifo();

    /* echo Off */
    STN_WriteData((INT8U *)"atsh7e0\r\n", strlen("atsh7e0\r\n"));
    /* Wait for delay */
	STN_WaitingDelay(100);

    /* Reset FIFO */
    STN_ResetFifo();

    /* send the PID */
    STN_WriteData((INT8U *)"0100\r\n", strlen("0100\r\n"));
    /* Wait for delay */
	STN_WaitingDelay(500);

    u8_lCANChekPointr = STN_GetFifoRef();
    
    /* check for Positive Response */
    if( PNULL != (INT8U *)strstr((const char *)&u8_lCANChekPointr[0] , ("4100")))
    {
        en_lStnStatus =  STN_SUCCESS;
    }
    /* Check for Negative Response */
    else if( PNULL != (INT8U *)strstr((const char *)&u8_lCANChekPointr[0] , ("ERROR")))
    {
        en_lStnStatus =  STN_FAIL;
    }

   /* Reset FIFO */
    STN_ResetFifo();

    /* Re register call back */
    pf_gStnCallBackRegister = pf_gBackUpCallBack;
    
    /* Return the Result */
    return en_lStnStatus;
}

/**************************************************************************************************/
/* Function Name   : void COMMON_Dec2Ascii(INT8U * P_fDst, INT32U u32_fSrc, INT8U u8_fLength)     */
/*                                                                                                */
/* Description     : Parse and Process the Received Command.                                      */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : METER_BUS_RESULT ( return 1 for Success, 0 for Failure )                     */
/**************************************************************************************************/

static EN_STN_STATUS_t  Kline_TestCheck(void)
{
    EN_STN_STATUS_t en_lStnStatus = STN_SUCCESS;
    
    void (*pf_gBackUpCallBack)(INT32U u32_fDataLen);  /* Take Call Back Up of Call back */

    INT8U *u8_lCANChekPointr = 0x00;
    
     pf_gBackUpCallBack = pf_gStnCallBackRegister;
    
    /* Make User call back Null */
	pf_gStnCallBackRegister = PNULL;
    
    /* echo Off */
    STN_WriteData((INT8U *)"ate0\r\n" , strlen("ate0\r\n"));
   /* Wait for delay */
	STN_WaitingDelay(200);

	/* Reset FIFO */
    STN_ResetFifo();

    /* echo Off */
    STN_WriteData((INT8U *)"atsp6\r\n", strlen("atsp5\r\n"));
    /* Wait for delay */
	STN_WaitingDelay(100);

    /* Reset FIFO */
    STN_ResetFifo();

    /* send the PID */
    STN_WriteData((INT8U *)"0100\r\n", strlen("0100\r\n"));
    /* Wait for delay */
	STN_WaitingDelay(300);

    u8_lCANChekPointr = STN_GetFifoRef();
    
    /* check for Positive Response */
    if( PNULL != (INT8U *)strstr((const char *)&u8_lCANChekPointr[0] , ("4100")))
    {
        en_lStnStatus =  STN_SUCCESS;
    }
    /* Check for Negative Response */
    else if( PNULL != (INT8U *)strstr((const char *)&u8_lCANChekPointr[0] , ("ERROR")))
    {
        en_lStnStatus =  STN_FAIL;
    }

   /* Reset FIFO */
    STN_ResetFifo();

    /* Re register call back */
    pf_gStnCallBackRegister = pf_gBackUpCallBack;
    
    /* Return the Result */
    return en_lStnStatus;
}


/**************************************************************************************************/
/* Function Name   : EN_STN_STATUS_t STN_GetSerialNumber(INT8U *pu8_fOutBuffer)                   */
/*                                                                                                */
/* Description     : Function to Read STN Serial Number                                           */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : pu8_fOutBuffer                                                               */
/*                                                                                                */
/* Return Value    : EN_STN_STATUS_t                                                              */
/**************************************************************************************************/

static EN_STN_STATUS_t STN_GetSerialNumber(INT8U *pu8_fOutBuffer, INT32U *pu32_fLength)
{
    EN_STN_STATUS_t en_lStnStatus = STN_SUCCESS;
	void (*pf_lBackUpCallBack)(INT32U u32_fDataLen);
    
    /* Take Call Back Up of Call back */
	pf_lBackUpCallBack = pf_gStnCallBackRegister;
	
	/* Make User call back Null */
	pf_gStnCallBackRegister = PNULL;
    
    /* Send Echo off and wait for some delay */
	STN_WriteData((INT8U *)"ATE0\r\n", strlen("ATE0\r\n"));
	STN_WaitingDelay(150);
    
    /* Reset the FIFO */
	STN_ResetFifo();
    
    /* Send Echo off and wait for some delay */
	STN_WriteData((INT8U *)"STSN\r\n", strlen("STSN\r\n"));
	STN_WaitingDelay(300);
    
    if(STN_ReadFifoLength() >= 12)
    {
        STN_ReadData(pu8_fOutBuffer, 12);
        *pu32_fLength = 12;
    }
    else
    {
        en_lStnStatus = STN_FAIL;
    }
    
    /* Reset the FIFO */
	STN_ResetFifo();
	
	/* Re register call back */
	pf_gStnCallBackRegister = pf_lBackUpCallBack;
    
    return en_lStnStatus;
}

/**************************************************************************************************/
/* Function Name   : void STN_1MsHandler(void)                                                    */
/*                                                                                                */
/* Description     : Function For 1ms Handler                                                     */
/*                                                                                                */
/* In Params       : void                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void STN_1MsHandler(void)
{
	/* Increment delay counter */
	u32_gSTNDelayCounter = u32_gSTNDelayCounter + 1;
}

/**************************************************************************************************/
/* Function Name   : void STN_Init(ST_STN_INIT_t *pst_gStnConfig)                                 */
/*                                                                                                */
/* Description     : Function to init the stn                                                     */
/*                                                                                                */
/* In Params       : pst_gStnConfig : Structure  to configure STN                                 */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void STN_Init(ST_STN_INIT_t *pst_gStnConfig)
{
	/* Structure for GPIO Configuration */
	ST_GPIO_PARAMS_t st_lStnPinConfig = 
	{
		.en_mPortSel = GPIO_PORT_A,
		.en_mPinSel = GPIO_PIN_8,
		.en_mPinDir = GPIO_DIR_OUTPUT,
		.en_mPinType = GPIO_PULL_LVL_DIS,
		.en_mPinPeriph = GPIO_PERIPHERAL_C,
		.en_mDriverStrenght	= GPIO_DRIV_STRENGTH_NORMAL
	};
	
	/* Structure to Configure UART */
	ST_UART_CONFIG_PARAMS_t st_lSTNUartConfig = 
	{
		.en_mSERCOMChnl	= SERCOM_CH_2,
		.en_mDataBits =	USART_CH_SIZE_8_BITS,
		.en_mStopBits = USART_ONE_STOP_BIT,
		.en_mParity = USART_PARITY_DISABLE,
		.u32_mBaudrate = 0,
		.en_mTXPad = SERCOM_TX_PAD0,
		.en_mRXPad = SERCOM_RX_PAD1,
		.fp_USERHANDLER	= STN_RxHandler,
	};

	/* Configure UART Tx Pin */
	st_lStnPinConfig.en_mPortSel = STN_TX_PORT;
	st_lStnPinConfig.en_mPinSel = STN_TX_PIN;
	st_lStnPinConfig.en_mPinDir = GPIO_DIR_OUTPUT;
	st_lStnPinConfig.en_mPinPeriph = STN_TX_PERIPH;
	
	GPIO_Init(&st_lStnPinConfig);
	
	/* Configure UART Rx Pin */
	st_lStnPinConfig.en_mPortSel = STN_RX_PORT;
	st_lStnPinConfig.en_mPinSel = STN_RX_PIN;
	st_lStnPinConfig.en_mPinDir = GPIO_DIR_INPUT;
	st_lStnPinConfig.en_mPinPeriph = STN_RX_PERIPH;
	
	GPIO_Init(&st_lStnPinConfig);
	
    /* Configure UART Rx Pin */
	st_lStnPinConfig.en_mPortSel = STN_STB_PORT;    
	st_lStnPinConfig.en_mPinSel = STN_STB_PIN;
	st_lStnPinConfig.en_mPinDir = GPIO_DIR_OUTPUT;
	st_lStnPinConfig.en_mPinPeriph = STN_STB_PERIPH;
	
	GPIO_Init(&st_lStnPinConfig);
    
	/* Configure STN UART */
	st_lSTNUartConfig.en_mSERCOMChnl = STN_UART_CH;
	
	if(pst_gStnConfig->u32_mBaudRate > 0)
	{
		st_lSTNUartConfig.u32_mBaudrate = pst_gStnConfig->u32_mBaudRate;
	}
	else
	{
		st_lSTNUartConfig.u32_mBaudrate = STN_UART_DEFAULT_BAUD;
	}
	
	st_lSTNUartConfig.en_mTXPad = STN_UART_TX_PAD;
	st_lSTNUartConfig.en_mRXPad = STN_UART_RX_PAD;
	st_lSTNUartConfig.fp_USERHANDLER = STN_UART_USER_RX_HANDLER;

	UART_Init(&st_lSTNUartConfig);
	
	/* Configure Reset Pin */
	st_lStnPinConfig.en_mPortSel = STN_RESET_PORT;
	st_lStnPinConfig.en_mPinSel = STN_RESET_PIN;
	st_lStnPinConfig.en_mPinDir = GPIO_DIR_OUTPUT;
	st_lStnPinConfig.en_mPinPeriph = STN_RESET_PERIPH;
	
	GPIO_Init(&st_lStnPinConfig);
	
	/* Reset STN */
	GPIO_ResetPin(STN_RESET_PORT, STN_RESET_PIN);
	STN_WaitingDelay(500);
    GPIO_SetPin(STN_RESET_PORT, STN_RESET_PIN);
	
	/* Wait for delay */
	STN_WaitingDelay(1000);
	
	/* Register the STN call back */
    
    if(PNULL != pst_gStnConfig->pf_mStnCallBack)
    {
        pf_gStnCallBackRegister = pst_gStnConfig->pf_mStnCallBack;
    }
    else
    {
        /* No Action */
    }
	
	/* Reset the FIFO */
	STN_ResetFifo();
    
    /* Reset STN */
	GPIO_ResetPin(STN_STB_PORT, STN_STB_PIN);
}

/**************************************************************************************************/
/* Function Name   : void STN_ReadData(INT8U *pu8_fData, INT32U u32_lLength)		              */
/*                                                                                                */
/* Description     : Read the Data                                                                */
/*                                                                                                */
/* In Params       : u32_lLength : Number of byte to be Read                                      */
/*                                                                                                */
/* Out Params      : pu8_fData : Buffer to Data from Fifo                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void STN_ReadData(INT8U *pu8_fData, INT32U u32_lLength)
{
	/* Read data from FIFO and update the data buffer */
	for(INT32U u32_lIndex = 0; u32_lIndex < u32_lLength; u32_lIndex++)
	{	
		pu8_fData[u32_lIndex] = STN_ReadFifo();
	}
}

/**************************************************************************************************/
/* Function Name   : void STN_WriteData(INT8U *pu8_fData, INT32U u32_fLength)                     */
/*                                                                                                */
/* Description     : To Write data to STN                                                         */
/*                                                                                                */
/* In Params       : pu8_fData, u32_fLength                                                       */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void STN_WriteData(INT8U *pu8_fData, INT32U u32_fLength)
{
    
	for(INT32U u32_lIndex = 0; u32_lIndex < u32_fLength; u32_lIndex++)
	{	
		/* Send data to STN */
		UART_TransmitChar(STN_UART_CH, pu8_fData[u32_lIndex]);
	}
}

/**************************************************************************************************/
/* Function Name   : EN_STN_STATUS_t STN_Ioctrl(EN_STN_IOCTRL_ID_t en_fID, INT8U *pu8_fInData, \  */
/*						INT32U u32_fInDataLen, INT8U *pu8_fOutData, INT32U u32_fOutDataLen);      */
/*                                                                                                */
/* Description     : Function to Control the STN Settings                                         */
/*                                                                                                */
/* In Params       : en_fID, p_fInData, u32_fInDataLen                                            */
/*                                                                                                */
/* Out Params      : p_fOutData, u32_fOutDataLen                                                  */
/*                                                                                                */
/* Return Value    : EN_STN_STATUS_t                                                              */
/**************************************************************************************************/

EN_STN_STATUS_t STN_Ioctrl(EN_STN_IOCTRL_ID_t en_fID, void *p_fInData, INT32U u32_fInDataLen, \
													  void *p_fOutData, INT32U *pu32_fOutDataLen)
{
	EN_STN_STATUS_t en_lStnStatus = STN_SUCCESS;
	
	switch(en_fID)
	{
	case STN_IOCTRL_RESET_FIFO:
	{
		/* Reset the Fifo */
		STN_ResetFifo();
	}
	break;
	
	case STN_IOCTRL_GET_FIFO_REF:
	{
		/* Return Fifo Reference */
		*((INT8U **)p_fOutData) = STN_GetFifoRef();
		*pu32_fOutDataLen = 1;
		
		/* Reset FIFO */
		STN_ResetFifo();
	}
	break;
	
	case STN_CALL_BACK_REGISTER:
	{
		STN_CallBackUpdate((void (*)(INT32U))p_fInData);
	}
	break;
	
	case STN_IOCTRL_CHANGE_SELF_BAUD:
	{
		/* Change the Controller UART baudrate */
		en_lStnStatus = STN_ChangeSelfBaud(*((INT32U *)p_fInData));
	}
	break;
	
	case STN_IOCTRL_CHANGE_STN_BAUD:
	{
		/* Change the STN BaudRate */
		en_lStnStatus = STN_ChangeBaud(*((INT32U *)p_fInData));
	}
	break;
    
    case STN_IOCTRL_GET_STN_S_NO:
    {
        en_lStnStatus = STN_GetSerialNumber((INT8U *)p_fOutData, pu32_fOutDataLen);
    }
    break;
    
	case STN_SET_RESTYPE:
    {
        en_gStnRespType = *((EN_STN_HANDLE_RESP_t *)p_fInData);
    }   
    break;
    
    case STN_ENTER_BOOTLOADER:
    {
        en_lStnStatus = STN_EnterBootLoader();    
    }
    break;
    
    case STN_CAN_CHECK:
    {
        en_lStnStatus = CAN_TestCheck();
    }
    break;
    
    case STN_KLINE_CHECK:
    {
        en_lStnStatus = Kline_TestCheck();
    }
    break;
    
	default:
	{
		/* Update status */
		en_lStnStatus = STN_FAIL;
	}
	break;
	}

	return en_lStnStatus;
}

void STN_STBCntrl(STN_STB_CNTRL_t en_mSTB_Cntrl)
{
    if(DISABLE == en_mSTB_Cntrl)
    {
        /* Reset STN */
        GPIO_SetPin(STN_STB_PORT, STN_STB_PIN);
    }
    else
    {
        /* Reset STN */
        GPIO_ResetPin(STN_STB_PORT, STN_STB_PIN);
    }
    
}

void STN_Reset(void)
{
  	GPIO_ResetPin(STN_RESET_PORT, STN_RESET_PIN);
	STN_WaitingDelay(500);
    GPIO_SetPin(STN_RESET_PORT, STN_RESET_PIN);
}
/**************************************************************************************************/
/* End of  STN.c                                                                                  */
/**************************************************************************************************/
