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
/*  File Name   : ISO15765_2.h                                                                    */
/*  Author      : B.Srilatha                                                                      */
/*  Version 	: v1.0                                                                            */
/*  Date        : 10-06-2018                                                                      */
/*                                                                                                */
/* @Description : ISO15765 Frame Work                                                             */
/**************************************************************************************************/

#ifndef _ISO15765_2_H_
#define _ISO15765_2_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

#define CAN_IF_OTA_REQ_HEADER                      ( 0x7E0 )

typedef enum
{
  ISOTP_ERROR = 0,
  ISOTP_SUCCESS
    
}ISOTP_STAUS_t;

/* Enum for frame types */
typedef enum
{
  SINGLE_FRAME = 0x00,
  FIRST_FRAME,
  CONSECUTIVE_FRAME,
  FLOWCONTROL_FRAME

}EN_FRAME_TYPE_t;

/* Enum For error selection*/
typedef enum
{
  OK = 0,
  INVALID_ADDMOD,
  DATA_LENGTH,
  WRONG_SN,
  INVALID_FC_STATUS,
  INVALID_STmin,
  TIMEOUT_FC,
  WFT_OVRN,
  BUFFER_OVFLW,
  ERROR

}EN_ERROR_t;

/* Structure for Isotp Initilization parameters */
typedef struct 
{
  INT32U u32_mTxTimeOut;
  INT32U u32_mFcTimeOut;
  void (*p_mRxIndication)(INT32U u8_fCanData, INT8U *pu8_fData, INT32U u32_fLength);
  void (*p_mTxConformation)(INT32U u8_fCanId);
  void (*p_mErrorIndication)(INT8U u8_fError);
    
}ST_ISOTP_INIT_t;

/* Enum Addressing Mode selection */
typedef enum
{
	NORMAL_ADDRESSING = 0,
	EXTENDED_ADDRESSING = 1
}AddressingMode_t;

/* stack enums ND strUctures */
typedef enum
{
    EN_SIGLE_FRAME = 0x00,
    EN_FIRST_FRAME = 0x01,
    EN_CONSECUTIVE_FRAME = 0x02,
    EN_FLOW_FRAME = 0x03
}FrameType_t;

/* Structure for Isotp Data */
typedef struct
{
  INT32U u32_mCanId;
  INT8U au8_mData[8];
  INT8U u8_mDLC;
  FrameType_t RxFrameType;

}ST_ISOTP_DATA_t;

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/* Testing Purpose Only. */
extern INT8U au8_gBuffer[8];
/* This flag variable is used to indicate the payload type of '0x676' frame to be 
sent on the CAN bus. */
extern INT8U u8_gFrameFlag;
/*************************/

/* This is the counter variable used for delays. */
extern INT16U u16_gEvntCntr;

/* This is another counter variable for 40seconds delay. */
extern INT16U u16_gEvntCntr2;

/* TESTACK variables */
extern INT8U u8_gIsoTpDataRecvdFlag;

/* */
extern AddressingMode_t en_gAddressingMode;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Reciving ISOTP Rx Data in Normal Addressing */
extern void ISO15765_RxNormalAdd(ST_ISOTP_DATA_t * pst_fData);

/* Isotp One Ms Handler */
extern void ISO15765_OneMsHandler(void);

/* ISotp Tx State Mission */
extern void ISO15765_TxScheduler(void);

/* Isotp Rx Handler */
extern void ISO15765_RxHandler(void * pv_fRxData);

/* Isotp Initilization */
extern void ISO15765_Init(ST_ISOTP_INIT_t * pst_fInitParams);

/* Isotp Update callbacks */
extern void ISO15765_UpdateCallBacks(void (* p_fRxIndication)(INT32U, INT8U *, INT32U), \
						void (* p_fErrorIndication)(INT8U));
/* Isotp Send Data */																
extern ISOTP_STAUS_t ISO15765_SendData(INT32U u32_fArbitrationId, INT8U * pu8_fData,INT16U u16_fDlc);

/* Isotp Send Flow Control Frame */
extern void ISO15765_SendFlowControlFrame(INT8U u8_fFCFlag, INT8U u8_fBlockSize, INT8U u8_fSTmin);

/* ISotp Tx Handler */
extern void ISO15765_TxHandler(INT32U u32_fCANid);

#endif

/**************************************************************************************************/
/* End of  ISO15765_2.h                                                                           */
/**************************************************************************************************/
