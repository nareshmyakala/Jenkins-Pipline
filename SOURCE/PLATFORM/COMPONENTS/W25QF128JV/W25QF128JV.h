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
/*  File Name   : W25QF128JV.h                                                                    */
/*  Author      : Yashwanth                                                                       */
/*  Version 	: 1.0                                                                             */
/*  Date        : 09-04-2018                                                                      */
/*                                                                                                */
/* @Description : W25Q128JV Serial Flash Driver                                                   */
/**************************************************************************************************/

#ifndef _W25QF128JV_PUBLIC_H_
#define _W25QF128JV_PUBLIC_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"
#include "SPI.h"

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* Export Global Definitions Section                                                              */
/**************************************************************************************************/

typedef enum
{
    W25Q128JV_FAILURE = 0x00,
    W25Q128JV_SUCCESS
}EN_W25Q128JV_STATUS_t;

typedef enum
{
    W25Q128JV_NO_WRITE_IN_PROGRESS = 0x00,
    W25Q128JV_WRITE_IN_PROGRESS
}EN_W25Q128JV_WRITE_PROGRESS_t;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/*  */
extern EN_W25Q128JV_STATUS_t W25Q128JV_Init(void);

/*  */
extern EN_W25Q128JV_STATUS_t w25q128jvDrvWriteData(INT32U u32_fAddr, INT8U *p_fSrcBuff, INT16U u16_fLen);

/*  */
extern EN_W25Q128JV_STATUS_t w25q128jvDrvReadData(INT32U u32_fAddr, INT8U *p_fDstBuff, INT32U u16_fLen);

/*  */
extern EN_W25Q128JV_STATUS_t w25q128jvDrvProgramPage(INT32U u32_fAddr, INT8U *p_fSrcBuff, INT16U u16_fLen);

/*  */
extern INT8U w25q128jvDrvReadStatusReg(void);

/*  */
extern void w25q128jvDrvWriteEnable(void);

/*  */
extern void w25q128jvDrvWriteDisable(void);

/*  */
extern EN_W25Q128JV_WRITE_PROGRESS_t w25q128jvDrvWriteInProgress(void);

/*  */
extern INT8U w25q128jvDrvWriteRegister(void);

/*  */
extern EN_W25Q128JV_STATUS_t w25q128jvDrvBulkErase(void);

/*  */
extern EN_W25Q128JV_STATUS_t w25q128jvDrv4KBSectorErase(INT32U u32_fAddr);

/*  */
extern EN_W25Q128JV_STATUS_t w25q128jvDrv32KBSectorErase(INT32U u32_fAddr);

/*  */
extern  EN_W25Q128JV_STATUS_t w25q128jvDrv64KBSectorErase(INT32U u32_fAddr);
       
/*  */
extern EN_W25Q128JV_STATUS_t w25q128jvDrvReadManufactureId(void);

/*  */
extern INT8U w25q128jvDrvTransferByte(EN_SPI_SERCOM_CH_SEL_t en_fChSel, INT8U u8_fData);

extern INT8U w25q128jvDrvTransferByte(EN_SPI_SERCOM_CH_SEL_t en_fChSel, INT8U u8_fData);

/*  */
extern INT8U w25q128jvDrvTransferLastByte(EN_SPI_SERCOM_CH_SEL_t en_fChSel, INT8U u8_fData);


#endif

/**************************************************************************************************/
/* End of  W25QF128FW.h                                                                    */
/**************************************************************************************************/
