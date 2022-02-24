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
/* \File Name   :  NVIC_Priv.h                                                                    */
/* \Author      :  Salman Ali                                                                     */
/* \Version     :  1.0                                                                            */
/* \Date        :  19/12/2015                                                                     */
/* @Description :  NVIC Framework                                                                 */
/**************************************************************************************************/

#ifndef _NVIC_PRIV_H_
#define _NVIC_PRIV_H_

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

/* NVIC Base Address */
#define NVIC_BASE_ADDR					( 0xE000E100 )

#define NVIC_REGS_OFFSET				( 0x05 )
#define NVIC_INTSET_OFFSET	   	( 0x1F )
#define NVIC_PRIORITY_BITS	    ( 6 )


/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/


/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

/* The Below Structure Definition is Used to Access the NVIC Registers */
typedef struct 
{
	SYS_REG NVIC_ISER[4];
	SYS_REG RESERVED1[28];
	SYS_REG NVIC_ICER[4];
	SYS_REG RESERVED2[28];
	SYS_REG NVIC_ISPR[4];
	SYS_REG RESERVED3[28];
	SYS_REG NVIC_ICPR[4];
	SYS_REG RESERVED4[28];
	SYS_REG RESERVED5[4];
	SYS_REG RESERVED6[60];
	SYS_REG NVIC_IPR[28];
}ST_NVIC_Regs_t;

#endif

/**************************************************************************************************/
/* End of NVIC_Priv.h                                                                             */
/**************************************************************************************************/
