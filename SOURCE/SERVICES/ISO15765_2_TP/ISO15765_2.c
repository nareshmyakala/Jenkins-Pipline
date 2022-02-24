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
/*  File Name   : ISO15765_2.c                                                                    */
/*  Author      : Srilatha B                                                                      */
/*  Version 	: v1.0                                                                            */
/*  Date        : 10-06-2018                                                                      */
/*                                                                                                */
/* @Description : ISO15765 Frame Work                                                             */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "CAN_IF.h"

#include "ISO15765_2.h"
#include "ISO15765_2_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Enum Variable for Selecting the Tx states */
EN_TX_STATES_t en_gTxState = TX_INIT_STATE;

/* Enum variable for error types*/
EN_ERROR_t en_gError = OK;

/* Structure variable for ISOTP initilization */
ST_ISOTP_INIT_t st_gIsoTpParams;

/* ISOTP Tx Parameters for Sending data */
INT32U u32_gIsoTpTxHeader = 0;
INT16U u16_gIsoTpTxDataSize = 0;
INT16U u16_gIsoTpTxIndex = 0;
INT8U au8_gIsoTpTxBuffer[ISO15765_MAX_DATA_SIZE] = {0, };
INT8U u8_gEnableTxFlag = 0;

/* ISOTP Rx Parameters For Reciving  */
INT32U u32_gIsoTpRxHeader = 0;
INT16U u16_gIsoTpRxDataSize = 0;
INT16U u16_gIsoTpRxIndex = 0;
INT8U au8_gIsoTpRxBuffer[ISO15765_MAX_DATA_SIZE] = {0, };

/* Variable for FC TimeOut Counter */
INT32U u32_gFcTimeOutCount = 0;

/* Variable for Tx Time Out flag */
INT8U u8_gTxTimeOutFlag = 0;

/* Rx Flow Control Parameters */
INT8U u8_gRxFC = 0;
INT16U u16_gRxBS = 0;
INT8U u8_gRxSTmin = 0;
INT8U u8_gConsdrSprtnTimeFalg = 0x00;

/* Variables For Storing an Rx AE,TA */ 
INT8U u8_gAddExtension = 0;
INT8U u8_gTargetAddress = 0;

/* Varibles for storing Rx Consecutive indexes*/
INT8U u8_gConsecutiveIndex = 0;
INT8U u8_gNextConsecutiveIndex = 0;

/* Variable for rx flow control*/
INT8U u8_gIsFlowControl = 0;

/* Variable Blocksize Counter*/
INT16U u16_gBsCount = 0;

/* Variable Seperation Time Counter*/
INT8U u8_gSTminCount = 0;

/* Variable for Tx TimeOut Counter */
INT32U u32_gTxTimeOutCount = 0;

/* TESTACK vARIABLES */
/* Stack Related Variables */
INT8U u8_gIsoTpDataRecvdFlag = 0;

INT8U u8_RxTimeOutFlag;

/* This is the counter variable used for delays. */
INT16U u16_gEvntCntr = 0x00;

/* This is another counter variable for 40seconds delay. */
INT16U u16_gEvntCntr2 = 0x00;

/* Varialble for Selecting  the Addressing Mode */
AddressingMode_t en_gAddressingMode = NORMAL_ADDRESSING;

/**************************************************************************************************/
/* Function Name   : void ISO15765_OneMsHandler(void)                                             */
/*                                                                                                */
/* Description     : This function using for timing base operations                               */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_OneMsHandler(void)
{
    /*Checking TxFlag */
    if(TRUE == u8_gEnableTxFlag)
    {
        /*Calling the Tx Scheduler*/
        ISO15765_TxScheduler();
    }
    else
    {
        /* No Action */
    }
    
    if(TRUE == u8_gTxTimeOutFlag)
    {
        /* Incrementing the time out counter */
        u32_gTxTimeOutCount++ ;

        /* Checking for time out */
        if(st_gIsoTpParams.u32_mTxTimeOut == u32_gTxTimeOutCount)
        {
            /* Disable the Tx Time out */
            ISO15765_TxTimeOutDisable();

            /* Updating the Error Variable */
            en_gError = ERROR;

            /* Calling error indication */
            if(PNULL != st_gIsoTpParams.p_mErrorIndication)
            {
                st_gIsoTpParams.p_mErrorIndication(en_gError);
            }
            else
            {
                /* No Action */
            }
        }
        else
        {
            /* No action*/
        }
    }
    else
    {
        /* No Action */
    }
    
   // if(1 == u8_gDevOpmode)
    {
        /* */
        u16_gEvntCntr = u16_gEvntCntr +1;
    }
  //  else
    {
        /* No Action */
    }
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_TxHandler(void)                                                */
/*                                                                                                */
/* Description     : This function calling the time out disable function                          */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_TxHandler(INT32U u32_fCANid)
{
  /*Disable the Timeout*/
  ISO15765_TxTimeOutDisable();
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_RxHandler(void * pv_fRxData)                                   */
/*                                                                                                */
/* Description     : This function Calls the frame type depending upon the Addressing modes       */
/*                                                                                                */
/* In Params       : void * pv_fRxData                                                            */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_RxHandler(void * pv_fRxData)
{
    /* Copying the Rx data */
    ST_ISOTP_DATA_t * pst_lIsotpData = (ST_ISOTP_DATA_t *)pv_fRxData;

    /* Reciving ISOTP Rx Data in Normal Addressing */
    ISO15765_RxNormalAdd(pst_lIsotpData);    
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_RxNormalAdd(ST_ISOTP_DATA_t * pst_fData)                       */
/*                                                                                                */
/* Description     : Calling the Frame Types                                                      */
/*                                                                                                */
/* In Params       : ST_ISOTP_DATA_t * pst_fData                                                  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_RxNormalAdd(ST_ISOTP_DATA_t * pst_fData)
{
    EN_FRAME_TYPE_t  en_lFrameType;
    
    /* Reading the higher nibble from zeroth byte to find type of frame */
    en_lFrameType = (EN_FRAME_TYPE_t)ISO15765_GetNibble(pst_fData->au8_mData[0], HIGHER);
    
    switch(en_lFrameType)
    {    
      case SINGLE_FRAME:
      {
        /* Read the length of the data */
        u16_gIsoTpRxDataSize = ISO15765_GetNibble(pst_fData->au8_mData[0], LOWER);

        /* Copying the data from RxData Size */
        memcpy(&au8_gIsoTpRxBuffer[0], &pst_fData->au8_mData[1], u16_gIsoTpRxDataSize);

        /* Calling Rx user indication*/
        if(NULL != st_gIsoTpParams.p_mRxIndication)
        {
            st_gIsoTpParams.p_mRxIndication(pst_fData->u32_mCanId, \
                                             &au8_gIsoTpRxBuffer[0], u16_gIsoTpRxDataSize);
        }
        else
        {
            /* No Action */
        }
      }
      break;

      case FIRST_FRAME:
      {
        /* Read the length of the data */
        u16_gIsoTpRxDataSize = ISO15765_GetNibble(pst_fData->au8_mData[0], LOWER) << 8;

        /* Update the Data size with first byte */
        u16_gIsoTpRxDataSize |= pst_fData->au8_mData[1];

        /* Copying the data from RxData Size */
        memcpy((void *)&au8_gIsoTpRxBuffer[0], (const void *)&pst_fData->au8_mData[2], 6);

        /* Incresing the Rx Index */
        u16_gIsoTpRxIndex = 6;

        /* Decresing the Rx Datasize */
        u16_gIsoTpRxDataSize = u16_gIsoTpRxDataSize - 6;

        /* Setting the Consecutive frame to one */
        u8_gNextConsecutiveIndex = 1;

        /* Enable the Tx Timeout */
        ISO15765_TxTimeOutEnable();

        /* Calling Send Flow Control Frame */
        ISO15765_SendFlowControlFrame(FC_CTS, 0x00, 0x00);     
      }
      break;

      case FLOWCONTROL_FRAME:
      {
         /* Update the Rx Flag With Lower nibble */
         u8_gRxFC = ISO15765_GetNibble(pst_fData->au8_mData[0], LOWER);
         
         /* Update the Rx  Block size with First byte */
         u16_gRxBS = pst_fData->au8_mData[1];
         
          if(0 == u8_gConsdrSprtnTimeFalg)
          {
                /* Update the Rx  Seperation time with second byte */
                u8_gRxSTmin = pst_fData->au8_mData[2];
          }
          else if(0x01 == u8_gConsdrSprtnTimeFalg)
          {
               if(u8_gRxSTmin < pst_fData->au8_mData[2])
               {
                   u8_gRxSTmin  = pst_fData->au8_mData[2];
               }
               else if(u8_gRxSTmin > pst_fData->au8_mData[2])
               {
                   /* No Action */
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

         /* Setting the flow control to one */
         u8_gIsFlowControl = 1;
      }
      break;

      case CONSECUTIVE_FRAME:
      {
        /* Read Rx Data size From Lower Nibble */
        u8_gConsecutiveIndex = ISO15765_GetNibble(pst_fData->au8_mData[0], LOWER);

        /* Checking Consecutive Index */
        if(u8_gConsecutiveIndex == u8_gNextConsecutiveIndex)
        {
            /* Checking whether data is more then eight bytes */
            if(u16_gIsoTpRxDataSize >= 7)
            {
              /* Copy the Local objects */
              memcpy((void *)&au8_gIsoTpRxBuffer[u16_gIsoTpRxIndex], \
              (const void *)&pst_fData->au8_mData[1], 7);

              /* Incresing the Rx Index */
              u16_gIsoTpRxIndex = u16_gIsoTpRxIndex + 7;

              /* Decresing the Rx Datasize */
              u16_gIsoTpRxDataSize = u16_gIsoTpRxDataSize - 7;
            }
            else
            {
                 /* Copying the Local objects */
                 memcpy((void *)&au8_gIsoTpRxBuffer[u16_gIsoTpRxIndex], \
                            (const void *)&pst_fData->au8_mData[1], u16_gIsoTpRxDataSize);
                 
                 /* Incresing Rx index With Rx Data size */
                 u16_gIsoTpRxIndex = u16_gIsoTpRxIndex + u16_gIsoTpRxDataSize;

                  /* After copying the data, data size should be zero */
                 u16_gIsoTpRxDataSize = 0;
            }
            
            /* If Data Size is Zero Calling Rx Indication */
            if(0 == u16_gIsoTpRxDataSize)
            {
                /* Calling user Rx indication */
               if(NULL != st_gIsoTpParams.p_mRxIndication)
                {
                    st_gIsoTpParams.p_mRxIndication(pst_fData->u32_mCanId, \
                                              &au8_gIsoTpRxBuffer[0], u16_gIsoTpRxIndex);
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
            /*If ConsecutiveIndex is equals to fifteen then it should be zero*/
            u8_gNextConsecutiveIndex = (u8_gNextConsecutiveIndex + 1) % 16;
        }
        else
        {
          /* No Action */
           en_gError = WRONG_SN;
        }
      }
      break;

      default:
      {
         /* No Action */
      }
    }
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_SendFlowControlFrame(INT8U u8_fFCFlag, INT8U u8_fBlockSize,    */
/*                                                                       INT8U u8_fSTmin)         */
/*                                                                                                */
/* Description     : Sending the Flow Control Frame depending upon the addressing mode            */
/*                                                                                                */
/* In Params       : INT8U u8_fFCFlag, INT8U u8_fBlockSize, INT8U u8_fSTmin                       */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_SendFlowControlFrame(INT8U u8_fFCFlag, INT8U u8_fBlockSize, INT8U u8_fSTmin)
{
    INT8U au8_lPayLoad[8] = {0, };

    /* Setting Higher nibble as Flow Control Frame */
    ISO15765_SetNibble(&au8_lPayLoad[0], FLOWCONTROL_FRAME, HIGHER);
            
    /* Setting Lower nibble as Flow Control Flag */
    ISO15765_SetNibble(&au8_lPayLoad[0], u8_fFCFlag, LOWER);

    /* Setting First Byte As BlockSize */
    au8_lPayLoad[1] = u8_fBlockSize;

    /* Setting second byte as Seperation Time */
    au8_lPayLoad[2] = u8_fSTmin;
    
#ifdef TRACE_ENABLE
    /* Reset the buffer. */
    memset(au8_gCAN_LogBuffer,0x00,sizeof(au8_gCAN_LogBuffer));

    sprintf((char*)au8_gCAN_LogBuffer,"[%.6f] %X Tx %02d %02X %02X %02X %02X %02X %02X %02X %02X \r\n",\
                    f32_gTimeStamp,CAN_IF_REQUEST_HEADER, 8, au8_lPayLoad[0], au8_lPayLoad[1],\
                        au8_lPayLoad[2], au8_lPayLoad[3], au8_lPayLoad[4], au8_lPayLoad[5],\
                                au8_lPayLoad[6], au8_lPayLoad[7]);

    TRACE_DEBUG_WP("%s",au8_gCAN_LogBuffer);
#endif
    
    /* */
    CAN_IF_WriteMsg(CAN_IF_CH_0, 0, CAN_IF_OTA_REQ_HEADER, &au8_lPayLoad[0], 8);
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_TxTimeOutEnable(void)                                          */
/*                                                                                                */
/* Description     : This function enables the TimeOut enable flag                                */
/*                                                                                                */
/* In Params       : void                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_TxTimeOutEnable(void)
{
  /* Setting the time out flag*/
  u8_gTxTimeOutFlag = TRUE;
  
  /* disable the tx time out counter varible*/
  u32_gTxTimeOutCount = FALSE;
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_TxTimeOutDisable(void)                                         */
/*                                                                                                */
/* Description     : This function disables the TimeOut flag and time Counter                     */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_TxTimeOutDisable(void)
{
    /* Disable the time out flag*/
    u8_gTxTimeOutFlag = FALSE;

    /* Disable the time out Counter*/
    u32_gTxTimeOutCount = FALSE;
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_TxScheduler(void)                                              */
/*                                                                                                */
/* Description     : This Function handling the Tx states                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_TxScheduler(void)
{
  switch(en_gTxState)
  {
    case TX_INIT_STATE:
    {
      /* Calling Tx init State */
      ISO15765_TxInitState(&en_gTxState);
    }
    break;

    case TX_SINGLE_FRAME_STATE:
    {
      /* Calling Tx Single frame State */
      ISO15765_TxSingleFrameState(&en_gTxState);
    }
    break;

    case TX_FIRST_FRAME_STATE:
    {
      /* Calling Tx First frame State */
      ISO15765_TxFirstFrameState(&en_gTxState);
    }
    break;

    case RX_FLOW_CONTROL_STATE:
    {
      /* Calling Rx Flow Control frame State */
      ISO15765_RxFlowControlFrameState(&en_gTxState);
    }
    break;

    case TX_CONSECUTIVE_FRAME_STATE:
    {
      /* Calling Tx Consecutive frame State */
      ISO15765_TxConsecutiveFrameState(&en_gTxState);
    }
    break;

    case TX_SUCCESS_STATE:
    {
      /* Calling Success State */
      ISO15765_TxSuccessState(&en_gTxState);

      /*Calling Tx Conformation*/
      if(PNULL != st_gIsoTpParams.p_mTxConformation)
      {
        st_gIsoTpParams.p_mTxConformation(u32_gIsoTpTxHeader);
      }
      else
      {
         /*No Action */
      }
    }
    break;

    case TX_ERROR_STATE:
    {
      /* Calling Tx Error State */
      ISO15765_TxErrorState(&en_gTxState);

      /* Calling error indication */
      /* Calling error indication */
      if(PNULL != st_gIsoTpParams.p_mErrorIndication)
      {
        st_gIsoTpParams.p_mErrorIndication(en_gError);
      }
      else
      {
         /*No Action */
      }
    }
    break;

    default :
    {
        /* No Action */
    }
  }
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_TxInitState(EN_TX_STATES_t *pen_fTxStatePtr)                   */
/*                                                                                                */
/* Description     : Initilization of Tx State                                                    */
/*                                                                                                */
/* In Params       : EN_TX_STATES_t *pen_fTxStatePtr                                              */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_TxInitState(EN_TX_STATES_t * pen_fTxStatePtr)
{
    /* Checking data size is lessthan are equals to seven */
    if((u16_gIsoTpTxDataSize > 0) && (u16_gIsoTpTxDataSize <= 7))
    {
        /* Moved to single frame State */
        *pen_fTxStatePtr = TX_SINGLE_FRAME_STATE;
    }
    else if((u16_gIsoTpTxDataSize > 7) && (u16_gIsoTpTxDataSize < 4096))
    {
        u16_gIsoTpTxIndex = 0;

        /*Moved to first frame State*/
        *pen_fTxStatePtr = TX_FIRST_FRAME_STATE;
    }
    else 
    {
        /* Updated the error variable */
        en_gError = DATA_LENGTH;

        /* Moved to Error State */
        *pen_fTxStatePtr = TX_ERROR_STATE;
    }

    /* ISOTP Time out enabling */
    ISO15765_TxTimeOutEnable();   
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_TxSingleFrameState(EN_TX_STATES_t *pen_fTxStatePtr             */
/*                                                                                                */
/* Description     : Sending single frame in this state                                           */
/*                                                                                                */
/* In Params       : EN_TX_STATES_t *pen_fTxStatePtr                                              */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_TxSingleFrameState(EN_TX_STATES_t *pen_fTxStatePtr)
{
    INT8U au8_lPayLoad[8] = {0x00, };

    /* Setting Higher nibble as a single Frame */
    ISO15765_SetNibble(&au8_lPayLoad[0], SINGLE_FRAME, HIGHER);

    /* Setting Lower nibble as a DataLength */
    ISO15765_SetNibble(&au8_lPayLoad[0], u16_gIsoTpTxDataSize, LOWER);

    /* copy the number of bytes */
    memcpy(&au8_lPayLoad[1], &au8_gIsoTpTxBuffer[0], u16_gIsoTpTxDataSize);

    /* after the copying data, data size should be zero */
    u16_gIsoTpTxDataSize = 0;
    
#ifdef TRACE_ENABLE

    /* Reset the buffer. */
    memset(au8_gCAN_LogBuffer,0x00,sizeof(au8_gCAN_LogBuffer));

    sprintf((char*)au8_gCAN_LogBuffer,"[%.6f] %X Tx %02d %02X %02X %02X %02X %02X %02X %02X %02X \r\n",\
                    f32_gTimeStamp,CAN_IF_REQUEST_HEADER, 8, au8_lPayLoad[0], au8_lPayLoad[1],\
                        au8_lPayLoad[2], au8_lPayLoad[3], au8_lPayLoad[4], au8_lPayLoad[5],\
                                au8_lPayLoad[6], au8_lPayLoad[7]);

    TRACE_DEBUG_WP("%s",au8_gCAN_LogBuffer);
#endif
 
    /* */
    CAN_IF_WriteMsg(CAN_IF_CH_0, 0, CAN_IF_OTA_REQ_HEADER, &au8_lPayLoad[0], 8);

    /* Moved to Success state */
    *pen_fTxStatePtr = TX_SUCCESS_STATE;
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_TxFirstFrameState(EN_TX_STATES_t *pen_fTxStatePtr)             */
/*                                                                                                */
/* Description     : Sending Tx First Frame in this State                                         */
/*                                                                                                */
/* In Params       : EN_TX_STATES_t *pen_fTxStatePtr                                              */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_TxFirstFrameState(EN_TX_STATES_t *pen_fTxStatePtr)
{
    INT8U au8_lPayLoad[8] = {0x00, };

    /* Setting Higher nibble as First Frame */
    ISO15765_SetNibble(&au8_lPayLoad[0], FIRST_FRAME, HIGHER);

    /* Setting Lower nibble as DataLength */
    ISO15765_SetNibble(&au8_lPayLoad[0], ((u16_gIsoTpTxDataSize >> 8) & 0x0F), LOWER);

    /* Update the datasize with first byte*/
    au8_lPayLoad[1] = u16_gIsoTpTxDataSize & 0xFF;

    /* copy the number of bytes */
    memcpy(&au8_lPayLoad[2], &au8_gIsoTpTxBuffer[u16_gIsoTpTxIndex], 6);

    /* Decresing the Tx Data length */
    u16_gIsoTpTxDataSize = u16_gIsoTpTxDataSize - 6;

    /* Incresing the Tx Index */
    u16_gIsoTpTxIndex = 6;
 
    /* Setting Consecutive Index As one */
    u8_gConsecutiveIndex =  1;

#ifdef TRACE_ENABLE

    /* Reset the buffer. */
    memset(au8_gCAN_LogBuffer,0x00,sizeof(au8_gCAN_LogBuffer));

    sprintf((char*)au8_gCAN_LogBuffer,"[%.6f] %X Tx %02d %02X %02X %02X %02X %02X %02X %02X %02X \r\n",\
                    f32_gTimeStamp,CAN_IF_REQUEST_HEADER, 8, au8_lPayLoad[0], au8_lPayLoad[1],\
                        au8_lPayLoad[2], au8_lPayLoad[3], au8_lPayLoad[4], au8_lPayLoad[5],\
                                au8_lPayLoad[6], au8_lPayLoad[7]);

    TRACE_DEBUG_WP("%s",au8_gCAN_LogBuffer);
#endif
    
        /* */
        CAN_IF_WriteMsg(CAN_IF_CH_0, 0, CAN_IF_OTA_REQ_HEADER, &au8_lPayLoad[0], 8);
    
    /* State moved to flow Control */
    *pen_fTxStatePtr = RX_FLOW_CONTROL_STATE;
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_RxFlowControlFrameState(EN_TX_STATES_t * pen_fTxStatePtr)      */
/*                                                                                                */
/* Description     : Receiving RxFlowControl in this state                                        */
/*                                                                                                */
/* In Params       : EN_TX_STATES_t * pen_fTxStatePtr                                             */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_RxFlowControlFrameState(EN_TX_STATES_t * pen_fTxStatePtr)
{	
  /* Checking the variable whether it is Flow Control */
  if(TRUE == u8_gIsFlowControl)
  {
    /* Clearing the Flow Control Flag */
    u8_gIsFlowControl = 0;
     
    if(FC_CTS == u8_gRxFC)
    {
      /* Block size equals to zero */
      u16_gBsCount = 0;
      
      /* Checking the STmin */
      if(FALSE == u8_gRxSTmin)
      {
        /* STmin equals to one */
        u8_gRxSTmin = 1;
         
        /* STmin Counter equals to one */
        u8_gSTminCount = 1;
      
        /* Moved to Consective Frame State */
        *pen_fTxStatePtr = TX_CONSECUTIVE_FRAME_STATE;
      }
      else if((u8_gRxSTmin > 0) && (u8_gRxSTmin <= 127))
      {   
        /* Assigning Receiving rx STmin to STmin Counter */
        u8_gSTminCount = u8_gRxSTmin;

        /* Moved to Consective Frame State */
        *pen_fTxStatePtr = TX_CONSECUTIVE_FRAME_STATE;
      }
      else if((u8_gRxSTmin >= 0xF1) && (u8_gRxSTmin <= 0xF9))
      {
        /* RxSTmin equals to one */
        u8_gRxSTmin = 1;
         
        /* RxSTminCounter equals to one */
        u8_gSTminCount = 1;
        
        /* Moved to Consective Frame State */
        *pen_fTxStatePtr = TX_CONSECUTIVE_FRAME_STATE;
      }
      else
      {
        /* Moved to Consective Frame State */
        *pen_fTxStatePtr = TX_ERROR_STATE;
      }
    }
    else if(FC_WAIT == u8_gRxFC)
    {
      /* Setting  FC Timeout to zero */
      u32_gFcTimeOutCount = 0;
    }
    else if(FC_OVERFLOW == u8_gRxFC)
    {
      /* moved to success state*/
      *pen_fTxStatePtr = TX_SUCCESS_STATE;
    }
    else
    {
      /* Updated the error variable */
      en_gError = INVALID_FC_STATUS;

      /* moved to Error state*/
      *pen_fTxStatePtr = TX_ERROR_STATE;
    }
  }
  else
  {
    /* Incresing the FC time out counter */
    u32_gFcTimeOutCount = u32_gFcTimeOutCount + 1;

    /*Checking the FC timeout */
    if(u32_gFcTimeOutCount > st_gIsoTpParams.u32_mFcTimeOut)
    {
      /* Updated the error variable */
      en_gError = TIMEOUT_FC;

      /* moved to Error state*/
      *pen_fTxStatePtr = TX_ERROR_STATE;

      /* Time out Counter equals to zero */
      u32_gFcTimeOutCount = 0;
    }
    else
    {
      /* No Action */
    }
  }
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_TxConsecutiveFrameState(EN_TX_STATES_t *pen_fTxStatePtr)       */
/*                                                                                                */
/* Description     : Sending tx Consecutive Frame in this State                                   */
/*                                                                                                */
/* In Params       : EN_TX_STATES_t *pen_fTxStatePtr                                              */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_TxConsecutiveFrameState(EN_TX_STATES_t * pen_fTxStatePtr)
{
    INT8U au8_lPayLoad[8] = {0x00, };

    /* Cheking Wether RxSTmin and STminCounter equal */
    if(u8_gRxSTmin == u8_gSTminCount)
    {
        /* Assigning STmin equals to one */
        u8_gSTminCount = 0;

        /* Setting Higher nibble as a consecutive Frame */
        ISO15765_SetNibble(&au8_lPayLoad[0], CONSECUTIVE_FRAME, HIGHER);

        /* Setting Higher nibble as a Consecutive Frame */
        ISO15765_SetNibble(&au8_lPayLoad[0], u8_gConsecutiveIndex, LOWER);

        if(u16_gIsoTpTxDataSize >= 7)
        {
            /* copy the number of bytes */
            memcpy(&au8_lPayLoad[1], &au8_gIsoTpTxBuffer[u16_gIsoTpTxIndex], 7);

            /* Decresing the Tx Data Size  */
            u16_gIsoTpTxDataSize = u16_gIsoTpTxDataSize - 7;

            /* Incresing the Tx Index */
            u16_gIsoTpTxIndex = u16_gIsoTpTxIndex + 7;
        }
        else
        {
            /* copy the number of bytes */
            memcpy(&au8_lPayLoad[1], &au8_gIsoTpTxBuffer[u16_gIsoTpTxIndex], \
                                                        u16_gIsoTpTxDataSize);
            /* Incresing the Tx Index */
            u16_gIsoTpTxIndex = u16_gIsoTpTxIndex + u16_gIsoTpTxDataSize;

            /* If data is lessthan 7 bytes, after the copying data size it should be zero */
            u16_gIsoTpTxDataSize = 0;
        }

        if(0 == u16_gIsoTpTxDataSize)
        {
            /* Moved to Success state */
            *pen_fTxStatePtr = TX_SUCCESS_STATE;
        }
        else
        {
            /* No Action */
        }

        /*If ConsecutiveIndex is 15 that should be 0*/
        u8_gConsecutiveIndex = ((u8_gConsecutiveIndex + 1) % 16);

#ifdef TRACE_ENABLE

    /* Reset the buffer. */
    memset(au8_gCAN_LogBuffer,0x00,sizeof(au8_gCAN_LogBuffer));

    sprintf((char*)au8_gCAN_LogBuffer,"[%.6f] %X Tx %02d %02X %02X %02X %02X %02X %02X %02X %02X \r\n",\
                    f32_gTimeStamp,CAN_IF_REQUEST_HEADER, 8, au8_lPayLoad[0], au8_lPayLoad[1],\
                        au8_lPayLoad[2], au8_lPayLoad[3], au8_lPayLoad[4], au8_lPayLoad[5],\
                                au8_lPayLoad[6], au8_lPayLoad[7]);

    TRACE_DEBUG_WP("%s",au8_gCAN_LogBuffer);
#endif

            /* */
            CAN_IF_WriteMsg(CAN_IF_CH_0, 0, CAN_IF_OTA_REQ_HEADER, &au8_lPayLoad[0], 8);

        /*Updating the Block size conter*/
        u16_gBsCount = u16_gBsCount + 1;

        if(u16_gRxBS == u16_gBsCount)
        {
            /* Moved to the Rx flow control state */
            *pen_fTxStatePtr = RX_FLOW_CONTROL_STATE;

            /* Time out Counter is zero */
            u32_gFcTimeOutCount = 0;
        }
        else
        {
            /* No Action */
        }
    }
    else
    {
        /* Increasing the Separation time */
        u8_gSTminCount = u8_gSTminCount + 1;
    }
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_TxSuccessState(EN_TX_STATES_t *pen_fTxStatePtr)                */
/*                                                                                                */
/* Description     : In this state we can disable the txenableflag                                */
/*                                                                                                */
/* In Params       : EN_TX_STATES_t * pen_fTxStatePtr                                              */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/
INT8U u8_gSuccessCounter = 0;
void ISO15765_TxSuccessState(EN_TX_STATES_t * pen_fTxStatePtr)
{
    /*Setting Tx Flag to zero*/
    u8_gEnableTxFlag = FALSE;
    
    u8_gSuccessCounter = u8_gSuccessCounter + 1;
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_TxErrorState(EN_TX_STATES_t *pen_fTxStatePtr)                  */
/*                                                                                                */
/* Description     : In this we can disable the enabletxflag                                      */
/*                                                                                                */
/* In Params       : EN_TX_STATES_t * pen_fTxStatePtr                                              */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_TxErrorState(EN_TX_STATES_t * pen_fTxStatePtr)
{
  /*Setting Tx Flag to zero*/
  u8_gEnableTxFlag = FALSE;
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_Init(ST_ISOTP_INIT_t *pst_fInitParams)                         */
/*                                                                                                */
/* Description     : Initilization of isotp params, that variables copied into global variables   */
/*                                                                                                */
/* In Params       : ST_ISOTP_INIT_t * pst_fInitParams                                             */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_Init(ST_ISOTP_INIT_t * pst_fInitParams)
{
  /*Assining the Isotp initilization parameters*/
  st_gIsoTpParams = *pst_fInitParams;
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_UpdateCallBacks(void (*p_fRxIndication)              \         */
/*                               (INT32U, INT8U *, INT16U), void (* p_fErrorIndication)(INT8U))   */                                                                        
/*                                                                                                */
/* Description     : Updating the Rx indication and error indication functions                    */
/*                                                                                                */
/* In Params       : void (*p_fRxIndication)INT32U, INT8U *, INT16U),                \            */         
/*                                                          void (* p_fErrorIndication)(INT8U))   */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_UpdateCallBacks(void (* p_fRxIndication)(INT32U, INT8U *, INT32U), \
                                                               void (* p_fErrorIndication)(INT8U))
{
  /*Assigning the rx indication function to structure member of rx indication */
  st_gIsoTpParams.p_mRxIndication = p_fRxIndication;

  /*Assigning the Error indication function to structure member of error indication */
  st_gIsoTpParams.p_mErrorIndication = p_fErrorIndication;
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_SendData(INT32U u32_fArbitrationId,INT8U * pu8_fData,          */
/*                                                                             INT16U u16_fDlc)   */
/*                                                                                                */
/* Description     : Sending Isotp data                                                           */
/*                                                                                                */
/* In Params       : INT32U u32_fArbitrationId,INT8U *pu8_fData, INT16U u16_fDlc                  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

ISOTP_STAUS_t ISO15765_SendData(INT32U u32_fArbitrationId,INT8U * pu8_fData, INT16U u16_fDlc)
{
    /* */
    ISOTP_STAUS_t  en_lStatus = ISOTP_SUCCESS;

    /* Updated the header with given arbitration Id*/
    u32_gIsoTpTxHeader = u32_fArbitrationId;

    /* Updated the Data length */
    u16_gIsoTpTxDataSize = u16_fDlc;

    /* Copying data to Tx buffer*/
    memcpy((void *)&au8_gIsoTpTxBuffer[0], (const void *)pu8_fData, u16_gIsoTpTxDataSize);

    /* make RX Index To 0 */
    u16_gIsoTpRxIndex = 0x00;
      
    /*Updating the state*/
    en_gTxState = TX_INIT_STATE;

    /* Setting the Tx flag to one */
    u8_gEnableTxFlag = TRUE;
        
    return en_lStatus;
}

/**************************************************************************************************/
/* Function Name   : void ISO15765_SetNibble(INT8U * pu8_fDataPtr, INT8U u8_fData, \              */
/*                                                                        EN_NIBBLE_t en_fNibble) */                                                                           
/*                                                                                                */
/* Description     : Setting Particular nibble in isotp data                                      */
/*                                                                                                */
/* In Params       : INT8U * pu8_fDataPtr, INT8U u8_fData, EN_NIBBLE_t en_fNibble                 */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISO15765_SetNibble(INT8U * pu8_fDataPtr, INT8U u8_fData, EN_NIBBLE_t en_fNibble)
{
  /* Cheking whether lower nibble */
  if(LOWER == en_fNibble)
  {
    /* Update the lower nibble with given data */
    *pu8_fDataPtr |= u8_fData & 0x0F;
  }
  else
  {
    /* Update the higher nibble with given data */
    *pu8_fDataPtr |= (u8_fData << 4) & 0xF0;
  }
}

/**************************************************************************************************/
/* Function Name   : INT8U ISO15765_GetNibble(INT8U u8_fData, EN_NIBBLE_t en_fNibble)             */
/*                                                                                                */
/* Description     : Getting Particular nibble Value in isotp data                                */
/*                                                                                                */
/* In Params       : INT8U u8_fData, EN_NIBBLE_t en_fNibble                                       */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : INT8U                                                                        */
/**************************************************************************************************/

INT8U ISO15765_GetNibble(INT8U u8_fData, EN_NIBBLE_t en_fNibble)
{
  INT8U u8_lResult = 0;

  if(LOWER == en_fNibble)
  {
    /* Return the Lower nibble value */ 
    u8_lResult = u8_fData & 0x0F;
  }
  else
  {
    /* Return the Higher nibble value */ 
    u8_lResult = (u8_fData >> 4) & 0x0F;
  }

  return u8_lResult;
}

/**************************************************************************************************/
/* End of  ISO15765_2.c                                                                           */
/**************************************************************************************************/
