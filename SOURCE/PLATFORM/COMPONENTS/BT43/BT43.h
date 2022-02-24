/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2015, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : BT43.h                                                                          */
/* \Author      :                                                                                 */
/* \Version 	:                                                                                 */
/* \Date        : 11-08-2016                                                                      */
/*                                                                                                */
/* @Description : BT43 Frame Work                                                                 */
/**************************************************************************************************/

#ifndef BT43_H_
#define BT43_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "UART.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

#define BT43_CMD_BUFFER_LENGTH  ( 250 )

/* TBUS Buffer Size */
#define BT43_BUFFER_SIZE                 ( 8300 )


#define BTLED_PORT                  GPIO_PORTE 
#define BTLED_PIN                   GPIO_PIN9

/* Enum for BT43 Result */
typedef enum
{
    BT43_ERROR = 0x00,
    BT43_SUCCESS
	
}EN_BT43_RESULT_t;

/* Enum for BT43 Connection Status */
typedef enum
{
	BT43_STATUS_ERROR = 0X00,
    BT43_STATUS_CONNECTED,
    BT43_STATUS_DISCONNECTED
	
}EN_BT43_STATUS_t;

/* Enum for BT43 IOCTRLs */
typedef enum
{
	BT43_IOCTRL_RESET_FIFO,
	BT43_IOCTRL_GET_FIFO_REF,
	BT43_CALL_BACK_REGISTER,
	BT43_IOCTRL_CHANGE_SELF_BAUD,
	BT43_IOCTRL_CHANGE_BT43_BAUD,
    BT43_ENTER_BOOTLOADER,
    BT_SET_RESTYPE,
    
}EN_BT43_IOCTRL_ID_t;

/* Enum to handle responce from wifi */
typedef enum
{
	BT_CRLF,
	BT_STNFLASH
	
}EN_BT_HANDLE_RESP_t;

/**************************************************************************************************/
/* Export Global Variable Section                                                                 */
/**************************************************************************************************/

/* */
extern volatile INT8U u8_gisDataFromBT;

/* */
extern ST_UART_CONFIG_PARAMS_t st_gBT43_UartParams;

/* Buffer for to Store the BT43 MAC Address */
extern INT8U u8_gMAC_ADDRESS[17];

/* Buffer for to Process BT43 MAC and Name */
extern INT8U au8_gBT43CmdRespBuf[BT43_CMD_BUFFER_LENGTH];
extern INT8U u8_gBT43CmdRespIndex;

/* Flag for to Process  BT43 MAC and Name */
extern volatile INT8U u8_gBT43CmdMode;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* */
extern INT8U* BT43_GetFifoRef(INT32U *u32_fDatalength);

/* */
extern void BT43_ResetFifo(void);

/* */
void BT43_RxHandler( INT8U u8_fData);

/* Function That Reset The Buffer */
extern void BT43_ResetCmdRespBuffer(void);

/* Function That Reset The Buffer */
extern void BT43_ResetTbusRXBuffer(void);

/* Function That Transmit The Data to Bluetooth */
extern void BT43_Transmit(INT8U * p_fData, INT32U u32_fLength);

/* Function which Initializes the BT43 */
extern void BT43_Init(void);

/* Function which Sets The BT43 Basic Settings */
extern void BT43_FirstBoot(void);

/* Function which Process The BT43 Mac Address */
extern EN_BT43_RESULT_t BT43_ProcessMAC(INT8U * p_fOutBuffer);

/* Function Which Checks The BT43 Connection Status */
extern EN_BT43_STATUS_t BT43_CheckConnectionStatus(void);

/* Function Which Chnage The BT43 Name */
extern void BT43_ChangeName(INT8U * p_fBuff);

/* Function Which gives The BT43 Mac Address */
extern void BT43_GetMacAddr(INT8U *p_fBuffer);

/* */
extern INT8U BT43_CheckCmdResponse(INT8U * p_fCmdInput, INT8U * p_fCmdResponse);

/* Function to Controll STN */
extern EN_BT43_RESULT_t BT43_Ioctrl(EN_BT43_IOCTRL_ID_t en_fID, void *p_fInData, INT32U u32_fInDataLen,\
													  void *p_fOutData, INT32U *pu32_fOutDataLen);
#endif

/**************************************************************************************************/
/* End of BT43.h                                                                                  */
/**************************************************************************************************/
