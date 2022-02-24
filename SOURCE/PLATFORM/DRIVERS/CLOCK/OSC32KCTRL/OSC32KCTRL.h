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
/* \File Name   : OSC32KCTRL.h                                                                    */
/* \Author      : Salman Ali                                                                      */
/* \Version 	: 1.1                                                                             */
/* \Date        :20/06/2016                                                                       */
/*                                                                                                */
/* @Description: OSC32KCTRL Driver Frame Work                                                     */
/**************************************************************************************************/

#ifndef OSC32KCTRL_H_
#define OSC32KCTRL_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

/* Enum for Result Purpose */
typedef enum
{
	OSC32KCTRL_ERROR = 0x00,
	OSC32KCTRL_SUCCESS
	
} EN_OSC32KCTRL_RESULT_t;

/**************************************************************************************************/
/* Export Global Variable Section                                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function to select External XOSC32K as Source */
extern 	void OSC32KCTRL_XOSC32KInit(void);

extern void OSC32KCTRL_XOSC32KConfig(void);

extern void OSC32KCTRL_1KHZClockEnable(void);

extern void OSC32KCTRL_OSC32KInit(void);

#endif

/**************************************************************************************************/
/* End of OSC32KCTRL.h                                                                            */
/**************************************************************************************************/