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
/* \File Name   : SPI.c                                                                           */
/* \Author      : Kishore D                                                                       */
/* \Version     : 1.0                                                                             */
/* \Date        : 22/08/2018                                                                      */
/*                                                                                                */
/* @Description :  SPI Driver                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "SPI.h"
#include "SPI_Priv.h"

#include "NVIC.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Structure Pointer to Access SPI System Registers */
ST_SPI_SYS_REGS_t *p_stgSPIBaseRegs[MAX_SERCOM_CHANNELS] = {
                                                              (ST_SPI_SYS_REGS_t *)SERCOM0_BASE_ADDRESS,	
                                                              (ST_SPI_SYS_REGS_t *)SERCOM1_BASE_ADDRESS,
                                                              (ST_SPI_SYS_REGS_t *)SERCOM2_BASE_ADDRESS,
                                                              (ST_SPI_SYS_REGS_t *)SERCOM3_BASE_ADDRESS,
                                                              (ST_SPI_SYS_REGS_t *)SERCOM4_BASE_ADDRESS,
                                                              (ST_SPI_SYS_REGS_t *)SERCOM5_BASE_ADDRESS,
                                                              (ST_SPI_SYS_REGS_t *)SERCOM6_BASE_ADDRESS,
                                                              (ST_SPI_SYS_REGS_t *)SERCOM7_BASE_ADDRESS,
                                                            };

ST_SPI_MASTER_CONFIG_PARAMS_t * pst_gSPISlaveConfigParam = PNULL;

/**************************************************************************************************/
/* Function Name   :  void SERCOM2_Handler(void)                                                  */
/*                                                                                                */
/* Description     :  SERCOM2 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/	
extern void CS_Low(void);

void SERCOM1_2_Handler(void)
{
  INT8U u8_lSPISlaveData = 0x00;
  
  if(p_stgSPIBaseRegs[SERCOM_CH1]->INTFLAG & SERCOM_SPI_INTFLAG_RXC_MASK)
  {        
        p_stgSPIBaseRegs[SERCOM_CH1]->INTFLAG |= SERCOM_SPI_INTFLAG_RXC_MASK;
        
        u8_lSPISlaveData = p_stgSPIBaseRegs[SERCOM_CH1]->DATA;          
        pst_gSPISlaveConfigParam->fp_USERHANDLER(u8_lSPISlaveData); 
  }
}	

/**************************************************************************************************/
/* Function Name   : void SPI_MasterInit(ST_SPI_MASTER_CONFIG_PARAMS_t *p_stgSPIMasterConfigParams*/
/*                                                                                                */
/* Description     : This function used to intialize the SPI                                      */
/*                                                                                                */
/* In Params       : p_stgSPIMasterConfigParams                                                   */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/
														   
void SPI_MasterInit(ST_SPI_MASTER_CONFIG_PARAMS_t *p_stgSPIMasterConfigParams)
{
    INT32U u32_lSERChannel = p_stgSPIMasterConfigParams->en_mChannel;
    INT8U u8_lBaudValue = 0;
    
    switch(u32_lSERChannel)
    {
    case SERCOM_CH0 :
        MCLK_PeriphClkInit(MCLK_APBA, MCLK_APBA_SERCOM0);
        break;

    case SERCOM_CH1 :
        MCLK_PeriphClkInit(MCLK_APBA, MCLK_APBA_SERCOM1);
        break;

    case SERCOM_CH2 :
        MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_SERCOM2);
        break;

    case SERCOM_CH3 :
        MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_SERCOM3);
        break;

    case SERCOM_CH4 :
        MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_SERCOM4);
        break;

    case SERCOM_CH5 :
        MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_SERCOM5);
        break;

    case SERCOM_CH6 :
        MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_SERCOM6);
        break;

    case SERCOM_CH7 :
        MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_SERCOM7);
        break;
    default :
        break;
    }
    
    /* Enable GCLK Clock for SERCOM */
    GCLK_EnableSERCOMClock((EN_GCLK_SERCOM_CH_SEL_t )p_stgSPIMasterConfigParams->en_mChannel);

    /*Disable the SPI */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA &= ~(SERCOM_SPI_CTRLA_ENABLE_MASK);

    /* Perform Software Reset */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA = SERCOM_SPI_CTRLA_SWRST_MASK;

    /* Waiting for SWRST SYNC */
    while(p_stgSPIBaseRegs[u32_lSERChannel]->SYNCBUSY & SERCOM_SPI_SYNCBUSY_SWRST_MASK);
            
    /* Configuring SPI in Master Mode */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA |= SERCOM_SPI_CTRLA_MASTER_MODE;

    /* Inter Character Spacing 3 ClK Cycles */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLC |= 0x3;

    /* Configuring Clock Polarity & Clock Phase */
    /* Configuring Clock Phase as Mode 0,1,2,3 */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA |= \
            (p_stgSPIMasterConfigParams->en_mClockPhaseSel << SERCOM_SPI_CTRLA_CPHA_POS);

    /* Selecting Frame Form Value as SPI frame  */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA &= ~(1 << SERCOM_SPI_CTRLA_FORM_POS);

    /* Selecting Pad for DIPO (MISO) */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA |= (p_stgSPIMasterConfigParams->en_mMISOPadSel << 20);

    /* Selecting Pad for DOPO (MOSI) and SCLK */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA |= (p_stgSPIMasterConfigParams->en_mMOSIPadSel << 16);

    /* Select the Character Size (8 bits ) */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLB |= 0x0;

    /* Select the data order (MSB or LSB first) */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA |= (p_stgSPIMasterConfigParams->en_mDataOrder << 30);

    /* Calculate the Baud value for desired baudrate */
    u8_lBaudValue = SPI_CalculateBaudrate(p_stgSPIMasterConfigParams->u32_mBaudrate);

    /* set the baud value in BAUD register */
    p_stgSPIBaseRegs[u32_lSERChannel]->BAUD = u8_lBaudValue;

    /* Select the Control for SS (software or Hardware) */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLB |= (p_stgSPIMasterConfigParams->en_mSSControlSel << 13);
    
   /* Rx Interrupt Enable */
    p_stgSPIBaseRegs[u32_lSERChannel]->INTENSET |= (SERCOM_SPI_INTENSET_RXC \
                                    | SERCOM_SPI_INTENSET_ERROR);
    
    switch(u32_lSERChannel)
    {
    case SERCOM_CH0 :
        NVIC_EnableInterrupt(SERCOM0_2_IRQ);
        break;

    case SERCOM_CH1 :
        NVIC_EnableInterrupt(SERCOM1_2_IRQ);
        break;

    case SERCOM_CH2 :
        NVIC_EnableInterrupt(SERCOM2_2_IRQ);
        break;

    case SERCOM_CH3 :
        NVIC_EnableInterrupt(SERCOM3_2_IRQ);
        break;

    case SERCOM_CH4 :
        NVIC_EnableInterrupt(SERCOM4_2_IRQ);
        break;

    case SERCOM_CH5 :
        NVIC_EnableInterrupt(SERCOM5_2_IRQ);
        break;

    case SERCOM_CH6 :
        NVIC_EnableInterrupt(SERCOM6_2_IRQ);
        break;

    case SERCOM_CH7 :
        NVIC_EnableInterrupt(SERCOM7_2_IRQ);
        break;
    default :
        break;
    }

    /* Enable Receiver */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLB |= (1 << 17);
    
    /* Enable SPI */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA |= (1 << 1);
    
    /* Waiting for Enable to SYNC */
    while(p_stgSPIBaseRegs[u32_lSERChannel]->SYNCBUSY & SERCOM_SPI_SYNCBUSY_ENABLE_MASK);
    
    /* */
    pst_gSPISlaveConfigParam = p_stgSPIMasterConfigParams;    
}
	
/**************************************************************************************************/
/* Function Name   : void SPI_MasterInit(ST_SPI_MASTER_CONFIG_PARAMS_t *p_stgSPIMasterConfigParams*/
/*                                                                                                */
/* Description     : This function used to intialize the SPI                                      */
/*                                                                                                */
/* In Params       : p_stgSPIMasterConfigParams                                                   */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void SPI_SlaveInit(ST_SPI_MASTER_CONFIG_PARAMS_t *p_stgSPIMasterConfigParams)
{
    EN_SPI_SERCOM_CH_SEL_t u32_lSERChannel = p_stgSPIMasterConfigParams->en_mChannel;
    
    switch(u32_lSERChannel)
    {
    case SERCOM_CH0 :
        MCLK_PeriphClkInit(MCLK_APBA, MCLK_APBA_SERCOM0);
        break;

    case SERCOM_CH1 :
        MCLK_PeriphClkInit(MCLK_APBA, MCLK_APBA_SERCOM1);
        break;

    case SERCOM_CH2 :
        MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_SERCOM2);
        break;

    case SERCOM_CH3 :
        MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_SERCOM3);
        break;

    case SERCOM_CH4 :
        MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_SERCOM4);
        break;

    case SERCOM_CH5 :
        MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_SERCOM5);
        break;

    case SERCOM_CH6 :
        MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_SERCOM6);
        break;

    case SERCOM_CH7 :
        MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_SERCOM7);
        break;
    default :
        break;
    }

    /* Enable GCLK Clock for SERCOM */
    GCLK_EnableSERCOMClock((EN_GCLK_SERCOM_CH_SEL_t )p_stgSPIMasterConfigParams->en_mChannel);

    /*Disable the SPI */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA &= ~(SERCOM_SPI_CTRLA_ENABLE_MASK);

    /* Perform Software Reset */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA  = SERCOM_SPI_CTRLA_SWRST_MASK;

    /* Waiting for SWRST SYNC */
    while(p_stgSPIBaseRegs[u32_lSERChannel]->SYNCBUSY & SERCOM_SPI_SYNCBUSY_SWRST_MASK);
    
    /* Configuring SPI in Slave Mode */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA |= SERCOM_SPI_CTRLA_SLAVE_MODE;
   
    /* Configuring Clock Polarity & Clock Phase */
    /* Configuring Clock Phase as Mode 0,1,2,3 */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA |= \
            (p_stgSPIMasterConfigParams->en_mClockPhaseSel << SERCOM_SPI_CTRLA_CPHA_POS);
    
    /* Slave Select Enable */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLB |= (1 << 9);
    
    /* Status Buffer Overflow */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA |= (SERCOM_SPI_CTRLA_IBON); 

    /* Selecting Frame Form Value as SPI frame  */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA &= ~(1 << SERCOM_SPI_CTRLA_FORM_POS);
    
    /* Select the data order (MSB or LSB first) */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA |= (p_stgSPIMasterConfigParams->en_mDataOrder << 30);

    /* Selecting Pad for DIPO (MISO) */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA |= (p_stgSPIMasterConfigParams->en_mMISOPadSel << 20);

    /* Selecting Pad for DOPO (MOSI) and SCLK */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA |= (p_stgSPIMasterConfigParams->en_mMOSIPadSel << 16);

    /* Select the Character Size (8 bits ) */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLB &= ~0x07;
    
//    /* Slave Preload Enable */
//    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLB |= (1 << 6);
    
    /* Rx Interrupt Enable */
    p_stgSPIBaseRegs[u32_lSERChannel]->INTENSET |= (SERCOM_SPI_INTENSET_RXC);
    
    switch(u32_lSERChannel)
    {
    case SERCOM_CH0 :
        NVIC_EnableInterrupt(SERCOM0_2_IRQ);
        break;

    case SERCOM_CH1 :
        NVIC_EnableInterrupt(SERCOM1_2_IRQ);
        break;

    case SERCOM_CH2 :
        NVIC_EnableInterrupt(SERCOM2_2_IRQ);
        break;

    case SERCOM_CH3 :
        NVIC_EnableInterrupt(SERCOM3_2_IRQ);
        break;

    case SERCOM_CH4 :
        NVIC_EnableInterrupt(SERCOM4_2_IRQ);
        break;

    case SERCOM_CH5 :
        NVIC_EnableInterrupt(SERCOM5_2_IRQ);
        break;

    case SERCOM_CH6 :
        NVIC_EnableInterrupt(SERCOM6_2_IRQ);
        break;

    case SERCOM_CH7 :
        NVIC_EnableInterrupt(SERCOM7_2_IRQ);
        break;
    default :
        break;
    }

    /* Enable Receiver */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLB |= (1 << 17);

    /* Enable SPI */
    p_stgSPIBaseRegs[u32_lSERChannel]->CTRLA |= (1 << 1);    

    /* Waiting for Enable to SYNC */
    while(p_stgSPIBaseRegs[u32_lSERChannel]->SYNCBUSY & SERCOM_SPI_SYNCBUSY_ENABLE_MASK);
    
    /* */
    pst_gSPISlaveConfigParam = p_stgSPIMasterConfigParams;
}

/**************************************************************************************************/
/* Function Name   : INT8U SPI_ReadData(EN_SPI_SERCOM_CH_SEL_t en_fSERCOMChannel)                 */
/*                                                                                                */
/* Description     : This function used to read the data                                          */
/*                                                                                                */
/* In Params       : en_fSERCOMChannel                                                            */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : INT8U                                                                        */
/**************************************************************************************************/

INT8U SPI_ReadData(EN_SPI_SERCOM_CH_SEL_t en_fSERCOMChannel)
{
    INT8U u8_lData = 0; 

    /* Waiting for Recieve Complete flag (RXC) */
    while(!(p_stgSPIBaseRegs[en_fSERCOMChannel]->INTFLAG & SERCOM_SPI_INTFLAG_RXC_MASK));
	
    u8_lData = p_stgSPIBaseRegs[en_fSERCOMChannel]->DATA;

    return u8_lData;
}	

/**************************************************************************************************/
/* Function Name   : void SPI_WriteData(EN_SPI_SERCOM_CH_SEL_t en_fSERCOMChannel,INT8U u8_fData)  */
/*                                                                                                */
/* Description     : This function is used to write the data into EEPROM using SPI                */
/*                                                                                                */
/* In Params       : en_fSERCOMChannel, u8_fData                                                  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void SPI_WriteData(EN_SPI_SERCOM_CH_SEL_t en_fSERCOMChannel,INT8U u8_fData)
{	
    /* Waiting for Data register empty flag */
    while(!(p_stgSPIBaseRegs[en_fSERCOMChannel]->INTFLAG & SERCOM_SPI_INTFLAG_DRE_MASK));

    /* writing data into the DATA register */
    p_stgSPIBaseRegs[en_fSERCOMChannel]->DATA = u8_fData;

    /* wait untill data is sent (TXC) */
    //while(!(p_stgSPIBaseRegs[en_fSERCOMChannel]->INTFLAG & SERCOM_SPI_INTFLAG_TXC_MASK));
}

/**************************************************************************************************/
/* Function Name   : INT8U SPI_Calculate_Baudrate(INT32U u32_lBaudrate)                           */
/*                                                                                                */
/* Description     : This function used to calculate the Baudrate                                 */
/*                                                                                                */
/* In Params       : u32_lBaudrate                                                                */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : INT8U                                                                        */
/**************************************************************************************************/

INT8U SPI_CalculateBaudrate(INT32U u32_lBaudrate)
{
    INT32U u32_lRefFreq = 120000000;
    INT32F f32_lTemp = 0;
    INT8U u8_lBaudVal = 0;

    /* BAUD = ((Fref/2(Fbaud)) - 1)*/

    f32_lTemp = ((INT32F)u32_lRefFreq/(2 * u32_lBaudrate));

    u8_lBaudVal = (INT8U)(f32_lTemp - 1);

    return u8_lBaudVal;
}		

/**************************************************************************************************/
/* Function Name : INT8U TransferByte(EN_SERCOM_CH_SEL_t en_fSercomChn,INT8U u8_fData)            */
/*											                                                      										*/
/* Description	 : This function used to transfer a Byte                                          */
/* 													                                              												*/
/* IN Parameter	 : en_fSercomChn, u8_fData                                                        */
/*					                                                                              				*/
/* OUT Parameter : void		       				                                                 					*/
/*					                                                          			  */
/* Return Value	 : void		       			    			                  */
/*                                                                                                */
/* Remarks	     : None                                                                       */
/**************************************************************************************************/

INT8U TransferByte(EN_SPI_SERCOM_CH_SEL_t en_fSercomChn,INT8U u8_fData)
{
    INT8U u8_lData = 0;
//    INT32U u32_lDelay = 0;
	
    /*Write Enable Instruction*/
    SPI_WriteData(en_fSercomChn, u8_fData);
    
//    for(u32_lDelay = 0; u32_lDelay < 123456; u32_lDelay++);

    /* Wait till dummy value is received */
 
//    /*Dummy Read*/
//    u8_lData = SPI_ReadData(en_fSercomChn);
	
    return u8_lData;
}

/**************************************************************************************************/
/* Function Name : INT8U TransferByte(EN_SERCOM_CH_SEL_t en_fSercomChn,INT8U u8_fData)            */
/*											                                                      */
/* Description	 : This function used to transfer a Byte                                          */
/* 													                                              */
/* IN Parameter	 : en_fSercomChn, u8_fData                                                        */
/*					                                                                              */
/* OUT Parameter : void		       				                                                  */
/*					                                                          			          */
/* Return Value	 : void		       			    			                                      */
/*                                                                                                */
/* Remarks	     : None                                                                           */
/**************************************************************************************************/

INT8U SPI_GetStatusFlag(EN_SPI_SERCOM_CH_SEL_t en_fSercomChn, INT32U u32_fFlag)
{
    INT8U u8_lResult = 0;
    
    if(p_stgSPIBaseRegs[en_fSercomChn]->INTFLAG & u32_fFlag)
    {
        u8_lResult = 1;
    }
    else
    {
        u8_lResult = 0;
    }
    
    return u8_lResult;
}

/**************************************************************************************************/
/* Function Name   : SPI_SlaveRead                                                                */
/*                                                                                                */
/* Description     : This function used to Read Data from SPI                                     */
/*                                                                                                */
/* In Params       : EN_SPI_SERCOM_CH_SEL_t en_fSercomChn                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : INT8U                                                                        */
/**************************************************************************************************/

void SPI_SlaveRead(EN_SPI_SERCOM_CH_SEL_t en_fSercomChn, INT8U *pu8_fSPIData)
{   
  static INT32U u32_lSPISlaveindex = 0x00;
  
  if(p_stgSPIBaseRegs[en_fSercomChn]->INTFLAG & SERCOM_SPI_INTFLAG_SSL_MASK)
  {         
    p_stgSPIBaseRegs[en_fSercomChn]->INTFLAG |= SERCOM_SPI_INTFLAG_SSL_MASK;
    
    pu8_fSPIData[u32_lSPISlaveindex] = SPI_ReadData(en_fSercomChn);
    
    SPI_WriteData(en_fSercomChn, 'S');
    
//    UART_TransmitChar(SERCOM_CH_0, pu8_fSPIData[u32_lSPISlaveindex]);
    
    u32_lSPISlaveindex++;
    
    if(u32_lSPISlaveindex >= 512)
    {
        u32_lSPISlaveindex = 0;
    }
  }
  else
  {
    /* No action */
  }
}

/**************************************************************************************************/
/* End of SPI.c                                                                                   */
/**************************************************************************************************/
