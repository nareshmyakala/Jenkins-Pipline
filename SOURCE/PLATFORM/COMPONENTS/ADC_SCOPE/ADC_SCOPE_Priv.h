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
/* \File Name   : ADC_SCOPE_Priv.h                                                             */
/* \Author      : Prashanth.A                                                                     */
/* \Version 	:                                                                                 */
/* \Date        : 15-12-2017                                                                      */
/*                                                                                                */
/* @Description : ADC scope Frame work                                                            */
/**************************************************************************************************/

#ifndef _ADC_SCOPE_PRIVATE_H_
#define _ADC_SCOPE_PRIVATE_H_

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

/* ADC Timer User Handler */
static void ADCSCOPE_TimerHandler(void);

/* ADC user Handlers */
static void ADC0_Ch1UserHandler(void);
static void ADC0_Ch6UserHandler(void);
static void ADC0_Ch7UserHandler(void);
static void ADC1_Ch8UserHandler(void);
static void ADC1_Ch9UserHandler(void);

/* declerations for to Store the MAF Applied Data for Each Channel */
static INT16U ADCSCOPE_Ch1MAF16(INT16U u16_fInPut);
static INT16U ADCSCOPE_Ch2MAF16(INT16U u16_fInPut);
static INT16U ADCSCOPE_Ch3MAF16(INT16U u16_fInPut);
static INT16U ADCSCOPE_Ch4MAF16(INT16U u16_fInPut);
static INT16U ADCSCOPE_Ch5MAF16(INT16U u16_fInPut);

#endif

/**************************************************************************************************/
/* End of ADC_SCOPE_Priv.h                                                                     */
/**************************************************************************************************/

