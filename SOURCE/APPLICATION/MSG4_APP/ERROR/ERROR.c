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
/*  File Name   : ERROR.c                                                                         */
/*  Author      : NAGANJALI.K                                                                     */
/*  Version 	: v1.0                                                                            */
/*  Date        : 24-01-2022                                                                      */
/*                                                                                                */
/* @Description : ERROR Driver Frame Work                                                         */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "ERROR.h"
#include "ERROR_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* Function Name   :  void Error_Init(void)                                                       */
/*                                                                                                */
/* Description     :   Error State Initialization                                                 */
/*                                                                                                */
/* In Params       :       void                                                                   */
/*                                                                                                */
/* Out Params      :       void                                                                   */
/*                                                                                                */
/* Return Value    :       None                                                                   */
/**************************************************************************************************/

void Error_Init(void)
{
    /* No Action */
}

/**************************************************************************************************/
/* Function Name   :       void Error_Handler(EN_STATE_LIST_t *pen_fState)                        */
/*                                                                                                */
/* Description     :       Error Handler State                                                    */
/*                                                                                                */
/* In Params       :         None                                                                 */
/*                                                                                                */
/* Out Params      :        pen_fState                                                            */
/*                                                                                                */
/* Return Value    :        None                                                                  */
/**************************************************************************************************/

void Error_Handler(EN_STATE_LIST_t *pen_fState)
{
    /* Switch From BOOTUP TO SCAN State */
    *pen_fState = MSG4_IDLE;
}

/**************************************************************************************************/
/* Function Name   :      void Error_Exit(void)                                                   */
/*                                                                                                */
/* Description     :      Error Exit state                                                        */
/*                                                                                                */
/* In Params       :       void                                                                   */
/*                                                                                                */
/* Out Params      :      void                                                                    */
/*                                                                                                */
/* Return Value    :     None                                                                     */
/**************************************************************************************************/

void Error_Exit(void)
{
    /* No Action */
}

/**************************************************************************************************/
/* End of  ERROR.c                                                                                */
/**************************************************************************************************/
