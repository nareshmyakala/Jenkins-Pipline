/******************************************************************************/
/*                                                                            */
/*         Technical Innovations N Solution (TINS) Design Unit                */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* All Rights Reserved Copyright (C) 2010, Technical Innovations N Solutions. */
/*                                                                            */
/* Redistribution and use in source and binary forms, with or without         */
/* modification, are not permitted in any case                                */
/*                                                                            */
/* TINS's name may not be used to endorse or promote products derived from    */
/* this software without specific prior written permission.                   */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* All Rights Reserved Copyright (C) 2008, Technical Innovations N Solutions. */
/* 																			  */
/* \File Name	:	Includes.h  											  */
/* \Author		:	Srikanth Ala											  */
/* \Version 	:	SmartIT(R) 1.0										      */
/* \Date		:	24/03/2010												  */
/* 																			  */
/******************************************************************************/

#ifndef _INCLUDES_H_
#define _INCLUDES_H_

/******************************************************************************/
/* System Header Files									                      */
/******************************************************************************/

/******************************************************************************/
/* User defined Header Files												  */
/******************************************************************************/

/******************************************************************************/
/* Global Definitions														  */
/******************************************************************************/

#define PNULL                (void *)0x00
 
typedef unsigned char       UINT8;
typedef char                INT8;
typedef unsigned short int  UINT16;
typedef short int           INT16;
typedef unsigned int        UINT32;
typedef int                 INT32;

typedef unsigned char       BYTE;
typedef unsigned short int  WORD;
typedef unsigned int        DWORD;
typedef unsigned int        SYS_REG;

typedef char                INT8S;
typedef unsigned char       INT8U;
typedef const char          INT8C;
typedef short int           INT16S;
typedef unsigned short int  INT16U;
typedef int                 INT32S;
typedef unsigned long int   INT32U;
typedef unsigned long long int INT64U;
typedef float					INT32F;

typedef volatile unsigned int * POINTER;
typedef volatile unsigned long int * LPOINTER;
typedef volatile void * VPOINTER;

typedef volatile unsigned char SYS_REG_BYTE;
typedef volatile unsigned short int SYS_REG_HWORD;

typedef unsigned long int 	   SIZE_t;

typedef INT32U MEM_PTR_t;

#endif

/******************************************************************************/
/* End of Includes.h                                                          */
/******************************************************************************/

