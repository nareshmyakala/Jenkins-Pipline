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
/* \File Name   : PP_HANDLER.c                                                                    */
/* \Author      :                                                                                 */
/* \Version 	:                                                                                 */
/* \Date        : 14-12-2016                                                                      */
/*                                                                                                */
/* @Description : Programble Paramters Frame work                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>
#include <stdio.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "DATACONV.h"

#include "XTP_public.h"
#include "XTP_TE_public.h"

#include "XTP_PP_public.h"
#include "XTP_PP_private.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

#define LAST_PROTOCOL                    ( 0x07 )
#define TIME_DELAY_FOR_PROTOCOL          ( 0x13 )
#define KWP_FAST_INIT_DELAY              ( 0x18 )
#define KWP_SLOW_INIT_DELAY              ( 0x19 )

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* variable to hold Programable Parameters */
ST_PROG_PARAMS_t st_gPPBackup[MAX_PP_COUNT] = 
{
    {
        .en_mPPIndex = PROG_PARAM_00,
        .u8_mPPValue = 0xFF,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 1,
        .u8_mEnabled = 0,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
        
    },
    {
        .en_mPPIndex = PROG_PARAM_01,   
        .f32_mPPFactor = 1,
        .u8_mPPValue = 0x00,
        .u8_mIsBoolean = 1,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,        
    },
    {
        .en_mPPIndex = PROG_PARAM_02,
        .u8_mPPValue = 0x00,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 1,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,        
    },
    {
        .en_mPPIndex = PROG_PARAM_03,
        .u8_mPPValue = 0x32,
        .f32_mPPFactor = 4.096,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_04,
        .u8_mPPValue = 0x01,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,        
    },
    {
        .en_mPPIndex = PROG_PARAM_05,
        .u8_mPPValue = 0x01,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,        
    },   
    {
        .en_mPPIndex = PROG_PARAM_06,
        .u8_mPPValue = 0xF1,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_07,
        .u8_mPPValue = 0x09,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_08,
        .u8_mPPValue = 0x01,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,        
    },   
    {
        .en_mPPIndex = PROG_PARAM_09,
        .u8_mPPValue = 0x00,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 1,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,       
    },
    {
        .en_mPPIndex = PROG_PARAM_0A,
        .u8_mPPValue = 0x0A,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_0B,
        .u8_mPPValue = 0x01,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,        
    },    
    {
        .en_mPPIndex = PROG_PARAM_0C,
        .u8_mPPValue = 0x68,
        .f32_mPPFactor = 4000,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_0D,
        .u8_mPPValue = 0x0D,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_0E,
        .u8_mPPValue = 0x9A,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_0F,
        .u8_mPPValue = 0xD5,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_10,
        .u8_mPPValue = 0x0D,
        .f32_mPPFactor = 4.096,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_11,
        .u8_mPPValue = 0x00,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 1,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,        
    },
    {
        .en_mPPIndex = PROG_PARAM_12,
        .u8_mPPValue = 0xFF,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 1,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        /* Value = 150 + (en_mPPIndex) * 4.096 */
        .en_mPPIndex = PROG_PARAM_13,
        .u8_mPPValue = 0x55,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        /* Value =  98 + en_mPPIndex * 64*/
        .en_mPPIndex = PROG_PARAM_14,
        .u8_mPPValue = 0x50,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_15,
        .u8_mPPValue = 0x0A,
        .f32_mPPFactor = 2.112,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_16,
        .u8_mPPValue = 0xFF,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_17,
        .u8_mPPValue = 0x92,
        .f32_mPPFactor = 20.48,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        /* Value =  1000 + (en_mPPIndex)* 20.48 */
        .en_mPPIndex = PROG_PARAM_18,
        .u8_mPPValue = 0x31,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula = 0,
    },
    {
        /* Value =  1000 + (en_mPPIndex)* 20.48 */
        .en_mPPIndex = PROG_PARAM_19,
        .u8_mPPValue = 0x31,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_1A,
        .u8_mPPValue = 0x0A,
        .f32_mPPFactor = 2.5,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_1B,
        .u8_mPPValue = 0x0A,
        .f32_mPPFactor = 2.5,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_1C,
        .u8_mPPValue = 0x03,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        /* Value =  (en_mPPIndex - 0.5 )* 4.096 */
        .en_mPPIndex = PROG_PARAM_1D,
        .u8_mPPValue = 0x0F,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula = 0,
    },
    {
        .en_mPPIndex = PROG_PARAM_1E,
        .u8_mPPValue = 0x4A,
        .f32_mPPFactor = 4.096,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula = 0,
    },
    {
        .en_mPPIndex = PROG_PARAM_1F,
        .u8_mPPValue = 0x01,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,        
    },
    {
        .en_mPPIndex = PROG_PARAM_20,
        .u8_mPPValue = 0x01,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,        
    },    
    {
        .en_mPPIndex = PROG_PARAM_21,
        .u8_mPPValue = 0xFF,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 1,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,       
    },
    {
        .en_mPPIndex = PROG_PARAM_22,
        .u8_mPPValue = 0x01,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,        
    },
    {
        .en_mPPIndex = PROG_PARAM_23,
        .u8_mPPValue = 0x01,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,        
    },    
    {
        .en_mPPIndex = PROG_PARAM_24,
        .u8_mPPValue = 0x00,
        .f32_mPPFactor = 1,      
        .u8_mIsBoolean = 1,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_25,
        .u8_mPPValue = 0x00,
        .f32_mPPFactor = 1,   
        .u8_mIsBoolean = 1,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_26,
        .u8_mPPValue = 0x00,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_27,
        .u8_mPPValue = 0x01,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,       
    },    
    {
        .en_mPPIndex = PROG_PARAM_28,
        .u8_mPPValue = 0xFF,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_29,
        .u8_mPPValue = 0xFF,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 1,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_2A,
        .u8_mPPValue = 0x3C,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_2B,
        .u8_mPPValue = 0x02,
        .f32_mPPFactor = 500,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_2C,
        .u8_mPPValue = 0xE0,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_2D,
        .u8_mPPValue = 0x04,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_2E,
        .u8_mPPValue = 0x80,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
    {
        .en_mPPIndex = PROG_PARAM_2F,
        .u8_mPPValue = 0x0A,
        .f32_mPPFactor = 1,
        .u8_mIsBoolean = 0,
        .u8_mEnabled = 1,
        .u8_mEffect = 0,
        .u8_mUseFormula =0,
    },
};

/* variable to hold Programable Parameters */
ST_PROG_PARAMS_t st_gPPCurrent[MAX_PP_COUNT];

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

EN_XTP_RESULT_t XTP_XTPPS(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    INT8U u8_lBuff[32];
    
    ST_PROG_PARAMS_t * p_lPPData = PNULL;
    
    /* Parse all PP Data */
    for(INT8U u8_lIndex = 0; u8_lIndex < MAX_PP_COUNT; u8_lIndex++)
    {
        p_lPPData = &st_gPPCurrent[u8_lIndex];
        
        memset((void *)&u8_lBuff[0], 0x00, 32);
        sprintf((char *)&u8_lBuff[0], "%02X:%02X ", p_lPPData->en_mPPIndex, p_lPPData->u8_mPPValue);
        
        if(1 == p_lPPData->u8_mEnabled)
        {
            strcat((char *)&u8_lBuff, "N \r\n");
        }
        else
        {
            strcat((char *)&u8_lBuff, "F \r\n");
        }
        
        /* Send Response */
        p_gXT_ReqComplete((INT8U *)&u8_lBuff[0], strlen((const char *)&u8_lBuff[0]));
    }

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

EN_XTP_RESULT_t XTP_XTPPSV(INT8U * p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold The Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    INT8U u8_lPPIndex = 0x00;
    INT8U u8_lPPValue = 0x00;
    
    if(COMMON_ERROR == COMMON_PAN2Byte(&p_fSrc[0], &u8_lPPIndex))
    {
        en_lResult = XTP_ERROR;
    }
    else
    {
        if(COMMON_ERROR == COMMON_PAN2Byte(&p_fSrc[4], &u8_lPPValue))
        {
            en_lResult = XTP_ERROR;
        }
        else
        {
            if(u8_lPPIndex <= 0x2F)
            {
                /* */
                if(PP_ERROR == PP_HANDLER_WriteValaue((EN_PROG_PARAMS_t )u8_lPPIndex, u8_lPPValue))
                {
                    en_lResult = XTP_ERROR;
                }
                else
                {
                    /* No acton */
                }
            }
            else
            {
                en_lResult = XTP_ERROR;
            }      
        }
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

EN_XTP_RESULT_t XTP_XTPPON(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold The Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
#if 0   
    /* Reset the Response Buffer*/
    memset((INT8U *)&u8_gTbusTxBuffer[0], 0, XTCOM_RESP_BUFFER_LENGTH);
    
    INT8U u8_lPPIndex = 0x00;
    
    if(COMMON_ERROR == COMMON_PAN2Byte(&p_fSrc[0],&u8_lPPIndex))
    {
        en_lResult = XTP_ERROR;
    }
    else
    {
        if((u8_lPPIndex <= 0x2F) || (0xFF == u8_lPPIndex))
        {
            /* */
            if(PP_ERROR == PP_HANDLER_WriteStatus((EN_PROG_PARAMS_t )u8_lPPIndex, PP_ON))
            {
                en_lResult = XTP_ERROR;
            }
            else
            {
                /* Copy the Success String */
                strcpy((char *)&u8_gTbusTxBuffer[0], (const char *)&au8_gIctSuccessString[0]);
                
                /* Send Response */
                XTCOM_SendResponse((INT8U *)&u8_gTbusTxBuffer[0], \
                    strlen((const char *)&u8_gTbusTxBuffer[0]));
            }
        }
        else
        {
            en_lResult = XTP_ERROR;
        }      
    }
#endif     
    /* Return The Result */
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

EN_XTP_RESULT_t XTP_XTPPOFF(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold The Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS; 
#if 0 
    INT8U u8_lPPIndex = 0x00;
    
    /* Reset the Response Buffer*/
    memset((INT8U *)&u8_gTbusTxBuffer[0], 0, XTCOM_RESP_BUFFER_LENGTH);
    
    if(COMMON_ERROR == COMMON_PAN2Byte(&p_fSrc[0],&u8_lPPIndex))
    {
        en_lResult = XTP_ERROR;
    }
    else
    {
        if((u8_lPPIndex <= 0x2F) || (0xFF== u8_lPPIndex))
        {
            /* */
            if(PP_ERROR == PP_HANDLER_WriteStatus((EN_PROG_PARAMS_t )u8_lPPIndex, PP_OFF))
            {
                en_lResult = XTP_ERROR;
            }
            else
            {
                /* Copy the Success String */
                strcpy((char *)&u8_gTbusTxBuffer[0], (const char *)&au8_gIctSuccessString[0]);
                
                /* Send Response */
                XTCOM_SendResponse((INT8U *)&u8_gTbusTxBuffer[0], \
                    strlen((const char *)&u8_gTbusTxBuffer[0]));
            }        
        }
        else
        {
            en_lResult = XTP_ERROR;
        }       
    }
#endif     
    /* Return The Result */
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

void PP_HANDLERS_Init(void)
{
    /* update ATMA FLag */
    PP_HANDLER_UpdateFlag(PROG_PARAM_00);
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

EN_PP_RESULT_t PP_HANDLER_WriteStatus(EN_PROG_PARAMS_t en_fPPIndex, EN_PP_STATUS_t en_fStatus)
{
    EN_PP_RESULT_t en_lResult = PP_SUCCESS;
    
    /* Update All PP Params */
    if(0xFF == en_fPPIndex)
    {
        if(PP_ON == en_fStatus)
        {
            for(INT8U u8_lIndex = 0; u8_lIndex <= 0x2F; u8_lIndex++)
            {
                st_gPPBackup[u8_lIndex].u8_mEnabled = 0x01; 
                st_gPPCurrent[u8_lIndex].u8_mEnabled = 0x01;           
            }
        }
        else if(PP_OFF == en_fStatus)
        {
            for(INT8U u8_lIndex = 0; u8_lIndex <= 0x2F; u8_lIndex++)
            {
                st_gPPBackup[u8_lIndex].u8_mEnabled = 0x00; 
                st_gPPCurrent[u8_lIndex].u8_mEnabled = 0x00;           
            }          
        }
        else
        {
            /* No Action */
        }
    }
    else
    {
        if(PP_ON == en_fStatus)
        {
            st_gPPBackup[en_fPPIndex].u8_mEnabled = 0x01; 
            st_gPPCurrent[en_fPPIndex].u8_mEnabled = 0x01; 
        }
        else
        {
            st_gPPBackup[en_fPPIndex].u8_mEnabled = 0x00;
            st_gPPCurrent[en_fPPIndex].u8_mEnabled = 0x00; 
        }      
    }
    
    /* Write Programmable Params */
    //NVM_Write(PP_BASE_ADDR, (INT8U *)&st_gPPBackup, sizeof(st_gPPBackup));    
    
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

EN_PP_STATUS_t PP_HANDLER_GetStatus(EN_PROG_PARAMS_t en_fPPIndex)
{
    EN_PP_STATUS_t en_lResult = PP_OFF;
    
    if(0x01 == st_gPPCurrent[en_fPPIndex].u8_mEnabled)
    {
        en_lResult = PP_ON;
    }
    else
    {
        en_lResult = PP_OFF;
    }
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_PP_RESULT_t PP_HANDLERS_WriteValaue(EN_PROG_PARAMS_t en_fPPIndex, \       */
/*                                                                            INT16U u16_OutData) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_PP_RESULT_t PP_HANDLER_WriteValaue(EN_PROG_PARAMS_t en_fPPIndex, INT8U u8_fPPValue)
{
    EN_PP_RESULT_t en_lResult = PP_SUCCESS;
    
    if(st_gPPBackup[en_fPPIndex].u8_mIsBoolean)
    {
        if(0x00 == u8_fPPValue)
        {
            /* Update Value to Backup */
            st_gPPBackup[en_fPPIndex].u8_mPPValue = u8_fPPValue; 
            
            /* Update Value */
            st_gPPCurrent[en_fPPIndex].u8_mPPValue = u8_fPPValue;
        }
        else
        {
            /* Update Value to Backup */
            st_gPPBackup[en_fPPIndex].u8_mPPValue = 0xFF;     
            
            /* Update Value */
            st_gPPCurrent[en_fPPIndex].u8_mPPValue = 0xFF;
        }
    }
    else
    {
        /* Update Value to Backup */
        st_gPPBackup[en_fPPIndex].u8_mPPValue = u8_fPPValue;  
        
        /* Update Value */
        st_gPPCurrent[en_fPPIndex].u8_mPPValue = u8_fPPValue;      
    }
    
    /* Write Programmable Params */
    //NVM_Write(PP_BASE_ADDR, (INT8U *)&st_gPPBackup, sizeof(st_gPPBackup));
    
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

EN_PP_RESULT_t PP_HANDLER_GetValaue(EN_PROG_PARAMS_t en_fPPIndex, INT8U * P_OutData)
{
    EN_PP_RESULT_t en_lResult = PP_SUCCESS;
    
    /* Fetch Value */
    *P_OutData = st_gPPCurrent[en_fPPIndex].u8_mPPValue;
    
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

EN_PP_RESULT_t PP_HANDLER_UpdateFlag(EN_PROG_PARAMS_t en_fPPIndex)
{
    EN_PP_RESULT_t en_lResult = PP_SUCCESS;
    
    switch(en_fPPIndex)
    {
    case PROG_PARAM_00:
        {
            if(1 == st_gPPCurrent[en_fPPIndex].u8_mEnabled)
            {
                if(0x00 == st_gPPCurrent[en_fPPIndex].u8_mPPValue)
                {
                    /* Enable ATMA Flag */
                    u8_gCanBusMonitorStaus = 1;
                }
                else
                {
                    /* Disable ATMA Flag */
                    u8_gCanBusMonitorStaus = 0;              
                }
            }
            else
            {
                /* Disable ATMA Flag */
                u8_gCanBusMonitorStaus = 0;
            }            
        }
        break;
        
    case PROG_PARAM_01:
        {
            if(1 == st_gPPCurrent[en_fPPIndex].u8_mEnabled)
            {
                /* Enable Header Bytes */
            }
            else
            {
                /* Disable Header Bytes */
            }         
        }
        break;   
        
    case PROG_PARAM_02:
        {
            if(1 == st_gPPCurrent[en_fPPIndex].u8_mEnabled)
            {
                /* Enable Allowing Long Messages */
            }
            else
            {
                /* Disable Allowing Long Messages */
            }         
        }
        break;
        
    case PROG_PARAM_09:
        {
            if(1 == st_gPPCurrent[en_fPPIndex].u8_mEnabled)
            {
                /* Enable Echo */
            }
            else
            {
                /* Disable Echo */
            }         
        }
        break;
        
    case PROG_PARAM_11:
        {
            if(1 == st_gPPCurrent[en_fPPIndex].u8_mEnabled)
            {
                /* Enable J1850  Break signal Monitor */
            }
            else
            {
                /* Disable J1850  Break signal Monitor */
            }         
        }
        break;
        
    case PROG_PARAM_21:
        {
            if(1 == st_gPPCurrent[en_fPPIndex].u8_mEnabled)
            {
                /* Enable CAN silent Mode */
            }
            else
            {
                /* Disable CAN silent MOode */ 
            }         
        }
        break;
        
    case PROG_PARAM_24:
        {
            if(1 == st_gPPCurrent[en_fPPIndex].u8_mEnabled)
            {
                /* Enable CAN Auto Formating */
            }
            else
            {
                /* Disble CAN Auto Formating*/
            }         
        }
        break;
        
    case PROG_PARAM_25:
        {
            if(1 == st_gPPCurrent[en_fPPIndex].u8_mEnabled)
            {
                /* Enable Auto Flow Control */
            }
            else
            {
                /* Disble Auto Flow Control */ 
            }         
        }
        break;
        
    case PROG_PARAM_29:
        {
            if(1 == st_gPPCurrent[en_fPPIndex].u8_mEnabled)
            {
                /* Enable CAN DLC show */
            }
            else
            {
                /* Disable CAN DLC show */
            }         
        }
        break;    
        
    default:
        break;
    }
    
    return en_lResult;
}

/**************************************************************************************************/
/* End of PP_HANDLER.c                                                                            */
/**************************************************************************************************/

