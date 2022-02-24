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
/* \File Name   : EIC_Priv.h                                                                      */
/* \Author      : Ravi Ranjan Kumar                                                               */
/* \Version 	: 1.0                                                                             */
/* \Date        : 07/09/2018                                                                      */
/*                                                                                                */
/* @Description : EIC Private Framework                                                           */
/**************************************************************************************************/

#ifndef _EIC_PRIV_H_ 
#define _EIC_PRIV_H_

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

#define EIC_BASE_ADDRESS				( 0x40002800 )

#define EIC_MAX_CHANNELS				( 16 )

#define EIC_CTRLA_SWRST_MASK			( 0x01 )
#define EIC_CTRLA_ENABLE_MASK			( 0x02 )
#define EIC_CTRLA_CLKSEL_MASK			( 0x10 )

#define EIC_SYNCBUSY_SWRST_MASK 		( 0x01 )
#define EIC_SYNCBUSY_ENABLE_MASK		( 0x02 )

#define EIC_INTFLAG_0_INDEX_MASK		( 0x00 )
#define EIC_INTFLAG_1_INDEX_MASK		( 0x01 )
#define EIC_INTFLAG_2_INDEX_MASK		( 0x02 )
#define EIC_INTFLAG_3_INDEX_MASK		( 0x03 )
#define EIC_INTFLAG_4_INDEX_MASK		( 0x04 )
#define EIC_INTFLAG_5_INDEX_MASK		( 0x05 )
#define EIC_INTFLAG_6_INDEX_MASK		( 0x06 )
#define EIC_INTFLAG_7_INDEX_MASK		( 0x07 )
#define EIC_INTFLAG_8_INDEX_MASK		( 0x08 )
#define EIC_INTFLAG_9_INDEX_MASK		( 0x09 )
#define EIC_INTFLAG_10_INDEX_MASK		( 0x0A )
#define EIC_INTFLAG_11_INDEX_MASK		( 0x0B )
#define EIC_INTFLAG_12_INDEX_MASK		( 0x0C )
#define EIC_INTFLAG_13_INDEX_MASK		( 0x0D )
#define EIC_INTFLAG_14_INDEX_MASK		( 0x0E )
#define EIC_INTFLAG_15_INDEX_MASK		( 0x0F )

/***********        MASKING FOR INTFLAG REGISTER    ***********************************************/

#define EIC_INTFLAG_0_MASK				( 0x0001 )
#define EIC_INTFLAG_1_MASK				( 0x0002 )
#define EIC_INTFLAG_2_MASK				( 0x0004 )
#define EIC_INTFLAG_3_MASK				( 0x0008 )
#define EIC_INTFLAG_4_MASK				( 0x0010 )
#define EIC_INTFLAG_5_MASK				( 0x0020 )
#define EIC_INTFLAG_6_MASK				( 0x0040 )
#define EIC_INTFLAG_7_MASK				( 0x0080 )
#define EIC_INTFLAG_8_MASK				( 0x0100 )
#define EIC_INTFLAG_9_MASK				( 0x0200 )
#define EIC_INTFLAG_10_MASK				( 0x0400 )
#define EIC_INTFLAG_11_MASK				( 0x0800 )
#define EIC_INTFLAG_12_MASK				( 0x1000 )
#define EIC_INTFLAG_13_MASK				( 0x2000 )
#define EIC_INTFLAG_14_MASK				( 0x4000 )
#define EIC_INTFLAG_15_MASK				( 0x8000 )

/***********        MASKING FOR CONFIGx REGISTER    ***********************************************/

#define     EIC_CONFIG_SENSE0_Pos       ( 0 )        /* (EIC_CONFIG) Input Sense Configuration 0 */
#define     EIC_CONFIG_SENSE0_Msk       (0x7ul << EIC_CONFIG_SENSE0_Pos)
#define     EIC_CONFIG_SENSE0(value)    (EIC_CONFIG_SENSE0_Msk & ((value) << EIC_CONFIG_SENSE0_Pos))
#define     EIC_CONFIG_SENSE0_NONE_Val  ( 0x0ul )   /* (EIC_CONFIG) No detection */
#define     EIC_CONFIG_SENSE0_RISE_Val  ( 0x1ul )   /* (EIC_CONFIG) Rising edge detection */
#define     EIC_CONFIG_SENSE0_FALL_Val  ( 0x2ul )   /* (EIC_CONFIG) Falling edge detection */
#define     EIC_CONFIG_SENSE0_BOTH_Val  ( 0x3ul )   /* (EIC_CONFIG) Both edges detection */
#define     EIC_CONFIG_SENSE0_HIGH_Val  ( 0x4ul )   /* (EIC_CONFIG) High level detection */
#define     EIC_CONFIG_SENSE0_LOW_Val   ( 0x5ul )   /* (EIC_CONFIG) Low level detection */
#define 	EIC_CONFIG_SENSE0_NONE      (EIC_CONFIG_SENSE0_NONE_Val    << EIC_CONFIG_SENSE0_Pos)
#define 	EIC_CONFIG_SENSE0_RISE      (EIC_CONFIG_SENSE0_RISE_Val    << EIC_CONFIG_SENSE0_Pos)
#define 	EIC_CONFIG_SENSE0_FALL      (EIC_CONFIG_SENSE0_FALL_Val    << EIC_CONFIG_SENSE0_Pos)
#define 	EIC_CONFIG_SENSE0_BOTH      (EIC_CONFIG_SENSE0_BOTH_Val    << EIC_CONFIG_SENSE0_Pos)
#define 	EIC_CONFIG_SENSE0_HIGH      (EIC_CONFIG_SENSE0_HIGH_Val    << EIC_CONFIG_SENSE0_Pos)
#define 	EIC_CONFIG_SENSE0_LOW       (EIC_CONFIG_SENSE0_LOW_Val     << EIC_CONFIG_SENSE0_Pos)
#define 	EIC_CONFIG_FILTEN0_Pos      ( 3 )       /* (EIC_CONFIG) Filter Enable 0 */
#define 	EIC_CONFIG_FILTEN0          (0x1ul << EIC_CONFIG_FILTEN0_Pos)
#define	 	EIC_CONFIG_SENSE1_Pos       ( 4 )       /* (EIC_CONFIG) Input Sense Configuration 1 */
#define 	EIC_CONFIG_SENSE1_Msk       (0x7ul << EIC_CONFIG_SENSE1_Pos)
#define 	EIC_CONFIG_SENSE1(value)    (EIC_CONFIG_SENSE1_Msk & ((value) << EIC_CONFIG_SENSE1_Pos))
#define     EIC_CONFIG_SENSE1_NONE_Val  ( 0x0ul )   /* (EIC_CONFIG) No detection */
#define     EIC_CONFIG_SENSE1_RISE_Val  ( 0x1ul )   /* (EIC_CONFIG) Rising edge detection */
#define     EIC_CONFIG_SENSE1_FALL_Val  ( 0x2ul )   /* (EIC_CONFIG) Falling edge detection */
#define     EIC_CONFIG_SENSE1_BOTH_Val  ( 0x3ul )   /* (EIC_CONFIG) Both edges detection */
#define     EIC_CONFIG_SENSE1_HIGH_Val  ( 0x4ul )   /* (EIC_CONFIG) High level detection */
#define     EIC_CONFIG_SENSE1_LOW_Val   ( 0x5ul )   /* (EIC_CONFIG) Low level detection */
#define 	EIC_CONFIG_SENSE1_NONE      (EIC_CONFIG_SENSE1_NONE_Val    << EIC_CONFIG_SENSE1_Pos)
#define 	EIC_CONFIG_SENSE1_RISE      (EIC_CONFIG_SENSE1_RISE_Val    << EIC_CONFIG_SENSE1_Pos)
#define 	EIC_CONFIG_SENSE1_FALL      (EIC_CONFIG_SENSE1_FALL_Val    << EIC_CONFIG_SENSE1_Pos)
#define 	EIC_CONFIG_SENSE1_BOTH      (EIC_CONFIG_SENSE1_BOTH_Val    << EIC_CONFIG_SENSE1_Pos)
#define 	EIC_CONFIG_SENSE1_HIGH      (EIC_CONFIG_SENSE1_HIGH_Val    << EIC_CONFIG_SENSE1_Pos)
#define 	EIC_CONFIG_SENSE1_LOW       (EIC_CONFIG_SENSE1_LOW_Val     << EIC_CONFIG_SENSE1_Pos)
#define 	EIC_CONFIG_FILTEN1_Pos      ( 7 )       /* (EIC_CONFIG) Filter Enable 1 */
#define 	EIC_CONFIG_FILTEN1          (0x1ul << EIC_CONFIG_FILTEN1_Pos)
#define 	EIC_CONFIG_SENSE2_Pos       ( 8 )       /* (EIC_CONFIG) Input Sense Configuration 2 */
#define 	EIC_CONFIG_SENSE2_Msk       (0x7ul << EIC_CONFIG_SENSE2_Pos)
#define 	EIC_CONFIG_SENSE2(value)    (EIC_CONFIG_SENSE2_Msk & ((value) << EIC_CONFIG_SENSE2_Pos))
#define     EIC_CONFIG_SENSE2_NONE_Val  ( 0x0ul )   /* (EIC_CONFIG) No detection */
#define     EIC_CONFIG_SENSE2_RISE_Val  ( 0x1ul )   /* (EIC_CONFIG) Rising edge detection */
#define     EIC_CONFIG_SENSE2_FALL_Val  ( 0x2ul )   /* (EIC_CONFIG) Falling edge detection */
#define     EIC_CONFIG_SENSE2_BOTH_Val  ( 0x3ul )   /* (EIC_CONFIG) Both edges detection */
#define     EIC_CONFIG_SENSE2_HIGH_Val  ( 0x4ul )   /* (EIC_CONFIG) High level detection */
#define     EIC_CONFIG_SENSE2_LOW_Val   ( 0x5ul )   /* (EIC_CONFIG) Low level detection */
#define 	EIC_CONFIG_SENSE2_NONE      (EIC_CONFIG_SENSE2_NONE_Val    << EIC_CONFIG_SENSE2_Pos)
#define 	EIC_CONFIG_SENSE2_RISE      (EIC_CONFIG_SENSE2_RISE_Val    << EIC_CONFIG_SENSE2_Pos)
#define 	EIC_CONFIG_SENSE2_FALL      (EIC_CONFIG_SENSE2_FALL_Val    << EIC_CONFIG_SENSE2_Pos)
#define 	EIC_CONFIG_SENSE2_BOTH      (EIC_CONFIG_SENSE2_BOTH_Val    << EIC_CONFIG_SENSE2_Pos)
#define 	EIC_CONFIG_SENSE2_HIGH      (EIC_CONFIG_SENSE2_HIGH_Val    << EIC_CONFIG_SENSE2_Pos)
#define 	EIC_CONFIG_SENSE2_LOW       (EIC_CONFIG_SENSE2_LOW_Val     << EIC_CONFIG_SENSE2_Pos)
#define 	EIC_CONFIG_FILTEN2_Pos      ( 11 )      /* (EIC_CONFIG) Filter Enable 2 */
#define 	EIC_CONFIG_FILTEN2          (0x1ul << EIC_CONFIG_FILTEN2_Pos)
#define 	EIC_CONFIG_SENSE3_Pos       ( 12 )      /* (EIC_CONFIG) Input Sense Configuration 3 */
#define 	EIC_CONFIG_SENSE3_Msk       (0x7ul << EIC_CONFIG_SENSE3_Pos)
#define 	EIC_CONFIG_SENSE3(value)    (EIC_CONFIG_SENSE3_Msk & ((value) << EIC_CONFIG_SENSE3_Pos))
#define     EIC_CONFIG_SENSE3_NONE_Val  ( 0x0ul )   /* (EIC_CONFIG) No detection */
#define     EIC_CONFIG_SENSE3_RISE_Val  ( 0x1ul )   /* (EIC_CONFIG) Rising edge detection */
#define     EIC_CONFIG_SENSE3_FALL_Val  ( 0x2ul )   /* (EIC_CONFIG) Falling edge detection */
#define     EIC_CONFIG_SENSE3_BOTH_Val  ( 0x3ul )   /* (EIC_CONFIG) Both edges detection */
#define     EIC_CONFIG_SENSE3_HIGH_Val  ( 0x4ul )   /* (EIC_CONFIG) High level detection */
#define     EIC_CONFIG_SENSE3_LOW_Val   ( 0x5ul )   /* (EIC_CONFIG) Low level detection */
#define 	EIC_CONFIG_SENSE3_NONE      (EIC_CONFIG_SENSE3_NONE_Val    << EIC_CONFIG_SENSE3_Pos)
#define 	EIC_CONFIG_SENSE3_RISE      (EIC_CONFIG_SENSE3_RISE_Val    << EIC_CONFIG_SENSE3_Pos)
#define 	EIC_CONFIG_SENSE3_FALL      (EIC_CONFIG_SENSE3_FALL_Val    << EIC_CONFIG_SENSE3_Pos)
#define	 	EIC_CONFIG_SENSE3_BOTH      (EIC_CONFIG_SENSE3_BOTH_Val    << EIC_CONFIG_SENSE3_Pos)
#define 	EIC_CONFIG_SENSE3_HIGH      (EIC_CONFIG_SENSE3_HIGH_Val    << EIC_CONFIG_SENSE3_Pos)
#define 	EIC_CONFIG_SENSE3_LOW       (EIC_CONFIG_SENSE3_LOW_Val     << EIC_CONFIG_SENSE3_Pos)
#define 	EIC_CONFIG_FILTEN3_Pos      ( 15 )      /* (EIC_CONFIG) Filter Enable 3 */
#define 	EIC_CONFIG_FILTEN3          (0x1ul << EIC_CONFIG_FILTEN3_Pos)
#define 	EIC_CONFIG_SENSE4_Pos       ( 16 )      /* (EIC_CONFIG) Input Sense Configuration 4 */
#define 	EIC_CONFIG_SENSE4_Msk       (0x7ul << EIC_CONFIG_SENSE4_Pos)
#define 	EIC_CONFIG_SENSE4(value)    (EIC_CONFIG_SENSE4_Msk & ((value) << EIC_CONFIG_SENSE4_Pos))
#define     EIC_CONFIG_SENSE4_NONE_Val  ( 0x0ul )   /* (EIC_CONFIG) No detection */
#define     EIC_CONFIG_SENSE4_RISE_Val  ( 0x1ul )   /* (EIC_CONFIG) Rising edge detection */
#define     EIC_CONFIG_SENSE4_FALL_Val  ( 0x2ul )   /* (EIC_CONFIG) Falling edge detection */
#define     EIC_CONFIG_SENSE4_BOTH_Val  ( 0x3ul )   /* (EIC_CONFIG) Both edges detection */
#define     EIC_CONFIG_SENSE4_HIGH_Val  ( 0x4ul )   /* (EIC_CONFIG) High level detection */
#define     EIC_CONFIG_SENSE4_LOW_Val   ( 0x5ul )   /* (EIC_CONFIG) Low level detection */
#define 	EIC_CONFIG_SENSE4_NONE      (EIC_CONFIG_SENSE4_NONE_Val    << EIC_CONFIG_SENSE4_Pos)
#define 	EIC_CONFIG_SENSE4_RISE      (EIC_CONFIG_SENSE4_RISE_Val    << EIC_CONFIG_SENSE4_Pos)
#define 	EIC_CONFIG_SENSE4_FALL      (EIC_CONFIG_SENSE4_FALL_Val    << EIC_CONFIG_SENSE4_Pos)
#define 	EIC_CONFIG_SENSE4_BOTH      (EIC_CONFIG_SENSE4_BOTH_Val    << EIC_CONFIG_SENSE4_Pos)
#define 	EIC_CONFIG_SENSE4_HIGH      (EIC_CONFIG_SENSE4_HIGH_Val    << EIC_CONFIG_SENSE4_Pos)
#define 	EIC_CONFIG_SENSE4_LOW       (EIC_CONFIG_SENSE4_LOW_Val     << EIC_CONFIG_SENSE4_Pos)
#define 	EIC_CONFIG_FILTEN4_Pos      ( 19 )      /* (EIC_CONFIG) Filter Enable 4 */
#define 	EIC_CONFIG_FILTEN4          (0x1ul << EIC_CONFIG_FILTEN4_Pos)
#define 	EIC_CONFIG_SENSE5_Pos       ( 20 )      /* (EIC_CONFIG) Input Sense Configuration 5 */
#define 	EIC_CONFIG_SENSE5_Msk       (0x7ul << EIC_CONFIG_SENSE5_Pos)
#define 	EIC_CONFIG_SENSE5(value)    (EIC_CONFIG_SENSE5_Msk & ((value) << EIC_CONFIG_SENSE5_Pos))
#define     EIC_CONFIG_SENSE5_NONE_Val  ( 0x0ul )   /* (EIC_CONFIG) No detection */
#define     EIC_CONFIG_SENSE5_RISE_Val  ( 0x1ul )   /* (EIC_CONFIG) Rising edge detection */
#define     EIC_CONFIG_SENSE5_FALL_Val  ( 0x2ul )   /* (EIC_CONFIG) Falling edge detection */
#define     EIC_CONFIG_SENSE5_BOTH_Val  ( 0x3ul )   /* (EIC_CONFIG) Both edges detection */
#define     EIC_CONFIG_SENSE5_HIGH_Val  ( 0x4ul )   /* (EIC_CONFIG) High level detection */
#define     EIC_CONFIG_SENSE5_LOW_Val   ( 0x5ul )   /* (EIC_CONFIG) Low level detection */
#define 	EIC_CONFIG_SENSE5_NONE      (EIC_CONFIG_SENSE5_NONE_Val    << EIC_CONFIG_SENSE5_Pos)
#define 	EIC_CONFIG_SENSE5_RISE      (EIC_CONFIG_SENSE5_RISE_Val    << EIC_CONFIG_SENSE5_Pos)
#define 	EIC_CONFIG_SENSE5_FALL      (EIC_CONFIG_SENSE5_FALL_Val    << EIC_CONFIG_SENSE5_Pos)
#define 	EIC_CONFIG_SENSE5_BOTH      (EIC_CONFIG_SENSE5_BOTH_Val    << EIC_CONFIG_SENSE5_Pos)
#define 	EIC_CONFIG_SENSE5_HIGH      (EIC_CONFIG_SENSE5_HIGH_Val    << EIC_CONFIG_SENSE5_Pos)
#define 	EIC_CONFIG_SENSE5_LOW       (EIC_CONFIG_SENSE5_LOW_Val     << EIC_CONFIG_SENSE5_Pos)
#define 	EIC_CONFIG_FILTEN5_Pos      ( 23 )      /* (EIC_CONFIG) Filter Enable 5 */
#define 	EIC_CONFIG_FILTEN5          (0x1ul << EIC_CONFIG_FILTEN5_Pos)
#define 	EIC_CONFIG_SENSE6_Pos       ( 24 )      /* (EIC_CONFIG) Input Sense Configuration 6 */
#define 	EIC_CONFIG_SENSE6_Msk       (0x7ul << EIC_CONFIG_SENSE6_Pos)
#define 	EIC_CONFIG_SENSE6(value)    (EIC_CONFIG_SENSE6_Msk & ((value) << EIC_CONFIG_SENSE6_Pos))
#define     EIC_CONFIG_SENSE6_NONE_Val  ( 0x0ul )   /* (EIC_CONFIG) No detection */
#define     EIC_CONFIG_SENSE6_RISE_Val  ( 0x1ul )   /* (EIC_CONFIG) Rising edge detection */
#define     EIC_CONFIG_SENSE6_FALL_Val  ( 0x2ul )   /* (EIC_CONFIG) Falling edge detection */
#define     EIC_CONFIG_SENSE6_BOTH_Val  ( 0x3ul )   /* (EIC_CONFIG) Both edges detection */
#define     EIC_CONFIG_SENSE6_HIGH_Val  ( 0x4ul )   /* (EIC_CONFIG) High level detection */
#define     EIC_CONFIG_SENSE6_LOW_Val   ( 0x5ul )   /* (EIC_CONFIG) Low level detection */
#define 	EIC_CONFIG_SENSE6_NONE      (EIC_CONFIG_SENSE6_NONE_Val    << EIC_CONFIG_SENSE6_Pos)
#define 	EIC_CONFIG_SENSE6_RISE      (EIC_CONFIG_SENSE6_RISE_Val    << EIC_CONFIG_SENSE6_Pos)
#define 	EIC_CONFIG_SENSE6_FALL      (EIC_CONFIG_SENSE6_FALL_Val    << EIC_CONFIG_SENSE6_Pos)
#define 	EIC_CONFIG_SENSE6_BOTH      (EIC_CONFIG_SENSE6_BOTH_Val    << EIC_CONFIG_SENSE6_Pos)
#define 	EIC_CONFIG_SENSE6_HIGH      (EIC_CONFIG_SENSE6_HIGH_Val    << EIC_CONFIG_SENSE6_Pos)
#define 	EIC_CONFIG_SENSE6_LOW       (EIC_CONFIG_SENSE6_LOW_Val     << EIC_CONFIG_SENSE6_Pos)
#define 	EIC_CONFIG_FILTEN6_Pos      ( 27 )      /* (EIC_CONFIG) Filter Enable 6 */
#define 	EIC_CONFIG_FILTEN6          (0x1ul << EIC_CONFIG_FILTEN6_Pos)
#define 	EIC_CONFIG_SENSE7_Pos       ( 28 )      /* (EIC_CONFIG) Input Sense Configuration 7 */
#define 	EIC_CONFIG_SENSE7_Msk       (0x7ul << EIC_CONFIG_SENSE7_Pos)
#define 	EIC_CONFIG_SENSE7(value)    (EIC_CONFIG_SENSE7_Msk & ((value) << EIC_CONFIG_SENSE7_Pos))
#define     EIC_CONFIG_SENSE7_NONE_Val  ( 0x0ul )   /* (EIC_CONFIG) No detection */
#define     EIC_CONFIG_SENSE7_RISE_Val  ( 0x1ul )   /* (EIC_CONFIG) Rising edge detection */
#define     EIC_CONFIG_SENSE7_FALL_Val  ( 0x2ul )   /* (EIC_CONFIG) Falling edge detection */
#define     EIC_CONFIG_SENSE7_BOTH_Val  ( 0x3ul )   /* (EIC_CONFIG) Both edges detection */
#define     EIC_CONFIG_SENSE7_HIGH_Val  ( 0x4ul )   /* (EIC_CONFIG) High level detection */
#define     EIC_CONFIG_SENSE7_LOW_Val   ( 0x5ul )   /* (EIC_CONFIG) Low level detection */
#define 	EIC_CONFIG_SENSE7_NONE      (EIC_CONFIG_SENSE7_NONE_Val    << EIC_CONFIG_SENSE7_Pos)
#define 	EIC_CONFIG_SENSE7_RISE      (EIC_CONFIG_SENSE7_RISE_Val    << EIC_CONFIG_SENSE7_Pos)
#define 	EIC_CONFIG_SENSE7_FALL      (EIC_CONFIG_SENSE7_FALL_Val    << EIC_CONFIG_SENSE7_Pos)
#define 	EIC_CONFIG_SENSE7_BOTH      (EIC_CONFIG_SENSE7_BOTH_Val    << EIC_CONFIG_SENSE7_Pos)
#define 	EIC_CONFIG_SENSE7_HIGH      (EIC_CONFIG_SENSE7_HIGH_Val    << EIC_CONFIG_SENSE7_Pos)
#define 	EIC_CONFIG_SENSE7_LOW       (EIC_CONFIG_SENSE7_LOW_Val     << EIC_CONFIG_SENSE7_Pos)
#define 	EIC_CONFIG_FILTEN7_Pos      ( 31 )      /* (EIC_CONFIG) Filter Enable 7 */
#define 	EIC_CONFIG_FILTEN7          (0x1ul << EIC_CONFIG_FILTEN7_Pos)

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

typedef struct 
{
	SYS_REG_BYTE	CTRLA;       /* Control A */
	SYS_REG_BYTE	NMICTRL;     /* Non-Maskable Interrupt Control */
	SYS_REG_HWORD	NMIFLAG;     /* Non-Maskable Interrupt Flag Status and Clear */
	SYS_REG         SYNCBUSY;    /* Synchronization Busy */
	SYS_REG			EVCTRL;      /* Event Control */
	SYS_REG         INTENCLR;    /* Interrupt Enable Clear */
	SYS_REG         INTENSET;    /* Interrupt Enable Set */
	SYS_REG			INTFLAG;     /* Interrupt Flag Status and Clear */
	SYS_REG			ASYNCH;      /* External Interrupt Asynchronous Mode */
	SYS_REG			CONFIG[2];   /* External Interrupt Sense Configuration */
	SYS_REG			RESERVED[3];/* Reserved */
	SYS_REG         DEBOUNCEN;   /* Debouncer Enable */
	SYS_REG         DPRESCALER;  /* Debouncer Prescaler */
	SYS_REG         PINSTATE;    /* Pin State */
}ST_EIC_REG_t;
	
#endif
/**************************************************************************************************/
/*End of EIC_Priv.h                           			                                          */
/**************************************************************************************************/
