/*******************************************************************************
* File Name: .h
* Version 3.30
*
* Description:
*  This file provides private constants and parameter values for the I2C
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_I2C_PVT_psoc_H)
#define CY_I2C_PVT_psoc_H

#include "psoc.h"

#define psoc_TIMEOUT_ENABLED_INC    (0u)
#if(0u != psoc_TIMEOUT_ENABLED_INC)
    #include "psoc_TMOUT.h"
#endif /* (0u != psoc_TIMEOUT_ENABLED_INC) */


/**********************************
*   Variables with external linkage
**********************************/

extern psoc_BACKUP_STRUCT psoc_backup;

extern volatile uint8 psoc_state;   /* Current state of I2C FSM */

/* Master variables */
#if(psoc_MODE_MASTER_ENABLED)
    extern volatile uint8 psoc_mstrStatus;   /* Master Status byte  */
    extern volatile uint8 psoc_mstrControl;  /* Master Control byte */

    /* Transmit buffer variables */
    extern volatile uint8 * psoc_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint8   psoc_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint8   psoc_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Receive buffer variables */
    extern volatile uint8 * psoc_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint8   psoc_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint8   psoc_mstrWrBufIndex; /* Master Write buffer Index      */

#endif /* (psoc_MODE_MASTER_ENABLED) */

/* Slave variables */
#if(psoc_MODE_SLAVE_ENABLED)
    extern volatile uint8 psoc_slStatus;         /* Slave Status  */

    /* Transmit buffer variables */
    extern volatile uint8 * psoc_slRdBufPtr;     /* Pointer to Transmit buffer  */
    extern volatile uint8   psoc_slRdBufSize;    /* Slave Transmit buffer size  */
    extern volatile uint8   psoc_slRdBufIndex;   /* Slave Transmit buffer Index */

    /* Receive buffer variables */
    extern volatile uint8 * psoc_slWrBufPtr;     /* Pointer to Receive buffer  */
    extern volatile uint8   psoc_slWrBufSize;    /* Slave Receive buffer size  */
    extern volatile uint8   psoc_slWrBufIndex;   /* Slave Receive buffer Index */

    #if(psoc_SW_ADRR_DECODE)
        extern volatile uint8 psoc_slAddress;     /* Software address variable */
    #endif   /* (psoc_SW_ADRR_DECODE) */

#endif /* (psoc_MODE_SLAVE_ENABLED) */

#if((psoc_FF_IMPLEMENTED) && (psoc_WAKEUP_ENABLED))
    extern volatile uint8 psoc_wakeupSource;
#endif /* ((psoc_FF_IMPLEMENTED) && (psoc_WAKEUP_ENABLED)) */


#endif /* CY_I2C_PVT_psoc_H */


/* [] END OF FILE */
