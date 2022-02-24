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
/*  File Name   : TBUS.h                                                                          */
/*  Author      :                                                                                 */
/*  Version 	: v1.0                                                                            */
/*  Date        : 17-02-2022                                                                      */
/*                                                                                                */
/* @Description : TBUS Service Frame Work                                                         */
/**************************************************************************************************/

#ifndef _TBUS_H_
#define _TBUS_H_

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

/* */
#define TBUS_BUFF_SIZE                     ( 8192 )

#define TBUS_MAX_SERVICES                  ( 128 )

#define TBUS_ACK                           ( 0x06 )
#define TBUS_NACK 			   ( 0x15 )

/* SID's LIST of TBUS Handlers */
#define TBUS_AUX_IN_APP                    ( 0x36 )
#define TBUS_RESET_VIC                     ( 0x37 )
//#define MODEM_IF_PING                       ( 0x41 )
#define TBUS_REQ_RESP                      ( 0x42 )
#define TBUS_SLEEP                         ( 0x43 )
#define MSG3_TBUS_EMS_FLASH_STATUS         ( 0x44 )

#define TBUS_REBOOT                        ( 0x38 )
 
#define TBUS_PING                          ( 0x41 )
#define TBUS_START                         ( 0x43 )
#define TBUS_STOP                          ( 0x44 )

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/* Service Structure */
typedef struct
{
    INT8U u8_mSID;	
    INT8U u8_mDID;	
    void (*fp_ServiceHandler)(INT8U, INT8U *, INT16U);
    
}ST_TBUS_SERVICES_t;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* */
extern void TBUS_Init(void);

/* */
extern INT8U TBUS_RegisterHandler(INT8U u8_fSID, INT8U u8_fDID, void (*fp_Handler)(INT8U, INT8U*, INT16U));

/* */
extern void TBUS_RxManager(void);

/* */
extern void TBUS_SendCommand(INT8U u8_fSID, INT8U u8_fDID, INT8U * p_fData, INT16U u16_fDataLen);

/* */
extern void TBUS_ResetHandlers(void);

extern void TBUS_Ping(INT8U u8_fDataID, INT8U *p_fPayload, INT16U u16_fLength);
extern void TBUS_StartScope(INT8U u8_fDataID, INT8U *p_fPayload, INT16U u16_fLength);
extern void TBUS_StopScope(INT8U u8_fDataID, INT8U *p_fPayload, INT16U u16_fLength);

#endif

/**************************************************************************************************/
/* End of  TBUS.h                                                                                 */
/**************************************************************************************************/
