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
/*  File Name   : W25QF128JV.c                                                                    */
/*  Author      : Yashwanth                                                                       */
/*  Version 	: 1.0                                                                             */
/*  Date        : 09-04-2018                                                                      */
/*                                                                                                */
/* @Description : W25Q128JV Serial Flash Driver                                                   */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "W25QF128JV.h"
#include "W25QF128JV_Priv.h"

#include "GPIO.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

#define W25QF128JV_SFLASH_PCS_PIN_LOW	 (GPIO_ResetPin(GPIO_PORT_A,GPIO_PIN_18))
#define W25QF128JV_SFLASH_PCS_PIN_HIGH	 (GPIO_SetPin(GPIO_PORT_A,GPIO_PIN_18))


/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Initialization of MISO  Pin  */
ST_GPIO_PARAMS_t st_gSPIMISOPortDPin20 = 
{
    .en_mPortSel		=	GPIO_PORT_A,
    .en_mPinSel			=	GPIO_PIN_19,
    .en_mPinDir			=	GPIO_DIR_INPUT,
    .en_mPinType		=	GPIO_IN_PULL_UP,
    .en_mPinPeriph		=	GPIO_PERIPHERAL_C,
    .en_mDriverStrenght		=	GPIO_DRIV_STRENGTH_NORMAL
};

/* Initialization of ChipSelect pin */
ST_GPIO_PARAMS_t st_gSPIChipSelWinboundCS = 
{
    .en_mPortSel		=	GPIO_PORT_A,
    .en_mPinSel			=	GPIO_PIN_18,
    .en_mPinDir			=	GPIO_DIR_OUTPUT,
    .en_mPinType		=	GPIO_PULL_LVL_DIS,
    .en_mPinPeriph		=	GPIO_GENERAL_PURPOSE,
    .en_mDriverStrenght		=	GPIO_DRIV_STRENGTH_NORMAL
};

/* Initialization of the MOSI Pin */
ST_GPIO_PARAMS_t st_gSPIMOSIPortDPin21 = 
{
    .en_mPortSel		=	GPIO_PORT_A,
    .en_mPinSel			=	GPIO_PIN_16,
    .en_mPinDir			=	GPIO_DIR_OUTPUT,
    .en_mPinType		=	GPIO_PULL_LVL_DIS,
    .en_mPinPeriph		=	GPIO_PERIPHERAL_C,
    .en_mDriverStrenght		=	GPIO_DRIV_STRENGTH_NORMAL
};

/* Initialization of SCLK Clock Out Pin */
ST_GPIO_PARAMS_t st_gSPIClockPortDPin22 = 
{
    .en_mPortSel		=	GPIO_PORT_A,
    .en_mPinSel			=	GPIO_PIN_17,
    .en_mPinDir			=	GPIO_DIR_OUTPUT,
    .en_mPinType		=	GPIO_PULL_LVL_DIS,
    .en_mPinPeriph		=	GPIO_PERIPHERAL_C,
    .en_mDriverStrenght		=	GPIO_DRIV_STRENGTH_NORMAL
};

/* Configuration for SPI MAster Init */
ST_SPI_MASTER_CONFIG_PARAMS_t st_gW25Q128InitParams = 
{
    .en_mChannel = SERCOM_CH1,
    .u32_mBaudrate = 30000000,
    .en_mDataOrder = SPI_DORD_MSB_FIRST,
    .en_mMISOPadSel = SPI_MISO_PAD3,
    .en_mMOSIPadSel = SPI_MOSIPAD0_SCKPAD1_SSPAD2,
    .en_mSSControlSel = SPI_SS_CONTROLLED_BY_SOFTWARE,
    .en_mClockPhaseSel = SPI_CLOCK_PHASE_CPOL0_CPHA1
};

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

EN_W25Q128JV_STATUS_t W25Q128JV_Init(void)
{
    EN_W25Q128JV_STATUS_t en_lResult = W25Q128JV_SUCCESS;
    
    /* Configure SPI Pins */
    GPIO_Init(&st_gSPIChipSelWinboundCS);
    GPIO_Init(&st_gSPIClockPortDPin22);
    GPIO_Init(&st_gSPIMOSIPortDPin21);
    GPIO_Init(&st_gSPIMISOPortDPin20);
    
    /* SPI Init */
    SPI_MasterInit(&st_gW25Q128InitParams);
    
    W25QF128JV_SFLASH_PCS_PIN_LOW;
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                            */
/**************************************************************************************************/

EN_W25Q128JV_STATUS_t w25q128jvDrvWriteData(INT32U u32_fAddr, INT8U *p_fSrcBuff, INT16U u16_fLen)
{
    EN_W25Q128JV_STATUS_t en_lResult = W25Q128JV_SUCCESS;
	
    INT16U u16_lTemp = 0;
    
    INT16U u16_lErroCounter = 0x00;
    
    /* Update address into temporary variable */
    INT32U u32_lTempAddr = u32_fAddr;
    
    /* Update Write Data Len into temporary variable */
    INT16U u16_lTempDataLen = u16_fLen;
    
    if((PNULL != p_fSrcBuff) && (0 != u16_fLen))
    {
        /* Wait if any write operation in progress */
        while(W25Q128JV_WRITE_IN_PROGRESS == w25q128jvDrvWriteInProgress())
        {
            /* Increment the Error Coutner */
            u16_lErroCounter =  u16_lErroCounter + 1;
            
            if(u16_lErroCounter > 32)
            {
              /* Update the Error Result */
              en_lResult = W25Q128JV_FAILURE;
              
              /* Returnt the Result */
              return en_lResult;
            }
        }
        
        /* Make Error Counter to zero */
        u16_lErroCounter = 0x00;
        
        /* Find the remaining bytes in current page */
        u16_lTemp = 256 - (u32_fAddr % 256);

        if(u16_lTempDataLen > u16_lTemp)
        {
            do
            {                  
                /*Send write enable command */
                w25q128jvDrvWriteEnable();
                
                /* Increment the Error Coutner */
                u16_lErroCounter =  u16_lErroCounter + 1;
                
                if(u16_lErroCounter > 32)
                {
                  /* Update the Error Result */
                  en_lResult = W25Q128JV_FAILURE;
                  
                  /* Returnt the Result */
                  return en_lResult;
                }
            }
            
            while((w25q128jvDrvReadStatusReg() & 0x02) == 0);
            
            u16_lErroCounter = 0x00;

            /* Wait if any write operation in progress */
            while(W25Q128JV_WRITE_IN_PROGRESS == w25q128jvDrvWriteInProgress());
            
            /* Write the remaining bytes into current page */
            w25q128jvDrvProgramPage(u32_lTempAddr, p_fSrcBuff, u16_lTemp);
            
            /* Increment Write Address */
            u32_lTempAddr = u32_fAddr + u16_lTemp;
            
            /* Increment source buffer poiter */
            p_fSrcBuff = p_fSrcBuff + u16_lTemp;
            
            /* Decrement length of data to be written */
            u16_lTempDataLen = u16_lTempDataLen - u16_lTemp;
        }
        else
        {
			
            do
            {
                /*Send write enable command */
                w25q128jvDrvWriteEnable();
            }
			
            while((w25q128jvDrvReadStatusReg() & 0x02) == 0);

            /* Wait if any write operation in progress */
            while(W25Q128JV_WRITE_IN_PROGRESS == w25q128jvDrvWriteInProgress());
            
            /* Write the remaining bytes into current page */
            w25q128jvDrvProgramPage(u32_lTempAddr, p_fSrcBuff, u16_lTempDataLen);
				
            /* Set u16_lTempDataLen length to be zero */
            u16_lTempDataLen = 0;
			
        }
			
        while(0 != u16_lTempDataLen)
        {
            /* Wait if any write operation in progress */
            while(W25Q128JV_WRITE_IN_PROGRESS == w25q128jvDrvWriteInProgress())
            {
                    /*wait*/
            }
				
            do
            {
                /*Send write enable command */
                w25q128jvDrvWriteEnable();
            }
			
            while((w25q128jvDrvReadStatusReg() & 0x02) == 0);

            /* Wait if any write operation in progress */
            while(W25Q128JV_WRITE_IN_PROGRESS == w25q128jvDrvWriteInProgress())
            {
                    /*wait*/
            }
            
            /* Check for Data to be written is more than 32 bytes or not */
            if(u16_lTempDataLen > 256)
            {
                /* Write data into eeprom */
                w25q128jvDrvProgramPage(u32_lTempAddr, p_fSrcBuff, 256);
                
                /* Increment Address by page size */
                u32_lTempAddr = u32_lTempAddr + 256;
                
                /* Increment source buffer by page size */
                p_fSrcBuff = p_fSrcBuff + 256;
                
                /* Decrement Data length by page size */
                u16_lTempDataLen = u16_lTempDataLen - 256;      
            }
            else
            {
                /* Write data into eeprom */
                w25q128jvDrvProgramPage((INT32U)u32_lTempAddr, p_fSrcBuff, u16_lTempDataLen);
                break;
            }
        }
    }
    else
    {
        /* No Action */
    }
	return en_lResult;
}

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                            */
/**************************************************************************************************/

EN_W25Q128JV_STATUS_t w25q128jvDrvReadData(INT32U u32_fAddr, INT8U *p_fDstBuff, INT32U u16_fLen)
{
    EN_W25Q128JV_STATUS_t en_lResult = W25Q128JV_SUCCESS;
    INT32U u16_lIndex = 0;
       
    /* Wait if any write operation in progress */
    while(W25Q128JV_WRITE_IN_PROGRESS == w25q128jvDrvWriteInProgress());
    
    /* Send Read command */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, W25Q128JV_CM_READ);
    
    /* Send Higher byte of address */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, \
                                                                (INT8U)((u32_fAddr >> 16) & 0xFF));
    
    /* Send Lower byte of address */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, \
                                                                (INT8U)((u32_fAddr >> 8) & 0xFF));
    
    /* Send Lower byte of address */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, \
                                                                (INT8U)((u32_fAddr >> 0) & 0xFF));
        
    for(u16_lIndex = 0; u16_lIndex < (u16_fLen - 1); u16_lIndex++)
    {
        /* Receive Data */
        p_fDstBuff[u16_lIndex] = w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel,\
                                                                            W25Q128JV_DUMMY_DATA);
    }
     
    /* Recive Last Byte of Data  & Make CS high */
    p_fDstBuff[u16_lIndex] = w25q128jvDrvTransferLastByte(st_gW25Q128InitParams.en_mChannel,\
                                                                            W25Q128JV_DUMMY_DATA);

    return en_lResult;
}

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                            */
/**************************************************************************************************/

EN_W25Q128JV_STATUS_t w25q128jvDrvProgramPage(INT32U u32_fAddr, INT8U *p_fSrcBuff, INT16U u16_fLen)
{
    EN_W25Q128JV_STATUS_t en_lResult = W25Q128JV_SUCCESS;
	
    INT16U u16_lIndex = 0;
    
    /* Send program page command */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, W25Q128JV_CM_PP);
    
    /* Send Higher byte of address */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, \
                                                            (INT8U)((u32_fAddr >> 16) & 0xFF));
    
    /* Send Lower byte of address */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, \
                                                            (INT8U)((u32_fAddr >> 8) & 0xFF));
    
    /* Send Lower byte of address */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, \
                                                            (INT8U)((u32_fAddr >> 0) & 0xFF));
    
    for(u16_lIndex = 0; u16_lIndex < (u16_fLen -1); u16_lIndex++)
    {
        /* Send Data */
        w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, p_fSrcBuff[u16_lIndex]);
    }
	
    /*Transmit Last Byte & make CS High*/
    w25q128jvDrvTransferLastByte(st_gW25Q128InitParams.en_mChannel, p_fSrcBuff[u16_lIndex]);
	
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                            */
/**************************************************************************************************/

INT8U w25q128jvDrvReadStatusReg(void)
{
    INT8U u8_lResult = 0;
    
    /* Send read status register command */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, W25Q128JV_CM_RDSR1);
    
    u8_lResult = w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel,W25Q128JV_DUMMY_DATA);
    /* Read Status register */
    u8_lResult = w25q128jvDrvTransferLastByte(st_gW25Q128InitParams.en_mChannel,\
                                                                            W25Q128JV_DUMMY_DATA);

    return u8_lResult;
}

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                            */
/**************************************************************************************************/

void w25q128jvDrvWriteEnable(void)
{
    /* Send write enable command */
    w25q128jvDrvTransferLastByte(st_gW25Q128InitParams.en_mChannel, W25Q128JV_CM_WREN);
}

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                            */
/**************************************************************************************************/

void w25qf128jvDrvWriteDisable(void)
{
    /* Send Write Disable Instruction */
    w25q128jvDrvTransferLastByte(st_gW25Q128InitParams.en_mChannel, W25Q128JV_CM_WRDI);
}

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                            */
/**************************************************************************************************/

EN_W25Q128JV_WRITE_PROGRESS_t w25q128jvDrvWriteInProgress(void)
{
    EN_W25Q128JV_WRITE_PROGRESS_t en_lResult = W25Q128JV_NO_WRITE_IN_PROGRESS;
    
    INT8U u8_lStatusRegister = 0;
    
    /* Send read status register command */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, W25Q128JV_CM_RDSR1);
    
    /* Read Status register */
    u8_lStatusRegister = w25q128jvDrvTransferLastByte(st_gW25Q128InitParams.en_mChannel,\
                                                                        W25Q128JV_DUMMY_DATA);
    
    /* Check for Write In Progress Bit */
    if((u8_lStatusRegister & 0x01) != 0)
    {
        /* Update result */
        en_lResult = W25Q128JV_WRITE_IN_PROGRESS;
    }
    else
    {
        /* No Action */
    }
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                            */
/**************************************************************************************************/

INT8U w25qf128jvDrvWriteRegister(void)
{
    INT8U u8_lResult = 0;
    
    w25q128jvDrvWriteDisable();
    
    while((0x02 & w25q128jvDrvReadStatusReg()));
    
    w25q128jvDrvWriteEnable();
    
    while(!(0x02 & w25q128jvDrvReadStatusReg()));
    
    /* Send read status register command */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, W25Q128JV_CM_WRR);
    
    w25q128jvDrvTransferLastByte(st_gW25Q128InitParams.en_mChannel, 0x80);
    
    u8_lResult = w25q128jvDrvReadStatusReg();
    
    return u8_lResult;
}

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                        */
/**************************************************************************************************/

EN_W25Q128JV_STATUS_t w25q128jvDrvBulkErase(void)
{
    EN_W25Q128JV_STATUS_t en_lResult = W25Q128JV_SUCCESS;    
    
    w25q128jvDrvWriteEnable();    
    
    /*  */
    while(!(0x02 & w25q128jvDrvReadStatusReg()));
    
    /* Send Bulk Erase Command */
    w25q128jvDrvTransferLastByte(st_gW25Q128InitParams.en_mChannel, W25Q128JV_CM_BE);
    
    /* Wait till Chip Erase */
    while((0x01 & w25q128jvDrvReadStatusReg()));
    
    return en_lResult;
    
}

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                            */
/**************************************************************************************************/

EN_W25Q128JV_STATUS_t w25q128jvDrv4KBSectorErase(INT32U u32_fAddr)
{
    EN_W25Q128JV_STATUS_t en_lResult = W25Q128JV_SUCCESS;    
    
    w25q128jvDrvWriteEnable();    
    
    /* Check Status Register for Write Enable */
    while(!(0x02 & w25q128jvDrvReadStatusReg()));
    
    /* Send Bulk Erase Command */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, W25Q128JV_CM_4KB_SE);
    
    /* Send Higher byte of address */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, (INT8U)((u32_fAddr >> 16) & 0xFF));
    
    /* Send Lower byte of address */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, (INT8U)((u32_fAddr >> 8) & 0xFF));
    
    /* Send Lower byte of address */
    w25q128jvDrvTransferLastByte(st_gW25Q128InitParams.en_mChannel, (INT8U)((u32_fAddr >> 0) & 0xFF));
    
    /* Wait till Chip Erase */
    while((0x01 & w25q128jvDrvReadStatusReg()));
    
    return en_lResult;
    
}

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                            */
/**************************************************************************************************/

EN_W25Q128JV_STATUS_t w25q128jvDrv32KBSectorErase(INT32U u32_fAddr)
{
    EN_W25Q128JV_STATUS_t en_lResult = W25Q128JV_SUCCESS;   
    
    /* Enable the write */
    w25q128jvDrvWriteEnable();    
    
    /* Check Status Register for Write Enable */
    while(!(0x02 & w25q128jvDrvReadStatusReg()));
    
    /* Send Bulk Erase Command */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, W25Q128JV_CM_32KB_SE);
    
    /* Send Higher byte of address */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, (INT8U)((u32_fAddr >> 16) & 0xFF));
    
    /* Send Lower byte of address */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, (INT8U)((u32_fAddr >> 8) & 0xFF));
    
    /* Send Lower byte of address */
    w25q128jvDrvTransferLastByte(st_gW25Q128InitParams.en_mChannel, (INT8U)((u32_fAddr >> 0) & 0xFF));
    
    /* Wait till Chip Erase */
    while((0x01 & w25q128jvDrvReadStatusReg()));
    
    return en_lResult;
    
}

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                            */
/**************************************************************************************************/

EN_W25Q128JV_STATUS_t w25q128jvDrv64KBSectorErase(INT32U u32_fAddr)
{
    EN_W25Q128JV_STATUS_t en_lResult = W25Q128JV_SUCCESS;   
    
    /* Enable the write */
    w25q128jvDrvWriteEnable();    
    
    /* Check Status Register for Write Enable */
    while(!(0x02 & w25q128jvDrvReadStatusReg()));
    
    /* Send Bulk Erase Command */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, W25Q128JV_CM_64KB_SE);
    
    /* Send Higher byte of address */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, (INT8U)((u32_fAddr >> 16) & 0xFF));
    
    /* Send Lower byte of address */
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, (INT8U)((u32_fAddr >> 8) & 0xFF));
    
    /* Send Lower byte of address */
    w25q128jvDrvTransferLastByte(st_gW25Q128InitParams.en_mChannel, (INT8U)((u32_fAddr >> 0) & 0xFF));
    
    /* Wait till Chip Erase */
    while((0x01 & w25q128jvDrvReadStatusReg()));
    
    return en_lResult;
    
}

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                        */
/**************************************************************************************************/
     
EN_W25Q128JV_STATUS_t w25q128jvDrvReadManufactureId(void)
{
    INT32U u32_lManfactId = 0;
    
    EN_W25Q128JV_STATUS_t en_lResult = W25Q128JV_SUCCESS;

    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, W25Q128JV_CM_REMID);
    
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, 0x00);
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, 0x00);
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, 0x00);
    
    w25q128jvDrvTransferByte(st_gW25Q128InitParams.en_mChannel, 0xFF);
    u32_lManfactId = w25q128jvDrvTransferLastByte(st_gW25Q128InitParams.en_mChannel, 0xFF);

    if(W25Q128FJV_MANF_ID == u32_lManfactId)
    {
        en_lResult = W25Q128JV_SUCCESS;
    }
    else
    {
        en_lResult = W25Q128JV_FAILURE;
    }
    
    return en_lResult;  
 }

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                            */
/**************************************************************************************************/

INT8U w25q128jvDrvTransferByte(EN_SPI_SERCOM_CH_SEL_t en_fChSel, INT8U u8_fData)
{   
    INT8U u8_lResult = 0;
    
    W25QF128JV_SFLASH_PCS_PIN_LOW;
    
     /* Write to Serial Memory */
    SPI_WriteData(en_fChSel, u8_fData);
    
    /* Receive data */
    u8_lResult = SPI_ReadData(en_fChSel);
    
    return u8_lResult;
    
}

/**************************************************************************************************/
/* Function Name:                                                                                 */
/*                                                                                                */
/* Description	:                                                                                 */
/*                                                                                                */
/* Parameter	:                                                                                 */
/*                                                                                                */
/* Return Value	: void                                                                            */
/*                                                                                                */
/* Remarks	    : None                                                                            */
/**************************************************************************************************/

INT8U w25q128jvDrvTransferLastByte(EN_SPI_SERCOM_CH_SEL_t en_fChSel, INT8U u8_fData)
{
    INT8U u8_lResult = 0;
    
    W25QF128JV_SFLASH_PCS_PIN_LOW;
    
    /* Write to Serial Memory */
    SPI_WriteData(en_fChSel, u8_fData);
    
    /* Receive data */
    u8_lResult = SPI_ReadData(en_fChSel);
    
    W25QF128JV_SFLASH_PCS_PIN_HIGH;
    
    return u8_lResult;
    
}

/**************************************************************************************************/
/* End of  W25QF128FW.c                                                                           */
/**************************************************************************************************/
