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
/* \File Name   : WDT.h                                                                           */
/* \Author      : Salman Ali                                                                      */
/* \Version 	: 1.1                                                                             */
/* \Date        : 30\06\2016                                                                      */
/*                                                                                                */
/* @Description : WatchDog Timer Driver                                                           */
/**************************************************************************************************/

#ifndef _WDT_H_
#define _WDT_H_

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

/* Enum to select WDT Mode */
typedef enum
{
	WDT_ERROR = 0,
	WDT_SUCCESS
}EN_WDT_STATUS_t;

/* Enum to select WDT Mode */
typedef enum
{
	EN_WDT_NORMAL_MODE = 0,
	EN_WDT_WINDOW_MODE
}EN_WDT_MODE_SEL_t;

/* Enum to select Time Out Period for WDT */
typedef enum
{
	WDT_CLK_8CYCLE 		= 8,  /* (WDT_CONFIG) 8 clock cycles */
	WDT_CLK_16CYCLE		= 16,         /* (WDT_CONFIG) 16 clock cycles */
	WDT_CLK_32CYCLE		= 32,         /* (WDT_CONFIG) 32 clock cycles */
	WDT_CLK_64CYCLE		= 64, 		 /* (WDT_CONFIG) 64 clock cycles */
	WDT_CLK_128CYCLE	= 128,  		 /* (WDT_CONFIG) 128 clock cycles */
	WDT_CLK_256CYCLE	= 256,  		 /* (WDT_CONFIG) 256 clock cycles */
	WDT_CLK_512CYCLE	= 512,  		 /* (WDT_CONFIG) 512 clock cycles */
	WDT_CLK_1024CYCLE	= 1024, 		 /* (WDT_CONFIG) 1024 clock cycles */
	WDT_CLK_2048CYCLE	= 2048,  	 /* (WDT_CONFIG) 2048 clock cycles */
	WDT_CLK_4096CYCLE	= 4096,  	 /* (WDT_CONFIG) 4096 clock cycles */
	WDT_CLK_8192CYCLE	= 8192, 		 /* (WDT_CONFIG) 8192 clock cycles */
	WDT_CLK_16384CYCLE	= 16384    	 /* (WDT_CONFIG) 16384 clock cycles */
}EN_WDT_CLK_CYCLE_t;

/* Enum to Select Early Warning Period for WDT */
typedef enum
{
	WDT_PERIOD_8CYCLE		= 0x00,  /* (WDT_CONFIG) 8 clock cycles */
	WDT_PERIOD_16CYCLE,         /* (WDT_CONFIG) 16 clock cycles */
	WDT_PERIOD_32CYCLE,         /* (WDT_CONFIG) 32 clock cycles */
	WDT_PERIOD_64CYCLE, 		  /* (WDT_CONFIG) 64 clock cycles */
	WDT_PERIOD_128CYCLE,        /* (WDT_CONFIG) 128 clock cycles */
	WDT_PERIOD_256CYCLE,  	  /* (WDT_CONFIG) 256 clock cycles */
	WDT_PERIOD_512CYCLE,  	  /* (WDT_CONFIG) 512 clock cycles */
	WDT_PERIOD_1024CYCLE, 	  /* (WDT_CONFIG) 1024 clock cycles */
	WDT_PERIOD_2048CYCLE,  	  /* (WDT_CONFIG) 2048 clock cycles */
	WDT_PERIOD_4096CYCLE,  	  /* (WDT_CONFIG) 4096 clock cycles */
	WDT_PERIOD_8192CYCLE, 	  /* (WDT_CONFIG) 8192 clock cycles */
	WDT_PERIOD_16384CYCLE,    	  /* (WDT_CONFIG) 16384 clock cycles */
}EN_WDT_PERIOD_CYCLE_t;

/* Enum to Select WDT Always ON/OFF */
typedef enum
{
	EN_WDT_ALWAYS_ON_DIS = 0,
	EN_WDT_ALWAYS_ON_ENA
}EN_WDT_ALWAYS_ON_SEL_t;

/* Early Warning Interrupt Select */
typedef enum
{
	EN_WDT_EARLY_WARNING_INT_DIS = 0,
	EN_WDT_EARLY_WARNING_INT_ENA
}EN_WDT_EWI_SEL_t;

/* Structure for WDT Init */
typedef struct
{
	EN_WDT_MODE_SEL_t 			   en_mModeSel;
	INT32U 						   u32_mClkRate;
	INT32U				      	   u32_mTimeOutPeriod;
	EN_WDT_ALWAYS_ON_SEL_t         en_mAlwaysOnSel;
}ST_WDT_INIT_PARAMS_t;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function to Initialize the WDT */
extern EN_WDT_STATUS_t WDT_Init(ST_WDT_INIT_PARAMS_t *p_stfWDTInitParams);

/* Function to Clear the WDT TimeOut */
extern void WDT_ClearWDT(void);

extern void WDT_Enable(void);

extern void WDT_WaitForSync(INT32U u32_fSyncMask);

extern INT8U WDT_CheckAlwaysOn(void);

extern INT8U WDT_CheckEnable(void);

extern void WDT_ConfigWindow(INT8U u8_lWindowVal);

extern void WDT_WritePeriod(INT8U u8_lPeriod);

extern EN_WDT_STATUS_t WDT_SetTimeoutPriod(INT32U u32_fTimeout, INT32U u32_fClkRate);

#endif

/**************************************************************************************************/
/* End of WDT.h                                                                                   */
/**************************************************************************************************/
