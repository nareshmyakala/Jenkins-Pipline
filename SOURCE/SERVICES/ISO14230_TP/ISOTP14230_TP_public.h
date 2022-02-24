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
/* \File Name   : ISOTP14230_TP.h                                                                 */
/* \Author      : PRASHANTH.A                                                                     */
/* \Version 	:                                                                                 */
/* \Date        : 18-10-2017                                                                      */
/*                                                                                                */
/* @Description : ISO14230 Frame Work                                                             */
/**************************************************************************************************/

#ifndef _ISOTP14230_TP_H_
#define _ISOTP14230_TP_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

#define KLINE_MAX_BUFF_LENGTH           ( 512 )
#define KLINE_MAX_RQST_LENGTH           ( 256 )
#define KLINE_P2_DEFAULT                ( 100 )
#define KLINE_P3_DEFAULT                ( 3000 )
#define KLINE_P4_DEFAULT                ( 5 )
#define KLINE_DAFAULT_FMT_BYTE          ( (INT8U)0xC1 ) 
#define KLINE_DAFAULT_TAR_BYTE          ( (INT8U)0x33 )
#define KLINE_DAFAULT_SRC_BYTE          ( (INT8U)0xF1 )
#define KLINE_NODATA_TIMEOUT_FACTOR     ( 351 )
/* */
typedef enum
{
    ISO14230_SUCCESS = 0x00,
    ISO14230_ERROR
      
}ISO14230_RESULT_t;

/* KLine Timing Parameters */
typedef struct
{
    INT8U u8_mP2min;
    INT32U u32_mP2max;
    INT8U u8_mP3min;
    INT32U u32_mP3max;
    INT8U u8_mP4min;
    
}ST_KLINE_TIMING_PARAMS_t;

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/* */
extern INT8U au8_gKLineTxBuffer[KLINE_MAX_BUFF_LENGTH];
extern volatile INT8U u8_gKlineInitSeqFlag;
extern volatile INT8U u8_gKLineRxFlag;
extern INT8U au8_gKLineRqstData[KLINE_MAX_RQST_LENGTH];
extern INT8U au8_gKLineRespBuf[KLINE_MAX_BUFF_LENGTH];
extern INT8U au8_gKLineReqBackupBuf[KLINE_MAX_BUFF_LENGTH];
extern INT8U au8_gKLineTrasBufferp[KLINE_MAX_BUFF_LENGTH];
extern INT16U u16_gKLineReqLength;

/* Set KLiine Default Header */
extern INT8U u8_gKlineFmtByte;
extern INT8U u8_gKlineTarByte;
extern INT8U u8_gKlineSrcByte;
extern INT8U u8_gKeyByte1;
extern INT8U u8_gKeyByte2;

extern INT8U u8_gKlineLegntByte;

extern INT8U u8_gKLineBusy;
extern INT32U u32_gKline_P2;
extern INT32U u32_gKline_P3;
extern INT8U u8_gKline_P4;

extern volatile INT32U u32_gKLineTesterCounter;
extern volatile INT8U u8_gTesterInProgress;
extern const INT8U au8_gTesterPresent[4];

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* */
extern ISO14230_RESULT_t ISO14230_Init(void);

extern void ISO14230_RxHandler(INT8U u8_fRxData);
/* */
extern ISO14230_RESULT_t ISO14230_FastInit(void);
extern ISO14230_RESULT_t ISO14230_5BaudInit(void);

/* */
extern ISO14230_RESULT_t ISO14230_PreparePacketAndWrite(INT8U * p_fInputBuff, INT16U u16_fInputLength);

/* */
extern void ISO14230_ResetKLineBuffers(void);

/* */
extern ISO14230_RESULT_t ISO14230_KLineWrite(INT8U * p_fData, INT16U u16_fLength);

/* */
extern void ISO14230_KLineProcessRxData(void);

/* */
extern void ISO14230_Delay(INT32U u32_fDelay);

/* */
extern void ISO14230_DeInit(void);

#endif

/**************************************************************************************************/
/* End of ISOTP14230_TP.h                                                                         */
/**************************************************************************************************/

