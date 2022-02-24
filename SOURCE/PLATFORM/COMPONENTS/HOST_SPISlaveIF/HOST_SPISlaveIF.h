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
/*  File Name   : HOST_SPISlaveIF.h                                                               */
/*  Author      : NAGANJALI.K                                                                     */
/*  Version 	: v1.0                                                                            */
/*  Date        : 12-02-2022                                                                      */
/*                                                                                                */
/* @Description : HOST_SPISlaveIF Component Frame work                                            */
/**************************************************************************************************/

#ifndef _HOST_SPISLAVEIF_H_
#define _HOST_SPISLAVEIF_H_

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

/* SPI Slave States */
typedef enum
{
    SLAVE_IDLE = 0,
    SLAVE_REQUESTDATA,
    SLAVE_TRASFERDATA,
    
}EN_SPI_SLAVE_STATES_t;

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/* TBUS Buffer Size */
#define SPI_SLAVEIF_BUFFER_SIZE            ( 8300 )

#define SPI_SLAVEIF_START_PREAMBLE         ( '@' )
#define SPI_SLAVEIF_END_PREAMBLE2          ( '#' )

/* Data Buffers */
#define DATA_BUFFER1                        ( 1100 )
#define DATA_BUFFER2                        ( 1100 )

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* SPI Slave IF Init*/
extern void HOST_SPISlaveIFInit(void);

/* SPI Slave IF 1 milli sec Handler */
extern void SPISlaveIF_Handler(void);

#endif

/**************************************************************************************************/
/* End of  HOST_SPISlaveIF.h                                                                      */
/**************************************************************************************************/
