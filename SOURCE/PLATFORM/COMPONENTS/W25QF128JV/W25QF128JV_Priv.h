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
/*  File Name   : W25QF128JV_Priv.h                                                            */
/*  Author      : Yashwanth                                                                       */
/*  Version 	: 1.0                                                                             */
/*  Date        : 09-04-2018                                                                      */
/*                                                                                                */
/* @Description : W25Q128JV Serial Flash Driver                                                   */
/**************************************************************************************************/

#ifndef _W25QF128JV_PRIVATE_H_
#define _W25QF128JV_PRIVATE_H_

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

/* macros for Read Device Identification */
#define W25Q128JV_CM_REMID               ( 0x90 )
#define W25Q128JV_CM_RDID                ( 0x9F )
#define W25Q128JV_CM_RSFDP               ( 0x5A )
#define W25Q128JV_CM_RES                 ( 0xAB )

/* Standard Instruction Macros  */
#define W25Q128JV_CM_READ                ( 0x03 )
#define W25Q128JV_CM_FAST_READ           ( 0x0B )
#define W25Q128JV_CM_DOR                 ( 0x3B )
#define W25Q128JV_CM_QOR                 ( 0x6B )
#define W25Q128JV_CM_DIOR                ( 0xBB )
#define W25Q128JV_CM_QIOR                ( 0xEB )
#define W25Q128JV_CM_PP                  ( 0x02 )

#define W25Q128JV_CM_4KB_SE              ( 0x20 )
#define W25Q128JV_CM_32KB_SE             ( 0x52 )
#define W25Q128JV_CM_64KB_SE             ( 0xD8 )
#define W25Q128JV_CM_BE                  ( 0x60 )

/* Macros for Register Access */
#define W25Q128JV_CM_RDSR1               ( 0x05 )
#define W25Q128JV_CM_RDSR2               ( 0x07 )
#define W25Q128JV_CM_RDCR                ( 0x35 )
#define W25Q128JV_CM_WRR                 ( 0x01 )

#define W25Q128JV_CM_WRDI                ( 0x04 )
#define W25Q128JV_CM_WREN                ( 0x06 )
#define W25Q128JV_CM_WRSR                ( 0x01 )

#define W25Q128JV_DUMMY_DATA             ( 0xFF )

#define W25Q128FJV_MANF_ID               ( 0x17 )



/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

#endif

/**************************************************************************************************/
/* End of  W25QF128FW_Priv.h                                                                   */
/**************************************************************************************************/
