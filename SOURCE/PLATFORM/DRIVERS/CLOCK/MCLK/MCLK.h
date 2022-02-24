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
/* \File Name   : MCLK.c                                                                          */
/* \Author      : Kishore D                                                                       */
/* \Version 		: v1.0                                                                            */
/* \Date        : 23/08/2018                                                                      */
/*                                                                                                */
/* @Description : MCLK Driver 	    		                                                          */
/**************************************************************************************************/

#ifndef _MCLK_H_
#define _MCLK_H_

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

/* Enum For Result Purpose */
typedef enum
{
	MCLK_ERROR = 0x00,
	MCLK_SUCCESS
} EN_MCLK_RESULT_t;

/* Enum For Periph Bus Sel */
typedef enum
{
    MCLK_AHB = 0x00,
    MCLK_APBA,
    MCLK_APBB,
    MCLK_APBC,
    MCLK_APBD,
}EN_PERIPH_BUS_SEL_t;

/* Enum For MCLK Periph Sel */
typedef enum
{
    MCLK_AHB_HPBn0	 = 0,
    MCLK_AHB_HPBn1	 = 1,
    MCLK_AHB_HPBn2	 = 2,
    MCLK_AHB_HPBn3	 = 3,
    MCLK_AHB_DSU 	 = 4,
    MCLK_AHB_NVMCTRL	 = 6,
    MCLK_AHB_CMCC	 = 8,
    MCLK_AHB_DMAC 	 = 9,
    MCLK_AHB_USB 	 = 10,
    MCLK_AHB_PAC 	 = 12,
    MCLK_AHB_QSPI 	 = 13,
    MCLK_AHB_GMAC 	 = 14,
    MCLK_AHB_SDHCn0 	 = 15,
    MCLK_AHB_SDHCn1 	 = 16,
    MCLK_AHB_CANn0 	 = 17,
    MCLK_AHB_CANn1 	 = 18,
    MCLK_AHB_ICM 	 = 19,
    MCLK_AHB_PUKCC 	 = 20,
    MCLK_AHB_QSPI_2X 	 = 21,
    MCLK_AHB_NVMCTRL_SMEEPROM = 22,
    MCLK_AHB_NVMCTRL_CACHE = 23,
    MCLK_APBA_PAC 	 = 0,
    MCLK_APBA_PM 	 = 1,
    MCLK_APBA_MCLK 	 = 2,
    MCLK_APBA_RSTC 	 = 3,
    MCLK_APBA_OSCCTRL 	 = 4,
    MCLK_APBA_OSC32KCTRL 	= 5,
    MCLK_APBA_SUPC 	 = 6,
    MCLK_APBA_GCLK 	 = 7,
    MCLK_APBA_WDT 	 = 8,
    MCLK_APBA_RTC 	 = 9,
    MCLK_APBA_EIC 	 = 10,
    MCLK_APBA_FREQM 	 = 11,
    MCLK_APBA_SERCOM0 	 = 12,
    MCLK_APBA_SERCOM1 	 = 13,
    MCLK_APBA_TCn0 	 = 14,
    MCLK_APBA_TCn1 	 = 15,
    MCLK_APBB_USB 	 = 0,
    MCLK_APBB_DSU 	 = 1,
    MCLK_APBB_NVMCTRL 	 = 2,
    MCLK_APBB_PORT 	 = 4,
    MCLK_APBB_EVSYS 	 = 7,
    MCLK_APBB_SERCOM2 	 = 9,
    MCLK_APBB_SERCOM3 	 = 10,
    MCLK_APBB_TCCn0 	 = 11,
    MCLK_APBB_TCCn1 	 = 12,
    MCLK_APBB_TCn2 	 = 13,
    MCLK_APBB_TCn3 	 = 14,
    MCLK_APBB_RAMECC 	 = 16,
    MCLK_APBC_GMAC 	 = 2,
    MCLK_APBC_TCCn2 	 = 3,
    MCLK_APBC_TCCn3 	 = 4,
    MCLK_APBC_TCn4 	 = 5,
    MCLK_APBC_TCn5 	 = 6,
    MCLK_APBC_PDEC 	 = 7,
    MCLK_APBC_AC 	 = 8,
    MCLK_APBC_AES 	 = 9,
    MCLK_APBC_TRNG 	 = 10,
    MCLK_APBC_ICM 	 = 11,
    MCLK_APBC_QSPI 	 = 13,
    MCLK_APBC_CCL 	 = 14,
    MCLK_APBD_SERCOM4 	 = 0,
    MCLK_APBD_SERCOM5 	 = 1,
    MCLK_APBD_SERCOM6 	 = 2,
    MCLK_APBD_SERCOM7 	 = 3,
    MCLK_APBD_TCC4 	 = 4,
    MCLK_APBD_TC6 	 = 5,
    MCLK_APBD_TC7 	 = 6,
    MCLK_APBD_ADCn0 	 = 7,
    MCLK_APBD_ADCn1 	 = 8,
    MCLK_APBD_DAC 	 = 9,
    MCLK_APBD_I2C 	 = 10,
    MCLK_APBD_PCC 	 = 11,
}EN_MCLK_PERIPH_SEL_t;

/**************************************************************************************************/
/* Export Global Variable Section                                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function to initialize the MCLK */
extern void MCLK_Init(void);

extern void MCLK_FlashClkInit(void);

extern void MCLK_PeriphClkInit(EN_PERIPH_BUS_SEL_t en_fPeriphBus, EN_MCLK_PERIPH_SEL_t en_fPeriph);

#endif

/**************************************************************************************************/
/* End of MCLK.h                                                                                  */
/**************************************************************************************************/
