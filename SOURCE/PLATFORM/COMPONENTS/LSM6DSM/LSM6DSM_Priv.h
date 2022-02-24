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
/*  File Name   : LSM6DSM_Priv.h                                                                  */
/*  Author      : NAGANJALI.K                                                                     */
/*  Version 	: v1.0                                                                            */
/*  Date        : 3-11-2021                                                                       */
/*                                                                                                */
/* @Description : LSM6DSM Driver Frame Work                                                       */
/**************************************************************************************************/

#ifndef _LSM6DSM_PRIV_H_
#define _LSM6DSM_PRIV_H_

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

typedef volatile unsigned char          SYS_BYTE_REG;

#define LSM6DSM_MANF_ACC_GYRO_ID        ( 0x6A )        
#define LSM6DSM_MAG_DEVICE_ID           ( 0x3D )  

#define LSM6DSM_DUMMY_DATA              ( 0xFF )

#define LSM6DSM_FUNC_CFG_ACCESS                 ( 0x01 )
#define LSM6DSM_SENSOR_SYNC_TIME_FRAME          ( 0x04 )
#define LSM6DSM_SENSOR_SYNC_RES_RATIO           ( 0x05 )
#define LSM6DSM_FIFO_CTRL1                      ( 0x06 )
#define LSM6DSM_FIFO_CTRL2                      ( 0x07 )
#define LSM6DSM_FIFO_CTRL3                      ( 0x08 )
#define LSM6DSM_FIFO_CTRL4                      ( 0x09 )
#define LSM6DSM_FIFO_CTRL5                      ( 0x0A )
#define LSM6DSM_DRDY_PULSE_CFG                  ( 0x0B )
#define LSM6DSM_INT1_CTRL                       ( 0x0D )
#define LSM6DSM_INT2_CTRL                       ( 0x0E )
#define LSM6DSM_WHO_AM_I                        ( 0x0F )
#define LSM6DSM_CTRL1_XL                        ( 0x10 )
#define LSM6DSM_CTRL2_G                         ( 0x11 )
#define LSM6DSM_CTRL3_C                         ( 0x12 )
#define LSM6DSM_CTRL4_C                         ( 0x13 )
#define LSM6DSM_CTRL5_C                         ( 0x14 )
#define LSM6DSM_CTRL6_C                         ( 0x15 )
#define LSM6DSM_CTRL7_C                         ( 0x16 )
#define LSM6DSM_CTRL8_XL                        ( 0x17 )
#define LSM6DSM_CTRL9_XL                        ( 0x18 )
#define LSM6DSM_CTRL10_C                        ( 0x19 )
#define LSM6DSM_MASTER_CONFIG                   ( 0x1A )
#define LSM6DSM_WAKE_UP_SRC                     ( 0x1B )
#define LSM6DSM_TAP_SRC                         ( 0x1C )
#define LSM6DSM_D6D_SRC                         ( 0x1D )
#define LSM6DSM_STATUS_REG                      ( 0x1E )
#define LSM6DSM_OUT_TEMP_L                      ( 0x20 )
#define LSM6DSM_OUT_TEMP_H                      ( 0x21 )
#define LSM6DSM_OUT_X_L_G                        ( 0x22 )
#define LSM6DSM_OUT_X_H_G                        ( 0x23 )
#define LSM6DSM_OUT_Y_L_G                        ( 0x24 )
#define LSM6DSM_OUT_Y_H_G                        ( 0x25 )
#define LSM6DSM_OUT_Z_L_G                        ( 0x26 )
#define LSM6DSM_OUT_Z_H_G                        ( 0x27 )
#define LSM6DSM_OUT_X_L_XL                       ( 0x28 )
#define LSM6DSM_OUT_X_H_XL                       ( 0x29 )
#define LSM6DSM_OUT_Y_L_XL                       ( 0x2A )
#define LSM6DSM_OUT_Y_H_XL                       ( 0x2B )
#define LSM6DSM_OUT_Z_L_XL                       ( 0x2C )
#define LSM6DSM_OUT_Z_H_XL                       ( 0x2D )

#define LSM6DSM_SENSORHUB1_REG                   ( 0x2E )
#define LSM6DSM_SENSORHUB2_REG                   ( 0x2F )
#define LSM6DSM_SENSORHUB3_REG                   ( 0x30 )
#define LSM6DSM_SENSORHUB4_REG                   ( 0x31 )
#define LSM6DSM_SENSORHUB5_REG                   ( 0x32 )
#define LSM6DSM_SENSORHUB6_REG                   ( 0x33 )
#define LSM6DSM_SENSORHUB7_REG                   ( 0x34 )
#define LSM6DSM_SENSORHUB8_REG                   ( 0x35 )
#define LSM6DSM_SENSORHUB9_REG                   ( 0x36 )
#define LSM6DSM_SENSORHUB10_REG                  ( 0x37 )
#define LSM6DSM_SENSORHUB11_REG                  ( 0x38 )
#define LSM6DSM_SENSORHUB12_REG                  ( 0x39 )

#define LSM6DSM_FIFO_STATUS1                     ( 0x3A )
#define LSM6DSM_FIFO_STATUS2                     ( 0x3B )
#define LSM6DSM_FIFO_STATUS3                     ( 0x3C )
#define LSM6DSM_FIFO_STATUS4                     ( 0x3D )
#define LSM6DSM_FIFO_DATA_OUT_L                  ( 0x3E )
#define LSM6DSM_FIFO_DATA_OUT_H                  ( 0x3F )
#define LSM6DSM_TIMESTAMP0_REG                   ( 0x40 )
#define LSM6DSM_TIMESTAMP1_REG                   ( 0x41 )
#define LSM6DSM_TIMESTAMP2_REG                   ( 0x42 )
#define LSM6DSM_STEP_TIMESTAMP_L                 ( 0x49 )
#define LSM6DSM_STEP_TIMESTAMP_H                 ( 0x4A )
#define LSM6DSM_STEP_COUNTER_L                   ( 0x4B )
#define LSM6DSM_STEP_COUNTER_H                   ( 0x4C )

#define LSM6DSM_SENSORHUB13_REG                  ( 0x4D )
#define LSM6DSM_SENSORHUB14_REG                  ( 0x4E )
#define LSM6DSM_SENSORHUB15_REG                  ( 0x4F )
#define LSM6DSM_SENSORHUB16_REG                  ( 0x50 )
#define LSM6DSM_SENSORHUB17_REG                  ( 0x51 )
#define LSM6DSM_SENSORHUB18_REG                  ( 0x52 )

#define LSM6DSM_FUNC_SRC                         ( 0x53 )
#define LSM6DSM_TAP_CFG                          ( 0x58 )
#define LSM6DSM_TAP_THS_6D                       ( 0x59 )
#define LSM6DSM_INT_DUR2                         ( 0x5A )
#define LSM6DSM_WAKE_UP_THS                      ( 0x5B )
#define LSM6DSM_WAKE_UP_DUR                      ( 0x5C )
#define LSM6DSM_WAKE_FREE_FALL                   ( 0x5D )
#define LSM6DSM_WAKE_MD1_CFG                     ( 0x5E )
#define LSM6DSMWAKE_MD2_CFG                      ( 0x5F )
#define WAKE_MASTER_CMD_CODE                     ( 0x60 )
#define WAKE_SENS_SYNC_SPI_ERROR_CODE            ( 0x61 )

#define LSM6DSM_OUT_MAG_RAW_X_L                  ( 0x66 )
#define LSM6DSM_OUT_MAG_RAW_X_H                  ( 0x67 )
#define LSM6DSM_OUT_MAG_RAW_Y_L                  ( 0x68 )
#define LSM6DSM_OUT_MAG_RAW_Y_H                  ( 0x69 )
#define LSM6DSM_OUT_MAG_RAW_Z_L                  ( 0x6A )

#define LSM6DSM_INT_OIS                          ( 0x6F )
#define LSM6DSM_CTRL_OIS                         ( 0x70 )
#define LSM6DSM_CTRL2_OIS                        ( 0x71 )
#define LSM6DSM_CTRL3_OIS                        ( 0x72 )
#define LSM6DSM_X_OFS_USR                        ( 0x73 )
#define LSM6DSM_Y_OFS_USR                        ( 0x74 )
#define LSM6DSM_Z_OFS_USR                        ( 0x75 )

#define  LSM6DSM_SM_THS                          ( 0x13 )

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

/* Structure for Magnetic sensor Register Address  */
typedef struct
{
    SYS_BYTE_REG        OFFSET_X_REG_L_M;
    SYS_BYTE_REG        OFFSET_X_REG_H_M;
    SYS_BYTE_REG        OFFSET_Y_REG_L_M;
    SYS_BYTE_REG        OFFSET_Y_REG_H_M;
    SYS_BYTE_REG        OFFSET_Z_REG_L_M;
    SYS_BYTE_REG        OFFSET_Z_REG_H_M;
    SYS_BYTE_REG        RESERVED1[3];
    SYS_BYTE_REG        WHO_AM_I;
    SYS_BYTE_REG        RESERVED2[15];
    SYS_BYTE_REG        CTRL_REG1_M;
    SYS_BYTE_REG        CTRL_REG2_M;
    SYS_BYTE_REG        CTRL_REG3_M;
    SYS_BYTE_REG        CTRL_REG4_M;
    SYS_BYTE_REG        CTRL_REG5_M;
    SYS_BYTE_REG        RESERVED3[2];
    SYS_BYTE_REG        STATUS_REG_M;
    SYS_BYTE_REG        OUT_X_L_M;
    SYS_BYTE_REG        OUT_X_H_M;
    SYS_BYTE_REG        OUT_Y_L_M;
    SYS_BYTE_REG        OUT_Y_H_M;
    SYS_BYTE_REG        OUT_Z_L_M;
    SYS_BYTE_REG        OUT_Z_H_M;
    SYS_BYTE_REG        RESERVED4[2];
    SYS_BYTE_REG        INT_CFG_M;
    SYS_BYTE_REG        INT_SRC_M;
    SYS_BYTE_REG        INT_THS_L_M;
    SYS_BYTE_REG        INT_THS_H_M;
    
}ST_LSM6DSM_MAG_REGS_t;

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

#endif

/**************************************************************************************************/
/* End of  LSM6DSM_Priv.h                                                                         */
/**************************************************************************************************/
