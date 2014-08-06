/*******************************************************************************
* File Name: psoc_PM.c
* Version 3.30
*
* Description:
*  This file provides Low power mode APIs for I2C component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "psoc_PVT.h"

psoc_BACKUP_STRUCT psoc_backup =
{
    psoc_DISABLE, /* enableState */

    #if(psoc_FF_IMPLEMENTED)
        psoc_DEFAULT_XCFG,  /* xcfg */
        psoc_DEFAULT_CFG,   /* cfg  */

        #if(psoc_MODE_SLAVE_ENABLED)
            psoc_DEFAULT_ADDR, /* addr */
        #endif /* (psoc_MODE_SLAVE_ENABLED) */

        #if(CY_PSOC5A)
            LO8(psoc_DEFAULT_DIVIDE_FACTOR),  /* div */
        #else
            LO8(psoc_DEFAULT_DIVIDE_FACTOR), /* div1 */
            HI8(psoc_DEFAULT_DIVIDE_FACTOR), /* div2 */
        #endif /* (CY_PSOC5A) */

    #else  /* (psoc_UDB_IMPLEMENTED) */
        psoc_DEFAULT_CFG,    /* control */

        #if(CY_UDB_V0)
            psoc_INT_ENABLE_MASK, /* aux_ctl */

            #if(psoc_MODE_SLAVE_ENABLED)
                psoc_DEFAULT_ADDR, /* addr_d0 */
            #endif /* (psoc_MODE_SLAVE_ENABLED) */
        #endif /* (CY_UDB_V0) */
    #endif /* (psoc_FF_IMPLEMENTED) */

    #if(psoc_TIMEOUT_ENABLED)
        psoc_DEFAULT_TMOUT_PERIOD,
        psoc_DEFAULT_TMOUT_INTR_MASK,

        #if(psoc_TIMEOUT_PRESCALER_ENABLED && CY_UDB_V0)
            psoc_DEFAULT_TMOUT_PRESCALER_PRD,
        #endif /* (psoc_TIMEOUT_PRESCALER_ENABLED) */

    #endif /* (psoc_TIMEOUT_ENABLED) */
};

#if((psoc_FF_IMPLEMENTED) && (psoc_WAKEUP_ENABLED))
    volatile uint8 psoc_wakeupSource;
#endif /* ((psoc_FF_IMPLEMENTED) && (psoc_WAKEUP_ENABLED)) */


/*******************************************************************************
* Function Name: psoc_SaveConfig
********************************************************************************
*
* Summary:
*  Wakeup on address match enabled: disables I2C Master(if was enabled before go
*  to sleep), enables I2C backup regulator. Waits while on-going transaction be
*  will completed and I2C will be ready go to sleep. All incoming transaction
*  will be NACKed till power down will be asserted. The address match event
*  wakes up the chip.
*  Wakeup on address match disabled: saves I2C configuration and non-retention
*  register values.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  psoc_backup - used to save component configuration and
*       none-retention registers before enter sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void psoc_SaveConfig(void) 
{
    #if(psoc_FF_IMPLEMENTED)
        #if(psoc_WAKEUP_ENABLED)
            uint8 enableInterrupts;
        #endif /* (psoc_WAKEUP_ENABLED) */

        /* Store regiters in either Sleep mode */
        psoc_backup.cfg  = psoc_CFG_REG;
        psoc_backup.xcfg = psoc_XCFG_REG;

        #if(psoc_MODE_SLAVE_ENABLED)
            psoc_backup.addr = psoc_ADDR_REG;
        #endif /* (psoc_MODE_SLAVE_ENABLED) */

        #if(CY_PSOC5A)
            psoc_backup.clkDiv   = psoc_CLKDIV_REG;
        #else
            psoc_backup.clkDiv1  = psoc_CLKDIV1_REG;
            psoc_backup.clkDiv2  = psoc_CLKDIV2_REG;
        #endif /* (CY_PSOC5A) */

        #if(psoc_WAKEUP_ENABLED)
            /* Need to disable Master */
            psoc_CFG_REG &= ((uint8) ~psoc_ENABLE_MASTER);

            /* Enable the I2C regulator backup */
            enableInterrupts = CyEnterCriticalSection();
            psoc_PWRSYS_CR1_REG |= psoc_PWRSYS_CR1_I2C_REG_BACKUP;
            CyExitCriticalSection(enableInterrupts);

            /* 1) Set force NACK to ignore I2C transactions
               2) Wait while I2C will be ready go to Sleep
               3) These bits are cleared on wake up */
            psoc_XCFG_REG |= psoc_XCFG_FORCE_NACK;
            while(0u == (psoc_XCFG_REG & psoc_XCFG_RDY_TO_SLEEP))
            {
                ; /* Wait when block is ready to Sleep */
            }

            /* Setup wakeup interrupt */
            psoc_DisableInt();
            (void) CyIntSetVector(psoc_ISR_NUMBER, &psoc_WAKEUP_ISR);
            psoc_wakeupSource = 0u;
            psoc_EnableInt();

        #endif /* (psoc_WAKEUP_ENABLED) */

    #else
        /* Store only address match bit */
        psoc_backup.control = (psoc_CFG_REG & psoc_CTRL_ANY_ADDRESS_MASK);

        #if(CY_UDB_V0)
            /* Store interrupt mask bits */
            psoc_backup.intMask = psoc_INT_MASK_REG;

            #if(psoc_MODE & psoc_MODE_SLAVE)
                psoc_backup.addr = psoc_ADDR_REG;
            #endif /* (psoc_MODE & psoc_MODE_SLAVE) */

        #endif /* (CY_UDB_V0) */

    #endif /* (psoc_FF_IMPLEMENTED) */

    #if(psoc_TIMEOUT_ENABLED)
        psoc_TimeoutSaveConfig();   /* Save Timeout config */
    #endif /* (psoc_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: psoc_Sleep
********************************************************************************
*
* Summary:
*  Wakeup on address match enabled: All incoming transaction will be NACKed till
*  power down will be asserted. The address match event wakes up the chip.
*  Wakeup on address match disabled: Disables active mode power template bits or
*  clock gating as appropriate. Saves I2C configuration and non-retention
*  register values.
*  Disables I2C interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void psoc_Sleep(void) 
{
    #if(psoc_WAKEUP_ENABLED)
        /* The I2C block should be always enabled if used as wakeup source */
        psoc_backup.enableState = psoc_DISABLE;

        #if(psoc_TIMEOUT_ENABLED)
            psoc_TimeoutStop();
        #endif /* (psoc_TIMEOUT_ENABLED) */

    #else

        psoc_backup.enableState = ((uint8) psoc_IS_ENABLED);

        if(psoc_IS_ENABLED)
        {
            psoc_Stop();
        }
    #endif /* (psoc_WAKEUP_ENABLED) */

    psoc_SaveConfig();
}


/*******************************************************************************
* Function Name: psoc_RestoreConfig
********************************************************************************
*
* Summary:
*  Wakeup on address match enabled: enables I2C Master (if was enabled before go
*  to sleep), disables I2C backup regulator.
*  Wakeup on address match disabled: Restores I2C configuration and
*  non-retention register values.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  psoc_backup - used to save component configuration and
*  none-retention registers before exit sleep mode.
*
*******************************************************************************/
void psoc_RestoreConfig(void) 
{
    #if(psoc_FF_IMPLEMENTED)
        uint8 enableInterrupts;

        if(psoc_CHECK_PWRSYS_I2C_BACKUP)    /* Enabled if was in Sleep */
        {
            /* Disable back-up regulator */
            enableInterrupts = CyEnterCriticalSection();
            psoc_PWRSYS_CR1_REG &= ((uint8) ~psoc_PWRSYS_CR1_I2C_REG_BACKUP);
            CyExitCriticalSection(enableInterrupts);

            /* Re-enable Master */
            psoc_CFG_REG = psoc_backup.cfg;
        }
        else /* The I2C_REG_BACKUP was cleaned by PM API: it means Hibernate or wake-up not set */
        {
            #if(psoc_WAKEUP_ENABLED)
                /* Disable power to I2C block before register restore */
                enableInterrupts = CyEnterCriticalSection();
                psoc_ACT_PWRMGR_REG  &= ((uint8) ~psoc_ACT_PWR_EN);
                psoc_STBY_PWRMGR_REG &= ((uint8) ~psoc_STBY_PWR_EN);
                CyExitCriticalSection(enableInterrupts);

                /* Enable component after restore complete */
                psoc_backup.enableState = psoc_ENABLE;
            #endif /* (psoc_WAKEUP_ENABLED) */

            /* Restore component registers: Hibernate disable power */
            psoc_XCFG_REG = psoc_backup.xcfg;
            psoc_CFG_REG  = psoc_backup.cfg;

            #if(psoc_MODE_SLAVE_ENABLED)
                psoc_ADDR_REG = psoc_backup.addr;
            #endif /* (psoc_MODE_SLAVE_ENABLED) */

            #if(CY_PSOC5A)
                psoc_CLKDIV_REG  = psoc_backup.clkDiv;
            #else
                psoc_CLKDIV1_REG = psoc_backup.clkDiv1;
                psoc_CLKDIV2_REG = psoc_backup.clkDiv2;
            #endif /* (CY_PSOC5A) */
        }

        #if(psoc_WAKEUP_ENABLED)
            psoc_DisableInt();
            (void) CyIntSetVector(psoc_ISR_NUMBER, &psoc_ISR);
            if(0u != psoc_wakeupSource)
            {
                psoc_SetPendingInt();   /* Generate interrupt to process incomming transcation */
            }
            psoc_EnableInt();
        #endif /* (psoc_WAKEUP_ENABLED) */

    #else

        #if(CY_UDB_V0)
            uint8 enableInterrupts;

            psoc_INT_MASK_REG |= psoc_backup.intMask;

            enableInterrupts = CyEnterCriticalSection();
            psoc_INT_ENABLE_REG |= psoc_INT_ENABLE_MASK;
            CyExitCriticalSection(enableInterrupts);

            #if(psoc_MODE_MASTER_ENABLED)
                /* Restore Master Clock generator */
                psoc_MCLK_PRD_REG = psoc_DEFAULT_MCLK_PRD;
                psoc_MCLK_CMP_REG = psoc_DEFAULT_MCLK_CMP;
            #endif /* (psoc_MODE_MASTER_ENABLED) */

            #if(psoc_MODE_SLAVE_ENABLED)
                psoc_ADDR_REG = psoc_backup.addr;

                /* Restore slave bit counter period */
                psoc_PERIOD_REG = psoc_DEFAULT_PERIOD;
            #endif /* (psoc_MODE_SLAVE_ENABLED) */

        #endif /* (CY_UDB_V0) */

        psoc_CFG_REG = psoc_backup.control;

    #endif /* (psoc_FF_IMPLEMENTED) */

    #if(psoc_TIMEOUT_ENABLED)
        psoc_TimeoutRestoreConfig();
    #endif /* (psoc_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: psoc_Wakeup
********************************************************************************
*
* Summary:
*  Wakeup on address match enabled: enables I2C Master (if was enabled before go
*  to sleep) and disables I2C backup regulator.
*  Wakeup on address match disabled: Restores I2C configuration and
*  non-retention register values. Restores Active mode power template bits or
*  clock gating as appropriate.
*  The I2C interrupt remains disabled after function call.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void psoc_Wakeup(void) 
{
    psoc_RestoreConfig();   /* Restore I2C register settings */

    /* Restore component enable state */
    if(0u != psoc_backup.enableState)
    {
        psoc_Enable();
        psoc_EnableInt();
    }
    else
    {
        #if(psoc_TIMEOUT_ENABLED)
            psoc_TimeoutEnable();
        #endif /* (psoc_TIMEOUT_ENABLED) */
    }
}


/* [] END OF FILE */
