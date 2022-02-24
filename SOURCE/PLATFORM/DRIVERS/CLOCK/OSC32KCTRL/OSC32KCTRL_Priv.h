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
/* \File Name   : OSC32KCTRL_Priv.h                                                               */
/* \Author      : Salman Ali                                                                      */
/* \Version 	: 1.1                                                                             */
/* \Date        : 20/06/2016                                                                      */
/*                                                                                                */
/* @Description : OSC32KCTRL Driver Frame Work                                                    */
/**************************************************************************************************/

#ifndef _OSC32KCTRL_PRIV_H_
#define _OSC32KCTRL_PRIV_H_

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

#define OSC32KCTRL_BASE_ADDRESS	               ( (INT32U)0x40001400 )

#define OSCCTRL_INTFLAG_DFLLRDY_FLAG			( (INT32U)0x00000100 )
#define OSC32KCTRL_XOSC32K_ENABLE	               ( (INT16U)0x0002 )
#define OSC32KCTRL_XOSC32K_XTALEN	               ( (INT16U)0x0004 )
#define OSC32KCTRL_XOSC32K_EN32K	               ( (INT16U)0x0008 )
#define OSC32KCTRL_XOSC32K_EN1K		          ( (INT16U)0x0010 )
#define OSC32KCTRL_XOSC32K_ONDEMAND	          ( (INT16U)0x0080 )
#define OSC32KCTRL_XOSC32K_STDBY	               ( (INT16U)0x0040 )
#define OSCCTRL_DFLLSYNC						( (INT8U)0x02 )

#define OSC32KCTRL_INTFLAG_XOSC32KRDY_MASK        ( (INT32U)0x00000001 )

#define OSC32KCTRL_XOSC32K_STARTUP_POS            ( 8 )

#define OSC32KCTRL_STATUS_XOSC32KRDY	          ( (INT16U)0x0001 )

#define OSC32KCTRL_OSC32K_EN1K                    ( 0x00000008 )
#define OSC32KCTRL_OSC32K_EN32K                   ( 0x00000004 )
#define OSC32KCTRL_OSC32K_ENABLE                  ( 0x00000002 )
#define OSC32KCTRL_OSC32K_RUNSTDBY                ( 0x00000040 )
#define OSC32KCTRL_OSC32K_ONDEMAND                ( 0x00000080 )

#define OSC32KCTRL_STATUS_OSC32KRDY               ( 0x00000002 )

/* Structure to Access OSC32KCTRL Registers */
typedef struct
{
	SYS_REG         INTENCLR;
	SYS_REG         INTENSET;
	SYS_REG         INTFLAG;
	SYS_REG         STATUS;
	SYS_REG_BYTE    RTCCTRL;
	SYS_REG_BYTE	 RESERVED[3];
	SYS_REG_HWORD 	 XOSC32K;
	SYS_REG_BYTE	 CFDCTRL;
	SYS_REG_BYTE	 EVCTRL;
	SYS_REG         OSC32K;
	SYS_REG_BYTE	 RESERVED1[4];
	SYS_REG         OSCULP32K;
	
} ST_OSC32KCTRL_REGS_t;

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

#endif

/**************************************************************************************************/
/*End of OSC32KCTRL_Priv.h                      			                                      */
/**************************************************************************************************/
