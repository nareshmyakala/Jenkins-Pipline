/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2014-15, Think Embedded Pvt. Ltd. (TEPL)                     */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : Common1.c                                                                       */
/* \Author      : Ashish Kumar kar                                                                */
/* \Version 	: iCONNECT V1                                                                     */
/* \Date        : 01/05/2015                                                                      */
/*                                                                                                */
/* @Description : Common functionality Framework                                                  */
/**************************************************************************************************/

/**************************************************************************************************/
/* System Header Files Section                                                					  */
/**************************************************************************************************/

#include "string.h"

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "DATACONV.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

INT8U u8_gDecimalPosition;

/**************************************************************************************************/
/* Function Name   : COMMON_Byte2PAN                                                              */
/*                                                                                                */
/* Description     : Function that convert Byte to PAN                                            */
/*                                                                                                */
/* In Params       : INT8U * p_fDstBuffer, INT8U u8_fInput                                        */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_COMMON_RESULT_t ( return 0 for Success, -1 for Failure )                  */
/**************************************************************************************************/

EN_COMMON_RESULT_t COMMON_Byte2PAN(INT8U * p_fDstBuffer, INT8U u8_fInput)
{
	EN_COMMON_RESULT_t en_lResult = COMMON_OK;
	INT8U u8_lIndex = 0x00;
	
	/* Check for Valid buffer */
	if(p_fDstBuffer == PNULL)
	{
		 en_lResult = COMMON_ERROR;
	}
	else
	{
		for(u8_lIndex = 0; u8_lIndex < 1; u8_lIndex++)
		{
			/* Check for LSB nibble is in between A and F */
			if(((u8_fInput & 0x0F) >= 0x0A) && ((u8_fInput & 0x0F) <= 0x0F))
			{
				/* Make the nibble to byte data */
				*(p_fDstBuffer + u8_lIndex + 1) = (0x40 + ((u8_fInput & 0x0F) - 0x09));
			}
			/* Check for LSB nibble is in between 0 and 9 */
			else if(((u8_fInput & 0x0F) >= 0x00) && ((u8_fInput & 0x0F) <= 0x09))
			{
				/* Make the nibble to byte data */
				*(p_fDstBuffer + u8_lIndex + 1) = (( u8_fInput & 0x0F) + 0x30);
			}
			else
			{
				en_lResult = COMMON_ERROR;
				break;
			}
			
			/* Load MSB byte */
			u8_fInput = u8_fInput >> 4;
			
			/* Check for MSB nibble is in between A and F */
			if(((u8_fInput & 0x0F) >= 0x0A) && ((u8_fInput & 0x0F) <= 0x0F))
			{
				/* Make the nibble to byte data */
				*(p_fDstBuffer + u8_lIndex) = (0x40 + ((u8_fInput & 0x0F) - 0x09));
			}
			/* Check for MSB nibble is in between 0 and 9 */
			else if(((u8_fInput & 0x0F) >= 0x00) && ((u8_fInput & 0x0F) <= 0x09))
			{
				/* Make the nibble to byte data */
				*(p_fDstBuffer + u8_lIndex) = ((u8_fInput & 0x0F) + 0x30);
			}
			else
			{
				en_lResult = COMMON_ERROR;
				break;
			}
		}
	 }
	return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : COMMON_HWord2PAN                                                             */
/*                                                                                                */
/* Description     : Function that convert HWord to PAN                                           */
/*                                                                                                */
/* In Params       : INT8U * p_fDstBuffer, INT16U u16_fInput                                      */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_COMMON_RESULT_t ( return 0 for Success, -1 for Failure )                  */
/**************************************************************************************************/

EN_COMMON_RESULT_t COMMON_HWord2PAN(INT8U * p_fDstBuffer, INT16U u16_fInput)
{
	EN_COMMON_RESULT_t en_lResult = COMMON_OK;
	INT8U u8_lInput = 0x00;
	INT8S u8_lIndex1 = 0x00;
	INT8S u8_lIndex2 = 0x00;
	
	/* Check for Valid buffer */
	if(p_fDstBuffer == PNULL)
	{
		 en_lResult = COMMON_ERROR;
	}
	else
	{
		for(u8_lIndex1 = 0, u8_lIndex2 = 0; u8_lIndex2 <= 2 ; u8_lIndex1 = u8_lIndex1 + 1, \
															u8_lIndex2 = u8_lIndex2 + 2)
		{
			/* Get MSB byte according to index*/
			u8_lInput = (INT8U)((u16_fInput >> (8 - (u8_lIndex1 * 8))) & 0xFF);
			en_lResult = COMMON_Byte2PAN( (INT8U *)&p_fDstBuffer[u8_lIndex2], u8_lInput);
		}
	}
	return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : COMMON_Word2PAN                                                              */
/*                                                                                                */
/* Description     : Function that convert Word to PAN                                            */
/*                                                                                                */
/* In Params       : INT8U * p_fDstBuffer, INT32U u32_fInput                                      */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_COMMON_RESULT_t ( return 0 for Success, -1 for Failure )                  */
/**************************************************************************************************/

EN_COMMON_RESULT_t COMMON_Word2PAN(INT8U * p_fDstBuffer, INT32U u32_fInput)
{
	EN_COMMON_RESULT_t en_lResult = COMMON_OK;
	INT8U u8_lInput = 0x00;
	INT8S u8_lIndex1 = 0x00;
	INT8S u8_lIndex2 = 0x00;
	
	/* Check for Valid buffer */
	if(p_fDstBuffer == PNULL)
	{
		 en_lResult = COMMON_ERROR;
	}
	else
	{
		for(u8_lIndex1 = 0, u8_lIndex2 = 0; u8_lIndex2 <= 6; u8_lIndex1 = u8_lIndex1 + 1, \
															u8_lIndex2 = u8_lIndex2 + 2)
		{
			/* Get MSB byte according to index*/
			u8_lInput = (INT8U)(((u32_fInput) >> (24 - (u8_lIndex1 * 8))) & 0xFF);
			en_lResult = COMMON_Byte2PAN( (INT8U *)&p_fDstBuffer[u8_lIndex2], u8_lInput);
		}
	}
	return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : COMMON_DWord2PAN                                                             */
/*                                                                                                */
/* Description     : Function that convert DWord to PAN                                           */
/*                                                                                                */
/* In Params       : INT8U * p_fDstBuffer, INT64U u64_fInput                                      */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_COMMON_RESULT_t ( return 0 for Success, -1 for Failure )                  */
/**************************************************************************************************/

EN_COMMON_RESULT_t COMMON_DWord2PAN(INT8U * p_fDstBuffer, INT64U u64_fInput)
{
	EN_COMMON_RESULT_t en_lResult = COMMON_OK;
	INT8U u8_lInput = 0x00;
	INT8S u8_lIndex1 = 0x00;
	INT8S u8_lIndex2 = 0x00;

	/* Check for Valid buffer */
	if(p_fDstBuffer == PNULL)
	{
		 en_lResult = COMMON_ERROR;
	}
	else
	{
		for(u8_lIndex1 = 0, u8_lIndex2 = 0; u8_lIndex2 <= 14; u8_lIndex1 = u8_lIndex1 + 1, \
															u8_lIndex2 = u8_lIndex2 + 2)
		{
			/* Get MSB byte according to index*/
			u8_lInput = (INT8U)(((u64_fInput) >> (56 - (u8_lIndex1 * 8))) & 0xFF);
			en_lResult = COMMON_Byte2PAN( (INT8U *)&p_fDstBuffer[u8_lIndex2], u8_lInput);
		}
	}
	return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : COMMON_ByteArray2PAN                                                         */
/*                                                                                                */
/* Description     : Function that convert ByteArray to PAN                                       */
/*                                                                                                */
/* In Params       : INT8U * p_fDstBuffer, INT8U * p_fSrcBuffer,INT16U u16_fSrcLen                */																		                                        
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_COMMON_RESULT_t ( return 0 for Success, -1 for Failure )                  */
/**************************************************************************************************/

EN_COMMON_RESULT_t COMMON_ByteArray2PAN(INT8U * p_fDstBuffer, INT8U * p_fSrcBuffer, \
																		INT16U u16_fSrcLen)
{
	EN_COMMON_RESULT_t en_lResult = COMMON_OK;
    INT16U u16_lOffset = 0;
    INT8U u8_lPanBytes[2] = {0, };
    
	/* Check for Valid buffer */
    if(p_fSrcBuffer == PNULL || p_fDstBuffer == PNULL || u16_fSrcLen == 0)
    {
        en_lResult = COMMON_ERROR;
    }
    else
    {
		for(INT16U u16_lIndex = 0; u16_lIndex < u16_fSrcLen; u16_lIndex++)
		{
			COMMON_Byte2PAN((INT8U *)&u8_lPanBytes[0], p_fSrcBuffer[u16_lIndex]);
            u16_lOffset = (INT16U)(u16_lIndex * 2);
            p_fDstBuffer[u16_lOffset] = u8_lPanBytes[0];
            p_fDstBuffer[u16_lOffset + 1] = u8_lPanBytes[1];
        }
	}
	return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : COMMON_PAN2Byte                                                              */
/*                                                                                                */
/* Description     : Function that convert PAN to Byte                                            */
/*                                                                                                */
/* In Params       : INT8U * p_fSrcBuffer, INT8U * p_fOutPut                                      */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_COMMON_RESULT_t ( return 0 for Success, -1 for Failure )                  */
/**************************************************************************************************/
    
EN_COMMON_RESULT_t COMMON_PAN2Byte(INT8U * p_fSrcBuffer, INT8U * p_fOutPut)
{
	EN_COMMON_RESULT_t en_lResult = COMMON_OK;
    INT8U u8_lIndex = 0x00;
	
	/* Check for Valid buffer */
    if(p_fSrcBuffer == PNULL)
    {
        en_lResult = COMMON_ERROR;
    }
    else
    {
		for(u8_lIndex = 0; u8_lIndex < 1; u8_lIndex++)
		{
			/* Check for nibble is in between A and F */
			if((*(p_fSrcBuffer + u8_lIndex) <= 0x46) && *(p_fSrcBuffer + u8_lIndex) >= 0x41)
			{
				/* Make the byte data to nibble */
				*p_fOutPut = (INT8U)(((*(p_fSrcBuffer + u8_lIndex) - 0x37) << 4));
			}
			/* Check for nibble is in between 0 and 9 */
			else if((*(p_fSrcBuffer + u8_lIndex) <= 0x39) && *(p_fSrcBuffer + u8_lIndex) >= 0x30)
			{
				/* Make the byte data to nibble */
				*p_fOutPut = (INT8U)(((*(p_fSrcBuffer + u8_lIndex) - 0x30) << 4));
			}
			else
			{
				en_lResult = COMMON_ERROR;
				break;
			}
			/* Check for nibble is in between 0 and 9 */
			if((*(p_fSrcBuffer + u8_lIndex + 1) <= 0x46) && (*(p_fSrcBuffer + u8_lIndex + 1) \
																					>= 0x41))
			{
				/* Make the byte data to nibble */
				*p_fOutPut |= (INT8U)((*(p_fSrcBuffer + (u8_lIndex + 1)) - 0x37));
			}
			/* Check for nibble is in between 0 and 9 */
			else if((*(p_fSrcBuffer + u8_lIndex + 1) <= 0x39) && (*(p_fSrcBuffer + u8_lIndex + 1) \
																						>= 0x30))																						
			{
				/* Make the byte data to nibble */
				*p_fOutPut |= (INT8U)((((*(p_fSrcBuffer + (u8_lIndex + 1)) & 0x0f) + 0x30)) - 0x30);
			}
			else
			{
				en_lResult = COMMON_ERROR;
				break;
			}
		}
    }
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : COMMON_PAN2HWord                                                             */
/*                                                                                                */
/* Description     : Function that convert PAN to HWord                                           */
/*                                                                                                */
/* In Params       : INT8U * p_fSrcBuffer, INT16U * p_fOutPut                                     */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_COMMON_RESULT_t ( return 0 for Success, -1 for Failure )                  */
/**************************************************************************************************/
    
EN_COMMON_RESULT_t COMMON_PAN2HWord(INT8U * p_fSrcBuffer, INT16U * p_fOutPut)
{
	EN_COMMON_RESULT_t en_lResult = COMMON_OK;
    INT8U u8_lIndex = 0x00;
	INT8U u8_lTemp = 0x00;

	/* Check for Valid buffer */
    if(p_fSrcBuffer == PNULL)
    {
        en_lResult = COMMON_ERROR;
    }
    else
    {
		for(u8_lIndex = 0; u8_lIndex < 3; u8_lIndex = u8_lIndex + 2)
		{
			/* Load each PAN Byte from MSB side */
			*p_fOutPut = *p_fOutPut << 8;
			
			/* Check for nibble is in between A and F */
			if((*(p_fSrcBuffer + u8_lIndex) <= 0x46) && *(p_fSrcBuffer + u8_lIndex) >= 0x41)
			{
				/* Make the byte data to nibble */
				u8_lTemp = (INT8U)(((*(p_fSrcBuffer + u8_lIndex) - 0x37) << 4));
			}
			/* Check for nibble is in between 0 and 9 */
			else if((*(p_fSrcBuffer + u8_lIndex) <= 0x39) && *(p_fSrcBuffer + u8_lIndex) >= 0x30)
			{
				/* Make the byte data to nibble */
				u8_lTemp = (INT8U)(((*(p_fSrcBuffer + u8_lIndex) - 0x30) << 4));
			}
			else
			{
				en_lResult = COMMON_ERROR;
				break;
			}
			/* Check for nibble is in between A and F */
			if((*(p_fSrcBuffer + u8_lIndex + 1) <= 0x46) && (*(p_fSrcBuffer + u8_lIndex + 1) \
																					>= 0x41))
			{
				/* Make the byte data to nibble */
				u8_lTemp |= (INT8U)((*(p_fSrcBuffer + (u8_lIndex + 1)) - 0x37));
			}
			/* Check for nibble is in between 0 and 9 */
			else if((*(p_fSrcBuffer + u8_lIndex + 1) <= 0x39) && (*(p_fSrcBuffer + u8_lIndex + 1) \
																					>=0x30))																				
			{
				/* Make the byte data to nibble */
				u8_lTemp |= (INT8U)((((*(p_fSrcBuffer + (u8_lIndex + 1)) & 0x0F) + 0x30)) - 0x30);
			}
			else
			{
				en_lResult = COMMON_ERROR;
				break;
			}
			*p_fOutPut |= u8_lTemp;
		}
    }
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : COMMON_PAN2Word                                                              */
/*                                                                                                */
/* Description     : Function that convert PAN to Word                                            */
/*                                                                                                */
/* In Params       : INT8U * p_fSrcBuffer, INT32U * p_fOutPut                                     */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_COMMON_RESULT_t ( return 0 for Success, -1 for Failure )                  */
/**************************************************************************************************/
    
EN_COMMON_RESULT_t COMMON_PAN2Word(INT8U * p_fSrcBuffer, INT32U * p_fOutPut)
{
	EN_COMMON_RESULT_t en_lResult = COMMON_OK;
    INT8U u8_lIndex = 0x00;
	INT8U u8_lTemp = 0x00;

	/* Check for Valid buffer */
    if(p_fSrcBuffer == PNULL)
    {
        en_lResult = COMMON_ERROR;
    }
    else
    {
		for(u8_lIndex = 0; u8_lIndex < 7; u8_lIndex = u8_lIndex + 2)
		{
			/* Load each PAN Byte from MSB side */
			*p_fOutPut = *p_fOutPut << 8;
			
			/* Check for nibble is in between A and F */
			if((*(p_fSrcBuffer + u8_lIndex) <= 0x46) && *(p_fSrcBuffer + u8_lIndex) >= 0x41)
			{
				/* Make the byte data to nibble */
				u8_lTemp = (INT8U)(((*(p_fSrcBuffer + u8_lIndex) - 0x37) << 4));
			}
			/* Check for nibble is in between 0 and 9 */
			else if((*(p_fSrcBuffer + u8_lIndex) <= 0x39) && *(p_fSrcBuffer + u8_lIndex) >= 0x30)
			{
				/* Make the byte data to nibble */
				u8_lTemp = (INT8U)(((*(p_fSrcBuffer + u8_lIndex) - 0x30) << 4));
			}
			else
			{
				en_lResult = COMMON_ERROR;
				break;
			}
			/* Check for nibble is in between A and F */
			if((*(p_fSrcBuffer + u8_lIndex + 1) <= 0x46) && (*(p_fSrcBuffer + u8_lIndex + 1) \
																					>= 0x41))
			{
				/* Make the byte data to nibble */
				u8_lTemp |= (INT8U)((*(p_fSrcBuffer + (u8_lIndex + 1)) - 0x37));
			}
			/* Check for nibble is in between 0 and 9 */
			else if((*(p_fSrcBuffer + u8_lIndex + 1) <= 0x39) && (*(p_fSrcBuffer + u8_lIndex + 1) \
																					>= 0x30))																					
			{
				/* Make the byte data to nibble */
				u8_lTemp |= (INT8U)((((*(p_fSrcBuffer + (u8_lIndex + 1)) & 0x0f) + 0x30)) - 0x30);
			}
			else
			{
				en_lResult = COMMON_ERROR;
				break;
			}
			*p_fOutPut |= u8_lTemp;
		}
    }
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : COMMON_PAN2DWord                                                             */
/*                                                                                                */
/* Description     : Function that convert PAN to DWord                                           */
/*                                                                                                */
/* In Params       : INT8U * p_fSrcBuffer, INT64U * p_fOutPut                                     */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_COMMON_RESULT_t ( return 0 for Success, -1 for Failure )                  */
/**************************************************************************************************/
    
EN_COMMON_RESULT_t COMMON_PAN2DWord(INT8U * p_fSrcBuffer, INT64U * p_fOutPut)
{
	EN_COMMON_RESULT_t en_lResult = COMMON_OK;
    INT8U u8_lIndex = 0;
	INT8U u8_lTemp = 0;

	/* Check for Valid buffer */
    if(p_fSrcBuffer == PNULL)
    {
        en_lResult = COMMON_ERROR;
    }
    else
    {
		for(u8_lIndex = 0; u8_lIndex < 15; u8_lIndex = u8_lIndex + 2)
		{
			/* Load each PAN Byte from MSB side */
			*p_fOutPut = *p_fOutPut << 8;
			
			/* Check for nibble is in between A and F */
			if((*(p_fSrcBuffer + u8_lIndex) <= 0x46) && *(p_fSrcBuffer + u8_lIndex) >= 0x41)
			{
				/* Make the byte data to nibble */
				u8_lTemp = (INT8U)(((*(p_fSrcBuffer + u8_lIndex) - 0x37) << 4));
			}
			/* Check for nibble is in between 0 and 9 */
			else if((*(p_fSrcBuffer + u8_lIndex) <= 0x39) && *(p_fSrcBuffer + u8_lIndex) >= 0x30)
			{
				/* Make the byte data to nibble */
				u8_lTemp = (INT8U)(((*(p_fSrcBuffer + u8_lIndex) - 0x30) << 4));
			}
			else
			{
				en_lResult = COMMON_ERROR;
				break;
			}
			/* Check for nibble is in between A and F */
			if((*(p_fSrcBuffer + u8_lIndex + 1) <= 0x46) && (*(p_fSrcBuffer + u8_lIndex + 1) \
																					>= 0x41))
			{
				/* Make the byte data to nibble */
				u8_lTemp |= (INT8U)((*(p_fSrcBuffer + (u8_lIndex + 1)) - 0x37));
			}
			/* Check for nibble is in between 0 and 9 */
			else if((*(p_fSrcBuffer + u8_lIndex + 1) <= 0x39) && (*(p_fSrcBuffer + u8_lIndex + 1) \
																					>= 	0x30))																			
			{
				/* Make the byte data to nibble */
				u8_lTemp |= (INT8U)((((*(p_fSrcBuffer + (u8_lIndex + 1)) & 0x0F) + 0x30)) - 0x30);																							
			}
			else
			{
				en_lResult = COMMON_ERROR;
				break;
			}
			*p_fOutPut |= u8_lTemp;
		}
    }
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : COMMON_PAN2ByteArray                                                         */
/*                                                                                                */
/* Description     : Function that convert PAN to ByteArray                                       */
/*                                                                                                */
/* In Params       : INT8U * p_fDstBuffer, INT8U * p_fSrcBuffer,INT16U u16_fSrcLen                */																		                                        
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : EN_COMMON_RESULT_t ( return 0 for Success, -1 for Failure )                  */
/**************************************************************************************************/

EN_COMMON_RESULT_t COMMON_PAN2ByteArray(INT8U * p_fSrcBuffer, INT8U * p_fDstBuffer, \
																		INT16U u16_fDstLen)
{
	EN_COMMON_RESULT_t en_lResult = COMMON_OK;
    INT8U u8_lByte = 0;
    INT16U u16_lOffset = 0;

	/* Check for Valid buffer */
    if((p_fSrcBuffer == PNULL) || (p_fDstBuffer == PNULL) || (u16_fDstLen == 0))
    {
        en_lResult = COMMON_ERROR;
    }
    else
    {
		for(INT16U u16_lIndex = 0; u16_lIndex < u16_fDstLen; u16_lIndex++)
		{
            u16_lOffset = (INT16U)(u16_lIndex * 2);
            COMMON_PAN2Byte((INT8U *)&p_fSrcBuffer[u16_lOffset], (INT8U *)&u8_lByte);
            p_fDstBuffer[u16_lIndex] = u8_lByte;
		}
    }
    
    return en_lResult;
}

/**************************************************************************************************/
/* Function Name   : void COMMON_Dec2Ascii(INT8U * P_fDst, INT32U u32_fSrc, \                     */
/*                                            INT8U u8_fLength)                                   */
/*                                                                                                */
/* Description     : Parse and Process the Received Command.                                      */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : METER_BUS_RESULT ( return 1 for Success, 0 for Failure )                     */
/**************************************************************************************************/
    
void COMMON_Dec2Ascii(UINT8 * P_fDst, UINT32 u32_fSrc, UINT8 u8_fLength)
{
    INT8U u8_lIndex;
    INT8U u8_lTemp;

    u8_lTemp = u8_fLength;

    u8_fLength = u8_fLength - 1;

    for(u8_lIndex = 0; u8_lIndex < u8_lTemp; u8_lIndex++)
    {
        if(0x00 == u32_fSrc)
        {
            *(P_fDst +  u8_fLength) =  '0';

            if((u8_lIndex == u8_gDecimalPosition)  && (u8_gDecimalPosition != 0))
            {
                *(P_fDst +  u8_fLength) =  '.';
            }
            else
            {
                /* NO ACTION */
            }
        }
        else
        {
            if((u8_lIndex == u8_gDecimalPosition)  && (u8_gDecimalPosition != 0))
            {
                *(P_fDst +  u8_fLength) =  '.';
            }
            else
            {
                *(P_fDst +  u8_fLength) = (INT8U)((u32_fSrc  % 10) + 0x30);
                u32_fSrc = u32_fSrc / 10;
            }
        }

        u8_fLength = u8_fLength - 1;
    }

    /* Add Record Separator */
    *(P_fDst +  u8_lTemp ) = 0x1E;
}

/**************************************************************************************************/
/* Function Name   : INT32U COMMON_Ascii2Dec(INT8U * p_fSrc, INT8U u8_fLength)                    */
/*                                                                                                */
/* Description     : Parse and Process the Received Command.                                      */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : METER_BUS_RESULT ( return 1 for Success, 0 for Failure )                     */
/**************************************************************************************************/
    
UINT32 COMMON_Ascii2Dec(INT8U * p_fSrc, INT8U u8_fLength)
{
    INT8U u8_lIndex;

    INT32U u32_fDst = 0;

    for(u8_lIndex = 0; u8_lIndex < u8_fLength; u8_lIndex++)
    {
        if(*(p_fSrc +  u8_lIndex) == '.')
        {
            /* No Action */
        }
        else if(*p_fSrc == 0x00)
        {
            u32_fDst = 0;

        }
        else if((*(p_fSrc +  u8_lIndex) >= 0x03) && (*(p_fSrc +  u8_lIndex) <= 0x39))
        {
           u32_fDst =  (u32_fDst * 10) + (INT8U)(*(p_fSrc +  u8_lIndex) - 0x30);
        }
    }

    return u32_fDst;
}

/**************************************************************************************************/
/* Function Name   : void COMMON_Ascii2Hex(INT8U * p_fDst, INT8U * p_fSrc, \                      */
/*                                              INT8U u8_fLength)                                 */
/*                                                                                                */
/* Description     : Convert ASCII to Hex                                                         */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/
    
void COMMON_Ascii2Hex(INT8U * p_fDst, INT8U * p_fSrc, INT8U u8_fLength)
{
    INT8U u8_lIndex1 = 0;
    INT8U u8_lIndex2;

    *p_fDst = 0x00000000;

    for(u8_lIndex2 = 0; u8_lIndex2 < u8_fLength; u8_lIndex2 = u8_lIndex2 + 2)
    {
        if(*(p_fSrc + u8_lIndex2) > 0x39)
        {
            *(p_fDst + u8_lIndex1) = (INT8U)(((*(p_fSrc + u8_lIndex2) - 0x37) << 4));
        }
        else
        {
            *(p_fDst + u8_lIndex1) = (INT8U)(((*(p_fSrc + u8_lIndex2) - 0x30) << 4));
        }
        if(*(p_fSrc + u8_lIndex2 + 1) > 0x39)
        {
            *(p_fDst + u8_lIndex1) |= (INT8U)((*(p_fSrc + u8_lIndex2 + 1) - 0x37));
        }
        else
        {
            *(p_fDst + u8_lIndex1) |= (INT8U)((*(p_fSrc + u8_lIndex2 + 1) - 0x30));
        }
        u8_lIndex1 = u8_lIndex1 + 1;
    }
}

/**************************************************************************************************/
/* Function Name   : void COMMON_Hex2Ascii(INT8U * p_fDst, INT8U * p_fSrc,                        */
/*                                               INT8U u8_fLength)                                */
/*                                                                                                */
/* Description     : Convert to Hex to Ascii                                                      */
/*                                                                                                */
/* In Params       : None                                                                         */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : METER_BUS_RESULT ( return 1 for Success, 0 for Failure )                     */
/**************************************************************************************************/
    
void COMMON_Hex2Ascii(INT8U * p_fDst, INT8U * p_fSrc, INT8U u8_fLength)
{
     INT8U u8_lIndex1;
    INT8U u8_lIndex2 = 0;
    INT8U u8_lTemp;

    for(u8_lIndex1 = 0; u8_lIndex1 < u8_fLength; u8_lIndex1++)
    {
        u8_lTemp = *(p_fSrc + u8_lIndex1);
        if((u8_lTemp & 0x0F) > 0x09)
        {
            *(p_fDst + u8_lIndex2 + 1) = (INT8U)(0x40 + ((u8_lTemp & 0x0F) - 0x09));
        }
        else
        {
            *(p_fDst + u8_lIndex2 + 1) = (INT8U)(( u8_lTemp & 0x0F) + 0x30);
        }
        u8_lTemp = u8_lTemp >> 4;

        if((u8_lTemp & 0x0F) > 0x09)
        {
            *(p_fDst + u8_lIndex2) = (INT8U)(0x40 + ((u8_lTemp & 0x0F) - 0x09));
        }
        else
        {
            *(p_fDst + u8_lIndex2) = (INT8U)((u8_lTemp & 0x0F) + 0x30);
        }

        u8_lIndex2 = u8_lIndex2 + 2;
    }
}

/**************************************************************************************************/
/* Function Name   : void COMMON_UnPackData(INT8U * p_fInput, INT32U u32_fLength)                       */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

EN_COMMON_RESULT_t COMMON_UnPackData(INT8U * p_fInput, INT32U u32_fLength,  ST_FOTA_PACKET_t *p_fOutput)
{
    /* Enum to Hold Result */
    EN_COMMON_RESULT_t en_lResult = COMMON_OK;

    /* Get the Sequence Number */
    if(COMMON_OK != COMMON_PAN2HWord(&p_fInput[0], &p_fOutput->u16_mSeqNumber))
    {
        /* Update the Error Result */
        en_lResult = COMMON_ERROR;
    }
    else
    {
        if(PNULL != strstr((const char *)&p_fInput[0], "END"))
        {
            /* Do Nothing End Frame is Received */
        }
        else
        {
            /* Get the Data 3(: & \r\n) + 8 (SEQ = 4 + Checksum = 4) */
            if(COMMON_OK != COMMON_PAN2ByteArray(&p_fInput[4], &(p_fOutput->au8_mPayload[0]), \
                                                                        ((u32_fLength - 4)/2)))
            {
                /* Update the Error Result */
                en_lResult = COMMON_ERROR;
            }
        }
        
        p_fOutput->u32_mDataLength = ((u32_fLength - 4)/2);
        
    }
    
    /* Return the Result */
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

void COMMON_ResultPackData(INT16U u16_fSeqNumber, EN_RESULT_TYPE_t en_fResult, INT8U *Output)
{
    INT8U au8_lSeqNumber[4] = {0, };
    INT16U u16_lChecksum = 0;
    INT8U au8_lCheckSum[4] = {0, };
    
    /* Append Start Preable */
    Output[0] = 0x3A;
    
    /* Convert Sequence Number and Append Sequence Number*/
    COMMON_HWord2PAN(&au8_lSeqNumber[0], u16_fSeqNumber);
    memcpy(&Output[1], &au8_lSeqNumber[0], 4);
    
    /* Append Result */
    if(ACKW == en_fResult)
    {
        /* Append 0x06 */
        Output[5] = 0x06;
    }
    else
    {
        /* Append 0x15 */
        Output[5] = 0x15;
    }
    
    /* Get the Checksum Append Checksum */
    u16_lChecksum = COMMON_GetCheckSum(&Output[1], strlen((const char *)&Output[1]));
    
    /* Append Checksum */
    COMMON_HWord2PAN(&au8_lCheckSum[0], u16_lChecksum);
    memcpy(&Output[6], &au8_lCheckSum[0], 4);
    
    /* Append End Preamble */
    memcpy(&Output[10], "\r\n", 2);
}


/**************************************************************************************************/
/* Function Name   : INT16U COMMON_GetCheckSum(INT8U * p_fInput, INT32U u32_fLength)                       */
/*                                                                                                */
/* Description     :                                                                              */
/*                                                                                                */
/* In Params       :                                                                              */
/*                                                                                                */
/* Out Params      :                                                                              */
/*                                                                                                */
/* Return Value    :                                                                              */
/**************************************************************************************************/

INT16U COMMON_GetCheckSum(INT8U * p_fInput, INT32U u32_fLength)
{
    /* To Hold Checksum */
    INT16U u16_lCheckSum = 0;
    
    /* To Perform 16bit operation */
    INT16U u16_lTemp = 0;
    
    /* To Perform 8bit operation */
    INT8U u8_lTemp = 0;
    INT8U u8_lTemp1 = 0;
    
    /* Variable to Hold Sum */
    INT32U u32_lSum = 0;
    
    /* For Looping Purpose */
    INT32U u32_lIndex = 0;
    
    /* Calculate Sum */
    for(u32_lIndex = 0; u32_lIndex < u32_fLength; u32_lIndex++)
    {
        u32_lSum = (u32_lSum + p_fInput[u32_lIndex]);
    }
    
    /* Get First 16bits */
    u16_lTemp = (INT16U)(u32_lSum & 0x0000FFFF);
    
    /* Get 2's Complement */
    u16_lTemp = ((~u16_lTemp) + 1);
    
    /* Get First 8bits */
    u8_lTemp = (u16_lTemp & 0x00FF);
    
    /* Hold 8bit as msb */
    u16_lCheckSum = (INT16U)u8_lTemp;
    u16_lCheckSum = (INT16U)(u16_lCheckSum << 8);
    
    /* Invert First Byte */
    u8_lTemp1 = (INT8U)(~u8_lTemp);
    
    /* Append First 8bits */
    u16_lCheckSum = (INT16U)(u16_lCheckSum | (INT16U)u8_lTemp1);
    
    /* Return Checksum */
    return u16_lCheckSum;
}


/**************************************************************************************************/
/* End of Common.c                                                                                */
/**************************************************************************************************/

