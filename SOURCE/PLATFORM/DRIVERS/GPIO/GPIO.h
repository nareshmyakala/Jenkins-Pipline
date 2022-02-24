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
/* \File Name   : PORT.c                                                                          */
/* \Author      : Kishore D                                                                       */
/* \Version     : v1.1                                                                            */
/* \Date        : 23/08/2018  					                                                  */
/* @Description : GPIO Driver 					                                                  */
/**************************************************************************************************/

#ifndef _GPIO_H_
#define _GPIO_H_

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

/*Enumeration of PORT status List */
typedef enum
{
	PORT_SUCCESS = 0x00,
	PORT_ERROR
}EN_PORT_RESULT_t;

/*Enumeration of Available PORTs list */
typedef enum
{
	GPIO_PORT_A = 0x00,
	GPIO_PORT_B,
	MAX_PORTS
}EN_GPIO_PORT_t;

/* Enum for available PORT Pins */
typedef enum
{
	GPIO_PIN_0 = 0,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7,
	GPIO_PIN_8,
	GPIO_PIN_9,
	GPIO_PIN_10,
	GPIO_PIN_11,
	GPIO_PIN_12,
	GPIO_PIN_13,
	GPIO_PIN_14,
	GPIO_PIN_15,
	GPIO_PIN_16,
	GPIO_PIN_17,
	GPIO_PIN_18,
	GPIO_PIN_19,
	GPIO_PIN_20,
	GPIO_PIN_21,
	GPIO_PIN_22,
	GPIO_PIN_23,
	GPIO_PIN_24,
	GPIO_PIN_25,
	GPIO_PIN_26,
	GPIO_PIN_27,
	GPIO_PIN_28,
	GPIO_PIN_29,
	GPIO_PIN_30,
	GPIO_PIN_31
}EN_GPIO_PIN_t;

/* Enum for selecting Pad Driver Strength */
typedef enum
{
	GPIO_DRIV_STRENGTH_NORMAL = 0,
	GPIO_DRIV_STRENGTH_STRONG		
}EN_DRIVER_STRENGTH_t;

/* Enum for selecting Pin Direction */
typedef enum
{
	GPIO_DIR_OUTPUT,
	GPIO_DIR_INPUT
}EN_GPIO_DIR_t;

/* Enum for selecting Level */
typedef enum
{
	GPIO_PIN_LEVEL_LOW,
	GPIO_PIN_LEVEL_HIGH
}EN_GPIO_PIN_LEVEL_t;

/* Enum for selecting Internal PullUp if pin is enabled as Input */
typedef enum
{
	GPIO_PULL_LVL_DIS = 0,
	GPIO_IN_PULL_UP,
	GPIO_IN_PULL_DOWN,
	GPIO_OUT_LEVEL_LOW,
	GPIO_OUT_LEVEL_HIGH
}EN_GPIO_PIN_TYPE_t;

/* Enum for selecting Peripheral */
typedef enum
{
	GPIO_PERIPHERAL_A = 0x0,
	GPIO_PERIPHERAL_B,
	GPIO_PERIPHERAL_C,
	GPIO_PERIPHERAL_D,
	GPIO_PERIPHERAL_E,
	GPIO_PERIPHERAL_F,
	GPIO_PERIPHERAL_G,
	GPIO_PERIPHERAL_H,
	GPIO_PERIPHERAL_I,
	GPIO_PERIPHERAL_J,
	GPIO_PERIPHERAL_K,
	GPIO_PERIPHERAL_L,
	GPIO_PERIPHERAL_M,
	GPIO_PERIPHERAL_N,
	GPIO_GENERAL_PURPOSE,
}EN_GPIO_PERIPH_t;

/* Port Configuration Parameters */
typedef struct
{
	EN_GPIO_PORT_t		    en_mPortSel;
	EN_GPIO_PIN_t		    en_mPinSel;
	EN_GPIO_DIR_t			en_mPinDir;
	EN_GPIO_PIN_TYPE_t		en_mPinType;
	EN_GPIO_PERIPH_t		en_mPinPeriph;
	EN_DRIVER_STRENGTH_t	en_mDriverStrenght;
}ST_GPIO_PARAMS_t; 

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function to configure GPIO pins*/
extern EN_PORT_RESULT_t GPIO_Init(ST_GPIO_PARAMS_t * p_stfPORTPinData);

/* Function to Set a GPIO Pin  */
extern EN_PORT_RESULT_t GPIO_SetPin(EN_GPIO_PORT_t en_fPort, EN_GPIO_PIN_t u8_fPin);

/* Function to Reset a GPIO Pin  */
extern EN_PORT_RESULT_t GPIO_ResetPin(EN_GPIO_PORT_t en_fPort, EN_GPIO_PIN_t u8_fPin);

/* Function to Toggle a GPIO Pin  */
extern EN_PORT_RESULT_t GPIO_TogglePin(EN_GPIO_PORT_t en_fPort, EN_GPIO_PIN_t u8_fPin);

/* Function to change pin to toggle pin mode (input or output) */
extern	EN_PORT_RESULT_t GPIO_ToggleMode(EN_GPIO_PORT_t en_fPort, EN_GPIO_PIN_t u8_fPin);

/* Function to Read a GPIO pin */
extern INT8U GPIO_ReadPin(EN_GPIO_PORT_t en_fPort,EN_GPIO_PIN_t u8_fPin);

/* Function to read the block */
extern INT32U GPIO_ReadBlock(EN_GPIO_PORT_t en_fPort,INT32U u32_fPins);


#endif 
/**************************************************************************************************/
/* End of GPIO.h                                                                                  */
/**************************************************************************************************/
