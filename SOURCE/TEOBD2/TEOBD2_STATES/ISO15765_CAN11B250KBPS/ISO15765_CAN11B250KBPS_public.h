/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2014-15, Think Embedded Pvt. Ltd. (TEPL)                     */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   :  MULTICAN_TEST_APP.h                                                            */
/* \Author      :  IRFAN AHMED FAROOQUI                                                           */
/* \Version 	:       					                                                      */
/* \Date        :               	                                                              */
/* @Description :                                                                                 */
/**************************************************************************************************/


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
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

extern EN_STACK_RESULT_t ISO15765_CAN11B250KBPS_Init(\
                                EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, INT32U u32_gTickCount);

extern EN_STACK_RESULT_t ISO15765_CAN11B250KBPS_Handler(\
                                EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, INT32U u32_gTickCount);

extern EN_STACK_RESULT_t ISO15765_CAN11B250KBPS_Exit(\
                                EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, INT32U u32_gTickCount);

extern EN_STACK_RESULT_t ISO15765_CAN11B250KBPS_WriteData(void * p_fWriteBuffer, INT16U u16_fLenght);

extern INT8U ISO15765_CAN11B250KBPS_ReadData(INT8U * p_fReadBuffer);

extern EN_STACK_RESULT_t ISO15765_CAN11B250KBPS_WaitForResp(void);

/**************************************************************************************************/
/* 						End of MULTICAN_TEST_APP.h                                                */
/**************************************************************************************************/
