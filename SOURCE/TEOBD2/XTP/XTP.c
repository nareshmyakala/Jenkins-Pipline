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
/* \File Name   : XTCOM.c                                                                         */
/* \Author      : Prashanth.A                                                                     */
/* \Version 	:                                                                                 */
/* \Date        : 12-09-2017                                                                      */
/*                                                                                                */
/* @Description :                                                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>
#include <stdio.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "DATACONV.h"

#include "XTP_PP_public.h"
#include "XTP_TE_public.h"
#include "XTP_GE_public.h"
#include "XTP_PM_public.h"
#include "XTP_CAN_public.h"
#include "XTP_ISO_public.h"
#include "XTP_OBD_public.h"
#include "XTP_SAEJ1939_public.h"

#include "TEOBD2_public.h"

#include "XTP_public.h"
#include "XTP_private.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* */
//INT8U au8_gXtComReqBackupBuffer[XTCOM_REQ_BUFFER_LENGTH] = {0, };

//INT8U TeObd2_RxBuffer[XTCOM_REQ_BUFFER_LENGTH] = {0, };


volatile INT16U u16_gXtComReqIndex = 0;
volatile INT16U u16_gXtComReqLength = 0;
volatile INT8U u8_gXtComReqFlag = 0;

INT16U u16_gTimeoutTime = 40;

/**************************************************************************************************/
/* Stack Variables                                                                                */
/**************************************************************************************************/

/* Constatnt Variable Which Holds The Firmware Version Info */
const INT8U au8_gIctVersionString[] = "iConnect v1.0\r\n#\0"; 

/* Constant Variable Which Holds Error Prompt */
const INT8U au8_gIctErrorString[] = {"@!\r\n#"};

/* Constant Variable Which Holds Success Prompt */
const INT8U au8_gIctSuccessString[] = {"OK\r\n#"};

/* Constant Variable Which Holds Success Prompt */
const INT8U au8_gIctSearchng[] = {"SEARCHING\r\n#"};

/* Echo Status Flag */
INT8U u8_gEchoFlagStatus = 1;

/* Repeat Flag */
INT8U u8_gRepeatFlag = 0;

/* Variable to Hold Response Flag */
INT8U u8_gResponseFlag = 1;

/* Variable to Hold Header Flag */
INT8U u8_gHeaderFlag = 0;

/* Variable to Hold Space Flag */
INT8U u8_gIctSpaceFlag = 1;

/* Variable to Hold Linefeed Flag */
INT8U u8_gLineFeedFlag = 1;

/* Variable to Hold DLC Flag */
INT8U u8_gDLCFlag = 0;

/* Variable to Hold CAN Bus Monitor Status */
INT8U u8_gCanBusMonitorStaus = 0;
INT8U u8_gCanBusMonitorHeadrs = 0;

/* Variable to Hold Tx Header ID */
INT32U u32_gTxHeaderId = 0x7E0;

/* Variable to Hold Rx Header ID */
INT32U u32_gRxHeaderId = 0x7E8;

/* Variable to Hold Tx Header ID */
INT32U u32_gTxHeaderBackUp = 0x7E0;

/* Variable to Hold Rx Header ID */
INT32U u32_gRxHeaderBackUp = 0x7E8;

/* Configuration Data*/
ST_SYS_CONFIG_DATA_t st_gChipConfigData = {0, };

INT8U u8_gExtendAdd = 0x00;

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t XTCOM_Init(void (* fp_XtpRxHandler)(INT8U u8_fData))       */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

//EN_XTCOM_RESULT_t XTP_Init(void)
//{
//    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
//    
//    /* Variable to Hold the XTCOM BootAddr*/
//    INT8U u8_lBootStatus = 0x00;
//    
//    /* */
//    if(PNULL != pst_gHalObjectPtr->NVM_Read)
//    {
//        pst_gHalObjectPtr->NVM_Read(EEPROM_XTCOM_BOOT_STATUS_ADD, (INT8U *)&u8_lBootStatus, 1);
//    }
//    else
//    {
//        while(1);
//    }
//    
//    if(0xA5 != u8_lBootStatus)
//    {
//        /* Upadate XTCOM Bootload Status */
//        u8_lBootStatus = 0xA5;
//        
//        /* write the XTCOM Boot status into EEPROM */
//        if(PNULL != pst_gHalObjectPtr->NVM_Write)
//        {
//            pst_gHalObjectPtr->NVM_Write(EEPROM_XTCOM_BOOT_STATUS_ADD, (INT8U *)&u8_lBootStatus, 1);
//        }
//        else
//        {
//            while(1);
//        }
//    
//        /* Set Config Data from NVM */
//        TEOBDII_STACK_WriteDefaultConfigData(); 
//        
//        /* Write Programmable Params */
//        if(PNULL != pst_gHalObjectPtr->NVM_Write)
//        {
//            pst_gHalObjectPtr->NVM_Write(PP_BASE_ADDR, (INT8U *)&st_gPPBackup, sizeof(st_gPPBackup));
//        }
//        else
//        {
//            while(1);
//        }
//        
//        /* Copy PP BackUp Data to PP Current Data */
//        memcpy((INT8U *)&st_gPPCurrent[0], (INT8U *)&st_gPPBackup[0], sizeof(st_gPPBackup));
//    }
//    else    
//    {
//        /* Get Config Data from NVM */
//        TEOBDII_STACK_GetConfigData();
//        
//        /* Get PP Params from NVM */
//        if(PNULL != pst_gHalObjectPtr->NVM_Write)
//        {
//            pst_gHalObjectPtr->NVM_Write(PP_BASE_ADDR, (INT8U *)&st_gPPBackup, sizeof(st_gPPBackup));
//        }
//        else
//        {
//            while(1);
//        }
//        
//        /* Copy PP Parameters Backup into PP Parameters into Current */
//        memcpy((INT8U *)&st_gPPCurrent[0], (INT8U *)&st_gPPBackup[0], sizeof(st_gPPBackup));
//    }
//    
//    //    /* Send Chip Verstion string to User */
//    //    //XTCOM_SendResponse((INT8U *)"iConnect v1.0\r\n", \
//    //        strlen("iConnect v1.0\r\n"));
//    
//    /* Reset the Buffer */
//    XTP_ResetRxBuffer();
//    
//    /* Return the result */
//    return en_lResult;  
//}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t XTP_ProcessBuffer( const INT8U *p_fSrc , \                    */
/*                                                                       const INT8U *p_fLength)     */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t XTP_ProcessBuffer(const INT8U *p_fSrc , INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* Remove Spaces */
    XTP_RemoveSpaces((INT8U *)p_fSrc,(INT16U *)&u16_fLength );
    
    /* Reset from (buffer + length) location */
   // memset((INT8U *)&p_fSrc[0] + u16_fLength, 0x00, (XTCOM_RESP_BUFFER_LENGTH - u16_fLength));
    
    /* Convert Small to Caps */
    XTP_SmallToCaps((INT8U *)p_fSrc, u16_fLength);
    
    /* Check for Data Frame */
    if(XTCOM_ERROR == XTP_CheckForDataFrame((INT8U *)p_fSrc, &u16_fLength))
    {
        /* Process the Command */
        if(XTCOM_SUCCESS != XTP_ProcessCommand((INT8U *)p_fSrc, u16_fLength))
        {
            /* */
            en_lResult = XTCOM_ERROR;
        }
        else
        {
            /* No action */
        }       
    }
    else
    {
        if(0 == (u16_fLength - 1) % 2)
        {
             /* Process the Data */ 
             XTP_ProcessData((INT8U *)p_fSrc, u16_fLength);
                
            if(0x00 == u8_gErrorSuccesFlag)
            {
               /* Send Error String */
               p_gXT_ReqComplete((INT8U *)&au8_gIctErrorString, strlen((const char *)&au8_gIctErrorString));
               
            }
               
        }
        else
        {
            /* */
            en_lResult = XTCOM_ERROR;
        }
    }
    
    /* Return the Result */
    return en_lResult;  
}


/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t XTP_RemoveSpaces( const INT8U *p_fSrc , const INT8U *p_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void XTP_RemoveSpaces( INT8U *p_fSrc , INT16U *p_fLength)
{
    INT16U u16_lIndex1 = 0;
    INT16U u16_lIndex2 = 0;
    
    INT8U au8_lDataBuffer[XTCOM_RESP_BUFFER_LENGTH] = {0, };
    
    while(u16_lIndex1  < *p_fLength)
    {
        if(' ' != p_fSrc[u16_lIndex1])
        {
            au8_lDataBuffer[u16_lIndex2] = p_fSrc[u16_lIndex1];
            
            u16_lIndex2 = u16_lIndex2 + 1;
        }
        else
        {
            /* No Action */
        }
        
        u16_lIndex1++;
    }
    
    if(u16_lIndex1 != u16_lIndex2)
    {
        memcpy(p_fSrc, &au8_lDataBuffer[0], u16_lIndex2);
        
        *p_fLength = u16_lIndex2;
    }   
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t TeXP_SmallToCaps( const INT8U *p_fSrc , const INT8U *p_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void XTP_SmallToCaps(INT8U *p_fSrc , INT16U u16_fLength)
{
    /* */
    INT16U u16_lIndex = 0;
    
    while(u16_lIndex  < u16_fLength)
    {
        if((p_fSrc[u16_lIndex ] >= 'a') && (p_fSrc[u16_lIndex ] <= 'z'))
        {
            p_fSrc[u16_lIndex ] = p_fSrc[u16_lIndex ] - 32;
        }
        else
        {
            /* No Action */
        }
        u16_lIndex++;
    }
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t CheckForDataFrame( const INT8U *p_fSrc, const INT8U *p_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t XTP_CheckForDataFrame( const INT8U *p_fSrc,  INT16U *p_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* for Looping purpose */
    INT16U u16_lIndex = 0;
    
    for(u16_lIndex = 0; u16_lIndex < (*p_fLength - 1); u16_lIndex++)
    {
        if((('0' <= p_fSrc[u16_lIndex]) && ('9' >= p_fSrc[u16_lIndex])) || \
            (('A' <= p_fSrc[u16_lIndex]) && ('F' >= p_fSrc[u16_lIndex])))
        {
            /* No Action */
        }
        else
        {
            en_lResult = XTCOM_ERROR;
            break;
        }
    }
    
    return en_lResult;
}


/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t XTP_ProcessCommand( const INT8U *p_fSrc , \                   */
/*                                                                       const INT8U *p_fLength)     */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t XTP_ProcessCommand( const INT8U *p_fSrc , INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* To Hold Command Type */
    EN_CMD_TYPE_t en_lCmdType = CMD_XT;
    
    en_lCmdType = XTP_Check_AT_ST_XT(&p_fSrc[0] , u16_fLength);
    
    if((CMD_ERROR != en_lCmdType) && ((CMD_XT == en_lCmdType)))
    {    
        /* Execute The Command */
        if(XTCOM_SUCCESS != XTP_ExecuteCommand(&p_fSrc[2], (u16_fLength-2)))
        {
            /* Update Error Status */
            en_lResult = XTCOM_ERROR;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Update Error Status */
        en_lResult = XTCOM_ERROR;
    }
    
    /* return Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t XTP_ProcessData( const INT8U *p_fSrc , const INT8U *p_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

INT8U u8_gErrorSuccesFlag = 0x01;

EN_XTCOM_RESULT_t XTP_ProcessData( const INT8U *p_fSrc , INT16U u16_fLength )
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    u8_gErrorSuccesFlag = 0x01;
    
    /* Write Data Through Corresponding State */
    if(STACK_SUCCESS != (p_stgOBDIIStates + en_gOBDII_State)->WriteData((void *)&p_fSrc[0], \
                                                                                       u16_fLength))
    {
         u8_gErrorSuccesFlag = 0x00;
         /* */
         en_lResult = XTCOM_ERROR;
    }
    else
    {
        /* No Action */
       
    }
    
    /* Return the Result */
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t XTP_ExecuteCommand( const INT8U *p_fSrc , const INT8U *p_fLength)*/
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t XTP_ExecuteCommand( const INT8U *p_fSrc , INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    u16_fLength = u16_fLength-1;
    
    switch(p_fSrc[0])
    {
    case '\r':
        {
            /* Make Repeat Flag to 1 */
            u8_gRepeatFlag = 1;
            
            /* Make Command Received Flag to 1 */
            u8_gXtComReqFlag = 1;
        }
        break;
        
    case 'A':
        {
            if(XTCOM_SUCCESS != A_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'B':
        {
            if(XTCOM_SUCCESS != B_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'C':
        {
            if(XTCOM_SUCCESS != C_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'D':
        {
            if(XTCOM_SUCCESS != D_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }
        break;
        
    case 'E':
        {
            if(XTCOM_SUCCESS != E_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'F':
        {
            if(XTCOM_SUCCESS != F_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'H':
        {
            if(XTCOM_SUCCESS != H_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'I':
        {
            if(XTCOM_SUCCESS != I_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'J':
        {
            if(XTCOM_SUCCESS != J_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
        
    case 'K':
        {
            if(XTCOM_SUCCESS != K_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'L':
        {
            if(XTCOM_SUCCESS != L_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'M':
        {
            if(XTCOM_SUCCESS != M_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'N':
        {
            if(XTCOM_SUCCESS != N_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'P':
        {
            if(XTCOM_SUCCESS != P_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'R':
        {
            if(XTCOM_SUCCESS != R_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'S':
        {
            if(XTCOM_SUCCESS != S_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'T':
        {
            if(XTCOM_SUCCESS != T_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'V':
        {
            if(XTCOM_SUCCESS != V_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'W':
        {
            if(XTCOM_SUCCESS != W_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case 'Z':
        {
            if(XTCOM_SUCCESS != Z_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
    case '@':
        {
            if(XTCOM_SUCCESS != Special_GrpupCommands(&p_fSrc[1],u16_fLength))
            {
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
            
        }break;
        
    default :
        {
            en_lResult = XTCOM_ERROR;
        }       
    }
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t A_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t A_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* */
    INT16U u16_lLength = u16_fLength;
    
    /* Handle TI */
    switch (p_fSrc[0])
    {
    case 'T':
        {
            switch(p_fSrc[2])
            {
            case '\r':
                {
                    /* Call Corresponding function */
                    if(XTP_ERROR == XTP_XTAT((INT8U *)&p_fSrc[1], u16_lLength-1))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }
                }
                break;
                
            default:
                {
                    /* */
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }
        }
        break;
    default:
        {
            /* */
            en_lResult = XTCOM_ERROR;
        }
        break;           
    }
    
    /* Return Result */
    return en_lResult; 
    
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t B_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t B_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;

    /* Return Result */
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t C_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t C_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /*Variable to Hold Length */
    INT16U u16_lLength = u16_fLength;
    
    /* Handle CMD */
    switch (p_fSrc[0])
    {
   
    case 'E':
        {
            switch(p_fSrc[1])
            {
            case 'A':
                {
                    if(('\r' == p_fSrc[2]) || ('\r' == p_fSrc[4]))
                    {
                        if('\r' == p_fSrc[2])
                        {
                            /* Call Corresponding function */
                            if(XTP_ERROR == XTP_XTCEA((INT8U *)&p_fSrc[2], (u16_lLength-2)))
                            {
                                /* Update Error Status */
                                en_lResult = XTCOM_ERROR;
                            }
                            else
                            {
                                /* No Action */
                            }						
                        }
                        else if('\r' == p_fSrc[4])
                        {
                            /* Call Corresponding function */
                            if(XTP_ERROR == XTP_XTCEA((INT8U *)&p_fSrc[2], (u16_lLength-2)))
                            {
                                /* Update Error Status */
                                en_lResult = XTCOM_ERROR;
                            }
                            else
                            {
                                /* No Action */
                            }							
                        }
                    }
                    else
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                }
                break;
                
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }
        }
        break;
    default:
        {
            /* Update Error Status */
            en_lResult = XTCOM_ERROR;
        }
        break;
    } 
    
    /* Return Result */
    return en_lResult;	
}   

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t D_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t D_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /*Variable to Hold Length */
    INT16U u16_lLength = u16_fLength;
    
    switch(p_fSrc[0])
    {
    case '\r':
        {
            if(XTP_ERROR == XTP_CAN_XTD((INT8U *)&p_fSrc[0], (u16_lLength-1)))
            {
                /* Update Error Status */
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
        }
        break;
        
    case '0':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_CAN_XTD((INT8U *)&p_fSrc[0], (u16_lLength-1)))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }	
                }
                break;
                
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }
        }
        break;
        
    case '1':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_CAN_XTD((INT8U *)&p_fSrc[0], (u16_lLength-1)))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }	
                }
                break;
                
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }
        }
        break;
        
    case 'I':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    /* calling the handler of discription protocol*/
                    if(XTP_ERROR == XTP_XTDI((INT8U *)&p_fSrc[1], (u16_lLength-2)))
                    {
                        /* updating the error status*/
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }
                }
                break;
                
            default:
                {
                    /* updating the error status*/
                    en_lResult = XTCOM_ERROR;
                    
                }
                break;
            }
        }
        break;
        
        
    case 'P':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    /* calling the handler of discription protocol*/
                    if(XTP_ERROR == XTP_XTDP((INT8U *)&p_fSrc[1], (u16_lLength-3)))
                    {
                        /* updating the error status*/
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }
                }
                break;
                
            case 'N':
                {
                    switch(p_fSrc[2])
                    {
                    case '\r':
                        {
                            /*calling the handler of discription protocol number */
                            if(XTP_ERROR == XTP_XTDPN((INT8U *)&p_fSrc[1], (u16_lLength-3)))
                            {
                                /*updating the error status */
                                en_lResult = XTCOM_ERROR;
                            }
                            else
                            {
                                /* No Action */
                            }
                        }
                        break;
                        
                    default:
                        {
                            /*updating the error status */
                            en_lResult = XTCOM_ERROR;
                        }
                        break; 
                    }
                }
                break;
                
            default:
                {
                    /*updating the error status */
                    en_lResult = XTCOM_ERROR;
                }
                break; 
            }
        }
        break;

        default:
        {
            /*updating the error status */
            en_lResult = XTCOM_ERROR;
        }
        break; 
    }
    
    /* Return Result */
    return en_lResult;    
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t E_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t E_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* Variable to Hold Length */
    INT16U u16_lLength = u16_fLength;
    
    /* Handle TE */
    switch (p_fSrc[0])
    {
    case '0':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_XTE((INT8U *)&p_fSrc[0], (u16_lLength)))
                    {
                        /* */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }  					
                }
                break;
                
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }             
        }
        break;
        
    case '1':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_XTE((INT8U *)&p_fSrc[0], (u16_lLength)))
                    {
                        /* */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }               
                }
                break;
                
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break;
            } 				
        }
        break;
        
    case 'A':
        {
            switch(p_fSrc[2])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_XTEA((INT8U *)&p_fSrc[1], (u16_lLength)))
                    {
                        /* */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }               
                }
                break;
                
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break;
            } 				
        }
        break;             
    default:
        {
            en_lResult = XTCOM_ERROR;
        }
        break;
    }
    
    /* Return Result */
    return en_lResult; 
    
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t F_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t F_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* Variable to Hold Length */
    INT16U u16_lLength = u16_fLength;
    
    switch(p_fSrc[0])
    {
        case'C':
            {
                switch(p_fSrc[1])
                {
                case 'S':
                    {
                        switch(p_fSrc[2])
                        {
                        case 'H':
                            {
                                if((('\r' == p_fSrc[6]) || ('\r' == p_fSrc[11])))
                                {
                                    if('\r' == p_fSrc[6])
                                    {
                                        if(XTP_ERROR == XTP_XTFCSH((INT8U *)&p_fSrc[3], (u16_lLength-3)))
                                        {
                                            /* Updating Error Status */
                                            en_lResult = XTCOM_ERROR;
                                        }
                                        else
                                        {
                                            /* No Action */
                                        }			
                                    }
                                    else if('\r' == p_fSrc[11])
                                    {
                                        if(XTP_ERROR == XTP_XTFCSH((INT8U *)&p_fSrc[3], (u16_lLength-3)))
                                        {
                                            /* Updating Error Status */
                                            en_lResult = XTCOM_ERROR;
                                        }
                                        else
                                        {
                                            /* No Action */
                                        }			
                                    }
                                    else
                                    {
                                        /* Updating Error Status */
                                        en_lResult = XTCOM_ERROR;
                                    }
                                }
                                else
                                {
                                    /* Updating Error Status */
                                    en_lResult = XTCOM_ERROR;
                                }
                            }
                            break;
                            
                        case 'D':
                            {
                                if(XTP_ERROR == XTP_XTFCSD((INT8U *)&p_fSrc[3], (u16_lLength-3)))
                                {
                                    /* Updating Error Status */
                                    en_lResult = XTCOM_ERROR;
                                }
                                else
                                {
                                    /* No Action */
                                }		
                            }
                            break;
                            
                        case 'M':
                            {
                                switch(p_fSrc[4])
                                {
                                case '\r':
                                    {
                                        if(XTP_ERROR == XTP_XTFCSM((INT8U *)&p_fSrc[0], (u16_lLength)))
                                        {
                                            /* Updating Error Status */
                                            en_lResult = XTCOM_ERROR;
                                        }
                                        else
                                        {
                                            /* No Action */
                                        }	
                                    }
                                    break;
                                    
                                default :
                                    {
                                        /* Updating Error Status */
                                        en_lResult = XTCOM_ERROR;
                                    }
                                    break;				
                                }                           
                            }
                            break;
                            
                        default:
                            {
                                /* Updating Error Status */
                                en_lResult = XTCOM_ERROR;
                            }
                            break; 								
                        }
                        
                    }
                    break;
                    
                default:
                    {
                        /* Updating Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    break;
                }
            }
            break;
            
    case 'I':
        {
            switch(p_fSrc[1]) 
            {
            case '\r':
                {
                    
                    if(XTP_ERROR == XTP_XTFI((INT8U *)&p_fSrc[0], (u16_lLength)))
                    {
                        /* Updating Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }			                    
                }
                break;
                
            default:
                {
                    /* Updating Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break;                 
            }
        }
        break;
        
    case 'P':
        {
            switch(p_fSrc[1])
            {
                case 'A':
                    {
                        if(('\r' == p_fSrc[9]) && (',' == p_fSrc[5]))
                        {
                            if(XTP_ERROR == XTP_XTFPA((INT8U *)&p_fSrc[2], (u16_lLength-3)))
                            {
                                /* Updating Error Status */
                                en_lResult = XTCOM_ERROR;
                            }
                            else
                            {
                                /* No Action */
                            }	 
                        }
                        else
                        {
                            /* Updating Error Status */
                            en_lResult = XTCOM_ERROR; 
                        }
                    }
                    break;
                    
                    default:
                    {
                        /* Updating Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    break;
            }                                  
        }
        break;

    case 'F':
        {
            switch(p_fSrc[1])
            {
                case 'C':
                    {
                        switch(p_fSrc[2])
                        {
                            case 'A':
                            {
                                if(('\r' == p_fSrc[10]) && (',' == p_fSrc[6]))
                                {
                                    if(XTP_ERROR == XTP_XTFFCA((INT8U *)&p_fSrc[3], (u16_lLength-4)))
                                    {
                                        /* Updating Error Status */
                                        en_lResult = XTCOM_ERROR;
                                    }
                                    else
                                    {
                                        /* No Action */
                                    }	 
                                }
                                else
                                {
                                    /* Updating Error Status */
                                    en_lResult = XTCOM_ERROR; 
                                }
                            }
                            break;

                            default:
                            {
                                /* Updating Error Status */
                                en_lResult = XTCOM_ERROR;
                            }
                            break;
                        }                        
                    }
                    break;
                    
                    default:
                    {
                        /* Updating Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    break;
            }                                  
        }
        break;      
        
    default:
        {
            /* Updating Error Status */
            en_lResult = XTCOM_ERROR;
        }
        break;
    }
    return en_lResult;     
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t H_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t H_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* */
    INT16U u16_lLength = u16_fLength;
    
    /* Handle TH */
    switch (p_fSrc[0])
    {
    case '0':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_XTH((INT8U *)&p_fSrc[0], (u16_lLength)))
                    {
                        /* */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }					
                }
                break;
                
            default:
                {
                    /* */
                    en_lResult = XTCOM_ERROR;
                }
            }
            
        }
        break;
        
    case '1':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_XTH((INT8U *)&p_fSrc[0], (u16_lLength)))
                    {
                        /* */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }					
                }
                break;
                
            default:
                {
                    /* */
                    en_lResult = XTCOM_ERROR;
                }
            }		
        }
        break;
        
    default:
        {
            en_lResult = XTCOM_ERROR;
        }
        break;           
    }
    
    /* Return Result */
    return en_lResult;   
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t I_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t I_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* */
    INT16U u16_lLength = u16_fLength;
    
    /* Handle TI */
    switch (p_fSrc[0])
    {
    case '\r':
        {
            
            if(XTP_ERROR == XTP_XTI((INT8U *)&p_fSrc[1], (u16_lLength-1)))
            {
                /* */
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }
        }
        break;
        
    case 'B':
        {
            if(p_fSrc[3] == '\r')
            {
                if(XTP_ERROR == XTP_XTIB((INT8U *)&p_fSrc[1], (u16_lLength-1)))
                {
                    /* Updating Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }	
                
            }
            else
            {
                switch(p_fSrc[1]) 
                {
                case 'R':
                    {
                        if( (p_fSrc[5] == '\r') || (p_fSrc[6] == '\r') || (p_fSrc[7] == '\r') )
                        {
                            if(XTP_ERROR == XTP_XTIBR((INT8U *)&p_fSrc[2], (u16_lLength-2)))
                            {
                                /* Updating Error Status */
                                en_lResult = XTCOM_ERROR;
                            }
                            else
                            {
                                /* No Action */
                            }	
                            
                        }
                        else
                        {
                            /* Updating Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                        
                    }
                    break;
                    
                default:
                    {
                        /* Updating Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    break;                 
                }
                
            }
        }
        break; 
        
    case 'I':
        {
            switch(p_fSrc[1])
            {
            case 'A':
                {
                    switch(p_fSrc[4]) 
                    {
                    case '\r':
                        {
                            
                            if(XTP_ERROR == XTP_XTIIA((INT8U *)&p_fSrc[2], (u16_lLength-2)))
                            {
                                /* Updating Error Status */
                                en_lResult = XTCOM_ERROR;
                            }
                            else
                            {
                                /* No Action */
                            }			                    
                        }
                        break;
                        
                    default:
                        {
                            /* Updating Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                        break;                 
                    }                                      
                }
                break;
                
            default:
                {
                    /* Updating Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }
        }
        break;
        
    case 'A':
        {
            switch(p_fSrc[1])
            {            
            case 'T':
                {
                    switch(p_fSrc[3]) 
                    {
                    case '\r':
                        {
                            
                            if(XTP_ERROR == XTP_XTIAT((INT8U *)&p_fSrc[3], (u16_lLength-3)))
                            {
                                /* Updating Error Status */
                                en_lResult = XTCOM_ERROR;
                            }
                            else
                            {
                                /* No Action */
                            }			                    
                        }
                        break;
                        
                    default:
                        {
                            /* Updating Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                        break;                 
                    }     
                    
                }
                break;
                
            default:
                {
                    /* Updating Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }               
        }
        break;
        
    case 'M':
        {
            switch(p_fSrc[1])
            {
            case 'C':
                {
                    switch(p_fSrc[2])
                    {
                    case 'S':
                        {
                            switch(p_fSrc[4]) 
                            {
                            case '\r':
                                {
                                    
                                    if(XTP_ERROR == XTP_XTIMCS((INT8U *)&p_fSrc[3], (u16_lLength-3)))
                                    {
                                        /* Updating Error Status */
                                        en_lResult = XTCOM_ERROR;
                                    }
                                    else
                                    {
                                        /* No Action */
                                    }			                    
                                }
                                break;
                                
                            default:
                                {
                                    /* Updating Error Status */
                                    en_lResult = XTCOM_ERROR;
                                }
                                break;                 
                            }     
                            
                        }
                        break;
                        
                    default:
                        {
                            /* Updating Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                        break;   
                    }
                    
                }
                break;
                
            default:
                {
                    /* Updating Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break; 
            }
            
        }
        break;
        
    case 'P':
        {
            switch(p_fSrc[1])
            {
            case '1':
                {
                    switch(p_fSrc[2])
                    {
                    case 'X':
                        {
                            if( (p_fSrc[4] == '\r') || (p_fSrc[5] == '\r'))  
                            {
                                if(XTP_ERROR == XTP_XTIP1X((INT8U *)&p_fSrc[3], (u16_lLength-3)))
                                {
                                    /* Updating Error Status */
                                    en_lResult = XTCOM_ERROR;
                                }
                                else
                                {
                                    /* No Action */
                                }	 
                                
                            }
                            else
                            {
                                /* Updating Error Status */
                                en_lResult = XTCOM_ERROR;
                            }
                            
                        }
                        break;
                        
                    default:
                        {
                            /* Updating Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                        break;   
                    }
                    
                }
                break;
                
            case '4':
                {
                    if( (p_fSrc[3] == '\r') || (p_fSrc[4] == '\r'))  
                    {
                        if(XTP_ERROR == XTP_XTIP4((INT8U *)&p_fSrc[3], (u16_lLength-3)))
                        {
                            /* Updating Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                        else
                        {
                            /* No Action */
                        }	 
                        
                    }
                    else
                    {
                        /* Updating Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    
                }
                break;
                
            default:
                {
                    /* Updating Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break;                
            }
            
        }
        break;        
    default:
        {
            /* Updating Error Status */
            en_lResult = XTCOM_ERROR;
        }
        break;           
    }
    
    /* Return Result */
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t J_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t J_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* Local variable to store length*/
    INT16U u16_lLength = u16_fLength;
    
    switch (p_fSrc[0])
    {
      case 'M':
        {
            if(p_fSrc[1] == 'P')
            {
                if(p_fSrc[2] == 'N')
                {
                    if(XTP_ERROR ==  XTP_XTJMPN((INT8U *)&p_fSrc[3], (u16_lLength-4)))
                    {
                         /* Updating Error Status */
                         en_lResult = XTCOM_ERROR;
                    }
                }
                else if(XTP_ERROR ==  XTP_XTJMP((INT8U *)&p_fSrc[2], (u16_lLength-3)))
                {
                    /* Updating Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                else
                {
                      /* No action */
                }	
                
            }
            else if(p_fSrc[1] == 'A')
            {
                if(XTP_ERROR ==  XTP_XTJMA((INT8U *)&p_fSrc[2], (u16_lLength-1)))
                {
                    /* Updating Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }
            }
            else
            {
               /* Updating Error Status */
               en_lResult = XTCOM_ERROR;
            }
        }       
        break;  
        
        case 'T':
        {
            if(p_fSrc[1] == 'P')
            {
                XTP_XTJTP((INT8U *)&p_fSrc[2], (u16_lLength-4));
            }
            else
            {
                /* Updating Error Status */
                en_lResult = XTCOM_ERROR;
            }
        }
        break;
        case 'D':
          {
             if(p_fSrc[1] == 'M')
             {
                if(XTP_ERROR ==  XTP_XTJDM((INT8U *)&p_fSrc[2], (u16_lLength-3)))
                {
                     /* Updating Error Status */
                     en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }
             }
              else if(p_fSrc[1] == 'A')
             {
                if(XTP_ERROR ==  XTP_XTJDA((INT8U *)&p_fSrc[2], (u16_lLength-3)))
                {
                     /* Updating Error Status */
                     en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }
                
             }
             else
             {
               /* Updating Error Status */
                en_lResult = XTCOM_ERROR;
             }
          }
          break;
         case 'N':
        {
            if(p_fSrc[1] == 'M')
            {
                XTP_XTJNM((INT8U *)&p_fSrc[3], (u16_lLength-4));
            }
            else
            {
                /* Updating Error Status */
                en_lResult = XTCOM_ERROR;
            }
        }
         break;
         
        default:
        {
            /* Updating Error Status */
            en_lResult = XTCOM_ERROR;
        }
        break;                 
     } 
    
    /* Return Result */
    return en_lResult; 
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t K_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t K_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* */
    INT16U u16_lLength = u16_fLength;    
    
    switch(p_fSrc[0])
    {
    case 'W':
        {
            if(p_fSrc[1] == '\r')
            {
                if(XTP_ERROR == XTP_XTKW((INT8U *)&p_fSrc[1], (u16_lLength-1)))
                {
                    /* Updating Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }	 
            }
            else
            {
                switch(p_fSrc[2]) 
                {
                case '\r':
                    {
                        
                        if(XTP_ERROR == XTP_XTKW((INT8U *)&p_fSrc[1], (u16_lLength-1)))
                        {
                            /* Updating Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                        else
                        {
                            /* No Action */
                        }			                    
                    }
                    break;
                    
                default:
                    {
                        /* Updating Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    break;                 
                }                   
            }
        }
        break;
        
    default:
        {
            /* Update Error Status */
            en_lResult = XTCOM_ERROR;  
        }
        break;
    }
    
    /* Return Result */
    return en_lResult; 
    
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t L_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t L_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;

    /* Return Result */
    return en_lResult; 
    
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t M_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t M_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* Variable to Hold Length */
    INT16U u16_lLength = u16_fLength;
    
    /* Handle MFR */
    switch (p_fSrc[0])
    {
    case 'A':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_XTMA((INT8U *)&p_fSrc[0], (u16_lLength)))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }                  
                }
                break;
                
            default:
                {
                    /* */
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }
        }
        break;
        
    case 'F':
        {
            switch(p_fSrc[1])
            {
            case 'R':
                {
                    switch(p_fSrc[2])
                    {
                    case '\r':
                        {
                            if(XTP_ERROR == XTP_XTMFR((INT8U *)&p_fSrc[3], (u16_lLength-3)))
                            {
                                /* Update Error Status */
                                en_lResult = XTCOM_ERROR;
                            }
                            else
                            {
                                /* No Action */
                            } 
                        }
                        break;
                        
                    default:
                        {
                            /* */
                            en_lResult = XTCOM_ERROR;
                        }
                    }
                }
                break;
                
            default:
                {
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }
        }
        break;
    case 'R':
        {
            switch(p_fSrc[4])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_XTMR((INT8U *)&p_fSrc[1], (u16_lLength-2)))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    } 
                }
                break;
                
            default:
                {
                    /* */
                    en_lResult = XTCOM_ERROR;
                }
            }
        }
        break;
        
    case '0':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_GNRL_XTM((INT8U *)&p_fSrc[0], (u16_lLength)))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }
                }
                break;
                
            default:
                {
                    /* */
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }
        }
        break;
    case '1':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_GNRL_XTM((INT8U *)&p_fSrc[0], (u16_lLength)))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }
                }
                break;
                
            default:
                {
                    /* */
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }
        }
        break;
        
      case 'H':
        {   
            /* Call Corresponding function */
            if(XTP_ERROR == XTP_XTMH((INT8U *)&p_fSrc[1], 20))
            {
                /* Update Error Status */
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }	
            
        }
        break;
        
    default:
        {
            en_lResult = XTCOM_ERROR;
        }
        break;           
    }
    
    /* Return Result */
    return en_lResult; 
    
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t N_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t N_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;

    /* Return Result */
    return en_lResult; 
    
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t P_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t P_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* Handle TI */
    switch (p_fSrc[0])
    {
    case 'P':
        {
            if( '\r' == p_fSrc[2])
            {
                switch(p_fSrc[1])
                {
                case 'S':
                    {
                        /* Calling the Handler of Read Voltage */
                        if(XTP_ERROR == XTP_XTPPS((INT8U *)&p_fSrc[0], 2))
                        {
                            /* */
                            en_lResult = XTCOM_ERROR; 
                        }
                        else
                        {
                            /* Do Nothing */
                        }
                    }
                    break;
                default:
                    {
                        /* */
                        en_lResult = XTCOM_ERROR;
                    }
                    break; 
                }
            }
            else if(('\r' == p_fSrc[5]) || ('\r' == p_fSrc[6]) || ('\r' == p_fSrc[7]))
            {
                switch(p_fSrc[3])
                {
                case 'O':
                    {
                        
                        switch(p_fSrc[4])
                        {
                        case 'N':
                            {
                                /* Calling the Handler of Read Voltage */
                                if(XTP_ERROR == XTP_XTPPON((INT8U *)&p_fSrc[1], 2))
                                {
                                    /* */
                                    en_lResult = XTCOM_ERROR; 
                                }
                                else
                                {
                                    /* Do Nothing */
                                }                    
                            }
                            break;
                        case 'F':
                            {
                                switch(p_fSrc[5])
                                {
                                case 'F':
                                    {
                                        /* Calling the Handler of Read Voltage */
                                        if(XTP_ERROR == XTP_XTPPOFF((INT8U *)&p_fSrc[1], 2))
                                        {
                                            /* */
                                            en_lResult = XTCOM_ERROR; 
                                        }
                                        else
                                        {
                                            /* Do Nothing */
                                        }
                                    }
                                    break;
                                    
                                default:
                                    {
                                        /* */
                                        en_lResult = XTCOM_ERROR;
                                    }
                                    break;
                                    
                                }
                                
                            }
                            break;
                            
                        default:
                            {
                                /* */
                                en_lResult = XTCOM_ERROR;
                            }
                            break;
                        }
                        
                    }
                    break;
                    
                case 'S':
                    {
                        switch(p_fSrc[4])
                        {
                        case 'V':
                            {
                                /* Calling the Handler of Read Voltage */
                                if(XTP_ERROR == XTP_XTPPSV((INT8U *)&p_fSrc[1], 2))
                                {
                                    /* */
                                    en_lResult = XTCOM_ERROR; 
                                }
                                else
                                {
                                    /* Do Nothing */
                                }
                            }
                            break;
                            
                        default:
                            {
                                /* */
                                en_lResult = XTCOM_ERROR;
                            }
                            break;
                            
                        }                                   
                    }
                    break;
                    
                default:
                    {
                        /* */
                        en_lResult = XTCOM_ERROR;
                    }
                    break;                           
                }
            }
            else
            {
                /* */
                en_lResult = XTCOM_ERROR;            
            }
        }
        break;
        
    case '2':
        {
            switch(p_fSrc[1])
            {
            case '5':
                {
                    switch(p_fSrc[2])
                    {
                    case '\r':
                        {
                            /* Calling the Handler of Read Voltage */
                            if(XTP_ERROR == XTP_XTP((INT8U *)&p_fSrc[0], 2))
                            {
                                /* */
                                en_lResult = XTCOM_ERROR; 
                            }
                            else
                            {
                                /* Do Nothing */
                            }
                        }
                        break;
                        
                    default:
                        {
                            /* */
                            en_lResult = XTCOM_ERROR;
                        }
                        break;   
                    }
                }
                break;
                
            default:
                {
                    /* */
                    en_lResult = XTCOM_ERROR;
                }
                break;                         
            }
        }
        break;
        
    case '3':
        {
            switch(p_fSrc[1])
            {
            case '3':
                {
                    switch(p_fSrc[2])
                    {
                    case '\r':
                        {
                            /* Calling the Handler of Read Voltage */
                            if(XTP_ERROR == XTP_XTP((INT8U *)&p_fSrc[0], 2))
                            {
                                /* */
                                en_lResult = XTCOM_ERROR; 
                            }
                            else
                            {
                                /* Do Nothing */
                            }
                        }
                        break;
                        
                    default:
                        {
                            /* */
                            en_lResult = XTCOM_ERROR;
                        }
                        break;   
                    }
                }
                break;
                
            default:
                {
                    /* */
                    en_lResult = XTCOM_ERROR;
                }
                break;                         
            }
        }
        break;        
    default:
        {
            /* */
            en_lResult = XTCOM_ERROR;
        }
        break;           
    }
    
    /* Return Result */
    return en_lResult; 
    
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t R_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t R_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* Variable to Hold Length*/
    INT16U u16_lLength = u16_fLength;
    
    switch (p_fSrc[0])
    {	
    case 'B':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_XTRB((INT8U *)&p_fSrc[0], (u16_lLength)))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }	
                }
                break;
                
            default:
                {
                    /* updating error status*/
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }
        }
        break;

    case 'V':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    /* Calling the Handler of Read Voltage */
                    if(XTP_ERROR == XTP_XTRV((INT8U *)&p_fSrc[1], (u16_lLength-2)))
                    {
                        /* update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }    
                }
                break;
                
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break; 
            }
        }
        break;
        
    case 'H':
        {
            if('\r' == p_fSrc[4])
            {
                /* Send to ATSH */
                if(XTP_ERROR == XTP_XTRH((INT8U *)&p_fSrc[1], (u16_lLength-2)))
                {
                    /* update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }			
            }
            else if('\r' == p_fSrc[7])
            {
                
                /* Send to ATSH */
                if(XTP_ERROR == XTP_XTRH((INT8U *)&p_fSrc[1], 6))
                {
                    /* update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }
            }
            else
            {
                /* update Error Status */
                en_lResult = XTCOM_ERROR;
            }        
        }
        break;   
        
     case 'Q':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_XTRQ((INT8U *)&p_fSrc[0], (u16_lLength)))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }	
                }
                break;
                
            default:
                {
                    /* updating error status*/
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }
        }
        break;
        
        case 'S':
        {
            switch(p_fSrc[1])
            {
            case 'T':
                {
                    if(XTP_ERROR == XTP_XTRST((INT8U *)&p_fSrc[0], (u16_lLength)))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }	
                }
                break;
                
            default:
                {
                    /* updating error status*/
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }
        }
        break;
        
    default:
        {
            /* Update Error Status */
            en_lResult = XTCOM_ERROR;
        }
        break; 
    }
    
    /* Return Result */
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t S_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t S_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* */
    INT16U u16_lLength = u16_fLength;
    
    /* ptr to hold character found */
    INT8U * p_lPtr = 0;
    
    /* Handle SN */
    switch (p_fSrc[0])
    {
    case '0':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_XTS((INT8U *)&p_fSrc[0], (u16_lLength)))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }					
                }
                break;
                
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
            }
        }
        break;
        
    case '1':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_XTS((INT8U *)&p_fSrc[0], (u16_lLength)))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }					
                }
                break;
                
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }		
        }
        break;
        
    case 'A':
        {
            switch(p_fSrc[1])
            {
            case 'T':
                {
                    switch(p_fSrc[2])
                    {
                    case 'I':
                        {
                            /* Search for \r */
                            p_lPtr = (INT8U *)strchr((const char *)&p_fSrc[0], '\r');
                            
                            /* */
                            if(NULL != p_lPtr)
                            {
                                if((&p_lPtr[0] - &p_fSrc[0]) <= 16)
                                {
                                    /* Call Corresponding Handler */
                                    if(XTP_ERROR == XTP_XTSATI((INT8U *)&p_fSrc[3], (INT16U)(&p_lPtr[0] - &p_fSrc[3])))
                                    {
                                        /* update Error Status */
                                        en_lResult = XTCOM_ERROR;
                                    }
                                    else
                                    {
                                        /* No Action */
                                    }
                                }
                                else
                                {
                                    /* update Error Status */
                                    en_lResult = XTCOM_ERROR;
                                }
                            }
                            else
                            {
                                /* update Error Status */
                                en_lResult = XTCOM_ERROR;
                            }
                        }
                        break;
                        
                    default:
                        {
                            /* update Error Status */
                            en_lResult = XTCOM_ERROR;						
                        }
                        break;
                    }
                }
                break;
                
            default:
                {
                    /* update Error Status */
                    en_lResult = XTCOM_ERROR;				
                }
                break;
            }
        }
        break;
        
        case 'B':
        {
            switch(p_fSrc[1])
            {
            case 'R':
                {
                    /* Search for \r */
                    p_lPtr = (INT8U *)strchr((const char *)&p_fSrc[0], '\r');
                    
                    /* */
                    if(NULL != p_lPtr)
                    {
                        if((&p_lPtr[0] - &p_fSrc[0]) <= 16)
                        {
                            /* Call Corresponding Handler */
                            if(XTP_ERROR == XTP_XTSBR((INT8U *)&p_fSrc[2], (INT16U)(&p_lPtr[0] - &p_fSrc[2])))
                            {
                                /* update Error Status */
                                en_lResult = XTCOM_ERROR;
                            }
                            else
                            {
                                /* No Action */
                            }
                        }
                        else
                        {
                            /* update Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                    }
                    else
                    {
                        /* update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }  
               }
                break;
                
                default:
                {
                    /* update Error Status */
                    en_lResult = XTCOM_ERROR;				
                }
                break;
            }
        }
        break;
    
        
    case 'C':
        {
            switch(p_fSrc[1])
            {
            case 'F':
                {
                    switch(p_fSrc[2])
                    {
                    case 'H':
                        {
                            if(('\r' == p_fSrc[10]) && (',' == p_fSrc[6]))
                            {
                                if(XTP_ERROR == XTP_XTSCFH((INT8U *)&p_fSrc[3], (u16_lLength-4)))
                                {
                                    /* Updating Error Status */
                                    en_lResult = XTCOM_ERROR;
                                }
                                else
                                {
                                    /* No Action */
                                }	 
                            }
                            else
                            {
                                /* Updating Error Status */
                                en_lResult = XTCOM_ERROR; 
                            }                                                           
                        }
                        break;
                        
                    default:
                        {
                            /* update Error Status */
                            en_lResult = XTCOM_ERROR;						
                        }
                        break;
                    }
                }
                break;
                
            default:
                {
                    /* update Error Status */
                    en_lResult = XTCOM_ERROR;				
                }
                break;
            }           
        }
        break;
        
    case 'H':
        {
            if('\r' == p_fSrc[4])
            {
                /* Send to ATSH */
                if(XTP_ERROR == XTP_XTSH((INT8U *)&p_fSrc[1], (u16_lLength-2)))
                {
                    /* update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }			
            }
            else if('\r' == p_fSrc[5])
            {
                /* Send to ATSH */
                if(XTP_ERROR == XTP_XTSH((INT8U *)&p_fSrc[1], (u16_lLength-2)))
                {
                    /* update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }			
            }
            else if('\r' == p_fSrc[7])
            {
                
                /* Send to ATSH */
                if(XTP_ERROR == XTP_XTSH((INT8U *)&p_fSrc[1], 6))
                {
                    /* update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }
            }
            else
            {
                /* update Error Status */
                en_lResult = XTCOM_ERROR;
            }
        }
        break;
        
    case 'P':
        {
            if('\r' == p_fSrc[2])
            {               
                /* Send to ATSH */
                if(XTP_ERROR == XTP_XTSP((INT8U *)&p_fSrc[1], (u16_lLength-1)))
                {
                    /* update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }
            }
            else
            {
               /* update Error Status */
                en_lResult = XTCOM_ERROR;
            }
        }
        break;
        
    case 'T':
        {
            switch(p_fSrc[3])
            {
            case '\r':
                {	
                    /* Send to ATST */
                    if(XTP_ERROR == XTP_XTST((INT8U *)&p_fSrc[1], (u16_lLength-1)))
                    {
                        /* update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }
                }
                break;
                
            default:
                {
                    /* */
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }
        }
        break;
        
    case 'N':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_ERROR == XTP_XTSN((INT8U *)&p_fSrc[2], (u16_lLength-2)))
                    {
                        /* update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }
                }
                break;
                
            default:
                {
                    en_lResult = XTCOM_ERROR;
                }
                break;
            }
        }
        break;
        
    case '@' :
        {
            switch(p_fSrc[1])
            {
            case '1' :
                {
                    switch(p_fSrc[2])
                    {
                    case '\r':
                        {
                            /* Call the Corresponding Handler */
                            if(XTP_ERROR == XTP_XTA((INT8U *)&p_fSrc[1], 1))
                            {
                                /* update Error Status */
                                en_lResult = XTCOM_ERROR;
                            }
                            else
                            {
                                /* No Action */
                            }		
                        }
                        break;
                        
                    default:
                        {
                            /* Update Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                        break;
                    }
                }
                break;
                
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
            }
        }
        break;
        
    case 'I':
        {
            switch(p_fSrc[1]) 
            {
            case '\r':
                {
                    
                    if(XTP_ERROR == XTP_XTSI((INT8U *)&p_fSrc[0], (u16_lLength)))
                    {
                        /* Updating Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }			                    
                }
                break;
                
            default:
                {
                    /* Updating Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break;                 
            }
        }
        break;
        
    case 'W':
        {
            if(p_fSrc[2] == '\r')
            {
                if(XTP_ERROR == XTP_XTSW((INT8U *)&p_fSrc[1], (u16_lLength-1)))
                {
                    /* Updating Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }	 
            }
            else
            {
                switch(p_fSrc[3]) 
                {
                case '\r':
                    {
                        
                        if(XTP_ERROR == XTP_XTSW((INT8U *)&p_fSrc[1], (u16_lLength-1)))
                        {
                            /* Updating Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                        else
                        {
                            /* No Action */
                        }			                    
                    }
                    break;
                    
                default:
                    {
                        /* Updating Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    break;                 
                }                   
            }
        } 
        break;
        
    case 'L':
        {
            switch(p_fSrc[1])
            {
            case 'C':
                {
                    switch(p_fSrc[2])
                    {
                    case 'S' :
                        {
                            switch(p_fSrc[3])
                            {
                            case '\r':
                                {
                                    /* Call the Corresponding Handler */
                                    if(XTP_ERROR == XTP_XTSLCS((INT8U *)&p_fSrc[1], 1))
                                    {
                                        /* update Error Status */
                                        en_lResult = XTCOM_ERROR;
                                    }
                                    else
                                    {
                                        /* No Action */
                                    }		
                                }
                                break;
                                
                            default:
                                {
                                    /* Update Error Status */
                                    en_lResult = XTCOM_ERROR;
                                }
                                break;
                            }
                        }
                        break;
                        
                    default:
                        {
                            /* Update Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                    }                  
                }
                break;
                
            case 'L':
                {
                    switch(p_fSrc[2])
                    {
                    case 'T' :
                        {
                            switch(p_fSrc[3])
                            {
                            case '\r':
                                {
                                    /* Call the Corresponding Handler */
                                    if(XTP_ERROR == XTP_XTSLLT((INT8U *)&p_fSrc[1], 1))
                                    {
                                        /* update Error Status */
                                        en_lResult = XTCOM_ERROR;
                                    }
                                    else
                                    {
                                        /* No Action */
                                    }		
                                }
                                break;
                                
                            default:
                                {
                                    /* Update Error Status */
                                    en_lResult = XTCOM_ERROR;
                                }
                                break;
                            }
                        }
                        break;
                        
                    default:
                        {
                            /* Update Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                    }                  
                }
                break;
            case 'P':
                {
                    switch(p_fSrc[2])
                    {
                    case 'C' :
                        {
                            switch(p_fSrc[3])
                            {
                            case 'P' :
                                {
                                    switch(p_fSrc[5])
                                    {
                                    case '\r':
                                        {
                                            /* Call the Corresponding Handler */
                                            if(XTP_ERROR == XTP_XTSLPCP((INT8U *)&p_fSrc[1], 1))
                                            {
                                                /* update Error Status */
                                                en_lResult = XTCOM_ERROR;
                                            }
                                            else
                                            {
                                                /* No Action */
                                            }		
                                        }
                                        break;
                                        
                                    default:
                                        {
                                            /* Update Error Status */
                                            en_lResult = XTCOM_ERROR;
                                        }
                                        break;
                                    }
                                }
                                break;
                                
                            default:
                                {
                                    /* Update Error Status */
                                    en_lResult = XTCOM_ERROR;
                                }
                            }
                        }
                        break;
                        
                    default:
                        {
                            /* Update Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                    }                  
                }
                break;
                
            case 'X':
                {
                    switch(p_fSrc[2])
                    {
                    case 'P' :
                        {
                            switch(p_fSrc[4])
                            {
                            case '\r':
                                {
                                    /* Call the Corresponding Handler */
                                    if(XTP_ERROR == XTP_XTSLXP((INT8U *)&p_fSrc[1], 1))
                                    {
                                        /* update Error Status */
                                        en_lResult = XTCOM_ERROR;
                                    }
                                    else
                                    {
                                        /* No Action */
                                    }		
                                }
                                break;
                                
                            default:
                                {
                                    /* Update Error Status */
                                    en_lResult = XTCOM_ERROR;
                                }
                                break;
                            }
                        }
                        break;
                        
                    case 'S':
                        {
                            switch(p_fSrc[3])
                            {
                            case '\r':
                                {
                                    /* Call the Corresponding Handler */
                                    if(XTP_ERROR == XTP_XTSLXS((INT8U *)&p_fSrc[1], 1))
                                    {
                                        /* update Error Status */
                                        en_lResult = XTCOM_ERROR;
                                    }
                                    else
                                    {
                                        /* No Action */
                                    }		
                                }
                                break;
                                
                            default:
                                {
                                    /* Update Error Status */
                                    en_lResult = XTCOM_ERROR;
                                }
                                break;
                            }                         
                        }
                        break;
                        
                    default:
                        {
                            /* Update Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                    }                  
                }
                break;
            default:
                {
                    /* Updating Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                break;             
            }
            
        }
        break;
        
        
    default:
        {
            /* Update Error Status */
            en_lResult = XTCOM_ERROR;
        }
        break;           
    }
    
    /* Return Result */
    return en_lResult;   
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t T_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t T_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    /* */
    INT16U u16_lLength = u16_fLength;   
    
    switch(p_fSrc[0])
    {
    case 'P':
        {
            if('\r' == p_fSrc[2])
            {				
                /* Call the Corresponding Handler */
                if(XTP_ERROR == XTP_XTTP((INT8U *)&p_fSrc[1], 1))
                {
                    /* update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }		
            }
            else
            {
                switch(p_fSrc[2])
                {
                case 'A':
                    {
                        if('\r' == p_fSrc[3])
                        {
                            /* */
                            XTP_XTTPA((INT8U *)&p_fSrc[2], (u16_lLength-2));
                        }
                        else
                        {
                            /* update Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                    }
                    break;
                    
                default:
                    {
                        /* update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    break;
                }
            }
        }
        break; 
         case 'M':
        {
             /* Call the Corresponding Handler */
                if(XTP_ERROR == XTP_XTTM((INT8U *)&p_fSrc[1], 4))
                {
                    /* update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }	
        }
        break;  
        
        default :
        {
            /* update Error Status */
            en_lResult = XTCOM_ERROR;  
        }
        break;  
                          
    }
    
    /* Return Result */
    return en_lResult;     
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t V_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t V_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;

    /* Return Result */
    return en_lResult; 
    
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t W_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t W_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    INT16U u16_lLength = u16_fLength-1;
    
    switch(p_fSrc[0])
    {
      
    case 'M':
        {
            if( (p_fSrc[3] == '\r') || (p_fSrc[5] == '\r') || (p_fSrc[7] == '\r')  \
                || (p_fSrc[9] == '\r') || (p_fSrc[11] == '\r') || (p_fSrc[13] == '\r') )
            {
                if(XTP_SUCCESS !=  XTP_XTWM((INT8U *)&p_fSrc[1], u16_lLength-1))
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
                else
                {
                    /* No Action */
                }   
                
            }
            else
            {
                /* Update Error Status */
                en_lResult = XTCOM_ERROR;
            }
            
        }
        break;
        
    case 'R':
        {
            switch(p_fSrc[1])
            {
            case 'S':
                {
                    if(p_fSrc[27] == '\r' || p_fSrc[5] == '\r')
                    {
                        //                        if(XTP_SUCCESS !=  XTP_XTWRS((INT8U *)&p_fSrc[2], u16_lLength))
                        //                        {
                        //                            /* Update Error Status */
                        //                            en_lResult = XTCOM_ERROR;
                        //                        }
                        //                        else
                        //                        {
                        //                            /* No Action */
                        //                        }                        
                    }
                    else
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    
                }
                break;
                
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
            }
        }
        break;
        
    case 'B':
        {
            switch(p_fSrc[1])
            {
            case 'R':
                {
                    switch(p_fSrc[2])
                    {
                    case '\r':
                        {
                            if(XTP_SUCCESS !=  XTP_XTWBR((INT8U *)&p_fSrc[1], u16_lLength))
                            {
                                /* Update Error Status */
                                en_lResult = XTCOM_ERROR;
                            }
                            else
                            {
                                /* No Action */
                            }  
                        }
                        break;
                        
                    default:
                        {
                            /* Update Error Status */
                            en_lResult = XTCOM_ERROR;
                        }
                    }
                    
                }
                break;
                
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
            }
        }
        break;
        
    default:
        {
            /* Update Error Status */
            en_lResult = XTCOM_ERROR;
        } 
    }    
    
    /* Return Result */
    return en_lResult; 
    
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t Z_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t Z_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    INT16U u16_lLength = u16_fLength-1;
    
    switch(p_fSrc[0])
    {
    case '\r':
        {
            if(XTP_SUCCESS !=  XTP_XTZ((INT8U *)&p_fSrc[1], u16_lLength))
            {
                /* Update Error Status */
                en_lResult = XTCOM_ERROR;
            }
            else
            {
                /* No Action */
            }  
        }
        break;
        
    default:
        {
            /* Update Error Status */
            en_lResult = XTCOM_ERROR;
        } 
    }    
    
    /* Return Result */
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   : EN_XTCOM_RESULT_t Special_GrpupCommands(const INT8U *p_fSrc,                    */
/*                                                                      const INT16U u16_fLength)    */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTCOM_RESULT_t Special_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTCOM_RESULT_t en_lResult = XTCOM_SUCCESS;
    
    INT16U u16_lLength = u16_fLength-1;
    
    switch(p_fSrc[0])
    {       
    case '1':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_SUCCESS !=  XTP_XTA((INT8U *)&p_fSrc[0], u16_lLength))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    }	 		
                }
                break;
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
            }	  
        }
        break;
        
    case '2':
        {
            switch(p_fSrc[1])
            {
            case '\r':
                {
                    if(XTP_SUCCESS !=  XTP_XTA((INT8U *)&p_fSrc[1], u16_lLength))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    } 
                }
                break;
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
            }
        }
        break;
        
    case '3':
        {
            switch(p_fSrc[13])
            {
            case '\r':
                {
                    if(XTP_SUCCESS !=  XTP_XTA((INT8U *)&p_fSrc[1], u16_lLength))
                    {
                        /* Update Error Status */
                        en_lResult = XTCOM_ERROR;
                    }
                    else
                    {
                        /* No Action */
                    } 
                    
                }
                break;
            default:
                {
                    /* Update Error Status */
                    en_lResult = XTCOM_ERROR;
                }
            }
        }
        break;
        
    default:
        {
            /* Update Error Status */
            en_lResult = XTCOM_ERROR;
        }	 
    }
    
    /* Return Result */
    return en_lResult; 
}

/**************************************************************************************************/
/* Function Name   : EN_CMD_TYPE_t XTCOM_Check_AT_ST_XT( const INT8U *p_fSrc, const INT16U u16_fLength) */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_CMD_TYPE_t XTP_Check_AT_ST_XT( const INT8U *p_fSrc, const INT16U u16_fLength) 
{
    
    EN_CMD_TYPE_t en_lCmdType = CMD_AT;
    
    if(('A' == p_fSrc[0]) && ('T' == p_fSrc[1]))
    {
        /* No action */
    }
    else if(('S' == p_fSrc[0]) && ('T' == p_fSrc[1]))
    {
        /* */
        en_lCmdType = CMD_ST;
    }
    else if(('X' == p_fSrc[0]) && ('T' == p_fSrc[1]))
    {
        /* */
        en_lCmdType = CMD_XT;
    }
    else 
    {
        en_lCmdType = CMD_ERROR;
    }
    
    return en_lCmdType;
}

/**************************************************************************************************/
/* Function Name   :  void CAN_DISPLAY(ISO_RxData_t * p_fCanDispData)                             */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

INT8U au8_lDisplayBuff[12288] = {0x00,};
INT16U u16_gDispIndex = 0x00;
INT8U u8_gHeadrflag = 0x00;

void CAN_DISPLAY(INT32U u32_fCANID, const INT8U *p_fData , INT32U u132_fLength)
{    
    /* */
    u16_gDispIndex = 0x00;
    INT8U u8_lIndex = 0;
    INT8U u8_lFrameIndx = 0x01;
    INT8U LengthCopy,LengthNibble = 0x10;
    INT8U u8_gConsegutveIndex = 0x01;
    INT16U u16_loffset = 0x06;
    
    /* Fill the Total Buffer with Space  */
    memset(&au8_lDisplayBuff[0] , ' ' ,12288);
    
    if(8 <= u132_fLength)
    {     
        /* Check For Header ON*/
        if(1 == u8_gHeaderFlag)
        {
           /* Convert The Target Address to PAN Format */
            COMMON_Word2PAN(&au8_lDisplayBuff[u16_gDispIndex], u32_fCANID); 
            /* Increment Idesx Including Space */
            u16_gDispIndex = u16_gDispIndex + 9;
            //else
            {
                if(1 == u8_gDLCFlag)
                {
                    /* Convert The Target Address to PAN Format */
                    COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], 8);
                    u16_gDispIndex = u16_gDispIndex + 2;

                    /* */
                    if(1 == u8_gIctSpaceFlag)
                    {
                        au8_lDisplayBuff[u16_gDispIndex] = ' ';                
                        u16_gDispIndex = u16_gDispIndex + 1;
                    }
                    else
                    {
                        /* No Action */
                    }
                }
                /* Copy the Nibble and Frame the Data */
                LengthCopy = (u132_fLength >> 8);
                LengthNibble = LengthNibble | LengthCopy;

                /* Convert The Target Address to PAN Format */
                COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], LengthNibble);                
                 /* Increment Idesx Including Space */
                u16_gDispIndex = u16_gDispIndex + 3;
                
                 /* Convert The Target Address to PAN Format */
                COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], u132_fLength); 
                 /* Increment Idesx Including Space */
                u16_gDispIndex = u16_gDispIndex + 3;
      
                for(INT16U u16_lIndex = 0 ; u16_lIndex < 6; u16_lIndex++)
                {    
                    /* Convert the Data into an PAN format */
                    COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], p_fData[u16_lIndex]);    
                     /* Increment Idesx Including Space */
                    u16_gDispIndex = u16_gDispIndex + 3;

                    /* Chek the Ending Byte and Dnt  */
                    if(u16_lIndex == 5)
                    {
                       au8_lDisplayBuff[u16_gDispIndex -1] = '\n';                       
                    }
                    else
                    {
                        /* No Action */
                    }

                }
          
                 u8_gHeadrflag = 0x01;
                
                goto B;
//                /* Startig Index 6 because 6 bytes Are already framed in Abou */
//                 INT16U u16_loffset = 0x06;
//                 for(INT16U u16_lIndex = 0; u16_loffset < u132_fLength;)
//                 {
////                    /* Convert The Target Address to PAN Format */
////                    COMMON_Word2PAN(&au8_lDisplayBuff[u16_gDispIndex], u32_fCANID);              
////                    u16_gDispIndex = u16_gDispIndex + 9;
////
////                    /* Convert The Target Address to PAN Format */
////                   COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], (0x20 | u8_gConsegutveIndex));
//                   
//                    /* Increment Idesx Including Space */
//                    u16_gDispIndex = u16_gDispIndex + 3;
//
//                    /* Cop the & Bytes Per iteration */
//                    for(INT8U u8_lIndex = 0x00; u8_lIndex < 7 ; u8_lIndex++)
//                    {
//                        /* Convert The Target Address to PAN Format */
//                        COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], p_fData[u16_loffset]);
//                        u16_gDispIndex = u16_gDispIndex + 2; 
//                        
//                        /* Increment the Offset For data */
//                        u16_loffset = u16_loffset + 1;
//                        
//                        if(u16_loffset == u132_fLength)
//                        {
//                           INT8U u8_lRemng = 0x00;
//                           
//                          /* Increment Idesx for Space */
//                           u16_gDispIndex = u16_gDispIndex + 1;
//                           
//                           /* Calculating the Remaining Bytes to Fill 0xAA */
//                           u8_lRemng = 6 - u8_lIndex;
//                            
//                           /* Fill with 0xAA */
//                           for(int i= 0x00 ; i< u8_lRemng ;i++)
//                           {
//                                /* Convert the Data into an PAN format */
//                                COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], 0xAA);
//                                
//                                /* Increment Idesx Including Space */
//                                u16_gDispIndex = u16_gDispIndex + 3;     
//                           }                        
//                           break;
//                        }
//                        else
//                        {
//                            /* Increment Idesx for Space */
//                            u16_gDispIndex = u16_gDispIndex + 1;
//                        }
//                    }
//                    
//                    /* Append \n */
//                    au8_lDisplayBuff[u16_gDispIndex-1] = '\n';                  
//                    
//                    /* */
//                    if(0x0F == u8_gConsegutveIndex)
//                    {
//                       u8_gConsegutveIndex = 0x00;
//                    }
//                    else
//                    {
//                       /* */
//                       u8_gConsegutveIndex = u8_gConsegutveIndex + 1;
//                    }   
//                    
//                 }  
          }
        }
        else
        {
            /* Convert The Target length to PAN Format */
            COMMON_HWord2PAN(&au8_lDisplayBuff[u16_gDispIndex], u132_fLength);
             /* Increment Idesx  */
            u16_gDispIndex = u16_gDispIndex + 4;
            
            /* */
            if(1 == u8_gIctSpaceFlag)
            {
                au8_lDisplayBuff[u16_gDispIndex] = ' ';                
                u16_gDispIndex = u16_gDispIndex + 1;
            }
            else
            {
                /* No Action */
            }
           
            /* Append the 0: */
            strcpy((char *)&au8_lDisplayBuff[u16_gDispIndex], "0:");
             /* Increment Idesx  */
            u16_gDispIndex = u16_gDispIndex + 2;
            
            /* */
            if(1 == u8_gIctSpaceFlag)
            {
                au8_lDisplayBuff[u16_gDispIndex] = ' ';                
                u16_gDispIndex = u16_gDispIndex + 1;
            }
            else
            {
                /* No Action */
            }

            for(INT16U u16_lIndex = 0 ; u16_lIndex < 6; u16_lIndex++)
            {    
                /* Convert the Data into an PAN format */
                COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], p_fData[u16_lIndex]); 
                 /* Increment Idesx  */
                u16_gDispIndex = u16_gDispIndex + 2;
                
                /* */
                if(1 == u8_gIctSpaceFlag)
                {
                    au8_lDisplayBuff[u16_gDispIndex] = ' ';                
                    u16_gDispIndex = u16_gDispIndex + 1;
                }
                else
                {
                    /* No Action */
                }
            
                /* Chek the Ending Byte and Dnt  */
                if(u16_lIndex == 5)
                {
                   au8_lDisplayBuff[u16_gDispIndex -1] = '\n';                       
                }
                else
                {
                    /* No Action */
                }

            }
          
             B:
            /* Startig Index 6 because 6 bytes Are already framed in Abou */
             for(; u16_loffset < u132_fLength;)
             {
            
                if(1 == u8_gHeaderFlag && 1 == u8_gHeadrflag)
                {
                    /* Convert The Target Address to PAN Format */
                    COMMON_Word2PAN(&au8_lDisplayBuff[u16_gDispIndex], u32_fCANID);              
                    u16_gDispIndex = u16_gDispIndex + 9;
                    
                    if(1 == u8_gDLCFlag)
                    {
                        /* Convert The Target Address to PAN Format */
                        COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], 8);
                        u16_gDispIndex = u16_gDispIndex + 2;

                        /* */
                        if(1 == u8_gIctSpaceFlag)
                        {
                            au8_lDisplayBuff[u16_gDispIndex] = ' ';                
                            u16_gDispIndex = u16_gDispIndex + 1;
                        }
                        else
                        {
                            /* No Action */
                        }
                    }
                    /* Convert The Target Address to PAN Format */
                   COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], (0x20 | u8_gConsegutveIndex));
                }
                else
                {
                    /* Copy the Frame Index into an buffer  */
                    sprintf((char *)&au8_lDisplayBuff[u16_gDispIndex], "%X:", u8_lFrameIndx);
                }
                
                /* Increment Idesx */
                u16_gDispIndex = u16_gDispIndex + 2;

                /* Cop the & Bytes Per iteration */
                for(INT8U u8_lIndex = 0x00; u8_lIndex < 7 ; u8_lIndex++)
                {
                    /* Convert The Target Address to PAN Format */
                    COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], p_fData[u16_loffset]);
                    u16_gDispIndex = u16_gDispIndex + 2; 
                    
                    /* Increment the Offset For data */
                    u16_loffset = u16_loffset + 1;
                    
                    if(u16_loffset == u132_fLength)
                    {
                       INT8U u8_lRemng = 0x00;
                       
                      /* Increment Idesx for Space */
                       u16_gDispIndex = u16_gDispIndex + 1;
                       
                       /* Calculating the Remaining Bytes to Fill 0xAA */
                       u8_lRemng = 6 - u8_lIndex;
                        
                       /* Fill with 0xAA */
                       for(int i= 0x00 ; i< u8_lRemng ;i++)
                       {
                            /* Convert the Data into an PAN format */
                            COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], 0xAA);
                            
                            /* Increment Idesx Including Space */
                            u16_gDispIndex = u16_gDispIndex + 3;     
                       }                        
                       break;
                    }
                    else if(1 == u8_gIctSpaceFlag)
                    {
                        /* Increment Idesx for Space */
                        u16_gDispIndex = u16_gDispIndex + 1;
                    }
                    else
                    {
                      /* No Action */
                    }
                }
                
                /* Append \n */
                au8_lDisplayBuff[u16_gDispIndex-1] = '\n';                  
                
                /* */
                if(0x0F == u8_lFrameIndx || 0x0F == u8_gConsegutveIndex)
                {
                  u8_lFrameIndx = 0x00;
                  u8_gConsegutveIndex = 0x00;
                }
                else
                {
                   /* */
                   u8_lFrameIndx = u8_lFrameIndx + 1;
                   u8_gConsegutveIndex = u8_gConsegutveIndex + 1;
                }
                
                
             }          
        }
    }
    else
    {
        /* Check For Header ON*/
        if(1 == u8_gHeaderFlag) 
        {
            /* Convert The Target Address to PAN Format */
            COMMON_Word2PAN(&au8_lDisplayBuff[u16_gDispIndex], u32_fCANID);
            u16_gDispIndex = u16_gDispIndex + 8;
            
            /* */
            if(1 == u8_gIctSpaceFlag)
            {
                au8_lDisplayBuff[u16_gDispIndex] = ' ';                
                u16_gDispIndex = u16_gDispIndex + 1;
            }
            else
            {
                /* No Action */
            }
            
            /* Convert The Target Address to PAN Format */
            COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], u132_fLength);
            u16_gDispIndex = u16_gDispIndex + 2;
            
            /* */
            if(1 == u8_gIctSpaceFlag)
            {
                au8_lDisplayBuff[u16_gDispIndex] = ' ';                
                u16_gDispIndex = u16_gDispIndex + 1;
            }
            else
            {
                /* No Action */
            }
            
            /* goto Single Frame Parsing */
            goto A;
        }
        else
        {
            /* Frame and Display Data */
        A:  for(u8_lIndex = 0; u8_lIndex < u132_fLength; u8_lIndex++)
            {
                /* Convert The Target Address to PAN Format */
                COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], p_fData[u8_lIndex]);
                u16_gDispIndex = u16_gDispIndex + 2;

                if(u8_lIndex < u132_fLength -1 && 1 == u8_gIctSpaceFlag)
                {
                    au8_lDisplayBuff[u16_gDispIndex] = ' ';                
                    u16_gDispIndex = u16_gDispIndex + 1; 
                }
                else
                {
                    /* No Action */
                }
            }
            strcpy((char *)&au8_lDisplayBuff[u16_gDispIndex], "\r\n");
            u16_gDispIndex = u16_gDispIndex + 2;

        }
    }
    
    /* */
    au8_lDisplayBuff[u16_gDispIndex] = '#';
    u16_gDispIndex = u16_gDispIndex + 1;
    
     /* And Send the Data to  Callback Function */
     p_gXT_ReqComplete((INT8U *)&au8_lDisplayBuff[0], u16_gDispIndex);
 
} 

/**************************************************************************************************/
/* Function Name   :  void CAN_DISPLAY_XTMA(ISO_RxData_t * p_fCanDispData)                        */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

void CAN_DISPLAY_XTMA(INT32U u32_fCANID, const INT8U *p_fData , INT32U u132_fLength)
{

    INT8U au8_lDisplayBuff[64] = {0x00,};
    INT8U u16_gDispIndex = 0x00;
    
    INT8U u8_lIndex = 0;
    
    /* Check for Response Flag */
    if(1 == u8_gResponseFlag)
    {
        if(1 == u8_gIctSpaceFlag)
        {
            /* Check For Header ON*/
            if(1 == u8_gHeaderFlag)
            {
                /* Convert The Target Address to PAN Format */
                COMMON_HWord2PAN(&au8_lDisplayBuff[u16_gDispIndex], u32_fCANID);
                u16_gDispIndex = u16_gDispIndex + 4;
                
                au8_lDisplayBuff[u16_gDispIndex] = ' ';
                u16_gDispIndex = u16_gDispIndex + 1;
                
                if(1 == u8_gDLCFlag)
                {
                    /* Convert The Target Address to PAN Format */
                    COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], 8);
                    u16_gDispIndex = u16_gDispIndex + 2;
                    
                    au8_lDisplayBuff[u16_gDispIndex] = ' ';
                    u16_gDispIndex = u16_gDispIndex + 1;
                }
                else
                {
                    /* No Action */
                }
                
                /* Display Data */
                for(u8_lIndex = 0; u8_lIndex < 8; u8_lIndex++)
                {
                    /* Convert The Target Address to PAN Format */
                    COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], p_fData[u8_lIndex]);
                    u16_gDispIndex = u16_gDispIndex + 2;
                    
                    au8_lDisplayBuff[u16_gDispIndex] = ' ';
                    u16_gDispIndex = u16_gDispIndex + 1;                  
                }
            }
            else
            {
                /* Display Data */
                for(u8_lIndex = 0; u8_lIndex < u132_fLength; u8_lIndex++)
                {
                    /* Convert The Target Address to PAN Format */
                    COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], p_fData[u8_lIndex]);
                    u16_gDispIndex = u16_gDispIndex + 2;
                    
                    au8_lDisplayBuff[u16_gDispIndex] = ' ';
                    u16_gDispIndex = u16_gDispIndex + 1;                    
                }             
            }
            strcat((char *)&au8_lDisplayBuff[u16_gDispIndex], "\r\n");
            u16_gDispIndex = u16_gDispIndex + 2;  
        }
        else
        {
             /* Space Flag is Disabled *//* Check For Header ON*/
            if(1 == u8_gHeaderFlag)
            {
                /* Convert The Target Address to PAN Format */
                COMMON_HWord2PAN(&au8_lDisplayBuff[u16_gDispIndex], u32_fCANID);
                u16_gDispIndex = u16_gDispIndex + 2;
                
                if(1 == u8_gDLCFlag)
                {
                    /* Convert The Target Address to PAN Format */
                    COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], 8);
                    u16_gDispIndex = u16_gDispIndex + 2;
                }
                else
                {
                    /* No Action */
                }
                
                /* Display Data */
                for(u8_lIndex = 0; u8_lIndex < 8; u8_lIndex++)
                {
                    /* Convert The Target Address to PAN Format */
                    COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], p_fData[u8_lIndex]);
                    u16_gDispIndex = u16_gDispIndex + 2;                 
                }
                
                strcat((char *)&au8_lDisplayBuff[u16_gDispIndex], "\r\n");
                u16_gDispIndex = u16_gDispIndex + 2; 
            }
            else
            {
                 /* Display Data */
                for(u8_lIndex = 0; u8_lIndex < 8; u8_lIndex++)
                {
                    /* Convert The Target Address to PAN Format */
                    COMMON_Byte2PAN(&au8_lDisplayBuff[u16_gDispIndex], p_fData[u8_lIndex]);
                    u16_gDispIndex = u16_gDispIndex + 1;                  
                }                
                strcat((char *)&au8_lDisplayBuff[u16_gDispIndex], "\r\n");
                u16_gDispIndex = u16_gDispIndex + 2;                
            }
        }
        
        au8_lDisplayBuff[u16_gDispIndex] = '#';
         p_gXT_ReqComplete((INT8U *)&au8_lDisplayBuff[0], u16_gDispIndex);
    }         
} 

/**************************************************************************************************/
/* Function Name   : void WriteConfigData(void)                                                   */
/*                                                                                                */
/* Description     : This Function is Used to Write The Data to EEPROM                            */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TEOBDII_STACK_WriteDefaultConfigData(void)
{
    /* serial Number update */
    strcpy((char *)&st_gChipConfigData.u8_mSerialNumber[0], TE_SERIAL_NUMBER);
    
    /* Firmware Version Update */
    strcpy((char *)&st_gChipConfigData.u8_mFirmwareVersion[0], TE_FIRMWARE_VERSION);
    
    /* Baudrate Update */
    st_gChipConfigData.u32_mBaudrate = TE_DEFAULT_BAUDRATE;
    
    /* Initialize Date Update*/
    strcpy((char *)&st_gChipConfigData.u8_mInitDate[0], TE_INITIALIZE_DATE);
    
    /* Update the Default Protocol */
    st_gChipConfigData.u8_mCurProtocol = TE_DEFAULT_PROTOCOL;
    
    /* POR Count Update */
    st_gChipConfigData.u8_mPORCount = 0;
    
    /* POR Time Update */
    st_gChipConfigData.u16_mPORTime = 0;
    
    /* Engine Crank Update */
    st_gChipConfigData.u8_mEngineCrank = 0;
    
    /* Runtime Update */
    st_gChipConfigData.u16_mRuntime = 0;
    
    /* Engine Status Update */
    st_gChipConfigData.u8_mEngineStatus = 0;
    
    /* Copy Device ID / Hardware ID String */
    strcpy((char *)&st_gChipConfigData.au8_mDeviceIdString[0], (const char *)TE_DEVICE_ID_STRING);
    
    /* Update Serial Info */
    if(PNULL != pst_gHalObjectPtr->NVM_Write)
    {
        pst_gHalObjectPtr->NVM_Write(SYS_CONFIG_DATA_BASE_ADDR, (INT8U *)&st_gChipConfigData, sizeof(ST_SYS_CONFIG_DATA_t));
    }
    else
    {
        while(1);
    }
    
}

/**************************************************************************************************/
/* Function Name   : void Update_SysConfigData(void)                                              */
/*                                                                                                */
/* Description     : This Function is Used to Get the Configuration Data From EEPROM              */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void TEOBDII_STACK_WriteConfigData(void)
{
    /* Update Serial Info */
    if(PNULL != pst_gHalObjectPtr->NVM_Write)
    {
        pst_gHalObjectPtr->NVM_Write(SYS_CONFIG_DATA_BASE_ADDR, (INT8U *)&st_gChipConfigData, \
                                                                    sizeof(ST_SYS_CONFIG_DATA_t));
    }
    else
    {
        while(1);
    }
}

/**************************************************************************************************/
/* Function Name   : void Update_SysConfigData(void)                                              */
/*                                                                                                */
/* Description     : This Function is Used to Get the Configuration Data From EEPROM              */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/


void TEOBDII_STACK_GetConfigData(void)
{
    /* Update Serial Info */
    if(PNULL != pst_gHalObjectPtr->NVM_Read)
    {
        pst_gHalObjectPtr->NVM_Read(SYS_CONFIG_DATA_BASE_ADDR, (INT8U *)&st_gChipConfigData, \
                                                                        sizeof(ST_SYS_CONFIG_DATA_t));
    }
    else
    {
        while(1);
    }
}

/**************************************************************************************************/
/* Function Name   : EN_STACK_MGR_STATES_LIST_t GetCurrentProtocol(void)                          */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_STACK_MGR_STATES_LIST_t GetCurrentProtocol(void)
{
    /* Variable to Hold The Current Protocol */
    EN_STACK_MGR_STATES_LIST_t en_lProtocol = IS015765_CAN_11_500;
    
    switch(st_gChipConfigData.u8_mCurProtocol)
    {  
    case 25:
        {
            en_lProtocol = IS014230_FAST; 
        }
        break;
        
    case 33:
        {
            en_lProtocol = IS015765_CAN_11_500;
        }
        break;
        
    case '5':
        {
            en_lProtocol = IS014230_FAST;
        }
        break;
        
    case '6':
        {
            en_lProtocol = IS015765_CAN_11_500;
        }
        break;
        
    case '7':
        {
            en_lProtocol = IS015765_CAN_29_500;
        }
        break;
        
    case '8':
        {
            en_lProtocol = IS015765_CAN_11_250;
        }
        break;
        
    case '9':
        {
            en_lProtocol = IS015765_CAN_29_250;
        }
        break;
        
    case 'A':
        {
            en_lProtocol = SAE_J1939_29_250;
        }
        break;
        
    default:
        {
            en_lProtocol = IS015765_CAN_11_500;
        }
        break;
    }
    
    return en_lProtocol;
}

/**************************************************************************************************/
/* End of XTCOM.c                                                                                 */
/**************************************************************************************************/
