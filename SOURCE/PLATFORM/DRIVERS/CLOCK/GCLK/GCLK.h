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
/* \File Name   : GCLK_Priv.h                                                                     */
/* \Author      : Kishore D	                                                                      */
/* \Version 		: v1.0                                                                            */
/* \Date        : 23/08/2018                                                                      */
/*                                                                                                */
/* @Description : GCLK Driver Frame Work                                                          */
/**************************************************************************************************/

#ifndef _GCLK_H_
#define _GCLK_H_

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

/* Enum for Result Purpose */
typedef enum
{
	GCLK_ERROR = 0x00,
	GCLK_SUCCESS
} EN_GCLK_RESULT_t;

/* Enum to Hold Generators */
typedef enum
{
	CLK_GEN0 = 0x00,
	CLK_GEN1,
	CLK_GEN2,
	CLK_GEN3,
	CLK_GEN4,
	CLK_GEN5,
	CLK_GEN6,
	CLK_GEN7,
	CLK_GEN8
} EN_CLK_GEN_t;

/* Enum Holds Peripheral Channel Control */
typedef enum
{
	PERIPH_CHNL_CTRL00 = 0x00,
	PERIPH_CHNL_CTRL01,
	PERIPH_CHNL_CTRL02,
	PERIPH_CHNL_CTRL03,
	PERIPH_CHNL_CTRL04,
	PERIPH_CHNL_CTRL05,
	PERIPH_CHNL_CTRL06,
	PERIPH_CHNL_CTRL07,
	PERIPH_CHNL_CTRL08,
	PERIPH_CHNL_CTRL09,
	PERIPH_CHNL_CTRL10,
	PERIPH_CHNL_CTRL11,
	PERIPH_CHNL_CTRL12,
	PERIPH_CHNL_CTRL13,
	PERIPH_CHNL_CTRL14,
	PERIPH_CHNL_CTRL15,
	PERIPH_CHNL_CTRL16,
	PERIPH_CHNL_CTRL17,
	PERIPH_CHNL_CTRL18,
	PERIPH_CHNL_CTRL19,
	PERIPH_CHNL_CTRL20,
	PERIPH_CHNL_CTRL21,
	PERIPH_CHNL_CTRL22,
	PERIPH_CHNL_CTRL23,
	PERIPH_CHNL_CTRL24,
	PERIPH_CHNL_CTRL25,
	PERIPH_CHNL_CTRL26,
	PERIPH_CHNL_CTRL27,
	PERIPH_CHNL_CTRL28,
	PERIPH_CHNL_CTRL29,
	PERIPH_CHNL_CTRL30,
	PERIPH_CHNL_CTRL31,
	PERIPH_CHNL_CTRL32,
	PERIPH_CHNL_CTRL33,
	PERIPH_CHNL_CTRL34
} EN_PERIPH_CHNL_CTRL_t;

/* enum for Generator Status */
typedef enum
{
	GEN_DISABLE = 0x00,
	GEN_ENABLE
} EN_GEN_STATUS_t;

/* Structure to Configure the Generator */
typedef struct
{
	INT8U u8_lGenClockSrc;
	EN_CLK_GEN_t en_mGenStatus;
	INT16U u16_mGenDivider;
	EN_CLK_GEN_t en_mGENSelect;
	EN_CLK_GEN_t en_mPerpheralSource;
	EN_GEN_STATUS_t en_mChnlStatus;
} ST_GEN_DATA_t;

/* Enum for list Peripherals */
typedef enum
{
	GCLK_DFLL_48_REF,
	GCLK_DPLL0,
	GCLK_DPLL1,
	GCLK_DPLL_32K,
	GCLK_EIC,
	GCLK_FREQM_MSR,
	GCLK_FREQM_REF,
	GCLK_SERCOM0_CORE,
	GCLK_SERCOM1_CORE,
	GCLK_TC0,
	GCLK_TC1 = 9,
	GCLK_USB,
	GCLK_EVSYS_CH0,
	GCLK_EVSYS_CH1,
	GCLK_EVSYS_CH2,
	GCLK_EVSYS_CH3,
	GCLK_EVSYS_CH4,
	GCLK_EVSYS_CH5,
	GCLK_EVSYS_CH6,
	GCLK_EVSYS_CH7,
	GCLK_EVSYS_CH8,
	GCLK_EVSYS_CH9,
	GCLK_EVSYS_CH10,
	GCLK_EVSYS_CH11,
	GCLK_SERCOM2_CORE,
	GCLK_SERCOM3_CORE,
	GCLK_TCC0,
	GCLK_TC2,
	GCLK_CAN0,
	GCLK_CAN1,
	GCLK_TCC2,
	GCLK_TC4,
	GCLK_PDEC,
	GCLK_AC,
	GCLK_CCL,
	GCLK_SERCOM4_CORE,
	GCLK_SERCOM5_CORE,
	GCLK_SERCOM6_CORE,
	GCLK_SERCOM7_CORE,
	GCLK_TCC4,
	GCLK_TC6,
	GCLK_ADC0,
	GCLK_ADC1,
	GCLK_DAC,
	GCLK_I2S0,
	GCLK_I2S1,
	GCLK_SDHC0,
	GCLK_SDHC1,
	GCLK_CM4_TRACE
} EN_GCLK_PERIPH_SEL_t;

/* Enum to select SERCOM channel */
typedef enum
{
	GCLK_SERCOM_CH_0 = 0,
	GCLK_SERCOM_CH_1,
	GCLK_SERCOM_CH_2,
	GCLK_SERCOM_CH_3,
	GCLK_SERCOM_CH_4,
	GCLK_SERCOM_CH_5,
	GCLK_SERCOM_CH_6,
	GCLK_SERCOM_CH_7
}EN_GCLK_SERCOM_CH_SEL_t;

/**************************************************************************************************/
/* Export Global Variable Section                                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function to Init GEN 0 */
extern void GCLK_Generator0Init(void);

/* Function to Enable Peripheral Clock */
extern void GCLK_PeripheralClockEnable(EN_GCLK_PERIPH_SEL_t en_fPeripheral);
	
/* Function to Enable SERCOM clock */
extern void GCLK_EnableSERCOMClock(EN_GCLK_SERCOM_CH_SEL_t en_fChannel);

#endif

/**************************************************************************************************/
/* End of GCLK.h                                                                                  */
/**************************************************************************************************/
