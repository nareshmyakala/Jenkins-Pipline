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
/* \File Name   : TC.c                                                                            */
/* \Author      : Salman Ali                                                                      */
/* \Version 	: 1.1                                                                             */
/* \Date        : 29/2/16                                                                         */
/*                                                                                                */
/* @Description : Drivers for Timer Control                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "GCLK.h"
#include "MCLK.h"

#include "NVIC.h"

#include "TC.h"
#include "TC_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

ST_TC_BASE_REG_t *p_stgTCBaseRegs[MAX_TC_TIMERS] = 
{
    (ST_TC_BASE_REG_t *)TC0_BASE_ADDRESS,
    (ST_TC_BASE_REG_t *)TC1_BASE_ADDRESS,
    (ST_TC_BASE_REG_t *)TC2_BASE_ADDRESS,
    (ST_TC_BASE_REG_t *)TC3_BASE_ADDRESS,
    (ST_TC_BASE_REG_t *)TC4_BASE_ADDRESS
};
 
/* Structure Pointer to Access TC 8-Bit System Registers */
ST_TC_COUNT8_BASE_REGS_t *p_stgTC8BitBaseRegs[MAX_TC_TIMERS]  = 
{
    (ST_TC_COUNT8_BASE_REGS_t *)(TC0_BASE_ADDRESS + 0x14),
    (ST_TC_COUNT8_BASE_REGS_t *)(TC1_BASE_ADDRESS + 0x14),
    (ST_TC_COUNT8_BASE_REGS_t *)(TC2_BASE_ADDRESS + 0x14),
    (ST_TC_COUNT8_BASE_REGS_t *)(TC3_BASE_ADDRESS + 0x14),
    (ST_TC_COUNT8_BASE_REGS_t *)(TC4_BASE_ADDRESS + 0x14)
};

/* Structure Pointer to Access TC 16-Bit System Registers */
ST_TC_COUNT16_BASE_REGS_t *p_stgTC16BitBaseRegs[MAX_TC_TIMERS] = 
{
    (ST_TC_COUNT16_BASE_REGS_t *)(TC0_BASE_ADDRESS + 0x14),
    (ST_TC_COUNT16_BASE_REGS_t *)(TC1_BASE_ADDRESS + 0x14),
    (ST_TC_COUNT16_BASE_REGS_t *)(TC2_BASE_ADDRESS + 0x14),
    (ST_TC_COUNT16_BASE_REGS_t *)(TC3_BASE_ADDRESS + 0x14),
    (ST_TC_COUNT16_BASE_REGS_t *)(TC4_BASE_ADDRESS + 0x14)
};
                                                
ST_TC_COUNT32_BASE_REGS_t  *p_stgTC32BitBaseRegs[MAX_TC_TIMERS]  = 
{
    (ST_TC_COUNT32_BASE_REGS_t *)(TC0_BASE_ADDRESS + 0x14),
    (ST_TC_COUNT32_BASE_REGS_t *)(TC1_BASE_ADDRESS + 0x14),
    (ST_TC_COUNT32_BASE_REGS_t *)(TC2_BASE_ADDRESS + 0x14),
    (ST_TC_COUNT32_BASE_REGS_t *)(TC3_BASE_ADDRESS + 0x14),
    (ST_TC_COUNT32_BASE_REGS_t *)(TC4_BASE_ADDRESS + 0x14)
};

 /* TC User Handlers */                                                               
ST_TC_EVENT_PARAMS_t *p_stgTCUserHandler[MAX_TC_TIMERS] = {PNULL, };

void (*fp_TCUserHandler[MAX_TC_TIMERS])(void);

/* TC User Capture Handlers */
void (*fp_TCCaptureUserHandler[MAX_TC_TIMERS])(void);
																
/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

INT8U au8_gUsingTimerEvent[8] = {0, };

/**************************************************************************************************/
/* Function Name   : void TC0_Handler(void)                                                       */
/*                                                                                                */
/* Description     : TC0 System Handler                                                           */
/**************************************************************************************************/

void TC0_Handler(void)
{
	/* Checking for Int ERR flag */
	if(p_stgTCBaseRegs[0]->INTFLAG & TC_INTFLAG_ERR)
	{
		/* Clear OVF Interrupt flag */
		p_stgTCBaseRegs[0]->INTFLAG = TC_INTFLAG_ERR;
	}
	
	/* Checking for Int OVF flag */
	if(p_stgTCBaseRegs[0]->INTFLAG & TC_INTFLAG_OVF)
	{
        /* Clear OVF Interrupt flag */
        p_stgTCBaseRegs[0]->INTFLAG = TC_INTFLAG_OVF;
		
        if(1 == au8_gUsingTimerEvent[0])
        {
            if(PNULL != (fp_TCUserHandler[0]))
            {
                /* Calling User Handler */
                //fp_TCUserHandler[0]();
            }
        }
	}
	
	/* Checking for Int Compare/Capture0 flag */
	if(p_stgTCBaseRegs[0]->INTFLAG & TC_INTFLAG_MC0)
	{
		/* Clear Match/Capture 0 Interrupt flag */
		p_stgTCBaseRegs[0]->INTFLAG = TC_INTFLAG_MC0;
        
        if(1 == au8_gUsingTimerEvent[0])
        {
           if(PNULL != (fp_TCUserHandler[0]))
            {
                /* Calling User Handler */
                fp_TCUserHandler[0]();
            }
            else
            {
                /* No Action */
            } 
        }
        else
        {
            if(PNULL != (fp_TCCaptureUserHandler[0]))
            {
                /* Calling User Handler */
                fp_TCCaptureUserHandler[0]();
            }
            else
            {
                /* No Action */
            }
        }
	}
    
	/* Checking for Int Compare/Capture1 flag */
	if(p_stgTCBaseRegs[0]->INTFLAG & TC_INTFLAG_MC1)
	{
		/* Clear OVF Interrupt flag */
		p_stgTCBaseRegs[0]->INTFLAG = TC_INTFLAG_MC1;
		
        if(PNULL != (fp_TCCaptureUserHandler[0]))
        {
            /* Calling User Handler */
            //fp_TCCaptureUserHandler[0]();
        }
        
    }
}

/**************************************************************************************************/
/* Function Name   : void TC1_Handler(void)                                                       */
/*                                                                                                */
/* Description     : TC1 System Handler                                                           */
/**************************************************************************************************/

void TC1_Handler(void)
{
	/* Checking for Int ERR flag */
	if(p_stgTCBaseRegs[1]->INTFLAG & TC_INTFLAG_ERR)
	{
		/* Clear OVF Interrupt flag */
		p_stgTCBaseRegs[1]->INTFLAG = TC_INTFLAG_ERR;
	}
	
	/* Checking for Int OVF flag */
	if(p_stgTCBaseRegs[1]->INTFLAG & TC_INTFLAG_OVF)
	{
        /* Clear OVF Interrupt flag */
        p_stgTCBaseRegs[1]->INTFLAG = TC_INTFLAG_OVF;
		
        if(1 == au8_gUsingTimerEvent[1])
        {
            if(PNULL != (fp_TCUserHandler[1]))
            {
                /* Calling User Handler */
                //fp_TCUserHandler[0]();
            }
        }
	}
	
	/* Checking for Int Compare/Capture0 flag */
	if(p_stgTCBaseRegs[1]->INTFLAG & TC_INTFLAG_MC0)
	{
		/* Clear OVF Interrupt flag */
		p_stgTCBaseRegs[1]->INTFLAG = TC_INTFLAG_MC0;
        
        if(1 == au8_gUsingTimerEvent[1])
        {
           if(PNULL != (fp_TCUserHandler[1]))
            {
                /* Calling User Handler */
                fp_TCUserHandler[1]();
            }
            else
            {
                /* No Action */
            } 
        }
        else
        {
            if(PNULL != (fp_TCCaptureUserHandler[1]))
            {
                /* Calling User Handler */
                fp_TCCaptureUserHandler[1]();
            }
            else
            {
                /* No Action */
            }
        }
	}
    
	/* Checking for Int Compare/Capture1 flag */
	if(p_stgTCBaseRegs[1]->INTFLAG & TC_INTFLAG_MC1)
	{
		/* Clear OVF Interrupt flag */
		p_stgTCBaseRegs[1]->INTFLAG = TC_INTFLAG_MC1;
		
        if(PNULL != (fp_TCCaptureUserHandler[1]))
        {
            /* Calling User Handler */
            //fp_TCCaptureUserHandler[0]();
        }
        
    }
}

/**************************************************************************************************/
/* Function Name   : void TC2_Handler(void)                                                       */
/*                                                                                                */
/* Description     : TC2 System Handler                                                           */
/**************************************************************************************************/

void TC2_Handler(void)
{
	/* Checking for Int ERR flag */
	if(p_stgTCBaseRegs[2]->INTFLAG & TC_INTFLAG_ERR)
	{
		/* Clear OVF Interrupt flag */
		p_stgTCBaseRegs[2]->INTFLAG = TC_INTFLAG_ERR;
	}
	
	/* Checking for Int OVF flag */
	if(p_stgTCBaseRegs[2]->INTFLAG & TC_INTFLAG_OVF)
	{
        /* Clear OVF Interrupt flag */
        p_stgTCBaseRegs[2]->INTFLAG = TC_INTFLAG_OVF;
		
        if(1 == au8_gUsingTimerEvent[2])
        {
            if(PNULL != (fp_TCUserHandler[2]))
            {
                /* Calling User Handler */
                //fp_TCUserHandler[0]();
            }
        }
	}
	
	/* Checking for Int Compare/Capture0 flag */
	if(p_stgTCBaseRegs[2]->INTFLAG & TC_INTFLAG_MC0)
	{
		/* Clear OVF Interrupt flag */
		p_stgTCBaseRegs[2]->INTFLAG = TC_INTFLAG_MC0;
        
        if(1 == au8_gUsingTimerEvent[2])
        {
           if(PNULL != (fp_TCUserHandler[2]))
            {
                /* Calling User Handler */
                fp_TCUserHandler[2]();
            }
            else
            {
                /* No Action */
            } 
        }
        else
        {
            if(PNULL != (fp_TCCaptureUserHandler[2]))
            {
                /* Calling User Handler */
                fp_TCCaptureUserHandler[2]();
            }
            else
            {
                /* No Action */
            }
        }
	}
    
	/* Checking for Int Compare/Capture1 flag */
	if(p_stgTCBaseRegs[2]->INTFLAG & TC_INTFLAG_MC1)
	{
		/* Clear OVF Interrupt flag */
		p_stgTCBaseRegs[2]->INTFLAG = TC_INTFLAG_MC1;
		
        if(PNULL != (fp_TCCaptureUserHandler[2]))
        {
            /* Calling User Handler */
            //fp_TCCaptureUserHandler[2]();
        }
        
    }
}

/**************************************************************************************************/
/* Function Name   : void TC3_Handler(void)                                                       */
/*                                                                                                */
/* Description     : TC3 System Handler                                                           */
/**************************************************************************************************/

void TC3_Handler(void)
{
	/* Checking for Int ERR flag */
	if(p_stgTCBaseRegs[3]->INTFLAG & TC_INTFLAG_ERR)
	{
		/* Clear OVF Interrupt flag */
		p_stgTCBaseRegs[3]->INTFLAG = TC_INTFLAG_ERR;
	}
	
	/* Checking for Int OVF flag */
	if(p_stgTCBaseRegs[3]->INTFLAG & TC_INTFLAG_OVF)
	{
        /* Clear OVF Interrupt flag */
        p_stgTCBaseRegs[3]->INTFLAG = TC_INTFLAG_OVF;
		
        if(1 == au8_gUsingTimerEvent[3])
        {
            if(PNULL != (fp_TCUserHandler[3]))
            {
                /* Calling User Handler */
                //fp_TCUserHandler[3]();
            }
        }
	}
	
	/* Checking for Int Compare/Capture0 flag */
	if(p_stgTCBaseRegs[3]->INTFLAG & TC_INTFLAG_MC0)
	{
		/* Clear MC0 Interrupt flag */
		p_stgTCBaseRegs[3]->INTFLAG = TC_INTFLAG_MC0;
        
        if(1 == au8_gUsingTimerEvent[3])
        {
           if(PNULL != (fp_TCUserHandler[3]))
            {
                /* Calling User Handler */
                fp_TCUserHandler[3]();
            }
            else
            {
                /* No Action */
            } 
        }
        else
        {
            if(PNULL != (fp_TCCaptureUserHandler[3]))
            {
                /* Calling User Handler */
                fp_TCCaptureUserHandler[3]();
            }
            else
            {
                /* No Action */
            }
        }
	}
    
	/* Checking for Int Compare/Capture1 flag */
	if(p_stgTCBaseRegs[3]->INTFLAG & TC_INTFLAG_MC1)
	{
		/* Clear OVF Interrupt flag */
		p_stgTCBaseRegs[3]->INTFLAG = TC_INTFLAG_MC1;
		
        if(PNULL != (fp_TCCaptureUserHandler[3]))
        {
            /* Calling User Handler */
            //fp_TCCaptureUserHandler[3]();
        }
        
    }
}

/**************************************************************************************************/
/* Function Name   : void TC4_Handler(void)                                                       */
/*                                                                                                */
/* Description     : TC4 System Handler                                                           */
/**************************************************************************************************/

void TC4_Handler(void)
{
	/* Checking for Int ERR flag */
	if(p_stgTCBaseRegs[4]->INTFLAG & TC_INTFLAG_ERR)
	{
		/* Clear OVF Interrupt flag */
		p_stgTCBaseRegs[4]->INTFLAG = TC_INTFLAG_ERR;
	}
	
	/* Checking for Int OVF flag */
	if(p_stgTCBaseRegs[4]->INTFLAG & TC_INTFLAG_OVF)
	{
        /* Clear OVF Interrupt flag */
        p_stgTCBaseRegs[4]->INTFLAG = TC_INTFLAG_OVF;
		
        if(1 == au8_gUsingTimerEvent[4])
        {
            if(PNULL != (fp_TCUserHandler[4]))
            {
                /* Calling User Handler */
                //fp_TCUserHandler[4]();
            }
        }
	}
	
	/* Checking for Int Compare/Capture0 flag */
	if(p_stgTCBaseRegs[4]->INTFLAG & TC_INTFLAG_MC0)
	{
		/* Clear OVF Interrupt flag */
		p_stgTCBaseRegs[4]->INTFLAG = TC_INTFLAG_MC0;
        
        if(1 == au8_gUsingTimerEvent[4])
        {
           if(PNULL != (fp_TCUserHandler[4]))
            {
                /* Calling User Handler */
                fp_TCUserHandler[4]();
            }
            else
            {
                /* No Action */
            } 
        }
        else
        {
            if(PNULL != (fp_TCCaptureUserHandler[4]))
            {
                /* Calling User Handler */
                fp_TCCaptureUserHandler[4]();
            }
            else
            {
                /* No Action */
            }
        }
	}
    
	/* Checking for Int Compare/Capture1 flag */
	if(p_stgTCBaseRegs[4]->INTFLAG & TC_INTFLAG_MC1)
	{
		/* Clear OVF Interrupt flag */
		p_stgTCBaseRegs[4]->INTFLAG = TC_INTFLAG_MC1;
		
        if(PNULL != (fp_TCCaptureUserHandler[4]))
        {
            /* Calling User Handler */
            //fp_TCCaptureUserHandler[4]();
        }
        
    }
}

/**************************************************************************************************/
/* Function Name   : void TC_EventInit(ST_TC_EVENT_PARAMS_t *p_stfTCEventParams)                  */
/*                                                                                                */
/* Description     : This function used to initialize the TC as basic timer                       */
/*                                                                                                */
/* In Params       : p_stfTCEventParams                                                           */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TC_EventInit(ST_TC_EVENT_PARAMS_t *p_stfTCEventParams)
{
    INT8U u8_lTc = p_stfTCEventParams->en_mTCSlice;
    static INT32U u32_lFirstFlag = 0;
    
    switch(u8_lTc)
    {
    	case 0:
        {
            /*Enabling clock for TC 0*/
            MCLK_PeriphClkInit(MCLK_APBA, MCLK_APBA_TCn0);
            GCLK_PeripheralClockEnable(GCLK_TC0);
        }
    	break;
        
        case 1:
        {
            MCLK_PeriphClkInit(MCLK_APBA, MCLK_APBA_TCn1);
            GCLK_PeripheralClockEnable(GCLK_TC1);
        }
        break;
        
        case 2:
        {
            MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_TCn2);
            GCLK_PeripheralClockEnable(GCLK_TC2);
        }
        break;
        
        case 3:
        {
            MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_TCn3);
            GCLK_PeripheralClockEnable(GCLK_TC2);
        }
        break;
        
        case 4:
        {
            MCLK_PeriphClkInit(MCLK_APBC, MCLK_APBC_TCn4);
            GCLK_PeripheralClockEnable(GCLK_TC4);
        }
        break;
        
        case 5:
        {
            MCLK_PeriphClkInit(MCLK_APBC, MCLK_APBC_TCn5);
            GCLK_PeripheralClockEnable(GCLK_TC4);
        }
        break;
        
        case 6:
        {
            MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_TC6);
            GCLK_PeripheralClockEnable(GCLK_TC6);
        }
        break;
        
        case 7:
        {
            MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_TC7);
            GCLK_PeripheralClockEnable(GCLK_TC6);
        }
        break;
        
        default :
            break;
    }
    
    /* Perform Software RESET */
	if(u32_lFirstFlag == 0)
	{
		/* Performing Software Reset */
		TC_SoftReset((EN_TC_SLICE_t )u8_lTc);
		
		u32_lFirstFlag = 1;
	}
	else
	{
			/* NOP */
	}
    
    p_stgTCBaseRegs[u8_lTc]->WAVE |= TC_WAVE_WAVEGEN_MFRQ;
    /* Configure Counter as 32-bit */
    p_stgTCBaseRegs[u8_lTc]->CTRLA |= TC_CTRLA_MODE_COUNT32;

    if(p_stfTCEventParams->en_mDelayType == TC_DELAY_US)
    {
        /* Enable */
        p_stgTCBaseRegs[u8_lTc]->CTRLA |= (4 << TC_CTRLA_PRESCALER_POS);
        
        /* Selecting Prescalar and Counter synchronization */
        p_stgTCBaseRegs[u8_lTc]->CTRLA |= TC_CTRLA_PRESCSYNC_PRESC;
        
        p_stgTC32BitBaseRegs[u8_lTc]->CC[0] = \
                TC_GetEventPeriodValueinTime(p_stfTCEventParams->u32_mTime, 16, TC_DELAY_US);
    }
    else if(p_stfTCEventParams->en_mDelayType == TC_DELAY_MS)
    {
        /* Enable */
        p_stgTCBaseRegs[u8_lTc]->CTRLA |= (7 << TC_CTRLA_PRESCALER_POS);
        
        /* Selecting Prescalar and Counter synchronization */
        p_stgTCBaseRegs[u8_lTc]->CTRLA |= TC_CTRLA_PRESCSYNC_PRESC;
        
        p_stgTC32BitBaseRegs[u8_lTc]->CC[0] = \
                    TC_GetEventPeriodValueinTime(p_stfTCEventParams->u32_mTime, 1024, TC_DELAY_MS);
    }
    else
    {
        /* No Action */
    }

    while(p_stgTCBaseRegs[u8_lTc]->SYNCBUSY & TC_SYNCBUSY_CC0);
    
    p_stgTCBaseRegs[u8_lTc]->INTENSET |= TC_INTENSET_MC0;
    
    /* Assigning Function Pointers for User Handlers */
    fp_TCUserHandler[u8_lTc] = p_stfTCEventParams->fp_User_Handler;
    au8_gUsingTimerEvent[u8_lTc] = 1;
    
    /* Enable NVIC for respective tc module */
	switch(u8_lTc)
	{
		case 0:
		{
			NVIC_EnableInterrupt(TC0_IRQ);
		}
		break;
		
		case 1:
		{
			NVIC_EnableInterrupt(TC1_IRQ);
		}
		break;
		
		case 2:
		{
			NVIC_EnableInterrupt(TC2_IRQ);
		}
		break;
		
		case 3:
		{
			NVIC_EnableInterrupt(TC3_IRQ);
		}
		break;
		
		case 4:
		{
			NVIC_EnableInterrupt(TC4_IRQ);
		}
		break;
		
        case 5:
		{
			NVIC_EnableInterrupt(TC5_IRQ);
		}
		break;
        
        case 6:
		{
			NVIC_EnableInterrupt(TC6_IRQ);
		}
		break;
        
        case 7:
		{
			NVIC_EnableInterrupt(TC7_IRQ);
		}
		break;
        
		default :
		{
			/* NOP */
		}
		break;
	}
    
    p_stgTCBaseRegs[u8_lTc]->CTRLA |= TC_CTRLA_ENABLE;
    while(p_stgTCBaseRegs[u8_lTc]->SYNCBUSY & TC_SYNCBUSY_ENABLE);
}			

/**************************************************************************************************/
/* Function Name   : void TC_CaptureEvents(ST_TC_CAPTURE_EVENT_PARAMS_t *p_stfCaptureEventParams) */
/*                                                                                                */
/* Description     : This function is used to capture the event                                   */
/*                                                                                                */
/* In Params       : p_stfCaptureEventParams                                                      */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TC_CaptureEvents(ST_TC_CAPTURE_EVENT_PARAMS_t *p_stfCaptureEventParams)
{
	
	static INT32U u32_lFirstFlag = 0;
	INT32U u32_lSlice = p_stfCaptureEventParams->en_mTCSlice;	
	
	/* Enabling GCLK clock for respective slice */
	switch (u32_lSlice)
    {
    	case 0:
        {
            /*Enabling clock for TC 0*/
            MCLK_PeriphClkInit(MCLK_APBA, MCLK_APBA_TCn0);
            GCLK_PeripheralClockEnable(GCLK_TC0);
        }
    	break;
        
        case 1:
        {
            MCLK_PeriphClkInit(MCLK_APBA, MCLK_APBA_TCn1);
            GCLK_PeripheralClockEnable(GCLK_TC1);
        }
        break;
        
        case 2:
        {
            MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_TCn2);
            GCLK_PeripheralClockEnable(GCLK_TC2);
        }
        break;
        
        case 3:
        {
            MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_TCn3);
            GCLK_PeripheralClockEnable(GCLK_TC2);
        }
        break;
        
        case 4:
        {
            MCLK_PeriphClkInit(MCLK_APBC, MCLK_APBC_TCn4);
            GCLK_PeripheralClockEnable(GCLK_TC4);
        }
        break;
        
        case 5:
        {
            MCLK_PeriphClkInit(MCLK_APBC, MCLK_APBC_TCn5);
            GCLK_PeripheralClockEnable(GCLK_TC4);
        }
        break;
        
        case 6:
        {
            MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_TC6);
            GCLK_PeripheralClockEnable(GCLK_TC6);
        }
        break;
        
        case 7:
        {
            MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_TC7);
            GCLK_PeripheralClockEnable(GCLK_TC6);
        }
        break;
        
        default :
            break;
    }

	/* Disable TC */
	//TC_Disable((EN_TC_SLICE_t )u32_lSlice);

  	/* Perform Software RESET */
	if(u32_lFirstFlag == 0)
	{
		/* Performing Software Reset */
		TC_SoftReset((EN_TC_SLICE_t )u32_lSlice);
		
		u32_lFirstFlag = 1;
	}
	else
	{
			/* NOP */
	}
    
	/* Selecting Prescalar for timer */
	p_stgTCBaseRegs[u32_lSlice]->CTRLA |= (6 << TC_CTRLA_PRESCALER_POS);
	
	/* Selecting Prescalar and Counter synchronization */
	p_stgTCBaseRegs[u32_lSlice]->CTRLA |= TC_CTRLA_PRESCSYNC_PRESC;
		
	/* Configure TImer in capture mode */
	if(p_stfCaptureEventParams->en_mCaptureChannel == TC_CCx_CHANNEL_0)
	{
		/* Enabling Capture/Compare Ch0 for Capturing */
		p_stgTCBaseRegs[u32_lSlice]->CTRLA |= TC_CTRLA_CAPTEN0;
		
        /* Configure Falling Edge */
		if(p_stfCaptureEventParams->en_mEdgeSel == TC_FALLING_EDGE)
		{
			/* Enabling WO invertible to input pin */
			p_stgTCBaseRegs[u32_lSlice]->DRVCTRL |= TC_DRVCTRL_INVEN0;	
		}
		
        p_stgTCBaseRegs[u32_lSlice]->CTRLA |= (2 << 24);
        /* Enable Capture on IO Pin */
        p_stgTCBaseRegs[u32_lSlice]->CTRLA |= TC_CTRLA_COPEN0;
	}
	else if(p_stfCaptureEventParams->en_mCaptureChannel == TC_CCx_CHANNEL_1)
	{
		/* Enabling Capture/Compare Ch1 for Capturing */
		p_stgTCBaseRegs[u32_lSlice]->CTRLA |= TC_CTRLA_CAPTEN1;
		
		/* Configure Falling Edge */
		if(p_stfCaptureEventParams->en_mEdgeSel == TC_FALLING_EDGE)
		{
			/* Enabling WO invertible to input pin */
			p_stgTCBaseRegs[u32_lSlice]->DRVCTRL |= TC_DRVCTRL_INVEN1;	
		}	
        /* Enable Capture on IO Pin */
        p_stgTCBaseRegs[u32_lSlice]->CTRLA |= TC_CTRLA_COPEN1;
	}
	else
	{
		/* NOP */
	}
    
    /* Configure PPW  */
   // p_stgTCBaseRegs[u32_lSlice]->EVCTRL |=  0x05;
    
    /* Enable Error Interrupt */
    p_stgTCBaseRegs[u32_lSlice]->INTENSET |= TC_INTENSET_ERR;
    
    if(p_stfCaptureEventParams->en_mCaptureChannel == TC_CCx_CHANNEL_0)
    {
        /* Enable Caputre Interrupt */
        p_stgTCBaseRegs[u32_lSlice]->INTENSET |= TC_INTENSET_MC0;
    }
    
    else if(p_stfCaptureEventParams->en_mCaptureChannel == TC_CCx_CHANNEL_1)
    {
        /* Enable Caputre Interrupt */
        p_stgTCBaseRegs[u32_lSlice]->INTENSET |= TC_INTENSET_MC1;
    }
    else
    {
        /* NO Action */
    }
	
	/* Enable NVIC for respective tc module */
	switch(u32_lSlice)
	{
		case 0:
		{
			NVIC_EnableInterrupt(TC0_IRQ);
		}
		break;
		
		case 1:
		{
			NVIC_EnableInterrupt(TC1_IRQ);
		}
		break;
		
		case 2:
		{
			NVIC_EnableInterrupt(TC2_IRQ);
		}
		break;
		
		case 3:
		{
			NVIC_EnableInterrupt(TC4_IRQ);
		}
		break;
		
		case 4:
		{
			NVIC_EnableInterrupt(TC5_IRQ);
		}
		break;
		
        case 5:
		{
			NVIC_EnableInterrupt(TC6_IRQ);
		}
		break;
        
        case 6:
		{
			NVIC_EnableInterrupt(TC7_IRQ);
		}
		break;
        
		default :
		{
			/* NOP */
		}
		break;
	}

	/* Assigning Function Pointers for User Handlers */
	fp_TCCaptureUserHandler[u32_lSlice] = p_stfCaptureEventParams->fp_User_Handler;
    
    /* Clear the Timer Event flag to use Capture */
    au8_gUsingTimerEvent[u32_lSlice] = 0;

	/*Enable Timer */
	TC_Enable(p_stfCaptureEventParams->en_mTCSlice);
}

/**************************************************************************************************/
/* Function Name   : void TC_PWMGenerationInit(ST_TC_PWM_PARAMS_t *p_stfTCPWMParams)              */
/*                                                                                                */
/* Description     : This function is used to generate PWM Waveform                               */
/*                                                                                                */
/* In Params       : p_stfTCPWMParams                                                             */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/ 

void TC_PWMInit(ST_TC_PWM_PARAMS_t *p_stfTCPWMParams)
{
	INT32U u32_lPresclar =0;
	INT16U u16_lPeriodValue = 0;
    INT16U u16_lCompVal = 0;
	
	/* Clock = 48MHZ */
	//INT32U u32_lGCLK = SYSTEM_CLOCK_FREQUENCY;
	
	INT32U u32_lSlice = p_stfTCPWMParams->en_mTCSlice;	
	
	/* Enabling GCLK clock for respective slice */
	switch (u32_lSlice)
    {
    	case 0:
        {
            /*Enabling clock for TC 0*/
            MCLK_PeriphClkInit(MCLK_APBA, MCLK_APBA_TCn0);
            GCLK_PeripheralClockEnable(GCLK_TC0);
        }
    	break;
        
        case 1:
        {
            MCLK_PeriphClkInit(MCLK_APBA, MCLK_APBA_TCn1);
            GCLK_PeripheralClockEnable(GCLK_TC1);
        }
        break;
        
        case 2:
        {
            MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_TCn2);
            GCLK_PeripheralClockEnable(GCLK_TC2);
        }
        break;
        
        case 3:
        {
            MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_TCn3);
            GCLK_PeripheralClockEnable(GCLK_TC2);
        }
        break;
        
        case 4:
        {
            MCLK_PeriphClkInit(MCLK_APBC, MCLK_APBC_TCn4);
            GCLK_PeripheralClockEnable(GCLK_TC4);
        }
        break;
        
        case 5:
        {
            MCLK_PeriphClkInit(MCLK_APBC, MCLK_APBC_TCn5);
            GCLK_PeripheralClockEnable(GCLK_TC4);
        }
        break;
        
        case 6:
        {
            MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_TC6);
            GCLK_PeripheralClockEnable(GCLK_TC6);
        }
        break;
        
        case 7:
        {
            MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_TC7);
            GCLK_PeripheralClockEnable(GCLK_TC6);
        }
        break;
        
        default :
            break;
    }

	/* Disable TC */
	TC_Disable((EN_TC_SLICE_t )u32_lSlice);
	
	switch(p_stfTCPWMParams->en_mPrescalar)
	{
		case TC_DIV_1:
		{
			u32_lPresclar = 1;
		}
		break;
		case TC_DIV_2:
		{
			u32_lPresclar = 2;
		}
		break;
		case TC_DIV_4:
		{
			u32_lPresclar = 4;
		}
		break;
		case TC_DIV_8:
		{
			u32_lPresclar = 8;
		}
		break;
		case TC_DIV_16:
		{
			u32_lPresclar = 16;
		}
		break;
		case TC_DIV_64:
		{
			u32_lPresclar = 64;
		}
		break;
		case TC_DIV_256:
		{
			u32_lPresclar = 256;
		}
		break;
		case TC_DIV_1024:
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
	TC_SoftReset((EN_TC_SLICE_t )u32_lSlice);
    
	/* Selecting Prescalar for timer */
	p_stgTCBaseRegs[u32_lSlice]->CTRLA |= \
									(p_stfTCPWMParams->en_mPrescalar << TC_CTRLA_PRESCALER_POS);
	
	/* Selecting Prescalar and Counter synchronization */
	p_stgTCBaseRegs[u32_lSlice]->CTRLA |= (1 << 4);
	
    /* Calculating Period Value */
    u16_lPeriodValue = TC_GetEventPeriodValuefor8BitCounter(p_stfTCPWMParams->u32_PWMFreq,\
												                  u32_lPresclar, 120000000);
        
    /* Setting Period Value */
    TC_SetCompareValuefor8BitCoutner((EN_TC_SLICE_t )u32_lSlice,u16_lPeriodValue);
       
    /* Calculating Duty Cycle Value */
    u16_lCompVal =  TC_PWMGetCompareValue((INT8U )p_stfTCPWMParams->f32_mCompDutyCycle, \
                                                                    u16_lPeriodValue);
		
    /* Setting Duty Cycle Value in Compare register 1 */
    TC_PWMSetCompareValue(p_stfTCPWMParams->en_mTCSlice,TC_CCx_CHANNEL_1,u16_lCompVal);
       
    /* Enable Waveform Generation */
    p_stgTCBaseRegs[u32_lSlice]->WAVE |= TC_WAVE_WAVEGEN_MPWM;
    
    /* Set the Timer Event flag as 1 */
    au8_gUsingTimerEvent[u32_lSlice] = 1;
							
	/*Enable Timer */
	TC_Enable(p_stfTCPWMParams->en_mTCSlice);
}

/**************************************************************************************************/
/* Function Name   : INT16U TC_GetEventPeriodValueinTime(INT32U u32_fTimeinMs,INT32U \            */
/*                                                                u32_fPresclar,INT32U u32_fGCLK) */
/*                                                                                                */
/* Description     : This function used to calculate Period Value                                 */
/*                                                                                                */
/* In Params       : u32_fTimeinMs, u32_fPresclar, u32_fGCLK                                      */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : INT16U                                                                       */
/**************************************************************************************************/ 

INT16U TC_GetEventPeriodValueinTime(INT32U u32_fTimeinMs,INT32U u32_fPresclar, \
                    EN_TC_DELAY_TYPE_t en_fDelayType)
{
	INT16U u16_lPeriodValue = 0;
	INT32F f32_lTimeinSec = 0;
	INT32F f32_lTempFreq = 0;
	
    if(TC_DELAY_MS == en_fDelayType)
    {
         f32_lTimeinSec = ((INT32F )u32_fTimeinMs/1000);
	}
    else 
    {
        f32_lTimeinSec = ((INT32F )u32_fTimeinMs/1000000);
    }
    
	INT32F f32_fPWMFreqHZ = (float )((INT32F )1/f32_lTimeinSec);
	
	f32_lTempFreq = (120000000/u32_fPresclar);
	
	u16_lPeriodValue = (INT16U)((f32_lTempFreq/f32_fPWMFreqHZ)-1);
    
	return u16_lPeriodValue;
}

/**************************************************************************************************/
/* Function Name   : INT16U TC_GetEventPeriodValueinTime(INT32U u32_fTimeinMs,INT32U \            */
/*                                                                u32_fPresclar,INT32U u32_fGCLK) */
/*                                                                                                */
/* Description     : This function used to calculate Period Value                                 */
/*                                                                                                */
/* In Params       : u32_fTimeinMs, u32_fPresclar, u32_fGCLK                                      */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : INT16U                                                                       */
/**************************************************************************************************/ 

INT16U TC_GetPwmPeriodValueinTime(INT32U u32_fTimeinMs,INT32U u32_fPresclar)
{
	INT16U u16_lPeriodValue = 0;
	INT32F f32_lTimeinSec = 0;
	INT32F f32_lTempFreq = 0;

    f32_lTimeinSec = ((INT32F )u32_fTimeinMs/1000000);

	INT32F f32_fPWMFreqHZ = (float )((INT32F )1/f32_lTimeinSec);
	
	f32_lTempFreq = (120000000/u32_fPresclar);
	
	u16_lPeriodValue = (INT16U)((f32_lTempFreq/f32_fPWMFreqHZ)-1);
    
	return u16_lPeriodValue;
}

/**************************************************************************************************/
/* Function Name   : INT16U TC_PWMGetCompareValue(INT8U u8_fDutyCycle,INT16U u16_fPeriod)         */
/*                                                                                                */
/* Description     : This function used to find Duty cycle                                        */
/*                                                                                                */
/* In Params       : u8_fDutyCycle, u16_fPeriod                                                   */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : INT8U                                                                        */
/**************************************************************************************************/ 

INT16U TC_PWMGetCompareValue(INT8U u8_fDutyCycle,INT16U u16_fPeriod)
{
	INT32F f32_lTemp = 0;
	
	INT16U	u16_lCompare = 0;
	
	//u32_fDutyCycle = 100 - u32_fDutyCycle;
	/* If User gives duty cycle more than 100 put max value to 100 */
	if(u8_fDutyCycle > 100 )
	{
		u8_fDutyCycle = 99;
	}
	
	f32_lTemp = (INT32F)((INT32F)u8_fDutyCycle/100 );
	
	u16_lCompare = (INT16U )(f32_lTemp * u16_fPeriod);
	
	return u16_lCompare;
}

/**************************************************************************************************/
/* Function Name   : void TC_PWMSetCompareValue(EN_TC_SLICE_t en_fSlice,EN_TC_CCx_CHANNEL_SEL_t \
                                                                en_fCh,INT16U u16_fCompval)       */
/*                                                                                                */
/* Description     : This function used to Set Duty Cycle                                         */
/*                                                                                                */
/* In Params       : en_fSlice, en_fCh, u16_fCompval                                              */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/ 

void TC_PWMSetCompareValue(EN_TC_SLICE_t en_fSlice,EN_TC_CCx_CHANNEL_SEL_t en_fCh,INT16U u16_fCompval)
{
    p_stgTC8BitBaseRegs[en_fSlice]->CC[en_fCh] = u16_fCompval;
}

/**************************************************************************************************/
/* Function Name   : void TC_SetCompareValue(EN_TC_SLICE_t en_fSlice, \                           */
/*									EN_CCx_CHANNEL_SEL_t en_fCh,INT32U u32_fCompval)              */
/*                                                                                                */
/* Description     : Sets the compare value                                                       */
/*                                                                                                */
/* In Params       : en_fSlice, en_fCh ,u32_fCompval                                              */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TC_SetCompareValue(EN_TC_SLICE_t en_fSlice,EN_TC_CCx_CHANNEL_SEL_t en_fCh,INT16U u16_fCompval)
{ 
	/* Set Compare Value */ 	
	p_stgTC32BitBaseRegs[en_fSlice]->CC[en_fCh] = u16_fCompval;
}

/**************************************************************************************************/
/* Function Name   : INT8U TC_GetEventPeriodValuefor8BitCounter(INT32U u32_fFreqHz,INT32U \       */
/*                                                          u32_fPresclar, INT32U u32_fGCLKFreq)  */
/*                                                                                                */
/* Description     : This function used to Calculate Period value                                 */
/*                                                                                                */
/* In Params       : u32_fFreqHz, u32_fPresclar, u32_fGCLKFreq                                    */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : INT8U                                                                        */
/**************************************************************************************************/ 

INT8U TC_GetEventPeriodValuefor8BitCounter(INT32U u32_fFreqHz,INT32U u32_fPresclar,\
                                                                            INT32U u32_fGCLKFreq)
{
    INT32F f32_lTempFreq = 0;
    INT8U u8_lPeriod = 0;

	/* Period = ((FGCLK/(N*FPWM))-1) */
	
	f32_lTempFreq = (u32_fGCLKFreq/u32_fPresclar);
	
	u8_lPeriod = (INT8U)((f32_lTempFreq/u32_fFreqHz)-1);
	
	return u8_lPeriod;
}


/**************************************************************************************************/
/* Function Name   : void TC_SetCompareValuefor8BitCoutner(EN_TC_SLICE_t en_fSlice, \             */
/*									EN_CCx_CHANNEL_SEL_t en_fCh,INT32U u32_fCompval)              */
/*                                                                                                */
/* Description     : Sets the compare value                                                       */
/*                                                                                                */
/* In Params       : en_fSlice, en_fCh ,u32_fCompval                                              */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TC_SetCompareValuefor8BitCoutner(EN_TC_SLICE_t en_fSlice, INT8U u8_fCompval)
{
	/* Set Compare Value */ 	
	p_stgTC8BitBaseRegs[en_fSlice]->CC[0] = u8_fCompval;
}

/**************************************************************************************************/
/* Function Name   : INT16U TC_GetCaptureValue(EN_TC_SLICE_t en_fSlice, EN_TC_CCx_CHANNEL_SEL_t \ */
/*                                                                                   en_fChNo)    */
/*                                                                                                */
/* Description     : This function used to Get Capture Value                                      */
/*                                                                                                */
/* In Params       : en_fSlice, en_fChNo                                                          */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : INT16U                                                                       */
/**************************************************************************************************/

INT16U TC_GetCaptureValue(EN_TC_SLICE_t en_fSlice, EN_TC_CCx_CHANNEL_SEL_t en_fChNo)
{
	INT16U u16_lCaptureCount = 0;
	
	u16_lCaptureCount = p_stgTC32BitBaseRegs[en_fSlice]->CC[en_fChNo];

	return u16_lCaptureCount;

}
/**************************************************************************************************/
/* Function Name   : void TC_Enable(EN_TC_SLICE_t en_fSlice)                                      */
/*                                                                                                */
/* Description     : Starts the Timer 									                          */
/*                                                                                                */
/* In Params       : en_fSlice                                                                    */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TC_Enable(EN_TC_SLICE_t en_fSlice)
{
	/* Enabling Timer */
	p_stgTCBaseRegs[en_fSlice]->CTRLA |= TC_CTRLA_ENABLE;

	/* Wait for Sync Enable */
	while((p_stgTCBaseRegs[en_fSlice]->SYNCBUSY) & TC_SYNCBUSY_ENABLE);
}

/**************************************************************************************************/
/* Function Name   : void TC_Disable(EN_TC_SLICE_t en_fSlice)                                     */
/*                                                                                                */
/* Description     : This functio used to Disable the Timer                                       */
/*                                                                                                */
/* In Params       : en_fSlice                                                                    */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TC_Disable(EN_TC_SLICE_t en_fSlice)
{
	/* Enabling Timer */
	p_stgTCBaseRegs[en_fSlice]->CTRLA &= ~TC_CTRLA_ENABLE;

	/* Wait for Sync Enable */
	while((p_stgTCBaseRegs[en_fSlice]->SYNCBUSY) & TC_SYNCBUSY_ENABLE);
}

/**************************************************************************************************/
/* Function Name   : void TC_SoftReset(EN_TC_SLICE_t en_fSlice)                                   */
/*                                                                                                */
/* Description     : Performs Software Reset to the timer                                         */
/*                                                                                                */
/* In Params       : en_fSlice                                                                    */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TC_SoftReset(EN_TC_SLICE_t en_fSlice)
{	
	/* Performing software reset */
	p_stgTCBaseRegs[en_fSlice]->CTRLA = TC_CTRLA_SWRST;
    
    /* Wait for Sync SWRST*/
	while((p_stgTCBaseRegs[en_fSlice]->SYNCBUSY) & TC_SYNCBUSY_SWRST);

}

/**************************************************************************************************/
/* End of TC.c                                                                                    */
/**************************************************************************************************/
