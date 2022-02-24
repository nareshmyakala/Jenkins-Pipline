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
/*  File Name   : MSG4_App.c                                                                      */
/*  Author      : NAGANJALI.K                                                                     */
/*  Version 	: v1.0                                                                            */
/*  Date        : 01-02-2022                                                                      */
/*                                                                                                */
/* @Description : MSG4_App Driver Frame Work                                                      */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>
#include <stdlib.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "PLATFORM.h"

#include "BOOTUP.h"
#include "AUTHENTICATION.h"
#include "PASSTHRU.h"
#include "DATACONV.h"

#include "STN.h"
#include "BT43.h"
#include "TBUS.h"
#include "IGN_ON.h"
#include "IGN_OFF.h"
#include "ERROR.h"
#include "IDLE.h"

#include "HOST_SPISlaveIF.h"
#include "TEOBD2_public.h"

#include "MSG4_App.h"
#include "MSG4_App_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* 1msec counter global variable */
INT32U u32_g1ms_Countr = 0x00;

/* ISOTP Rx Data Buffer */
INT8U au8_gIsoTpRxDataBuffer[4095] = {0, };

/* Initialization OF FSM Statemachines */
const ST_STATES_t st_gFSM_States[] =
{
    {
        /* Bootup State Handlers */
        .fp_mStateInit = BOOTUP_Init,
        .fp_mStateHandler = BOOTUP_Handler,
        .fp_mStateExit = BOOTUP_Exit
    },

    {
        /* Authentication State Handlers */
        .fp_mStateInit = AUTHENTICATION_Init,
        .fp_mStateHandler = AUTHENTICATION_Handler,
        .fp_mStateExit = AUTHENTICATION_Exit
    },

    {
        /* PASSTHRU API's */
        .fp_mStateInit = PASSTHRU_Init,
        .fp_mStateHandler = PASSTHRU_Handler,
        .fp_mStateExit = PASSTHRU_Exit,
    }, 
    
    {
        /* IGN_ON State Handlers */
        .fp_mStateInit = IGN_ON_Init,
        .fp_mStateHandler = IGN_ON_Handler,
        .fp_mStateExit = IGN_ON_Exit
    },
    
    {
        /* IGN_OFF State Handlers */
        .fp_mStateInit = IGN_OFF_Init,
        .fp_mStateHandler = IGN_OFF_Handler,
        .fp_mStateExit = IGN_OFF_Exit
    },
    
    {
        /* Error State Handlers */
        .fp_mStateInit = Error_Init,
        .fp_mStateHandler = Error_Handler,
        .fp_mStateExit = Error_Exit
    },
    
    {
        /* IDLE State Handlers */
        .fp_mStateInit = IDLE_Init,
        .fp_mStateHandler = IDLE_Handler,
        .fp_mStateExit = IDLE_Exit
    },
};


/* Initializing can */
ST_CAN_MO_CFG_t ISOTP_canInit[3] = 
{
  {
    .en_mCanCh = CAN0,     
    .u8_mCanMOIndex = 0,    
    .u32_mCanMsgId =  0x7E0,
    .u32_mAcceptMask = 0x00,   
    .u8_mDLC = 8,             
    .en_mCanIdType = CAN_STD_ID, 
    .en_mMOType = CAN_MB_TRANSMIT,        
    .en_mCanIfBaudRate = CAN_500_KBPS,  
    .u8_mEOL = 0,            
    .fp_CanIfTxHandler = CAN_TxHandler, 
    .fp_CanIfRxHandler = CAN_RxHandler, 
    .fp_CanIfBusOffHandler = CAN_BusOffHandler, 
    .fp_CanIfErrorHandler =  CAN_ErrorHandler, 
  },
  
  {
    .en_mCanCh                  = CAN0,
    .u8_mCanMOIndex             = 0,
    .u32_mCanMsgId              = 0x7E8,
    .u32_mAcceptMask            = 0x00,
    .u8_mDLC                    = 8,
    .en_mCanIdType              = CAN_STD_ID,
    .en_mMOType                 = CAN_MB_RECEIVE,
    .u8_mEOL                    = 0,
  },
  {     
    .u8_mEOL                    = 1,    
  }
}; 

/* Initialize a state variables */
EN_STATE_LIST_t en_gCurrState = BOOTUP;
EN_STATE_LIST_t en_gPrevState = BOOTUP;

/* Pointer to Hold States */
const ST_STATES_t * p_stgFSM_States = (ST_STATES_t *)&st_gFSM_States;

/* STN data length */
INT32U u32_gStnDataLength = 0;

/* Flag to know is there data from STN */
INT8U u8_gIsDataFromStn = 0;

/* Varibale for Authentication Complete check */
INT8U u8_gAuthCompltedFlag = 0;

INT32U u32_gAdcScopeTimeOutCounter = 0;

/* Enum Variable For BT43 Connection Status */
EN_BT43_STATUS_t en_gBT43ConnectionStatus = BT43_STATUS_DISCONNECTED;

/**************************************************************************************************/
/* Function Name   :     void MSG4_1MsHandler(void)                                               */
/*                                                                                                */
/* Description     :     MSG4 1 msec Handler                                                      */
/*                                                                                                */
/* In Params       :     void                                                                     */
/*                                                                                                */
/* Out Params      :     void                                                                     */
/*                                                                                                */
/* Return Value    :     None                                                                     */
/**************************************************************************************************/

void MSG4_1MsHandler(void)
{
    /* Increment ADC Scope Time Out Counter */
    u32_gAdcScopeTimeOutCounter = u32_gAdcScopeTimeOutCounter + 1;
    
    /* Increment 1 milli sec counter */
    u32_g1ms_Countr = u32_g1ms_Countr + 1;
}

/**************************************************************************************************/
/* Function Name   : EN_STATE_LIST_t MSG2PRO_GetCurrentState(INT8U u8_fState)                     */
/*                                                                                                */
/* Description     : This Function is Used To Initialize the Default Initializations              */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

EN_STATE_LIST_t MSG2PRO_GetCurrentState(void)
{
    return en_gCurrState;
}

/**************************************************************************************************/
/* Function Name   :      void MSG4_IsotpRxConfirmation(INT32U u32_fCanId, INT8U *p_fPayload, \
                                                                             INT32U u32_fLength)  */
/*                                                                                                */
/* Description     :      Isotp Rx Confirmation                                                   */
/*                                                                                                */
/* In Params       :     u32_fCanId, u32_fLength                                                  */
/*                                                                                                */
/* Out Params      :      p_fPayload                                                              */
/*                                                                                                */
/* Return Value    :      None                                                                    */
/**************************************************************************************************/

void MSG4_IsotpRxConfirmation(INT32U u32_fCanId, INT8U *p_fPayload, INT32U u32_fLength)
{
    /* call Convert Bytearray to Pan */
    COMMON_ByteArray2PAN(au8_gIsoTpRxDataBuffer, p_fPayload, u32_fLength);
    
    /* Call TBUS Send Command */
    //TBUS_SendCommand(TBUS_PING, 0x00, au8_gIsoTpRxDataBuffer, u32_fLength); 
}

/**************************************************************************************************/
/* Function Name   :    void MSG4_IsotpTxConfirmation(INT32U u32_fData)                           */
/*                                                                                                */
/* Description     :        ISOTP Tx confirmation                                                 */
/*                                                                                                */
/* In Params       :         u32_fData                                                            */
/*                                                                                                */
/* Out Params      :         void                                                                 */
/*                                                                                                */
/* Return Value    :         None                                                                 */
/**************************************************************************************************/

void MSG4_IsotpTxConfirmation(INT32U u32_fData)
{
   /* No Action */
}

/**************************************************************************************************/
/* Function Name   :      void MSG4_IsotpErrorConfirmation(INT8U u8_fError)                       */
/*                                                                                                */
/* Description     :     ISOTP Error confirmation                                                 */
/*                                                                                                */
/* In Params       :       u8_fError                                                              */
/*                                                                                                */
/* Out Params      :       void                                                                   */
/*                                                                                                */
/* Return Value    :      None                                                                    */
/**************************************************************************************************/

void MSG4_IsotpErrorConfirmation(INT8U u8_fError)
{
    /* No Action */
}

/**************************************************************************************************/
/* Function Name   : void MSG2PRO_SwitchState(INT8U u8_fState)                                    */
/*                                                                                                */
/* Description     : This Function is Used To Initialize the Default Initializations              */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void MSG2PRO_SwitchState(INT8U u8_fState)
{
    if(u8_fState < MSG2_MAX_STATES)
    {
        if((en_gCurrState != AUTHENTICATION) && (en_gCurrState != BOOTUP))
        {
            en_gCurrState = (EN_STATE_LIST_t)u8_fState;
        }
        else
        {
           /* No Action */
        }
    }
    else
    {
        /* No Action */
    }
}

/**************************************************************************************************/
/* Function Name   :     void MSG4_CallBackFromStn(INT32U u32_fLength)                            */
/*                                                                                                */
/* Description     :      Call back from stn Function                                             */
/*                                                                                                */
/* In Params       :      u32_fLength                                                             */
/*                                                                                                */
/* Out Params      :       void                                                                   */
/*                                                                                                */
/* Return Value    :       None                                                                   */
/**************************************************************************************************/

void MSG4_CallBackFromStn(INT32U u32_fLength)
{
      /* Update Data Length */
      u32_gStnDataLength = u32_fLength;
      
      /* Set Falg */
      u8_gIsDataFromStn = 1;
}

/**************************************************************************************************/
/* Function Name   :    void MSG4_RegisterCallBacks(void)                                         */
/*                                                                                                */
/* Description     :        Register Call Back Function                                           */
/*                                                                                                */
/* In Params       :         void                                                                 */
/*                                                                                                */
/* Out Params      :          void                                                                */
/*                                                                                                */
/* Return Value    :          None                                                                */
/**************************************************************************************************/

void MSG4_RegisterCallBacks(void)
{
    /* Update STN call Back */
    STN_Ioctrl(STN_CALL_BACK_REGISTER, (void *)MSG4_CallBackFromStn, 1, PNULL, 0);
}

/**************************************************************************************************/
/* Function Name   :       void MSG4_AppInit(void)                                                */
/*                                                                                                */
/* Description     :       MSG4 App Initialization                                                */
/*                                                                                                */
/* In Params       :        void                                                                  */
/*                                                                                                */
/* Out Params      :        void                                                                  */
/*                                                                                                */
/* Return Value    :        None                                                                  */
/**************************************************************************************************/

void MSG4_AppInit(void)
{ 
    /* Register The WIF and STN Call BAck Functions*/
    MSG4_RegisterCallBacks();

    /* TBUS Initialization */
    TBUS_Init();
    
    /* TBUS Register Handlers */
//    TBUS_RegisterHandler(TBUS_PING, 0x00, TBUS_Ping);
//    TBUS_RegisterHandler(TBUS_SCOPE_START, 0x00, Tbus_ScopeStartHandler);
//    TBUS_RegisterHandler(TBUS_SCOPE_STOP, 0x00, Tbus_ScopeStopHandler);
    
    TBUS_RegisterHandler(TBUS_PING, 0x00, TBUS_Ping);
    TBUS_RegisterHandler(TBUS_START, 0x00, TBUS_StartScope);
    TBUS_RegisterHandler(TBUS_STOP, 0x00, TBUS_StopScope);
    
    /* Initialize the Default State */
    (p_stgFSM_States + en_gCurrState)->fp_mStateInit();
    
    while(1)
    {                 
        /* Check the present and previous states status */
        if(en_gCurrState != en_gPrevState)
        {
            /* Exit the Previous State */
            (p_stgFSM_States + en_gPrevState)->fp_mStateExit();

            /* Initialize the Current state */
            (p_stgFSM_States + en_gCurrState)->fp_mStateInit();

            /* Update the State Variables */
            en_gPrevState = en_gCurrState;
        }
        else
        {
            /* Run the Handler */
            (p_stgFSM_States + en_gCurrState)->fp_mStateHandler(&en_gCurrState);
        }   
        
       
         /* HOST SPI Slave IF Handler */
         SPISlaveIF_Handler();
         
        if(1 == u8_gIsSystickTimeOut)
        {
            u8_gIsSystickTimeOut =0;

//            /* Stack 1ms Handler */
//            TEOBD2_1MSHandler();
//
//            /* Call MSG2PRO 1ms Handler */
//            MSG4_1MsHandler();
            
            /* TBUS Rx Manager */
            TBUS_RxManager();
        }
    }
}

/**************************************************************************************************/
/* End of  MSG4_App.c                                                                             */
/**************************************************************************************************/
