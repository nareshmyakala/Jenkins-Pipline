/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2015, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   :SAEJ1939_29_250.h                                                          */
/* \Author      :                                                                                 */
/* \Version 	:                                                                                 */
/* \Date        :08/03/2016                                                              */
/*                                                                                                */
/* @Description: SAEJ1939_29_250 FRAME WORK                                                                                   */
/**************************************************************************************************/

#ifndef SAEJ1939_29_250_H_
#define SAEJ1939_29_250_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "TEOBD2_public.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Global Variable Section                                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

extern EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_Init(\
                                EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, INT32U u32_gTickCount);

extern EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_Handler(\
                                EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, INT32U u32_gTickCount);

extern EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_Exit(\
                                EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, INT32U u32_gTickCount);

extern EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_WriteData(void * p_fWriteBuffer, INT16U u16_fLenght);

extern INT8U SAEJ1939_CAN29B250KBPS_ReadData(INT8U * p_fReadBuffer);

extern EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_WaitForResp(void);

#endif

/**************************************************************************************************/
/* End of SAEJ1939_29_250.h                                                                              */
/**************************************************************************************************/
