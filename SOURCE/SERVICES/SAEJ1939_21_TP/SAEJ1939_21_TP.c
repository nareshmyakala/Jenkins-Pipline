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
/* \File Name   : SAEJ1939_21_TP.c                                                                */
/* \Author      : A.Prashanth                                                                     */
/* \Version 	:                                                                                 */
/* \Date        : 18-10-2017                                                                      */
/*                                                                                                */
/* @Description : SAEJ1939_21 TP frame work                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "DATACONV.h"

#include "ISOTPQ_public.h"
#include "ISO15765_2.h"
#include "XTP_SAEJ1939_public.h"

#include "XTP_public.h"
//#include "HAL_CAN_public.h"

#include "PLATFORM.h"

#include "SAEJ1939_21_TP_public.h"
#include "SAEJ1939_21_TP_private.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

#define J1939_DEFAULT_HEADER        0x18EAFFF9
#define J1939_DEFAULT_CTS_HEADER    0x1CEC00F9

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Global variable for default Send Header */
INT32U u32_gJ1939Header = J1939_DEFAULT_HEADER;

/* Global variable for default CTS Header */
INT32U u32_gJ1939CTSHeader = J1939_DEFAULT_CTS_HEADER;

/* Global variable for default CTS Header */
INT32U u32_gJ1939RTSHeader = J1939_DEFAULT_RTS_HEADER;

/* Global variable for default RTS Header */
INT32U u32_gDataHeader = J1939_DEFAULT_DATA_HEADER;

/* Global variable for default NM Header */
INT32U u32_gNMheader = J1939_DEFAULT_NM_HEADER;

/* Global variable for PDU format */
INT8U volatile u8_gJ1939_PF = 0x00;

/* Global variable for PDU specific */
INT8U volatile u8_gJ1939_PS = 0x00;

/* Global variable for PDU format */
INT8U u8_gTP_J1939_PF = 0x00;
INT8U u8_gTP_J1939_PS = 0x00;

/* Global variable for Monitor PF */
INT8U u8_gJ1939_MPF = 0x00;

/* Global variable for Monitor PS */
INT8U u8_gJ1939_MPS = 0x00;

/* Global variable for Expected Packets */
INT8U u8_J1939_ExptPkts = 0x00;

/* Global variable for Total message size */
INT16U u16_gJ1939TotalBytes = 0x00;

/* Global variable to store Next CTS to send  */
INT8U u8_j1939_NextCTS = 0x00;

/* Global variable for Received packets */
INT8U u8_gRcvdPkts = 0x00;

/* Global variable for Rx timeout counter */
INT32U u32_gJ1939RxTimeOutCnt = 0x00;

/* Global variable to conform data reception */
INT8U  u8_gJ1939IsRxRcvd = 1;

/* Global request sent flag */
INT8U u8_gJ1939RqstSent = 0x00;

/* Global Multi request flag */
INT8U u8_gJ1939MultiRqst = 0x00; 

/* Multipacket Handlig */
INT8U u8_gMaxPacktstoSend = 0x00;
INT8U u8_gCTS_Received_Flag = 0x00;
INT8U u8_gSequence_Number = 0x00;

/* Global variable to conform CM message */
INT8U u8_gJ1939CMMsgRcvd = 0x00;

/* Global variable for Rx timeout flag */
INT8U u8_J1939RxTimeOutFlag = 0x00;
INT32U u32_gJ1939RxMonitrTimeOutFlag = 0x00;
INT32U u32_gJ1939RxMonitrTimeOutCntr = 0x00;

/* Global variable to store source address */
INT32U u32_gRTSSorce_Addrs = 0x00;

/* Make the Flag 0 initially for number of frames*/
INT8U u8_gMntrPGN_N_timesFlag = 0x00;
INT8U u8_gMntrPGN_N_Frames = 0x00;
INT8U u8_gSAEJ1939MtntlAllPGN = 0x00;
INT8U u8_gJ1939SnglPGNMntr = 0x00;

/* */
INT8U u8_gCM_BAM_Flag = 0x00;

/* */
INT8U u8_gTP_PGN[3] = {0x00,};

INT8U u8_gPGN_Flag = 0x01;
INT8U u8_gSPN_Flag = 0x00;
/* Default CTS message data field */
INT8U au8_gJ1939_CTS_Msg[8] = {0x11, 0xFF, 0x01,0xFF,0xFF, 0xFF, 0xFF, 0x00};

/* Default end of message data field */
INT8U au8_gJ939_END_ACK_Msg[8] = {0x13, 0xFF, 0xFF,0xFF,0xFF, 0xFF, 0xFF, 0x00};

INT8U u8_gSentPackets  = 0x00;
 
INT8U au8_gSorceAdress[5] = {0x00, };
INT8U u8_gSorceAdressIndx = 0x00;
INT8U u8_RecverSorceAdrs = 0x00;
INT8U u8_gSentFlag = 0x00;

/**************************************************************************************************/
/* Function Name   :  void J1939_Timer(void)                                                      */
/*                                                                                                */
/* Description     :  This is Function used to Incremet the J1939 Counter                         */
/*                                                                                                */
/* In Params       :  None                                                                        */
/*                                                                                                */
/* Out Params      :  None                                                                        */
/*                                                                                                */
/* Return Value    :  None                                                                        */
/**************************************************************************************************/

void J1939_Timer(void)
{  
    /* Checking request sent */
    if(1 == u8_gJ1939RqstSent)
    {        
        /* Incrementing RX timeout Counter */
        u32_gJ1939RxTimeOutCnt = u32_gJ1939RxTimeOutCnt + 1;
            
        /* Checking whether Rx received or not */
        if(0 == u8_gJ1939IsRxRcvd)
        {
            /* checking Rx timeout counter greater than 200 ms */
            if(u32_gJ1939RxTimeOutCnt >= 1250)
            {
                /* setting timeout flag */
                u8_J1939RxTimeOutFlag = 1;
            }
            else
            {
                /* No Action */
            }
        }
        else
        {
            /* No action */
        }
    }
    if(1 == u32_gJ1939RxMonitrTimeOutFlag)
    {
        /* Incrment the Counter for No data msg */
        u32_gJ1939RxMonitrTimeOutCntr = u32_gJ1939RxMonitrTimeOutCntr + 1;
        
         /* checking Rx timeout counter greater than 200 ms */
        if(u32_gJ1939RxMonitrTimeOutCntr >= 5000)
        {
            /* setting timeout flag */
            u8_J1939RxTimeOutFlag = 1;
        }
        else
        {
            /* No Action */
        }
    }
}

/**************************************************************************************************/
/* Function Name   :  void J1939_RxMsgHandler(void * p_fRxData)                                   */
/*                                                                                                */
/* Description     :  THis is function used as Can Rx Msg Handler for J1939                       */
/*                                                                                                */
/* In Params       :  void * p_fRxData)                                                           */
/*                                                                                                */
/* Out Params      :  None                                                                        */
/*                                                                                                */
/* Return Value    :  None                                                                        */
/**************************************************************************************************/

void J1939_RxMsgHandler(void * p_fRxData)
{  
    /* Local variable to store Received PDU format */
    INT8U u8_lJ1939_PF = 0x00;
    
    /* Local variable to store Received PDU specific */
    INT8U u8_lJ1939_PS = 0x00;
    
    ST_ISOTP_DATA_t st_lIsoRxData,st_lIsoRxData1;
    
    /* Copy to Local Object*/
    memcpy((void *)&st_lIsoRxData, (const void *)p_fRxData, sizeof(ST_ISOTP_DATA_t));
    
    /* Assigning PF to Local variable */
    u8_lJ1939_PF  = (st_lIsoRxData.u32_mCanId & 0x00FF0000) >> 16;
    
    /* Assigning PS to Local variable */   
    u8_lJ1939_PS  = (st_lIsoRxData.u32_mCanId & 0x0000FF00) >> 8;
    
    if(1 == u8_gSAEJ1939MtntlAllPGN)
    {
        /* If Data is received make counter to zero */
        u32_gJ1939RxMonitrTimeOutCntr = 0x00;

        /*  Write the data into queue */
        ISOTPQ_WriteMsg((const ST_ISOTP_DATA_t *)&st_lIsoRxData);
    }   
    else if(1 == u8_gMntrPGN_N_timesFlag)
    {
        /* Checking sent PGN(PF and PS) and RX timeout counter */
        if(((u8_lJ1939_PF == u8_gJ1939_MPF  && (u8_lJ1939_PS == u8_gJ1939_MPS))))
        {
            /* */
            //st_lIsoRxData.RxFrameType  = EN_SIGLE_FRAME;  
            
            /* If Data is received make counter to zero */
            u32_gJ1939RxMonitrTimeOutCntr = 0x00;
            
            if(u8_gMntrPGN_N_Frames > 0)
            {
                /*  Write the data into queue */
                ISOTPQ_WriteMsg((const ST_ISOTP_DATA_t *)&st_lIsoRxData);  
            }
            else
            {
                /* Make the Flag to Zero*/
                u8_gMntrPGN_N_timesFlag = 0x00;
                u8_gMntrPGN_N_Frames = 0x00;

                /* */
                u32_gJ1939RxMonitrTimeOutFlag = 0x00;

                /* If Data is received make counter to zero */
                u32_gJ1939RxMonitrTimeOutCntr = 0x00;

                /* Display no data */
                p_gXT_ReqComplete((INT8U *)"\r\n#", 3);
              
            }
            /* Deacrese the Number of Frame Count*/
            u8_gMntrPGN_N_Frames = u8_gMntrPGN_N_Frames -1;
        }
    }
    else if(1 == u8_gJ1939SnglPGNMntr)
    {
        /* Checking sent PGN(PF and PS) and RX timeout counter */
        if(((u8_lJ1939_PF == u8_gJ1939_MPF  && (u8_lJ1939_PS == u8_gJ1939_MPS))))
        {

            //st_lIsoRxData.RxFrameType  = EN_SIGLE_FRAME;  

            /* If Data is received make counter to zero */
            u32_gJ1939RxMonitrTimeOutCntr = 0x00;

            /*  Write the data into queue */
            ISOTPQ_WriteMsg((const ST_ISOTP_DATA_t *)&st_lIsoRxData);  
        }      
    }   
    else
    {
        /* Checking sent PGN(PF and PS) and RX timeout counter */
        if(((u8_lJ1939_PF == u8_gJ1939_PF  && (u8_lJ1939_PS == u8_gJ1939_PS)) && \
                                                                  (u32_gJ1939RxTimeOutCnt <= 1250)))
        {
          
              u8_RecverSorceAdrs = st_lIsoRxData.u32_mCanId & 0x000000FF; 
              au8_gSorceAdress[u8_gSorceAdressIndx] = u8_RecverSorceAdrs;
              u8_gSorceAdressIndx = u8_gSorceAdressIndx + 1;
                
              
            for(int i = 0; i<5 ;i++)
            {
                  if(au8_gSorceAdress[i] != u8_RecverSorceAdrs)
                  {
                      u8_gSentFlag = 0x01;
                  }
            }
            
            if(0x01 == u8_gSentFlag)
            {
              
                u8_gSentFlag = 0x00;
                
                /* clearing Rx timeout counter */
                u32_gJ1939RxTimeOutCnt = 0x00;
                
                /* set Data Reception flag */
                //u8_gJ1939IsRxRcvd = 1;
                
                //st_lIsoRxData.RxFrameType  = EN_SIGLE_FRAME;  
                
                /*  Write the data into queue */
                ISOTPQ_WriteMsg((const ST_ISOTP_DATA_t *)&st_lIsoRxData); 
            }
            else
            {
               u8_gJ1939IsRxRcvd = 1;
            }
        
        }
        else if((u8_lJ1939_PF == u8_gJ1939_PF) && (((u8_lJ1939_PF <= 240)  && (u8_lJ1939_PS == 0xF9)) && (u32_gJ1939RxTimeOutCnt <= 1250)))
        {
             u8_RecverSorceAdrs = st_lIsoRxData.u32_mCanId & 0x000000FF; 
              au8_gSorceAdress[u8_gSorceAdressIndx] = u8_RecverSorceAdrs;
              
            for(int i = 0; i<5 ;i++)
            {
                  if(au8_gSorceAdress[i] != u8_RecverSorceAdrs)
                  {
                      u8_gSentFlag = 0x01;
                  }
            }
            
            if(0x01 == u8_gSentFlag)
            {
              
                u8_gSentFlag = 0x00;
                
                /* clearing Rx timeout counter */
                u32_gJ1939RxTimeOutCnt = 0x00;
                
                /* set Data Reception flag */
                //u8_gJ1939IsRxRcvd = 1;
                
                //st_lIsoRxData.RxFrameType  = EN_SIGLE_FRAME;  
                
                /*  Write the data into queue */
                ISOTPQ_WriteMsg((const ST_ISOTP_DATA_t *)&st_lIsoRxData); 
            }
            else
            {
               u8_gJ1939IsRxRcvd = 1;
            }
                        
        }
        else if((u8_lJ1939_PF == 0x93)  && (u32_gJ1939RxTimeOutCnt <= 1250))
        {
            /* Checking request sent */
            //if(1 == u8_gJ1939RqstSent)
            {
                /* clearing Rx timeout counter */
                u32_gJ1939RxTimeOutCnt = 0x00;

                /* set Data Reception flag */
                u8_gJ1939IsRxRcvd = 1;

                //st_lIsoRxData.RxFrameType  = EN_SIGLE_FRAME;  

                /*  Write the data into queue */
                ISOTPQ_WriteMsg((const ST_ISOTP_DATA_t *)&st_lIsoRxData); 
            }
        }
        else 
        {
            /* Condition to check whether the message received is in BAM or CM mode */
            switch(u8_lJ1939_PF)
            {
              
            /* BAM transmission */
            case J1939_BAM_CM_PACKET:
                {
                    /* Checking sent PGN(PF and PS) and RX timeout counter */
                    if(((u8_gJ1939_PF == st_lIsoRxData.au8_mData[6]  && \
                            (u8_gJ1939_PS == st_lIsoRxData.au8_mData[5])) && (u32_gJ1939RxTimeOutCnt <= 1250)))
                    {
                      
                        if(u8_gTP_J1939_PF == st_lIsoRxData.au8_mData[6] && u8_gTP_J1939_PS == st_lIsoRxData.au8_mData[5])
                        {
                            /* Copy to Local Object*/
                            memcpy((void *)&st_lIsoRxData1, (const void *)p_fRxData, sizeof(ST_ISOTP_DATA_t));
                        }
                        /* Clear Rx Timeout counter */
                        u32_gJ1939RxTimeOutCnt = 0x00;
                        u8_J1939RxTimeOutFlag = 0x00;

                        /* Checking BAM message with fixed control byte */
                        if(0x20 == st_lIsoRxData.au8_mData[0])
                        {
                            /* Checking request sent */
                            if(1 == u8_gJ1939RqstSent)
                            {   
                                /* Set multirequest flag */
                                u8_gJ1939MultiRqst = 1;
                                
                                /* Storing number of expected packets */
                                u8_J1939_ExptPkts = u8_J1939_ExptPkts + st_lIsoRxData.au8_mData[3];
                                
                                /* Update the frame type */
                                //st_lIsoRxData.RxFrameType  = EN_FIRST_FRAME; 
                                
                                /* Write data to queue */
                                ISOTPQ_WriteMsg((const ST_ISOTP_DATA_t *)&st_lIsoRxData);                
                            }                
                            else
                            {
                                /* No Action */
                            }
                        }
                        /* Checking RTS message */
                        else if(0x10 == st_lIsoRxData.au8_mData[0])
                        {
                            /* Checking request sent */
                            if(1 == u8_gJ1939RqstSent)
                            {
                                /* Set multirequest flag */ 
                                u8_gJ1939MultiRqst = 1;
                                
                                /* Set CM message reception flag */
                                u8_gJ1939CMMsgRcvd = 1;
                                
                                /* Message size */
                                u16_gJ1939TotalBytes = st_lIsoRxData.au8_mData[1];
                                u16_gJ1939TotalBytes |= st_lIsoRxData.au8_mData[2] << 8;                         
                                
                                /* Storing number of expected packets */
                                u8_J1939_ExptPkts = u8_J1939_ExptPkts + st_lIsoRxData.au8_mData[3];
                                
                                /* storing when to send next CTS, packet number */
                                u8_j1939_NextCTS = st_lIsoRxData.au8_mData[5];
                                
                                /* Setting CTS frame */
                                au8_gJ1939_CTS_Msg[1] = st_lIsoRxData.au8_mData[4];
                                au8_gJ1939_CTS_Msg[5] = u8_gJ1939_PS;
                                au8_gJ1939_CTS_Msg[6] = u8_gJ1939_PF;   
                                
                                /* Send CTS Message */
                                u32_gJ1939CTSHeader &= ~(0x0000FF00);
                                
                                /* Storing store address */
                                u32_gRTSSorce_Addrs = (st_lIsoRxData.u32_mCanId & 0x000000FF);
                                
                                /* Setting CTS header */
                                u32_gJ1939CTSHeader |=  u32_gRTSSorce_Addrs << 8;
                                
                                /* checking Rx Timeout counter */
                                if(u32_gJ1939RxTimeOutCnt <= 200)
                                {
                                  //HAL_CAN_TxMsg(u32_gJ1939CTSHeader, &au8_gJ1939_CTS_Msg[0], 8);  
                                }
                                
                              // st_lIsoRxData.RxFrameType  = EN_FIRST_FRAME;    
                                
                                /* Write data into queue */
                                ISOTPQ_WriteMsg((const ST_ISOTP_DATA_t *)&st_lIsoRxData);
                            }                    
                        }
                        else if(0x11 == st_lIsoRxData1.au8_mData[0])
                        {
                            /* Make the Flag to 1 */
                            u8_gCTS_Received_Flag = 0x01;  
                            
                            /* */
                            //st_lIsoRxData.RxFrameType  = EN_SIGLE_FRAME;  
                            
                            /* Setting message received flag */
                            u8_gJ1939IsRxRcvd = 1;

                            /* */
                            u8_gMaxPacktstoSend = st_lIsoRxData1.au8_mData[1];
                            u8_gSequence_Number = st_lIsoRxData1.au8_mData[2];

                            /* */
                            u32_gDataHeader &= 0xFFFF00FF;

                            /* */
                            u32_gDataHeader |= (((st_lIsoRxData.u32_mCanId) & 0x000000FF) << 8);
 
                            /* Write message into queue */
                             //ISOTPQ_WriteMsg((const ISO_RxData_t *)&st_lIsoRxData);   
                            J1939_DISPLAY(&st_lIsoRxData1);
                            
                            /* Display prompt */
                            p_gXT_ReqComplete((INT8U *)"\r\n#", 3);
                            
                            /* clear timeout counter  */
                            u32_gJ1939RxTimeOutCnt = 0x00; 
                        }
                        else if( J1939_CM_ACK_PACKET == st_lIsoRxData1.au8_mData[0])
                        {
                            /* Checking PGN(PF and PS) and timeout */
                            if((u8_gJ1939_PF == st_lIsoRxData1.au8_mData[6]  && \
                            (u8_gJ1939_PS == st_lIsoRxData1.au8_mData[5]) && (u32_gJ1939RxTimeOutCnt <= 1250)))
                            {

                                /* Setting message received flag */
                                u8_gJ1939IsRxRcvd = 1; 
                                    
                                 u8_gTP_J1939_PS = 0x00;
                                 u8_gTP_J1939_PF = 0x00;
                                  u8_gSentPackets = st_lIsoRxData1.au8_mData[3];
                                  
                                /* Write message into queue */
                                 J1939_DISPLAY(&st_lIsoRxData1);
                                 
                                 /* Display prompt */
                                 p_gXT_ReqComplete((INT8U *)"\r\n#", 3);
                                //ISOTPQ_WriteMsg((const ISO_RxData_t *)&st_lIsoRxData1); 
                                 
                                  /* */
                                u32_gJ1939RxTimeOutCnt = 0x00;
                                u32_gJ1939RxMonitrTimeOutCntr = 0x00;

                            }
                        }
                        else
                        {
                            /* No action */
                        }
                    }
                }
                break;
                
            case J1939_DATA_PACKET:
                {   
                    /* Checking Multi request and timeout */
                    if (((1 == u8_gJ1939MultiRqst) && (u8_gRcvdPkts <= u8_J1939_ExptPkts)) && (u32_gJ1939RxTimeOutCnt <= 750))
                    {

                        /* Clear timeout counter */
                        u32_gJ1939RxTimeOutCnt = 0x00;
                        
                        /* Update the received packets */
                        u8_gRcvdPkts = u8_gRcvdPkts + 1;
                        
                        /* Checking CM message received or not */
                        if(1 == u8_gJ1939CMMsgRcvd)
                        {
                            if(u8_gRcvdPkts >= u8_j1939_NextCTS)
                            {       
                                /* Setting CTS frame */
                                au8_gJ1939_CTS_Msg[1] = u8_j1939_NextCTS;
                                au8_gJ1939_CTS_Msg[2] = u8_gRcvdPkts + 1;
                                au8_gJ1939_CTS_Msg[5] = u8_gJ1939_PS;
                                au8_gJ1939_CTS_Msg[6] = u8_gJ1939_PF;
                                
                                /* Setting CTS header */
                                u32_gJ1939CTSHeader &= ~(0x0000FFFF);
                                u32_gJ1939CTSHeader |= ( 0x0000FFFF & u32_gJ1939Header);
                                
                                /* Transmit CTS header and CTS message */
                                //HAL_CAN_TxMsg(u32_gJ1939CTSHeader, &au8_gJ1939_CTS_Msg[0], 8);
                                
                                /* clear received packets flag */
                                u8_gRcvdPkts = 0x00;
                                
                                /* Update the expected packets */
                                u8_J1939_ExptPkts = u8_J1939_ExptPkts - u8_gRcvdPkts;
                            }
                            
                            /* Check whether number of received packets is equal to expected packets or not */
                            if(u8_gRcvdPkts == u8_J1939_ExptPkts)
                            {
                                /* clear CM message received flag */
                                u8_gJ1939CMMsgRcvd = 0x00;

                                /* Setting message received flag */
                                u8_gJ1939IsRxRcvd = 1;
                                
                                /* Send end of message ACK */
                                au8_gJ939_END_ACK_Msg[1] = (u16_gJ1939TotalBytes & 0xFF);
                                
                                au8_gJ939_END_ACK_Msg[2] = (u16_gJ1939TotalBytes >> 8) & 0xFF;
                                
                                au8_gJ939_END_ACK_Msg[3] = u8_gRcvdPkts;
                                
                                au8_gJ939_END_ACK_Msg[5] = u8_gJ1939_PS;
                                
                                au8_gJ939_END_ACK_Msg[6] = u8_gJ1939_PF; 
                                
                                /* Send CTS Message */
                                u32_gJ1939CTSHeader &= ~(0x0000FF00);
                                
                                /* Storing RTS source address */
                                u32_gRTSSorce_Addrs = (st_lIsoRxData.u32_mCanId & 0x000000FF);
                                
                                /* Placing RTS source address in CTS destination address */
                                u32_gJ1939CTSHeader |=  u32_gRTSSorce_Addrs << 8;
                                
                                /* Transmit CTS header and CTS message */
                               // HAL_CAN_TxMsg(u32_gJ1939CTSHeader, &au8_gJ939_END_ACK_Msg[0], 8);
                                
                                u8_gJ1939MultiRqst = 0x00;
                                
                                u8_gRcvdPkts = 0x00;
                                u8_J1939_ExptPkts = 0x00;
                            } 
                        }
                        
                        else if(u8_gRcvdPkts == u8_J1939_ExptPkts)
                        {
                            /* Setting message received flag */
                            u8_gJ1939IsRxRcvd = 1;
                            u8_gJ1939MultiRqst = 0x00;
                            u8_gRcvdPkts = 0x00;
                            u8_J1939_ExptPkts = 0x00;
                        }
                        else
                        {
                            /* No Action */
                        }
                        
                        /* Write message into queue */
                        //st_lIsoRxData.RxFrameType = EN_CONSECUTIVE_FRAME;   
                        ISOTPQ_WriteMsg((const ST_ISOTP_DATA_t *)&st_lIsoRxData);
                    }
                    else
                    {
                        /* No action */
                    }                      
                }
                break;
                
            case J1939_ACK_NACK_PACKET:
              {     
                    /* Checking PGN(PF and PS) and timeout */
                    if((u8_gJ1939_PF == st_lIsoRxData.au8_mData[6]  && \
                              (u8_gJ1939_PS == st_lIsoRxData.au8_mData[5]) && (u32_gJ1939RxTimeOutCnt <= 1250)))
                    {
                          /* Checking request sent flag */
                          if(1 == u8_gJ1939RqstSent)
                          {
                              /* clear timeout counter  */
                              u32_gJ1939RxTimeOutCnt = 0x00;
                              
                              /* */
                              u32_gJ1939RxTimeOutCnt = 0x00;
                              
                              /* Setting message received flag */
                             // u8_gJ1939IsRxRcvd = 1;
                              
                             // st_lIsoRxData.RxFrameType  = EN_SIGLE_FRAME;  
                              
                              /* Write message into queue */
                              ISOTPQ_WriteMsg((const ST_ISOTP_DATA_t *)&st_lIsoRxData);                        
                          }
                    }
                    else
                    {
                         u8_gJ1939IsRxRcvd = 1;
                    }
              }
              break;
              
            default:
                {
                    /* set Data Reception flag */
                    //u8_gJ1939_PF =0x00;
                    //u8_lJ1939_PS = 0x00;
                    
                    //if(1 != u8_gJ1939MultiRqst)
                    {
                        //u8_gJ1939IsRxRcvd = 1;
                    }
                }
                break;
            }
        } 
   }    
}

/**************************************************************************************************/
/* Function Name   :  void J1939_TxConformation(void * p_fRxData)                                  */
/*                                                                                                */
/* Description     :  THis is function used as Can Rx Msg Handler for J1939                       */
/*                                                                                                */
/* In Params       :  void * p_fRxData)                                                           */
/*                                                                                                */
/* Out Params      :  None                                                                        */
/*                                                                                                */
/* Return Value    :  None                                                                        */
/**************************************************************************************************/

void J1939_TxConformation(INT32U u32_fMBnumber)
{
  
}

/**************************************************************************************************/
/* Function Name   :  void J1939_DISPLAY(ST_J1939_HEADER_t * p_fJ1939DisplayData)                 */
/*                                                                                                */
/* Description     :  This function is used to Display J1939 Data to User                         */
/*                                                                                                */
/* In Params       :  SISO_RxData_t * p_fCanDispData                                              */
/*                                                                                                */
/* Out Params      :  None                                                                        */
/*                                                                                                */
/* Return Value    :  None                                                                        */
/**************************************************************************************************/

void J1939_DISPLAY(ST_ISOTP_DATA_t * p_fCanDispData)
{
    /* To Hold Arbitaration Buffer */
    INT8U au8_lDisplayBuff[64] = {0,};	
    INT8U u8_lIndex = 0;
    
    /* Local variable for storing Priority */
    INT8U u8_lJ1939Priority = 0x00;
    
    /* Local variable for storing PGN */
    INT16U u16_lJ1939PGN = 0x00;
    
    /* Local variable for storing source address */
    INT8U u8_lJ1939SourcAdd = 0x00;
    
    /* Local variable for storing DLC */
    INT16U u16_lLength = 0x00;
    
    INT8U u8_lFrameIndex = 0x00;
    INT8U au8_lTemp[2] = {0x00, };
    
    /* Local variable for storing index buffer */
    INT8U u8_lBuffIndex = 0x00;
    
    /* Check for Response Flag */
    if(1 == u8_gResponseFlag)
    {
         if(1 == u8_gIctSpaceFlag)
         {         
            /* Check For Header ON*/
            if(1 == u8_gHeaderFlag)
            {
                /* Assigning priority to local variable */
                u8_lJ1939Priority =  (p_fCanDispData->u32_mCanId & 0x1C000000) >> 26;
                
                /* Convert The Target Address to PAN Format */
                COMMON_Byte2PAN(&au8_lDisplayBuff[u8_lBuffIndex], u8_lJ1939Priority);
                u8_lBuffIndex = u8_lBuffIndex + 2;
                
                /* Display space */
                au8_lDisplayBuff[u8_lBuffIndex] = ' ';
                u8_lBuffIndex = u8_lBuffIndex + 1;
                
                /* Display zero */
                au8_lDisplayBuff[u8_lBuffIndex] = '0';
                u8_lBuffIndex = u8_lBuffIndex + 1;
                
                /* Assigning PGN to Local variable */
                u16_lJ1939PGN =  (p_fCanDispData->u32_mCanId & 0x00FFFF00) >> 8;
                
                /* Convert the PGN to PAN */
                COMMON_HWord2PAN(&au8_lDisplayBuff[u8_lBuffIndex], u16_lJ1939PGN);
                u8_lBuffIndex = u8_lBuffIndex + 4;

                au8_lDisplayBuff[u8_lBuffIndex] = ' ';
                u8_lBuffIndex = u8_lBuffIndex + 1;
                
                /* Assigning source address to local variable */
                u8_lJ1939SourcAdd =  (p_fCanDispData->u32_mCanId & 0x000000FF);
                
                /* convert the source address to PAN */
                COMMON_Byte2PAN(&au8_lDisplayBuff[u8_lBuffIndex], u8_lJ1939SourcAdd);
                u8_lBuffIndex = u8_lBuffIndex + 2; 
                
                au8_lDisplayBuff[u8_lBuffIndex] = ' ';
                u8_lBuffIndex = u8_lBuffIndex + 1;                
                
                if(1 == u8_gDLCFlag)
                {
                     /* Convert The Target Address to PAN Format */
                   COMMON_Byte2PAN(&au8_lDisplayBuff[u8_lBuffIndex], p_fCanDispData->u8_mDLC);
                   u8_lBuffIndex = u8_lBuffIndex + 2;
                   
                   au8_lDisplayBuff[u8_lBuffIndex] = ' ';
                   u8_lBuffIndex = u8_lBuffIndex + 1;
                }
                else
                {
                    /* No Action */
                }
                
                /* Display Data */
                for(u8_lIndex = 0; u8_lIndex < p_fCanDispData->u8_mDLC; u8_lIndex++)
                {
                   /* Convert The Target Address to PAN Format */
                   COMMON_Byte2PAN(&au8_lDisplayBuff[u8_lBuffIndex], p_fCanDispData->au8_mData[u8_lIndex]);
                   u8_lBuffIndex = u8_lBuffIndex + 2;
                    
                   au8_lDisplayBuff[u8_lBuffIndex] = ' ';                  
                   u8_lBuffIndex = u8_lBuffIndex + 1;                   
                }
                
                /* Append to CRLF to the User Response Data */
                strcat((char *)&au8_lDisplayBuff[u8_lBuffIndex], "\r\n");
                u8_lBuffIndex = u8_lBuffIndex + 2;  
            }
            else
            {
                /* Heeader Flag is Disabled */
                switch(EN_SIGLE_FRAME)
                {
                    case EN_SIGLE_FRAME :
                    {                        
                        for(u8_lIndex = 0; u8_lIndex < p_fCanDispData->u8_mDLC; u8_lIndex++)
                        {
                            /* Convert The Target Address to PAN Format */
                            COMMON_Byte2PAN(&au8_lDisplayBuff[u8_lBuffIndex], \
                                                              p_fCanDispData->au8_mData[u8_lIndex]);
                            u8_lBuffIndex = u8_lBuffIndex + 2;
                            
                            au8_lDisplayBuff[u8_lBuffIndex] = ' ';
                            u8_lBuffIndex = u8_lBuffIndex + 1;                                                            
                        }
                        /* Append to CRLF to the User Response Data */
                        strcat((char *)&au8_lDisplayBuff[u8_lBuffIndex], "\r\n");
                        u8_lBuffIndex = u8_lBuffIndex + 2;   
                    }
                    break;
                    
                    case EN_FIRST_FRAME :
                    {           
                        /* Copy the length */
                        u16_lLength = p_fCanDispData->au8_mData[1];
                        u16_lLength |= p_fCanDispData->au8_mData[2];
 
                        /* Display the length Byte */
                        COMMON_HWord2PAN(&au8_lDisplayBuff[u8_lBuffIndex], u16_lLength);
                         
                        /* Incrementing buffer index */
                        u8_lBuffIndex = u8_lBuffIndex + 4;                                        

                        au8_lDisplayBuff[u8_lBuffIndex] = '\n'; 
                        u8_lBuffIndex = u8_lBuffIndex + 1; 
                    }
                    break;
                        
                    case EN_CONSECUTIVE_FRAME :
                    {
                        /* Copy the frame index */
                        u8_lFrameIndex = p_fCanDispData->au8_mData[0];
                        
                        COMMON_Byte2PAN(&au8_lTemp[u8_lBuffIndex], u8_lFrameIndex);
                        
                        sprintf((char *)&au8_lDisplayBuff[u8_lBuffIndex], "%c%c:", \
                                                                        au8_lTemp[0], au8_lTemp[1]);                       

                        u8_lBuffIndex = u8_lBuffIndex + 3;

                        au8_lDisplayBuff[u8_lBuffIndex] = ' ';
                        u8_lBuffIndex = u8_lBuffIndex + 1;
                            
                        for(u8_lIndex = 0; u8_lIndex < 7 ; u8_lIndex++)
                        {
                            /* Convert The Target Address to PAN Format */
                            COMMON_Byte2PAN(&au8_lDisplayBuff[u8_lBuffIndex], \
                                                          p_fCanDispData->au8_mData[u8_lIndex + 1]);
                            u8_lBuffIndex = u8_lBuffIndex + 2;

                            au8_lDisplayBuff[u8_lBuffIndex] = ' ';
                            u8_lBuffIndex = u8_lBuffIndex + 1;                                    
                        }

                        au8_lDisplayBuff[u8_lBuffIndex] = '\n'; 
                        u8_lBuffIndex = u8_lBuffIndex + 1; 
                    }
                    break;
                    
                    default :
                    break;
                }
            }              
         }
         else
         {
            /* Check For Header ON*/
            if(1 == u8_gHeaderFlag)
            {
                /* Convert The Target Address to PAN Format */
                COMMON_Word2PAN(&au8_lDisplayBuff[u8_lBuffIndex], \
                                                              p_fCanDispData->u32_mCanId);
                u8_lBuffIndex = u8_lBuffIndex + 8;
                
                if(1 == u8_gDLCFlag)
                {
                    /* Convert The Target Address to PAN Format */
                   COMMON_Byte2PAN(&au8_lDisplayBuff[u8_lBuffIndex], p_fCanDispData->u8_mDLC);
                   u8_lBuffIndex = u8_lBuffIndex + 2;
                }
                else
                {
                    /* No Action */
                }
                
                for(u8_lIndex = 0; u8_lIndex < p_fCanDispData->u8_mDLC; u8_lIndex++)
                {
                    /* Convert The Target Address to PAN Format */
                    COMMON_Byte2PAN(&au8_lDisplayBuff[u8_lBuffIndex], \
                      
                                                              p_fCanDispData->au8_mData[u8_lIndex]);
                    u8_lBuffIndex = u8_lBuffIndex + 1;                 
                }
                
                /* Append to CRLF to the User Response Data */
                strcat((char *)&au8_lDisplayBuff[u8_lBuffIndex], "\r\n");
                u8_lBuffIndex = u8_lBuffIndex + 2;
            }
            else
            {
                /* Heeader Flag is Disabled */
                switch(EN_SIGLE_FRAME)
                {
                    case EN_SIGLE_FRAME :
                    {                        
                        for(u8_lIndex = 0; u8_lIndex < p_fCanDispData->u8_mDLC; u8_lIndex++)
                        {
                            /* Convert The Target Address to PAN Format */
                           COMMON_Byte2PAN(&au8_lDisplayBuff[u8_lBuffIndex], \
                                                              p_fCanDispData->au8_mData[u8_lIndex]);
                           u8_lBuffIndex = u8_lBuffIndex + 2;                                                   
                        }
                        strcat((char *)&au8_lDisplayBuff[u8_lBuffIndex], "\r\n");
                        u8_lBuffIndex = u8_lBuffIndex + 2;
                    }
                    break;
                    
                    case EN_FIRST_FRAME :
                    {
                        u16_lLength = p_fCanDispData->au8_mData[1];
                        u16_lLength |= p_fCanDispData->au8_mData[2];
 
                        /* Display the length Byte */
                        COMMON_HWord2PAN(&au8_lDisplayBuff[u8_lBuffIndex], u16_lLength);
                        
                        u8_lBuffIndex = u8_lBuffIndex + 4;
                        
                        au8_lDisplayBuff[u8_lBuffIndex] = '\n';
                        u8_lBuffIndex = u8_lBuffIndex + 1;
                    }
                    break;
                    
                    case EN_CONSECUTIVE_FRAME :
                    {
                        u8_lFrameIndex = p_fCanDispData->au8_mData[0];
                        
                        COMMON_Byte2PAN(&au8_lTemp[u8_lBuffIndex], u8_lFrameIndex);
                        
                        sprintf((char *)&au8_lDisplayBuff[u8_lBuffIndex], "%c%c:", au8_lTemp[0], \
                                                                                      au8_lTemp[1]);
                        
                        u8_lBuffIndex = u8_lBuffIndex + 3;
                        
                        for(u8_lIndex = 0; u8_lIndex < 7 ; u8_lIndex++)
                        {
                            /* Convert The Target Address to PAN Format */
                            COMMON_Byte2PAN(&au8_lDisplayBuff[u8_lBuffIndex], \
                                                          p_fCanDispData->au8_mData[u8_lIndex + 1]);
                            u8_lBuffIndex = u8_lBuffIndex + 2;                                   
                        }
                        
                        au8_lDisplayBuff[u8_lBuffIndex] = '\n';
                        u8_lBuffIndex = u8_lBuffIndex + 1;                           
                    }
                    break;
                    
                    default :
                    break;
                }
            } 
         }
         
        p_gXT_ReqComplete((INT8U *)&au8_lDisplayBuff[0], u8_lBuffIndex);
    }                        
}

/**************************************************************************************************/
/* Function Name   : void J1939_SendTP_Data(INT8U *au8_lPayloadBuff , INT16U u16_lPayloadLen)           */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

INT8U au8_gRTSBuff[8] = {0x10,};
INT8U au8_gBAMpacketBuffer[8] = {0x20,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00};
INT8U au8_gConnctionAbort[8] = {0xFF,0xBC,0xFF,0xFF,0xFF,0xFF,0xFF,0x00};

void J1939_SendTP_Data(INT8U *au8_lPayloadBuff , INT16U u16_lPayloadLen)
{  
    float f8_lPackets = 0x00;
    INT8U u8_lMaxPackets = 0x00;   

    /* Buffer to store * bytes each time for send to ECU*/
    INT8U au8_lPayloadSendBuf[8] = {0x00,};
    
    /* INdex for to copy data */
    INT8U u8_lDataindex = 0x00;
    
    /* index for yo run For loop*/
    INT8U u8_lIndex = 0x00;
     
     /* Back Up the Requested PDU Format and PDU specific */
    u8_gJ1939_PF = u8_gTP_PGN[1];       
    u8_gJ1939_PS = u8_gTP_PGN[2];
   
    u8_gTP_J1939_PF = u8_gTP_PGN[1];
    u8_gTP_J1939_PS =  u8_gTP_PGN[2];
    
     /* Arrenge  Connection ABort Buffer with Requested PGN*/
    au8_gConnctionAbort[5]= u8_gTP_PGN[2];
    au8_gConnctionAbort[6]= u8_gTP_PGN[1];
    au8_gConnctionAbort[7]= u8_gTP_PGN[0];
    
        
    /* find out remainind packets */
    f8_lPackets  = (u16_lPayloadLen%7);
    
     /* Check whether remaining Bytes ir avalable or not */
    if(0x00 == f8_lPackets)
    {
        /* Arenge Same data in Buffer */
        au8_gRTSBuff[3]= (u16_lPayloadLen/7);
        
        /* Arenge Same data in Buffer */
        u8_lMaxPackets = au8_gBAMpacketBuffer[3]= (u16_lPayloadLen/7);
    }
    else
    {
         /* Make the The buffer packets + 1 because remaining Data is there to send*/
         au8_gRTSBuff[3]= ((u16_lPayloadLen/7) + 1);
         
          /* Make the The buffer packets + 1 because remaining Data is there to send*/
        u8_lMaxPackets = au8_gBAMpacketBuffer[3]= ((u16_lPayloadLen/7) + 1);
    }
    
    if(0x00 == u8_gCM_BAM_Flag)
    {
         /* if Destination Adrs is Specific Fill BAM buffer */
        au8_gBAMpacketBuffer[1]= u16_lPayloadLen;
        au8_gBAMpacketBuffer[2]=  ((u16_lPayloadLen & 0xFF00)>> 8);    
        au8_gBAMpacketBuffer[4]= 0xFF;
        au8_gBAMpacketBuffer[5]= u8_gTP_PGN[2];
        au8_gBAMpacketBuffer[6]= u8_gTP_PGN[1];
        au8_gBAMpacketBuffer[7]= u8_gTP_PGN[0];
        
        u8_gMaxPacktstoSend =  au8_gBAMpacketBuffer[3];
        u8_gSequence_Number = 0x01;
        
        /* Send the RTS on the Bus */
        pst_gHalObjectPtr->CAN_TxMsg(u32_gJ1939RTSHeader, &au8_gBAMpacketBuffer[0], 8);
        
        u32_gTickCounter = 0x00;
        while(u32_gTickCounter < 50);
    }
    else
    {   
        /* if Destination aAdrs is Specific Fill RTS buffer */
        au8_gRTSBuff[1]= u16_lPayloadLen;
        au8_gRTSBuff[2]=  ((u16_lPayloadLen & 0xFF00)>> 8);    
        au8_gRTSBuff[4]= 0xFF;
        au8_gRTSBuff[5]= u8_gTP_PGN[2];
        au8_gRTSBuff[6]= u8_gTP_PGN[1];
        au8_gRTSBuff[7]= u8_gTP_PGN[0];
        
        /* Send the RTS on the Bus */
        pst_gHalObjectPtr->CAN_TxMsg(u32_gJ1939RTSHeader, &au8_gRTSBuff[0], 8);
      
    }

    /* Make the Counter to Zero and make Flag to 1 For to start Timer Counter */
    u32_gJ1939RxMonitrTimeOutCntr = 0x00;
    u32_gJ1939RxMonitrTimeOutFlag = 0x01;
    
    /* */
    while(1 != u8_J1939RxTimeOutFlag && 0x00 != u8_gCM_BAM_Flag)
    {
        if(1 == u8_gCTS_Received_Flag)
        {
            /* if within time CTS Received Make the FLag and Counter 0 */
           u32_gJ1939RxMonitrTimeOutCntr = 0x00;
           u32_gJ1939RxMonitrTimeOutFlag = 0x00;
           break;
        }
    }
    if((1 == u8_gCTS_Received_Flag) || (0x00 == u8_gCM_BAM_Flag))
    {
        /* */
        u8_gCTS_Received_Flag = 0x00;
        u8_J1939RxTimeOutFlag = 0x00;
   
 SEND_REMNG:       
        for(u8_lIndex = 0x01; u8_lIndex <= u8_gMaxPacktstoSend ;u8_lIndex++)
        {
            /* Copy Seqnce number and DATA */
            au8_lPayloadSendBuf[0] = u8_gSequence_Number;
            
            if((u8_gSequence_Number == u8_gMaxPacktstoSend) && ((0 != (u16_lPayloadLen%7))&& \
                                                               (u8_lMaxPackets == u8_gSentPackets)))
            {
                /* Copy Seqnce number and DATA */
                au8_lPayloadSendBuf[0] = u8_gSequence_Number;
            
                /* */
                memset(&au8_lPayloadSendBuf[1],0xAA,7);

                /* */
                memcpy(&au8_lPayloadSendBuf[1] , &au8_lPayloadBuff[u8_lDataindex] , \
                                                                                u16_lPayloadLen%7); 
                                         /* Send the Data on the Bus  and wait for 50ms*/
                pst_gHalObjectPtr->CAN_TxMsg(J1939_DEFAULT_DATA_HEADER, &au8_lPayloadSendBuf[0], 8);
                
                /* Increment Sequence Number */
                u8_gSequence_Number = u8_gSequence_Number + 1;
            }
            else
            {
                /* */
                memcpy(&au8_lPayloadSendBuf[1] , &au8_lPayloadBuff[u8_lDataindex] , 7);
                /* Send the Data on the Bus  and wait for 50ms*/
                pst_gHalObjectPtr->CAN_TxMsg(J1939_DEFAULT_DATA_HEADER, &au8_lPayloadSendBuf[0], 8);

                /* Increment Sequence Number */
                u8_gSequence_Number = u8_gSequence_Number + 1;

                u32_gTickCounter = 0x00;
                while(u32_gTickCounter < 50);
            }

            /* */
            u32_gJ1939RxMonitrTimeOutCntr = 0x00;

            /* Increment Data Index */
            u8_lDataindex = u8_lDataindex + 7; 
            
            /* */
            //u8_lSentPackets = u8_lSentPackets + 1;
        }

        /* */               
        u32_gJ1939RxMonitrTimeOutCntr = 0x00;
        u32_gJ1939RxMonitrTimeOutFlag = 0x01;
   
        /* */
        while(1 != u8_J1939RxTimeOutFlag)
        {
             
            if(1 == u8_gCTS_Received_Flag)
            {
                /* if within time CTS Received Make the FLag and Counter 0 */
                u8_gCTS_Received_Flag = 0x00;
                 u8_J1939RxTimeOutFlag = 0x00;
                u32_gJ1939RxMonitrTimeOutCntr = 0x00;
                u32_gJ1939RxMonitrTimeOutFlag = 0x00;
               // u8_lMultpleCTSFlag = 0x01;
                goto SEND_REMNG;
            }
            else if((u8_lMaxPackets == u8_gSentPackets))
            {
                /* No Action */
                break;
            }
            else
            {
               /* No Action */
            }
        }
        if((1 != u8_gCTS_Received_Flag)&& (u8_lMaxPackets != u8_gSentPackets))
        {
            /* Send the Connection ABORT Data on the Bus */
            pst_gHalObjectPtr->CAN_TxMsg(u32_gJ1939CTSHeader, &au8_gConnctionAbort[0], 8);
            
            /* */
            u8_J1939RxTimeOutFlag = 0x00;
        }
        else
        {
            /* No Action */
        }
        
        /* */
        u8_gSequence_Number = 0x00;
        
        /* */
        u8_J1939RxTimeOutFlag = 0x00;
    }
    else if(1 != u8_gCTS_Received_Flag && 0x01 == u8_gCM_BAM_Flag)
    {
        /* Send the Connection ABORT Data on the Bus */
        pst_gHalObjectPtr->CAN_TxMsg(u32_gJ1939CTSHeader, &au8_gConnctionAbort[0], 8);
        
        /* */
        u8_J1939RxTimeOutFlag = 0x00;
    }
    else
    {
        /* No Action */
    }
    
    /* */
    u8_gMaxPacktstoSend = 0x00;
    u32_gJ1939RxMonitrTimeOutCntr = 0x00;
    u32_gJ1939RxMonitrTimeOutFlag = 0x00;
    u8_gSentPackets = 0x00;
    
}

/**************************************************************************************************/
/* End of SAEJ1939_21_TP.c                                                                        */
/**************************************************************************************************/

