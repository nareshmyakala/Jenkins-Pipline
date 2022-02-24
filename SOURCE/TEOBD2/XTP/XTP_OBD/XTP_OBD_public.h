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
/* \File Name   : OBD_CMD_HANDLERS.h                                                              */
/* \Author      : PRASHANTH                                                                       */
/* \Version 	:                                                                                 */
/* \Date        : 25-03-2017                                                                      */
/*                                                                                                */
/* @Description : OBD Handlers Frame Work                                                         */
/**************************************************************************************************/

#ifndef _OBD_CMD_HANDLERS_H_
#define _OBD_CMD_HANDLERS_H_

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
extern EN_XTP_RESULT_t XTP_XTAT(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTDP(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTH(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTDPN(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTMA(INT8U *p_fSrc, INT16U u16_lLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSP(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSH(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTST(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTMR(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTRA(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTTP(INT8U *p_fSrc, INT16U u16_fLength);

extern EN_XTP_RESULT_t XTP_XTTM(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTS(INT8U *p_fSrc, INT16U u16_fLength);

#endif

/**************************************************************************************************/
/* End of OBD_CMD_HANDLERS.h                                                                      */
/**************************************************************************************************/

