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
/* \File Name   : ADC.c                                                                           */
/* \Author      : Ravi Ranjan Kumar                                                               */
/* \Version 	: 1.1                                                                             */
/* \Date        : 14/12/2015                                                                      */
/*                                                                                                */
/* @Description :  ADC Driver Framework                                                           */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "GPIO.h"
#include "GCLK.h"
#include "MCLK.h"
#include "NVIC.h"

#include "ADC.h"
#include "ADC_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Structure Pointer to Access ADC System Registers */
ST_ADC_REG_t *p_stgADCRegAccess[MAX_ADC]=	{	
												(ST_ADC_REG_t *)ADC0_BASE_ADDRESS,
												(ST_ADC_REG_t *)ADC1_BASE_ADDRESS
											};

/* ADC User Handlers */
void (*fp_gADCUserHandler[2][16])(void);

INT8U u8_gTriggerInProgress = 0;

/**************************************************************************************************/
/* Function Name   : void ADC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : ADC System Handler                                                           */
/*                                                                                                */
/**************************************************************************************************/

void ADC0_1_Handler(void)
{
	if(p_stgADCRegAccess[ADC_0]->INTFLAG & ADC_INTFLAG_RESRDY)
	{
		p_stgADCRegAccess[ADC_0]->INTFLAG |= ADC_INTFLAG_RESRDY;
		
		switch(p_stgADCRegAccess[ADC_0]->INPUTCTRL & ADC_INPUTCTRL_MUXPOS_Msk)
		{
			case 0x00:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][0]))
				{
					/* Calling User Handler for ADC channel 0 */
					fp_gADCUserHandler[ADC_0][0]();
				}
			}
			break;
			
			case 0x01:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][1]))
				{
					/* Calling User Handler for ADC channel 1 */
					fp_gADCUserHandler[ADC_0][1]();
				}
			}
			break;
			
			case 0x02:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][2]))
				{
					/* Calling User Handler for ADC channel 2 */
					fp_gADCUserHandler[ADC_0][2]();
				}
			}
			break;
			case 0x03:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][3]))
				{
					/* Calling User Handler for ADC channel 3 */
					fp_gADCUserHandler[ADC_0][3]();
				}
			}
			break;
			
			case 0x04:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][4]))
				{
					/* Calling User Handler for ADC channel 4 */
					fp_gADCUserHandler[ADC_0][4]();
				}
			}
			break;
			
			case 0x05:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][5]))
				{
					/* Calling User Handler for ADC channel 5 */
					fp_gADCUserHandler[ADC_0][5]();
				}
			}
			break;
			case 0x06:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][6]))
				{
					/* Calling User Handler for ADC channel 6 */
					fp_gADCUserHandler[ADC_0][6]();
				}
			}
			break;
			
			case 0x07:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][7]))
				{
					/* Calling User Handler for ADC channel 7 */
					fp_gADCUserHandler[ADC_0][7]();
				}
			}
			break;
			
			case 0x08:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][8]))
				{
					/* Calling User Handler for ADC channel 8 */
					fp_gADCUserHandler[ADC_0][8]();
				}
			}
			break;
			
			case 0x09:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][9]))
				{
					/* Calling User Handler for ADC channel 9 */
					fp_gADCUserHandler[ADC_0][9]();
				}
			}
			break;
			
			case 0x0A:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][10]))
				{
					/* Calling User Handler for ADC channel 10 */
					fp_gADCUserHandler[ADC_0][10]();
				}
			}
			break;
			
			case 0x0B:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][11]))
				{
					/* Calling User Handler for ADC channel 11 */
					fp_gADCUserHandler[ADC_0][11]();
				}
			}
			break;
			
			case 0x0C:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][12]))
				{
					/* Calling User Handler for ADC channel 12 */
					fp_gADCUserHandler[ADC_0][12]();
				}
			}
			break;
			
			case 0x0D:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][13]))
				{
					/* Calling User Handler for ADC channel 13 */
					fp_gADCUserHandler[ADC_0][13]();
				}
			}
			break;
			
			case 0x0E:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][14]))
				{
					/* Calling User Handler for ADC channel 14 */
					fp_gADCUserHandler[ADC_0][14]();
				}
			}
			break;
			
			case 0x0F:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_0][15]))
				{
					/* Calling User Handler for ADC channel 15 */
					fp_gADCUserHandler[ADC_0][15]();
				}
			}
			break;
			default :
			break;
		}
        
        u8_gTriggerInProgress = 0;
	}
}

/**************************************************************************************************/
/* Function Name   : void ADC_Handler(void)                                                       */
/*                                                                                                */
/* Description     : ADC System Handler                                                           */
/*                                                                                                */
/**************************************************************************************************/

void ADC1_1_Handler(void)
{
	if(p_stgADCRegAccess[ADC_1]->INTFLAG & ADC_INTFLAG_RESRDY)
	{
		p_stgADCRegAccess[ADC_1]->INTFLAG |= ADC_INTFLAG_RESRDY;
		
		switch(p_stgADCRegAccess[ADC_1]->INPUTCTRL & ADC_INPUTCTRL_MUXPOS_Msk)
		{
			case 0x00:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][0]))
				{
					/* Calling User Handler for ADC channel 0 */
					fp_gADCUserHandler[ADC_1][0]();
				}
			}
			break;
			
			case 0x01:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][1]))
				{
					/* Calling User Handler for ADC channel 1 */
					fp_gADCUserHandler[ADC_1][1]();
				}
			}
			break;
			
			case 0x02:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][2]))
				{
					/* Calling User Handler for ADC channel 2 */
					fp_gADCUserHandler[ADC_1][2]();
				}
			}
			break;
			case 0x03:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][3]))
				{
					/* Calling User Handler for ADC channel 3 */
					fp_gADCUserHandler[ADC_1][3]();
				}
			}
			break;
			
			case 0x04:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][4]))
				{
					/* Calling User Handler for ADC channel 4 */
					fp_gADCUserHandler[ADC_1][4]();
				}
			}
			break;
			
			case 0x05:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][5]))
				{
					/* Calling User Handler for ADC channel 5 */
					fp_gADCUserHandler[ADC_1][5]();
				}
			}
			break;
			case 0x06:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][6]))
				{
					/* Calling User Handler for ADC channel 6 */
					fp_gADCUserHandler[ADC_1][6]();
				}
			}
			break;
			
			case 0x07:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][7]))
				{
					/* Calling User Handler for ADC channel 7 */
					fp_gADCUserHandler[ADC_1][7]();
				}
			}
			break;
			
			case 0x08:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][8]))
				{
					/* Calling User Handler for ADC channel 8 */
					fp_gADCUserHandler[ADC_1][8]();
				}
			}
			break;
			
			case 0x09:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][9]))
				{
					/* Calling User Handler for ADC channel 9 */
					fp_gADCUserHandler[ADC_1][9]();
				}
			}
			break;
			
			case 0x0A:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][10]))
				{
					/* Calling User Handler for ADC channel 10 */
					fp_gADCUserHandler[ADC_1][10]();
				}
			}
			break;
			
			case 0x0B:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][11]))
				{
					/* Calling User Handler for ADC channel 11 */
					fp_gADCUserHandler[ADC_1][11]();
				}
			}
			break;
			
			case 0x0C:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][12]))
				{
					/* Calling User Handler for ADC channel 12 */
					fp_gADCUserHandler[ADC_1][12]();
				}
			}
			break;
			
			case 0x0D:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][13]))
				{
					/* Calling User Handler for ADC channel 13 */
					fp_gADCUserHandler[ADC_1][13]();
				}
			}
			break;
			
			case 0x0E:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][14]))
				{
					/* Calling User Handler for ADC channel 14 */
					fp_gADCUserHandler[ADC_1][14]();
				}
			}
			break;
			
			case 0x0F:
			{
				/* Checking if the User Handler is defined */
				if(PNULL != (fp_gADCUserHandler[ADC_1][15]))
				{
					/* Calling User Handler for ADC channel 15 */
					fp_gADCUserHandler[ADC_1][15]();
				}
			}
			break;
			default :
			break;
		}
        
        u8_gTriggerInProgress = 0;
	}
}

/**************************************************************************************************/
/* Function Name   : void ADC_Init(ST_ADC_PARAMS_t *p_stfADCParams)                   			  */
/*                                                                                                */
/* Description     : Initializes ADC                                                              */
/*                                                                                                */
/* In Params       : ST_ADC_PARAMS_t *p_stfADCParams                                  			  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : Void                                                                         */
/**************************************************************************************************/

void ADC_Init(ST_ADC_PARAMS_t *p_stfADCParams)
{
	static INT32U u32_lAdc0Flag = 0;
	static INT32U u32_lAdc1Flag = 0;
	
	EN_ADC_SEL_t en_lADCModule = p_stfADCParams->en_mADCModule;
	
	/* Enable ADC Clock */
	if(ADC_0 == en_lADCModule)
	{
		if(0 == u32_lAdc0Flag)
		{
			u32_lAdc0Flag = 1;
			
			/* ADC0 Clk Init */
			MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_ADCn0);
			GCLK_PeripheralClockEnable(GCLK_ADC0);
			
			/* Disable ADC */
			ADC_Operation(ADC_0, ADC_DISABLE);
			
			/* WAITING FOR SYNC BUSY */
			while(p_stgADCRegAccess[ADC_0]->SYNCBUSY & ADC_SYNCBUSY_ENABLE_MASK);
			
			/* Reset ADC */
			ADC_Operation(ADC_0, ADC_SWRST);
			
			/* WAITING FOR SYNC BUSY */
			while(p_stgADCRegAccess[ADC_0]->SYNCBUSY & ADC_SYNCBUSY_SWRST_MASK);
		}
		else
		{
			/* No Action */
		}
	}
	else
	{
		if(0 == u32_lAdc1Flag)
		{
			u32_lAdc1Flag = 1;
			
			/* ADC1 Clk Init */
			MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_ADCn1);
			GCLK_PeripheralClockEnable(GCLK_ADC1);
			
			/* Disable ADC */
			ADC_Operation(ADC_1, ADC_DISABLE);
			
			/* WAITING FOR SYNC BUSY */
			while(p_stgADCRegAccess[ADC_1]->SYNCBUSY & ADC_SYNCBUSY_ENABLE_MASK);
			
			/* Reset ADC */
			ADC_Operation(ADC_1, ADC_SWRST);
			
			/* WAITING FOR SYNC BUSY */
			while(p_stgADCRegAccess[ADC_1]->SYNCBUSY & ADC_SYNCBUSY_SWRST_MASK);
		}
		else
		{
			/* No Action */
		}
	}
	
	/* Disable ADC */
	ADC_Operation(en_lADCModule, ADC_DISABLE);

	/* Selecting Conversion resolution */
	p_stgADCRegAccess[en_lADCModule]->CTRLB &= ~(ADC_CTRLB_RESSEL_Msk);
	p_stgADCRegAccess[en_lADCModule]->CTRLB |= \
									(p_stfADCParams->en_mADCResolution << ADC_CTRLB_RESSEL_Pos);
	
	/* Selecting VREF = VDDANA (3.3v) */
	p_stgADCRegAccess[en_lADCModule]->REFCTRL |= 0x03; //ADC_REFCTRL_REFSEL_INTVCC2_MASK;
	
	/* Configuring Average sample */
	p_stgADCRegAccess[en_lADCModule]->AVGCTRL &= ~ADC_AVGCTRL_SAMPLENUM_Msk;
	p_stgADCRegAccess[en_lADCModule]->AVGCTRL |= \
							(p_stfADCParams->en_mADCSample << ADC_AVGCTRL_SAMPLENUM_Pos);
	
	/* Configuring Sampling time */
	p_stgADCRegAccess[en_lADCModule]->SAMPCTRL &= ~ADC_SAMPCTRL_SAMPLEN_Msk;
	p_stgADCRegAccess[en_lADCModule]->SAMPCTRL |= \
								(p_stfADCParams->u8_mSampleTimeLen << ADC_SAMPCTRL_SAMPLEN_Pos);
	/* Selecting Prescalar */
	p_stgADCRegAccess[en_lADCModule]->CTRLA &= ~ADC_CTRLA_PRESCALER_MASK;
	p_stgADCRegAccess[en_lADCModule]->CTRLA |= \
								  (p_stfADCParams->en_mADCPrescalar << ADC_CTRLA_PRESCALER_Pos);
	
	/* Enabling Interrupt for Conversion Complete (Result Ready) */
	p_stgADCRegAccess[en_lADCModule]->INTENSET |= ADC_INTENSET_RESRDY_MASK;
	
	/* Enabling NVIC */
	if(ADC_0 == en_lADCModule)
	{
		NVIC_EnableInterrupt(ADC0_1_IRQ);
	}
	else
	{
		NVIC_EnableInterrupt(ADC1_1_IRQ);
	}
	
	/* Assigning Pointer for User Handler */
	fp_gADCUserHandler[en_lADCModule][p_stfADCParams->en_mADCChannel] = \
                                                                p_stfADCParams->fp_ADCUserHandler;
	
	/* Enabling ADC */
	ADC_Operation(en_lADCModule, ADC_ENABLE);
	
	/* WAITING FOR SYNC BUSY */
	while(p_stgADCRegAccess[en_lADCModule]->SYNCBUSY & ADC_SYNCBUSY_ENABLE_MASK);
}

/**************************************************************************************************/
/* Function Name   : void ADC_Operation(EN_ADC_CTRLA_OPER_SEL_t en_fOperationSel)                 */
/*                                                                                                */
/* Description     : Performs operation like SWRST, ENABLE, DISABLE etc                           */
/*                                                                                                */
/* In Params       : EN_ADC_CTRLA_OPER_SEL_t en_fOperationSel                                     */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ADC_Operation(EN_ADC_SEL_t en_fADCModule, EN_ADC_CTRLA_OPER_SEL_t en_fOperationSel)
{
	switch(en_fOperationSel)
	{
		case ADC_SWRST:
		{
			/* WAITING FOR SYNC BUSY */
			while(p_stgADCRegAccess[en_fADCModule]->SYNCBUSY & ADC_SYNCBUSY_SWRST_MASK);
			
			p_stgADCRegAccess[en_fADCModule]->CTRLA |= ADC_CTRLA_SWRST_MASK;
		}
		break;
		
		case ADC_ENABLE:
		{
			/* WAITING FOR SYNC BUSY */
			while(p_stgADCRegAccess[en_fADCModule]->SYNCBUSY & \
									(ADC_SYNCBUSY_ENABLE_MASK | ADC_SYNCBUSY_SWRST_MASK));
			
			p_stgADCRegAccess[en_fADCModule]->CTRLA |= ADC_CTRLA_ENABLE_MASK;
		}
		break;
		
		case ADC_RUNSTDBY :
		{
			/* Waiting for SYNC */
			while(p_stgADCRegAccess[en_fADCModule]->SYNCBUSY & ADC_SYNCBUSY_MASK);
			
			p_stgADCRegAccess[en_fADCModule]->CTRLA |= ADC_CTRLA_RUNSTDBY_MASK;
		}
		break;
		
		case ADC_ONDEMAND:
		{
			/* Waiting for SYNC */
			while(p_stgADCRegAccess[en_fADCModule]->SYNCBUSY & ADC_SYNCBUSY_MASK);
			
			p_stgADCRegAccess[en_fADCModule]->CTRLA |= ADC_CTRLA_ONDEMAND_MASK;
		}
		break;
		
		case ADC_DISABLE:
		{
			/* WAITING FOR SYNC BUSY */
			while(p_stgADCRegAccess[en_fADCModule]->SYNCBUSY & \
									(ADC_SYNCBUSY_ENABLE_MASK | ADC_SYNCBUSY_SWRST_MASK));
			
			p_stgADCRegAccess[en_fADCModule]->CTRLA &= ~ADC_CTRLA_ENABLE_MASK;
		}
		break;
		
		default:
		{
			/* No Action */
		}
		break;
	}
}

/**************************************************************************************************/
/* Function Name   :  void ADC_Trigger(EN_ADC_TRIGGER_SEL_t en_fTrigger)                          */
/*                                                                                                */
/* Description     :  API to perform software Trigger for start conversion and flush              */
/*                                                                                                */
/* In Params       :  EN_ADC_TRIGGER_SEL_t en_fTrigger                                            */
/*                                                                                                */
/* Out Params      :  void                                                                        */
/*                                                                                                */
/* Return Value    :  void                                                                        */
/**************************************************************************************************/

void ADC_Trigger(EN_ADC_SEL_t en_fADCModule, EN_ADC_CHANNEL_t en_lADCChannel, \
														EN_ADC_TRIGGER_SEL_t en_fTrigger)
{
    while(1 == u8_gTriggerInProgress);
    
    u8_gTriggerInProgress = 1;
    
	/* Selecting ADC Input Pin */
	p_stgADCRegAccess[en_fADCModule]->INPUTCTRL &= ~ADC_INPUTCTRL_MUXPOS_Msk;
	p_stgADCRegAccess[en_fADCModule]->INPUTCTRL |= en_lADCChannel << ADC_INPUTCTRL_MUXPOS_Pos;
	
	switch(en_fTrigger)
	{
		case ADC_START_CONVERSION:
		{
			/* Waiting for SYNC */
			while(p_stgADCRegAccess[en_fADCModule]->SYNCBUSY & ADC_SYNCBUSY_MASK);
			
			p_stgADCRegAccess[en_fADCModule]->SWTRIG |= ADC_SWTRIG_START_MASK;
		}
		break;
		
		case ADC_FLUSH_CONVERSION:
		{
			/* Waiting for SYNC */
			while(p_stgADCRegAccess[en_fADCModule]->SYNCBUSY & ADC_SYNCBUSY_MASK);
			
			p_stgADCRegAccess[en_fADCModule]->SWTRIG |= ADC_SWTRIG_FLUSH_MASK;
		}
		break;
		default:
		{
			/* NO ACTION */
		}
		break;	
	}
}

/**************************************************************************************************/
/* Function Name   : INT16U ADC_GetResult(void)                                                   */
/*                                                                                                */
/* Description     : API to get ADC Result                                                        */
/*                                                                                                */
/* In Params       : void                                                                         */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : u16_lResult                                                                  */
/**************************************************************************************************/

INT16U ADC_GetResult(EN_ADC_SEL_t en_fADCModule)
{
    INT16U u16_lResult = 0;

    u16_lResult = p_stgADCRegAccess[en_fADCModule]->RESULT;

    return u16_lResult;
}

/*************************************************************************************************/
/* Function Name: INT32F ADC_GetAnalogEquivalent(INT16U u16_fADCResult)  		                 */
/*                                                                            					 */
/* Description	: Converts received Adc result into Analog Equivalent 							 */
/* Parameter	: Value									                      					 */
/* Return Value	: void							 	                          					 */
/*                                                                            					 */
/* Remarks	    : None                                                        					 */
/*************************************************************************************************/

INT32F ADC_GetAnalogEquivalent(EN_ADC_SEL_t en_fADCModule, INT16U u16_fADCResult)
{
	INT32U u32_lMaxCount = 65536;
	INT32F f32_lAnalogEq;
	INT32F f32_lTemp;
	INT32F f32_lVref = 3.3;
	INT32F f32_lAdcCount = u16_fADCResult;
	
	f32_lTemp = f32_lVref/u32_lMaxCount;
	
	f32_lAnalogEq = (f32_lAdcCount * f32_lTemp );
	
	return f32_lAnalogEq;
}
		
/*************************************************************************************************/
/* Function Name: INT32F ADC_GetAnalogEquivalent(INT16U u16_fADCResult)  		                 */
/*                                                                            					 */
/* Description	: Converts received Adc result into Analog Equivalent 							 */
/* Parameter	: Value									                      					 */
/* Return Value	: void							 	                          					 */
/*                                                                            					 */
/* Remarks	    : None                                                        					 */
/*************************************************************************************************/

void ADC_ResetTrigger(void)
{
    u8_gTriggerInProgress = 0;
}

/**************************************************************************************************/
/* End of ADC.c                                                                                   */
/**************************************************************************************************/
