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
/*  File Name   : TBUS.c                                                                          */
/*  Author      :                                                                                 */
/*  Version 	: v1.0                                                                            */
/*  Date        : 17-02-2022                                                                      */
/*                                                                                                */
/* @Description : TBUS Service Frame Work                                                         */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "DATACONV.h"

#include "GPIO.h"
#include "UART.h"
#include "ADC_SCOPE.h"

#include "TBUS.h"
#include "TBUS_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

#define TBUS_UART_CHANNEL               ( SERCOM_CH_2 )

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* */
INT8U au8_gTBUSRxData[TBUS_BUFF_SIZE] = {0,};
INT32U u32_gTBUSRxIndex = 0;
INT8U u8_gTBUSCmdRecvd = 0;

/* */
INT8U au8_gTBUSTxData[TBUS_BUFF_SIZE] = {0,};

/* Variable to hold  SID */
INT8U u8_gServiceID;
INT8U u8_gDataID;

/* Variable to hold Frame length */
INT16U u16_gRxFrameLength = 0;


/* Port Configuration for UART RX */
ST_GPIO_PARAMS_t st_gTBUSTxPin = 
{
    .en_mPortSel	= GPIO_PORT_A,
    .en_mPinSel		= GPIO_PIN_13,    
    .en_mPinDir		= GPIO_DIR_OUTPUT,
    .en_mPinType	= GPIO_PULL_LVL_DIS,
    .en_mPinPeriph	= GPIO_PERIPHERAL_D,
    .en_mDriverStrenght	= GPIO_DRIV_STRENGTH_NORMAL
};

/* Port Configuration for UART RX */
ST_GPIO_PARAMS_t st_gTBUSRxPin = 
{
    .en_mPortSel	= GPIO_PORT_A,
    .en_mPinSel		= GPIO_PIN_12,    
    .en_mPinDir		= GPIO_DIR_INPUT,
    .en_mPinType	= GPIO_PULL_LVL_DIS,
    .en_mPinPeriph	= GPIO_PERIPHERAL_D,
    .en_mDriverStrenght	= GPIO_DRIV_STRENGTH_NORMAL
    
};

ST_UART_CONFIG_PARAMS_t st_gTBUSUartConfig = 
{
    .en_mSERCOMChnl	= SERCOM_CH_4,
    .en_mDataBits	= USART_CH_SIZE_8_BITS,
    .en_mStopBits	= USART_ONE_STOP_BIT,
    .en_mParity		= USART_PARITY_DISABLE,
    .u32_mBaudrate	= 3000000,
    .en_mTXPad		= SERCOM_TX_PAD0,
    .en_mRXPad		= SERCOM_RX_PAD1,
    .fp_USERHANDLER	= TBUS_RxHandler,
    
};

/* */
INT8U u8_gTBUSServiceIndex = 0;
ST_TBUS_SERVICES_t st_gTBUSServices[TBUS_MAX_SERVICES] = 
{    
    {0xFF, 0x00, (void *)0}    
};


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

void TBUS_RxHandler(INT8U u8_fData)
{
    switch(u8_fData)
    {
        case TBUS_START_PREMBLE:
        {
            u32_gTBUSRxIndex = 0;
        }
        break;

        case TBUS_LF:
        {
            u8_gTBUSCmdRecvd = 1;
        }
        break;
            
        default:
        break;
    }
    
    au8_gTBUSRxData[u32_gTBUSRxIndex] = u8_fData;
    u32_gTBUSRxIndex = u32_gTBUSRxIndex + 1;
    
    /* Check the Boundary */
    if(u32_gTBUSRxIndex >= TBUS_BUFF_SIZE)
    {
        u32_gTBUSRxIndex = 0;
    }
    else
    {
        /* No Action */
    }
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

void TBUS_RxManager(void)
{
    if(1 == u8_gTBUSCmdRecvd)
    {
        u8_gTBUSCmdRecvd = 0;
        
        if(':' == au8_gTBUSRxData[0])
        {
            TBUS_ProcessResponse(au8_gTBUSRxData);
            u32_gTBUSRxIndex = 0;
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

void TBUS_Init(void)
{
    /* Configure MODEM UART Tx&Rx Pins */
    GPIO_Init(&st_gTBUSTxPin);
    GPIO_Init(&st_gTBUSRxPin);

    UART_Init(&st_gTBUSUartConfig);
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

void TBUS_ProcessResponse(INT8U *pu8_fData)
{
    INT8U u8_lIndex = 0;
    
    /* Get the Modem IF frame Length */
    if(COMMON_OK == COMMON_PAN2HWord(&au8_gTBUSRxData[TBUS_LENGTH_OFFSET], &u16_gRxFrameLength))
    {
        /* Validate the Frame Check sum */
        if(TBUS_CheckSum(&au8_gTBUSRxData[TBUS_LENGTH_OFFSET], u16_gRxFrameLength, \
                                                                        TBUS_RX_CHECKSUM))
        {
            /* Get SID */
            COMMON_PAN2Byte(&au8_gTBUSRxData[TBUS_SID_OFFSET],&u8_gServiceID);
            
            /* Get DID */
            COMMON_PAN2Byte(&au8_gTBUSRxData[TBUS_DID_OFFSET],&u8_gDataID);

            while(u8_lIndex < u8_gTBUSServiceIndex)
            {
                /* Check for the SID in serivces list */
                if(st_gTBUSServices[u8_lIndex].u8_mSID == u8_gServiceID)
                {
                    /* Call the Service Handler */
                    if(PNULL != st_gTBUSServices[u8_lIndex].fp_ServiceHandler)
                    {
                        st_gTBUSServices[u8_lIndex].fp_ServiceHandler(u8_gDataID, \
                                        &au8_gTBUSRxData[TBUS_DATA_OFFSET], u16_gRxFrameLength - 8);
                    }
                    else
                    {
                      /* No Action */
                    }
                    
                    return;
                }
                else
                {
                    u8_lIndex++;
                }
            }
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

INT8U TBUS_RegisterHandler(INT8U u8_fSid, INT8U u8_fDid, void (*fp_fHandler)(INT8U, INT8U*, INT16U))
{
    INT8U u8_lRegStatus = 0;
    
    if(u8_gTBUSServiceIndex < TBUS_MAX_SERVICES)
    {
        /* Copy Global Register Handler */
        st_gTBUSServices[u8_gTBUSServiceIndex].u8_mSID = u8_fSid;
        st_gTBUSServices[u8_gTBUSServiceIndex].u8_mDID = u8_fDid;
        st_gTBUSServices[u8_gTBUSServiceIndex].fp_ServiceHandler = fp_fHandler;
        
        /* Increment Register Handler Index */
        u8_gTBUSServiceIndex = u8_gTBUSServiceIndex + 1;
        
        u8_lRegStatus = 1;
    }
    else
    {
        /* No Action */
    }
    
    return u8_lRegStatus;
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

void TBUS_SendCommand(INT8U u8_fSID, INT8U u8_fDID, INT8U * p_fData, INT16U u16_fDataLen)
{
    INT16U u16_lFrameLength = 0;
    INT16U u16_lIndex = 0;

    /* Add StartPre Amble to Tbus Tx Buffer */
    au8_gTBUSTxData[TBUS_START_PREAMBLE_OFFSET] = TBUS_START_PREMBLE;

    /* Add Serveice ID to the Tbus Tx Buffer */
    COMMON_Byte2PAN(&au8_gTBUSTxData[TBUS_SID_OFFSET], u8_fSID);
    
    /* Add Data ID to the Modem Tx Buffer */
    COMMON_Byte2PAN(&au8_gTBUSTxData[TBUS_DID_OFFSET], u8_fDID);
    
    /* Add Data to the Modem Tx Buffer */
    for(u16_lIndex = 0; u16_lIndex < u16_fDataLen; u16_lIndex++)
    {
        au8_gTBUSTxData[TBUS_DATA_OFFSET + u16_lIndex] = p_fData[u16_lIndex];
    }
    
    /* Updating the Tx Frame lenght With Data Lenght(variable), Service Id(2) , Data Id(2), 
                                                                                       checksum(4)*/
    u16_lFrameLength = u16_fDataLen + 8;
    
    /* Add Frame to the Modem Tx Buffer  */
    COMMON_HWord2PAN(&au8_gTBUSTxData[TBUS_LENGTH_OFFSET], u16_lFrameLength);
     
    /* Caliculate the Modem Transmit frame CheckSum */
    TBUS_CheckSum(&au8_gTBUSTxData[TBUS_LENGTH_OFFSET], u16_lFrameLength, \
                                                                            TBUS_TX_CHECKSUM);
    
    /* Add End Preambles to the Modem Tx Buffer */
    au8_gTBUSTxData[u16_lFrameLength + 5] = TBUS_CR;
    au8_gTBUSTxData[u16_lFrameLength + 6] = TBUS_LF;
    
    /* Update the TotalFrame Length */
    u16_lFrameLength = u16_lFrameLength + 7;
    
    /* Send Data to modem */
    TBUS_SendData(au8_gTBUSTxData, u16_lFrameLength);
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

void TBUS_SendData(INT8U *pu8_fData, INT16U u16_fLength)
{
    INT16U u16_lIndex = 0;
    
    /* Send Data to Modem */
    for(u16_lIndex = 0; u16_lIndex < u16_fLength; u16_lIndex++)
    {
        UART_TransmitChar(TBUS_UART_CHANNEL, pu8_fData[u16_lIndex]);
    }
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

INT8U TBUS_CheckSum(INT8U *pu8_fData, INT16U u16_fLength, INT8U u8_fFlag)
{
    INT32U u32_lAccumulator = 0x00000000;
    INT16U u16_lCheckSum = 0x0000;
    INT16U u16_lRxCheckSum = 0x0000;
    INT8U u8_lResult = 0;
    INT16U u16_lIndex;
    INT8U u8_lIndex1 = 0;
    INT8U u8_lTemp = 0;
    INT8U u8_lCmpBuff[5] = {0, };
    
    /* Calculate Check Sum */
    for(u16_lIndex = 0; u16_lIndex < u16_fLength; u16_lIndex++)
    {
        u32_lAccumulator = u32_lAccumulator + *(pu8_fData + u16_lIndex);
    }
    
    u16_lCheckSum = (INT16U)(u32_lAccumulator & 0x0000FFFF);
    u16_lCheckSum = (INT16U)(~u16_lCheckSum + 1);
    u16_lIndex = (INT8U)(u16_lCheckSum & 0x00FF);
    u16_lCheckSum = 0;
    u16_lCheckSum = (INT16U)(u16_lIndex);
    u16_lCheckSum <<= 8;
    u8_lTemp = (INT8U)~(u16_lIndex);
    u16_lCheckSum |= (INT16U)(u8_lTemp);

     /* Calculate CheckSum for Transmit Message */
    if(TBUS_TX_CHECKSUM == u8_fFlag)
    {
        for(u8_lIndex1 = 0; u8_lIndex1 < 4; u8_lIndex1++)
        {
            u8_lTemp = ((u16_lCheckSum >> (12 - 4 * u8_lIndex1)) & 0x000F);
            
            /* Check the Byte nibble is in between A and F */
            if((u8_lTemp >= 0x0A) && (u8_lTemp <= 0x0F))             
            {
                *(pu8_fData + (u16_fLength + u8_lIndex1)) = u8_lTemp + 0x37;
            }
            
            /* Check the Byte nibble is in between 0 and 9 */
            else if(u8_lTemp <= 0x09)
            {
                *(pu8_fData + (u16_fLength + u8_lIndex1)) = u8_lTemp + 0x30;
            }
            else
            {
                /* No Action */
            }
        }
        
        u8_lResult = 1;
    }
    else if(TBUS_RX_CHECKSUM == u8_fFlag)
    {
        memcpy(u8_lCmpBuff, pu8_fData + u16_fLength, 4);
        u8_lCmpBuff[4] = '\0';
        
        for(u16_lIndex = 0; u16_lIndex < 4; u16_lIndex++)
        {
            /* Check the Byte nibble is in between A and F */
            if((u8_lCmpBuff[u16_lIndex] >= 0x41) && (u8_lCmpBuff[u16_lIndex] <= 0x46))
            {
                u8_lCmpBuff[u16_lIndex] = u8_lCmpBuff[u16_lIndex] - 0x37;
            }
            
            /* Check the Byte nibble is in between 0 and 9 */
            else if((u8_lCmpBuff[u16_lIndex] >= 0x39) && (u8_lCmpBuff[u16_lIndex] <= 0x30))
            {
                u8_lCmpBuff[u16_lIndex] = u8_lCmpBuff[u16_lIndex] - 0x30;
            }
            
            else
            {
                /* No Action */
            }
            
            /* Convert to Required format */
            u16_lRxCheckSum |= (INT16U)((u8_lCmpBuff[u16_lIndex] & 0x0F) << (12 - u16_lIndex * 4));
        }
        
        if(u16_lCheckSum == u16_lRxCheckSum)
        {
            u8_lResult = 1;
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
    
    return u8_lResult;
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

void TBUS_ResetHandlers(void)
{
    u8_gTBUSServiceIndex = 0;
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
  
void TBUS_Ping(INT8U u8_fDataID, INT8U *p_fPayload, INT16U u16_fLength)
{       
    INT8U u8_lAck = TBUS_ACK;
    
    /* Send ACK */
    TBUS_SendCommand(0x41, u8_fDataID, &u8_lAck, 1);
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

void TBUS_StartScope(INT8U u8_fDataID, INT8U *p_fPayload, INT16U u16_fLength)
{       
    /* Start Analog Channel Timer */
    ADC_ScopeStart();
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

void TBUS_StopScope(INT8U u8_fDataID, INT8U *p_fPayload, INT16U u16_fLength)
{       
    /* Stop Analog Channel Timer */
    ADC_ScopeStop();
}

/**************************************************************************************************/
/* End of  TBUS.c                                                                                 */
/**************************************************************************************************/
