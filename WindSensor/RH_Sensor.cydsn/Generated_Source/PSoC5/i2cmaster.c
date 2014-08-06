/*******************************************************************************
* File Name: i2cmaster.c
* Version 3.30
*
* Description:
*  This file provides the source code of APIs for the I2C component.
*  Actual protocol and operation code resides in the interrupt service routine
*  file.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "i2cmaster_PVT.h"


/**********************************
*      System variables
**********************************/

uint8 i2cmaster_initVar = 0u;    /* Defines if component was initialized */

volatile uint8 i2cmaster_state;  /* Current state of I2C FSM */


/*******************************************************************************
* Function Name: i2cmaster_Init
********************************************************************************
*
* Summary:
*  Initializes I2C registers with initial values provided from customizer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void i2cmaster_Init(void) 
{
    #if(i2cmaster_FF_IMPLEMENTED)
        i2cmaster_CFG_REG  = i2cmaster_DEFAULT_CFG;
        i2cmaster_XCFG_REG = i2cmaster_DEFAULT_XCFG;

        #if(CY_PSOC5A)
            i2cmaster_CLKDIV_REG  = LO8(i2cmaster_DEFAULT_DIVIDE_FACTOR);
        #else
            i2cmaster_CLKDIV1_REG = LO8(i2cmaster_DEFAULT_DIVIDE_FACTOR);
            i2cmaster_CLKDIV2_REG = HI8(i2cmaster_DEFAULT_DIVIDE_FACTOR);
        #endif /* (CY_PSOC5A) */

    #else
        uint8 enableInterrupts;

        i2cmaster_CFG_REG      = i2cmaster_DEFAULT_CFG;      /* control  */
        i2cmaster_INT_MASK_REG = i2cmaster_DEFAULT_INT_MASK; /* int_mask */

        /* Enable interrupts from block */
        enableInterrupts = CyEnterCriticalSection();
        i2cmaster_INT_ENABLE_REG |= i2cmaster_INTR_ENABLE; /* aux_ctl */
        CyExitCriticalSection(enableInterrupts);

        #if(i2cmaster_MODE_MASTER_ENABLED)
            i2cmaster_MCLK_PRD_REG = i2cmaster_DEFAULT_MCLK_PRD;
            i2cmaster_MCLK_CMP_REG = i2cmaster_DEFAULT_MCLK_CMP;
         #endif /* (i2cmaster_MODE_MASTER_ENABLED) */

        #if(i2cmaster_MODE_SLAVE_ENABLED)
            i2cmaster_PERIOD_REG = i2cmaster_DEFAULT_PERIOD;
        #endif  /* (i2cmaster_MODE_SLAVE_ENABLED) */

    #endif /* (i2cmaster_FF_IMPLEMENTED) */

    #if(i2cmaster_TIMEOUT_ENABLED)
        i2cmaster_TimeoutInit();
    #endif /* (i2cmaster_TIMEOUT_ENABLED) */

    /* Disable Interrupt and set vector and priority */
    CyIntDisable    (i2cmaster_ISR_NUMBER);
    CyIntSetPriority(i2cmaster_ISR_NUMBER, i2cmaster_ISR_PRIORITY);
    #if(i2cmaster_INTERN_I2C_INTR_HANDLER)
        (void) CyIntSetVector(i2cmaster_ISR_NUMBER, &i2cmaster_ISR);
    #endif /* (i2cmaster_INTERN_I2C_INTR_HANDLER) */


    /* Put state machine in idle state */
    i2cmaster_state = i2cmaster_SM_IDLE;

    #if(i2cmaster_MODE_SLAVE_ENABLED)
        /* Reset status and buffers index */
        i2cmaster_SlaveClearReadBuf();
        i2cmaster_SlaveClearWriteBuf();
        i2cmaster_slStatus = 0u; /* Reset slave status */

        /* Set default address */
        i2cmaster_SlaveSetAddress(i2cmaster_DEFAULT_ADDR);
    #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */

    #if(i2cmaster_MODE_MASTER_ENABLED)
        /* Reset status and buffers index */
        i2cmaster_MasterClearReadBuf();
        i2cmaster_MasterClearWriteBuf();
        (void) i2cmaster_MasterClearStatus();
    #endif /* (i2cmaster_MODE_MASTER_ENABLED) */
}


/*******************************************************************************
* Function Name: i2cmaster_Enable
********************************************************************************
*
* Summary:
*  Enables I2C operations.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void i2cmaster_Enable(void) 
{
    #if(i2cmaster_FF_IMPLEMENTED)
        uint8 enableInterrupts;

        /* Enable power to I2C FF block */
        enableInterrupts = CyEnterCriticalSection();
        i2cmaster_ACT_PWRMGR_REG  |= i2cmaster_ACT_PWR_EN;
        i2cmaster_STBY_PWRMGR_REG |= i2cmaster_STBY_PWR_EN;
        CyExitCriticalSection(enableInterrupts);

    #else

        #if(i2cmaster_MODE_SLAVE_ENABLED)
            uint8 enableInterrupts;
        #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */

        #if(i2cmaster_MODE_SLAVE_ENABLED)
            /* Enable slave bit counter */
            enableInterrupts = CyEnterCriticalSection();
            i2cmaster_COUNTER_AUX_CTL_REG |= i2cmaster_CNT7_ENABLE;   /* aux_ctl */
            CyExitCriticalSection(enableInterrupts);
        #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */

        i2cmaster_CFG_REG |= i2cmaster_ENABLE_MS;

    #endif /* (i2cmaster_FF_IMPLEMENTED) */

    #if(i2cmaster_TIMEOUT_ENABLED)
        i2cmaster_TimeoutEnable();
    #endif /* (i2cmaster_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: i2cmaster_Start
********************************************************************************
*
* Summary:
*  Starts the I2C hardware. Enables Active mode power template bits or clock
*  gating as appropriate. It is required to be executed before I2C bus
*  operation.
*  The I2C interrupt remains disabled after this function call.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This component automatically enables it's interrupt.  If I2C is enabled
*  without the interrupt enabled, it could lock up the I2C bus.
*
* Global variables:
*  i2cmaster_initVar - used to check initial configuration, modified
*  on first function call.
*
* Reentrant:
*  No
*
*******************************************************************************/
void i2cmaster_Start(void) 
{
    /* Initialize I2C registers, reset I2C buffer index and clears status */
    if(0u == i2cmaster_initVar)
    {
        i2cmaster_Init();
        i2cmaster_initVar = 1u; /* Component initialized */
    }

    i2cmaster_Enable();
    i2cmaster_EnableInt();
}


/*******************************************************************************
* Function Name: i2cmaster_Stop
********************************************************************************
*
* Summary:
*  Disables I2C hardware and disables I2C interrupt. Disables Active mode power
*  template bits or clock gating as appropriate.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void i2cmaster_Stop(void) 
{
    #if((i2cmaster_FF_IMPLEMENTED)  || \
        (i2cmaster_UDB_IMPLEMENTED && i2cmaster_MODE_SLAVE_ENABLED))
        uint8 enableInterrupts;
    #endif /* ((i2cmaster_FF_IMPLEMENTED)  || \
               (i2cmaster_UDB_IMPLEMENTED && i2cmaster_MODE_SLAVE_ENABLED)) */

    i2cmaster_DisableInt();

    i2cmaster_DISABLE_INT_ON_STOP;   /* Interrupt on Stop can be enabled by write */
    (void) i2cmaster_CSR_REG;        /* Clear CSR reg */
    
    #if(i2cmaster_TIMEOUT_ENABLED)
        i2cmaster_TimeoutStop();
    #endif  /* End (i2cmaster_TIMEOUT_ENABLED) */

    #if(i2cmaster_FF_IMPLEMENTED)
        #if(CY_PSOC3 || CY_PSOC5LP)
            /* Store registers which are held in reset when Master and Slave bits are cleared */
            #if(i2cmaster_MODE_SLAVE_ENABLED)
                i2cmaster_backup.addr = i2cmaster_ADDR_REG;
            #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */

            i2cmaster_backup.clkDiv1  = i2cmaster_CLKDIV1_REG;
            i2cmaster_backup.clkDiv2  = i2cmaster_CLKDIV2_REG;


            /* Reset FF block */
            i2cmaster_CFG_REG &= ((uint8) ~i2cmaster_ENABLE_MS);
            CyDelayUs(i2cmaster_FF_RESET_DELAY);
            i2cmaster_CFG_REG |= ((uint8)  i2cmaster_ENABLE_MS);


            /* Restore registers */
            #if(i2cmaster_MODE_SLAVE_ENABLED)
                i2cmaster_ADDR_REG = i2cmaster_backup.addr;
            #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */

            i2cmaster_CLKDIV1_REG = i2cmaster_backup.clkDiv1;
            i2cmaster_CLKDIV2_REG = i2cmaster_backup.clkDiv2;

        #endif /* (CY_PSOC3 || CY_PSOC5LP) */

        /* Disable power to I2C block */
        enableInterrupts = CyEnterCriticalSection();
        i2cmaster_ACT_PWRMGR_REG  &= ((uint8) ~i2cmaster_ACT_PWR_EN);
        i2cmaster_STBY_PWRMGR_REG &= ((uint8) ~i2cmaster_STBY_PWR_EN);
        CyExitCriticalSection(enableInterrupts);

    #else

        #if(i2cmaster_MODE_SLAVE_ENABLED)
            /* Disable slave bit counter */
            enableInterrupts = CyEnterCriticalSection();
            i2cmaster_COUNTER_AUX_CTL_REG &= ((uint8) ~i2cmaster_CNT7_ENABLE);
            CyExitCriticalSection(enableInterrupts);
        #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */

        i2cmaster_CFG_REG &= ((uint8) ~i2cmaster_ENABLE_MS);

    #endif /* (i2cmaster_FF_IMPLEMENTED) */

    i2cmaster_ClearPendingInt();  /* Clear interrupt triggers on reset */

    i2cmaster_state = i2cmaster_SM_IDLE;  /* Reset software FSM */
}


/* [] END OF FILE */
