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
/* \File Name   : ADC.h                                                                           */
/* \Author      : Ravi Ranjan Kumar                                                               */
/* \Version 	: 1.1                                                                             */
/* \Date        : 10/09/2018                                                                      */
/*                                                                                                */
/* @Description : ADC Driver Framework                                                            */
/**************************************************************************************************/

#ifndef _ADC_H_ 
#define _ADC_H_

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


/* Enum to select ADC */
typedef enum
{
	ADC_0,
	ADC_1,
	MAX_ADC
}EN_ADC_SEL_t;

/* Enum to select desired operation in ctrla register */
typedef enum
{
	ADC_SWRST = 0,
	ADC_ENABLE,
	ADC_RUNSTDBY,
	ADC_ONDEMAND,
	ADC_DISABLE
}EN_ADC_CTRLA_OPER_SEL_t;

/* Enum to provide ADC trigger */
typedef enum
{
	ADC_START_CONVERSION,
	ADC_FLUSH_CONVERSION
}EN_ADC_TRIGGER_SEL_t;

/* Enum for ADC Channel Selection */
typedef enum
{
	ADC_CH0 = 0x00,
	ADC_CH1,
	ADC_CH2,
	ADC_CH3,
	ADC_CH4,
	ADC_CH5,
	ADC_CH6,
	ADC_CH7,
	ADC_CH8,
	ADC_CH9,
	ADC_CH10,
	ADC_CH11,
	ADC_CH12,
	ADC_CH13,
	ADC_CH14,
	ADC_CH15,
}EN_ADC_CHANNEL_t;

/* Enum for selecting Prescalar */
typedef enum
{
	ADC_DIV_2 = 0,
	ADC_DIV_4,
	ADC_DIV_8,
	ADC_DIV_16,
	ADC_DIV_32,
	ADC_DIV_64,
	ADC_DIV_128,
	ADC_DIV_256
}EN_ADC_PRESCALAR_t;

/* Enum for selecting Prescalar */
typedef enum
{
	ADC_12BIT_RESOLUTION = 0,
	ADC_16BIT_RESOLUTION,		/* For this Enable Averaging */
	ADC_10BIT_RESOLUTION,
	ADC_8BIT_RESOLUTION,
}EN_ADC_RESOLUTION_t;

/* Enum to Select  Sample */
typedef enum
{
	ADC_1_SAMPLE 	= 0,
	ADC_2_SAMPLE,
	ADC_4_SAMPLE,
	ADC_8_SAMPLE,
	ADC_16_SAMPLE,
	ADC_32_SAMPLE,
	ADC_64_SAMPLE,
	ADC_128_SAMPLE,
	ADC_256_SAMPLE,
	ADC_512_SAMPLE,
	ADC_1024_SAMPLE,
}EN_ADC_SAMPLE_t;

/* ADC Config Parameters */
typedef struct
{
	EN_ADC_SEL_t		en_mADCModule;
	EN_ADC_CHANNEL_t 	en_mADCChannel;
	EN_ADC_SAMPLE_t		en_mADCSample;
	INT8U				u8_mSampleTimeLen;
	EN_ADC_RESOLUTION_t	en_mADCResolution;
	EN_ADC_PRESCALAR_t  en_mADCPrescalar;
	void 				(* fp_ADCUserHandler)(void);
}ST_ADC_PARAMS_t;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function to  Function to initialize the ADC */ 
extern void ADC_Init(ST_ADC_PARAMS_t *st_gADCConfigParams);

/* Function to  Trigger the ADC */
extern void ADC_Trigger(EN_ADC_SEL_t en_fADCModule, EN_ADC_CHANNEL_t en_lADCChannel, \
																EN_ADC_TRIGGER_SEL_t en_fTrigger);
/* Function to  Get the Result */
extern INT16U ADC_GetResult(EN_ADC_SEL_t en_fADCModule);

/* Function to Get an analog equivalent */
extern INT32F ADC_GetAnalogEquivalent(EN_ADC_SEL_t en_fADCModule, INT16U u16_fADCResult);

/* Function to Perform ADC Operation */ 
extern void ADC_Operation(EN_ADC_SEL_t en_fADCModule, EN_ADC_CTRLA_OPER_SEL_t en_fOperationSel);

extern void ADC_ResetTrigger(void);

#endif

/**************************************************************************************************/
/* End of ADC.h                                                                                   */
/**************************************************************************************************/
