/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2015, Think Embedded Pvt. Ltd. (TEPL)	                  */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : TCC.c                                                                           */
/* \Author      : Salman Ali                                                                      */
/* \Version 	: 1.1                                                                             */
/* \Date        : 20/11/2015  			                                                  */
/* @Description : TCC  Driver                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "TCC.h"
#include "TCC_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Structure Pointer to  Access TCC System Registers */
ST_TCC_REGS_t *p_stgTCCREGS[MAX_TCC_SLICES] = {	
                                                (ST_TCC_REGS_t *)TCC0_BASE_ADDRESS,
                                                (ST_TCC_REGS_t *)TCC1_BASE_ADDRESS,
                                                (ST_TCC_REGS_t *)TCC2_BASE_ADDRESS,
                                                (ST_TCC_REGS_t *)TCC3_BASE_ADDRESS,
                                                (ST_TCC_REGS_t *)TCC4_BASE_ADDRESS,
                                              };

/* TCC User Handlers */
ST_TCC_EVENT_PARAMS_t *p_stgUserHandlerTCC[MAX_TCC_SLICES] = {PNULL, };

/* TCC Capture User Handlers */
ST_TCC_CAPTURE_PARAMS_t *p_stgCaptureUserHandler[MAX_TCC_SLICES] = {PNULL,};

INT8U u8_gTimerEvent = 0;

/**************************************************************************************************/
/* Function Name   : void TCC0_1_Handler(void)                                                    */
/*                                                                                                */
/* Description     : TCC1 TIMER1  Handler  Definition                                             */
/*                                                                                                */
/**************************************************************************************************/

void TCC0_0_Handler(void)
{
    /* Checking for Int MC1 Flag */
    if(p_stgTCCREGS[0]->INTFLAG & TCC_INTFLAG_MC0_MASK)
    {
        /* Clear MC0 Interrupt flag */
		p_stgTCCREGS[0]->INTFLAG = TCC_INTFLAG_MC0_MASK;
		
        if(1 == u8_gTimerEvent)
        {
            if(PNULL != (p_stgUserHandlerTCC[0]->fp_User_Handler))
            {
                /* Calling User Handler */
                p_stgUserHandlerTCC[0]->fp_User_Handler();
            }
            else
            {
                /* No Action */
            }
        }
        else
        {
            if(PNULL != (p_stgCaptureUserHandler[0]->fp_User_Handler))
            {
                /* Calling User Handler */
                p_stgCaptureUserHandler[0]->fp_User_Handler();
            }
            else
            {
                /* No Action */
            }
        }
    }
}

/**************************************************************************************************/
/* Function Name   : void TCC0_1_Handler(void)                                                    */
/*                                                                                                */
/* Description     : TCC1 TIMER1  Handler  Definition                                             */
/*                                                                                                */
/**************************************************************************************************/

void TCC0_1_Handler(void)
{
    /* Checking for Int MC1 Flag */
    if(p_stgTCCREGS[0]->INTFLAG & TCC_INTFLAG_MC1_MASK)
    {
        /* Clear MC0 Interrupt flag */
		p_stgTCCREGS[0]->INTFLAG = TCC_INTFLAG_MC1_MASK;
		
        if(1 == u8_gTimerEvent)
        {
            if(PNULL != (p_stgUserHandlerTCC[0]->fp_User_Handler))
            {
                /* Calling User Handler */
                p_stgUserHandlerTCC[0]->fp_User_Handler();
            }
            else
            {
                /* No Action */
            }
        }
        else
        {
            if(PNULL != (p_stgCaptureUserHandler[0]->fp_User_Handler))
            {
                /* Calling User Handler */
                p_stgCaptureUserHandler[0]->fp_User_Handler();
            }
            else
            {
                /* No Action */
            }
        }
    }
}

/**************************************************************************************************/
/* Function Name   : void TCC0_2_Handler(void)                                                    */
/*                                                                                                */
/* Description     : TCC1 TIMER1  Handler  Definition                                             */
/*                                                                                                */
/**************************************************************************************************/

void TCC0_2_Handler(void)
{
    /* Checking for Int MC2 Flag */
    if(p_stgTCCREGS[0]->INTFLAG & TCC_INTFLAG_MC2_MASK)
    {
        /* Clear MC0 Interrupt flag */
		p_stgTCCREGS[0]->INTFLAG = TCC_INTFLAG_MC2_MASK;
		
        if(1 == u8_gTimerEvent)
        {
            if(PNULL != (p_stgUserHandlerTCC[0]->fp_User_Handler))
            {
                /* Calling User Handler */
                p_stgUserHandlerTCC[0]->fp_User_Handler();
            }
            else
            {
                /* No Action */
            }
        }
        else
        {
            if(PNULL != (p_stgCaptureUserHandler[0]->fp_User_Handler))
            {
                /* Calling User Handler */
                p_stgCaptureUserHandler[0]->fp_User_Handler();
            }
            else
            {
                /* No Action */
            }
        }
    }
}

/**************************************************************************************************/
/* Function Name   : void TCC0_3_Handler(void)                                                    */
/*                                                                                                */
/* Description     : TCC1 TIMER1  Handler  Definition                                             */
/*                                                                                                */
/**************************************************************************************************/

void TCC0_3_Handler(void)
{
     /* Checking for Int MC1 Flag */
    if(p_stgTCCREGS[0]->INTFLAG & TCC_INTFLAG_MC3_MASK)
    {
        /* Clear MC0 Interrupt flag */
		p_stgTCCREGS[0]->INTFLAG = TCC_INTFLAG_MC3_MASK;
		
        if(1 == u8_gTimerEvent)
        {
            if(PNULL != (p_stgUserHandlerTCC[0]->fp_User_Handler))
            {
                /* Calling User Handler */
                p_stgUserHandlerTCC[0]->fp_User_Handler();
            }
            else
            {
                /* No Action */
            }
        }
        else
        {
            if(PNULL != (p_stgCaptureUserHandler[0]->fp_User_Handler))
            {
                /* Calling User Handler */
                p_stgCaptureUserHandler[0]->fp_User_Handler();
            }
            else
            {
                /* No Action */
            }
        }
    }
}

/**************************************************************************************************/
/* Function Name   : void TCC0_4_Handler(void)                                                    */
/*                                                                                                */
/* Description     : TCC1 TIMER1  Handler  Definition                                             */
/*                                                                                                */
/**************************************************************************************************/

void TCC0_4_Handler(void)
{
     /* Checking for Int MC1 Flag */
    if(p_stgTCCREGS[0]->INTFLAG & TCC_INTFLAG_MC4_MASK)
    {
        /* Clear MC0 Interrupt flag */
		p_stgTCCREGS[0]->INTFLAG = TCC_INTFLAG_MC4_MASK;
		
        if(1 == u8_gTimerEvent)
        {
            if(PNULL != (p_stgUserHandlerTCC[0]->fp_User_Handler))
            {
                /* Calling User Handler */
                p_stgUserHandlerTCC[0]->fp_User_Handler();
            }
            else
            {
                /* No Action */
            }
        }
        else
        {
            if(PNULL != (p_stgCaptureUserHandler[0]->fp_User_Handler))
            {
                /* Calling User Handler */
                p_stgCaptureUserHandler[0]->fp_User_Handler();
            }
            else
            {
                /* No Action */
            }
        }
    }
}

/**************************************************************************************************/
/* Function Name   : void TCC0_4_Handler(void)                                                    */
/*                                                                                                */
/* Description     : TCC1 TIMER1  Handler  Definition                                             */
/*                                                                                                */
/**************************************************************************************************/

void TCC0_5_Handler(void)
{
     /* Checking for Int MC1 Flag */
    if(p_stgTCCREGS[0]->INTFLAG & TCC_INTFLAG_MC5_MASK)
    {
        /* Clear MC0 Interrupt flag */
		p_stgTCCREGS[0]->INTFLAG = TCC_INTFLAG_MC5_MASK;
		
        if(1 == u8_gTimerEvent)
        {
            if(PNULL != (p_stgUserHandlerTCC[0]->fp_User_Handler))
            {
                /* Calling User Handler */
                p_stgUserHandlerTCC[0]->fp_User_Handler();
            }
            else
            {
                /* No Action */
            }
        }
        else
        {
            if(PNULL != (p_stgCaptureUserHandler[0]->fp_User_Handler))
            {
                /* Calling User Handler */
                p_stgCaptureUserHandler[0]->fp_User_Handler();
            }
            else
            {
                /* No Action */
            }
        }
    }
}

/**************************************************************************************************/
/* Function Name   : void TCC1_Handler(void)                                                      */
/*                                                                                                */
/* Description     : TCC1 TIMER1  Handler  Definition                                             */
/*                                                                                                */
/**************************************************************************************************/

void TCC1_0_Handler(void)
{
     /* Checking for Int MC0 Flag */
     if(p_stgTCCREGS[1]->INTFLAG & TCC_INTFLAG_MC0_MASK)
     {
        /* Clear OVF Interrupt flag */
        p_stgTCCREGS[1]->INTFLAG = TCC_INTFLAG_MC0_MASK;
                    
        if(PNULL != (p_stgUserHandlerTCC[1]->fp_User_Handler))
        {
            /* Calling User Handler */
            p_stgUserHandlerTCC[1]->fp_User_Handler();
        }
     }
}

/**************************************************************************************************/
/* Function Name   : void TCC1_Handler(void)                                                      */
/*                                                                                                */
/* Description     : TCC1 TIMER1  Handler  Definition                                             */
/*                                                                                                */
/**************************************************************************************************/

void TCC1_1_Handler(void)
{
     /* Checking for Int MC0 Flag */
     if(p_stgTCCREGS[1]->INTFLAG & TCC_INTFLAG_MC1_MASK)
     {
        /* Clear OVF Interrupt flag */
        p_stgTCCREGS[1]->INTFLAG = TCC_INTFLAG_MC1_MASK;
                    
        if(PNULL != (p_stgUserHandlerTCC[1]->fp_User_Handler))
        {
            /* Calling User Handler */
            p_stgUserHandlerTCC[1]->fp_User_Handler();
        }
     }
}

/**************************************************************************************************/
/* Function Name   : void TCC1_Handler(void)                                                      */
/*                                                                                                */
/* Description     : TCC1 TIMER1  Handler  Definition                                             */
/*                                                                                                */
/**************************************************************************************************/

void TCC1_2_Handler(void)
{
     /* Checking for Int MC0 Flag */
     if(p_stgTCCREGS[1]->INTFLAG & TCC_INTFLAG_MC2_MASK)
     {
        /* Clear OVF Interrupt flag */
        p_stgTCCREGS[1]->INTFLAG = TCC_INTFLAG_MC2_MASK;
                    
        if(PNULL != (p_stgUserHandlerTCC[1]->fp_User_Handler))
        {
            /* Calling User Handler */
            p_stgUserHandlerTCC[1]->fp_User_Handler();
        }
     }
}

/**************************************************************************************************/
/* Function Name   : void TCC1_Handler(void)                                                      */
/*                                                                                                */
/* Description     : TCC1 TIMER1  Handler  Definition                                             */
/*                                                                                                */
/**************************************************************************************************/

void TCC1_3_Handler(void)
{
     /* Checking for Int MC0 Flag */
     if(p_stgTCCREGS[1]->INTFLAG & TCC_INTFLAG_MC3_MASK)
     {
        /* Clear OVF Interrupt flag */
        p_stgTCCREGS[1]->INTFLAG = TCC_INTFLAG_MC3_MASK;
                    
        if(PNULL != (p_stgUserHandlerTCC[1]->fp_User_Handler))
        {
            /* Calling User Handler */
            p_stgUserHandlerTCC[1]->fp_User_Handler();
        }
     }
}

/**************************************************************************************************/
/* Function Name   : void TCC1_Handler(void)                                                      */
/*                                                                                                */
/* Description     : TCC1 TIMER1  Handler  Definition                                             */
/*                                                                                                */
/**************************************************************************************************/

void TCC1_4_Handler(void)
{
     /* Checking for Int MC0 Flag */
     if(p_stgTCCREGS[1]->INTFLAG & TCC_INTFLAG_MC4_MASK)
     {
        /* Clear OVF Interrupt flag */
        p_stgTCCREGS[1]->INTFLAG = TCC_INTFLAG_MC4_MASK;
                    
        if(PNULL != (p_stgUserHandlerTCC[1]->fp_User_Handler))
        {
            /* Calling User Handler */
            p_stgUserHandlerTCC[1]->fp_User_Handler();
        }
     }    
}

/**************************************************************************************************/
/* Function Name   : void TCC2_Handler(void)                                                      */
/*                                                                                                */
/* Description     : TCC2 TIMER  Handler  Definition                                              */
/*                                                                                                */
/**************************************************************************************************/

void TCC2_1_Handler(void)
{
    /* Checking for Int MC0 Flag */
    if(p_stgTCCREGS[2]->INTFLAG & TCC_INTFLAG_MC0_MASK)
    {
        /* Clear OVF Interrupt flag */
		p_stgTCCREGS[2]->INTFLAG = TCC_INTFLAG_MC0_MASK;
				
        if(PNULL != (p_stgUserHandlerTCC[2]->fp_User_Handler))
        {
            /* Calling User Handler */
            p_stgUserHandlerTCC[2]->fp_User_Handler();
        }
    }	
}

/**************************************************************************************************/
/* Function Name   : void TCC2_Handler(void)                                                      */
/*                                                                                                */
/* Description     : TCC2 TIMER  Handler  Definition                                              */
/*                                                                                                */
/**************************************************************************************************/

void TCC2_2_Handler(void)
{
    /* Checking for Int MC0 Flag */
    if(p_stgTCCREGS[2]->INTFLAG & TCC_INTFLAG_MC1_MASK)
    {
        /* Clear OVF Interrupt flag */
		p_stgTCCREGS[2]->INTFLAG = TCC_INTFLAG_MC1_MASK;
				
        if(PNULL != (p_stgUserHandlerTCC[2]->fp_User_Handler))
        {
            /* Calling User Handler */
            p_stgUserHandlerTCC[2]->fp_User_Handler();
        }
    }
	
}

/**************************************************************************************************/
/* Function Name   : void TCC2_Handler(void)                                                      */
/*                                                                                                */
/* Description     : TCC2 TIMER  Handler  Definition                                              */
/*                                                                                                */
/**************************************************************************************************/

void TCC2_3_Handler(void)
{
    /* Checking for Int MC0 Flag */
    if(p_stgTCCREGS[2]->INTFLAG & TCC_INTFLAG_MC2_MASK)
    {
        /* Clear OVF Interrupt flag */
		p_stgTCCREGS[2]->INTFLAG = TCC_INTFLAG_MC2_MASK;
				
        if(PNULL != (p_stgUserHandlerTCC[2]->fp_User_Handler))
        {
            /* Calling User Handler */
            p_stgUserHandlerTCC[2]->fp_User_Handler();
        }
    }
}

/**************************************************************************************************/
/* Function Name   : void TCC2_Handler(void)                                                      */
/*                                                                                                */
/* Description     : TCC2 TIMER  Handler  Definition                                              */
/*                                                                                                */
/**************************************************************************************************/

void TCC3_1_Handler(void)
{
    /* Checking for Int MC0 Flag */
    if(p_stgTCCREGS[3]->INTFLAG & TCC_INTFLAG_MC0_MASK)
    {
        /* Clear OVF Interrupt flag */
		p_stgTCCREGS[3]->INTFLAG = TCC_INTFLAG_MC0_MASK;
				
        if(PNULL != (p_stgUserHandlerTCC[3]->fp_User_Handler))
        {
            /* Calling User Handler */
            p_stgUserHandlerTCC[3]->fp_User_Handler();
        }
    }
}

/**************************************************************************************************/
/* Function Name   : void TCC2_Handler(void)                                                      */
/*                                                                                                */
/* Description     : TCC2 TIMER  Handler  Definition                                              */
/*                                                                                                */
/**************************************************************************************************/

void TCC3_2_Handler(void)
{
    /* Checking for Int MC0 Flag */
    if(p_stgTCCREGS[3]->INTFLAG & TCC_INTFLAG_MC1_MASK)
    {
        /* Clear OVF Interrupt flag */
		p_stgTCCREGS[3]->INTFLAG = TCC_INTFLAG_MC1_MASK;
				
        if(PNULL != (p_stgUserHandlerTCC[3]->fp_User_Handler))
        {
            /* Calling User Handler */
            p_stgUserHandlerTCC[3]->fp_User_Handler();
        }
    }
}

/**************************************************************************************************/
/* Function Name   : void TCC2_Handler(void)                                                      */
/*                                                                                                */
/* Description     : TCC2 TIMER  Handler  Definition                                              */
/*                                                                                                */
/**************************************************************************************************/

void TCC4_1_Handler(void)
{
    /* Checking for Int MC0 Flag */
    if(p_stgTCCREGS[4]->INTFLAG & TCC_INTFLAG_MC0_MASK)
    {
        /* Clear OVF Interrupt flag */
		p_stgTCCREGS[4]->INTFLAG = TCC_INTFLAG_MC0_MASK;
				
        if(PNULL != (p_stgUserHandlerTCC[4]->fp_User_Handler))
        {
            /* Calling User Handler */
            p_stgUserHandlerTCC[4]->fp_User_Handler();
        }
    }
}

/**************************************************************************************************/
/* Function Name   : void TCC2_Handler(void)                                                      */
/*                                                                                                */
/* Description     : TCC2 TIMER  Handler  Definition                                              */
/*                                                                                                */
/**************************************************************************************************/

void TCC4_2_Handler(void)
{
    /* Checking for Int MC0 Flag */
    if(p_stgTCCREGS[4]->INTFLAG & TCC_INTFLAG_MC1_MASK)
    {
        /* Clear OVF Interrupt flag */
		p_stgTCCREGS[4]->INTFLAG = TCC_INTFLAG_MC1_MASK;
				
        if(PNULL != (p_stgUserHandlerTCC[4]->fp_User_Handler))
        {
            /* Calling User Handler */
            p_stgUserHandlerTCC[4]->fp_User_Handler();
        }
    }
}

/**************************************************************************************************/
/* Function Name: 	void TCC_Init(ST_TCC_CONFIG_DATA_t *p_stfTCCConfigParams)                 */
/*                                                                                                */
/* Description	:	Configures the desired TCC				                  */
/*                                                                                                */
/* In Params	  :	ST_TCC_CONFIG_DATA_t *p_stfTCCConfig                                      */
/*                                                                                                */
/* Out Params  	:	None                                                                      */
/*                                                                                                */
/* Return Value	:	Void                              					  */
/*                                     							          */
/*                                                                                                */
/* Remarks	    :	None                                                                      */
/**************************************************************************************************/

void TCC_PwmInit(ST_TCC_PWM_CONFIG_t *p_stfTCCPwmConfigParams)
{
	INT32U u32_lPresclar =0,u32_lPeriodVal =0;
	INT32F f32_lComp0Val,f32_lComp1Val, f32_lComp2Val, f32_lComp3Val, f32_lComp4Val, \
                        f32_lComp5Val = 0;
	
	/* Clock = 48MHZ */
	INT32U	u32_lGCLK = SYSTEM_CLOCK;
	
	INT32U u32_lSlice = p_stfTCCPwmConfigParams->en_mTCCSlice;	
	
	if(u32_lSlice == 0)
	{
		/*Enabling clock for tcc 0*/
         MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_TCCn0);    
		GCLK_PeripheralClockEnable(GCLK_TCC0);
	}
	if(u32_lSlice == 1)
	{
		/*Enabling clock for tcc 0*/
        MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_TCCn1);
		GCLK_PeripheralClockEnable(GCLK_TCC0);
	}
	if(u32_lSlice == 2)
	{
		/*Enabling clock for tcc 0*/
         MCLK_PeriphClkInit(MCLK_APBC, MCLK_APBC_TCCn2);
		GCLK_PeripheralClockEnable(GCLK_TCC2);
	}
    if(u32_lSlice == 3)
	{
		/*Enabling clock for tcc 0*/
         MCLK_PeriphClkInit(MCLK_APBC, MCLK_APBC_TCCn3);
         GCLK_PeripheralClockEnable(GCLK_TCC2);
	}
    if(u32_lSlice == 4)
	{
		/*Enabling clock for tcc 0*/
         MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_TCC4);
		GCLK_PeripheralClockEnable(GCLK_TCC4);
	}
	else
	{
		/* NOP */
	}
	/* Disable TCC */
	TCC_Disable((EN_TCC_SLICE_t )u32_lSlice);
	
	switch(p_stfTCCPwmConfigParams->en_mPrescalar)
	{
		case TCC_DIV_1:
		{
			u32_lPresclar = 1;
		}
		break;
		case TCC_DIV_2:
		{
			u32_lPresclar = 2;
		}
		break;
		case TCC_DIV_4:
		{
			u32_lPresclar = 4;
		}
		break;
		case TCC_DIV_8:
		{
			u32_lPresclar = 8;
		}
		break;
		case TCC_DIV_16:
		{
			u32_lPresclar = 16;
		}
		break;
		case TCC_DIV_64:
		{
			u32_lPresclar = 64;
		}
		break;
		case TCC_DIV_256:
		{
			u32_lPresclar = 256;
		}
		break;
		case TCC_DIV_1024:
		{
			u32_lPresclar = 1024;
		}
		break;
		default:
		{
			/* NOP */
		}
		break;
	}		
	/* Performing Software Reset */
	TCC_SoftReset(p_stfTCCPwmConfigParams->en_mTCCSlice);
	
	/* Selecting Prescalar for timer */
	p_stgTCCREGS[u32_lSlice]->CTRLA |= \
					(p_stfTCCPwmConfigParams->en_mPrescalar << TCC_CTRLA_PRESCALAR_POS);
	
	/* Selecting Prescalar and Counter synchronization */
	p_stgTCCREGS[u32_lSlice]->CTRLA |= TCC_CTRLA_PRESYNC_PRESC_MASK;
		
	/* Calculating Period Value */
	u32_lPeriodVal = TCC_GetPeriodValue(p_stfTCCPwmConfigParams->u32_mPWMFreq,u32_lPresclar,u32_lGCLK);
	
    /* Setting Period Value */
    TCC_SetPeriodValue(p_stfTCCPwmConfigParams->en_mTCCSlice,u32_lPeriodVal);
    
	if(p_stfTCCPwmConfigParams->en_mCCxCh == CCx_CHANNEL_0)
	{
		/* Calculating Compare 0 Value */
		f32_lComp0Val =  TCC_GetCompareValue(p_stfTCCPwmConfigParams->f32_mComp0DutyCycle,u32_lPeriodVal);
		
		/* Setting Compare Value in Compare register 0 */
		TCC_SetCompareValue(p_stfTCCPwmConfigParams->en_mTCCSlice,CCx_CHANNEL_0,f32_lComp0Val);
	}
	
	if(p_stfTCCPwmConfigParams->en_mCCxCh == CCx_CHANNEL_1)
	{
		/* Calculating Compare 1 Value */
		f32_lComp1Val =  TCC_GetCompareValue(p_stfTCCPwmConfigParams->f32_mComp1DutyCycle,u32_lPeriodVal);
		
		/* Setting Compare Value in Compare register 1 */
		TCC_SetCompareValue(p_stfTCCPwmConfigParams->en_mTCCSlice,CCx_CHANNEL_1,f32_lComp1Val);
	}
	
	if(p_stfTCCPwmConfigParams->en_mCCxCh == CCx_CHANNEL_2)
	{
		/* Calculating Compare 2 Value */
		f32_lComp2Val =  TCC_GetCompareValue(p_stfTCCPwmConfigParams->f32_mComp2DutyCycle,u32_lPeriodVal);
		
		/* Setting Compare Value in Compare register 2 */
		TCC_SetCompareValue(p_stfTCCPwmConfigParams->en_mTCCSlice,CCx_CHANNEL_2,f32_lComp2Val);
	}
	
	if(p_stfTCCPwmConfigParams->en_mCCxCh == CCx_CHANNEL_3)
	{
		/* Calculating Compare 3 Value */
		f32_lComp3Val =  TCC_GetCompareValue(p_stfTCCPwmConfigParams->f32_mComp3DutyCycle,u32_lPeriodVal);
		
		/* Setting Compare Value in Compare register 3 */
		TCC_SetCompareValue(p_stfTCCPwmConfigParams->en_mTCCSlice,CCx_CHANNEL_3,f32_lComp3Val);
	}
    
    if(p_stfTCCPwmConfigParams->en_mCCxCh == CCx_CHANNEL_4)
	{
		/* Calculating Compare 3 Value */
		f32_lComp4Val =  TCC_GetCompareValue(p_stfTCCPwmConfigParams->f32_mComp4DutyCycle,u32_lPeriodVal);
		
		/* Setting Compare Value in Compare register 3 */
		TCC_SetCompareValue(p_stfTCCPwmConfigParams->en_mTCCSlice,CCx_CHANNEL_4,f32_lComp4Val);
	}
    
    if(p_stfTCCPwmConfigParams->en_mCCxCh == CCx_CHANNEL_5)
	{
		/* Calculating Compare 3 Value */
		f32_lComp5Val =  TCC_GetCompareValue(p_stfTCCPwmConfigParams->f32_mComp5DutyCycle,u32_lPeriodVal);
		
		/* Setting Compare Value in Compare register 3 */
		TCC_SetCompareValue(p_stfTCCPwmConfigParams->en_mTCCSlice,CCx_CHANNEL_5,f32_lComp5Val);
	}
    
	if(p_stfTCCPwmConfigParams->en_mCCxCh == CCx_ALL_CHANNELS)
	{
		/* Calculating Compare 0 Value */
		f32_lComp0Val =  TCC_GetCompareValue(p_stfTCCPwmConfigParams->f32_mComp0DutyCycle,u32_lPeriodVal);
		
		/* Setting Compare Value in Compare register 0 */
		TCC_SetCompareValue(p_stfTCCPwmConfigParams->en_mTCCSlice,CCx_CHANNEL_0,f32_lComp0Val);
		
		/* Calculating Compare 1 Value */
		f32_lComp1Val =  TCC_GetCompareValue(p_stfTCCPwmConfigParams->f32_mComp1DutyCycle,u32_lPeriodVal);
		
		/* Setting Compare Value in Compare register 1 */
		TCC_SetCompareValue(p_stfTCCPwmConfigParams->en_mTCCSlice,CCx_CHANNEL_1,f32_lComp1Val);
		
		/* Calculating Compare 2 Value */
		f32_lComp2Val =  TCC_GetCompareValue(p_stfTCCPwmConfigParams->f32_mComp2DutyCycle,u32_lPeriodVal);
		
		/* Setting Compare Value in Compare register 2 */
		TCC_SetCompareValue(p_stfTCCPwmConfigParams->en_mTCCSlice,CCx_CHANNEL_2,f32_lComp2Val);
		
		/* Calculating Compare 3 Value */
		f32_lComp3Val =  TCC_GetCompareValue(p_stfTCCPwmConfigParams->f32_mComp3DutyCycle,u32_lPeriodVal);
		
		/* Setting Compare Value in Compare register 3 */
		TCC_SetCompareValue(p_stfTCCPwmConfigParams->en_mTCCSlice,CCx_CHANNEL_3,f32_lComp3Val);
        
        /* Calculating Compare 4 Value */
		f32_lComp4Val =  TCC_GetCompareValue(p_stfTCCPwmConfigParams->f32_mComp4DutyCycle,u32_lPeriodVal);
		
		/* Setting Compare Value in Compare register 3 */
		TCC_SetCompareValue(p_stfTCCPwmConfigParams->en_mTCCSlice,CCx_CHANNEL_4, f32_lComp4Val);
        
        /* Calculating Compare 5 Value */
		f32_lComp5Val =  TCC_GetCompareValue(p_stfTCCPwmConfigParams->f32_mComp5DutyCycle,u32_lPeriodVal);
		
		/* Setting Compare Value in Compare register 3 */
		TCC_SetCompareValue(p_stfTCCPwmConfigParams->en_mTCCSlice,CCx_CHANNEL_5,f32_lComp3Val);
	}
	else
	{
		/* NOP */
	}
	
	/* Selecting Double Buffering */
	p_stgTCCREGS[u32_lSlice]->CTRLBCLR &= ~(1<<1);
	
	/* Configuring Output matrix 0*/
	p_stgTCCREGS[u32_lSlice]->WEXCTRL = TCC_OUTMX_0;
	
	/* Selecting waveform generation  */
	p_stgTCCREGS[u32_lSlice]->WAVE |= (p_stfTCCPwmConfigParams->en_mWaveType << 0);
	
	/* Waiting for Wave Sync */
	while((p_stgTCCREGS[u32_lSlice]->SYNCBUSY) & TCC_SYNCBUSY_WAVE_MASK);
	
	/*Enable Timer */
	TCC_Enable(p_stfTCCPwmConfigParams->en_mTCCSlice);
}

/**************************************************************************************************/
/* Function Name   : void TCC_CaptureInit(ST_TCC_CAPTURE_PARAMS_t *p_stfTCCCaptureParams)         */
/*                                                                                                */
/* Description     : This function is used to capture the incoming events                         */
/*                                                                                                */
/* In Params       : p_stfTCCCaptureParams                                                        */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TCC_CaptureEventInit(ST_TCC_CAPTURE_PARAMS_t *p_stfTCCCaptureParams)
{
    
	INT32U u32_lSlice = p_stfTCCCaptureParams->en_mTCCSlice;
	
	if(u32_lSlice == 0)
	{
		/* Enabling clock for tcc 0 */
		GCLK_PeripheralClockEnable(GCLK_TCC0);
	}
	if(u32_lSlice == 1)
	{
		/* Enabling clock for tcc 1 */
		GCLK_PeripheralClockEnable(GCLK_TCC0);
	}
	if(u32_lSlice == 2)
	{
		/* Enabling clock for tcc 2 */
		GCLK_PeripheralClockEnable(GCLK_TCC2);
	}
	else
	{
		/* NOP */
	}
    
	/* Disable TCC */
	TCC_Disable((EN_TCC_SLICE_t )u32_lSlice);
			
	/* Performing Software Reset */
	TCC_SoftReset(p_stfTCCCaptureParams->en_mTCCSlice);
	
	/* Selecting Prescalar for timer */
	p_stgTCCREGS[u32_lSlice]->CTRLA |= \
					(p_stfTCCCaptureParams->en_mPrescalar << TCC_CTRLA_PRESCALAR_POS);
	
	/* Selecting Prescalar and Counter synchronization */
	p_stgTCCREGS[u32_lSlice]->CTRLA |= TCC_CTRLA_PRESYNC_PRESC_MASK;
		
	if(p_stfTCCCaptureParams->en_mCCxCh == CCx_CHANNEL_0)
	{
        /* Enable CAPTURE Operation */
        p_stgTCCREGS[u32_lSlice]->CTRLA |= ( 1 << TCC_CTRLA_CPTEN0_POS );
       
        /* Generates Events on Capture */
        p_stgTCCREGS[u32_lSlice]->EVCTRL |= TCC_EVCTRL_MCEI0_MASK;
        
        //p_stgTCCREGS[u32_lSlice]->EVCTRL |= TCC_EVCTRL_MCEO0_MASK;
		
	}
    
	if(p_stfTCCCaptureParams->en_mCCxCh == CCx_CHANNEL_1)
	{
        /* Selecting Mode of Operation (COMPARE OR CAPTURE) */
        TCC_ModeSelect(p_stfTCCCaptureParams->en_mTCCSlice,p_stfTCCCaptureParams->en_mMode,\
									p_stfTCCCaptureParams->en_mCCxCh);
        
        /* Generates Events on Capure */
        p_stgTCCREGS[u32_lSlice]->EVCTRL |= TCC_EVCTRL_MCEI1_MASK;
        
        //p_stgTCCREGS[u32_lSlice]->EVCTRL |= TCC_EVCTRL_MCEO1_MASK;
    }
	
	if(p_stfTCCCaptureParams->en_mCCxCh == CCx_CHANNEL_2)
	{
        /* Selecting Mode of Operation (COMPARE OR CAPTURE) */
        TCC_ModeSelect(p_stfTCCCaptureParams->en_mTCCSlice,p_stfTCCCaptureParams->en_mMode,\
									p_stfTCCCaptureParams->en_mCCxCh);
        
        /* Generates Events on Capure */
        p_stgTCCREGS[u32_lSlice]->EVCTRL |= TCC_EVCTRL_MCEI2_MASK;
        
        //p_stgTCCREGS[u32_lSlice]->EVCTRL |= TCC_EVCTRL_MCEO2_MASK;
		
	}
	
	if(p_stfTCCCaptureParams->en_mCCxCh == CCx_CHANNEL_3)
	{
        /* Selecting Mode of Operation (COMPARE OR CAPTURE) */
        TCC_ModeSelect(p_stfTCCCaptureParams->en_mTCCSlice,p_stfTCCCaptureParams->en_mMode,\
									p_stfTCCCaptureParams->en_mCCxCh);
        
  
        /* Generates Events on Capure */
        p_stgTCCREGS[u32_lSlice]->EVCTRL |= TCC_EVCTRL_MCEI3_MASK;
        
        //p_stgTCCREGS[u32_lSlice]->EVCTRL |= TCC_EVCTRL_MCEO3_MASK;
		
	}
	if(p_stfTCCCaptureParams->en_mCCxCh == CCx_ALL_CHANNELS)
	{
        /* Selecting Mode of Operation (COMPARE OR CAPTURE) */
        TCC_ModeSelect(p_stfTCCCaptureParams->en_mTCCSlice,p_stfTCCCaptureParams->en_mMode,\
									p_stfTCCCaptureParams->en_mCCxCh);
        
        /* Generates Events on Capure */
        p_stgTCCREGS[u32_lSlice]->EVCTRL |= TCC_EVCTRL_MCEI0_MASK;
        
        /* Selecting Mode of Operation (COMPARE OR CAPTURE) */
        TCC_ModeSelect(p_stfTCCCaptureParams->en_mTCCSlice,p_stfTCCCaptureParams->en_mMode,\
									p_stfTCCCaptureParams->en_mCCxCh);
        
        /* Generates Events on Capure */
        p_stgTCCREGS[u32_lSlice]->EVCTRL |= TCC_EVCTRL_MCEI1_MASK;
        
        /* Selecting Mode of Operation (COMPARE OR CAPTURE) */
        TCC_ModeSelect(p_stfTCCCaptureParams->en_mTCCSlice,p_stfTCCCaptureParams->en_mMode,\
									p_stfTCCCaptureParams->en_mCCxCh);
        
        /* Generates Events on Capture */
        p_stgTCCREGS[u32_lSlice]->EVCTRL |= TCC_EVCTRL_MCEI2_MASK;
		
        /* Selecting Mode of Operation (COMPARE OR CAPTURE) */
        TCC_ModeSelect(p_stfTCCCaptureParams->en_mTCCSlice,p_stfTCCCaptureParams->en_mMode,\
									p_stfTCCCaptureParams->en_mCCxCh);
        
        /* Generates Events on Capure */
        p_stgTCCREGS[u32_lSlice]->EVCTRL |= TCC_EVCTRL_MCEI3_MASK;
	}
	else
	{
		/* NOP */
	}

	/* Selecting Double Buffering */
	p_stgTCCREGS[u32_lSlice]->CTRLBCLR &= ~(1<<1);
 
    /* Enabling Interuupts for OVF and Compare match ( MCx ) */
	TCC_InterruptEnable(p_stfTCCCaptureParams->en_mTCCSlice, \
                                            TCC_OVF_INT,p_stfTCCCaptureParams->en_mCCxCh);
    /* MC0 = 16 */
    //p_stgTCCREGS[p_stfTCCCaptureParams->en_mCCxCh]->INTENSET |= (TCC_INTENSET_MC0_MASK);
    
    /* MC1 = 17 */
    //p_stgTCCREGS[p_stfTCCCaptureParams->en_mCCxCh]->INTENSET |= (TCC_INTENSET_MC1_MASK);
    
#if 0     
    if(CCx_CHANNEL_0 == p_stfTCCCaptureParams->en_mCCxCh)
    {
        /* MC0 = 16 */
		p_stgTCCREGS[p_stfTCCCaptureParams->en_mCCxCh]->INTENSET |= (TCC_INTENSET_MC0_MASK);
        
        /* MC1 = 17 */
		p_stgTCCREGS[p_stfTCCCaptureParams->en_mCCxCh]->INTENSET |= (TCC_INTENSET_MC1_MASK);
    }
  
    if(CCx_CHANNEL_1 == p_stfTCCCaptureParams->en_mCCxCh)
    {
        /* MC1 = 17 */
		p_stgTCCREGS[p_stfTCCCaptureParams->en_mCCxCh]->INTENSET |= (TCC_INTENSET_MC1_MASK);
    }
    if(CCx_CHANNEL_2 == p_stfTCCCaptureParams->en_mCCxCh)
    {
        /* MC2 = 18 */
		p_stgTCCREGS[p_stfTCCCaptureParams->en_mCCxCh]->INTENSET |= (TCC_INTENSET_MC2_MASK);
    }
    if(CCx_CHANNEL_3 == p_stfTCCCaptureParams->en_mCCxCh)
    {
        /* MC3 = 19 */
		p_stgTCCREGS[p_stfTCCCaptureParams->en_mCCxCh]->INTENSET |= (TCC_INTENSET_MC3_MASK);
    }
    if(CCx_NO_CHANNEL == p_stfTCCCaptureParams->en_mCCxCh)
    {
        /* NOP */
    }
    if(CCx_ALL_CHANNELS == p_stfTCCCaptureParams->en_mCCxCh)
	{
		/* MC0 = 16 */
		p_stgTCCREGS[p_stfTCCCaptureParams->en_mCCxCh]->INTENSET |= (TCC_INTENSET_MC0_MASK);
		
		/*  MC1 = 17*/
		p_stgTCCREGS[p_stfTCCCaptureParams->en_mCCxCh]->INTENSET |= (TCC_INTENSET_MC1_MASK);
		
        /*  MC2 = 18 */
		p_stgTCCREGS[p_stfTCCCaptureParams->en_mCCxCh]->INTENSET |= (TCC_INTENSET_MC2_MASK);
		
		/*  MC3 = 19 */
		p_stgTCCREGS[p_stfTCCCaptureParams->en_mCCxCh]->INTENSET |= (TCC_INTENSET_MC3_MASK);
	}
#endif
    
    /* Event Action : Selecting PPW Period in CC0 Pulse width in CC1 */
    p_stgTCCREGS[u32_lSlice]->EVCTRL |= TCC_EVCTRL_PPW_MASK;
    
    /* Enable Input Events */
    p_stgTCCREGS[u32_lSlice]->EVCTRL |= TCC_EVCTRL_TCEI1_MASK;
    
    if(u32_lSlice == 0)
	{
		/* Enabling NVIC for TCC0 */
		NVIC_EnableInterrupt(TCC0_1_IRQ);
	}
	else if(u32_lSlice == 1)
	{		
		/* Enabling NVIC for TCC1 */
		NVIC_EnableInterrupt(TCC1_0_IRQ);
	}
	else if(u32_lSlice == 2)
	{
		/* Enabling NVIC for TCC2 */
		NVIC_EnableInterrupt(TCC2_0_IRQ);
	}
	else
	{
		/* NOP */
	}
    
    /* Assigning Function Pointers for User Handlers */
    p_stgCaptureUserHandler[u32_lSlice] = p_stfTCCCaptureParams;
    
    /* Clear the Timer Event flag to use Capture */
    u8_gTimerEvent = 0;
	
	/*Enable Timer */
	TCC_Enable(p_stfTCCCaptureParams->en_mTCCSlice);
}

/**************************************************************************************************/
/* Function Name   : void TCC_EventInit(ST_TCC_EVENT_PARAMS_t *p_stfTCCEventParams)               */
/*                                                                                                */
/* Description     : This function is used for TCC as normal timer                                */
/*                                                                                                */
/* In Params       : p_stfTCCEventParams                                                          */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TCC_EventInit(ST_TCC_EVENT_PARAMS_t *p_stfTCCEventParams)
{
	INT32F f32_lPeriodVal = 0;
	
	/* Clock = 120MHZ */
	INT32U	u32_lGCLK = SYSTEM_CLOCK;
	
	INT32U u32_lSlice = p_stfTCCEventParams->en_mTCCSlice;	
	
	if(u32_lSlice == 0)
	{
		/*Enabling clock for tcc 0*/
         MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_TCCn0);    
		GCLK_PeripheralClockEnable(GCLK_TCC0);
	}
	if(u32_lSlice == 1)
	{
		/*Enabling clock for tcc 0*/
        MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_TCCn1);
		GCLK_PeripheralClockEnable(GCLK_TCC0);
	}
	if(u32_lSlice == 2)
	{
		/*Enabling clock for tcc 0*/
         MCLK_PeriphClkInit(MCLK_APBC, MCLK_APBC_TCCn2);
		GCLK_PeripheralClockEnable(GCLK_TCC2);
	}
    if(u32_lSlice == 3)
	{
		/*Enabling clock for tcc 0*/
         MCLK_PeriphClkInit(MCLK_APBC, MCLK_APBC_TCCn3);
		GCLK_PeripheralClockEnable(GCLK_TCC2);
	}
    if(u32_lSlice == 4)
	{
		/*Enabling clock for tcc 0*/
         MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_TCC4);
		GCLK_PeripheralClockEnable(GCLK_TCC4);
	}
	else
	{
		/* NOP */
	}

	
	/* Disable TCC */
	TCC_Disable((EN_TCC_SLICE_t )u32_lSlice);

	/* Performing Software Reset */
	TCC_SoftReset(p_stfTCCEventParams->en_mTCCSlice);
	
	/* Selecting Mode of Operation (COMPARE OR CAPTURE) */
	TCC_ModeSelect(p_stfTCCEventParams->en_mTCCSlice,p_stfTCCEventParams->en_mMode,\
																				CCx_CHANNEL_0);
	
	/* Calculating Period Value */
    if(TCC_DELAY_MS == p_stfTCCEventParams->en_mDelayType)
    {
      	/* Selecting Prescalar for timer */
        p_stgTCCREGS[u32_lSlice]->CTRLA |= (1024 << TCC_CTRLA_PRESCALAR_POS);
        
        /* Selecting Prescalar and Counter synchronization */
        p_stgTCCREGS[u32_lSlice]->CTRLA |= TCC_CTRLA_PRESYNC_PRESC_MASK;
    
        f32_lPeriodVal = TCC_GetPeriodValueinTime(p_stfTCCEventParams->f32_mTime, 1024,
                                                  u32_lGCLK, p_stfTCCEventParams->en_mDelayType);
	}
    else
    {
        /* Selecting Prescalar for timer */
        p_stgTCCREGS[u32_lSlice]->CTRLA |= (16 << TCC_CTRLA_PRESCALAR_POS);
        
        /* Selecting Prescalar and Counter synchronization */
        p_stgTCCREGS[u32_lSlice]->CTRLA |= TCC_CTRLA_PRESYNC_PRESC_MASK;
        
        f32_lPeriodVal = TCC_GetPeriodValueinTime(p_stfTCCEventParams->f32_mTime, 16, u32_lGCLK, 
                                                             p_stfTCCEventParams->en_mDelayType);
    }
    
	/* Setting Period Value */
	TCC_SetPeriodValue(p_stfTCCEventParams->en_mTCCSlice, (INT32U )f32_lPeriodVal);
	
	/* Enabling Interuupts for OVF */
	 TCC_InterruptEnable(p_stfTCCEventParams->en_mTCCSlice, \
							TCC_OVF_INT,CCx_NO_CHANNEL);
	if(u32_lSlice == 0)
	{
		/* Enabling NVIC for TCC0 */
		NVIC_EnableInterrupt(TCC0_0_IRQ);
	}
	else if(u32_lSlice == 1)
	{		
		/* Enabling NVIC for TCC1 */
		NVIC_EnableInterrupt(TCC1_0_IRQ);
	}
	else if(u32_lSlice == 2)
	{
		/* Enabling NVIC for TCC2 */
		NVIC_EnableInterrupt(TCC2_0_IRQ);
	}
	else
	{
		/* NOP */
	}
	/* Assigning Function Pointers for User Handlers */
	p_stgUserHandlerTCC[u32_lSlice] = p_stfTCCEventParams;
    
    u8_gTimerEvent = 1;
	
	/*Enable Timer */
	TCC_Enable(p_stfTCCEventParams->en_mTCCSlice);
}

/**************************************************************************************************/
/* Function Name   : INT32U	Get_Period_Value(INT32U u32_fPWMFreqHZ,INT32U u32_fPrescalar \    */
/*				                                ,INT32U u32_fGCLKFreqHZ)          */
/*                                                                                                */
/* Description     : API to calculate Period Value			                          */
/*                                                                                                */
/* In Params       : PWM frequency, Prescalar, GCLK Clock frequency                               */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : u32_lPeriod                                                                  */
/**************************************************************************************************/

INT32U TCC_GetPeriodValue(INT32U u32_fPWMFreqHZ,INT32U u32_fPrescalar,INT32U u32_fGCLKFreqHZ)
{
	INT32F f32_lTempFreq = 0;
    INT32U u32_lPeriod = 0;
	
	/* Period = ((FGCLK/(N*FPWM))-1) */
	
	f32_lTempFreq = (u32_fGCLKFreqHZ/u32_fPrescalar);
	
	u32_lPeriod = (INT32U )((f32_lTempFreq/u32_fPWMFreqHZ)-1);
	
	return u32_lPeriod;
}

/**************************************************************************************************/
/* Function Name   : INT32U TCC_GetPeriodValueinTime(INT32F f32_fTimeinMS,INT32U u32_fPrescalar,\ */
 /*                                                           INT32U u32_fGCLKFreqHZ)             */
/*                                                                                                */
/* Description     : This function is used to get period value                                    */
/*                                                                                                */
/* In Params       : f32_fTimeinMS, u32_fPrescalar, u32_fGCLKFreqHZ                               */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

INT32U TCC_GetPeriodValueinTime(INT32F f32_fTimeinMS,INT32U u32_fPrescalar,INT32U u32_fGCLKFreqHZ, \
                                            EN_TCC_DELAY_TYPE_t en_fDelayType)
{
    INT32F f32_lTempFreq = 0;
    INT32F f32_lTimeinSec = 0;
    INT32U u32_lPeriod = 0;
    
      
    if(TCC_DELAY_MS == en_fDelayType)
    {
       f32_lTimeinSec = ((INT32F )f32_fTimeinMS/1000);
	}
    else
    {
       f32_lTimeinSec = ((INT32F )f32_fTimeinMS/1000000);
    }

	INT32F f32_fPWMFreqHZ = ((INT32F )1/f32_lTimeinSec);
	
	/* Period = ((FGCLK/(N*FPWM))-1) */
	
	f32_lTempFreq = (u32_fGCLKFreqHZ/u32_fPrescalar);
	
	u32_lPeriod = (INT32U )((f32_lTempFreq/f32_fPWMFreqHZ)-1);
	
	return u32_lPeriod;
}

/**************************************************************************************************/
/* Function Name   : INT32U Get_Compare_Value(INT32U u32_fDutyCycle,INT32U u32_fPeriod)           */
/*                                                                                                */
/* Description     : API to calculate Compare value                                               */
/*                                                                                                */
/* In Params       : Desired Duty Cycle, Period value                                             */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : u32_lCompare                                                                 */
/**************************************************************************************************/

INT32F TCC_GetCompareValue(INT32F f32_fDutyCycle,INT32U u32_fPeriod)
{
	INT32F f32_lTemp = 0;
	
	INT32F	f32_lCompare = 0;
	
	//u32_fDutyCycle = 100 - u32_fDutyCycle;
	/* If User gives duty cycle more than 100 put max value to 100 */
	if(f32_fDutyCycle > 100 )
	{
		f32_fDutyCycle = 100;
	}
    else if (f32_fDutyCycle < 0)
    {
        f32_fDutyCycle = 0;
    }
	
	f32_lTemp = ((INT32F )f32_fDutyCycle/100 );
	
	f32_lCompare = (f32_lTemp * u32_fPeriod);
	
	return f32_lCompare;
}

/**************************************************************************************************/
/* Function Name   : void Timer_Command(EN_TCC_SLICE_t en_fSlice,EN_TCC_COMMAND_t en_fCommand)    */
/*                                                                                                */
/* Description     : Command to retrigger or update or stop the timer                             */
/*                                                                                                */
/* In Params       : en_fSlice,en_fCommand                                                        */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TCC_Timer_Command(EN_TCC_SLICE_t en_fSlice,EN_TCC_COMMAND_t en_fCommand)
{
	/* Bit 5: CMD*/
	switch(en_fCommand)
	{
            case TCC_NO_ACTION:
                /* No action */
            break;
            
            case TCC_RETRIGGER:
                p_stgTCCREGS[en_fSlice]->CTRLBSET |= (TCC_RETRIGGER << TCC_CTRLBSET_CMD_POS);
            break;
            
            case TCC_STOP:
                p_stgTCCREGS[en_fSlice]->CTRLBSET |= (TCC_STOP << TCC_CTRLBSET_CMD_POS);
            break;

            case TCC_UPDATE:
                p_stgTCCREGS[en_fSlice]->CTRLBSET |= (TCC_UPDATE << TCC_CTRLBSET_CMD_POS);
            break;
            
            case TCC_READSYNC:
                p_stgTCCREGS[en_fSlice]->CTRLBSET |= (TCC_READSYNC << TCC_CTRLBSET_CMD_POS);
            break;
            
            default:
                 /* NOP */
            break;
	}
}

/**************************************************************************************************/
/* Function Name   : void TCC_Enable(EN_TCC_SLICE_t en_fSlice)                                    */
/*                                                                                                */
/* Description     : Starts the Timer 								  */
/*                                                                                                */
/* In Params       : en_fSlice                                                                    */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TCC_Enable(EN_TCC_SLICE_t en_fSlice)
{
	/* Enabling Timer */
	p_stgTCCREGS[en_fSlice]->CTRLA |= TCC_CTRLA_ENABLE_MASK;

	/* Wait for Sync Enable */
	while((p_stgTCCREGS[en_fSlice]->SYNCBUSY) & TCC_SYNCBUSY_ENABLE_MASK);
}

/**************************************************************************************************/
/* Function Name   : void TCC_Disable(EN_TCC_SLICE_t en_fSlice)                                   */
/*                                                                                                */
/* Description     : Starts the Timer   				                          */
/*                                                                                                */
/* In Params       : en_fSlice                                                                    */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TCC_Disable(EN_TCC_SLICE_t en_fSlice)
{
	/* Enabling Timer */
	p_stgTCCREGS[en_fSlice]->CTRLA &= ~TCC_CTRLA_ENABLE_MASK;

	/* Wait for Sync Enable */
	while((p_stgTCCREGS[en_fSlice]->SYNCBUSY) & TCC_SYNCBUSY_ENABLE_MASK);
}

/**************************************************************************************************/
/* Function Name   : void TCC_SoftReset(EN_TCC_SLICE_t en_fSlice)                                 */
/*                                                                                                */
/* Description     : Performs Software Reset to the timer                                         */
/*                                                                                                */
/* In Params       : en_fSlice                                                                    */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TCC_SoftReset(EN_TCC_SLICE_t en_fSlice)
{
	/* Wait for Sync SWRST*/
	while((p_stgTCCREGS[en_fSlice]->SYNCBUSY) & TCC_SYNCBUSY_SWRST_MASK);
	
	/* Performing software reset */
	p_stgTCCREGS[en_fSlice]->CTRLA = TCC_CTRLA_SWRST_MASK;

}

/**************************************************************************************************/
/* Function Name   : void TCC_ModeSelect(EN_TCC_SLICE_t en_fSlice,EN_TCC_CC_MODE_SEL_t en_fMode,\ */
/*								     EN_CCx_CHANNEL_SEL_t en_fCh) */
/*                                                                                                */
/* Description     : API to select compare or capture mode                                        */
/*                                                                                                */
/* In Params       : en_fSlice,  en_fMode, en_fCh                                                 */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TCC_ModeSelect(EN_TCC_SLICE_t en_fSlice,EN_TCC_CC_MODE_SEL_t en_fMode,EN_CCx_CHANNEL_SEL_t \
                                                                                        en_fCh)
{
	switch(en_fCh)
    {
        case CCx_CHANNEL_0:
        {
            if(en_fMode == TCC_CAPTURE_MODE)
            {		
                p_stgTCCREGS[en_fSlice]->CTRLA  |= (1UL << TCC_CTRLA_CPTEN0_POS );
                
                /* Wait for Sync Busy for Ch0*/
                while((p_stgTCCREGS[en_fSlice]->SYNCBUSY) & TCC_SYNC_BUSY_CC0_MASK );
            }
        }
        break;
        
        case CCx_CHANNEL_1:
        {
            if(en_fMode == TCC_CAPTURE_MODE)
            {		
                p_stgTCCREGS[en_fSlice]->CTRLA  |= (1UL << TCC_CTRLA_CPTEN1_POS );
                
                /* Wait for Sync Busy for Ch1*/
                while((p_stgTCCREGS[en_fSlice]->SYNCBUSY) & TCC_SYNC_BUSY_CC1_MASK );
            }
        }
        break;
        
        case CCx_CHANNEL_2:
        {
            if(en_fMode == TCC_CAPTURE_MODE)
            {		
                p_stgTCCREGS[en_fSlice]->CTRLA  |= (1UL << TCC_CTRLA_CPTEN2_POS );
                
                /* Wait for Sync Busy for Ch2*/
                while((p_stgTCCREGS[en_fSlice]->SYNCBUSY) & TCC_SYNC_BUSY_CC2_MASK );
            }
        }
        break;
        
        case CCx_CHANNEL_3:
        {
            if(en_fMode == TCC_CAPTURE_MODE)
            {		
                p_stgTCCREGS[en_fSlice]->CTRLA  |= (1UL << TCC_CTRLA_CPTEN3_POS );
                
                /* Wait for Sync Busy for Ch3*/
                while((p_stgTCCREGS[en_fSlice]->SYNCBUSY) & TCC_SYNC_BUSY_CC3_MASK );
            }
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
/* Function Name   : void TCC_SetPeriodValue(EN_TCC_SLICE_t en_fSlice,INT32U u32_fPeriod)         */
/*                                                                                                */
/* Description     : API to set the Period Value 				                  */
/*                                                                                                */
/* In Params       : en_fSlice,  u32_fPeriod                                                      */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TCC_SetPeriodValue(EN_TCC_SLICE_t en_fSlice,INT32U u32_fPeriod)
{
    p_stgTCCREGS[en_fSlice]->PER = u32_fPeriod;    
    
	/* Waiting for PER Sync */
	while((p_stgTCCREGS[en_fSlice]->SYNCBUSY) & 0x40);
}

/**************************************************************************************************/
/* Function Name   : void TCC_SetCompareValue(EN_TCC_SLICE_t en_fSlice, \                         */
/*				c   EN_CCx_CHANNEL_SEL_t en_fCh,INT32U u32_fCompval)              */
/*                                                                                                */
/* Description     : Sets the compare value                                                       */
/*                                                                                                */
/* In Params       : en_fSlice, en_fCh ,u32_fCompval                                              */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TCC_SetCompareValue(EN_TCC_SLICE_t en_fSlice,EN_CCx_CHANNEL_SEL_t en_fCh,INT32F f32_fCompval)
{
    p_stgTCCREGS[en_fSlice]->CC[en_fCh] = (INT32U)f32_fCompval;
}

/**************************************************************************************************/
/* Function Name   : INT32U TCC_ReadCaptureData(EN_CCx_CHANNEL_SEL_t en_fCh)                      */
/*                                                                                                */
/* Description     : Read the Capture value                                                       */
/*                                                                                                */
/* In Params       : en_fCh                                                                       */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : INT32U                                                                       */
/**************************************************************************************************/

INT32U TCC_ReadCaptureData(EN_TCC_SLICE_t en_fSlice)
{
    INT32U u32_lReaddata = 0;
    
    u32_lReaddata = p_stgTCCREGS[en_fSlice]->CC[0];
    
    return u32_lReaddata;
}

/**************************************************************************************************/
/* Function Name   : void TCC_InterruptEnable(EN_TCC_SLICE_t en_fSlice, \                         */
/*				EN_INTERRUPT_SEL_t en_fIntSel,EN_CCx_CHANNEL_SEL_t en_fChnl)	  */
/*                                                                                                */
/* Description     : Enables the interrupt for TCC module                                         */
/*                                                                                                */
/* In Params       : en_fSlice, en_fIntSel, en_fChnl                                              */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TCC_InterruptEnable(EN_TCC_SLICE_t en_fSlice,EN_INTERRUPT_SEL_t en_fIntSel,\
                                                                     EN_CCx_CHANNEL_SEL_t en_fChnl)
{
	if(en_fIntSel == TCC_OVF_INT)
	{
            /* For OVF  */
            p_stgTCCREGS[en_fSlice]->INTENSET = (0x01);
	}
	if(en_fChnl == CCx_CHANNEL_0)
	{
            /* MC0 = 16 */
            p_stgTCCREGS[en_fSlice]->INTENSET |= TCC_INTENSET_MC0_MASK;
	}
	if(en_fChnl == CCx_CHANNEL_1)
	{
            /*  MC1 = 17*/
            p_stgTCCREGS[en_fSlice]->INTENSET |= TCC_INTENSET_MC1_MASK;
	}
	if(en_fChnl == CCx_CHANNEL_2)
	{
            /*  MC2 = 18 */
            p_stgTCCREGS[en_fSlice]->INTENSET |= TCC_INTENSET_MC2_MASK;
	}
	if(en_fChnl == CCx_CHANNEL_3)
	{
            /*  MC3 = 19 */
            p_stgTCCREGS[en_fSlice]->INTENSET |= TCC_INTENSET_MC3_MASK;
	}
	if(en_fChnl == CCx_NO_CHANNEL)
	{
            /* NOP */
	}
	if(en_fChnl == CCx_ALL_CHANNELS)
	{
            /* MC0 = 16 */
            p_stgTCCREGS[en_fSlice]->INTENSET |= TCC_INTENSET_MC0_MASK;
            
            /*  MC1 = 17*/
            p_stgTCCREGS[en_fSlice]->INTENSET |= TCC_INTENSET_MC1_MASK;
            
                    /*  MC2 = 18 */
            p_stgTCCREGS[en_fSlice]->INTENSET |= TCC_INTENSET_MC2_MASK;
            
            /*  MC3 = 19 */
            p_stgTCCREGS[en_fSlice]->INTENSET |= TCC_INTENSET_MC3_MASK;
	}
}

/**************************************************************************************************/
/* Function Name   : void TCC_Dead_Time_Config(ST_DEAD_TIME_CONFIG_PARAMS_t *p_stfDTParams)       */
/*                                                                                                */
/* Description     : API to use dead time generation feature                                      */
/*                                                                                                */
/* In Params       : p_stfDTParams                                                                */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TCC_Dead_Time_Config(ST_DEAD_TIME_CONFIG_PARAMS_t *p_stfDTParams)
{
    INT32U u32_lSlice = p_stfDTParams->en_mTCCSlice;

    /* Selecting OUTPUT matrix */
    p_stgTCCREGS[u32_lSlice]->WEXCTRL = p_stfDTParams->en_mOutMatrix;

    /* Set DTLS Value (POS: 16) */
    p_stgTCCREGS[u32_lSlice]->WEXCTRL |= (p_stfDTParams->u32_mDTLS << TCC_WEXCTRL_DTLS_POS);

    /* Set DTHS Value (POS: 24)*/
    p_stgTCCREGS[u32_lSlice]->WEXCTRL |= (p_stfDTParams->u32_mDTLS << TCC_WEXCTRL_DTHS_POS);

    /* Enabling the DT channels */
    if(p_stfDTParams->en_mDTChnSel == TCC_DTIEN0)
    {
        /*Enabling DT channel 0 */
        p_stgTCCREGS[u32_lSlice]->WEXCTRL |= (1 << TCC_WEXCTRL_DTIEN0_POS);	
    }
    if(p_stfDTParams->en_mDTChnSel == TCC_DTIEN1)
    {
        /*Enabling DT channel 1 */
        p_stgTCCREGS[u32_lSlice]->WEXCTRL |= (1 << TCC_WEXCTRL_DTIEN1_POS);	
    }
    if(p_stfDTParams->en_mDTChnSel == TCC_DTIEN2)
    {
        /*Enabling DT channel 2 */
        p_stgTCCREGS[u32_lSlice]->WEXCTRL |= (1 << TCC_WEXCTRL_DTIEN2_POS);
    }
    if(p_stfDTParams->en_mDTChnSel == TCC_DTIEN3)
    {
        /*Enabling DT channel 3 */
        p_stgTCCREGS[u32_lSlice]->WEXCTRL |= (1 << TCC_WEXCTRL_DTIEN3_POS);
    }
}

/**************************************************************************************************/
/* Function Name   : void Update_Duty_Cycle(ST_TCC_CONFIG_DATA_t *p_stfTCCConfigParams)           */
/*                                                                                                */
/* Description     : This function used to Update Dutycycle                                       */
/*                                                                                                */
/* In Params       : void                                                                         */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TCC_UpdateDutyCycle(EN_CCx_CHANNEL_SEL_t en_fCompChNo,INT32F f32_fDutyCycle, \
                                                                            INT32U u32_fPWMFreq)
{
    INT32F f32_lComp0DutyCycle = 0;
    INT32F f32_lComp1DutyCycle = 0;
    INT32F f32_lComp2DutyCycle = 0;
    INT32F f32_lComp3DutyCycle = 0;

    if(en_fCompChNo == CCx_CHANNEL_0)
    {
        f32_lComp0DutyCycle = f32_fDutyCycle;
    }

    if(en_fCompChNo == CCx_CHANNEL_1)
    {
        f32_lComp1DutyCycle = f32_fDutyCycle;
    }

    if(en_fCompChNo == CCx_CHANNEL_2)
    {
        f32_lComp2DutyCycle = f32_fDutyCycle;
    }

    if(en_fCompChNo == CCx_CHANNEL_3)
    {
        f32_lComp3DutyCycle = f32_fDutyCycle;
    }
    if(en_fCompChNo == CCx_ALL_CHANNELS)
    {
        f32_lComp0DutyCycle = f32_fDutyCycle;
        f32_lComp1DutyCycle = f32_fDutyCycle;
        f32_lComp2DutyCycle = f32_fDutyCycle;
        f32_lComp3DutyCycle = f32_fDutyCycle;
    }
    else
    {
            /* NOP */
    }
    /* Configuring all the parameters for updating duty cycle */
    ST_TCC_PWM_CONFIG_t st_gTCC0_Params = 
    {
        .en_mTCCSlice = TCC_SLICE_0,
        .en_mCCxCh = en_fCompChNo,
        .en_mMode = TCC_COMPARE_MODE,
        .u32_mPWMFreq = u32_fPWMFreq,
        .en_mPrescalar = TCC_DIV_64,
        .f32_mComp0DutyCycle = f32_lComp0DutyCycle,
        .f32_mComp1DutyCycle = f32_lComp1DutyCycle,
        .f32_mComp2DutyCycle = f32_lComp2DutyCycle,
        .f32_mComp3DutyCycle = f32_lComp3DutyCycle,
        .en_mWaveType = TCC_NORMAL_PWM,
    };

    INT32F f32_lComp0 = 0,f32_lComp1 = 0,f32_lComp2 = 0,f32_lComp3 = 0;
    INT32U u32_lPeriod = 0;
    INT32U u32_lSystemFreq = 48000000;
    INT32U u32_lPresclar = st_gTCC0_Params.en_mPrescalar;
    INT32U u32_lSlice = st_gTCC0_Params.en_mTCCSlice;	

    switch(st_gTCC0_Params.en_mPrescalar)
    {
        case TCC_DIV_1:
                u32_lPresclar = 1;
        break;
        case TCC_DIV_2:
                u32_lPresclar = 2;
        break;
        case TCC_DIV_4:
                u32_lPresclar = 4;
        break;
        case TCC_DIV_8:
                u32_lPresclar = 8;
        break;
        case TCC_DIV_16:
                u32_lPresclar = 16;
        break;
        case TCC_DIV_64:
                u32_lPresclar = 64;
        break;
        case TCC_DIV_256:
                u32_lPresclar = 256;
        break;
        case TCC_DIV_1024:
                u32_lPresclar = 1024;
        break;
    }	
    /* Calculating Period Value */
    u32_lPeriod = TCC_GetPeriodValue(st_gTCC0_Params.u32_mPWMFreq,u32_lPresclar,u32_lSystemFreq);

    if(en_fCompChNo == CCx_CHANNEL_0)
    {
        /* Calculating Compare Value */
        f32_lComp0 =  TCC_GetCompareValue(st_gTCC0_Params.f32_mComp0DutyCycle,u32_lPeriod);
        
        /* Updating the Duty Cycle */
        p_stgTCCREGS[u32_lSlice]->CCBUF[0] = (INT32U )f32_lComp0;
    }

    if(en_fCompChNo == CCx_CHANNEL_1)
    {            
        /* Calculating Compare Value */
        f32_lComp1 =  TCC_GetCompareValue(st_gTCC0_Params.f32_mComp1DutyCycle,u32_lPeriod);
        
        /* Updating the Duty Cycle */
        p_stgTCCREGS[u32_lSlice]->CCBUF[1] = (INT32U )f32_lComp1;
    }

    if(en_fCompChNo == CCx_CHANNEL_2)
    {
        /* Calculating Compare Value */
        f32_lComp2 =  TCC_GetCompareValue(st_gTCC0_Params.f32_mComp2DutyCycle,u32_lPeriod);
        
        /* Updating the Duty Cycle */
        p_stgTCCREGS[u32_lSlice]->CCBUF[2] = (INT32U )f32_lComp2;
    }

    if(en_fCompChNo == CCx_CHANNEL_3)
    {
        /* Calculating Compare Value */
        f32_lComp3 =  TCC_GetCompareValue(st_gTCC0_Params.f32_mComp3DutyCycle,u32_lPeriod);
        
        /* Updating the Duty Cycle */
        p_stgTCCREGS[u32_lSlice]->CCBUF[3] = (INT32U )f32_lComp3;
    }

    if(en_fCompChNo == CCx_ALL_CHANNELS)
    {
        /* Calculating Compare Value */
        f32_lComp0 =  TCC_GetCompareValue(st_gTCC0_Params.f32_mComp0DutyCycle,u32_lPeriod);
        
        /* Updating the Duty Cycle */
        p_stgTCCREGS[u32_lSlice]->CCBUF[0] = (INT32U )f32_lComp0;
        
        /* Calculating Compare Value */
        f32_lComp1 =  TCC_GetCompareValue(st_gTCC0_Params.f32_mComp1DutyCycle,u32_lPeriod);
        
        /* Updating the Duty Cycle */
        p_stgTCCREGS[u32_lSlice]->CCBUF[1] = (INT32U )f32_lComp1;
        
        /* Calculating Compare Value */
        f32_lComp2 =  TCC_GetCompareValue(st_gTCC0_Params.f32_mComp2DutyCycle,u32_lPeriod);
        
        /* Updating the Duty Cycle */
        p_stgTCCREGS[u32_lSlice]->CCBUF[2] = (INT32U )f32_lComp2;
        
        /* Calculating Compare Value */
        f32_lComp3 =  TCC_GetCompareValue(st_gTCC0_Params.f32_mComp3DutyCycle,u32_lPeriod);
        
        /* Updating the Duty Cycle */
        p_stgTCCREGS[u32_lSlice]->CCBUF[3] = (INT32U )f32_lComp3;
    }
    else
    {
        /* NOP */
    }
    /* Sending Command to Update */
    TCC_Timer_Command((EN_TCC_SLICE_t)u32_lSlice,TCC_UPDATE);
}

/**************************************************************************************************/
/* End of TCC.C                                                                                   */
/**************************************************************************************************/
