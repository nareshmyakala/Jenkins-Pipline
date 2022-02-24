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
/*  File Name   : BOOTUP.c                                                                        */
/*  Author      : santhosh                                                                        */
/*  Version 	: v1.0                                                                            */
/*  Date        : 24-09-2018                                                                      */
/*                                                                                                */
/* @Description : BOOTUP Handler                                                                  */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "DATACONV.h"

#include "PLATFORM.h"

#include "NVMCTRL.h"
#include "ADC_SCOPE.h"
#include "HOST_SPISlaveIF.h"

#include "STN.h"
#include "BT43.h"
#include "UART.h"
#include "SPI.h"

#include "BOOTUP.h"
#include "BOOTUP.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Boot Flag */
INT8U u8_gBootFlag = 0x00;

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

void BOOTUP_Init(void)
{
    /* FLASH Init */
    FLASH_Init();

    ADC_ScopeInit();
     
  //  ADC_ScopeStart();
    
    //CAN_IF_Init(ISOTP_canInit);

    /* Check Whether FirstBoot Is done or not if not perform and Switch the State */
   // FirstBootCheck();

    /* Host SPI Slave IF Init */
    HOST_SPISlaveIFInit();
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

void BOOTUP_Handler(EN_STATE_LIST_t * p_fState)
{
    /* Switch The Sate To Authentication */
   // *p_fState = AUTHENTICATION;
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

void BOOTUP_Exit(void)
{
    /* No Action */
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

void FirstBootCheck(void)
{
    ST_STN_INIT_t st_lStnData;
   
    /* Write the First Boot Flag Into NVM */
    FLASH_Read(EEPROM_BOOT_STATUS_BASEADDR, &u8_gBootFlag, 1);
    
    /* Check for the First Boot */
    if(0x55 != u8_gBootFlag)
    {       
        /* Update the Boot Flag */
        u8_gBootFlag = 0x55;
 
        /* Update the STN Baudrate and Call Back */
        st_lStnData.u32_mBaudRate = 9600;
        st_lStnData.pf_mStnCallBack = PNULL;

         /* Init the STN11110 */
        STN_Init(&st_lStnData);
        
        /* Init the BT43 in First Boot Mode */
        BT43_FirstBoot();

        INT32U u32_lSTNBaudrate = 460800;
        if(STN_SUCCESS == STN_Ioctrl(STN_IOCTRL_CHANGE_STN_BAUD, &u32_lSTNBaudrate ,4 ,PNULL, 0))
        {
            /* Write the First Boot Flag Into EEPROM */
            FLASH_Write(EEPROM_BOOT_STATUS_BASEADDR, &u8_gBootFlag, 1);
        }
        else
        {
          /* No Action */
        }
    }
    else
    {  
        /* Update the STN Baudrate and Call Back */
        st_lStnData.u32_mBaudRate = 460800;
        st_lStnData.pf_mStnCallBack = PNULL;

        /* Init the STN11110 */
        STN_Init(&st_lStnData);
        
        /* Initi The BT43 */
        BT43_Init();
    }
}

/**************************************************************************************************/
/* End of  BOOTUP.c                                                                               */
/**************************************************************************************************/
