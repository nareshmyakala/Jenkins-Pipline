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
/* \File Name   : SPI_priv.h                                                                      */
/* \Author      : Kishore D                                                                       */
/* \Version     : 1.0                                                                             */
/* \Date        : 22/08/2018                                                                      */
/*                                                                                                */
/* @Description :  SPI Driver                                                                     */
/**************************************************************************************************/

#ifndef _SPI_PRIV_H_ 
#define _SPI_PRIV_H_ 

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

#define SERCOM0_BASE_ADDRESS                                    ( 0x40003000 ) 
#define SERCOM1_BASE_ADDRESS                                    ( 0x40003400 )
#define SERCOM2_BASE_ADDRESS                                    ( 0x41012000 )
#define SERCOM3_BASE_ADDRESS                                    ( 0x41014000 )
#define SERCOM4_BASE_ADDRESS    		       	        ( 0x43000000 ) 
#define SERCOM5_BASE_ADDRESS   	    	    		        ( 0x43000400 )
#define SERCOM6_BASE_ADDRESS				        ( 0x43000800 )
#define SERCOM7_BASE_ADDRESS					( 0x43000C00 )
	
#define MAX_SERCOM_CHANNELS																	( 8 )

#define SERCOM_SPI_DATA_DATA_POS        ( 0 )            /* (SERCOM_SPI_DATA) Data Value */
#define SERCOM_SPI_DATA_DATA_MASK       (0x1FFul << SERCOM_SPI_DATA_DATA_POS)
#define SERCOM_SPI_DATA_DATA(value)     (SERCOM_SPI_DATA_DATA_MASK & ((value) << \
                                                                    SERCOM_SPI_DATA_DATA_POS))
#define SERCOM_SPI_DATA_MASK            ( 0x000001FFul ) /* (SERCOM_SPI_DATA) MASK Register */

#define SERCOM_SPI_ADDR_ADDR_POS        ( 0 )            /* (SERCOM_SPI_ADDR) Address Value */
#define SERCOM_SPI_ADDR_ADDR_MASK       (0xFFul << SERCOM_SPI_ADDR_ADDR_POS)
#define SERCOM_SPI_ADDR_ADDR(value)     (SERCOM_SPI_ADDR_ADDR_MASK & ((value) << \
                                                                    SERCOM_SPI_ADDR_ADDR_POS))
#define SERCOM_SPI_ADDR_ADDRMASK_POS    ( 16 )           /* (SERCOM_SPI_ADDR) Address Mask */
#define SERCOM_SPI_ADDR_ADDRMASK_MASK   (0xFFul << SERCOM_SPI_ADDR_ADDRMASK_POS)
#define SERCOM_SPI_ADDR_ADDRMASK(value) (SERCOM_SPI_ADDR_ADDRMASK_MASK & ((value) << \
                                                                SERCOM_SPI_ADDR_ADDRMASK_POS))
#define SERCOM_SPI_ADDR_MASK            ( 0x00FF00FFul ) /* (SERCOM_SPI_ADDR) MASK Register */

#define SERCOM_SPI_SYNCBUSY_SWRST_POS   ( 0 )            /* Software Reset Synchronization Busy */
#define SERCOM_SPI_SYNCBUSY_SWRST_MASK  (0x1ul << SERCOM_SPI_SYNCBUSY_SWRST_POS)
#define SERCOM_SPI_SYNCBUSY_ENABLE_POS  ( 1 )            /*  SERCOM Enable Synchronization Busy */
#define SERCOM_SPI_SYNCBUSY_ENABLE_MASK (0x1ul << SERCOM_SPI_SYNCBUSY_ENABLE_POS)
#define SERCOM_SPI_SYNCBUSY_CTRLB_POS   ( 2 )            /*  CTRLB Synchronization Busy */
#define SERCOM_SPI_SYNCBUSY_CTRLB_MASK  (0x1ul << SERCOM_SPI_SYNCBUSY_CTRLB_POS)
#define SERCOM_SPI_SYNCBUSY_MASK        ( 0x00000007ul ) /* SYNCBUSY MASK Register */


#define SERCOM_SPI_STATUS_BUFOVF_POS    ( 2 )            /* (SERCOM_SPI_STATUS) Buffer Overflow */
#define SERCOM_SPI_STATUS_BUFOVF        (0x1ul << SERCOM_SPI_STATUS_BUFOVF_POS)
#define SERCOM_SPI_STATUS_MASK          ( 0x0004ul )     /* (SERCOM_SPI_STATUS) MASK Register */

#define SERCOM_SPI_INTFLAG_DRE_POS      ( 0 )            /*  Data Register Empty Interrupt */
#define SERCOM_SPI_INTFLAG_DRE_MASK     (0x1ul << SERCOM_SPI_INTFLAG_DRE_POS)
#define SERCOM_SPI_INTFLAG_TXC_POS      ( 1 )            /* Transmit Complete Interrupt */
#define SERCOM_SPI_INTFLAG_TXC_MASK     (0x1ul << SERCOM_SPI_INTFLAG_TXC_POS)
#define SERCOM_SPI_INTFLAG_RXC_POS      ( 2 )           /* Receive Complete Interrupt */
#define SERCOM_SPI_INTFLAG_RXC_MASK     (0x1ul << SERCOM_SPI_INTFLAG_RXC_POS)
#define SERCOM_SPI_INTFLAG_SSL_POS      ( 3 )           /* Slave Select Low Interrupt Flag */
#define SERCOM_SPI_INTFLAG_SSL_MASK     (0x1ul << SERCOM_SPI_INTFLAG_SSL_POS)
#define SERCOM_SPI_INTFLAG_ERROR_POS    ( 7 )           /* Combined Error Interrupt */
#define SERCOM_SPI_INTFLAG_ERROR_MASK   (0x1ul << SERCOM_SPI_INTFLAG_ERROR_POS)
#define SERCOM_SPI_INTFLAG_MASK         ( 0x8Ful )      /* (SERCOM_SPI_INTFLAG) MASK Register */

#define SERCOM_SPI_INTENSET_DRE_POS     ( 0 )           /* Data Register Empty Interrupt Enable */
#define SERCOM_SPI_INTENSET_DRE         (0x1ul << SERCOM_SPI_INTENSET_DRE_POS)
#define SERCOM_SPI_INTENSET_TXC_POS     ( 1 )           /* Transmit Complete Interrupt Enable */
#define SERCOM_SPI_INTENSET_TXC         (0x1ul << SERCOM_SPI_INTENSET_TXC_POS)
#define SERCOM_SPI_INTENSET_RXC_POS     ( 2 )           /* Receive Complete Interrupt Enable */
#define SERCOM_SPI_INTENSET_RXC         (0x1ul << SERCOM_SPI_INTENSET_RXC_POS)
#define SERCOM_SPI_INTENSET_SSL_POS     ( 3 )           /* Slave Select Low Interrupt Enable */
#define SERCOM_SPI_INTENSET_SSL         (0x1ul << SERCOM_SPI_INTENSET_SSL_POS)
#define SERCOM_SPI_INTENSET_ERROR_POS   ( 7 )           /* Combined Error Interrupt Enable */
#define SERCOM_SPI_INTENSET_ERROR       (0x1ul << SERCOM_SPI_INTENSET_ERROR_POS)
#define SERCOM_SPI_INTENSET_MASK        ( 0x8Ful )      /* (SERCOM_SPI_INTENSET) MASK Register */


#define SERCOM_SPI_INTENCLR_DRE_POS     ( 0 )           /* Data Register Empty Interrupt Disable */
#define SERCOM_SPI_INTENCLR_DRE         (0x1ul << SERCOM_SPI_INTENCLR_DRE_POS)
#define SERCOM_SPI_INTENCLR_TXC_POS     ( 1 )           /* Transmit Complete Interrupt Disable */
#define SERCOM_SPI_INTENCLR_TXC         (0x1ul << SERCOM_SPI_INTENCLR_TXC_POS)
#define SERCOM_SPI_INTENCLR_RXC_POS     ( 2 )           /* Receive Complete Interrupt Disable */
#define SERCOM_SPI_INTENCLR_RXC         (0x1ul << SERCOM_SPI_INTENCLR_RXC_POS)
#define SERCOM_SPI_INTENCLR_SSL_POS     ( 3 )           /* Slave Select Low Interrupt Disable */
#define SERCOM_SPI_INTENCLR_SSL         (0x1ul << SERCOM_SPI_INTENCLR_SSL_POS)
#define SERCOM_SPI_INTENCLR_ERROR_POS   ( 7 )           /* Combined Error Interrupt Disable */
#define SERCOM_SPI_INTENCLR_ERROR       (0x1ul << SERCOM_SPI_INTENCLR_ERROR_POS)
#define SERCOM_SPI_INTENCLR_MASK        ( 0x8Ful )      /* (SERCOM_SPI_INTENCLR) MASK Register */

#define SERCOM_SPI_BAUD_BAUD_POS        ( 0 )           /* (SERCOM_SPI_BAUD) Baud Rate Value */
#define SERCOM_SPI_BAUD_BAUD_MASK       (0xFFul << SERCOM_SPI_BAUD_BAUD_POS)
#define SERCOM_SPI_BAUD_BAUD(value)     (SERCOM_SPI_BAUD_BAUD_MASK & ((value) << \
                                                                SERCOM_SPI_BAUD_BAUD_POS))
#define SERCOM_SPI_BAUD_MASK            ( 0xFFul )      /* (SERCOM_SPI_BAUD) MASK Register */

#define SERCOM_SPI_CTRLB_CHSIZE_POS     ( 0 )           /* (SERCOM_SPI_CTRLB) Character Size */
#define SERCOM_SPI_CTRLB_CHSIZE_MASK    (0x7ul << SERCOM_SPI_CTRLB_CHSIZE_POS)
#define SERCOM_SPI_CTRLB_CHSIZE(value)  (SERCOM_SPI_CTRLB_CHSIZE_MASK & ((value) << \
                                                                SERCOM_SPI_CTRLB_CHSIZE_POS))
#define SERCOM_SPI_CTRLB_PLOADEN_POS    ( 6 )           /* (SERCOM_SPI_CTRLB) Data Preload Enable */
#define SERCOM_SPI_CTRLB_PLOADEN        (0x1ul << SERCOM_SPI_CTRLB_PLOADEN_POS)
#define SERCOM_SPI_CTRLB_SSDE_POS       ( 9 )           /* Slave Select Low Detect Enable */
#define SERCOM_SPI_CTRLB_SSDE           (0x1ul << SERCOM_SPI_CTRLB_SSDE_POS)
#define SERCOM_SPI_CTRLB_MSSEN_POS      ( 13 )          /* Master Slave Select Enable */
#define SERCOM_SPI_CTRLB_MSSEN          (0x1ul << SERCOM_SPI_CTRLB_MSSEN_POS)
#define SERCOM_SPI_CTRLB_AMODE_POS      ( 14 )          /* (SERCOM_SPI_CTRLB) Address Mode */
#define SERCOM_SPI_CTRLB_AMODE_MASK     (0x3ul << SERCOM_SPI_CTRLB_AMODE_POS)
#define SERCOM_SPI_CTRLB_AMODE(value)   (SERCOM_SPI_CTRLB_AMODE_MASK & ((value) << \
                                                                SERCOM_SPI_CTRLB_AMODE_POS))
#define SERCOM_SPI_CTRLB_RXEN_POS       ( 17 )          /* (SERCOM_SPI_CTRLB) Receiver Enable */
#define SERCOM_SPI_CTRLB_RXEN           (0x1ul << SERCOM_SPI_CTRLB_RXEN_POS)
#define SERCOM_SPI_CTRLB_MASK           ( 0x0002E247ul )/* (SERCOM_SPI_CTRLB) MASK Register */

#define SERCOM_SPI_CTRLA_SWRST_POS      ( 0 )           /* (SERCOM_SPI_CTRLA) Software Reset */
#define SERCOM_SPI_CTRLA_SWRST_MASK     (0x1ul << SERCOM_SPI_CTRLA_SWRST_POS)
#define SERCOM_SPI_CTRLA_ENABLE_POS     ( 1 )           /* (SERCOM_SPI_CTRLA) Enable */
#define SERCOM_SPI_CTRLA_ENABLE_MASK    (0x1ul << SERCOM_SPI_CTRLA_ENABLE_POS)
#define SERCOM_SPI_CTRLA_MODE_POS       ( 2 )           /* (SERCOM_SPI_CTRLA) Operating Mode */
#define SERCOM_SPI_CTRLA_MASTER_MODE    (0x3 << SERCOM_SPI_CTRLA_MODE_POS);
#define SERCOM_SPI_CTRLA_SLAVE_MODE     (0x2 << SERCOM_SPI_CTRLA_MODE_POS);

#define SERCOM_SPI_CTRLA_MODE_MASK      (0x7ul << SERCOM_SPI_CTRLA_MODE_POS)
#define SERCOM_SPI_CTRLA_MODE(value)    (SERCOM_SPI_CTRLA_MODE_MASK & ((value) << \
                                                                SERCOM_SPI_CTRLA_MODE_POS))
#define SERCOM_SPI_CTRLA_RUNSTDBY_POS   ( 7 )           /* (SERCOM_SPI_CTRLA) Run during Standby */
#define SERCOM_SPI_CTRLA_RUNSTDBY       (0x1ul << SERCOM_SPI_CTRLA_RUNSTDBY_POS)
#define SERCOM_SPI_CTRLA_IBON_POS       ( 8 )           /* Immediate Buffer Overflow Notification */
#define SERCOM_SPI_CTRLA_IBON           (0x1ul << SERCOM_SPI_CTRLA_IBON_POS)
#define SERCOM_SPI_CTRLA_DOPO_POS       ( 16 )          /* (SERCOM_SPI_CTRLA) Data Out Pinout */
#define SERCOM_SPI_CTRLA_DOPO_MASK      (0x3ul << SERCOM_SPI_CTRLA_DOPO_POS)
#define SERCOM_SPI_CTRLA_DOPO(value)    (SERCOM_SPI_CTRLA_DOPO_MASK & ((value) << \
                                                                  SERCOM_SPI_CTRLA_DOPO_POS))
#define SERCOM_SPI_CTRLA_DIPO_POS       ( 20 )          /* (SERCOM_SPI_CTRLA) Data In Pinout */
#define SERCOM_SPI_CTRLA_DIPO_MASK      (0x3ul << SERCOM_SPI_CTRLA_DIPO_POS)
#define SERCOM_SPI_CTRLA_DIPO(value)    (SERCOM_SPI_CTRLA_DIPO_MASK & ((value) << \
                                                                 SERCOM_SPI_CTRLA_DIPO_POS))
#define SERCOM_SPI_CTRLA_FORM_POS       ( 24 )          /* (SERCOM_SPI_CTRLA) Frame Format */
#define SERCOM_SPI_CTRLA_FORM_MASK      (0xFul << SERCOM_SPI_CTRLA_FORM_POS)
#define SERCOM_SPI_CTRLA_FORM(value)    (SERCOM_SPI_CTRLA_FORM_MASK & ((value) << \
                                                                   SERCOM_SPI_CTRLA_FORM_POS))
#define SERCOM_SPI_CTRLA_CPHA_POS       ( 28 )          /* (SERCOM_SPI_CTRLA) Clock Phase */
#define SERCOM_SPI_CTRLA_CPHA           (0x1ul << SERCOM_SPI_CTRLA_CPHA_POS)
#define SERCOM_SPI_CTRLA_CPOL_POS       ( 29 )           /* (SERCOM_SPI_CTRLA) Clock Polarity */
#define SERCOM_SPI_CTRLA_CPOL           (0x1ul << SERCOM_SPI_CTRLA_CPOL_POS)
#define SERCOM_SPI_CTRLA_DORD_POS       ( 30 )           /* (SERCOM_SPI_CTRLA) Data Order */
#define SERCOM_SPI_CTRLA_DORD           (0x1ul << SERCOM_SPI_CTRLA_DORD_POS)
#define SERCOM_SPI_CTRLA_MASK           ( 0x7F33019Ful ) /* (SERCOM_SPI_CTRLA) MASK Register */


/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

typedef struct 
{
    SYS_REG     	CTRLA;       /* Offset: 0x00 (R/W 32) SPI Control A */
    SYS_REG    		CTRLB;       /* Offset: 0x04 (R/W 32) SPI Control B */
    SYS_REG    		CTRLC;       /* Offset: 0x04 (R/W 32) SPI Control B */
    SYS_REG_BYTE        BAUD;        /* Offset: 0x0C (R/W  8) SPI Baud Rate */
    SYS_REG_BYTE        Reserved2[7];
    SYS_REG_BYTE        INTENCLR;    /* Offset: 0x14 (R/W  8) SPI Interrupt Enable Clear */
    SYS_REG_BYTE        Reserved3[1];
    SYS_REG_BYTE        INTENSET;    /* Offset: 0x16 (R/W  8) SPI Interrupt Enable Set */
    SYS_REG_BYTE        Reserved4[1];
    SYS_REG_BYTE        INTFLAG;     /* Offset: 0x18 (R/W  8) SPI Interrupt Flag Status and Clear */
    SYS_REG_BYTE        Reserved5[1];
    SYS_REG_HWORD       STATUS;      /* Offset: 0x1A (R/W 16) SPI Status */
    SYS_REG             SYNCBUSY;    /* Offset: 0x1C (R/  32) SPI Synchronization Busy */
    SYS_REG_BYTE        Reserved6[2];
    SYS_REG_HWORD	LENGTH;
    SYS_REG             ADDR;        /* Offset: 0x24 (R/W 32) SPI Address */
    SYS_REG             DATA;        /* Offset: 0x28 (R/W 32) SPI Data */
    SYS_REG_BYTE        Reserved7[4];
    SYS_REG_BYTE        DBGCTRL;     /* Offset: 0x30 (R/W  8) SPI Debug Control */
}ST_SPI_SYS_REGS_t;

/**************************************************************************************************/
/* Private Functions Section                                                                      */
/**************************************************************************************************/

/* Function to calculate Baudrate */
static INT8U SPI_CalculateBaudrate(INT32U u32_lBaudrate);

#endif

/**************************************************************************************************/
/*End of SPI_Priv.h                         			                                  */
/**************************************************************************************************/
