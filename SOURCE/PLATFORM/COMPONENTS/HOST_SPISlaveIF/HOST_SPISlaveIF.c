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
/*  File Name   : HOST_SPISlaveIF.c                                                               */
/*  Author      : NAGANJALI.K                                                                     */
/*  Version 	: v1.0                                                                            */
/*  Date        : 12-02-2022                                                                      */
/*                                                                                                */
/* @Description : HOST_SPISlaveIF Component Frame work                                            */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "SPI.h"
#include "GPIO.h"
#include "UART.h"
#include "ADC_SCOPE.h"
#include "DATACONV.h"

#include "HOST_SPISlaveIF.h"
#include "HOST_SPISlaveIF_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* One time Flag global variable */
INT8U u8_gOTAFlag = 0;

INT8U u8_gSPIRxBuff[SPI_SLAVEIF_BUFFER_SIZE] = {0, };
INT32U u32_gSPIRxIndex = 0;

/* Data Buffer Index Variables */
INT16U u16_gDataBuff1OffsetIndex = 0;
INT16U u16_gDataBuff2OffsetIndex = 0;

/* Global Data buffers */
INT8U u8_gDataBuffer1[DATA_BUFFER1] = {0, };
INT8U u8_gDataBuffer2[DATA_BUFFER2] = {0, };

/* Timer Counter Variable */
INT32U u32_gTimerCouter = 0;

/* Ping & Pong Buffer  Variables */
INT8U *p_gu8PingBuffer = 0;
INT8U *p_gu8PongBuffer = 0;

/* Global  variable for SPI States */
EN_SPI_SLAVE_STATES_t en_gCurrentSatate = SLAVE_IDLE;

/* SPI Slave Rx Buffer Flag */
INT8U u8_gSPISlaveIFRxFlag  = 0;

void UART_RXHandler_R(INT8U u8_fData)
{
    UART_TransmitChar(SERCOM_CH_0, u8_fData);
}

/* */
ST_UART_CONFIG_PARAMS_t st_gUartChannelConfig = 
{
    .en_mSERCOMChnl	= SERCOM_CH_0,
    .en_mDataBits	= USART_CH_SIZE_8_BITS,
    .en_mStopBits	= USART_ONE_STOP_BIT,
    .en_mParity		= USART_PARITY_DISABLE,
    .u32_mBaudrate	= 3000000,
    .en_mTXPad		= SERCOM_TX_PAD0,
    .en_mRXPad		= SERCOM_RX_PAD1,
    .fp_USERHANDLER	= UART_RXHandler_R,
    
};

/* Port Configuration for UART RX */
ST_GPIO_PARAMS_t p_stgGpioUartTxPin = 
{
    .en_mPortSel        = GPIO_PORT_A,
    .en_mPinSel	        = GPIO_PIN_4,    
    .en_mPinDir	        = GPIO_DIR_OUTPUT,
    .en_mPinType        = GPIO_PULL_LVL_DIS,
    .en_mPinPeriph      = GPIO_PERIPHERAL_D,
    .en_mDriverStrenght	= GPIO_DRIV_STRENGTH_NORMAL
};

/* Port Configuration for UART RX */
ST_GPIO_PARAMS_t p_stgGpioUartRxPin = 
{
  .en_mPortSel		= GPIO_PORT_A,
  .en_mPinSel		= GPIO_PIN_5,    
  .en_mPinDir		= GPIO_DIR_INPUT,
  .en_mPinType		= GPIO_PULL_LVL_DIS,
  .en_mPinPeriph	= GPIO_PERIPHERAL_D,
  .en_mDriverStrenght	= GPIO_DRIV_STRENGTH_NORMAL
    
};

/* Initialization of MISO  Pin  */
ST_GPIO_PARAMS_t st_gSlaveSercom1MISOPinParams = 
{
    .en_mPortSel		=	GPIO_PORT_A,
    .en_mPinSel			=	GPIO_PIN_19,
    .en_mPinDir			=	GPIO_DIR_OUTPUT,
    .en_mPinType		=	GPIO_PULL_LVL_DIS,
    .en_mPinPeriph		=	GPIO_PERIPHERAL_C,
    .en_mDriverStrenght		=	GPIO_DRIV_STRENGTH_NORMAL
};

/* Initialization of ChipSelect pin */
ST_GPIO_PARAMS_t st_gSlaveSercom1CSPinParams = 
{
    .en_mPortSel		=	GPIO_PORT_A,
    .en_mPinSel			=	GPIO_PIN_18,
    .en_mPinDir			=	GPIO_DIR_INPUT,
    .en_mPinType		=	GPIO_IN_PULL_UP,
    .en_mPinPeriph		=	GPIO_PERIPHERAL_C,
    .en_mDriverStrenght		=	GPIO_DRIV_STRENGTH_NORMAL
};

/* Initialization of the MOSI Pin */
ST_GPIO_PARAMS_t st_gSlaveSercom1MOSIPinParams = 
{
    .en_mPortSel		=	GPIO_PORT_A,
    .en_mPinSel			=	GPIO_PIN_16,
    .en_mPinDir			=	GPIO_DIR_INPUT,
    .en_mPinType		=	GPIO_IN_PULL_UP,
    .en_mPinPeriph		=	GPIO_PERIPHERAL_C,
    .en_mDriverStrenght		=	GPIO_DRIV_STRENGTH_NORMAL
};

/* Initialization of SCLK Clock Out Pin */
ST_GPIO_PARAMS_t st_gSlaveSercom1SCLKPinParams = 
{
    .en_mPortSel		=	GPIO_PORT_A,
    .en_mPinSel			=	GPIO_PIN_17,
    .en_mPinDir			=	GPIO_DIR_INPUT,
    .en_mPinType		=	GPIO_IN_PULL_UP,
    .en_mPinPeriph		=	GPIO_PERIPHERAL_C,
    .en_mDriverStrenght		=	GPIO_DRIV_STRENGTH_NORMAL
};

/* Configuration for SPI MAster Init */
ST_SPI_MASTER_CONFIG_PARAMS_t st_gSercom1SlaveInitParams = 
{
    .en_mChannel = SERCOM_CH1,
    .u32_mBaudrate = 20000000,
    .en_mDataOrder = SPI_DORD_MSB_FIRST,
    .en_mMISOPadSel = SPI_MISO_PAD0,
    .en_mMOSIPadSel = SPI_MOSIPAD3_SCKPAD1_SSPAD2,
    .en_mSSControlSel = SPI_SS_CONTROLLED_BY_HARDWARE,
    .en_mClockPhaseSel = SPI_CLOCK_PHASE_CPOL1_CPHA1,
    .fp_USERHANDLER   = SPI_RxHandler
};

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

void SPI_RxHandler(INT8U u8_fSPISlaveRxData)
{                     
    u8_gSPIRxBuff[u32_gSPIRxIndex] = u8_fSPISlaveRxData;
    u32_gSPIRxIndex = u32_gSPIRxIndex + 1;
    
    u8_gSPISlaveIFRxFlag = 1;
    
    if(u32_gSPIRxIndex >= SPI_SLAVEIF_BUFFER_SIZE)
    {
        u32_gSPIRxIndex = 0;
    }
    else
    {
        /* No Action */
    }
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

void Scope_WriteAnalogData(INT8U * pu8_fData)
{
    pu8_fData[0] = '@';
    COMMON_HWord2PAN(&pu8_fData[1], u16_gAdcValue1);
    COMMON_HWord2PAN(&pu8_fData[5], u16_gAdcValue2);
    COMMON_HWord2PAN(&pu8_fData[9], u16_gAdcValue3);
    COMMON_HWord2PAN(&pu8_fData[13], u16_gAdcValue4);
    COMMON_HWord2PAN(&pu8_fData[17], u16_gAdcValue5);
    pu8_fData[21] = '#';
    
    for(INT32U u32_lIndex = 0; u32_lIndex < 22; u32_lIndex++)
    {
        TransferByte(SERCOM_CH1, pu8_fData[u32_lIndex]);
    }
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

void Logger_Init(void)
{
    GPIO_Init(&p_stgGpioUartTxPin);
    GPIO_Init(&p_stgGpioUartRxPin);
    UART_Init(&st_gUartChannelConfig);
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

void HOST_SPISlaveIFInit(void)
{
     /* Configuration of MISO pin */
    GPIO_Init(&st_gSlaveSercom1MISOPinParams);

    /* Configuration of CS pin */
    GPIO_Init(&st_gSlaveSercom1CSPinParams);

    /* Configuration of MOSI Pin */
    GPIO_Init(&st_gSlaveSercom1MOSIPinParams);

    /* Configuration of SCLK Clock Out Pin */
    GPIO_Init(&st_gSlaveSercom1SCLKPinParams);

    /* Initializing SPI */
    SPI_SlaveInit(&st_gSercom1SlaveInitParams);
	
    Logger_Init();
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

void SPISlaveIF_Handler(void)
{    
    /* State Machine */
    switch(en_gCurrentSatate)
    {
        case SLAVE_IDLE:
        {
            HOST_SPISlaveIF_IdleHandler(&en_gCurrentSatate);
        }
        break;
        
        case SLAVE_REQUESTDATA:
        {
            HOST_SPISlaveIF_RequestDataHandler(&en_gCurrentSatate);
        }
        break;
        
        case SLAVE_TRASFERDATA:
        {
            HOST_SPISlaveIF_TansferDataHandler(&en_gCurrentSatate);
        }
        break;
        
        default:
        break;
    }
    
    if(1 == u8_gSPISlaveIFRxFlag)
    {
        u8_gSPISlaveIFRxFlag = 0;    
        
        if(1 == u8_gAnalogEOC)
        {
            u8_gAnalogEOC = 0;

            if(u16_gDataBuff1OffsetIndex >= DATA_BUFFER1)
            {
                u16_gDataBuff1OffsetIndex = 0;
            }
            else
            {
                Scope_WriteAnalogData(&u8_gDataBuffer1[u16_gDataBuff1OffsetIndex]);

                u16_gDataBuff1OffsetIndex = u16_gDataBuff1OffsetIndex + 22;
            }
        }
        else
        {
            /* No Action */
        }
        
    }
    else
    {
        /* No Action */
    }
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

void HOST_SPISlaveIF_IdleHandler(EN_SPI_SLAVE_STATES_t *pen_fState)
{
    if(1 == u8_gOTAFlag)
    {
        /* TO DO */
      
        u8_gOTAFlag = 0;
    }
    else
    {
        /* No Action */
    }
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

void HOST_SPISlaveIF_RequestDataHandler(EN_SPI_SLAVE_STATES_t *pen_fState)
{
    if(1 == u8_gOTAFlag)
    {
        /* TO DO */
        u8_gOTAFlag = 0;
    }
    else
    {
        /* No Action */
    }
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

void HOST_SPISlaveIF_TansferDataHandler(EN_SPI_SLAVE_STATES_t *pen_fState)
{
    if(1 == u8_gOTAFlag)
    {
        /* TO DO */
      
        u8_gOTAFlag = 0;
    }
    else
    {
        /* No Action*/
    }
}

/**************************************************************************************************/
/* End of  HOST_SPISlaveIF.c                                                                      */
/**************************************************************************************************/
