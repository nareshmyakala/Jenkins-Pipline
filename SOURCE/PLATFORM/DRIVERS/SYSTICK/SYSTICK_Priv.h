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

#ifndef _SYSTICK_PRIV_H_
#define _SYSTICK_PRIV_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

/**************************************************************************************************/
/* Private Global Definitions Section                                                             */
/**************************************************************************************************/

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

#define SYSTICK_BASE_ADDR				(  0xE000E010 )

/* SYSTICK Control and Status Register Mask */
#define PPB_SYST_CSR_ENABLE_MASK		( 0x00000001 )
#define PPB_SYST_CSR_TICKINT_MASK		( 0x00000002 )
#define PPB_SYST_CSR_CLKSOURCE_MASK		( 0x00000004 )
#define PPB_SYST_CSR_COUNTFLAG_MASK		( 0x00010000 )

#define PPB_SYST_CALIB_NOREF_MASK		( 0x80000000 )

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

/* The Below Structure Defination is Used to Access the Systick Registers */
typedef struct
{
	SYS_REG SYST_CSR;
	SYS_REG SYST_RVR;
	SYS_REG SYST_CVR; 
	SYS_REG SYST_CALIB;
	
}ST_SYSTICK_Regs_t;

#endif

/**************************************************************************************************/
/* End of SYSTICK_Priv.h                                                                          */
/**************************************************************************************************/
