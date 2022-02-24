/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2016, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/*  File Name   : CAN_IF.h                                                                        */
/*  Author      : Ravi Ranjan Kumar                                                               */
/*  Version 	: 1.0                                                                             */
/*  Date        : 27/04/2018                                                                      */
/*                                                                                                */
/* @Description : CAN Interface                                                                   */
/**************************************************************************************************/

#ifndef _CANIF_H_
#define _CANIF_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "GPIO.h"
#include "CAN.h"

/**************************************************************************************************/
/* Private Global Definitions Section                                                             */
/**************************************************************************************************/

typedef enum
{
   CAN_MO_TRANSMIT = 0,
   CAN_MO_RECEIVE
     
}CANMOTYPE_t;

typedef enum
{
   STB_DISABLE = 0,
   STB_ENABLE  
}TE_STB_CNTRL_t;

typedef enum
{
    CAN_IF_OK = 0x00,
    CAN_IF_ERROR
      
}EN_CAN_IF_RESULT_t;

/* */
typedef enum
{
  CAN_OFFLINE,
  CAN_ONLINE,
}EN_CAN_STATE_t;

/* CAN Tx Rx Mode */
typedef enum
{
  CAN_TXOFF,
  CAN_TXON,
  CAN_RXOFF,
  CAN_RXON,
}EN_CAN_TRANS_MODE_t;


typedef enum
{
    CAN_IF_CH_0 = 0x00,
    CAN_IF_CH_1,
    MAX_CAN_IF,
}EN_CAN_IF_CH_t;

/* Acceptance Mask Bit for Message IDE Bit */
typedef enum
{
	CAN_RECEIVE_ALL = 0x00,
	CAN_RECEIVE_MATCH_IDE,
}EN_CAN_RX_ACC_MASK_t;

/* ENUM for CAN FRAME Type */
typedef enum
{
    EN_MAILBOX_TRANSMIT = 0x00,
    EN_MAILBOX_RECEIVE  
}EN_MAILBOX_DIR_t;

/* ENUM for CAN FRAME Type */
typedef enum
{
	CAN_IF_250KBPS = 0,
	CAN_IF_500KBPS
}EN_CAN_IF_BAUDRATE_t;

/* enum to select the functional states   */
typedef enum
{
	CAN_DISABLE = 0,
	CAN_ENABLE
}EN_CAN_FUN_STATE_t;

typedef struct
{
    void (* fp_IsoTpTxHandler)(INT32U); 
    void (* fp_IsoTpRxHandler)(void * pv_fRxData);
    INT32U u32_mIsoTpReqId;
    INT32U u32_mIsoTpRespId;  
}ST_ISOTP_PARAMS_t;

/* Rx Ipdu Data */
typedef struct 
{
    INT32U u32_mArbitrationId;              /* */
    INT8U  au8_mDataBuff[8];                /* */
    INT8U  u8_mDataSize;                    /* */
}ST_RX_IPDU_DATA_t;

typedef enum
{
  MO_CONFIGURE = 0x00,
  
}EN_IOCTRL_ID_t;

/* MO Configuration */
typedef struct
{
    EN_CAN_CH_t          en_mCanCh;           /* */
    INT8U                u8_mCanMOIndex;      /* */
    INT32U               u32_mCanMsgId;       /* */
    INT32U               u32_mAcceptMask;     /* */
    INT8U                u8_mDLC;             /* */
    EN_CAN_ID_TYPE      en_mCanIdType;       /* */
    EN_CAN_MB_TYPE_t     en_mMOType;          /* */
    EN_CAN_BAUDRATE_t en_mCanIfBaudRate;   /* */
    INT8U                u8_mEOL;             /* */
    void (* fp_CanIfTxHandler)(INT32U u32_fArbitrationID);
    void (* fp_CanIfRxHandler)(void * );
    void (* fp_CanIfBusOffHandler)(void);
    void (* fp_CanIfErrorHandler)(void);
}ST_CAN_MO_CFG_t; 

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

extern ST_GPIO_PARAMS_t st_gCANStbPinConfig;

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

/* Initialize the CAN Section */
extern EN_CAN_IF_RESULT_t CAN_IF_Init(ST_CAN_MO_CFG_t * p_stfMailBoxConfig);

/* */
extern EN_CAN_IF_RESULT_t CAN_IF_Ioctrl(EN_IOCTRL_ID_t en_fIoctrlID,EN_CAN_CH_t en_CANChnl, \
                        INT8U u8_fMONumber , INT32U u32_fAccceptnceMask ,EN_CAN_ID_TYPE en_fIDType,\
                                                    EN_CAN_MB_TYPE_t en_fMOType ,INT32U u32_fCANID);

/* */
extern EN_CAN_IF_RESULT_t CAN_IF_WriteMsg(EN_CAN_IF_CH_t en_fCANCh, INT8U u8_fMONumber, \
                                                 INT32U u32_gCanID, INT8U * u8_fPtr, INT8U u8_fDLC);

/* */
extern EN_CAN_IF_RESULT_t CAN_IF_InitIsoTp(ST_ISOTP_PARAMS_t * p_stfIsoTpInitData); 


/**/
extern EN_CAN_IF_RESULT_t CAN_IF_StopComm(void);

/* */
extern INT8U CAN_IF_GetMailBoxID(INT32U u32_fCanMsgID);

/**/
extern EN_CAN_IF_RESULT_t CAN_IF_Sleep(EN_CAN_IF_CH_t en_fCANCh);

/* */
extern EN_CAN_IF_RESULT_t CAN_IF_SutdownComm(EN_CAN_IF_CH_t en_mCANCh);

/**/
extern EN_CAN_IF_RESULT_t CAN_IF_Awake(EN_CAN_IF_CH_t en_mCANCh);

/*  */
extern EN_CAN_IF_RESULT_t CAN_IF_ChangeBuadrate(EN_CAN_IF_CH_t en_mCANCh,
                                                                EN_CAN_IF_BAUDRATE_t en_fBaudrate);


/* */
extern void CAN_RxHandler(void * p_fCANData);

extern void CAN_BusOffHandler(void);

extern void CAN_ErrorHandler(void);

extern  void CAN_TxHandler(INT32U u32_fCanID);

extern void TE_StackSTB_Cntrl(TE_STB_CNTRL_t en_mIntrpt);

#endif

/**************************************************************************************************/
/* End of CanIf_Priv.h                      			                                          */
/**************************************************************************************************/
