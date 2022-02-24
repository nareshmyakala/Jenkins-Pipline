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
/*  File Name   : TBUS_Priv.h                                                                     */
/*  Author      :                                                                                 */
/*  Version 	: v1.0                                                                            */
/*  Date        : 17-02-2022                                                                      */
/*                                                                                                */
/* @Description : TBUS Service Frame Work                                                         */
/**************************************************************************************************/

#ifndef _TBUS_PRIV_H_
#define _TBUS_PRIV_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

/**************************************************************************************************/
/* Private Global Definitions Section                                                             */
/**************************************************************************************************/


/* Modem IF check sum selection macros */
#define TBUS_RX_CHECKSUM				        ( 0x01 )
#define TBUS_TX_CHECKSUM				        ( 0x02 )

/* Modem IF Moacros for frame offsets */
#define TBUS_START_PREAMBLE_OFFSET		  ( 0x00 )
#define TBUS_LENGTH_OFFSET			  ( 0x01 )
#define TBUS_SID_OFFSET				  ( 0x05 )
#define TBUS_DID_OFFSET				  ( 0x07 )
#define TBUS_DATA_OFFSET			  ( 0x09 )
#define TBUS_CHECSUM_OFFSET			  ( 0x0A )
#define TBUS_ENDPREAMBLE1_OFFSET		  ( 0x0E )
#define TBUS_ENDPREAMBLE2_OFFSET		  ( 0x0F )

/* Modem IF Prembels */
#define TBUS_START_PREMBLE              ( 0x3A )
#define TBUS_CR                         ( 0x0D )
#define TBUS_LF                         ( 0x0A )

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

/* */
static void TBUS_RxHandler(INT8U u8_fData);

/* */
static INT8U TBUS_CheckSum(INT8U *pu8_fData, INT16U u16_fLength, INT8U u8_fFlag);

/* */
static void TBUS_SendData(INT8U *pu8_fData, INT16U u16_fLength);

/* */
static void TBUS_ProcessResponse(INT8U *pu8_fData);;

#endif

/**************************************************************************************************/
/* End of  TBUS_Priv.h                                                                            */
/**************************************************************************************************/
