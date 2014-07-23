/*******************************************************************************
* File Name: Airmar_PM.c
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

#include "Airmar.h"


/***************************************
* Local data allocation
***************************************/

static Airmar_BACKUP_STRUCT  Airmar_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: Airmar_SaveConfig
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
*  Airmar_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Airmar_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(Airmar_CONTROL_REG_REMOVED == 0u)
            Airmar_backup.cr = Airmar_CONTROL_REG;
        #endif /* End Airmar_CONTROL_REG_REMOVED */

        #if( (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) )
            Airmar_backup.rx_period = Airmar_RXBITCTR_PERIOD_REG;
            Airmar_backup.rx_mask = Airmar_RXSTATUS_MASK_REG;
            #if (Airmar_RXHW_ADDRESS_ENABLED)
                Airmar_backup.rx_addr1 = Airmar_RXADDRESS1_REG;
                Airmar_backup.rx_addr2 = Airmar_RXADDRESS2_REG;
            #endif /* End Airmar_RXHW_ADDRESS_ENABLED */
        #endif /* End Airmar_RX_ENABLED | Airmar_HD_ENABLED*/

        #if(Airmar_TX_ENABLED)
            #if(Airmar_TXCLKGEN_DP)
                Airmar_backup.tx_clk_ctr = Airmar_TXBITCLKGEN_CTR_REG;
                Airmar_backup.tx_clk_compl = Airmar_TXBITCLKTX_COMPLETE_REG;
            #else
                Airmar_backup.tx_period = Airmar_TXBITCTR_PERIOD_REG;
            #endif /*End Airmar_TXCLKGEN_DP */
            Airmar_backup.tx_mask = Airmar_TXSTATUS_MASK_REG;
        #endif /*End Airmar_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(Airmar_CONTROL_REG_REMOVED == 0u)
            Airmar_backup.cr = Airmar_CONTROL_REG;
        #endif /* End Airmar_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: Airmar_RestoreConfig
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
*  Airmar_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Airmar_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(Airmar_CONTROL_REG_REMOVED == 0u)
            Airmar_CONTROL_REG = Airmar_backup.cr;
        #endif /* End Airmar_CONTROL_REG_REMOVED */

        #if( (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) )
            Airmar_RXBITCTR_PERIOD_REG = Airmar_backup.rx_period;
            Airmar_RXSTATUS_MASK_REG = Airmar_backup.rx_mask;
            #if (Airmar_RXHW_ADDRESS_ENABLED)
                Airmar_RXADDRESS1_REG = Airmar_backup.rx_addr1;
                Airmar_RXADDRESS2_REG = Airmar_backup.rx_addr2;
            #endif /* End Airmar_RXHW_ADDRESS_ENABLED */
        #endif  /* End (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) */

        #if(Airmar_TX_ENABLED)
            #if(Airmar_TXCLKGEN_DP)
                Airmar_TXBITCLKGEN_CTR_REG = Airmar_backup.tx_clk_ctr;
                Airmar_TXBITCLKTX_COMPLETE_REG = Airmar_backup.tx_clk_compl;
            #else
                Airmar_TXBITCTR_PERIOD_REG = Airmar_backup.tx_period;
            #endif /*End Airmar_TXCLKGEN_DP */
            Airmar_TXSTATUS_MASK_REG = Airmar_backup.tx_mask;
        #endif /*End Airmar_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(Airmar_CONTROL_REG_REMOVED == 0u)
            Airmar_CONTROL_REG = Airmar_backup.cr;
        #endif /* End Airmar_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: Airmar_Sleep
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
*  Airmar_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Airmar_Sleep(void)
{

    #if(Airmar_RX_ENABLED || Airmar_HD_ENABLED)
        if((Airmar_RXSTATUS_ACTL_REG  & Airmar_INT_ENABLE) != 0u)
        {
            Airmar_backup.enableState = 1u;
        }
        else
        {
            Airmar_backup.enableState = 0u;
        }
    #else
        if((Airmar_TXSTATUS_ACTL_REG  & Airmar_INT_ENABLE) !=0u)
        {
            Airmar_backup.enableState = 1u;
        }
        else
        {
            Airmar_backup.enableState = 0u;
        }
    #endif /* End Airmar_RX_ENABLED || Airmar_HD_ENABLED*/

    Airmar_Stop();
    Airmar_SaveConfig();
}


/*******************************************************************************
* Function Name: Airmar_Wakeup
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
*  Airmar_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Airmar_Wakeup(void)
{
    Airmar_RestoreConfig();
    #if( (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) )
        Airmar_ClearRxBuffer();
    #endif /* End (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) */
    #if(Airmar_TX_ENABLED || Airmar_HD_ENABLED)
        Airmar_ClearTxBuffer();
    #endif /* End Airmar_TX_ENABLED || Airmar_HD_ENABLED */

    if(Airmar_backup.enableState != 0u)
    {
        Airmar_Enable();
    }
}


/* [] END OF FILE */
