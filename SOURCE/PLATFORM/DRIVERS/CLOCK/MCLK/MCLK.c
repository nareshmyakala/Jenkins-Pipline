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
/* \File Name   : MCLK.c                                                                          */
/* \Author      : Kishore D                                                                       */
/* \Version 		: v1.0                                                                            */
/* \Date        : 23/08/2018                                                                      */
/*                                                                                                */
/* @Description : MCLK Driver 	    		                                                          */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "MCLK.h"
#include "MCLK_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Variable to Access the MCLK Register */
ST_MCLK_REGS_t * p_stgMCLKRegs = (ST_MCLK_REGS_t *)MCLK_BASE_ADDRESS;

/**************************************************************************************************/
/* Function Name   : void MCLK_Init(void)                                                         */
/*                                                                                                */
/* Description     : This function used to initialize the MCLK                                    */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void MCLK_Init(void)
{			
	/* Configure CPUDIV in CPUDIV Register */
	p_stgMCLKRegs->CPUDIV = MCLK_CPUDIV_MASK;
	p_stgMCLKRegs->HSDIV = MCLK_HSDIV_MASK;
		
	/* Wait till Clock Ready */
	while(!(p_stgMCLKRegs->INTFLAG));
	p_stgMCLKRegs->INTFLAG = 0x01;
}

/**************************************************************************************************/
/* Function Name   : void MCLK_FlashClkInit(void)                                                 */
/*                                                                                                */
/* Description     : This function used to initialize the MCLK                                    */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void MCLK_FlashClkInit(void)
{	
	p_stgMCLKRegs->AHBMASK |= (1 << MCLK_AHBMASK_NVMCTRL_OFFSET);
}

/**************************************************************************************************/
/* Function Name   : void MCLK_FlashClkInit(void)                                                 */
/*                                                                                                */
/* Description     : This function used to initialize the MCLK                                    */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void MCLK_PeriphClkInit(EN_PERIPH_BUS_SEL_t en_fPeriphBus, EN_MCLK_PERIPH_SEL_t en_fPeriph)
{	
    INT32U u32_lRegVal = 0;

    switch(en_fPeriphBus)
    {
    case MCLK_AHB :
        u32_lRegVal = p_stgMCLKRegs->AHBMASK;
        u32_lRegVal |= (1 << en_fPeriph);
        p_stgMCLKRegs->AHBMASK = u32_lRegVal;
    break;

    case MCLK_APBA :
        u32_lRegVal = p_stgMCLKRegs->APBAMASK;
        u32_lRegVal |= (1 << en_fPeriph);
        p_stgMCLKRegs->APBAMASK = u32_lRegVal;
    break;

    case MCLK_APBB :
        u32_lRegVal = p_stgMCLKRegs->APBBMASK;
        u32_lRegVal |= (1 << en_fPeriph);
        p_stgMCLKRegs->APBBMASK = u32_lRegVal;
    break;

    case MCLK_APBC :
        u32_lRegVal = p_stgMCLKRegs->APBCMASK;
        u32_lRegVal |= (1 << en_fPeriph);
        p_stgMCLKRegs->APBCMASK = u32_lRegVal;
    break;

    case MCLK_APBD :
        u32_lRegVal = p_stgMCLKRegs->APBDMASK;
        u32_lRegVal |= (1 << en_fPeriph);
        p_stgMCLKRegs->APBDMASK = u32_lRegVal;
    break;

    default :
    break;
    }
}

/**************************************************************************************************/
/* Function Name   : void MCLK_FlashClkInit(void)                                                 */
/*                                                                                                */
/* Description     : This function used to initialize the MCLK                                    */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void MCLK_PeriphClkClearInit(EN_PERIPH_BUS_SEL_t en_fPeriphBus, EN_MCLK_PERIPH_SEL_t en_fPeriph)
{	
    INT32U u32_lRegVal = 0;

    switch(en_fPeriphBus)
    {
    case MCLK_AHB :
        u32_lRegVal = p_stgMCLKRegs->AHBMASK;
        u32_lRegVal |= (1 << en_fPeriph);
        p_stgMCLKRegs->AHBMASK = u32_lRegVal;
    break;

    case MCLK_APBA :
        u32_lRegVal = p_stgMCLKRegs->APBAMASK;
        u32_lRegVal |= (1 << en_fPeriph);
        p_stgMCLKRegs->APBAMASK = u32_lRegVal;
    break;

    case MCLK_APBB :
        u32_lRegVal = p_stgMCLKRegs->APBBMASK;
        u32_lRegVal |= (1 << en_fPeriph);
        p_stgMCLKRegs->APBBMASK = u32_lRegVal;
    break;

    case MCLK_APBC :
        u32_lRegVal = p_stgMCLKRegs->APBCMASK;
        u32_lRegVal |= (1 << en_fPeriph);
        p_stgMCLKRegs->APBCMASK = u32_lRegVal;
    break;

    case MCLK_APBD :
        u32_lRegVal = p_stgMCLKRegs->APBDMASK;
        u32_lRegVal |= (1 << en_fPeriph);
        p_stgMCLKRegs->APBDMASK = u32_lRegVal;
    break;

    default :
    break;
    }
}

/**************************************************************************************************/
/* End of MCLK.c                                                                                  */
/**************************************************************************************************/
