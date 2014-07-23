/*******************************************************************************
* File Name: dataPin.c  
* Version 2.0
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "dataPin.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 dataPin__PORT == 15 && ((dataPin__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: dataPin_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void dataPin_Write(uint8 value) 
{
    uint8 staticBits = (dataPin_DR & (uint8)(~dataPin_MASK));
    dataPin_DR = staticBits | ((uint8)(value << dataPin_SHIFT) & dataPin_MASK);
}


/*******************************************************************************
* Function Name: dataPin_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  dataPin_DM_STRONG     Strong Drive 
*  dataPin_DM_OD_HI      Open Drain, Drives High 
*  dataPin_DM_OD_LO      Open Drain, Drives Low 
*  dataPin_DM_RES_UP     Resistive Pull Up 
*  dataPin_DM_RES_DWN    Resistive Pull Down 
*  dataPin_DM_RES_UPDWN  Resistive Pull Up/Down 
*  dataPin_DM_DIG_HIZ    High Impedance Digital 
*  dataPin_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void dataPin_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(dataPin_0, mode);
}


/*******************************************************************************
* Function Name: dataPin_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro dataPin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 dataPin_Read(void) 
{
    return (dataPin_PS & dataPin_MASK) >> dataPin_SHIFT;
}


/*******************************************************************************
* Function Name: dataPin_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 dataPin_ReadDataReg(void) 
{
    return (dataPin_DR & dataPin_MASK) >> dataPin_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(dataPin_INTSTAT) 

    /*******************************************************************************
    * Function Name: dataPin_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 dataPin_ClearInterrupt(void) 
    {
        return (dataPin_INTSTAT & dataPin_MASK) >> dataPin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
