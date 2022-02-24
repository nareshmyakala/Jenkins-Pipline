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
/*  File Name   : PASSTHRU.c                                                                      */
/*  Author      : NAGANJALI.K                                                                     */
/*  Version 	: v1.0                                                                            */
/*  Date        : 01-02-2022                                                                      */
/*                                                                                                */
/* @Description : PASSTHRu driver frame work                                                      */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "STN.h"
#include "BT43.h"
#include "STN.h"
//#include "TBUS.h"

#include "CAN_IF.h"

#include "PASSTHRU.h"
#include "PASSTHRU_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Select Diag Mode */
EN_DIAG_MODE_t en_gDiagMode = DIAG_THROUGH_STN;

/* */
INT8U *pu8_gXTPDataRecvPntr = PNULL;

/* */
INT32U u32_gXTPRecvdlength = 0x00;

INT8U u8_gStackCANintrptMange = 0x00;

INT8U u8_gSTNMntrFlag = 0x00;

/**************************************************************************************************/
/* Function Name   :       void PASSTHRU_Init(void)                                               */
/*                                                                                                */
/* Description     :      Pasthru Initialization                                                  */
/*                                                                                                */
/* In Params       :        void                                                                  */
/*                                                                                                */
/* Out Params      :       void                                                                   */
/*                                                                                                */
/* Return Value    :       None                                                                   */
/**************************************************************************************************/

void PASSTHRU_Init(void)
{
    /* Reset Data variables */
    u8_gIsDataFromStn = 0x00;
    
    /* oN The Authentication LED */
    SET_PIN(AUTHNTCTN_LED_PORT , AUTHNTCTN_LED_PIN);  

    /* Reset the STN FIFO */
    STN_Ioctrl(STN_IOCTRL_RESET_FIFO, PNULL, 0, PNULL, 0);
    
    /* get the refernce from the BT Buffer */
    BT43_Ioctrl(BT43_IOCTRL_RESET_FIFO ,PNULL, 0, PNULL , 0);
        
    /* Init The TEOBD2 */
    XTP_Init(XT_RequestComplete);
    
    /* Disable STN CAN */
    STN_STBCntrl(ENABLE);
      
    /* */
    en_gStnRespType = STN_PROMPT;
            
    /* Disable CAn intrp */
    TE_StackSTB_Cntrl(STB_DISABLE);
    CAN_IF_Sleep(CAN_IF_CH_0);
}

/**************************************************************************************************/
/* Function Name   :      void PASSTHRU_Handler(EN_STATE_LIST_t * p_fState)                       */
/*                                                                                                */
/* Description     :       Passthru Handler  State                                                */
/*                                                                                                */
/* In Params       :         void                                                                 */
/*                                                                                                */
/* Out Params      :         p_fState                                                             */
/*                                                                                                */
/* Return Value    :          None                                                                */
/**************************************************************************************************/

void PASSTHRU_Handler(EN_STATE_LIST_t * p_fState)
{ 
	/* Check for Data from STN */
	if(1 == u8_gIsDataFromStn)
	{
          INT8U *pu8_lFifoRefHold = PNULL;
          INT32U u32_lLength = 0;
          
          /* Make the Flag to 0 */
          u8_gIsDataFromStn = 0;
          
          /* Get STN FIFO Reference */
          STN_Ioctrl(STN_IOCTRL_GET_FIFO_REF, PNULL, 0, &pu8_lFifoRefHold, &u32_lLength);
          
          /* Write Data to Wifi */
          BT43_Transmit(pu8_lFifoRefHold, u32_gStnDataLength);
          //WIFI_WriteData(pu8_lFifoRefHold, u32_gStnDataLength);
	}
	else
	{
		/* No Action */
	}

	/*  Check Whther Data Recived Frm BT or not*/
	if(1 == u8_gisDataFromBT)
	{
		INT8U *pu8_lFifoRefHold = PNULL;
		INT32U u32_lLength = 0;
		
        /* Make the Flag 0 */
		u8_gisDataFromBT = 0;
		
        /* get the refernce from the BT Buffer */
        BT43_Ioctrl(BT43_IOCTRL_GET_FIFO_REF ,PNULL, 0, &pu8_lFifoRefHold , &u32_lLength);
        
		/* Read Data from WIFI FIFO */
		//WIFI_Ioctrl(WIFI_IOCTRL_GET_FIFO_REF, PNULL, 0, &pu8_lFifoRefHold, &u32_lLength);
		
		/* Per Form Checking */
		switch(pu8_lFifoRefHold[0])
		{
		case ':':
		{
			/* Call Tbus Parsing */
			///TBUS_ProcessCmd(pu8_lFifoRefHold, u32_lLength);
		}
		break;
		
		case 'a':
		case 'A':
		case 's':
		case 'S':
		{
                  switch(pu8_lFifoRefHold[1])
                  {
                          case 'T':
                          case 't':
                          {
                    if(0x00 != strstr((const char *)&pu8_lFifoRefHold[0], "STMA"))
                    {
                        /* */
                        //en_gStnRespType = STN_NO_RECEIVE;
                        
                        /* */
                        u8_gSTNMntrFlag = 0x01;
                    }
                    else if((0x00 != strstr((const char *)&pu8_lFifoRefHold[0], "STM")))
                    {
                        /* */
                        //en_gStnRespType = STN_NO_RECEIVE;
                        
                        /* */
                        u8_gSTNMntrFlag = 0x01;
                    }
                    else
                    {
                        /* */
                        en_gStnRespType = STN_PROMPT;
                        
                        u8_gSTNMntrFlag = 0x00;
                    }
                    
                    /* Reset FIFO *//* Get STN FIFO Reference */
                    STN_Ioctrl(STN_IOCTRL_RESET_FIFO, PNULL, 0, PNULL, 0);
                    
                    /* Send Data to STN */
                    STN_WriteData(pu8_lFifoRefHold, u32_lLength);

                    /* Change Diagnostics Mode to XTP */
                    en_gDiagMode = DIAG_THROUGH_STN;


				}
				break;
				
				default:
				{
					
				}
				break;
			}
		}
		break;
		
		case 'x':
		case 'X':
		{
			switch(pu8_lFifoRefHold[1])
			{
				case 'T':
				case 't':
				{
                    /* Check Length is Greater then Zero or not */
					if(u32_lLength > 0)
                    {
                        /* Send Data to XTP */
                        XTP_SendRequest(pu8_lFifoRefHold, u32_lLength-1);
                        
                        /* Change Diagnostics mode to XTP */
                        en_gDiagMode = DIAG_THROUGH_XTP;
                    }
                    else
                    {
                        /* No Action */
                    }
					
					
				}
				break;
				
				default:
				{
					/* No action */
				}
				break;
			}
		}
		break;
		
		default:
		{
			switch(en_gDiagMode)
			{
				case DIAG_THROUGH_STN:
				{
                    /* Reset FIFO */
                    STN_Ioctrl(STN_IOCTRL_RESET_FIFO, PNULL, 0, PNULL, 0);
        
					/* Send Data to STN */
					STN_WriteData(pu8_lFifoRefHold, u32_lLength);
                    
                    u8_gSTNMntrFlag = 0x00;
				}
				break;
				
				case DIAG_THROUGH_XTP:
				{
                    if(u32_lLength > 0)
                    {
                        /* Send Data to XTP */
                        XTP_SendRequest(pu8_lFifoRefHold, u32_lLength-1);
                    }
                    else
                    {
                        /* No Action */
                    }
				}
				break;
				
				default:
				{
					/* No Action */
				}
				break;
			}
		}
		break;
		}
	}
	else
	{
		/* No Action */
	}
        
    switch(en_gDiagMode)
    {
    case DIAG_THROUGH_XTP:
    {
        if(0x01 == u8_gStackCANintrptMange)
        {
            u8_gStackCANintrptMange = 0x00;
            
            /* enable CAn intrp */
            TE_StackSTB_Cntrl(STB_ENABLE);
            
            /* */
            en_gStnRespType = STN_NO_RECEIVE;
            
            /* Set the STN Headre to 000 */
            STN_WriteData("ATSH000\r\n",9);
            
            CAN_IF_Awake(CAN_IF_CH_0);
            
            /* Disable STN CAN */
            STN_STBCntrl(DISABLE);
            
        }
        else
        {
            /* No Action */
        }
        TEOBD2_StackHandler();
    }
    break;
    default:
      {
        if(0x00 == u8_gStackCANintrptMange)
        {
            u8_gStackCANintrptMange = 0x01;
            
             /* Disable STN CAN */
             STN_STBCntrl(ENABLE);
            
              /* */
            en_gStnRespType = STN_PROMPT;
            
            /* Disable CAn intrp */
            TE_StackSTB_Cntrl(STB_DISABLE);
            
            CAN_IF_Sleep(CAN_IF_CH_0);
        }
        else
        {
            /* No Action */
        }
      }
      break;
    }
}

/**************************************************************************************************/
/* Function Name   : TEOBD2_ErrCodes_t XT_RequestComplete(U8 * p_fData, U16 u16_fLen)             */
/*                                                                                                */
/* Description     : TEOBD2 Initialization                                                        */
/*                                                                                                */
/* In Params       : void                                                                         */
/*                                                                                                */
/* Out Params      : p_fXT_ReqCompleat                                                            */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

TEOBD2_ErrCodes_t XT_RequestComplete(INT8U *p_fData, INT32U u32_fLen)
{
    /* Variable to store the result */
    TEOBD2_ErrCodes_t en_lResult = TEOBD2_SUCCESS;

    /* Transmit char by char to Bluetooth*/
    BT43_Transmit(p_fData, u32_fLen);

    /* Return result */
    return en_lResult;
}


/**************************************************************************************************/
/* Function Name   :       void PASSTHRU_Exit(void)                                               */
/*                                                                                                */
/* Description     :        Passthru exit State                                                   */
/*                                                                                                */
/* In Params       :           void                                                               */
/*                                                                                                */
/* Out Params      :         void                                                                 */
/*                                                                                                */
/* Return Value    :         None                                                                 */
/**************************************************************************************************/

void PASSTHRU_Exit(void)
{
    /* No Action */
}

/**************************************************************************************************/
/* End of  PASSTHRU.c                                                                             */
/**************************************************************************************************/
