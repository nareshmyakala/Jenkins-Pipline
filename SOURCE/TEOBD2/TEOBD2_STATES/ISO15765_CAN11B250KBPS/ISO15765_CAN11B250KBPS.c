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
/* \File Name   : CAN_MGR.C                                                                       */
/* \Author      : IRFAN AHMED FAROOQUI                                                            */
/* \Version 	: V1.0     					                                  */
/* \Date        : 27/10/2015     	                                                          */
/* @Description : CAN manager FrameWork                                                           */
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

#include "CAN_IF.h"

#include "ISO15765_2.h"

#include "ISO15765_CAN11B250KBPS_public.h"
#include "ISO15765_CAN11B250KBPS_private.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO15765_CAN11B250KBPS_Init(void)                          */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO15765_CAN11B250KBPS_Init(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
    INT32U u32_gTickCount)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
      /* Init the CAN Stur Structures */
    ST_CAN_MO_CFG_t st_lCANTxMOConfig[3] =
    {
        {
            .en_mCanCh                 = CAN0,
            .u8_mCanMOIndex             = 0,
            .u32_mCanMsgId              = 0x7E0,
            .u32_mAcceptMask            = 0x7FF,
            .u8_mDLC                    = 8,
            .en_mCanIdType              = CAN_STD_ID,
            .en_mMOType                 = CAN_MB_TRANSMIT,
            .en_mCanIfBaudRate          = CAN_250_KBPS,
            .fp_CanIfTxHandler          = ISO15765_TxHandler,
            .fp_CanIfRxHandler          = ISO15765_RxHandler,
            .fp_CanIfBusOffHandler      = CAN_BusOffHandler,
            .fp_CanIfErrorHandler       = CAN_ErrorHandler,
            .u8_mEOL                    = 0,
        },

        {
            .en_mCanCh                  = CAN0,
            .u8_mCanMOIndex             = 0,
            .u32_mCanMsgId              = 0x7E8,
            .u32_mAcceptMask            = 0x7FF,
            .u8_mDLC                    = 8,
            .en_mCanIdType              = CAN_STD_ID,
            .en_mMOType                 = CAN_MB_RECEIVE,
            .u8_mEOL                    = 0,
        },

        {     
            .u8_mEOL                    = 1,    
        },
    };
    
    /* init the CAN */
    CAN_IF_Init(st_lCANTxMOConfig);

    /* Initialize the ISOTP Parameters */
    ST_ISOTP_INIT_t st_lISOTP_Data = 
    {
        .u32_mTxTimeOut = 5000,
        .u32_mFcTimeOut = 5000,
       // .en_mAddMode = NORMAL,
        .p_mRxIndication =  ISOTP_DataReceived,
        .p_mTxConformation = PNULL,
        .p_mErrorIndication = ISOTO_ErrorType
    };
    
    /* Init The ISOTP Data */
    ISO15765_Init(&st_lISOTP_Data);
    
    /* Return The Result */
    return en_lResult;	
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO15765_CAN11B250KBPS\                                    */
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

EN_STACK_RESULT_t ISO15765_CAN11B250KBPS_Handler(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
                                                                                INT32U u32_gTickCount)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    /* Return The Result */
    return en_lResult;		
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t IS015765_CAN_11_500_Exit(void)                             */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO15765_CAN11B250KBPS_Exit(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
                                                                                INT32U u32_gTickCount)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    /* Return The Result */
    return en_lResult;	
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO15765_CAN11B250KBPS_WriteData\                          */
/*                                                      (void * p_fWriteBuffer, INT8U u8_fLenght)    */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO15765_CAN11B250KBPS_WriteData(void * p_fWriteBuffer, INT16U u16_fLenght)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : INT8U ISO15765_CAN11B250KBPS_ReadData(INT8U * p_fReadBuffer)                       */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

INT8U ISO15765_CAN11B250KBPS_ReadData(INT8U * p_fReadBuffer)
{
    return 0;	
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO15765_CAN11B250KBPS_WaitForResp(void)                   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO15765_CAN11B250KBPS_WaitForResp(void)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* 	End of ISO15765_CAN11B250KBPS.c                                                          */
/**************************************************************************************************/
