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
/* \File Name   : TEOBD2_public.h                                                                 */
/* \Author      : L.SRIKANTH                                                                      */
/* \Version 	:                                                                                 */
/* \Date        : 17-10-2017                                                                      */
/*                                                                                                */
/* @Description :                                                                                 */
/**************************************************************************************************/

#ifndef _TEOBD2_PUBLIC_H_
#define _TEOBD2_PUBLIC_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "NVMCTRL.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

/* enum for TEOBD ERROR Code */
typedef enum
{
    TEOBD2_SUCCESS = 0,
    TEOBD2_FAILE = 1
        
}TEOBD2_ErrCodes_t;

/* Enum to Hold Result */
typedef enum
{
    STACK_ERROR = 0,
    STACK_SUCCESS,	
}EN_STACK_RESULT_t;

/* OBD States List */
typedef enum
{
    IS014230_FAST,
    IS015765_CAN_11_500,
    IS015765_CAN_29_500,
    IS015765_CAN_11_250,
    IS015765_CAN_29_250,
    SAE_J1939_29_250      
}EN_STACK_MGR_STATES_LIST_t;

/* FSM State Definition */
typedef struct
{
    EN_STACK_RESULT_t (* Init)(EN_STACK_MGR_STATES_LIST_t *, INT32U u32_gTickCount);
    EN_STACK_RESULT_t (* Handler)(EN_STACK_MGR_STATES_LIST_t *, INT32U u32_gTickCount);
    EN_STACK_RESULT_t (* Exit)(EN_STACK_MGR_STATES_LIST_t *, INT32U u32_gTickCount);
    EN_STACK_RESULT_t ( *WriteData)(void * p_fWriteBuffer, INT16U u16_fLenght);
    INT8U ( *ReadData)(INT8U * p_fReadBuffer);
    EN_STACK_RESULT_t ( *WaitForResp)(void);
    
}ST_OBDII_STATES_t;


/* ENUM for CAN ID Type */
typedef enum
{
    OBD_CAN_STANDARD_ID = 0,
    OBD_CAN_EXTENDED_ID

}EN_OBD_CAN_IDTYPE_t;


/*ENUM FOR BAUD RATE */
typedef enum
{
    OBD_CAN_MO_RX = 0x00,
    OBD_CAN_MO_TX
    
}EN_OBD_CAN_MOTYPE_t;

/*ENUM FOR BAUD RATE */
typedef enum
{
    OBD_CAN_250KBPS = 0x00,
    OBD_CAN_500KBPS
    
}EN_OBD_CAN_BAUDRATE_t;

typedef struct 
{  
    EN_OBD_CAN_IDTYPE_t en_fCanIdType;
    EN_OBD_CAN_BAUDRATE_t en_fCanBaudRate;
    void (* fpCan_RxIndication)(void *);
    void (* fpCan_TxConfirmation)(INT32U);
    void (* fpCan_ErrorHandler)(void);
    void (* fpCan_BussOffHandler)(void);
}OBDCanObj_t;

/* */
typedef struct
{
    /* Can Funtion Pointers*/
    void (* CAN_Init)(void *p_fCanInit);
    EN_STACK_RESULT_t (* CAN_TxMsg)(INT32U u32_fCanId, INT8U * p_fCanData, INT8U u8_fDlc);    
    EN_STACK_RESULT_t (* CAN_ConfigMO)(INT32U canId_u32, INT8U moNumber_u8, EN_OBD_CAN_IDTYPE_t en_fIdType, \
                                                EN_OBD_CAN_MOTYPE_t en_CanMOType, INT32U u32_fCanMoMask);
    
    /* Kline Funtion Pointers*/
    void (* KLine_ConfigUART)(void);  
    void (* KLine_ConfigGpio)(void);
    void (* KLine_Init)(void (*RxIndication)(INT8U u8_fData));
    void (* KLine_Set)(void);
    void (* KLine_Reset)(void);   
    void (* KLine_TransmitChar)(INT8U u8_fData);   
    void (* KLine_DeInit)(void);
    
    /* Nvm Funtion Pointes*/  
    void (* NVM_Init)(void);   
    EN_STACK_RESULT_t (* NVM_Read)(INT32U u32_fAddr, INT8U * p_fSrcBuff, INT16U u16_fLen);  
    EN_STACK_RESULT_t (* NVM_Write)(INT32U u32_fAddr, INT8U * p_fSrcBuff, INT16U u16_fLen);
    
    /* Timer Funtion Pointers*/   
    void (* TimerInit)(INT32U u32_fDelay, void (*fp_fTimerHandler)(void));
    void (* TimerDeInit)(void);
    
    void (* ADC_Init)(void);
     
    /* Hal Reset */
    void (* ResetDevice)(void);
    
}HalObject_t;

#define INTERNAL_EEPROM_START_ADD                               (0x14000300u)

/* Stack Related Locations */
#define EEPROM_XTCOM_BOOT_STATUS_ADD                            ( INTERNAL_EEPROM_START_ADD )
#define DATARATE_BASE_ADDR                                      ( EEPROM_XTCOM_BOOT_STATUS_ADD + 1 )
#define SYS_CONFIG_DATA_BASE_ADDR                               ( DATARATE_BASE_ADDR + 6 )
#define PP_BASE_ADDR                                            ( SYS_CONFIG_DATA_BASE_ADDR + 72 )

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

extern TEOBD2_ErrCodes_t (* p_gXT_ReqComplete)(INT8U * p_fData, INT32U u32_fLen);

extern ST_OBDII_STATES_t * p_stgOBDIIStates;

extern EN_STACK_MGR_STATES_LIST_t en_gOBDII_State;
extern EN_STACK_MGR_STATES_LIST_t en_gOBDII_Prevstate;

extern HalObject_t st_gHalObject;

extern HalObject_t * pst_gHalObjectPtr;

extern INT32U u32_gPrevDataRate;
extern INT32U u32_gCurrentDataRate;

/* */
extern INT8U u8_gAutoPrtcl;

/* */
extern INT8U u8_gAutprtclDtaFlag;

extern INT8U u8_gErrorSuccesFlag;

/* Timeout Variables */
extern INT32U u32_gTEOBD2TimeoutCounter;
extern INT8U u8_gTEOBD2TimeoutFlag;
extern INT8U u8_gTEOBD2ReqstSentFlag;
extern INT32U u32_gTimeout;
/* */
extern INT8U  *pu8_gISOTPDataRcvPntr;
extern INT32U u32_gISOTPdLength;
extern INT32U u32_gISOTP_CANid;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* */
extern void XTP_Init(TEOBD2_ErrCodes_t (* p_fXT_ReqCompleat)(INT8U * p_fData, INT32U u32_fLen));

/* */
extern void XTP_UpdateCallBack(TEOBD2_ErrCodes_t (* p_fXT_ReqComplete)(INT8U * p_fData, \
                                                                                  INT32U u32_fLen));
/* */
extern void XTP_SendRequest(INT8U *p_fData, INT32U u32_fLength);

/* */
extern void TEOBD2_StackHandler(void);

/* */
extern void ISOTP_DataReceived(INT32U u32_fCANid , INT8U *pu8_fData , INT32U u32_fLngth);

extern void ISOTO_ErrorType(INT8U u8_lError);

extern void TEOBD2_1MSHandler(void);

#endif
/**************************************************************************************************/
/* End of XTCOM.h                                                                                 */
/**************************************************************************************************/
