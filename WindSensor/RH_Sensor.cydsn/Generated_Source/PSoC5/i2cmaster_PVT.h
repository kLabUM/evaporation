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

#if !defined(CY_I2C_PVT_i2cmaster_H)
#define CY_I2C_PVT_i2cmaster_H

#include "i2cmaster.h"

#define i2cmaster_TIMEOUT_ENABLED_INC    (0u)
#if(0u != i2cmaster_TIMEOUT_ENABLED_INC)
    #include "i2cmaster_TMOUT.h"
#endif /* (0u != i2cmaster_TIMEOUT_ENABLED_INC) */


/**********************************
*   Variables with external linkage
**********************************/

extern i2cmaster_BACKUP_STRUCT i2cmaster_backup;

extern volatile uint8 i2cmaster_state;   /* Current state of I2C FSM */

/* Master variables */
#if(i2cmaster_MODE_MASTER_ENABLED)
    extern volatile uint8 i2cmaster_mstrStatus;   /* Master Status byte  */
    extern volatile uint8 i2cmaster_mstrControl;  /* Master Control byte */

    /* Transmit buffer variables */
    extern volatile uint8 * i2cmaster_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint8   i2cmaster_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint8   i2cmaster_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Receive buffer variables */
    extern volatile uint8 * i2cmaster_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint8   i2cmaster_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint8   i2cmaster_mstrWrBufIndex; /* Master Write buffer Index      */

#endif /* (i2cmaster_MODE_MASTER_ENABLED) */

/* Slave variables */
#if(i2cmaster_MODE_SLAVE_ENABLED)
    extern volatile uint8 i2cmaster_slStatus;         /* Slave Status  */

    /* Transmit buffer variables */
    extern volatile uint8 * i2cmaster_slRdBufPtr;     /* Pointer to Transmit buffer  */
    extern volatile uint8   i2cmaster_slRdBufSize;    /* Slave Transmit buffer size  */
    extern volatile uint8   i2cmaster_slRdBufIndex;   /* Slave Transmit buffer Index */

    /* Receive buffer variables */
    extern volatile uint8 * i2cmaster_slWrBufPtr;     /* Pointer to Receive buffer  */
    extern volatile uint8   i2cmaster_slWrBufSize;    /* Slave Receive buffer size  */
    extern volatile uint8   i2cmaster_slWrBufIndex;   /* Slave Receive buffer Index */

    #if(i2cmaster_SW_ADRR_DECODE)
        extern volatile uint8 i2cmaster_slAddress;     /* Software address variable */
    #endif   /* (i2cmaster_SW_ADRR_DECODE) */

#endif /* (i2cmaster_MODE_SLAVE_ENABLED) */

#if((i2cmaster_FF_IMPLEMENTED) && (i2cmaster_WAKEUP_ENABLED))
    extern volatile uint8 i2cmaster_wakeupSource;
#endif /* ((i2cmaster_FF_IMPLEMENTED) && (i2cmaster_WAKEUP_ENABLED)) */


#endif /* CY_I2C_PVT_i2cmaster_H */


/* [] END OF FILE */
