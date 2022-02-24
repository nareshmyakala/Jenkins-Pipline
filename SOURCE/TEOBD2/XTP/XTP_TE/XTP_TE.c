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
/* \File Name   : XTCOM_HANDLERS.c                                                                */
/* \Author      : harshan                                                                         */
/* \Version 	:                                                                                 */
/* \Date        : 12-12-2016                                                                      */
/*                                                                                                */
/* @Description : XTCOM                                                                           */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <stdlib.h>
#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "DATACONV.h"

#include "ISO15765_2.h"
#include "ISOTPQ_public.h"
#include "XTP_public.h"

#include "CAN_IF.h"

#include "XTP_TE_public.h"
#include "XTP_TE_private.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

INT8U u8_gTimeoutBufer[4] = {0x00, };

/* Variable to Hold The Current Baudrate */
INT32U u32_gCurrentBaudrate = 0;

/* Variable to Hold The Ataptive Timing Response */
INT8U u8_gAdptiveTiming = 0;

/* Variable to Hold The Default Timeout Time */
INT16U u16_TimeoutTime = 0;

/* Two Buffer for Error Handling */
INT8U au8_gCAN_PrevBuffer[4] = {0, };

/* Count for Repeated CAN Messages */
INT8U u8_gMessageRepeatCount = 0;

/* Flag for Append the CAN Message */
INT8U u8_gAppendNegRespFlag = 0;

/* Previous SID */
INT8U u8_gPrevSid;

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTRB(INT8U *p_fSrc, INT16U u16_fLength)                  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTRB(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTIIA(INT8U *p_fSrc, INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTIIA(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    return en_lResult;
}


/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTFC(INT8U *p_fSrc, INT16U u16_fLength)    */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTFC(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTCEA(INT8U *p_fSrc, INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTCEA(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold The Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    return en_lResult;   
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTIFR(INT8U *p_fSrc, INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTIFR(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold The Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTPB(INT8U *p_fSrc, INT16U u16_fLength)                        */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTPB(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold The Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult; 
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTP(INT8U *p_fSrc, INT16U u16_fLength)                         */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTP(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    INT32U  u32_lProtocolNumber = 0;
    
    /* */
    u32_lProtocolNumber = COMMON_Ascii2Dec(&p_fSrc[0], 2);
    
    /* Write the Corresponding argument to memory */
    st_gChipConfigData.u8_mCurProtocol  = u32_lProtocolNumber;
    TEOBDII_STACK_WriteConfigData();
    
    /* update Protocol State */
    en_gOBDII_State = GetCurrentProtocol();   
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    return en_lResult;     
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSI(INT8U *p_fSrc, INT16U u16_fLength)                        */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSI(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTTPA(INT8U *p_fSrc, INT16U u16_fLength)                       */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTTPA(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;   
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTTPA(INT8U *p_fSrc, INT16U u16_fLength)                       */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTTM(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Copy the Data Into Buffer upto length */
    memcpy(&u8_gTimeoutBufer[0] , p_fSrc , u16_fLength);
    
    /* Convert the Ascci data into Integer */
    u32_gTimeout =  atoi((char *)&u8_gTimeoutBufer[0]);  
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;   
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSA(INT8U *p_fSrc, INT16U u16_fLength)                        */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSA(INT16U * p_fArgs, INT8U u8_fArgCount)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    return en_lResult;
}
/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSATI(INT8U *p_fSrc, INT16U u16_fLength)                      */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSATI(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSLU(INT8U *p_fSrc, INT16U u16_fLength)                       */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSLU(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;
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

EN_XTP_RESULT_t XTP_XTMODE(INT16U * p_fArgs, INT8U u8_fArgCount)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTDIX(INT8U *p_fSrc, INT16U u16_fLength)                       */
/*                                                                                                */
/* Description     : This function is used to Read The CAN Data from the Queue                    */
/*                                                                                                */
/* In Params       : INT8U *p_fSrc, INT16U u16_fLength                                                  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_XTP_RESULT_t                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTDIX(INT16U * p_fArgs, INT8U u8_fArgCount)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTRH(INT8U *p_fSrc, INT16U u16_fLength)                        */
/*                                                                                                */
/* Description     : This function is used to Set Can Receive Header                              */
/*                                                                                                */
/* In Params       : INT8U *p_fSrc, INT16U u16_fLength                                                  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_XTP_RESULT_t                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTRH(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    INT8U u8_lBuff[6] = {0x00,};
    
    memcpy(&u8_lBuff[0],&p_fSrc[0],u16_fLength);
    /* Variable to Hold Header */
    INT32U u32_lHeader = 0;

    if(3 == u16_fLength)
    {
        /* append 0 */
        u8_lBuff[3] = '0';

        /* Convert the Content to Halfword */
        COMMON_PAN2HWord(&u8_lBuff[0], (INT16U *)&u32_lHeader);

        /* Shift the header by 1 */
        u32_lHeader = u32_lHeader >> 4;

        if(u32_lHeader <= 0x7FF)
        {  
            /* Tx Address Should be - 8 */
            u32_gRxHeaderId = u32_lHeader;
            
            //u8_gExtendAdd = u32_gRxHeaderId & 0xFF;
            
           // u32_gTxHeaderId = 0x6F1; 
            
             /* Initialize the CAN MO foto receive Data From All Headers */
            CAN_IF_Ioctrl(MO_CONFIGURE,CAN0,1,0x7FF,CAN_STD_ID,CAN_MB_RECEIVE,u32_gRxHeaderId);
            
           // pst_gHalObjectPtr->CAN_ConfigMO(u32_gRxHeaderId, 1, OBD_CAN_STANDARD_ID, \
                                                            OBD_CAN_MO_RX, 0x7FF);
            
            
        }
        else
        {
            /* Update Error Status To The Variable */
            en_lResult = XTP_ERROR;
        }
    }
    else if(6 == u16_fLength)
    {
#if 0      
        /* */
        memcpy(&au8_lTemp[0], &p_fSrc[0], u16_fLength);
        strcat((char *)&au8_lTemp[0], "00");

        /* Convert the Content to Word */
        if(COMMON_OK == COMMON_PAN2Word(&au8_lTemp[0], &u32_lHeader))
        {
            /* */
            u32_lHeader = (u32_lHeader >> 8);
            /* Update Format Byte */
            u8_gKlineFmtByte = (INT8U)((u32_lHeader & 0xFF0000) >> 16);

            /* Update Target Address */
            u8_gKlineTarByte = (INT8U)((u32_lHeader & 0x00FF00) >> 8);

            /* Update Source Address */
            u8_gKlineSrcByte = (INT8U)((u32_lHeader & 0x0000FF) >> 0);

            /* Display OK */
            strcpy((char *)&u8_gTbusTxBuffer[0], \
                (const char *)&au8_gIctSuccessString[0]);
        }
        else
        {
            /* Update Error Status To The Variable */
            en_lResult = XTP_ERROR;
        }
#endif        
    }
    else
    {
        /* Update Error Status To The Variable */
        en_lResult = XTP_ERROR;
    }

    if(XTP_ERROR != en_lResult)
    {
      /* Send Response */
      p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                           strlen((const char *)&au8_gIctSuccessString[0])); 
    }

    /* Return The Result */
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTEA(INT8U *p_fSrc, INT16U u16_fLength)                        */
/*                                                                                                */
/* Description     : This function is used to Enable or Diasble Extended ISOTP                    */
/*                                                                                                */
/* In Params       : INT8U *p_fSrc, INT16U u16_fLength                                                  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_XTP_RESULT_t                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTEA(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    if('0' == p_fSrc[0])
    {
        /* */
        u32_gRxHeaderId = u32_gRxHeaderBackUp;      
        u32_gTxHeaderId = u32_gTxHeaderBackUp;
        
        u8_gExtendAdd = 0x00;
        
         /* */
        en_gAddressingMode = NORMAL_ADDRESSING;
        
        if(PNULL != pst_gHalObjectPtr->CAN_ConfigMO)
        {
            pst_gHalObjectPtr->CAN_ConfigMO(u32_gRxHeaderId, 1, OBD_CAN_STANDARD_ID,  OBD_CAN_MO_RX, 0x7FF);
        }
        else
        {
            while(1);
        } 
    }
    else if('1' == p_fSrc[0])
    {
        /* */
        if(en_gAddressingMode != EXTENDED_ADDRESSING)
        {
            u32_gRxHeaderBackUp = u32_gRxHeaderId;          
            u32_gTxHeaderBackUp = u32_gTxHeaderId;
        }
        else
        {
            /* No Action */
        }
        
        /* */
        en_gAddressingMode = EXTENDED_ADDRESSING;      
    }
    else
    {
        /* Update Error Status To The Variable */
        en_lResult = XTP_ERROR;      
    }
    
    if(XTP_ERROR != en_lResult)
    {
      /* Send Response */
      p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                           strlen((const char *)&au8_gIctSuccessString[0])); 
    }
    
    return en_lResult;  
}


/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTRQ(INT8U *p_fSrc, INT16U u16_fLength)                        */
/*                                                                                                */
/* Description     : This function is used to Read The CAN Data from the Queue                    */
/*                                                                                                */
/* In Params       : INT8U *p_fSrc, INT16U u16_fLength                                                  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_XTP_RESULT_t                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTRQ(INT8U *p_fSrc, INT16U u16_fLength)
{ 
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    ST_ISOTP_DATA_t st_lCanTpLog = {0,};

    while(ISOTPQ_LOGQUEUE_ReadAvailMsgCount())
    {
        /* Reset the Buffer */
        memset((void *)&st_lCanTpLog, 0x00, sizeof(st_lCanTpLog));
        
        /* Read the Msg and Display */
        ISOTPQ_ReadMsg(&st_lCanTpLog);
        //CAN_DISPLAY(&st_lCanTpLog);     
    }
    
    /* Display no data */
    p_gXT_ReqComplete((INT8U *)"#\r\n", 3);
    
    return en_lResult;  
}

/**************************************************************************************************/
/* End of XTCOM_HANDLERS.c                                                                        */
/**************************************************************************************************/

