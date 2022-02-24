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
/* \File Name   : OSCCTRL.c                                                                       */
/* \Author      : Kishore D                                                                       */
/* \Version 		: 1.1                                                                             */
/* \Date        : 23/08/2018                                                                      */
/*                                                                                                */
/* @Description : OSCCTRL Driver Frame Work                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "OSCCTRL.h"
#include "OSCCTRL_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Variable to Access the OSCCTRL Regsiters */
ST_OSCCTRL_BASE_REGS_t * p_stgOscCtrlRegs = (ST_OSCCTRL_BASE_REGS_t *)OSCCTRL_BASE_ADDRESS;

/**************************************************************************************************/
/* Function Name   : EN_OSCCTRL_RESULT_t XOSCClockConfig(EN_OSCTRL_XOSC_FREQ en_fXOSCFreq)        */
/*                                                                                                */
/* Description     : This function used confiure the source Clock(XOSC)                           */
/*                                                                                                */
/* In Params       : EN_OSCTRL_XOSC_FREQ en_fXOSCFreq                                             */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_OSCCTRL_RESULT_t Type                                                     */
/**************************************************************************************************/

EN_OSCCTRL_RESULT_t XOSCClockConfig(EN_OSCTRL_XOSC_FREQ en_fXOSCFreq)
{
    EN_OSCCTRL_RESULT_t en_lResult = OSCCTRL_SUCCESS;
    INT32U u32_lTemp = 0;
    
    u32_lTemp = (5 << 20) | OSCCTRL_XOSC_AUTO_LOOP | (1 << 8) | (1 << 17) | (0x03 << 9) | (0x04 << 11) | \
                                                    OSCCTRL_XOSC_XTALEN | OSCCTRL_XOSC_ENABLE;
      
    p_stgOscCtrlRegs->XOSCCTRL1 = u32_lTemp;

    /* Wait unitil Oscillator is Synchronized */
    while(!(p_stgOscCtrlRegs->STATUS & OSCCTRL_XOSCRDY1));
  
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_OSCCTRL_RESULT_t XOSCDpllCOnfig(void)                                     */
/*                                                                                                */
/* Description     : This function used confiure the source Clock(XOSC)                           */
/*                                                                                                */
/* In Params       : EN_OSCTRL_XOSC_FREQ en_fXOSCFreq                                             */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_OSCCTRL_RESULT_t Type                                                     */
/**************************************************************************************************/

void XOSCDpllCOnfig(INT32U u32_fFrequency)
{
    INT32U u32_lTemp = 0;

    p_stgOscCtrlRegs->DPLL1CTRLA = 0x00;
    
    p_stgOscCtrlRegs->DPLL1CTRLB = 0x00000020; 
    
    u32_lTemp = (0x03 << 5);
    p_stgOscCtrlRegs->DPLL1CTRLB = u32_lTemp;
    
    u32_lTemp = (u32_fFrequency/6000000) - 1;

    p_stgOscCtrlRegs->DPLL1RATIO = u32_lTemp;
    while(p_stgOscCtrlRegs->DPLL1SYNCBUSY & 0x04);
    
    p_stgOscCtrlRegs->DPLL1CTRLA = 0x02;
    
    while(p_stgOscCtrlRegs->DPLL1SYNCBUSY & 0x02);

    while(0x03 != (p_stgOscCtrlRegs->DPLL1STATUS & 0x03));
}

/**************************************************************************************************/
/* End of OSCCTRL.c                                                                               */
/**************************************************************************************************/
