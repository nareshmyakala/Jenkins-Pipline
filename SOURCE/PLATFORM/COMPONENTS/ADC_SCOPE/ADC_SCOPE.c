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
/* \File Name   : ADC_SCOPE.c                                                                     */
/* \Author      : SANTHOSH                                                                        */
/* \Version 	:                                                                                 */
/* \Date        : 27-09-2018                                                                      */
/*                                                                                                */
/* @Description : ADC scope Frame work                                                            */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "ADC.h"
#include "TC.h"
#include "UART.h"
#include "GPIO.h"
#include "NVMCTRL.h"

#include "ADC_SCOPE.h"
#include "ADC_SCOPE_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

#define MAXADC_MAF_BUFFER ( 16 )

#define MAX_SCOPE_QUEUE_SIZE        ( 120 )

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Analog EOC Flag */
INT8U u8_gAnalogEOC = 0;

/* Pin Configuratioin for AIN0 (PA02)*/
const ST_GPIO_PARAMS_t st_gADC0Ch1PinParams =
{
	.en_mPortSel	 	= GPIO_PORT_A,
	.en_mPinSel	 		= GPIO_PIN_3,
	.en_mPinDir	 		= GPIO_DIR_INPUT,
	.en_mPinType	 	= GPIO_PULL_LVL_DIS,
	.en_mPinPeriph	 	= GPIO_PERIPHERAL_B,
	.en_mDriverStrenght	= GPIO_DRIV_STRENGTH_STRONG
};

/* Pin Configuratioin for AIN0 (PA02)*/
const ST_GPIO_PARAMS_t st_gADC0Ch6PinParams =
{
	.en_mPortSel	 	= GPIO_PORT_A,
	.en_mPinSel	 		= GPIO_PIN_6,
	.en_mPinDir	 		= GPIO_DIR_INPUT,
	.en_mPinType	 	= GPIO_PULL_LVL_DIS,
	.en_mPinPeriph	 	= GPIO_PERIPHERAL_B,
	.en_mDriverStrenght	= GPIO_DRIV_STRENGTH_STRONG
};

/* Pin Configuratioin for AIN0 (PA02)*/
const ST_GPIO_PARAMS_t st_gADC0Ch7PinParams =
{
	.en_mPortSel	 	= GPIO_PORT_A,
	.en_mPinSel	 		= GPIO_PIN_7,
	.en_mPinDir	 		= GPIO_DIR_INPUT,
	.en_mPinType	 	= GPIO_PULL_LVL_DIS,
	.en_mPinPeriph	 	= GPIO_PERIPHERAL_B,
	.en_mDriverStrenght	= GPIO_DRIV_STRENGTH_STRONG
};

/* Pin Configuratioin for AIN0 (PA02)*/
const ST_GPIO_PARAMS_t st_gADC1Ch8PinParams =
{
	.en_mPortSel	 	= GPIO_PORT_B,
	.en_mPinSel	 		= GPIO_PIN_6,
	.en_mPinDir	 		= GPIO_DIR_INPUT,
	.en_mPinType	 	= GPIO_PULL_LVL_DIS,
	.en_mPinPeriph	 	= GPIO_PERIPHERAL_B,
	.en_mDriverStrenght	= GPIO_DRIV_STRENGTH_STRONG
};

/* Pin Configuratioin for AIN0 (PA02)*/
const ST_GPIO_PARAMS_t st_gADC1Ch9PinParams =
{
	.en_mPortSel	 	= GPIO_PORT_B,
	.en_mPinSel	 		= GPIO_PIN_7,
	.en_mPinDir	 		= GPIO_DIR_INPUT,
	.en_mPinType	 	= GPIO_PULL_LVL_DIS,
	.en_mPinPeriph	 	= GPIO_PERIPHERAL_B,
	.en_mDriverStrenght	= GPIO_DRIV_STRENGTH_STRONG
};

/* Configuration of ADC AIN0 */
const ST_ADC_PARAMS_t  st_gADC0Ch1Params = 
{	
	.en_mADCModule		= ADC_0,
	.en_mADCChannel 	= ADC_CH1,
	.en_mADCSample		= ADC_1_SAMPLE,
	.u8_mSampleTimeLen  = 3,
	.en_mADCResolution  = ADC_12BIT_RESOLUTION,
	.en_mADCPrescalar 	= ADC_DIV_8,
	.fp_ADCUserHandler 	= ADC0_Ch1UserHandler
};

/* Configuration of ADC AIN0 */
const ST_ADC_PARAMS_t  st_gADC0Ch6Params = 
{	
	.en_mADCModule		= ADC_0,
	.en_mADCChannel 	= ADC_CH6,
	.en_mADCSample		= ADC_1_SAMPLE,
	.u8_mSampleTimeLen  = 3,
	.en_mADCResolution  = ADC_12BIT_RESOLUTION,
	.en_mADCPrescalar 	= ADC_DIV_8,
	.fp_ADCUserHandler 	= ADC0_Ch6UserHandler
};

/* Configuration of ADC AIN0 */
const ST_ADC_PARAMS_t  st_gADC0Ch7Params = 
{	
	.en_mADCModule		= ADC_0,
	.en_mADCChannel 	= ADC_CH7,
	.en_mADCSample		= ADC_1_SAMPLE,
	.u8_mSampleTimeLen  = 3,
	.en_mADCResolution  = ADC_12BIT_RESOLUTION,
	.en_mADCPrescalar 	= ADC_DIV_8,
	.fp_ADCUserHandler 	= ADC0_Ch7UserHandler
};

/* Configuration of ADC AIN0 */
const ST_ADC_PARAMS_t  st_gADC1Ch8Params = 
{	
	.en_mADCModule		= ADC_1,
	.en_mADCChannel 	= ADC_CH8,
	.en_mADCSample		= ADC_1_SAMPLE,
	.u8_mSampleTimeLen  = 3,
	.en_mADCResolution  = ADC_12BIT_RESOLUTION,
	.en_mADCPrescalar 	= ADC_DIV_8,
	.fp_ADCUserHandler 	= ADC1_Ch8UserHandler
};

/* Configuration of ADC AIN0 */
const ST_ADC_PARAMS_t  st_gADC1Ch9Params = 
{	
	.en_mADCModule		= ADC_1,
	.en_mADCChannel 	= ADC_CH9,
	.en_mADCSample		= ADC_1_SAMPLE,
	.u8_mSampleTimeLen  = 3,
	.en_mADCResolution  = ADC_12BIT_RESOLUTION,
	.en_mADCPrescalar 	= ADC_DIV_8,
	.fp_ADCUserHandler 	= ADC1_Ch9UserHandler
};

/* Timer Configuration */
const ST_TC_EVENT_PARAMS_t st_gADCTimer =
{
    .en_mTCSlice = TC_SLICE_0,
    .en_mDelayType = TC_DELAY_US,              
    .u32_mTime = 40,
    .fp_User_Handler = ADCSCOPE_TimerHandler
};

/* Variables for to Store the 100 Samples Calibrtaed Values */
double f32_gChanne11Factor = 1024.0;
double f32_gChanne12Factor = 1024.0;
double f32_gChanne13Factor = 1024.0;
double f32_gChanne14Factor = 1024.0;
double f32_gChanne15Factor = 1024.0;

/* Adc Scope Queue Buffer  */
INT16U au16_gScopeQueue[5][MAX_SCOPE_QUEUE_SIZE] = {0, };

/* Buffers for to Store the MAF Applied Data for Each Channel */
INT16U u16_gAdcCh1Data[MAXADC_MAF_BUFFER] = {0,};
INT16U u16_gAdcCh2Data[MAXADC_MAF_BUFFER] = {0,};
INT16U u16_gAdcCh3Data[MAXADC_MAF_BUFFER] = {0,};
INT16U u16_gAdcCh4Data[MAXADC_MAF_BUFFER] = {0,};
INT16U u16_gAdcCh5Data[MAXADC_MAF_BUFFER] = {0,};

/* Queue Control Variables  */
INT8U u8_gScopeQueueFront = 0;
INT8U u8_gScopeQueueRare = 0;
INT8U u8_gScopeQueueAvail = 0;

/* varibale for to Triger the Channels Inidividually */
INT8U u8_gTringgerCounter = 0;

/**************************************************************************************************/
/* Function Name   : void ADC_AIN_USERHANDLER(void)                                               */
/*                                                                                                */
/* Description     : ADC UserHandler                                                              */
/*                                                                                                */
/**************************************************************************************************/
INT16U u16_gAdcValue1 = 0;
    
void ADC0_Ch1UserHandler(void)
{
    u16_gAdcValue1 =  ADCSCOPE_Ch1MAF16(ADC_GetResult(ADC_0));
    
  //  ADCSCOPE_QueueWrite(0, (INT16U)((INT32U)(u16_lAdcValue1 * f32_gChanne11Factor) >> 10));
}

/**************************************************************************************************/
/* Function Name   : void ADC_AIN_USERHANDLER(void)                                               */
/*                                                                                                */
/* Description     : ADC UserHandler                                                              */
/*                                                                                                */
/**************************************************************************************************/

INT16U u16_gAdcValue2 = 0;
void ADC1_Ch9UserHandler(void)
{
    u16_gAdcValue2 =  ADCSCOPE_Ch2MAF16(ADC_GetResult(ADC_1));
    
 //   ADCSCOPE_QueueWrite(1, (INT16U)((INT32U)(u16_lAdcValue2 * f32_gChanne12Factor) >> 10));
}

/**************************************************************************************************/
/* Function Name   : void ADC_AIN_USERHANDLER(void)                                               */
/*                                                                                                */
/* Description     : ADC UserHandler                                                              */
/*                                                                                                */
/**************************************************************************************************/
  
INT16U u16_gAdcValue3 = 0;

void ADC1_Ch8UserHandler(void)
{
    u16_gAdcValue3 =  ADCSCOPE_Ch3MAF16(ADC_GetResult(ADC_1));
    
  //  ADCSCOPE_QueueWrite(2, (INT16U)((INT32U)(u16_lAdcValue3 * f32_gChanne13Factor) >> 10));
}

/**************************************************************************************************/
/* Function Name   : void ADC_AIN_USERHANDLER(void)                                               */
/*                                                                                                */
/* Description     : ADC UserHandler                                                              */
/*                                                                                                */
/**************************************************************************************************/

INT16U u16_gAdcValue4 = 0;

void ADC0_Ch7UserHandler(void)
{   
    u16_gAdcValue4 =  ADCSCOPE_Ch4MAF16(ADC_GetResult(ADC_0));
    
   // ADCSCOPE_QueueWrite(3, (INT16U)((INT32U)(u16_lAdcValue4 * f32_gChanne14Factor) >> 10));
}

/**************************************************************************************************/
/* Function Name   : void ADC_AIN_USERHANDLER(void)                                               */
/*                                                                                                */
/* Description     : ADC UserHandler                                                              */
/*                                                                                                */
/**************************************************************************************************/
INT16U u16_gAdcValue5 = 0;
    
void ADC0_Ch6UserHandler(void)
{	
    u16_gAdcValue5 =  ADCSCOPE_Ch5MAF16(ADC_GetResult(ADC_0));
     
    u8_gAnalogEOC = 1;

   // ADCSCOPE_QueueWrite(4, (INT16U)((INT32U)(u16_lAdcValue5 * f32_gChanne15Factor) >> 10));
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

void ADCSCOPE_TimerHandler(void)
{
    /* */
    switch(u8_gTringgerCounter)
    {
    case 0:
        ADC_Trigger(ADC_0, ADC_CH1, ADC_START_CONVERSION);
        u8_gTringgerCounter = 1;
        break;
    case 1:
        ADC_Trigger(ADC_1, ADC_CH9, ADC_START_CONVERSION);
        u8_gTringgerCounter = 2;
        break;
    case 2:
        ADC_Trigger(ADC_1, ADC_CH8, ADC_START_CONVERSION);
        u8_gTringgerCounter = 3;
        break;
    case 3:
        ADC_Trigger(ADC_0, ADC_CH7, ADC_START_CONVERSION);
        u8_gTringgerCounter = 4;
        break;
    case 4:
        ADC_Trigger(ADC_0, ADC_CH6, ADC_START_CONVERSION);
        u8_gTringgerCounter = 0;
        break;
    }
}

/**************************************************************************************************/
/* Function Name   : INT16U ADCSCOPE_Ch1MAF16(INT16U u16_fInPut)                                  */
/*                                                                                                */
/* Description     : 16Bit MAF apply                                                              */
/*                                                                                                */
/* In Params       : u16_fInPut                                                                   */
/*                                                                                                */
/* Out Params      : NO                                                                           */
/*                                                                                                */
/* Return Value    : u16_lMAF16Value                                                              */
/**************************************************************************************************/

INT16U ADCSCOPE_Ch1MAF16(INT16U u16_fInPut)
{
    INT32U u32_lAccVal = 0;
    INT16U u16_lMAF16Value = 0;
    INT8U u8_lIndex = 0;

    for(u8_lIndex = (MAXADC_MAF_BUFFER - 1); u8_lIndex > 0; u8_lIndex--)
    {
        u16_gAdcCh1Data[u8_lIndex] = u16_gAdcCh1Data[u8_lIndex - 1];
    }
    
    u16_gAdcCh1Data[0] = u16_fInPut;
    
    for(u8_lIndex = 0; u8_lIndex < MAXADC_MAF_BUFFER; u8_lIndex++)
    {
        u32_lAccVal = u32_lAccVal + u16_gAdcCh1Data[u8_lIndex];
    }
    
    u16_lMAF16Value = (INT16U)(u32_lAccVal >> 4);
    
    return u16_lMAF16Value;
}

/**************************************************************************************************/
/* Function Name   : INT16U ADCSCOPE_Ch2MAF16(INT16U u16_fInPut)                                  */
/*                                                                                                */
/* Description     : 16Bit MAF apply                                                              */
/*                                                                                                */
/* In Params       : u16_fInPut                                                                   */
/*                                                                                                */
/* Out Params      : NO                                                                           */
/*                                                                                                */
/* Return Value    : u16_lMAF16Value                                                              */
/**************************************************************************************************/

INT16U ADCSCOPE_Ch2MAF16(INT16U u16_fInPut)
{
    INT32U u32_lAccVal = 0;
    INT16U u16_lMAF16Value = 0;
    INT8U u8_lIndex = 0;

    for(u8_lIndex = (MAXADC_MAF_BUFFER - 1); u8_lIndex > 0; u8_lIndex--)
    {
        u16_gAdcCh2Data[u8_lIndex] = u16_gAdcCh2Data[u8_lIndex - 1];
    }
    
    u16_gAdcCh2Data[0] = u16_fInPut;
    
    for(u8_lIndex = 0; u8_lIndex < MAXADC_MAF_BUFFER; u8_lIndex++)
    {
        u32_lAccVal = u32_lAccVal + u16_gAdcCh2Data[u8_lIndex];
    }
    
    u16_lMAF16Value = (INT16U)(u32_lAccVal >> 4);
    
    return u16_lMAF16Value;
}

/**************************************************************************************************/
/* Function Name   : INT16U ADCSCOPE_Ch3MAF16(INT16U u16_fInPut)                                  */
/*                                                                                                */
/* Description     : 16Bit MAF apply                                                              */
/*                                                                                                */
/* In Params       : u16_fInPut                                                                   */
/*                                                                                                */
/* Out Params      : NO                                                                           */
/*                                                                                                */
/* Return Value    : u16_lMAF16Value                                                              */
/**************************************************************************************************/

INT16U ADCSCOPE_Ch3MAF16(INT16U u16_fInPut)
{
    INT32U u32_lAccVal = 0;
    INT16U u16_lMAF16Value = 0;
    INT8U u8_lIndex = 0;

    for(u8_lIndex = (MAXADC_MAF_BUFFER - 1); u8_lIndex > 0; u8_lIndex--)
    {
        u16_gAdcCh3Data[u8_lIndex] = u16_gAdcCh3Data[u8_lIndex - 1];
    }
    
    u16_gAdcCh3Data[0] = u16_fInPut;
    
    for(u8_lIndex = 0; u8_lIndex < MAXADC_MAF_BUFFER; u8_lIndex++)
    {
        u32_lAccVal = u32_lAccVal + u16_gAdcCh3Data[u8_lIndex];
    }
    
    u16_lMAF16Value = (INT16U)(u32_lAccVal >> 4);
    
    return u16_lMAF16Value;
}

/**************************************************************************************************/
/* Function Name   : INT16U ADCSCOPE_Ch4MAF16(INT16U u16_fInPut)                                  */
/*                                                                                                */
/* Description     : 16Bit MAF apply                                                              */
/*                                                                                                */
/* In Params       : u16_fInPut                                                                   */
/*                                                                                                */
/* Out Params      : NO                                                                           */
/*                                                                                                */
/* Return Value    : u16_lMAF16Value                                                              */
/**************************************************************************************************/

INT16U ADCSCOPE_Ch4MAF16(INT16U u16_fInPut)
{
    INT32U u32_lAccVal = 0;
    INT16U u16_lMAF16Value = 0;
    INT8U u8_lIndex = 0;
    
    for(u8_lIndex = (MAXADC_MAF_BUFFER - 1); u8_lIndex > 0; u8_lIndex--)
    {
        u16_gAdcCh4Data[u8_lIndex] = u16_gAdcCh4Data[u8_lIndex - 1];
    }
    
    u16_gAdcCh4Data[0] = u16_fInPut;
    
    for(u8_lIndex = 0; u8_lIndex < MAXADC_MAF_BUFFER; u8_lIndex++)
    {
        u32_lAccVal = u32_lAccVal + u16_gAdcCh4Data[u8_lIndex];
    }
    
    u16_lMAF16Value = (INT16U)(u32_lAccVal >> 4);
    
    return u16_lMAF16Value;
}

/**************************************************************************************************/
/* Function Name   : INT16U ADCSCOPE_Ch5MAF16(INT16U u16_fInPut)                                  */
/*                                                                                                */
/* Description     : 16Bit MAF apply                                                              */
/*                                                                                                */
/* In Params       : u16_fInPut                                                                   */
/*                                                                                                */
/* Out Params      : NO                                                                           */
/*                                                                                                */
/* Return Value    : u16_lMAF16Value                                                              */
/**************************************************************************************************/

INT16U ADCSCOPE_Ch5MAF16(INT16U u16_fInPut)
{
    INT32U u32_lAccVal = 0;
    INT16U u16_lMAF16Value = 0;
    INT8U u8_lIndex = 0;
    
    for(u8_lIndex = (MAXADC_MAF_BUFFER - 1); u8_lIndex > 0; u8_lIndex--)
    {
        u16_gAdcCh5Data[u8_lIndex] = u16_gAdcCh5Data[u8_lIndex - 1];
    }
    
    u16_gAdcCh5Data[0] = u16_fInPut;
    
    for(u8_lIndex = 0; u8_lIndex < MAXADC_MAF_BUFFER; u8_lIndex++)
    {
        u32_lAccVal = u32_lAccVal + u16_gAdcCh5Data[u8_lIndex];
    }
    
    u16_lMAF16Value = (INT16U)(u32_lAccVal >> 4);
    
    return u16_lMAF16Value;
}

/**************************************************************************************************/
/* Function Name   : void ADC_ScopeInit(void)                                                     */
/*                                                                                                */
/* Description     : Initialize the ADC  pins and structures                                      */
/*                                                                                                */
/* In Params       : NULL                                                                         */
/*                                                                                                */
/* Out Params      : NULL                                                                         */
/*                                                                                                */
/* Return Value    : no                                                                           */
/**************************************************************************************************/

void ADC_ScopeInit(void)
{
	 /* ADC Pin Initialization */
    GPIO_Init((ST_GPIO_PARAMS_t *)&st_gADC0Ch1PinParams);
    GPIO_Init((ST_GPIO_PARAMS_t *)&st_gADC0Ch6PinParams);
    GPIO_Init((ST_GPIO_PARAMS_t *)&st_gADC0Ch7PinParams);
    GPIO_Init((ST_GPIO_PARAMS_t *)&st_gADC1Ch8PinParams);
    GPIO_Init((ST_GPIO_PARAMS_t *)&st_gADC1Ch9PinParams);

    /* ADC Initialization */
	ADC_Init((ST_ADC_PARAMS_t *)&st_gADC0Ch1Params);
    ADC_Init((ST_ADC_PARAMS_t *)&st_gADC0Ch6Params);
    ADC_Init((ST_ADC_PARAMS_t *)&st_gADC0Ch7Params);
    ADC_Init((ST_ADC_PARAMS_t *)&st_gADC1Ch8Params);
    ADC_Init((ST_ADC_PARAMS_t *)&st_gADC1Ch9Params);
}

/**************************************************************************************************/
/* Function Name   : void ADC_ScopeStart(void)                                                    */
/*                                                                                                */
/* Description     : Initialize the ADC  Timer                                                    */
/*                                                                                                */
/* In Params       : NULL                                                                         */
/*                                                                                                */
/* Out Params      : NULL                                                                         */
/*                                                                                                */
/* Return Value    : no                                                                           */
/**************************************************************************************************/

void ADC_ScopeStart(void)
{
    /* Init the Timer */ 
    TC_EventInit((ST_TC_EVENT_PARAMS_t *)&st_gADCTimer);
}

/**************************************************************************************************/
/* Function Name   : void ADC_ScopeStop(void)                                                     */
/*                                                                                                */
/* Description     : DeInitialize the ADC  Timer                                                  */
/*                                                                                                */
/* In Params       : NULL                                                                         */
/*                                                                                                */
/* Out Params      : NULL                                                                         */
/*                                                                                                */
/* Return Value    : no                                                                           */
/**************************************************************************************************/

void ADC_ScopeStop(void)
{
    TC_Disable(TC_SLICE_0);
    
    /* DeInit the Timer */
    ADC_ResetTrigger();
}

/**************************************************************************************************/
/* Function Name   : void ADCSCOPE_QueueWrite(INT8U u8_fChannel, INT16U u16_fData)                */
/*                                                                                                */
/* Description     : DeInitialize the ADC  Timer                                                  */
/*                                                                                                */
/* In Params       : NULL                                                                         */
/*                                                                                                */
/* Out Params      : NULL                                                                         */
/*                                                                                                */
/* Return Value    : no                                                                           */
/**************************************************************************************************/

void ADCSCOPE_QueueWrite(INT8U u8_fChannel, INT16U u16_fData)
{
    if(u8_gScopeQueueAvail < MAX_SCOPE_QUEUE_SIZE)
    {
        au16_gScopeQueue[u8_fChannel][u8_gScopeQueueRare] = (u16_fData <= 4095) ? u16_fData : 4095;
        
        if(u8_fChannel == 4)
        {
            u8_gScopeQueueRare = u8_gScopeQueueRare + 1;
            u8_gScopeQueueAvail = u8_gScopeQueueAvail + 1;
        }
        else
        {
            /* No Action */
        }

        if(u8_gScopeQueueRare == MAX_SCOPE_QUEUE_SIZE)
        {
            u8_gScopeQueueRare = 0;
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
/* Function Name   : INT16U ADCSCOPE_QueueRead(INT8U u8_fChannel)                                 */
/*                                                                                                */
/* Description     : DeInitialize the ADC  Timer                                                  */
/*                                                                                                */
/* In Params       : NULL                                                                         */
/*                                                                                                */
/* Out Params      : NULL                                                                         */
/*                                                                                                */
/* Return Value    : no                                                                           */
/**************************************************************************************************/

INT16U ADCSCOPE_QueueRead(INT8U u8_fChannel)
{
    INT16U u16_lData = 0;
    
    if(u8_gScopeQueueAvail > 0)
    {
        u16_lData = au16_gScopeQueue[u8_fChannel][u8_gScopeQueueFront];
        
        if(u8_fChannel == 4)
        {
            u8_gScopeQueueFront = u8_gScopeQueueFront + 1;
            u8_gScopeQueueAvail = u8_gScopeQueueAvail - 1;
        }
        else
        {
            /* No Action */
        }

        if(u8_gScopeQueueFront == MAX_SCOPE_QUEUE_SIZE)
        {
            u8_gScopeQueueFront = 0;
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
    
    return u16_lData;
}

/**************************************************************************************************/
/* Function Name   : INT8U ADCSCOPE_GetQueueSize(void)                                            */
/*                                                                                                */
/* Description     : DeInitialize the ADC  Timer                                                  */
/*                                                                                                */
/* In Params       : NULL                                                                         */
/*                                                                                                */
/* Out Params      : NULL                                                                         */
/*                                                                                                */
/* Return Value    : no                                                                           */
/**************************************************************************************************/

INT8U ADCSCOPE_GetQueueSize(void)
{
    return u8_gScopeQueueAvail;
}

/**************************************************************************************************/
/* Function Name   : void ADCSCOPE_ResetQueue(void)                                               */
/*                                                                                                */
/* Description     : DeInitialize the ADC  Timer                                                  */
/*                                                                                                */
/* In Params       : NULL                                                                         */
/*                                                                                                */
/* Out Params      : NULL                                                                         */
/*                                                                                                */
/* Return Value    : no                                                                           */
/**************************************************************************************************/

void ADCSCOPE_ResetQueue(void)
{
    u8_gScopeQueueRare = 0;
    u8_gScopeQueueFront = 0;
    u8_gScopeQueueAvail = 0;
}

/**************************************************************************************************/
/* Function Name   : void ADCSCOPE_ReadCalibValues(void)                                          */
/*                                                                                                */
/* Description     : DeInitialize the ADC  Timer                                                  */
/*                                                                                                */
/* In Params       : NULL                                                                         */
/*                                                                                                */
/* Out Params      : NULL                                                                         */
/*                                                                                                */
/* Return Value    : no                                                                           */
/**************************************************************************************************/

#if 0

void ADCSCOPE_ReadCalibValues(void)
{
    /* Read the ADC Variables Calibration Values once firstboot is Completed */
    FLASH_Read(EEPROM_CH1_FACTOR, (INT8U *)&f32_gChanne11Factor, 8);
    FLASH_Read(EEPROM_CH2_FACTOR, (INT8U *)&f32_gChanne12Factor, 8);
    FLASH_Read(EEPROM_CH3_FACTOR, (INT8U *)&f32_gChanne13Factor, 8);
    FLASH_Read(EEPROM_CH4_FACTOR, (INT8U *)&f32_gChanne14Factor, 8);
    FLASH_Read(EEPROM_CH5_FACTOR, (INT8U *)&f32_gChanne15Factor, 8);
}

#endif

/**************************************************************************************************/
/* Function Name   : void ADCSCOPE_ReadCalibValues(void)                                          */
/*                                                                                                */
/* Description     : DeInitialize the ADC  Timer                                                  */
/*                                                                                                */
/* In Params       : NULL                                                                         */
/*                                                                                                */
/* Out Params      : NULL                                                                         */
/*                                                                                                */
/* Return Value    : no                                                                           */
/**************************************************************************************************/

void ADCSCOPE_ResetCalib(void)
{
    f32_gChanne11Factor = 1024.0;
    f32_gChanne12Factor = 1024.0;
    f32_gChanne13Factor = 1024.0;
    f32_gChanne14Factor = 1024.0;
    f32_gChanne15Factor = 1024.0;
}

/**************************************************************************************************/
/* End of ADC_SCOPE.c                                                                             */
/**************************************************************************************************/
