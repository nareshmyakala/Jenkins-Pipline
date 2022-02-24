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
/*  File Name   : NVMCTRL.c                                                                       */
/*  Author      : Ravi Ranjan Kumar                                                               */
/*  Version 	: 1.0                                                                             */
/*  Date        : 30-08-2018                                                                      */
/*                                                                                                */
/* @Description : NVM Driver                                                                      */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

#include "compiler.h"
#include <string.h>

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "MCLK.h"

#include "NVMCTRL.h"
#include "NVMCTRL_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

#define NVMCTRL_BLOCK_PAGES 		( NVMCTRL_BLOCK_SIZE / NVMCTRL_PAGE_SIZE )
#define NVM_MEMORY 					((volatile INT32U *)FLASH_ADDR)
#define NVMCTRL_REGIONS_NUM 		( 32 )

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Array of Pointer that Holds All the Base Addresses of NVM */
ST_NVMCTRL_REG_t *p_gNVMRegAccess = (ST_NVMCTRL_REG_t *)NVMCTRL_BASE_ADDR;
	
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

INT32U FLASH_Init(void)
{
	INT32U u32_lStatus = 0;
	INT32U u32_lReg = 0;
	
	/* Enable AHB Clk for NVM */
	CRITICAL_SECTION_ENTER();
	
	/* Flash Clk Init */
	MCLK_PeriphClkInit(MCLK_AHB, MCLK_AHB_NVMCTRL);
	
	CRITICAL_SECTION_LEAVE();
	
	/* Read CRLA Reg */
	u32_lReg = p_gNVMRegAccess->CTRLA;
	
	/* Clear CACHE0, CACHE1 and PRM */
	u32_lReg &= ~(NVMCTRL_CTRLA_CACHEDIS0_MASK | \
								NVMCTRL_CTRLA_CACHEDIS1_MASK | NVMCTRL_CTRLA_PRM_MASK);

	CRITICAL_SECTION_ENTER();
	
	p_gNVMRegAccess->CTRLA = u32_lReg;
	
	CRITICAL_SECTION_LEAVE();
	
	return u32_lStatus;
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

void FLASH_SendCommand(const INT32U u32_fAddress, EN_NVM_CMD_t en_fNvmCmd)
{
	/* Enter Critical Section */
	CRITICAL_SECTION_ENTER();
	
	/* Write Address */
	p_gNVMRegAccess->ADDR = u32_fAddress;
		
	/* Write Command */
	p_gNVMRegAccess->CTRLB = (en_fNvmCmd | \
							(NVMCTRL_CTRLB_CMDEX_KEY << NVMCTRL_CTRLB_CMDEX_OFFSET));
	/* Exit Critical Section */
	CRITICAL_SECTION_LEAVE();
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

INT32U FLASH_GetTotalPages(void)
{
	return (INT32U)(p_gNVMRegAccess->PARAM & NVMCTRL_PARAM_NVMP_MASK);
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

INT8U FLASH_GetWaitState(void)
{
	return (INT8U)((p_gNVMRegAccess->CTRLA & NVMCTRL_CTRLA_RWS_MASK) >> NVMCTRL_CTRLA_RWS_OFFSET);
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

void FLASH_SetWaitState(INT8U u8_fWaitState)
{
	INT16U u16_lReg = 0;
	
	/* Enter Crital Section */
	CRITICAL_SECTION_ENTER();
	
	/* Read CTRLA */
	u16_lReg = p_gNVMRegAccess->CTRLA;
	
	/* Clear RWS */
	u16_lReg &= ~NVMCTRL_CTRLA_RWS_MASK;
	
	/* Write RWS */
	u16_lReg |= (u8_fWaitState << NVMCTRL_CTRLA_RWS_OFFSET);
	
	/* Write Reg */
	p_gNVMRegAccess->CTRLA = u16_lReg;
	
	/* Exit Crital Section */
	CRITICAL_SECTION_LEAVE();
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

void FLASH_Read(const INT32U u32_fAddress, INT8U *p_u8fBuffer, INT32U u32_fLength)
{
	INT32U u32_lIndex = 0;
	INT8U  *p_u8lDestAddr = (INT8U *)NVM_MEMORY;
		
	/* Check if the module is busy */
	while(!(p_gNVMRegAccess->STATUS & NVMCTRL_STATUS_READY_MASK));
    
    for(u32_lIndex = 0; u32_lIndex < u32_fLength; u32_lIndex++)
    {
      p_u8fBuffer[u32_lIndex] = p_u8lDestAddr[u32_fAddress + u32_lIndex];
    }
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

void FLASH_Write(const INT32U u32_fDestAddr, INT8U *p_u8lBuffer, INT32U u32_fLength)
{
	INT8U  au8_lTmpBuffer[NVMCTRL_BLOCK_PAGES][NVMCTRL_PAGE_SIZE];
	INT32U u32_lBlockStartAddr, u32_lBlockEndAddr;
	INT32U u32_lIndex1, u32_lIndex2, u32_lIndex3;
	INT32U u32_lStartAddr = u32_fDestAddr;

	do 
	{
		u32_lBlockStartAddr = u32_lStartAddr & ~(NVMCTRL_BLOCK_SIZE - 1);
		u32_lBlockEndAddr   = u32_lBlockStartAddr + NVMCTRL_BLOCK_SIZE - 1;

		/* store the erase data into temp buffer before write */
		for (u32_lIndex1 = 0; u32_lIndex1 < NVMCTRL_BLOCK_PAGES; u32_lIndex1++) 
		{
			FLASH_Read(u32_lBlockStartAddr + u32_lIndex1 * NVMCTRL_PAGE_SIZE, \
												au8_lTmpBuffer[u32_lIndex1], NVMCTRL_PAGE_SIZE);
		}

		/* temp buffer update */
		u32_lIndex2 = (u32_lStartAddr - u32_lBlockStartAddr) / NVMCTRL_PAGE_SIZE;
		u32_lIndex3 = u32_lStartAddr - u32_lBlockStartAddr - u32_lIndex2 * NVMCTRL_PAGE_SIZE;
		
		while ((u32_lStartAddr <= u32_lBlockEndAddr) && (u32_fLength > 0)) 
		{
			au8_lTmpBuffer[u32_lIndex2][u32_lIndex3] = *p_u8lBuffer;
			u32_lIndex3 = (u32_lIndex3 + 1) % NVMCTRL_PAGE_SIZE;

			if (0 == u32_lIndex3) 
			{
				u32_lIndex2++;
			}
			else
			{
				/* No Action */
			}

			u32_lStartAddr++;
			p_u8lBuffer++;
			u32_fLength--;
		}

		/* Erase Row Before Write */
		FLASH_EraseBlock(u32_lBlockStartAddr);

		/* Write Buffer to flash */
		for (u32_lIndex1 = 0; u32_lIndex1 < NVMCTRL_BLOCK_PAGES; u32_lIndex1++) 
		{
			FLASH_Program(u32_lBlockStartAddr + u32_lIndex1 * NVMCTRL_PAGE_SIZE, \
												au8_lTmpBuffer[u32_lIndex1], NVMCTRL_PAGE_SIZE);
		}
	} while (u32_lBlockEndAddr < (u32_lStartAddr + u32_fLength - 1));
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

void FLASH_Append(const INT32U u32_fDestAddr, INT8U *p_u8lBuffer, INT32U u32_fLength)
{
	INT32U u32_lPageStartAddr = u32_fDestAddr & ~(NVMCTRL_PAGE_SIZE - 1);
	INT32U u32_lSize;
	INT32U u32_lOffset = 0;

	if (u32_fDestAddr != u32_lPageStartAddr) 
	{
		/* Need to write some data to the end of a page */
		u32_lSize = min(u32_fLength, NVMCTRL_PAGE_SIZE - (u32_fDestAddr - u32_lPageStartAddr));
		
		FLASH_Program(u32_fDestAddr, p_u8lBuffer, u32_lSize);
		
		u32_lPageStartAddr += NVMCTRL_PAGE_SIZE;
		u32_lOffset += u32_lSize;
	}
	else
	{
		/* No Action */
	}

	while (u32_lOffset < u32_fLength) 
	{
		u32_lSize = min(u32_fLength - u32_lOffset, NVMCTRL_PAGE_SIZE);
		
		FLASH_Program(u32_lPageStartAddr, p_u8lBuffer + u32_lOffset, u32_lSize);
		
		u32_lPageStartAddr += NVMCTRL_PAGE_SIZE;
		u32_lOffset += u32_lSize;
	}
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

void FLASH_Erase(INT32U u32_fDestAddr, INT32U u32_fPageNums)
{
	INT8U  au8_lTmpBuffer[NVMCTRL_PAGE_SIZE];
	INT32U u32_lBlockStartAddr;
	INT32U u32_lIndex;

	u32_lBlockStartAddr = u32_fDestAddr & ~(NVMCTRL_BLOCK_SIZE - 1);

	memset(au8_lTmpBuffer, 0xFF, NVMCTRL_PAGE_SIZE);

	/* when address is not aligned with block start address */
	if (u32_fDestAddr != u32_lBlockStartAddr) 
	{
		u32_lBlockStartAddr += NVMCTRL_BLOCK_SIZE;
		
		for (u32_lIndex = 0; u32_lIndex < NVMCTRL_BLOCK_PAGES - 1; u32_lIndex++)
		{
			FLASH_Write(u32_fDestAddr, au8_lTmpBuffer, NVMCTRL_PAGE_SIZE);

			if (--u32_fPageNums == 0) 
			{
				return;
			}
			else
			{
				/* No Action */
			}

			u32_fDestAddr += NVMCTRL_PAGE_SIZE;

			if(u32_fDestAddr == u32_lBlockStartAddr) 
			{
				break;
			}
			else
			{
				/* No Action */
			}
		}
	}
	else
	{
		/* No Action */
	}

	while (u32_fPageNums >= NVMCTRL_BLOCK_PAGES) 
	{
		FLASH_EraseBlock(u32_lBlockStartAddr);
		
		u32_lBlockStartAddr += NVMCTRL_BLOCK_SIZE;
		
		u32_fPageNums -= NVMCTRL_BLOCK_PAGES;
	}

	if (u32_fPageNums != 0) 
	{
		for (u32_lIndex = 0; u32_lIndex < u32_fPageNums; u32_lIndex++) 
		{
			FLASH_Write(u32_lBlockStartAddr, au8_lTmpBuffer, NVMCTRL_PAGE_SIZE);
			
			u32_lBlockStartAddr += NVMCTRL_PAGE_SIZE;
		}
	}
	else
	{
		/* No Action */
	}
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

INT32U FLASH_Lock(const INT32U u32_fDestAddr, INT32U u32_fPageNums)
{
	INT32U u32_lRegionPages;
	INT32U u32_lBlockStartAddr;

	u32_lRegionPages     = (INT32U)FLASH_SIZE / (NVMCTRL_REGIONS_NUM * NVMCTRL_PAGE_SIZE);
	u32_lBlockStartAddr = u32_fDestAddr & ~(NVMCTRL_BLOCK_SIZE - 1);

	if ((u32_fPageNums != u32_lRegionPages) || (u32_fDestAddr != u32_lBlockStartAddr)) 
	{
		return (INT32U)NVM_ERROR;
	}
	else
	{
		/* No Action */
	}

	/* Check if the module is busy */
	while(!(p_gNVMRegAccess->STATUS & NVMCTRL_STATUS_READY_MASK));
	
	/* Send Cmd */	
	FLASH_SendCommand(u32_fDestAddr, NVMCTRL_CTRLB_CMD_LR);
	
	return (int32_t)FLASH_SIZE / (NVMCTRL_REGIONS_NUM * NVMCTRL_PAGE_SIZE);
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

INT32U FLASH_Unlock(const INT32U u32_fDestAddr, INT32U u32_fPageNums)
{
	INT32U u32_lRegionPages;
	INT32U u32_lBlockStartAddr;

	u32_lRegionPages     = (INT32U)FLASH_SIZE / (NVMCTRL_REGIONS_NUM * NVMCTRL_PAGE_SIZE);
	u32_lBlockStartAddr = u32_fDestAddr & ~(NVMCTRL_BLOCK_SIZE - 1);

	if ((u32_fPageNums != u32_lRegionPages) || (u32_fDestAddr != u32_lBlockStartAddr)) 
	{
		return (INT32U)NVM_ERROR;
	}
	else
	{
		/* No Action */
	}

	/* Check if the module is busy */
	while(!(p_gNVMRegAccess->STATUS & NVMCTRL_STATUS_READY_MASK));

	/* Send Cmd */	
	FLASH_SendCommand(u32_fDestAddr, NVMCTRL_CTRLB_CMD_UR);

	return (INT32U)FLASH_SIZE / (NVMCTRL_REGIONS_NUM * NVMCTRL_PAGE_SIZE);
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

INT8U IsFLASH_Locked(const INT32U u32_fDestAddr)
{
	INT16U u16_lRegionId = 0;
	INT32U u32_lTempReg = 0;

	/* Get region for given page */
	u16_lRegionId = u32_fDestAddr / (FLASH_SIZE / NVMCTRL_REGIONS_NUM);

	u32_lTempReg = p_gNVMRegAccess->RUNLOCK;
	u32_lTempReg &= (1 << u16_lRegionId);
	
	return !(u32_lTempReg);
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

void FLASH_EraseBlock(const INT32U u32_fDestAddr)
{
	/* Check if the module is busy */
	while(!(p_gNVMRegAccess->STATUS & NVMCTRL_STATUS_READY_MASK));

	/* Set address and command */
	FLASH_SendCommand(u32_fDestAddr, NVMCTRL_CTRLB_CMD_EB);
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

void FLASH_Program(INT32U u32_fDestAddr, const INT8U *p_u8fBuffer, const INT16U u16_fSize)
{
	INT32U *p_u32ReadPtr    = (INT32U *)p_u8fBuffer;
	INT32U  u32_lNvmAddress = u32_fDestAddr / 4;
	INT16U  u16_lIndex = 0;

	/* Check if the module is busy */
	while(!(p_gNVMRegAccess->STATUS & NVMCTRL_STATUS_READY_MASK));

	CRITICAL_SECTION_ENTER();
	
	p_gNVMRegAccess->CTRLB = (NVMCTRL_CTRLB_CMD_PBC | \
							(NVMCTRL_CTRLB_CMDEX_KEY << NVMCTRL_CTRLB_CMDEX_OFFSET));
	CRITICAL_SECTION_LEAVE();
	
	/* Check if the module is busy */
	while(!(p_gNVMRegAccess->STATUS & NVMCTRL_STATUS_READY_MASK));

	/* Writes to the page buffer must be 32 bits, perform manual copy to ensure alignment */
	for (u16_lIndex = 0; u16_lIndex < u16_fSize; u16_lIndex += 4) 
	{
		NVM_MEMORY[u32_lNvmAddress++] = *p_u32ReadPtr;
		p_u32ReadPtr++;
	}

	/* Check if the module is busy */
	while(!(p_gNVMRegAccess->STATUS & NVMCTRL_STATUS_READY_MASK));

	/* Set address and command */
	FLASH_SendCommand(u32_fDestAddr, NVMCTRL_CTRLB_CMD_WP);
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

void FLASH_DeInit(void)
{
	
}

/**************************************************************************************************/
/* End of  NVMCTRL.c                                                                              */
/**************************************************************************************************/
