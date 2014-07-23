/*******************************************************************************
* File Name: .h
* Version 2.40
*
* Description:
*  This private header file contains internal definitions for the SPIM
*  component. Do not use these definitions directly in your application.
*
* Note:
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_PVT_master_H)
#define CY_SPIM_PVT_master_H

#include "master.h"


/**********************************
*   Functions with external linkage
**********************************/


/**********************************
*   Variables with external linkage
**********************************/

extern volatile uint8 master_swStatusTx;
extern volatile uint8 master_swStatusRx;

#if(master_TX_SOFTWARE_BUF_ENABLED)
    extern volatile uint16 master_txBuffer[master_TX_BUFFER_SIZE];
    extern volatile uint8 master_txBufferRead;
    extern volatile uint8 master_txBufferWrite;
    extern volatile uint8 master_txBufferFull;
#endif /* (master_TX_SOFTWARE_BUF_ENABLED) */

#if(master_RX_SOFTWARE_BUF_ENABLED)
    extern volatile uint16 master_rxBuffer[master_RX_BUFFER_SIZE];
    extern volatile uint8 master_rxBufferRead;
    extern volatile uint8 master_rxBufferWrite;
    extern volatile uint8 master_rxBufferFull;
#endif /* (master_RX_SOFTWARE_BUF_ENABLED) */

#endif /* CY_SPIM_PVT_master_H */


/* [] END OF FILE */
