/*******************************************************************************
* File Name: UART_Wind_PM.c
* Version 2.30
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_Wind.h"


/***************************************
* Local data allocation
***************************************/

static UART_Wind_BACKUP_STRUCT  UART_Wind_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: UART_Wind_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Wind_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Wind_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(UART_Wind_CONTROL_REG_REMOVED == 0u)
            UART_Wind_backup.cr = UART_Wind_CONTROL_REG;
        #endif /* End UART_Wind_CONTROL_REG_REMOVED */

        #if( (UART_Wind_RX_ENABLED) || (UART_Wind_HD_ENABLED) )
            UART_Wind_backup.rx_period = UART_Wind_RXBITCTR_PERIOD_REG;
            UART_Wind_backup.rx_mask = UART_Wind_RXSTATUS_MASK_REG;
            #if (UART_Wind_RXHW_ADDRESS_ENABLED)
                UART_Wind_backup.rx_addr1 = UART_Wind_RXADDRESS1_REG;
                UART_Wind_backup.rx_addr2 = UART_Wind_RXADDRESS2_REG;
            #endif /* End UART_Wind_RXHW_ADDRESS_ENABLED */
        #endif /* End UART_Wind_RX_ENABLED | UART_Wind_HD_ENABLED*/

        #if(UART_Wind_TX_ENABLED)
            #if(UART_Wind_TXCLKGEN_DP)
                UART_Wind_backup.tx_clk_ctr = UART_Wind_TXBITCLKGEN_CTR_REG;
                UART_Wind_backup.tx_clk_compl = UART_Wind_TXBITCLKTX_COMPLETE_REG;
            #else
                UART_Wind_backup.tx_period = UART_Wind_TXBITCTR_PERIOD_REG;
            #endif /*End UART_Wind_TXCLKGEN_DP */
            UART_Wind_backup.tx_mask = UART_Wind_TXSTATUS_MASK_REG;
        #endif /*End UART_Wind_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(UART_Wind_CONTROL_REG_REMOVED == 0u)
            UART_Wind_backup.cr = UART_Wind_CONTROL_REG;
        #endif /* End UART_Wind_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: UART_Wind_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Wind_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Wind_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(UART_Wind_CONTROL_REG_REMOVED == 0u)
            UART_Wind_CONTROL_REG = UART_Wind_backup.cr;
        #endif /* End UART_Wind_CONTROL_REG_REMOVED */

        #if( (UART_Wind_RX_ENABLED) || (UART_Wind_HD_ENABLED) )
            UART_Wind_RXBITCTR_PERIOD_REG = UART_Wind_backup.rx_period;
            UART_Wind_RXSTATUS_MASK_REG = UART_Wind_backup.rx_mask;
            #if (UART_Wind_RXHW_ADDRESS_ENABLED)
                UART_Wind_RXADDRESS1_REG = UART_Wind_backup.rx_addr1;
                UART_Wind_RXADDRESS2_REG = UART_Wind_backup.rx_addr2;
            #endif /* End UART_Wind_RXHW_ADDRESS_ENABLED */
        #endif  /* End (UART_Wind_RX_ENABLED) || (UART_Wind_HD_ENABLED) */

        #if(UART_Wind_TX_ENABLED)
            #if(UART_Wind_TXCLKGEN_DP)
                UART_Wind_TXBITCLKGEN_CTR_REG = UART_Wind_backup.tx_clk_ctr;
                UART_Wind_TXBITCLKTX_COMPLETE_REG = UART_Wind_backup.tx_clk_compl;
            #else
                UART_Wind_TXBITCTR_PERIOD_REG = UART_Wind_backup.tx_period;
            #endif /*End UART_Wind_TXCLKGEN_DP */
            UART_Wind_TXSTATUS_MASK_REG = UART_Wind_backup.tx_mask;
        #endif /*End UART_Wind_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(UART_Wind_CONTROL_REG_REMOVED == 0u)
            UART_Wind_CONTROL_REG = UART_Wind_backup.cr;
        #endif /* End UART_Wind_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: UART_Wind_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration. Should be called
*  just prior to entering sleep.
*
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Wind_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Wind_Sleep(void)
{

    #if(UART_Wind_RX_ENABLED || UART_Wind_HD_ENABLED)
        if((UART_Wind_RXSTATUS_ACTL_REG  & UART_Wind_INT_ENABLE) != 0u)
        {
            UART_Wind_backup.enableState = 1u;
        }
        else
        {
            UART_Wind_backup.enableState = 0u;
        }
    #else
        if((UART_Wind_TXSTATUS_ACTL_REG  & UART_Wind_INT_ENABLE) !=0u)
        {
            UART_Wind_backup.enableState = 1u;
        }
        else
        {
            UART_Wind_backup.enableState = 0u;
        }
    #endif /* End UART_Wind_RX_ENABLED || UART_Wind_HD_ENABLED*/

    UART_Wind_Stop();
    UART_Wind_SaveConfig();
}


/*******************************************************************************
* Function Name: UART_Wind_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Wind_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Wind_Wakeup(void)
{
    UART_Wind_RestoreConfig();
    #if( (UART_Wind_RX_ENABLED) || (UART_Wind_HD_ENABLED) )
        UART_Wind_ClearRxBuffer();
    #endif /* End (UART_Wind_RX_ENABLED) || (UART_Wind_HD_ENABLED) */
    #if(UART_Wind_TX_ENABLED || UART_Wind_HD_ENABLED)
        UART_Wind_ClearTxBuffer();
    #endif /* End UART_Wind_TX_ENABLED || UART_Wind_HD_ENABLED */

    if(UART_Wind_backup.enableState != 0u)
    {
        UART_Wind_Enable();
    }
}


/* [] END OF FILE */
