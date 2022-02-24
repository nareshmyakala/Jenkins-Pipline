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
/* \File Name   : ADC_Priv.h                                                                      */
/* \Author      : Ravi Ranjan Kumar                                                               */
/* \Version 	: 1.1                                                                             */
/* \Date        : 10/09/2018                                                                      */
/*                                                                                                */
/* @Description : ADC Driver Framework                                                            */
/**************************************************************************************************/

#ifndef _ADC_PRIV_H_ 
#define _ADC_PRIV_H_ 

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

#define ADC0_BASE_ADDRESS                ( 0x43001C00UL )
#define ADC1_BASE_ADDRESS                ( 0x43002000UL )

#define ADC_MAX_CHANNELS				 ( 16 )

/****************************  ADC CTRLA REGISTER MASKING  ****************************************/
#define ADC_CTRLA_SWRST_Pos          	( 0 )
#define ADC_CTRLA_SWRST_MASK       		( 0x0001 )
#define ADC_CTRLA_ENABLE_Pos          	( 1 )
#define ADC_CTRLA_ENABLE_MASK       	( 0x0002 )
#define ADC_CTRLA_DUALSEL_Pos          	( 3 )
#define ADC_CTRLA_DUALSEL_MASK       	( 0x0018 )
#define ADC_CTRLA_SLAVEEN_Pos          	( 5 )
#define ADC_CTRLA_SLAVEEN_MASK       	( 0x0020 )
#define ADC_CTRLA_RUNSTDBY_Pos         	( 6 )
#define ADC_CTRLA_RUNSTDBY_MASK       	( 0x0040 )
#define ADC_CTRLA_ONDEMAND_Pos         	( 7 )
#define ADC_CTRLA_ONDEMAND_MASK     	( 0x0080 )
#define ADC_CTRLA_PRESCALER_Pos         ( 8 )
#define ADC_CTRLA_PRESCALER_MASK       	( 0x0700 )
#define ADC_CTRLA_R2R_Pos  	        	( 15 )
#define ADC_CTRLA_R2R_MASK       		( 0x1000 )

/********************  ADC REFCTRL REGISTER MASKING  **********************************************/

#define ADC_REFCTRL_REFSEL_Pos          ( 0 )        /* (ADC_REFCTRL) Reference Selection */
#define ADC_REFCTRL_REFSEL_Msk          (0xFul << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL(value)       (ADC_REFCTRL_REFSEL_Msk & ((value) << ADC_REFCTRL_REFSEL_Pos))
#define ADC_REFCTRL_REFSEL_INTREF_Val   ( 0x0ul )    /* (ADC_REFCTRL) Internal Bandgap Reference */
#define ADC_REFCTRL_REFSEL_INTVCC0_Val  ( 0x1ul )    /* (ADC_REFCTRL) 1/1.6 VDDANA */
#define ADC_REFCTRL_REFSEL_INTVCC1_Val  ( 0x2ul )    /* (ADC_REFCTRL) 1/2 VDDANA */
#define ADC_REFCTRL_REFSEL_AREFA_Val    ( 0x3ul )    /* (ADC_REFCTRL) External Reference */
#define ADC_REFCTRL_REFSEL_AREFB_Val    ( 0x4ul )    /* (ADC_REFCTRL) External Reference */
#define ADC_REFCTRL_REFSEL_INTVCC2_Val  ( 0x5ul )    /* (ADC_REFCTRL) VCCANA */
#define ADC_REFCTRL_REFSEL_INTREF       (ADC_REFCTRL_REFSEL_INTREF_Val << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL_INTVCC0      (ADC_REFCTRL_REFSEL_INTVCC0_Val << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL_INTVCC1      (ADC_REFCTRL_REFSEL_INTVCC1_Val << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL_AREFA        (ADC_REFCTRL_REFSEL_AREFA_Val  << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL_AREFB        (ADC_REFCTRL_REFSEL_AREFB_Val  << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL_INTVCC2_MASK (ADC_REFCTRL_REFSEL_INTVCC2_Val << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFCOMP_Pos         ( 7 )            
#define ADC_REFCTRL_REFCOMP             (0x1ul << ADC_REFCTRL_REFCOMP_Pos)
#define ADC_REFCTRL_MASK                ( 0x8Ful )   /* (ADC_REFCTRL) MASK Register */

/********************  ADC EVCTRL REGISTER MASKING  **********************************************/

#define ADC_EVCTRL_FLUSHEI_Pos          ( 0 )        /* (ADC_EVCTRL) Flush Event Input Enable */
#define ADC_EVCTRL_FLUSHEI              (0x1ul << ADC_EVCTRL_FLUSHEI_Pos)
#define ADC_EVCTRL_STARTEI_Pos          ( 1 )        /* Start Conversion Event Input Enable*/
#define ADC_EVCTRL_STARTEI              (0x1ul << ADC_EVCTRL_STARTEI_Pos)
#define ADC_EVCTRL_FLUSHINV_Pos         ( 2 )        /* (ADC_EVCTRL) Flush Event Invert Enable */
#define ADC_EVCTRL_FLUSHINV             (0x1ul << ADC_EVCTRL_FLUSHINV_Pos)
#define ADC_EVCTRL_STARTINV_Pos         ( 3 )        /* (ADC_EVCTRL) Satrt Event Invert Enable */
#define ADC_EVCTRL_STARTINV             (0x1ul << ADC_EVCTRL_STARTINV_Pos)
#define ADC_EVCTRL_RESRDYEO_Pos         ( 4 )        /* (ADC_EVCTRL) Result Ready Event Out */
#define ADC_EVCTRL_RESRDYEO             (0x1ul << ADC_EVCTRL_RESRDYEO_Pos)
#define ADC_EVCTRL_WINMONEO_Pos         ( 5 )        /* (ADC_EVCTRL) Window Monitor Event Out */
#define ADC_EVCTRL_WINMONEO             (0x1ul << ADC_EVCTRL_WINMONEO_Pos)
#define ADC_EVCTRL_MASK                 ( 0x3Ful )   /* (ADC_EVCTRL) MASK Register */

/********************  ADC INTENCLR REGISTER MASKING  ********************************************/

#define ADC_INTENCLR_RESRDY_Pos         ( 0 )        /* Result Ready Interrupt Disable */
#define ADC_INTENCLR_RESRDY             (0x1ul << ADC_INTENCLR_RESRDY_Pos)
#define ADC_INTENCLR_OVERRUN_Pos        ( 1 )        /* (ADC_INTENCLR) Overrun Interrupt Disable */
#define ADC_INTENCLR_OVERRUN            (0x1ul << ADC_INTENCLR_OVERRUN_Pos)
#define ADC_INTENCLR_WINMON_Pos         ( 2 )        /* Window Monitor Interrupt Disable */
#define ADC_INTENCLR_WINMON             (0x1ul << ADC_INTENCLR_WINMON_Pos)
#define ADC_INTENCLR_MASK               ( 0x07ul )   /* (ADC_INTENCLR) MASK Register */

/********************  ADC INTENSET REGISTER MASKING  *********************************************/

#define ADC_INTENSET_RESRDY_Pos         ( 0 )        /* Result Ready Interrupt Enable */
#define ADC_INTENSET_RESRDY_MASK        (0x1ul << ADC_INTENSET_RESRDY_Pos)
#define ADC_INTENSET_OVERRUN_Pos        ( 1 )        /* (ADC_INTENSET) Overrun Interrupt Enable */
#define ADC_INTENSET_OVERRUN_MASK       (0x1ul << ADC_INTENSET_OVERRUN_Pos)
#define ADC_INTENSET_WINMON_Pos         ( 2 )        /* Window Monitor Interrupt Enable */
#define ADC_INTENSET_WINMON             (0x1ul << ADC_INTENSET_WINMON_Pos)
#define ADC_INTENSET_MASK               ( 0x07ul )   /* (ADC_INTENSET) MASK Register */

/********************  ADC INTFLAG REGISTER MASKING  **********************************************/

#define ADC_INTFLAG_RESRDY_Pos          ( 0 )        /* (ADC_INTFLAG) Result Ready Interrupt Flag */
#define ADC_INTFLAG_RESRDY              (0x1ul << ADC_INTFLAG_RESRDY_Pos)
#define ADC_INTFLAG_OVERRUN_Pos         ( 1 )        /* (ADC_INTFLAG) Overrun Interrupt Flag */
#define ADC_INTFLAG_OVERRUN             (0x1ul << ADC_INTFLAG_OVERRUN_Pos)
#define ADC_INTFLAG_WINMON_Pos          ( 2 )        /* Window Monitor Interrupt Flag */
#define ADC_INTFLAG_WINMON              (0x1ul << ADC_INTFLAG_WINMON_Pos)
#define ADC_INTFLAG_MASK                ( 0x07ul )   /* (ADC_INTFLAG) MASK Register */

/********************  ADC INPUTCTRL REGISTER MASKING  *******************************************/

#define ADC_INPUTCTRL_MUXPOS_Pos        ( 0 )        /* Positive Mux Input Selection */
#define ADC_INPUTCTRL_MUXPOS_Msk        (0x1Ful << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS(value)     (ADC_INPUTCTRL_MUXPOS_Msk & ((value) << \
                                                                        ADC_INPUTCTRL_MUXPOS_Pos))
#define ADC_INPUTCTRL_MUXPOS_AIN0_Val   ( 0x0ul )    /* (ADC_INPUTCTRL) ADC AIN0 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN1_Val   ( 0x1ul )    /* (ADC_INPUTCTRL) ADC AIN1 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN2_Val   ( 0x2ul )    /* (ADC_INPUTCTRL) ADC AIN2 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN3_Val   ( 0x3ul )    /* (ADC_INPUTCTRL) ADC AIN3 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN4_Val   ( 0x4ul )    /* (ADC_INPUTCTRL) ADC AIN4 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN5_Val   ( 0x5ul )    /* (ADC_INPUTCTRL) ADC AIN5 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN6_Val   ( 0x6ul )    /* (ADC_INPUTCTRL) ADC AIN6 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN7_Val   ( 0x7ul )    /* (ADC_INPUTCTRL) ADC AIN7 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN8_Val   ( 0x8ul )    /* (ADC_INPUTCTRL) ADC AIN8 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN9_Val   ( 0x9ul )    /* (ADC_INPUTCTRL) ADC AIN9 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN10_Val  ( 0xAul )    /* (ADC_INPUTCTRL) ADC AIN10 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN11_Val  ( 0xBul )    /* (ADC_INPUTCTRL) ADC AIN11 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN12_Val  ( 0xCul )    /* (ADC_INPUTCTRL) ADC AIN12 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN13_Val  ( 0xDul )    /* (ADC_INPUTCTRL) ADC AIN13 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN14_Val  ( 0xEul )    /* (ADC_INPUTCTRL) ADC AIN14 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN15_Val  ( 0xFul )    /* (ADC_INPUTCTRL) ADC AIN15 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN16_Val  ( 0x10ul )   /* (ADC_INPUTCTRL) ADC AIN16 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN17_Val  ( 0x11ul )   /* (ADC_INPUTCTRL) ADC AIN17 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN18_Val  ( 0x12ul )   /* (ADC_INPUTCTRL) ADC AIN18 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN19_Val  ( 0x13ul )   /* (ADC_INPUTCTRL) ADC AIN19 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN20_Val  ( 0x14ul )   /* (ADC_INPUTCTRL) ADC AIN20 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN21_Val  ( 0x15ul )   /* (ADC_INPUTCTRL) ADC AIN21 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN22_Val  ( 0x16ul )   /* (ADC_INPUTCTRL) ADC AIN22 Pin */
#define ADC_INPUTCTRL_MUXPOS_AIN23_Val  ( 0x17ul )   /* (ADC_INPUTCTRL) ADC AIN23 Pin */
#define ADC_INPUTCTRL_MUXPOS_TEMP_Val   ( 0x18ul )   /* (ADC_INPUTCTRL) Temperature Sensor */
#define ADC_INPUTCTRL_MUXPOS_BANDGAP_Val (0x19ul)    /* (ADC_INPUTCTRL) Bandgap Voltage */
#define ADC_INPUTCTRL_MUXPOS_SCALEDCOREVCC_Val ( 0x1Aul ) /* (ADC_INPUTCTRL) 1/4 Scaled Core Supply */
#define ADC_INPUTCTRL_MUXPOS_SCALEDIOVCC_Val ( 0x1Bul )   /* (ADC_INPUTCTRL) 1/4 Scaled I/O Supply */
#define ADC_INPUTCTRL_MUXPOS_DAC_Val    ( 0x1Cul )   /* (ADC_INPUTCTRL) DAC Output */
#define ADC_INPUTCTRL_MUXPOS_SCALEDVBAT_Val ( 0x1Dul ) /* (ADC_INPUTCTRL) 1/4 Scaled VBAT Supply */
#define ADC_INPUTCTRL_MUXPOS_OPAMP01_Val ( 0x1Eul )    /* (ADC_INPUTCTRL) OPAMP0 or OPAMP1 output */
#define ADC_INPUTCTRL_MUXPOS_OPAMP2_Val ( 0x1Ful )   /* (ADC_INPUTCTRL) OPAMP2 output */
#define ADC_INPUTCTRL_MUXPOS_AIN0       (ADC_INPUTCTRL_MUXPOS_AIN0_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN1       (ADC_INPUTCTRL_MUXPOS_AIN1_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN2       (ADC_INPUTCTRL_MUXPOS_AIN2_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN3       (ADC_INPUTCTRL_MUXPOS_AIN3_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN4       (ADC_INPUTCTRL_MUXPOS_AIN4_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN5       (ADC_INPUTCTRL_MUXPOS_AIN5_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN6       (ADC_INPUTCTRL_MUXPOS_AIN6_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN7       (ADC_INPUTCTRL_MUXPOS_AIN7_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN8       (ADC_INPUTCTRL_MUXPOS_AIN8_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN9       (ADC_INPUTCTRL_MUXPOS_AIN9_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN10      (ADC_INPUTCTRL_MUXPOS_AIN10_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN11      (ADC_INPUTCTRL_MUXPOS_AIN11_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN12      (ADC_INPUTCTRL_MUXPOS_AIN12_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN13      (ADC_INPUTCTRL_MUXPOS_AIN13_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN14      (ADC_INPUTCTRL_MUXPOS_AIN14_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN15      (ADC_INPUTCTRL_MUXPOS_AIN15_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN16      (ADC_INPUTCTRL_MUXPOS_AIN16_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN17      (ADC_INPUTCTRL_MUXPOS_AIN17_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN18      (ADC_INPUTCTRL_MUXPOS_AIN18_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN19      (ADC_INPUTCTRL_MUXPOS_AIN19_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN20      (ADC_INPUTCTRL_MUXPOS_AIN20_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN21      (ADC_INPUTCTRL_MUXPOS_AIN21_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN22      (ADC_INPUTCTRL_MUXPOS_AIN22_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN23      (ADC_INPUTCTRL_MUXPOS_AIN23_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_TEMP       (ADC_INPUTCTRL_MUXPOS_TEMP_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_BANDGAP    (ADC_INPUTCTRL_MUXPOS_BANDGAP_Val << \
                                                                        ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_SCALEDCOREVCC (ADC_INPUTCTRL_MUXPOS_SCALEDCOREVCC_Val << \
                                                                        ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_SCALEDIOVCC (ADC_INPUTCTRL_MUXPOS_SCALEDIOVCC_Val << \
                                                                        ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_DAC        (ADC_INPUTCTRL_MUXPOS_DAC_Val  << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_SCALEDVBAT (ADC_INPUTCTRL_MUXPOS_SCALEDVBAT_Val << \
                                                                           ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_OPAMP01    (ADC_INPUTCTRL_MUXPOS_OPAMP01_Val << \
                                                                      ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_OPAMP2     (ADC_INPUTCTRL_MUXPOS_OPAMP2_Val << \
                                                                    ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_DIFFMODE_Pos      ( 7 )
#define ADC_INPUTCTRL_DIFFMODE_Msk      (1 <<  ADC_INPUTCTRL_DIFFMODE_Pos);
#define ADC_INPUTCTRL_MUXNEG_Pos        ( 8        /* (ADC_INPUTCTRL) Negative Mux Input Selection */
#define ADC_INPUTCTRL_MUXNEG_Msk        (0x1Ful << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG(value)     (ADC_INPUTCTRL_MUXNEG_Msk & ((value) << \
                                                            ADC_INPUTCTRL_MUXNEG_Pos))
#define ADC_INPUTCTRL_MUXNEG_AIN0_Val   ( 0x0ul )  /* (ADC_INPUTCTRL) ADC AIN0 Pin */
#define ADC_INPUTCTRL_MUXNEG_AIN1_Val   ( 0x1ul )  /* (ADC_INPUTCTRL) ADC AIN1 Pin */
#define ADC_INPUTCTRL_MUXNEG_AIN2_Val   ( 0x2ul )  /* (ADC_INPUTCTRL) ADC AIN2 Pin */
#define ADC_INPUTCTRL_MUXNEG_AIN3_Val   ( 0x3ul )  /* (ADC_INPUTCTRL) ADC AIN3 Pin */
#define ADC_INPUTCTRL_MUXNEG_AIN4_Val   ( 0x4ul )  /* (ADC_INPUTCTRL) ADC AIN4 Pin */
#define ADC_INPUTCTRL_MUXNEG_AIN5_Val   ( 0x5ul )  /* (ADC_INPUTCTRL) ADC AIN5 Pin */
#define ADC_INPUTCTRL_MUXNEG_AIN6_Val   ( 0x6ul )  /* (ADC_INPUTCTRL) ADC AIN6 Pin */
#define ADC_INPUTCTRL_MUXNEG_AIN7_Val   ( 0x7ul )  /* (ADC_INPUTCTRL) ADC AIN7 Pin */
#define ADC_INPUTCTRL_MUXNEG_AIN0       (ADC_INPUTCTRL_MUXNEG_AIN0_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_AIN1       (ADC_INPUTCTRL_MUXNEG_AIN1_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_AIN2       (ADC_INPUTCTRL_MUXNEG_AIN2_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_AIN3       (ADC_INPUTCTRL_MUXNEG_AIN3_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_AIN4       (ADC_INPUTCTRL_MUXNEG_AIN4_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_AIN5       (ADC_INPUTCTRL_MUXNEG_AIN5_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_AIN6       (ADC_INPUTCTRL_MUXNEG_AIN6_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_AIN7       (ADC_INPUTCTRL_MUXNEG_AIN7_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_DSEQSTOP_Pos      ( 15 )
#define ADC_INPUTCTRL_DSEQSTOP_Msk      (1 <<  ADC_INPUTCTRL_DIFFMODE_Pos);
#define ADC_INPUTCTRL_MASK              ( 0x9F9Ful )  /* (ADC_INPUTCTRL) MASK Register */

/********************  ADC CTRLC REGISTER MASKING  **********************************************/

#define ADC_CTRLB_LEFTADJ_Pos           ( 0         /* (ADC_CTRLB) Left-Adjusted Result */
#define ADC_CTRLB_LEFTADJ               (0x1ul << ADC_CTRLB_LEFTADJ_Pos)
#define ADC_CTRLB_FREERUN_Pos           ( 1         /* (ADC_CTRLB) Free Running Mode */
#define ADC_CTRLB_FREERUN_MASK          (0x1ul << ADC_CTRLB_FREERUN_Pos)
#define ADC_CTRLB_CORREN_Pos            ( 2         /* Digital Correction Logic Enable */
#define ADC_CTRLB_CORREN                (0x1ul << ADC_CTRLB_CORREN_Pos)
#define ADC_CTRLB_RESSEL_Pos            ( 3 )       /* Conversion Result Resolution */
#define ADC_CTRLB_RESSEL_Msk            (0x3ul << ADC_CTRLB_RESSEL_Pos)
#define ADC_CTRLB_RESSEL(value)         (ADC_CTRLB_RESSEL_Msk & ((value) << ADC_CTRLB_RESSEL_Pos))
#define ADC_CTRLB_RESSEL_12BIT_Val      ( 0x0ul )   /* (ADC_CTRLB) 12-bit result */
#define ADC_CTRLB_RESSEL_16BIT_Val      ( 0x1ul )   /* (ADC_CTRLB) For averaging mode output */
#define ADC_CTRLB_RESSEL_10BIT_Val      ( 0x2ul )   /* (ADC_CTRLB) 10-bit result */
#define ADC_CTRLB_RESSEL_8BIT_Val       ( 0x3ul )   /* (ADC_CTRLB) 8-bit result */
#define ADC_CTRLB_RESSEL_12BIT          (ADC_CTRLB_RESSEL_12BIT_Val    << ADC_CTRLB_RESSEL_Pos)
#define ADC_CTRLB_RESSEL_16BIT_MASK     (ADC_CTRLB_RESSEL_16BIT_Val    << ADC_CTRLB_RESSEL_Pos)
#define ADC_CTRLB_RESSEL_10BIT          (ADC_CTRLB_RESSEL_10BIT_Val    << ADC_CTRLB_RESSEL_Pos)
#define ADC_CTRLB_RESSEL_8BIT           (ADC_CTRLB_RESSEL_8BIT_Val     << ADC_CTRLB_RESSEL_Pos)
#define ADC_CTRLB_WINMODE_Pos           ( 8 )       /* (ADC_CTRLB) Window Monitor Mode */
#define ADC_CTRLB_WINMODE_Msk           (0x7ul << ADC_CTRLB_WINMODE_Pos)
#define ADC_CTRLB_WINMODE(value)        (ADC_CTRLB_WINMODE_Msk & ((value) << \
                                                                        ADC_CTRLB_WINMODE_Pos))
#define ADC_CTRLB_WINMODE_DISABLE_Val   ( 0x0ul )  /* (ADC_CTRLB) No window mode (default) */
#define ADC_CTRLB_WINMODE_MODE1_Val     ( 0x1ul )  /* (ADC_CTRLB) RESULT > WINLT */
#define ADC_CTRLB_WINMODE_MODE2_Val     ( 0x2ul )  /* (ADC_CTRLB) RESULT < WINUT */
#define ADC_CTRLB_WINMODE_MODE3_Val     ( 0x3ul )  /* (ADC_CTRLB) WINLT < RESULT < WINUT */
#define ADC_CTRLB_WINMODE_MODE4_Val     ( 0x4ul )  /* (ADC_CTRLB) !(WINLT < RESULT < WINUT) */
#define ADC_CTRLB_WINMODE_DISABLE       (ADC_CTRLB_WINMODE_DISABLE_Val << ADC_CTRLB_WINMODE_Pos)
#define ADC_CTRLB_WINMODE_MODE1         (ADC_CTRLB_WINMODE_MODE1_Val   << ADC_CTRLB_WINMODE_Pos)
#define ADC_CTRLB_WINMODE_MODE2         (ADC_CTRLB_WINMODE_MODE2_Val   << ADC_CTRLB_WINMODE_Pos)
#define ADC_CTRLB_WINMODE_MODE3         (ADC_CTRLB_WINMODE_MODE3_Val   << ADC_CTRLB_WINMODE_Pos)
#define ADC_CTRLB_WINMODE_MODE4         (ADC_CTRLB_WINMODE_MODE4_Val   << ADC_CTRLB_WINMODE_Pos)
#define ADC_CTRLB_WINSS_Pos      ( 11 )
#define ADC_CTRLB_WINSS_Msk      (1 <<  ADC_INPUTCTRL_DIFFMODE_Pos);
#define ADC_CTRLB_MASK                  ( 0x0F1Ful )/* (ADC_CTRLB) MASK Register */

/********************  ADC AVGCTRL REGISTER MASKING  **********************************************/

#define ADC_AVGCTRL_SAMPLENUM_Pos       ( 0 )      /* (ADC_AVGCTRL) Number of Samples Collected */
#define ADC_AVGCTRL_SAMPLENUM_Msk       (0xFul << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_ADJRES_Pos          ( 4 )      /* Adjusting Result / Division Coefficient */
#define ADC_AVGCTRL_ADJRES_Msk          (0x7ul << ADC_AVGCTRL_ADJRES_Pos)
#define ADC_AVGCTRL_ADJRES(value)       (ADC_AVGCTRL_ADJRES_Msk & ((value) << ADC_AVGCTRL_ADJRES_Pos))
#define ADC_AVGCTRL_MASK                ( 0x7Ful ) /* (ADC_AVGCTRL) MASK Register */

/********************  ADC SAMPCTRL REGISTER MASKING  **********************************************/

#define ADC_SAMPCTRL_SAMPLEN_Pos        ( 0 )      /* (ADC_SAMPCTRL) Sampling Time Length */
#define ADC_SAMPCTRL_SAMPLEN_Msk        (0x3Ful << ADC_SAMPCTRL_SAMPLEN_Pos)
#define ADC_SAMPCTRL_SAMPLEN(value)     (ADC_SAMPCTRL_SAMPLEN_Msk & ((value) << \
                                                                            ADC_SAMPCTRL_SAMPLEN_Pos))
#define ADC_SAMPCTRL_OFFCOMP_Pos        ( 7 )      /* Comparator Offset Compensation Enable */
#define ADC_SAMPCTRL_OFFCOMP            (0x1ul << ADC_SAMPCTRL_OFFCOMP_Pos)
#define ADC_SAMPCTRL_MASK               ( 0xBFul ) /* (ADC_SAMPCTRL) MASK Register */

/********************  ADC WINLT REGISTER MASKING  **********************************************/

#define ADC_WINLT_WINLT_Pos             ( 0 )      /* (ADC_WINLT) Window Lower Threshold */
#define ADC_WINLT_WINLT_Msk             (0xFFFFul << ADC_WINLT_WINLT_Pos)
#define ADC_WINLT_WINLT(value)          (ADC_WINLT_WINLT_Msk & ((value) << ADC_WINLT_WINLT_Pos))
#define ADC_WINLT_MASK                  ( 0xFFFFul ) /* (ADC_WINLT) MASK Register */

/********************  ADC WINUT REGISTER MASKING  **********************************************/

#define ADC_WINUT_WINUT_Pos             ( 0 )      /* (ADC_WINUT) Window Upper Threshold */
#define ADC_WINUT_WINUT_Msk             (0xFFFFul << ADC_WINUT_WINUT_Pos)
#define ADC_WINUT_WINUT(value)          (ADC_WINUT_WINUT_Msk & ((value) << ADC_WINUT_WINUT_Pos))
#define ADC_WINUT_MASK                  ( 0xFFFFul )  /* (ADC_WINUT) MASK Register */

/********************  ADC GAINCORR REGISTER MASKING  *********************************************/

#define ADC_GAINCORR_GAINCORR_Pos       ( 0 )     /* (ADC_GAINCORR) Gain Correction Value */
#define ADC_GAINCORR_GAINCORR_Msk       (0xFFFul << ADC_GAINCORR_GAINCORR_Pos)
#define ADC_GAINCORR_GAINCORR(value)    (ADC_GAINCORR_GAINCORR_Msk & ((value) << \
                                                                ADC_GAINCORR_GAINCORR_Pos))
#define ADC_GAINCORR_MASK               ( 0x0FFFul )   /* (ADC_GAINCORR) MASK Register */

/********************  ADC OFFSETCORR REGISTER MASKING  *******************************************/

#define ADC_OFFSETCORR_OFFSETCORR_Pos   ( 0 )     /* (ADC_OFFSETCORR) Offset Correction Value */
#define ADC_OFFSETCORR_OFFSETCORR_Msk   (0xFFFul << ADC_OFFSETCORR_OFFSETCORR_Pos)
#define ADC_OFFSETCORR_OFFSETCORR(value) (ADC_OFFSETCORR_OFFSETCORR_Msk & ((value) \
													<< ADC_OFFSETCORR_OFFSETCORR_Pos))
#define ADC_OFFSETCORR_MASK             ( 0x0FFFul ) /* (ADC_OFFSETCORR) MASK Register */

/********************  ADC SWTRIG REGISTER MASKING  **********************************************/

#define ADC_SWTRIG_FLUSH_Pos            ( 0 )     /* (ADC_SWTRIG) ADC Flush */
#define ADC_SWTRIG_FLUSH_MASK           (0x1ul << ADC_SWTRIG_FLUSH_Pos)
#define ADC_SWTRIG_START_Pos            ( 1 )     /* (ADC_SWTRIG) Start ADC Conversion */
#define ADC_SWTRIG_START_MASK           (0x1ul << ADC_SWTRIG_START_Pos)
#define ADC_SWTRIG_MASK                 ( 0x03ul )/* (ADC_SWTRIG) MASK Register */

/********************  ADC DBGCTRL REGISTER MASKING  **********************************************/

#define ADC_DBGCTRL_DBGRUN_Pos          ( 0 )     /* (ADC_DBGCTRL) Debug Run */
#define ADC_DBGCTRL_DBGRUN              (0x1ul << ADC_DBGCTRL_DBGRUN_Pos)
#define ADC_DBGCTRL_MASK                ( 0x01ul )/* (ADC_DBGCTRL) MASK Register */

/********************  ADC SYNCBUSY REGISTER MASKING  *********************************************/

#define ADC_SYNCBUSY_SWRST_Pos          ( 0 )     /* (ADC_SYNCBUSY) SWRST Synchronization Busy */
#define ADC_SYNCBUSY_SWRST_MASK         (0x1ul << ADC_SYNCBUSY_SWRST_Pos)
#define ADC_SYNCBUSY_ENABLE_Pos         ( 1 )     /* (ADC_SYNCBUSY) ENABLE Synchronization Busy */
#define ADC_SYNCBUSY_ENABLE_MASK        (0x1ul << ADC_SYNCBUSY_ENABLE_Pos)
#define ADC_SYNCBUSY_INPUTCTRL_Pos      ( 2 )     /* (ADC_SYNCBUSY) AVGCTRL Synchronization Busy */
#define ADC_SYNCBUSY_INPUTCTRL_MASK     (0x1ul << ADC_SYNCBUSY_AVGCTRL_Pos)
#define ADC_SYNCBUSY_CTRLB_Pos       	( 3 )     /* (ADC_SYNCBUSY) SAMPCTRL Synchronization Busy */
#define ADC_SYNCBUSY_CTRLB_MASK      	(0x1ul << ADC_SYNCBUSY_SAMPCTRL_Pos)
#define ADC_SYNCBUSY_REFCTRL_Pos          ( 4 )     /* (ADC_SYNCBUSY) CTRLC Synchronization Busy */
#define ADC_SYNCBUSY_REFCTRL_MASK         (0x1ul << ADC_SYNCBUSY_CTRLC_Pos)
#define ADC_SYNCBUSY_AVGCTRL_Pos      ( 5 )     /* (ADC_SYNCBUSY) INPUTCTRL Synchronization Busy */
#define ADC_SYNCBUSY_AVGCTRL_MASK     (0x1ul << ADC_SYNCBUSY_INPUTCTRL_Pos)
#define ADC_SYNCBUSY_SAMPCTRL_Pos     ( 6 )     /* (ADC_SYNCBUSY) OFFSETCTRL Synchronization Busy */
#define ADC_SYNCBUSY_SAMPCTRL_MASK    (0x1ul << ADC_SYNCBUSY_OFFSETCORR_Pos)
#define ADC_SYNCBUSY_WINLT_Pos       ( 7 )     /* (ADC_SYNCBUSY) GAINCORR Synchronization Busy */
#define ADC_SYNCBUSY_WINLT_MASK      (0x1ul << ADC_SYNCBUSY_GAINCORR_Pos)
#define ADC_SYNCBUSY_WINUT_Pos          ( 8 )     /* (ADC_SYNCBUSY) WINLT Synchronization Busy */
#define ADC_SYNCBUSY_WINUT_MASK         (0x1ul << ADC_SYNCBUSY_WINLT_Pos)
#define ADC_SYNCBUSY_GAINCORR_Pos          ( 9 )     /* (ADC_SYNCBUSY) WINUT Synchronization Busy */
#define ADC_SYNCBUSY_GAINCORR_MASK         (0x1ul << ADC_SYNCBUSY_WINUT_Pos)
#define ADC_SYNCBUSY_OFFSETCORR_Pos         ( 10 )    /* (ADC_SYNCBUSY) SWTRG Synchronization Busy*/
#define ADC_SYNCBUSY_OFFSETCORR_MASK        (0x1ul << ADC_SYNCBUSY_SWTRIG_Pos)
#define ADC_SYNCBUSY_SWTRIG_Pos         ( 11 )
#define ADC_SYNCBUSY_SWTRIG_Msk         (1 <<  ADC_SYNCBUSY_SWTRIG_Msk)
#define ADC_SYNCBUSY_MASK               ( 0x0FFFul )/* (ADC_SYNCBUSY) MASK Register */

/********************  ADC RESULT REGISTER MASKING  **********************************************/

#define ADC_RESULT_RESULT_Pos           ( 0 )     /* (ADC_RESULT) Result Value */
#define ADC_RESULT_RESULT_Msk           (0xFFFFul << ADC_RESULT_RESULT_Pos)
#define ADC_RESULT_RESULT(value)        (ADC_RESULT_RESULT_Msk & ((value) << ADC_RESULT_RESULT_Pos))
#define ADC_RESULT_MASK                 ( 0xFFFFul )     /* (ADC_RESULT) MASK Register */

/********************  ADC CALIB REGISTER MASKING  **********************************************/

#define ADC_CALIB_BIASCOMP_Pos          ( 0 )     /* (ADC_CALIB) Bias Comparator Scaling */
#define ADC_CALIB_BIASCOMP_Msk          (0x7ul << ADC_CALIB_BIASCOMP_Pos)
#define ADC_CALIB_BIASCOMP(value)       (ADC_CALIB_BIASCOMP_Msk & ((value) << \
                                                                        ADC_CALIB_BIASCOMP_Pos))
#define ADC_CALIB_BIASR2R_Pos        	( 4 )
#define ADC_CALIB_BIASR2R_Msk        (0x7ul << ADC_CALIB_BIASR2R_Pos)
#define ADC_CALIB_BIASREFBUF_Pos        ( 8 )     /* (ADC_CALIB) Bias  Reference Buffer Scaling */
#define ADC_CALIB_BIASREFBUF_Msk        (0x7ul << ADC_CALIB_BIASREFBUF_Pos)
#define ADC_CALIB_BIASREFBUF(value)     (ADC_CALIB_BIASREFBUF_Msk & ((value) << \
                                                                        ADC_CALIB_BIASREFBUF_Pos))
#define ADC_CALIB_MASK                  ( 0x0777ul ) /* (ADC_CALIB) MASK Register */

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

typedef struct
{
	SYS_REG_HWORD		CTRLA;
	SYS_REG_BYTE        EVCTRL;
	SYS_REG_BYTE        DBGCTRL;
	SYS_REG_HWORD		INPUTCTRL;
	SYS_REG_HWORD		CTRLB;
	SYS_REG_BYTE        REFCTRL;
	SYS_REG_BYTE        RESERVED1;
	SYS_REG_BYTE        AVGCTRL;
	SYS_REG_BYTE        SAMPCTRL;
	SYS_REG_HWORD		WINLT;
	SYS_REG_HWORD		WINUT;
	SYS_REG_HWORD		GAINCORR;
	SYS_REG_HWORD		OFFSETCORR;
	SYS_REG_BYTE        SWTRIG;
	SYS_REG_BYTE        RESERVED2[23];
	SYS_REG_BYTE        INTENCLR;
	SYS_REG_BYTE        INTENSET;
	SYS_REG_BYTE        INTFLAG;
	SYS_REG_BYTE        STATUS;
	SYS_REG				SYNCBUSY;
	SYS_REG				DSEQDATA;
	SYS_REG				DSEQCTRL;
	SYS_REG				DSEQSTAT;
	SYS_REG_HWORD		RESULT;
	SYS_REG_BYTE        RESERVED3[2];
	SYS_REG_HWORD       RESS;
	SYS_REG_BYTE		RESERVED4[2];
	SYS_REG_HWORD       CALIB;
}ST_ADC_REG_t;

#endif

/**************************************************************************************************/
/*End of ADC_Priv.h                       			                                              */
/**************************************************************************************************/
