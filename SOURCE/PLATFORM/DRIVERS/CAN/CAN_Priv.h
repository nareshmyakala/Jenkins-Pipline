/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2017, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : CAN_private.h                                                                   */
/* \Author      : Yashwanth                                                                       */
/* \Version 	: v1.0                                                                            */
/* \Date        : 02-01-2018                                                                      */
/*                                                                                                */
/* @Description : CAN Driver Framework                                                            */
/**************************************************************************************************/

#ifndef _CAN_PRIVATE_H_
#define _CAN_PRIVATE_H_

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "includes.h"

/**************************************************************************************************/
/* Private Global Definitions Section                                                             */
/**************************************************************************************************/

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

/* CAN Base Address */
#define CAN0_BASE_ADDR                     ( 0x42000000 )
#define CAN1_BASE_ADDR                     ( 0x42000400 )

/* CAN_CREL Register Bit Masking */
#define CAN_CREL_DAY_MASK                  ( 0x000000FF )
#define CAN_CREL_MON_MASK                  ( 0x0000FF00 )
#define CAN_CREL_YEAR_MASK                 ( 0x000F0000 )
#define CAN_CREL_SUBSTEP_MASK              ( 0x00F00000 )
#define CAN_CREL_STEP_MASK                 ( 0x0F000000 )
#define CAN_CREL_REL_MASK                  ( 0xF0000000 )

/* CAN_DBTP Register Bit Masking */
#define CAN_DBTP_DSJW_MASK                  ( 0x00000007 )
#define CAN_DBTP_DSJW_OFFSET                ( 0 )
#define CAN_DBTP_DTSEG2_MASK                ( 0x000000F0 )
#define CAN_DBTP_DTSEG2_OFFSET              ( 4 )
#define CAN_DBTP_DTSEG1_MASK                ( 0x00001F00 )
#define CAN_DBTP_DTSEG1_OFFSET              ( 8 )
#define CAN_DBTP_DBRP_MASK                  ( 0x001F0000 )
#define CAN_DBTP_DBRP_OFFSET                ( 16 )
#define CAN_DBTP_TDC_MASK                   ( 23 )

/* CAN_TEST Register Bit Masking */
#define CAN_TEST_LBCK_MASK                  ( 0x00000010 )
#define CAN_TEST_TX_MASK                    ( 0x00000020 )
#define CAN_TEST_TX_OFFSET                  ( 5 )
#define CAN_TEST_RX_MASK                    ( 0x00000080 )

/* CAN_CCCR Register Bits Masking */
#define CAN_CCCR_INIT_MASK                 ( 0x00000001 )
#define CAN_CCCR_CCE_MASK                  ( 0x00000002 )
#define CAN_CCCR_ASM_MASK                  ( 0x00000004 )
#define CAN_CCCR_CSA_MASK                  ( 0x00000008 )
#define CAN_CCCR_CSR_MASK                  ( 0x00000010 )
#define CAN_CCCR_MON_MASK                  ( 0x00000020 )
#define CAN_CCCR_DAR_MASK                  ( 0x00000040 )
#define CAN_CCCR_TEST_MASK                 ( 0x00000080 )
#define CAN_CCCR_FDOE_MASK                 ( 0x00000100 )
#define CAN_CCCR_BRSE_MASK                 ( 0x00000200 )
#define CAN_CCCR_PXHD_MASK                 ( 0x00001000 )
#define CAN_CCCR_EFBI_MASK                 ( 0x00002000 )
#define CAN_CCCR_TXP_MASK                  ( 0x00004000 )
#define CAN_CCCR_NISO_MASK                 ( 0x00008000 )

/* CAN_NBTP Register Bit Masking */
#define CAN_NBTP_NTSEG2_MASK               ( 0x0000007F )
#define CAN_NBTP_NTSEG2_OFFSET             ( 0 )
#define CAN_NBTP_NTSEG1_MASK               ( 0x0000FF00 )
#define CAN_NBTP_NTSEG1_OFFSET             ( 8 )
#define CAN_NBTP_NBRP_MASK                 ( 0x01FF0000 )
#define CAN_NBTP_NBRP_OFFSET               ( 16 )
#define CAN_NBTP_NSJW_MASK                 ( 0xFC000000 )
#define CAN_NBTP_NSJW_OFFSET               ( 25 )

/* CAN_TSCC Register Bit Masking */
#define CAN_TSCC_TSS_MASK                  ( 0x00000003 )
#define CAN_TSCC_TSS_OFFSET                ( 0 )
#define CAN_TSCC_TCP_MASK                  ( 0x000F0000 )
#define CAN_TSCC_TCP_OFFSET                ( 16 )

/* CAN_ECR Register Bit Masking */
#define CAN_ECR_TEC_MASK                   ( 0x000000FF )
#define CAN_ECR_TEC_OFFSET                 ( 0 )
#define CAN_ECR_REC_MASK                   ( 0x00007F00 )
#define CAN_ECR_REC_OFFSET                 ( 8 )
#define CAN_ECR_CEL_MASK                   ( 0x00FF0000 )
#define CAN_ECR_CEL_OFFSET                 ( 16 )

/* MCNA_PSR Register Bit Masking */
#define CAN_PSR_LEC_MASK                   ( 0x00000007 )
#define CAN_PSR_LEC_OFFSET                 ( 0 )
#define CAN_PSR_ACT_MASK                   ( 0x00000018 )
#define CAN_PSR_ACT_OFFSET                 ( 3 )
#define CAN_PSR_EP_MASK                    ( 0x00000020 )
#define CAN_PSR_EW_MASK                    ( 0x00000040 )
#define CAN_PSR_BO_MASK                    ( 0x00000080 )
#define CAN_PSR_DLEC_MASK                  ( 0x00000700 )
#define CAN_PSR_DLEC_OFFSET                ( 8 )
#define CAN_PSR_RESI_MASK                  ( 0x00000800 )
#define CAN_PSR_RBRS_MASK                  ( 0x00001000 )
#define CAN_PSR_RFDF_MASK                  ( 0x00002000 )
#define CAN_PSR_PXE_MASK                   ( 0x00004000 )
#define CAN_PSR_TDCV_MASK                  ( 0x007F0000 )
#define CAN_PSR_TDCV_OFFSET                ( 16 )

/* CAN_IR Register Bit Masking */
#define CAN_IR_RF0N_MASK                   ( 0x00000001 )
#define CAN_IR_RF0W_MASK                   ( 0x00000002 )
#define CAN_IR_RF0F_MASK                   ( 0x00000004 )
#define CAN_IR_RF0L_MASK                   ( 0x00000008 )
#define CAN_IR_RF1N_MASK                   ( 0x00000010 )
#define CAN_IR_RF1W_MASK                   ( 0x00000020 )
#define CAN_IR_RF1F_MASK                   ( 0x00000040 )
#define CAN_IR_RF1L_MASK                   ( 0x00000080 )
#define CAN_IR_HPM_MASK                    ( 0x00000100 )
#define CAN_IR_TC_MASK                     ( 0x00000200 )
#define CAN_IR_TCF_MASK                    ( 0x00000400 )
#define CAN_IR_TFE_MASK                    ( 0x00000800 )
#define CAN_IR_TEFN_MASK                   ( 0x00001000 )
#define CAN_IR_TEFW_MASK                   ( 0x00002000 )
#define CAN_IR_TEFF_MASK                   ( 0x00004000 )
#define CAN_IR_TEFL_MASK                   ( 0x00008000 )
#define CAN_IR_TSW_MASK                    ( 0x00010000 )
#define CAN_IR_MRAF_MASK                   ( 0x00020000 )
#define CAN_IR_TOO_MASK                    ( 0x00040000 )
#define CAN_IR_DRX_MASK                    ( 0x00080000 )
#define CAN_IR_ELO_MASK                    ( 0x00400000 )
#define CAN_IR_EP_MASK                     ( 0x00800000 )
#define CAN_IR_EW_MASK                     ( 0x01000000 )
#define CAN_IR_BO_MASK                     ( 0x02000000 )
#define CAN_IR_WDI_MASK                    ( 0x04000000 )
#define CAN_IR_PEA_MASK                    ( 0x08000000 )
#define CAN_IR_PED_MASK                    ( 0x10000000 )
#define CAN_IR_ARA_MASK                    ( 0x20000000 )

/* CAN Interrupt Enable Register Bit Masking */
#define CAN_IE_RF0NE_MASK                  ( 0x00000001 )
#define CAN_IE_RF0WE_MASK                  ( 0x00000002 )
#define CAN_IE_RF0F_MASK                   ( 0x00000004 )
#define CAN_IE_RF0LE_MASK                  ( 0x00000008 )
#define CAN_IE_RF1NE_MASK                  ( 0x00000010 )
#define CAN_IE_RF1WE_MASK                  ( 0x00000020 )
#define CAN_IE_RF1FE_MASK                  ( 0x00000040 )
#define CAN_IE_RF1LE_MASK                  ( 0x00000080 )
#define CAN_IE_HPME_MASK                   ( 0x00000100 )
#define CAN_IE_TCE_MASK                    ( 0x00000200 )
#define CAN_IE_TCFE_MASK                   ( 0x00000400 )
#define CAN_IE_TFEE_MASK                   ( 0x00000800 )
#define CAN_IE_TEFNE_MASK                  ( 0x00001000 )
#define CAN_IE_TEFWE_MASK                  ( 0x00002000 )
#define CAN_IE_TEFFE_MASK                  ( 0x00004000 )
#define CAN_IE_TEFLE_MASK                  ( 0x00008000 )
#define CAN_IE_TSWE_MASK                   ( 0x00010000 )
#define CAN_IE_MRAFE_MASK                  ( 0x00020000 )
#define CAN_IE_TOOE_MASK                   ( 0x00040000 )
#define CAN_IE_DRXE_MASK                   ( 0x00080000 )
#define CAN_IE_ELOE_MASK                   ( 0x00400000 )
#define CAN_IE_EPE_MASK                    ( 0x00800000 )
#define CAN_IE_EWE_MASK                    ( 0x01000000 )
#define CAN_IE_BOE_MASK                    ( 0x02000000 )
#define CAN_IE_WDIE_MASK                   ( 0x04000000 )
#define CAN_IE_PEAE_MASK                   ( 0x04000000 )
#define CAN_IE_PEDE_MASK                   ( 0x10000000 )
#define CAN_IE_ARAE_MASK                   ( 0x20000000 )

/* CAN Interrupt Enable Register Bit Masking */
#define CAN_ILS_RF0NL_MASK                 ( 0x00000001 )
#define CAN_ILS_RF0WL_MASK                 ( 0x00000002 )
#define CAN_ILS_RF0FL_MASK                 ( 0x00000004 )
#define CAN_ILS_RF0LL_MASK                 ( 0x00000008 )
#define CAN_ILS_RF1NL_MASK                 ( 0x00000010 )
#define CAN_ILS_RF1WL_MASK                 ( 0x00000020 )
#define CAN_ILS_RF1FL_MASK                 ( 0x00000040 )
#define CAN_ILS_RF1LL_MASK                 ( 0x00000080 )
#define CAN_ILS_HPML_MASK                  ( 0x00000100 )
#define CAN_ILS_TCL_MASK                   ( 0x00000200 )
#define CAN_ILS_TCFL_MASK                  ( 0x00000400 )
#define CAN_ILS_TFEL_MASK                  ( 0x00000800 )
#define CAN_ILS_TEFNL_MASK                 ( 0x00001000 )
#define CAN_ILS_TEFWL_MASK                 ( 0x00002000 )
#define CAN_ILS_TEFFL_MASK                 ( 0x00004000 )
#define CAN_ILS_TEFLL_MASK                 ( 0x00008000 )
#define CAN_ILS_TSWL_MASK                  ( 0x00010000 )
#define CAN_ILS_MRAFL_MASK                 ( 0x00020000 )
#define CAN_ILS_TOOL_MASK                  ( 0x00040000 )
#define CAN_ILS_DRXL_MASK                  ( 0x00080000 )
#define CAN_ILS_ELOL_MASK                  ( 0x00400000 )
#define CAN_ILS_EPL_MASK                   ( 0x00800000 )
#define CAN_ILS_EWL_MASK                   ( 0x01000000 )
#define CAN_ILS_BOL_MASK                   ( 0x02000000 )
#define CAN_ILS_WDIL_MASK                  ( 0x04000000 )
#define CAN_ILS_PEAL_MASK                  ( 0x04000000 )
#define CAN_ILS_PEDL_MASK                  ( 0x10000000 )
#define CAN_ILS_ARAL_MASK                  ( 0x20000000 )

/* CAN_ILE Register Bit Masking */
#define CAN_ILE_EINT0_MASK                 ( 0x00000001 )
#define CAN_ILE_EINT1_MASK                 ( 0x00000002 )

/* CAN_GFC Register Bit Masking */
#define CAN_GFC_RRFE_MASK                  ( 0x00000001 )
#define CAN_GFC_RRFS_MASK                  ( 0x00000002 )
#define CAN_GFC_ANFE_MASK                  ( 0x0000000C )
#define CAN_GFC_ANFE_OFFSET                ( 2 )
#define CAN_GFC_ANFS_MASK                  ( 0x00000030 )
#define CAN_GFC_ANFS_OFFSET                ( 4 )

/* CAN_SIDFC Register Bit Masking */
#define CAN_SIDFC_FLSSA_MASK               ( 0x0000FFFC )
#define CAN_SIDFC_FLSSA_OFFSET             ( 2 )
#define CAN_SIDFC_LSS_MASK                 ( 0x00FF0000 )
#define CAN_SIDFC_LSS_OFFSET               ( 16 )

/* CAN_XIDFC Register Bit Masking */
#define CAN_XIDFC_FLESA_MASK               ( 0x0000FFFC )
#define CAN_XIDFC_FLESA_OFFSET             ( 2 )
#define CAN_XIDFC_LSE_MASK                 ( 0x00FF0000 )
#define CAN_XIDFC_LSE_OFFSET               ( 16 )

/* CAN_XIDAM Register Bit Masking */
#define CAN_XIDMA_EIDM_MASK                ( 0x1FFFFFFF )

/* CAN_HPMS */
#define CAN_HPMS_BIDX_MASK                 ( 0x0000003F )
#define CAN_HPMS_BIDX_OFFSET               ( 0 )
#define CAN_HPMS_MSI_MASK                  ( 0x000000C0 )
#define CAN_HPMS_MSI_OFFSET                ( 6 )
#define CAN_HPMS_FIDX_MASK                 ( 0x00007F00 )
#define CAN_HPMS_FLST_MASK                 ( 0x00008000 )

/* CAN_NDAT1 Register Bit Masking */
#define CAN_NDAT1_ND0_MASK                 ( 0x00000001 )
#define CAN_NDAT1_ND1_MASK                 ( 0x00000002 )
#define CAN_NDAT1_ND2_MASK                 ( 0x00000004 )
#define CAN_NDAT1_ND3_MASK                 ( 0x00000008 )
#define CAN_NDAT1_ND4_MASK                 ( 0x00000010 )
#define CAN_NDAT1_ND5_MASK                 ( 0x00000020 )
#define CAN_NDAT1_ND6_MASK                 ( 0x00000040 )
#define CAN_NDAT1_ND7_MASK                 ( 0x00000080 )
#define CAN_NDAT1_ND8_MASK                 ( 0x00000100 )
#define CAN_NDAT1_ND9_MASK                 ( 0x00000200 )
#define CAN_NDAT1_ND10_MASK                ( 0x00000400 )
#define CAN_NDAT1_ND11_MASK                ( 0x00000800 )
#define CAN_NDAT1_ND12_MASK                ( 0x00001000 )
#define CAN_NDAT1_ND13_MASK                ( 0x00002000 )
#define CAN_NDAT1_ND14_MASK                ( 0x00004000 )
#define CAN_NDAT1_ND15_MASK                ( 0x00008000 )
#define CAN_NDAT1_ND16_MASK                ( 0x00010000 )
#define CAN_NDAT1_ND17_MASK                ( 0x00020000 )
#define CAN_NDAT1_ND18_MASK                ( 0x00040000 )
#define CAN_NDAT1_ND19_MASK                ( 0x00080000 )
#define CAN_NDAT1_ND20_MASK                ( 0x00100000 )
#define CAN_NDAT1_ND21_MASK                ( 0x00200000 )
#define CAN_NDAT1_ND22_MASK                ( 0x00400000 )
#define CAN_NDAT1_ND23_MASK                ( 0x00800000 )
#define CAN_NDAT1_ND24_MASK                ( 0x01000000 )
#define CAN_NDAT1_ND25_MASK                ( 0x02000000 )
#define CAN_NDAT1_ND26_MASK                ( 0x04000000 )
#define CAN_NDAT1_ND27_MASK                ( 0x08000000 )
#define CAN_NDAT1_ND28_MASK                ( 0x10000000 )
#define CAN_NDAT1_ND29_MASK                ( 0x20000000 )
#define CAN_NDAT1_ND30_MASK                ( 0x40000000 )
#define CAN_NDAT1_ND31_MASK                ( 0x80000000 )


/* CAN_NDAT1 Register Bit Masking */
#define CAN_NDAT2_ND32_MASK                ( 0x00000001 )
#define CAN_NDAT2_ND33_MASK                ( 0x00000002 )
#define CAN_NDAT2_ND34_MASK                ( 0x00000004 )
#define CAN_NDAT2_ND35_MASK                ( 0x00000008 )
#define CAN_NDAT2_ND36_MASK                ( 0x00000010 )
#define CAN_NDAT2_ND37_MASK                ( 0x00000020 )
#define CAN_NDAT2_ND38_MASK                ( 0x00000040 )
#define CAN_NDAT2_ND39_MASK                ( 0x00000080 )
#define CAN_NDAT2_ND40_MASK                ( 0x00000100 )
#define CAN_NDAT2_ND41_MASK                ( 0x00000200 )
#define CAN_NDAT2_ND42_MASK                ( 0x00000400 )
#define CAN_NDAT2_ND43_MASK                ( 0x00000800 )
#define CAN_NDAT2_ND44_MASK                ( 0x00001000 )
#define CAN_NDAT2_ND45_MASK                ( 0x00002000 )
#define CAN_NDAT2_ND46_MASK                ( 0x00004000 )
#define CAN_NDAT2_ND47_MASK                ( 0x00008000 )
#define CAN_NDAT2_ND48_MASK                ( 0x00010000 )
#define CAN_NDAT2_ND49_MASK                ( 0x00020000 )
#define CAN_NDAT2_ND50_MASK                ( 0x00040000 )
#define CAN_NDAT2_ND51_MASK                ( 0x00080000 )
#define CAN_NDAT2_ND52_MASK                ( 0x00100000 )
#define CAN_NDAT2_ND53_MASK                ( 0x00200000 )
#define CAN_NDAT2_ND54_MASK                ( 0x00400000 )
#define CAN_NDAT2_ND55_MASK                ( 0x00800000 )
#define CAN_NDAT2_ND56_MASK                ( 0x01000000 )
#define CAN_NDAT2_ND57_MASK                ( 0x02000000 )
#define CAN_NDAT2_ND58_MASK                ( 0x04000000 )
#define CAN_NDAT2_ND59_MASK                ( 0x08000000 )
#define CAN_NDAT2_ND60_MASK                ( 0x10000000 )
#define CAN_NDAT2_ND61_MASK                ( 0x20000000 )
#define CAN_NDAT2_ND62_MASK                ( 0x40000000 )
#define CAN_NDAT2_ND63_MASK                ( 0x80000000 )

/* CAN_RXF0C Register Bit Masking */
#define CAN_RX0FC_F0SA_MASK                ( 0x0000FFFC )
#define CAN_RX0FC_F0SA_OFFSET              ( 2 )
#define CAN_RX0FC_F0S_MASK                 ( 0x007F0000 )
#define CAN_RX0FC_F0S_OFFSET               ( 16 )
#define CAN_RX0FC_F0WM_MASK                ( 0x7F000000 )
#define CAN_RX0FC_F0WM_OFFSET              ( 24 )
#define CAN_RX0FC_F0OM_MASK                ( 0x80000000 )

/* CAN_RXF0S Register Bit Masking */
#define CAN_RXF0S_F0FL_MASK                ( 0x0000007F )
#define CAN_RXF0S_F0FL_OFFSET              ( 0 )
#define CAN_RXF0S_F0GI_MASK                ( 0x00003F00 )
#define CAN_RXF0S_F0GI_OFFSET              ( 8 )
#define CAN_RXF0S_F0PI_MASK                ( 0x003F0000 )
#define CAN_RXF0S_F0PI_OFFSET              ( 16 )
#define CAN_RXF0S_F0F_MASK                 ( 0x01000000 )
#define CAN_RXF0S_RF0L_MASK                ( 0x02000000 )

/* CAN_RXF0A Register Bit Masking */
#define CAN_RXF0A_F0AI_MASK                ( 0x0000003F )

/* CAN_RXF1C Register Bit Masking */
#define CAN_RX1FC_F1SA_MASK                ( 0x0000FFFC )
#define CAN_RX1FC_F1SA_OFFSET              ( 2 )
#define CAN_RX1FC_F1S_MASK                 ( 0x007F0000 )
#define CAN_RX1FC_F1S_OFFSET               ( 16 )
#define CAN_RX1FC_F1WM_MASK                ( 0x7F000000 )
#define CAN_RX1FC_F1WM_OFFSET              ( 24 )
#define CAN_RX1FC_F1OM_MASK                ( 0x80000000 )

/* CAN_RXF1S Register Bit Masking */
#define CAN_RXF1S_F1FL_MASK                ( 0x0000007F )
#define CAN_RXF1S_F1FL_OFFSET              ( 0 )
#define CAN_RXF1S_F1GI_MASK                ( 0x00003F00 )
#define CAN_RXF1S_F1GI_OFFSET              ( 8 )
#define CAN_RXF1S_F1PI_MASK                ( 0x003F0000 )
#define CAN_RXF1S_F1PI_OFFSET              ( 16 )
#define CAN_RXF1S_F1F_MASK                 ( 0x01000000 )
#define CAN_RXF1S_RF1L_MASK                ( 0x02000000 )

/* CAN_RXF1A Register Bit Masking */
#define CAN_RXF1A_F1AI_MASK                ( 0x0000003F )

/* CAN_RXBC Register Bit Masking */
#define CAN_RXBC_RBSA_MASK                 ( 0x0000FFFC )
#define CAN_RXBC_RBSA_OFFSET               ( 2 )

/* CAN_TXBC Register Bit Masking */
#define CAN_TXBC_TBSA_MASK                 ( 0x0000FFFC )
#define CAN_TXBC_TBSA_OFFSET               ( 2 )
#define CAN_TXBC_NDTB_MASK                 ( 0x003F0000 )
#define CAN_TXBC_NDTB_OFFSET               ( 16 )
#define CAN_TXBC_TFQS_MASK                 ( 0x3F000000 )
#define CAN_TXBC_TFQS_OFFSET               ( 24 )
#define CAN_TXBC_TFQM_MASK                 ( 0x40000000 )

/* MCNA_TXESC Register Bit Masking */
#define CAN_TXESC_TBDS_MASK                ( 0x00000007 )
#define CAN_TXESC_TBDS_12_BYTE_MASK        ( 0x00000001 )
#define CAN_TXESC_TBDS_16_BYTE_MASK        ( 0x00000002 )
#define CAN_TXESC_TBDS_20_BYTE_MASK        ( 0x00000003 )
#define CAN_TXESC_TBDS_24_BYTE_MASK        ( 0x00000004 )
#define CAN_TXESC_TBDS_32_BYTE_MASK        ( 0x00000005 )
#define CAN_TXESC_TBDS_48_BYTE_MASK        ( 0x00000006 )
#define CAN_TXESC_TBDS_64_BYTE_MASK        ( 0x00000007 )
#define CAN_TXESC_TBDS_OFFSET              ( 0 )

#define CAN_RXESC_RBDS_MASK                ( 0x00000700 )
#define CAN_RXESC_RBDS_12_BYTE_MASK        ( 0x00000100 )
#define CAN_RXESC_RBDS_16_BYTE_MASK        ( 0x00000200 )
#define CAN_RXESC_RBDS_20_BYTE_MASK        ( 0x00000300 )
#define CAN_RXESC_RBDS_24_BYTE_MASK        ( 0x00000400 )
#define CAN_RXESC_RBDS_32_BYTE_MASK        ( 0x00000500 )
#define CAN_RXESC_RBDS_48_BYTE_MASK        ( 0x00000600 )
#define CAN_RXESC_RBDS_64_BYTE_MASK        ( 0x00000700 )
#define CAN_RXESC_RBDS_OFFSET              ( 8 )
#define CAN_RXESC_F0DS_MASK                ( 0x00000007 )

#define CAN_NBTP_OFFSET             0x1C         /**< \brief (CAN_NBTP offset) Nominal Bit Timing and Prescaler */
#define CAN_NBTP_RESETVALUE         (0x06000A03) /**< \brief (CAN_NBTP reset_value) Nominal Bit Timing and Prescaler */

#define CAN_NBTP_NTSEG2_Pos         0            /**< \brief (CAN_NBTP) Nominal Time segment after sample point */
#define CAN_NBTP_NTSEG2_Msk         ((0x7F) << CAN_NBTP_NTSEG2_Pos)
#define CAN_NBTP_NTSEG2(value)      (CAN_NBTP_NTSEG2_Msk & ((value) << CAN_NBTP_NTSEG2_Pos))
#define CAN_NBTP_NTSEG1_Pos         8            /**< \brief (CAN_NBTP) Nominal Time segment before sample point */
#define CAN_NBTP_NTSEG1_Msk         ((0xFF) << CAN_NBTP_NTSEG1_Pos)
#define CAN_NBTP_NTSEG1(value)      (CAN_NBTP_NTSEG1_Msk & ((value) << CAN_NBTP_NTSEG1_Pos))
#define CAN_NBTP_NBRP_Pos           16           /**< \brief (CAN_NBTP) Nominal Baud Rate Prescaler */
#define CAN_NBTP_NBRP_Msk           ((0x1FF) << CAN_NBTP_NBRP_Pos)
#define CAN_NBTP_NBRP(value)        (CAN_NBTP_NBRP_Msk & ((value) << CAN_NBTP_NBRP_Pos))
#define CAN_NBTP_NSJW_Pos           25           /**< \brief (CAN_NBTP) Nominal (Re)Synchronization Jump Width */
#define CAN_NBTP_NSJW_Msk           ((0x7F) << CAN_NBTP_NSJW_Pos)
#define CAN_NBTP_NSJW(value)        (CAN_NBTP_NSJW_Msk & ((value) << CAN_NBTP_NSJW_Pos))
#define CAN_NBTP_MASK               (0xFFFFFF7F) /**< \brief (CAN_NBTP) MASK Register */

/* CAN Register Strcuture */
typedef struct
{
    SYS_REG     CAN_CREL;
    SYS_REG     CAN_ENDN;
    SYS_REG     CAN_CUST;
    SYS_REG     CAN_DBTP;
    SYS_REG     CAN_TEST;
    SYS_REG     CAN_RWD;
    SYS_REG     CAN_CCCR;
    SYS_REG     CAN_NBTP;
    SYS_REG     CAN_TSCC;
    SYS_REG     CAN_TSCV;
    SYS_REG     CAN_TOCC;
    SYS_REG     CAN_TOCV;
    SYS_REG     RESERVED1[4];
    SYS_REG     CAN_ECR;
    SYS_REG     CAN_PSR;
    SYS_REG     CAN_TDCR;
    SYS_REG     RESERVED2;
    SYS_REG     CAN_IR;
    SYS_REG     CAN_IE;
    SYS_REG     CAN_ILS;
    SYS_REG     CAN_ILE;
    SYS_REG     RESERVED3[8];
    SYS_REG     CAN_GFC;
    SYS_REG     CAN_SIDFC;
    SYS_REG     CAN_XIDFC;
    SYS_REG     RESERVED4;
    SYS_REG     CAN_XIDAM;
    SYS_REG     CAN_HPMS;
    SYS_REG     CAN_NDAT1;
    SYS_REG     CAN_NDAT2;
    SYS_REG     CAN_RXF0C;
    SYS_REG     CAN_RXF0S;
    SYS_REG     CAN_RXF0A;
    SYS_REG     CAN_RXBC;
    SYS_REG     CAN_RXF1C;
    SYS_REG     CAN_RXF1S;
    SYS_REG     CAN_RXF1A;
    SYS_REG     CAN_RXESC;
    SYS_REG     CAN_TXBC;
    SYS_REG     CAN_TXFQS;
    SYS_REG     CAN_TXESC;
    SYS_REG     CAN_TXBRP;
    SYS_REG     CAN_TXBAR;
    SYS_REG     CAN_TXBCR;
    SYS_REG     CAN_TXBTO;
    SYS_REG     CAN_TXBCF;
    SYS_REG     CAN_TXBTIE;
    SYS_REG     CAN_TXBCIE;
    SYS_REG     RESERVED5[2];
    SYS_REG     CAN_TXEFC;
    SYS_REG     CAN_TXEFS;
    SYS_REG     CAN_TXEFA;
}ST_CAN_REGS_t;

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

#endif

/**************************************************************************************************/
/*End of CAN_Priv.h                      			                                              */
/**************************************************************************************************/
