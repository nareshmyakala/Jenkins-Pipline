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
/* \File Name   : OBD_CMD_HANDLERS.c                                                              */
/* \Author      : PRASHANTH                                                                       */
/* \Version 	:                                                                                 */
/* \Date        : 25-03-2017                                                                      */
/*                                                                                                */
/* @Description : OBD Handlers Frame Work                                                         */
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

#include "XTP_public.h"

#include "SAEJ1939_21_TP_public.h"
#include "ISOTP14230_TP_public.h"

#include "CAN_IF.h"
#include "TEOBD2_public.h"

#include "XTP_OBD_public.h"
#include "XTP_OBD_private.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTAT(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTAT(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
#if 0
    switch(p_fSrc[0])
    {
    case '0':
        {
            /* */
            st_gProgrambleParameter[0x04].en_ProgramParameterStatus = PP_OFF;
        }
        break;

    case '1':
        {
            /* */
            st_gProgrambleParameter[0x04].en_ProgramParameterStatus = PP_ON;
            st_gProgrambleParameter[0x04].u16_mValue = DEFAULT_ADAPTIVE_TIMEOUT;
        }
        break;

    case '2':
        {
            /* */
            st_gProgrambleParameter[0x04].en_ProgramParameterStatus = PP_ON;
            st_gProgrambleParameter[0x04].u16_mValue = MAX_ADAPTIVE_TIMEOUT;
        }
        break;

    default:
        {
            /* update Error */
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

#endif
    
        /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                                strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTDP(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTDP(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    INT8U au8_lTempBuff[32] = {0x00, };

    /* Display the Current Protocol */
    switch(st_gChipConfigData.u8_mCurProtocol)
    {
    case '0':
        {
            /* Copy Automatic to Response Buffer */
          strcpy((char *)&au8_lTempBuff[0], (const char *)"AUTO\r\n#");
        }
        break;
    case '1':
        {
            /* Copy J1850 PWM to Resonse Buffer */
          strcpy((char *)&au8_lTempBuff[0], (const char *)"SAE J1850 PWM\r\n#");
        }
        break;
    case '2':
        {
            /* Copy J1850 VPW to Response Buffer */
          strcpy((char *)&au8_lTempBuff[0], (const char *)"SAE J1850 VPW\r\n#");
        }
        break;
    case '3':
        {
            /* Copy 9141-2 to Response Buffer */
            strcpy((char *)&au8_lTempBuff[0], \
              (const char *)"ISO 9141-2\r\n#");
        }
        break;
    case '4':
        {
            /* Copy 5 Baud to Response Buffer */
            strcpy((char *)&au8_lTempBuff[0], \
              (const char *)"ISO 14230-4 (KWP 5BAUD)\r\n#");
        }
        break;
    case '5':
        {
            /* Copy KWP Fast to Response Buffer */
            strcpy((char *)&au8_lTempBuff[0], \
                                        (const char *)"ISO 14230-4 (KWP_FAST)\r\n#");
        }
        break;
    case '6':
        {
            /* Copy CAN 11 500 to Response Buffer */
            strcpy((char *)&au8_lTempBuff[0], \
              (const char *)"ISO 15765-4 (CAN 11/500)\r\n#");
        }
        break;
    case '7':
        {
            /* Copy CAN 29 500 to Response Buffer */
            strcpy((char *)&au8_lTempBuff[0], \
              (const char *)"ISO 15765-4 (CAN 29/500)\r\n#");
        }
        break;
    case '8':
        {
            /* Copy CAN 11 250 to Response Buffer */
            strcpy((char *)&au8_lTempBuff[0], \
              (const char *)"ISO 15764-4 (CAN 11/250)\r\n#");
        }
        break;
    case '9':
        {
            /* Copy CAN 29 250 to Response Buffer */
            strcpy((char *)&au8_lTempBuff[0], \
                                        (const char *)"ISO 15764-4 (CAN 29/250)\r\n#");
        }
        break;
    case 'A':
        {
            /* Copy SAEJ1939 To Response Buffer */
            strcpy((char *)&au8_lTempBuff[0], \
              (const char *)"SAE J1939 (CAN 29/250)\r\n#");
        }
        break;
    case 11:
        {
            /* Copy USER1 CAN 11 125 to Response Buffer */
            strcpy((char *)&au8_lTempBuff[0], \
              (const char *)"USER1 (CAN 11/125)\r\n#");
        }
        break;
    case 12:
        {
            /* Copy USER2 CAN 11 125 to Response Buffer */
            strcpy((char *)&au8_lTempBuff[0], \
              (const char *)"USER2 (CAN 11/50)\r\n#");
        }
    case 25:
        {
            /* Copy USER2 CAN 11 125 to Response Buffer */
            strcpy((char *)&au8_lTempBuff[0], \
              (const char *)"ISO 14230 (FAST) [XT]\r\n#");
        }
        break;

    case 33:
        {
            /* Copy USER2 CAN 11 125 to Response Buffer */
            strcpy((char *)&au8_lTempBuff[0], \
              (const char *)"HS CAN(ISO 15765, 500K/11B) [XT]\r\n#");
        }
        break;

    default:
        break;
    }

    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_lTempBuff[0], \
                                strlen((const char *)&au8_lTempBuff[0]));
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTH(INT8U *p_fSrc, INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :  Headers on/off                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTH(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    switch(p_fSrc[0])
    {
    case '1':
        {
            /* Update Header flag to 1 */
            u8_gHeaderFlag = 1;
        }
        break;

    case '0':
        {
            /* Update Header flag to 0 */
            u8_gHeaderFlag = 0;
        }
        break;

    default:
        {
            /* update Error */
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
/* Function Name   : EN_XTP_RESULT_t XTP_XTDPN(INT8U *p_fSrc, INT16U u16_fLength) */
/*                                                                                                */
/* Description     :  Results the current protocol number                                         */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTDPN(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    INT8U au8_lTempBuff[8] = {0x00, };
    
    /* update Current Protocol to Response Buffer */
    au8_lTempBuff[0] = st_gChipConfigData.u8_mCurProtocol;

    if('9' >= au8_lTempBuff[0] && '0' < au8_lTempBuff[0])
    {
        /* No action */
    }
    else if(25 == au8_lTempBuff[0])
    {
        /* */
        memcpy(&au8_lTempBuff[0], "25 [XT]", sizeof("25 [XT]"));
    }
    else if(33 == au8_lTempBuff[0])
    {
        /* */
        memcpy(&au8_lTempBuff[0], "33 [XT]", sizeof("33 [XT]"));
    }
    else
    {
        /* Update the Error Status */
        en_lResult = XTP_ERROR;
    }

    /* Append Carriage Return and New Line */
    strcat((char *)&au8_lTempBuff[0], (const char *)"\r\n#");

    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_lTempBuff[0], \
                                               strlen((const char *)&au8_lTempBuff[0]));

    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTMA(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :  Monitors the All CAN Headers/Data                                           */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTMA(INT8U *p_fSrc, INT16U u16_lLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;

    /* update Global Echo Flag to 1 */
    u8_gCanBusMonitorStaus = 1;
    
    if(en_gOBDII_State == SAE_J1939_29_250)
    {
        en_lResult = XTP_ERROR;
    }
    else 
    {
       /* Initialize the CAN MO foto receive Data From All Headers */
       CAN_IF_Ioctrl(MO_CONFIGURE,CAN0,1,0x000,CAN_STD_ID,CAN_MB_RECEIVE,u32_gRxHeaderId);
       
       /* Initialize the CAN MO foto receive Data From All Headers */
       // pst_gHalObjectPtr->CAN_ConfigMO(u32_gRxHeaderId, 1, OBD_CAN_STANDARD_ID,\
                                                                              OBD_CAN_MO_RX, 0x000);
    }
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTSH(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     : Sets the CAN/K-LINE/J1939 TX header                                           */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSH(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Variable to Hold Header */
    INT32U u32_lHeader = 0;
    INT8U au8_lTemp[8] = {0, };
    
    if(3 == u16_fLength)
    {
        /* Aappend 0 */
        memcpy(&au8_lTemp[0], &p_fSrc[0], u16_fLength);
        au8_lTemp[3] = '0';
        
        /* Convert the Content to Halfword */
        COMMON_PAN2HWord(&au8_lTemp[0], (INT16U *)&u32_lHeader);
        
        /* Shift the header by 1 */
        u32_lHeader = u32_lHeader >> 4;
        
        if(u32_lHeader <= 0x7FF)
        {
            /* Tx Address Should be - 8 */
            u32_gTxHeaderId = u32_lHeader;
            
            if(0x7DF == u32_gTxHeaderId)
            {
                u32_gRxHeaderId = 0x7E8;
            }
            else
            {
                /* update Global Tx and Rx header */
                //u32_gRxHeaderId = u32_lHeader + 8;
            }
            
            /* Initialize the CAN MO foto receive Data From All Headers */
            CAN_IF_Ioctrl(MO_CONFIGURE,CAN0,1,0x7FF,CAN_STD_ID,CAN_MB_TRANSMIT,u32_gRxHeaderId);
   
            //pst_gHalObjectPtr->CAN_ConfigMO(u32_gRxHeaderId, 1, OBD_CAN_STANDARD_ID, \
                                                                        OBD_CAN_MO_RX, 0x7FF);
        }
        else
        {
            /* Update Error Status To The Variable */
            en_lResult = XTP_ERROR;
        }
    }
    else if(4 == u16_fLength)
    {
        memcpy(&au8_lTemp[0], &p_fSrc[0], u16_fLength);
        au8_lTemp[6] = '0';
        au8_lTemp[7] = '0';

        COMMON_PAN2Word(&au8_lTemp[0], &u32_lHeader);

        /* */
        u32_lHeader = (u32_lHeader >> 8);

        /* Update Target Address */
        u8_gKlineTarByte = (INT8U)((u32_lHeader & 0x00FF00) >> 8);

        /* Update Source Address */
        u8_gKlineSrcByte = (INT8U)((u32_lHeader & 0x0000FF) >> 0);
      
    }
    else if(6 == u16_fLength)
    {
        
        switch(en_gOBDII_State)
        {
        case SAE_J1939_29_250:
            {
                /* */
                memcpy(&au8_lTemp[0], &p_fSrc[0], u16_fLength);
                au8_lTemp[6] = '0';
                au8_lTemp[7] = '0';
                
                COMMON_PAN2Word(&au8_lTemp[0], &u32_lHeader);
                
                u32_lHeader = (u32_lHeader >> 8);
                
                u32_gJ1939Header &= ~(0x00FFFFFF);
                
                u32_gJ1939Header |= (u32_lHeader); 
            }
            break;
        
        default :
            {
                /* Update Error Status To The Variable */
                en_lResult = XTP_ERROR;          
            }
            break;
        }
        
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
/* Function Name   : EN_XTP_RESULT_t XTP_XTST(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTST(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Temp Variable */
    INT8U u8_lTimeoutValue = 0;

    /* */
    if(COMMON_OK == COMMON_PAN2Byte(&p_fSrc[0], &u8_lTimeoutValue))
    {
        switch(en_gOBDII_State)
        {
        case IS015765_CAN_11_500:
            {
                /* update Timeout Value */
                u16_gTimeoutTime = (u8_lTimeoutValue * TIMEOUT_FACTOR);

                /* copy to Programable Parameter */
              //  st_gProgrambleParameter[0x03].u16_mValue = u16_TimeoutTime;

            }
            break;

        case IS014230_FAST:
            {
                /* update Timeout Value */
               // u32_gKlineTimeOut = (u8_lTimeoutValue * KLINE_NODATA_TIMEOUT_FACTOR );
            }
            break;

        default :
          {
                /* Update Error Status To The Variable */
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
    
    }
    else
    {
        /* Update Error Status To The Variable */
        en_lResult = XTP_ERROR;         
    }
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTMR(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

INT32U u32_gRxheaderForMntor = 0x00;
INT32U u32_gRxheaderForMntor1 = 0x00;

INT8U u8_gUserRXMntorAdres[3] = {0x00,};

EN_XTP_RESULT_t XTP_XTMR(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    INT32U u32_lRxheaderForMntor = 0x00;
    
    /* Copy the User Haeder inot the Buffer */
    //memcpy(&u8_gUserRXMntorAdres[0] ,p_fSrc , u16_fLength);
    
    for(int i = 0,j=8;i<u16_fLength ;i++)
    {
        if('A' <= p_fSrc[i] && 'F' >= p_fSrc[i])
        {
           u32_lRxheaderForMntor = ((p_fSrc[i] - 0x37));
           u32_gRxheaderForMntor |= u32_lRxheaderForMntor << j;
           
           if(0!= j)
           {
              j = j-4;
           }
        }
        else
        {
             u32_lRxheaderForMntor = ((p_fSrc[i] - 0x30));
             u32_gRxheaderForMntor |= u32_lRxheaderForMntor << j;
             if(j != 0)
             {
                j = j-4;
             }
        }
    }
    
    /* Init The CAN Message Object with New USER Header */
     if(PNULL != pst_gHalObjectPtr->CAN_ConfigMO)
    {
        pst_gHalObjectPtr->CAN_ConfigMO(u32_gRxheaderForMntor, 1, OBD_CAN_STANDARD_ID, \
            OBD_CAN_MO_RX, 0x7FF);
    }
    else
    {
        while(1);
    }
    
    /* */
    u32_gRxheaderForMntor = 0x00;
    
    /* Send Response */
    p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0]));
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTS(INT8U *p_fSrc, INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTS(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    switch(p_fSrc[0])
    {
    case '0':
        {
            /* Update The Space Flag */
            u8_gIctSpaceFlag = 0;
        }
        break;

    case '1':
        {
            /* Update The Space Flag */
            u8_gIctSpaceFlag = 1;
        }
        break;

    default:
        {
            /* update Error */
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
/* Function Name   : EN_XTP_RESULT_t XTP_XTTP(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTTP(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;

    if((p_fSrc[0] <= '9') && (p_fSrc[0] > '0'))
    {
        /* Write the Corresponding argument to memory */
        st_gChipConfigData.u8_mCurProtocol  = p_fSrc[0];

      	/* update Protocol State */
        en_gOBDII_State = GetCurrentProtocol();
    }
    else
    {
        /* update Error */
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
/* Function Name   : EN_XTP_RESULT_t XTP_XTSP(INT8U *p_fSrc, INT16U u16_fLength)  */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTSP(INT8U * p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    INT8U u8_lSearchFlag = 0x00;
    
    if(((p_fSrc[0] <= '9') && (p_fSrc[0] > '0')) || ('A' == p_fSrc[0]))
    {
        /* Write the Corresponding argument to memory */
        st_gChipConfigData.u8_mCurProtocol  = p_fSrc[0];

        /* Update the stack Config Data */
        //TEOBDII_STACK_WriteConfigData();

        /* update Protocol State */
        en_gOBDII_State = GetCurrentProtocol();
    }
    else if('0' == p_fSrc[0])
    {
        u8_lSearchFlag = 0x01;
        
       /* Send Response */
       // p_gXT_ReqComplete((INT8U *)&au8_gIctSearchng[0], \
                                                strlen((const char *)&au8_gIctSearchng[0]));
        //AutoSearchProtocl();
        en_lResult = XTP_ERROR;
    }
    else
    {
        /* update Error */
        en_lResult = XTP_ERROR;
    }

    if(XTP_ERROR != en_lResult)
    {
        if(0 == u8_lSearchFlag)
        {
          /* Send Response */
          p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                                strlen((const char *)&au8_gIctSuccessString[0]));
        }
        else
        {
           u8_lSearchFlag = 0x00;
        }
    }
    
    return en_lResult;
}

/**************************************************************************************************/
/* End of OBD_CMD_HANDLERS.c                                                                      */
/**************************************************************************************************/
