/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2015, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : UART.c                                                                          */
/* \Author      : Kishore D                                                                       */
/* \Version 		: v1.0                                                                            */
/* \Date        : 23/08/2018                                                                      */
/*                                                                                                */
/* @Description : UART Driver                                                                     */
/**************************************************************************************************/

#ifndef _UART_H_
#define _UART_H_ 

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

/* Enum to select RX Data pinout PAD */
typedef enum
{
	SERCOM_RX_PAD0 = 0,
	SERCOM_RX_PAD1,
	SERCOM_RX_PAD2,
	SERCOM_RX_PAD3
}EN_USART_RX_PAD_SEL_t;

/* Enum to select TX Data pinout pad */
typedef enum
{
	SERCOM_TX_PAD0 = 0,
	RESERVED,
	SERCOM_TX_PAD2,
	SERCOM_TX_PAD0_RTS_CTS,
}EN_USART_TX_PAD_SEL_t;

/* Enum for Parity Select */
typedef enum
{
	USART_EVEN_PARITY = 0,
	USART_ODD_PARITY,
	USART_PARITY_DISABLE
}EN_USART_PARITY_SEL_t;

/* Enum for Selecting number of stop bits */
typedef enum
{
	USART_ONE_STOP_BIT = 0,
	USART_TWO_STOP_BITS
}EN_USART_STOP_BITS_SEL_t;

/* ENUM TO SELECT CHARACTER SIZE */
typedef enum
{
	USART_CH_SIZE_8_BITS = 0,
	USART_CH_SIZE_9_BITS,
	CH_SIZE_RESERVED0,
	CH_SIZE_RESERVED1,
	CH_SIZE_RESERVED2,
	USART_CH_SIZE_5_BITS,
	USART_CH_SIZE_6_BITS,
	USART_CH_SIZE_7_BITS
}EN_USART_DATA_BITS_SEL_t;

/* Enum to select SERCOM channel */
typedef enum
{
	SERCOM_CH_0 = 0,
	SERCOM_CH_1,
	SERCOM_CH_2,
	SERCOM_CH_3,
	SERCOM_CH_4,
	SERCOM_CH_5,
	SERCOM_CH_6,
	SERCOM_CH_7,
}EN_SERCOM_CH_SEL_t;

/* Enum to SERCOM PAD Selection */
typedef enum
{
	SERCOM_PAD_0 = 0,
	SERCOM_PAD_1,
	SERCOM_PAD_2,
	SERCOM_PAD_3
}EN_SERCOM_PAD_t;

/* Structure to Configure UART */
typedef struct
{
	EN_SERCOM_CH_SEL_t         en_mSERCOMChnl;
	EN_USART_DATA_BITS_SEL_t   en_mDataBits;
	EN_USART_STOP_BITS_SEL_t   en_mStopBits;
	EN_USART_PARITY_SEL_t      en_mParity;
	INT32U 				  u32_mBaudrate;
	EN_USART_TX_PAD_SEL_t      en_mTXPad;
	EN_USART_RX_PAD_SEL_t      en_mRXPad;
	void (*fp_USERHANDLER)(INT8U);
}ST_UART_CONFIG_PARAMS_t;

/**************************************************************************************************/
/* Helper Functions Section                                                                       */
/**************************************************************************************************/

/* Function to calculate baudrate */
extern INT16U UART_CalculateBaudrate(INT32U u32_fBaudrate);

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function to Initialize the UART */
extern void UART_Init(ST_UART_CONFIG_PARAMS_t *p_stfUARTConfigParams);

/* Function to Transmit a character */
extern void UART_TransmitChar(EN_SERCOM_CH_SEL_t en_fChannel,INT8U u8_fData);

/* Function to Transmit string */
extern void UART_TransmitString(EN_SERCOM_CH_SEL_t en_fChannel,INT8U *u8_fstr);

/* Function to Transmit number */
extern void UART_TransmitNumber(EN_SERCOM_CH_SEL_t en_fChannel,INT32U u32_fNumber);

/* Function to Receive character */
extern INT8U UART_RecieveChar(EN_SERCOM_CH_SEL_t en_fChannel);

/**************************************************************************************************/
/* Helper Functions Section                                                                       */
/**************************************************************************************************/

/* Function to Enable UART */
extern void UART_Enable(EN_SERCOM_CH_SEL_t en_fChannel);

/* Function to Disable UART */
extern void UART_Disable(EN_SERCOM_CH_SEL_t en_fChannel);

#endif

/**************************************************************************************************/
/* End of UART.h                                                                                  */
/**************************************************************************************************/
