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
/*  File Name   : XTP_SAEJ1939.c                                                                  */
/*  Author      : Santhosh                                                                        */
/*  Version 	:                                                                                 */
/*  Date        : 25-04-2018                                                                      */
/*                                                                                                */
/* @Description : XTP_SAEJ1939                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include "stdlib.h"
#include "string.h"

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "DATACONV.h"

#include "XTP_TE_public.h"
#include "XTP_public.h"

#include "SAEJ1939_21_TP_public.h"
#include "SAEJ1939_CAN29B250KBPS_public.h"

#include "XTP_SAEJ1939_public.h"
#include "XTP_SAEJ1939_private.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Response Receiving Gfrom All ECU's Flag */
INT8U u8_gGlobalRespReq = 0x01;

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

EN_XTP_RESULT_t XTP_XTJDM(INT8U *p_fSrc, INT16U u16_fLength)
{
     EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
     
    /* variable for to store DM number */ 
    INT8U u8_lDM_Number;
    
    /* Convert the Data into An Integer */
    u8_lDM_Number = atoi((const char *)&p_fSrc[0]);
    
    /* Search for the DM Number */
    switch(u8_lDM_Number)
    {
    case 1:
    {      
       /* sending PGN for DM1 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00FECA" , 7);
    }
    break;
    
    case 2:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00FECB" , 7);
    }
    break;
        
    case 3:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FECC" , 7);
    }
    break;
        
    case 4:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FECD" , 7);
    }
    break;
        
    case 5:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00FECE" , 7);
    }
    break;
    case 6:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FECF" , 7);
    }
    break;
    
    case 7:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00E300" , 7);
    }
    break;
    
    case 8:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00FED0" , 7);
    }
    break;
    
    case 9:
        {
           SAEJ1939_CAN29B250KBPS_WriteData("00FED1" , 7);
        }
        break;
    case 10:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FED2" , 7);
    }
    break;
    
    case 11:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00FED3" , 7);
    }
    break;
    
    case 12:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FED4" , 7);
    }
    break;
    
    case 13:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00DF00" , 7);
    }
    break;
    case 14:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00D900" , 7);
    }
    break;
    case 15:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00D800" , 7);
    }
    break;
    case 16:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00D700" , 7);
    }
    break;
    case 17:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00D600" , 7);
    }
    break;
    case 18:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00D400" , 7);
    }
    break;
    case 19:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00D300" , 7);
    }
    break;
    case 20:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00C200" , 7);
    }
    break;
    case 21:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00C100" , 7);
    }
    break;
    case 22:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00C300" , 7);
    }
    break;
    case 23:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00FDB5" , 7);
    }
    break;
    case 24:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FDB6" , 7);
    }
    break;
    case 25:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FDB7" , 7);
    }
    break;
    case 26:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00FDB8" , 7);
    }
    break;
    case 27:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FD82" , 7);
    }
    break;
    case 28:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FD80" , 7);
    }
    break;
    case 29:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("009E00" , 7);
    }
    break;
    case 30:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00A400" , 7);
    }
    break;
    case 31:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00A300" , 7);
    }
    break;
    case 32:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00A200" , 7);
    }
    break;
    case 33:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00A100" , 7);
    }
    break;
    case 34:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00A000" , 7);
    }
    break;
    case 35:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("009F00" , 7);
    }
    break;
    case 36:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FD64" , 7);
    }
    break;
    case 37:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FD63" , 7);
    }
    break;
    case 38:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00FD62" , 7);
    }
    break;
    case 39:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FD61" , 7);
    }
    break;
    case 40:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FD60" , 7);
    }
    break;
    case 41:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00FD5F" , 7);
    }
    break;
    case 42:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FD5E" , 7);
    }
    break;
    case 43:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FD5D" , 7);
    }
    break;
    case 44:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00FD5C" , 7);
    }
    break;
    case 45:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FD5B" , 7);
    }
    break;
    case 46:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FD5A" , 7);
    }
    break;        
    case 47:
    {
        SAEJ1939_CAN29B250KBPS_WriteData("00FD59" , 7);
    }
    break;
    case 48:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FD58" , 7);
    }
    break;
    case 49:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FD57" , 7);
    }
    break;
    case 50:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00FD56" , 7);
    }
    break;
    case 51:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FD55" , 7);
    }
    break;
    case 52:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FD54" , 7);
    }
    break;        
    case 53:
    {
        SAEJ1939_CAN29B250KBPS_WriteData("00FCD1" , 7);
    }
    break;
    case 54:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FCD2" , 7);
    }
    break;
    case 55:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FCD3" , 7);
    }
    break;
    case 56:
    {
       /* sending PGN for DM2 message */
       SAEJ1939_CAN29B250KBPS_WriteData("00FCC7" , 7);
    }
    break;
    case 57:
    {
       SAEJ1939_CAN29B250KBPS_WriteData("00FCC6" , 7);
    }
    break;
    default:
      {
        en_lResult = XTP_ERROR;
      }
      break;
    }
    
    return en_lResult; 
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTJE(INT8U *p_fSrc, INT16U u16_fLength)    */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTJDA(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* */
    INT8U u8_lDstntnAdrs = 0xFF;
    
     /* */
     INT32U u32_lDefaultHeader = 0x18EAFFF9;
    
     /* */
    COMMON_PAN2Byte(&p_fSrc[0],&u8_lDstntnAdrs);

    if(0xFF == u8_lDstntnAdrs)
    {
        /* */
        u8_gCM_BAM_Flag = 0x00;
        
        u8_gGlobalRespReq = 0x01;
        
         u8_gJ1939_PF = 0x00;
         u8_gJ1939_PS = 0x00;
         
         /* Reset the Souce Place to 00 */
        u32_lDefaultHeader &= 0xFFFF00FF;
        
        /* Place the User given Source Adrs in place */
        u32_lDefaultHeader |= u8_lDstntnAdrs << 8;
        
        /*assign to a Global Geader */
        u32_gJ1939Header = u32_lDefaultHeader;
        
        /* */
        u32_gJ1939RTSHeader &= 0xFFFF00FF;
        
       /* Place the User given Source Adrs in place */
        u32_gJ1939RTSHeader |= u8_lDstntnAdrs << 8;
    }
    else
    {
        /* */
        u8_gCM_BAM_Flag = 0x01;
        
         u8_gGlobalRespReq = 0x00;
         
         u8_gJ1939_PF = 0x00;
         u8_gJ1939_PS = 0x00;
         
         /* Reset the Souce Place to 00 */
        u32_lDefaultHeader &= 0xFFFF00FF;
        
        /* Place the User given Source Adrs in place */
        u32_lDefaultHeader |= u8_lDstntnAdrs << 8;
        
        /*assign to a Global Geader */
        u32_gJ1939Header = u32_lDefaultHeader;
        
        /* */
        u32_gJ1939RTSHeader &= 0xFFFF00FF;
        
       /* Place the User given Source Adrs in place */
        u32_gJ1939RTSHeader |= u8_lDstntnAdrs << 8;
    }

    if(0x02 == u16_fLength && 0x01 == u8_gCM_BAM_Flag)
    {    
        /* Reset the Souce Place to 00 */
        u32_lDefaultHeader &= 0xFFFF00FF;
        
        /* Place the User given Source Adrs in place */
        u32_lDefaultHeader |= u8_lDstntnAdrs << 8;
        
        /*assign to a Global Geader */
        u32_gJ1939Header = u32_lDefaultHeader;
        
        /* */
        u32_gJ1939RTSHeader &= 0xFFFF00FF;
        
       /* Place the User given Source Adrs in place */
        u32_gJ1939RTSHeader |= u8_lDstntnAdrs << 8;
        
         /* Send Response */
        p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    }
    else
    {
        /* return Error */
        en_lResult = XTP_SUCCESS;
        
         /* Send Response */
        p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    }
    
    /* */
    return en_lResult; 
}
/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTCP(INT8U *p_fSrc, INT16U u16_fLength)    */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTJNM(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold the Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* */
    INT8U u8_lNMData[8] = {0x00, };
    
    /* */
    COMMON_PAN2ByteArray(p_fSrc, &u8_lNMData[0], 8);
    
    /* */
     pst_gHalObjectPtr->CAN_TxMsg(u32_gNMheader, &u8_lNMData[0], 8);
    
    /* Send Response */    
    return en_lResult;
}
/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTJHF(INT8U *p_fSrc, INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTJTP(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    if(0x05 == u16_fLength)
    {
        /* Convert the Payload of PAN to  Payload */
        COMMON_PAN2ByteArray((INT8U *)&p_fSrc[0], &u8_gTP_PGN[0], 3);
        
        /* Send Response */
        p_gXT_ReqComplete((INT8U *)&au8_gIctSuccessString[0], \
                                            strlen((const char *)&au8_gIctSuccessString[0])); 
    }
    else
    {
      /* */
      en_lResult = XTP_ERROR;
    }
  
    /* */
    return en_lResult; 
}

/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTJTM(INT8U *p_fSrc, INT16U u16_fLength)   */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTJTM(INT8U *p_fSrc, INT16U u16_fLength)
{
    /* Variable to Hold The Result */
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
   
    
    return en_lResult;  
}
/**************************************************************************************************/
/* Function Name   : EN_XTP_RESULT_t XTP_XTMP(INT8U *p_fSrc, INT16U u16_fLength)                        */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTJMP(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* Send the PGN to Stack to vechiles  +1 for \r*/
      /* */
    INT8U u8_lPGN[6] = {0x00,};
    INT8U u8_l3BytesPGN[3] = {0x00,};
      
    memcpy(&u8_lPGN[0],&p_fSrc[0],6);
    
    COMMON_PAN2ByteArray(&u8_lPGN[0] ,&u8_l3BytesPGN[0],3);
    
    u8_gJ1939_MPF = u8_l3BytesPGN[1];
    u8_gJ1939_MPS = u8_l3BytesPGN[2];
    
    if(0x00 != u8_gJ1939_MPF && 0x00 != u8_gJ1939_MPS)
    {
        /* */
        u8_gJ1939SnglPGNMntr = 1;
        
         /* */
        u32_gJ1939RxMonitrTimeOutFlag = 0x01;
        
        /* */
        u32_gJ1939RxMonitrTimeOutCntr = 0x00;
    }
    else
    {
      en_lResult = XTP_ERROR;
    }
    
    /* Return the result */
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   :                                                                              */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTJMPN(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* */
    INT8U u8_lPGN[6] = {0x00,};
    INT8U u8_l3BytesPGN[3] = {0x00,};
    
    memcpy(&u8_lPGN[0],&p_fSrc[0],6);
    
    COMMON_PAN2ByteArray(&u8_lPGN[0] ,&u8_l3BytesPGN[0],3);
    
    u8_gJ1939_MPF = u8_l3BytesPGN[1];
    u8_gJ1939_MPS = u8_l3BytesPGN[2];
   
    /* */
    u8_gMntrPGN_N_Frames  =  atoi((const char *)&p_fSrc[6]);
    
    if(0x00 != u8_gMntrPGN_N_Frames)
    {
        /* */
        u32_gJ1939RxMonitrTimeOutFlag = 0x01;
        
        /* */
        u32_gJ1939RxMonitrTimeOutCntr = 0x00;
    
        /* Make the Flag to 1 */
        u8_gMntrPGN_N_timesFlag = 0x01;
    }
    else
    {
        /* */
        en_lResult = XTP_ERROR;
    }
    
    /* */
    return en_lResult;  
}

/**************************************************************************************************/
/* Function Name   :                                                                              */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_XTP_RESULT_t XTP_XTJMA(INT8U *p_fSrc, INT16U u16_fLength)
{
    EN_XTP_RESULT_t en_lResult = XTP_SUCCESS;
    
    /* make the timer counter zero */
    u32_gJ1939RxMonitrTimeOutFlag = 0x01;
    
    /* */
    u32_gJ1939RxMonitrTimeOutCntr = 0x00;
    
    /* Make the J1939 Monitor All PGN's Flag to 1 */
    u8_gSAEJ1939MtntlAllPGN = 1;
    
    return en_lResult;  
}

/**************************************************************************************************/
/* End of  XTP_SAEJ1939.c                                                                         */
/**************************************************************************************************/
