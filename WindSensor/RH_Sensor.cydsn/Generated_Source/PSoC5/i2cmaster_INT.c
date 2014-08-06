/*******************************************************************************
* File Name: i2cmaster_INT.c
* Version 3.30
*
* Description:
*  This file provides the source code of Interrupt Service Routine (ISR)
*  for I2C component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "i2cmaster_PVT.h"


/*******************************************************************************
*  Place your includes, defines and code here
********************************************************************************/
/* `#START i2cmaster_ISR_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: i2cmaster_ISR
********************************************************************************
*
* Summary:
*  Handler for I2C interrupt. The Slave and Master operations are handled here.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Reentrant:
*  No
*
*******************************************************************************/
CY_ISR(i2cmaster_ISR)
{
    #if(i2cmaster_MODE_SLAVE_ENABLED)
       uint8  tmp8;
    #endif  /* (i2cmaster_MODE_SLAVE_ENABLED) */

    uint8  tmpCsr;

    #if(i2cmaster_TIMEOUT_FF_ENABLED)
        if(0u != i2cmaster_TimeoutGetStatus())
        {
            i2cmaster_TimeoutReset();
            i2cmaster_state = i2cmaster_SM_EXIT_IDLE;
            /* i2cmaster_CSR_REG should be cleared after reset */
        }
    #endif /* (i2cmaster_TIMEOUT_FF_ENABLED) */


    tmpCsr = i2cmaster_CSR_REG;      /* Make copy as interrupts clear */

    #if(i2cmaster_MODE_MULTI_MASTER_SLAVE_ENABLED)
        if(i2cmaster_CHECK_START_GEN(i2cmaster_MCSR_REG))
        {
            i2cmaster_CLEAR_START_GEN;

            /* Set READ complete, but was aborted */
            i2cmaster_mstrStatus |= (i2cmaster_MSTAT_ERR_XFER |
                                            i2cmaster_GET_MSTAT_CMPLT);

            /* The slave was addressed */
            i2cmaster_state = i2cmaster_SM_SLAVE;
        }
    #endif /* (i2cmaster_MODE_MULTI_MASTER_SLAVE_ENABLED) */


    #if(i2cmaster_MODE_MULTI_MASTER_ENABLED)
        if(i2cmaster_CHECK_LOST_ARB(tmpCsr))
        {
            /* Set errors */
            i2cmaster_mstrStatus |= (i2cmaster_MSTAT_ERR_XFER     |
                                            i2cmaster_MSTAT_ERR_ARB_LOST |
                                            i2cmaster_GET_MSTAT_CMPLT);

            i2cmaster_DISABLE_INT_ON_STOP; /* Interrupt on Stop is enabled by write */

            #if(i2cmaster_MODE_MULTI_MASTER_SLAVE_ENABLED)
                if(i2cmaster_CHECK_ADDRESS_STS(tmpCsr))
                {
                    /* The slave was addressed */
                    i2cmaster_state = i2cmaster_SM_SLAVE;
                }
                else
                {
                    i2cmaster_BUS_RELEASE;

                    i2cmaster_state = i2cmaster_SM_EXIT_IDLE;
                }
            #else
                i2cmaster_BUS_RELEASE;

                i2cmaster_state = i2cmaster_SM_EXIT_IDLE;

            #endif /* (i2cmaster_MODE_MULTI_MASTER_SLAVE_ENABLED) */
        }
    #endif /* (i2cmaster_MODE_MULTI_MASTER_ENABLED) */

    /* Check for Master operation mode */
    if(i2cmaster_CHECK_SM_MASTER)
    {
        #if(i2cmaster_MODE_MASTER_ENABLED)
            if(i2cmaster_CHECK_BYTE_COMPLETE(tmpCsr))
            {
                switch (i2cmaster_state)
                {
                case i2cmaster_SM_MSTR_WR_ADDR:  /* After address is sent, WRITE data */
                case i2cmaster_SM_MSTR_RD_ADDR:  /* After address is sent, READ  data */

                    tmpCsr &= ((uint8) ~i2cmaster_CSR_STOP_STATUS); /* Clear STOP bit history on address phase */
                    
                    if(i2cmaster_CHECK_ADDR_ACK(tmpCsr))
                    {
                        /* Setup for transmit or receive of data */
                        if(i2cmaster_state == i2cmaster_SM_MSTR_WR_ADDR)   /* TRANSMIT data */
                        {
                            /* Check if at least one byte to transfer */
                            if(i2cmaster_mstrWrBufSize > 0u)
                            {
                                /* Load the 1st data byte */
                                i2cmaster_DATA_REG = i2cmaster_mstrWrBufPtr[0u];
                                i2cmaster_TRANSMIT_DATA;
                                i2cmaster_mstrWrBufIndex = 1u;   /* Set index to 2nd element */

                                /* Set transmit state until done */
                                i2cmaster_state = i2cmaster_SM_MSTR_WR_DATA;
                            }
                            /* End of buffer: complete writing */
                            else if(i2cmaster_CHECK_NO_STOP(i2cmaster_mstrControl))
                            {
                                #if(CY_PSOC5A)
                                    /* Do not handles 0 bytes transfer - HALT is NOT allowed */
                                    i2cmaster_ENABLE_INT_ON_STOP;
                                    i2cmaster_GENERATE_STOP;
                                
                                #else
                                    /* Set WRITE complete and Master HALTED */
                                    i2cmaster_mstrStatus |= (i2cmaster_MSTAT_XFER_HALT |
                                                                    i2cmaster_MSTAT_WR_CMPLT);

                                    i2cmaster_state = i2cmaster_SM_MSTR_HALT; /* Expect RESTART */
                                    i2cmaster_DisableInt();
                                
                                #endif /* (CY_PSOC5A) */
                            }
                            else
                            {
                                i2cmaster_ENABLE_INT_ON_STOP; /* Enable interrupt on STOP, to catch it */
                                i2cmaster_GENERATE_STOP;
                            }
                        }
                        else  /* Master Receive data */
                        {
                            i2cmaster_READY_TO_READ; /* Release bus to read data */

                            i2cmaster_state  = i2cmaster_SM_MSTR_RD_DATA;
                        }
                    }
                    /* Address is NACKed */
                    else if(i2cmaster_CHECK_ADDR_NAK(tmpCsr))
                    {
                        /* Set Address NAK error */
                        i2cmaster_mstrStatus |= (i2cmaster_MSTAT_ERR_XFER |
                                                        i2cmaster_MSTAT_ERR_ADDR_NAK);
                                                        
                        if(i2cmaster_CHECK_NO_STOP(i2cmaster_mstrControl))
                        {
                            i2cmaster_mstrStatus |= (i2cmaster_MSTAT_XFER_HALT | 
                                                            i2cmaster_GET_MSTAT_CMPLT);

                            i2cmaster_state = i2cmaster_SM_MSTR_HALT; /* Expect RESTART */
                            i2cmaster_DisableInt();
                        }
                        else  /* Do normal Stop */
                        {
                            i2cmaster_ENABLE_INT_ON_STOP; /* Enable interrupt on STOP, to catch it */
                            i2cmaster_GENERATE_STOP;
                        }
                    }
                    else
                    {
                        /* Address phase is not set for some reason: error */
                        #if(i2cmaster_TIMEOUT_ENABLED)
                            /* Exit from interrupt to take a chance for timeout timer handle this case */
                            i2cmaster_DisableInt();
                            i2cmaster_ClearPendingInt();
                        #else
                            /* Block execution flow: unexpected condition */
                            CYASSERT(0u != 0u);
                        #endif /* (i2cmaster_TIMEOUT_ENABLED) */
                    }
                    break;

                case i2cmaster_SM_MSTR_WR_DATA:

                    if(i2cmaster_CHECK_DATA_ACK(tmpCsr))
                    {
                        /* Check if end of buffer */
                        if(i2cmaster_mstrWrBufIndex  < i2cmaster_mstrWrBufSize)
                        {
                            i2cmaster_DATA_REG =
                                                     i2cmaster_mstrWrBufPtr[i2cmaster_mstrWrBufIndex];
                            i2cmaster_TRANSMIT_DATA;
                            i2cmaster_mstrWrBufIndex++;
                        }
                        /* End of buffer: complete writing */
                        else if(i2cmaster_CHECK_NO_STOP(i2cmaster_mstrControl))
                        {
                            /* Set WRITE complete and Master HALTED */
                            i2cmaster_mstrStatus |= (i2cmaster_MSTAT_XFER_HALT |
                                                            i2cmaster_MSTAT_WR_CMPLT);

                            i2cmaster_state = i2cmaster_SM_MSTR_HALT;    /* Expect RESTART */
                            i2cmaster_DisableInt();
                        }
                        else  /* Do normal STOP */
                        {
                            i2cmaster_Workaround();          /* Workaround: empty function */
                            i2cmaster_ENABLE_INT_ON_STOP;    /* Enable interrupt on STOP, to catch it */
                            i2cmaster_GENERATE_STOP;
                        }
                    }
                    /* Last byte NAKed: end writing */
                    else if(i2cmaster_CHECK_NO_STOP(i2cmaster_mstrControl))
                    {
                        /* Set WRITE complete, SHORT transfer and Master HALTED */
                        i2cmaster_mstrStatus |= (i2cmaster_MSTAT_ERR_XFER       |
                                                        i2cmaster_MSTAT_ERR_SHORT_XFER |
                                                        i2cmaster_MSTAT_XFER_HALT      |
                                                        i2cmaster_MSTAT_WR_CMPLT);

                        i2cmaster_state = i2cmaster_SM_MSTR_HALT;    /* Expect RESTART */
                        i2cmaster_DisableInt();
                    }
                    else  /* Do normal STOP */
                    {
                        i2cmaster_ENABLE_INT_ON_STOP;    /* Enable interrupt on STOP, to catch it */
                        i2cmaster_GENERATE_STOP;

                        /* Set SHORT and ERR transfer */
                        i2cmaster_mstrStatus |= (i2cmaster_MSTAT_ERR_SHORT_XFER |
                                                        i2cmaster_MSTAT_ERR_XFER);
                    }
                    
                    break;

                case i2cmaster_SM_MSTR_RD_DATA:

                    i2cmaster_mstrRdBufPtr[i2cmaster_mstrRdBufIndex] = i2cmaster_DATA_REG;
                    i2cmaster_mstrRdBufIndex++;

                    /* Check if end of buffer */
                    if(i2cmaster_mstrRdBufIndex < i2cmaster_mstrRdBufSize)
                    {
                        i2cmaster_ACK_AND_RECEIVE;       /* ACK and receive byte */
                    }
                    /* End of buffer: complete reading */
                    else if(i2cmaster_CHECK_NO_STOP(i2cmaster_mstrControl))
                    {                        
                        /* Set READ complete and Master HALTED */
                        i2cmaster_mstrStatus |= (i2cmaster_MSTAT_XFER_HALT |
                                                        i2cmaster_MSTAT_RD_CMPLT);
                        
                        i2cmaster_state = i2cmaster_SM_MSTR_HALT;    /* Expect RESTART */
                        i2cmaster_DisableInt();
                    }
                    else
                    {
                        i2cmaster_ENABLE_INT_ON_STOP;
                        i2cmaster_NAK_AND_RECEIVE;       /* NACK and TRY to generate STOP */
                    }
                    break;

                default: /* This is an invalid state and should not occur */

                    #if(i2cmaster_TIMEOUT_ENABLED)
                        /* Exit from interrupt to take a chance for timeout timer handle this case */
                        i2cmaster_DisableInt();
                        i2cmaster_ClearPendingInt();
                    #else
                        /* Block execution flow: unexpected condition */
                        CYASSERT(0u != 0u);
                    #endif /* (i2cmaster_TIMEOUT_ENABLED) */

                    break;
                }
            }

            /* Catches the Stop: end of transaction */
            if(i2cmaster_CHECK_STOP_STS(tmpCsr))
            {
                i2cmaster_mstrStatus |= i2cmaster_GET_MSTAT_CMPLT;

                i2cmaster_DISABLE_INT_ON_STOP;
                i2cmaster_state = i2cmaster_SM_IDLE;
            }
        #endif /* (i2cmaster_MODE_MASTER_ENABLED) */
    }
    else if(i2cmaster_CHECK_SM_SLAVE)
    {
        #if(i2cmaster_MODE_SLAVE_ENABLED)
            
            if((i2cmaster_CHECK_STOP_STS(tmpCsr)) || /* Stop || Restart */
               (i2cmaster_CHECK_BYTE_COMPLETE(tmpCsr) && i2cmaster_CHECK_ADDRESS_STS(tmpCsr)))
            {
                /* Catch end of master write transcation: use interrupt on Stop */
                /* The STOP bit history on address phase does not have correct state */
                if(i2cmaster_SM_SL_WR_DATA == i2cmaster_state)
                {
                    i2cmaster_DISABLE_INT_ON_STOP;

                    i2cmaster_slStatus &= ((uint8) ~i2cmaster_SSTAT_WR_BUSY);
                    i2cmaster_slStatus |= ((uint8)  i2cmaster_SSTAT_WR_CMPLT);

                    i2cmaster_state = i2cmaster_SM_IDLE;
                }
            }

            if(i2cmaster_CHECK_BYTE_COMPLETE(tmpCsr))
            {
                /* The address only issued after Start or ReStart: so check address
                   to catch this events:
                    FF : sets Addr phase with byte_complete interrupt trigger.
                    UDB: sets Addr phase immediately after Start or ReStart. */
                if(i2cmaster_CHECK_ADDRESS_STS(tmpCsr))
                {
                    /* Check for software address detection */
                    #if(i2cmaster_SW_ADRR_DECODE)
                        tmp8 = i2cmaster_GET_SLAVE_ADDR(i2cmaster_DATA_REG);

                        if(tmp8 == i2cmaster_slAddress)   /* Check for address match */
                        {
                            if(0u != (i2cmaster_DATA_REG & i2cmaster_READ_FLAG))
                            {
                                /* Place code to prepare read buffer here                  */
                                /* `#START i2cmaster_SW_PREPARE_READ_BUF_interrupt` */

                                /* `#END` */

                                /* Prepare next opeation to read, get data and place in data register */
                                if(i2cmaster_slRdBufIndex < i2cmaster_slRdBufSize)
                                {
                                    /* Load first data byte from array */
                                    i2cmaster_DATA_REG = i2cmaster_slRdBufPtr[i2cmaster_slRdBufIndex];
                                    i2cmaster_ACK_AND_TRANSMIT;
                                    i2cmaster_slRdBufIndex++;

                                    i2cmaster_slStatus |= i2cmaster_SSTAT_RD_BUSY;
                                }
                                else    /* Overflow: provide 0xFF on the bus */
                                {
                                    i2cmaster_DATA_REG = i2cmaster_OVERFLOW_RETURN;
                                    i2cmaster_ACK_AND_TRANSMIT;

                                    i2cmaster_slStatus  |= (i2cmaster_SSTAT_RD_BUSY |
                                                                   i2cmaster_SSTAT_RD_ERR_OVFL);
                                }

                                i2cmaster_state = i2cmaster_SM_SL_RD_DATA;
                            }
                            else  /* Write transaction: receive 1st byte */
                            {
                                i2cmaster_ACK_AND_RECEIVE;
                                i2cmaster_state = i2cmaster_SM_SL_WR_DATA;

                                i2cmaster_slStatus |= i2cmaster_SSTAT_WR_BUSY;
                                i2cmaster_ENABLE_INT_ON_STOP;
                            }
                        }    
                        else
                        {
                            /*     Place code to compare for additional address here    */
                            /* `#START i2cmaster_SW_ADDR_COMPARE_interruptStart` */

                            /* `#END` */
                            
                            i2cmaster_NAK_AND_RECEIVE;   /* NACK address */

                            /* Place code to end of condition for NACK generation here */
                            /* `#START i2cmaster_SW_ADDR_COMPARE_interruptEnd`  */

                            /* `#END` */
                        }
                        
                    #else /* (i2cmaster_HW_ADRR_DECODE) */
                        
                        if(0u != (i2cmaster_DATA_REG & i2cmaster_READ_FLAG))
                        {
                            /* Place code to prepare read buffer here                  */
                            /* `#START i2cmaster_HW_PREPARE_READ_BUF_interrupt` */

                            /* `#END` */

                            /* Prepare next opeation to read, get data and place in data register */
                            if(i2cmaster_slRdBufIndex < i2cmaster_slRdBufSize)
                            {
                                /* Load first data byte from array */
                                i2cmaster_DATA_REG = i2cmaster_slRdBufPtr[i2cmaster_slRdBufIndex];
                                i2cmaster_ACK_AND_TRANSMIT;
                                i2cmaster_slRdBufIndex++;

                                i2cmaster_slStatus |= i2cmaster_SSTAT_RD_BUSY;
                            }
                            else    /* Overflow: provide 0xFF on the bus */
                            {
                                i2cmaster_DATA_REG = i2cmaster_OVERFLOW_RETURN;
                                i2cmaster_ACK_AND_TRANSMIT;

                                i2cmaster_slStatus  |= (i2cmaster_SSTAT_RD_BUSY |
                                                               i2cmaster_SSTAT_RD_ERR_OVFL);
                            }

                            i2cmaster_state = i2cmaster_SM_SL_RD_DATA;
                        }
                        else  /* Write transaction: receive 1st byte */
                        {
                            i2cmaster_ACK_AND_RECEIVE;
                            i2cmaster_state = i2cmaster_SM_SL_WR_DATA;

                            i2cmaster_slStatus |= i2cmaster_SSTAT_WR_BUSY;
                            i2cmaster_ENABLE_INT_ON_STOP;
                        }
                        
                    #endif /* (i2cmaster_SW_ADRR_DECODE) */
                }
                /* Data states */
                /* Data master writes into slave */
                else if(i2cmaster_state == i2cmaster_SM_SL_WR_DATA)
                {
                    if(i2cmaster_slWrBufIndex < i2cmaster_slWrBufSize)
                    {
                        tmp8 = i2cmaster_DATA_REG;
                        i2cmaster_ACK_AND_RECEIVE;
                        i2cmaster_slWrBufPtr[i2cmaster_slWrBufIndex] = tmp8;
                        i2cmaster_slWrBufIndex++;
                    }
                    else  /* of array: complete write, send NACK */
                    {
                        i2cmaster_NAK_AND_RECEIVE;

                        i2cmaster_slStatus |= i2cmaster_SSTAT_WR_ERR_OVFL;
                    }
                }
                /* Data master reads from slave */
                else if(i2cmaster_state == i2cmaster_SM_SL_RD_DATA)
                {
                    if(i2cmaster_CHECK_DATA_ACK(tmpCsr))
                    {
                        if(i2cmaster_slRdBufIndex < i2cmaster_slRdBufSize)
                        {
                             /* Get data from array */
                            i2cmaster_DATA_REG = i2cmaster_slRdBufPtr[i2cmaster_slRdBufIndex];
                            i2cmaster_TRANSMIT_DATA;
                            i2cmaster_slRdBufIndex++;
                        }
                        else   /* Overflow: provide 0xFF on the bus */
                        {
                            i2cmaster_DATA_REG = i2cmaster_OVERFLOW_RETURN;
                            i2cmaster_TRANSMIT_DATA;

                            i2cmaster_slStatus |= i2cmaster_SSTAT_RD_ERR_OVFL;
                        }
                    }
                    else  /* Last byte was NACKed: read complete */
                    {
                        /* Only NACK appears on the bus */
                        i2cmaster_DATA_REG = i2cmaster_OVERFLOW_RETURN;
                        i2cmaster_NAK_AND_TRANSMIT;

                        i2cmaster_slStatus &= ((uint8) ~i2cmaster_SSTAT_RD_BUSY);
                        i2cmaster_slStatus |= ((uint8)  i2cmaster_SSTAT_RD_CMPLT);

                        i2cmaster_state = i2cmaster_SM_IDLE;
                    }
                }
                else
                {
                    #if(i2cmaster_TIMEOUT_ENABLED)
                        /* Exit from interrupt to take a chance for timeout timer handle this case */
                        i2cmaster_DisableInt();
                        i2cmaster_ClearPendingInt();
                    #else
                        /* Block execution flow: unexpected condition */
                        CYASSERT(0u != 0u);
                    #endif /* (i2cmaster_TIMEOUT_ENABLED) */
                }
            }
        #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */
    }
    else
    {
        /* The FSM skips master and slave processing: return to IDLE */
        i2cmaster_state = i2cmaster_SM_IDLE;
    }
}


#if((i2cmaster_FF_IMPLEMENTED) && (i2cmaster_WAKEUP_ENABLED))
    /*******************************************************************************
    * Function Name: i2cmaster_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Empty interrupt handler to trigger after wakeup.
    *
    * Parameters:
    *  void
    *
    * Return:
    *  void
    *
    *******************************************************************************/
    CY_ISR(i2cmaster_WAKEUP_ISR)
    {
        i2cmaster_wakeupSource = 1u;  /* I2C was wakeup source */
        /* The SCL is stretched unitl the I2C_Wake() is called */
    }
#endif /* ((i2cmaster_FF_IMPLEMENTED) && (i2cmaster_WAKEUP_ENABLED))*/


/* [] END OF FILE */
