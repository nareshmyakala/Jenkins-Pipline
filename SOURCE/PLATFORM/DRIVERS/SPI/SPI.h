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
/* \File Name   : SPI.h                                                                           */
/* \Author      : Kishore D                                                                       */
/* \Version     : 1.0                                                                             */
/* \Date        : 22/08/2018                                                                      */
/*                                                                                                */
/* @Description :  SPI Driver                                                                     */
/**************************************************************************************************/

#ifndef _SPI_H_
#define _SPI_H_ 

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "GCLK.h"
#include "NVIC.h"
#include "MCLK.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

/*Enum For SPI Module Selection*/
typedef enum
{
    SPI0 = 0,
    SPI1
}EN_SPI_CHANNEL_t;

/* Enum to select SPI Channel */
typedef enum
{
    SERCOM_CH0 = 0,
    SERCOM_CH1,
    SERCOM_CH2,
    SERCOM_CH3,
    SERCOM_CH4,
    SERCOM_CH5,
    SERCOM_CH6,
    SERCOM_CH7
}EN_SPI_SERCOM_CH_SEL_t;

/* Enum for selecting Data Order */
typedef enum
{
    SPI_DORD_MSB_FIRST = 0,
    SPI_DORD_LSB_FIRST
}EN_SPI_DORD_SEL_t;

/* Enum for Selecting MISO Pad */
typedef enum
{
    SPI_MISO_PAD0 = 0,
    SPI_MISO_PAD1,
    SPI_MISO_PAD2,
    SPI_MISO_PAD3
}EN_SPI_MISO_PAD_SEL_t;

/* Enum for Selecting MOSI Pad */
typedef enum
{
    SPI_MOSI_PAD0_SCKL_PAD1 = 0,
    SPI_MOSI_PAD2_SCKL_PAD3,
    SPI_MOSI_PAD3_SCKL_PAD1,
    SPI_MOSI_PAD0_SCKL_PAD3
}EN_SPI_MOSI_PAD_SEL_t;

/* Enum for Selecting MOSI,SCK and SS */
typedef enum
{
    SPI_MOSIPAD0_SCKPAD1_SSPAD2 = 0,
    SPI_MOSIPAD2_SCKPAD3_SSPAD1,
    SPI_MOSIPAD3_SCKPAD1_SSPAD2,
    SPI_MOSIPAD0_SCKPAD3_SSPAD1
}EN_SPI_DOPO_PAD_SEL_t;

/* Choosing SS as Software Control or Hardware Control */
typedef enum
{
    SPI_SS_CONTROLLED_BY_SOFTWARE = 0,
    SPI_SS_CONTROLLED_BY_HARDWARE
}EN_SPI_SS_CONTROL_SELECT_t;

/* Enum to select clock  phase */
typedef enum
{
    SPI_CLOCK_PHASE_CPOL0_CPHA0 = 0x0,
    SPI_CLOCK_PHASE_CPOL0_CPHA1,
    SPI_CLOCK_PHASE_CPOL1_CPHA0,
    SPI_CLOCK_PHASE_CPOL1_CPHA1
}EN_SPI_CLOCK_PHASE_SELECT_t;

/* Structure for SPI Configuration paramaters */
typedef struct
{
    EN_SPI_SERCOM_CH_SEL_t 	        en_mChannel;
    INT32U 				u32_mBaudrate;
    EN_SPI_DORD_SEL_t  			en_mDataOrder;
    EN_SPI_MISO_PAD_SEL_t 		en_mMISOPadSel;
    EN_SPI_DOPO_PAD_SEL_t 		en_mMOSIPadSel;
    EN_SPI_SS_CONTROL_SELECT_t          en_mSSControlSel;
    EN_SPI_CLOCK_PHASE_SELECT_t         en_mClockPhaseSel;
    void (*fp_USERHANDLER)(INT8U );
}ST_SPI_MASTER_CONFIG_PARAMS_t;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function to intialize the SPI Master */
extern void SPI_MasterInit(ST_SPI_MASTER_CONFIG_PARAMS_t *p_stgSPIMasterConfigParams);

/* Function to  read the data in SPI DATA register */
extern INT8U SPI_ReadData(EN_SPI_SERCOM_CH_SEL_t en_fSERCOMChannel);

/* Function to write the data in SPI DATA Register */
extern void SPI_WriteData(EN_SPI_SERCOM_CH_SEL_t en_fSERCOMChannel,INT8U u8_fData);

/* Function to write the data in SPI DATA Register */
extern void SPI_WriteDataI(EN_SPI_SERCOM_CH_SEL_t en_fSERCOMChannel,INT8U u8_fData);

/* Function to transfer byte usign SPI */
extern INT8U TransferByte(EN_SPI_SERCOM_CH_SEL_t en_fSercomChn,INT8U u8_fData);

/* */
extern void SPI_SlaveInit(ST_SPI_MASTER_CONFIG_PARAMS_t *);

/* */
extern void SPI_SlaveRead(EN_SPI_SERCOM_CH_SEL_t, INT8U *);

/* */
extern INT8U SPI_GetStatusFlag(EN_SPI_SERCOM_CH_SEL_t en_fSercomChn, INT32U u32_fFlag);

#endif

/**************************************************************************************************/
/* End of SPI.h                                                                                   */
/**************************************************************************************************/
