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
/* \File Name   : CLOCK.c                                                                         */
/* \Author      : Kishore D	                                                                    */
/* \Version 	  : V1.0       	                                                               */
/* \Date        : 23/08/2018                                                                      */
/*                                                                                                */
/* @Description: Clock Driver                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "GCLK.h"
#include "OSC32KCTRL.h"
#include "OSCCTRL.h"
#include "MCLK.h"

#include "CLOCK.h"
#include "CLOCK_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

#define GCLK_SET_REG(OFFSET, VALUE)        ((*(INT32U *)(0x40001C00 + OFFSET)) = VALUE)
#define OSCTRL_SET_REG(OFFSET, VALUE)      ((*(INT32U *)(0x40001000 + OFFSET)) = VALUE)

#define GCLK_GET_REG(OFFSET)               (*(INT32U *)(0x40001C00 + OFFSET))
#define OSCTRL_GET_REG(OFFSET)             (*(INT32U *)(0x40001000 + OFFSET))

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* Function Name   : void ClockInit(void)                                                         */
/*                                                                                                */
/* Description     : This function is used to Initialize the 48MHz clock                          */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void CLOCK_ResetClocks(void)
{
    GCLK_SET_REG(0x00, 0x01);
    while(GCLK_GET_REG(0x04) & 0x01);

    OSCTRL_SET_REG(0x44, 0x00000080);
    OSCTRL_SET_REG(0x4C, 0x00000020);

    while(OSCTRL_GET_REG(0x50) & 0x02);

    OSCTRL_SET_REG(0x18, 0x00000080);
}

/**************************************************************************************************/
/* Function Name   : void ClockInit(void)                                                         */
/*                                                                                                */
/* Description     : This function is used to Initialize the 48MHz clock                          */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ClockInit(void)
{	    
    /* */
    CLOCK_ResetClocks();
    
    /* External Clock Oscillator */
    XOSCClockConfig(FREQ_8MHZ_16MHZ);

    /* */
    OSC32KCTRL_XOSC32KInit();

    /* */
    XOSCDpllCOnfig(120000000);
    
    /* Generator-0 */
    GCLK_Generator0Init();

    /* Configure MCLK */
    MCLK_Init();
}

/**************************************************************************************************/
/* End of CLOCK.c                                                                                 */
/**************************************************************************************************/
