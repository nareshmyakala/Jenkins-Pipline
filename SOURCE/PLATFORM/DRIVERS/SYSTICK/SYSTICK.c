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
/* \File Name   : SYSTICK.C                                                                       */
/* \Author      : Kishore D                                                                       */
/* \Version     : v1.0                                                                            */
/* \Date        : 23/08/2018                                                                      */
/* @Description :                                                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "SYSTICK.h"
#include "SYSTICK_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

#define _120MHZ

#ifdef _120MHZ
#define FREQ	( (INT32U)120000000 )
#endif

#ifdef _80MHZ
#define FREQ	( (INT32U)80000000 )
#endif

#ifdef _72MHZ
#define FREQ	( (INT32U)72000000 )
#endif

#ifdef _64MHZ
#define FREQ	( (INT32U)64000000 )
#endif

#ifdef _48MHZ
#define FREQ	( (INT32U)48000000 )
#endif

#ifdef _25_6MHZ
#define FREQ	( (INT32U)25600000 )
#endif

#ifdef _30MHZ
#define FREQ	( (INT32U)30000000 )
#endif

#ifdef _32MHZ
#define FREQ	( (INT32U)32000000 )
#endif

#ifdef _24MHZ
#define FREQ	( (INT32U)24000000 )
#endif

#ifdef _16MHZ
#define FREQ	( (INT32U)16000000 )
#endif

#ifdef _12MHZ
#define FREQ	( (INT32U)12000000 )
#endif

#ifdef _8MHZ
#define FREQ	( (INT32U)8000000 )
#endif

#ifdef _6MHZ
#define FREQ	( (INT32U)6000000 )
#endif

#ifdef _4MHZ
#define FREQ	( (INT32U)4000000 )
#endif

#ifdef _2MHZ
#define FREQ	( (INT32U)2000000 )
#endif

#ifdef _1MHZ
#define FREQ	( (INT32U)1000000 )
#endif

#ifdef _3MHZ
#define FREQ	( (INT32U)3000000 )
#endif

#ifdef _32KHZ
#define FREQ	( (INT32U)32000 )
#endif


#define MS(X)	(((FREQ)/1000) * (X))
#define US(X) (((FREQ)/1000000) * (X))

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* This Variable is used to Access the Systick Registers */
ST_SYSTICK_Regs_t * p_stgSYSTICKRegs = (ST_SYSTICK_Regs_t *)SYSTICK_BASE_ADDR;

/**************************************************************************************************/
/* Function Name   :  void SYSTICK_Enable(EN_SYSTICK_CLOCK_t en_fSYSTICKClock)                    */
/*                                                                                                */
/* Description     :  This Function is Used to Enable the Systick                                 */
/*                                                                                                */
/* In Params       :  EN_SYSTICK_CLOCK_t Type                                                     */
/*                                                                                                */
/* Out Params      :  None                                                                        */
/*                                                                                                */
/* Return Value    :  void                                                                        */
/**************************************************************************************************/

void SYSTICK_Enable(EN_SYSTICK_CLOCK_t en_fSYSTICKClock)
{
	
	/* Selecting the Clocksource for SysTick */
	switch(en_fSYSTICKClock)
	{
		case SYSTICK_FSTANDBY_2:
		{
			p_stgSYSTICKRegs->SYST_CSR &= ~PPB_SYST_CSR_CLKSOURCE_MASK;
		}
		break;
		
		case SYSTICK_FCPU:
		{
			p_stgSYSTICKRegs->SYST_CSR |= PPB_SYST_CSR_CLKSOURCE_MASK;
		}
		break;
		
		default:
		{
				/* NOP */
		}
		break;			
	}	
	
	/* Enable Systick */
	p_stgSYSTICKRegs->SYST_CSR |= PPB_SYST_CSR_ENABLE_MASK;
}

/**************************************************************************************************/
/* Function Name   :  void SYSTICK_Disable(void)                                                  */
/*                                                                                                */
/* Description     :  This Function is Used to Disable the Systick                                */
/*                                                                                                */
/* In Params       :  None                                                                        */
/*                                                                                                */
/* Out Params      :  None                                                                        */
/*                                                                                                */
/* Return Value    :  void                                                                        */
/**************************************************************************************************/

void SYSTICK_Disable(void)
{
	/* Disable Systick */
	p_stgSYSTICKRegs->SYST_CSR &= ~PPB_SYST_CSR_ENABLE_MASK;
}

/**************************************************************************************************/
/* Function Name   :   void SYSTICK_EnableInterrupt(void)                                         */
/*                                                                                                */
/* Description     :   This Function is Used to Enable the Interrupt                              */
/*                                                                                                */
/* In Params       :   None                                                                       */
/*                                                                                                */
/* Out Params      :   None                                                                       */
/*                                                                                                */
/* Return Value    :   void                                                                       */
/**************************************************************************************************/

void SYSTICK_EnableInterrupt(void)
{
	/* enable the Interrupt by Setting the TICKINT bit in SYST_CSR Register */
	p_stgSYSTICKRegs->SYST_CSR |= PPB_SYST_CSR_TICKINT_MASK;
}

/**************************************************************************************************/
/* Function Name   :   void SYSTICK_DisableInterrupt(void)                                        */
/*                                                                                                */
/* Description     :   This Function is Used to Disable the Interrupt                             */
/*                                                                                                */
/* In Params       :   None                                                                       */
/*                                                                                                */
/* Out Params      :   None                                                                       */
/*                                                                                                */
/* Return Value    :   void                                                                       */
/**************************************************************************************************/

void SYSTICK_DisableInterrupt(void)
{
	/* Disable the Interrupt by resetting the TICKINT bit in SYST_CSR Register */
	p_stgSYSTICKRegs->SYST_CSR &= ~PPB_SYST_CSR_TICKINT_MASK;
}

/**************************************************************************************************/
/* Function Name   :  void SYSTICK_SetTickCount(INT32U u32_fTime)                                 */
/*                                                                                                */
/* Description     :  This Function is Used to Set the Systick Count                              */
/*                                                                                                */
/* In Params       :  INT32U Type                                                                 */
/*                                                                                                */
/* Out Params      :  None                                                                        */
/*                                                                                                */
/* Return Value    :  void                                                                        */
/**************************************************************************************************/

void SYSTICK_SetTickCount(EN_SYSTICK_TYPE_t en_fSystickType, INT32U u32_fTime)
{
	INT32U u32_lCount = 0;
	
	if((u32_fTime > 0) && (u32_fTime <= 0x00FFFFFF))
	{
		if(en_fSystickType == SYSTICK_MS)
		{
			u32_lCount =  MS(u32_fTime);
		}
		else
		{
			u32_lCount =  US(u32_fTime);
		}
		
		p_stgSYSTICKRegs->SYST_RVR = u32_lCount;	
		p_stgSYSTICKRegs->SYST_CVR = 0x00000000;
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   :  INT32U SYSTICK_GetTickCount(void)                                           */
/*                                                                                                */
/* Description     :  This Function is Used to Get the Tick Count                                 */
/*                                                                                                */
/* In Params       :  None                                                                        */
/*                                                                                                */
/* Out Params      :  None                                                                        */
/*                                                                                                */
/* Return Value    :  INT32U Type                                                                 */
/**************************************************************************************************/

INT32U SYSTICK_GetTickCount(void)
{
	/* This Function is Used to collect the tick Count Value */
	INT32U u32_lValue;
	
	/* read the SYST_CVR Register for the current value */
	u32_lValue = p_stgSYSTICKRegs->SYST_CVR;
	
	/* return value */
	return u32_lValue;
}

/**************************************************************************************************/
/* Function Name   :  INT8U SYSTICK_GetStatus(void)                                               */
/*                                                                                                */
/* Description     :  This Function is Used to Get the Status of the Function                     */
/*                                                                                                */
/* In Params       :  None                                                                        */
/*                                                                                                */
/* Out Params      :  None                                                                        */
/*                                                                                                */
/* Return Value    :  INT8U Type                                                                  */
/**************************************************************************************************/

INT8U SYSTICK_GetStatus(void)
{
	/* Variable to Collect the Status */
	INT8U u8_lValue;
	
	/* Collect the Status by reading the CSR Register */
	u8_lValue = (INT8U)((p_stgSYSTICKRegs->SYST_CSR & PPB_SYST_CSR_COUNTFLAG_MASK)>>16);
	
	/* Return the Status */
	return u8_lValue;
}
/**************************************************************************************************/
/* End of SYSTICK.c                                                                               */
/**************************************************************************************************/
