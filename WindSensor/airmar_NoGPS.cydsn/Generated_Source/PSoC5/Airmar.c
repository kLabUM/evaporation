/*******************************************************************************
* File Name: Airmar.c
* Version 2.30
*
* Description:
*  This file provides all API functionality of the UART component
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
#include "CyLib.h"
#if(Airmar_INTERNAL_CLOCK_USED)
    #include "Airmar_IntClock.h"
#endif /* End Airmar_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 Airmar_initVar = 0u;
#if( Airmar_TX_ENABLED && (Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH))
    volatile uint8 Airmar_txBuffer[Airmar_TXBUFFERSIZE];
    volatile uint8 Airmar_txBufferRead = 0u;
    uint8 Airmar_txBufferWrite = 0u;
#endif /* End Airmar_TX_ENABLED */
#if( ( Airmar_RX_ENABLED || Airmar_HD_ENABLED ) && \
     (Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH) )
    volatile uint8 Airmar_rxBuffer[Airmar_RXBUFFERSIZE];
    volatile uint8 Airmar_rxBufferRead = 0u;
    volatile uint8 Airmar_rxBufferWrite = 0u;
    volatile uint8 Airmar_rxBufferLoopDetect = 0u;
    volatile uint8 Airmar_rxBufferOverflow = 0u;
    #if (Airmar_RXHW_ADDRESS_ENABLED)
        volatile uint8 Airmar_rxAddressMode = Airmar_RXADDRESSMODE;
        volatile uint8 Airmar_rxAddressDetected = 0u;
    #endif /* End EnableHWAddress */
#endif /* End Airmar_RX_ENABLED */


/*******************************************************************************
* Function Name: Airmar_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the UART component.
*  Enable the clock input to enable operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The Airmar_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time UART_Start() is called. This allows for
*  component initialization without re-initialization in all subsequent calls
*  to the Airmar_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Airmar_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(Airmar_initVar == 0u)
    {
        Airmar_Init();
        Airmar_initVar = 1u;
    }
    Airmar_Enable();
}


/*******************************************************************************
* Function Name: Airmar_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  Airmar_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Airmar_Init(void) 
{
    #if(Airmar_RX_ENABLED || Airmar_HD_ENABLED)

        #if(Airmar_RX_INTERRUPT_ENABLED && (Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH))
            /* Set the RX Interrupt. */
            (void)CyIntSetVector(Airmar_RX_VECT_NUM, &Airmar_RXISR);
            CyIntSetPriority(Airmar_RX_VECT_NUM, Airmar_RX_PRIOR_NUM);
        #endif /* End Airmar_RX_INTERRUPT_ENABLED */

        #if (Airmar_RXHW_ADDRESS_ENABLED)
            Airmar_SetRxAddressMode(Airmar_RXAddressMode);
            Airmar_SetRxAddress1(Airmar_RXHWADDRESS1);
            Airmar_SetRxAddress2(Airmar_RXHWADDRESS2);
        #endif /* End Airmar_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        Airmar_RXBITCTR_PERIOD_REG = Airmar_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        Airmar_RXSTATUS_MASK_REG  = Airmar_INIT_RX_INTERRUPTS_MASK;
    #endif /* End Airmar_RX_ENABLED || Airmar_HD_ENABLED*/

    #if(Airmar_TX_ENABLED)
        #if(Airmar_TX_INTERRUPT_ENABLED && (Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH))
            /* Set the TX Interrupt. */
            (void)CyIntSetVector(Airmar_TX_VECT_NUM, &Airmar_TXISR);
            CyIntSetPriority(Airmar_TX_VECT_NUM, Airmar_TX_PRIOR_NUM);
        #endif /* End Airmar_TX_INTERRUPT_ENABLED */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if(Airmar_TXCLKGEN_DP)
            Airmar_TXBITCLKGEN_CTR_REG = Airmar_BIT_CENTER;
            Airmar_TXBITCLKTX_COMPLETE_REG = (Airmar_NUMBER_OF_DATA_BITS +
                        Airmar_NUMBER_OF_START_BIT) * Airmar_OVER_SAMPLE_COUNT;
        #else
            Airmar_TXBITCTR_PERIOD_REG = ((Airmar_NUMBER_OF_DATA_BITS +
                        Airmar_NUMBER_OF_START_BIT) * Airmar_OVER_SAMPLE_8) - 1u;
        #endif /* End Airmar_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if(Airmar_TX_INTERRUPT_ENABLED && (Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH))
            Airmar_TXSTATUS_MASK_REG = Airmar_TX_STS_FIFO_EMPTY;
        #else
            Airmar_TXSTATUS_MASK_REG = Airmar_INIT_TX_INTERRUPTS_MASK;
        #endif /*End Airmar_TX_INTERRUPT_ENABLED*/

    #endif /* End Airmar_TX_ENABLED */

    #if(Airmar_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        Airmar_WriteControlRegister( \
            (Airmar_ReadControlRegister() & (uint8)~Airmar_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(Airmar_PARITY_TYPE << Airmar_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End Airmar_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: Airmar_Enable
********************************************************************************
*
* Summary:
*  Enables the UART block operation
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Airmar_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void Airmar_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if(Airmar_RX_ENABLED || Airmar_HD_ENABLED)
        /*RX Counter (Count7) Enable */
        Airmar_RXBITCTR_CONTROL_REG |= Airmar_CNTR_ENABLE;
        /* Enable the RX Interrupt. */
        Airmar_RXSTATUS_ACTL_REG  |= Airmar_INT_ENABLE;
        #if(Airmar_RX_INTERRUPT_ENABLED && (Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH))
            CyIntEnable(Airmar_RX_VECT_NUM);
            #if (Airmar_RXHW_ADDRESS_ENABLED)
                Airmar_rxAddressDetected = 0u;
            #endif /* End Airmar_RXHW_ADDRESS_ENABLED */
        #endif /* End Airmar_RX_INTERRUPT_ENABLED */
    #endif /* End Airmar_RX_ENABLED || Airmar_HD_ENABLED*/

    #if(Airmar_TX_ENABLED)
        /*TX Counter (DP/Count7) Enable */
        #if(!Airmar_TXCLKGEN_DP)
            Airmar_TXBITCTR_CONTROL_REG |= Airmar_CNTR_ENABLE;
        #endif /* End Airmar_TXCLKGEN_DP */
        /* Enable the TX Interrupt. */
        Airmar_TXSTATUS_ACTL_REG |= Airmar_INT_ENABLE;
        #if(Airmar_TX_INTERRUPT_ENABLED && (Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH))
            CyIntEnable(Airmar_TX_VECT_NUM);
        #endif /* End Airmar_TX_INTERRUPT_ENABLED*/
     #endif /* End Airmar_TX_ENABLED */

    #if(Airmar_INTERNAL_CLOCK_USED)
        /* Enable the clock. */
        Airmar_IntClock_Start();
    #endif /* End Airmar_INTERNAL_CLOCK_USED */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Airmar_Stop
********************************************************************************
*
* Summary:
*  Disable the UART component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Airmar_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if(Airmar_RX_ENABLED || Airmar_HD_ENABLED)
        Airmar_RXBITCTR_CONTROL_REG &= (uint8)~Airmar_CNTR_ENABLE;
    #endif /* End Airmar_RX_ENABLED */

    #if(Airmar_TX_ENABLED)
        #if(!Airmar_TXCLKGEN_DP)
            Airmar_TXBITCTR_CONTROL_REG &= (uint8)~Airmar_CNTR_ENABLE;
        #endif /* End Airmar_TXCLKGEN_DP */
    #endif /* Airmar_TX_ENABLED */

    #if(Airmar_INTERNAL_CLOCK_USED)
        /* Disable the clock. */
        Airmar_IntClock_Stop();
    #endif /* End Airmar_INTERNAL_CLOCK_USED */

    /* Disable internal interrupt component */
    #if(Airmar_RX_ENABLED || Airmar_HD_ENABLED)
        Airmar_RXSTATUS_ACTL_REG  &= (uint8)~Airmar_INT_ENABLE;
        #if(Airmar_RX_INTERRUPT_ENABLED && (Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH))
            Airmar_DisableRxInt();
        #endif /* End Airmar_RX_INTERRUPT_ENABLED */
    #endif /* End Airmar_RX_ENABLED */

    #if(Airmar_TX_ENABLED)
        Airmar_TXSTATUS_ACTL_REG &= (uint8)~Airmar_INT_ENABLE;
        #if(Airmar_TX_INTERRUPT_ENABLED && (Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH))
            Airmar_DisableTxInt();
        #endif /* End Airmar_TX_INTERRUPT_ENABLED */
    #endif /* End Airmar_TX_ENABLED */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Airmar_ReadControlRegister
********************************************************************************
*
* Summary:
*  Read the current state of the control register
*
* Parameters:
*  None.
*
* Return:
*  Current state of the control register.
*
*******************************************************************************/
uint8 Airmar_ReadControlRegister(void) 
{
    #if( Airmar_CONTROL_REG_REMOVED )
        return(0u);
    #else
        return(Airmar_CONTROL_REG);
    #endif /* End Airmar_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: Airmar_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  Airmar_WriteControlRegister(uint8 control) 
{
    #if( Airmar_CONTROL_REG_REMOVED )
        if(control != 0u) { }      /* release compiler warning */
    #else
       Airmar_CONTROL_REG = control;
    #endif /* End Airmar_CONTROL_REG_REMOVED */
}


#if(Airmar_RX_ENABLED || Airmar_HD_ENABLED)

    #if(Airmar_RX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: Airmar_EnableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void Airmar_EnableRxInt(void) 
        {
            CyIntEnable(Airmar_RX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: Airmar_DisableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void Airmar_DisableRxInt(void) 
        {
            CyIntDisable(Airmar_RX_VECT_NUM);
        }

    #endif /* Airmar_RX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: Airmar_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  IntSrc:  An or'd combination of the desired status bit masks (defined in
    *           the header file)
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void Airmar_SetRxInterruptMode(uint8 intSrc) 
    {
        Airmar_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: Airmar_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns data in RX Data register without checking status register to
    *  determine if data is valid
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  Airmar_rxBuffer - RAM buffer pointer for save received data.
    *  Airmar_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  Airmar_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  Airmar_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 Airmar_ReadRxData(void) 
    {
        uint8 rxData;

        #if(Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH)
            uint8 loc_rxBufferRead;
            uint8 loc_rxBufferWrite;
            /* Protect variables that could change on interrupt. */
            /* Disable Rx interrupt. */
            #if(Airmar_RX_INTERRUPT_ENABLED)
                Airmar_DisableRxInt();
            #endif /* Airmar_RX_INTERRUPT_ENABLED */
            loc_rxBufferRead = Airmar_rxBufferRead;
            loc_rxBufferWrite = Airmar_rxBufferWrite;

            if( (Airmar_rxBufferLoopDetect != 0u) || (loc_rxBufferRead != loc_rxBufferWrite) )
            {
                rxData = Airmar_rxBuffer[loc_rxBufferRead];
                loc_rxBufferRead++;

                if(loc_rxBufferRead >= Airmar_RXBUFFERSIZE)
                {
                    loc_rxBufferRead = 0u;
                }
                /* Update the real pointer */
                Airmar_rxBufferRead = loc_rxBufferRead;

                if(Airmar_rxBufferLoopDetect != 0u )
                {
                    Airmar_rxBufferLoopDetect = 0u;
                    #if( (Airmar_RX_INTERRUPT_ENABLED) && (Airmar_FLOW_CONTROL != 0u) && \
                         (Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( Airmar_HD_ENABLED )
                            if((Airmar_CONTROL_REG & Airmar_CTRL_HD_SEND) == 0u)
                            {   /* In Half duplex mode return RX mask only in RX
                                *  configuration set, otherwise
                                *  mask will be returned in LoadRxConfig() API.
                                */
                                Airmar_RXSTATUS_MASK_REG  |= Airmar_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            Airmar_RXSTATUS_MASK_REG  |= Airmar_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end Airmar_HD_ENABLED */
                    #endif /* Airmar_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }
            }
            else
            {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
                rxData = Airmar_RXDATA_REG;
            }

            /* Enable Rx interrupt. */
            #if(Airmar_RX_INTERRUPT_ENABLED)
                Airmar_EnableRxInt();
            #endif /* End Airmar_RX_INTERRUPT_ENABLED */

        #else /* Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH */

            /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
            rxData = Airmar_RXDATA_REG;

        #endif /* Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: Airmar_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the current state of the status register
    *  And detect software buffer overflow.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Global Variables:
    *  Airmar_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn?t free space in
    *   Airmar_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   Airmar_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 Airmar_ReadRxStatus(void) 
    {
        uint8 status;

        status = Airmar_RXSTATUS_REG & Airmar_RX_HW_MASK;

        #if(Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH)
            if( Airmar_rxBufferOverflow != 0u )
            {
                status |= Airmar_RX_STS_SOFT_BUFF_OVER;
                Airmar_rxBufferOverflow = 0u;
            }
        #endif /* Airmar_RXBUFFERSIZE */

        return(status);
    }


    /*******************************************************************************
    * Function Name: Airmar_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, if data is not available or an error
    *  condition exists, zero is returned; otherwise, character is read and
    *  returned.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  Airmar_rxBuffer - RAM buffer pointer for save received data.
    *  Airmar_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  Airmar_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  Airmar_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 Airmar_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

        #if(Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH)
            uint8 loc_rxBufferRead;
            uint8 loc_rxBufferWrite;
            /* Protect variables that could change on interrupt. */
            /* Disable Rx interrupt. */
            #if(Airmar_RX_INTERRUPT_ENABLED)
                Airmar_DisableRxInt();
            #endif /* Airmar_RX_INTERRUPT_ENABLED */
            loc_rxBufferRead = Airmar_rxBufferRead;
            loc_rxBufferWrite = Airmar_rxBufferWrite;

            if( (Airmar_rxBufferLoopDetect != 0u) || (loc_rxBufferRead != loc_rxBufferWrite) )
            {
                rxData = Airmar_rxBuffer[loc_rxBufferRead];
                loc_rxBufferRead++;
                if(loc_rxBufferRead >= Airmar_RXBUFFERSIZE)
                {
                    loc_rxBufferRead = 0u;
                }
                /* Update the real pointer */
                Airmar_rxBufferRead = loc_rxBufferRead;

                if(Airmar_rxBufferLoopDetect > 0u )
                {
                    Airmar_rxBufferLoopDetect = 0u;
                    #if( (Airmar_RX_INTERRUPT_ENABLED) && (Airmar_FLOW_CONTROL != 0u) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( Airmar_HD_ENABLED )
                            if((Airmar_CONTROL_REG & Airmar_CTRL_HD_SEND) == 0u)
                            {   /* In Half duplex mode return RX mask only if
                                *  RX configuration set, otherwise
                                *  mask will be returned in LoadRxConfig() API.
                                */
                                Airmar_RXSTATUS_MASK_REG  |= Airmar_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            Airmar_RXSTATUS_MASK_REG  |= Airmar_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end Airmar_HD_ENABLED */
                    #endif /* Airmar_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }

            }
            else
            {   rxStatus = Airmar_RXSTATUS_REG;
                if((rxStatus & Airmar_RX_STS_FIFO_NOTEMPTY) != 0u)
                {   /* Read received data from FIFO*/
                    rxData = Airmar_RXDATA_REG;
                    /*Check status on error*/
                    if((rxStatus & (Airmar_RX_STS_BREAK | Airmar_RX_STS_PAR_ERROR |
                                   Airmar_RX_STS_STOP_ERROR | Airmar_RX_STS_OVERRUN)) != 0u)
                    {
                        rxData = 0u;
                    }
                }
            }

            /* Enable Rx interrupt. */
            #if(Airmar_RX_INTERRUPT_ENABLED)
                Airmar_EnableRxInt();
            #endif /* Airmar_RX_INTERRUPT_ENABLED */

        #else /* Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH */

            rxStatus =Airmar_RXSTATUS_REG;
            if((rxStatus & Airmar_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO*/
                rxData = Airmar_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (Airmar_RX_STS_BREAK | Airmar_RX_STS_PAR_ERROR |
                               Airmar_RX_STS_STOP_ERROR | Airmar_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        #endif /* Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: Airmar_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Grab the next available byte of data from the recieve FIFO
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains Status Register and LSB contains UART RX data
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 Airmar_GetByte(void) 
    {
        return ( ((uint16)Airmar_ReadRxStatus() << 8u) | Airmar_ReadRxData() );
    }


    /*******************************************************************************
    * Function Name: Airmar_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of bytes left in the RX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Integer count of the number of bytes left
    *  in the RX buffer
    *
    * Global Variables:
    *  Airmar_rxBufferWrite - used to calculate left bytes.
    *  Airmar_rxBufferRead - used to calculate left bytes.
    *  Airmar_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 Airmar_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

        #if(Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(Airmar_RX_INTERRUPT_ENABLED)
                Airmar_DisableRxInt();
            #endif /* Airmar_RX_INTERRUPT_ENABLED */

            if(Airmar_rxBufferRead == Airmar_rxBufferWrite)
            {
                if(Airmar_rxBufferLoopDetect > 0u)
                {
                    size = Airmar_RXBUFFERSIZE;
                }
                else
                {
                    size = 0u;
                }
            }
            else if(Airmar_rxBufferRead < Airmar_rxBufferWrite)
            {
                size = (Airmar_rxBufferWrite - Airmar_rxBufferRead);
            }
            else
            {
                size = (Airmar_RXBUFFERSIZE - Airmar_rxBufferRead) + Airmar_rxBufferWrite;
            }

            /* Enable Rx interrupt. */
            #if(Airmar_RX_INTERRUPT_ENABLED)
                Airmar_EnableRxInt();
            #endif /* End Airmar_RX_INTERRUPT_ENABLED */

        #else /* Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH */

            /* We can only know if there is data in the fifo. */
            size = ((Airmar_RXSTATUS_REG & Airmar_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

        #endif /* End Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: Airmar_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the RX RAM buffer by setting the read and write pointers both to zero.
    *  Clears hardware RX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Airmar_rxBufferWrite - cleared to zero.
    *  Airmar_rxBufferRead - cleared to zero.
    *  Airmar_rxBufferLoopDetect - cleared to zero.
    *  Airmar_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *******************************************************************************/
    void Airmar_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* clear the HW FIFO */
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();
        Airmar_RXDATA_AUX_CTL_REG |=  Airmar_RX_FIFO_CLR;
        Airmar_RXDATA_AUX_CTL_REG &= (uint8)~Airmar_RX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);

        #if(Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH)
            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(Airmar_RX_INTERRUPT_ENABLED)
                Airmar_DisableRxInt();
            #endif /* End Airmar_RX_INTERRUPT_ENABLED */

            Airmar_rxBufferRead = 0u;
            Airmar_rxBufferWrite = 0u;
            Airmar_rxBufferLoopDetect = 0u;
            Airmar_rxBufferOverflow = 0u;

            /* Enable Rx interrupt. */
            #if(Airmar_RX_INTERRUPT_ENABLED)
                Airmar_EnableRxInt();
            #endif /* End Airmar_RX_INTERRUPT_ENABLED */
        #endif /* End Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH */

    }


    /*******************************************************************************
    * Function Name: Airmar_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the receive addressing mode
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  Airmar__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  Airmar__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  Airmar__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  Airmar__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  Airmar__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Airmar_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  Airmar_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void Airmar_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(Airmar_RXHW_ADDRESS_ENABLED)
            #if(Airmar_CONTROL_REG_REMOVED)
                if(addressMode != 0u) { }     /* release compiler warning */
            #else /* Airmar_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = Airmar_CONTROL_REG & (uint8)~Airmar_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << Airmar_CTRL_RXADDR_MODE0_SHIFT);
                Airmar_CONTROL_REG = tmpCtrl;
                #if(Airmar_RX_INTERRUPT_ENABLED && \
                   (Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH) )
                    Airmar_rxAddressMode = addressMode;
                    Airmar_rxAddressDetected = 0u;
                #endif /* End Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH*/
            #endif /* End Airmar_CONTROL_REG_REMOVED */
        #else /* Airmar_RXHW_ADDRESS_ENABLED */
            if(addressMode != 0u) { }     /* release compiler warning */
        #endif /* End Airmar_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: Airmar_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Set the first hardware address compare value
    *
    * Parameters:
    *  address
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void Airmar_SetRxAddress1(uint8 address) 

    {
        Airmar_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: Airmar_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Set the second hardware address compare value
    *
    * Parameters:
    *  address
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void Airmar_SetRxAddress2(uint8 address) 
    {
        Airmar_RXADDRESS2_REG = address;
    }

#endif  /* Airmar_RX_ENABLED || Airmar_HD_ENABLED*/


#if( (Airmar_TX_ENABLED) || (Airmar_HD_ENABLED) )

    #if(Airmar_TX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: Airmar_EnableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void Airmar_EnableTxInt(void) 
        {
            CyIntEnable(Airmar_TX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: Airmar_DisableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void Airmar_DisableTxInt(void) 
        {
            CyIntDisable(Airmar_TX_VECT_NUM);
        }

    #endif /* Airmar_TX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: Airmar_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  intSrc: An or'd combination of the desired status bit masks (defined in
    *          the header file)
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void Airmar_SetTxInterruptMode(uint8 intSrc) 
    {
        Airmar_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: Airmar_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Write a byte of data to the Transmit FIFO or TX buffer to be sent when the
    *  bus is available. WriteTxData sends a byte without checking for buffer room
    *  or status. It is up to the user to separately check status.
    *
    * Parameters:
    *  TXDataByte: byte of data to place in the transmit FIFO
    *
    * Return:
    * void
    *
    * Global Variables:
    *  Airmar_txBuffer - RAM buffer pointer for save data for transmission
    *  Airmar_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  Airmar_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  Airmar_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void Airmar_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(Airmar_initVar != 0u)
        {
            #if(Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH)

                /* Disable Tx interrupt. */
                /* Protect variables that could change on interrupt. */
                #if(Airmar_TX_INTERRUPT_ENABLED)
                    Airmar_DisableTxInt();
                #endif /* End Airmar_TX_INTERRUPT_ENABLED */

                if( (Airmar_txBufferRead == Airmar_txBufferWrite) &&
                    ((Airmar_TXSTATUS_REG & Airmar_TX_STS_FIFO_FULL) == 0u) )
                {
                    /* Add directly to the FIFO. */
                    Airmar_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(Airmar_txBufferWrite >= Airmar_TXBUFFERSIZE)
                    {
                        Airmar_txBufferWrite = 0u;
                    }

                    Airmar_txBuffer[Airmar_txBufferWrite] = txDataByte;

                    /* Add to the software buffer. */
                    Airmar_txBufferWrite++;

                }

                /* Enable Tx interrupt. */
                #if(Airmar_TX_INTERRUPT_ENABLED)
                    Airmar_EnableTxInt();
                #endif /* End Airmar_TX_INTERRUPT_ENABLED */

            #else /* Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH */

                /* Add directly to the FIFO. */
                Airmar_TXDATA_REG = txDataByte;

            #endif /* End Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH */
        }
    }


    /*******************************************************************************
    * Function Name: Airmar_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the status register for the component
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the status register which is clear on read. It is up to
    *  the user to handle all bits in this return value accordingly, even if the bit
    *  was not enabled as an interrupt source the event happened and must be handled
    *  accordingly.
    *
    *******************************************************************************/
    uint8 Airmar_ReadTxStatus(void) 
    {
        return(Airmar_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: Airmar_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Wait to send byte until TX register or buffer has room.
    *
    * Parameters:
    *  txDataByte: The 8-bit data value to send across the UART.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Airmar_txBuffer - RAM buffer pointer for save data for transmission
    *  Airmar_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  Airmar_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  Airmar_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void Airmar_PutChar(uint8 txDataByte) 
    {
            #if(Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH)
                /* The temporary output pointer is used since it takes two instructions
                *  to increment with a wrap, and we can't risk doing that with the real
                *  pointer and getting an interrupt in between instructions.
                */
                uint8 loc_txBufferWrite;
                uint8 loc_txBufferRead;

                do{
                    /* Block if software buffer is full, so we don't overwrite. */
                    #if ((Airmar_TXBUFFERSIZE > Airmar_MAX_BYTE_VALUE) && (CY_PSOC3))
                        /* Disable TX interrupt to protect variables that could change on interrupt */
                        CyIntDisable(Airmar_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                    loc_txBufferWrite = Airmar_txBufferWrite;
                    loc_txBufferRead = Airmar_txBufferRead;
                    #if ((Airmar_TXBUFFERSIZE > Airmar_MAX_BYTE_VALUE) && (CY_PSOC3))
                        /* Enable interrupt to continue transmission */
                        CyIntEnable(Airmar_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                }while( (loc_txBufferWrite < loc_txBufferRead) ? (loc_txBufferWrite == (loc_txBufferRead - 1u)) :
                                        ((loc_txBufferWrite - loc_txBufferRead) ==
                                        (uint8)(Airmar_TXBUFFERSIZE - 1u)) );

                if( (loc_txBufferRead == loc_txBufferWrite) &&
                    ((Airmar_TXSTATUS_REG & Airmar_TX_STS_FIFO_FULL) == 0u) )
                {
                    /* Add directly to the FIFO. */
                    Airmar_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(loc_txBufferWrite >= Airmar_TXBUFFERSIZE)
                    {
                        loc_txBufferWrite = 0u;
                    }
                    /* Add to the software buffer. */
                    Airmar_txBuffer[loc_txBufferWrite] = txDataByte;
                    loc_txBufferWrite++;

                    /* Finally, update the real output pointer */
                    #if ((Airmar_TXBUFFERSIZE > Airmar_MAX_BYTE_VALUE) && (CY_PSOC3))
                        CyIntDisable(Airmar_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                    Airmar_txBufferWrite = loc_txBufferWrite;
                    #if ((Airmar_TXBUFFERSIZE > Airmar_MAX_BYTE_VALUE) && (CY_PSOC3))
                        CyIntEnable(Airmar_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                }

            #else /* Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH */

                while((Airmar_TXSTATUS_REG & Airmar_TX_STS_FIFO_FULL) != 0u)
                {
                    ; /* Wait for room in the FIFO. */
                }

                /* Add directly to the FIFO. */
                Airmar_TXDATA_REG = txDataByte;

            #endif /* End Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: Airmar_PutString
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: char pointer to character string of Data to Send.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Airmar_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  This function will block if there is not enough memory to place the whole
    *  string, it will block until the entire string has been written to the
    *  transmit buffer.
    *
    *******************************************************************************/
    void Airmar_PutString(const char8 string[]) 
    {
        uint16 buf_index = 0u;
        /* If not Initialized then skip this function*/
        if(Airmar_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent*/
            while(string[buf_index] != (char8)0)
            {
                Airmar_PutChar((uint8)string[buf_index]);
                buf_index++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: Airmar_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of Bytes to be transmitted.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Airmar_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void Airmar_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 buf_index = 0u;
        /* If not Initialized then skip this function*/
        if(Airmar_initVar != 0u)
        {
            do
            {
                Airmar_PutChar(string[buf_index]);
                buf_index++;
            }while(buf_index < byteCount);
        }
    }


    /*******************************************************************************
    * Function Name: Airmar_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Write a character and then carriage return and line feed.
    *
    * Parameters:
    *  txDataByte: uint8 Character to send.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Airmar_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void Airmar_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(Airmar_initVar != 0u)
        {
            Airmar_PutChar(txDataByte);
            Airmar_PutChar(0x0Du);
            Airmar_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: Airmar_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of space left in the TX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Integer count of the number of bytes left in the TX buffer
    *
    * Global Variables:
    *  Airmar_txBufferWrite - used to calculate left space.
    *  Airmar_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 Airmar_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

        #if(Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(Airmar_TX_INTERRUPT_ENABLED)
                Airmar_DisableTxInt();
            #endif /* End Airmar_TX_INTERRUPT_ENABLED */

            if(Airmar_txBufferRead == Airmar_txBufferWrite)
            {
                size = 0u;
            }
            else if(Airmar_txBufferRead < Airmar_txBufferWrite)
            {
                size = (Airmar_txBufferWrite - Airmar_txBufferRead);
            }
            else
            {
                size = (Airmar_TXBUFFERSIZE - Airmar_txBufferRead) + Airmar_txBufferWrite;
            }

            /* Enable Tx interrupt. */
            #if(Airmar_TX_INTERRUPT_ENABLED)
                Airmar_EnableTxInt();
            #endif /* End Airmar_TX_INTERRUPT_ENABLED */

        #else /* Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH */

            size = Airmar_TXSTATUS_REG;

            /* Is the fifo is full. */
            if((size & Airmar_TX_STS_FIFO_FULL) != 0u)
            {
                size = Airmar_FIFO_LENGTH;
            }
            else if((size & Airmar_TX_STS_FIFO_EMPTY) != 0u)
            {
                size = 0u;
            }
            else
            {
                /* We only know there is data in the fifo. */
                size = 1u;
            }

        #endif /* End Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: Airmar_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the TX RAM buffer by setting the read and write pointers both to zero.
    *  Clears the hardware TX FIFO.  Any data present in the FIFO will not be sent.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Airmar_txBufferWrite - cleared to zero.
    *  Airmar_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM buffer will be lost when overwritten.
    *
    *******************************************************************************/
    void Airmar_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();
        /* clear the HW FIFO */
        Airmar_TXDATA_AUX_CTL_REG |=  Airmar_TX_FIFO_CLR;
        Airmar_TXDATA_AUX_CTL_REG &= (uint8)~Airmar_TX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);

        #if(Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(Airmar_TX_INTERRUPT_ENABLED)
                Airmar_DisableTxInt();
            #endif /* End Airmar_TX_INTERRUPT_ENABLED */

            Airmar_txBufferRead = 0u;
            Airmar_txBufferWrite = 0u;

            /* Enable Tx interrupt. */
            #if(Airmar_TX_INTERRUPT_ENABLED)
                Airmar_EnableTxInt();
            #endif /* End Airmar_TX_INTERRUPT_ENABLED */

        #endif /* End Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: Airmar_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Write a Break command to the UART
    *
    * Parameters:
    *  uint8 retMode:  Wait mode,
    *   0 - Initialize registers for Break, sends the Break signal and return
    *       imediately.
    *   1 - Wait until Break sending is complete, reinitialize registers to normal
    *       transmission mode then return.
    *   2 - Reinitialize registers to normal transmission mode then return.
    *   3 - both steps: 0 and 1
    *       init registers for Break, send Break signal
    *       wait until Break sending is complete, reinit registers to normal
    *       transmission mode then return.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Airmar_initVar - checked to identify that the component has been
    *     initialized.
    *  tx_period - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  Trere are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Funcition will block CPU untill transmition
    *     complete.
    *  2) User may want to use bloking time if UART configured to the low speed
    *     operation
    *     Emample for this case:
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to init and use the interrupt for complete
    *     break operation.
    *     Example for this case:
    *     Init TX interrupt whith "TX - On TX Complete" parameter
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     When interrupt appear with UART_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *   Uses static variable to keep registers configuration.
    *
    *******************************************************************************/
    void Airmar_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(Airmar_initVar != 0u)
        {
            /*Set the Counter to 13-bits and transmit a 00 byte*/
            /*When that is done then reset the counter value back*/
            uint8 tmpStat;

            #if(Airmar_HD_ENABLED) /* Half Duplex mode*/

                if( (retMode == Airmar_SEND_BREAK) ||
                    (retMode == Airmar_SEND_WAIT_REINIT ) )
                {
                    /* CTRL_HD_SEND_BREAK - sends break bits in HD mode*/
                    Airmar_WriteControlRegister(Airmar_ReadControlRegister() |
                                                          Airmar_CTRL_HD_SEND_BREAK);
                    /* Send zeros*/
                    Airmar_TXDATA_REG = 0u;

                    do /*wait until transmit starts*/
                    {
                        tmpStat = Airmar_TXSTATUS_REG;
                    }while((tmpStat & Airmar_TX_STS_FIFO_EMPTY) != 0u);
                }

                if( (retMode == Airmar_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == Airmar_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = Airmar_TXSTATUS_REG;
                    }while(((uint8)~tmpStat & Airmar_TX_STS_COMPLETE) != 0u);
                }

                if( (retMode == Airmar_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == Airmar_REINIT) ||
                    (retMode == Airmar_SEND_WAIT_REINIT) )
                {
                    Airmar_WriteControlRegister(Airmar_ReadControlRegister() &
                                                  (uint8)~Airmar_CTRL_HD_SEND_BREAK);
                }

            #else /* Airmar_HD_ENABLED Full Duplex mode */

                static uint8 tx_period;

                if( (retMode == Airmar_SEND_BREAK) ||
                    (retMode == Airmar_SEND_WAIT_REINIT) )
                {
                    /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode*/
                    #if( (Airmar_PARITY_TYPE != Airmar__B_UART__NONE_REVB) || \
                                        (Airmar_PARITY_TYPE_SW != 0u) )
                        Airmar_WriteControlRegister(Airmar_ReadControlRegister() |
                                                              Airmar_CTRL_HD_SEND_BREAK);
                    #endif /* End Airmar_PARITY_TYPE != Airmar__B_UART__NONE_REVB  */

                    #if(Airmar_TXCLKGEN_DP)
                        tx_period = Airmar_TXBITCLKTX_COMPLETE_REG;
                        Airmar_TXBITCLKTX_COMPLETE_REG = Airmar_TXBITCTR_BREAKBITS;
                    #else
                        tx_period = Airmar_TXBITCTR_PERIOD_REG;
                        Airmar_TXBITCTR_PERIOD_REG = Airmar_TXBITCTR_BREAKBITS8X;
                    #endif /* End Airmar_TXCLKGEN_DP */

                    /* Send zeros*/
                    Airmar_TXDATA_REG = 0u;

                    do /* wait until transmit starts */
                    {
                        tmpStat = Airmar_TXSTATUS_REG;
                    }while((tmpStat & Airmar_TX_STS_FIFO_EMPTY) != 0u);
                }

                if( (retMode == Airmar_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == Airmar_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = Airmar_TXSTATUS_REG;
                    }while(((uint8)~tmpStat & Airmar_TX_STS_COMPLETE) != 0u);
                }

                if( (retMode == Airmar_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == Airmar_REINIT) ||
                    (retMode == Airmar_SEND_WAIT_REINIT) )
                {

                    #if(Airmar_TXCLKGEN_DP)
                        Airmar_TXBITCLKTX_COMPLETE_REG = tx_period;
                    #else
                        Airmar_TXBITCTR_PERIOD_REG = tx_period;
                    #endif /* End Airmar_TXCLKGEN_DP */

                    #if( (Airmar_PARITY_TYPE != Airmar__B_UART__NONE_REVB) || \
                         (Airmar_PARITY_TYPE_SW != 0u) )
                        Airmar_WriteControlRegister(Airmar_ReadControlRegister() &
                                                      (uint8)~Airmar_CTRL_HD_SEND_BREAK);
                    #endif /* End Airmar_PARITY_TYPE != NONE */
                }
            #endif    /* End Airmar_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: Airmar_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the transmit addressing mode
    *
    * Parameters:
    *  addressMode: 0 -> Space
    *               1 -> Mark
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void Airmar_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable*/
        if(addressMode != 0u)
        {
            #if( Airmar_CONTROL_REG_REMOVED == 0u )
                Airmar_WriteControlRegister(Airmar_ReadControlRegister() |
                                                      Airmar_CTRL_MARK);
            #endif /* End Airmar_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
            #if( Airmar_CONTROL_REG_REMOVED == 0u )
                Airmar_WriteControlRegister(Airmar_ReadControlRegister() &
                                                    (uint8)~Airmar_CTRL_MARK);
            #endif /* End Airmar_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndAirmar_TX_ENABLED */

#if(Airmar_HD_ENABLED)


    /*******************************************************************************
    * Function Name: Airmar_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Rx configuration if required and loads the
    *  Tx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Tx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART.
    *
    * Side Effects:
    *  Disable RX interrupt mask, when software buffer has been used.
    *
    *******************************************************************************/
    void Airmar_LoadTxConfig(void) 
    {
        #if((Airmar_RX_INTERRUPT_ENABLED) && (Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH))
            /* Disable RX interrupts before set TX configuration */
            Airmar_SetRxInterruptMode(0u);
        #endif /* Airmar_RX_INTERRUPT_ENABLED */

        Airmar_WriteControlRegister(Airmar_ReadControlRegister() | Airmar_CTRL_HD_SEND);
        Airmar_RXBITCTR_PERIOD_REG = Airmar_HD_TXBITCTR_INIT;
        #if(CY_UDB_V0) /* Manually clear status register when mode has been changed */
            /* Clear status register */
            CY_GET_REG8(Airmar_RXSTATUS_PTR);
        #endif /* CY_UDB_V0 */
    }


    /*******************************************************************************
    * Function Name: Airmar_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Tx configuration if required and loads the
    *  Rx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Rx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART
    *
    * Side Effects:
    *  Set RX interrupt mask based on customizer settings, when software buffer
    *  has been used.
    *
    *******************************************************************************/
    void Airmar_LoadRxConfig(void) 
    {
        Airmar_WriteControlRegister(Airmar_ReadControlRegister() &
                                                (uint8)~Airmar_CTRL_HD_SEND);
        Airmar_RXBITCTR_PERIOD_REG = Airmar_HD_RXBITCTR_INIT;
        #if(CY_UDB_V0) /* Manually clear status register when mode has been changed */
            /* Clear status register */
            CY_GET_REG8(Airmar_RXSTATUS_PTR);
        #endif /* CY_UDB_V0 */

        #if((Airmar_RX_INTERRUPT_ENABLED) && (Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH))
            /* Enable RX interrupt after set RX configuration */
            Airmar_SetRxInterruptMode(Airmar_INIT_RX_INTERRUPTS_MASK);
        #endif /* Airmar_RX_INTERRUPT_ENABLED */
    }

#endif  /* Airmar_HD_ENABLED */


/* [] END OF FILE */
