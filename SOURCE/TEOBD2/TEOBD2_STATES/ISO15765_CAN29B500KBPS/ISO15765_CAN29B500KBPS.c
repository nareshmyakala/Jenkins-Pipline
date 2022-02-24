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
/* \File Name   : IS015765_CAN_29_500.c                                                           */
/* \Author      :                                                                                 */
/* \Version 	:                                                                                 */
/* \Date        : 08/03/2016                                                                      */
/*                                                                                                */
/* @Description : IS015765_CAN_29_500 FRAME WORK                                                  */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "DATACONV.h"

#include "ISO15765_CAN29B500KBPS_public.h"
#include "ISO15765_CAN29B500KBPS_private.h"

#include "TEOBD2_public.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_Init(void)                          */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_Init(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
                                                                                INT32U u32_gTickCount)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_Handler\                      */
/*                                                (EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_Handler(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
                                                                                INT32U u32_gTickCount)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    /* Return The Result */
    return en_lResult;	
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_Exit(void)                          */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_Exit(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
                                                                                INT32U u32_gTickCount)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_WriteData\                          */
/*                                                      (void * p_fWriteBuffer, INT8U u8_fLenght) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_WriteData(void * p_fWriteBuffer, INT16U u16_fLenght)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : INT8U ISO15765_CAN29B500KBPS_ReadData(INT8U * p_fReadBuffer)                 */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

INT8U ISO15765_CAN29B500KBPS_ReadData(INT8U * p_fReadBuffer)
{
    return 0;
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_WaitForResp(void)                   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO15765_CAN29B500KBPS_WaitForResp(void)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* End of IS015765_CAN_29_500.c                                                                   */
/**************************************************************************************************/
