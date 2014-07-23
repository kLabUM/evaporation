/*******************************************************************************
* File Name: main.c
*
* Version: 1.10
*
* Description:
*  This is source code for the datasheet example of the I2C master and slave
*  components.
*
*  The project explains the usage of I2C slave and I2C master components. In
*  the project when switch SW1 is pressed the I2C master writes a corresponding
*  message to the I2C slave and when switch SW2 is pressed the I2C master will
*  read back the data from the slave. Both the written and read back data are
*  displayed on LCD if both write and read operations happens successfully.
*
*  Display legend:
*   First string:
*    WR: xxxxxxxxxx
*       WR:- Data being written by I2C mater to I2C slave.
*
*   Second string:
*    RD: xxxxxxxxxx
*       RD:- Data being read by I2C mater from I2C slave.
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

/* Desing interrupt handlers for SW1 and SW2 event */
CY_ISR_PROTO(ISR_WriteSW1_Interrupt);
CY_ISR_PROTO(ISR_ReadSW2_Interrupt);

/* Button press actions */
#define ACTION_SELECT_NONE      (0x00u) /* Do nothing           */
#define ACTION_SELECT_WRITE     (0x01u) /* Write into I2C slave */
#define ACTION_SELECT_READ      (0x02u) /* Read from I2C slave  */

/* Slave address of the I2C slave */
#define I2C_SLAVE_ADDR  (I2C_S_I2C_SLAVE_ADDRESS)

/* Buffer size for read or write */
#define BUFFER_SIZE     (0x04u)

/* I2C master read and write buffers */
uint8 i2cMasterReadBuf[BUFFER_SIZE];
uint8 i2cMasterWriteBuf[BUFFER_SIZE] = {0x01u, 0x02u, 0x03u, 0x04u};

/* I2C slave read and write buffers */
uint8 i2cSlaveReadBuf[BUFFER_SIZE]  = {0x00u, 0x00u, 0x00u, 0x00u};
uint8 i2cSlaveWriteBuf[BUFFER_SIZE];

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
    LCD_PrintString("I2C slave      ");
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
    
    /* Start I2C slave (SCB mode) */
    I2C_S_I2CSlaveInitReadBuf(i2cSlaveReadBuf, BUFFER_SIZE);
    I2C_S_I2CSlaveInitWriteBuf(i2cSlaveWriteBuf, BUFFER_SIZE);
    I2C_S_Start();
    
    /* Start I2C master (SCB mode) */
    I2C_M_Start();

    CyGlobalIntEnable;

    for(;;)
    {
        /* SW1: Write data to I2C slave */
        if(ACTION_SELECT_WRITE == actionSelect)
        {
            /* Clear action */
            actionSelect = ACTION_SELECT_NONE;

            /* Write data to the slave */
            I2C_M_I2CMasterWriteBuf(I2C_SLAVE_ADDR, (uint8 *) i2cMasterWriteBuf,
                                     BUFFER_SIZE, I2C_M_I2C_MODE_COMPLETE_XFER);

            while(0u == (I2C_M_I2CMasterStatus() & I2C_M_I2C_MSTAT_WR_CMPLT))
            {
                /* Wait until master complete write */
            }
            
            /* Clear I2C master status */
            (void) I2C_M_I2CMasterClearStatus();

            /* Display data written into the I2C slave */
            LCD_Position(0u, 0u);
            LCD_PrintString("WR: ");

            for(i = 0u; i < I2C_S_I2CSlaveGetWriteBufSize(); i++)
            {   
                LCD_PrintInt8(i2cSlaveWriteBuf[i]);
                LCD_PrintString(" ");
                
                /* Copy writen bytes into the slave read buffer */
                i2cSlaveReadBuf[i] = i2cSlaveWriteBuf[i]; 
            }
            
            /* Clear slave write buffer */
            I2C_S_I2CSlaveClearWriteBuf();
            
            /* Update buffer to be written into I2C slave */
            for(i = 0u; i < BUFFER_SIZE; i++)
            {
                i2cMasterWriteBuf[i]++;
            }

        } /* End of write data to I2C slave */

        /* SW2: Read data from I2C slave */
        if(ACTION_SELECT_READ == actionSelect)
        {
            /* Clear action */
            actionSelect = ACTION_SELECT_NONE;                        

            /* Read the data from the I2C slave */
            I2C_M_I2CMasterReadBuf(I2C_SLAVE_ADDR, (uint8 *) i2cMasterReadBuf,
                                   BUFFER_SIZE, I2C_M_I2C_MODE_COMPLETE_XFER);

            while(0u == (I2C_M_I2CMasterStatus() & I2C_M_I2C_MSTAT_RD_CMPLT))
            {
                /* Wait until master complete reading */
            }
            
            /* Clear I2C master status */
            (void) I2C_M_I2CMasterClearStatus();

            /* Display data read from the I2C slave */
            LCD_Position(1u, 0u);
            LCD_PrintString("RD: ");
            
            for(i = 0u; i < I2C_M_I2CMasterGetReadBufSize(); i++)
            {                
                LCD_PrintInt8(i2cMasterReadBuf[i]);
                LCD_PrintString(" ");
            }
             
            /* Clear slave read buffer */
            I2C_S_I2CSlaveClearReadBuf();
            
        } /* End of read data from I2C slave */
    }
}


/*******************************************************************************
*  The Interrupt Service Routine for SW1 event.
*******************************************************************************/
CY_ISR(ISR_WriteSW1_Interrupt)
{
    /* Clear pin interrupt request bit */
    (void) SW1_Write_ClearInterrupt();

    /* Select read action */
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
