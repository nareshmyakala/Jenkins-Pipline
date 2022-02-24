/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2016, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : ISOTP14230_TP.c                                                                 */
/* \Author      : PRASHANTH.A                                                                     */
/* \Version 	:                                                                                 */
/* \Date        : 18-10-2017                                                                      */
/*                                                                                                */
/* @Description : ISO14230 Frame Work                                                             */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <stdlib.h>
#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "DATACONV.h"

#include "XTP_public.h"
#include "UART.h"

#include "TEOBD2_public.h"

#include "ISOTP14230_TP_public.h"
#include "ISOTP14230_TP_private.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

#define KLINE_FMT_LEN_CLR       ( (INT8U)0xC0 )

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

void ISO14230_TimerHandler(void);

/* */
const INT8U au8_gKLineStartCommRqst[] = {0xC1, 0x33, 0xF1, 0x81};
const INT8U au8_gTesterPresent[4] = {0xC1, 0x33, 0xF1, 0x3E};

/* */
INT8U au8_gKLineReqBuf[KLINE_MAX_BUFF_LENGTH] = {0, };
INT8U au8_gKLineRespBuf[KLINE_MAX_BUFF_LENGTH] = {0, };
INT8U au8_gKLineReqBackupBuf[KLINE_MAX_BUFF_LENGTH] = {0, };
INT8U au8_gKLineTrasBufferp[KLINE_MAX_BUFF_LENGTH] = {0x00, };
INT16U u16_gKLineReqLength = 0;
INT16U u16_gKLineRespIndex = 0;

INT8U u8_gKLineReqByteBuffer[512] = {0, };

ST_KLINE_TIMING_PARAMS_t st_gKlintTimingParams = {0, };

/* Variables to Store Keybytes */
INT8U u8_gKeyByte1 = 0;
INT8U u8_gKeyByte2 = 0;

/* */
INT8U u8_gKlineFmtByte = KLINE_DAFAULT_FMT_BYTE;
INT8U u8_gKlineTarByte = KLINE_DAFAULT_TAR_BYTE;
INT8U u8_gKlineSrcByte = KLINE_DAFAULT_SRC_BYTE;
INT8U u8_gKlineAddLngthByte = 0x00;

volatile INT8U u8_gKlineInitSeqFlag = 0;

/* Make KLINE ( P2 )Default Timing to 3 sec */
INT32U u32_gKline_P2 = KLINE_P2_DEFAULT;
INT32U u32_gKline_P3 = KLINE_P3_DEFAULT;
INT8U u8_gKline_P4 = KLINE_P4_DEFAULT;
INT8U u8_gKLineBusy = 0;


volatile INT32U u32_gKLineTick = 0;
volatile INT32U u32_gKLineTesterCounter = 0;
volatile INT8U u8_gTesterInProgress = 0;
INT8U u8_gKlineLegntByte = 0x00;

/**************************************************************************************************/
/* Function Name   :  void ISO14230_TimerOut(void)                                               */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void ISO14230_TimerHandler(void)
{
    /* Increment KLine Tick count*/
    u32_gKLineTick = u32_gKLineTick + 1;
    
    /* Increment the Tester present Counter */
    u32_gKLineTesterCounter = u32_gKLineTesterCounter + 1; 
} 

/**************************************************************************************************/
/* Function Name   :  ISO14230_RxHandler()                                                       */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void ISO14230_RxHandler(INT8U u8_fRxData)
{
    /* Copy the byte to buffer */
    au8_gKLineRespBuf[u16_gKLineRespIndex] = u8_fRxData;

    /* Incrementing index */
    u16_gKLineRespIndex = u16_gKLineRespIndex + 1;   
}

/**************************************************************************************************/
/* Function Name   : ISO14230_RESULT_t ISO14230_Init(void)                                      */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

ISO14230_RESULT_t ISO14230_Init(void)
{
    ISO14230_RESULT_t en_lResult = ISO14230_SUCCESS;
    
    /* Init The KLine */
    if(PNULL != pst_gHalObjectPtr->KLine_Init)
    {
        pst_gHalObjectPtr->KLine_Init(ISO14230_RxHandler);
    }
    else
    {
        while(1);
    }
    
    if(PNULL != pst_gHalObjectPtr->KLine_ConfigGpio)
    {
        pst_gHalObjectPtr->KLine_ConfigGpio();
    }
    else
    {
        while(1);
    }
    
    /* Init the Timer */
    if(PNULL != pst_gHalObjectPtr->TimerInit)
    {
        pst_gHalObjectPtr->TimerInit(1, ISO14230_TimerHandler);
    }
    else
    {
        while(1);
    }
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : void ISO14230_TesterPresent(void)                                           */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

ISO14230_RESULT_t ISO14230_FastInit(void)
{
    ISO14230_RESULT_t en_lResult = ISO14230_SUCCESS;
    INT8U * p_lTemp = 0;
    
    /* Set KLine Pin 300mSec High */
    if(PNULL != pst_gHalObjectPtr->KLine_Reset)
    {
        pst_gHalObjectPtr->KLine_Reset();
    }
    else
    {
        while(1);
    }
    ISO14230_Delay(300);
      
    /* Set KLine Pin 25mSec Low */
    if(PNULL != pst_gHalObjectPtr->KLine_Set)
    {
        pst_gHalObjectPtr->KLine_Set();
    }
    else
    {
        while(1);
    }
    ISO14230_Delay(25);

    /* Set KLine Pin 25mSec High */
    if(PNULL != pst_gHalObjectPtr->KLine_Reset)
    {
        pst_gHalObjectPtr->KLine_Reset();
    }
    else
    {
        while(1);
    }
    ISO14230_Delay(25); 
    
    /* Configure it as UART */
    if(PNULL != pst_gHalObjectPtr->KLine_ConfigUART)
    {
        pst_gHalObjectPtr->KLine_ConfigUART();
    }
    else
    {
        while(1);
    }
    
    /* Backup the Request Message */
    u16_gKLineReqLength = 4;
    ISO14230_KLineWrite((INT8U *)&au8_gKLineStartCommRqst[0], u16_gKLineReqLength);
    
    /* Delay for P2 ms */
    ISO14230_Delay(u32_gKline_P2);
    
    /* Find the Response  */
    p_lTemp = (INT8U *)strstr((const char *)&au8_gKLineRespBuf[0], \
                                          (const char *)&au8_gKLineReqBackupBuf[0]);
    
    /* Update the Response Datat to KLine Object */
    if(PNULL != p_lTemp)
    {
        /* Seek the Location  and +1, because to eleminate Request CheckSum */
        p_lTemp = (p_lTemp + u16_gKLineReqLength + 1);
        
        if(0x00 != p_lTemp[0])
        {            
            /* Update the Key Bytes */
            u8_gKeyByte2 =  p_lTemp[4];
            u8_gKeyByte1 =  p_lTemp[5];
        }
        else
        {
            /* Update Error Status */
            en_lResult = ISO14230_ERROR;          
        }
    }
    else
    {
        /* Update Error Status */
        en_lResult = ISO14230_ERROR;
    }    
    
    /* Return the result */
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   : void ISO14230_TesterPresent(void)                                           */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

extern ST_UART_CONFIG_PARAMS_t st_gKLinePhyConfig;

ISO14230_RESULT_t ISO14230_5BaudInit(void)
{
    ISO14230_RESULT_t en_lResult = ISO14230_SUCCESS;
    INT8U * p_lTemp = 0;
   // INT8U u8_lReversedMsb = 0;
    //INT8U u8_lReversedLsb = 0;
    
    /* Set Baud Rate to 5Bits/Sec */
    st_gKLinePhyConfig.u32_mBaudrate = 5;
            
    /* Set KLine Pin 300mSec High */
    if(PNULL != pst_gHalObjectPtr->KLine_Reset)
    {
        pst_gHalObjectPtr->KLine_Reset();
    }
    else
    {
        while(1);
    }
    
    ISO14230_Delay(300);
    
    /* Configure it as UART */
    if(PNULL != pst_gHalObjectPtr->KLine_ConfigUART)
    {
        pst_gHalObjectPtr->KLine_ConfigUART();
    }
    else
    {
        while(1);
    }
    
    /* Initialize UART */
    UART_Init(&st_gKLinePhyConfig);
    
    /* Reset the Buffer */
    ISO14230_ResetKLineBuffers();
    
    /* Send Target Message */
    if(PNULL != pst_gHalObjectPtr->KLine_TransmitChar)
    {
        pst_gHalObjectPtr->KLine_TransmitChar(u8_gKlineTarByte);
    }
    else
    {
        while(1);
    }
    
    /* Delay for 25 ms */
    ISO14230_Delay(25);
    
    /* Find the Response  */
    p_lTemp = (INT8U *)strstr((const char *)&au8_gKLineRespBuf[0], (const char *)u8_gKlineTarByte);
    
    /* Update the Response Datat to KLine Object */
    if(PNULL != p_lTemp)
    {
        p_lTemp = p_lTemp + 1;
        
        if(0x55 == *p_lTemp)
        {            
            /* Set Baud Rate to 10400 KBits/Sec */
            st_gKLinePhyConfig.u32_mBaudrate = 10400;
            
            /* Configure it as UART */
            if(PNULL != pst_gHalObjectPtr->KLine_ConfigUART)
            {
                pst_gHalObjectPtr->KLine_ConfigUART();
            }
            else
            {
                while(1);
            }
            /* Initialize UART */
            UART_Init(&st_gKLinePhyConfig);
            
            /* Delay for 25 ms */
            ISO14230_Delay(25);
            
            /* Find the Response  */
            p_lTemp =  p_lTemp + 1;
            
            u8_gKeyByte1 = *p_lTemp;
            
            /* Delay for 25 ms */
            ISO14230_Delay(25);            
            
            /* Find the Response  */
            p_lTemp =  p_lTemp + 1;
            
            u8_gKeyByte2 = *p_lTemp;
            
            /* Delay for 25 ms */
            ISO14230_Delay(25); 
            
            /* Send Target Message */
            if(PNULL != pst_gHalObjectPtr->KLine_TransmitChar)
            {
                pst_gHalObjectPtr->KLine_TransmitChar(~u8_gKeyByte2);
            }
            else
            {
                while(1);
            }
            
            /* Delay for 25 ms */
            ISO14230_Delay(50); 
            
            /* Find the Response  */
            p_lTemp = (INT8U *)strstr((const char *)&au8_gKLineRespBuf[0], (const char *)~u8_gKeyByte2);
            
            if(PNULL != p_lTemp)
            {
                /* Delay for 25 ms */
                ISO14230_Delay(25); 
                
                p_lTemp = p_lTemp + 1;
                
                if(~u8_gKlineTarByte == *p_lTemp)
                {
                    /* No action */
                }
                else
                {
                    /* return Error */
                    en_lResult = ISO14230_ERROR;
                }
                
            }
            else
            {
                /* Return Error */
                en_lResult = ISO14230_ERROR;
            }
        }        
    }
    else
    {
        /* return Error */
        en_lResult = ISO14230_ERROR;
    }
    
    /* Return the result */
    return en_lResult;  
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

ISO14230_RESULT_t ISO14230_PreparePacketAndWrite(INT8U * p_fInputBuff, INT16U u16_fInputLength)
{
    ISO14230_RESULT_t en_lResult = ISO14230_SUCCESS;
    
    if(u16_fInputLength > 510)
    {
      /* Send Error string */
        p_gXT_ReqComplete((INT8U *)&au8_gIctErrorString, \
                                                strlen((const char *)&au8_gIctErrorString));  
        /* Update the Result to Error */
        en_lResult = ISO14230_ERROR;
    }
    else if(u16_fInputLength <= 510 && u16_fInputLength >= 128)
    {    
        /* */
        INT8U u8_lPosition = 0;
        
        /* PAN Length will be Double So, Make it Half */
        u16_fInputLength = (u16_fInputLength >> 1);

        /* Convert PAN to Byte Array */
        if(COMMON_OK != COMMON_PAN2ByteArray(&p_fInputBuff[0], \
                                                        &u8_gKLineReqByteBuffer[0], u16_fInputLength))
        {
            /* Update Error status */
            en_lResult = ISO14230_ERROR;
        }
        else
        {
            /* Clear the Format Byte */
            u8_gKlineFmtByte = 0x80;
            
            /* Update the Converted Length */
            INT8U u8_lKlineAddLngthByte = u16_fInputLength;
                   
            /* Copy the Header into Output Buffer */
            memcpy(&au8_gKLineReqBuf[u8_lPosition], (INT8U *)&u8_gKlineFmtByte, 1);
            
            u8_lPosition = u8_lPosition + 1;

            /* Copy the Header into Output Buffer */
            memcpy(&au8_gKLineReqBuf[u8_lPosition], (INT8U *)&u8_gKlineTarByte, 1);

            u8_lPosition = u8_lPosition + 1;
            
            /* Copy the Header into Output Buffer */
            memcpy(&au8_gKLineReqBuf[u8_lPosition], (INT8U *)&u8_gKlineSrcByte, 1);
               
            u8_lPosition = u8_lPosition + 1;
            
             /* Copy the Header into Output Buffer */
            memcpy(&au8_gKLineReqBuf[u8_lPosition], (INT8U *)&u8_lKlineAddLngthByte, 1);
               
            u8_lPosition = u8_lPosition + 1;
            
            /* Copy the Converted Data to Output Buffer */
            memcpy(&au8_gKLineReqBuf[u8_lPosition], &u8_gKLineReqByteBuffer[0], u16_fInputLength);

            /* Backup the Request Message */
            u16_gKLineReqLength = (u16_fInputLength + u8_lPosition);            
            ISO14230_KLineWrite(&au8_gKLineReqBuf[0], u16_gKLineReqLength); 
       }
    }
    else
    {
        /* */
        INT8U u8_lPosition = 0;
        
        /* PAN Length will be Double So, Make it Half */
        u16_fInputLength = (u16_fInputLength >> 1);

        /* Convert PAN to Byte Array */
        if(COMMON_OK != COMMON_PAN2ByteArray(&p_fInputBuff[0], \
                                                        &u8_gKLineReqByteBuffer[0], u16_fInputLength))
        {
            /* Update Error status */
            en_lResult = ISO14230_ERROR;
        }
        else
        {
            /* Clear the Format Byte */
            u8_gKlineFmtByte &= KLINE_FMT_LEN_CLR;
            
            /* Update the Converted Length */
            u8_gKlineFmtByte |= (INT8U)u16_fInputLength;
                   
            /* Copy the Header into Output Buffer */
            memcpy(&au8_gKLineReqBuf[u8_lPosition], (INT8U *)&u8_gKlineFmtByte, 1);
            
            u8_lPosition = u8_lPosition + 1;

            /* Copy the Header into Output Buffer */
            memcpy(&au8_gKLineReqBuf[u8_lPosition], (INT8U *)&u8_gKlineTarByte, 1);

            u8_lPosition = u8_lPosition + 1;
            
            /* Copy the Header into Output Buffer */
            memcpy(&au8_gKLineReqBuf[u8_lPosition], (INT8U *)&u8_gKlineSrcByte, 1);
               
            u8_lPosition = u8_lPosition + 1;
            
            /* Copy the Converted Data to Output Buffer */
            memcpy(&au8_gKLineReqBuf[u8_lPosition], &u8_gKLineReqByteBuffer[0], u16_fInputLength);

            /* Backup the Request Message */
            u16_gKLineReqLength = (u16_fInputLength + u8_lPosition);            
            ISO14230_KLineWrite(&au8_gKLineReqBuf[0], u16_gKLineReqLength);        
        }      
    }  
    
    /* return the result */
    return en_lResult;
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

ISO14230_RESULT_t ISO14230_KLineWrite(INT8U * p_fData, INT16U u16_fLength)
{
    ISO14230_RESULT_t en_lResult = ISO14230_SUCCESS;
    INT8U u8_CheckSum = 0;
    
    /* Reset the Buffer  */
    ISO14230_ResetKLineBuffers();
    
    u8_gKLineBusy = 1;

    /* Backup the Request Message */
    u16_gKLineReqLength = u16_fLength;
    memcpy(&au8_gKLineReqBackupBuf[0], &p_fData[0], u16_gKLineReqLength);
    
    if(1 == u8_gKlineInitSeqFlag)
    {
        /* Delay for P4 timing  */
        ISO14230_Delay(u8_gKline_P4);
    }
    
    /* Write to KLine Bus */
    for(INT16U u16_lIndex = 0; u16_lIndex < u16_fLength; u16_lIndex++)
    {
        /* Write Byte to Bus */
        if(PNULL != pst_gHalObjectPtr->KLine_TransmitChar)
        {
            pst_gHalObjectPtr->KLine_TransmitChar(p_fData[u16_lIndex]);
        }
        else
        {
            while(1);
        }
        
        u8_CheckSum = u8_CheckSum + p_fData[u16_lIndex];
        
        /* Delay for P4 timing  */
        ISO14230_Delay(u8_gKline_P4);
    }
            
    /* Write CheckSum */
    if(PNULL != pst_gHalObjectPtr->KLine_TransmitChar)
    {
        pst_gHalObjectPtr->KLine_TransmitChar(u8_CheckSum);
    }
    else
    {
        while(1);
    }
    
    /* Delay for 3 mSec */
    ISO14230_Delay(u8_gKline_P4);
    
    /* Return the Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : void ISO14230_ResetRxBuff(void)                                             */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void ISO14230_ResetKLineBuffers(void)
{
    /* Reset the Previous Request Buffer */
    memset(&au8_gKLineReqBackupBuf[0], 0x00, KLINE_MAX_BUFF_LENGTH);
    
    /* Reset the Rx Buffer */
    memset(&au8_gKLineRespBuf[0], 0x00, KLINE_MAX_BUFF_LENGTH);  

    /* Reset Rx Index */
    u16_gKLineRespIndex = 0;
    
   /* Reset ReqBacklength */
    u16_gKLineReqLength = 0;
}

/**************************************************************************************************/
/* Function Name   : void ISO14230_ReadData(void)                                                */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void ISO14230_KLineProcessRxData(void)
{
    /* Temp Variables */
    INT32U u32_lIndex = 0;
    INT8U * p_lTemp = 0;
    INT32U u32_lPos = 0;
    INT8U u8_lLenghtByte = 0;
      
   /* Find Reueted Frame in Response Buffer */
    p_lTemp = (INT8U *)strstr((const char *)&au8_gKLineRespBuf[0], \
                                               (const char *)&au8_gKLineReqBackupBuf[0]);
    /* Validate The Response correct or not */
    if(PNULL != p_lTemp)
    {
        /* Seek to Actual Response Location */
        p_lTemp = (p_lTemp + (u16_gKLineReqLength + 1));

        while(1)
        {
            if(0x00 == p_lTemp[0])
            {
                /* Send through Bluetooth */
              p_gXT_ReqComplete((INT8U *)"NO DATA", strlen("NO DATA"));               
                
                /* Make Tester counter to 0 */
                u32_gKLineTesterCounter = 0;  
                
                /* To aterminate the loop */  
                break;
            }
            else
            {              
                /* Get the Length Byte of Frame */
                u8_lLenghtByte = (p_lTemp[0] & 0x3F);
                
                /* Manage Response */
                if(1 == u8_gResponseFlag)
                {
                    /* Manage Space */
                    if(1 == u8_gIctSpaceFlag)
                    {
                        /* Manage Header */
                        if(1 == u8_gHeaderFlag)
                        {
                            /* Format Byte */
                            COMMON_Byte2PAN(&au8_gKLineTrasBufferp[u32_lPos], p_lTemp[0]);
                            u32_lPos = (u32_lPos + 2);
                            au8_gKLineTrasBufferp[u32_lPos] = ' ';
                            u32_lPos = (u32_lPos + 1);
                            
                            /* Target Byte */
                            COMMON_Byte2PAN(&au8_gKLineTrasBufferp[u32_lPos], p_lTemp[1]);
                            u32_lPos = (u32_lPos + 2);
                            au8_gKLineTrasBufferp[u32_lPos] = ' ';
                            u32_lPos = (u32_lPos + 1);
                            
                            /* Source Byte */
                            COMMON_Byte2PAN(&au8_gKLineTrasBufferp[u32_lPos], p_lTemp[2]);
                            u32_lPos = (u32_lPos + 2);
                            au8_gKLineTrasBufferp[u32_lPos] = ' ';
                            u32_lPos = (u32_lPos + 1);
                            
                            /* Pay Load */
                            for(u32_lIndex = 0; u32_lIndex<u8_lLenghtByte; u32_lIndex++)
                            {
                                COMMON_Byte2PAN(&au8_gKLineTrasBufferp[u32_lPos], p_lTemp[(3 + u32_lIndex)]);
                                u32_lPos = (u32_lPos + 2);
                                au8_gKLineTrasBufferp[u32_lPos] = ' ';
                                u32_lPos = (u32_lPos + 1);
                            }
                            
                            /* Checksum Byte */
                            COMMON_Byte2PAN(&au8_gKLineTrasBufferp[u32_lPos], p_lTemp[(3 + u8_lLenghtByte)]);
                            u32_lPos = (u32_lPos + 2);
                            au8_gKLineTrasBufferp[u32_lPos] = ' ';
                            u32_lPos = (u32_lPos + 1);

                            /* Seek to Next Pointer */
                            p_lTemp = (p_lTemp + 4 + u8_lLenghtByte);
                        }
                        else
                        {                          
                            /* Pay Load */
                            for(u32_lIndex = 0; u32_lIndex<u8_lLenghtByte; u32_lIndex++)
                            {
                                COMMON_Byte2PAN(&au8_gKLineTrasBufferp[u32_lPos], p_lTemp[(3 + u32_lIndex)]);
                                u32_lPos = (u32_lPos + 2);
                                au8_gKLineTrasBufferp[u32_lPos] = ' ';
                                u32_lPos = (u32_lPos + 1);
                            }

                            /* Seek to Next Pointer */
                            p_lTemp = (p_lTemp + 4 + u8_lLenghtByte);                        
                        } 
                    }
                    else
                    {
                        /* Manage Header */
                        if(1 == u8_gHeaderFlag)
                        {
                            /* Format Byte */
                            COMMON_Byte2PAN(&au8_gKLineTrasBufferp[u32_lPos], p_lTemp[0]);
                            u32_lPos = (u32_lPos + 2);
                            
                            /* Target Byte */
                            COMMON_Byte2PAN(&au8_gKLineTrasBufferp[u32_lPos], p_lTemp[1]);
                            u32_lPos = (u32_lPos + 2);
                            
                            /* Source Byte */
                            COMMON_Byte2PAN(&au8_gKLineTrasBufferp[u32_lPos], p_lTemp[2]);
                            u32_lPos = (u32_lPos + 2);
                            
                            /* Pay Load */
                            for(u32_lIndex = 0; u32_lIndex<u8_lLenghtByte; u32_lIndex++)
                            {
                                COMMON_Byte2PAN(&au8_gKLineTrasBufferp[u32_lPos], p_lTemp[(3 + u32_lIndex)]);
                                u32_lPos = (u32_lPos + 2);
                            }
                            
                            /* Checksum Byte */
                            COMMON_Byte2PAN(&au8_gKLineTrasBufferp[u32_lPos], p_lTemp[(3 + u8_lLenghtByte)]);
                            
                            u32_lPos = (u32_lPos + 2);

                            /* Seek to Next Pointer */
                            p_lTemp = (p_lTemp + 4 + u8_lLenghtByte);
                        }
                        else
                        {
                            /* Pay Load */
                            for(u32_lIndex = 0; u32_lIndex < u8_lLenghtByte; u32_lIndex++)
                            {
                                COMMON_Byte2PAN(&au8_gKLineTrasBufferp[u32_lPos], p_lTemp[(3 + u32_lIndex)]);
                                u32_lPos = (u32_lPos + 2);
                            }
                            
                            /* Seek to Next Pointer */
                            p_lTemp = (p_lTemp + 4 + u8_lLenghtByte); 
                        }     
                    }
                    
                    /* Append to CRLF to the User Response Data */
                    strcat((char *)&au8_gKLineTrasBufferp[0], "\n");
                    
                    /* Send through Bluetooth */
                    p_gXT_ReqComplete(&au8_gKLineTrasBufferp[0], \
                                                     strlen((const char *)&au8_gKLineTrasBufferp[0]));
                    
                    /* Reset Response Buffer */
                    memset(&au8_gKLineTrasBufferp[0], 0x00, KLINE_MAX_BUFF_LENGTH);
                    
                    /* Reset New Frame Position to Zero */
                    u32_lPos = 0;
                    
                    /* Wait for P2 timing  for next frame */
                    ISO14230_Delay(u32_gKline_P2);
    
                    if(p_lTemp[0] == 0x00)
                    {                      
                        /* Make Tester counter to 0*/
                        u32_gKLineTesterCounter = 0;
                        
                        /* Exit the Loop */
                        break;
                    }
                }
                else
                {
                    /* Reset Response Buffer */
                    memset(&au8_gKLineTrasBufferp[0], 0x00, KLINE_MAX_BUFF_LENGTH);

                    /* Reset New Frame Position to Zero */
                    u32_lPos = 0;
                    
                    /* Make Tester counter to 0 */
                    u32_gKLineTesterCounter = 0;
                    
                    /* Exit the Loop */
                    break;
                }
            }
        }
        
        /* Append to CRLF to the User Response Data */
        p_gXT_ReqComplete((INT8U *)"\r\n#", strlen("\r\n#"));
    }
    else
    {
        /* Send through Bluetooth */
      p_gXT_ReqComplete((INT8U *)"KLINE ERROR...\r\n#", strlen("KLINE ERROR...\r\n#"));        
    }
    
    /* Make Tester Busy to 0*/
    u8_gKLineBusy = 0;
}

/**************************************************************************************************/
/* Function Name   : void ISO14230_DeInit(void)                                                  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void ISO14230_DeInit(void)
{
    /* Makek Initsequence flag to 0 */
    u8_gKlineInitSeqFlag = 0;
   
    /* Reset the Buffer  */
    ISO14230_ResetKLineBuffers();
    
    if(PNULL != pst_gHalObjectPtr->KLine_DeInit)
    {
        pst_gHalObjectPtr->KLine_DeInit();
    }
    else
    {
        while(1);
    }
    
    /* Hal Timer DeInit */
    if(PNULL != pst_gHalObjectPtr->TimerDeInit)
    {
        pst_gHalObjectPtr->TimerDeInit();
    }
    else
    {
        while(1);
    }
}

/**************************************************************************************************/
/* Function Name   : void ISO14230_Delay(INT32U u32_fDelay)                                          */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void ISO14230_Delay(INT32U u32_fDelay)
{
   u32_gKLineTick = 0;
   
   while(u32_gKLineTick < u32_fDelay);
}

/**************************************************************************************************/
/* End of ISOTP14230_TP.c                                                                         */
/**************************************************************************************************/

