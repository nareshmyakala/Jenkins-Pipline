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
/* \File Name   : SYSTICK.C                                                                       */
/* \Author      : Kishore D                                                                       */
/* \Version     : v1.0                                                                            */
/* \Date        : 23/08/2018                                                                      */
/* @Description :                                                                                 */
/**************************************************************************************************/

#ifndef _SYSTICK_H_
#define _SYSTICK_H_

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


/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/* The Below Enum is Used to Select the Clock Source for Systick */
typedef enum
{
	SYSTICK_FSTANDBY_2 = 0,
	SYSTICK_FCPU
	
}EN_SYSTICK_CLOCK_t;

/* */
typedef enum
{
	SYSTICK_MS = 0,
	SYSTICK_US = 1,
}EN_SYSTICK_TYPE_t;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* To Enable the SYSTICK */
extern void SYSTICK_Enable(EN_SYSTICK_CLOCK_t en_fSYSTICKClock);

/* To Disable the SYSTICK */
extern void SYSTICK_Disable(void);

/* To Enable the SYSTICK Interrupt when Count is 0 */
extern void SYSTICK_EnableInterrupt(void);

/* To Disable the SYSTICK Interrupt */
extern void SYSTICK_DisableInterrupt(void);

/* To Set the Tick Count for the SYSTICK */
extern void SYSTICK_SetTickCount(EN_SYSTICK_TYPE_t, INT32U u32_fTime);

/* To Get the SYSTICK  Count */
extern INT32U SYSTICK_GetTickCount(void);

/* status check*/
extern INT8U SYSTICK_GetStatus(void);

#endif
/**************************************************************************************************/
/* End of SYSTICK.h                                                                               */
/**************************************************************************************************/
