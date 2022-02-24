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
/*  File Name   : IGN_OFF.c                                                                       */
/*  Author      : NAGANJALI.K                                                                     */
/*  Version 	: v1.0                                                                            */
/*  Date        : 24-01-2022                                                                      */
/*                                                                                                */
/* @Description : IGN_OFF Driver Frame work                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "IGN_OFF.h"
#include "IGN_OFF_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* Function Name   :     void IGN_OFF_Init(void)                                                  */
/*                                                                                                */
/* Description     :     Ignition Off sate                                                        */
/*                                                                                                */
/* In Params       :     void                                                                     */
/*                                                                                                */
/* Out Params      :     void                                                                     */
/*                                                                                                */
/* Return Value    :     None                                                                     */
/**************************************************************************************************/

void IGN_OFF_Init(void)
{
    /* No Action */  
}

/**************************************************************************************************/
/* Function Name   :   void IGN_OFF_Handler(EN_STATE_LIST_t *pen_fState)                          */
/*                                                                                                */
/* Description     :       Ignition Off State Handler                                             */
/*                                                                                                */
/* In Params       :       None                                                                   */
/*                                                                                                */
/* Out Params      :       pen_fState                                                             */
/*                                                                                                */
/* Return Value    :       None                                                                   */
/**************************************************************************************************/

void IGN_OFF_Handler(EN_STATE_LIST_t *pen_fState)
{
    /* Switch From IGN_OFF TO Error State */
    *pen_fState = MSG4_ERROR;
}

/**************************************************************************************************/
/* Function Name   :    void IGN_OFF_Exit(void)                                                   */
/*                                                                                                */
/* Description     :    Ignition off exit Handler                                                 */
/*                                                                                                */
/* In Params       :     void                                                                     */
/*                                                                                                */
/* Out Params      :     void                                                                     */
/*                                                                                                */
/* Return Value    :     None                                                                     */
/**************************************************************************************************/

void IGN_OFF_Exit(void)
{
    /* No Action */
}

/**************************************************************************************************/
/* End of  IGN_OFF.c                                                                              */
/**************************************************************************************************/
