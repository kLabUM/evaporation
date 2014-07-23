/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  This is source code for example project of the SPI Master component.
*  Parameters used:
*   Mode                CPHA == 0, CPOL == 0                
*   Data lines          MOSI+MISO
*   Shift direction     MSB First
*   DataBits:           8 
*   Bit Rate            1 Mbps
*   Clock source        External 
*
*  SPI communication test using DMA. 8 bytes are transmitted
*  between SPI Master and SPI Slave.
*  Received data are displayed on LCD. 
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <device.h>

void Dma_M_Tx_Configuration(void);
void Dma_M_Rx_Configuration(void);

/* DMA Configuration for DMA_TX_M */
#define DMA_TX_M_BYTES_PER_BURST       (1u)
#define DMA_TX_M_REQUEST_PER_BURST     (1u)
#define DMA_TX_M_SRC_BASE              (CYDEV_SRAM_BASE)
#define DMA_TX_M_DST_BASE              (CYDEV_PERIPH_BASE)

/* DMA Configuration for DMA_RX_M */
#define DMA_RX_M_BYTES_PER_BURST       (1u)
#define DMA_RX_M_REQUEST_PER_BURST     (1u)
#define DMA_RX_M_SRC_BASE              (CYDEV_PERIPH_BASE)
#define DMA_RX_M_DST_BASE              (CYDEV_SRAM_BASE)

/* Variable declarations for DMA_Tx_M */
uint8 M_TxChannel;
uint8 M_TxTD[2u];

/* Variable declarations for DMA_Rx_M */
uint8 M_RxChannel;
uint8 M_RxTD[2u];

/* Data to be transmitted by Tx */
uint8 m_txBuffer [8u] = {0x0u, 0x01u, 0x02u, 0x03u, 0x04u, 0x05u, 0x06u, 0x07u};

uint8 m_rxBuffer[8u];


/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  Main function performs following functions:
*   1. Starts Character LCD and print project info
*   2. Starts SPI Master component
*   3. Configures the DMA transfer for RX and TX directions
*   4. Displays the results on Character LCD
*   
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void main()
{
    uint8 i = 0u;
    CyGlobalIntEnable; 
    
    for(i=0u; i<8u; i++)
    {
        m_rxBuffer[i] = 0u;
    }
    
    LCD_Start();
    LCD_Position(0u,0u);
    LCD_PrintString("SPI Master");
    LCD_Position(1u,0u);
    LCD_PrintString("example");
    CyDelay(3000u);
    
    Dma_M_Tx_Configuration();
    Dma_M_Rx_Configuration();
    
    CyDmaChEnable(M_TxChannel, 1u); 
    CyDmaChEnable(M_RxChannel, 1u);
    
    LCD_Position(0u,0u);
    LCD_PrintString("Master Tx data:");
    LCD_Position(1u,0u);
    for(i=0u; i<8u; i++)
    {
        LCD_PrintHexUint8(m_txBuffer[i]);
    }
    
    CyDelay(5000u);
    SPIM_Start();
    
    while(!(SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE));
    
    LCD_ClearDisplay();
    LCD_PrintString("Master Rx data:");
    LCD_Position(1u,0u);
    
    for(i=0u; i<8u; i++)
    {
        LCD_PrintHexUint8(m_rxBuffer[i]);
    }
    CyDelay(5000u);
    LCD_ClearDisplay();
    LCD_PrintString("SPI Master");
    LCD_Position(1u,0u);
    LCD_PrintString("example complete.");
     
    for(;;)
    {
        
    }
}

    
/*******************************************************************************
* Function Name: Dma_M_Tx_Configuration
********************************************************************************
* Summary:
*  Configures the DMA transfer for TX direction
*   
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Dma_M_Tx_Configuration()
{
    /* Init DMA, 1 byte bursts, each burst requires a request */ 
    M_TxChannel = DMA_TX_M_DmaInitialize(DMA_TX_M_BYTES_PER_BURST, DMA_TX_M_REQUEST_PER_BURST, 
                                        HI16(DMA_TX_M_SRC_BASE), HI16(DMA_TX_M_DST_BASE));

    M_TxTD[0u] = CyDmaTdAllocate();
    M_TxTD[1u] = CyDmaTdAllocate();

    /* Configure this Td chain as follows:
    *  - The TD is looping on itself
    *  - Increment the source address, but not the destination address   
    */
    CyDmaTdSetConfiguration(M_TxTD[0u], 8u, M_TxTD[1u], TD_INC_SRC_ADR);
    CyDmaTdSetConfiguration(M_TxTD[1u], 1u, M_TxTD[1u], 0u);
    
    /* From the memory to the SPIM */
    CyDmaTdSetAddress(M_TxTD[0u], LO16((uint32)m_txBuffer), LO16((uint32)SPIM_BSPIM_sR8_Dp_u0__F0_REG));
    CyDmaTdSetAddress(M_TxTD[1u], LO16((uint32)m_txBuffer), LO16((uint32)m_txBuffer));
    
    /* Associate the TD with the channel */
    CyDmaChSetInitialTd(M_TxChannel, M_TxTD[0u]); 
}    


/*******************************************************************************
* Function Name: Dma_M_Rx_Configuration
********************************************************************************
* Summary:
*  Configures the DMA transfer for RX direction
*   
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Dma_M_Rx_Configuration()
{ 
    /* Init DMA, 1 byte bursts, each burst requires a request */ 
    M_RxChannel = DMA_RX_M_DmaInitialize(DMA_RX_M_BYTES_PER_BURST, DMA_RX_M_REQUEST_PER_BURST,
                                     HI16(DMA_RX_M_SRC_BASE), HI16(DMA_RX_M_DST_BASE));

    M_RxTD[0u] = CyDmaTdAllocate();
    M_RxTD[1u] = CyDmaTdAllocate();
    /* Configure this Td as follows:
    *  - The TD is looping on itself
    *  - Increment the destination address, but not the source address
    */
    CyDmaTdSetConfiguration(M_RxTD[0u], 8u, M_RxTD[1u], TD_INC_DST_ADR);
    CyDmaTdSetConfiguration(M_RxTD[1u], 1u, M_RxTD[0u], 0u);

    /* From the SPIM to the memory */
    CyDmaTdSetAddress(M_RxTD[0u], LO16((uint32)SPIM_BSPIM_sR8_Dp_u0__F1_REG), LO16((uint32)m_rxBuffer));
    CyDmaTdSetAddress(M_RxTD[1u], LO16((uint32)m_rxBuffer), LO16((uint32)m_rxBuffer));

    /* Associate the TD with the channel */
    CyDmaChSetInitialTd(M_RxChannel, M_RxTD[0u]);
}
   
	
/* [] END OF FILE */
