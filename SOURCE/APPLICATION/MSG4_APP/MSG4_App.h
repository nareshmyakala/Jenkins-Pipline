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
/*  File Name   : MSG4_App.h                                                                      */
/*  Author      : NAGANJALI.K                                                                     */
/*  Version 	: v1.0                                                                            */
/*  Date        : 01-02-2022                                                                      */
/*                                                                                                */
/* @Description : MSG4_App Driver Frame Work                                                      */
/**************************************************************************************************/

#ifndef _MSG4_APP_H_
#define _MSG4_APP_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "GPIO.h"
#include "CAN_IF.h"

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

/* Macros For WIFI and Authentication LED */
#define  AUTHNTCTN_LED_PORT                        ( GPIO_PORT_B ) 
#define  AUTHNTCTN_LED_PIN                         ( GPIO_PIN_13 ) 

#define  WIFI_LED_PORT                             ( GPIO_PORT_B ) 
#define  WIFI_LED_PIN                              ( GPIO_PIN_12 ) 

#define SET_PIN(X,Y)                               ( GPIO_SetPin(X ,Y) )
#define RESSET_PIN(X,Y)                            ( GPIO_ResetPin(X ,Y) )

/* Macros for to maintain Secuirty Variable Addresses */
#define INTERNAL_EEPRM_START_ADD                   ( 0x0007C000 )

#define FLAH_BOOTLADER_BASE                        ( 0x0007C000 + 60 )
#define FLASH_BOOTLOADER_BASE1                     ( FLAH_BOOTLADER_BASE + 1 )
#define SSID_NAME                                  ( FLASH_BOOTLOADER_BASE1 + 5 )
#define IP_ADDRS                                   ( SSID_NAME + 20 )
#define EEPROM_BOOT_STATUS_BASEADDR		           ( IP_ADDRS + 25 )
#define EEPROM_TRIPLEDES_KEY_BASEADDR			   ( EEPROM_BOOT_STATUS_BASEADDR + 1 )
#define EEPROM_MSG2PROREFDATA_BASEADDR			   ( EEPROM_TRIPLEDES_KEY_BASEADDR + 24 )
#define EEPROM_MSG2PROSEQ_DATA_BASEADDR			   ( EEPROM_MSG2PROREFDATA_BASEADDR + 24 )
#define EEPROM_SERIAL_BASE_ADDR				       ( EEPROM_MSG2PROSEQ_DATA_BASEADDR + 24 )
#define EEPROM_KEY_LERANT_STATUS_BASE_ADDR		   ( EEPROM_SERIAL_BASE_ADDR + 12)
#define EEPROM_MANUFACTURE_DATE_BASE_ADDR		   ( EEPROM_KEY_LERANT_STATUS_BASE_ADDR + 4)
#define EEPROM_SOFTWARE_VERSION_BASE_ADDR		   ( EEPROM_MANUFACTURE_DATE_BASE_ADDR + 3)
#define EEPROM_NONCE_BASE_ADDR			           ( EEPROM_SOFTWARE_VERSION_BASE_ADDR + 8)
#define EEPROM_EMSFLSH_START_ADDR			       ( EEPROM_NONCE_BASE_ADDR + 4)
#define EEPROM_EMSFLSH_END_ADDR 		           ( EEPROM_EMSFLSH_START_ADDR + 4)

#define EEPROM_CH1_FACTOR         		           ( EEPROM_EMSFLSH_START_ADDR + 4)
#define EEPROM_CH2_FACTOR 		                   ( EEPROM_CH1_FACTOR + 8)
#define EEPROM_CH3_FACTOR 		                   ( EEPROM_CH2_FACTOR + 8)
#define EEPROM_CH4_FACTOR 		                   ( EEPROM_CH3_FACTOR + 8)
#define EEPROM_CH5_FACTOR 		                   ( EEPROM_CH4_FACTOR + 8)

#define TE_VCI_BOOTLOEADER_VRSN 		            ( EEPROM_CH5_FACTOR + 10) //EX- TE_V1.2
#define CONNECTR_SERIL_NUMBER 		                ( TE_VCI_BOOTLOEADER_VRSN + 20) //EX- YY MM CC Z XXXXX

/* Buffer Sizes */
#define SERIAL_NUMBER_SIZE	( 15 )
#define FIRMWARE_SIZE		( 13 )
#define BAUDRATE_SIZE		( 4 )
#define INIT_DATE_SIZE		( 12 )
#define	CUR_PROTOCOL_SIZE	( 1 )
#define HARDWARE_ID_SIZE	( 16 )
#define SAVE_DATA_SIZE      ( 1 )


/* Enum to Hold Result */
typedef enum 
{
    STATE_ERROR = 0x00,
    STATE_SUCCESS
        
}EN_STATE_RESULT_t;


/* OBD States List */
typedef enum
{
    BOOTUP,
    AUTHENTICATION,
    PASSTHRU,
    IGN_ON,
    IGN_OFF,
    MSG4_ERROR,
    MSG4_IDLE,
    MSG2_MAX_STATES
 
}EN_STATE_LIST_t;


/* FSM State Definition */
typedef struct
{
    void (*fp_mStateInit)(void);
    void (*fp_mStateHandler)(EN_STATE_LIST_t *pu8_State);
    void (*fp_mStateExit)(void);
    
}ST_STATES_t;

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

extern EN_STATE_LIST_t en_gCurrState;

/* */
extern INT8U u8_gAuthCompltedFlag;

/* STN data length */
extern INT32U u32_gStnDataLength;

/* Flag to know is there data from STN */
extern INT8U u8_gIsDataFromStn;

/* Flag to know is there data from Wifi */
extern INT8U u8_gIsDataFromWifi;

extern INT32U u32_g1ms_Countr;

extern INT8U u8_gSTNMntrFlag;

extern ST_CAN_MO_CFG_t ISOTP_canInit[3];

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Stack Initialization */
extern void MSG4_AppInit(void);

extern void MSG2PRO_SwitchState(INT8U en_fState);

/* */
void FirstBootCheck(void);

extern EN_STATE_LIST_t MSG2PRO_GetCurrentState(void);

/* */
extern void MSG4_1MsHandler(void);

/* MSG4 Rx Confirmation */
extern void MSG4_IsotpRxConfirmation(INT32U u32_fCanId, INT8U *pu8_fData, INT32U u32_fLength);

extern void MSG4_IsotpTxConfirmation(INT32U u32_fData);

extern void MSG4_IsotpErrorConfirmation(INT8U u8_fError);
 
#endif

/**************************************************************************************************/
/* End of  MSG4_App.h                                                                             */
/**************************************************************************************************/
