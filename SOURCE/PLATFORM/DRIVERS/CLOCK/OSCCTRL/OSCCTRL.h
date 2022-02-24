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
/* \File Name   : OSCCTRL.h                                                                       */
/* \Author      : Kishore D                                                                       */
/* \Version 		: v1.0                                                                            */
/* \Date        : 23/08/2018                                                                      */
/*                                                                                                */
/* @Description : OSCCTRL Driver Frame Work                                                       */
/**************************************************************************************************/

#ifndef _OSCCTRL_H_
#define _OSCCTRL_H_

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
	OSCCTRL_ERROR = 0x00,
	OSCCTRL_SUCCESS
} EN_OSCCTRL_RESULT_t;

/* Enum for Status Purpose */
typedef enum
{
	OSCCTRL_DISABLE = 0x00,
	OSCCTRL_ENABLE
} EN_OSCCTRL_STATUS_t;

/* Crystall Oscillatior Freq */
typedef enum
{
	FREQ_8MHZ = 0,
	FREQ_8MHZ_16MHZ,
	FREQ_16MHZ_24MHZ,
	FREQ_24MHZ_48MHZ,
}EN_OSCTRL_XOSC_FREQ;

/**************************************************************************************************/
/* Export Global Variable Section                                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function to configure the OSC Clock */
extern EN_OSCCTRL_RESULT_t XOSCClockConfig(EN_OSCTRL_XOSC_FREQ );

/* */
extern void XOSCDpllCOnfig(INT32U u32_fFrequency);

#endif

/**************************************************************************************************/
/* End of OSCCTRL.h                                                                               */
/**************************************************************************************************/
