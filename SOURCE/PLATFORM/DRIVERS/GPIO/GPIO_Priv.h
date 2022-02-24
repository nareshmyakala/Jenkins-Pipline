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
/* \File Name   : PORT.c                                                                          */
/* \Author      : Kishore D                                                                       */
/* \Version     : v1.1                                                                            */
/* \Date        : 23/08/2018  					                                                  */
/* @Description : GPIO Driver 					                                                  */
/**************************************************************************************************/

#ifndef _GPIO_PRIV_H_
#define _GPIO_PRIV_H_

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

/* PORT Base Address */
#define PORTA_BASE						( 0x41008000 )
#define PORTB_BASE					 	( 0x41008080 )

#define BIT_SET							( 1UL )
#define BIT_CLEAR						( 1UL )

#define GPIO_PINCFG_PMUXEVEN_MSK        ( 0x0F )
#define GPIO_PINCFG_PMUXODD_MSK         ( 0xF0 )
#define GPIO_PINCFG_PMUXEVEN_POS        ( 0 )
#define GPIO_PINCFG_PMUXODD_POS         ( 4 )
#define GPIO_PINCFG_PULLEN_POS          ( 2 )
#define GPIO_PINCFG_DRVSTR_POS          ( 6 )
#define GPIO_PINCFG_INEN_POS            ( 1 )
#define GPIO_PINCFG_PMUXEN_POS			( 0 )

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

/* PORT REGISTER STRUCTURE */
typedef struct
{
	SYS_REG			DIR;            		/* Offset: 0x00 (R/W 32) Data Direction */
	SYS_REG			DIRCLR;					/* Offset: 0x04 (R/W 32) Data Direction Clear */
	SYS_REG			DIRSET;					/* Offset: 0x08 (R/W 32) Data Direction Set */
	SYS_REG			DIRTGL;         		/* Offset: 0x0C (R/W 32) Data Direction Toggle */
	SYS_REG       	OUT;					/* Offset: 0x10 (R/W 32) Data Output Value */
	SYS_REG			OUTCLR;					/* Offset: 0x14 (R/W 32) Data Output Value Clear */
	SYS_REG			OUTSET;					/* Offset: 0x18 (R/W 32) Data Output Value Set */
	SYS_REG			OUTTGL;					/* Offset: 0x1C (R/W 32) Data Output Value Toggle */
	SYS_REG       	IN;						/* Offset: 0x20 (R/  32) Data Input Value */
	SYS_REG			CTRL;					/* Offset: 0x24 (R/W 32) Control */
	SYS_REG			WRCONFIG;				/* Offset: 0x28 ( /W 32) Write Configuration */
	SYS_REG			EVCTRL;					/* Offset: 0x2C (R/W 32) Event Input Control */
	SYS_REG_BYTE	PMUX[16];				/* Offset: 0x30 (R/W  8) Peripheral Multiplexing n */
	SYS_REG_BYTE	PINCFG[32];				/* Offset: 0x40 (R/W  8) Pin Configuration n */	 
}ST_PORT_REGS_t;

#endif 
/**************************************************************************************************/
/* End of PORT_Priv.h                                                                             */
/**************************************************************************************************/
