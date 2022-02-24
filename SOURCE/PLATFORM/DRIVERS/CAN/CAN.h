/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2017, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : CAN.h                                                                           */
/* \Author      : Yashwanth                                                                       */
/* \Version 	: v1.0                                                                            */
/* \Date        : 02-01-2018                                                                      */
/*                                                                                                */
/* @Description : CAN Driver Framework                                                            */
/**************************************************************************************************/

#ifndef _CAN_PUBLIC_H_
#define _CAN_PUBLIC_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "includes.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

/* Enum for CAN Results */
typedef enum
{
    CAN_FAILURE = 0x00,
    CAN_SUCCESS,
}EN_CAN_STATUS_t;

typedef enum
{
    CAN_DISABLE_MSG_BUFF = 0x00,
    CAN_ENABLE_MSG_BUFF,
}EN_CAN_MSG_BUFF_CTRL_t;

/* Enum for CAN Channels */
typedef enum
{
    CAN0 = 0x00,
    CAN1,
    MAX_CAN,
}EN_CAN_CH_t;

typedef enum
{
    CAN_RXFIFO_0 = 0x0,
    CAN_RXFIFO_1,
}EN_CAN_RXFIFO_SEL_t;

typedef enum
{
    CAN_STD_ID = 0x00,
    CAN_EXTENDED_ID,
}EN_CAN_ID_TYPE;
    
typedef enum
{
    CAN_DATA_FRAME = 0x00,
    CAN_REMOTE_FRAME,
}EN_CAN_FRAME_TYPE_t;

/* CAN Message Buffer(MB) Type*/
typedef enum
{
    CAN_MB_TRANSMIT = 0,
    CAN_MB_RECEIVE

}EN_CAN_MB_TYPE_t;

/* CAN Data Field Size */
typedef enum
{
    CAN_8_BYTE_DATA  = 8,
    CAN_12_BYTE_DATA = 12,
    CAN_16_BYTE_DATA = 16,
    CAN_20_BYTE_DATA = 20,
    CAN_24_BYTE_DATA = 24,
    CAN_32_BYTE_DATA = 32,
    CAN_48_BYTE_DATA = 48,    
    CAN_64_BYTE_DATA = 64,    
}EN_CAN_DATA_SIZE_t;

/* CAN Standard Baudrates */
typedef enum
{
    CAN_250_KBPS = 0x00,
    CAN_500_KBPS,
    CAN_1_MBPS
}EN_CAN_BAUDRATE_t;

/* CAN FD Enable or Disable Optionis */
typedef enum
{
    CAN_FD_DISABLE = 0x00,
    CAN_FD_ENABLE,
}EN_CAN_FD_SEL_t;

/* User Configuration Structure */
typedef struct
{
    EN_CAN_CH_t        en_mCANCh;
    EN_CAN_BAUDRATE_t  en_mBaudRate;
    EN_CAN_FD_SEL_t    en_mCANFdEnRDis;
    EN_CAN_DATA_SIZE_t en_mDataFieldSize;
    void (* fp_TxHandler)(INT32U );
    void (* fp_RxHandler)(void * );
    void (* fp_BusOffHandler)(void);
    void (* fp_ErrorHandler)(void);
}ST_CAN_CONFIG_PARAMS_t;


/* User Message Buffer Configuration Structure */
typedef struct
{
    EN_CAN_CH_t            en_mCANCh;
    EN_CAN_ID_TYPE         en_mIdType;
    INT8U                   u8_mMsgBuffNo;
    INT32U                  u32_mCANId;
    INT32U                  u32_mAcceptMsk;
    INT8U                   u8_mDlc;
    INT8U                   au8_mData[8];
    EN_CAN_MB_TYPE_t       en_MsgBuffType;
}ST_CAN_MB_CONFIG_PARAMS_t;

/* */
typedef struct 
{
    INT32U u32_mCAN_ID;
    INT8U au8_mMCanData[8];
    INT8U u8_mMcanDlc;
}ST_CAN_DATA_t;

typedef enum
{
   IOCTRL_FAIL = 0x00,
   IOCTRL_SUCCESS
    
}EN_IOCTRL_STATUS_t;

typedef enum
{
    CAN_BAUDRTAE_CHNAGE = 0x00,
    CAN_ID_CHNAGE,
    CAN_IDTYPE_CHNAGE
  
}EN_CAN_IOCTRLI_ID_t;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function to Initialize the CAN  */
extern EN_CAN_STATUS_t CAN_Init(ST_CAN_CONFIG_PARAMS_t * p_stfCANConfigParmas);

/* Function to Configure Rx Message Buffer */
extern EN_CAN_STATUS_t CAN_ConfigTxMsgBuff(ST_CAN_MB_CONFIG_PARAMS_t * p_stfMBConfigParams);

/* Function to Configure Message Buffer Data */
extern EN_CAN_STATUS_t CAN_ConfigMsgBuffData(ST_CAN_MB_CONFIG_PARAMS_t * p_stfMBConfigParams);

/* Function to Configure Rx Message Buffer */
extern EN_CAN_STATUS_t CAN_ConfigRxMsgBuff(ST_CAN_MB_CONFIG_PARAMS_t * p_stfMBConfigParams);

/* Function to transmit Data Buffer */
extern EN_CAN_STATUS_t CAN_TransmitDataBuffer(EN_CAN_CH_t en_fCANCh, INT8U u8_fMsgBuffer);

/* Function to Read CAN Messages */
extern EN_CAN_STATUS_t CAN_ReadMessageBuffer(ST_CAN_MB_CONFIG_PARAMS_t * p_stfMBConfigParams, 
                              INT16U u16_fRxBuffElmnts, INT32U ** p_fRxBuffAddr, INT8U u8_fRxBuff);

/* Function to Check New data Received or not */
extern INT8U CAN_CheckReceiveFlag(EN_CAN_CH_t en_fCANCh, INT8U u8_fMsgBuffNo);

/* Function to Read CAN Data from RXFIFOs */
extern INT32U CAN_ReadReceiveFifoData(ST_CAN_MB_CONFIG_PARAMS_t * p_stfMBConfigParams,
                                                                        INT32U * p_fFifoAddr);

/* Function to Configure RAM Message Buffers */
extern EN_CAN_STATUS_t CAN_ConfigRAMBuffers(EN_CAN_CH_t en_fCANCh);

/* Function to Configure CAN Data Field Size */
extern EN_CAN_STATUS_t CAN_ConfigDataField(EN_CAN_CH_t en_fCANCh, 
                                                        EN_CAN_DATA_SIZE_t en_fDataSize);
/* Function to deinitialize the CAN */
extern EN_CAN_STATUS_t CAN_DeInit(EN_CAN_CH_t en_fCANCh);

/* Function to Keep CAN in Sleep Mode */
extern EN_CAN_STATUS_t CAN_Sleep(EN_CAN_CH_t en_fCANCh);

/* Function to Wakeup the CAN channel from Sleep */
extern EN_CAN_STATUS_t CAN_Wakeup(EN_CAN_CH_t en_fCANCh);

/* Function to Enable or Disable Rx Message Buffers */
extern EN_CAN_STATUS_t CAN_EnDisMsgBuff(EN_CAN_CH_t en_fCANCh, EN_CAN_ID_TYPE en_fIdType,
                                  INT8U u8_fRxMsgBuffNo, EN_CAN_MSG_BUFF_CTRL_t en_fMBCtrl);

/* Function to Change CAN Buadrate */
extern EN_CAN_STATUS_t CAN_ChangeBaudRate(EN_CAN_CH_t en_fCANCh,
                                                            EN_CAN_BAUDRATE_t en_fBuadrate);

/* Initialize the CAN Section */
extern EN_IOCTRL_STATUS_t CAN_Ioctrl(EN_CAN_IOCTRLI_ID_t en_Ioctrl_ID, EN_CAN_CH_t en_CAN_Chnl , \
                                            INT32U en_fArbitrtnID, EN_CAN_BAUDRATE_t en_fBaudrtae , \
                                                       EN_CAN_ID_TYPE en_fIDType,INT8U u8_fMONumber);

#endif

/**************************************************************************************************/
/* End of CAN.h                                                                              */
/**************************************************************************************************/
