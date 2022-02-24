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
/* \File Name   : XTCOM_HANDLERS.h                                                                */
/* \Author      : harshan                                                                         */
/* \Version 	:                                                                                 */
/* \Date        : 12-12-2016                                                                      */
/*                                                                                                */
/* @Description : XTCOM                                                                           */
/**************************************************************************************************/

#ifndef _XTCOM_HANDLERS_H_
#define _XTCOM_HANDLERS_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "XTP_TE_public.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

/* Enum to Hold The Result */
typedef enum
{
    XTP_SUCCESS = 0x00,
    XTP_ERROR
	
}EN_XTP_RESULT_t;

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* */
extern EN_XTP_RESULT_t XTP_XTA(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTRB(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSPC(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSPB(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTP(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTIIA(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTCP(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTFC(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTCEA(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTDM(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTIFR(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTJE(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTJHF(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTJS(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTJTM(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTMP(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTPB(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSI(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTTPA(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSA(INT16U * p_fArgs, INT8U u8_fArgCount);

/* */
extern EN_XTP_RESULT_t XTP_XTSATI(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTSLU(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTMODE(INT16U * p_fArgs, INT8U u8_fArgCount);

/* */
extern EN_XTP_RESULT_t XTP_XTDIX(INT16U * p_fArgs, INT8U u8_fArgCount);

/* */
extern EN_XTP_RESULT_t XTP_XTPP(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTRH(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTEA(INT8U *p_fSrc, INT16U u16_fLength);

/* */
extern EN_XTP_RESULT_t XTP_XTRQ(INT8U *p_fSrc, INT16U u16_fLength);

#endif

/**************************************************************************************************/
/* End of XTCOM_HANDLERS.h                                                                        */
/**************************************************************************************************/

