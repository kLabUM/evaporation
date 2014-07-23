/*******************************************************************************
* File Name: clockPin.c  
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
#include "clockPin.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 clockPin__PORT == 15 && ((clockPin__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: clockPin_Write
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
void clockPin_Write(uint8 value) 
{
    uint8 staticBits = (clockPin_DR & (uint8)(~clockPin_MASK));
    clockPin_DR = staticBits | ((uint8)(value << clockPin_SHIFT) & clockPin_MASK);
}


/*******************************************************************************
* Function Name: clockPin_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  clockPin_DM_STRONG     Strong Drive 
*  clockPin_DM_OD_HI      Open Drain, Drives High 
*  clockPin_DM_OD_LO      Open Drain, Drives Low 
*  clockPin_DM_RES_UP     Resistive Pull Up 
*  clockPin_DM_RES_DWN    Resistive Pull Down 
*  clockPin_DM_RES_UPDWN  Resistive Pull Up/Down 
*  clockPin_DM_DIG_HIZ    High Impedance Digital 
*  clockPin_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void clockPin_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(clockPin_0, mode);
}


/*******************************************************************************
* Function Name: clockPin_Read
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
*  Macro clockPin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 clockPin_Read(void) 
{
    return (clockPin_PS & clockPin_MASK) >> clockPin_SHIFT;
}


/*******************************************************************************
* Function Name: clockPin_ReadDataReg
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
uint8 clockPin_ReadDataReg(void) 
{
    return (clockPin_DR & clockPin_MASK) >> clockPin_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(clockPin_INTSTAT) 

    /*******************************************************************************
    * Function Name: clockPin_ClearInterrupt
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
    uint8 clockPin_ClearInterrupt(void) 
    {
        return (clockPin_INTSTAT & clockPin_MASK) >> clockPin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
