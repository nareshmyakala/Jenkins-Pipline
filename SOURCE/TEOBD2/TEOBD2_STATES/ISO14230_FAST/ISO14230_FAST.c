/*************************************************************************************************/
/*                                                                                               */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                          */
/*                                                                                               */
/*************************************************************************************************/
/*                                                                                               */
/* All Rights Reserved Copyright (C) 2014, Technical Innovations N Solutions.                    */
/*                                                                                               */
/* Redistribution and use in source and binary forms, with or without                            */
/* modification, are not permitted in any case                                                   */
/*                                                                                               */
/* TINS's name may not be used to endorse or promote products derived from                       */
/* this software without specific prior written permission.                                      */
/*                                                                                               */
/*************************************************************************************************/

/*************************************************************************************************/
/* \File Name   : ISO14230_FAST.c                                                                 */
/* \Author      : Santhosh.s                                                                      */
/* \Version 	: V1.0     					                                                      */
/* \Date        : 08/03/2016    	                                                              */
/* @Description : ISO14230 FAST frame work                                                        */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include<string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "DATACONV.h"

#include "ISOTP14230_TP_public.h"

#include "XTP_public.h"

#include "ISO14230_FAST_public.h"
#include "ISO14230_FAST_private.h"

//#include "ISO15765_CAN_11B500KBPS_public.h"
#include "TEOBD2_public.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO14230_KlineFast_Init(\                                  */
/*                          EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, INT32U u32_gTickCount) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO14230_KlineFast_Init(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
                                                                              INT32U u32_gTickCount)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
   
    /* Kline MGR */
    //ISO14230_Init();
    
    /* Return The Result */
    return en_lResult;	
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO14230_KlineFast_Handler\                                */
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

EN_STACK_RESULT_t ISO14230_KlineFast_Handler(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
                                                                              INT32U u32_gTickCount)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;

#if 0
    /* Validate whether Fast Intit is performed or not */
    if(1 == u8_gKlineInitSeqFlag)
    {
        /* Check wehter Tester Busy Flag is free */
        if((u32_gKLineTesterCounter >= u32_gKline_P3) && (0 == u8_gKLineBusy))
        {           
            /* Indicate the The tester is in progress */
            u8_gTesterInProgress = 1;
            
            /* send Tester Present Sequence */
            ISO14230_KLineWrite((INT8U *)&au8_gTesterPresent[0], 4);
            
            /* Delay for P2 timing  */
            ISO14230_Delay(u32_gKline_P2);
            
            /* Release Tester Busy flag */
            u8_gKLineBusy = 0;
            
            /* Make Kline Tester counter to 0 */
            u32_gKLineTesterCounter = 0;
            
            /* Indicate the The tester is completed  */
            u8_gTesterInProgress = 0;
        }
        else
        {
            /* No action */
        }
    }
    else if(0x02 == u8_gAutprtclDtaFlag)
    {
        /* No action */
          if(STACK_ERROR == ISO14230_KlineFast_WriteData("0100\r",5))
          {
             *p_stfOBDII_State = IS015765_CAN_11_500;
             //ISO15765_CAN11B500KBPS_Init(p_stfOBDII_State,0);
          }
          else
          {
             /*No Action */
          }
        
       
    }    

#endif
    
    /* Return The Result */
    return en_lResult;	
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO14230_Fast_Exit(void)                                   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO14230_KlineFast_Exit(EN_STACK_MGR_STATES_LIST_t * p_stfOBDII_State, \
                                                                              INT32U u32_gTickCount)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
  
    /* DeInit K_Line Modules */
    //ISO14230_DeInit();
    
    /* Return The Result */
    return en_lResult;	
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO14230_KlineFast_WriteData\                              */
/*                                                      (void * p_fWriteBuffer, INT8U u8_fLenght) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO14230_KlineFast_WriteData(void * p_fWriteBuffer, INT16U u16_fLenght)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;

#if 0
    /* */
    INT8U u8_lKlineDataSentFlag = 0;
    
    /* One Time Execution Flag */
    if(0 == u8_gKlineInitSeqFlag)
    {            
        /* KWP2000 Fast Init Performed */
        if(ISO14230_SUCCESS == ISO14230_FastInit())
        {
            /* Init Sequence has been finished */
            u8_gKlineInitSeqFlag = 1;
            
            /* Reset the Response Buffer*/
            memset((INT8U *)&au8_gKLineTrasBufferp[0], 0x00, KLINE_MAX_BUFF_LENGTH);

            if(0x02 == u8_gAutprtclDtaFlag)
            {
                u8_gAutprtclDtaFlag = 0x00;
                 
                /* Make the Flag to Zero */
                u8_gAutoPrtcl = 0x00;
                
                /* Update the Current P{rotocol */
                st_gChipConfigData.u8_mCurProtocol = '5';
                
                /* Send Success String */
                p_gXT_ReqComplete((INT8U *)"ISO 14230-4 (KWP_FAST)\r\n#", 
                                                          strlen("ISO 14230-4 (KWP_FAST)\r\n#"));
    
            }
            else
            {
                /* Display BUS INIT OK...*/
                p_gXT_ReqComplete((INT8U *)"BUS INIT: OK\r\n", strlen("BUS INIT: OK\r\n")); 
            }
            /* form User Packet & Write */ 
            if(ISO14230_SUCCESS == ISO14230_PreparePacketAndWrite(&((INT8U *)p_fWriteBuffer)[0], \
                u16_fLenght-1))
            {                
                /*  Update Indication that data has sent */
                u8_lKlineDataSentFlag = 1; 
            }
            else
            {
                /* Update the status to Error */
                en_lResult = STACK_ERROR;            
            } 
        }
        else
        {
            if(0x02 == u8_gAutprtclDtaFlag)
            {
                u8_gAutprtclDtaFlag = 0x00;
                
                /* Make the Flag to Zero */
                u8_gAutoPrtcl = 0x00;
                
                /* Display BUS INIT ERROR...*/
                p_gXT_ReqComplete((INT8U *)"NO PROTOCOL FOUND TRY MANUALLY>\r\n", \
                                                     strlen("NO PROTOCOL FOUND TRY MANUALLY>\r\n"));
            }
            else
            {
                /* Display BUS INIT ERROR...*/
              p_gXT_ReqComplete((INT8U *)"BUS INIT: ...ERROR#\r\n",  strlen("BUS INIT: ...ERROR#\r\n"));
            }
            /* Relese the Kline busy flag */
            u8_gKLineBusy = 0;
            
            /* Update the Error Status */
            en_lResult = STACK_ERROR;         
        }
    }
    else
    {
        /* wait untill Tester present is complete */
        while(1 == u8_gTesterInProgress);
        
        /* form User Packet */ 
        if(ISO14230_SUCCESS == ISO14230_PreparePacketAndWrite(&((INT8U *)p_fWriteBuffer)[0], \
                                                                                    u16_fLenght-1))
        {
            /* Update Indication that data has sent */
            u8_lKlineDataSentFlag = 1;
        }
        else
        {
            /* Make Tester busy flag to 0 */
            u8_gKLineBusy = 0;
            
            /* Update the status to Error */
            en_lResult = STACK_ERROR;
        }     
    }
    
    if(1 == u8_lKlineDataSentFlag)
    {
        /* Make KLine data sent flag to 0 */
        u8_lKlineDataSentFlag = 0;
        
        /* wait for P2 timing */
        ISO14230_Delay(u32_gKline_P2);
        
        /* Reset Response Buffer */
        memset(&au8_gKLineTrasBufferp[0], 0x00, KLINE_MAX_BUFF_LENGTH);
        
        /* Extract the Output Data */
        ISO14230_KLineProcessRxData();   
    }
    else
    {    
        /* No action */    
    }
 
#endif
    
    /* Return The Result */
    return en_lResult;    
}

/**************************************************************************************************/
/* Function Name   : INT8U ISO14230_KlineFast_ReadData(INT8U * p_fReadBuffer)                           */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

INT8U ISO14230_KlineFast_ReadData(INT8U * p_fReadBuffer)
{
    return 0;
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_RESULT_t ISO14230_KlineFast_WaitForResp(void)                       */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_RESULT_t ISO14230_KlineFast_WaitForResp(void)
{
    /* Variable to Hold Result */
    EN_STACK_RESULT_t en_lResult = STACK_SUCCESS;
    
    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* End of ISO14230_FAST.c                                                                         */
/**************************************************************************************************/
