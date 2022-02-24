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
/*  File Name   : LSM6DSM.c                                                                       */
/*  Author      : NAGANJALI.K                                                                     */
/*  Version 	: v1.0                                                                            */
/*  Date        : 3-11-2021                                                                       */
/*                                                                                                */
/* @Description : LSM6DSM Driver Frame Work                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "SPI.h"
#include "EIC.h"
#include "PLATFORM.h"
#include "GPIO.h"

#include "LSM6DSM.h"
#include "LSM6DSM_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

#define SPI_LSM6DSM_PCS_PIN_LOW  	        ( GPIO_ResetPin(GPIO_PORT_A, GPIO_PIN_18) )
#define SPI_LSM6DSM_PCS_PIN_HIGH	        ( GPIO_SetPin(GPIO_PORT_A, GPIO_PIN_18) )

#define SPI_LSM6DSM_MAG_CS_LOW                  ( GPIO_ResetPin(GPIO_PORT_A, GPIO_PIN_18) )
#define SPI_LSM6DSM_MAG_CS_HIGH                 ( GPIO_SetPin(GPIO_PORT_A, GPIO_PIN_18) )

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Initialization of MISO  Pin  */
ST_GPIO_PARAMS_t st_gLSM6DSMMISOPinConfig = 
{
    .en_mPortSel		=	GPIO_PORT_A,
    .en_mPinSel			=	GPIO_PIN_19,
    .en_mPinDir			=	GPIO_DIR_OUTPUT,
    .en_mPinType		=	GPIO_PULL_LVL_DIS,
    .en_mPinPeriph		=	GPIO_PERIPHERAL_C,
    .en_mDriverStrenght		=	GPIO_DRIV_STRENGTH_NORMAL
};

/* Initialization of ChipSelect pin */
ST_GPIO_PARAMS_t st_gLSM6DSMAccCSConfig = 
{
    .en_mPortSel		=	GPIO_PORT_A,
    .en_mPinSel			=	GPIO_PIN_18,
    .en_mPinDir			=	GPIO_DIR_INPUT,
    .en_mPinType		=	GPIO_IN_PULL_UP,
    .en_mPinPeriph		=	GPIO_PERIPHERAL_C,
    .en_mDriverStrenght		=	GPIO_DRIV_STRENGTH_NORMAL
};

/* Initialization of the MOSI Pin */
ST_GPIO_PARAMS_t st_gLSM6DSMMOSIPinConfig = 
{
    .en_mPortSel		=	GPIO_PORT_A,
    .en_mPinSel			=	GPIO_PIN_16,
    .en_mPinDir			=	GPIO_DIR_INPUT,
    .en_mPinType		=	GPIO_IN_PULL_UP,
    .en_mPinPeriph		=	GPIO_PERIPHERAL_C,
    .en_mDriverStrenght		=	GPIO_DRIV_STRENGTH_NORMAL
};

/* Initialization of SCLK Clock Out Pin */
ST_GPIO_PARAMS_t st_gLSM6DSMSCKPinConfig = 
{
    .en_mPortSel		=	GPIO_PORT_A,
    .en_mPinSel			=	GPIO_PIN_17,
    .en_mPinDir			=	GPIO_DIR_INPUT,
    .en_mPinType		=	GPIO_IN_PULL_UP,
    .en_mPinPeriph		=	GPIO_PERIPHERAL_C,
    .en_mDriverStrenght		=	GPIO_DRIV_STRENGTH_NORMAL
};

/* Configuration for SPI MAster Init */
ST_SPI_MASTER_CONFIG_PARAMS_t st_gLSM6DSMConfigParams = 
{
    .en_mChannel       = SERCOM_CH1,
    .u32_mBaudrate     = 1000000,
    .en_mDataOrder     = SPI_DORD_MSB_FIRST,
    .en_mMISOPadSel    = SPI_MISO_PAD3,
    .en_mMOSIPadSel    = SPI_MOSIPAD0_SCKPAD1_SSPAD2,
    .en_mSSControlSel  = SPI_SS_CONTROLLED_BY_SOFTWARE,
    .en_mClockPhaseSel = SPI_CLOCK_PHASE_CPOL1_CPHA0
};

/* Switch Configuration for PB05 Pin */
ST_GPIO_PARAMS_t st_gLSM6DSMInt1Config = 
{
    .en_mPortSel        = GPIO_PORT_B,
    .en_mPinSel	        = GPIO_PIN_11,
    .en_mPinDir		= GPIO_DIR_INPUT,
    .en_mPinType	= GPIO_PULL_LVL_DIS,
    .en_mPinPeriph  	= GPIO_PERIPHERAL_A,
    .en_mDriverStrenght	= GPIO_DRIV_STRENGTH_NORMAL
      
};

ST_EIC_PARAMS_t st_gLSM6DSMInt1EICConfig =
{
    .en_mInputSense    = EIC_CONFIG_SENSEx_RISE,
    .u32_mExtnlIntNo   = 11,
    .fp_UserHandler    = AccRxExt_Handler,
};

/* Switch Configuration for PB05 Pin */
ST_GPIO_PARAMS_t st_gLSM6DSMInt2Config = 
{
    .en_mPortSel        = GPIO_PORT_B,
    .en_mPinSel	        = GPIO_PIN_10,
    .en_mPinDir		= GPIO_DIR_INPUT,
    .en_mPinType	= GPIO_PULL_LVL_DIS,
    .en_mPinPeriph  	= GPIO_PERIPHERAL_A,
    .en_mDriverStrenght	= GPIO_DRIV_STRENGTH_NORMAL
      
};

ST_EIC_PARAMS_t st_gLSM6DSMInt2EICConfig =
{
    .en_mInputSense    = EIC_CONFIG_SENSEx_RISE,
    .u32_mExtnlIntNo   = 10,
    .fp_UserHandler    = AccRxExt_Handler,
};

/* Structure variable to store the Accelerometer & Gyroscope data */
ST_LSM6DSM_ACC_GYRO_DATA_t st_gLSM6DSMAccGyroData;

INT8U u8_gAcceIntFlag = 0;

INT32U u32_gIMUSensorCount = 0;

/* */
void (*fp_gAcceWakeHandler)(void);

void AccRxExt_Handler(void)
{
  
}

/**************************************************************************************************/
/* Function Name   :                                                                              */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void LSM6DSM_AccelCallBack(INT32U u32_fPinMask)
{
    u8_gAcceIntFlag = 1;
   
    if(fp_gAcceWakeHandler != PNULL)
    {
        fp_gAcceWakeHandler();
    }
    else
    {
        /* No Action */
    }
}

/**************************************************************************************************/
/* Function Name   : EN_LSM6DSM_RESULT_t LSM6DSM_PhysicalInit(void (*fp_fAccelWakeHandler)(void)) */
/*                                                                                                */
/* Description     :   LSM6DSM Physical Init                                                      */
/*                                                                                                */
/* In Params       :    None                                                                      */
/*                                                                                                */
/* Out Params      :    None                                                                      */
/*                                                                                                */
/* Return Value    :   en_lResult                                                                 */
/**************************************************************************************************/

EN_LSM6DSM_RESULT_t LSM6DSM_PhysicalInit(void (*fp_fAccelWakeHandler)(void))
{
    EN_LSM6DSM_RESULT_t en_lResult = LSM6DSM_SUCCESS;
    
    /* Update Wake handler */
    fp_gAcceWakeHandler = fp_fAccelWakeHandler;
      
    /* Configure MOSI Pin */
    GPIO_Init(&st_gLSM6DSMMOSIPinConfig);
    /* Configure MISO Pin */
    GPIO_Init(&st_gLSM6DSMMISOPinConfig);
    /* Configure SCK Pin */
    GPIO_Init(&st_gLSM6DSMSCKPinConfig);
    /* Configure CS Pin */
    GPIO_Init(&st_gLSM6DSMAccCSConfig);

    /* Initializing SPI */
    SPI_MasterInit(&st_gLSM6DSMConfigParams);
  
    /* Chip Select for Acc & Mag */
    SPI_LSM6DSM_PCS_PIN_HIGH;
    SPI_LSM6DSM_MAG_CS_HIGH;  

    en_lResult = LSM6DSM_AccGyroReadDeviceId();

    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   :   void LSM6DSM_EnableInterrupt(void)                                         */
/*                                                                                                */
/* Description     :     LSM6DSM Enabling Interrupt Function                                      */
/*                                                                                                */
/* In Params       :       void                                                                   */
/*                                                                                                */
/* Out Params      :       void                                                                   */
/*                                                                                                */
/* Return Value    :       None                                                                   */
/**************************************************************************************************/

void LSM6DSM_EnableInterrupt(void)
{
    /* COnfigure INT1 Pin */ 
    GPIO_Init(&st_gLSM6DSMInt1Config);
    EIC_Init(&st_gLSM6DSMInt1EICConfig);
}

/**************************************************************************************************/
/* Function Name   :           void LSM6DSM_DisableInterrupt(void)                                */
/*                                                                                                */
/* Description     :         Disable Interrupt                                                    */
/*                                                                                                */
/* In Params       :        void                                                                  */
/*                                                                                                */
/* Out Params      :        void                                                                  */
/*                                                                                                */
/* Return Value    :        None                                                                  */
/**************************************************************************************************/

void LSM6DSM_DisableInterrupt(void)
{
    st_gLSM6DSMInt1EICConfig.en_mInputSense = EIC_CONFIG_SENSEx_NONE;
    st_gLSM6DSMInt2EICConfig.en_mInputSense = EIC_CONFIG_SENSEx_NONE;

    /* COnfigure INT1 Pin */
       /* COnfigure INT1 Pin */ 
    GPIO_Init(&st_gLSM6DSMInt1Config);
    EIC_Init(&st_gLSM6DSMInt1EICConfig);
    
    GPIO_Init(&st_gLSM6DSMInt2Config);
    EIC_Init(&st_gLSM6DSMInt2EICConfig);       
}

/**************************************************************************************************/
/* Function Name   :         EN_LSM6DSM_RESULT_t LSM6DSM_AccelInit(void)                          */
/*                                                                                                */
/* Description     :        LSM6DSM Accelerameter Initialization                                  */
/*                                                                                                */
/* In Params       :          void                                                                */
/*                                                                                                */
/* Out Params      :          void                                                                */
/*                                                                                                */
/* Return Value    :          en_lResult                                                          */
/**************************************************************************************************/

EN_LSM6DSM_RESULT_t LSM6DSM_AccelInit(void)
{
    EN_LSM6DSM_RESULT_t en_lResult = LSM6DSM_SUCCESS;
    
    LSM6DSMDrvTransferByte(LSM6DSM_CTRL5_C);
    LSM6DSMDrvTransferLastByte(0x20);    

    /* Set Accelerometer Output Data Rate to 119 Hz */
    LSM6DSMDrvTransferByte(LSM6DSM_CTRL1_XL);
    LSM6DSMDrvTransferLastByte(0x44);  

    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   :  EN_LSM6DSM_RESULT_t LSM6DSM_ReadAccData(ST_LSM6DSM_ACC_GYRO_DATA_t * \
                                                                                p_stgAccGyroData) */
/*                                                                                                */
/* Description     :        LSM6DSM Read Accelerometer Data                                       */
/*                                                                                                */
/* In Params       :          None                                                                */
/*                                                                                                */
/* Out Params      :          p_stgAccGyroData                                                    */
/*                                                                                                */
/* Return Value    :          en_lResult                                                          */
/**************************************************************************************************/

EN_LSM6DSM_RESULT_t LSM6DSM_ReadAccData(ST_LSM6DSM_ACC_GYRO_DATA_t * p_stgAccGyroData)
{
    EN_LSM6DSM_RESULT_t en_lResult = LSM6DSM_SUCCESS;

    if(LSM6DSM_CheckNewAccDataAvailable())
    {
        /* Read Acceleromter X-Axis Data */
        LSM6DSMDrvTransferByte(0x80 + LSM6DSM_OUT_X_L_XL);
        
        p_stgAccGyroData->s16_mAccX = LSM6DSMDrvTransferByte(LSM6DSM_DUMMY_DATA);
        
        p_stgAccGyroData->s16_mAccX |= LSM6DSMDrvTransferLastByte(LSM6DSM_DUMMY_DATA) << 8;
        
        /* Read Acceleromter Y-Axis Data */
        LSM6DSMDrvTransferByte(0x80 + LSM6DSM_OUT_Y_L_XL);
        
        p_stgAccGyroData->s16_mAccY = LSM6DSMDrvTransferByte(LSM6DSM_DUMMY_DATA);
        
        p_stgAccGyroData->s16_mAccY |= LSM6DSMDrvTransferLastByte(LSM6DSM_DUMMY_DATA) << 8;

        /* Read Acceleromter Z-Axis Data */
        LSM6DSMDrvTransferByte(0x80 + LSM6DSM_OUT_Z_L_XL);
        
        p_stgAccGyroData->s16_mAccZ = LSM6DSMDrvTransferByte(LSM6DSM_DUMMY_DATA);
        
        p_stgAccGyroData->s16_mAccZ |= LSM6DSMDrvTransferLastByte(LSM6DSM_DUMMY_DATA) << 8;
    }
    else
    {   
        en_lResult = LSM6DSM_FAILURE;
    }
    
    return en_lResult;
    
}

/**************************************************************************************************/
/* Function Name   :     INT8U LSM6DSM_CheckAccelIntEnable(void)                                  */
/*                                                                                                */
/* Description     :     Check Accelerometer interrupt                                            */
/*                                                                                                */
/* In Params       :      void                                                                    */
/*                                                                                                */
/* Out Params      :      void                                                                    */
/*                                                                                                */
/* Return Value    :      u8_lData                                                                */
/**************************************************************************************************/

INT8U LSM6DSM_CheckAccelIntEnable(void)
{
    INT8U u8_lData = 0;
    
    LSM6DSMDrvTransferByte(0x80 + LSM6DSM_STATUS_REG);
    
    u8_lData = LSM6DSMDrvTransferLastByte(LSM6DSM_DUMMY_DATA);
    
    if(0xFF != u8_lData)
    {
        if(u8_lData & 0x40)
        {
            u8_lData = 1;
        }
        else
        {   
            u8_lData = 0;
        }
    }
    else
    {
        u8_lData = 0;
    }
    
    return u8_lData;
}

/**************************************************************************************************/
/* Function Name   :     INT8U LSM6DSM_CheckNewAccDataAvailable(void)                             */
/*                                                                                                */
/* Description     :    Chacking New Data available Function                                      */
/*                                                                                                */
/* In Params       :     void                                                                     */
/*                                                                                                */
/* Out Params      :    None                                                                      */
/*                                                                                                */
/* Return Value    :    u8_lData                                                                  */
/**************************************************************************************************/

INT8U LSM6DSM_CheckNewAccDataAvailable(void)
{
    INT8U u8_lData = 0;
     
    LSM6DSMDrvTransferByte(0x80 + LSM6DSM_STATUS_REG);
    
    u8_lData = LSM6DSMDrvTransferLastByte(LSM6DSM_DUMMY_DATA);
    
    if(u8_lData & 0x01)
    {
        u8_lData = 1;
    }
    else
    {   
        u8_lData = 0;
    }
    
    return u8_lData;
}

/**************************************************************************************************/
/* Function Name   :      void LSM6DSM_MotionEnableAcclInt(void)                                  */
/*                                                                                                */
/* Description     :      Accelerometer Motion Enable Interrupt                                   */
/*                                                                                                */
/* In Params       :          void                                                                */
/*                                                                                                */
/* Out Params      :          void                                                                */
/*                                                                                                */
/* Return Value    :          None                                                                 */
/**************************************************************************************************/

void LSM6DSM_MotionEnableAcclInt(void)
{    
    LSM6DSMDrvTransferByte(LSM6DSM_FUNC_CFG_ACCESS);
    LSM6DSMDrvTransferLastByte(0x80);  
    
    LSM6DSMDrvTransferByte(LSM6DSM_SM_THS);
    LSM6DSMDrvTransferLastByte(1); 
    
    LSM6DSMDrvTransferByte(LSM6DSM_FUNC_CFG_ACCESS);
    LSM6DSMDrvTransferLastByte(0x00);
    
    LSM6DSMDrvTransferByte(LSM6DSM_CTRL1_XL);
    LSM6DSMDrvTransferLastByte(0x20);
    
    LSM6DSMDrvTransferByte(LSM6DSM_CTRL10_C);
    LSM6DSMDrvTransferLastByte(0x05);
    
    LSM6DSMDrvTransferByte(LSM6DSM_INT1_CTRL);
    LSM6DSMDrvTransferLastByte(0x40);   
}

/**************************************************************************************************/
/* Function Name   :        void LSM6DSM_TILTINTEnableAcclInt(void)                               */
/*                                                                                                */
/* Description     :        LSM6DSM Tilt Enable Accelerometer Interrupt                           */
/*                                                                                                */
/* In Params       :        void                                                                  */
/*                                                                                                */
/* Out Params      :        void                                                                  */
/*                                                                                                */
/* Return Value    :        None                                                                  */
/**************************************************************************************************/

void LSM6DSM_TILTINTEnableAcclInt(void)
{
    LSM6DSMDrvTransferByte(LSM6DSM_CTRL1_XL);
    LSM6DSMDrvTransferLastByte(0x20);
    
    LSM6DSMDrvTransferByte(LSM6DSM_CTRL10_C);
    LSM6DSMDrvTransferLastByte(0x0C);  
    
    LSM6DSMDrvTransferByte(LSM6DSM_WAKE_MD1_CFG);
    LSM6DSMDrvTransferLastByte(0x02);
}


/**************************************************************************************************/
/* Function Name   :       void LSM6DSM_SingleTapEnableAcclInt(void)                              */
/*                                                                                                */
/* Description     :       LSM6DSM Single Tap Enable Interrupt                                    */
/*                                                                                                */
/* In Params       :       void                                                                   */
/*                                                                                                */
/* Out Params      :       void                                                                   */
/*                                                                                                */
/* Return Value    :       None                                                                   */
/**************************************************************************************************/

void LSM6DSM_SingleTapEnableAcclInt(void)
{
    LSM6DSMDrvTransferByte(LSM6DSM_CTRL1_XL);
    LSM6DSMDrvTransferLastByte(0x60);

    LSM6DSMDrvTransferByte(LSM6DSM_TAP_CFG);
    LSM6DSMDrvTransferLastByte(0x8E);

    LSM6DSMDrvTransferByte(LSM6DSM_TAP_THS_6D);
    LSM6DSMDrvTransferLastByte(0x89);  

    LSM6DSMDrvTransferByte(LSM6DSM_INT_DUR2);
    LSM6DSMDrvTransferLastByte(0x06);

    LSM6DSMDrvTransferByte(LSM6DSM_WAKE_UP_THS);
    LSM6DSMDrvTransferLastByte(0x00);

    LSM6DSMDrvTransferByte(LSM6DSM_WAKE_MD1_CFG);
    LSM6DSMDrvTransferLastByte(0x40);
}

/**************************************************************************************************/
/* Function Name   :     void LSM6DSM_WakeupIntEnable(void)                                       */
/*                                                                                                */
/* Description     :       LSM6DSMTR wakeup Enble Interrupt                                       */
/*                                                                                                */
/* In Params       :        void                                                                  */
/*                                                                                                */
/* Out Params      :        void                                                                  */
/*                                                                                                */
/* Return Value    :        None                                                                  */
/**************************************************************************************************/

void LSM6DSM_WakeupIntEnable(void)
{
    LSM6DSMDrvTransferByte(LSM6DSM_WAKE_UP_DUR);
    LSM6DSMDrvTransferLastByte(0x00);
    
    LSM6DSMDrvTransferByte(LSM6DSM_WAKE_UP_THS);
    LSM6DSMDrvTransferLastByte(0x02);
    
    LSM6DSMDrvTransferByte(LSM6DSM_TAP_CFG);
    LSM6DSMDrvTransferLastByte(0x80);
    
    LSM6DSMDrvTransferByte(LSM6DSM_CTRL1_XL);
    LSM6DSMDrvTransferLastByte(0x40); 
    
    LSM6DSMDrvTransferByte(LSM6DSM_WAKE_MD1_CFG);
    LSM6DSMDrvTransferLastByte(0x20);
}

/**************************************************************************************************/
/* Function Name   :    void AcceEnter_SleepMode(void)                                            */
/*                                                                                                */
/* Description     :    Accelerometer Enter Sleep Mode                                            */
/*                                                                                                */
/* In Params       :    void                                                                      */
/*                                                                                                */
/* Out Params      :    void                                                                      */
/*                                                                                                */
/* Return Value    :    None                                                                      */
/**************************************************************************************************/

void AcceEnter_SleepMode(void)
{
    LSM6DSMDrvTransferByte(LSM6DSM_CTRL1_XL);
    LSM6DSMDrvTransferLastByte(0x00);  
}

/**************************************************************************************************/
/* Function Name   :     void LSM6DSM_DoubleTapEnableAcclInt(void)                                */
/*                                                                                                */
/* Description     :     LSM6DSM Double Tap Interrupt                                             */
/*                                                                                                */
/* In Params       :      void                                                                    */
/*                                                                                                */
/* Out Params      :      void                                                                    */
/*                                                                                                */
/* Return Value    :      None                                                                    */
/**************************************************************************************************/

void LSM6DSM_DoubleTapEnableAcclInt(void)
{
    LSM6DSMDrvTransferByte(LSM6DSM_CTRL1_XL);
    LSM6DSMDrvTransferLastByte(0x60);
    
    LSM6DSMDrvTransferByte(LSM6DSM_TAP_CFG);
    LSM6DSMDrvTransferLastByte(0x8E);
    
    LSM6DSMDrvTransferByte(LSM6DSM_TAP_THS_6D);
    LSM6DSMDrvTransferLastByte(0x8C);
    
    LSM6DSMDrvTransferByte(LSM6DSM_INT_DUR2);
    LSM6DSMDrvTransferLastByte(0x7F);
    
    LSM6DSMDrvTransferByte(LSM6DSM_WAKE_UP_THS);
    LSM6DSMDrvTransferLastByte(0x80);
     
    LSM6DSMDrvTransferByte(LSM6DSM_WAKE_MD1_CFG);
    LSM6DSMDrvTransferLastByte(0x08);
}

/**************************************************************************************************/
/* Function Name   :           void LSM6DSM_ClearInterrupt(void)                                  */
/*                                                                                                */
/* Description     :           LSM6DSMTR Clear Interrupt                                          */
/*                                                                                                */
/* In Params       :           void                                                               */
/*                                                                                                */
/* Out Params      :           void                                                               */
/*                                                                                                */
/* Return Value    :           None                                                               */
/**************************************************************************************************/

void LSM6DSM_ClearInterrupt(void)
{
    LSM6DSMDrvTransferByte(LSM6DSM_INT1_CTRL);
    LSM6DSMDrvTransferLastByte(0x00);  
}

/**************************************************************************************************/
/* Function Name   :        EN_LSM6DSM_RESULT_t LSM6DSM_AccGyroReadDeviceId(void)                 */
/*                                                                                                */
/* Description     :        Accelerometer Read Device ID                                          */
/*                                                                                                */
/* In Params       :        void                                                                  */
/*                                                                                                */
/* Out Params      :        void                                                                  */
/*                                                                                                */
/* Return Value    :        en_lResult                                                            */
/**************************************************************************************************/

EN_LSM6DSM_RESULT_t LSM6DSM_AccGyroReadDeviceId(void)
{
    EN_LSM6DSM_RESULT_t en_lResult = LSM6DSM_SUCCESS;
    
    INT8U u8_lData = 0;
    
    LSM6DSMDrvTransferByte(0x80 + LSM6DSM_WHO_AM_I);
    
    u8_lData = LSM6DSMDrvTransferLastByte(LSM6DSM_DUMMY_DATA);  

    if(LSM6DSM_MANF_ACC_GYRO_ID == u8_lData) 
    {
        en_lResult = LSM6DSM_SUCCESS;
    }
    else
    {   
        en_lResult = LSM6DSM_FAILURE;
    }
    
    return en_lResult;
}


/**************************************************************************************************/
/* Function Name:         INT8U LSM6DSMDrvTransferByte(INT8U u8_fData)                            */
/*                                                                                                */
/* Description	:         LSM6DSMTR Driver Transfer Byte                                          */
/*                                                                                                */
/* Parameter	:         u8_fData                                                                */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                        */
/**************************************************************************************************/

INT8U LSM6DSMDrvTransferByte(INT8U u8_fData)
{
    INT8U u8_lResult = 0;
    
    SPI_LSM6DSM_PCS_PIN_LOW;

    /* Write to Serial Memory */
    SPI_WriteData(st_gLSM6DSMConfigParams.en_mChannel, u8_fData);
    
    /* Receive data */
    u8_lResult = SPI_ReadData(st_gLSM6DSMConfigParams.en_mChannel);	
    
    return u8_lResult;
}


/**************************************************************************************************/
/* Function Name:        INT8U LSM6DSMDrvTransferLastByte(INT8U u8_fData)                         */
/*                                                                                                */
/* Description	:           LSM6DSMTR Driver Transfer Last Byte                                   */
/*                                                                                                */
/* Parameter	:           u8_fData                                                              */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                        */
/**************************************************************************************************/

INT8U LSM6DSMDrvTransferLastByte(INT8U u8_fData)
{
    INT8U u8_lResult = 0;
    
    SPI_LSM6DSM_PCS_PIN_LOW;

    /* Write to Serial Memory */
    SPI_WriteData(st_gLSM6DSMConfigParams.en_mChannel, u8_fData);
    
    /* Receive data */
    u8_lResult = SPI_ReadData(st_gLSM6DSMConfigParams.en_mChannel);	
    
    SPI_LSM6DSM_PCS_PIN_HIGH;
    
    return u8_lResult;
}

/**************************************************************************************************/
/* End of  LSM6DSM.c                                                                              */
/**************************************************************************************************/
