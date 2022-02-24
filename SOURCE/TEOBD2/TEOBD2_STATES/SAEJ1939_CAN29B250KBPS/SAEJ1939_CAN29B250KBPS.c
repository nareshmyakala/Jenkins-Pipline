/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2015, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : SAEJ1939_29_250.c                                                               */
/* \Author      :                                                                                 */
/* \Version 	:                                                                                 */
/* \Date        : 08/03/2016                                                                      */
/*                                                                                                */
/* @Description : SAEJ1939_29_250 FRAME WORK                                                      */
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

#include "ISO15765_2.h"
#include "ISOTPQ_public.h"
#include "XTP_public.h"

#include "SAEJ1939_21_TP_public.h"

#include "SAEJ1939_CAN29B250KBPS_public.h"
#include "SAEJ1939_CAN29B250KBPS_private.h"

#include "PLATFORM.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Dummy Variable for Queue Variable */
ST_ISOTP_DATA_t st_gJ1939CanTpLog = {0,};

INT8U u8_gJ1939DatatCmpltdFlag = 0x00;

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_Init(void)                          */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void SAEJ1939_ErrorHandler(void)
{
  
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_Init(void)                          */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void SAEJ1939_BusOff(void)
{
  
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_Init(void)                          */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_Init(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
                                                                                INT32U u32_gTickCount)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    /* Initilize Can Phy */
    OBDCanObj_t st_lOBDCanObj = 
    {    
        .en_fCanIdType = OBD_CAN_EXTENDED_ID,
        .en_fCanBaudRate = OBD_CAN_250KBPS,
        .fpCan_RxIndication = J1939_RxMsgHandler,
        .fpCan_TxConfirmation = J1939_TxConformation,
        .fpCan_ErrorHandler = SAEJ1939_ErrorHandler,
        .fpCan_BussOffHandler = SAEJ1939_BusOff  
    };
    
    /* Intialise the Can Physical layer */
    if(PNULL != pst_gHalObjectPtr->CAN_Init)
    {
        pst_gHalObjectPtr->CAN_Init((void *)&st_lOBDCanObj);
    }
    else
    {
       // while(1);
    } 
    
    /*Init the Quue for Messages */
    ISOTPLOGQUEUE_Init();
    
    /* Init ISOTP Timer */   
    if(PNULL != pst_gHalObjectPtr->TimerInit)
    {
        pst_gHalObjectPtr->TimerInit(1, J1939_Timer);
    }
    else
    {
        //while(1);
    }
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_Handler\                            */
/*                                                (EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_Handler(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
                                                                                INT32U u32_gTickCount)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    if(1 == u8_gMntrPGN_N_timesFlag)
    {
          if(ISOTPQ_LOGQUEUE_ReadAvailMsgCount())
          {
              /* Reset the Buffer */
              memset((void *)&st_gJ1939CanTpLog, 0x00, sizeof(st_gJ1939CanTpLog));
              
              /* Read the Msg and Display */
              ISOTPQ_ReadMsg(&st_gJ1939CanTpLog);
              J1939_DISPLAY(&st_gJ1939CanTpLog);                    
          }      
    }
    else if(1 == u8_gSAEJ1939MtntlAllPGN)
    {
          if(ISOTPQ_LOGQUEUE_ReadAvailMsgCount())
          {
              /* Reset the Buffer */
              memset((void *)&st_gJ1939CanTpLog, 0x00, sizeof(st_gJ1939CanTpLog));
              
              /* Read the Msg and Display */
              ISOTPQ_ReadMsg(&st_gJ1939CanTpLog);
              J1939_DISPLAY(&st_gJ1939CanTpLog);                    
          }        
    }
    else if(1 == u8_gJ1939SnglPGNMntr)
    {
          if(ISOTPQ_LOGQUEUE_ReadAvailMsgCount())
          {
              /* Reset the Buffer */
              memset((void *)&st_gJ1939CanTpLog, 0x00, sizeof(st_gJ1939CanTpLog));
              
              /* Read the Msg and Display */
              ISOTPQ_ReadMsg(&st_gJ1939CanTpLog);
              J1939_DISPLAY(&st_gJ1939CanTpLog);                    
          }         
    }
    else
    {
      if(1 == u8_gJ1939RqstSent)
      {
          if(ISOTPQ_LOGQUEUE_ReadAvailMsgCount())
          {
              /* Reset the Buffer */
              memset((void *)&st_gJ1939CanTpLog, 0x00, sizeof(st_gJ1939CanTpLog));
              
              /* Read the Msg and Display */
              ISOTPQ_ReadMsg(&st_gJ1939CanTpLog);
              J1939_DISPLAY(&st_gJ1939CanTpLog);
              
              u8_gJ1939DatatCmpltdFlag = 1;                     
          }
          else
          {
              if((1 == u8_gJ1939DatatCmpltdFlag))
              {
                  if(((0 == ISOTPQ_LOGQUEUE_ReadAvailMsgCount()))&& (1 == u8_J1939RxTimeOutFlag))
                  {
                      u8_gJ1939DatatCmpltdFlag = 0;
                      u8_gJ1939IsRxRcvd = 0x00;
                      
                      u8_J1939RxTimeOutFlag = 0x00;
                      
                      u8_gJ1939RqstSent = 0;
                      
                      /* Display no data */
                      p_gXT_ReqComplete((INT8U *)"#", 1);
                  }
              }
              else
              {
                  /* No Action */
                  
              }
          }
          
          if(0 == u8_gJ1939DatatCmpltdFlag)
          {
              if((1 == u8_J1939RxTimeOutFlag) && (0 == ISOTPQ_LOGQUEUE_ReadAvailMsgCount()))
              {
                  /* Make the Flag to Zero */
                  u8_J1939RxTimeOutFlag = 0x00;
                  
                  u32_gJ1939RxTimeOutCnt = 0x00;

                  /* Make the Flag to 0 */
                  u8_gJ1939RqstSent = 0;
                  
                  /* Display no data */
                  p_gXT_ReqComplete((INT8U *)"NO DATA\r\n#", 10);
              }
              else
              {
                  /* No action */
              }
          }
      }
      else
      {
          if(ISOTPQ_LOGQUEUE_ReadAvailMsgCount())
          {
              /* Reset the Buffer */
              memset((void *)&st_gJ1939CanTpLog, 0x00, sizeof(st_gJ1939CanTpLog));
              
              /* Read the Msg and Display */
              ISOTPQ_ReadMsg(&st_gJ1939CanTpLog);
              J1939_DISPLAY(&st_gJ1939CanTpLog);
          }
          else
          {
                u8_gJ1939_PF = 0x00;
                u8_gJ1939_PS = 0x00;
                u8_gRcvdPkts = 0x00;
                u8_J1939_ExptPkts = 0x00;
          }
      }      
    }
    
    /* Return The Result */
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_Exit(void)                          */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_Exit(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
                                                                                INT32U u32_gTickCount)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_WriteData\                          */
/*                                                      (void * p_fWriteBuffer, INT8U u8_fLenght)    */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_WriteData(void * p_fWriteBuffer, INT16U u16_fLenght)
{
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
   
    /* Variable to Hold Payload Length */
    INT16U u16_lPayloadLen = 0;
    
    /* Variable to Make Data In Big endian FOrmat */
    INT8U u8_ltemp = 0x00;
    
    /* Arry to Hold the Payload Data */
    INT8U au8_lPayloadBuff[1800] = {0, };
    
    /* */
    u16_lPayloadLen = (u16_fLenght-1)/2;
    
     /* Convert the Payload of PAN to  Payload */
     COMMON_PAN2ByteArray(p_fWriteBuffer, &au8_lPayloadBuff[0], u16_lPayloadLen);
         
     /* Check for Payload is Morethan 8 Bytes or not */
    if(0x08 <= u16_lPayloadLen && 1800 >= u16_lPayloadLen)
    {
         /* Convert the Payload of PAN to  Payload */
         //COMMON_PAN2ByteArray(p_fWriteBuffer, &au8_lPayloadBuff[0], u16_lPayloadLen);
         
         /* */
         J1939_SendTP_Data(&au8_lPayloadBuff[0],u16_lPayloadLen);
        
    }
    
    /* Check whether it is Request PGN or Not */
    else if((3 == u16_lPayloadLen) && (au8_lPayloadBuff[0] == 0x00))
    { 
        /* Convert the Payload of PAN to  Payload */
        // COMMON_PAN2ByteArray(p_fWriteBuffer, &au8_lPayloadBuff[0], u16_lPayloadLen);
         
//        u8_gJ1939_PF = 0x00;
//        u8_gJ1939_PS = 0x00;
        u8_gSorceAdressIndx = 0x00;
        memset(&au8_gSorceAdress[0] , 0x00,5);
        
        /* Back Up the Requested PDU Format and PDU specific */
        u8_gJ1939_PF = au8_lPayloadBuff[1];       
        u8_gJ1939_PS = au8_lPayloadBuff[2];
        
        /* Send the Data in Big endian Format */
        u8_ltemp = au8_lPayloadBuff[0];
        au8_lPayloadBuff[0] = au8_lPayloadBuff[2];
        au8_lPayloadBuff[2] = u8_ltemp;
        
        /* Send the Can Data to Physical Layer */                               
        if(PNULL != pst_gHalObjectPtr->CAN_TxMsg)
        {
            /* Clear the Queue */
            ISOTPLOGQUEUE_Clear();
        
            pst_gHalObjectPtr->CAN_TxMsg(u32_gJ1939Header, &au8_lPayloadBuff[0], u16_lPayloadLen);

             u8_J1939RxTimeOutFlag = 0x00;
             
             /* */
            u32_gJ1939RxTimeOutCnt = 0x00;
            
            /* */
            u8_gJ1939IsRxRcvd = 0;
            
            /* Make J1939 Rqst sent Flag to 1 */
            u8_gJ1939RqstSent = 1;
        }
        else
        {
            while(1);
        } 
    }
    else
    {
        en_lResult = STACK_ERROR;
    }
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : INT8U SAEJ1939_CAN29B250KBPS_ReadData(INT8U * p_fReadBuffer)                       */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

INT8U SAEJ1939_CAN29B250KBPS_ReadData(INT8U * p_fReadBuffer)
{
    return 0;
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_WaitForResp(void)                   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t SAEJ1939_CAN29B250KBPS_WaitForResp(void)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* End of SAEJ1939_29_250.c                                                                       */
/**************************************************************************************************/
