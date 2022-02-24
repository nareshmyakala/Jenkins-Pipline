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
/* \File Name   : ISO_HANDLERS.c                                                                  */
/* \Author      : PRASHANTH                                                                       */
/* \Version 	:                                                                                 */
/* \Date        : 25-03-2017                                                                      */
/*                                                                                                */
/* @Description : ISO Handlers Frame Work                                                         */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include<string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "DATACONV.h"

#include "XTP_public.h"
#include "XTP_TE_public.h"

#include "ISOTP14230_TP_public.h"
#include "TEOBD2_public.h"

#include "XTP_ISO_public.h"
#include "XTP_ISO_private.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTIB(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTIB(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
#if 0    
    /* */
    INT8U u8_lTempBaud = 0;
    INT8U u8_lTempFlag = 1;
    
    /* */
    if(COMMON_OK == COMMON_PAN2Byte(&p_fSrc[0], &u8_lTempBaud))
    {
        switch(u8_lTempBaud)
        {
        case 0x10:
            {
                /* */
                //HAL_UpdateBaudrae(st_gKLINE_PhyConfigData.en_mUSICChannel, 10400);
            }
            break;
        case 0x48:
            {
                /* */
                //HAL_UpdateBaudrae(st_gKLINE_PhyConfigData.en_mUSICChannel, 4800);
            }
            break;
        case 0x96:
            {
                /* */
                //HAL_UpdateBaudrae(st_gKLINE_PhyConfigData.en_mUSICChannel, 9600);
            }
            break;
        default:
            {
                /* update Error Status */
                en_lResult = XTP_ERROR;
            }
            break;
        }
    }
    else if(('H' == p_fSrc[0]) && ('I' == p_fSrc[1]))
    {
        /* */
        //HAL_UpdateBaudrae(st_gKLINE_PhyConfigData.en_mUSICChannel, 115200);
    }
    else
    {
        
        /* update Error Status */
        en_lResult = XTP_ERROR;
    }
    
    if(1 == u8_lTempFlag)
    {   
        u8_lTempFlag= 0;
        
        /* Send Response */
        p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    }

 #endif 
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTFI(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTFI(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
#if 0
    
    if(IS014230_FAST == en_gOBDII_State)
    {
        /* KWP2000 Fast Init Performed */
        if(ISO14230_SUCCESS == ISO14230_FastInit())
        {
            /* Display BUS INIT OK...*/
            p_gXT_ReqComplete((INT8U *)"BUS INIT: OK\r\n", sizeof("BUS INIT: OK\r\n"));
        }
        else
        {
            /* Display BUS INIT OK...*/
            p_gXT_ReqComplete((INT8U *)"BUS INIT: ...ERROR>\r\n", sizeof("BUS INIT: ...ERROR>\r\n"));
        }
        
        /* */
        u8_gKlineInitSeqFlag = 1;
        
        /* Release Tester Busy Flag */
        //u8_gTesterBusyFlag = 0;
    }
    else
    {
        /* Update Error Status */
        en_lResult = XTP_ERROR;
    }
    
    if(XTP_ERROR != en_lResult)	
    {
        /* Send Response */
        p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                                strlen((const char *)&au8_gIctSuccessString[0])); 
    }
    
 #endif 
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                                strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSW(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSW(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                                strlen((const char *)&au8_gIctSuccessString[0]));   
    /* Return Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTKW(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTKW(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* */
    INT8U au8_lTemBuff[16] = {0x00, };
    
    /* If Current Protocol is KLinne Fast then only process else don't */
    if(IS014230_FAST == en_gOBDII_State)
    {
        if(1 == u8_gKlineInitSeqFlag)
        {	
            /* Convert and copy keywords to Response Buffer */          
            memcpy((INT8U *)&au8_lTemBuff[0], "1:", sizeof("1:"));
            
            COMMON_Byte2PAN(&au8_lTemBuff[2],u8_gKeyByte1);
            
            memcpy((INT8U *)&au8_lTemBuff[4], "2:", sizeof("2:"));
            
            COMMON_Byte2PAN(&au8_lTemBuff[6], u8_gKeyByte2);
        }
        else
        {
            memcpy((INT8U *)&au8_lTemBuff[0], "1:-- 2:--", sizeof("1:-- 2:--")); 
        }
        /* Append \r\n>*/
        strcat((char *)&au8_lTemBuff[0], "\r\n#");
        
        /* Send Response */
        p_gXT_ReqComplete((INT8U *)&au8_lTemBuff[0], \
                                                strlen((const char *)&au8_lTemBuff[0]));    
    }
    else
    {
        /* Update Error */
        en_lResult = XTP_ERROR;
    }
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTWM(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTWM(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                                strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTIAT(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTIAT(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                                strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTIBR(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTIBR(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                                strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTIMCS(INT8U *p_fSrc, INT16U u16_fLength)*/
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTIMCS(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                                strlen((const char *)&au8_gIctSuccessString[0]));
        
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTIP1X(INT16U * p_fArgs, INT8U u8_fArgCount)*/
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTIP1X(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                                strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTIP4(INT16U * p_fArgs, INT8U u8_fArgCount)*/
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTIP4(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;

    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                                strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;
}

/**************************************************************************************************/
/* End of ISO_HANDLERS.c                                                                          */
/**************************************************************************************************/

