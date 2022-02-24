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
/* \File Name   : MCLK.c                                                                          */
/* \Author      : Kishore D                                                                       */
/* \Version 		: v1.0                                                                            */
/* \Date        : 23/08/2018                                                                      */
/*                                                                                                */
/* @Description : MCLK Driver 	    		                                                          */
/**************************************************************************************************/

#ifndef MCLK_PRIV_H_
#define MCLK_PRIV_H_

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

#define	MCLK_BASE_ADDRESS				( (INT32U)0x40000800 )

#define MCLK_APBAMASK_MCLK			( (INT32U)0x00000004 )
#define MCLK_APBAMASK_OSCCTRL		( (INT32U)0x00000010 )
#define MCLK_CPUDIV_MASK				( (INT8U)0x01 )
#define MCLK_HSDIV_MASK					( (INT8U)0x01 )

#define MCLK_CPUDIV_BY_1				( (INT32U)0x01 )
#define MCLK_CPUDIV_BY_2				( (INT32U)0x02 )
#define MCLK_AHBMASK_APBA				( (INT32U)0x00000001 )
#define MCLK_APBBMASK_PORT			( (INT32U)0x00000010 )
#define MCLK_INTENSET_CKRDY			( (INT8U)0x01 )
#define MCLK_GCLK_ENABLE				( (INT32U)0x00000080)
#define MCLK_AHBMASK_NVMCTRL_OFFSET		( 6 )

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

/* Structure to Access MCLK Register */
typedef struct
{
	SYS_REG_BYTE 		CTRLA;
	SYS_REG_BYTE 		INTENCLR;
	SYS_REG_BYTE 		INTENSET;
	SYS_REG_BYTE 		INTFLAG;
	SYS_REG_BYTE 		HSDIV;
	SYS_REG_BYTE 		CPUDIV;	
	SYS_REG_BYTE 		RESERVED1[10];
	SYS_REG 		 		AHBMASK;
	SYS_REG 		 		APBAMASK;
	SYS_REG 		 		APBBMASK;
	SYS_REG 		 		APBCMASK;
	SYS_REG 		 		APBDMASK;	
} ST_MCLK_REGS_t;

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

#endif

/**************************************************************************************************/
/*End of MCLK_Priv.h                          	                                                  */
/**************************************************************************************************/
