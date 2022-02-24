/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2018, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/*  File Name   : ERROR.h                                                                         */
/*  Author      : NAGANJALI.K                                                                     */
/*  Version 	: v1.0                                                                            */
/*  Date        : 24-01-2022                                                                      */
/*                                                                                                */
/* @Description : ERROR Driver Frame Work                                                         */
/**************************************************************************************************/

#ifndef _ERROR_H_
#define _ERROR_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "MSG4_App.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

extern void Error_Init(void);
extern void Error_Handler(EN_STATE_LIST_t *pen_fState);
extern void Error_Exit(void);

#endif

/**************************************************************************************************/
/* End of  ERROR.h                                                                                */
/**************************************************************************************************/
