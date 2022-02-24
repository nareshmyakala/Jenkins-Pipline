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
/* \File Name   : GENERAL_CMD_HANDLERS.c                                                          */
/* \Author      : PRASHANTH                                                                       */
/* \Version 	:                                                                                 */
/* \Date        : 25-03-2017                                                                      */
/*                                                                                                */
/* @Description : General Cmd Hadlers Frame work                                                  */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "DATACONV.h"

#include "TEOBD2_public.h"
#include "XTP_public.h"

//#include "HAL_NVM_public.h"
//#include "HAL_ADC_public.h"

#include "NVMCTRL.h"

#include "TEOBD2_public.h"

#include "XTP_GE_public.h"
#include "XTP_GE_private.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Buffer for to Store USer Data Rate */
INT8U u8_gDatarate[6] = {0x00,};

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTZ(INT8U *p_fSrc, INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTZ(INT8U * p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;    

   /* iConnect Serial Number */
    INT8U au8_gIctSerialNumberString[] = "iConnect V1.0\r\n#";
    
    /* Send Response */
    p_gXT_ReqComplete(&au8_gIctSerialNumberString[0], \
                            strlen((const char *)&au8_gIctSerialNumberString[0]));

    return en_lResult;   
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTZ(INT8U *p_fSrc, INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTRST(INT8U * p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;    

    /* Waite For Delay */
    for(INT32U u32_lIndex = 0; u32_lIndex < 5000; u32_lIndex++);
    
    /* Reset the Device */
    if(PNULL != pst_gHalObjectPtr->ResetDevice)
    {
        pst_gHalObjectPtr->ResetDevice();
    }
    else
    {
        while(1);
    }

    return en_lResult;   
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTBRD(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTBRD(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold The Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0]));  
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTBRT(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTBRT(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold The Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
  
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0]));
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTE(INT8U *p_fSrc, INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTE(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    switch(p_fSrc[0])
    {
    case '0':
        {
            /* update Global Echo Flag to 0 */
            u8_gEchoFlagStatus = 0;
        }
        break;
        
    case '1':
        {
            /* update Global Echo Flag to 1 */
            u8_gEchoFlagStatus = 1;

        }
        break;
        
    default:
        {
            /* update Error */
            en_lResult = XTP_ERROR;
        }
        break;
    }
    
    if(XTP_ERROR != en_lResult)
    {
        /* Send Response */
        p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0]));
    }
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTI(INT8U *p_fSrc, INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTI(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;

    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTLP(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTLP(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;  
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTM(INT8U *p_fSrc, INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_GNRL_XTM(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;  
#if 0    
    /* Reset the Response Buffer*/
    memset((INT8U *)&u8_gTbusTxBuffer[0], 0, XTCOM_RESP_BUFFER_LENGTH);
    
    /* Dummy String */
    strcpy((char *)&u8_gTbusTxBuffer[0], (const char *)"Executing XTM Command\r\n#");
    
    /* Send Response */
    XTCOM_SendResponse((INT8U *)&u8_gTbusTxBuffer[0], \
        strlen((const char *)&u8_gTbusTxBuffer[0]));
#endif    
    
        /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTWS(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTWS(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    /* Return The Result */
    return en_lResult;
    
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSD(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSD(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;	
#if 0
    
    /* Temp Variable */
    INT8U u8_lWriteValue = 0;
    
    /* */
    COMMON_PAN2Byte(&p_fSrc[0], &u8_lWriteValue);
    
    /* Write the Corresponding Data into memory */
    st_gChipConfigData.u8_mNVM_SD_Data  = u8_lWriteValue;
    
    /* */
    TEOBDII_STACK_WriteConfigData();
 
#endif
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTRD(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTRD(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold The Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;  
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    /* Return The Result */
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSN(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSN(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* iConnect Serial Number */
    INT8U au8_gIctSerialNumberString[] = "TE0000000001\r\n#";
    
    /* Send Response */
    p_gXT_ReqComplete(&au8_gIctSerialNumberString[0], \
                            strlen((const char *)&au8_gIctSerialNumberString[0]));
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSBR(INT16U * p_fArgs, INT8U u8_fArgCount)*/
/*                                                                                                */
/* Description     : This Function is Used to Set the Baudrate                                    */
/*                                                                                                */
/* In Params       : Arguments and Argument Count                                                 */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSBR(INT8U * p_fArgs, INT8U u8_fArgCount)
{
    /* Variable to Hold the Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS; 
    
    /* Copy the Data Into Buffer upto length */
    memcpy(&u8_gDatarate[0] , p_fArgs , u8_fArgCount);
    
    /* Convert the Ascci data into Integer */
   // u32_gCurrentDataRate = atoi((char *)&u8_gDatarate[0]);
    
    /* Update the  datarate into UART structure*/
    //st_gTeOBD2APPConfig.u32_mBaudRate = u32_gCurrentDataRate;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0]));
    for(int i=0 ; i<10000;i++);
    
    /* Initialize UART */
    //uartDrvInit(&st_gTeOBD2APPConfig);       
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTWBR(INT16U * p_fArgs, INT8U u8_fArgCount)*/
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTWBR(INT8U * p_fArgs, INT8U u8_fArgCount)
{
    /* Variable to Hold the Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
   // if(FTFC_OK == EEPROM_WriteData(DATARATE_BASE_ADDR ,&u8_gDatarate[0], 7))
    {
       // EEPROM_WriteData(DATARATE_BASE_ADDR ,&u8_gDatarate[0], 7);
        
        /* Send Response */
        p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    }
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTBR(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTBR(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;

        /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTDI(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTDI(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS; 
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTMFR(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTMFR(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
        /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTFE(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTFE(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
        /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;   
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTRV(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTRV(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
     
    float f32_lVoltage = 0.0;
    INT8U u8_lVoltage[7] = {0x00, };
    
    /* */
   // f32_lVoltage = HAL_ADC_ReadVoltage();
    
    sprintf((char *)&u8_lVoltage[0] , "%.2fV" , f32_lVoltage );
    
    u8_lVoltage[5] = '\r';
    u8_lVoltage[6] = '\n';
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&u8_lVoltage[0], 7); 
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTCV(INT8U *p_fSrc, INT16U u16_fLength)    */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTCV(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
         /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTIGN(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTIGN(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 

    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTA(INT8U *p_fSrc, INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTA(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* 1 or 2 or 3 are the Arguments*/
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* End of GENERAL_CMD_HANDLERS.c                                                                  */
/**************************************************************************************************/

