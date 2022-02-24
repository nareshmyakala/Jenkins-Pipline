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
/* \File Name   : ISOTPQ.c                                                                        */
/* \Author      : PRASHANTH.A                                                                     */
/* \Version 	:                                                                                 */
/* \Date        : 18-10-2017                                                                      */
/*                                                                                                */
/* @Description : ISOTPQ Frame Work                                                               */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "ISOTPQ_public.h"
#include "ISOTPQ_private.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

#define CANLOG_BUFFER_SIZE                  ( 700 )

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Buffer to store logged can messages */
ST_ISOTP_DATA_t ast_gISOTPLogBuffer[CANLOG_BUFFER_SIZE] = {0, };

/* Queue write pointer */
ST_ISOTP_DATA_t * p_gISOTPLogWritePtr = PNULL;

/* Queue read pointer */
ST_ISOTP_DATA_t * p_gISOTPLogReadPtr = PNULL;

/* Available Message Counter */
INT16U u16_gISOTP_MsgCnt = 0;

/**************************************************************************************************/
/* Function Name   : void CANLOGQUEUE_Init(void)                                                  */
/*                                                                                                */
/* Description     : Initialize the Queue for CAN Data Handling                                   */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISOTPLOGQUEUE_Init(void)
{
    /* Clear the can log buffer */
    memset(&ast_gISOTPLogBuffer[0], 0x00, sizeof(ast_gISOTPLogBuffer));
    
    /* Update Write Pointer with beginning of CAN log queue */
    p_gISOTPLogWritePtr = &ast_gISOTPLogBuffer[0];
    
    /* Update Read Pointer with beginning of CAN log queue */
    p_gISOTPLogReadPtr = &ast_gISOTPLogBuffer[0];
    
    /* Set Message count to zero */
    u16_gISOTP_MsgCnt= 0;
}

/**************************************************************************************************/
/* Function Name   : void CANLOGQUEUE_Init(void)                                                  */
/*                                                                                                */
/* Description     : Initialize the Queue for CAN Data Handling                                   */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void ISOTPLOGQUEUE_Clear(void)
{
    /* Update Write Pointer with beginning of CAN log queue */
    p_gISOTPLogWritePtr = &ast_gISOTPLogBuffer[0];
    
    /* Update Read Pointer with beginning of CAN log queue */
    p_gISOTPLogReadPtr = &ast_gISOTPLogBuffer[0];
    
    /* Set Message count to zero */
    u16_gISOTP_MsgCnt= 0;
}

/**************************************************************************************************/
/* Function Name   : EN_CANLOGQUEUE_WRITE_STATUS_t CANLOGQUEUE_WriteMsg( \                        */
/*                                                     const ST_ISOTP_LOG_MSG_t * p_fCanLogMsg)   */
/*                                                                                                */
/* Description     : This Function is Used to Write the Data to Queue                             */
/*                                                                                                */
/* In Params       : const ST_ISOTP_LOG_MSG_t * Type                                              */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CANLOGQUEUE_WRITE_STATUS_t Type                                           */
/**************************************************************************************************/

EN_ISOTPLOGQUEUE_WRITE_STATUS_t ISOTPQ_WriteMsg(const ST_ISOTP_DATA_t * p_fISOTPLogMsg)
{
	/* Variable to Hold Status */
    EN_ISOTPLOGQUEUE_WRITE_STATUS_t en_lResult = Q_WRITE_SUCCESS;
    
    /* Check for Buffer full condition */
    if(u16_gISOTP_MsgCnt < CANLOG_BUFFER_SIZE)
    {
        if(PNULL != p_fISOTPLogMsg)
        { 
            /* Update Can Arbitration ID */
            p_gISOTPLogWritePtr->u32_mCanId = p_fISOTPLogMsg->u32_mCanId;
            
            /* Update Can Message DLC */
            p_gISOTPLogWritePtr->u8_mDLC = p_fISOTPLogMsg->u8_mDLC;
            
            /* Update Can Message Payload */
            memcpy(&p_gISOTPLogWritePtr->au8_mData[0], &p_fISOTPLogMsg->au8_mData[0], \
                                                                      p_fISOTPLogMsg->u8_mDLC);
            
            /* update Frame */
           // p_gISOTPLogWritePtr->RxFrameType = p_fISOTPLogMsg->RxFrameType;
            
            
            /* Check for end of queue */
            if(p_gISOTPLogWritePtr == &ast_gISOTPLogBuffer[CANLOG_BUFFER_SIZE - 1])
            {
                /* Update Queue pointer with beginning of Queue */
                p_gISOTPLogWritePtr = &ast_gISOTPLogBuffer[0];
                
            }
            else
            {
                /* Increment Queue pointer */
                p_gISOTPLogWritePtr = p_gISOTPLogWritePtr + 1;
            }
            
            /* Increment Message Count available in Queue */
            u16_gISOTP_MsgCnt = u16_gISOTP_MsgCnt + 1;
        }
        else
        {
			/* Update Write Failure Status to Variable */
            en_lResult = Q_WRITE_FAILURE;
        }
    }
    else
    {
		/* Update Write Buffer Full Status to Variable */
        en_lResult = Q_WRITE_BUFFER_FULL;
    }
	
    /* Return Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_CANLOGQUEUE_READ_STATUS_t CANLOGQUEUE_ReadMsg( \                          */
/*                                                            ST_ISOTP_LOG_MSG_t * p_fCanLogMsg)  */
/*                                                                                                */
/* Description     : This Function is Used to Read The Data From Queue                            */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : CAN Log Message of ST_ISOTP_LOG_MSG_t* Type                                  */
/*                                                                                                */
/* Return Value    : status of EN_CANLOGQUEUE_READ_STATUS_t Type                                  */
/**************************************************************************************************/

EN_ISOTPLOGQUEUE_READ_STATUS_t ISOTPQ_ReadMsg(ST_ISOTP_DATA_t * p_fISOTPLogMsg)
{
	/* Variable to HOld Result */
    EN_ISOTPLOGQUEUE_READ_STATUS_t en_lResult = Q_READ_SUCCESS;
    
    if(u16_gISOTP_MsgCnt > 0)
    {
            /* Update Aribitration ID */
            p_fISOTPLogMsg->u32_mCanId = p_gISOTPLogReadPtr->u32_mCanId;
            
            /* Update Can Message DLC */
            p_fISOTPLogMsg->u8_mDLC = p_gISOTPLogReadPtr->u8_mDLC;
            
            /* Update Can Message Payload */
            memcpy(&p_fISOTPLogMsg->au8_mData[0], &p_gISOTPLogReadPtr->au8_mData[0], \
                                                                     p_fISOTPLogMsg->u8_mDLC);           
            /* update Frame */
            p_fISOTPLogMsg->RxFrameType = p_gISOTPLogReadPtr->RxFrameType;
        
        /* Check for end of CAN log message Queue */
        if(p_gISOTPLogReadPtr == &ast_gISOTPLogBuffer[CANLOG_BUFFER_SIZE - 1])
        {
            /* Update read pointer with beginning of queue */
            p_gISOTPLogReadPtr = &ast_gISOTPLogBuffer[0];
        }
        else
        {
            /* Increment read pointer */
            p_gISOTPLogReadPtr = p_gISOTPLogReadPtr + 1;
        }
        
        /* Decrement Message count by one */
        u16_gISOTP_MsgCnt = u16_gISOTP_MsgCnt - 1;
    }
    else
    {
        /* Update CAN Id with null */
        //p_fCanLogMsg->u16_mCanID = 0x00;
        
        /* Update DLC with zero */
        p_fISOTPLogMsg->u8_mDLC = 0x00;
        
        /* Clear the CAN Log payload */
        memset(&p_fISOTPLogMsg->au8_mData[0], 0x00, 8);
        
        /* Update result */
        en_lResult = Q_READ_FAILURE;
    }
    
    /* Return the CAN Log read status */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : INT16U CANLOGQUEUE_ReadAvailMsgCount(void)                                      */
/*                                                                                                */
/* Description     : This Function is Used to Read Available Mesage                               */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : CAN log message Count of INT16U Type                                            */
/**************************************************************************************************/

INT16U ISOTPQ_LOGQUEUE_ReadAvailMsgCount(void)
{
	/* Variable to Hold CAN message Log Count */
    INT16U u16_lCanLogMsgCnt = 0;
    
    /* Update Available Message count */
    u16_lCanLogMsgCnt = u16_gISOTP_MsgCnt;
    
	/* Return Log Count */
    return u16_lCanLogMsgCnt;
}

/**************************************************************************************************/
/* End of ISOTPQ.c                                                                                */
/**************************************************************************************************/

