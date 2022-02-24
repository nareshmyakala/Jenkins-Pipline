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
/* \File Name   : POWERSAVE_HANDLERS.c                                                            */
/* \Author      : PRASHANTH                                                                       */
/* \Version 	:                                                                                 */
/* \Date        : 25-03-2017                                                                      */
/*                                                                                                */
/* @Description : Powersave Handlers Frame Work                                                   */
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

#include "XTP_PM_public.h"
#include "XTP_PM_private.h"

#include "XTP_public.h"
#include "XTP_TE_public.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSLCS(INT16U * p_fArgs, INT8U u8_fArgCount)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSLCS(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                           strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSLEEP(INT8U *p_fSrc, INT16U u16_fLength)*/
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSLEEP(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                           strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult; 
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSLLIT(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSLLIT(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                           strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult; 
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSLPCP(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSLPCP(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                           strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;   
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSLUIT(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSLUIT(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                           strlen((const char *)&au8_gIctSuccessString[0]));
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSLUWP(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSLUWP(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                           strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSLX(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSLX(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                           strlen((const char *)&au8_gIctSuccessString[0]));
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSLXS(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSLXS(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                           strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;   
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSLXST(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSLXST(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                           strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSLXWT(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSLXWT(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                           strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSLXP(INT8U *p_fSrc, INT16U u16_fLength   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSLXP(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                           strlen((const char *)&au8_gIctSuccessString[0]));
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSLLT(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSLLT(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                           strlen((const char *)&au8_gIctSuccessString[0]));
    return en_lResult;
}

/**************************************************************************************************/
/* End of POWERSAVE_HANDLERS.c                                                                    */
/**************************************************************************************************/

