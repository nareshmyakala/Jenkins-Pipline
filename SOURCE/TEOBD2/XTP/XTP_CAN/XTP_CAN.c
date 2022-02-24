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
/* \File Name   : CAN_HANDLERS.c                                                                  */
/* \Author      : PRASHANTH                                                                       */
/* \Version 	:                                                                                 */
/* \Date        : 25-03-2017                                                                      */
/*                                                                                                */
/* @Description : CAN Hndlers Frame work                                                          */
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

#include "XTP_CAN_public.h"
#include "XTP_CAN_private.h"

#include "CAN_IF.h"

#include "XTP_public.h"
#include "XTP_TE_public.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTD(INT8U *p_fSrc, INT16U u16_fLength)                         */
/*                                                                                                */
/* Description     : This functions is used to turn DLC Off  or On                                */
/*                                                                                                */
/* In Params       : INT8U *p_fSrc, INT16U u16_fLength                                                  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_XTP_RESULT_t                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_CAN_XTD(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    switch(p_fSrc[0])
    {
    case '0':
        {
            /* */
            u8_gDLCFlag = 0;
        }
        break;
    case '1':
        {
            /* */
           u8_gDLCFlag = 1; 
        }
        break;
    default:
        {
            /* Update Error Status */
            en_lResult = XTP_ERROR;
        }
        break;
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
/* Function Name   : EN_XTP_RESULT_t XTP_XTFCSD(INT8U *p_fSrc, INT16U u16_fLength)*/
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTFCSD(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;  
}

/***************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTFCSH(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                 */
/* Description     :                                                                               */
/*                                                                                                 */
/* In Params       :                                                                               */
/*                                                                                                 */
/* Out Params      :                                                                               */
/*                                                                                                 */
/* Return Value    :                                                                               */
/***************************************************************************************************/

EN_XTP_RESULT_t XTP_XTFCSH(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold The Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0]));
    
    /* Return The Result */
    return en_lResult;  
}

/***************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTFCSH(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                 */
/* Description     :                                                                               */
/*                                                                                                 */
/* In Params       :                                                                               */
/*                                                                                                 */
/* Out Params      :                                                                               */
/*                                                                                                 */
/* Return Value    :                                                                               */
/***************************************************************************************************/

EN_XTP_RESULT_t XTP_XTMH(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold The Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    INT8U u8_lCanHeadrenumber = 0x00;
    INT32U u32_lRxHeaderId = 0x00;
    INT8U au8_lTemp[8] = {0, };
    
    /* Copy the Header numbers for monitor */
    u8_lCanHeadrenumber = (p_fSrc[0] - 48);
    
    if(u8_lCanHeadrenumber <= 8)
    {
        for(INT8U u8_lIndex = 0x00,u8_lTakeHdr= 0x00 ; u8_lIndex < u8_lCanHeadrenumber ; u8_lIndex++)
        {
              /* Aappend 0 */
            memcpy(&au8_lTemp[0], &p_fSrc[u8_lTakeHdr + 2], 3);
            au8_lTemp[3] = '0';
            
            /* Convert the Content to Halfword */
            COMMON_PAN2HWord(&au8_lTemp[0], (INT16U *)&u32_lRxHeaderId);
            
            /* Shift the header by 1 */
            u32_lRxHeaderId = u32_lRxHeaderId >> 4;
            
            if(PNULL != pst_gHalObjectPtr->CAN_ConfigMO)
            {
                 /* Initialize the CAN MO foto receive Data From All Headers */
                CAN_IF_Ioctrl(MO_CONFIGURE,CAN0,u8_lIndex + 2,0x7FF,CAN_STD_ID,CAN_MB_RECEIVE,\
                                                                                   u32_gRxHeaderId);
                
               // pst_gHalObjectPtr->CAN_ConfigMO(u32_lRxHeaderId, u8_lIndex + 2, OBD_CAN_STANDARD_ID, \
                                                                              OBD_CAN_MO_RX, 0x7FF);
            }
            else
            {
               en_lResult = XTP_ERROR;
            } 
            
            /* Increment value to copy nect header */
            u8_lTakeHdr = u8_lTakeHdr + 4;
        }
        
        /* Make the Monitor Header Flag to 1 */
        u8_gCanBusMonitorHeadrs = 0x01;
    }
    else
    {
        /* */
        en_lResult = XTP_ERROR;
    }
    
    
    /* Return The Result */
    return en_lResult;  
}

/***************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTFCSM(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                 */
/* Description     :                                                                               */
/*                                                                                                 */
/* In Params       :                                                                               */
/*                                                                                                 */
/* Out Params      :                                                                               */
/*                                                                                                 */
/* Return Value    :                                                                               */
/***************************************************************************************************/

EN_XTP_RESULT_t XTP_XTFCSM(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    
    return en_lResult;  
}


/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTFPA(INT8U *p_fSrc, INT16U u16_fLength)                       */
/*                                                                                                */
/* Description     : This function used to Set CAN Receive Header and Rx Filter Mask              */
/*                                                                                                */
/* In Params       : INT8U *p_fSrc, INT16U u16_fLength                                                  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_XTP_RESULT_t                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTFPA(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Variable to Hold Header */
    INT32U u32_lHeader = 0;
    INT32U u32_lFilterMask = 0x00;
    INT8U au8_lTemp[16] = {0, };
    
    memcpy(&au8_lTemp[0], &p_fSrc[0], u16_fLength);
    
    if(6 == u16_fLength)
    {
        /* append 0 */
        au8_lTemp[3] = '0';

        /* Convert the Content to Halfword */
        COMMON_PAN2HWord(&au8_lTemp[0], (INT16U *)&u32_lHeader);

        /* Shift the header by 1 */
        u32_lHeader = u32_lHeader >> 4;

        if(u32_lHeader <= 0x7FF)
        {
            /* Tx Address Should be - 8 */
            u32_gRxHeaderId = u32_lHeader; 
            
            /* append 0 */
            au8_lTemp[7] = '0';
            
            /* Convert the Content to Halfword */
            COMMON_PAN2HWord(&au8_lTemp[4], (INT16U *)&u32_lFilterMask);
            
            /* Shift the header by 1 */
            u32_lFilterMask = u32_lFilterMask >> 4;
            
            if(u32_lFilterMask <= 0x7FF)
            {
                if(PNULL != pst_gHalObjectPtr->CAN_ConfigMO)
                {
                    pst_gHalObjectPtr->CAN_ConfigMO(u32_gRxHeaderId, 1, OBD_CAN_STANDARD_ID, \
                                                                OBD_CAN_MO_RX, u32_lFilterMask);
                }
                else
                {
                    while(1);
                }              
            }
            else
            {
                /* Update Error Status To The Variable */
                en_lResult = XTP_ERROR;                
            }
        }
        else
        {
            /* Update Error Status To The Variable */
            en_lResult = XTP_ERROR;
        }
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
/* Function Name   : EN_XTP_RESULT_t XTP_XTSCFH(INT8U *p_fSrc, INT16U u16_fLength)                      */
/*                                                                                                */
/* Description     : This function used to Set Can Tx and Rx Header (Flow Control)                */
/*                                                                                                */
/* In Params       : INT8U *p_fSrc, INT16U u16_fLength                                                  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_XTP_RESULT_t                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSCFH(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Variable to Hold Header */
    INT32U u32_TxHeader = 0x00;
    INT32U u32_RxHeader = 0x00;
    INT8U au8_lTemp[16] = {0, };
    
    memcpy(&au8_lTemp[0], &p_fSrc[0], u16_fLength);
    
    if(6 == u16_fLength)
    {
        /* append 0 */
        au8_lTemp[3] = '0';

        /* Convert the Content to Halfword */
        COMMON_PAN2HWord(&au8_lTemp[0], (INT16U *)&u32_TxHeader);

        /* Shift the header by 1 */
        u32_TxHeader = u32_TxHeader >> 4;
        
        /* append 0 */
        au8_lTemp[7] = '0';       
        
         /* Convert the Content to Halfword */
        COMMON_PAN2HWord(&au8_lTemp[4], (INT16U *)&u32_RxHeader);

        /* Shift the header by 1 */
        u32_RxHeader = u32_RxHeader >> 4;
        
        if((u32_TxHeader <= 0x7FF)  && (u32_RxHeader <= 0x7FF))
        {
            /* Set the Tx Header */
            u32_gTxHeaderId = u32_TxHeader;
            
            /* Set the Rx Header  */
            u32_gRxHeaderId = u32_RxHeader; 
           
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
        else
        {
            /* Update Error Status To The Variable */
            en_lResult = XTP_ERROR;
        }
    }
    
    if(XTP_ERROR != en_lResult)
    {
        /* Send Response */
        p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                                strlen((const char *)&au8_gIctSuccessString[0])); 
    }
    
    return en_lResult;
}

/****************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTFFCA(INT8U *p_fSrc, INT16U u16_fLength)                        */
/*                                                                                                  */
/* Description     : This function used to Set CAN Receive Header and Rx Filter Mask                */
/*                                                                                                  */
/* In Params       : INT8U *p_fSrc, INT16U u16_fLength                                                    */
/*                                                                                                  */
/* Out Params      : None                                                                           */
/*                                                                                                  */
/* Return Value    : EN_XTP_RESULT_t                                                                */
/****************************************************************************************************/

EN_XTP_RESULT_t XTP_XTFFCA(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Variable to Hold Header */
    INT32U u32_lHeader = 0;
    INT32U u32_lFilterMask = 0x00;
    INT8U au8_lTemp[16] = {0, };
    
    memcpy(&au8_lTemp[0], &p_fSrc[0], u16_fLength);
    
    if(6 == u16_fLength)
    {
        /* append 0 */
        au8_lTemp[3] = '0';

        /* Convert the Content to Halfword */
        COMMON_PAN2HWord(&au8_lTemp[0], (INT16U *)&u32_lHeader);

        /* Shift the header by 1 */
        u32_lHeader = u32_lHeader >> 4;

        if(u32_lHeader <= 0x7FF)
        {
            /* Tx Address Should be - 8 */
            u32_gRxHeaderId = u32_lHeader; 
            
            /* append 0 */
            au8_lTemp[7] = '0';
            
            /* Convert the Content to Halfword */
            COMMON_PAN2HWord(&au8_lTemp[4], (INT16U *)&u32_lFilterMask);
            
            /* Shift the header by 1 */
            u32_lFilterMask = u32_lFilterMask >> 4;
            
            if(u32_lFilterMask <= 0x7FF)
            {
                if(PNULL != pst_gHalObjectPtr->CAN_ConfigMO)
                {
                    pst_gHalObjectPtr->CAN_ConfigMO(u32_gRxHeaderId, 1, OBD_CAN_STANDARD_ID, \
                                                                OBD_CAN_MO_RX, u32_lFilterMask);
                }
                else
                {
                    while(1);
                }              
            }
            else
            {
                /* Update Error Status To The Variable */
                en_lResult = XTP_ERROR;                
            }
        }
        else
        {
            /* Update Error Status To The Variable */
            en_lResult = XTP_ERROR;
        }
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
/* End of CAN_HANDLERS.c                                                                          */
/**************************************************************************************************/

