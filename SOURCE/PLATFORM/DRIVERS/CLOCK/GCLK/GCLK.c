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
/* \File Name   : GCLK_Priv.h                                                                     */
/* \Author      : Kishore D	                                                                      */
/* \Version 		: v1.0                                                                            */
/* \Date        : 23/08/2018                                                                      */
/*                                                                                                */
/* @Description : GCLK Driver Frame Work                                                          */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "GCLK.h"
#include "GCLK_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* GCLK Register Access Variable */
ST_GCLK_REGS_t * p_stgGCLKRegister = (ST_GCLK_REGS_t *)GCLK_BASE_ADDRESS;

/**************************************************************************************************/
/* Function Name   : void GCLK_Generator0Init(void)                                               */
/*                                                                                                */
/* Description     : This function is used to initialize the Generator 0                          */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void GCLK_Generator0Init(void)
{	
    INT32U u32_lTemp = 0;
    
    p_stgGCLKRegister->CTRLA = 0x01;
    
    while(p_stgGCLKRegister->SYNCBUSY & 0x01);
    
    u32_lTemp = 0x08 | (1 << 8) | (1 << 9) | (1 << 16);
    
    p_stgGCLKRegister->GENCTRL[0] = u32_lTemp;
    
    while(p_stgGCLKRegister->SYNCBUSY & 0x04);
    
    u32_lTemp = 0x06 | (1 << 8) | (1 << 9) | (1 << 16);
    
    p_stgGCLKRegister->GENCTRL[1] = u32_lTemp;
    
    while(p_stgGCLKRegister->SYNCBUSY & 0x04);
} 

/**************************************************************************************************/
/* Function Name   : void GCLK_PeripheralClockEnable(EN_GCLK_PERIPH_SEL_t en_fPeripheral)         */
/*                                                                                                */
/* Description     : This function is used to enables peripheral clock                            */
/*                                                                                                */
/* In Params       : en_fPeripheral                                                               */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void GCLK_PeripheralClockEnable(EN_GCLK_PERIPH_SEL_t en_fPeripheral)
{
	switch(en_fPeripheral)
	{
		case GCLK_DFLL_48_REF:
		{
			/* Enabling clock for ph ch 0 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[0] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_DPLL0:
		{
			/* Enabling clock for ph ch 1 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[1] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_DPLL1:
		{
			/* Enabling clock for ph ch 2 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[2] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_DPLL_32K:
		{
			/* Enabling clock for ph ch 3 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[3] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_EIC:
		{
			/* Enabling clock for ph ch 4 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[4] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_FREQM_MSR:
		{
			/* Enabling clock for ph ch 5 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[5] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_FREQM_REF:
		{
			/* Enabling clock for ph ch 6 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[6] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_SERCOM0_CORE:
		{
			/* Enabling clock for ph ch 7 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[7] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_SERCOM1_CORE:
		{
			/* Enabling clock for ph ch 8 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[8] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_TC0:
		{
			/* Enabling clock for ph ch 9 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[9] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;

		case GCLK_USB:
		{
			/* Enabling clock for ph ch 11 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[10] |= 0x01 | (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_EVSYS_CH0:
		{
			/* Enabling clock for ph ch 11 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[11] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_EVSYS_CH1:
		{
			/* Enabling clock for ph ch 12 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[12] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_EVSYS_CH2:
		{
			/* Enabling clock for ph ch 12 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[13] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_EVSYS_CH3:
		{
			/* Enabling clock for ph ch 13 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[14] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_EVSYS_CH4:
		{
			/* Enabling clock for ph ch 14 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[15] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_EVSYS_CH5:
		{
			/* Enabling clock for ph ch 15 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[16] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_EVSYS_CH6:
		{
			/* Enabling clock for ph ch 16 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[17] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_EVSYS_CH7:
		{
			/* Enabling clock for ph ch 17 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[18] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_EVSYS_CH8:
		{
			p_stgGCLKRegister->PCHCTRL[19] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_EVSYS_CH9:
		{
			p_stgGCLKRegister->PCHCTRL[20] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_EVSYS_CH10:
		{
			p_stgGCLKRegister->PCHCTRL[21] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_EVSYS_CH11:
		{
			p_stgGCLKRegister->PCHCTRL[22] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_SERCOM2_CORE:
		{
			p_stgGCLKRegister->PCHCTRL[23] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_SERCOM3_CORE:
		{
			p_stgGCLKRegister->PCHCTRL[24] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_TCC0:
		{
			p_stgGCLKRegister->PCHCTRL[25] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_TC2:
		{
			/* Enabling clock for ph ch 25 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[26] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_CAN0:
		{
			/* Enabling clock for ph ch 25 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[27] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_CAN1:
		{
			/* Enabling clock for ph ch 26 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[28] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_TCC2:
		{
			/* Enabling clock for ph ch 27 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[29] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_TC4:
		{
			/* Enabling clock for ph ch 27 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[30] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_PDEC:
		{
			/* Enabling clock for ph ch 28 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[31] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_AC:
		{
			/* Enabling clock for ph ch 28 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[32] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_CCL:
		{
			/* Enabling clock for ph ch 29 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[33] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_SERCOM4_CORE:
		{
			/* Enabling clock for ph ch 30 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[34] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_SERCOM5_CORE:
		{
			/* Enabling clock for ph ch 31 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[35] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_SERCOM6_CORE:
		{
			/* Enabling clock for ph ch 32 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[36] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_SERCOM7_CORE:
		{
			/* Enabling clock for ph ch 33 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[37] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_TCC4:
		{
			/* Enabling clock for ph ch 34 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[38] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_TC6:
		{
			/* Enabling clock for ph ch 34 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[39] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_ADC0:
		{
			/* Enabling clock for ph ch 34 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[40] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_ADC1:
		{
			/* Enabling clock for ph ch 34 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[41] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_DAC:
		{
			/* Enabling clock for ph ch 34 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[42] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;
		case GCLK_I2S0:
		{
			/* Enabling clock for ph ch 34 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[43] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;		
		case GCLK_I2S1:
		{
			/* Enabling clock for ph ch 34 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[44] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;		
		case GCLK_SDHC0:
		{
			/* Enabling clock for ph ch 34 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[45] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;	
		case GCLK_SDHC1:
		{
			/* Enabling clock for ph ch 34 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[46] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;	
		case GCLK_CM4_TRACE:
		{
			/* Enabling clock for ph ch 34 and gen 0 as source */
			p_stgGCLKRegister->PCHCTRL[47] |= (1 << GCLK_PCHCTRL_CHEN_POS);
		}
		break;			
		default:
		{
			/* NOP */
		}
		break;
	}
}

/**************************************************************************************************/
/* Function Name   : void GCLK_Enable_SERCOM_Clock(EN_GCLK_SERCOM_CH_SEL_t en_fChannel)           */
/*                                                                                                */
/* Description     : This function is used to enable the SERCOM Clock                             */
/*                                                                                                */
/* In Params       : en_fChannel                                                                  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void GCLK_EnableSERCOMClock(EN_GCLK_SERCOM_CH_SEL_t en_fChannel)
{
	switch(en_fChannel)
	{
		case GCLK_SERCOM_CH_0:
		{
			GCLK_PeripheralClockEnable(GCLK_SERCOM0_CORE);
		}
		break;
		case GCLK_SERCOM_CH_1:
		{
			GCLK_PeripheralClockEnable(GCLK_SERCOM1_CORE);
		}
		break;
		case GCLK_SERCOM_CH_2:
		{
			GCLK_PeripheralClockEnable(GCLK_SERCOM2_CORE);
		}
		break;
		case GCLK_SERCOM_CH_3:
		{
			GCLK_PeripheralClockEnable(GCLK_SERCOM3_CORE);
		}
		break;
		case GCLK_SERCOM_CH_4:
		{
			GCLK_PeripheralClockEnable(GCLK_SERCOM4_CORE);
		}
		break;
		case GCLK_SERCOM_CH_5:
		{
			GCLK_PeripheralClockEnable(GCLK_SERCOM5_CORE);
		}
		break;
		default:
		{
				/* NOP */
		}
		break;
	}
}

/**************************************************************************************************/
/* End of GCLK.c                                                                                  */
/**************************************************************************************************/
