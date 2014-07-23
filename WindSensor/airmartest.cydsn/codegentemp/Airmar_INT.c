/*******************************************************************************
* File Name: Airmar_INT.c
* Version 2.30
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Airmar.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (Airmar_RX_ENABLED || Airmar_HD_ENABLED) && \
     (Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: Airmar_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Airmar_rxBuffer - RAM buffer pointer for save received data.
    *  Airmar_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  Airmar_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  Airmar_rxBufferOverflow - software overflow flag. Set to one
    *     when Airmar_rxBufferWrite index overtakes
    *     Airmar_rxBufferRead index.
    *  Airmar_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when Airmar_rxBufferWrite is equal to
    *    Airmar_rxBufferRead
    *  Airmar_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  Airmar_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(Airmar_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;
        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START Airmar_RXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        readData = Airmar_RXSTATUS_REG;

        if((readData & (Airmar_RX_STS_BREAK | Airmar_RX_STS_PAR_ERROR |
                        Airmar_RX_STS_STOP_ERROR | Airmar_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            /* `#START Airmar_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & Airmar_RX_STS_FIFO_NOTEMPTY) != 0u)
        {

            #if (Airmar_RXHW_ADDRESS_ENABLED)
                if(Airmar_rxAddressMode == (uint8)Airmar__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readData & Airmar_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readData & Airmar_RX_STS_ADDR_MATCH) != 0u)
                        {
                            Airmar_rxAddressDetected = 1u;
                        }
                        else
                        {
                            Airmar_rxAddressDetected = 0u;
                        }
                    }

                    readData = Airmar_RXDATA_REG;
                    if(Airmar_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        Airmar_rxBuffer[Airmar_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    Airmar_rxBuffer[Airmar_rxBufferWrite] = Airmar_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                Airmar_rxBuffer[Airmar_rxBufferWrite] = Airmar_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */

            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(Airmar_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    Airmar_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                Airmar_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(Airmar_rxBufferWrite >= Airmar_RXBUFFERSIZE)
                {
                    Airmar_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(Airmar_rxBufferWrite == Airmar_rxBufferRead)
                {
                    Airmar_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(Airmar_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        Airmar_RXSTATUS_MASK_REG  &= (uint8)~Airmar_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(Airmar_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End Airmar_FLOW_CONTROL != 0 */
                }
            }

            /* Check again if there is data. */
            readData = Airmar_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Airmar_RXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End Airmar_RX_ENABLED && (Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH) */


#if(Airmar_TX_ENABLED && (Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: Airmar_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Airmar_txBuffer - RAM buffer pointer for transmit data from.
    *  Airmar_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmited byte.
    *  Airmar_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(Airmar_TXISR)
    {

        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START Airmar_TXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        while((Airmar_txBufferRead != Airmar_txBufferWrite) &&
             ((Airmar_TXSTATUS_REG & Airmar_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer. */
            if(Airmar_txBufferRead >= Airmar_TXBUFFERSIZE)
            {
                Airmar_txBufferRead = 0u;
            }

            Airmar_TXDATA_REG = Airmar_txBuffer[Airmar_txBufferRead];

            /* Set next pointer. */
            Airmar_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Airmar_TXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End Airmar_TX_ENABLED && (Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH) */


/* [] END OF FILE */
