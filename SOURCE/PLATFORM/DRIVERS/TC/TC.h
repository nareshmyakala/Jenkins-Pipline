/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2013, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : TC.h                                                                            */
/* \Author      : Salman Ali                                                                      */
/* \Version 	: 1.1                                                                             */
/* \Date        : 29/2/16                                                                         */
/*                                                                                                */
/* @Description : TC Driver Framework                                                             */
/**************************************************************************************************/

#ifndef _TC_H_ 
#define _TC_H_ 

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

/*Enum to select Timer Slice (TC0/1/2/3/4) */
typedef enum
{
	TC_SLICE_0 = 0,
	TC_SLICE_1,
	TC_SLICE_2,
	TC_SLICE_3,
	TC_SLICE_4,
    TC_SLICE_5,
	TC_SLICE_6,
	TC_SLICE_7	
}EN_TC_SLICE_t;

typedef enum
{
    TC_16_BIT_COUNTER = 0x0,
    TC_8_BIT_COUNTER,
    TC_32_BIT_COUNTER
}EN_TC_COUNTER_MODE_t;

/* Enum for choosing Capture/Compare Mode */
typedef enum
{
	TC_COMPARE_MODE = 0,
	TC_CAPTURE_MODE
}EN_TC_CC_MODE_SEL_t;

/* Enum to select Prescalar */
typedef enum
{
	TC_DIV_1 = 0,
	TC_DIV_2,
	TC_DIV_4,
	TC_DIV_8,
	TC_DIV_16,
	TC_DIV_64,
	TC_DIV_256,
	TC_DIV_1024
}EN_TC_PRESCALAR_t;

/* Capture/Compare Channel Select */
typedef enum
{
	TC_CCx_CHANNEL_0 = 0,
	TC_CCx_CHANNEL_1,
}EN_TC_CCx_CHANNEL_SEL_t;

/* */
typedef enum
{
	TC_EVACT_OFF = 0x0,
	TC_EVACT_RETRIGGER,
	TC_EVACT_COUNT,
	TC_EVACT_START,
	TC_EVACT_STAMP,
	TC_EVACT_PPW,
	TC_EVACT_PWP,
	TC_EVACT_PW
}EN_TC_EVACT_SEL_t;

typedef enum
{
    TC_RISING_EDGE = 0x00,
    TC_FALLING_EDGE,
}EN_TC_EDGE_SEL_t;

typedef enum
{
    TC_DELAY_US = 0x00,
    TC_DELAY_MS,
}EN_TC_DELAY_TYPE_t;

/* Structure for TC Event parameters */
typedef struct
{
    EN_TC_SLICE_t 		    en_mTCSlice;
    EN_TC_DELAY_TYPE_t      en_mDelayType;              
    INT32U			        u32_mTime;
    void (*fp_User_Handler)(void);
}ST_TC_EVENT_PARAMS_t;

/* Structure for TC PWM Parameters */
typedef struct
{
	EN_TC_SLICE_t 			  	en_mTCSlice;
	INT32U					    u32_PWMFreq;
	EN_TC_PRESCALAR_t	        en_mPrescalar;
    EN_TC_CCx_CHANNEL_SEL_t     en_mCompareChannel;
    INT32F					    f32_mCompDutyCycle;
}ST_TC_PWM_PARAMS_t;

/* Structure for TC Capture Event parameters */
typedef struct
{
	EN_TC_SLICE_t 			  	en_mTCSlice;
	EN_TC_CCx_CHANNEL_SEL_t		en_mCaptureChannel;
	EN_TC_EDGE_SEL_t            en_mEdgeSel;
	void (*fp_User_Handler)(void);
	
}ST_TC_CAPTURE_EVENT_PARAMS_t;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function to Select TC Mode */
static void TC_ModeSelect(EN_TC_SLICE_t en_fSlice,EN_TC_CC_MODE_SEL_t en_fMode,\
                                                                EN_TC_CCx_CHANNEL_SEL_t en_fCh);
/* Function to Enable TC */
extern void TC_Enable(EN_TC_SLICE_t en_fSlice);

/* Function to Disable TC */
extern void TC_Disable(EN_TC_SLICE_t en_fSlice);

/* Function to Perform Software Reset */
extern void TC_SoftReset(EN_TC_SLICE_t en_fSlice);

/******************************* TC Event Functions ***********************************************/

/* Function to iniitialize TC Event */
extern void TC_EventInit(ST_TC_EVENT_PARAMS_t *p_stfTCEventParams);

/* Function to Calculate Period value */
INT16U TC_GetEventPeriodValueinTime(INT32U u32_fTimeinMs,INT32U u32_fPresclar,\
                                                            EN_TC_DELAY_TYPE_t en_fDelayType);
/* Function to Set Period Value */
static void TC_SetPeriodValue(EN_TC_SLICE_t en_fSlice,INT32U u32_fPeriod);

/* Function to Get Period Value for 8-Bit Counter */
extern INT8U TC_GetEventPeriodValuefor8BitCounter(INT32U u32_fFreqHz,INT32U u32_fPresclar,\
                                                                            INT32U u32_fGCLKFreq);
/********************************* TC Capture Functions ********************************************/

/* Function to Get Capture Value */
extern INT16U TC_GetCaptureValue(EN_TC_SLICE_t en_fSlice, EN_TC_CCx_CHANNEL_SEL_t en_fChNo);

/* Function to Initialize Capture Events */
extern void TC_CaptureEvents(ST_TC_CAPTURE_EVENT_PARAMS_t *p_stfCaptureEventParams);

/* Function to Set Compare Value */
extern void TC_SetCompareValue(EN_TC_SLICE_t en_fSlice,EN_TC_CCx_CHANNEL_SEL_t \
                                                                    en_fCh,INT16U u16_fCompval);

/************************************* TC PWM Functions ********************************************/

/* Function to Set compare value in 8-bit counter */
extern void TC_SetCompareValuefor8BitCoutner(EN_TC_SLICE_t en_fSlice, INT8U u8_fCompval);

/* Function to Initialize the PWM Generation */
extern void TC_PWMInit(ST_TC_PWM_PARAMS_t *p_stfTCPWMParams);

/* Function to Set PWM Compare Value */
extern void TC_PWMSetCompareValue(EN_TC_SLICE_t en_fSlice,\
                                            EN_TC_CCx_CHANNEL_SEL_t en_fCh,INT16U u16_fCompval);
/* Function to Get DutyCycle */
extern INT16U TC_PWMGetCompareValue(INT8U u8_fDutyCycle,INT16U u16_fPeriod);

extern INT16U TC_GetPwmPeriodValueinTime(INT32U u32_fTimeinMs,INT32U u32_fPresclar);

#endif

/**************************************************************************************************/
/* End of TC.h                                                                                    */
/**************************************************************************************************/
