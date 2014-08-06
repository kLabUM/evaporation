/*******************************************************************************
* File Name: i2cmaster_PM.c
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

#include "i2cmaster_PVT.h"

i2cmaster_BACKUP_STRUCT i2cmaster_backup =
{
    i2cmaster_DISABLE, /* enableState */

    #if(i2cmaster_FF_IMPLEMENTED)
        i2cmaster_DEFAULT_XCFG,  /* xcfg */
        i2cmaster_DEFAULT_CFG,   /* cfg  */

        #if(i2cmaster_MODE_SLAVE_ENABLED)
            i2cmaster_DEFAULT_ADDR, /* addr */
        #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */

        #if(CY_PSOC5A)
            LO8(i2cmaster_DEFAULT_DIVIDE_FACTOR),  /* div */
        #else
            LO8(i2cmaster_DEFAULT_DIVIDE_FACTOR), /* div1 */
            HI8(i2cmaster_DEFAULT_DIVIDE_FACTOR), /* div2 */
        #endif /* (CY_PSOC5A) */

    #else  /* (i2cmaster_UDB_IMPLEMENTED) */
        i2cmaster_DEFAULT_CFG,    /* control */

        #if(CY_UDB_V0)
            i2cmaster_INT_ENABLE_MASK, /* aux_ctl */

            #if(i2cmaster_MODE_SLAVE_ENABLED)
                i2cmaster_DEFAULT_ADDR, /* addr_d0 */
            #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */
        #endif /* (CY_UDB_V0) */
    #endif /* (i2cmaster_FF_IMPLEMENTED) */

    #if(i2cmaster_TIMEOUT_ENABLED)
        i2cmaster_DEFAULT_TMOUT_PERIOD,
        i2cmaster_DEFAULT_TMOUT_INTR_MASK,

        #if(i2cmaster_TIMEOUT_PRESCALER_ENABLED && CY_UDB_V0)
            i2cmaster_DEFAULT_TMOUT_PRESCALER_PRD,
        #endif /* (i2cmaster_TIMEOUT_PRESCALER_ENABLED) */

    #endif /* (i2cmaster_TIMEOUT_ENABLED) */
};

#if((i2cmaster_FF_IMPLEMENTED) && (i2cmaster_WAKEUP_ENABLED))
    volatile uint8 i2cmaster_wakeupSource;
#endif /* ((i2cmaster_FF_IMPLEMENTED) && (i2cmaster_WAKEUP_ENABLED)) */


/*******************************************************************************
* Function Name: i2cmaster_SaveConfig
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
*  i2cmaster_backup - used to save component configuration and
*       none-retention registers before enter sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void i2cmaster_SaveConfig(void) 
{
    #if(i2cmaster_FF_IMPLEMENTED)
        #if(i2cmaster_WAKEUP_ENABLED)
            uint8 enableInterrupts;
        #endif /* (i2cmaster_WAKEUP_ENABLED) */

        /* Store regiters in either Sleep mode */
        i2cmaster_backup.cfg  = i2cmaster_CFG_REG;
        i2cmaster_backup.xcfg = i2cmaster_XCFG_REG;

        #if(i2cmaster_MODE_SLAVE_ENABLED)
            i2cmaster_backup.addr = i2cmaster_ADDR_REG;
        #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */

        #if(CY_PSOC5A)
            i2cmaster_backup.clkDiv   = i2cmaster_CLKDIV_REG;
        #else
            i2cmaster_backup.clkDiv1  = i2cmaster_CLKDIV1_REG;
            i2cmaster_backup.clkDiv2  = i2cmaster_CLKDIV2_REG;
        #endif /* (CY_PSOC5A) */

        #if(i2cmaster_WAKEUP_ENABLED)
            /* Need to disable Master */
            i2cmaster_CFG_REG &= ((uint8) ~i2cmaster_ENABLE_MASTER);

            /* Enable the I2C regulator backup */
            enableInterrupts = CyEnterCriticalSection();
            i2cmaster_PWRSYS_CR1_REG |= i2cmaster_PWRSYS_CR1_I2C_REG_BACKUP;
            CyExitCriticalSection(enableInterrupts);

            /* 1) Set force NACK to ignore I2C transactions
               2) Wait while I2C will be ready go to Sleep
               3) These bits are cleared on wake up */
            i2cmaster_XCFG_REG |= i2cmaster_XCFG_FORCE_NACK;
            while(0u == (i2cmaster_XCFG_REG & i2cmaster_XCFG_RDY_TO_SLEEP))
            {
                ; /* Wait when block is ready to Sleep */
            }

            /* Setup wakeup interrupt */
            i2cmaster_DisableInt();
            (void) CyIntSetVector(i2cmaster_ISR_NUMBER, &i2cmaster_WAKEUP_ISR);
            i2cmaster_wakeupSource = 0u;
            i2cmaster_EnableInt();

        #endif /* (i2cmaster_WAKEUP_ENABLED) */

    #else
        /* Store only address match bit */
        i2cmaster_backup.control = (i2cmaster_CFG_REG & i2cmaster_CTRL_ANY_ADDRESS_MASK);

        #if(CY_UDB_V0)
            /* Store interrupt mask bits */
            i2cmaster_backup.intMask = i2cmaster_INT_MASK_REG;

            #if(i2cmaster_MODE & i2cmaster_MODE_SLAVE)
                i2cmaster_backup.addr = i2cmaster_ADDR_REG;
            #endif /* (i2cmaster_MODE & i2cmaster_MODE_SLAVE) */

        #endif /* (CY_UDB_V0) */

    #endif /* (i2cmaster_FF_IMPLEMENTED) */

    #if(i2cmaster_TIMEOUT_ENABLED)
        i2cmaster_TimeoutSaveConfig();   /* Save Timeout config */
    #endif /* (i2cmaster_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: i2cmaster_Sleep
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
void i2cmaster_Sleep(void) 
{
    #if(i2cmaster_WAKEUP_ENABLED)
        /* The I2C block should be always enabled if used as wakeup source */
        i2cmaster_backup.enableState = i2cmaster_DISABLE;

        #if(i2cmaster_TIMEOUT_ENABLED)
            i2cmaster_TimeoutStop();
        #endif /* (i2cmaster_TIMEOUT_ENABLED) */

    #else

        i2cmaster_backup.enableState = ((uint8) i2cmaster_IS_ENABLED);

        if(i2cmaster_IS_ENABLED)
        {
            i2cmaster_Stop();
        }
    #endif /* (i2cmaster_WAKEUP_ENABLED) */

    i2cmaster_SaveConfig();
}


/*******************************************************************************
* Function Name: i2cmaster_RestoreConfig
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
*  i2cmaster_backup - used to save component configuration and
*  none-retention registers before exit sleep mode.
*
*******************************************************************************/
void i2cmaster_RestoreConfig(void) 
{
    #if(i2cmaster_FF_IMPLEMENTED)
        uint8 enableInterrupts;

        if(i2cmaster_CHECK_PWRSYS_I2C_BACKUP)    /* Enabled if was in Sleep */
        {
            /* Disable back-up regulator */
            enableInterrupts = CyEnterCriticalSection();
            i2cmaster_PWRSYS_CR1_REG &= ((uint8) ~i2cmaster_PWRSYS_CR1_I2C_REG_BACKUP);
            CyExitCriticalSection(enableInterrupts);

            /* Re-enable Master */
            i2cmaster_CFG_REG = i2cmaster_backup.cfg;
        }
        else /* The I2C_REG_BACKUP was cleaned by PM API: it means Hibernate or wake-up not set */
        {
            #if(i2cmaster_WAKEUP_ENABLED)
                /* Disable power to I2C block before register restore */
                enableInterrupts = CyEnterCriticalSection();
                i2cmaster_ACT_PWRMGR_REG  &= ((uint8) ~i2cmaster_ACT_PWR_EN);
                i2cmaster_STBY_PWRMGR_REG &= ((uint8) ~i2cmaster_STBY_PWR_EN);
                CyExitCriticalSection(enableInterrupts);

                /* Enable component after restore complete */
                i2cmaster_backup.enableState = i2cmaster_ENABLE;
            #endif /* (i2cmaster_WAKEUP_ENABLED) */

            /* Restore component registers: Hibernate disable power */
            i2cmaster_XCFG_REG = i2cmaster_backup.xcfg;
            i2cmaster_CFG_REG  = i2cmaster_backup.cfg;

            #if(i2cmaster_MODE_SLAVE_ENABLED)
                i2cmaster_ADDR_REG = i2cmaster_backup.addr;
            #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */

            #if(CY_PSOC5A)
                i2cmaster_CLKDIV_REG  = i2cmaster_backup.clkDiv;
            #else
                i2cmaster_CLKDIV1_REG = i2cmaster_backup.clkDiv1;
                i2cmaster_CLKDIV2_REG = i2cmaster_backup.clkDiv2;
            #endif /* (CY_PSOC5A) */
        }

        #if(i2cmaster_WAKEUP_ENABLED)
            i2cmaster_DisableInt();
            (void) CyIntSetVector(i2cmaster_ISR_NUMBER, &i2cmaster_ISR);
            if(0u != i2cmaster_wakeupSource)
            {
                i2cmaster_SetPendingInt();   /* Generate interrupt to process incomming transcation */
            }
            i2cmaster_EnableInt();
        #endif /* (i2cmaster_WAKEUP_ENABLED) */

    #else

        #if(CY_UDB_V0)
            uint8 enableInterrupts;

            i2cmaster_INT_MASK_REG |= i2cmaster_backup.intMask;

            enableInterrupts = CyEnterCriticalSection();
            i2cmaster_INT_ENABLE_REG |= i2cmaster_INT_ENABLE_MASK;
            CyExitCriticalSection(enableInterrupts);

            #if(i2cmaster_MODE_MASTER_ENABLED)
                /* Restore Master Clock generator */
                i2cmaster_MCLK_PRD_REG = i2cmaster_DEFAULT_MCLK_PRD;
                i2cmaster_MCLK_CMP_REG = i2cmaster_DEFAULT_MCLK_CMP;
            #endif /* (i2cmaster_MODE_MASTER_ENABLED) */

            #if(i2cmaster_MODE_SLAVE_ENABLED)
                i2cmaster_ADDR_REG = i2cmaster_backup.addr;

                /* Restore slave bit counter period */
                i2cmaster_PERIOD_REG = i2cmaster_DEFAULT_PERIOD;
            #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */

        #endif /* (CY_UDB_V0) */

        i2cmaster_CFG_REG = i2cmaster_backup.control;

    #endif /* (i2cmaster_FF_IMPLEMENTED) */

    #if(i2cmaster_TIMEOUT_ENABLED)
        i2cmaster_TimeoutRestoreConfig();
    #endif /* (i2cmaster_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: i2cmaster_Wakeup
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
void i2cmaster_Wakeup(void) 
{
    i2cmaster_RestoreConfig();   /* Restore I2C register settings */

    /* Restore component enable state */
    if(0u != i2cmaster_backup.enableState)
    {
        i2cmaster_Enable();
        i2cmaster_EnableInt();
    }
    else
    {
        #if(i2cmaster_TIMEOUT_ENABLED)
            i2cmaster_TimeoutEnable();
        #endif /* (i2cmaster_TIMEOUT_ENABLED) */
    }
}


/* [] END OF FILE */
