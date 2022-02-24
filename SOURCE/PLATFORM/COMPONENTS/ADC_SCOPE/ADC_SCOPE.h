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
/* \File Name   : ADC_SCOPE.h                                                              */
/* \Author      : Prashanth.A                                                                     */
/* \Version 	:                                                                                 */
/* \Date        : 15-12-2017                                                                      */
/*                                                                                                */
/* @Description : ADC scope Frame work                                                            */
/**************************************************************************************************/

#ifndef _ADC_SCOPE_PUBLIC_H_
#define _ADC_SCOPE_PUBLIC_H_

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

/* Scope Frame offsets */
#define ADC_START_PREMBLE	  	 '@'
#define ADC_START_PREMBLE_OFFSET	 ( 0 ) 

#define ADC_END_PREEMBLE	  	 '$'
#define ADC_END_PREEMBLE_OFFSET	  ( 15 )

#define ADC_TIMESTAMP_OFFSET	  ( 1 )
#define ADC_CHANNEL1_OFFSET	  ( 5 )
#define ADC_CHANNEL2_OFFSET	  ( 7 )
#define ADC_CHANNEL3_OFFSET	  ( 9 )
#define ADC_CHANNEL4_OFFSET	  ( 11 )
#define ADC_CHANNEL5_OFFSET	  ( 13 )

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/* Varibale for to Store the Data with Front Index */
extern INT8U u8_gChnlFront;

/* ADC Queue Buffer */
extern INT16U au16_gAdcChnlQueue[5][120];

/* Variables for to Store the 100 Samples Calibrtaed Values */
extern double f32_gC1_Factor;
extern double f32_gC2_Factor;
extern double f32_gC3_Factor;
extern double f32_gC4_Factor;
extern double f32_gC5_Factor;

extern INT16U u16_gAdcValue1;
extern INT16U u16_gAdcValue2;
extern INT16U u16_gAdcValue3;
extern INT16U u16_gAdcValue4;
extern INT16U u16_gAdcValue5;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function Decleration For timer start and Stop */
extern void ADC_ScopeInit(void);

extern INT8U u8_gAnalogEOC;

/* */
extern void ADC_ScopeStart(void);

/* */
extern void ADC_ScopeStop(void);

/* */
extern void ADCSCOPE_QueueWrite(INT8U u8_fChannel, INT16U u16_fData);

/* */
extern INT16U ADCSCOPE_QueueRead(INT8U u8_fChannel);

/* */
extern INT8U ADCSCOPE_GetQueueSize(void);

/* */
extern void ADCSCOPE_ResetQueue(void);

/* */
extern void ADCSCOPE_ReadCalibValues(void);

/* */
extern void ADCSCOPE_ResetCalib(void);

extern void Scope_WriteAnalogData(INT8U * pu8_fData);

#endif

/**************************************************************************************************/
/* End of ADC_SCOPE.h                                                                      */
/**************************************************************************************************/

