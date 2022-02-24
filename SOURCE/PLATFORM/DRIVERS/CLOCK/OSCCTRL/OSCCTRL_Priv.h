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
/* \File Name   : OSCCTRL_Priv.h                                                                  */
/* \Author      : Kishore D                                                                       */
/* \Version 		: V1.0                                                                            */
/* \Date        : 23/08/2018                                                                      */
/*                                                                                                */
/* @Description : OSCCTRL Driver Frame Work                                                       */
/**************************************************************************************************/

#ifndef OSCCTRL_PRIV_H_
#define OSCCTRL_PRIV_H_

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

/* Base Address for Oscilattor Controller */
#define OSCCTRL_BASE_ADDRESS					     ( 0x40001000 )

/* XOSC & Crystal Connection Enable */
#define OSCCTRL_XOSC_ENABLE						( (INT32U)0x00000002 )
#define OSCCTRL_XOSC_XTALEN						( (INT32U)0x00000004 )

/* Auto Loop Enable */
#define OSCCTRL_XOSC_AUTO_LOOP				     ( (INT32U)0x00008000 )
#define OSCCTRL_XOSC_STARTUP					     ( (INT32U)0x00500000 )

/* Frequency Selection */
#define OSCCTRL_XOSC_FREQ_8MHZ_IMUL		          ( (INT32U)0x00001800 )
#define OSCCTRL_XOSC_FREQ_8MHZ_IPTAT	               ( (INT32U)0x00000400 )
#define OSCCTRL_XOSC_FREQ_16MHZ_IMUL	               ( (INT32U)0x00002000 )
#define OSCCTRL_XOSC_FREQ_16MHZ_IPTAT	               ( (INT32U)0x00000600 )
#define OSCCTRL_XOSC_FREQ_24MHZ_IMUL	               ( (INT32U)0x00002800 )
#define OSCCTRL_XOSC_FREQ_24MHZ_IPTAT	               ( (INT32U)0x00000600 )
#define OSCCTRL_XOSC_FREQ_48MHZ_IMUL	               ( (INT32U)0x00003000 )
#define OSCCTRL_XOSC_FREQ_48MHZ_IPTAT	               ( (INT32U)0x00000600 )

/* Disable XOSC OnDemand & RunstdBy ( Always Clock Run )*/
#define OSCCTRL_XOSC_ONDEMAND					     ( (INT32U)0x00000080 )
#define OSCCTRL_XOSC_RUNSTDBY					     ( (INT32U)0x00000040 )

/* Status Check */
#define OSCCTRL_XOSCRDY0							( (INT32U)0x00000001 )
#define OSCCTRL_XOSCRDY1							( (INT32U)0x00000002 )
#define OSCCTRL_XOSCFAIL1						( (INT32U)0x00000008 )

/* DPLL Configuration */
#define OSCCTRL_XOSC_CLEAR_REG				     ( (INT8U)0xFF )
#define OSCCTRL_XOSC_WAKEUP_CLOCK			          ( (INT32U)0x00000010 )
#define OSCCTRL_DPLL_ENABLE						( (INT8U)0x02 )
#define OSCCTRL_DPLL_STATUS						( (INT32U)0x00000006 )

#define OSCCTRL_DPLL_REFCLK_XSCO1			          ( 3 )
#define OSCCTRL_DPLL_RESFCLK_POS			          ( 5 )

/* Disable DPLL OnDemand & RunstdBy ( Always Clock Run )*/
#define OSCCTRL_DFLLCTRL_RUNSTDBY_MASK  		     ( (INT8U)0x40 )
#define OSCCTRL_DFLLCTRL_ONDEMAND_MASK  		     ( (INT8U)0x80 )

/* DFLL Enable */
#define OSCCTRL_DFLL48M_ENABLE					( (INT8U)0x02 )

/* Register Structure for Oscilattor Controller */
typedef struct
{
	SYS_REG_BYTE        EVCTRL;
	SYS_REG_BYTE        RESERVED0[3];
	SYS_REG		    	INTENCLR;
	SYS_REG             INTENSET;
	SYS_REG             INTFLAG;
	SYS_REG             STATUS;
	SYS_REG             XOSCCTRL0;
	SYS_REG             XOSCCTRL1;
	SYS_REG_BYTE	     DFLLCTRLA;
	SYS_REG_BYTE        RESERVED1[3];
	SYS_REG_BYTE	     DFLLCTRLB;
	SYS_REG_BYTE        RESERVED2[3];
	SYS_REG             DFLLVAL;
	SYS_REG             DFLLMUL;
	SYS_REG_BYTE	     DFLLSYNC;
	SYS_REG_BYTE	     RESERVED3[3];
	SYS_REG_BYTE	    	DPLL0CTRLA;
	SYS_REG_BYTE	    	RESERVED4[3];
	SYS_REG             DPLL0RATIO;
	SYS_REG             DPLL0CTRLB;
	SYS_REG             DPLL0SYNCBUSY;
	SYS_REG             DPLL0STATUS;
	SYS_REG_BYTE	    	DPLL1CTRLA;
	SYS_REG_BYTE        RESERVED5[3];
	SYS_REG             DPLL1RATIO;
	SYS_REG             DPLL1CTRLB;
	SYS_REG             DPLL1SYNCBUSY;
	SYS_REG             DPLL1STATUS;		
} ST_OSCCTRL_BASE_REGS_t;

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

#endif

/**************************************************************************************************/
/*End of OSCCTRL_Priv.h     			                 			                                          */
/**************************************************************************************************/
