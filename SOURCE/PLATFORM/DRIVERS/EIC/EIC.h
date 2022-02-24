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
/* \File Name   : EIC.h                                                                           */
/* \Author      : Ravi Ranjan Kumar                                                               */
/* \Version 	: 1.0                                                                             */
/* \Date        : 07/09/2018                                                                      */
/*                                                                                                */
/* @Description : EIC Framework   		                                                          */
/**************************************************************************************************/

#ifndef _EIC_H_
#define _EIC_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

typedef enum
{
		EIC_CONFIG_SENSEx_NONE  = 0x0ul,    /* (EIC_CONFIG) No detection */
		EIC_CONFIG_SENSEx_RISE,             /* (EIC_CONFIG) Rising edge detection */
		EIC_CONFIG_SENSEx_FALL,             /* (EIC_CONFIG) Falling edge detection */
		EIC_CONFIG_SENSEx_BOTH,             /* (EIC_CONFIG) Both edges detection */
		EIC_CONFIG_SENSEx_HIGH,             /* (EIC_CONFIG) High level detection */
		EIC_CONFIG_SENSEx_LOW               /* (EIC_CONFIG) Low level detection */
}EN_EXTNL_SENSE_t;

/* Stucture to configure EIC */
typedef struct
{
	INT32U              u32_mExtnlIntNo;
	EN_EXTNL_SENSE_t    en_mInputSense;
	void                (* fp_UserHandler)(void);	
}ST_EIC_PARAMS_t;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Should be used if using EIC alone without Event System */
extern void EIC_Init(ST_EIC_PARAMS_t *p_stfEICParams);

/* Should be used if using EIC along with Event Systems */
extern void EIC_ExtIntWithEventsInit(INT32U u32_fExtnlIntNo, EN_EXTNL_SENSE_t en_fInputSense);

/**************************************************************************************************/
/* Helper Functions Section                                                                       */
/**************************************************************************************************/

/* Function to configure External Interrupt */
extern void EIC_ExtIntConfig(INT32U u32_fExtnlIntNo,INT32U u32_fInputSense);

/* Function to Perform Software Reset */
extern void EIC_SoftReset(void);

/* Function to Enable EIC */
extern void EIC_Enable(void);

/* Function to Disable EIC */
extern void EIC_Disable(void);

/* Function to Enable Interrupt */ 
extern void EIC_InterruptEnable(INT32U u32_fExtnlIntNo);

/* Function to Disable Interrupt */
extern void EIC_InterruptDisable(INT32U u32_fExtnlIntNo);

#endif

/**************************************************************************************************/
/* End of EIC.h                                                                                   */
/**************************************************************************************************/
