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
/*  File Name   : MODEM_IF.c                                                                      */
/*  Author      : NagaPrasad.V                                                                    */
/*  Version 	: v2.1.0                                                                          */
/*  Date        : 21-07-2021                                                                      */
/*                                                                                                */
/* @Description : Modem IF Frame Work                                                             */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "MODEM_IF.h"
#include "MODEM_IF_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/* Modem IF Tx Pin data */
#define MODEM_IF_TX_PORT                    ( GPIO_PORT_A )
#define MODEM_IF_TX_PIN                     ( GPIO_PIN_9 )

/* Modem IF Rx Pin data */
#define MODEM_IF_RX_PORT                    ( GPIO_PORT_A )
#define MODEM_IF_RX_PIN                     ( GPIO_PIN_8 )

/* Modem IF Reset Pin data */
#define MODEM_IF_RESET_PORT                 ( GPIO_PORT_A )
#define MODEM_IF_RESET_PIN                  ( GPIO_PIN_10 )

/* Modem IF Power Key Pin data */
#define MODEM_IF_POWER_KEY_PORT             ( GPIO_PORT_A )
#define MODEM_IF_POWER_KEY_PIN              ( GPIO_PIN_11 )

/* */



/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* */
volatile INT8U u8_gIsModemRdyFlag = 0;

/* */
INT32U u32_gModemIfTick = 0;



/* TeRIL Power Key pin */
ST_GPIO_PARAMS_t st_gModemPowerKeyPin =
{
    .en_mPortSel = GPIO_PORT_A,
    .en_mPinSel = GPIO_PIN_11,
    .en_mPinDir = GPIO_DIR_OUTPUT, 
    .en_mPinType = GPIO_PULL_LVL_DIS,   
    .en_mPinPeriph = GPIO_GENERAL_PURPOSE,
    .en_mDriverStrenght  = GPIO_DRIV_STRENGTH_STRONG
};

/* TeRIL Reset Pin */
ST_GPIO_PARAMS_t st_gModemResetPin =
{
    .en_mPortSel          = GPIO_PORT_A,
    .en_mPinSel          = GPIO_PIN_10,
    .en_mPinDir          = GPIO_DIR_OUTPUT, 
    .en_mPinType         = GPIO_PULL_LVL_DIS,   
    .en_mPinPeriph       = GPIO_GENERAL_PURPOSE,
    .en_mDriverStrenght  = GPIO_DRIV_STRENGTH_STRONG
};



/**************************************************************************************************/
/* Function Name   :                                                                              */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void MODEM_IF_10MsHandler(void)
{
  u32_gModemIfTick = u32_gModemIfTick + 10;
}

/**************************************************************************************************/
/* Function Name   :                                                                              */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void MODEM_IF_Delay(INT32U u32_fDelay)
{
    u32_gModemIfTick = 0;
    while(u32_gModemIfTick < u32_fDelay);
}

/**************************************************************************************************/
/* Function Name   :                                                                              */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void MODEM_IF_TurnOn(void)
{    
    GPIO_ResetPin(MODEM_IF_POWER_KEY_PORT, MODEM_IF_POWER_KEY_PIN);
    MODEM_IF_Delay(500);
    GPIO_SetPin(MODEM_IF_POWER_KEY_PORT, MODEM_IF_POWER_KEY_PIN);    
}

/**************************************************************************************************/
/* End of  MODEM_IF.c                                                                             */
/**************************************************************************************************/
