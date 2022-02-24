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
/*  File Name   : AUTHENTICATION.c                                                                */
/*  Author      : SANTHOSH                                                                        */
/*  Version 	: V1.0                                                                            */
/*  Date        : 24-09-2018                                                                      */
/*                                                                                                */
/* @Description : AUTHENTICATION                                                                  */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "BT43.h"
#include "STN.h"

#include "AUTHENTICATION.h"
#include "AUTHENTICATION_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

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

void AUTHENTICATION_Init(void)
{    
    /* Make the Authentication Flag to Zero */
    u8_gAuthCompltedFlag = 0x00;
    
    u8_gSTNMntrFlag = 0x00;
    
    /* Reset The Authentication LED */
    RESSET_PIN(AUTHNTCTN_LED_PORT ,AUTHNTCTN_LED_PIN );
                
    /* Reset the BT FIFO */
    BT43_Ioctrl(BT43_IOCTRL_RESET_FIFO ,PNULL, 0, PNULL , 0);
    
    /* Reset STN */
    en_gStnRespType = STN_PROMPT;
    
    STN_WriteData("ATZ\r\n", 5);
}

/**************************************************************************************************/
/* Function Name   : EN_STATE_RESULT_t BOOTUP_Handler(EN_STATE_LIST_t * p_fState, \               */
/*                                                                         INT32U u32_fTickCount) */
/*                                                                                                */
/* Description     : Bootup Handler State                                                         */
/*                                                                                                */
/* In Params       : State and Tickcount                                                          */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : Result                                                                       */
/**************************************************************************************************/

void AUTHENTICATION_Handler(EN_STATE_LIST_t * p_fState)
{
    if(1 == u8_gisDataFromBT)
    {
        INT8U *pu8_lFifoRefHold = PNULL;
        INT32U u32_lLength = 0;

        u8_gisDataFromBT = 0;
		
        /* Read Data from WIFI FIFO */
        /* get the refernce from the BT Buffer */
        BT43_Ioctrl(BT43_IOCTRL_GET_FIFO_REF ,PNULL, 0, &pu8_lFifoRefHold , &u32_lLength);
        
		//WIFI_Ioctrl(WIFI_IOCTRL_GET_FIFO_REF, PNULL, 0, &pu8_lFifoRefHold, &u32_lLength);
        
        /* Per Form Checking */
        switch(pu8_lFifoRefHold[0])
        {
        case ':':
        {
                /* Call Tbus Parsing */
                //TBUS_ParseCmd(pu8_lFifoRefHold, u32_lLength);
        }
        break;
        default:
        {
            /* No Action */
        }
        break;
        }
    }
    else
    {
        /* No Action */
    }
    
    if(1 == u8_gAuthCompltedFlag)
    {
        *p_fState = PASSTHRU;
    }
    else
    {
        /* No Action */
    }
}

/**************************************************************************************************/
/* Function Name   : EN_STATE_RESULT_t BOOTUP_Exit(EN_STATE_LIST_t * p_fState, \                  */
/*                                                                         INT32U u32_fTickCount) */
/*                                                                                                */
/* Description     : Bootup Exit State                                                            */
/*                                                                                                */
/* In Params       : State and Tick Count                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : Result                                                                       */
/**************************************************************************************************/

void AUTHENTICATION_Exit(void)
{
    /* No Action */
}

/**************************************************************************************************/
/* End of  AUTHENTICATION.c                                                                       */
/**************************************************************************************************/
