/*******************************************************************************
* File Name: AMux_Neg.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_AMux_Neg_H)
#define CY_AMUX_AMux_Neg_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void AMux_Neg_Start(void) ;
#define AMux_Neg_Init() AMux_Neg_Start()
void AMux_Neg_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void AMux_Neg_Stop(void); */
/* void AMux_Neg_Select(uint8 channel); */
/* void AMux_Neg_Connect(uint8 channel); */
/* void AMux_Neg_Disconnect(uint8 channel); */
/* void AMux_Neg_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define AMux_Neg_CHANNELS  6u
#define AMux_Neg_MUXTYPE   1
#define AMux_Neg_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define AMux_Neg_NULL_CHANNEL 0xFFu
#define AMux_Neg_MUX_SINGLE   1
#define AMux_Neg_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if AMux_Neg_MUXTYPE == AMux_Neg_MUX_SINGLE
# if !AMux_Neg_ATMOSTONE
#  define AMux_Neg_Connect(channel) AMux_Neg_Set(channel)
# endif
# define AMux_Neg_Disconnect(channel) AMux_Neg_Unset(channel)
#else
# if !AMux_Neg_ATMOSTONE
void AMux_Neg_Connect(uint8 channel) ;
# endif
void AMux_Neg_Disconnect(uint8 channel) ;
#endif

#if AMux_Neg_ATMOSTONE
# define AMux_Neg_Stop() AMux_Neg_DisconnectAll()
# define AMux_Neg_Select(channel) AMux_Neg_FastSelect(channel)
void AMux_Neg_DisconnectAll(void) ;
#else
# define AMux_Neg_Stop() AMux_Neg_Start()
void AMux_Neg_Select(uint8 channel) ;
# define AMux_Neg_DisconnectAll() AMux_Neg_Start()
#endif

#endif /* CY_AMUX_AMux_Neg_H */


/* [] END OF FILE */
