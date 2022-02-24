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
/* \File Name   : GENERAL_CMD_HANDLERS.h                                                          */
/* \Author      : PRASHANTH                                                                       */
/* \Version 	:                                                                                 */
/* \Date        : 25-03-2017                                                                      */
/*                                                                                                */
/* @Description : General Cmd Hadlers Frame work                                                  */
/**************************************************************************************************/

#ifndef _GENERAL_CMD_HANDLERS_H_
#define _GENERAL_CMD_HANDLERS_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "XTP_TE_public.h"

//#include "XTP_public.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* */
extern EN_XTP_RESULT_t XTP_XTZ(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTRST(INT8U *p_fSrc,INT16U u16_lLength);

/* */
extern EN_XTP_RESULT_t XTP_XTE(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTI(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_GNRL_XTM(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSN(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSBR(INT8U * p_fArgs, INT8U u8_fArgCount);

/* */
extern EN_XTP_RESULT_t XTP_XTWBR(INT8U * p_fArgs, INT8U u8_fArgCount);

/* */
extern EN_XTP_RESULT_t XTP_XTDI(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTMFR(INT8U *p_fSrc, INT16U u16_fLength);

/********************** Voltage Reading & Other Commands **************************/
/* */
extern EN_XTP_RESULT_t XTP_XTRV(INT8U *p_fSrc, INT16U u16_fLength);

#endif

/**************************************************************************************************/
/* End of GENERAL_CMD_HANDLERS.h                                                                  */
/**************************************************************************************************/

