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
/*  File Name   : CAN_IF.c                                                                        */
/*  Author      : Ravi Ranjan Kumar                                                               */
/*  Version 	: 1.0                                                                             */
/*  Date        : 27/04/2018                                                                      */
/*                                                                                                */
/* @Description : CAN Interface                                                                   */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "CAN.h"
#include "GPIO.h"
#include "TC.h"
#include "NVIC.h"

#include "CAN_IF.h"
#include "CAN_IF_Priv.h"
#include "MSG4_App.h"

#include "ISO15765_2.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

#define CAN_TX_PORT                  ( GPIO_PORT_A )
#define CAN_TX_PIN                   ( GPIO_PIN_22 )

#define CAN_RX_PORT                  ( GPIO_PORT_A )
#define CAN_RX_PIN                   ( GPIO_PIN_23 )

#define CAN_STB_PORT                 ( GPIO_PORT_A )
#define CAN_STB_PIN                  ( GPIO_PIN_21 )

#define CAN_PERIPHERAL               ( GPIO_PERIPHERAL_I )

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Initialize the CAN Data with the Rewuired Data */
ST_CAN_MO_CFG_t st_gCANTxMOConfig[3] =
{
  {
     .en_mCanCh                 = CAN0,
    .u8_mCanMOIndex             = 0,
    .u32_mCanMsgId              = 0x7E0,
    .u32_mAcceptMask            = 0x7FF,
    .u8_mDLC                    = 8,
    .en_mCanIdType              = CAN_STD_ID,
    .en_mMOType                 = CAN_MB_TRANSMIT,
    .en_mCanIfBaudRate          = CAN_500_KBPS,
    .fp_CanIfTxHandler          = CAN_TxHandler,
    .fp_CanIfRxHandler          = CAN_RxHandler,
    .fp_CanIfBusOffHandler      = CAN_BusOffHandler,
    .fp_CanIfErrorHandler       = CAN_ErrorHandler,
    .u8_mEOL                    = 0,
  },
  
  {
    .en_mCanCh                  = CAN0,
    .u8_mCanMOIndex             = 0,
    .u32_mCanMsgId              = 0x7E8,
    .u32_mAcceptMask            = 0x7FF,
    .u8_mDLC                    = 8,
    .en_mCanIdType              = CAN_STD_ID,
    .en_mMOType                 = CAN_MB_RECEIVE,
    .u8_mEOL                    = 0,
  },
  
  {     
    .u8_mEOL                    = 1,    
  },
};

/* Initialize the ISOTP Parameters */
ST_ISOTP_INIT_t st_gISOTP_Data = 
{
    .u32_mTxTimeOut = 5000,
    .u32_mFcTimeOut = 5000,
   // .en_mAddMode = NORMAL,
    .p_mRxIndication =  MSG4_IsotpRxConfirmation,
    .p_mTxConformation = MSG4_IsotpTxConfirmation,
    .p_mErrorIndication = MSG4_IsotpErrorConfirmation,
};

/* 1mSec Timer Configuration */
ST_TC_EVENT_PARAMS_t st_gISOTPTimer =
{
    .en_mTCSlice = TC_SLICE_2,
    .en_mDelayType = TC_DELAY_MS,              
    .u32_mTime = 1,
    .fp_User_Handler = ISO15765_OneMsHandler
};

/* ISO TP Tx & Rx Handlers */
INT32U u32_gCANReqID = 0x7E0;
INT32U u32_gCANRespID = 0x7E8;

void (* IsoTpTxHandler_fp)(INT32U msgId_u32); 
void (* IsoTpRxHandler_fp)(void * rxData_pv);

ST_CAN_MO_CFG_t * p_stgMailBoxConfig;

/**************************************************************************************************/
/* Function Name   : CAN_IF_Init()                                                                */
/*                                                                                                */
/* Description     : Initializes the CAN Low Level Driver                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_IF_RESULT_t : returns CAN_IF_OK On success                            */
/**************************************************************************************************/

void CAN_RxHandler(void * p_fCANData)
{
    /* Call the ISOTP Rx Handler */
    ISO15765_RxHandler(p_fCANData);   
}

/**************************************************************************************************/
/* Function Name   : CAN_IF_Init()                                                                */
/*                                                                                                */
/* Description     : Initializes the CAN Low Level Driver                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_IF_RESULT_t : returns CAN_IF_OK On success                            */
/**************************************************************************************************/

void CAN_TxHandler(INT32U u32_fCanID)
{
    /* Call the ISOTP TX Handler */
    ISO15765_TxHandler(u32_fCanID);
}

/**************************************************************************************************/
/* Function Name   : CAN_IF_Init()                                                                */
/*                                                                                                */
/* Description     : Initializes the CAN Low Level Driver                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_IF_RESULT_t : returns CAN_IF_OK On success                            */
/**************************************************************************************************/

void CAN_BusOffHandler(void)
{
    /* No Action */
  
}

/**************************************************************************************************/
/* Function Name   : CAN_IF_Init()                                                                */
/*                                                                                                */
/* Description     : Initializes the CAN Low Level Driver                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_IF_RESULT_t : returns CAN_IF_OK On success                            */
/**************************************************************************************************/

void CAN_ErrorHandler(void)
{
    /* No Action */
}

/**************************************************************************************************/
/* Function Name   : CAN_IF_Init()                                                                */
/*                                                                                                */
/* Description     : Initializes the CAN Low Level Driver                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_IF_RESULT_t : returns CAN_IF_OK On success                            */
/**************************************************************************************************/

EN_CAN_IF_RESULT_t CAN_IF_Init(ST_CAN_MO_CFG_t * p_stfMOConfig)
{
    EN_CAN_IF_RESULT_t en_lResult = CAN_IF_OK;

    /* Copy The Data into an Local Variable */
    ST_CAN_MB_CONFIG_PARAMS_t st_lMBConfig;
    
    /* MCAN0 Initialization */
    ST_CAN_CONFIG_PARAMS_t st_lCANConfigParams;

    /* Update the MO into an Global pointer */
    p_stgMailBoxConfig = p_stfMOConfig;

    /* Initialize the TX pin Data */    
    ST_GPIO_PARAMS_t st_lMCANTxConfig = 
    {    
        .en_mPortSel	 	= CAN_TX_PORT,
        .en_mPinSel	 	= CAN_TX_PIN,
        .en_mPinDir	 	= GPIO_DIR_OUTPUT,
        .en_mPinType	 	= GPIO_PULL_LVL_DIS,
        .en_mPinPeriph	 	= CAN_PERIPHERAL,
        .en_mDriverStrenght	= GPIO_DRIV_STRENGTH_STRONG
    };

    /* Configure CAN Tx Pin */
    GPIO_Init(&st_lMCANTxConfig);

     /* Initialize the RX pin Data */   
     ST_GPIO_PARAMS_t st_lMCANRxConfig = 
    {    
        .en_mPortSel	 	= CAN_RX_PORT,
        .en_mPinSel	 	= CAN_RX_PIN,
        .en_mPinDir	 	= GPIO_DIR_INPUT,
        .en_mPinType	 	= GPIO_PULL_LVL_DIS,
        .en_mPinPeriph	 	= CAN_PERIPHERAL,
        .en_mDriverStrenght	= GPIO_DRIV_STRENGTH_STRONG
    };
    
    /* Configure CAN Rx Pin */
    GPIO_Init(&st_lMCANRxConfig);
  
        /* Initialize the STB pin Data */    
    ST_GPIO_PARAMS_t st_lCANStbPinConfig = 
    {
        .en_mPortSel	    = CAN_STB_PORT,
        .en_mPinSel	 	    = CAN_STB_PIN,
        .en_mPinDir	 	    = GPIO_DIR_OUTPUT,
        .en_mPinType	 	= GPIO_PULL_LVL_DIS,
        .en_mPinPeriph	 	= GPIO_GENERAL_PURPOSE,
        .en_mDriverStrenght	= GPIO_DRIV_STRENGTH_STRONG
    };

     /* Initialize the STB pin Data */    
    GPIO_Init(&st_lCANStbPinConfig);

    /* Wakeup CAN Transceiver from Sleep */
    GPIO_ResetPin(st_lCANStbPinConfig.en_mPortSel, st_lCANStbPinConfig.en_mPinSel);
    
    /* Check the CAN Channel */
    if(p_stfMOConfig->en_mCanCh == CAN0)
    {     
        /* Initialization of CAN RX/TX  callback function handler */
        st_lCANConfigParams.en_mCANCh = p_stfMOConfig->en_mCanCh;
        st_lCANConfigParams.fp_TxHandler = p_stfMOConfig->fp_CanIfTxHandler;
        st_lCANConfigParams.fp_RxHandler = p_stfMOConfig->fp_CanIfRxHandler;
        st_lCANConfigParams.fp_BusOffHandler = p_stfMOConfig->fp_CanIfBusOffHandler;
        st_lCANConfigParams.fp_ErrorHandler = p_stfMOConfig->fp_CanIfErrorHandler;
        st_lCANConfigParams.en_mCANFdEnRDis = CAN_FD_DISABLE;
        st_lCANConfigParams.en_mDataFieldSize = CAN_8_BYTE_DATA;
        
        /* Update the Baudrate into an Varibale */
        st_lCANConfigParams.en_mBaudRate = p_stfMOConfig->en_mCanIfBaudRate;
        
        /* Initialize MCAN0 driver */
        CAN_Init(&st_lCANConfigParams);

        /* Configure MO from MailBox Config */
        for(INT8U u8_lIndex = 0; !p_stfMOConfig[u8_lIndex].u8_mEOL; u8_lIndex++)
        {
            ST_CAN_MO_CFG_t * p_stlMailBox = &p_stfMOConfig[u8_lIndex];
            
            st_lMBConfig.en_mCANCh       = (EN_CAN_CH_t )CAN_IF_CH_0;
            st_lMBConfig.en_mIdType      = (EN_CAN_ID_TYPE )p_stlMailBox->en_mCanIdType;
            st_lMBConfig.u8_mMsgBuffNo   = p_stlMailBox->u8_mCanMOIndex;
            st_lMBConfig.u32_mCANId     = p_stlMailBox->u32_mCanMsgId;
            st_lMBConfig.u32_mAcceptMsk  = p_stlMailBox->u32_mAcceptMask;
            st_lMBConfig.u8_mDlc         = p_stlMailBox->u8_mDLC;
            st_lMBConfig.en_MsgBuffType  = (EN_CAN_MB_TYPE_t )p_stlMailBox->en_mMOType;
            
            if(CAN_MB_TRANSMIT == p_stlMailBox->en_mMOType)
            {
                /* Configure Tx message buffer */
                CAN_ConfigTxMsgBuff(&st_lMBConfig);
            }
            else if(CAN_MB_RECEIVE == p_stlMailBox->en_mMOType)
            {
                /* Configure Rx message buffer */
                CAN_ConfigRxMsgBuff(&st_lMBConfig);
            }
            else
            {
                en_lResult = CAN_IF_ERROR;
            }
        }
    }
    else
    {
        /* No Action */
    }
    
    /* Initialize the ISOTP */
    ISO15765_Init(&st_gISOTP_Data);
    
    /* Initialize the Timer for ISOTP */
    TC_EventInit(&st_gISOTPTimer);
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : OSEK_COM_WriteMsgDataToPdu()                                                 */
/*                                                                                                */
/* Description     : Write the Signal Value to respective IPDU                                    */
/*                                                                                                */
/* In Params       : INT16U comMsgId_u16 : Unique Message ID                                      */
/*                                                                                                */
/* Out Params      : const void * comMsgDataRef_pv : Message Data pointer                         */
/*                                                                                                */
/* Return Value    : ComStatusType_t : returns E_OK On success                                    */
/**************************************************************************************************/

INT8U CAN_IF_GetMailBoxID(INT32U u32_fCanMsgID)
{
    INT8U u8_lMailBoxID = 0;
    
    for(INT8U u8_lIndex = 0; !p_stgMailBoxConfig[u8_lIndex].u8_mEOL; u8_lIndex++)
    {
        const ST_CAN_MO_CFG_t * p_lMbConfig = \
                   (const ST_CAN_MO_CFG_t *)&p_stgMailBoxConfig [u8_lIndex];
        
        if(p_lMbConfig->u32_mCanMsgId == u32_fCanMsgID)
        {
            u8_lMailBoxID = p_lMbConfig->u8_mCanMOIndex;
            break;
        }
    }
    
    return u8_lMailBoxID;
}

/**************************************************************************************************/
/* Function Name   : CAN_IF_WriteMsg()                                                            */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       : INT32U u32_fCANID : Transmit Message ID                                         */
/*                   INT8U u8_fMONumber : Trasmit MO Number                                          */
/*                   INT8U * u8_fPtr : Transmit Data Pointer                                         */
/*                   INT8U u8_fDLC : Transmit Message Length                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_IF_RESULT_t : returns CAN_IF_OK On success                            */
/**************************************************************************************************/

EN_CAN_IF_RESULT_t CAN_IF_WriteMsg(EN_CAN_IF_CH_t en_fCANCh, INT8U u8_fMONumber, INT32U u32_gCanID,
                                                            INT8U * u8_fPtr, INT8U u8_fDLC)
{
    EN_CAN_IF_RESULT_t canIfResult_en = CAN_IF_OK;
    ST_CAN_MB_CONFIG_PARAMS_t st_lMBConfig;
    
    st_lMBConfig.en_mCANCh = (EN_CAN_CH_t )en_fCANCh;
    st_lMBConfig.u8_mMsgBuffNo  = u8_fMONumber;
    st_lMBConfig.u32_mCANId = u32_gCanID;
    st_lMBConfig.u8_mDlc = u8_fDLC;
    st_lMBConfig.en_mIdType = CAN_STD_ID;
    st_lMBConfig.en_MsgBuffType = CAN_MB_TRANSMIT;
    st_lMBConfig.u32_mAcceptMsk = 0x7FF;
    memcpy(&st_lMBConfig.au8_mData[0], &u8_fPtr[0], u8_fDLC);
    
    /* Configure Tx message buffer*/
    CAN_ConfigTxMsgBuff(&st_lMBConfig);
    
    /* Execute send non-blocking */
    CAN_TransmitDataBuffer((EN_CAN_CH_t )en_fCANCh,u8_fMONumber);

    return canIfResult_en;
}

/**************************************************************************************************/
/* Function Name   : EN_CAN_IF_RESULT_t CAN_IF_ChangeBuadrate(EN_CAN_IF_CH_t en_mCANCh,           */
/*                                                            EN_CAN_IF_BAUDRATE_t en_fBaudrate)  */
/*                                                                                                */
/* Description     : Change the CAN Buadrate                                                      */
/*                                                                                                */
/* In Params       : EN_CAN_IF_CH_t en_mCANCh, EN_CAN_IF_BAUDRATE_t en_fBaudrate                  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_IF_RESULT_t : returns CAN_IF_OK On success                            */
/**************************************************************************************************/

EN_CAN_IF_RESULT_t CAN_IF_ChangeBuadrate(EN_CAN_IF_CH_t en_mCANCh,EN_CAN_IF_BAUDRATE_t en_fBaudrate)
{
    EN_CAN_IF_RESULT_t en_CanIfResult = CAN_IF_OK;
    
    CAN_ChangeBaudRate((EN_CAN_CH_t )en_mCANCh, (EN_CAN_BAUDRATE_t )en_fBaudrate);
    
    return en_CanIfResult;
}

/**************************************************************************************************/
/* Function Name   : CAN_IF_SutdownComm()                                                         */
/*                                                                                                */
/* Description     : Shutdown the CAN Communication                                               */
/*                                                                                                */
/* In Params       : EN_CAN_IF_CH_t en_mCANCh                                                     */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_IF_RESULT_t : returns CAN_IF_OK On success                            */
/**************************************************************************************************/

EN_CAN_IF_RESULT_t CAN_IF_SutdownComm(EN_CAN_IF_CH_t en_mCANCh)
{
    EN_CAN_IF_RESULT_t en_CanIfResult = CAN_IF_OK;
    
    CAN_DeInit((EN_CAN_CH_t )en_mCANCh);
    
    return en_CanIfResult;
}

/**************************************************************************************************/
/* Function Name   : CAN_IF_Sleep(EN_CAN_IF_CH_t en_fCANCh)                                       */
/*                                                                                                */
/* Description     : Function to enter sleep mode of CAN channel                                  */
/*                                                                                                */
/* In Params       : EN_CAN_IF_CH_t en_fCANCh                                                     */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_IF_RESULT_t : returns CAN_IF_OK On success                            */
/**************************************************************************************************/

EN_CAN_IF_RESULT_t CAN_IF_Sleep(EN_CAN_IF_CH_t en_fCANCh)
{
    EN_CAN_IF_RESULT_t canIfResult_en = CAN_IF_OK;  
    
    CAN_Sleep((EN_CAN_CH_t )en_fCANCh);
    
    return canIfResult_en;
}

/**************************************************************************************************/
/* Function Name   : EN_CAN_IF_RESULT_t CAN_IF_Awake(EN_CAN_IF_CH_t en_mCANCh)                    */
/*                                                                                                */
/* Description     : Wakeup the CAN node from the Sleep                                           */
/*                                                                                                */
/* In Params       : EN_CAN_IF_CH_t en_mCANCh                                                     */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_IF_RESULT_t : returns CAN_IF_OK On success                            */
/**************************************************************************************************/

EN_CAN_IF_RESULT_t CAN_IF_Awake(EN_CAN_IF_CH_t en_mCANCh)
{
    EN_CAN_IF_RESULT_t canIfResult_en = CAN_IF_OK;

    CAN_Wakeup((EN_CAN_CH_t )en_mCANCh);

    return canIfResult_en;
}


/**************************************************************************************************/
/* Function Name   : CAN_IF_InitIsoTp()                                                           */
/*                                                                                                */
/* Description     : Initialize the ISOTP request and response IDs, and TX and Rx Handlers        */
/*                                                                                                */
/* In Params       : IsoTpConfigParams_t * isoTpInitData_pst : ISOTP init data Pointer            */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : CanIfResult_t : returns CAN_IF_OK On success                                 */
/**************************************************************************************************/

EN_CAN_IF_RESULT_t CAN_IF_InitIsoTp(ST_ISOTP_PARAMS_t * isoTpInitData_pst)  
{
    EN_CAN_IF_RESULT_t canIfResult_en = CAN_IF_OK;

    /* update CAN TX and RX Event Handlers */
    IsoTpTxHandler_fp = isoTpInitData_pst->fp_IsoTpTxHandler;
    IsoTpRxHandler_fp = isoTpInitData_pst->fp_IsoTpRxHandler; 
     
     /* Update Request & Respose ID */
    u32_gCANReqID = isoTpInitData_pst->u32_mIsoTpReqId;
    u32_gCANRespID = isoTpInitData_pst->u32_mIsoTpRespId;
    
    return canIfResult_en;
}

EN_CAN_IF_RESULT_t CAN_IF_Ioctrl(EN_IOCTRL_ID_t en_fIoctrlID,EN_CAN_CH_t en_CANChnl, \
                        INT8U u8_fMONumber , INT32U u32_fAccceptnceMask ,EN_CAN_ID_TYPE en_fIDType,\
                                                     EN_CAN_MB_TYPE_t en_fMOType ,INT32U u32_fCANID)

{
    EN_CAN_IF_RESULT_t en_lResult = CAN_IF_OK;
    
    /* Copy The Data into an Local Variable */
    ST_CAN_MB_CONFIG_PARAMS_t st_lMBConfig;
        
    switch(en_fIoctrlID)
    {
    case MO_CONFIGURE:
      {
            st_lMBConfig.en_mCANCh       = (EN_CAN_CH_t )en_CANChnl;
            st_lMBConfig.en_mIdType      = (EN_CAN_ID_TYPE )en_fIDType;
            st_lMBConfig.u8_mMsgBuffNo   =  u8_fMONumber;
            st_lMBConfig.u32_mCANId     =   u32_fCANID;
            st_lMBConfig.u32_mAcceptMsk  =  u32_fAccceptnceMask;
            st_lMBConfig.u8_mDlc         = 8;
            st_lMBConfig.en_MsgBuffType  = (EN_CAN_MB_TYPE_t )en_fMOType;
            
            if(CAN_MB_TRANSMIT == en_fMOType)
            {
                /* Configure Tx message buffer */
                CAN_ConfigTxMsgBuff(&st_lMBConfig);
            }
            else if(CAN_MB_RECEIVE == en_fMOType)
            {
                /* Configure Rx message buffer */
                CAN_ConfigRxMsgBuff(&st_lMBConfig);
            }
            else
            {
                en_lResult = CAN_IF_ERROR;
            }
      }
      break;
    default:
      {
      }
    break;
    }
    
    return en_lResult;
}
/**************************************************************************************************/
/* Function Name   : CAN_IF_InitIsoTp()                                                           */
/*                                                                                                */
/* Description     : Initialize the ISOTP request and response IDs, and TX and Rx Handlers        */
/*                                                                                                */
/* In Params       : IsoTpConfigParams_t * isoTpInitData_pst : ISOTP init data Pointer            */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : CanIfResult_t : returns CAN_IF_OK On success                                 */
/**************************************************************************************************/

 void TE_StackSTB_Cntrl(TE_STB_CNTRL_t en_mIntrpt)
 {
   if(STB_ENABLE == en_mIntrpt)
   {
        //NVIC_EnableInterrupt(CAN0_IRQ);  

        /* Wakeup CAN Transceiver from Sleep */
        GPIO_ResetPin(CAN_STB_PORT, CAN_STB_PIN);
     
   }
   else if(STB_DISABLE == en_mIntrpt)
   {
       // NVIC_DisableInterrupt(CAN0_IRQ);

        /* Wakeup CAN Transceiver from Sleep */
        GPIO_SetPin(CAN_STB_PORT, CAN_STB_PIN);
   }
   else
   {
     
   }
   
 }

/**************************************************************************************************/
/* End of CAN_IF.c                                                                                */
/**************************************************************************************************/
