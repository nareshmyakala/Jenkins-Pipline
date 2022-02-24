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
/* \File Name   : PP_HANDLER.h                                                                    */
/* \Author      : PRASHANTH                                                                       */
/* \Version 	:                                                                                 */
/* \Date        : 14-12-2016                                                                      */
/*                                                                                                */
/* @Description : Programble Paramters Frame work                                                 */
/**************************************************************************************************/

#ifndef _PP_HANDLER_H_
#define _PP_HANDLER_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "XTP_TE_public.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

/* Program parameter Status */
typedef enum
{   
    PP_OFF = 0x00,
    PP_ON,
    PP_OUT_OF_RANGE       
}EN_PP_STATUS_t;

/* */
typedef enum
{
    PP_SUCCESS = 0x00,
    PP_ERROR
        
}EN_PP_RESULT_t;

/* Enum to hold Program Params */
typedef enum
{
    PROG_PARAM_00 = 0x00,
    PROG_PARAM_01,
    PROG_PARAM_02,
    PROG_PARAM_03,
    PROG_PARAM_04,
    PROG_PARAM_05,
    PROG_PARAM_06,
    PROG_PARAM_07,
    PROG_PARAM_08,
    PROG_PARAM_09,
    PROG_PARAM_0A,
    PROG_PARAM_0B,
    PROG_PARAM_0C,
    PROG_PARAM_0D,
    PROG_PARAM_0E,
    PROG_PARAM_0F,
    PROG_PARAM_10,
    PROG_PARAM_11,
    PROG_PARAM_12,
    PROG_PARAM_13,
    PROG_PARAM_14,
    PROG_PARAM_15,
    PROG_PARAM_16,
    PROG_PARAM_17,
    PROG_PARAM_18,
    PROG_PARAM_19,
    PROG_PARAM_1A,
    PROG_PARAM_1B,
    PROG_PARAM_1C,
    PROG_PARAM_1D,
    PROG_PARAM_1E,
    PROG_PARAM_1F,
    PROG_PARAM_20,
    PROG_PARAM_21,
    PROG_PARAM_22,
    PROG_PARAM_23,
    PROG_PARAM_24,
    PROG_PARAM_25,
    PROG_PARAM_26,
    PROG_PARAM_27,
    PROG_PARAM_28,
    PROG_PARAM_29,
    PROG_PARAM_2A,
    PROG_PARAM_2B,
    PROG_PARAM_2C,
    PROG_PARAM_2D,
    PROG_PARAM_2E,
    PROG_PARAM_2F,
    MAX_PP_COUNT
        
}EN_PROG_PARAMS_t;

/* Structure for Programable Parameter */
typedef struct
{
    EN_PROG_PARAMS_t en_mPPIndex;
    INT8U u8_mPPValue;
    float f32_mPPFactor;
    struct
    {
        INT8U u8_mIsBoolean:1;
        INT8U u8_mEnabled:1;
        INT8U u8_mEffect:1;
        INT8U u8_mUseFormula:1; 
    };
    
}ST_PROG_PARAMS_t;

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/*  */
extern ST_PROG_PARAMS_t st_gPPBackup[MAX_PP_COUNT];

/* */
extern ST_PROG_PARAMS_t st_gPPCurrent[MAX_PP_COUNT];

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* */
extern void PP_HANDLERS_Init(void);

/* */
extern EN_XTP_RESULT_t XTP_XTPPS(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTPPS(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTPPON(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTPPOFF(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_PP_RESULT_t PP_HANDLER_WriteValaue(EN_PROG_PARAMS_t en_fPPIndex, INT8U u8_fPPValue);

/* */
extern EN_PP_RESULT_t PP_HANDLER_WriteStatus(EN_PROG_PARAMS_t en_fPPIndex, \
    EN_PP_STATUS_t en_fStatus);

/* */
extern EN_XTP_RESULT_t XTP_XTPPSV(INT8U *p_fSrc, INT16U u16_fLength);

#endif

/**************************************************************************************************/
/* End of PP_HANDLER.h                                                                            */
/**************************************************************************************************/

