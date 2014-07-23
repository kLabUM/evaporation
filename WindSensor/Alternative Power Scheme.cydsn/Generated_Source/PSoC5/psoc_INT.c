/*******************************************************************************
* File Name: psoc_INT.c
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

#include "psoc_PVT.h"


/*******************************************************************************
*  Place your includes, defines and code here
********************************************************************************/
/* `#START psoc_ISR_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: psoc_ISR
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
CY_ISR(psoc_ISR)
{
    #if(psoc_MODE_SLAVE_ENABLED)
       uint8  tmp8;
    #endif  /* (psoc_MODE_SLAVE_ENABLED) */

    uint8  tmpCsr;

    #if(psoc_TIMEOUT_FF_ENABLED)
        if(0u != psoc_TimeoutGetStatus())
        {
            psoc_TimeoutReset();
            psoc_state = psoc_SM_EXIT_IDLE;
            /* psoc_CSR_REG should be cleared after reset */
        }
    #endif /* (psoc_TIMEOUT_FF_ENABLED) */


    tmpCsr = psoc_CSR_REG;      /* Make copy as interrupts clear */

    #if(psoc_MODE_MULTI_MASTER_SLAVE_ENABLED)
        if(psoc_CHECK_START_GEN(psoc_MCSR_REG))
        {
            psoc_CLEAR_START_GEN;

            /* Set READ complete, but was aborted */
            psoc_mstrStatus |= (psoc_MSTAT_ERR_XFER |
                                            psoc_GET_MSTAT_CMPLT);

            /* The slave was addressed */
            psoc_state = psoc_SM_SLAVE;
        }
    #endif /* (psoc_MODE_MULTI_MASTER_SLAVE_ENABLED) */


    #if(psoc_MODE_MULTI_MASTER_ENABLED)
        if(psoc_CHECK_LOST_ARB(tmpCsr))
        {
            /* Set errors */
            psoc_mstrStatus |= (psoc_MSTAT_ERR_XFER     |
                                            psoc_MSTAT_ERR_ARB_LOST |
                                            psoc_GET_MSTAT_CMPLT);

            psoc_DISABLE_INT_ON_STOP; /* Interrupt on Stop is enabled by write */

            #if(psoc_MODE_MULTI_MASTER_SLAVE_ENABLED)
                if(psoc_CHECK_ADDRESS_STS(tmpCsr))
                {
                    /* The slave was addressed */
                    psoc_state = psoc_SM_SLAVE;
                }
                else
                {
                    psoc_BUS_RELEASE;

                    psoc_state = psoc_SM_EXIT_IDLE;
                }
            #else
                psoc_BUS_RELEASE;

                psoc_state = psoc_SM_EXIT_IDLE;

            #endif /* (psoc_MODE_MULTI_MASTER_SLAVE_ENABLED) */
        }
    #endif /* (psoc_MODE_MULTI_MASTER_ENABLED) */

    /* Check for Master operation mode */
    if(psoc_CHECK_SM_MASTER)
    {
        #if(psoc_MODE_MASTER_ENABLED)
            if(psoc_CHECK_BYTE_COMPLETE(tmpCsr))
            {
                switch (psoc_state)
                {
                case psoc_SM_MSTR_WR_ADDR:  /* After address is sent, WRITE data */
                case psoc_SM_MSTR_RD_ADDR:  /* After address is sent, READ  data */

                    tmpCsr &= ((uint8) ~psoc_CSR_STOP_STATUS); /* Clear STOP bit history on address phase */
                    
                    if(psoc_CHECK_ADDR_ACK(tmpCsr))
                    {
                        /* Setup for transmit or receive of data */
                        if(psoc_state == psoc_SM_MSTR_WR_ADDR)   /* TRANSMIT data */
                        {
                            /* Check if at least one byte to transfer */
                            if(psoc_mstrWrBufSize > 0u)
                            {
                                /* Load the 1st data byte */
                                psoc_DATA_REG = psoc_mstrWrBufPtr[0u];
                                psoc_TRANSMIT_DATA;
                                psoc_mstrWrBufIndex = 1u;   /* Set index to 2nd element */

                                /* Set transmit state until done */
                                psoc_state = psoc_SM_MSTR_WR_DATA;
                            }
                            /* End of buffer: complete writing */
                            else if(psoc_CHECK_NO_STOP(psoc_mstrControl))
                            {
                                #if(CY_PSOC5A)
                                    /* Do not handles 0 bytes transfer - HALT is NOT allowed */
                                    psoc_ENABLE_INT_ON_STOP;
                                    psoc_GENERATE_STOP;
                                
                                #else
                                    /* Set WRITE complete and Master HALTED */
                                    psoc_mstrStatus |= (psoc_MSTAT_XFER_HALT |
                                                                    psoc_MSTAT_WR_CMPLT);

                                    psoc_state = psoc_SM_MSTR_HALT; /* Expect RESTART */
                                    psoc_DisableInt();
                                
                                #endif /* (CY_PSOC5A) */
                            }
                            else
                            {
                                psoc_ENABLE_INT_ON_STOP; /* Enable interrupt on STOP, to catch it */
                                psoc_GENERATE_STOP;
                            }
                        }
                        else  /* Master Receive data */
                        {
                            psoc_READY_TO_READ; /* Release bus to read data */

                            psoc_state  = psoc_SM_MSTR_RD_DATA;
                        }
                    }
                    /* Address is NACKed */
                    else if(psoc_CHECK_ADDR_NAK(tmpCsr))
                    {
                        /* Set Address NAK error */
                        psoc_mstrStatus |= (psoc_MSTAT_ERR_XFER |
                                                        psoc_MSTAT_ERR_ADDR_NAK);
                                                        
                        if(psoc_CHECK_NO_STOP(psoc_mstrControl))
                        {
                            psoc_mstrStatus |= (psoc_MSTAT_XFER_HALT | 
                                                            psoc_GET_MSTAT_CMPLT);

                            psoc_state = psoc_SM_MSTR_HALT; /* Expect RESTART */
                            psoc_DisableInt();
                        }
                        else  /* Do normal Stop */
                        {
                            psoc_ENABLE_INT_ON_STOP; /* Enable interrupt on STOP, to catch it */
                            psoc_GENERATE_STOP;
                        }
                    }
                    else
                    {
                        /* Address phase is not set for some reason: error */
                        #if(psoc_TIMEOUT_ENABLED)
                            /* Exit from interrupt to take a chance for timeout timer handle this case */
                            psoc_DisableInt();
                            psoc_ClearPendingInt();
                        #else
                            /* Block execution flow: unexpected condition */
                            CYASSERT(0u != 0u);
                        #endif /* (psoc_TIMEOUT_ENABLED) */
                    }
                    break;

                case psoc_SM_MSTR_WR_DATA:

                    if(psoc_CHECK_DATA_ACK(tmpCsr))
                    {
                        /* Check if end of buffer */
                        if(psoc_mstrWrBufIndex  < psoc_mstrWrBufSize)
                        {
                            psoc_DATA_REG =
                                                     psoc_mstrWrBufPtr[psoc_mstrWrBufIndex];
                            psoc_TRANSMIT_DATA;
                            psoc_mstrWrBufIndex++;
                        }
                        /* End of buffer: complete writing */
                        else if(psoc_CHECK_NO_STOP(psoc_mstrControl))
                        {
                            /* Set WRITE complete and Master HALTED */
                            psoc_mstrStatus |= (psoc_MSTAT_XFER_HALT |
                                                            psoc_MSTAT_WR_CMPLT);

                            psoc_state = psoc_SM_MSTR_HALT;    /* Expect RESTART */
                            psoc_DisableInt();
                        }
                        else  /* Do normal STOP */
                        {
                            psoc_Workaround();          /* Workaround: empty function */
                            psoc_ENABLE_INT_ON_STOP;    /* Enable interrupt on STOP, to catch it */
                            psoc_GENERATE_STOP;
                        }
                    }
                    /* Last byte NAKed: end writing */
                    else if(psoc_CHECK_NO_STOP(psoc_mstrControl))
                    {
                        /* Set WRITE complete, SHORT transfer and Master HALTED */
                        psoc_mstrStatus |= (psoc_MSTAT_ERR_XFER       |
                                                        psoc_MSTAT_ERR_SHORT_XFER |
                                                        psoc_MSTAT_XFER_HALT      |
                                                        psoc_MSTAT_WR_CMPLT);

                        psoc_state = psoc_SM_MSTR_HALT;    /* Expect RESTART */
                        psoc_DisableInt();
                    }
                    else  /* Do normal STOP */
                    {
                        psoc_ENABLE_INT_ON_STOP;    /* Enable interrupt on STOP, to catch it */
                        psoc_GENERATE_STOP;

                        /* Set SHORT and ERR transfer */
                        psoc_mstrStatus |= (psoc_MSTAT_ERR_SHORT_XFER |
                                                        psoc_MSTAT_ERR_XFER);
                    }
                    
                    break;

                case psoc_SM_MSTR_RD_DATA:

                    psoc_mstrRdBufPtr[psoc_mstrRdBufIndex] = psoc_DATA_REG;
                    psoc_mstrRdBufIndex++;

                    /* Check if end of buffer */
                    if(psoc_mstrRdBufIndex < psoc_mstrRdBufSize)
                    {
                        psoc_ACK_AND_RECEIVE;       /* ACK and receive byte */
                    }
                    /* End of buffer: complete reading */
                    else if(psoc_CHECK_NO_STOP(psoc_mstrControl))
                    {                        
                        /* Set READ complete and Master HALTED */
                        psoc_mstrStatus |= (psoc_MSTAT_XFER_HALT |
                                                        psoc_MSTAT_RD_CMPLT);
                        
                        psoc_state = psoc_SM_MSTR_HALT;    /* Expect RESTART */
                        psoc_DisableInt();
                    }
                    else
                    {
                        psoc_ENABLE_INT_ON_STOP;
                        psoc_NAK_AND_RECEIVE;       /* NACK and TRY to generate STOP */
                    }
                    break;

                default: /* This is an invalid state and should not occur */

                    #if(psoc_TIMEOUT_ENABLED)
                        /* Exit from interrupt to take a chance for timeout timer handle this case */
                        psoc_DisableInt();
                        psoc_ClearPendingInt();
                    #else
                        /* Block execution flow: unexpected condition */
                        CYASSERT(0u != 0u);
                    #endif /* (psoc_TIMEOUT_ENABLED) */

                    break;
                }
            }

            /* Catches the Stop: end of transaction */
            if(psoc_CHECK_STOP_STS(tmpCsr))
            {
                psoc_mstrStatus |= psoc_GET_MSTAT_CMPLT;

                psoc_DISABLE_INT_ON_STOP;
                psoc_state = psoc_SM_IDLE;
            }
        #endif /* (psoc_MODE_MASTER_ENABLED) */
    }
    else if(psoc_CHECK_SM_SLAVE)
    {
        #if(psoc_MODE_SLAVE_ENABLED)
            
            if((psoc_CHECK_STOP_STS(tmpCsr)) || /* Stop || Restart */
               (psoc_CHECK_BYTE_COMPLETE(tmpCsr) && psoc_CHECK_ADDRESS_STS(tmpCsr)))
            {
                /* Catch end of master write transcation: use interrupt on Stop */
                /* The STOP bit history on address phase does not have correct state */
                if(psoc_SM_SL_WR_DATA == psoc_state)
                {
                    psoc_DISABLE_INT_ON_STOP;

                    psoc_slStatus &= ((uint8) ~psoc_SSTAT_WR_BUSY);
                    psoc_slStatus |= ((uint8)  psoc_SSTAT_WR_CMPLT);

                    psoc_state = psoc_SM_IDLE;
                }
            }

            if(psoc_CHECK_BYTE_COMPLETE(tmpCsr))
            {
                /* The address only issued after Start or ReStart: so check address
                   to catch this events:
                    FF : sets Addr phase with byte_complete interrupt trigger.
                    UDB: sets Addr phase immediately after Start or ReStart. */
                if(psoc_CHECK_ADDRESS_STS(tmpCsr))
                {
                    /* Check for software address detection */
                    #if(psoc_SW_ADRR_DECODE)
                        tmp8 = psoc_GET_SLAVE_ADDR(psoc_DATA_REG);

                        if(tmp8 == psoc_slAddress)   /* Check for address match */
                        {
                            if(0u != (psoc_DATA_REG & psoc_READ_FLAG))
                            {
                                /* Place code to prepare read buffer here                  */
                                /* `#START psoc_SW_PREPARE_READ_BUF_interrupt` */

                                /* `#END` */

                                /* Prepare next opeation to read, get data and place in data register */
                                if(psoc_slRdBufIndex < psoc_slRdBufSize)
                                {
                                    /* Load first data byte from array */
                                    psoc_DATA_REG = psoc_slRdBufPtr[psoc_slRdBufIndex];
                                    psoc_ACK_AND_TRANSMIT;
                                    psoc_slRdBufIndex++;

                                    psoc_slStatus |= psoc_SSTAT_RD_BUSY;
                                }
                                else    /* Overflow: provide 0xFF on the bus */
                                {
                                    psoc_DATA_REG = psoc_OVERFLOW_RETURN;
                                    psoc_ACK_AND_TRANSMIT;

                                    psoc_slStatus  |= (psoc_SSTAT_RD_BUSY |
                                                                   psoc_SSTAT_RD_ERR_OVFL);
                                }

                                psoc_state = psoc_SM_SL_RD_DATA;
                            }
                            else  /* Write transaction: receive 1st byte */
                            {
                                psoc_ACK_AND_RECEIVE;
                                psoc_state = psoc_SM_SL_WR_DATA;

                                psoc_slStatus |= psoc_SSTAT_WR_BUSY;
                                psoc_ENABLE_INT_ON_STOP;
                            }
                        }    
                        else
                        {
                            /*     Place code to compare for additional address here    */
                            /* `#START psoc_SW_ADDR_COMPARE_interruptStart` */

                            /* `#END` */
                            
                            psoc_NAK_AND_RECEIVE;   /* NACK address */

                            /* Place code to end of condition for NACK generation here */
                            /* `#START psoc_SW_ADDR_COMPARE_interruptEnd`  */

                            /* `#END` */
                        }
                        
                    #else /* (psoc_HW_ADRR_DECODE) */
                        
                        if(0u != (psoc_DATA_REG & psoc_READ_FLAG))
                        {
                            /* Place code to prepare read buffer here                  */
                            /* `#START psoc_HW_PREPARE_READ_BUF_interrupt` */

                            /* `#END` */

                            /* Prepare next opeation to read, get data and place in data register */
                            if(psoc_slRdBufIndex < psoc_slRdBufSize)
                            {
                                /* Load first data byte from array */
                                psoc_DATA_REG = psoc_slRdBufPtr[psoc_slRdBufIndex];
                                psoc_ACK_AND_TRANSMIT;
                                psoc_slRdBufIndex++;

                                psoc_slStatus |= psoc_SSTAT_RD_BUSY;
                            }
                            else    /* Overflow: provide 0xFF on the bus */
                            {
                                psoc_DATA_REG = psoc_OVERFLOW_RETURN;
                                psoc_ACK_AND_TRANSMIT;

                                psoc_slStatus  |= (psoc_SSTAT_RD_BUSY |
                                                               psoc_SSTAT_RD_ERR_OVFL);
                            }

                            psoc_state = psoc_SM_SL_RD_DATA;
                        }
                        else  /* Write transaction: receive 1st byte */
                        {
                            psoc_ACK_AND_RECEIVE;
                            psoc_state = psoc_SM_SL_WR_DATA;

                            psoc_slStatus |= psoc_SSTAT_WR_BUSY;
                            psoc_ENABLE_INT_ON_STOP;
                        }
                        
                    #endif /* (psoc_SW_ADRR_DECODE) */
                }
                /* Data states */
                /* Data master writes into slave */
                else if(psoc_state == psoc_SM_SL_WR_DATA)
                {
                    if(psoc_slWrBufIndex < psoc_slWrBufSize)
                    {
                        tmp8 = psoc_DATA_REG;
                        psoc_ACK_AND_RECEIVE;
                        psoc_slWrBufPtr[psoc_slWrBufIndex] = tmp8;
                        psoc_slWrBufIndex++;
                    }
                    else  /* of array: complete write, send NACK */
                    {
                        psoc_NAK_AND_RECEIVE;

                        psoc_slStatus |= psoc_SSTAT_WR_ERR_OVFL;
                    }
                }
                /* Data master reads from slave */
                else if(psoc_state == psoc_SM_SL_RD_DATA)
                {
                    if(psoc_CHECK_DATA_ACK(tmpCsr))
                    {
                        if(psoc_slRdBufIndex < psoc_slRdBufSize)
                        {
                             /* Get data from array */
                            psoc_DATA_REG = psoc_slRdBufPtr[psoc_slRdBufIndex];
                            psoc_TRANSMIT_DATA;
                            psoc_slRdBufIndex++;
                        }
                        else   /* Overflow: provide 0xFF on the bus */
                        {
                            psoc_DATA_REG = psoc_OVERFLOW_RETURN;
                            psoc_TRANSMIT_DATA;

                            psoc_slStatus |= psoc_SSTAT_RD_ERR_OVFL;
                        }
                    }
                    else  /* Last byte was NACKed: read complete */
                    {
                        /* Only NACK appears on the bus */
                        psoc_DATA_REG = psoc_OVERFLOW_RETURN;
                        psoc_NAK_AND_TRANSMIT;

                        psoc_slStatus &= ((uint8) ~psoc_SSTAT_RD_BUSY);
                        psoc_slStatus |= ((uint8)  psoc_SSTAT_RD_CMPLT);

                        psoc_state = psoc_SM_IDLE;
                    }
                }
                else
                {
                    #if(psoc_TIMEOUT_ENABLED)
                        /* Exit from interrupt to take a chance for timeout timer handle this case */
                        psoc_DisableInt();
                        psoc_ClearPendingInt();
                    #else
                        /* Block execution flow: unexpected condition */
                        CYASSERT(0u != 0u);
                    #endif /* (psoc_TIMEOUT_ENABLED) */
                }
            }
        #endif /* (psoc_MODE_SLAVE_ENABLED) */
    }
    else
    {
        /* The FSM skips master and slave processing: return to IDLE */
        psoc_state = psoc_SM_IDLE;
    }
}


#if((psoc_FF_IMPLEMENTED) && (psoc_WAKEUP_ENABLED))
    /*******************************************************************************
    * Function Name: psoc_WAKEUP_ISR
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
    CY_ISR(psoc_WAKEUP_ISR)
    {
        psoc_wakeupSource = 1u;  /* I2C was wakeup source */
        /* The SCL is stretched unitl the I2C_Wake() is called */
    }
#endif /* ((psoc_FF_IMPLEMENTED) && (psoc_WAKEUP_ENABLED))*/


/* [] END OF FILE */
