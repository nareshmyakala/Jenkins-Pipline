/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2014-15, Think Embedded Pvt. Ltd. (TEPL)                     */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : Common1.h                                                                       */
/* \Author      : Santhosh dixith.Y                                                               */
/* \Version 	: iCONNECT V1                                                                     */
/* \Date        : 01/05/2015  			                                                          */
/* @Description : Gpio  Driver Framework                                                          */
/**************************************************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User defined Header Files Section                                                              */
/**************************************************************************************************/

#include "Includes.h"

/**************************************************************************************************/
/* Export Definitions Section                                                                     */
/**************************************************************************************************/

/* Enumeration List for Application */
typedef enum
{
    APP_ERROR = -1,
    APP_SUCCESS,
    APP_UNKNOWN_EVENT,
    APP_NO_MEM_AVAIL

}EN_APP_RESULT_t;

typedef enum
{
	COMMON_ERROR = -1,
	COMMON_OK
	
}EN_COMMON_RESULT_t;

/**************************************************************************************************/
/* Export Variables Section                                                                       */
/**************************************************************************************************/

extern UINT8 u8_gDecimalPosition;

/* */
typedef enum
{
    NAK = 0x00,
    ACKW     
}EN_RESULT_TYPE_t;

/* */
typedef struct
{
    INT8U au8_mPayload[1024];
    INT16U u16_mSeqNumber;
    INT16U u16_mChecksum;
    INT32U u32_mDataLength;
    INT8U u8_mResult;
    
}ST_FOTA_PACKET_t;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* */
void COMMON_ResultPackData(INT16U u16_fSeqNumber, EN_RESULT_TYPE_t en_fResult, INT8U *Output);

/* Function that convert Byte to PAN */
extern EN_COMMON_RESULT_t COMMON_Byte2PAN(INT8U * p_fDstBuffer, INT8U u8_fInput);

/* Function that convert HWord to PAN */
extern EN_COMMON_RESULT_t COMMON_HWord2PAN(INT8U * p_fDstBuffer, INT16U u16_fInput);

/* Function that convert Word to PAN */
extern EN_COMMON_RESULT_t COMMON_Word2PAN(INT8U * p_fDstBuffer, INT32U u32_fInput);

/* Function that convert DWord to PAN */
extern EN_COMMON_RESULT_t COMMON_DWord2PAN(INT8U * p_fDstBuffer, INT64U u64_fInput);

/* Function that convert ByteArray to PAN */
extern EN_COMMON_RESULT_t COMMON_ByteArray2PAN(INT8U * p_fDstBuffer, INT8U * p_fSrcBuffer, \
																		INT16U u16_fSrcLen);
/* Function that convert PAN to Byte */
extern EN_COMMON_RESULT_t COMMON_PAN2Byte(INT8U * p_fSrcBuffer, INT8U * p_fOutPut);	

/* Function that convert PAN to HWord */
extern EN_COMMON_RESULT_t COMMON_PAN2HWord(INT8U * p_fSrcBuffer, INT16U * p_fOutPut);

/* Function that convert PAN to Word */
extern EN_COMMON_RESULT_t COMMON_PAN2Word(INT8U * p_fSrcBuffer, INT32U * p_fOutPut);

/* Function that convert PAN to DWord */
extern EN_COMMON_RESULT_t COMMON_PAN2DWord(INT8U * p_fSrcBuffer, INT64U * p_fOutPut);

/* Function that convert PAN to ByteArray  */
extern EN_COMMON_RESULT_t COMMON_PAN2ByteArray(INT8U * p_fSrcBuffer, INT8U * p_fDstBuffer,  \
																		INT16U u16_fDstLen);

/*Function that defines hex to ascii conversion */
extern void COMMON_Hex2Ascii(UINT8 * p_fDst, UINT8 * p_fSrc, UINT8 u8_fLength);

/*Function that defines ascii to hex conversion*/
extern void COMMON_Ascii2Hex(UINT8 * p_fDst, UINT8 * p_fSrc, UINT8 u8_fLength);

/*Function that defines ascii to decima conversion*/
extern UINT32 COMMON_Ascii2Dec(UINT8 * p_fSrc, UINT8 u8_fLength);

/*Function that defines decimal to ascii conversion*/
extern void COMMON_Dec2Ascii(UINT8 * P_fDst, UINT32 u32_fSrc, UINT8 u8_fLength);

/* */
INT16U COMMON_GetCheckSum(INT8U * p_fInput, INT32U u32_fLength);


extern EN_COMMON_RESULT_t COMMON_UnPackData(INT8U * p_fInput, INT32U u32_fLength, \
                                                                     ST_FOTA_PACKET_t *p_fOutput);
#endif

/**************************************************************************************************/
/* End of SMART_COM.h                                                                             */
/**************************************************************************************************/
