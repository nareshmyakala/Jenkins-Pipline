/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2014-15, Think Embedded Pvt. Ltd. (TEPL)                     */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   :  NVIC.c                                                                         */
/* \Author      :  Salman Ali                                                                     */
/* \Version     :  1.0                                                                            */
/* \Date        :  19/12/2015                                                                     */
/* @Description :  NVIC Driver                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "NVIC.h"
#include "NVIC_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Variable To Access NVIC Register */
ST_NVIC_Regs_t * p_stgNVICRegs = (ST_NVIC_Regs_t *)NVIC_BASE_ADDR;

/**************************************************************************************************/
/* Function Name   :  void NVIC_EnableInterrupt(INT8U en_fIrqId)                                  */
/*                                                                                                */
/* Description     :  This Function is Used to Enable the Interrupt                               */
/*                                                                                                */
/* In Params       :  INT8U Type Refer "Interrupt numbers"                                        */
/*                                                                                                */
/* Out Params      :  None                                                                        */
/*                                                                                                */
/* Return Value    :  void                                                                        */
/**************************************************************************************************/

void NVIC_EnableInterrupt(EN_NVIC_IRQ_t en_fIrqId)
{
	/* Enable Interrupt by setting corresponding bit in NVIC_ISER Register */
	p_stgNVICRegs->NVIC_ISER[en_fIrqId >> NVIC_REGS_OFFSET] |= (1 << \
	                                                     ((en_fIrqId) & NVIC_INTSET_OFFSET));
}

/**************************************************************************************************/
/* Function Name   :  void NVIC_DisableInterrupt(INT8U en_fIrqId)                                 */
/*                                                                                                */
/* Description     :  This Function is Used To Disable the Interrupt                              */
/*                                                                                                */
/* In Params       :  INT8U Type Refer "Interrupt numbers"                                        */
/*                                                                                                */
/* Out Params      :  None                                                                        */
/*                                                                                                */
/* Return Value    :  void                                                                        */
/**************************************************************************************************/

void NVIC_DisableInterrupt(EN_NVIC_IRQ_t en_fIrqId)
{
	/* Disable Interrupt by setting the Corresponding bit in NVIC_ICER Register */
	p_stgNVICRegs->NVIC_ICER[(en_fIrqId) >> NVIC_REGS_OFFSET] = (1 << \
	                                                        (en_fIrqId) & NVIC_INTSET_OFFSET);
}

/**************************************************************************************************/
/* Function Name   :   void NVIC_SetPriorityTE(INT8U en_fIrqId, INT8U u8_fPriority)               */
/*                                                                                                */
/* Description     :   This Function is Used to Set the Priority for the Interupt                 */
/*                                                                                                */
/* In Params       :   INT8U Type Refer "Interrupt numbers" and INT8U Type for Priority(0-63)     */
/*                                                                                                */
/* Out Params      :   None                                                                       */
/*                                                                                                */
/* Return Value    :   void                                                                       */
/**************************************************************************************************/

void NVIC_SetPriorityTE(EN_NVIC_IRQ_t en_fIrqId, INT8U u8_fPriority)
{
	/* set Priority for the General Interrupts */
	p_stgNVICRegs->NVIC_IPR[en_fIrqId/4] |= (u8_fPriority << (((en_fIrqId % \
									    				NVIC_PRIORITY_BITS) * 8) + 4));   
	
}

/**************************************************************************************************/
/* Function Name   :  INT8U NVIC_GetPriorityTE(INT8U u8_fPeripheralID)                            */
/*                                                                                                */
/* Description     :  This Function is Used to Get the Priority of an Interrupt                   */
/*                                                                                                */
/* In Params       :  INT8U Type Refer "Interrupt numbers"                                        */
/*                                                                                                */
/* Out Params      :  None                                                                        */
/*                                                                                                */
/* Return Value    :  INT8U Type                                                                  */
/**************************************************************************************************/

INT8U NVIC_GetPriorityTE(EN_NVIC_IRQ_t u8_fPeripheralID)
{
	/* Variable for Collect the Priority Register Data */
	INT32U u32_lPR;
	
	/* Variable for Calculating the Priorty of the Interrupt */
	INT8U  u8_lPriority;
	
	/* Read the Priority Register */
	u32_lPR = p_stgNVICRegs->NVIC_IPR[u8_fPeripheralID/4];
	
	/* Calculate the priority of the Interrupt */
	u8_lPriority = (INT8U)(u32_lPR >> (((u8_fPeripheralID % NVIC_PRIORITY_BITS) * 8) + 4));
	
	/* Return the priority */
	return u8_lPriority;
}

/**************************************************************************************************/
/* Function Name   :  void NVIC_PendInterrupt(INT8U en_fIrqId)                                    */
/*                                                                                                */
/* Description     :  This Function Defines The Pend Interrupt                                    */
/*                                                                                                */
/* In Params       :  INT8U Type Refer "Interrupt numbers"                                        */
/*                                                                                                */
/* Out Params      :  None                                                                        */
/*                                                                                                */
/* Return Value    :  void                                                                        */
/**************************************************************************************************/

void NVIC_SetPendInterrupt(EN_NVIC_IRQ_t en_fIrqId)
{
	/* Set Interrupt pending */
	p_stgNVICRegs->NVIC_IPR[en_fIrqId >> NVIC_REGS_OFFSET] |= \
							 				(1 << ((en_fIrqId) & NVIC_INTSET_OFFSET));
}

/**************************************************************************************************/
/* Function Name   :   void NVIC_ClearPendInterrupt(INT8U en_fIrqId)                              */
/*                                                                                                */
/* Description     :   This Function is Used to Clear the Pend Interrupt                          */
/*                                                                                                */
/* In Params       :   INT8U Type Refer "Interrupt numbers"                                       */
/*                                                                                                */
/* Out Params      :   None                                                                       */
/*                                                                                                */
/* Return Value    :   void                                                                       */
/**************************************************************************************************/

void NVIC_ClearPendInterrupt(EN_NVIC_IRQ_t en_fIrqId) 
{
	/* Clear pending Interrupt*/
	p_stgNVICRegs->NVIC_ICER[(en_fIrqId) >> NVIC_REGS_OFFSET] |= (1 << \
	                                                (en_fIrqId) & NVIC_INTSET_OFFSET);
}

/**************************************************************************************************/
/* End of NVIC.c                                                                                  */
/**************************************************************************************************/
