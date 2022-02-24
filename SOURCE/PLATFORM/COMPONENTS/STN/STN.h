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
/*  File Name   : STN.h                                                                           */
/*  Author      : Srikanth L                                                                      */
/*  Version 	: V1.0                                                                            */
/*  Date        : 24-09-2018                                                                      */
/*                                                                                                */
/* @Description : STN Interface frame work                                                        */
/**************************************************************************************************/

#ifndef _STN_H_
#define _STN_H_

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

/* Enum for STN Status */
typedef enum
{
	STN_FAIL,
	STN_SUCCESS
	
}EN_STN_STATUS_t;

/* to STN Handle Responce */
typedef enum
{
    STN_PROMPT,
    STN_FLASHING,
    STN_NO_RECEIVE
}EN_STN_HANDLE_RESP_t;

/* Enum for STN IOCTRLs */
typedef enum
{
	STN_IOCTRL_RESET_FIFO,
	STN_IOCTRL_GET_FIFO_REF,
	STN_CALL_BACK_REGISTER,
	STN_IOCTRL_CHANGE_SELF_BAUD,
	STN_IOCTRL_CHANGE_STN_BAUD,
    STN_IOCTRL_GET_STN_S_NO,
    STN_SET_RESTYPE,
    STN_ENTER_BOOTLOADER,
    STN_CAN_CHECK,
    STN_KLINE_CHECK
	
}EN_STN_IOCTRL_ID_t;

/* Structure to Configure STN */
typedef struct
{
	INT32U u32_mBaudRate;
	void (*pf_mStnCallBack)(INT32U u32_fDataLen);
	
}ST_STN_INIT_t;

typedef enum
{
  DISABLE = 0x00,
  ENABLE
  
}STN_STB_CNTRL_t;

/* */
extern EN_STN_HANDLE_RESP_t en_gStnRespType;

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function to Init the STN */
extern void STN_Init(ST_STN_INIT_t *pst_gStnConfig);

/* Function to Write data to STN */
extern void STN_WriteData(INT8U *pu8_fData, INT32U u32_fLength);

/* Function to Read data form STN */
extern void STN_ReadData(INT8U *pu8_fData, INT32U u32_lLength);

/* Function to Controll STN */
extern EN_STN_STATUS_t STN_Ioctrl(EN_STN_IOCTRL_ID_t en_fID, void *p_fInData, INT32U u32_fInDataLen, \
													  void *p_fOutData, INT32U *pu32_fOutDataLen);

/* STN 1ms Handler to manage Delays */
extern void STN_1MsHandler(void);

extern void STN_STBCntrl(STN_STB_CNTRL_t en_mSTB_Cntrl);

extern void STN_Reset(void);

#endif

/**************************************************************************************************/
/* End of  STN.h                                                                                  */
/**************************************************************************************************/
