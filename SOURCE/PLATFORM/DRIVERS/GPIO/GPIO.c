/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2016, Think Embedded Pvt. Ltd. (TEPL)	                  */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : PORT.c                                                                          */
/* \Author      : Kishore D                                                                       */
/* \Version     : v1.1                                                                            */
/* \Date        : 23/08/2018  					                                  */
/* @Description : GPIO Driver 					                                  */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <compiler.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "GPIO.h"
#include "GPIO_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Array of Pointer that Holds All the Base Addresses of PORTS */
ST_PORT_REGS_t *p_stgPORTRegAccess[MAX_PORTS] = {
													(ST_PORT_REGS_t *)PORTA_BASE,
													(ST_PORT_REGS_t *)PORTB_BASE,
											  	};

/**************************************************************************************************/
/* Function Name: EN_PORT_RESULT_t GPIO_ConfigurePin(PORT_PIN_DATA_t * p_stfPORTPinData)          */
/*                                                                                                */
/* Description	:	Configures the Given GPIO PORT and PIN Number                                 */
/*                                                                                                */
/* In Params	  :	PORT_PIN_DATA_t * p_stfPORTPinData                                            */
/*                                                                                                */
/* Out Params  	:	None                                                                          */
/*                                                                                                */
/* Return Value	:	EN_PORT_RESULT_t 															  */
/**************************************************************************************************/

EN_PORT_RESULT_t GPIO_Init(ST_GPIO_PARAMS_t *p_stfPORTPinData)
{
	EN_PORT_RESULT_t en_lResult = PORT_SUCCESS;
	
	EN_GPIO_PORT_t en_lPort = p_stfPORTPinData->en_mPortSel;
	EN_GPIO_PIN_t en_lPin =  p_stfPORTPinData->en_mPinSel;
	
	/* Choosing the Pin type (Alternate function) */
	if(p_stfPORTPinData->en_mPinPeriph == GPIO_GENERAL_PURPOSE)
	{
		/* Disable MUX */	
		p_stgPORTRegAccess[en_lPort]->PINCFG[en_lPin] &= ~(BIT_SET << GPIO_PINCFG_PMUXEN_POS);
	}
	else
	{
		/* Enable MUX */	
		p_stgPORTRegAccess[en_lPort]->PINCFG[en_lPin] |= (BIT_SET << GPIO_PINCFG_PMUXEN_POS);
			
		if(en_lPin & 1)
		{
			/* If Pin number is Odd */
			p_stgPORTRegAccess[en_lPort]->PMUX[en_lPin >> 1] &= ~GPIO_PINCFG_PMUXODD_MSK;
			p_stgPORTRegAccess[en_lPort]->PMUX[en_lPin >> 1] |= \
									(p_stfPORTPinData->en_mPinPeriph << GPIO_PINCFG_PMUXODD_POS);		
		}
		else
		{
			/* If Pin number is Even */
			p_stgPORTRegAccess[en_lPort]->PMUX[en_lPin >> 1] &= ~GPIO_PINCFG_PMUXEVEN_MSK;
			p_stgPORTRegAccess[en_lPort]->PMUX[en_lPin >> 1] |= \
									(p_stfPORTPinData->en_mPinPeriph << GPIO_PINCFG_PMUXEVEN_POS);
		}	
	}
	
	/* Setting the Direction of corresponding Port Pin */
	if(GPIO_DIR_OUTPUT == p_stfPORTPinData->en_mPinDir)
	{
		/* Setting Particular Port Pin as Output */
		p_stgPORTRegAccess[en_lPort]->DIRSET = (BIT_SET << en_lPin);
		
		if(GPIO_OUT_LEVEL_HIGH == p_stfPORTPinData->en_mPinType)
		{
			/* Setting Pin Output Level High*/
			p_stgPORTRegAccess[en_lPort]->OUT |= (BIT_SET << en_lPin);
		}
		else if(GPIO_OUT_LEVEL_LOW == p_stfPORTPinData->en_mPinType)
		{
			/* Setting Pin Output Level Low*/
			p_stgPORTRegAccess[en_lPort]->OUT &= ~(BIT_SET << en_lPin);
		}
		else
		{
			/* No Action */
		}
	}
	else
	{
		/* Setting Particular Port Pin as Input */
		p_stgPORTRegAccess[en_lPort]->DIRCLR = (BIT_SET << en_lPin);
		
		/* Selecting Internal Pull Ups */
		if(p_stfPORTPinData->en_mPinType == GPIO_IN_PULL_UP)
		{
			/* Enable Pull and Level*/
			p_stgPORTRegAccess[en_lPort]->PINCFG[en_lPin] |= (BIT_SET << GPIO_PINCFG_PULLEN_POS);
			p_stgPORTRegAccess[en_lPort]->OUTSET = (BIT_SET << en_lPin);
		}
		else if(p_stfPORTPinData->en_mPinType == GPIO_IN_PULL_DOWN)
		{
			/* Enable Pull and Disable Level*/
			p_stgPORTRegAccess[en_lPort]->PINCFG[en_lPin] |= (BIT_SET << GPIO_PINCFG_PULLEN_POS);
			p_stgPORTRegAccess[en_lPort]->OUTCLR = (BIT_SET << en_lPin);
		}
		else
		{
			/* Disable Pull */
			p_stgPORTRegAccess[en_lPort]->PINCFG[en_lPin] &= ~(BIT_SET << GPIO_PINCFG_PULLEN_POS);
		}
		
		/* Enable Input (INEN) */
		p_stgPORTRegAccess[en_lPort]->PINCFG[en_lPin] |= (BIT_SET << GPIO_PINCFG_INEN_POS);
		
		/* Enable input synchronization */
		p_stgPORTRegAccess[en_lPort]->CTRL |= (BIT_SET << en_lPin);
	}
	
	/* Setting Driver Strength */
	if(GPIO_DRIV_STRENGTH_STRONG == p_stfPORTPinData->en_mDriverStrenght)
	{
		p_stgPORTRegAccess[en_lPort]->PINCFG[en_lPin] |= (BIT_SET << GPIO_PINCFG_DRVSTR_POS);
	}
	else
	{
		p_stgPORTRegAccess[en_lPort]->PINCFG[en_lPin] &= ~(BIT_SET << GPIO_PINCFG_DRVSTR_POS);
	}

	return en_lResult;
}

/**************************************************************************************************/
/* Function Name: EN_PORT_RESULT_t GPIO_SetPin(EN_GPIO_PORT_t en_fPort,				 			  */
/*													 EN_GPIO_PIN_t en_fPin)                       */
/*                                                                                                */
/* Description	:	Set the Corresponding PORT pin                                                */
/*                                                                                                */
/* In Params	  :	EN_GPIO_PORT_t en_fPort,EN_GPIO_PIN_t en_fPin                         		  */
/*                                                                                                */
/* Out Params	  :	None                                              	                          */
/*                                                                                                */
/* Return Value	:	EN_PORT_RESULT_t 															  */
/**************************************************************************************************/

EN_PORT_RESULT_t GPIO_SetPin(EN_GPIO_PORT_t en_fPort, EN_GPIO_PIN_t u8_fPin)
{
	EN_PORT_RESULT_t en_lResult = PORT_SUCCESS;

	/* Select the Corresponding PORT & Set the Pin */
	p_stgPORTRegAccess[en_fPort]->OUTSET = (BIT_SET << u8_fPin);

	return en_lResult;
}

/**************************************************************************************************/
/* Function Name: EN_PORT_RESULT_t GPIO_ResetPin(EN_GPIO_PORT_t en_fPort, \                       */
/*                                                          EN_GPIO_PIN_t en_fPin)                */
/*                                                                                                */
/* Description	:	ReSet the Corresponding PORT pin                                              */
/*                                                                                                */
/* In Params	  :	EN_GPIO_PORT_t en_fPort,EN_GPIO_PIN_t en_fPin								  */
/*                                                                                                */
/* Out Params  	:	None                                            	                          */
/*                                                                                                */
/* Return Value	:	EN_PORT_RESULT_t															  */
/**************************************************************************************************/

EN_PORT_RESULT_t GPIO_ResetPin(EN_GPIO_PORT_t en_fPort, EN_GPIO_PIN_t u8_fPin)
{
	EN_PORT_RESULT_t en_lResult = PORT_SUCCESS;

	/* Select the Corresponding PORT & Reset the Pin */
	p_stgPORTRegAccess[en_fPort]->OUTCLR = (BIT_SET << u8_fPin);

	return en_lResult;
}

/**************************************************************************************************/
/* Function Name: EN_PORT_RESULT_t PORT_TooglePin(EN_GPIO_PORT_t en_fPort,\                       */
/*                                             EN_GPIO_PIN_t en_fPin)                             */
/*                                                                                                */
/* Description	:	Toggle the Corresponding PORT pin                                             */
/*                                                                                                */
/* In Params	  :	EN_GPIO_PORT_t en_fPort,EN_GPIO_PIN_t en_fPin                      			  */
/*                                                                                                */
/* Out Params	  :	None                                                                          */
/*                                                                                                */
/* Return Value	:	EN_PORT_RESULT_t											                  */
/**************************************************************************************************/

EN_PORT_RESULT_t GPIO_TogglePin(EN_GPIO_PORT_t en_fPort, EN_GPIO_PIN_t u8_fPin)
{
	EN_PORT_RESULT_t en_lResult = PORT_SUCCESS;

	/* Select the Corresponding PORT & Toggle the Pin */
	p_stgPORTRegAccess[en_fPort]->OUTTGL = (BIT_SET << u8_fPin);

	return en_lResult;
}

/**************************************************************************************************/
/* Function Name: EN_PORT_RESULT_t PORT_ToogleMode(EN_GPIO_PORT_t en_fPort,\                      */
/*                                           							  EN_GPIO_PIN_t en_fPin)  */
/*                                                                                                */
/* Description:	Switches the Corresponding PORT pin from Input to Output or vice versa            */
/*                                                                                                */
/* In Params	:	EN_GPIO_PORT_t en_fPort, EN_GPIO_PIN_t en_fPin								  */
/*                                                                                                */
/* Out Params	:	None                                                                          */
/*                                                                                                */
/* Return Value	:	EN_PORT_RESULT_t															  */
/**************************************************************************************************/

EN_PORT_RESULT_t GPIO_ToggleMode(EN_GPIO_PORT_t en_fPort, EN_GPIO_PIN_t u8_fPin)
{
	EN_PORT_RESULT_t en_lResult = PORT_SUCCESS;

	/* Toggle the PORT PIN Mode (Input to Output or vice versa) */
	p_stgPORTRegAccess[en_fPort]->DIRTGL = (BIT_SET << u8_fPin);

	return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : INT8U GPIO_ReadPin(EN_GPIO_PORT_t en_fPort,EN_GPIO_PIN_t en_fPin)            */
/*                                                                                                */
/* Description     : This function is used to read the pin                                        */
/*                                                                                                */
/* In Params       : en_fPort, en_fPin                                                            */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : INT8U                                                                        */
/**************************************************************************************************/

INT8U GPIO_ReadPin(EN_GPIO_PORT_t en_fPort,EN_GPIO_PIN_t en_fPin)
{
	INT8U u8_lLevel = 0;
	
	if(0 != (p_stgPORTRegAccess[en_fPort]->IN & (1 << en_fPin)))
	{
		u8_lLevel = 1;
	}
	else
	{
		u8_lLevel = 0;
	}
	
	return u8_lLevel;
}

/**************************************************************************************************/
/* Function Name   : INT32U GPIO_ReadBlock(EN_GPIO_PORT_t en_fPort,INT16U u16_fPins)              */
/*                                                                                                */
/* Description     : This function is used to read pins data.                                     */
/*                                                                                                */
/* In Params       : en_fPort, u16_fPins                                                          */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : INT32U                                                                       */
/**************************************************************************************************/

INT32U GPIO_ReadBlock(EN_GPIO_PORT_t en_fPort,INT32U u32_fPins)
{
    INT32U u32_lBlockdata = 0;
    
    u32_lBlockdata = p_stgPORTRegAccess[en_fPort]->IN;
    
    return u32_lBlockdata;
}

/**************************************************************************************************/
/* End of PORT.C                                                                                  */
/**************************************************************************************************/
