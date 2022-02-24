/**************************************************************************************************/
/*                                                                                                */
/*                          Think Embedded Pvt. Ltd. (TEPL) Design Unit                           */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/* All Rights Reserved Copyright (C) 2013, Think Embedded Pvt. Ltd. (TEPL)                        */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without modification,               */
/* are not permitted in any case                                                                  */
/*                                                                                                */
/* TEPL's name may not be used to endorse or promote products derived from this software without  */
/* specific prior written permission.                                                             */
/*                                                                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/* \File Name   : TC_Priv.h                                                                       */
/* \Author      : Salman Ali                                                                      */
/* \Version 	: 1.1                                                                             */
/* \Date        : 29/2/16                                                                         */
/*                                                                                                */
/* @Description : TCC Drvier Framework                                                            */
/**************************************************************************************************/

#ifndef _TC_PRIV_H_ 
#define _TC_PRIV_H_ 

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

#define SYSTEM_CLOCK_FREQUENCY		    ( 48000000 )

#define TC0_BASE_ADDRESS			    ( 0x40003800 )
#define TC1_BASE_ADDRESS			    ( 0x40003C00 )
#define TC2_BASE_ADDRESS			    ( 0x4101A000 )
#define TC3_BASE_ADDRESS			    ( 0x4101C000 )
#define TC4_BASE_ADDRESS			    ( 0x42001400 )
#define TC5_BASE_ADDRESS                ( 0x42001800 )
#define TC6_BASE_ADDRESS			    ( 0x43001400 )
#define TC7_BASE_ADDRESS                ( 0x43001800 )
#define MAX_TC_TIMERS				    ( 8 )
 

#define TC_CTRLA_SWRST_POS              ( 0 )        /* (TC_CTRLA) Software Reset */
#define TC_CTRLA_SWRST                  (0x1ul << TC_CTRLA_SWRST_POS)
#define TC_CTRLA_ENABLE_POS             ( 1 )        /* (TC_CTRLA) Enable */
#define TC_CTRLA_ENABLE                 (0x1ul << TC_CTRLA_ENABLE_POS)
#define TC_CTRLA_MODE_POS               ( 2 )        /* (TC_CTRLA) Timer Counter Mode */
#define TC_CTRLA_MODE_MASK              (0x3ul << TC_CTRLA_MODE_POS)
#define TC_CTRLA_MODE(value)            (TC_CTRLA_MODE_MASK & ((value) << TC_CTRLA_MODE_POS))
#define   TC_CTRLA_MODE_COUNT16_Val     ( 0x0ul )    /* (TC_CTRLA)  */
#define   TC_CTRLA_MODE_COUNT8_Val      ( 0x1ul )    /* (TC_CTRLA)  */
#define   TC_CTRLA_MODE_COUNT32_Val     ( 0x2ul )    /* (TC_CTRLA)  */
#define TC_CTRLA_MODE_COUNT16           (TC_CTRLA_MODE_COUNT16_Val     << TC_CTRLA_MODE_POS)
#define TC_CTRLA_MODE_COUNT8            (TC_CTRLA_MODE_COUNT8_Val      << TC_CTRLA_MODE_POS)
#define TC_CTRLA_MODE_COUNT32           (TC_CTRLA_MODE_COUNT32_Val     << TC_CTRLA_MODE_POS)
#define TC_CTRLA_PRESCSYNC_POS          ( 4 )        /* Prescaler and Counter Synchronization */
#define TC_CTRLA_PRESCSYNC_MASK         (0x3ul << TC_CTRLA_PRESCSYNC_POS)
#define TC_CTRLA_PRESCSYNC(value)       (TC_CTRLA_PRESCSYNC_MASK & ((value) << \
                                                                    TC_CTRLA_PRESCSYNC_POS))
#define   TC_CTRLA_PRESCSYNC_GCLK_Val   ( 0x0ul )    /* (TC_CTRLA)  */
#define   TC_CTRLA_PRESCSYNC_PRESC_Val  ( 0x1ul )    /* (TC_CTRLA)  */
#define   TC_CTRLA_PRESCSYNC_RESYNC_Val ( 0x2ul )    /* (TC_CTRLA)  */
#define TC_CTRLA_PRESCSYNC_GCLK         (TC_CTRLA_PRESCSYNC_GCLK_Val   << TC_CTRLA_PRESCSYNC_POS)
#define TC_CTRLA_PRESCSYNC_PRESC        (TC_CTRLA_PRESCSYNC_PRESC_Val  << TC_CTRLA_PRESCSYNC_POS)
#define TC_CTRLA_PRESCSYNC_RESYNC       (TC_CTRLA_PRESCSYNC_RESYNC_Val << TC_CTRLA_PRESCSYNC_POS)
#define TC_CTRLA_RUNSTDBY_POS           ( 6 )        /* (TC_CTRLA) Run during Standby */
#define TC_CTRLA_RUNSTDBY               (0x1ul << TC_CTRLA_RUNSTDBY_POS)
#define TC_CTRLA_ONDEMAND_POS           ( 7 )        /* (TC_CTRLA) Clock On Demand */
#define TC_CTRLA_ONDEMAND               (0x1ul << TC_CTRLA_ONDEMAND_POS)
#define TC_CTRLA_PRESCALER_POS          ( 8 )        /* (TC_CTRLA) Prescaler */
#define TC_CTRLA_PRESCALER_MASK         (0x7ul << TC_CTRLA_PRESCALER_POS)
#define TC_CTRLA_PRESCALER(value)       (TC_CTRLA_PRESCALER_MASK & ((value) << \
                                                                      TC_CTRLA_PRESCALER_POS))
#define TC_CTRLA_ALOCK_POS              ( 11 )       /* (TC_CTRLA) Auto Lock */
#define TC_CTRLA_ALOCK                  (0x1ul << TC_CTRLA_ALOCK_POS)
#define TC_CTRLA_CAPTEN0_POS            ( 16 )       /* (TC_CTRLA) Capture Channel 0 Enable */
#define TC_CTRLA_CAPTEN0                (1 << TC_CTRLA_CAPTEN0_POS)
#define TC_CTRLA_CAPTEN1_POS            ( 17 )       /* (TC_CTRLA) Capture Channel 1 Enable */
#define TC_CTRLA_CAPTEN1                (1 << TC_CTRLA_CAPTEN1_POS)
#define TC_CTRLA_CAPTEN_POS             ( 16 )       /* (TC_CTRLA) Capture Channel x Enable */
#define TC_CTRLA_CAPTEN_MASK            (0x3ul << TC_CTRLA_CAPTEN_POS)
#define TC_CTRLA_CAPTEN(value)          (TC_CTRLA_CAPTEN_MASK & ((value) << TC_CTRLA_CAPTEN_POS))
#define TC_CTRLA_COPEN0_POS             ( 20 )       /* (TC_CTRLA) Capture On Pin 0 Enable */
#define TC_CTRLA_COPEN0                 (1 << TC_CTRLA_COPEN0_POS)
#define TC_CTRLA_COPEN1_POS             ( 21 )       /* (TC_CTRLA) Capture On Pin 1 Enable */
#define TC_CTRLA_COPEN1                 (1 << TC_CTRLA_COPEN1_POS)
#define TC_CTRLA_COPEN_POS              ( 20 )       /* (TC_CTRLA) Capture On Pin x Enable */
#define TC_CTRLA_COPEN_MASK             (0x3ul << TC_CTRLA_COPEN_POS)
#define TC_CTRLA_COPEN(value)           (TC_CTRLA_COPEN_MASK & ((value) << TC_CTRLA_COPEN_POS))
#define TC_CTRLA_MASK                   ( 0x00330FFFul ) /* (TC_CTRLA) MASK Register */ 



#define TC_CTRLBCLR_DIR_POS             ( 0 )        /* (TC_CTRLBCLR) Counter Direction */
#define TC_CTRLBCLR_DIR                 (0x1ul << TC_CTRLBCLR_DIR_POS)
#define TC_CTRLBCLR_LUPD_POS            ( 1 )        /* (TC_CTRLBCLR) Lock Update */
#define TC_CTRLBCLR_LUPD                (0x1ul << TC_CTRLBCLR_LUPD_POS)
#define TC_CTRLBCLR_ONESHOT_POS         ( 2 )        /* (TC_CTRLBCLR) One-Shot on Counter */
#define TC_CTRLBCLR_ONESHOT             (0x1ul << TC_CTRLBCLR_ONESHOT_POS)
#define TC_CTRLBCLR_CMD_POS             ( 5 )        /* (TC_CTRLBCLR) Command */
#define TC_CTRLBCLR_CMD_MASK            (0x7ul << TC_CTRLBCLR_CMD_POS)
#define TC_CTRLBCLR_CMD(value)          (TC_CTRLBCLR_CMD_MASK & ((value) << TC_CTRLBCLR_CMD_POS))
#define   TC_CTRLBCLR_CMD_NONE_Val      ( 0x0ul )    /* (TC_CTRLBCLR)  */
#define   TC_CTRLBCLR_CMD_RETRIGGER_Val ( 0x1ul )    /* (TC_CTRLBCLR)  */
#define   TC_CTRLBCLR_CMD_STOP_Val      ( 0x2ul )    /* (TC_CTRLBCLR)  */
#define   TC_CTRLBCLR_CMD_UPDATE_Val    ( 0x3ul )    /* (TC_CTRLBCLR)  */
#define   TC_CTRLBCLR_CMD_READSYNC_Val  ( 0x4ul )    /* (TC_CTRLBCLR)  */
#define TC_CTRLBCLR_CMD_NONE            (TC_CTRLBCLR_CMD_NONE_Val      << TC_CTRLBCLR_CMD_POS)
#define TC_CTRLBCLR_CMD_RETRIGGER       (TC_CTRLBCLR_CMD_RETRIGGER_Val << TC_CTRLBCLR_CMD_POS)
#define TC_CTRLBCLR_CMD_STOP            (TC_CTRLBCLR_CMD_STOP_Val      << TC_CTRLBCLR_CMD_POS)
#define TC_CTRLBCLR_CMD_UPDATE          (TC_CTRLBCLR_CMD_UPDATE_Val    << TC_CTRLBCLR_CMD_POS)
#define TC_CTRLBCLR_CMD_READSYNC        (TC_CTRLBCLR_CMD_READSYNC_Val  << TC_CTRLBCLR_CMD_POS)
#define TC_CTRLBCLR_MASK                ( 0xE7ul )   /* (TC_CTRLBCLR) MASK Register */


#define TC_CTRLBSET_DIR_POS             ( 0 )        /* Counter Direction */
#define TC_CTRLBSET_DIR                 (0x1ul << TC_CTRLBSET_DIR_POS)
#define TC_CTRLBSET_LUPD_POS            ( 1 )        /**< \brief (TC_CTRLBSET) Lock Update */
#define TC_CTRLBSET_LUPD                (0x1ul << TC_CTRLBSET_LUPD_POS)
#define TC_CTRLBSET_ONESHOT_POS         ( 2 )        /**< \brief One-Shot on Counter */
#define TC_CTRLBSET_ONESHOT             (0x1ul << TC_CTRLBSET_ONESHOT_POS)
#define TC_CTRLBSET_CMD_POS             ( 5 )        /**< \brief (TC_CTRLBSET) Command */
#define TC_CTRLBSET_CMD_MASK            (0x7ul << TC_CTRLBSET_CMD_POS)
#define TC_CTRLBSET_CMD(value)          (TC_CTRLBSET_CMD_MASK & ((value) << TC_CTRLBSET_CMD_POS))
#define   TC_CTRLBSET_CMD_NONE_Val      ( 0x0ul )    /**< \brief (TC_CTRLBSET)  */
#define   TC_CTRLBSET_CMD_RETRIGGER_Val ( 0x1ul )    /**< \brief (TC_CTRLBSET)  */
#define   TC_CTRLBSET_CMD_STOP_Val      ( 0x2ul )    /**< \brief (TC_CTRLBSET)  */
#define   TC_CTRLBSET_CMD_UPDATE_Val    ( 0x3ul )    /**< \brief (TC_CTRLBSET)  */
#define   TC_CTRLBSET_CMD_READSYNC_Val  ( 0x4ul )    /**< \brief (TC_CTRLBSET)  */
#define TC_CTRLBSET_CMD_NONE            (TC_CTRLBSET_CMD_NONE_Val      << TC_CTRLBSET_CMD_POS)
#define TC_CTRLBSET_CMD_RETRIGGER       (TC_CTRLBSET_CMD_RETRIGGER_Val << TC_CTRLBSET_CMD_POS)
#define TC_CTRLBSET_CMD_STOP            (TC_CTRLBSET_CMD_STOP_Val      << TC_CTRLBSET_CMD_POS)
#define TC_CTRLBSET_CMD_UPDATE          (TC_CTRLBSET_CMD_UPDATE_Val    << TC_CTRLBSET_CMD_POS)
#define TC_CTRLBSET_CMD_READSYNC        (TC_CTRLBSET_CMD_READSYNC_Val  << TC_CTRLBSET_CMD_POS)
#define TC_CTRLBSET_MASK                ( 0xE7ul )   /**< \brief (TC_CTRLBSET) MASK Register */


#define TC_EVCTRL_EVACT_POS             ( 0 )        /**< \brief (TC_EVCTRL) Event Action */
#define TC_EVCTRL_EVACT_MASK            (0x7ul << TC_EVCTRL_EVACT_POS)
#define TC_EVCTRL_EVACT(value)          (TC_EVCTRL_EVACT_MASK & ((value) << TC_EVCTRL_EVACT_POS))
#define   TC_EVCTRL_EVACT_OFF_Val       ( 0x0ul )    /**< \brief (TC_EVCTRL)  */
#define   TC_EVCTRL_EVACT_RETRIGGER_Val ( 0x1ul )    /**< \brief (TC_EVCTRL)  */
#define   TC_EVCTRL_EVACT_COUNT_Val     ( 0x2ul )    /**< \brief (TC_EVCTRL)  */
#define   TC_EVCTRL_EVACT_START_Val     ( 0x3ul )    /**< \brief (TC_EVCTRL)  */
#define   TC_EVCTRL_EVACT_STAMP_Val     ( 0x4ul )    /**< \brief (TC_EVCTRL)  */
#define   TC_EVCTRL_EVACT_PPW_Val       ( 0x5ul )    /**< \brief (TC_EVCTRL)  */
#define   TC_EVCTRL_EVACT_PWP_Val       ( 0x6ul )    /**< \brief (TC_EVCTRL)  */
#define   TC_EVCTRL_EVACT_PW_Val        ( 0x7ul )    /**< \brief (TC_EVCTRL)  */
#define TC_EVCTRL_EVACT_OFF             (TC_EVCTRL_EVACT_OFF_Val       << TC_EVCTRL_EVACT_POS)
#define TC_EVCTRL_EVACT_RETRIGGER       (TC_EVCTRL_EVACT_RETRIGGER_Val << TC_EVCTRL_EVACT_POS)
#define TC_EVCTRL_EVACT_COUNT           (TC_EVCTRL_EVACT_COUNT_Val     << TC_EVCTRL_EVACT_POS)
#define TC_EVCTRL_EVACT_START           (TC_EVCTRL_EVACT_START_Val     << TC_EVCTRL_EVACT_POS)
#define TC_EVCTRL_EVACT_STAMP           (TC_EVCTRL_EVACT_STAMP_Val     << TC_EVCTRL_EVACT_POS)
#define TC_EVCTRL_EVACT_PPW             (TC_EVCTRL_EVACT_PPW_Val       << TC_EVCTRL_EVACT_POS)
#define TC_EVCTRL_EVACT_PWP             (TC_EVCTRL_EVACT_PWP_Val       << TC_EVCTRL_EVACT_POS)
#define TC_EVCTRL_EVACT_PW              (TC_EVCTRL_EVACT_PW_Val        << TC_EVCTRL_EVACT_POS)
#define TC_EVCTRL_TCINV_POS             ( 4 )        /**< \brief TC Event Input Polarity */
#define TC_EVCTRL_TCINV                 (0x1ul << TC_EVCTRL_TCINV_POS)
#define TC_EVCTRL_TCEI_POS              ( 5 )        /**< \brief (TC_EVCTRL) TC Event Enable */
#define TC_EVCTRL_TCEI                  (0x1ul << TC_EVCTRL_TCEI_POS)
#define TC_EVCTRL_OVFEO_POS             ( 8 )        /**< \brief (TC_EVCTRL) Event Output Enable */
#define TC_EVCTRL_OVFEO                 (0x1ul << TC_EVCTRL_OVFEO_POS)
#define TC_EVCTRL_MCEO0_POS             ( 12 )       /**< \brief MC Event Output Enable 0 */
#define TC_EVCTRL_MCEO0                 (1 << TC_EVCTRL_MCEO0_POS)
#define TC_EVCTRL_MCEO1_POS             ( 13 )       /**< \brief MC Event Output Enable 1 */
#define TC_EVCTRL_MCEO1                 (1 << TC_EVCTRL_MCEO1_POS)
#define TC_EVCTRL_MCEO_POS              ( 12 )       /**< \brief MC Event Output Enable x */
#define TC_EVCTRL_MCEO_MASK             (0x3ul << TC_EVCTRL_MCEO_POS)
#define TC_EVCTRL_MCEO(value)           (TC_EVCTRL_MCEO_MASK & ((value) << TC_EVCTRL_MCEO_POS))
#define TC_EVCTRL_MASK                  ( 0x3137ul ) /**< \brief (TC_EVCTRL) MASK Register */


#define TC_INTENCLR_OVF_POS             ( 0 )        /**< \brief OVF Interrupt Disable */
#define TC_INTENCLR_OVF                 (0x1ul << TC_INTENCLR_OVF_POS)
#define TC_INTENCLR_ERR_POS             ( 1 )        /**< \brief ERR Interrupt Disable */
#define TC_INTENCLR_ERR                 (0x1ul << TC_INTENCLR_ERR_POS)
#define TC_INTENCLR_MC0_POS             ( 4 )        /**< \brief MC Interrupt Disable 0 */
#define TC_INTENCLR_MC0                 (1 << TC_INTENCLR_MC0_POS)
#define TC_INTENCLR_MC1_POS             ( 5 )        /**< \brief MC Interrupt Disable 1 */
#define TC_INTENCLR_MC1                 (1 << TC_INTENCLR_MC1_POS)
#define TC_INTENCLR_MC_POS              ( 4 )        /**< \brief MC Interrupt Disable x */
#define TC_INTENCLR_MC_MASK             (0x3ul << TC_INTENCLR_MC_POS)
#define TC_INTENCLR_MC(value)           (TC_INTENCLR_MC_MASK & ((value) << TC_INTENCLR_MC_POS))
#define TC_INTENCLR_MASK                ( 0x33ul )   /**< \brief (TC_INTENCLR) MASK Register */



#define TC_INTENSET_OVF_POS             ( 0 )        /**< \brief OVF Interrupt Enable */
#define TC_INTENSET_OVF                 (0x1ul << TC_INTENSET_OVF_POS)
#define TC_INTENSET_ERR_POS             ( 1 )        /**< \brief ERR Interrupt Enable */
#define TC_INTENSET_ERR                 (0x1ul << TC_INTENSET_ERR_POS)
#define TC_INTENSET_MC0_POS             ( 4 )        /**< \brief MC Interrupt Enable 0 */
#define TC_INTENSET_MC0                 (1 << TC_INTENSET_MC0_POS)
#define TC_INTENSET_MC1_POS             ( 5 )        /**< \brief MC Interrupt Enable 1 */
#define TC_INTENSET_MC1                 (1 << TC_INTENSET_MC1_POS)
#define TC_INTENSET_MC_POS              ( 4 )        /**< \brief MC Interrupt Enable x */
#define TC_INTENSET_MC_MASK             (0x3ul << TC_INTENSET_MC_POS)
#define TC_INTENSET_MC(value)           (TC_INTENSET_MC_MASK & ((value) << TC_INTENSET_MC_POS))
#define TC_INTENSET_MASK                ( 0x33ul )   /**< \brief (TC_INTENSET) MASK Register */

#define TC_INTFLAG_OVF_POS              ( 0 )        /**< \brief OVF Interrupt Flag */
#define TC_INTFLAG_OVF                  (0x1ul << TC_INTFLAG_OVF_POS)
#define TC_INTFLAG_ERR_POS              ( 1 )        /**< \brief ERR Interrupt Flag */
#define TC_INTFLAG_ERR                  (0x1ul << TC_INTFLAG_ERR_POS)
#define TC_INTFLAG_MC0_POS              ( 4 )        /**< \brief MC Interrupt Flag 0 */
#define TC_INTFLAG_MC0                  (1 << TC_INTFLAG_MC0_POS)
#define TC_INTFLAG_MC1_POS              ( 5 )        /**< \brief MC Interrupt Flag 1 */
#define TC_INTFLAG_MC1                  (1 << TC_INTFLAG_MC1_POS)
#define TC_INTFLAG_MC_POS               ( 4 )        /**< \brief MC Interrupt Flag x */
#define TC_INTFLAG_MC_MASK              (0x3ul << TC_INTFLAG_MC_POS)
#define TC_INTFLAG_MC(value)            (TC_INTFLAG_MC_MASK & ((value) << TC_INTFLAG_MC_POS))
#define TC_INTFLAG_MASK                 ( 0x33ul )   /**< \brief (TC_INTFLAG) MASK Register */


#define TC_STATUS_STOP_POS              ( 0 )        /**< \brief Stop Status Flag */
#define TC_STATUS_STOP                  (0x1ul << TC_STATUS_STOP_POS)
#define TC_STATUS_SLAVE_POS             ( 1 )        /**< \brief Slave Status Flag */
#define TC_STATUS_SLAVE                 (0x1ul << TC_STATUS_SLAVE_POS)
#define TC_STATUS_PERBUFV_POS           ( 3 )        /**< \brief Synchronization Busy Status */
#define TC_STATUS_PERBUFV               (0x1ul << TC_STATUS_PERBUFV_POS)
#define TC_STATUS_CCBUFV0_POS           ( 4 )        /**< \brief Compare channel buffer 0 valid */
#define TC_STATUS_CCBUFV0               (1 << TC_STATUS_CCBUFV0_POS)
#define TC_STATUS_CCBUFV1_POS           ( 5 )        /**< \brief Compare channel buffer 1 valid */
#define TC_STATUS_CCBUFV1               (1 << TC_STATUS_CCBUFV1_POS)
#define TC_STATUS_CCBUFV_POS            ( 4 )        /**< \brief Compare channel buffer x valid */
#define TC_STATUS_CCBUFV_MASK           (0x3ul << TC_STATUS_CCBUFV_POS)
#define TC_STATUS_CCBUFV(value)         (TC_STATUS_CCBUFV_MASK & ((value) << TC_STATUS_CCBUFV_POS))
#define TC_STATUS_MASK                  ( 0x3Bul )   /**< \brief (TC_STATUS) MASK Register */


#define TC_WAVE_WAVEGEN_POS             ( 0 )        /**< \brief Waveform Generation Mode */
#define TC_WAVE_WAVEGEN_MASK            (0x3ul << TC_WAVE_WAVEGEN_POS)
#define TC_WAVE_WAVEGEN(value)          (TC_WAVE_WAVEGEN_MASK & ((value) << TC_WAVE_WAVEGEN_POS))
#define   TC_WAVE_WAVEGEN_NFRQ_Val      ( 0x0ul )    /**< \brief (TC_WAVE)  */
#define   TC_WAVE_WAVEGEN_MFRQ_Val      ( 0x1ul )    /**< \brief (TC_WAVE)  */
#define   TC_WAVE_WAVEGEN_NPWM_Val      ( 0x2ul )    /**< \brief (TC_WAVE)  */
#define   TC_WAVE_WAVEGEN_MPWM_Val      ( 0x3ul )    /**< \brief (TC_WAVE)  */
#define TC_WAVE_WAVEGEN_NFRQ            (TC_WAVE_WAVEGEN_NFRQ_Val      << TC_WAVE_WAVEGEN_POS)
#define TC_WAVE_WAVEGEN_MFRQ            (TC_WAVE_WAVEGEN_MFRQ_Val      << TC_WAVE_WAVEGEN_POS)
#define TC_WAVE_WAVEGEN_NPWM            (TC_WAVE_WAVEGEN_NPWM_Val      << TC_WAVE_WAVEGEN_POS)
#define TC_WAVE_WAVEGEN_MPWM            (TC_WAVE_WAVEGEN_MPWM_Val      << TC_WAVE_WAVEGEN_POS)
#define TC_WAVE_MASK                    ( 0x03ul )   /**< \brief (TC_WAVE) MASK Register */


#define TC_DRVCTRL_INVEN0_POS           ( 0 )        /**< \brief Output Waveform Invert Enable 0 */
#define TC_DRVCTRL_INVEN0               (1 << TC_DRVCTRL_INVEN0_POS)
#define TC_DRVCTRL_INVEN1_POS           ( 1 )        /**< \brief Output Waveform Invert Enable 1 */
#define TC_DRVCTRL_INVEN1               (1 << TC_DRVCTRL_INVEN1_POS)
#define TC_DRVCTRL_INVEN_POS            ( 0 )        /**< \brief Output Waveform Invert Enable x */
#define TC_DRVCTRL_INVEN_MASK           (0x3ul << TC_DRVCTRL_INVEN_POS)
#define TC_DRVCTRL_INVEN(value)         (TC_DRVCTRL_INVEN_MASK & ((value) << TC_DRVCTRL_INVEN_POS))
#define TC_DRVCTRL_MASK                 ( 0x03ul )   /**< \brief (TC_DRVCTRL) MASK Register */


#define TC_DBGCTRL_DBGRUN_POS           ( 0 )        /**< \brief Run During Debug */
#define TC_DBGCTRL_DBGRUN               (0x1ul << TC_DBGCTRL_DBGRUN_POS)
#define TC_DBGCTRL_MASK                 ( 0x01ul )   /**< \brief (TC_DBGCTRL) MASK Register */


#define TC_SYNCBUSY_SWRST_POS           ( 0 )        /**< \brief (TC_SYNCBUSY) swrst */
#define TC_SYNCBUSY_SWRST               (0x1ul << TC_SYNCBUSY_SWRST_POS)
#define TC_SYNCBUSY_ENABLE_POS          ( 1 )        /**< \brief (TC_SYNCBUSY) enable */
#define TC_SYNCBUSY_ENABLE              (0x1ul << TC_SYNCBUSY_ENABLE_POS)
#define TC_SYNCBUSY_CTRLB_POS           ( 2 )        /**< \brief (TC_SYNCBUSY) CTRLB */
#define TC_SYNCBUSY_CTRLB               (0x1ul << TC_SYNCBUSY_CTRLB_POS)
#define TC_SYNCBUSY_STATUS_POS          ( 3 )        /**< \brief (TC_SYNCBUSY) STATUS */
#define TC_SYNCBUSY_STATUS              (0x1ul << TC_SYNCBUSY_STATUS_POS)
#define TC_SYNCBUSY_COUNT_POS           ( 4 )        /**< \brief (TC_SYNCBUSY) Counter */
#define TC_SYNCBUSY_COUNT               (0x1ul << TC_SYNCBUSY_COUNT_POS)
#define TC_SYNCBUSY_PER_POS             ( 5 )        /**< \brief (TC_SYNCBUSY) Period */
#define TC_SYNCBUSY_PER                 (0x1ul << TC_SYNCBUSY_PER_POS)
#define TC_SYNCBUSY_CC0_POS             ( 6 )        /**< \brief (TC_SYNCBUSY) Compare Channel 0 */
#define TC_SYNCBUSY_CC0                 (1 << TC_SYNCBUSY_CC0_POS)
#define TC_SYNCBUSY_CC1_POS             ( 7 )        /**< \brief Compare Channel 1 */
#define TC_SYNCBUSY_CC1                 (1 << TC_SYNCBUSY_CC1_POS)
#define TC_SYNCBUSY_CC_POS              ( 6 )        /**< \brief (TC_SYNCBUSY) Compare Channel x */
#define TC_SYNCBUSY_CC_MASK             (0x3ul << TC_SYNCBUSY_CC_POS)
#define TC_SYNCBUSY_CC(value)           (TC_SYNCBUSY_CC_MASK & ((value) << TC_SYNCBUSY_CC_POS))
#define TC_SYNCBUSY_MASK                (0x000000FFul ) /**< \brief (TC_SYNCBUSY) MASK Register */


#define TC_COUNT16_COUNT_COUNT_POS      ( 0 )        /* (TC_COUNT16_COUNT) Counter Value */
#define TC_COUNT16_COUNT_COUNT_MASK     (0xFFFFul << TC_COUNT16_COUNT_COUNT_POS)
#define TC_COUNT16_COUNT_COUNT(value)   (TC_COUNT16_COUNT_COUNT_MASK & ((value) << \
                                                                TC_COUNT16_COUNT_COUNT_POS))
#define TC_COUNT16_COUNT_MASK           ( 0xFFFFul ) /* (TC_COUNT16_COUNT) MASK Register */



#define TC_COUNT16_CC_CC_POS            ( 0 )        /* (TC_COUNT16_CC) Counter/Compare Value */
#define TC_COUNT16_CC_CC_MASK           (0xFFFFul << TC_COUNT16_CC_CC_POS)
#define TC_COUNT16_CC_CC(value)         (TC_COUNT16_CC_CC_MASK & ((value) << TC_COUNT16_CC_CC_POS))
#define TC_COUNT16_CC_MASK              ( 0xFFFFul ) /**< \brief (TC_COUNT16_CC) MASK Register */


/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

/* Structure for TC module registers */
typedef struct
{
  SYS_REG          	CTRLA;
  SYS_REG_BYTE          CTRLBCLR;
  SYS_REG_BYTE          CTRLBSET;
  SYS_REG_HWORD         EVCTRL;
  SYS_REG_BYTE          INTENCLR;
  SYS_REG_BYTE          INTENSET;
  SYS_REG_BYTE          INTFLAG;
  SYS_REG_BYTE          STATUS;
  SYS_REG_BYTE          WAVE;
  SYS_REG_BYTE          DRVCTRL;
  SYS_REG_BYTE          Reserved1;
  SYS_REG_BYTE          DBGCTRL;
  SYS_REG          	SYNCBUSY;
  
}ST_TC_BASE_REG_t;

/* Structure for Hardware Registers in 8-bit Counter Mode */
typedef struct 
{ 
  SYS_REG_BYTE       	COUNT;       /* Offset: 0x14 (R/W 8) COUNT8 Count */
  SYS_REG_BYTE          Reserved2[6];
  SYS_REG_BYTE          PER;         /* Offset: 0x1B (R/W 8) COUNT8 Count */   
  SYS_REG_BYTE        	CC[2];       /* Offset: 0x1C (R/W 8) COUNT8 Compare and Capture */
  SYS_REG_BYTE          Reserved3[17];
  SYS_REG_BYTE          PERBUF;      /* Offset: 0x2F (R/W 8) COUNT16 Count */
  SYS_REG_BYTE       	CCBUF[2];    /* Offset: 0x30 (R/W 8) COUNT8 Compare and Capture Buffer */
  SYS_REG_BYTE          Reserved4[0x2];      
} ST_TC_COUNT8_BASE_REGS_t;


/* Structure for Hardware Registers in 16-bit Counter Mode */

typedef struct 
{ 
  SYS_REG_HWORD     	COUNT;       /* Offset: 0x14 (R/W 16) COUNT16 Count */
  SYS_REG_BYTE          Reserved2[6];
  SYS_REG_HWORD        	CC[2];       /* Offset: 0x1C (R/W 16) COUNT16 Compare and Capture */
  SYS_REG_BYTE          Reserved3[17];
  SYS_REG_HWORD     	CCBUF[2];    /* Offset: 0x30 (R/W 16) COUNT16 Compare and Capture Buffer */
	
}ST_TC_COUNT16_BASE_REGS_t;

typedef struct 
{ 
  SYS_REG            	COUNT;       /* Offset: 0x14 (R/W 16) COUNT16 Count */
  SYS_REG_BYTE          Reserved2[4];
  SYS_REG        	    CC[2];       /* Offset: 0x1C (R/W 16) COUNT16 Compare and Capture */
  SYS_REG_BYTE          Reserved3[12];
  SYS_REG           	CCBUF[2];    /* Offset: 0x30 (R/W 16) COUNT16 Compare and Capture Buffer */
	
} ST_TC_COUNT32_BASE_REGS_t;

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

#endif

/**************************************************************************************************/
/*End of TC_Priv.h                           			                                          */
/**************************************************************************************************/
