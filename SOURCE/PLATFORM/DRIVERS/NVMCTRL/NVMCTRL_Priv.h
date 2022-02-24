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
/*  File Name   : NVMCTRL_Priv.h                                                                  */
/*  Author      : Ravi Ranjan Kumar                                                               */
/*  Version 	: 1.0                                                                             */
/*  Date        : 30-08-2018                                                                      */
/*                                                                                                */
/* @Description : NVM Driver                                                                      */
/**************************************************************************************************/

#ifndef _NVMCTRL_PRIV_H_
#define _NVMCTRL_PRIV_H_

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

#define NVMCTRL_BASE_ADDR                   (0x41004000)


#define NVMCTRL_CTRLA_AUTOWS_OFFSET    		( 2 )
#define NVMCTRL_CTRLA_AUTOWS_MASK			( 0x0004 )
#define NVMCTRL_CTRLA_SUSPEN_OFFSET			( 3 )
#define NVMCTRL_CTRLA_SUSPEN_MASK			( 0x0008 )
#define NVMCTRL_CTRLA_WMODE_OFFSET			( 4 )
#define NVMCTRL_CTRLA_WMODE_MASK			( 0x0030 )
#define NVMCTRL_CTRLA_PRM_OFFSET			( 6 )
#define NVMCTRL_CTRLA_PRM_MASK				( 0x00C0 )
#define NVMCTRL_CTRLA_RWS_OFFSET			( 8 )
#define NVMCTRL_CTRLA_RWS_MASK				( 0x0F00 )
#define NVMCTRL_CTRLA_AHBNS0_OFFSET			( 12 )
#define NVMCTRL_CTRLA_AHBNS0_MASK			( 0x1000 )
#define NVMCTRL_CTRLA_AHBNS1_OFFSET			( 13 )
#define NVMCTRL_CTRLA_AHBNS1_MASK			( 0x2000 )
#define NVMCTRL_CTRLA_CACHEDIS0_OFFSET		( 14 )
#define NVMCTRL_CTRLA_CACHEDIS0_MASK		( 0x4000 )
#define NVMCTRL_CTRLA_CACHEDIS1_OFFSET		( 15)
#define NVMCTRL_CTRLA_CACHEDIS1_MASK		( 0x8000 )

#define NVMCTRL_CTRLB_CMD_OFFSET			( 0 )
#define NVMCTRL_CTRLB_CMD_MASK				( 0x007F )
#define NVMCTRL_CTRLB_CMDEX_OFFSET			( 8 )
#define NVMCTRL_CTRLB_CMDEX_MASK			( 0xFF00 )

#define NVMCTRL_PARAM_NVMP_OFFSET			( 0 )
#define NVMCTRL_PARAM_NVMP_MASK				( 0x0000FFFF )
#define NVMCTRL_PARAM_PSZ_OFFSET			( 16 )
#define NVMCTRL_PARAM_PSZ_MASK				( 0x00070000 )
#define NVMCTRL_PARAM_SEE_OFFSET			( 31 )
#define NVMCTRL_PARAM_SEE_MASK				( 0x80000000 )

#define NVMCTRL_INTENCLR_DONE_OFFSET		( 0 )
#define NVMCTRL_INTENCLR_DONE_MASK			( 0x0001 )
#define NVMCTRL_INTENCLR_ADDRE_OFFSET		( 1 )
#define NVMCTRL_INTENCLR_ADDRE_MASK			( 0x0002 )
#define NVMCTRL_INTENCLR_PROGE_OFFSET		( 2 )
#define NVMCTRL_INTENCLR_PROGE_MASK			( 0x0004 )
#define NVMCTRL_INTENCLR_LOCKE_OFFSET		( 3 )
#define NVMCTRL_INTENCLR_LOCKE_MASK			( 0x0008 )
#define NVMCTRL_INTENCLR_ECCSE_OFFSET		( 4 )
#define NVMCTRL_INTENCLR_ECCSE_MASK			( 0x0010 )
#define NVMCTRL_INTENCLR_ECCDE_OFFSET		( 5 )
#define NVMCTRL_INTENCLR_ECCDE_MASK			( 0x0020 )
#define NVMCTRL_INTENCLR_NVME_OFFSET		( 6 )
#define NVMCTRL_INTENCLR_NVME_MASK			( 0x0040 )
#define NVMCTRL_INTENCLR_SUSP_OFFSET		( 7 )
#define NVMCTRL_INTENCLR_SUSP_MASK			( 0x0080 )
#define NVMCTRL_INTENCLR_SEESFULL_OFFSET	( 8 )
#define NVMCTRL_INTENCLR_SEESFULL_MASK		( 0x0100 )
#define NVMCTRL_INTENCLR_SEESOVF_OFFSET		( 9 )
#define NVMCTRL_INTENCLR_SEESOVF_MASK		( 0x0200 )
#define NVMCTRL_INTENCLR_SEEWRC_OFFSET		( 10 )
#define NVMCTRL_INTENCLR_SEEWRC_MASK		( 0x0400 )

#define NVMCTRL_INTENSET_DONE_OFFSET		( 0 )
#define NVMCTRL_INTENSET_DONE_MASK			( 0x0001 )
#define NVMCTRL_INTENSET_ADDRE_OFFSET		( 1 )
#define NVMCTRL_INTENSET_ADDRE_MASK			( 0x0002 )
#define NVMCTRL_INTENSET_PROGE_OFFSET		( 2 )
#define NVMCTRL_INTENSET_PROGE_MASK			( 0x0004 )
#define NVMCTRL_INTENSET_LOCKE_OFFSET		( 3 )
#define NVMCTRL_INTENSET_LOCKE_MASK			( 0x0008 )
#define NVMCTRL_INTENSET_ECCSE_OFFSET		( 4 )
#define NVMCTRL_INTENSET_ECCSE_MASK			( 0x0010 )
#define NVMCTRL_INTENSET_ECCDE_OFFSET		( 5 )
#define NVMCTRL_INTENSET_ECCDE_MASK			( 0x0020 )
#define NVMCTRL_INTENSET_NVME_OFFSET		( 6 )
#define NVMCTRL_INTENSET_NVME_MASK			( 0x0040 )
#define NVMCTRL_INTENSET_SUSP_OFFSET		( 7 )
#define NVMCTRL_INTENSET_SUSP_MASK			( 0x0080 )
#define NVMCTRL_INTENSET_SEESFULL_OFFSET	( 8 )
#define NVMCTRL_INTENSET_SEESFULL_MASK		( 0x0100 )
#define NVMCTRL_INTENSET_SEESOVF_OFFSET		( 9 )
#define NVMCTRL_INTENSET_SEESOVF_MASK		( 0x0200 )
#define NVMCTRL_INTENSET_SEEWRC_OFFSET		( 10 )
#define NVMCTRL_INTENSET_SEEWRC_MASK		( 0x0400 )

#define NVMCTRL_INTFLAG_DONE_OFFSET			( 0 )
#define NVMCTRL_INTFLAG_DONE_MASK			( 0x0001 )
#define NVMCTRL_INTFLAG_ADDRE_OFFSET		( 1 )
#define NVMCTRL_INTFLAG_ADDRE_MASK			( 0x0002 )
#define NVMCTRL_INTFLAG_PROGE_OFFSET		( 2 )
#define NVMCTRL_INTFLAG_PROGE_MASK			( 0x0004 )
#define NVMCTRL_INTFLAG_LOCKE_OFFSET		( 3 )
#define NVMCTRL_INTFLAG_LOCKE_MASK			( 0x0008 )
#define NVMCTRL_INTFLAG_ECCSE_OFFSET		( 4 )
#define NVMCTRL_INTFLAG_ECCSE_MASK			( 0x0010 )
#define NVMCTRL_INTFLAG_ECCDE_OFFSET		( 5 )
#define NVMCTRL_INTFLAG_ECCDE_MASK			( 0x0020 )
#define NVMCTRL_INTFLAG_NVME_OFFSET			( 6 )
#define NVMCTRL_INTFLAG_NVME_MASK			( 0x0040 )
#define NVMCTRL_INTFLAG_SUSP_OFFSET			( 7 )
#define NVMCTRL_INTFLAG_SUSP_MASK			( 0x0080 )
#define NVMCTRL_INTFLAG_SEESFULL_OFFSET		( 8 )
#define NVMCTRL_INTFLAG_SEESFULL_MASK		( 0x0100 )
#define NVMCTRL_INTFLAG_SEESOVF_OFFSET		( 9 )
#define NVMCTRL_INTFLAG_SEESOVF_MASK		( 0x0200 )
#define NVMCTRL_INTFLAG_SEEWRC_OFFSET		( 10 )
#define NVMCTRL_INTFLAG_SEEWRC_MASK			( 0x0400 )

#define NVMCTRL_STATUS_READY_OFFSET			( 0 )
#define NVMCTRL_STATUS_READY_MASK			( 0x0001 )
#define NVMCTRL_STATUS_PRM_OFFSET			( 1 )
#define NVMCTRL_STATUS_PRM_MASK				( 0x0002 )
#define NVMCTRL_STATUS_LOAD_OFFSET			( 2 )
#define NVMCTRL_STATUS_LOAD_MASK			( 0x0004 )
#define NVMCTRL_STATUS_SUSP_OFFSET			( 3 )
#define NVMCTRL_STATUS_SUSP_MASK			( 0x0008 )
#define NVMCTRL_STATUS_AFIRST_OFFSET		( 4 )
#define NVMCTRL_STATUS_AFIRST_MASK			( 0x0010 )
#define NVMCTRL_STATUS_BPDIS_OFFSET			( 5 )
#define NVMCTRL_STATUS_BPDIS_MASK			( 0x0020 )
#define NVMCTRL_STATUS_BOOTPROT_OFFSET		( 8 )
#define NVMCTRL_STATUS_BOOTPROT_MASK		( 0x0F00 )

#define NVMCTRL_ADDR_OFFSET					( 0 )
#define NVMCTRL_ADDR_MASK					( 0x00FFFFFF )

#define NVMCTRL_RUNLOCK_OFFSET				( 0 )
#define NVMCTRL_RUNLOCK_MASK				( 0xFFFFFFFF )

#define NVMCTRL_RUNLOCK_OFFSET				( 0 )
#define NVMCTRL_RUNLOCK_MASK				( 0xFFFFFFFF )

#define NVMCTRL_PBLDATAn_DATA_OFFSET		( 0 )
#define NVMCTRL_PBLDATAn_DATA_MASK			( 0xFFFFFFFF )

#define NVMCTRL_ECCERR_ADDR_OFFSET			( 0 )
#define NVMCTRL_ECCERR_ADDR_MASK			( 0x00FFFFFF )
#define NVMCTRL_ECCERR_TYPEL_OFFSET			( 28 )
#define NVMCTRL_ECCERR_TYPEL_MASK			( 0x30000000 )
#define NVMCTRL_ECCERR_TYPEH_OFFSET			( 30 )
#define NVMCTRL_ECCERR_TYPEH_MASK			( 0xC0000000 )

#define NVMCTRL_DBGCTRL_ECCDIS_OFFSET		( 0 )
#define NVMCTRL_DBGCTRL_ECCDIS_MASK			( 0x01 )
#define NVMCTRL_DBGCTRL_ECCELOG_OFFSET		( 1 )
#define NVMCTRL_DBGCTRL_ECCLOG_MASK			( 0x02 )

#define NVMCTRL_SEECFG_WMODE_OFFSET			( 0 )
#define NVMCTRL_SEECFG_WMODE_MASK			( 0x01 )
#define NVMCTRL_SEECFG_APRDIS_OFFSET		( 1 )
#define NVMCTRL_SEECFG_APRDIS_MASK			( 0x02 )

#define NVMCTRL_SEESTAT_ASEES_OFFSET		( 0 )
#define NVMCTRL_SEESTAT_ASEES_MASK			( 0x00000001 )
#define NVMCTRL_SEESTAT_LOAD_OFFSET			( 1 )
#define NVMCTRL_SEESTAT_LOAD_MASK			( 0x00000002 )
#define NVMCTRL_SEESTAT_BUSY_OFFSET			( 2 )
#define NVMCTRL_SEESTAT_BUSY_MASK			( 0x00000004 )
#define NVMCTRL_SEESTAT_LOCK_OFFSET			( 3 )
#define NVMCTRL_SEESTAT_LOCK_MASK			( 0x00000008 )
#define NVMCTRL_SEESTAT_RLOCK_OFFSET		( 4 )
#define NVMCTRL_SEESTAT_RLOCK_MASK			( 0x00000010 )
#define NVMCTRL_SEESTAT_SBLK_OFFSET			( 8 )
#define NVMCTRL_SEESTAT_SBLK_MASK			( 0x00000F00 )
#define NVMCTRL_SEESTAT_PSZ_OFFSET			( 16 )
#define NVMCTRL_SEESTAT_PSZ_MASK			( 0x00070000 )

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

typedef struct 
{
	volatile INT16U		CTRLA;       		/* Control A */
	volatile INT8U		Reserved1[0x2];		/* Reserved */
	volatile INT16U		CTRLB;       		/* Control B */
	volatile INT8U		Reserved2[0x2];		/* Reserved */
	SYS_REG        		PARAM;       		/* NVM Parameter */
	volatile INT16U     INTENCLR;    		/* Interrupt Enable Clear */
	volatile INT16U     INTENSET;    		/* Interrupt Enable Set */
	volatile INT16U     INTFLAG;     		/* Interrupt Flag Status and Clear */
	volatile INT16U     STATUS;      		/* Status */
	SYS_REG         	ADDR;        		/* Address */
	SYS_REG      		RUNLOCK;     		/* Lock Section */
	SYS_REG      		PBLDATA[2];  		/* Page Buffer Load Data x */
	SYS_REG       		ECCERR;      		/* ECC Error Status Register */
	volatile INT8U      DBGCTRL;     		/* Debug Control */
	volatile INT8U		Reserved3[0x1];		/* Reserved */
	volatile INT8U		SEECFG;      		/* SmartEEPROM Configuration Register */
	volatile INT8U		Reserved4[0x1];		/* Reserved */
	SYS_REG      		SEESTAT;     		/* SmartEEPROM Status Register */
}ST_NVMCTRL_REG_t;

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

#endif

/**************************************************************************************************/
/* End of  NVMCTRL_Priv.h                                                                         */
/**************************************************************************************************/
