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
/* \File Name   : IS015765_CAN_29_500.h                                                           */
/* \Author      :                                                                                 */
/* \Version 	:                                                                                 */
/* \Date        : 08/03/2016                                                                      */
/*                                                                                                */
/* @Description : IS015765_CAN_29_500 FRAME WORK                                                  */
/**************************************************************************************************/

#ifndef _IS015765_CAN_29_500_H_
#define _IS015765_CAN_29_500_H_

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

extern EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_Init(\
                                EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, INT32U u32_gTickCount);

extern EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_Handler(\
                                EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, INT32U u32_gTickCount);

extern EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_Exit(\
                                EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, INT32U u32_gTickCount);

extern EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_WriteData(void * p_fWriteBuffer, INT16U u16_fLenght);

extern INT8U ISO15765_CAN29B500KBPS_ReadData(INT8U * p_fReadBuffer);

extern EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_WaitForResp(void);

#endif

/**************************************************************************************************/
/* End of IS015765_CAN_29_500.h                                                                   */
/**************************************************************************************************/
