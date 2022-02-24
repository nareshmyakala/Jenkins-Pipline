/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2018, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/*  File Name   : ISO15765_2_Priv.h                                                               */
/*  Author      : B.Srilatha                                                                      */
/*  Version 	: v1.0                                                                            */
/*  Date        : 10-06-2018                                                                      */
/*                                                                                                */
/* @Description : ISO15765 Frame Work                                                             */
/**************************************************************************************************/

#ifndef _ISO15765_2_PRIV_H_
#define _ISO15765_2_PRIV_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

/**************************************************************************************************/
/* Private Global Definitions Section                                                             */
/**************************************************************************************************/

/* Macro for Isotp data size */
#define ISO15765_MAX_DATA_SIZE  ( 4095 )

/* Macros for Fc parameters*/
#define FC_CTS                  ( 0x00 )
#define FC_WAIT                 ( 0x01 )
#define FC_OVERFLOW             ( 0x02 )

#define TRUE                    ( 0x01 )
#define FALSE                   ( 0x00 )

/* Enum for selecting  the nibble */
typedef enum
{
    LOWER = 0,
    HIGHER
      
}EN_NIBBLE_t;

/* Enum for Tx States */
typedef enum
{
    TX_INIT_STATE = 0,
    TX_SINGLE_FRAME_STATE,
    TX_FIRST_FRAME_STATE,
    RX_FLOW_CONTROL_STATE,
    TX_CONSECUTIVE_FRAME_STATE,
    TX_SUCCESS_STATE,
    TX_ERROR_STATE,
    TX_TESETR_PRSNT

}EN_TX_STATES_t;

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

/* Isotp intilization */
static void ISO15765_TxInitState(EN_TX_STATES_t * pen_fTxStatePtr);

/* Isotp Tx Single frame State */
static void ISO15765_TxSingleFrameState(EN_TX_STATES_t * pen_fTxStatePtr);

/* Isotp Tx first frame State */
static void ISO15765_TxFirstFrameState(EN_TX_STATES_t * pen_fTxStatePtr);

/* Isotp Rx Flow Control frame State */
static void ISO15765_RxFlowControlFrameState(EN_TX_STATES_t * pen_fTxStatePtr);

/*Isotp Tx consecutive frame State*/
static void ISO15765_TxConsecutiveFrameState(EN_TX_STATES_t * pen_fTxStatePtr);

/* Isotp Tx Success State */
static void ISO15765_TxSuccessState(EN_TX_STATES_t * pen_fTxStatePtr);

/* Isotp Tx Error State */
static void ISO15765_TxErrorState(EN_TX_STATES_t * pen_fTxStatePtr);

/* Isotp set nibble */
static void ISO15765_SetNibble(INT8U * pu8_fDataPtr, INT8U u8_fData, EN_NIBBLE_t en_fNibble);

/* Isotp get nibble */
static INT8U ISO15765_GetNibble(INT8U u8_fData, EN_NIBBLE_t en_fNibble);

/* Function for isotp Tx timeout enable */
static void ISO15765_TxTimeOutEnable(void);

/* Function for isotp Tx timeout disable */
static void ISO15765_TxTimeOutDisable(void);

#endif

/**************************************************************************************************/
/* End of  ISO15765_2_Priv.h                                                                      */
/**************************************************************************************************/
