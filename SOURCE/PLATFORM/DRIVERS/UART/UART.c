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

/**************************************************************************************************/
/* System Header Files Section                                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/* User Header Files Section                                                                      */
/**************************************************************************************************/

#include "Includes.h"

#include "GCLK.h"
#include "MCLK.h"
#include "NVIC.h"

#include "UART.h"
#include "UART_Priv.h"

/**************************************************************************************************/
/* Global Definitions Section                                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/* Global Variables Section                                                                       */
/**************************************************************************************************/

/* Structure Pointer to access UART System Registers */
ST_USART_BASE_REGS_t *p_stgUSART_BASE_REGS[MAX_SERCOM_CHANNELS]= 
{
    (ST_USART_BASE_REGS_t *)SERCOM0_BASE_ADDRESS,
    (ST_USART_BASE_REGS_t *)SERCOM1_BASE_ADDRESS,
    (ST_USART_BASE_REGS_t *)SERCOM2_BASE_ADDRESS,
    (ST_USART_BASE_REGS_t *)SERCOM3_BASE_ADDRESS,
    (ST_USART_BASE_REGS_t *)SERCOM4_BASE_ADDRESS,
    (ST_USART_BASE_REGS_t *)SERCOM5_BASE_ADDRESS,
    (ST_USART_BASE_REGS_t *)SERCOM6_BASE_ADDRESS,
    (ST_USART_BASE_REGS_t *)SERCOM7_BASE_ADDRESS,
};
																				
/* Uart User Handlers */
void (*fp_gUARTUserHandler[MAX_SERCOM_CHANNELS])(INT8U);

/**************************************************************************************************/
/* Function Name   : void SERCOM0_Handler(void)			                                   			      */
/*                                                                                                */
/* Description     : SERCOM0 System Handler                                                       */
/*                                                                                                */
/**************************************************************************************************/	
																																 
void SERCOM0_0_Handler(void)
{
	INT8U u8_lRxData = 0;
    
	/* Checking for Receive Complete Status flag */
	if(p_stgUSART_BASE_REGS[0]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
	{
		/*Reading Data to clear the RXC flag */
		u8_lRxData = p_stgUSART_BASE_REGS[0]->DATA;
			
		if(PNULL != (fp_gUARTUserHandler[0]))
		{
			/* Calling User Handler */
			fp_gUARTUserHandler[0](u8_lRxData);
		}
	}
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM1_Handler(void)                                   				        */
/*                                                                                                */
/* Description     :   SERCOM1 System Handler                                                     */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM0_1_Handler(void)
{
    INT8U u8_lRxData = 0;
    
    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[0]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[0]->DATA;

        if(PNULL != (fp_gUARTUserHandler[0]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[0](u8_lRxData);
        }
    }
}		

/**************************************************************************************************/
/* Function Name   :  void SERCOM2_Handler(void)                                   			          */
/*                                                                                                */
/* Description     :  SERCOM2 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/	

void SERCOM0_2_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[0]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[0]->DATA;

        if(PNULL != (fp_gUARTUserHandler[0]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[0](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				  			*/
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM0_3_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[0]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[0]->DATA;

        if(PNULL != (fp_gUARTUserHandler[0]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[0](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				  			*/
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM1_0_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[1]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[1]->DATA;

        if(PNULL != (fp_gUARTUserHandler[1]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[1](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM1_Handler(void)                                   				        */
/*                                                                                                */
/* Description     :   SERCOM1 System Handler                                                     */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM1_1_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[1]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[1]->DATA;

        if(PNULL != (fp_gUARTUserHandler[1]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[1](u8_lRxData);
        }
    }
}		

/**************************************************************************************************/
/* Function Name   :  void SERCOM2_Handler(void)                                   			          */
/*                                                                                                */
/* Description     :  SERCOM2 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/	

#if 0

void SERCOM1_2_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[1]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[1]->DATA;

        if(PNULL != (fp_gUARTUserHandler[1]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[1](u8_lRxData);
        }
    }
}	

#endif

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				        */
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM1_3_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[1]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[1]->DATA;

        if(PNULL != (fp_gUARTUserHandler[1]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[1](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				  			*/
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM2_0_Handler(void)
{
	INT8U u8_lRxData = 0;
    
	/* Checking for Receive Complete Status flag */
	if(p_stgUSART_BASE_REGS[2]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
	{
		/*Reading Data to clear the RXC flag */
		u8_lRxData = p_stgUSART_BASE_REGS[2]->DATA;
			
		if(PNULL != (fp_gUARTUserHandler[2]))
		{
			/* Calling User Handler */
			fp_gUARTUserHandler[2](u8_lRxData);
		}
	}
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM1_Handler(void)                                   				        */
/*                                                                                                */
/* Description     :   SERCOM1 System Handler                                                     */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM2_1_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[2]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[1]->DATA;

        if(PNULL != (fp_gUARTUserHandler[2]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[2](u8_lRxData);
        }
    }
}		

/**************************************************************************************************/
/* Function Name   :  void SERCOM2_Handler(void)                                   			          */
/*                                                                                                */
/* Description     :  SERCOM2 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/	

void SERCOM2_2_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[2]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[2]->DATA;

        if(PNULL != (fp_gUARTUserHandler[2]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[2](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				        */
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM2_3_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[2]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[2]->DATA;

        if(PNULL != (fp_gUARTUserHandler[2]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[2](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				  			*/
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM3_0_Handler(void)
{
	INT8U u8_lRxData = 0;
    
	/* Checking for Receive Complete Status flag */
	if(p_stgUSART_BASE_REGS[3]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
	{
		/*Reading Data to clear the RXC flag */
		u8_lRxData = p_stgUSART_BASE_REGS[3]->DATA;
			
		if(PNULL != (fp_gUARTUserHandler[3]))
		{
			/* Calling User Handler */
			fp_gUARTUserHandler[3](u8_lRxData);
		}
	}
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM1_Handler(void)                                   				        */
/*                                                                                                */
/* Description     :   SERCOM1 System Handler                                                     */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM3_1_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[3]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[3]->DATA;

        if(PNULL != (fp_gUARTUserHandler[3]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[3](u8_lRxData);
        }
    }
}		

/**************************************************************************************************/
/* Function Name   :  void SERCOM2_Handler(void)                                   			          */
/*                                                                                                */
/* Description     :  SERCOM2 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/	

void SERCOM3_2_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[3]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[3]->DATA;

        if(PNULL != (fp_gUARTUserHandler[3]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[3](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				        */
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM3_3_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[3]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[3]->DATA;

        if(PNULL != (fp_gUARTUserHandler[3]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[3](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				  			*/
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM4_0_Handler(void)
{
	INT8U u8_lRxData = 0;
    
	/* Checking for Receive Complete Status flag */
	if(p_stgUSART_BASE_REGS[4]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
	{
		/*Reading Data to clear the RXC flag */
		u8_lRxData = p_stgUSART_BASE_REGS[4]->DATA;
			
		if(PNULL != (fp_gUARTUserHandler[4]))
		{
			/* Calling User Handler */
			fp_gUARTUserHandler[4](u8_lRxData);
		}
	}
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM1_Handler(void)                                   				        */
/*                                                                                                */
/* Description     :   SERCOM1 System Handler                                                     */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM4_1_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[4]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[4]->DATA;

        if(PNULL != (fp_gUARTUserHandler[4]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[4](u8_lRxData);
        }
    }
}		

/**************************************************************************************************/
/* Function Name   :  void SERCOM2_Handler(void)                                   			          */
/*                                                                                                */
/* Description     :  SERCOM2 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/	

void SERCOM4_2_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[4]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[4]->DATA;

        if(PNULL != (fp_gUARTUserHandler[4]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[4](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				        */
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM4_3_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[4]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[4]->DATA;

        if(PNULL != (fp_gUARTUserHandler[4]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[4](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				  			*/
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM5_0_Handler(void)
{
	INT8U u8_lRxData = 0;
    
	/* Checking for Receive Complete Status flag */
	if(p_stgUSART_BASE_REGS[5]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
	{
		/*Reading Data to clear the RXC flag */
		u8_lRxData = p_stgUSART_BASE_REGS[5]->DATA;
			
		if(PNULL != (fp_gUARTUserHandler[5]))
		{
			/* Calling User Handler */
			fp_gUARTUserHandler[5](u8_lRxData);
		}
	}
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM1_Handler(void)                                   				        */
/*                                                                                                */
/* Description     :   SERCOM1 System Handler                                                     */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM5_1_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[5]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[5]->DATA;

        if(PNULL != (fp_gUARTUserHandler[5]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[5](u8_lRxData);
        }
    }
}		

/**************************************************************************************************/
/* Function Name   :  void SERCOM2_Handler(void)                                   			          */
/*                                                                                                */
/* Description     :  SERCOM2 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/	

void SERCOM5_2_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[5]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[5]->DATA;

        if(PNULL != (fp_gUARTUserHandler[5]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[5](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				        */
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM5_3_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[5]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[5]->DATA;

        if(PNULL != (fp_gUARTUserHandler[5]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[5](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				  			*/
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM6_0_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[6]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[6]->DATA;

        if(PNULL != (fp_gUARTUserHandler[6]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[6](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM1_Handler(void)                                   				        */
/*                                                                                                */
/* Description     :   SERCOM1 System Handler                                                     */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM6_1_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[6]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[6]->DATA;

        if(PNULL != (fp_gUARTUserHandler[6]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[6](u8_lRxData);
        }
    }
}		

/**************************************************************************************************/
/* Function Name   :  void SERCOM2_Handler(void)                                   			          */
/*                                                                                                */
/* Description     :  SERCOM2 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/	

void SERCOM6_2_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[6]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[6]->DATA;

        if(PNULL != (fp_gUARTUserHandler[6]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[6](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				        */
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM6_3_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[6]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[6]->DATA;

        if(PNULL != (fp_gUARTUserHandler[6]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[6](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				  			*/
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM7_0_Handler(void)
{
	INT8U u8_lRxData = 0;
    
	/* Checking for Receive Complete Status flag */
	if(p_stgUSART_BASE_REGS[7]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
	{
		/*Reading Data to clear the RXC flag */
		u8_lRxData = p_stgUSART_BASE_REGS[7]->DATA;
			
		if(PNULL != (fp_gUARTUserHandler[7]))
		{
			/* Calling User Handler */
			fp_gUARTUserHandler[7](u8_lRxData);
		}
	}
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM1_Handler(void)                                   				        */
/*                                                                                                */
/* Description     :   SERCOM1 System Handler                                                     */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM7_1_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[7]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[7]->DATA;

        if(PNULL != (fp_gUARTUserHandler[7]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[7](u8_lRxData);
        }
    }
}		

/**************************************************************************************************/
/* Function Name   :  void SERCOM2_Handler(void)                                   			          */
/*                                                                                                */
/* Description     :  SERCOM2 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/	

void SERCOM7_2_Handler(void)
{
    INT8U u8_lRxData = 0;

    /* Checking for Receive Complete Status flag */
    if(p_stgUSART_BASE_REGS[7]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
    {
        /*Reading Data to clear the RXC flag */
        u8_lRxData = p_stgUSART_BASE_REGS[7]->DATA;

        if(PNULL != (fp_gUARTUserHandler[7]))
        {
            /* Calling User Handler */
            fp_gUARTUserHandler[7](u8_lRxData);
        }
    }
}	

/**************************************************************************************************/
/* Function Name   :  void SERCOM3_Handler(void)                                   				 			  */
/*                                                                                                */
/* Description     :  SERCOM3 System Handler                                                      */
/*                                                                                                */
/**************************************************************************************************/

void SERCOM7_3_Handler(void)
{
	INT8U u8_lRxData = 0;
    
	/* Checking for Receive Complete Status flag */
	if(p_stgUSART_BASE_REGS[7]->INTFLAG & SERCOM_USART_INTFLAG_RXC)
	{
			/*Reading Data to clear the RXC flag */
			u8_lRxData = p_stgUSART_BASE_REGS[7]->DATA;
			
		if(PNULL != (fp_gUARTUserHandler[7]))
		{
			/* Calling User Handler */
			fp_gUARTUserHandler[7](u8_lRxData);
		}
	}
}	

/**************************************************************************************************/
/* Function Name   : void UART_Init(ST_UART_CONFIG_PARAMS_t *p_stfUARTConfigParams)               */
/*                                                                                                */
/* Description     : This function used to Initialize the UART                                    */
/*                                                                                                */
/* In Params       : *p_stfUARTConfigParams                                                       */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void UART_Init(ST_UART_CONFIG_PARAMS_t *p_stfUARTConfigParams)
{
    INT8U u8_lChannel = (INT8U)p_stfUARTConfigParams->en_mSERCOMChnl;
    INT16U u16_lBaud = 0;

    switch(u8_lChannel)
    {
    case SERCOM_CH_0 :
        MCLK_PeriphClkInit(MCLK_APBA, MCLK_APBA_SERCOM0);
        NVIC_EnableInterrupt(SERCOM0_2_IRQ);
        break;

    case SERCOM_CH_1 :
        MCLK_PeriphClkInit(MCLK_APBA, MCLK_APBA_SERCOM1);
        NVIC_EnableInterrupt(SERCOM1_2_IRQ);
        break;

    case SERCOM_CH_2 :
        MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_SERCOM2);
        NVIC_EnableInterrupt(SERCOM2_2_IRQ);
        break;

    case SERCOM_CH_3 :
        MCLK_PeriphClkInit(MCLK_APBB, MCLK_APBB_SERCOM3);
        NVIC_EnableInterrupt(SERCOM3_2_IRQ);
        break;

    case SERCOM_CH_4 :
        MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_SERCOM4);
        NVIC_EnableInterrupt(SERCOM4_2_IRQ);
        break;

    case SERCOM_CH_5 :
        MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_SERCOM5);
        NVIC_EnableInterrupt(SERCOM5_2_IRQ);
        break;

    case SERCOM_CH_6 :
        MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_SERCOM6);
       // NVIC_EnableInterrupt(SERCOM6_2_IRQ);
        break;

    case SERCOM_CH_7 :
        MCLK_PeriphClkInit(MCLK_APBD, MCLK_APBD_SERCOM7);
        //NVIC_EnableInterrupt(SERCOM7_2_IRQ);
        break;
    default :
        break;
    }
        
    GCLK_EnableSERCOMClock((EN_GCLK_SERCOM_CH_SEL_t )u8_lChannel);
    
    /* Reset the Sercom Channel registers */
    p_stgUSART_BASE_REGS[u8_lChannel]->CTRLA |= 0x01; 
    
    /* Waiting for Sync */
    while(p_stgUSART_BASE_REGS[u8_lChannel]->SYNCBUSY & 0x01);
    
    /* Select Internal clock and default Asynchronus com mode */
    p_stgUSART_BASE_REGS[u8_lChannel]->CTRLA |= 0x01 << 2;

    /* Select Rx Pad */
    p_stgUSART_BASE_REGS[u8_lChannel]->CTRLA |= p_stfUARTConfigParams->en_mRXPad << 20;
    
    /* Select Tx Pad */
    p_stgUSART_BASE_REGS[u8_lChannel]->CTRLA |= p_stfUARTConfigParams->en_mTXPad << 16;
    
    /* Select Charecter size */
    p_stgUSART_BASE_REGS[u8_lChannel]->CTRLB |= p_stfUARTConfigParams->en_mDataBits;
    
    /* Select LSB */
    p_stgUSART_BASE_REGS[u8_lChannel]->CTRLA |= 1 << 30;

    /* Stop Bit Mode */
    p_stgUSART_BASE_REGS[u8_lChannel]->CTRLB |= p_stfUARTConfigParams->en_mStopBits;
    
    /* Claiculate Baud value for Desired baud rate*/
    u16_lBaud = (INT16U)(65536 * (1 - (16 * (p_stfUARTConfigParams->u32_mBaudrate / 120000000.0))) + 0.5);
    
    /* Update Baudrate */
    p_stgUSART_BASE_REGS[u8_lChannel]->BAUD = u16_lBaud;
    
    /* Enable Tx And Rx */
    p_stgUSART_BASE_REGS[u8_lChannel]->CTRLB |= 0x03 << 16;
    
    while(p_stgUSART_BASE_REGS[u8_lChannel]->SYNCBUSY & 0x4);
    
    /* Enable Recive Interrupt */
    p_stgUSART_BASE_REGS[u8_lChannel]->INTENSET |= 0x04;

    /* Assigning Pointers for user handlers */
    fp_gUARTUserHandler[u8_lChannel] = p_stfUARTConfigParams->fp_USERHANDLER;
     
    /* Enable Sercom */
    p_stgUSART_BASE_REGS[u8_lChannel]->CTRLA |= 0x02;
    while(p_stgUSART_BASE_REGS[u8_lChannel]->SYNCBUSY & 0x2);
}

/**************************************************************************************************/
/* Function Name   : void UART_TransmitChar(EN_SERCOM_CH_SEL_t en_fChannel,INT8U u8_fData)        */
/*                                                                                                */
/* Description     : API to send char                                                             */
/*                                                                                                */
/* In Params       : EN_SERCOM_CH_SEL_t en_fChannel,INT8U u8_fData                                */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void UART_TransmitChar(EN_SERCOM_CH_SEL_t en_fChannel,INT8U u8_fData)
{
    while(!(p_stgUSART_BASE_REGS[en_fChannel]->INTFLAG & SERCOM_USART_INTFLAG_DRE));
     
	/* Writing Data to the DATA register */
	p_stgUSART_BASE_REGS[en_fChannel]->DATA = u8_fData;
    
    while(!(p_stgUSART_BASE_REGS[en_fChannel]->INTFLAG & SERCOM_USART_INTFLAG_TXC));
}

/**************************************************************************************************/
/* Function Name   : INT8U UART_Recieve_Char(EN_SERCOM_CH_SEL_t en_fChannel)    				  				*/
/*                                                                                                */
/* Description     :  API to receive char                                                         */
/*                                                                                                */
/* In Params       :  EN_SERCOM_CH_SEL_t en_fChannel                                              */
/*                                                                                                */
/* Out Params      :  void                                                                        */
/*                                                                                                */
/* Return Value    :  u8_lData                                                                    */
/**************************************************************************************************/

INT8U UART_RecieveChar(EN_SERCOM_CH_SEL_t en_fChannel)
{
	INT8U u8_lData = 0;
	
	/* Waiting for Recieve Complete flag (RXC) */
	while(!(p_stgUSART_BASE_REGS[en_fChannel]->INTFLAG & SERCOM_USART_INTFLAG_RXC));
	
	u8_lData = p_stgUSART_BASE_REGS[en_fChannel]->DATA;

	return u8_lData;
}

/**************************************************************************************************/
/* Function Name   : void UART_TransmitString(EN_SERCOM_CH_SEL_t en_fChannel,INT8U *u8_fstr)      */
/*                                                                                                */
/* Description     : API to send string                                                           */
/*                                                                                                */
/* In Params       : EN_SERCOM_CH_SEL_t en_fChannel,INT8U *u8_fstr                                */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void UART_TransmitString(EN_SERCOM_CH_SEL_t en_fChannel,INT8U *u8_fstr)
{
	/* Checking for End of String */
	while(*u8_fstr != '\0')
	{
		UART_TransmitChar(en_fChannel,* u8_fstr);
		
		u8_fstr++;
	}
}   

/**************************************************************************************************/
/* Function Name   : void UART_TransmitNumber(EN_SERCOM_CH_SEL_t en_fChannel,INT32U u32_fNumber)  */
/*                                                                                                */
/* Description     : API to send Number over UART                                                 */
/*                                                                                                */
/* In Params       : en_fChannel, u32_fNumber                                                     */
/*                                                                                                */
/* Out Params      : void                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void UART_TransmitNumber(EN_SERCOM_CH_SEL_t en_fChannel,INT32U u32_fNumber)
{
	INT8U u8_lReminder = 0;
	
	INT8U u8_lTempBuff[12];
	
	INT8U u8_lIndex = 0;

	if(u32_fNumber != 0)
	{
		while(u32_fNumber > 0)
		{
			u8_lReminder = u32_fNumber % 10;
			
			u8_lTempBuff[u8_lIndex++] = (u8_lReminder + 0x30);
			
			u32_fNumber = u32_fNumber/10;
		}
		while(u8_lIndex)
		{
			UART_TransmitChar(en_fChannel,u8_lTempBuff[--u8_lIndex]);
		}
	}
	else
	{
		UART_TransmitChar(en_fChannel, '0');
	}
}
/**************************************************************************************************/
/* Function Name   : void UART_Enable(EN_SERCOM_CH_SEL_t en_fChannel)                             */
/*                                                                                                */
/* Description     : This function is used to Enable the UART                                     */
/*                                                                                                */
/* In Params       : en_fChannel                                                                  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void UART_Enable(EN_SERCOM_CH_SEL_t en_fChannel)
{
	/* Enable USART */
	p_stgUSART_BASE_REGS[en_fChannel]->CTRLA |= SERCOM_USART_CTRLA_ENABLE;
	
	/* Waiting for ENABLE SYNC */
	while(p_stgUSART_BASE_REGS[en_fChannel]->SYNCBUSY & 0x02);
}

/**************************************************************************************************/
/* Function Name   : void UART_Disable(EN_SERCOM_CH_SEL_t en_fChannel)                            */
/*                                                                                                */
/* Description     : This function is used to Disable the UART                                    */
/*                                                                                                */
/* In Params       : en_fChannel                                                                  */
/*                                                                                                */
/* Out Params      : None                                                                         */
/*                                                                                                */
/* Return Value    : void                                                                         */
/**************************************************************************************************/

void UART_Disable(EN_SERCOM_CH_SEL_t en_fChannel)
{
	/* Disable USART */
	p_stgUSART_BASE_REGS[en_fChannel]->CTRLA &= ~(SERCOM_USART_CTRLA_ENABLE);
     
     /* Waite for Sync Busy */
     while(p_stgUSART_BASE_REGS[en_fChannel]->SYNCBUSY & 0x2);
}

/**************************************************************************************************/
/* End of UART.c                                                                                  */
/**************************************************************************************************/
