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
/* \File Name   : WDT_Priv.h                                                                      */
/* \Author      : Salman Ali                                                                      */
/* \Version 	: 1.1                                                                             */
/* \Date        : 30\06\2016                                                                      */
/*                                                                                                */
/* @Description : WatchDog Timer Driver                                                           */
/**************************************************************************************************/

#ifndef _WDT_PRIV_H_
#define _WDT_PRIV_H_

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

#define WDT_BASE_ADDRESS					( 0x40002000 )


#define WDT_SYNCBUSY_ENABLE_MASK			(0x01 << 1)
#define WDT_SYNCBUSY_WEN_MASK				(0x01 << 2)
#define WDT_SYNCBUSY_ALWAYSON_MASK			(0x01 << 3)
#define WDT_CTRLA_ENABLE_MASK				(0x01 << 1)

#define WDT_CTRLA_ALWAYSON_OFFSET     		( 7 )         
#define WDT_CTRLA_ALWAYSON_MSK         		(0x01 << WDT_CTRLA_ALWAYSON_OFFSET)

#define WDT_CTRLA_ENABLE_OFFSET				( 1 )
#define WDT_CTRLA_ENABLE_MSK				(1 << WDT_CTRLA_ENABLE_OFFSET)

#define WDT_CONFIG_WINDOW_OFFSET			( 4 )
#define WDT_CONFIG_WINDOW_MSK				(0x0F <<  WDT_CONFIG_WINDOW_OFFSET)

#define WDT_CTRLA_WEN_MSK					(0x01 << 2)

#define WDT_CONFIG_PER_OFFSET				( 0 )
#define WDT_CONFIG_PER_MSK					(0x0F << WDT_CONFIG_PER_OFFSET)

#define WDT_CLEAR_RESET_VALUE        		( 0x00 )       

#define WDT_CLEAR_CLEAR_OFFSET		        ( 0 )
#define WDT_CLEAR_CLEAR_MSK         		(0xFFul << WDT_CLEAR_CLEAR_OFFSET)
#define WDT_CLEAR_CLEAR_KEY_VAL         	( 0xA5 )
#define WDT_CLEAR_CLEAR_KEY         		(WDT_CLEAR_CLEAR_KEY_VAL << WDT_CLEAR_CLEAR_OFFSET)
#define WDT_CLEAR_MASK              		( 0xFF )
#define WDT_INTFLAG_EW_MSK					( 0x01 )

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

typedef struct 
{
  SYS_REG_BYTE           CTRLA;       /* Offset: 0x0 (R/W  8) Control */
  SYS_REG_BYTE           CONFIG;      /* Offset: 0x1 (R/W  8) Configuration */
  SYS_REG_BYTE           EWCTRL;      /* Offset: 0x2 (R/W  8) Early Warning Interrupt Control */
  SYS_REG_BYTE           Reserved1[0x1];
  SYS_REG_BYTE           INTENCLR;    /* Offset: 0x4 (R/W  8) Interrupt Enable Clear */
  SYS_REG_BYTE           INTENSET;    /* Offset: 0x5 (R/W  8) Interrupt Enable Set */
  SYS_REG_BYTE           INTFLAG;     /* Offset: 0x6 (R/W  8) Interrupt Flag Status and Clear */
  SYS_REG_BYTE           Reserved2[0x1];
  SYS_REG                SYNCBUSY;    /* Offset: 0x8 (R/  32) Synchronization Busy */
  SYS_REG_BYTE           CLEAR;       /* Offset: 0xC ( /W  8) Clear */
}ST_WDT_SYS_REGS_t;

#endif

/**************************************************************************************************/
/*End of WDT_Priv.h                      			                                              */
/**************************************************************************************************/
