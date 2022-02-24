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
/* \File Name   : UART.c                                                                          */
/* \Author      : Kishore D                                                                       */
/* \Version 		: v1.0                                                                            */
/* \Date        : 23/08/2018                                                                      */
/*                                                                                                */
/* @Description : UART Driver                                                                     */
/**************************************************************************************************/

#ifndef _UART_PRIV_H_ 
#define _UART_PRIV_H_ 

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

#define SERCOM0_BASE_ADDRESS                                ( 0x40003000 ) 
#define SERCOM1_BASE_ADDRESS                                ( 0x40003400 )
#define SERCOM2_BASE_ADDRESS                                ( 0x41012000 )
#define SERCOM3_BASE_ADDRESS                                ( 0x41014000 )
#define SERCOM4_BASE_ADDRESS    		       			( 0x43000000 ) 
#define SERCOM5_BASE_ADDRESS   	    	    			     ( 0x43000400 )
#define SERCOM6_BASE_ADDRESS							( 0x43000800 )
#define SERCOM7_BASE_ADDRESS							( 0x43000C00 )

#define MAX_SERCOM_CHANNELS							( 8 )

/****************        CTRLA REGISTER MASKING          *****************************************/

#define SERCOM_USART_CTRLA_SWRST_POS 						( 0 )   
#define SERCOM_USART_CTRLA_SWRST    						(0x1ul << SERCOM_USART_CTRLA_SWRST_POS)
#define SERCOM_USART_CTRLA_ENABLE_POS 					    ( 1 )  
#define SERCOM_USART_CTRLA_ENABLE  							(0x1ul << SERCOM_USART_CTRLA_ENABLE_POS)
#define SERCOM_USART_CTRLA_MODE_POS 						( 2 )   
#define SERCOM_USART_CTRLA_MODE_Msk 						(0x7ul << SERCOM_USART_CTRLA_MODE_POS)
#define SERCOM_USART_CTRLA_RUNSTDBY_POS 				    ( 7 )  
#define SERCOM_USART_CTRLA_RUNSTDBY 						(0x1ul << SERCOM_USART_CTRLA_RUNSTDBY_POS)
#define SERCOM_USART_CTRLA_IBON_POS 						( 8 )   
#define SERCOM_USART_CTRLA_IBON     						(0x1ul << SERCOM_USART_CTRLA_IBON_POS)
#define SERCOM_USART_CTRLA_SAMPR_POS 						( 13 )  
#define SERCOM_USART_CTRLA_SAMPR_Msk 						(0x7ul << SERCOM_USART_CTRLA_SAMPR_POS)
#define SERCOM_USART_CTRLA_TXPO_POS 						( 16 )  
#define SERCOM_USART_CTRLA_TXPO_Msk 						(0x3ul << SERCOM_USART_CTRLA_TXPO_POS)
#define SERCOM_USART_CTRLA_RXPO_POS 						( 20 ) 
#define SERCOM_USART_CTRLA_RXPO_Msk 						(0x3ul << SERCOM_USART_CTRLA_RXPO_POS)
#define SERCOM_USART_CTRLA_SAMPA_POS 						( 22 )  
#define SERCOM_USART_CTRLA_SAMPA_Msk 						(0x3ul << SERCOM_USART_CTRLA_SAMPA_POS)
#define SERCOM_USART_CTRLA_FORM_POS 						( 24 ) 
#define SERCOM_USART_CTRLA_FORM_Msk 						(0xFul << SERCOM_USART_CTRLA_FORM_POS)
#define SERCOM_USART_CTRLA_CMODE_POS 						( 28 ) 
#define SERCOM_USART_CTRLA_CMODE    						(0x1ul << SERCOM_USART_CTRLA_CMODE_POS)
#define SERCOM_USART_CTRLA_CPOL_POS 						( 29 )  
#define SERCOM_USART_CTRLA_CPOL     						(0x1ul << SERCOM_USART_CTRLA_CPOL_POS)
#define SERCOM_USART_CTRLA_DORD_POS 						( 30 )  
#define SERCOM_USART_CTRLA_DORD     						(0x1ul << SERCOM_USART_CTRLA_DORD_POS)

/****************        CTRLB REGISTER MASKING          *****************************************/

#define SERCOM_USART_CTRLB_CHSIZE_POS 					    ( 0 )   
#define SERCOM_USART_CTRLB_CHSIZE_Msk 					    (0x7ul << SERCOM_USART_CTRLB_CHSIZE_POS)
#define SERCOM_USART_CTRLB_SBMODE_POS 					    ( 6 )  
#define SERCOM_USART_CTRLB_SBMODE   						(0x1ul << SERCOM_USART_CTRLB_SBMODE_POS)
#define SERCOM_USART_CTRLB_COLDEN_POS	 					( 8 )   
#define SERCOM_USART_CTRLB_COLDEN   						(0x1ul << SERCOM_USART_CTRLB_COLDEN_POS)
#define SERCOM_USART_CTRLB_SFDE_POS 						( 9 )  
#define SERCOM_USART_CTRLB_SFDE     						(0x1ul << SERCOM_USART_CTRLB_SFDE_POS)
#define SERCOM_USART_CTRLB_ENC_POS  						( 10 )  
#define SERCOM_USART_CTRLB_ENC      						(0x1ul << SERCOM_USART_CTRLB_ENC_POS)
#define SERCOM_USART_CTRLB_PMODE_POS 						( 13 )  
#define SERCOM_USART_CTRLB_PMODE    						(0x1ul << SERCOM_USART_CTRLB_PMODE_POS)
#define SERCOM_USART_CTRLB_TXEN_POS 						( 16 )  
#define SERCOM_USART_CTRLB_TXEN     						(0x1ul << SERCOM_USART_CTRLB_TXEN_POS)
#define SERCOM_USART_CTRLB_RXEN_POS 						( 17 )  
#define SERCOM_USART_CTRLB_RXEN     						(0x1ul << SERCOM_USART_CTRLB_RXEN_POS)

/****************        INTENCLR REGISTER MASKING          **************************************/

#define SERCOM_USART_INTENCLR_DRE_POS 					    ( 0 )  
#define SERCOM_USART_INTENCLR_DRE   						(0x1ul << SERCOM_USART_INTENCLR_DRE_POS)
#define SERCOM_USART_INTENCLR_TXC_POS 					    ( 1 )   
#define SERCOM_USART_INTENCLR_TXC   						(0x1ul << SERCOM_USART_INTENCLR_TXC_POS)
#define SERCOM_USART_INTENCLR_RXC_POS 					    ( 2 )  
#define SERCOM_USART_INTENCLR_RXC   						(0x1ul << SERCOM_USART_INTENCLR_RXC_POS)
#define SERCOM_USART_INTENCLR_RXS_POS 					    ( 3 )  
#define SERCOM_USART_INTENCLR_RXS   						(0x1ul << SERCOM_USART_INTENCLR_RXS_POS)
#define SERCOM_USART_INTENCLR_CTSIC_POS 				    ( 4 )  
#define SERCOM_USART_INTENCLR_CTSIC 						(0x1ul << SERCOM_USART_INTENCLR_CTSIC_POS)
#define SERCOM_USART_INTENCLR_RXBRK_POS 				    ( 5 )   
#define SERCOM_USART_INTENCLR_RXBRK 						(0x1ul << SERCOM_USART_INTENCLR_RXBRK_POS)
#define SERCOM_USART_INTENCLR_ERROR_POS 				    ( 7 )  
#define SERCOM_USART_INTENCLR_ERROR 						(0x1ul << SERCOM_USART_INTENCLR_ERROR_POS)    

/****************        INTENSET REGISTER MASKING          **************************************/

#define SERCOM_USART_INTENSET_DRE_POS 					    ( 0 )  
#define SERCOM_USART_INTENSET_DRE   						(0x1ul << SERCOM_USART_INTENSET_DRE_POS)
#define SERCOM_USART_INTENSET_TXC_POS 					    ( 1 )   
#define SERCOM_USART_INTENSET_TXC   						(0x1ul << SERCOM_USART_INTENSET_TXC_POS)
#define SERCOM_USART_INTENSET_RXC_POS 					    ( 2 )   
#define SERCOM_USART_INTENSET_RXC  	 						(0x1ul << SERCOM_USART_INTENSET_RXC_POS)
#define SERCOM_USART_INTENSET_RXS_POS 					    ( 3 )  
#define SERCOM_USART_INTENSET_RXS   						(0x1ul << SERCOM_USART_INTENSET_RXS_POS)
#define SERCOM_USART_INTENSET_CTSIC_POS 				    ( 4 )  
#define SERCOM_USART_INTENSET_CTSIC 						(0x1ul << SERCOM_USART_INTENSET_CTSIC_POS)
#define SERCOM_USART_INTENSET_RXBRK_POS 				    ( 5 )   
#define SERCOM_USART_INTENSET_RXBRK 						(0x1ul << SERCOM_USART_INTENSET_RXBRK_POS)
#define SERCOM_USART_INTENSET_ERROR_POS 				    ( 7 )         
#define SERCOM_USART_INTENSET_ERROR 						(0x1ul << SERCOM_USART_INTENSET_ERROR_POS)
   
/****************        INTFLAG REGISTER MASKING          ***************************************/

#define SERCOM_USART_INTFLAG_DRE_POS 						( 0 )  
#define SERCOM_USART_INTFLAG_DRE    						(0x1ul << SERCOM_USART_INTFLAG_DRE_POS)
#define SERCOM_USART_INTFLAG_TXC_POS 						( 1 )   
#define SERCOM_USART_INTFLAG_TXC    						(0x1ul << SERCOM_USART_INTFLAG_TXC_POS)
#define SERCOM_USART_INTFLAG_RXC_POS 						( 2 )   
#define SERCOM_USART_INTFLAG_RXC    						(0x1ul << SERCOM_USART_INTFLAG_RXC_POS)
#define SERCOM_USART_INTFLAG_RXS_POS 						( 3 ) 
#define SERCOM_USART_INTFLAG_RXS    						(0x1ul << SERCOM_USART_INTFLAG_RXS_POS)
#define SERCOM_USART_INTFLAG_CTSIC_POS 					    ( 4 )   
#define SERCOM_USART_INTFLAG_CTSIC  						(0x1ul << SERCOM_USART_INTFLAG_CTSIC_POS)
#define SERCOM_USART_INTFLAG_RXBRK_POS 					    ( 5 )   
#define SERCOM_USART_INTFLAG_RXBRK  						(0x1ul << SERCOM_USART_INTFLAG_RXBRK_POS)
#define SERCOM_USART_INTFLAG_ERROR_POS 					    ( 7 )   
#define SERCOM_USART_INTFLAG_ERROR  						(0x1ul << SERCOM_USART_INTFLAG_ERROR_POS)
      
/****************        SYNCBUSY REGISTER MASKING          **************************************/

#define SERCOM_USART_SYNCBUSY_SWRST_POS 				    ( 0 )   
#define SERCOM_USART_SYNCBUSY_SWRST 						(0x1ul << SERCOM_USART_SYNCBUSY_SWRST_POS)
#define SERCOM_USART_SYNCBUSY_ENABLE_POS 				    ( 1 )  
#define SERCOM_USART_SYNCBUSY_ENABLE 						(0x1ul << SERCOM_USART_SYNCBUSY_ENABLE_POS)
#define SERCOM_USART_SYNCBUSY_CTRLB_POS 				    ( 2 )   
#define SERCOM_USART_SYNCBUSY_CTRLB 						(0x1ul << SERCOM_USART_SYNCBUSY_CTRLB_POS) 

/****************        STATUS REGISTER MASKING          ****************************************/

#define SERCOM_USART_STATUS_PERR_POS 						( 0 )          
#define SERCOM_USART_STATUS_PERR    						(0x1ul << SERCOM_USART_STATUS_PERR_POS)
#define SERCOM_USART_STATUS_FERR_POS 						( 1 )           
#define SERCOM_USART_STATUS_FERR    						(0x1ul << SERCOM_USART_STATUS_FERR_POS)
#define SERCOM_USART_STATUS_BUFOVF_POS 					    ( 2 )           
#define SERCOM_USART_STATUS_BUFOVF  						(0x1ul << SERCOM_USART_STATUS_BUFOVF_POS)
#define SERCOM_USART_STATUS_CTS_POS 						( 3 )           
#define SERCOM_USART_STATUS_CTS     						(0x1ul << SERCOM_USART_STATUS_CTS_POS)
#define SERCOM_USART_STATUS_ISF_POS 						( 4 )           
#define SERCOM_USART_STATUS_ISF     						(0x1ul << SERCOM_USART_STATUS_ISF_POS)
#define SERCOM_USART_STATUS_COLL_POS 						( 5 )           
#define SERCOM_USART_STATUS_COLL    						(0x1ul << SERCOM_USART_STATUS_COLL_POS) 

typedef struct 
{ 
		SYS_REG   	CTRLA;          /* Offset: 0x00 (R/W 32) USART Control A */
		SYS_REG   	CTRLB;          /* Offset: 0x04 (R/W 32) USART Control B */
		SYS_REG   	CTRLC;          /* Offset: 0x04 (R/W 32) USART Control C */
		SYS_REG_HWORD  BAUD;           /* Offset: 0x0C (R/W 16) USART Baud Rate */
		SYS_REG_BYTE   RXPL;           /* Offset: 0x0E (R/W  8) USART Receive Pulse Length */
		SYS_REG_BYTE   Reserved1[5];
		SYS_REG_BYTE 	INTENCLR;       /* Offset: 0x14 (R/W  8) USART Interrupt Enable Clear */
		SYS_REG_BYTE   Reserved2;
		SYS_REG_BYTE 	INTENSET;       /* Offset: 0x16 (R/W  8) USART Interrupt Enable Set */
		SYS_REG_BYTE   Reserved3;
		SYS_REG_BYTE 	INTFLAG;        /* Offset: 0x18 (R/W  8) USART Interrupt Flag Status and Clear */
		SYS_REG_BYTE   Reserved4;
		SYS_REG_HWORD  STATUS;         /* Offset: 0x1A (R/W 16) USART Status */
		SYS_REG 		SYNCBUSY;       /* Offset: 0x1C (R/  32) USART Synchronization Busy */
		SYS_REG_BYTE	RXERRCNT;
		SYS_REG_BYTE	Reserved5;
		SYS_REG_HWORD	LENGTH;
		SYS_REG_BYTE	Reserved6[4];
		SYS_REG		DATA;
		SYS_REG_BYTE   Reserved7[4];
		SYS_REG_BYTE	DBGCTRL;        /* Offset: 0x30 (R/W  8) USART Debug Control */
} ST_USART_BASE_REGS_t;

/**************************************************************************************************/
/* Private Global Variables Section                                                               */
/**************************************************************************************************/

/**************************************************************************************************/
/*End of UART_Priv.h                          			                                          */
/**************************************************************************************************/

#endif