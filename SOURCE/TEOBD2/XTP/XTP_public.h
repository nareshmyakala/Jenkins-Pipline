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
/* \File Name   : XTCOM.h                                                                         */
/* \Author      : SRIKANTH                                                                        */
/* \Version 	:                                                                                 */
/* \Date        : 08-12-2016                                                                      */
/*                                                                                                */
/* @Description :                                                                                 */
/**************************************************************************************************/

#ifndef _XTCOM_H_
#define _XTCOM_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "ISO15765_2.h"
#include "TEOBD2_public.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

#define XTCOM_RESP_BUFFER_LENGTH                  ( 8300 )
#define XTCOM_REQ_BUFFER_LENGTH                   ( 8300 )
#define TIMEOUT_FACTOR                            ( 40  )      

/* To Hold HAL Result  */
typedef enum
{
    XTCOM_SUCCESS = 0x00,
    XTCOM_ERROR
        
}EN_XTCOM_RESULT_t;

/* Enum for Command Type */
typedef enum 
{
    CMD_AT = 0x00,
    CMD_ST,
    CMD_XT,
    CMD_ERROR
        
}EN_CMD_TYPE_t;

/* Structure for EEPROM Data */
typedef struct
{	
    /* Serial Number */
    INT8U u8_mSerialNumber[15];
    
    /* Firmware Version */
    INT8U u8_mFirmwareVersion[13];
    
    /* BaudRate */
    INT32U u32_mBaudrate;
    
    /* Initialization Date */
    INT8U u8_mInitDate[12];
    
    /* Current Protocol */
    INT8U u8_mCurProtocol;
    
    /* POR Count */
    INT8U u8_mPORCount;
    
    /* POR Time */
    INT16U u16_mPORTime;
    
    /* Total Runtime */
    INT16U u16_mRuntime;
    
    /* Engine Crank */
    INT8U u8_mEngineCrank;
    
    /* Engine Status */
    INT8U u8_mEngineStatus;
    
    /* Device ID String */
    INT8U au8_mDeviceIdString[17];
    
    /* Save Data String */
    INT8U u8_mNVM_SD_Data;
    
}ST_SYS_CONFIG_DATA_t;


/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/* */
extern volatile INT8U u8_gXtComReqFlag;

/* */
extern volatile INT16U u16_gXtComReqLength;

/* */
extern volatile INT16U u16_gXtComReqIndex;

/* */
//extern INT8U au8_gXtComReqBackupBuffer[XTCOM_RESP_BUFFER_LENGTH];

/* */
//extern INT8U TeObd2_RxBuffer[XTCOM_REQ_BUFFER_LENGTH] ;

/* Constatnt Variable Which Holds The Firmware Version Info */
extern const INT8U au8_gIctVersionString[]; 

/* Constant Variable Which Holds Error Prompt */
extern const INT8U au8_gIctErrorString[];

/* Constant Variable Which Holds Success Prompt */
extern const INT8U au8_gIctSuccessString[];

/* variable Fore to Send Srachninf String */
extern  const INT8U au8_gIctSearchng[];

/* */
extern INT8U u8_gEchoFlagStatus;

/* */
extern INT8U u8_gRepeatFlag;

/* Variable to Hold Space Flag */
extern INT8U u8_gIctSpaceFlag;

/* Variable to Hold Response Flag */
extern INT8U u8_gResponseFlag;

/* Variable to Hold Header Flag */
extern INT8U u8_gHeaderFlag;

/* Variable to Hold Linefeed Flag */
extern INT8U u8_gLineFeedFlag;

/* Variable to Hold CAN Bus Monitor Status */
extern INT8U u8_gCanBusMonitorStaus ;
extern INT8U u8_gCanBusMonitorHeadrs;

/* Variable to Hold Tx Header ID */
extern INT32U u32_gTxHeaderId;

/* Variable to Hold Rx Header ID */
extern INT32U u32_gRxHeaderId;

/* Variable to Hold Tx Header ID */
extern INT32U u32_gTxHeaderBackUp;

/* Variable to Hold Rx Header ID */
extern INT32U u32_gRxHeaderBackUp;

/* Variable to Hold the DLC Flag */
extern INT8U u8_gDLCFlag;

/* */
extern ST_SYS_CONFIG_DATA_t st_gChipConfigData;

/* */
extern INT8U u8_gExtendAdd; 

/* */
extern INT16U u16_gTimeoutTime;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* */
extern void XTCOM_RxHandler(INT8U u8_fData);

/* */
extern EN_XTCOM_RESULT_t XTP_ConfigureBaudrate(INT32U u32_fBaudRate);                         

/* */
extern void XTP_ResetRxBuffer(void);

/* */
extern EN_XTCOM_RESULT_t XTP_ProcessBuffer(const INT8U *p_fSrc , INT16U u16_fLength);

/* */
extern void CAN_DISPLAY(INT32U  u32_gISOTP_CANid, const INT8U *p_fData , INT32U u132_fLength);

/* */
extern void CAN_DISPLAY_XTMA(INT32U u32_fCANID, const INT8U *p_fData , INT32U u132_fLength);

/* */
extern EN_XTCOM_RESULT_t XTP_CheckForDataFrame( const INT8U *p_fSrc,  INT16U *p_fLength);

/* */
extern void TEOBDII_STACK_WriteDefaultConfigData(void);

/* */
extern void TEOBDII_STACK_GetConfigData(void);

/* */
extern void TEOBDII_STACK_WriteConfigData(void);

/* */
extern EN_STACK_MGR_STATES_LIST_t GetCurrentProtocol(void);

#endif

/**************************************************************************************************/
/* End of XTCOM.h                                                                                 */
/**************************************************************************************************/

