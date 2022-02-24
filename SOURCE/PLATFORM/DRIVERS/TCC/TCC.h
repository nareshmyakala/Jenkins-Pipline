/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2015, Think Embedded Pvt. Ltd. (TEPL)             	          */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : TCC.h                                                                           */
/* \Author      : Salman Ali                                                                      */
/* \Version 	: 1.0c	                                                                          */
/* \Date        : 20/11/2015  			                                                  */
/* @Description : TCC  Driver Framework                                                           */
/**************************************************************************************************/

#ifndef TCC_H_
#define TCC_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "GPIO.h"
#include "GCLK.h"
#include "NVIC.h"
#include "MCLK.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

/*Enum to select Timer Slice (TCC0/1/2) */
typedef enum
{
    TCC_SLICE_0 = 0,
    TCC_SLICE_1,
    TCC_SLICE_2,
    TCC_SLICE_3,
    TCC_SLICE_4,
}EN_TCC_SLICE_t;

/* Capture/Compare Channel Select */
typedef enum
{
    CCx_CHANNEL_0 = 0,
    CCx_CHANNEL_1,
    CCx_CHANNEL_2,
    CCx_CHANNEL_3,
    CCx_CHANNEL_4,
    CCx_CHANNEL_5,
    CCx_NO_CHANNEL,
    CCx_ALL_CHANNELS	
}EN_CCx_CHANNEL_SEL_t;



/* Enum for choosing Capture/Compare Mode */
typedef enum
{
    TCC_COMPARE_MODE = 0,
    TCC_CAPTURE_MODE
}EN_TCC_CC_MODE_SEL_t;

/* Enum to select Prescalar */
typedef enum
{
    TCC_DIV_1 = 0,
    TCC_DIV_2,
    TCC_DIV_4,
    TCC_DIV_8,
    TCC_DIV_16,
    TCC_DIV_64,
    TCC_DIV_256,
    TCC_DIV_1024
}EN_TCC_PRESCALAR_t;

/* Enum to select TCC Command */
typedef enum
{
    TCC_NO_ACTION = 0,
    TCC_RETRIGGER,
    TCC_STOP,
    TCC_UPDATE,
    TCC_READSYNC
}EN_TCC_COMMAND_t;

/* Enum to slect Inverted Input Enable or disable */
typedef enum
{
    TCC_INVERTED_INUPUT_DISABLE = 0,
    TCC_INVERTED_INUPUT_ENABLE
}TCC_TC_INVEN_SEL_t;

/*Enum to select Waveform generator type */
typedef enum
{
    TCC_NORMAL_FREQUENCY = 0,
    TCC_MATCH_FREQUENCY,
    TCC_NORMAL_PWM,
    TCC_RESERVED,
    TCC_DSCRITICAL,
    TCC_DSBOTTOM,
    TCC_DSBOTH,
    TCC_DSTOP
}EN_WAVEFORM_TYPE_t;

/* Enum to select Interrupts */
typedef enum
{
    TCC_OVF_INT,
    TCC_TRG_INT,
    TCC_CNT_INT,
    TCC_ERR_INT,
    TCC_DFS_INT,
    TCC_FAULTA_INT,
    TCC_FAULTB_INT,
    TCC_FAULT0_INT,
    TCC_FAULT1_INT,
    TCC_MC0_INT,
    TCC_MC1_INT,
    TCC_MC2_INT,
    TCC_MC3_INT
}EN_INTERRUPT_SEL_t;

/* Enum to select Output matrix */
typedef enum
{
    TCC_OUTMX_0 = 0,
    TCC_OUTMX_1,
    TCC_OUTMX_2,
    TCC_OUTMX_3
}EN_OUTMATRIX_SEL_t;

/*Enable to Enable/Disable Dead time insertion */
typedef enum
{
    TCC_DEAD_TIME_DISABLE = 0,
    TCC_DEAD_TIME_ENABLE
}EN_DEAD_TIME_SEL_t;

/* Enum for selecting Dead Time Generator 0/1/2/3 */
typedef enum
{
    TCC_DTIEN0,
    TCC_DTIEN1,
    TCC_DTIEN2,
    TCC_DTIEN3
}EN_DEAD_TIME_CHNL_SEL_t;

/* Structure for Dead Time Params */
typedef struct
{
    EN_TCC_SLICE_t 		en_mTCCSlice;
    EN_OUTMATRIX_SEL_t          en_mOutMatrix;
    EN_DEAD_TIME_CHNL_SEL_t     en_mDTChnSel;
    EN_DEAD_TIME_SEL_t          en_mDeadTimeSel;
    INT32U			u32_mDTLS;
    INT32U			u32_mDTHS;
}ST_DEAD_TIME_CONFIG_PARAMS_t;

/* Enum to select TCC use */
typedef enum
{
    TCC_EVENT_GENERATION,
    TCC_PWM_GENERATION
}EN_TCC_USE_SEL_t;

typedef enum
{
    TCC_DELAY_MS = 0x00,
    TCC_DELAY_US,
}EN_TCC_DELAY_TYPE_t;

/* Structure for TCC Params for PWM Generation */
typedef struct
{
    EN_TCC_SLICE_t 		en_mTCCSlice;
    EN_CCx_CHANNEL_SEL_t 	en_mCCxCh;
    EN_TCC_CC_MODE_SEL_t 	en_mMode;
    INT32U         		u32_mPWMFreq;
    EN_TCC_PRESCALAR_t	        en_mPrescalar;
    INT32F			f32_mComp0DutyCycle;
    INT32F			f32_mComp1DutyCycle;
    INT32F			f32_mComp2DutyCycle;
    INT32F			f32_mComp3DutyCycle;
    INT32F			f32_mComp4DutyCycle;
    INT32F                      f32_mComp5DutyCycle;
    EN_WAVEFORM_TYPE_t 		en_mWaveType;
}ST_TCC_PWM_CONFIG_t;

/* Structure for TCC Params for Capture */
typedef struct
{
    EN_TCC_SLICE_t 		  en_mTCCSlice;
    EN_CCx_CHANNEL_SEL_t 	  en_mCCxCh;
    EN_TCC_CC_MODE_SEL_t 	  en_mMode;
    EN_TCC_PRESCALAR_t	          en_mPrescalar;
    void (*fp_User_Handler)(void);
}ST_TCC_CAPTURE_PARAMS_t;

/* Structure for TCC Event parameters */
typedef struct
{
    EN_TCC_SLICE_t 		en_mTCCSlice;
    EN_TCC_CC_MODE_SEL_t 	en_mMode;
    INT32F			f32_mTime;
    EN_TCC_DELAY_TYPE_t         en_mDelayType;
    void (*fp_User_Handler)(void);
	
}ST_TCC_EVENT_PARAMS_t;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function to Enable TCC */
static void TCC_Enable(EN_TCC_SLICE_t en_fSlice);

/* Function to Perform Software Reset */
static void TCC_SoftReset(EN_TCC_SLICE_t en_fSlice);

/* Function to Select TCC Mode */
static void TCC_ModeSelect(EN_TCC_SLICE_t en_fSlice,EN_TCC_CC_MODE_SEL_t en_fMode,\
                                                          EN_CCx_CHANNEL_SEL_t en_fCh);
/* Function to Enable Interrupt */
static void TCC_InterruptEnable(EN_TCC_SLICE_t en_fSlice,EN_INTERRUPT_SEL_t en_fIntSel,\
							EN_CCx_CHANNEL_SEL_t en_fChnl);
/* Function to Disable TCC */
extern void TCC_Disable(EN_TCC_SLICE_t en_fSlice);


/************************************* TCC Event Functions ****************************************/

/* Function to initialize the TCC Event */
extern void TCC_EventInit(ST_TCC_EVENT_PARAMS_t *p_stfTCCEventParams);

/* Function to Set Period Value */
extern void TCC_SetPeriodValue(EN_TCC_SLICE_t en_fSlice,INT32U u32_fPeriod);

/* Function to Get Period Value */
static INT32U TCC_GetPeriodValue(INT32U u32_fPWMFreqHZ,INT32U u32_fPrescalar,\
                                      INT32U u32_fGCLKFreqHZ);

/************************************* TCC Capture Functions **************************************/

/* Function to Initialize Captrue Event */
extern void TCC_CaptureEventInit(ST_TCC_CAPTURE_PARAMS_t *p_stfTCCCaptureParams);

/* Function to Get Period Value */
static INT32U TCC_GetPeriodValueinTime(INT32F f32_fTimeinMS,INT32U u32_fPrescalar,\
                                INT32U u32_fGCLKFreqHZ, EN_TCC_DELAY_TYPE_t en_fDelayType);

/* Function to read the Capture data */
extern INT32U TCC_ReadCaptureData(EN_TCC_SLICE_t en_fSlice);

/************************************* TCC PWM Functions ******************************************/

/* Function to initialize the TCC */
extern void TCC_PwmInit(ST_TCC_PWM_CONFIG_t *p_stfTCCPwmConfigParams);

/* Function to Set Period Value */
static void TCC_SetPeriodValue(EN_TCC_SLICE_t en_fSlice,INT32U u32_fPeriod);

/* Function to Get DutyCycle */
static INT32F TCC_GetCompareValue(INT32F f32_fDutyCycle,INT32U u32_fPeriod);

/* Function to Set DutyCycle */
static void TCC_SetCompareValue(EN_TCC_SLICE_t en_fSlice,EN_CCx_CHANNEL_SEL_t en_fCh, \
								INT32F f32_fCompval);

/* Function to Upadate DutyCycle */
extern void TCC_UpdateDutyCycle(EN_CCx_CHANNEL_SEL_t en_fCompChNo,INT32F f32_fDutyCycle, \
								INT32U u32_fPWMFreq);

#endif

/**************************************************************************************************/
/* End of TCC.h                                                                                   */
/**************************************************************************************************/
