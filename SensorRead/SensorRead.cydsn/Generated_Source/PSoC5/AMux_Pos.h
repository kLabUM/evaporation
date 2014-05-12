/*******************************************************************************
* File Name: AMux_Pos.h
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

#if !defined(CY_AMUX_AMux_Pos_H)
#define CY_AMUX_AMux_Pos_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void AMux_Pos_Start(void) ;
#define AMux_Pos_Init() AMux_Pos_Start()
void AMux_Pos_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void AMux_Pos_Stop(void); */
/* void AMux_Pos_Select(uint8 channel); */
/* void AMux_Pos_Connect(uint8 channel); */
/* void AMux_Pos_Disconnect(uint8 channel); */
/* void AMux_Pos_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define AMux_Pos_CHANNELS  6u
#define AMux_Pos_MUXTYPE   1
#define AMux_Pos_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define AMux_Pos_NULL_CHANNEL 0xFFu
#define AMux_Pos_MUX_SINGLE   1
#define AMux_Pos_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if AMux_Pos_MUXTYPE == AMux_Pos_MUX_SINGLE
# if !AMux_Pos_ATMOSTONE
#  define AMux_Pos_Connect(channel) AMux_Pos_Set(channel)
# endif
# define AMux_Pos_Disconnect(channel) AMux_Pos_Unset(channel)
#else
# if !AMux_Pos_ATMOSTONE
void AMux_Pos_Connect(uint8 channel) ;
# endif
void AMux_Pos_Disconnect(uint8 channel) ;
#endif

#if AMux_Pos_ATMOSTONE
# define AMux_Pos_Stop() AMux_Pos_DisconnectAll()
# define AMux_Pos_Select(channel) AMux_Pos_FastSelect(channel)
void AMux_Pos_DisconnectAll(void) ;
#else
# define AMux_Pos_Stop() AMux_Pos_Start()
void AMux_Pos_Select(uint8 channel) ;
# define AMux_Pos_DisconnectAll() AMux_Pos_Start()
#endif

#endif /* CY_AMUX_AMux_Pos_H */


/* [] END OF FILE */
