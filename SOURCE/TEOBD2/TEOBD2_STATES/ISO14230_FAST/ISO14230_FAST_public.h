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
/* \File Name   : ISO14230_FAST.h                                                                */
/* \Author      : Prashanth.A                                                                    */
/* \Version 	: v1.0     					                                 */
/* \Date        : 08/03/2016    	                                                         */
/* @Description : ISO14230 FAST frame work                                                       */
/*************************************************************************************************/


/*************************************************************************************************/
/* System Header Files Section                                                                   */
/*************************************************************************************************/

/*************************************************************************************************/
/* User Header Files Section                                                                     */
/*************************************************************************************************/

#include "Includes.h"

#include "TEOBD2_public.h"

/*************************************************************************************************/
/* Export Global Definitions Section                                                             */
/*************************************************************************************************/

/*************************************************************************************************/
/* Export Global Variables Section                                                               */
/*************************************************************************************************/

/*************************************************************************************************/
/* Export Functions Section                                                                      */
/*************************************************************************************************/

/* */
extern EN_STACK_RESULT_t ISO14230_KlineFast_Init(\
                                EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, INT32U u32_gTickCount);

/* */
extern EN_STACK_RESULT_t ISO14230_KlineFast_Handler(\
                                EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, INT32U u32_gTickCount);

/* */
extern EN_STACK_RESULT_t ISO14230_KlineFast_Exit(\
                                EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, INT32U u32_gTickCount);

/* */
extern EN_STACK_RESULT_t ISO14230_KlineFast_WriteData(void * p_fWriteBuffer, INT16U u16_fLenght);

/* */
extern INT8U ISO14230_KlineFast_ReadData(INT8U * p_fReadBuffer);

/* */
extern EN_STACK_RESULT_t ISO14230_KlineFast_WaitForResp(void);

/*************************************************************************************************/
/* 						End of MULTICAN_TEST_APP.h                       */
/*************************************************************************************************/
