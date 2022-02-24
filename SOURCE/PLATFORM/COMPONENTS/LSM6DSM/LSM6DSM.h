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
/*  File Name   : LSM6DSM.h                                                                       */
/*  Author      : NAGANJALI.K                                                                     */
/*  Version 	: v1.0                                                                            */
/*  Date        : 3-11-2021                                                                       */
/*                                                                                                */
/* @Description : LSM6DSM Driver Frame Work                                                       */
/**************************************************************************************************/

#ifndef _LSM6DSM_H_
#define _LSM6DSM_H_

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

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

extern INT32U u32_gIMUSensorCount;

/* Enum for LSM9DS1 Result */
typedef enum
{       
    LSM6DSM_FAILURE = 0x0,
    LSM6DSM_SUCCESS,
}EN_LSM6DSM_RESULT_t;

typedef struct
{
    INT16S         s16_mAccX;
    INT16S         s16_mAccY;
    INT16S         s16_mAccZ;
    INT16S         s16_mGyroX;
    INT16S         s16_mGyroY;
    INT16S         s16_mGyroZ;    
    
}ST_LSM6DSM_ACC_GYRO_DATA_t;
  
extern INT8U u8_gAcceIntFlag;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function to Initiliaze LSM9DS1 Physical Layer */
extern EN_LSM6DSM_RESULT_t LSM6DSM_PhysicalInit(void (*fp_fAccelWakeHandler)(void));

/* Function to Initialize Accelerometer */
extern EN_LSM6DSM_RESULT_t LSM6DSM_AccelInit(void);

/* Function to Read Accelerometer Data */
extern EN_LSM6DSM_RESULT_t LSM6DSM_ReadAccData(ST_LSM6DSM_ACC_GYRO_DATA_t * p_stgAccGyroData);

/* Function to enable accelerometer interrupt with threshold value */
extern void LSM6DSM_MotionEnableAcclInt(void);

extern void LSM6DSM_TILTINTEnableAcclInt(void);

extern void LSM6DSM_TimeStampEnableAcclInt(void);

extern void LSM6DSM_SingleTapEnableAcclInt(void);

extern void LSM6DSM_DoubleTapEnableAcclInt(void);

extern void LSM6DSM_WakeupIntEnable(void);

/* Function to Read Acc & Gyro Device ID */
extern EN_LSM6DSM_RESULT_t LSM6DSM_AccGyroReadDeviceId(void);

/* Function to check new accelerometer Data available or not */
extern INT8U LSM6DSM_CheckNewAccDataAvailable(void);

/* Function to check new gyroscope Data available or not */
extern INT8U LSM6DSM_CheckNewGyroDataAvailable(void);

/* Function to Transfer data byte */
extern INT8U LSM6DSMDrvTransferByte(INT8U u8_fData);

/* Function to trnasfer last data byte */
extern INT8U LSM6DSMDrvTransferLastByte(INT8U u8_fData);

/* Motion Indication User Call Back function */
extern void LSM6DSM_AccelCallBack(INT32U u32_fPinMask);
  
/* Function to Check Accelerometer interrupt enble or disable */
extern INT8U LSM6DSM_CheckAccelIntEnable(void);

/* Function to configure accelerometer threshold level */
extern INT8U LSM6DSM_ConfigAccelThreshold(INT8U u8_fThreshold, INT8U u8_fAxis, INT8U u8_fDuration, \
                                                                                    INT8U u8_fwait);
/* Function to get accelerometer interrupt source */
extern INT8U LSM6DSM_GetAccelIntSrc(void);

/* Function to clear interrupt */
extern void LSM6DSM_ClearInterrupt(void);

/* */
extern void LSM6DSM_EnableInterrupt(void);

/* */
extern void LSM6DSM_DisableInterrupt(void);

void AccRxExt_Handler(void);

extern void AcceEnter_SleepMode(void);

#endif

/**************************************************************************************************/
/* End of  LSM6DSM.h                                                                              */
/**************************************************************************************************/
