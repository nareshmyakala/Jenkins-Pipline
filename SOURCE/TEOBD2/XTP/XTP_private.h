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
/* \File Name   : XTCOM_Priv.h                                                                    */
/* \Author      : SRIKANTH                                                                        */
/* \Version 	:                                                                                 */
/* \Date        : 08-12-2016                                                                      */
/*                                                                                                */
/* @Description :                                                                                 */
/**************************************************************************************************/

#ifndef _XTCOM_PRIV_H_
#define _XTCOM_PRIV_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

/**************************************************************************************************/
/* Private Global Definitions Section                                                             */
/**************************************************************************************************/

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

#define TE_SERIAL_NUMBER	        ( "TE0000000001\r\n" )
#define TE_FIRMWARE_VERSION	        ( "iConnect v1.0\r\n" )
#define TE_DEFAULT_BAUDRATE	        ( 115200 )
#define TE_INITIALIZE_DATE	        ( "03/12/2015\r\n" )
#define	TE_DEFAULT_PROTOCOL	        ( '6' )
#define TE_DEVICE_ID_STRING	        ( "iConnect v1.0\r\n" )

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

/* */
static void XTP_RemoveSpaces(INT8U *p_fSrc , INT16U *p_fLength);

/* */
static void XTP_SmallToCaps(INT8U *p_fSrc , INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t XTP_CheckForDataFrame(const INT8U *p_fSrc,  INT16U *p_fLength);

/* */
static EN_XTCOM_RESULT_t XTP_ProcessCommand(const INT8U *p_fSrc , INT16U u16_fLength);

/* */
extern EN_XTCOM_RESULT_t XTP_ProcessData(const INT8U *p_fSrc , INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t XTP_ExecuteCommand( const INT8U *p_fSrc , INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t Special_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t Z_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t W_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t V_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t T_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t S_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t R_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t P_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t N_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t M_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t L_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t K_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t J_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t I_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t H_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t F_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t E_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t D_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t C_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t B_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_XTCOM_RESULT_t A_GrpupCommands(const INT8U *p_fSrc, const INT16U u16_fLength);

/* */
static EN_CMD_TYPE_t XTP_Check_AT_ST_XT( const INT8U *p_fSrc, const INT16U u16_fLength);

#endif

/**************************************************************************************************/
/* End of XTCOM_Priv.h                                                                            */
/**************************************************************************************************/

