/*******************************************************************************
* File Name: psoc.c
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

#include "psoc_PVT.h"


/**********************************
*      System variables
**********************************/

uint8 psoc_initVar = 0u;    /* Defines if component was initialized */

volatile uint8 psoc_state;  /* Current state of I2C FSM */


/*******************************************************************************
* Function Name: psoc_Init
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
void psoc_Init(void) 
{
    #if(psoc_FF_IMPLEMENTED)
        psoc_CFG_REG  = psoc_DEFAULT_CFG;
        psoc_XCFG_REG = psoc_DEFAULT_XCFG;

        #if(CY_PSOC5A)
            psoc_CLKDIV_REG  = LO8(psoc_DEFAULT_DIVIDE_FACTOR);
        #else
            psoc_CLKDIV1_REG = LO8(psoc_DEFAULT_DIVIDE_FACTOR);
            psoc_CLKDIV2_REG = HI8(psoc_DEFAULT_DIVIDE_FACTOR);
        #endif /* (CY_PSOC5A) */

    #else
        uint8 enableInterrupts;

        psoc_CFG_REG      = psoc_DEFAULT_CFG;      /* control  */
        psoc_INT_MASK_REG = psoc_DEFAULT_INT_MASK; /* int_mask */

        /* Enable interrupts from block */
        enableInterrupts = CyEnterCriticalSection();
        psoc_INT_ENABLE_REG |= psoc_INTR_ENABLE; /* aux_ctl */
        CyExitCriticalSection(enableInterrupts);

        #if(psoc_MODE_MASTER_ENABLED)
            psoc_MCLK_PRD_REG = psoc_DEFAULT_MCLK_PRD;
            psoc_MCLK_CMP_REG = psoc_DEFAULT_MCLK_CMP;
         #endif /* (psoc_MODE_MASTER_ENABLED) */

        #if(psoc_MODE_SLAVE_ENABLED)
            psoc_PERIOD_REG = psoc_DEFAULT_PERIOD;
        #endif  /* (psoc_MODE_SLAVE_ENABLED) */

    #endif /* (psoc_FF_IMPLEMENTED) */

    #if(psoc_TIMEOUT_ENABLED)
        psoc_TimeoutInit();
    #endif /* (psoc_TIMEOUT_ENABLED) */

    /* Disable Interrupt and set vector and priority */
    CyIntDisable    (psoc_ISR_NUMBER);
    CyIntSetPriority(psoc_ISR_NUMBER, psoc_ISR_PRIORITY);
    #if(psoc_INTERN_I2C_INTR_HANDLER)
        (void) CyIntSetVector(psoc_ISR_NUMBER, &psoc_ISR);
    #endif /* (psoc_INTERN_I2C_INTR_HANDLER) */


    /* Put state machine in idle state */
    psoc_state = psoc_SM_IDLE;

    #if(psoc_MODE_SLAVE_ENABLED)
        /* Reset status and buffers index */
        psoc_SlaveClearReadBuf();
        psoc_SlaveClearWriteBuf();
        psoc_slStatus = 0u; /* Reset slave status */

        /* Set default address */
        psoc_SlaveSetAddress(psoc_DEFAULT_ADDR);
    #endif /* (psoc_MODE_SLAVE_ENABLED) */

    #if(psoc_MODE_MASTER_ENABLED)
        /* Reset status and buffers index */
        psoc_MasterClearReadBuf();
        psoc_MasterClearWriteBuf();
        (void) psoc_MasterClearStatus();
    #endif /* (psoc_MODE_MASTER_ENABLED) */
}


/*******************************************************************************
* Function Name: psoc_Enable
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
void psoc_Enable(void) 
{
    #if(psoc_FF_IMPLEMENTED)
        uint8 enableInterrupts;

        /* Enable power to I2C FF block */
        enableInterrupts = CyEnterCriticalSection();
        psoc_ACT_PWRMGR_REG  |= psoc_ACT_PWR_EN;
        psoc_STBY_PWRMGR_REG |= psoc_STBY_PWR_EN;
        CyExitCriticalSection(enableInterrupts);

    #else

        #if(psoc_MODE_SLAVE_ENABLED)
            uint8 enableInterrupts;
        #endif /* (psoc_MODE_SLAVE_ENABLED) */

        #if(psoc_MODE_SLAVE_ENABLED)
            /* Enable slave bit counter */
            enableInterrupts = CyEnterCriticalSection();
            psoc_COUNTER_AUX_CTL_REG |= psoc_CNT7_ENABLE;   /* aux_ctl */
            CyExitCriticalSection(enableInterrupts);
        #endif /* (psoc_MODE_SLAVE_ENABLED) */

        psoc_CFG_REG |= psoc_ENABLE_MS;

    #endif /* (psoc_FF_IMPLEMENTED) */

    #if(psoc_TIMEOUT_ENABLED)
        psoc_TimeoutEnable();
    #endif /* (psoc_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: psoc_Start
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
*  psoc_initVar - used to check initial configuration, modified
*  on first function call.
*
* Reentrant:
*  No
*
*******************************************************************************/
void psoc_Start(void) 
{
    /* Initialize I2C registers, reset I2C buffer index and clears status */
    if(0u == psoc_initVar)
    {
        psoc_Init();
        psoc_initVar = 1u; /* Component initialized */
    }

    psoc_Enable();
    psoc_EnableInt();
}


/*******************************************************************************
* Function Name: psoc_Stop
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
void psoc_Stop(void) 
{
    #if((psoc_FF_IMPLEMENTED)  || \
        (psoc_UDB_IMPLEMENTED && psoc_MODE_SLAVE_ENABLED))
        uint8 enableInterrupts;
    #endif /* ((psoc_FF_IMPLEMENTED)  || \
               (psoc_UDB_IMPLEMENTED && psoc_MODE_SLAVE_ENABLED)) */

    psoc_DisableInt();

    psoc_DISABLE_INT_ON_STOP;   /* Interrupt on Stop can be enabled by write */
    (void) psoc_CSR_REG;        /* Clear CSR reg */
    
    #if(psoc_TIMEOUT_ENABLED)
        psoc_TimeoutStop();
    #endif  /* End (psoc_TIMEOUT_ENABLED) */

    #if(psoc_FF_IMPLEMENTED)
        #if(CY_PSOC3 || CY_PSOC5LP)
            /* Store registers which are held in reset when Master and Slave bits are cleared */
            #if(psoc_MODE_SLAVE_ENABLED)
                psoc_backup.addr = psoc_ADDR_REG;
            #endif /* (psoc_MODE_SLAVE_ENABLED) */

            psoc_backup.clkDiv1  = psoc_CLKDIV1_REG;
            psoc_backup.clkDiv2  = psoc_CLKDIV2_REG;


            /* Reset FF block */
            psoc_CFG_REG &= ((uint8) ~psoc_ENABLE_MS);
            CyDelayUs(psoc_FF_RESET_DELAY);
            psoc_CFG_REG |= ((uint8)  psoc_ENABLE_MS);


            /* Restore registers */
            #if(psoc_MODE_SLAVE_ENABLED)
                psoc_ADDR_REG = psoc_backup.addr;
            #endif /* (psoc_MODE_SLAVE_ENABLED) */

            psoc_CLKDIV1_REG = psoc_backup.clkDiv1;
            psoc_CLKDIV2_REG = psoc_backup.clkDiv2;

        #endif /* (CY_PSOC3 || CY_PSOC5LP) */

        /* Disable power to I2C block */
        enableInterrupts = CyEnterCriticalSection();
        psoc_ACT_PWRMGR_REG  &= ((uint8) ~psoc_ACT_PWR_EN);
        psoc_STBY_PWRMGR_REG &= ((uint8) ~psoc_STBY_PWR_EN);
        CyExitCriticalSection(enableInterrupts);

    #else

        #if(psoc_MODE_SLAVE_ENABLED)
            /* Disable slave bit counter */
            enableInterrupts = CyEnterCriticalSection();
            psoc_COUNTER_AUX_CTL_REG &= ((uint8) ~psoc_CNT7_ENABLE);
            CyExitCriticalSection(enableInterrupts);
        #endif /* (psoc_MODE_SLAVE_ENABLED) */

        psoc_CFG_REG &= ((uint8) ~psoc_ENABLE_MS);

    #endif /* (psoc_FF_IMPLEMENTED) */

    psoc_ClearPendingInt();  /* Clear interrupt triggers on reset */

    psoc_state = psoc_SM_IDLE;  /* Reset software FSM */
}


/* [] END OF FILE */
