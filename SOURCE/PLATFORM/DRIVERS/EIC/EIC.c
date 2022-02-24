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
/* \File Name   : EIC.c                                                                           */
/* \Author      : Ravi Ranjan Kumar                                                               */
/* \Version 	: 1.0                                                                             */
/* \Date        : 07/09/2018                                                                      */
/*                                                                                                */
/* @Description : EIC Driver     		                                                          */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "MCLK.h"
#include "NVIC.h"
#include "GCLK.h"

#include "EIC.h"
#include "EIC_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Structure pointer to access EIC system registers */
ST_EIC_REG_t *p_stgEICBaseRegs = (ST_EIC_REG_t *)EIC_BASE_ADDRESS;

/* EIC resutlt Handler */
void (*fp_gEICUserHandler[16])(void);

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_0_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_0_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_0_MASK;
		
		if(PNULL != (fp_gEICUserHandler[0]))
		{
			fp_gEICUserHandler[0]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_1_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_1_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_1_MASK;
		
		if(PNULL != (fp_gEICUserHandler[1]))
		{
			fp_gEICUserHandler[1]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_2_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & EIC_INTFLAG_2_MASK))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG = EIC_INTFLAG_2_MASK;
		
		if(PNULL != (fp_gEICUserHandler[2]))
		{
			fp_gEICUserHandler[2]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_3_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_3_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_3_MASK;
		
		if(PNULL != (fp_gEICUserHandler[3]))
		{
			fp_gEICUserHandler[3]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_4_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_4_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_4_MASK;
		
		if(PNULL != (fp_gEICUserHandler[4]))
		{
			fp_gEICUserHandler[4]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_5_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_5_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_5_MASK;
		
		if(PNULL != (fp_gEICUserHandler[5]))
		{
			fp_gEICUserHandler[5]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_6_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_6_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_6_MASK;
		
		if(PNULL != (fp_gEICUserHandler[6]))
		{
			fp_gEICUserHandler[6]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_7_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_7_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_7_MASK;
		
		if(PNULL != (fp_gEICUserHandler[7]))
		{
			fp_gEICUserHandler[7]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_8_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_8_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_8_MASK;
		
		if(PNULL != (fp_gEICUserHandler[8]))
		{
			fp_gEICUserHandler[8]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_9_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_9_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_9_MASK;
		
		if(PNULL != (fp_gEICUserHandler[9]))
		{
			fp_gEICUserHandler[9]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_10_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_10_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_10_MASK;
		
		if(PNULL != (fp_gEICUserHandler[10]))
		{
			fp_gEICUserHandler[10]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_11_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_11_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_11_MASK;
		
		if(PNULL != (fp_gEICUserHandler[11]))
		{
			fp_gEICUserHandler[11]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_12_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_12_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_12_MASK;
		
		if(PNULL != (fp_gEICUserHandler[12]))
		{
			fp_gEICUserHandler[12]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_13_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_13_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_3_MASK;
		
		if(PNULL != (fp_gEICUserHandler[13]))
		{
			fp_gEICUserHandler[13]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_14_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_14_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_14_MASK;
		
		if(PNULL != (fp_gEICUserHandler[14]))
		{
			fp_gEICUserHandler[14]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : EIC Handler                                                                  */
/*                                                                                                */
/**************************************************************************************************/

void EIC_15_Handler(void)
{
	if(0 != (p_stgEICBaseRegs->INTFLAG & (1 << EIC_INTFLAG_15_INDEX_MASK)))
	{
		/* Clear Interrupt Flag */
		p_stgEICBaseRegs->INTFLAG |= EIC_INTFLAG_15_MASK;
		
		if(PNULL != (fp_gEICUserHandler[15]))
		{
			fp_gEICUserHandler[15]();
		}
	}
	else
	{
		/* No Action */
	}
}

/**************************************************************************************************/
/* Function Name   : void EIC_Init(ST_EIC_CONFIG_PARAMS_t *p_stfEICParams)      	              */
/*                                                                                                */
/* Description     : Function to Initialize EIC                                                   */
/*                                                                                                */
/* In Params       : ST_EIC_CONFIG_PARAMS_t *p_stfEICParams                      	              */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : Void                                                                         */
/**************************************************************************************************/

void EIC_Init(ST_EIC_PARAMS_t *p_stfEICParams)
{	
    static INT8U u8_lSwrst = 0;
    INT8U u8_lExtIntNo = p_stfEICParams->u32_mExtnlIntNo;
    INT8U u8_lInSence = p_stfEICParams->en_mInputSense;
    if(0 == u8_lSwrst)
    {
        u8_lSwrst = 1;
        
        /* Enabling CLK */
        MCLK_PeriphClkInit(MCLK_APBA, MCLK_APBA_EIC);

        /* Enabling Clock for EIC */
        GCLK_PeripheralClockEnable(GCLK_EIC);
        
        p_stgEICBaseRegs->CTRLA |= 0x01;
        
        while(p_stgEICBaseRegs->SYNCBUSY & EIC_SYNCBUSY_SWRST_MASK);
    }
    else
    {
        /* No Action */
    }
    
    /* Disable EIC */
	p_stgEICBaseRegs->CTRLA &= ~EIC_CTRLA_ENABLE_MASK;
	
	/*Wait for Sync Enable bit */
    while(p_stgEICBaseRegs->SYNCBUSY & EIC_SYNCBUSY_ENABLE_MASK);
    	 
    p_stgEICBaseRegs->CONFIG[u8_lExtIntNo/8] |= ((u8_lInSence | 0x8) << ((u8_lExtIntNo%8) * 4));
    
	switch(p_stfEICParams->u32_mExtnlIntNo)
	{
		case 0:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_0_IRQ);
		}
		break;
		case 1:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_1_IRQ);
		}
		break;
		case 2:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_2_IRQ);
		}
		break;
		case 3:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_3_IRQ);
		}
		break;
		case 4:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_4_IRQ);
	  	}
		break;
		case 5:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_5_IRQ);
		}
		break;
		case 6:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_6_IRQ);
		}
		break;
		case 7:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_7_IRQ);
		}
		break;
		case 8:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_8_IRQ);
		}
		break;
		case 9:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_9_IRQ);
		}
		break;
		case 10:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_10_IRQ);
		}
		break;
		case 11:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_11_IRQ);
		}
		break;
		case 12:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_12_IRQ);
		}
		break;
		case 13:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_13_IRQ);
		}
		break;
		case 14:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_14_IRQ);
		}
		break;
		case 15:
		{
			/* Enabling NVIC */
			NVIC_EnableInterrupt(EIC_15_IRQ);
		}
		break;
		default:
		break;
	}
	
	/* Enabling External Interrupt */
	p_stgEICBaseRegs->INTENSET |= (1 << p_stfEICParams->u32_mExtnlIntNo);

	/* Assigning Handlers */
	fp_gEICUserHandler[p_stfEICParams->u32_mExtnlIntNo] = p_stfEICParams->fp_UserHandler;
     
    /*Enable EIC */
    p_stgEICBaseRegs->CTRLA |= EIC_CTRLA_ENABLE_MASK;
    while(p_stgEICBaseRegs->SYNCBUSY & EIC_CTRLA_ENABLE_MASK);
}

/**************************************************************************************************/
/* Function Name   : void EXTNLINT_Config(INT32U u32_fExtnlIntNo,INT32U u32_fInputSense)          */
/*                                                                                                */
/* Description     : Configure Ext Int line                                                       */
/*                                                                                                */
/* In Params       : INT32U u32_fExtnlIntNo,INT32U u32_fInputSense                                */
/*                                                                                                */
/* Out Params      : NOne                                                                         */
/*                                                                                                */
/* Return Value    : Void                                                                         */
/**************************************************************************************************/

void EIC_ExtIntConfig(INT32U u32_fExtnlIntNo,INT32U u32_fInputSense)
{
	switch(u32_fExtnlIntNo)
	{
		case 0:
		{
			p_stgEICBaseRegs->CONFIG[0] |= (u32_fInputSense << EIC_CONFIG_SENSE0_Pos);			
			p_stgEICBaseRegs->CONFIG[0] |= (1UL << EIC_CONFIG_FILTEN0_Pos);
		}
		break;
		case 1:
		{
			p_stgEICBaseRegs->CONFIG[0] |= u32_fInputSense << EIC_CONFIG_SENSE1_Pos;			
			p_stgEICBaseRegs->CONFIG[0] |= 1UL << EIC_CONFIG_FILTEN1_Pos;
		}
		break;
		case 2:
		{
			p_stgEICBaseRegs->CONFIG[0] |= u32_fInputSense << EIC_CONFIG_SENSE2_Pos;			
			p_stgEICBaseRegs->CONFIG[0] |= 1UL << EIC_CONFIG_FILTEN2_Pos;
		}
		break;
		case 3:
		{
			p_stgEICBaseRegs->CONFIG[0] |= u32_fInputSense << EIC_CONFIG_SENSE3_Pos;
			p_stgEICBaseRegs->CONFIG[0] |= 1UL << EIC_CONFIG_FILTEN3_Pos;
		}
		break;
		case 4:
		{
			p_stgEICBaseRegs->CONFIG[0] |= u32_fInputSense << EIC_CONFIG_SENSE4_Pos;			
			p_stgEICBaseRegs->CONFIG[0] |= 1UL << EIC_CONFIG_FILTEN4_Pos;
	  }
		break;
		case 5:
		{
			p_stgEICBaseRegs->CONFIG[0] |= u32_fInputSense << EIC_CONFIG_SENSE5_Pos;			
			p_stgEICBaseRegs->CONFIG[0] |= 1UL << EIC_CONFIG_FILTEN5_Pos;
		}
		break;
		case 6:
		{
			p_stgEICBaseRegs->CONFIG[0] |= u32_fInputSense << EIC_CONFIG_SENSE6_Pos;			
			p_stgEICBaseRegs->CONFIG[0] |= 1UL << EIC_CONFIG_FILTEN6_Pos;
		}
		break;
		case 7:
		{
			p_stgEICBaseRegs->CONFIG[0] |= u32_fInputSense << EIC_CONFIG_SENSE7_Pos;			
			p_stgEICBaseRegs->CONFIG[0] |= 1UL << EIC_CONFIG_FILTEN7_Pos;
		}
		break;
		case 8:
		{
			p_stgEICBaseRegs->CONFIG[1] |= u32_fInputSense << EIC_CONFIG_SENSE0_Pos;			
			p_stgEICBaseRegs->CONFIG[1] |= 1UL << EIC_CONFIG_FILTEN0_Pos;
		}
		break;
		case 9:
		{
			p_stgEICBaseRegs->CONFIG[1] |= u32_fInputSense << EIC_CONFIG_SENSE1_Pos;			
			p_stgEICBaseRegs->CONFIG[1] |= 1UL << EIC_CONFIG_FILTEN1_Pos;
		}
		break;
		case 10:
		{
			p_stgEICBaseRegs->CONFIG[1] |= u32_fInputSense << EIC_CONFIG_SENSE2_Pos;			
			p_stgEICBaseRegs->CONFIG[1] |= 1UL << EIC_CONFIG_FILTEN2_Pos;
		}
		break;
		case 11:
		{
			p_stgEICBaseRegs->CONFIG[1] |= u32_fInputSense << EIC_CONFIG_SENSE3_Pos;			
			p_stgEICBaseRegs->CONFIG[1] |= 1UL << EIC_CONFIG_FILTEN3_Pos;
		}
		break;
		case 12:
		{
			p_stgEICBaseRegs->CONFIG[1] |= u32_fInputSense << EIC_CONFIG_SENSE4_Pos;			
			p_stgEICBaseRegs->CONFIG[1] |= 1UL << EIC_CONFIG_FILTEN4_Pos;
		}
		break;
		case 13:
		{
			p_stgEICBaseRegs->CONFIG[1] |= u32_fInputSense << EIC_CONFIG_SENSE5_Pos;			
			p_stgEICBaseRegs->CONFIG[1] |= 1UL << EIC_CONFIG_FILTEN5_Pos;
		}
		break;
		case 14:
		{
			p_stgEICBaseRegs->CONFIG[1] |= u32_fInputSense << EIC_CONFIG_SENSE6_Pos;			
			p_stgEICBaseRegs->CONFIG[1] |= 1UL << EIC_CONFIG_FILTEN6_Pos;
		}
		break;
		case 15:
		{
			p_stgEICBaseRegs->CONFIG[1] |= u32_fInputSense << EIC_CONFIG_SENSE7_Pos;			
			p_stgEICBaseRegs->CONFIG[1] |= 1UL << EIC_CONFIG_FILTEN7_Pos;
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
/* Function Name   : void EIC_SoftReset(void)                                                     */
/*                                                                                                */
/* Description     : API to perform Software Reset                                                */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : Void                                                                         */
/**************************************************************************************************/

void EIC_SoftReset(void)
{
	/* Performing Software Reset */
	p_stgEICBaseRegs->CTRLA = EIC_CTRLA_SWRST_MASK;
}

/**************************************************************************************************/
/* Function Name   : void EIC_Enable(void)                                                        */
/*                                                                                                */
/* Description     : Api to Enable EIC                                                            */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : Void                                                                         */
/**************************************************************************************************/

void EIC_Enable(void)
{
	/*Wait for Sync Enable bit */
    while(p_stgEICBaseRegs->SYNCBUSY & (EIC_SYNCBUSY_ENABLE_MASK | EIC_SYNCBUSY_SWRST_MASK));
	
	/*Enable EIC */
	p_stgEICBaseRegs->CTRLA |= EIC_CTRLA_ENABLE_MASK;
}

/**************************************************************************************************/
/* Function Name   : void EIC_Disable(void)                                                       */
/*                                                                                                */
/* Description     : API to disable EIC                                                           */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : Void                                                                         */
/**************************************************************************************************/

void EIC_Disable(void)
{
	/*Enable EIC */
	p_stgEICBaseRegs->CTRLA &= ~EIC_CTRLA_ENABLE_MASK;
	
	/*Wait for Sync Enable bit */
    while(p_stgEICBaseRegs->SYNCBUSY & EIC_SYNCBUSY_ENABLE_MASK);
}

/**************************************************************************************************/
/* Function Name   : void EIC_InterruptDisable(INT32U u32_fExtnlIntNo)                            */
/*                                                                                                */
/* Description     : This funtion is used to disable a interrupt                                  */
/*                                                                                                */
/* In Params       : u32_fExtnlIntNo                                                              */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void EIC_Debounce(INT32U u32_fExtnlIntNo)
{
	p_stgEICBaseRegs->DPRESCALER |= (1 << 3);
	
	p_stgEICBaseRegs->DEBOUNCEN |= (1 << u32_fExtnlIntNo);
}

/**************************************************************************************************/
/* Function Name   : void EIC_InterruptEnable(INT32U u32_fExtnlIntNo)                             */
/*                                                                                                */
/* Description     : This function is used to enable a interrupt                                  */
/*                                                                                                */
/* In Params       : u32_fExtnlIntNo                                                              */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void EIC_InterruptEnable(INT32U u32_fExtnlIntNo)
{
	p_stgEICBaseRegs->INTENSET |= (1 << u32_fExtnlIntNo);
}

/**************************************************************************************************/
/* Function Name   : void EIC_InterruptDisable(INT32U u32_fExtnlIntNo)                            */
/*                                                                                                */
/* Description     : This funtion is used to disable a interrupt                                  */
/*                                                                                                */
/* In Params       : u32_fExtnlIntNo                                                              */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void EIC_InterruptDisable(INT32U u32_fExtnlIntNo)
{
	p_stgEICBaseRegs->INTENCLR |= (1 << u32_fExtnlIntNo);
}

/**************************************************************************************************/
/* Function Name   : void EIC_ExtIntWithEventsInit(INT32U u32_fExtnlIntNo, EN_EXTNL_SENSE_t \     */
/*                                                                            en_fInputSense)     */
/*                                                                                                */
/* Description     : This function is used to initializes the ExtInt using event                  */
/*                                                                                                */
/* In Params       : EN_EXTNL_SENSE_t, en_fInputSense                                             */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void EIC_ExtIntWithEventsInit(INT32U u32_fExtnlIntNo, EN_EXTNL_SENSE_t en_fInputSense)
{
	static INT32U u32_lFirstFlag = 0;
	
	/* Enabling Clock for EIC */
	GCLK_PeripheralClockEnable(GCLK_EIC);
	
	/*Disable EIC */
	EIC_Disable();
	
	/* Perform Software RESET */
	if(u32_lFirstFlag == 0)
	{
		EIC_SoftReset();
		
		u32_lFirstFlag = 1;
	}
	else
	{
			/* NOP */
	}
	
	/*Configuring desired EXTINT and selecting input sense level */
	EIC_ExtIntConfig(u32_fExtnlIntNo,en_fInputSense);
	
	/* Enabling Events for corresponding EIC line */
	p_stgEICBaseRegs->EVCTRL |= (1 << u32_fExtnlIntNo);
	
	/* Enable EIC */
	EIC_Enable();
}

/**************************************************************************************************/
/* End of EIC.c                                                                                   */
/**************************************************************************************************/
