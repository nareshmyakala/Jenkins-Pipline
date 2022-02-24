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
/* \File Name   :IS015765_CAN_11_250.c                                                            */
/* \Author      :                                                                                 */
/* \Version 	:                                                                                 */
/* \Date        : 08/03/2016                                                                      */
/*                                                                                                */
/* @Description: IS015765_CAN_11_250 FRAME WORK                                                   */
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

#include "ISO15765_2.h"
#include "CAN_IF.h"

#include "ISOTPQ_public.h"
#include "XTP_public.h"

#include "ISO15765_2.h"

#include "ISO15765_CAN11B500KBPS_public.h"
#include "ISO15765_CAN11B500KBPS_private.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Dummy Variable for Queue Variable */
ST_ISOTP_DATA_t st_gCanTpLog = {0,};

volatile INT8U u8_gDatatCmpltdFlag = 0x00;

/**************************************************************************************************/
/* Function Name   : EN_STACK_HANDLER_RESULT_t ISO15765_CAN_11_250_Init(void)                     */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO15765_CAN11B500KBPS_Init(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
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
            .en_mCanIfBaudRate          = CAN_500_KBPS,
            .fp_CanIfTxHandler          = CAN_TxHandler,
            .fp_CanIfRxHandler          = CAN_RxHandler,
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
        //.en_mAddMode = NORMAL,
        .p_mRxIndication =  ISOTP_DataReceived,
        .p_mTxConformation = PNULL,
        .p_mErrorIndication = PNULL
    };
    
    /* Init The ISOTP Data */
    ISO15765_Init(&st_lISOTP_Data);
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t IS015765_CAN_11_500_Handler\                               */
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

EN_STACK_RESULT_t ISO15765_CAN11B500KBPS_Handler(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
                                                            INT32U u32_gTickCount)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    if(1 == u8_gCanBusMonitorStaus || 1 == u8_gCanBusMonitorHeadrs)
    {
        if(1 == u8_gIsoTpDataRecvdFlag)
        {
            /* Read the Msg and Display */
            ISOTPQ_ReadMsg(&st_gCanTpLog);
            CAN_DISPLAY_XTMA(u32_gISOTP_CANid ,pu8_gISOTPDataRcvPntr , u32_gISOTPdLength);               
        }
        else
        {
        }
    }
    else
    {
        /* Check whether ISOTP Send Data Satrted or not */
        if(1 == u8_gIsoTpDataRecvdFlag)
        {
            if(PNULL != pu8_gISOTPDataRcvPntr)
            {
                /* */
                CAN_DISPLAY(u32_gISOTP_CANid ,pu8_gISOTPDataRcvPntr , u32_gISOTPdLength);
            }
            else
            {
               /* No Action */
            }
            
             /* */
            u8_gIsoTpDataRecvdFlag = 0x00;

            /* */
            u8_gDatatCmpltdFlag = 1;
            
            /* */
            u8_gTEOBD2TimeoutFlag = 0x00;

            /* Make the Flag to 0 */
            u8_gDatatCmpltdFlag = 0;

            /* */
            u8_gTEOBD2ReqstSentFlag = 0x00;
                
        } 
        else
        {
            if((1 == u8_gDatatCmpltdFlag))
            {
                /* make the Flag to 0 */
                u8_gDatatCmpltdFlag = 0;
            }
            else
            {
                /* No Action */
            }
        }
        if((0 == u8_gDatatCmpltdFlag))
        {
            if((1 == u8_gTEOBD2TimeoutFlag) && (0 == u8_gIsoTpDataRecvdFlag))
            {
                /* */
                u8_gTEOBD2TimeoutFlag = 0x00;
                
                /* Make the Flag to 0 */
                u8_gDatatCmpltdFlag = 0;
                
                /* */
                u8_gTEOBD2ReqstSentFlag = 0x00;
                
                /* AutoProtocol Search */
                if(0 == u8_gAutoPrtcl)
                {
                    /* Display no data */
                    p_gXT_ReqComplete((INT8U *)"NO DATA\r\n#", 10);
                }
                else
                {
                    /* Switch The State */
                    *p_stfOBDII_State = IS014230_FAST;
                }
            }
            else
            {
                /* No action */
            }
        }
        else
        {
           /* No Action */
        } 
     }
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_HANDLER_RESULT_t IS015765_CAN_11_500_Exit(void)                     */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO15765_CAN11B500KBPS_Exit(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
                                                                              INT32U u32_gTickCount)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;

    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO15765_CAN11B500KBPS_WriteData\                          */
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

EN_STACK_RESULT_t ISO15765_CAN11B500KBPS_WriteData(void * p_fWriteBuffer, INT16U u16_fLenght)
{
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    /* Arry to Hold the Payload Data */
    INT8U au8_lPayloadBuff[4096] = {0, };

    /* */
    INT16U u16_lPayloadLen = 0x00;

    /* Calculating the Payload */
    u16_lPayloadLen = (u16_fLenght - 1) / 2;

    /* Convert the Payload Lenght to PAN Format */
    if(COMMON_OK == COMMON_PAN2ByteArray(p_fWriteBuffer, &au8_lPayloadBuff[0], u16_lPayloadLen))
    {
        /* */
        u32_gTEOBD2TimeoutCounter = 0x00;
        
        /* */
        u8_gTEOBD2ReqstSentFlag = 0x01;
        
        /* */
        u8_gIsoTpDataRecvdFlag = 0x00;
        
        /* */
        pu8_gISOTPDataRcvPntr = PNULL;
        
        /* Request The Data */
        if(ISOTP_ERROR == ISO15765_SendData(u32_gTxHeaderId, &au8_lPayloadBuff[0], u16_lPayloadLen))
        {
           /* Update the Error */
           en_lResult = STACK_ERROR;
        }
        else
        {
            /* No Action */
        }        
    }
    else
    {
        en_lResult = STACK_ERROR;
    }

    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : INT8U ISO15765_CAN11B500KBPS_ReadData(INT8U * p_fReadBuffer)                 */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

INT8U ISO15765_CAN11B500KBPS_ReadData(INT8U * p_fReadBuffer)
{
    return 0;
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO15765_CAN11B500KBPS_WaitForResp(void)                   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO15765_CAN11B500KBPS_WaitForResp(void)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;

    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* End of IS015765_CAN_11_250.c                                                                   */
/**************************************************************************************************/
