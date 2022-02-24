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
/* \File Name   : PLATFORM.c                                                                      */
/* \Author      : Santhosh Kumar                                                                  */
/* \Version 	: 1.0                                                                             */
/* \Date        : 13/06/2019                                                                      */
/*                                                                                                */
/* @Description : Platform Driver Frame Work                                                      */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "SYSTICK.h"
#include "NVIC.h"
#include "GPIO.h"
#include "CLOCK.h"
#include "EIC.h"

#include "STN.h"

#include "MSG4_App.h"

#include "PLATFORM.h"
#include "PLATFORM_Priv.h"

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* */
INT32U u32_gTickCounter = 0x00;
INT8U u8_gIsSystickTimeOut = 0;

/* Configure Led */
const ST_GPIO_PARAMS_t st_gAuthntctnLedConfigParams = 
{
    .en_mPortSel	 = AUTHNTCTN_LED_PORT,
    .en_mPinSel	         = AUTHNTCTN_LED_PIN,
    .en_mPinDir	         = GPIO_DIR_OUTPUT,
    .en_mPinType	 = GPIO_PULL_LVL_DIS,
    .en_mPinPeriph	 = GPIO_GENERAL_PURPOSE,
    .en_mDriverStrenght	 = GPIO_DRIV_STRENGTH_STRONG
};

/* Configure Led */
const ST_GPIO_PARAMS_t st_gWIFILedConfigParams = 
{
    .en_mPortSel = WIFI_LED_PORT,
    .en_mPinSel	 = WIFI_LED_PIN,
    .en_mPinDir	 = GPIO_DIR_OUTPUT,
    .en_mPinType = GPIO_PULL_LVL_DIS,
    .en_mPinPeriph = GPIO_GENERAL_PURPOSE,
    .en_mDriverStrenght	= GPIO_DRIV_STRENGTH_STRONG
};


/**************************************************************************************************/
/* Function Name   : void PLATFORM_Init(void)                                                     */
/*                                                                                                */
/* Description     : This funcction is used to Initialise the Clocks and Systick                  */
/*                                                                                                */
/* In Params       : void                                                                         */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void PLATFORM_Init(void)
{
    /* Generation of 120MHz Clock */
    ClockInit();

    /* Initialize the LED */
    GPIO_Init((ST_GPIO_PARAMS_t *)&st_gWIFILedConfigParams);
  
    /* Initialize the LED */
    GPIO_Init((ST_GPIO_PARAMS_t *)&st_gAuthntctnLedConfigParams);

    /* Reset The Authentication LED */
    RESSET_PIN(AUTHNTCTN_LED_PORT ,AUTHNTCTN_LED_PIN );
    
    /* Switch off the WiFi LED */
    SET_PIN(WIFI_LED_PORT, WIFI_LED_PIN);
    
    /* Configure systick for tick count */
    SYSTICK_SetTickCount(SYSTICK_MS, 1);

    /*Enable the SysTick Interrupt */
    SYSTICK_EnableInterrupt();

    /* Enabling of systick timer */
    SYSTICK_Enable(SYSTICK_FCPU);
}

/**************************************************************************************************/
/* Function Name   : void SysTick_Handler(void)                                                   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void SysTick_Handler(void)
{
    /* Increment the TIick Counter */
    u32_gTickCounter = u32_gTickCounter + 1;
    
    u8_gIsSystickTimeOut = 1;   
                    
    /* Call STN 1ms Handler */
    STN_1MsHandler();

}

/**************************************************************************************************/
/* End of PLATFORM.c                                                                              */
/**************************************************************************************************/
