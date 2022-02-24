
/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2015, Think Embedded Pvt. Ltd. (TEPL)  	                  */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : TCC_Priv.h                                                                      */
/* \Author      : Salman Ali                                                                      */
/* \Version 	: 1.0                                                                             */
/* \Date        : 20/11/2015    	                                                          */
/* @Description : TCC Driver Framework                                                            */
/**************************************************************************************************/

#ifndef _TCC_PRIV_H_
#define _TCC_PRIV_H_

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

#define TCC0_BASE_ADDRESS	( 0x41016000 )
#define TCC1_BASE_ADDRESS	( 0x41018000 )
#define TCC2_BASE_ADDRESS	( 0x42000C00 )
#define TCC3_BASE_ADDRESS	( 0x42001000 )
#define TCC4_BASE_ADDRESS       ( 0x43001000 )

#define MAX_TCC_SLICES							    ( 5 )
#define SYSTEM_CLOCK							    ( 120000000 )

#define TCC_SYNC_BUSY_SWRST_MASK                    ( (INT32U)0x00000001 )
#define TCC_SYNC_BUSY_ENABLE_MASK                   ( (INT32U)0x00000002 )
#define TCC_SYNC_BUSY_CTRLB_MASK                    ( (INT32U)0x00000004 )
#define TCC_SYNC_BUSY_STATUS_MASK                   ( (INT32U)0x00000008 )
#define TCC_SYNC_BUSY_COUNT_MASK                    ( (INT32U)0x00000010 )
#define TCC_SYNC_BUSY_PATT_MASK                     ( (INT32U)0x00000020 )
#define TCC_SYNC_BUSY_WAVE_MASK                     ( (INT32U)0x00000040 )
#define TCC_SYNC_BUSY_PER_MASK                      ( (INT32U)0x00000080 )
#define TCC_SYNC_BUSY_CC0_MASK                      ( (INT32U)0x00000100 )
#define TCC_SYNC_BUSY_CC1_MASK                      ( (INT32U)0x00000200 )
#define TCC_SYNC_BUSY_CC2_MASK                      ( (INT32U)0x00000400 )
#define TCC_SYNC_BUSY_CC3_MASK                      ( (INT32U)0x00000800 )
#define TCC_SYNC_BUSY_PATTB_MASK                    ( (INT32U)0x00010000 )
#define TCC_SYNC_BUSY_PERB_MASK                     ( (INT32U)0x00040000 )
#define TCC_SYNC_BUSY_CCB0_MASK                     ( (INT32U)0x00080000 )
#define TCC_SYNC_BUSY_CCB1_MASK                     ( (INT32U)0x00100000 )
#define TCC_SYNC_BUSY_CCB2_MASK                     ( (INT32U)0x00200000 )
#define TCC_SYNC_BUSY_CCB3_MASK                     ( (INT32U)0x00400000 )

/*Masking for Interrupt FLag register */
#define TCC_INTFLAG_OVF_MASK			    ( 0x000001 )
#define TCC_INTFLAG_ERR_MASK			    ( 1 << 3 )
#define TCC_INTFLAG_MC0_MASK			    ( 1 << 16 )
#define TCC_INTFLAG_MC1_MASK                        ( 1 << 17 )
#define TCC_INTFLAG_MC2_MASK                        ( 1 << 18 )
#define TCC_INTFLAG_MC3_MASK                        ( 1 << 19 )
#define TCC_INTFLAG_MC4_MASK                        ( 1 << 20 )
#define TCC_INTFLAG_MC5_MASK                        ( 1 << 21 )


/* Masking for CTRLA register */
#define TCC_CTRLA_PRESCALAR_POS			( 8 )
#define TCC_CTRLA_PRESYNC_PRESC_MASK		( 0x00001000 )
#define TCC_CTRLA_ENABLE_MASK			( 0x00000002 )
#define TCC_CTRLA_SWRST_MASK			( 0x00000001 )
#define TCC_CTRLA_CPTEN0_POS                        ( 24 )
#define TCC_CTRLA_CPTEN1_POS                        ( 25 )
#define TCC_CTRLA_CPTEN2_POS                        ( 26 )
#define TCC_CTRLA_CPTEN3_POS                        ( 27 )


/* Masking for EVCTRL Register */
#define TCC_EVCTRL_PWP_MASK                         ( 0x00000030 )
#define TCC_EVCTRL_PPW_MASK                         ( 0x00000028 )
#define TCC_EVCTRL_TCEI0_MASK                       ( 0x00004000 )
#define TCC_EVCTRL_TCEI1_MASK                       ( 0x00008000 )
#define TCC_EVCTRL_MCEO0_MASK                       ( 0x01000000 )
#define TCC_EVCTRL_MCEO1_MASK                       ( 0x02000000 )
#define TCC_EVCTRL_MCEO2_MASK                       ( 0x04000000 )
#define TCC_EVCTRL_MCEO3_MASK                       ( 0x08000000 )
#define TCC_EVCTRL_MCEI0_MASK                       ( 0x00010000 )
#define TCC_EVCTRL_MCEI1_MASK                       ( 0x00020000 )
#define TCC_EVCTRL_MCEI2_MASK                       ( 0x00040000 )
#define TCC_EVCTRL_MCEI3_MASK                       ( 0x00080000 )

/* Masking for DRVCTRL Register */
#define TCC_DRVCTRL_INVEN0_MASK                     ( 0x00010000 )
#define TCC_DRVCTRL_INVEN1_MASK                     ( 0x00020000 )
#define TCC_DRVCTRL_INVEN2_MASK                     ( 0x00040000 )
#define TCC_DRVCTRL_INVEN3_MASK                     ( 0x00080000 )

/*Masking for SYNCBUSY register */
#define TCC_SYNCBUSY_WAVE_MASK			( 0x40 )
#define TCC_SYNCBUSY_ENABLE_MASK		( 0x02 )
#define TCC_SYNCBUSY_SWRST_MASK			( 0x01 )

/*Masking for CTRLBSET register */
#define TCC_CTRLBSET_CMD_POS			( 5 )

/* Masking for INTENSET register */
#define TCC_INTENSET_MC0_MASK                       ( 0x010000 )
#define TCC_INTENSET_MC1_MASK                       ( 0x020000 )
#define TCC_INTENSET_MC2_MASK                       ( 0x040000 )
#define TCC_INTENSET_MC3_MASK                       ( 0x080000 )

/* Masking for WEXCTRL register */
#define TCC_WEXCTRL_DTLS_POS                        ( 16 )
#define TCC_WEXCTRL_DTHS_POS                        ( 24 )
#define TCC_WEXCTRL_DTIEN0_POS                      ( 8 )
#define TCC_WEXCTRL_DTIEN1_POS                      ( 9 )
#define TCC_WEXCTRL_DTIEN2_POS                      ( 10 )
#define TCC_WEXCTRL_DTIEN3_POS                      ( 11 )


/* TCC System Registers */
typedef struct
{
    SYS_REG          	 CTRLA;       /* Offset: 0x00 (R/W 32) Control A */
    SYS_REG_BYTE         CTRLBCLR;    /* Offset: 0x04 (R/W  8) Control B Clear */
    SYS_REG_BYTE         CTRLBSET;    /* Offset: 0x05 (R/W  8) Control B Set */
    SYS_REG_BYTE         Reserved1[0x2];
    SYS_REG         	 SYNCBUSY;    /* Offset: 0x08 (R/  32) Synchronization Busy */
    SYS_REG          	 FCTRLA;      /* Offset: 0x0C (R/W 32) Recoverable Fault A Configuration */
    SYS_REG          	 FCTRLB;      /* Offset: 0x10 (R/W 32) Recoverable Fault B Configuration */
    SYS_REG              WEXCTRL;     /* Offset: 0x14 (R/W 32) Waveform Extension Configuration */
    SYS_REG         	 DRVCTRL;     /* Offset: 0x18 (R/W 32) Driver Control */
    SYS_REG_BYTE         Reserved2[0x2];
    SYS_REG_BYTE         DBGCTRL;     /* Offset: 0x1E (R/W  8) Debug Control */
    SYS_REG_BYTE         Reserved3[0x1];
    SYS_REG        	 EVCTRL;        /* Offset: 0x20 (R/W 32) Event Control */
    SYS_REG        	 INTENCLR;      /* Offset: 0x24 (R/W 32) Interrupt Enable Clear */
    SYS_REG         	 INTENSET;    /* Offset: 0x28 (R/W 32) Interrupt Enable Set */
    SYS_REG          	 INTFLAG;     /* Offset: 0x2C (R/W 32) Interrupt Flag Status and Clear */
    SYS_REG          	 STATUS;      /* Offset: 0x30 (R/W 32) Status */
    SYS_REG              COUNT;       /* Offset: 0x34 (R/W 32) Count */
    SYS_REG_HWORD        PATT;        /* Offset: 0x38 (R/W 16) Pattern */
    SYS_REG_BYTE         Reserved4[0x2];
    SYS_REG              WAVE;        /* Offset: 0x3C (R/W 32) Waveform Control */
    SYS_REG              PER;         /* Offset: 0x40 (R/W 32) Period */
    SYS_REG              CC[6];       /* Offset: 0x44 (R/W 32) Compare and Capture */
    SYS_REG_BYTE         Reserved5[0x08];
    SYS_REG_HWORD        PATTBUF;     /* Offset: 0x64 (R/W 16) Pattern Buffer */
    SYS_REG_BYTE         Reserved6[0x6];
    SYS_REG              PERBUF;      /* Offset: 0x6C (R/W 32) Period Buffer */
    SYS_REG              CCBUF[6];    /* Offset: 0x70 (R/W 32) Compare and Capture Buffer */
}ST_TCC_REGS_t;

#endif
/**************************************************************************************************/
/* End of TCC_Priv.h                                                                              */
/**************************************************************************************************/
