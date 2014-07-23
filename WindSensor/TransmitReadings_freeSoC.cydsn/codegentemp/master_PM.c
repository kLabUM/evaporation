/*******************************************************************************
* File Name: master_PM.c
* Version 2.40
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "master_PVT.h"

static master_BACKUP_STRUCT master_backup =
{
    master_DISABLED,
    master_BITCTR_INIT,
    #if(CY_UDB_V0)
        master_TX_INIT_INTERRUPTS_MASK,
        master_RX_INIT_INTERRUPTS_MASK
    #endif /* CY_UDB_V0 */
};


/*******************************************************************************
* Function Name: master_SaveConfig
********************************************************************************
*
* Summary:
*  Saves SPIM configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  master_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void master_SaveConfig(void) 
{
    /* Store Status Mask registers */
    #if(CY_UDB_V0)
       master_backup.cntrPeriod      = master_COUNTER_PERIOD_REG;
       master_backup.saveSrTxIntMask = master_TX_STATUS_MASK_REG;
       master_backup.saveSrRxIntMask = master_RX_STATUS_MASK_REG;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: master_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores SPIM configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  master_backup - used when non-retention registers are restored.
*
* Side Effects:
*  If this API is called without first calling SaveConfig then in the following
*  registers will be default values from Customizer:
*  master_STATUS_MASK_REG and master_COUNTER_PERIOD_REG.
*
*******************************************************************************/
void master_RestoreConfig(void) 
{
    /* Restore the data, saved by SaveConfig() function */
    #if(CY_UDB_V0)
        master_COUNTER_PERIOD_REG = master_backup.cntrPeriod;
        master_TX_STATUS_MASK_REG = ((uint8) master_backup.saveSrTxIntMask);
        master_RX_STATUS_MASK_REG = ((uint8) master_backup.saveSrRxIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: master_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPIM Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  master_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void master_Sleep(void) 
{
    /* Save components enable state */
    master_backup.enableState = ((uint8) master_IS_ENABLED);

    master_Stop();
    master_SaveConfig();
}


/*******************************************************************************
* Function Name: master_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  master_backup - used when non-retention registers are restored.
*  master_txBufferWrite - modified every function call - resets to
*  zero.
*  master_txBufferRead - modified every function call - resets to
*  zero.
*  master_rxBufferWrite - modified every function call - resets to
*  zero.
*  master_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void master_Wakeup(void) 
{
    master_RestoreConfig();

    #if(master_RX_SOFTWARE_BUF_ENABLED)
        master_rxBufferFull  = 0u;
        master_rxBufferRead  = 0u;
        master_rxBufferWrite = 0u;
    #endif /* (master_RX_SOFTWARE_BUF_ENABLED) */

    #if(master_TX_SOFTWARE_BUF_ENABLED)
        master_txBufferFull  = 0u;
        master_txBufferRead  = 0u;
        master_txBufferWrite = 0u;
    #endif /* (master_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    master_ClearFIFO();

    /* Restore components block enable state */
    if(0u != master_backup.enableState)
    {
        master_Enable();
    }
}


/* [] END OF FILE */
