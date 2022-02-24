/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2017, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : CAN.c                                                                           */
/* \Author      : Yashwanth                                                                       */
/* \Version 	: v1.0                                                                            */
/* \Date        : 02-01-2018                                                                      */
/*                                                                                                */
/* @Description : CAN Driver Framework                                                            */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "NVIC.h"
#include "GCLK.h"
#include "MCLK.h"

#include "CAN.h"
#include "CAN_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

#define CAN_PCK_PRESCALER_VALUE        ( 1 )

#define CAN_ELEMENT_SIZE_MASK          ( 0x1F )
#define CAN_STD_FILT_SFEC_DIABLE       ( 0x0 << 27 )
#define CAN_STD_FILT_SFEC_MASK         ( 0x08000000 )
#define CAN_EXT_FILT_SFEC_DIABLE       ( 0x0 << 29 )
#define CAN_EXT_BUFFER_MASK            ( 0x40000000 )

#define CAN_11_BIT_ID_MASK             ( 0x1FFC0000 )
#define CAN_STD_FILT_SFID2_RX_BUFFER   ( 0 << 9 )
#define CAN_STD_FILT_SFEC_BUFFER       ( 1U << 27)
#define CAN_STD_SFT_CLASSIC_MASK       ( 2U << 30 )

#define CAN_BUFFER_DLC_MASK            ( 0x000F0000 )

#define CAN_29_BIT_ID_MASK             ( 0x1FFFFFFF )
#define CAN_EXT_FILT_EFEC_BUFFER       ( 1U << 29 )
#define CAN_EXT_FILT_EFEC_MASK         ( 0x20000000 )
#define CAN_EXT_FILT_EFID2_RX_BUFFER   ( 0U << 9 )
#define CAN_EXT_EFT_CLASSIC_MASK       ( 2U << 30 )

#define CAN_BUFFER_RXTS_MASK           (0x0000FFFF)

#define CAN_DATA_FIELD_SIZE            ( 8 )

#define CAN_MAX_STD_FLTS               ( 32 )
#define CAN_MAX_EXT_FLTS               ( 32 )
#define CAN_MAX_RXFIFO                 ( 64 )
#define CAN_MAX_TX_BUFF                ( 32 )

                                        /*  SIZE * No.of Buffers */
#define CAN_STD_FLTS_WRDS              ( 1 * CAN_MAX_STD_FLTS )
#define CAN_EXT_FLTS_WRDS              ( 2 * CAN_MAX_EXT_FLTS )
#define CAN_RXFIFO_WRDS                ( 4 * CAN_MAX_RXFIFO ) 
#define CAN_TX_DED_BUFS_WRDS           ( 4 * CAN_MAX_TX_BUFF )

#define CONF_CAN0_BTP_REG                         \
	CAN_NBTP_NBRP(CONF_CAN0_BTP_BRP - 1) | CAN_NBTP_NTSEG1(CONF_CAN0_BTP_TSEG1 - 1) \
	    | CAN_NBTP_NTSEG2(CONF_CAN0_BTP_TSEG2 - 1) | CAN_NBTP_NSJW(CONF_CAN0_BTP_SJW - 1)
			
#define CONF_CAN0_BTP_BRP 3

#define CONF_CAN0_BTP_TSEG1 11

#define CONF_CAN0_BTP_TSEG2 8

#define CONF_CAN0_BTP_SJW 4

			
/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Global Array for CAN Message RAM Configuration */
INT32U CANMsgRam[MAX_CAN][CAN_STD_FLTS_WRDS + CAN_EXT_FLTS_WRDS + CAN_TX_DED_BUFS_WRDS + 
                                                                        CAN_RXFIFO_WRDS];
/* Array of Structure Pointers to access CAN Registers */
ST_CAN_REGS_t * p_stgCANRegsAccess[MAX_CAN] = 
                                            {
                                                (ST_CAN_REGS_t *)CAN0_BASE_ADDR,
                                                (ST_CAN_REGS_t *)CAN1_BASE_ADDR,
                                            };
/* */
void (*fp_gCANUserRxHandler[MAX_CAN])(void *);
void (*fp_gCANUserTxHandler[MAX_CAN])(INT32U);
void (*fp_gCANUserBusOffHandler[MAX_CAN])(void);
void (*fp_gCANUserErrorHandler[MAX_CAN])(void);

ST_CAN_MB_CONFIG_PARAMS_t st_gReadCanMsg;                                            
                                            
INT8U au8_gCANFirstMsgBuff[MAX_CAN] = {0, };
INT8U au8_gCANMaxMsgBuff[MAX_CAN] = {0, };

ST_CAN_DATA_t st_gMcanMsgData;

/**************************************************************************************************/
/* Function Name   :                                                                              */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/**************************************************************************************************/

void CAN0_Handler(void)
{
    INT32U u32_lFifoFill, u32_lIndex = 0;
    INT32U u32_lFifoFilLevel = 0;
    INT32U u32_lCanId = 0x00;
    
    /* Check Tx Complete Flag */
    if(0 != (p_stgCANRegsAccess[CAN0]->CAN_IR & CAN_IR_TC_MASK))
    {
        p_stgCANRegsAccess[CAN0]->CAN_IR |= CAN_IR_TC_MASK;
        
        if(PNULL != fp_gCANUserTxHandler[CAN0])
        {
            /* Call User Tx Handler */
            fp_gCANUserTxHandler[CAN0](u32_lCanId);
        }
    }
    
    if(0 != (p_stgCANRegsAccess[CAN0]->CAN_IR & CAN_IR_RF0N_MASK))
    {
        p_stgCANRegsAccess[CAN0]->CAN_IR |= CAN_IR_RF0N_MASK;
        
        /* Read RXFIFO_0 Data */
        u32_lFifoFilLevel = CAN_ReadReceiveFifoData(&st_gReadCanMsg,
                                          &CANMsgRam[0][CAN_STD_FLTS_WRDS + CAN_EXT_FLTS_WRDS]);
        
        st_gMcanMsgData.u32_mCAN_ID = st_gReadCanMsg.u32_mCANId;
        
        st_gMcanMsgData.u8_mMcanDlc = st_gReadCanMsg.u8_mDlc;
        
        memcpy(&st_gMcanMsgData.au8_mMCanData[0], &st_gReadCanMsg.au8_mData[0], 
                                                            st_gMcanMsgData.u8_mMcanDlc);

        u32_lFifoFill = u32_lFifoFilLevel;
        
        if(PNULL != fp_gCANUserRxHandler[CAN0])
        {
            /* Call User Receiver Handler */
            fp_gCANUserRxHandler[CAN0]((void *)&st_gMcanMsgData);
        }
        
        if(u32_lFifoFill != 0)
        {
            for(u32_lIndex = 0; u32_lIndex < (u32_lFifoFill - 1); u32_lIndex++)
            {
                u32_lFifoFilLevel = CAN_ReadReceiveFifoData(&st_gReadCanMsg,
                                          &CANMsgRam[0][CAN_STD_FLTS_WRDS + CAN_EXT_FLTS_WRDS]);
                
                st_gMcanMsgData.u32_mCAN_ID = st_gReadCanMsg.u32_mCANId;
                
                st_gMcanMsgData.u8_mMcanDlc = st_gReadCanMsg.u8_mDlc;
                
                memcpy(&st_gMcanMsgData.au8_mMCanData[0], &st_gReadCanMsg.au8_mData[0], 
                                                                st_gMcanMsgData.u8_mMcanDlc);            
                if(PNULL != fp_gCANUserRxHandler[CAN0])
                {
                    /* Call User Receiver Handler */
                    fp_gCANUserRxHandler[CAN0]((void *)&st_gMcanMsgData);
                }
            }
        }        
    }
    
    /* Check for CAN Bus Error */
    if(0 != (p_stgCANRegsAccess[CAN0]->CAN_IR & CAN_IR_BO_MASK))
    {
        /* Clear BusOff Error  */
        p_stgCANRegsAccess[CAN0]->CAN_IR = CAN_IR_BO_MASK;
        
        if(PNULL != fp_gCANUserBusOffHandler[CAN0])
        {
            /* Call User Bus Off Handler */
            fp_gCANUserBusOffHandler[CAN0]();
        }
    }
    
    /* Check for ACK, STUFF, FORM, BIT1, BIT0 & CRC Errors */
    if(0 != (p_stgCANRegsAccess[CAN0]->CAN_PSR & CAN_PSR_LEC_MASK))
    {
        if(PNULL != fp_gCANUserErrorHandler[CAN0])
        {
            /* Call User Error Handler */
            fp_gCANUserErrorHandler[CAN0]();
        }
    }    
}

/**************************************************************************************************/
/* Function Name   :  void CAN1_Handler(void)                                                     */
/*                                                                                                */
/* Description     :  CAN Handler                                                                 */
/**************************************************************************************************/

void CAN1_Handler(void)
{
    INT32U u32_lIndex, u32_lFifoFill, u32_lFifoFilLevel = 0;
    INT32U u32_lCanId = 0x00;
    
    /* Check Tx Complete Flag */
    if(0 != (p_stgCANRegsAccess[CAN1]->CAN_IR & CAN_IR_TC_MASK))
    {
        p_stgCANRegsAccess[CAN1]->CAN_IR |= CAN_IR_TC_MASK;
        
        if(PNULL != fp_gCANUserTxHandler[CAN1])
        {
            fp_gCANUserTxHandler[CAN1](u32_lCanId);
        }
    }
    
    if(0 != (p_stgCANRegsAccess[CAN1]->CAN_IR & CAN_IR_RF0N_MASK))
    {
        p_stgCANRegsAccess[CAN1]->CAN_IR |= CAN_IR_RF0N_MASK;
        st_gReadCanMsg.en_mCANCh = CAN1;
        u32_lFifoFilLevel = CAN_ReadReceiveFifoData(&st_gReadCanMsg,
                                         &CANMsgRam[1][CAN_STD_FLTS_WRDS + CAN_EXT_FLTS_WRDS]);
        
        st_gMcanMsgData.u32_mCAN_ID = st_gReadCanMsg.u32_mCANId;
        
        st_gMcanMsgData.u8_mMcanDlc = st_gReadCanMsg.u8_mDlc;
        
        memcpy(&st_gMcanMsgData.au8_mMCanData[0], &st_gReadCanMsg.au8_mData[0], 
                                                                st_gMcanMsgData.u8_mMcanDlc);

        u32_lFifoFill = u32_lFifoFilLevel;
        
        if(PNULL != fp_gCANUserRxHandler[CAN1])
        {
            /* Call User Receiver Handler */
            fp_gCANUserRxHandler[CAN1]((void *)&st_gMcanMsgData);
        }
        
        if(u32_lFifoFill != 0)
        {
          for(u32_lIndex = 0; u32_lIndex < (u32_lFifoFill - 1); u32_lIndex++)
          {
              u32_lFifoFilLevel = CAN_ReadReceiveFifoData(&st_gReadCanMsg,
                                       &CANMsgRam[1][CAN_STD_FLTS_WRDS + CAN_EXT_FLTS_WRDS]);
              
              st_gMcanMsgData.u32_mCAN_ID = st_gReadCanMsg.u32_mCANId;
              
              st_gMcanMsgData.u8_mMcanDlc = st_gReadCanMsg.u8_mDlc;
              
              memcpy(&st_gMcanMsgData.au8_mMCanData[0], &st_gReadCanMsg.au8_mData[0], 
                                                              st_gMcanMsgData.u8_mMcanDlc);            
              if(PNULL != fp_gCANUserRxHandler[CAN1])
              {
                  /* Call User Receiver Handler */
                  fp_gCANUserRxHandler[CAN1]((void *)&st_gMcanMsgData);
              }
          }
        }
    }
    
    /* Check for CAN Bus Error */
    if(0 != (p_stgCANRegsAccess[CAN1]->CAN_IR & CAN_IR_BO_MASK))
    {
        /* Clear BusOff Error  */
        p_stgCANRegsAccess[CAN1]->CAN_IR = CAN_IR_BO_MASK;
        
        if(PNULL != fp_gCANUserBusOffHandler[CAN1])
        {
            /* Call User Bus Off Handler */
            fp_gCANUserBusOffHandler[CAN1]();
        }
    }
    
    /* Check for ACK, STUFF, FORM, BIT1, BIT0 & CRC Errors */
    if(0 != (p_stgCANRegsAccess[CAN1]->CAN_PSR & CAN_PSR_LEC_MASK))
    {
        if(PNULL != fp_gCANUserErrorHandler[CAN1])
        {
            /* Call User Error Handler */
            fp_gCANUserErrorHandler[CAN1]();
        }
    }        
    
}

/**************************************************************************************************/
/* Function Name   : EN_CAN_STATUS_t CAN_Init(ST_CAN_CONFIG_PARAMS_t * p_stfCANConfigParmas)      */
/*                                                                                                */
/* Description     : Function to Initialize the CAN                                               */
/*                                                                                                */
/* In Params       : ST_CAN_CONFIG_PARAMS_t * p_stfCANConfigParmas                                */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_STATUS_t                                                              */
/**************************************************************************************************/

EN_CAN_STATUS_t CAN_Init(ST_CAN_CONFIG_PARAMS_t * p_stfCANConfigParmas)
{
    EN_CAN_STATUS_t en_lResult = CAN_SUCCESS;
    
    EN_CAN_CH_t en_lCANCh = p_stfCANConfigParmas->en_mCANCh;
    INT32U * p_lMsgRam;
    INT32U u32_lCntr;
    
    if(CAN0 == en_lCANCh)
    {
		/* Configure Clock for CAN to derive CAN Bit Rate */
    	MCLK_PeriphClkInit(MCLK_AHB, MCLK_AHB_CANn0);
	
        /* Enable CAN0 Peripheral Clock */
        GCLK_PeripheralClockEnable(GCLK_CAN0);
        
//        BusMatrix_CANConfigure(BUSMATRIX_CAN0, (INT32U )&CANMsgRam[en_lCANCh][0]);
    }
    else if(CAN1 == en_lCANCh)
    {
		/* Configure Clock for CAN to derive CAN Bit Rate */
   		 MCLK_PeriphClkInit(MCLK_AHB, MCLK_AHB_CANn1);
	
        /* Enable CAN1 Peripheral Clock */
        GCLK_PeripheralClockEnable(GCLK_CAN1);
    
//        BusMatrix_CANConfigure(BUSMATRIX_CAN1, (INT32U )&CANMsgRam[en_lCANCh][0]);
    }
    else
    {
        /* No Action */
    }
    
    /* Initialize the CAN Bus */
    p_stgCANRegsAccess[en_lCANCh]->CAN_CCCR |= CAN_CCCR_INIT_MASK;
    
    /* Enable Configuration Change */
    p_stgCANRegsAccess[en_lCANCh]->CAN_CCCR |= CAN_CCCR_CCE_MASK;
    
    /* Reject Remote Frames & Non-matching Frames */
    p_stgCANRegsAccess[en_lCANCh]->CAN_GFC = (CAN_GFC_RRFE_MASK | CAN_GFC_RRFS_MASK | \
                                   (0x2 << CAN_GFC_ANFE_OFFSET) | (0x2 << CAN_GFC_ANFS_OFFSET));
    
    /* Extended ID Filter And Mask */
    p_stgCANRegsAccess[en_lCANCh]->CAN_XIDAM = 0x1FFFFFFF;
    
    /* Configure CAN FD */
    if(CAN_FD_ENABLE == p_stfCANConfigParmas->en_mCANFdEnRDis)
    {
        p_stgCANRegsAccess[en_lCANCh]->CAN_CCCR |= CAN_CCCR_FDOE_MASK;
    }
    else
    {
        /* Configure CAN Normal Operation */
        p_stgCANRegsAccess[en_lCANCh]->CAN_CCCR &= ~CAN_CCCR_FDOE_MASK;
        
    }

    /* Configure CAN Bit Timing */
    if(CAN_250_KBPS == p_stfCANConfigParmas->en_mBaudRate)
    {
        p_stgCANRegsAccess[en_lCANCh]->CAN_NBTP = 0x003B0700;//for Evaluation Board:0x00093360
    }
    else if(CAN_500_KBPS == p_stfCANConfigParmas->en_mBaudRate)
    {
        p_stgCANRegsAccess[en_lCANCh]->CAN_NBTP = 0x00170700;//((24 <<16) | (8 << 8) | (1 << 25) | ( 1 << 0));//0x00170700;//0x001D0700;//for Evaluation Board:0x000A0DB3
    }
    else if(CAN_1_MBPS == p_stfCANConfigParmas->en_mBaudRate)
    {
        p_stgCANRegsAccess[en_lCANCh]->CAN_NBTP = 0x00022A50;
    }
    else
    {
        /* No Action */
    }
    
    /* Configure Message RAM Addresses */
    CAN_ConfigRAMBuffers(en_lCANCh);
    
    /* Configure CAN Data Field Size */
    CAN_ConfigDataField(en_lCANCh,p_stfCANConfigParmas->en_mDataFieldSize);
    
    /* Clear New Data flags  */
    p_stgCANRegsAccess[en_lCANCh]->CAN_NDAT1 = 0xFFFFFFFF;
    
    /* Clear New Data flags  */
    p_stgCANRegsAccess[en_lCANCh]->CAN_NDAT2 = 0xFFFFFFFF;
    
    /* Configure Message Filters */
    /* Disable All Standard Filters */
    p_lMsgRam = &CANMsgRam[en_lCANCh][0];
    u32_lCntr = CAN_MAX_STD_FLTS;

    while(u32_lCntr > 0)
    {
        *p_lMsgRam++ = CAN_STD_FILT_SFEC_DIABLE;
        u32_lCntr--;
    }
    
    /* Disable All Extended Filters */
    p_lMsgRam = &CANMsgRam[en_lCANCh][CAN_STD_FLTS_WRDS];
    u32_lCntr = CAN_MAX_EXT_FLTS;
    
    while(u32_lCntr > 0)
    {
        *p_lMsgRam = CAN_EXT_FILT_SFEC_DIABLE;
        p_lMsgRam = p_lMsgRam + 2;
        u32_lCntr--;
    }
    
    /* Enable Interrupts */
    p_stgCANRegsAccess[en_lCANCh]->CAN_IE |= (CAN_IE_TCE_MASK | CAN_IE_RF0NE_MASK); 
    
    fp_gCANUserRxHandler[en_lCANCh] = p_stfCANConfigParmas->fp_RxHandler;
    fp_gCANUserTxHandler[en_lCANCh] = p_stfCANConfigParmas->fp_TxHandler;
    fp_gCANUserBusOffHandler[en_lCANCh] = p_stfCANConfigParmas->fp_BusOffHandler;
    fp_gCANUserErrorHandler[en_lCANCh] = p_stfCANConfigParmas->fp_ErrorHandler;

    if(en_lCANCh == CAN0)
    {
        p_stgCANRegsAccess[en_lCANCh]->CAN_ILE |= 0x01;
        /* Enable NVIC CAN0 Interrupt */
        NVIC_EnableInterrupt(CAN0_IRQ);
    }
    else if(en_lCANCh == CAN1)
    {
        p_stgCANRegsAccess[en_lCANCh]->CAN_ILE |= 0x01;
        
        /* Enable NVIC CAN1 Interrupt */
        NVIC_EnableInterrupt(CAN1_IRQ);  
    }
    else
    {
       /* No Action */
    }
    
    /* Configure Normal Operation & Protect the Configuration Registers */
    p_stgCANRegsAccess[en_lCANCh]->CAN_CCCR &= ~(CAN_CCCR_INIT_MASK | CAN_CCCR_CCE_MASK);
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_CAN_STATUS_t CAN_DeInit(EN_CAN_CH_t en_fCANCh)                            */
/*                                                                                                */
/* Description     : Function to Deinitialize the CAN Channel                                     */
/*                                                                                                */
/* In Params       : EN_CAN_CH_t en_fCANCh                                                        */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_STATUS_t                                                              */
/**************************************************************************************************/

EN_CAN_STATUS_t CAN_DeInit(EN_CAN_CH_t en_fCANCh)
{
    EN_CAN_STATUS_t en_lResult = CAN_SUCCESS;
    
    p_stgCANRegsAccess[en_fCANCh]->CAN_CCCR = 0x00000001;
    p_stgCANRegsAccess[en_fCANCh]->CAN_NBTP = 0x06000A03;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TSCC = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TSCV = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TOCC = 0xFFFF0000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TOCV = 0x0000FFFF;
    p_stgCANRegsAccess[en_fCANCh]->CAN_ECR  = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_PSR  = 0x00000707;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TDCR = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_IR   = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_IE   = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_ILS  = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_ILE  = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_GFC  = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_SIDFC = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_XIDFC = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_XIDAM = 0x1FFFFFFF;
    p_stgCANRegsAccess[en_fCANCh]->CAN_HPMS  = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_NDAT1 = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_NDAT2 = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_RXF0C = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_RXF0S = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_RXF0A = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_RXBC  = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_RXF1C = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_RXF1S = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_RXF1A = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_RXESC = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXBC  = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXFQS = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXESC = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXBRP = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXBAR = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXBCR = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXBTO = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXBCF = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXBTIE = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXBCIE = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXEFC = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXEFS = 0x00000000;
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXEFA = 0x00000000;
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_CAN_STATUS_t CAN_ChangeBaudRate(EN_CAN_CH_t en_fCANCh, \                  */
/*                                                  EN_CAN_BAUDRATE_t en_fBuadrate)               */
/*                                                                                                */
/* Description     : Function to Change Buadrate                                                  */
/*                                                                                                */
/* In Params       : EN_CAN_CH_t en_fCANCh, EN_CAN_BAUDRATE_t en_fBuadrate                        */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_STATUS_t                                                              */
/**************************************************************************************************/

EN_CAN_STATUS_t CAN_ChangeBaudRate(EN_CAN_CH_t en_fCANCh, EN_CAN_BAUDRATE_t en_fBuadrate)
{
    EN_CAN_STATUS_t en_lResult = CAN_SUCCESS;
    
    /* Initialize the CAN Bus */
    p_stgCANRegsAccess[en_fCANCh]->CAN_CCCR |= CAN_CCCR_INIT_MASK;
    
    /* Enable Configuration Change */
    p_stgCANRegsAccess[en_fCANCh]->CAN_CCCR |= CAN_CCCR_CCE_MASK;
    
    /* Configure CAN Bit Timing */
    if(CAN_250_KBPS == en_fBuadrate)
    {
        p_stgCANRegsAccess[en_fCANCh]->CAN_NBTP = 0x003B0700;//for Evaluation Board:0x00093360
    }
    else if(CAN_500_KBPS == en_fBuadrate)
    {
        p_stgCANRegsAccess[en_fCANCh]->CAN_NBTP = 0x00030300;//for Evaluation Board:0x000A0DB3

    }
    else if(CAN_1_MBPS == en_fBuadrate)
    {
        p_stgCANRegsAccess[en_fCANCh]->CAN_NBTP = 0x00022A50;
    }
    else
    {
        en_lResult = CAN_FAILURE;
    }
    
    /* Configure Normal Operation & Protect the Configuration Registers */
    p_stgCANRegsAccess[en_fCANCh]->CAN_CCCR &= ~(CAN_CCCR_INIT_MASK | CAN_CCCR_CCE_MASK);    
        
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_CAN_STATUS_t CAN_Sleep(EN_CAN_CH_t en_fCANCh)                             */
/*                                                                                                */
/* Description     : Function to keep CAN in Sleep mode                                           */
/*                                                                                                */
/* In Params       : EN_CAN_CH_t en_fCANCh                                                        */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_STATUS_t                                                              */
/**************************************************************************************************/

EN_CAN_STATUS_t CAN_Sleep(EN_CAN_CH_t en_fCANCh)
{
    EN_CAN_STATUS_t en_lResult = CAN_SUCCESS;
    
    /* Request for Clock to Stop */
    p_stgCANRegsAccess[en_fCANCh]->CAN_CCCR |= CAN_CCCR_CSR_MASK;
    
    /* Wait for All Pending Requests will be Over */
    while(!(p_stgCANRegsAccess[en_fCANCh]->CAN_CCCR & CAN_CCCR_INIT_MASK));
    
    /* Wait for Clock Stop Acknowledges */
    while(!(p_stgCANRegsAccess[en_fCANCh]->CAN_CCCR & CAN_CCCR_CSA_MASK));
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_CAN_STATUS_t CAN_Wakeup(EN_CAN_CH_t en_fCANCh)                            */
/*                                                                                                */
/* Description     : Function to Wakeup CAN channel from Sleep                                    */
/*                                                                                                */
/* In Params       : EN_CAN_CH_t en_fCANCh                                                        */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_STATUS_t                                                              */
/**************************************************************************************************/

EN_CAN_STATUS_t CAN_Wakeup(EN_CAN_CH_t en_fCANCh)
{
    EN_CAN_STATUS_t en_lResult = CAN_SUCCESS;
    
    if(CAN0 == en_fCANCh)
    {
        /* Enable CAN0 Peripheral Clock */
        GCLK_PeripheralClockEnable(GCLK_CAN0);
    }
    else if(CAN1 == en_fCANCh)
    {
        /* Enable CAN1 Peripheral Clock */
        GCLK_PeripheralClockEnable(GCLK_CAN1);
    }
    else
    {
        en_lResult = CAN_FAILURE;
    }
    
    /* Clear Clock Stop Request */
    p_stgCANRegsAccess[en_fCANCh]->CAN_CCCR &= ~CAN_CCCR_CSR_MASK;
    
    /* Wait for Clock Enable Acknowledges */
    while(p_stgCANRegsAccess[en_fCANCh]->CAN_CCCR & CAN_CCCR_CSA_MASK);
    
    /* Start CAN Transmission & Reception */
    p_stgCANRegsAccess[en_fCANCh]->CAN_CCCR &= ~CAN_CCCR_INIT_MASK;
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_CAN_STATUS_t CAN_ConfigTxMsgBuff(ST_CAN_MB_CONFIG_PARAMS_t                */
/*                           * p_stfMBConfigParams,ST_CAN_CONFIG_PARAMS_t * p_stfCANConfigParmas) */
/*                                                                                                */
/* Description     : Function to Configure Transmit Message Buffer                                */
/*                                                                                                */
/* In Params       : ST_CAN_MB_CONFIG_PARAMS_t * p_stfMBConfigParams,                             */
/*                                ST_CAN_CONFIG_PARAMS_t * p_stfCANConfigParmas                    */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_CAN_STATUS_t CAN_ConfigTxMsgBuff(ST_CAN_MB_CONFIG_PARAMS_t * p_stfMBConfigParams)
{
    EN_CAN_STATUS_t en_lResult = CAN_SUCCESS;
    
    INT32U * p_lMsgRamAddr = 0;
    EN_CAN_CH_t en_lCANCh = p_stfMBConfigParams->en_mCANCh;
    INT8U u8_lMsgBuffNo = p_stfMBConfigParams->u8_mMsgBuffNo;
    INT32U u32_lTxLBuff = 0;
    INT32U u32_lTxHBuff = 0;
    INT8U u8_lIndex = 0;
   
    if(CAN_MB_TRANSMIT == p_stfMBConfigParams->en_MsgBuffType)
    {
        if(p_stfMBConfigParams->u8_mMsgBuffNo < 32)
        {
            
            p_lMsgRamAddr = (&CANMsgRam[en_lCANCh][CAN_STD_FLTS_WRDS + CAN_EXT_FLTS_WRDS + 
                             CAN_RXFIFO_WRDS]+ (u8_lMsgBuffNo * ((CAN_DATA_FIELD_SIZE/4) + 2)));
            
            if(CAN_STD_ID == p_stfMBConfigParams->en_mIdType)
            {
                *p_lMsgRamAddr = ((p_stfMBConfigParams->u32_mCANId << 18) & 
                                                    (CAN_11_BIT_ID_MASK));
                
                p_lMsgRamAddr = p_lMsgRamAddr + 1;
            }
            else
            {
                *p_lMsgRamAddr = CAN_EXT_BUFFER_MASK |
                            (p_stfMBConfigParams->u32_mCANId & CAN_29_BIT_ID_MASK);
                
                p_lMsgRamAddr = p_lMsgRamAddr + 1;
            }
            
            /* Configure DLC */
            *p_lMsgRamAddr = (p_stfMBConfigParams->u8_mDlc << 16);
            
            p_lMsgRamAddr = p_lMsgRamAddr + 1;
            
            /* Configure Data in TX Buffer */
            for(u8_lIndex= 0; u8_lIndex < 8; u8_lIndex++)
            {
                if(u8_lIndex < 4)
                {
                    u32_lTxLBuff |= (p_stfMBConfigParams->au8_mData[u8_lIndex] << (u8_lIndex * 8));
                }
                else
                {
                    u32_lTxHBuff|= (p_stfMBConfigParams->au8_mData[u8_lIndex] << 
                                                                ((u8_lIndex - 4) * 8));
                }
            }
            
            /* Write Lower Data Byte */
            *p_lMsgRamAddr = u32_lTxLBuff;
            
            p_lMsgRamAddr = p_lMsgRamAddr + 1;
            
            /* Write Higher Data Byte */
            *p_lMsgRamAddr = u32_lTxHBuff;
            
            /* Enable Transmit Interrupt */
            p_stgCANRegsAccess[p_stfMBConfigParams->en_mCANCh]->CAN_TXBTIE |= (1 << u8_lMsgBuffNo);
        }
        else
        {
            en_lResult = CAN_FAILURE;
        }
    }
    else
    {
        en_lResult = CAN_FAILURE;
    }

    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_CAN_STATUS_t CAN_ConfigMsgBuffData(ST_CAN_MB_CONFIG_PARAMS_t              */
/*                                                                      * p_stfMBConfigParams)    */
/*                                                                                                */
/* Description     : Function to Configure Message Buffer Data                                    */
/*                                                                                                */
/* In Params       : ST_CAN_MB_CONFIG_PARAMS_t * p_stfMBConfigParams                              */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_STATUS_t                                                              */
/**************************************************************************************************/

EN_CAN_STATUS_t CAN_ConfigMsgBuffData(ST_CAN_MB_CONFIG_PARAMS_t * p_stfMBConfigParams)
{
    EN_CAN_STATUS_t en_lResult = CAN_SUCCESS;
    
    INT32U * p_lMsgRamAddr = 0;
    EN_CAN_CH_t en_lCANCh = p_stfMBConfigParams->en_mCANCh;
    INT8U u8_lMsgBuffNo = p_stfMBConfigParams->u8_mMsgBuffNo;
    INT32U u32_lTxLBuff = 0;
    INT32U u32_lTxHBuff = 0;
    INT8U u8_lIndex = 0;

    if(p_stfMBConfigParams->u8_mMsgBuffNo < 32)
    {
        
        p_lMsgRamAddr = (&CANMsgRam[en_lCANCh][CAN_STD_FLTS_WRDS + CAN_EXT_FLTS_WRDS + 
                         CAN_RXFIFO_WRDS]+ (u8_lMsgBuffNo * ((CAN_DATA_FIELD_SIZE/4) + 2)));
        
        p_lMsgRamAddr = p_lMsgRamAddr + 1;
        
        /* Configure DLC */
        *p_lMsgRamAddr = (p_stfMBConfigParams->u8_mDlc << 16);
        
        p_lMsgRamAddr = p_lMsgRamAddr + 1;
        
        /* Configure Data in TX Buffer */
        for(u8_lIndex= 0; u8_lIndex < 8; u8_lIndex++)
        {
            if(u8_lIndex < 4)
            {
                u32_lTxLBuff |= (p_stfMBConfigParams->au8_mData[u8_lIndex] << (u8_lIndex * 8));
            }
            else
            {
                u32_lTxHBuff|= (p_stfMBConfigParams->au8_mData[u8_lIndex] << 
                                                            ((u8_lIndex - 4) * 8));
            }
        }
        
        /* Write Lower Data Byte */
        *p_lMsgRamAddr = u32_lTxLBuff;
        
        p_lMsgRamAddr = p_lMsgRamAddr + 1;
        
        /* Write Higher Data Byte */
        *p_lMsgRamAddr = u32_lTxHBuff;
    }
    else
    {
        en_lResult = CAN_FAILURE;
    }

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

EN_CAN_STATUS_t CAN_ConfigRxMsgBuff(ST_CAN_MB_CONFIG_PARAMS_t * p_stfMBConfigParams)
{
    EN_CAN_STATUS_t en_lResult = CAN_SUCCESS;
    
    EN_CAN_CH_t en_lCANCh = p_stfMBConfigParams->en_mCANCh;
    INT32U u32_lAcceptMsk = p_stfMBConfigParams->u32_mAcceptMsk;
    INT32U * p_lRxFiltAddr = 0;

    if(CAN_MB_RECEIVE == p_stfMBConfigParams->en_MsgBuffType)
    {
        if(p_stfMBConfigParams->u8_mMsgBuffNo < 64)
        {
            /* Standard Filter Configuration for acceptance Masking  */
            if(CAN_STD_ID == p_stfMBConfigParams->en_mIdType)
            {
                p_lRxFiltAddr = &CANMsgRam[en_lCANCh][0] + p_stfMBConfigParams->u8_mMsgBuffNo;     
                
                *p_lRxFiltAddr = (INT32U)((p_stfMBConfigParams->u32_mCANId << 16) |
                  CAN_STD_FILT_SFEC_BUFFER | CAN_STD_SFT_CLASSIC_MASK | u32_lAcceptMsk);
            }
            else
            {
                /* Extended Filter Configuration for acceptance Masking */
                p_lRxFiltAddr = &CANMsgRam[en_lCANCh][CAN_STD_FLTS_WRDS] +
                                                        (2 * p_stfMBConfigParams->u8_mMsgBuffNo);
                
                /* Configure Extended Filter and write CAN ID */
                *p_lRxFiltAddr++ = (INT32U )CAN_EXT_FILT_EFEC_BUFFER |
                                                    p_stfMBConfigParams->u32_mCANId;
                
                /* Configure Classic Filter and write Mask  */
                *p_lRxFiltAddr = (INT32U)(CAN_EXT_EFT_CLASSIC_MASK | u32_lAcceptMsk);    
            }
        }
        else
        {
            en_lResult = CAN_FAILURE;
        }

    }
    else
    {
        en_lResult = CAN_FAILURE;
    }
    
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

EN_CAN_STATUS_t CAN_EnDisMsgBuff(EN_CAN_CH_t en_fCANCh, EN_CAN_ID_TYPE en_fIdType,
                                 INT8U u8_fRxMsgBuffNo, EN_CAN_MSG_BUFF_CTRL_t en_fMBCtrl)
{
    EN_CAN_STATUS_t en_lResult = CAN_SUCCESS;
    
    INT32U * p_fRamAddr;
    
    if(CAN_DISABLE_MSG_BUFF == en_fMBCtrl)
    {
        if(CAN_STD_ID == en_fIdType)
        {
            /* Disable Filter Elements for Stanadard ID's */
            p_fRamAddr = &CANMsgRam[en_fCANCh][0] + u8_fRxMsgBuffNo;
            *p_fRamAddr &= ~CAN_STD_FILT_SFEC_MASK;
        }
        else
        {
            /* Disable Filter Elements for Extended ID's */
            p_fRamAddr = &CANMsgRam[en_fCANCh][CAN_STD_FLTS_WRDS] + (2 * u8_fRxMsgBuffNo);
            *p_fRamAddr &= ~CAN_EXT_FILT_EFEC_MASK;
        }
    }
    else if(CAN_ENABLE_MSG_BUFF == en_fMBCtrl)
    {
        if(CAN_STD_ID == en_fIdType)
        {
            /* Disable Filter Elements for Stanadard ID's */
            p_fRamAddr = &CANMsgRam[en_fCANCh][0] + u8_fRxMsgBuffNo;
            *p_fRamAddr |= CAN_STD_FILT_SFEC_BUFFER;
        }
        else
        {
            /* Disable Filter Elements for Extended ID's */
            p_fRamAddr = &CANMsgRam[en_fCANCh][CAN_STD_FLTS_WRDS] + (2 * u8_fRxMsgBuffNo);
            *p_fRamAddr |= CAN_EXT_FILT_EFEC_BUFFER;
        }
    }
    else
    {
        en_lResult = CAN_FAILURE;
    }
    
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

EN_CAN_STATUS_t CAN_TransmitDataBuffer(EN_CAN_CH_t en_fCANCh, INT8U u8_fMsgBuffer)
{
    EN_CAN_STATUS_t en_lResult = CAN_SUCCESS;
    
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXBAR |= (1 << u8_fMsgBuffer);
    
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

INT8U CAN_CheckReceiveFlag(EN_CAN_CH_t en_fCANCh, INT8U u8_fMsgBuffNo)
{
    INT8U u8_lRxFlag = 0;
    
    if(p_stgCANRegsAccess[en_fCANCh]->CAN_NDAT1 & (1 << u8_fMsgBuffNo))
    {
        u8_lRxFlag = 1;
    }
    else
    {
        u8_lRxFlag = 0;
    }
    
    return u8_lRxFlag;
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

INT32U CAN_ReadReceiveFifoData(ST_CAN_MB_CONFIG_PARAMS_t * p_stfMBConfigParams,
                                                                       INT32U * p_fFifoAddr)
{
    INT32U u32_lGetIndex, u32_lFillLevel, u32_lElmntSize, u32_lTempRx;
    INT32U * p_lFifoAckReg;
    INT32U * pRxFifo = 0;
    EN_CAN_CH_t en_lCANCh = p_stfMBConfigParams->en_mCANCh;
    INT8U * p_RxData, u8_lLen;
    
    u32_lFillLevel = 0;

    u32_lGetIndex = (p_stgCANRegsAccess[en_lCANCh]->CAN_RXF0S & CAN_RXF0S_F0GI_MASK) >> 
                                    CAN_RXF0S_F0GI_OFFSET;

    u32_lFillLevel = (p_stgCANRegsAccess[en_lCANCh]->CAN_RXF0S & CAN_RXF0S_F0FL_MASK) >>
                                        CAN_RXF0S_F0FL_OFFSET;

    pRxFifo = p_fFifoAddr;
    u32_lElmntSize = 0x4 & 0x1F;
    p_lFifoAckReg = (INT32U *)&p_stgCANRegsAccess[en_lCANCh]->CAN_RXF0A;
   
    if(u32_lFillLevel > 0)
    {
        pRxFifo = pRxFifo + (u32_lGetIndex * u32_lElmntSize);
        
        u32_lTempRx = *pRxFifo++;
        
        if(u32_lTempRx & CAN_EXT_BUFFER_MASK)
        {
            p_stfMBConfigParams->en_mIdType = CAN_EXTENDED_ID;
            p_stfMBConfigParams->u32_mCANId = u32_lTempRx & CAN_29_BIT_ID_MASK;
        }
        else
        {
            p_stfMBConfigParams->en_mIdType = CAN_STD_ID;
            p_stfMBConfigParams->u32_mCANId = (u32_lTempRx & CAN_11_BIT_ID_MASK) >> 18;
        }
        
        /* Read Word R1 */
        u32_lTempRx = *pRxFifo++;
        
        p_stfMBConfigParams->u8_mDlc = (u32_lTempRx & CAN_BUFFER_DLC_MASK) >> 16;
        
        p_RxData = (INT8U *)pRxFifo;
        
        for(u8_lLen = 0; u8_lLen < p_stfMBConfigParams->u8_mDlc; u8_lLen++)
        {
            /* Copy the Data into User Buffer */
            p_stfMBConfigParams->au8_mData[u8_lLen] = *p_RxData++;
        }
    
        *p_lFifoAckReg = u32_lGetIndex;
        
        p_stgCANRegsAccess[en_lCANCh]->CAN_IR |= CAN_IE_RF0NE_MASK;
    }

    return u32_lFillLevel;
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

EN_CAN_STATUS_t CAN_ReadMessageBuffer(ST_CAN_MB_CONFIG_PARAMS_t * p_stfMBConfigParams, 
                          INT16U u16_fRxBuffElmnts, INT32U ** p_fRxBuffAddr, INT8U u8_fRxBuff)
{
    EN_CAN_STATUS_t en_lResult = CAN_SUCCESS;
    
    INT32U * p_RxBuff = 0;
    INT32U u32_lTempRxBuff = 0;
    INT8U u8_lLen = 0;
    INT8U * p_RxData = 0;
    
    if(u8_fRxBuff < u16_fRxBuffElmnts)
    {
        p_RxBuff = *p_fRxBuffAddr + (u8_fRxBuff * 4);
            
        u32_lTempRxBuff = *p_RxBuff++;  /* Read Word0 to get CAN ID */
        
        if(u32_lTempRxBuff & CAN_EXT_BUFFER_MASK)
        {
            /* Store Extended ID */
            p_stfMBConfigParams->u32_mCANId = u32_lTempRxBuff & CAN_29_BIT_ID_MASK;
            
        }
        else
        {
            /* Store Standard ID */
            p_stfMBConfigParams->u32_mCANId = (u32_lTempRxBuff & CAN_11_BIT_ID_MASK) >> 18;

        }
        
        /* Word 1 Contains DLC & Time Stamp */
        u32_lTempRxBuff = *p_RxBuff++;
        
        p_stfMBConfigParams->u8_mDlc = (u32_lTempRxBuff & CAN_BUFFER_DLC_MASK) >> 16;
        
        /* Copy the Data from the Buffer to the Mailbox */
        p_RxData = (INT8U *)p_RxBuff;
        
        for(u8_lLen = 0; u8_lLen < p_stfMBConfigParams->u8_mDlc; u8_lLen++)
        {
            /* Copy the Data into User Buffer */
            p_stfMBConfigParams->au8_mData[u8_lLen] = *p_RxData++;
        }
        
        /* Clear the New Data Flag for the Buffer */
        if(u8_fRxBuff < 32)
        {
            p_stgCANRegsAccess[p_stfMBConfigParams->en_mCANCh]->CAN_NDAT1 = (1 << u8_fRxBuff);
            
            
        }
        else
        {
            p_stgCANRegsAccess[p_stfMBConfigParams->en_mCANCh]->CAN_NDAT2 = (1 << (u8_fRxBuff - 32));
        }
        
        /* Clear Receive Flag */
        p_stgCANRegsAccess[p_stfMBConfigParams->en_mCANCh]->CAN_IR = CAN_IR_DRX_MASK;
    }
   
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_CAN_STATUS_t CAN_ConfigDataField(EN_CAN_CH_t en_fCANCh,                   */
/*                                                EN_CAN_DATA_SIZE_t en_fDataSize)                */
/*                                                                                                */
/* Description     : Function to configure CAN Data Field Size                                    */
/*                                                                                                */
/* In Params       : EN_CAN_CH_t en_fCANCh, EN_CAN_DATA_SIZE_t en_fDataSize                       */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_STATUS_t                                                              */
/**************************************************************************************************/

EN_CAN_STATUS_t CAN_ConfigDataField(EN_CAN_CH_t en_fCANCh, EN_CAN_DATA_SIZE_t en_fDataSize)
{
    EN_CAN_STATUS_t en_lResult = CAN_SUCCESS;
    
    if(CAN_8_BYTE_DATA == en_fDataSize)
    {
        /* Configure Rx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_RXESC &= ~CAN_RXESC_F0DS_MASK;
        
        /* Configure Tx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_TXESC &= ~CAN_TXESC_TBDS_MASK;
    }
    else if(CAN_12_BYTE_DATA == en_fDataSize)
    {
        /* Configure Rx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_RXESC &= ~CAN_RXESC_F0DS_MASK;
        
        /* Configure Tx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_TXESC |= CAN_TXESC_TBDS_12_BYTE_MASK;
    }
    else if(CAN_16_BYTE_DATA == en_fDataSize)
    {
        /* Configure Rx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_RXESC &= ~CAN_RXESC_F0DS_MASK;
        
        /* Configure Tx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_TXESC |= CAN_TXESC_TBDS_16_BYTE_MASK;
    }
    else if(CAN_20_BYTE_DATA == en_fDataSize)
    {
        /* Configure Rx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_RXESC &= ~CAN_RXESC_F0DS_MASK;
        
        /* Configure Tx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_TXESC |= CAN_TXESC_TBDS_20_BYTE_MASK;
    }
    else if(CAN_24_BYTE_DATA == en_fDataSize)
    {
        /* Configure Rx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_RXESC &= ~CAN_RXESC_F0DS_MASK;
        
        /* Configure Tx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_TXESC |= CAN_TXESC_TBDS_24_BYTE_MASK;
    }
    else if(CAN_32_BYTE_DATA == en_fDataSize)
    {
        /* Configure Rx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_RXESC &= ~CAN_RXESC_F0DS_MASK;
        
        /* Configure Tx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_TXESC |= CAN_TXESC_TBDS_32_BYTE_MASK;
    }
    else if(CAN_48_BYTE_DATA == en_fDataSize)
    {
        /* Configure Rx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_RXESC &= ~CAN_RXESC_F0DS_MASK;
        
        /* Configure Tx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_TXESC |= CAN_TXESC_TBDS_48_BYTE_MASK;
    }
    else if(CAN_64_BYTE_DATA == en_fDataSize)
    {
        /* Configure Rx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_RXESC &= ~CAN_RXESC_F0DS_MASK;
        
        /* Configure Tx Data Field Size */
        p_stgCANRegsAccess[en_fCANCh]->CAN_TXESC |= CAN_TXESC_TBDS_64_BYTE_MASK;
    }
    else
    {
        /* No Action */
    }
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : EN_CAN_STATUS_t CAN_ConfigRAMBuffers(EN_CAN_CH_t en_fCANCh)                  */
/*                                                                                                */
/* Description     : Function to Configure Message RAM address                                    */
/*                                                                                                */
/* In Params       : EN_CAN_CH_t en_fCANCh                                                        */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_STATUS_t                                                              */
/**************************************************************************************************/

EN_CAN_STATUS_t CAN_ConfigRAMBuffers(EN_CAN_CH_t en_fCANCh)
{
    EN_CAN_STATUS_t en_lResult = CAN_SUCCESS;
    
    /* Configure Message RAM Starting Addresses & Sizes */
    /* Configure Standard Filters */
    p_stgCANRegsAccess[en_fCANCh]->CAN_SIDFC = ((0xFFFC & (INT32U )&CANMsgRam[en_fCANCh][0]) |
                                                 (CAN_MAX_STD_FLTS << CAN_SIDFC_LSS_OFFSET));
                               
    /* Configure Extended Filters */
    p_stgCANRegsAccess[en_fCANCh]->CAN_XIDFC = 
       ((0xFFFC & (INT32U )&CANMsgRam[en_fCANCh][CAN_STD_FLTS_WRDS]) |
                                                (CAN_MAX_EXT_FLTS << CAN_XIDFC_LSE_OFFSET));  
        
    /* Configure RxFIFO Size in RAM */
    p_stgCANRegsAccess[en_fCANCh]->CAN_RXF0C = 
           ((0xFFFC & (INT32U )&CANMsgRam[en_fCANCh][CAN_STD_FLTS_WRDS + CAN_EXT_FLTS_WRDS]) | 
                        (CAN_MAX_RXFIFO << CAN_RX0FC_F0S_OFFSET) | CAN_RX0FC_F0OM_MASK);
     
    /* Configure Tx Buffer Size in RAM*/
    p_stgCANRegsAccess[en_fCANCh]->CAN_TXBC = 
    ((0xFFFC & (INT32U)&CANMsgRam[en_fCANCh][CAN_STD_FLTS_WRDS + CAN_EXT_FLTS_WRDS + 
                                CAN_RXFIFO_WRDS]) | (CAN_MAX_TX_BUFF << CAN_TXBC_NDTB_OFFSET));

    return en_lResult;    
}

/**************************************************************************************************/
/* Function Name   : EN_CAN_STATUS_t CAN_ConfigRAMBuffers(EN_CAN_CH_t en_fCANCh)                  */
/*                                                                                                */
/* Description     : Function to Configure Message RAM address                                    */
/*                                                                                                */
/* In Params       : EN_CAN_CH_t en_fCANCh                                                        */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_CAN_STATUS_t                                                              */
/**************************************************************************************************/

EN_IOCTRL_STATUS_t CAN_Ioctrl(EN_CAN_IOCTRLI_ID_t en_Ioctrl_ID, EN_CAN_CH_t en_CAN_Chnl , \
                                            INT32U en_fArbitrtnID, EN_CAN_BAUDRATE_t en_fBaudrtae , \
                                                       EN_CAN_ID_TYPE en_fIDType,INT8U u8_fMONumber)
{
    /* Update the Result */
    EN_IOCTRL_STATUS_t en_lResult = IOCTRL_SUCCESS;
    
    /* */
    ST_CAN_MB_CONFIG_PARAMS_t st_lMBConfig;
      
    switch(en_Ioctrl_ID)
    {
    case CAN_BAUDRTAE_CHNAGE:
        
        /* */
        CAN_ChangeBaudRate(en_CAN_Chnl ,en_fBaudrtae);
        break;
     
     case CAN_ID_CHNAGE:
       
        /* Update the RX MB with ID  And Initialize */
        st_lMBConfig.en_mCANCh = (EN_CAN_CH_t )en_CAN_Chnl;
        st_lMBConfig.u8_mMsgBuffNo  = u8_fMONumber;
        st_lMBConfig.u32_mCANId = en_fArbitrtnID;
        st_lMBConfig.u8_mDlc = 8;
        st_lMBConfig.en_mIdType = en_fIDType;

        /* Configure Tx message buffer*/
        CAN_ConfigTxMsgBuff(&st_lMBConfig);
        
        break;
        
     case CAN_IDTYPE_CHNAGE:
       
        /* Update the RX MB with ID type And Initialize */
        st_lMBConfig.en_mCANCh = (EN_CAN_CH_t )en_CAN_Chnl;
        st_lMBConfig.u8_mMsgBuffNo  = u8_fMONumber;
        st_lMBConfig.u32_mCANId = en_fArbitrtnID;
        st_lMBConfig.u8_mDlc = 8;
        st_lMBConfig.en_mIdType = en_fIDType;

        /* Configure Tx message buffer*/
        CAN_ConfigTxMsgBuff(&st_lMBConfig);
        
        break;
        
    default:
      en_lResult = IOCTRL_FAIL;
      break;
      
    }

    /* Return The Result */
    return en_lResult;
}

/**************************************************************************************************/
/* End of CAN.c                                                                                   */
/**************************************************************************************************/