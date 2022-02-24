/*************************************************************************************************/
/*                                                                                               */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                          */
/*                                                                                               */
/*************************************************************************************************/
/*                                                                                               */
/* All Rights Reserved Copyright (C) 2014, Technical Innovations N Solutions.                    */
/*                                                                                               */
/* Redistribution and use in source and binary forms, with or without                            */
/* modification, are not permitted in any case                                                   */
/*                                                                                               */
/* TINS's name may not be used to endorse or promote products derived from                       */
/* this software without specific prior written permission.                                      */
/*                                                                                               */
/*************************************************************************************************/
/*************************************************************************************************/
/* \File Name   : ISO14230_KWP_Priv.h                                                            */
/* \Author      : Prashanth.A                                                                    */
/* \Version 	: V1.0     					                                                     */
/* \Date        : 08/03/2016    	                                                             */
/* @Description : kwp frame work                                                                 */
/*************************************************************************************************/

#ifndef _ISO14230_FAST_PRIV_H_
#define _ISO14230_FAST_PRIV_H_

/*************************************************************************************************/
/* System Header Files Section                                                                   */
/*************************************************************************************************/

#include "Includes.h"

#include "TEOBD2_public.h"

/*************************************************************************************************/
/* User Header Files Section                                                                     */
/*************************************************************************************************/

/*************************************************************************************************/
/* Private Global Definitions Section                                                            */
/*************************************************************************************************/

/* To hold KLine Default States */
typedef enum
{
    KLINE_IDLE_STATE = 0x00,
    KLINE_TESTER_PRESENT_STATE,
    KLINE_RECEIVE_STATE
        
}EN_KLINE_STATE_t;

/*************************************************************************************************/
/* Private Global Variables Section                                                              */
/*************************************************************************************************/

/*************************************************************************************************/
/* Private Functions Section                                                                     */
/*************************************************************************************************/

#if 0
/* */
static EN_STACK_RESULT_t ISO14230_KLineReceiveStateHander(EN_KLINE_STATE_t * p_fKLineState) ;

/* */
static EN_STACK_RESULT_t ISO14230_KLineTesterPresentStateHander(EN_KLINE_STATE_t * p_fKLineState);

/* */
static EN_STACK_RESULT_t ISO14230_KLineIdleStateHander(EN_KLINE_STATE_t * p_fKLineState);

/* */
static void ISO14230_KLineProcessConsecutiveFrame(void);

/* */
static void ISO14230_KLineProcessFirstFrame(void);

/* */
static INT8U ISO14230_IsTpResponse(INT8U * p_fBuff);

/* */
static INT8U ISO14230_IsTpRequest(INT8U * p_fBuff);

#endif

#endif

/**************************************************************************************************/
/* 						End of ISO14230_KWP_priv.h                                                */
/**************************************************************************************************/
