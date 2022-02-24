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
/* \File Name   : WDT.c                                                                           */
/* \Author      : Salman Ali                                                                      */
/* \Version 	: 1.1                                                                             */
/* \Date        : 30\06\2016                                                                      */
/*                                                                                                */
/* @Description : WatchDog Timer Driver                                                           */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <compiler.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "WDT.h"
#include "MCLK.h"
#include "NVIC.h"
#include "OSC32KCTRL.h"

#include "WDT.h"
#include "WDT_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/* Structure Pointer to Access WDT System Registers  */
ST_WDT_SYS_REGS_t *p_stgWDTRegAccess = (ST_WDT_SYS_REGS_t *)WDT_BASE_ADDRESS;

#define WDT_PERIOD_RATE 			( 1000 )

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* Function Name   : void WDT_Handler(void)                                                       */
/*                                                                                                */
/* Description     : WDT System Handler                                                           */
/**************************************************************************************************/

void WDT_Handler(void)
{
	if(0 != (p_stgWDTRegAccess->INTFLAG & WDT_INTFLAG_EW_MSK))
	{
		/* Clear Flag */
		p_stgWDTRegAccess->INTFLAG = WDT_INTFLAG_EW_MSK;
	}
}

/**************************************************************************************************/
/* Function Name   : void WDT_Init(ST_WDT_INIT_PARAMS_t *p_stfWDTInitParams)                      */
/*                                                                                                */
/* Description     : This function used to initialize the WDT                                     */
/*                                                                                                */
/* In Params       : p_stfWDTInitParams                                                           */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

EN_WDT_STATUS_t WDT_Init(ST_WDT_INIT_PARAMS_t *p_stfWDTInitParams)
{
	/* WDT Clk Init */
	MCLK_PeriphClkInit(MCLK_APBA, MCLK_APBA_WDT);
	
	if(WDT_CheckAlwaysOn() || WDT_CheckEnable())
	{
		return WDT_ERROR;
	} 
	else 
	{
		if(EN_WDT_WINDOW_MODE == p_stfWDTInitParams->en_mModeSel) 
		{
			WDT_ConfigWindow(0x00);
		} 
		else 
		{
			CRITICAL_SECTION_ENTER();
			
			WDT_WaitForSync(WDT_SYNCBUSY_ENABLE_MASK | WDT_SYNCBUSY_WEN_MASK | WDT_SYNCBUSY_ALWAYSON_MASK);
	
			p_stgWDTRegAccess->CTRLA &= ~WDT_CTRLA_WEN_MSK;
			
			CRITICAL_SECTION_LEAVE();
		}

		WDT_WritePeriod(0x00);
	}
	
	WDT_SetTimeoutPriod(p_stfWDTInitParams->u32_mTimeOutPeriod, p_stfWDTInitParams->u32_mClkRate);
	
	WDT_Enable();
	
	return WDT_SUCCESS;
}

/**************************************************************************************************/
/* Function Name   : void WDT_ClearWDT(void)                                                      */
/*                                                                                                */
/* Description     : API to Clear the WDT                                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

EN_WDT_STATUS_t WDT_SetTimeoutPriod(INT32U u32_fTimeout, INT32U u32_fClkRate)
{
	INT64U            u64_lTmp = 0;
	INT8U             u8_lTmpReg = 0;
	INT32U            u32_lPeriodCycles;
	EN_WDT_PERIOD_CYCLE_t en_lTimeoutPeriod;
	
	/* Calc the period cycles corresponding to timeout period */
	u64_lTmp = (INT64U)(u32_fTimeout * u32_fClkRate);

	/* Check whether overflow*/
	if (u64_lTmp >> 32) 
	{
		return WDT_ERROR;
	}
	else
	{
		/* No Action */
	}

	u32_lPeriodCycles = (INT32U)u64_lTmp;
	
	/* Calc the register value corresponding to period cysles */
	switch(u32_lPeriodCycles) 
	{
	case WDT_CLK_8CYCLE *WDT_PERIOD_RATE:
		en_lTimeoutPeriod = WDT_PERIOD_8CYCLE;
		break;
	case WDT_CLK_16CYCLE *WDT_PERIOD_RATE:
		en_lTimeoutPeriod = WDT_PERIOD_16CYCLE;
		break;
	case WDT_CLK_32CYCLE *WDT_PERIOD_RATE:
		en_lTimeoutPeriod = WDT_PERIOD_32CYCLE;
		break;
	case WDT_CLK_64CYCLE *WDT_PERIOD_RATE:
		en_lTimeoutPeriod = WDT_PERIOD_64CYCLE;
		break;
	case WDT_CLK_128CYCLE *WDT_PERIOD_RATE:
		en_lTimeoutPeriod = WDT_PERIOD_128CYCLE;
		break;
	case WDT_CLK_256CYCLE *WDT_PERIOD_RATE:
		en_lTimeoutPeriod = WDT_PERIOD_256CYCLE;
		break;
	case WDT_CLK_512CYCLE *WDT_PERIOD_RATE:
		en_lTimeoutPeriod = WDT_PERIOD_512CYCLE;
		break;
	case WDT_CLK_1024CYCLE *WDT_PERIOD_RATE:
		en_lTimeoutPeriod = WDT_PERIOD_1024CYCLE;
		break;
	case WDT_CLK_2048CYCLE *WDT_PERIOD_RATE:
		en_lTimeoutPeriod = WDT_PERIOD_2048CYCLE;
		break;
	case WDT_CLK_4096CYCLE *WDT_PERIOD_RATE:
		en_lTimeoutPeriod = WDT_PERIOD_4096CYCLE;
		break;
	case WDT_CLK_8192CYCLE *WDT_PERIOD_RATE:
		en_lTimeoutPeriod = WDT_PERIOD_8192CYCLE;
		break;
	case WDT_CLK_16384CYCLE *WDT_PERIOD_RATE:
		en_lTimeoutPeriod = WDT_PERIOD_16384CYCLE;
		break;
	default:
		return WDT_ERROR;
	}
	
	CRITICAL_SECTION_ENTER();
	
	u8_lTmpReg = p_stgWDTRegAccess->CONFIG;
	u8_lTmpReg &= ~WDT_CONFIG_PER_MSK;
	u8_lTmpReg |= (INT8U)en_lTimeoutPeriod;
	p_stgWDTRegAccess->CONFIG = u8_lTmpReg;
	
	CRITICAL_SECTION_LEAVE();
	
	return WDT_SUCCESS;
}

/**************************************************************************************************/
/* Function Name   : void WDT_ClearWDT(void)                                                      */
/*                                                                                                */
/* Description     : API to Clear the WDT                                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

INT8U WDT_CheckAlwaysOn(void)
{
	INT8U u8_lTempReg = 0;
		
	WDT_WaitForSync(WDT_SYNCBUSY_ENABLE_MASK | WDT_SYNCBUSY_WEN_MASK | WDT_SYNCBUSY_ALWAYSON_MASK);
	
	u8_lTempReg = p_stgWDTRegAccess->CTRLA;
	
	u8_lTempReg = ((u8_lTempReg & WDT_CTRLA_ALWAYSON_MSK) >> WDT_CTRLA_ALWAYSON_OFFSET);
	
	return u8_lTempReg;
}

/**************************************************************************************************/
/* Function Name   : void WDT_ClearWDT(void)                                                      */
/*                                                                                                */
/* Description     : API to Clear the WDT                                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

INT8U WDT_CheckEnable(void)
{	
	INT8U u8_lTempReg = 0;
		
	WDT_WaitForSync(WDT_SYNCBUSY_ENABLE_MASK | WDT_SYNCBUSY_WEN_MASK | WDT_SYNCBUSY_ALWAYSON_MASK);
	
	u8_lTempReg = p_stgWDTRegAccess->CTRLA;
	
	u8_lTempReg = ((u8_lTempReg & WDT_CTRLA_ENABLE_MSK) >> WDT_CTRLA_ENABLE_OFFSET);
	
	return u8_lTempReg;
}

/**************************************************************************************************/
/* Function Name   : void WDT_ClearWDT(void)                                                      */
/*                                                                                                */
/* Description     : API to Clear the WDT                                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void WDT_Enable(void)
{
	CRITICAL_SECTION_ENTER();
	
	WDT_WaitForSync(WDT_SYNCBUSY_ENABLE_MASK | WDT_SYNCBUSY_WEN_MASK | WDT_SYNCBUSY_ALWAYSON_MASK);
	
	p_stgWDTRegAccess->CTRLA |= WDT_CTRLA_ENABLE_MASK;
	
	CRITICAL_SECTION_LEAVE();
}

/**************************************************************************************************/
/* Function Name   : void WDT_ClearWDT(void)                                                      */
/*                                                                                                */
/* Description     : API to Clear the WDT                                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void WDT_WaitForSync(INT32U u32_fSyncMask)
{
	while(p_stgWDTRegAccess->SYNCBUSY & u32_fSyncMask);
}


/**************************************************************************************************/
/* Function Name   : void WDT_ClearWDT(void)                                                      */
/*                                                                                                */
/* Description     : API to Clear the WDT                                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void WDT_ConfigWindow(INT8U u8_lWindowVal)
{
	INT8U u8_lTmpReg = 0;
	
	CRITICAL_SECTION_ENTER();
	
	u8_lTmpReg = p_stgWDTRegAccess->CONFIG;
	
	u8_lTmpReg &= ~WDT_CONFIG_WINDOW_MSK;
	
	u8_lTmpReg |= u8_lWindowVal << WDT_CONFIG_WINDOW_OFFSET;
	
	p_stgWDTRegAccess->CONFIG = u8_lTmpReg;
	
	CRITICAL_SECTION_LEAVE();
}

/**************************************************************************************************/
/* Function Name   : void WDT_ClearWDT(void)                                                      */
/*                                                                                                */
/* Description     : API to Clear the WDT                                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void WDT_WritePeriod(INT8U u8_lPeriod)
{
	INT8U u8_lTmpReg = 0;
	
	CRITICAL_SECTION_ENTER();
	
	u8_lTmpReg = p_stgWDTRegAccess->CONFIG;
	
	u8_lTmpReg &= ~WDT_CONFIG_PER_MSK;
	
	u8_lTmpReg |= (u8_lPeriod << WDT_CONFIG_PER_OFFSET);
	
	p_stgWDTRegAccess->CONFIG = u8_lTmpReg;
	
	CRITICAL_SECTION_LEAVE();
}
	
/**************************************************************************************************/
/* Function Name   : void WDT_ClearWDT(void)                                                      */
/*                                                                                                */
/* Description     : API to Clear the WDT                                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void WDT_Feed(void)
{
	CRITICAL_SECTION_ENTER();
	
	p_stgWDTRegAccess->CLEAR = WDT_CLEAR_CLEAR_KEY;
	
	CRITICAL_SECTION_LEAVE();
}

/**************************************************************************************************/
/* End of WDT.c                                                                                   */
/**************************************************************************************************/
