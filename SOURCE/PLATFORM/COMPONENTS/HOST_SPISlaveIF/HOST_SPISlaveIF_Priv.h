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
/*  File Name   : HOST_SPISlaveIF_Priv.h                                                          */
/*  Author      : NAGANJALI.K                                                                     */
/*  Version 	: v1.0                                                                            */
/*  Date        : 12-02-2022                                                                      */
/*                                                                                                */
/* @Description : HOST_SPISlaveIF Component Frame work                                            */
/**************************************************************************************************/

#ifndef _HOST_SPISLAVEIF_PRIV_H_
#define _HOST_SPISLAVEIF_PRIV_H_

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

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

/* SPI Slave Idle Handler */
static void HOST_SPISlaveIF_IdleHandler(EN_SPI_SLAVE_STATES_t *pen_fState);

/* SPI Slave Request Data Handler */
static void HOST_SPISlaveIF_RequestDataHandler(EN_SPI_SLAVE_STATES_t *pen_fState);

static void HOST_SPISlaveIF_TansferDataHandler(EN_SPI_SLAVE_STATES_t *pen_fState);

/* SPI Slave Rx Handler */
static void SPI_RxHandler(INT8U u8_fSPISlaveRxData);

#endif

/**************************************************************************************************/
/* End of  HOST_SPISlaveIF_Priv.h                                                                 */
/**************************************************************************************************/
