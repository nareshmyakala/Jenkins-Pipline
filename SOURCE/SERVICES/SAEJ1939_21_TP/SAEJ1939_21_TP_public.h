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
/* \File Name   : SAEJ1939_21_TP_public.h                                                         */
/* \Author      : A.Prashanth                                                                     */
/* \Version 	:                                                                                 */
/* \Date        : 16-11-2017                                                                      */
/*                                                                                                */
/* @Description : SAEJ1939_21 TP frame work                                                       */
/**************************************************************************************************/

#ifndef _SAEJ1939_21_TP_PUBLIC_H_
#define _SAEJ1939_21_TP_PUBLIC_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "ISO15765_2.h"
#include "TEOBD2_public.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

#define J1939_DEFAULT_CTS_HEADER    0x1CEC00F9
#define J1939_DEFAULT_RTS_HEADER    0x1CECFFF9

#define J1939_DEFAULT_DATA_HEADER   0x1CEBFFF9

#define J1939_DEFAULT_NM_HEADER     0x1893FFF9

/* J1939 Default Priorities */

#define J1939_CONTROL_PRIORITY			0x03
#define J1939_INFO_PRIORITY			    0x06
#define J1939_PROPRIETARY_PRIORITY		0x06
#define J1939_REQUEST_PRIORITY			0x06
#define J1939_ACK_PRIORITY			    0x06
#define J1939_TP_CM_PRIORITY			0x07
#define J1939_TP_DT_PRIORITY			0x07


/* J1939 Defined Addresses  */

#define J1939_GLOBAL_ADDRESS			0xFF
#define J1939_NULL_ADDRESS			    0xFE
#define J1939_SOURCE_ADDRESS            0xF9 

/* J1939 MultiPacket Address */

#define J1939_BAM_CM_PACKET			    0xEC
#define J1939_DATA_PACKET			    0xEB
#define J1939_ACK_NACK_PACKET           0xE8
#define J1939_CM_ACK_PACKET			    0x13
/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

extern INT8U au8_gSorceAdress[5];
extern INT8U u8_gSorceAdressIndx;

extern INT8U u8_gGlobalRespReq ;

extern INT8U u8_gCM_BAM_Flag;

extern INT32U u32_gJ1939RTSHeader;

/* Global variable for Monitor PF */
extern INT8U u8_gJ1939_MPF;

/* Global variable for Monitor PS */
extern INT8U u8_gJ1939_MPS;

/* */
extern INT8U u8_gMntrPGN_N_timesFlag;

extern INT8U u8_gMntrPGN_N_Frames;

extern INT8U u8_gSAEJ1939MtntlAllPGN;

extern INT8U u8_gJ1939SnglPGNMntr;

extern INT8U u8_J1939_ExptPkts;

extern INT8U u8_gRcvdPkts;

extern INT8U u8_gJ1939RqstSent;

extern INT8U u8_gJ1939MultiRqst;

extern INT8U volatile u8_gJ1939_PF;

extern INT8U volatile u8_gJ1939_PS;

extern INT32U u32_gJ1939Header ;
extern INT32U u32_gNMheader;

extern INT8U u8_J1939RxTimeOutFlag;
extern INT32U u32_gJ1939RxMonitrTimeOutFlag;
extern INT32U u32_gJ1939RxMonitrTimeOutCntr;

extern INT8U  u8_gJ1939IsRxRcvd;

extern INT32U u32_gJ1939RxTimeOutCnt;
extern INT8U u8_gTP_PGN[3];

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* */
extern void J1939_RxMsgHandler(void * p_fRxData);

/* */
extern void J1939_TxConformation(INT32U u32_fMBnumber);

/* */
extern void J1939_DISPLAY(ST_ISOTP_DATA_t * p_fCanDispData);

extern void J1939_SendTP_Data(INT8U *au8_lPayloadBuff , INT16U u16_lPayloadLen);

/* */
extern void J1939_Timer(void);

#endif

/**************************************************************************************************/
/* End of ISOTP15765_public.h                                                                     */
/**************************************************************************************************/
