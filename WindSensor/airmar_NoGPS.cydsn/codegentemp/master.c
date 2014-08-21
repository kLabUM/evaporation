/*******************************************************************************
* File Name: master.c
* Version 2.40
*
* Description:
*  This file provides all API functionality of the SPI Master component.
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

#if(master_TX_SOFTWARE_BUF_ENABLED)
    volatile uint16 master_txBuffer[master_TX_BUFFER_SIZE] = {0u};
    volatile uint8 master_txBufferFull;
    volatile uint8 master_txBufferRead;
    volatile uint8 master_txBufferWrite;
#endif /* (master_TX_SOFTWARE_BUF_ENABLED) */

#if(master_RX_SOFTWARE_BUF_ENABLED)
    volatile uint16 master_rxBuffer[master_RX_BUFFER_SIZE] = {0u};
    volatile uint8 master_rxBufferFull;
    volatile uint8 master_rxBufferRead;
    volatile uint8 master_rxBufferWrite;
#endif /* (master_RX_SOFTWARE_BUF_ENABLED) */

uint8 master_initVar = 0u;

volatile uint8 master_swStatusTx;
volatile uint8 master_swStatusRx;


/*******************************************************************************
* Function Name: master_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default SPIM configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  When this function is called it initializes all of the necessary parameters
*  for execution. i.e. setting the initial interrupt mask, configuring the
*  interrupt service routine, configuring the bit-counter parameters and
*  clearing the FIFO and Status Register.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void master_Init(void) 
{
    /* Initialize the Bit counter */
    master_COUNTER_PERIOD_REG = master_BITCTR_INIT;

    /* Init TX ISR  */
    #if(0u != master_INTERNAL_TX_INT_ENABLED)
        CyIntDisable         (master_TX_ISR_NUMBER);
        CyIntSetPriority     (master_TX_ISR_NUMBER,  master_TX_ISR_PRIORITY);
        (void) CyIntSetVector(master_TX_ISR_NUMBER, &master_TX_ISR);
    #endif /* (0u != master_INTERNAL_TX_INT_ENABLED) */

    /* Init RX ISR  */
    #if(0u != master_INTERNAL_RX_INT_ENABLED)
        CyIntDisable         (master_RX_ISR_NUMBER);
        CyIntSetPriority     (master_RX_ISR_NUMBER,  master_RX_ISR_PRIORITY);
        (void) CyIntSetVector(master_RX_ISR_NUMBER, &master_RX_ISR);
    #endif /* (0u != master_INTERNAL_RX_INT_ENABLED) */

    /* Clear any stray data from the RX and TX FIFO */
    master_ClearFIFO();

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

    (void) master_ReadTxStatus(); /* Clear Tx status and swStatusTx */
    (void) master_ReadRxStatus(); /* Clear Rx status and swStatusRx */

    /* Configure TX and RX interrupt mask */
    master_TX_STATUS_MASK_REG = master_TX_INIT_INTERRUPTS_MASK;
    master_RX_STATUS_MASK_REG = master_RX_INIT_INTERRUPTS_MASK;
}


/*******************************************************************************
* Function Name: master_Enable
********************************************************************************
*
* Summary:
*  Enable SPIM component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void master_Enable(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    master_COUNTER_CONTROL_REG |= master_CNTR_ENABLE;
    master_TX_STATUS_ACTL_REG  |= master_INT_ENABLE;
    master_RX_STATUS_ACTL_REG  |= master_INT_ENABLE;
    CyExitCriticalSection(enableInterrupts);

    #if(0u != master_INTERNAL_CLOCK)
        master_IntClock_Enable();
    #endif /* (0u != master_INTERNAL_CLOCK) */

    master_EnableTxInt();
    master_EnableRxInt();
}


/*******************************************************************************
* Function Name: master_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the SPI Master component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  master_initVar - used to check initial configuration, modified on
*  first function call.
*
* Theory:
*  Enable the clock input to enable operation.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void master_Start(void) 
{
    if(0u == master_initVar)
    {
        master_Init();
        master_initVar = 1u;
    }

    master_Enable();
}


/*******************************************************************************
* Function Name: master_Stop
********************************************************************************
*
* Summary:
*  Disable the SPI Master component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the clock input to enable operation.
*
*******************************************************************************/
void master_Stop(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    master_TX_STATUS_ACTL_REG &= ((uint8) ~master_INT_ENABLE);
    master_RX_STATUS_ACTL_REG &= ((uint8) ~master_INT_ENABLE);
    CyExitCriticalSection(enableInterrupts);

    #if(0u != master_INTERNAL_CLOCK)
        master_IntClock_Disable();
    #endif /* (0u != master_INTERNAL_CLOCK) */

    master_DisableTxInt();
    master_DisableRxInt();
}


/*******************************************************************************
* Function Name: master_EnableTxInt
********************************************************************************
*
* Summary:
*  Enable internal Tx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal Tx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void master_EnableTxInt(void) 
{
    #if(0u != master_INTERNAL_TX_INT_ENABLED)
        CyIntEnable(master_TX_ISR_NUMBER);
    #endif /* (0u != master_INTERNAL_TX_INT_ENABLED) */
}


/*******************************************************************************
* Function Name: master_EnableRxInt
********************************************************************************
*
* Summary:
*  Enable internal Rx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal Rx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void master_EnableRxInt(void) 
{
    #if(0u != master_INTERNAL_RX_INT_ENABLED)
        CyIntEnable(master_RX_ISR_NUMBER);
    #endif /* (0u != master_INTERNAL_RX_INT_ENABLED) */
}


/*******************************************************************************
* Function Name: master_DisableTxInt
********************************************************************************
*
* Summary:
*  Disable internal Tx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal Tx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void master_DisableTxInt(void) 
{
    #if(0u != master_INTERNAL_TX_INT_ENABLED)
        CyIntDisable(master_TX_ISR_NUMBER);
    #endif /* (0u != master_INTERNAL_TX_INT_ENABLED) */
}


/*******************************************************************************
* Function Name: master_DisableRxInt
********************************************************************************
*
* Summary:
*  Disable internal Rx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal Rx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void master_DisableRxInt(void) 
{
    #if(0u != master_INTERNAL_RX_INT_ENABLED)
        CyIntDisable(master_RX_ISR_NUMBER);
    #endif /* (0u != master_INTERNAL_RX_INT_ENABLED) */
}


/*******************************************************************************
* Function Name: master_SetTxInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void master_SetTxInterruptMode(uint8 intSrc) 
{
    master_TX_STATUS_MASK_REG = intSrc;
}


/*******************************************************************************
* Function Name: master_SetRxInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void master_SetRxInterruptMode(uint8 intSrc) 
{
    master_RX_STATUS_MASK_REG  = intSrc;
}


/*******************************************************************************
* Function Name: master_ReadTxStatus
********************************************************************************
*
* Summary:
*  Read the Tx status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the Tx status register.
*
* Global variables:
*  master_swStatusTx - used to store in software status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the Tx status register for error
*  detection and flow control.
*
* Side Effects:
*  Clear Tx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 master_ReadTxStatus(void) 
{
    uint8 tmpStatus;

    #if(master_TX_SOFTWARE_BUF_ENABLED)
        /* Disable TX interrupt to protect global veriables */
        master_DisableTxInt();

        tmpStatus = master_GET_STATUS_TX(master_swStatusTx);
        master_swStatusTx = 0u;

        master_EnableTxInt();

    #else

        tmpStatus = master_TX_STATUS_REG;

    #endif /* (master_TX_SOFTWARE_BUF_ENABLED) */

    return(tmpStatus);
}


/*******************************************************************************
* Function Name: master_ReadRxStatus
********************************************************************************
*
* Summary:
*  Read the Rx status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the Rx status register.
*
* Global variables:
*  master_swStatusRx - used to store in software Rx status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the Rx status register for error
*  detection and flow control.
*
* Side Effects:
*  Clear Rx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 master_ReadRxStatus(void) 
{
    uint8 tmpStatus;

    #if(master_RX_SOFTWARE_BUF_ENABLED)
        /* Disable RX interrupt to protect global veriables */
        master_DisableRxInt();

        tmpStatus = master_GET_STATUS_RX(master_swStatusRx);
        master_swStatusRx = 0u;

        master_EnableRxInt();

    #else

        tmpStatus = master_RX_STATUS_REG;

    #endif /* (master_RX_SOFTWARE_BUF_ENABLED) */

    return(tmpStatus);
}


/*******************************************************************************
* Function Name: master_WriteTxData
********************************************************************************
*
* Summary:
*  Write a byte of data to be sent across the SPI.
*
* Parameters:
*  txDataByte: The data value to send across the SPI.
*
* Return:
*  None.
*
* Global variables:
*  master_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer, modified every function
*  call if TX Software Buffer is used.
*  master_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer.
*  master_txBuffer[master_TX_BUFFER_SIZE] - used to store
*  data to sending, modified every function call if TX Software Buffer is used.
*
* Theory:
*  Allows the user to transmit any byte of data in a single transfer.
*
* Side Effects:
*  If this function is called again before the previous byte is finished then
*  the next byte will be appended to the transfer with no time between
*  the byte transfers. Clear Tx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void master_WriteTxData(uint16 txData) 
{
    #if(master_TX_SOFTWARE_BUF_ENABLED)

        uint8 tempStatus;
        uint8 tmpTxBufferRead;

        /* Block if TX buffer is FULL: don't overwrite */
        do
        {
            tmpTxBufferRead = master_txBufferRead;
            if(0u == tmpTxBufferRead)
            {
                tmpTxBufferRead = (master_TX_BUFFER_SIZE - 1u);
            }
            else
            {
                tmpTxBufferRead--;
            }

        }while(tmpTxBufferRead == master_txBufferWrite);

        /* Disable TX interrupt to protect global veriables */
        master_DisableTxInt();

        tempStatus = master_GET_STATUS_TX(master_swStatusTx);
        master_swStatusTx = tempStatus;


        if((master_txBufferRead == master_txBufferWrite) &&
           (0u != (master_swStatusTx & master_STS_TX_FIFO_NOT_FULL)))
        {
            /* Add directly to the TX FIFO */
            CY_SET_REG16(master_TXDATA_PTR, txData);
        }
        else
        {
            /* Add to the TX software buffer */
            master_txBufferWrite++;
            if(master_txBufferWrite >= master_TX_BUFFER_SIZE)
            {
                master_txBufferWrite = 0u;
            }

            if(master_txBufferWrite == master_txBufferRead)
            {
                master_txBufferRead++;
                if(master_txBufferRead >= master_TX_BUFFER_SIZE)
                {
                    master_txBufferRead = 0u;
                }
                master_txBufferFull = 1u;
            }

            master_txBuffer[master_txBufferWrite] = txData;

            master_TX_STATUS_MASK_REG |= master_STS_TX_FIFO_NOT_FULL;
        }

        master_EnableTxInt();

    #else

        while(0u == (master_TX_STATUS_REG & master_STS_TX_FIFO_NOT_FULL))
        {
            ; /* Wait for room in FIFO */
        }

        /* Put byte in TX FIFO */
        CY_SET_REG16(master_TXDATA_PTR, txData);

    #endif /* (master_TX_SOFTWARE_BUF_ENABLED) */
}


/*******************************************************************************
* Function Name: master_ReadRxData
********************************************************************************
*
* Summary:
*  Read the next byte of data received across the SPI.
*
* Parameters:
*  None.
*
* Return:
*  The next byte of data read from the FIFO.
*
* Global variables:
*  master_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer.
*  master_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified every function
*  call if RX Software Buffer is used.
*  master_rxBuffer[master_RX_BUFFER_SIZE] - used to store
*  received data.
*
* Theory:
*  Allows the user to read a byte of data received.
*
* Side Effects:
*  Will return invalid data if the FIFO is empty. The user should Call
*  GetRxBufferSize() and if it returns a non-zero value then it is safe to call
*  ReadByte() function.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint16 master_ReadRxData(void) 
{
    uint16 rxData;

    #if(master_RX_SOFTWARE_BUF_ENABLED)

        /* Disable RX interrupt to protect global veriables */
        master_DisableRxInt();

        if(master_rxBufferRead != master_rxBufferWrite)
        {
            if(0u == master_rxBufferFull)
            {
                master_rxBufferRead++;
                if(master_rxBufferRead >= master_RX_BUFFER_SIZE)
                {
                    master_rxBufferRead = 0u;
                }
            }
            else
            {
                master_rxBufferFull = 0u;
            }
        }

        rxData = master_rxBuffer[master_rxBufferRead];

        master_EnableRxInt();

    #else

        rxData = CY_GET_REG16(master_RXDATA_PTR);

    #endif /* (master_RX_SOFTWARE_BUF_ENABLED) */

    return(rxData);
}


/*******************************************************************************
* Function Name: master_GetRxBufferSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes/words of data currently held in the RX buffer.
*  If RX Software Buffer not used then function return 0 if FIFO empty or 1 if
*  FIFO not empty. In another case function return size of RX Software Buffer.
*
* Parameters:
*  None.
*
* Return:
*  Integer count of the number of bytes/words in the RX buffer.
*
* Global variables:
*  master_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer.
*  master_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
uint8 master_GetRxBufferSize(void) 
{
    uint8 size;

    #if(master_RX_SOFTWARE_BUF_ENABLED)

        /* Disable RX interrupt to protect global veriables */
        master_DisableRxInt();

        if(master_rxBufferRead == master_rxBufferWrite)
        {
            size = 0u;
        }
        else if(master_rxBufferRead < master_rxBufferWrite)
        {
            size = (master_rxBufferWrite - master_rxBufferRead);
        }
        else
        {
            size = (master_RX_BUFFER_SIZE - master_rxBufferRead) + master_rxBufferWrite;
        }

        master_EnableRxInt();

    #else

        /* We can only know if there is data in the RX FIFO */
        size = (0u != (master_RX_STATUS_REG & master_STS_RX_FIFO_NOT_EMPTY)) ? 1u : 0u;

    #endif /* (master_TX_SOFTWARE_BUF_ENABLED) */

    return(size);
}


/*******************************************************************************
* Function Name: master_GetTxBufferSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes/words of data currently held in the TX buffer.
*  If TX Software Buffer not used then function return 0 - if FIFO empty, 1 - if
*  FIFO not full, 4 - if FIFO full. In another case function return size of TX
*  Software Buffer.
*
* Parameters:
*  None.
*
* Return:
*  Integer count of the number of bytes/words in the TX buffer.
*
* Global variables:
*  master_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  master_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
uint8  master_GetTxBufferSize(void) 
{
    uint8 size;

    #if(master_TX_SOFTWARE_BUF_ENABLED)
        /* Disable TX interrupt to protect global veriables */
        master_DisableTxInt();

        if(master_txBufferRead == master_txBufferWrite)
        {
            size = 0u;
        }
        else if(master_txBufferRead < master_txBufferWrite)
        {
            size = (master_txBufferWrite - master_txBufferRead);
        }
        else
        {
            size = (master_TX_BUFFER_SIZE - master_txBufferRead) + master_txBufferWrite;
        }

        master_EnableTxInt();

    #else

        size = master_TX_STATUS_REG;

        if(0u != (size & master_STS_TX_FIFO_EMPTY))
        {
            size = 0u;
        }
        else if(0u != (size & master_STS_TX_FIFO_NOT_FULL))
        {
            size = 1u;
        }
        else
        {
            size = master_FIFO_SIZE;
        }

    #endif /* (master_TX_SOFTWARE_BUF_ENABLED) */

    return(size);
}


/*******************************************************************************
* Function Name: master_ClearRxBuffer
********************************************************************************
*
* Summary:
*  Clear the RX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  master_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer, modified every function
*  call - resets to zero.
*  master_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified every function call -
*  resets to zero.
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to
*  read and writing will resume at address 0 overwriting any data that may have
*  remained in the RAM.
*
* Side Effects:
*  Any received data not read from the RAM buffer will be lost when overwritten.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void master_ClearRxBuffer(void) 
{
    /* Clear Hardware RX FIFO */
    while(0u !=(master_RX_STATUS_REG & master_STS_RX_FIFO_NOT_EMPTY))
    {
        (void) CY_GET_REG16(master_RXDATA_PTR);
    }

    #if(master_RX_SOFTWARE_BUF_ENABLED)
        /* Disable RX interrupt to protect global veriables */
        master_DisableRxInt();

        master_rxBufferFull  = 0u;
        master_rxBufferRead  = 0u;
        master_rxBufferWrite = 0u;

        master_EnableRxInt();
    #endif /* (master_RX_SOFTWARE_BUF_ENABLED) */
}


/*******************************************************************************
* Function Name: master_ClearTxBuffer
********************************************************************************
*
* Summary:
*  Clear the TX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  master_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer, modified every function
*  call - resets to zero.
*  master_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified every function call -
*  resets to zero.
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to
*  read and writing will resume at address 0 overwriting any data that may have
*  remained in the RAM.
*
* Side Effects:
*  Any data not yet transmitted from the RAM buffer will be lost when
*  overwritten.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void master_ClearTxBuffer(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    /* Clear TX FIFO */
    master_AUX_CONTROL_DP0_REG |= ((uint8)  master_TX_FIFO_CLR);
    master_AUX_CONTROL_DP0_REG &= ((uint8) ~master_TX_FIFO_CLR);

    #if(master_USE_SECOND_DATAPATH)
        /* Clear TX FIFO for 2nd Datapath */
        master_AUX_CONTROL_DP1_REG |= ((uint8)  master_TX_FIFO_CLR);
        master_AUX_CONTROL_DP1_REG &= ((uint8) ~master_TX_FIFO_CLR);
    #endif /* (master_USE_SECOND_DATAPATH) */
    CyExitCriticalSection(enableInterrupts);

    #if(master_TX_SOFTWARE_BUF_ENABLED)
        /* Disable TX interrupt to protect global veriables */
        master_DisableTxInt();

        master_txBufferFull  = 0u;
        master_txBufferRead  = 0u;
        master_txBufferWrite = 0u;

        /* Buffer is EMPTY: disable TX FIFO NOT FULL interrupt */
        master_TX_STATUS_MASK_REG &= ((uint8) ~master_STS_TX_FIFO_NOT_FULL);

        master_EnableTxInt();
    #endif /* (master_TX_SOFTWARE_BUF_ENABLED) */
}


#if(0u != master_BIDIRECTIONAL_MODE)
    /*******************************************************************************
    * Function Name: master_TxEnable
    ********************************************************************************
    *
    * Summary:
    *  If the SPI master is configured to use a single bi-directional pin then this
    *  will set the bi-directional pin to transmit.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void master_TxEnable(void) 
    {
        master_CONTROL_REG |= master_CTRL_TX_SIGNAL_EN;
    }


    /*******************************************************************************
    * Function Name: master_TxDisable
    ********************************************************************************
    *
    * Summary:
    *  If the SPI master is configured to use a single bi-directional pin then this
    *  will set the bi-directional pin to receive.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void master_TxDisable(void) 
    {
        master_CONTROL_REG &= ((uint8) ~master_CTRL_TX_SIGNAL_EN);
    }

#endif /* (0u != master_BIDIRECTIONAL_MODE) */


/*******************************************************************************
* Function Name: master_PutArray
********************************************************************************
*
* Summary:
*  Write available data from ROM/RAM to the TX buffer while space is available
*  in the TX buffer. Keep trying until all data is passed to the TX buffer.
*
* Parameters:
*  *buffer: Pointer to the location in RAM containing the data to send
*  byteCount: The number of bytes to move to the transmit buffer.
*
* Return:
*  None.
*
* Side Effects:
*  Will stay in this routine until all data has been sent.  May get locked in
*  this loop if data is not being initiated by the master if there is not
*  enough room in the TX FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void master_PutArray(const uint16 buffer[], uint8 byteCount)
                                                                          
{
    uint8 bufIndex;

    bufIndex = 0u;

    while(byteCount > 0u)
    {
        master_WriteTxData(buffer[bufIndex]);
        bufIndex++;
        byteCount--;
    }
}


/*******************************************************************************
* Function Name: master_ClearFIFO
********************************************************************************
*
* Summary:
*  Clear the RX and TX FIFO's of all data for a fresh start.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
void master_ClearFIFO(void) 
{
    uint8 enableInterrupts;

    /* Clear Hardware RX FIFO */
    while(0u !=(master_RX_STATUS_REG & master_STS_RX_FIFO_NOT_EMPTY))
    {
        (void) CY_GET_REG16(master_RXDATA_PTR);
    }

    enableInterrupts = CyEnterCriticalSection();
    /* Clear TX FIFO */
    master_AUX_CONTROL_DP0_REG |= ((uint8)  master_TX_FIFO_CLR);
    master_AUX_CONTROL_DP0_REG &= ((uint8) ~master_TX_FIFO_CLR);

    #if(master_USE_SECOND_DATAPATH)
        /* Clear TX FIFO for 2nd Datapath */
        master_AUX_CONTROL_DP1_REG |= ((uint8)  master_TX_FIFO_CLR);
        master_AUX_CONTROL_DP1_REG &= ((uint8) ~master_TX_FIFO_CLR);
    #endif /* (master_USE_SECOND_DATAPATH) */
    CyExitCriticalSection(enableInterrupts);
}


/* Following functions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects.
*/


/*******************************************************************************
* Function Name: master_EnableInt
********************************************************************************
*
* Summary:
*  Enable internal interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void master_EnableInt(void) 
{
    master_EnableRxInt();
    master_EnableTxInt();
}


/*******************************************************************************
* Function Name: master_DisableInt
********************************************************************************
*
* Summary:
*  Disable internal interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void master_DisableInt(void) 
{
    master_DisableTxInt();
    master_DisableRxInt();
}


/*******************************************************************************
* Function Name: master_SetInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void master_SetInterruptMode(uint8 intSrc) 
{
    master_TX_STATUS_MASK_REG  = (intSrc & ((uint8) ~master_STS_SPI_IDLE));
    master_RX_STATUS_MASK_REG  =  intSrc;
}


/*******************************************************************************
* Function Name: master_ReadStatus
********************************************************************************
*
* Summary:
*  Read the status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the status register.
*
* Global variables:
*  master_swStatus - used to store in software status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the status register for error detection
*  and flow control.
*
* Side Effects:
*  Clear status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 master_ReadStatus(void) 
{
    uint8 tmpStatus;

    #if(master_TX_SOFTWARE_BUF_ENABLED || master_RX_SOFTWARE_BUF_ENABLED)

        master_DisableInt();

        tmpStatus  = master_GET_STATUS_RX(master_swStatusRx);
        tmpStatus |= master_GET_STATUS_TX(master_swStatusTx);
        tmpStatus &= ((uint8) ~master_STS_SPI_IDLE);

        master_swStatusTx = 0u;
        master_swStatusRx = 0u;

        master_EnableInt();

    #else

        tmpStatus  = master_RX_STATUS_REG;
        tmpStatus |= master_TX_STATUS_REG;
        tmpStatus &= ((uint8) ~master_STS_SPI_IDLE);

    #endif /* (master_TX_SOFTWARE_BUF_ENABLED || master_RX_SOFTWARE_BUF_ENABLED) */

    return(tmpStatus);
}


/* [] END OF FILE */
