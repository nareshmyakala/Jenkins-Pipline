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
/* \File Name   : GCLK_Priv.h                                                                     */
/* \Author      : Kishore D	                                                                      */
/* \Version 		: v1.0                                                                            */
/* \Date        : 23/08/2018                                                                      */
/*                                                                                                */
/* @Description : GCLK Driver Frame Work                                                          */
/**************************************************************************************************/

#ifndef _GCLK_PRIV_H_
#define _GCLK_PRIV_H_

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

/* GCLK Base Address */
#define	GCLK_BASE_ADDRESS						( (INT32U)0x40001C00 )

/* Peripheral Selection */
#define GCLK_PCHCTRL_GEN_REG						( (INT32U)0x0000000F )
#define GCLK_PCHCTRL_GEN0					     ( (INT32U)0x00000000 )
#define GCLK_PCHCTRL_GEN1					     ( (INT32U)0x00000001 )
#define GCLK_PCHCTRL_GEN4		    			   	( (INT32U)0x00000004 )
#define GCLK_GENCTRL_ENABLE						( (INT32U)0x00000100 )

/* Generator Source Selection */
#define 	GCLK_GENCTRL_SRC_REG		     ( (INT32U)0x0000001F )
#define   GCLK_GENCTRL_SRC_XOSC0             ( (INT32U)0x00000000 )
#define   GCLK_GENCTRL_SRC_XOSC1	          ( (INT32U)0x00000001 )
#define   GCLK_GENCTRL_SRC_GCLKGEN1          ( (INT32U)0x00000002 )
#define   GCLK_GENCTRL_SRC_OSCULP32K         ( (INT32U)0x00000003 ) 
#define   GCLK_GENCTRL_SRC_OSC32K            ( (INT32U)0x00000004 )
#define   GCLK_GENCTRL_SRC_XOSC32K           ( (INT32U)0x00000005 )
#define   GCLK_GENCTRL_SRC_OSC16M            ( (INT32U)0x00000006 )   
#define   GCLK_GENCTRL_SRC_DFLL48M           ( (INT32U)0x00000006 ) 
#define 	GCLK_GENCTRL_SRC_DPLL			( (INT32U)0x00000008 )

#define GCLK_GENCTRL_DIVSEL				( (INT32U)0x00001000 )

/* GCLK Enable */
#define GCLK_GENCTRL_GENEN_MASK         	( (INT32U)0x00000100 )

/* CLock Generator Selection */
#define GCLK_SYNCBUSY_GENCTRL0			( (INT32U)0x00000004 )
#define GCLK_SYNCBUSY_GENCTRL1			( (INT32U)0x00000008 )
#define GCLK_SYNCBUSY_GENCTRL2			( (INT32U)0x00000010 )
#define GCLK_SYNCBUSY_GENCTRL3			( (INT32U)0x00000020 )
#define GCLK_SYNCBUSY_GENCTRL4			( (INT32U)0x00000040 )
#define GCLK_SYNCBUSY_GENCTRL5			( (INT32U)0x00000080 )
#define GCLK_SYNCBUSY_GENCTRL6			    		( (INT32U)0x00000100 )
#define GCLK_SYNCBUSY_GENCTRL7			    		( (INT32U)0x00000200 )
#define GCLK_SYNCBUSY_GENCTRL8			    		( (INT32U)0x00000400 )

/* GCLK Software Reset */
#define GCLK_CTRLA_SWRST_MASK								( (INT8U)0x01 )

/* Peripheral Config */
#define GCLK_PCHCTRL_CHEN_POS               ( 6 )

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

/* Structure to Access GCLK Registers */
typedef struct
{
	SYS_REG_BYTE    CTRLA;
	SYS_REG_BYTE    RESERVED[3];
	SYS_REG         SYNCBUSY;
	SYS_REG_BYTE    RESERVED1[24];
	SYS_REG         GENCTRL[12];
	SYS_REG_BYTE    RESERVED2[48];
	SYS_REG         PCHCTRL[48];
} ST_GCLK_REGS_t;

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

#endif

/**************************************************************************************************/
/*End of GCLK_Priv.h                   			                                                  */
/**************************************************************************************************/
