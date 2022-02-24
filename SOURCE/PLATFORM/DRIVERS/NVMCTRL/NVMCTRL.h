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
/*  File Name   : NVMCTRL.h                                                                       */
/*  Author      : Ravi Ranjan Kumar                                                               */
/*  Version 	: 1.0                                                                             */
/*  Date        : 30-08-2018                                                                      */
/*                                                                                                */
/* @Description : NVM Driver                                                                      */
/**************************************************************************************************/

#ifndef _NVMCTRL_H_
#define _NVMCTRL_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

#define NVMCTRL_BLOCK_SIZE          ( 8192 )    /* Bytes, Smallest for Erase Operation */
#define NVMCTRL_CLK_AHB_ID          ( 6 )       /* Index of AHB Clock */
#define NVMCTRL_CLK_AHB_ID_CACHE    ( 23 )      /* Index of AHB Clock for NVMCTRL CACHE lines */
#define NVMCTRL_CLK_AHB_ID_SMEEPROM ( 22 )      /* Index of AHB Clock for SMEE submodule */
#define NVMCTRL_PAGE_SIZE           ( 512 )     /* Size Of Page (Bytes) */

#define NVMCTRL_CTRLB_CMDEX_KEY   ( 0xA5 ) 

/* NVM Status */
typedef enum
{
	STATUS_OK = 0x00,
	NVM_ERROR,
	STATUS_BUSY,
	STATUS_ABORTED,
	ERR_DENIED,
	ERR_UNSUPPORTED_OP,
	ERR_INVALID_ARG,
	ERR_NO_MEMORY,
	ERR_BAD_ADDRESS
}EN_NVM_STATUS_t;

/* Enum for Internal EEPROM Space in KB */
typedef enum
{
	EEPROM_0KB_0BLOCK = 0,
	EEPROM_16KB_2BLOCK,
	EEPROM_32KB_4BLOCK,
	EEPROM_48KB_6BLOCK,
	EEPROM_64KB_8BLOCK,
	EEPROM_80KB_10BLOCK,
	EEPROM_96KB_12BLOCK,
	EEPROM_112KB_14BLOCK,
	EEPROM_128KB_16BLOCK,
	EEPROM_144KB_18BLOCK,
	EEPROM_160KB_20BLOCK,
}EN_EEPROM_SIZE_t;

/* Enum for Internal EEPROM Page Sige in KB */
typedef enum
{
	EEPROM_4KB_PAGE = 0,
	EEPROM_8KB_PAGE,
	EEPROM_16KB_PAGE,
	EEPROM_32KB_PAGE,
	EEPROM_64KB_PAGE,
	EEPROM_128KB_PAGE,
	EEPROM_256KB_PAGE,	
	EEPROM_512KB_PAGE,
}EN_EEPROM_PAGE_t;

/* Enum for Bootloader Space in KB */
typedef enum
{
	BTLDR_120KB_15ROW_PRTCT = 0,
	BTLDR_112KB_14ROW_PRTCT,
	BTLDR_104KB_13ROW_PRTCT,
	BTLDR_96KB_12ROW_PRTCT,
	BTLDR_88KB_11ROW_PRTCT,
	BTLDR_80KB_10ROW_PRTCT,
	BTLDR_72KB_9ROW_PRTCT,
	BTLDR_64KB_8ROW_PRTCT,
	BTLDR_56KB_7ROW_PRTCT,
	BTLDR_48KB_6ROW_PRTCT,
	BTLDR_40KB_5ROW_PRTCT,
	BTLDR_32KB_4ROW_PRTCT,
	BTLDR_24KB_3ROW_PRTCT,
	BTLDR_16KB_2ROW_PRTCT,
	BTLDR_8KB_1ROW_PRTCT,
	BTLDR_0KB_0ROW_PRTCT,
}EN_BTLDR_SIZE_t;

/* NVM Command */
typedef enum
{
    NVMCTRL_CTRLB_CMD_EP       = (0x0),   /* Erase Page - Only supported in the USER and AUX pages. */
    NVMCTRL_CTRLB_CMD_EB       = (0x1),   /* Erase Block - Erases the block addressed by the ADDR register, not supported in the user page */
    NVMCTRL_CTRLB_CMD_WP       = (0x3),   /* Write Page - Writes the contents of the page buffer to the page addressed by the ADDR register, not supported in the user page */
    NVMCTRL_CTRLB_CMD_WQW      = (0x4),   /* Write Quad Word - Writes a 128-bit word at the location addressed by the ADDR register. */
    NVMCTRL_CTRLB_CMD_SWRST    = (0x10),   /* Software Reset - Power-Cycle the NVM memory and replay the device automatic calibration procedure and resets the module configuration registers */
    NVMCTRL_CTRLB_CMD_LR       = (0x11),   /* Lock Region - Locks the region containing the address location in the ADDR register. */
    NVMCTRL_CTRLB_CMD_UR       = (0x12),   /* Unlock Region - Unlocks the region containing the address location in the ADDR register. */
    NVMCTRL_CTRLB_CMD_SPRM     = (0x13),   /* Sets the power reduction mode. */
    NVMCTRL_CTRLB_CMD_CPRM     = (0x14),   /* Clears the power reduction mode. */
    NVMCTRL_CTRLB_CMD_PBC      = (0x15),   /* Page Buffer Clear - Clears the page buffer. */
    NVMCTRL_CTRLB_CMD_SSB      = (0x16),   /* Set Security Bit */
    NVMCTRL_CTRLB_CMD_BKSWRST  = (0x17),   /* Bank swap and system reset, if SMEE is used also reallocate SMEE data into the opposite BANK */
    NVMCTRL_CTRLB_CMD_CELCK    = (0x18),   /* Chip Erase Lock - DSU.CE command is not available */
    NVMCTRL_CTRLB_CMD_CEULCK   = (0x19),   /* Chip Erase Unlock - DSU.CE command is available */
    NVMCTRL_CTRLB_CMD_SBPDIS   = (0x1A),   /* Sets STATUS.BPDIS, Boot loader protection is discarded until CBPDIS is issued or next start-up sequence */
    NVMCTRL_CTRLB_CMD_CBPDIS   = (0x1B),   /* Clears STATUS.BPDIS, Boot loader protection is not discarded */
    NVMCTRL_CTRLB_CMD_ASEES0   = (0x30),   /* Activate SmartEEPROM Sector 0, deactivate Sector 1 */
    NVMCTRL_CTRLB_CMD_ASEES1   = (0x31),   /* Activate SmartEEPROM Sector 1, deactivate Sector 0 */
    NVMCTRL_CTRLB_CMD_SEERALOC = (0x32),   /* Starts SmartEEPROM sector reallocation algorithm */
    NVMCTRL_CTRLB_CMD_SEEFLUSH = (0x33),   /* Flush SMEE data when in buffered mode */
    NVMCTRL_CTRLB_CMD_LSEE     = (0x34),   /* Lock access to SmartEEPROM data from any mean */
    NVMCTRL_CTRLB_CMD_USEE     = (0x35),   /* Unlock access to SmartEEPROM data */
    NVMCTRL_CTRLB_CMD_LSEER    = (0x36),   /* Lock access to the SmartEEPROM Register Address Space (above 64KB) */
    NVMCTRL_CTRLB_CMD_USEER    = (0x37)   /* Unlock access to the SmartEEPROM Register Address Space (above 64KB) */
}EN_NVM_CMD_t;

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function for Flash */
extern INT32U FLASH_Init(void);

/* Function for Flash */
extern INT32U FLASH_GetTotalPages(void);

/* Function for Flash */
extern INT8U FLASH_GetWaitState(void);

/* Function for Flash */
extern void FLASH_SetWaitState(INT8U u8_fWaitState);

/* Function for Flash */
extern void FLASH_SendCommand(const INT32U u32_fAddress, EN_NVM_CMD_t en_fNvmCmd);

/* Function for Flash */
extern void FLASH_Read(const INT32U u32_fAddress, INT8U *p_u8fBuffer, INT32U u32_fLength);

/* Function for Flash */
extern void FLASH_Write(const INT32U u32_fDestAddr, INT8U *p_u8lBuffer, INT32U u32_fLength);

/* Function for Flash */
extern void FLASH_Append(const INT32U u32_fDestAddr, INT8U *p_u8lBuffer, INT32U u32_fLength);

/* Function for Flash */
extern void FLASH_Erase(INT32U u32_fDestAddr, INT32U u32_fPageNums);

/* Function for Flash */
extern void FLASH_Erase(INT32U u32_fDestAddr, INT32U u32_fPageNums);

/* Function for Flash */
extern INT32U FLASH_Lock(const INT32U u32_fDestAddr, INT32U u32_fPageNums);

/* Function for Flash */
extern INT32U FLASH_Unlock(const INT32U u32_fDestAddr, INT32U u32_fPageNums);

/* Function for Flash */
extern INT8U IsFLASH_Locked(const INT32U u32_fDestAddr);

/* Function for Flash */
extern void FLASH_EraseBlock(const INT32U u32_fDestAddr);

/* Function for Flash */
extern void FLASH_Program(INT32U u32_fDestAddr, const INT8U *p_u8fBuffer, const INT16U u16_fSize);

/* Function for Flash */
extern void FLASH_DeInit(void);

#endif

/**************************************************************************************************/
/* End of  NVMCTRL.h                                                                              */
/**************************************************************************************************/
