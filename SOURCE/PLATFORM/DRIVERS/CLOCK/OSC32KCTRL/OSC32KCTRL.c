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
/* \File Name   : OSC32KCTRL.c                                                                    */
/* \Author      : Salman Ali                                                                      */
/* \Version 	: 1.1                                                                             */
/* \Date        : 20/06/2016                                                                      */
/*                                                                                                */
/* @Description: OSC32KCTRL Driver Frame Work                                            		  */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "OSC32KCTRL.h"
#include "OSC32KCTRL_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Variable to Access OSC32KCTRL Registers */
ST_OSC32KCTRL_REGS_t * p_stgOSC32KCtrlRegs = (ST_OSC32KCTRL_REGS_t *)OSC32KCTRL_BASE_ADDRESS;

/**************************************************************************************************/
/* Function Name   : void OSC32KCTL_XOSC32KInit(void)                                             */
/*                                                                                                */
/* Description     : This function used to initialize the XOSC32K                                 */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void OSC32KCTRL_XOSC32KInit(void)
{	
     INT16U u16_lTemp = 0;
     
     p_stgOSC32KCtrlRegs->XOSC32K = 0x2000;
     
     u16_lTemp = OSC32KCTRL_XOSC32K_ENABLE | OSC32KCTRL_XOSC32K_EN32K | OSC32KCTRL_XOSC32K_XTALEN;
	
     p_stgOSC32KCtrlRegs->XOSC32K |= u16_lTemp;
     
	/* Wait till Clock was set */
	while(!(p_stgOSC32KCtrlRegs -> STATUS & OSC32KCTRL_STATUS_XOSC32KRDY));
}

/**************************************************************************************************/
/* Function Name   : void OSC32KCTRL_XOSC32KConfig(void)                                          */
/*                                                                                                */
/* Description     : This function used to configure the XOSC32K                                  */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void OSC32KCTRL_XOSC32KConfig(void)
{
	/* Clearing XOSC32 ready flag */
	p_stgOSC32KCtrlRegs->INTFLAG &= ~OSC32KCTRL_INTFLAG_XOSC32KRDY_MASK;
	
	/* Enable external Crystal */
	p_stgOSC32KCtrlRegs -> XOSC32K |= OSC32KCTRL_XOSC32K_XTALEN;
	
	/* Setting Startup Time as 655366 */
	p_stgOSC32KCtrlRegs->XOSC32K |= (0x4 << OSC32KCTRL_XOSC32K_STARTUP_POS);
		
    /* Enable The Generation of 32K */
	p_stgOSC32KCtrlRegs -> XOSC32K |= OSC32KCTRL_XOSC32K_EN32K;	
	
	/* Set on STDBY Mode */
	p_stgOSC32KCtrlRegs -> XOSC32K |= OSC32KCTRL_XOSC32K_STDBY;

	/* Enable oscillator */
	p_stgOSC32KCtrlRegs -> XOSC32K |= OSC32KCTRL_XOSC32K_ENABLE;
	
	/* Wait till Clock was set */
	while(!(p_stgOSC32KCtrlRegs -> STATUS & OSC32KCTRL_STATUS_XOSC32KRDY));
}

/**************************************************************************************************/
/* Function Name   : void OSC32KCTRL_1KHZClockEnable(void)                                        */
/*                                                                                                */
/* Description     : This function is used to enable the 1Khz clock                               */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void OSC32KCTRL_1KHZClockEnable(void)
{	
	/* Enable The Generatio of 1K */
	p_stgOSC32KCtrlRegs -> OSC32K |= OSC32KCTRL_OSC32K_EN1K;
	
	/* Enable oscillator */
	p_stgOSC32KCtrlRegs -> OSC32K |= OSC32KCTRL_OSC32K_ENABLE;      
}

/**************************************************************************************************/
/* Function Name   : void OSC32KCTRL_OSC32KInit(void)                                             */
/*                                                                                                */
/* Description     : This function is used to initialize OSC32K oscillator                        */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void OSC32KCTRL_OSC32KInit(void)
{
    /* Clear the Generation 1K */
	p_stgOSC32KCtrlRegs -> OSC32K &= ~OSC32KCTRL_OSC32K_EN1K; 
	
	/* Enable the Generation of 32K */
	p_stgOSC32KCtrlRegs -> OSC32K |= OSC32KCTRL_OSC32K_ENABLE;
	
	/* Clear ONDEMAND and STDBY Mode */
	p_stgOSC32KCtrlRegs -> OSC32K &= ~(OSC32KCTRL_OSC32K_ONDEMAND | OSC32KCTRL_OSC32K_RUNSTDBY);
	
	/* Enable oscillator */
	p_stgOSC32KCtrlRegs -> OSC32K |= OSC32KCTRL_OSC32K_ENABLE;
	
	/* Wait till Clock was set */
	while(!(p_stgOSC32KCtrlRegs -> STATUS & OSC32KCTRL_STATUS_OSC32KRDY));
}

/**************************************************************************************************/
/* End of OSC32KCTRL.c                                                                            */
/**************************************************************************************************/
