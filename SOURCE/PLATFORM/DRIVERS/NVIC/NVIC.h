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
/* \File Name   :  NVIC.h                                                                         */
/* \Author      :  Salman Ali                                                                     */
/* \Version     :  1.0                                                                            */
/* \Date        :  19/12/2015                                                                     */
/* @Description :  NVIC Framework                                                                 */
/**************************************************************************************************/

#ifndef _NVIC_H_
#define _NVIC_H_

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

/**************************************************************************************************/
/* Export Global Variables Section                                                                */
/**************************************************************************************************/

typedef enum
{
	/******  Cortex-M4 Processor Exceptions Numbers ******************************/
	NonMaskableInt_IRQ      = -14,/**<  2 Non Maskable Interrupt                */
	HardFault_IRQ           = -13,/**<  3 Cortex-M4 Hard Fault Interrupt        */
	MemoryManagement_IRQ    = -12,/**<  4 Cortex-M4 Memory Management Interrupt */
	BusFault_IRQ            = -11,/**<  5 Cortex-M4 Bus Fault Interrupt         */
	UsageFault_IRQ          = -10,/**<  6 Cortex-M4 Usage Fault Interrupt       */
	SVCall_IRQ              = -5, /**< 11 Cortex-M4 SV Call Interrupt           */
	DebugMonitor_IRQ        = -4, /**< 12 Cortex-M4 Debug Monitor Interrupt     */
	PendSV_IRQ              = -2, /**< 14 Cortex-M4 Pend SV Interrupt           */
	SysTick_IRQ             = -1, /**< 15 Cortex-M4 System Tick Interrupt       */
	/******  SAME51J19A-specific Interrupt Numbers ***********************/
	PM_IRQ                  =  0, /**<  0 SAME51J19A Power Manager (PM) */
	MCLK_IRQ                =  1, /**<  1 SAME51J19A Main Clock (MCLK) */
	OSCCTRL_0_IRQ           =  2, /**<  2 SAME51J19A Oscillators Control (OSCCTRL): OSCCTRL_XOSCFAIL_0, OSCCTRL_XOSCRDY_0 */
	OSCCTRL_1_IRQ           =  3, /**<  3 SAME51J19A Oscillators Control (OSCCTRL): OSCCTRL_XOSCFAIL_1, OSCCTRL_XOSCRDY_1 */
	OSCCTRL_2_IRQ           =  4, /**<  4 SAME51J19A Oscillators Control (OSCCTRL): OSCCTRL_DFLLLOCKC, OSCCTRL_DFLLLOCKF, OSCCTRL_DFLLOOB, OSCCTRL_DFLLRCS, OSCCTRL_DFLLRDY */
	OSCCTRL_3_IRQ           =  5, /**<  5 SAME51J19A Oscillators Control (OSCCTRL): OSCCTRL_DPLLLCKF_0, OSCCTRL_DPLLLCKR_0, OSCCTRL_DPLLLDRTO_0, OSCCTRL_DPLLLTO_0 */
	OSCCTRL_4_IRQ           =  6, /**<  6 SAME51J19A Oscillators Control (OSCCTRL): OSCCTRL_DPLLLCKF_1, OSCCTRL_DPLLLCKR_1, OSCCTRL_DPLLLDRTO_1, OSCCTRL_DPLLLTO_1 */
	OSC32KCTRL_IRQ          =  7, /**<  7 SAME51J19A 32kHz Oscillators Control (OSC32KCTRL) */
	SUPC_0_IRQ              =  8, /**<  8 SAME51J19A Supply Controller (SUPC): SUPC_B12SRDY, SUPC_B33SRDY, SUPC_BOD12RDY, SUPC_BOD33RDY, SUPC_VCORERDY, SUPC_VREGRDY */
	SUPC_1_IRQ              =  9, /**<  9 SAME51J19A Supply Controller (SUPC): SUPC_BOD12DET, SUPC_BOD33DET */
	WDT_IRQ                 = 10, /**< 10 SAME51J19A Watchdog Timer (WDT) */
	RTC_IRQ                 = 11, /**< 11 SAME51J19A Real-Time Counter (RTC) */
	EIC_0_IRQ               = 12, /**< 12 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_0 */
	EIC_1_IRQ               = 13, /**< 13 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_1 */
	EIC_2_IRQ               = 14, /**< 14 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_2 */
	EIC_3_IRQ               = 15, /**< 15 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_3 */
	EIC_4_IRQ               = 16, /**< 16 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_4 */
	EIC_5_IRQ               = 17, /**< 17 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_5 */
	EIC_6_IRQ               = 18, /**< 18 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_6 */
	EIC_7_IRQ               = 19, /**< 19 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_7 */
	EIC_8_IRQ               = 20, /**< 20 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_8 */
	EIC_9_IRQ               = 21, /**< 21 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_9 */
	EIC_10_IRQ              = 22, /**< 22 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_10 */
	EIC_11_IRQ              = 23, /**< 23 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_11 */
	EIC_12_IRQ              = 24, /**< 24 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_12 */
	EIC_13_IRQ              = 25, /**< 25 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_13 */
	EIC_14_IRQ              = 26, /**< 26 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_14 */
	EIC_15_IRQ              = 27, /**< 27 SAME51J19A External Interrupt Controller (EIC): EIC_EXTINT_15 */
	FREQM_IRQ               = 28, /**< 28 SAME51J19A Frequency Meter (FREQM) */
	NVMCTRL_0_IRQ           = 29, /**< 29 SAME51J19A Non-Volatile Memory Controller (NVMCTRL): NVMCTRL_0, NVMCTRL_1, NVMCTRL_2, NVMCTRL_3, NVMCTRL_4, NVMCTRL_5, NVMCTRL_6, NVMCTRL_7 */
	NVMCTRL_1_IRQ           = 30, /**< 30 SAME51J19A Non-Volatile Memory Controller (NVMCTRL): NVMCTRL_10, NVMCTRL_8, NVMCTRL_9 */
	DMAC_0_IRQ              = 31, /**< 31 SAME51J19A Direct Memory Access Controller (DMAC): DMAC_SUSP_0, DMAC_TCMPL_0, DMAC_TERR_0 */
	DMAC_1_IRQ              = 32, /**< 32 SAME51J19A Direct Memory Access Controller (DMAC): DMAC_SUSP_1, DMAC_TCMPL_1, DMAC_TERR_1 */
	DMAC_2_IRQ              = 33, /**< 33 SAME51J19A Direct Memory Access Controller (DMAC): DMAC_SUSP_2, DMAC_TCMPL_2, DMAC_TERR_2 */
	DMAC_3_IRQ              = 34, /**< 34 SAME51J19A Direct Memory Access Controller (DMAC): DMAC_SUSP_3, DMAC_TCMPL_3, DMAC_TERR_3 */
	DMAC_4_IRQ              = 35, /**< 35 SAME51J19A Direct Memory Access Controller (DMAC): DMAC_SUSP_10, DMAC_SUSP_11, DMAC_SUSP_12, DMAC_SUSP_13, DMAC_SUSP_14, DMAC_SUSP_15, DMAC_SUSP_16, DMAC_SUSP_17, DMAC_SUSP_18, DMAC_SUSP_19, DMAC_SUSP_20, DMAC_SUSP_21, DMAC_SUSP_22, DMAC_SUSP_23, DMAC_SUSP_24, DMAC_SUSP_25, DMAC_SUSP_26, DMAC_SUSP_27, DMAC_SUSP_28, DMAC_SUSP_29, DMAC_SUSP_30, DMAC_SUSP_31, DMAC_SUSP_4, DMAC_SUSP_5, DMAC_SUSP_6, DMAC_SUSP_7, DMAC_SUSP_8, DMAC_SUSP_9, DMAC_TCMPL_10, DMAC_TCMPL_11, DMAC_TCMPL_12, DMAC_TCMPL_13, DMAC_TCMPL_14, DMAC_TCMPL_15, DMAC_TCMPL_16, DMAC_TCMPL_17, DMAC_TCMPL_18, DMAC_TCMPL_19, DMAC_TCMPL_20, DMAC_TCMPL_21, DMAC_TCMPL_22, DMAC_TCMPL_23, DMAC_TCMPL_24, DMAC_TCMPL_25, DMAC_TCMPL_26, DMAC_TCMPL_27, DMAC_TCMPL_28, DMAC_TCMPL_29, DMAC_TCMPL_30, DMAC_TCMPL_31, DMAC_TCMPL_4, DMAC_TCMPL_5, DMAC_TCMPL_6, DMAC_TCMPL_7, DMAC_TCMPL_8, DMAC_TCMPL_9, DMAC_TERR_10, DMAC_TERR_11, DMAC_TERR_12, DMAC_TERR_13, DMAC_TERR_14, DMAC_TERR_15, DMAC_TERR_16, DMAC_TERR_17, DMAC_TERR_18, DMAC_TERR_19, DMAC_TERR_20, DMAC_TERR_21, DMAC_TERR_22, DMAC_TERR_23, DMAC_TERR_24, DMAC_TERR_25, DMAC_TERR_26, DMAC_TERR_27, DMAC_TERR_28, DMAC_TERR_29, DMAC_TERR_30, DMAC_TERR_31, DMAC_TERR_4, DMAC_TERR_5, DMAC_TERR_6, DMAC_TERR_7, DMAC_TERR_8, DMAC_TERR_9 */
	EVSYS_0_IRQ             = 36, /**< 36 SAME51J19A Event System Interface (EVSYS): EVSYS_EVD_0, EVSYS_OVR_0 */
	EVSYS_1_IRQ             = 37, /**< 37 SAME51J19A Event System Interface (EVSYS): EVSYS_EVD_1, EVSYS_OVR_1 */
	EVSYS_2_IRQ             = 38, /**< 38 SAME51J19A Event System Interface (EVSYS): EVSYS_EVD_2, EVSYS_OVR_2 */
	EVSYS_3_IRQ             = 39, /**< 39 SAME51J19A Event System Interface (EVSYS): EVSYS_EVD_3, EVSYS_OVR_3 */
	EVSYS_4_IRQ             = 40, /**< 40 SAME51J19A Event System Interface (EVSYS): EVSYS_EVD_10, EVSYS_EVD_11, EVSYS_EVD_4, EVSYS_EVD_5, EVSYS_EVD_6, EVSYS_EVD_7, EVSYS_EVD_8, EVSYS_EVD_9, EVSYS_OVR_10, EVSYS_OVR_11, EVSYS_OVR_4, EVSYS_OVR_5, EVSYS_OVR_6, EVSYS_OVR_7, EVSYS_OVR_8, EVSYS_OVR_9 */
	PAC_IRQ                 = 41, /**< 41 SAME51J19A Peripheral Access Controller (PAC) */
	TAL_0_IRQ               = 42, /**< 42 SAME51J19A Trigger Allocator (TAL): TAL_BRK */
	TAL_1_IRQ               = 43, /**< 43 SAME51J19A Trigger Allocator (TAL): TAL_IPS_0, TAL_IPS_1 */
	RAMECC_IRQ              = 45, /**< 45 SAME51J19A RAM ECC (RAMECC) */
	SERCOM0_0_IRQ           = 46, /**< 46 SAME51J19A Serial Communication Interface 0 (SERCOM0): SERCOM0_0 */
	SERCOM0_1_IRQ           = 47, /**< 47 SAME51J19A Serial Communication Interface 0 (SERCOM0): SERCOM0_1 */
	SERCOM0_2_IRQ           = 48, /**< 48 SAME51J19A Serial Communication Interface 0 (SERCOM0): SERCOM0_2 */
	SERCOM0_3_IRQ           = 49, /**< 49 SAME51J19A Serial Communication Interface 0 (SERCOM0): SERCOM0_3, SERCOM0_4, SERCOM0_5, SERCOM0_6 */
	SERCOM1_0_IRQ           = 50, /**< 50 SAME51J19A Serial Communication Interface 1 (SERCOM1): SERCOM1_0 */
	SERCOM1_1_IRQ           = 51, /**< 51 SAME51J19A Serial Communication Interface 1 (SERCOM1): SERCOM1_1 */
	SERCOM1_2_IRQ           = 52, /**< 52 SAME51J19A Serial Communication Interface 1 (SERCOM1): SERCOM1_2 */
	SERCOM1_3_IRQ           = 53, /**< 53 SAME51J19A Serial Communication Interface 1 (SERCOM1): SERCOM1_3, SERCOM1_4, SERCOM1_5, SERCOM1_6 */
	SERCOM2_0_IRQ           = 54, /**< 54 SAME51J19A Serial Communication Interface 2 (SERCOM2): SERCOM2_0 */
	SERCOM2_1_IRQ           = 55, /**< 55 SAME51J19A Serial Communication Interface 2 (SERCOM2): SERCOM2_1 */
	SERCOM2_2_IRQ           = 56, /**< 56 SAME51J19A Serial Communication Interface 2 (SERCOM2): SERCOM2_2 */
	SERCOM2_3_IRQ           = 57, /**< 57 SAME51J19A Serial Communication Interface 2 (SERCOM2): SERCOM2_3, SERCOM2_4, SERCOM2_5, SERCOM2_6 */
	SERCOM3_0_IRQ           = 58, /**< 58 SAME51J19A Serial Communication Interface 3 (SERCOM3): SERCOM3_0 */
	SERCOM3_1_IRQ           = 59, /**< 59 SAME51J19A Serial Communication Interface 3 (SERCOM3): SERCOM3_1 */
	SERCOM3_2_IRQ           = 60, /**< 60 SAME51J19A Serial Communication Interface 3 (SERCOM3): SERCOM3_2 */
	SERCOM3_3_IRQ           = 61, /**< 61 SAME51J19A Serial Communication Interface 3 (SERCOM3): SERCOM3_3, SERCOM3_4, SERCOM3_5, SERCOM3_6 */
	SERCOM4_0_IRQ           = 62, /**< 62 SAME51J19A Serial Communication Interface 4 (SERCOM4): SERCOM4_0 */
	SERCOM4_1_IRQ           = 63, /**< 63 SAME51J19A Serial Communication Interface 4 (SERCOM4): SERCOM4_1 */
	SERCOM4_2_IRQ           = 64, /**< 64 SAME51J19A Serial Communication Interface 4 (SERCOM4): SERCOM4_2 */
	SERCOM4_3_IRQ           = 65, /**< 65 SAME51J19A Serial Communication Interface 4 (SERCOM4): SERCOM4_3, SERCOM4_4, SERCOM4_5, SERCOM4_6 */
	SERCOM5_0_IRQ           = 66, /**< 66 SAME51J19A Serial Communication Interface 5 (SERCOM5): SERCOM5_0 */
	SERCOM5_1_IRQ           = 67, /**< 67 SAME51J19A Serial Communication Interface 5 (SERCOM5): SERCOM5_1 */
	SERCOM5_2_IRQ           = 68, /**< 68 SAME51J19A Serial Communication Interface 5 (SERCOM5): SERCOM5_2 */
	SERCOM5_3_IRQ           = 69, /**< 69 SAME51J19A Serial Communication Interface 5 (SERCOM5): SERCOM5_3, SERCOM5_4, SERCOM5_5, SERCOM5_6 */
	SERCOM6_0_IRQ       		= 70, /* SERCOM6_0 */ 
	SERCOM6_1_IRQ       		= 71, /* SERCOM6_1 */ 
	SERCOM6_2_IRQ       		= 72, /* SERCOM6_2 */
	SERCOM6_3_IRQ       		= 73, /* SERCOM6_3, SERCOM6_4, SERCOM6_5, SERCOM6_6 */
	SERCOM7_0_IRQ       		= 74, /* SERCOM7_0 */
	SERCOM7_1_IRQ       		= 75, /* SERCOM7_1 */
  SERCOM7_2_IRQ         	= 76, /* SERCOM7_2 */
  SERCOM7_3_IRQ         	= 77, /* SERCOM7_3 */
	CAN0_IRQ                = 78, /**< 78 SAME51J19A Control Area Network 0 (CAN0) */
	CAN1_IRQ                = 79, /**< 79 SAME51J19A Control Area Network 1 (CAN1) */
	USB_0_IRQ               = 80, /**< 80 SAME51J19A Universal Serial Bus (USB): USB_EORSM_DNRSM, USB_EORST_RST, USB_LPMSUSP_DDISC, USB_LPM_DCONN, USB_MSOF, USB_RAMACER, USB_RXSTP_TXSTP_0, USB_RXSTP_TXSTP_1, USB_RXSTP_TXSTP_2, USB_RXSTP_TXSTP_3, USB_RXSTP_TXSTP_4, USB_RXSTP_TXSTP_5, USB_RXSTP_TXSTP_6, USB_RXSTP_TXSTP_7, USB_STALL0_STALL_0, USB_STALL0_STALL_1, USB_STALL0_STALL_2, USB_STALL0_STALL_3, USB_STALL0_STALL_4, USB_STALL0_STALL_5, USB_STALL0_STALL_6, USB_STALL0_STALL_7, USB_STALL1_0, USB_STALL1_1, USB_STALL1_2, USB_STALL1_3, USB_STALL1_4, USB_STALL1_5, USB_STALL1_6, USB_STALL1_7, USB_SUSPEND, USB_TRFAIL0_TRFAIL_0, USB_TRFAIL0_TRFAIL_1, USB_TRFAIL0_TRFAIL_2, USB_TRFAIL0_TRFAIL_3, USB_TRFAIL0_TRFAIL_4, USB_TRFAIL0_TRFAIL_5, USB_TRFAIL0_TRFAIL_6, USB_TRFAIL0_TRFAIL_7, USB_TRFAIL1_PERR_0, USB_TRFAIL1_PERR_1, USB_TRFAIL1_PERR_2, USB_TRFAIL1_PERR_3, USB_TRFAIL1_PERR_4, USB_TRFAIL1_PERR_5, USB_TRFAIL1_PERR_6, USB_TRFAIL1_PERR_7, USB_UPRSM, USB_WAKEUP */
	USB_1_IRQ               = 81, /**< 81 SAME51J19A Universal Serial Bus (USB): USB_SOF_HSOF */
	USB_2_IRQ               = 82, /**< 82 SAME51J19A Universal Serial Bus (USB): USB_TRCPT0_0, USB_TRCPT0_1, USB_TRCPT0_2, USB_TRCPT0_3, USB_TRCPT0_4, USB_TRCPT0_5, USB_TRCPT0_6, USB_TRCPT0_7 */
	USB_3_IRQ               = 83, /**< 83 SAME51J19A Universal Serial Bus (USB): USB_TRCPT1_0, USB_TRCPT1_1, USB_TRCPT1_2, USB_TRCPT1_3, USB_TRCPT1_4, USB_TRCPT1_5, USB_TRCPT1_6, USB_TRCPT1_7 */
	TCC0_0_IRQ              = 85, /**< 85 SAME51J19A Timer Counter Control 0 (TCC0): TCC0_CNT_A, TCC0_DFS_A, TCC0_ERR_A, TCC0_FAULT0_A, TCC0_FAULT1_A, TCC0_FAULTA_A, TCC0_FAULTB_A, TCC0_OVF, TCC0_TRG, TCC0_UFS_A */
	GMAC_IRQ		            = 84, //Ethernet MAC
	TCC0_1_IRQ              = 86, /**< 86 SAME51J19A Timer Counter Control 0 (TCC0): TCC0_MC_0 */
	TCC0_2_IRQ              = 87, /**< 87 SAME51J19A Timer Counter Control 0 (TCC0): TCC0_MC_1 */
	TCC0_3_IRQ              = 88, /**< 88 SAME51J19A Timer Counter Control 0 (TCC0): TCC0_MC_2 */
	TCC0_4_IRQ              = 89, /**< 89 SAME51J19A Timer Counter Control 0 (TCC0): TCC0_MC_3 */
	TCC0_5_IRQ              = 90, /**< 90 SAME51J19A Timer Counter Control 0 (TCC0): TCC0_MC_4 */
	TCC0_6_IRQ              = 91, /**< 91 SAME51J19A Timer Counter Control 0 (TCC0): TCC0_MC_5 */
	TCC1_0_IRQ              = 92, /**< 92 SAME51J19A Timer Counter Control 1 (TCC1): TCC1_CNT_A, TCC1_DFS_A, TCC1_ERR_A, TCC1_FAULT0_A, TCC1_FAULT1_A, TCC1_FAULTA_A, TCC1_FAULTB_A, TCC1_OVF, TCC1_TRG, TCC1_UFS_A */
	TCC1_1_IRQ              = 93, /**< 93 SAME51J19A Timer Counter Control 1 (TCC1): TCC1_MC_0 */
	TCC1_2_IRQ              = 94, /**< 94 SAME51J19A Timer Counter Control 1 (TCC1): TCC1_MC_1 */
	TCC1_3_IRQ              = 95, /**< 95 SAME51J19A Timer Counter Control 1 (TCC1): TCC1_MC_2 */
	TCC1_4_IRQ              = 96, /**< 96 SAME51J19A Timer Counter Control 1 (TCC1): TCC1_MC_3 */
	TCC2_0_IRQ              = 97, /**< 97 SAME51J19A Timer Counter Control 2 (TCC2): TCC2_CNT_A, TCC2_DFS_A, TCC2_ERR_A, TCC2_FAULT0_A, TCC2_FAULT1_A, TCC2_FAULTA_A, TCC2_FAULTB_A, TCC2_OVF, TCC2_TRG, TCC2_UFS_A */
	TCC2_1_IRQ              = 98, /**< 98 SAME51J19A Timer Counter Control 2 (TCC2): TCC2_MC_0 */
	TCC2_2_IRQ              = 99, /**< 99 SAME51J19A Timer Counter Control 2 (TCC2): TCC2_MC_1 */
	TCC2_3_IRQ              = 100, /**< 100 SAME51J19A Timer Counter Control 2 (TCC2): TCC2_MC_2 */
	TCC3_0_IRQ              = 101, /**< 101 SAME51J19A Timer Counter Control 3 (TCC3): TCC3_CNT_A, TCC3_DFS_A, TCC3_ERR_A, TCC3_FAULT0_A, TCC3_FAULT1_A, TCC3_FAULTA_A, TCC3_FAULTB_A, TCC3_OVF, TCC3_TRG, TCC3_UFS_A */
	TCC3_1_IRQ              = 102, /**< 102 SAME51J19A Timer Counter Control 3 (TCC3): TCC3_MC_0 */
	TCC3_2_IRQ              = 103, /**< 103 SAME51J19A Timer Counter Control 3 (TCC3): TCC3_MC_1 */
	TCC4_0_IRQ              = 104, /**< 104 SAME51J19A Timer Counter Control 4 (TCC4): TCC4_CNT_A, TCC4_DFS_A, TCC4_ERR_A, TCC4_FAULT0_A, TCC4_FAULT1_A, TCC4_FAULTA_A, TCC4_FAULTB_A, TCC4_OVF, TCC4_TRG, TCC4_UFS_A */
	TCC4_1_IRQ              = 105, /**< 105 SAME51J19A Timer Counter Control 4 (TCC4): TCC4_MC_0 */
	TCC4_2_IRQ              = 106, /**< 106 SAME51J19A Timer Counter Control 4 (TCC4): TCC4_MC_1 */
	TC0_IRQ                 = 107, /**< 107 SAME51J19A Basic Timer Counter 0 (TC0) */
	TC1_IRQ                 = 108, /**< 108 SAME51J19A Basic Timer Counter 1 (TC1) */
	TC2_IRQ                 = 109, /**< 109 SAME51J19A Basic Timer Counter 2 (TC2) */
	TC3_IRQ                 = 110, /**< 110 SAME51J19A Basic Timer Counter 3 (TC3) */
	TC4_IRQ                 = 111, /**< 111 SAME51J19A Basic Timer Counter 4 (TC4) */
	TC5_IRQ                 = 112, /**< 112 SAME51J19A Basic Timer Counter 5 (TC5) */
	TC6_IRQ			        = 113, /* Basic Timer Counter 6 */
    TC7_IRQ                 = 114, /* Basic Timer Counter 7 */
	PDEC_0_IRQ              = 115, /**< 115 SAME51J19A Quadrature Decodeur (PDEC): PDEC_DIR_A, PDEC_ERR_A, PDEC_OVF, PDEC_VLC_A */
	PDEC_1_IRQ              = 116, /**< 116 SAME51J19A Quadrature Decodeur (PDEC): PDEC_MC_0 */
	PDEC_2_IRQ              = 117, /**< 117 SAME51J19A Quadrature Decodeur (PDEC): PDEC_MC_1 */
	ADC0_0_IRQ              = 118, /**< 118 SAME51J19A Analog Digital Converter 0 (ADC0): ADC0_OVERRUN, ADC0_WINMON */
	ADC0_1_IRQ              = 119, /**< 119 SAME51J19A Analog Digital Converter 0 (ADC0): ADC0_RESRDY */
	ADC1_0_IRQ              = 120, /**< 120 SAME51J19A Analog Digital Converter 1 (ADC1): ADC1_OVERRUN, ADC1_WINMON */
	ADC1_1_IRQ              = 121, /**< 121 SAME51J19A Analog Digital Converter 1 (ADC1): ADC1_RESRDY */
	AC_IRQ                  = 122, /**< 122 SAME51J19A Analog Comparators (AC) */
	DAC_0_IRQ               = 123, /**< 123 SAME51J19A Digital-to-Analog Converter (DAC): DAC_OVERRUN_A_0, DAC_OVERRUN_A_1, DAC_UNDERRUN_A_0, DAC_UNDERRUN_A_1 */
	DAC_1_IRQ               = 124, /**< 124 SAME51J19A Digital-to-Analog Converter (DAC): DAC_EMPTY_0 */
	DAC_2_IRQ               = 125, /**< 125 SAME51J19A Digital-to-Analog Converter (DAC): DAC_EMPTY_1 */
	DAC_3_IRQ               = 126, /**< 126 SAME51J19A Digital-to-Analog Converter (DAC): DAC_RESRDY_0 */
	DAC_4_IRQ               = 127, /**< 127 SAME51J19A Digital-to-Analog Converter (DAC): DAC_RESRDY_1 */
	I2S_IRQ                 = 128, /**< 128 SAME51J19A Inter-IC Sound Interface (I2S) */
	PCC_IRQ                 = 129, /**< 129 SAME51J19A Parallel Capture Controller (PCC) */
	AES_IRQ                 = 130, /**< 130 SAME51J19A Advanced Encryption Standard (AES) */
	TRNG_IRQ                = 131, /**< 131 SAME51J19A True Random Generator (TRNG) */
	ICM_IRQ                 = 132, /**< 132 SAME51J19A Integrity Check Monitor (ICM) */
	PUKCC_IRQ               = 133, /**< 133 SAME51J19A PUblic-Key Cryptography Controller (PUKCC) */
	QSPI_IRQ                = 134, /**< 134 SAME51J19A Quad SPI interface (QSPI) */
	SDHC0_IRQ               = 135, /**< 135 SAME51J19A SD/MMC Host Controller 0 (SDHC0) */
	SDHC1_IRQ            		= 136  /* SD/MMC 1 */
}EN_NVIC_IRQ_t;

/**************************************************************************************************/
/* Export Functions Section                                                                       */
/**************************************************************************************************/

/* Function that enables NVIC interrupt */
extern void NVIC_EnableInterrupt(EN_NVIC_IRQ_t en_fIrqId);

/* Function that disables NVIC interrupt */
extern void NVIC_DisableInterrupt(EN_NVIC_IRQ_t en_fIrqId);

/* defines to set the priority*/
extern void NVIC_SetPriorityTE(EN_NVIC_IRQ_t s8_fIrqId, INT8U u8_fPriority);

/* defines to get priority */
extern INT8U NVIC_GetPriorityTE(EN_NVIC_IRQ_t u8_fPeripheralID);

/* Clears the pending interrupt */
extern void NVIC_ClearPendInterrupt(EN_NVIC_IRQ_t en_fIrqId);

/* defines the pending interrupt */
extern void NVIC_PendInterrupt(EN_NVIC_IRQ_t en_fIrqId);

#endif

/**************************************************************************************************/
/* End of NVIC.h                                                                                  */
/**************************************************************************************************/
