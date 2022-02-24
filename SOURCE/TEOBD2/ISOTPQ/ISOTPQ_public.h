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
/* \File Name   : ISOTPQ.h                                                                        */
/* \Author      : PRASHANTH.A                                                                     */
/* \Version 	:                                                                                 */
/* \Date        : 18-10-2017                                                                      */
/*                                                                                                */
/* @Description : ISOTPQ Frame Work                                                               */
/**************************************************************************************************/

#ifndef _ISOTPQ_H_
#define _ISOTPQ_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "ISO15765_2.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

/* */
typedef enum
{
    Q_READ_SUCCESS,
    Q_READ_FAILURE
}EN_ISOTPLOGQUEUE_READ_STATUS_t;

/* */
typedef enum
{
    Q_WRITE_SUCCESS,
    Q_WRITE_BUFFER_FULL,
    Q_WRITE_FAILURE
}EN_ISOTPLOGQUEUE_WRITE_STATUS_t;

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/* Queue write pointer */
extern ST_ISOTP_DATA_t * p_gISOTPLogWritePtr ;

/* Queue read pointer */
extern ST_ISOTP_DATA_t * p_gISOTPLogReadPtr ;

/* Available Message Counter */
extern INT16U u16_gISOTP_MsgCnt;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* */
extern void ISOTPLOGQUEUE_Init(void);

/* */
extern void ISOTPLOGQUEUE_Clear(void);

/* */
extern EN_ISOTPLOGQUEUE_WRITE_STATUS_t ISOTPQ_WriteMsg(const ST_ISOTP_DATA_t * p_fISOTPLogMsg);

/* */
extern EN_ISOTPLOGQUEUE_READ_STATUS_t ISOTPQ_ReadMsg(ST_ISOTP_DATA_t * p_fISOTPLogMsg);

/* */
extern INT16U ISOTPQ_LOGQUEUE_ReadAvailMsgCount(void);

/* */
extern ST_ISOTP_DATA_t ast_gISOTPLogBuffer[];

#endif

/**************************************************************************************************/
/* End of ISOTPQ.h                                                                                */
/**************************************************************************************************/

