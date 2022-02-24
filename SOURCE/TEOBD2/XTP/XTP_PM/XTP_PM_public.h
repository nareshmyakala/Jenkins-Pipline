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
/* \File Name   : POWERSAVE_HANDLERS.h                                                            */
/* \Author      : PRASHANTH                                                                       */
/* \Version 	:                                                                                 */
/* \Date        : 25-03-2017                                                                      */
/*                                                                                                */
/* @Description : Powersave Handlers Frame Work                                                   */
/**************************************************************************************************/

#ifndef _POWERSAVE_HANDLERS_H_
#define _POWERSAVE_HANDLERS_H_

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
extern EN_XTP_RESULT_t XTP_XTSLCS(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSLEEP(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSLLT(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSLPCP(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSLUIT(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSLUWP(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSLX(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSLXS(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSLXST(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSLXWT(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSLXP(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSLLT(INT8U *p_fSrc, INT16U u16_fLength);

#endif

/**************************************************************************************************/
/* End of POWERSAVE_HANDLERS.h                                                                    */
/**************************************************************************************************/

