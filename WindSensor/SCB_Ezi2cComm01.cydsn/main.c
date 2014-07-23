/*******************************************************************************
* File Name: main.c
*
* Version: 3.0
*
* Description:
*  This is source code for the datasheet example of the EZI2C and I2C
*  components.
*
*  The project explains the usage of EZI2C slave and I2C master components. In
*  the project when switch SW1 is pressed the I2C master writes a corresponding
*  message to the EZI2C slave and when switch SW2 is pressed the I2C master will
*  read back the data from the slave. Both the written and read back data are
*  displayed on LCD if both write and read operations happens successfully.
*
*  Display legend:
*   First string:
*    WR: xxxxxxxxxx
*       WR:- Data being written by I2C mater to EZI2C.
*
*   Second string:
*    RD: xxxxxxxxxx
*       RD:- Data being read by I2C mater from EZI2C.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <device.h>

/* Interrupt handlers for SW1 and SW2 event */
CY_ISR_PROTO(ISR_WriteSW1_Interrupt);
CY_ISR_PROTO(ISR_ReadSW2_Interrupt);

#define ACTION_SELECT_NONE      (0x00u)     /* Do nothing       */
#define ACTION_SELECT_WRITE     (0x01u)     /* Write to EZI2C   */
#define ACTION_SELECT_READ      (0x02u)     /* Read from EZI2C  */

/* Slave address of the EZI2C */
#define EZI2C_SLAVE_ADDR        (EZI2C_S_EZI2C_PRIMARY_SLAVE_ADDRESS)

/* Buffer definition constants */
#define BUFFER_SIZE             (0x04u)
#define OFFSET_POSITION         (0x01u)
#define RW_BOUNDARY_POSITION    (0x02u)
#define SUB_ADDRESS_SIZE        (0x01u)
#define WR_BUFFER_SIZE          (SUB_ADDRESS_SIZE + BUFFER_SIZE)

/* I2C master read and write buffers  */
uint8 i2cBufferRead[BUFFER_SIZE];
uint8 i2cBufferWrite[WR_BUFFER_SIZE] = {0x00u, 0x01u, 0x02u, 0x03u, 0x04u};

/* EZI2C buffer */
uint8 ezI2CBuffer[BUFFER_SIZE] = {0x00u, 0x00u, 0xAAu, 0xBBu};

/* Initialize action variable */
volatile uint8 actionSelect = ACTION_SELECT_NONE;


void main()
{
    uint8 i;

    /* Start Character LCD and display usage info */
    LCD_Start();
    
    LCD_Position(0u, 0u);
    LCD_PrintString("I2C master com  ");
    LCD_Position(1u, 0u);
    LCD_PrintString("EZI2C slave     ");
    CyDelay(3000u);
    
    LCD_Position(0u, 0u);
    LCD_PrintString("SW1 to Write    ");
    LCD_Position(1u, 0u);
    LCD_PrintString("SW2 to Read     ");

    /* Start ISRs */
    (void) SW1_Write_ClearInterrupt();
    (void) SW2_Read_ClearInterrupt();
    ISR_Write_StartEx(&ISR_WriteSW1_Interrupt);
    ISR_Read_StartEx (&ISR_ReadSW2_Interrupt);
    
    /* Start EZI2C slave (SCB mode) */
    EZI2C_S_EzI2CSetBuffer1(BUFFER_SIZE, RW_BOUNDARY_POSITION, ezI2CBuffer);
    EZI2C_S_Start();
    
    /* Start I2C master (SCB mode) */
    I2C_M_Start();
    
    CyGlobalIntEnable;

    for(;;)
    {
        /* SW1: Write data to EZI2C slave */
        if(actionSelect == ACTION_SELECT_WRITE)
        {
            /* Clear action */
            actionSelect = ACTION_SELECT_NONE;

            /* Write data to the EZI2C slave */
            I2C_M_I2CMasterWriteBuf(EZI2C_SLAVE_ADDR, i2cBufferWrite,
                                        (SUB_ADDRESS_SIZE + BUFFER_SIZE), 
                                            I2C_M_I2C_MODE_COMPLETE_XFER);

            while(0u == (I2C_M_I2CMasterStatus() & I2C_M_I2C_MSTAT_WR_CMPLT))
            {
                /* Wait write to be completed */
            }
            
            /* Clear I2C master status */
            (void) I2C_M_I2CMasterClearStatus();
            
            /* Display data in the EZI2C buffer */
            LCD_Position(0u, 0u);
            LCD_PrintString("WR: ");
            
            for(i = OFFSET_POSITION; i < WR_BUFFER_SIZE; i++)
            {
                LCD_PrintInt8(i2cBufferWrite[i]);
                LCD_PrintString(" ");
            }
            
            /* Update buffer to be written into EZI2C slave */
            for(i = OFFSET_POSITION; i < WR_BUFFER_SIZE; i++)
            {
                i2cBufferWrite[i]++;
            }

        } /* End of write data to EZI2C */

        /* SW2: Read data from EZI2C slave */
        if(actionSelect == ACTION_SELECT_READ)
        {
            /* Clear action */
            actionSelect = ACTION_SELECT_NONE;

            /* Read the data from the EZI2C */
            I2C_M_I2CMasterReadBuf(EZI2C_SLAVE_ADDR, i2cBufferRead, BUFFER_SIZE, 
                                            I2C_M_I2C_MODE_COMPLETE_XFER);

            while(0u == (I2C_M_I2CMasterStatus() & I2C_M_I2C_MSTAT_RD_CMPLT))
            {
                /* Wait read to be completed */
            }
            
            /* Clear I2C Master status */
            I2C_M_I2CMasterClearStatus();

            /* Display data that I2C master has read */
            LCD_Position(1u, 0u);
            LCD_PrintString("RD: ");
            
            for(i = 0u; i < BUFFER_SIZE; i++)
            {
                LCD_PrintInt8(i2cBufferRead[i]);
                LCD_PrintString(" ");
            }

        } /* End of read data from EZI2C */
    }
}


/*******************************************************************************
*  The Interrupt Service Routine for SW1 event.
*******************************************************************************/
CY_ISR(ISR_WriteSW1_Interrupt)
{
    /* Clear pin interrupt request bit */
    (void) SW1_Write_ClearInterrupt();

    /* Select write action */
    actionSelect = ACTION_SELECT_WRITE;
}


/*******************************************************************************
*  The Interrupt Service Routine for SW2 event.
*******************************************************************************/
CY_ISR(ISR_ReadSW2_Interrupt)
{
    /* Clear pin interrupt request bit */
    (void) SW2_Read_ClearInterrupt();

    /* Select read action */
    actionSelect = ACTION_SELECT_READ;
}


/* [] END OF FILE */
