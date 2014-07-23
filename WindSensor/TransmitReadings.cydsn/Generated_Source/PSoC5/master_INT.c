/*******************************************************************************
* File Name: master_INT.c
* Version 2.40
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Master
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "master_PVT.h"

/* User code required at start of ISR */
/* `#START master_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: master_TX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  master_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  master_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  master_txBuffer[master_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(master_TX_ISR)
{
    #if(master_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (master_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at start of ISR */
    /* `#START master_TX_ISR_START` */

    /* `#END` */

    #if(master_TX_SOFTWARE_BUF_ENABLED)
        /* Check if TX data buffer is not empty and there is space in TX FIFO */
        while(master_txBufferRead != master_txBufferWrite)
        {
            tmpStatus = master_GET_STATUS_TX(master_swStatusTx);
            master_swStatusTx = tmpStatus;

            if(0u != (master_swStatusTx & master_STS_TX_FIFO_NOT_FULL))
            {
                if(0u == master_txBufferFull)
                {
                   master_txBufferRead++;

                    if(master_txBufferRead >= master_TX_BUFFER_SIZE)
                    {
                        master_txBufferRead = 0u;
                    }
                }
                else
                {
                    master_txBufferFull = 0u;
                }

                /* Move data from the Buffer to the FIFO */
                CY_SET_REG16(master_TXDATA_PTR,
                    master_txBuffer[master_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        if(master_txBufferRead == master_txBufferWrite)
        {
            /* TX Buffer is EMPTY: disable interrupt on TX NOT FULL */
            master_TX_STATUS_MASK_REG &= ((uint8) ~master_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* (master_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START master_TX_ISR_END` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: master_RX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  master_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  master_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  master_rxBuffer[master_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(master_RX_ISR)
{
    #if(master_RX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint16 rxData;
    #endif /* (master_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at start of ISR */
    /* `#START master_RX_ISR_START` */

    /* `#END` */

    #if(master_RX_SOFTWARE_BUF_ENABLED)

        tmpStatus = master_GET_STATUS_RX(master_swStatusRx);
        master_swStatusRx = tmpStatus;

        /* Check if RX data FIFO has some data to be moved into the RX Buffer */
        while(0u != (master_swStatusRx & master_STS_RX_FIFO_NOT_EMPTY))
        {
            rxData = CY_GET_REG16(master_RXDATA_PTR);

            /* Set next pointer. */
            master_rxBufferWrite++;
            if(master_rxBufferWrite >= master_RX_BUFFER_SIZE)
            {
                master_rxBufferWrite = 0u;
            }

            if(master_rxBufferWrite == master_rxBufferRead)
            {
                master_rxBufferRead++;
                if(master_rxBufferRead >= master_RX_BUFFER_SIZE)
                {
                    master_rxBufferRead = 0u;
                }

                master_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            master_rxBuffer[master_rxBufferWrite] = rxData;

            tmpStatus = master_GET_STATUS_RX(master_swStatusRx);
            master_swStatusRx = tmpStatus;
        }

    #endif /* (master_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START master_RX_ISR_END` */

    /* `#END` */
}

/* [] END OF FILE */
