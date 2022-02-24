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
/* \File Name   : TEOBD2.c                                                                        */
/* \Author      : L.Srikanth                                                                      */
/* \Version 	:                                                                                 */
/* \Date        : 17-10-2017                                                                      */
/*                                                                                                */
/* @Description :                                                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "ISO14230_FAST_public.h"
#include "ISO15765_CAN11B250KBPS_public.h"
#include "ISO15765_CAN11B500KBPS_public.h"
#include "ISO15765_CAN29B250KBPS_public.h"
#include "ISO15765_CAN29B500KBPS_public.h"
#include "SAEJ1939_CAN29B250KBPS_public.h"
#include "SAEJ1939_21_TP_public.h"

#include "XTP_PP_public.h"
#include "XTP_public.h"

#include "TEOBD2_public.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Variable for Auto Protocol Search */
INT8U u8_gAutoPrtcl =0x00;
INT8U u8_gAutprtclDtaFlag = 0x00;

TEOBD2_ErrCodes_t (* p_gXT_ReqComplete)(INT8U * p_fData, INT32U u32_fLen);

/* OBDII States Assignment */
const ST_OBDII_STATES_t st_gOBDIIStates[] =
{
    {
        /* ISO14230_KlineFast Handlers */
        .Init = ISO14230_KlineFast_Init,
        .Handler = ISO14230_KlineFast_Handler,
        .Exit = ISO14230_KlineFast_Exit,
        .WriteData = ISO14230_KlineFast_WriteData,
        .ReadData = ISO14230_KlineFast_ReadData,
        .WaitForResp = ISO14230_KlineFast_WaitForResp,
    },
    {
        /* ISO15765_CAN11B500KBPS State Handlers */
        .Init = ISO15765_CAN11B500KBPS_Init,
        .Handler = ISO15765_CAN11B500KBPS_Handler,
        .Exit = ISO15765_CAN11B500KBPS_Exit,
        .WriteData = ISO15765_CAN11B500KBPS_WriteData,
        .ReadData = ISO15765_CAN11B500KBPS_ReadData,
        .WaitForResp = ISO15765_CAN11B500KBPS_WaitForResp,
    },
    {
        /* ISO15765_CAN29B500KBPS Handlers */
        .Init = ISO15765_CAN29B500KBPS_Init,
        .Handler = ISO15765_CAN29B500KBPS_Handler,
        .Exit = ISO15765_CAN29B500KBPS_Exit,
        .WriteData = ISO15765_CAN29B500KBPS_WriteData,
        .ReadData = ISO15765_CAN29B500KBPS_ReadData,
        .WaitForResp = ISO15765_CAN29B500KBPS_WaitForResp,
    },
    {
        /* IS015765_CAN11B250KBPS Handlers */
        .Init = ISO15765_CAN11B250KBPS_Init,
        .Handler = ISO15765_CAN11B250KBPS_Handler,
        .Exit = ISO15765_CAN11B250KBPS_Exit,
        .WriteData = ISO15765_CAN11B250KBPS_WriteData,
        .ReadData = ISO15765_CAN11B250KBPS_ReadData,
        .WaitForResp = ISO15765_CAN11B250KBPS_WaitForResp,
    },
    {
        /* ISO15765_CAN29B250KBPS Handlers */
        .Init = ISO15765_CAN29B250KBPS_Init,
        .Handler = ISO15765_CAN29B250KBPS_Handler,
        .Exit = ISO15765_CAN29B250KBPS_Exit,
        .WriteData = ISO15765_CAN29B250KBPS_WriteData,
        .ReadData = ISO15765_CAN29B250KBPS_ReadData,
        .WaitForResp = ISO15765_CAN29B250KBPS_WaitForResp,
    },
    {
        /* SAEJ1939_CAN29B250KBPS Handlers */
        .Init = SAEJ1939_CAN29B250KBPS_Init,
        .Handler = SAEJ1939_CAN29B250KBPS_Handler,
        .Exit = SAEJ1939_CAN29B250KBPS_Exit,
        .WriteData = SAEJ1939_CAN29B250KBPS_WriteData,
        .ReadData = SAEJ1939_CAN29B250KBPS_ReadData,
        .WaitForResp = SAEJ1939_CAN29B250KBPS_WaitForResp,
    },
};

/* Pointer to Hold OBDII States */
ST_OBDII_STATES_t * p_stgOBDIIStates = (ST_OBDII_STATES_t *)&st_gOBDIIStates[0];

/* Initialize a state variables */
EN_STACK_MGR_STATES_LIST_t en_gOBDII_State = IS015765_CAN_11_500;
EN_STACK_MGR_STATES_LIST_t en_gOBDII_Prevstate = IS015765_CAN_11_500;

/* */
INT16U u16_gXTComBackupReqlength = 0;

/* */
HalObject_t st_gHalObject;

INT32U u32_gStackickCounter = 0x00;
/* */
HalObject_t * pst_gHalObjectPtr = &st_gHalObject;

/* */
INT32U u32_gTEOBD2TimeoutCounter = 0x00;
INT8U u8_gTEOBD2TimeoutFlag = 0x00;
INT8U u8_gTEOBD2ReqstSentFlag = 0x00;
INT32U u32_gTimeout = 200;
/* */
INT8U  *pu8_gISOTPDataRcvPntr = PNULL;
INT32U u32_gISOTPdLength = 0x00;
INT32U u32_gISOTP_CANid = 0x00;

/**************************************************************************************************/
/* Function Name   : void ISOTP_DataReceived(TEOBD2_ErrCodes_t (* p_fXT_ReqCompleat)(INT8U *  \
                                                                    p_fData, \   INT16U u16_fLen))*/
/*                                                                                                */
/* Description     : ISOTP_DataReceived Check whether ISOTP data Received or not                  */
/*                                                                                                */
/* In Params       : u32_fCANid , pu8_fData, u16_fLength                                          */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : None                                                                         */
/**************************************************************************************************/

void ISOTP_DataReceived(INT32U u32_fCANid , INT8U *pu8_fData , INT32U u32_fLength)
{
    /* */
    u32_gISOTP_CANid = u32_fCANid;
    
    /* */
    pu8_gISOTPDataRcvPntr = pu8_fData;
    
    /* */
    u32_gISOTPdLength = u32_fLength;
    
    /* Make the Flag to One */
    u8_gIsoTpDataRecvdFlag = 0x01;
}

/**************************************************************************************************/
/* Function Name   : void ISOTP_DataReceived(TEOBD2_ErrCodes_t (* p_fXT_ReqCompleat)(INT8U *  \
                                                                    p_fData, \   INT16U u16_fLen))*/
/*                                                                                                */
/* Description     : ISOTP_DataReceived Check whether ISOTP data Received or not                  */
/*                                                                                                */
/* In Params       : u32_fCANid , pu8_fData, u16_fLength                                          */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : None                                                                         */
/**************************************************************************************************/

void ISOTO_ErrorType(INT8U u8_lError)
{
    
}

/**************************************************************************************************/
/* Function Name   : void TEOBD2_Init(TEOBD2_ErrCodes_t (* p_fXT_ReqCompleat)(INT8U * p_fData, \     */
/*                                                                              INT16U u16_fLen))    */
/*                                                                                                */
/* Description     : TEOBD2 Initialization                                                        */
/*                                                                                                */
/* In Params       : void                                                                         */
/*                                                                                                */
/* Out Params      : p_fXT_ReqCompleat                                                            */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void XTP_Init(TEOBD2_ErrCodes_t (* p_fXT_ReqComplete)(INT8U * p_fData, INT32U u32_fLen))
{
    /* Update the Callback */
    p_gXT_ReqComplete = p_fXT_ReqComplete;
    
    /* Default Protocol Setting to CAN 11/500 */
    st_gChipConfigData.u8_mCurProtocol = '6';
    
//    if(PNULL != pst_gHalObjectPtr->NVM_Init)
//    {
//        pst_gHalObjectPtr->NVM_Init();
//    }
//    else
//    {
//        while(1);
//    }
//    
    /* Send Response */
   // p_gXT_ReqComplete((INT8U *)&au8_gIctVersionString[0], \
                                            strlen((const char *)&au8_gIctVersionString[0]));  
    
    /* Initialize the Current state */
    (p_stgOBDIIStates + en_gOBDII_State)->Init(&en_gOBDII_State, u32_gStackickCounter);
}

/**************************************************************************************************/
/* Function Name   : void TEOBD2_SendRequest(INT8U *p_fData, INT16U u16_fLength)                  */
/*                                                                                                */
/* Description     : TEOBD2 Initialization                                                        */
/*                                                                                                */
/* In Params       : p_fData, u16_fLength                                                         */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TEOBD2_StackHandler(void)
{
    /* Check the present and previous states status */
    if(en_gOBDII_State != en_gOBDII_Prevstate)
    {
        /* Exit the Previous State */
        (p_stgOBDIIStates + en_gOBDII_Prevstate)->Exit(&en_gOBDII_Prevstate, \
                                                                            u32_gStackickCounter);

         /* Initialize the Current state */
         (p_stgOBDIIStates + en_gOBDII_State)->Init(&en_gOBDII_State, u32_gStackickCounter);

         /* Initialize the Current state */
         (p_stgOBDIIStates + en_gOBDII_State)->Handler(&en_gOBDII_State, \
                                                                    u32_gStackickCounter);

          /* Update the State Variables */
          en_gOBDII_Prevstate = en_gOBDII_State;
    }
    else
    {
        /* Run the Handler */
        (p_stgOBDIIStates + en_gOBDII_State)->Handler(&en_gOBDII_State, \
                                                            u32_gStackickCounter);
    }
}

/**************************************************************************************************/
/* Function Name   : void TEOBD2_SendRequest(INT8U *p_fData, INT16U u16_fLength)                   */
/*                                                                                                */
/* Description     : TEOBD2 Initialization                                                        */
/*                                                                                                */
/* In Params       : p_fData, u16_fLength                                                         */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void XTP_SendRequest(INT8U * p_fData, INT32U u32_fLength)
{
    if(1 == u8_gCanBusMonitorStaus || 1 == u8_gCanBusMonitorHeadrs)
    {
        /* Check The Monitor Flag if 1 then make 0 */
        u8_gCanBusMonitorStaus = 0x00;
        u8_gCanBusMonitorHeadrs = 0x00;
        
        if(PNULL != pst_gHalObjectPtr->CAN_ConfigMO)
        {
            pst_gHalObjectPtr->CAN_ConfigMO(u32_gRxHeaderId, 1, OBD_CAN_STANDARD_ID, \
                OBD_CAN_MO_RX, 0x7FF);
        }
        else
        {
            while(1);
        }      
    }
    
    /* Check for Monitor ALL Flag */
    if(1 == u8_gSAEJ1939MtntlAllPGN)
    {
        
        u8_gSAEJ1939MtntlAllPGN = 0x00;
        
         /* Display no data */
         p_gXT_ReqComplete((INT8U *)"\r\n#", 3);
        
    }
    else if(1 == u8_gJ1939SnglPGNMntr)
    {
        u8_gJ1939SnglPGNMntr = 0x00;
        
         /* Display no data */
         p_gXT_ReqComplete((INT8U *)"\r\n#", 3);
    }
    
    if(0x00 != u32_gJ1939RxMonitrTimeOutFlag)
    {
        u32_gJ1939RxMonitrTimeOutFlag = 0x00;
        u32_gJ1939RxMonitrTimeOutCntr = 0x00;
    }
    
    /* Check for Echo Enable */
    if(1 == u8_gEchoFlagStatus)
    {
        /* Send Response */
        p_gXT_ReqComplete((INT8U *)&p_fData[0], u32_fLength);
    }
    
    /* Make the Flag 0 */
    u8_gIsoTpDataRecvdFlag = 0x00;

    /* Make the Pointe Null */
    pu8_gISOTPDataRcvPntr = PNULL;
            
    /* Process the Received Data or COmmand */
    if(XTCOM_SUCCESS != XTP_ProcessBuffer(&p_fData[0], u32_fLength))
    {
        /* Send Error String */
        p_gXT_ReqComplete((INT8U *)&au8_gIctErrorString, strlen((const char *)&au8_gIctErrorString));
    }
    else
    {
        /* No Action */
    }
}

/**************************************************************************************************/
/* Function Name   : void TEOBD2_SendRequest(INT8U *p_fData, INT16U u16_fLength)                  */
/*                                                                                                */
/* Description     : TEOBD2 Initialization                                                        */
/*                                                                                                */
/* In Params       : p_fData, u16_fLength                                                         */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void AutoSearchProtocl(void)
{
    /* Memset the Can Data Buffer */
    memset(&st_gCanTpLog.au8_mData[0],0x00 ,8);
    
    /* Make the Autosearch Flag to 1 */
    u8_gAutoPrtcl = 0x01;
    
    /* Satrt the Search From CAn,Kline,J1939 so switch to CAN */
    en_gOBDII_State = IS015765_CAN_11_500;
    
    /* Send  the  CAN Command  */ 
    ISO15765_CAN11B500KBPS_WriteData("0100\r", 5);
    
}


/**************************************************************************************************/
/* Function Name   : void TEOBD2_SendRequest(INT8U *p_fData, INT16U u16_fLength)                  */
/*                                                                                                */
/* Description     : TEOBD2 Initialization                                                        */
/*                                                                                                */
/* In Params       : p_fData, u16_fLength                                                         */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TEOBD2_UpdateCallBack(TEOBD2_ErrCodes_t (* p_fXT_ReqComplete)(INT8U * p_fData,INT32U u32_fLen))
{
    /* Update the CallBack Function */
    p_gXT_ReqComplete = p_fXT_ReqComplete;
    
}


/**************************************************************************************************/
/* Function Name   : void TEOBD2_SendRequest(INT8U *p_fData, INT16U u16_fLength)                  */
/*                                                                                                */
/* Description     : TEOBD2 Initialization                                                        */
/*                                                                                                */
/* In Params       : p_fData, u16_fLength                                                         */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TEOBD2_1MSHandler()
{
    u32_gTEOBD2TimeoutCounter = u32_gTEOBD2TimeoutCounter + 1;
    
    if(0x01 == u8_gTEOBD2ReqstSentFlag)
    {
        if(u32_gTEOBD2TimeoutCounter >= u32_gTimeout)
        {
           u8_gTEOBD2TimeoutFlag = 0x01;
        }
        else
        {
            /* No Action */
        }
    }
}
/**************************************************************************************************/
/* End of XTCOM.c                                                                                 */
/**************************************************************************************************/
