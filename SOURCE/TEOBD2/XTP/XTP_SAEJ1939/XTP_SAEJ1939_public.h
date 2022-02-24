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
/*  File Name   : XTP_SAEJ1939_public.h                                                           */
/*  Author      : Santhosh                                                                        */
/*  Version 	:                                                                                 */
/*  Date        : 25-04-2018                                                                      */
/*                                                                                                */
/* @Description : XTP_SAEJ1939                                                                    */
/**************************************************************************************************/

#ifndef _XTP_SAEJ1939_PUBLIC_H_
#define _XTP_SAEJ1939_PUBLIC_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "XTP_TE_public.h"

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

extern EN_XTP_RESULT_t XTP_XTJMA(INT8U *p_fSrc, INT16U u16_fLength);

extern EN_XTP_RESULT_t XTP_XTJMPN(INT8U *p_fSrc, INT16U u16_fLength);

extern EN_XTP_RESULT_t XTP_XTJMP(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTJDM(INT8U *p_fSrc, INT16U u16_fLength);

extern EN_XTP_RESULT_t XTP_XTJTP(INT8U *p_fSrc, INT16U u16_fLength);

extern EN_XTP_RESULT_t XTP_XTJDA(INT8U *p_fSrc, INT16U u16_fLength);

extern EN_XTP_RESULT_t XTP_XTJNM(INT8U *p_fSrc, INT16U u16_fLength);

#endif

/**************************************************************************************************/
/* End of  XTP_SAEJ1939_public.h                                                                  */
/**************************************************************************************************/
