/*******************************************************************************
* File Name: Battery_Ground.c  
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
#include "Battery_Ground.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Battery_Ground__PORT == 15 && ((Battery_Ground__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Battery_Ground_Write
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
void Battery_Ground_Write(uint8 value) 
{
    uint8 staticBits = (Battery_Ground_DR & (uint8)(~Battery_Ground_MASK));
    Battery_Ground_DR = staticBits | ((uint8)(value << Battery_Ground_SHIFT) & Battery_Ground_MASK);
}


/*******************************************************************************
* Function Name: Battery_Ground_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Battery_Ground_DM_STRONG     Strong Drive 
*  Battery_Ground_DM_OD_HI      Open Drain, Drives High 
*  Battery_Ground_DM_OD_LO      Open Drain, Drives Low 
*  Battery_Ground_DM_RES_UP     Resistive Pull Up 
*  Battery_Ground_DM_RES_DWN    Resistive Pull Down 
*  Battery_Ground_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Battery_Ground_DM_DIG_HIZ    High Impedance Digital 
*  Battery_Ground_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Battery_Ground_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Battery_Ground_0, mode);
}


/*******************************************************************************
* Function Name: Battery_Ground_Read
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
*  Macro Battery_Ground_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Battery_Ground_Read(void) 
{
    return (Battery_Ground_PS & Battery_Ground_MASK) >> Battery_Ground_SHIFT;
}


/*******************************************************************************
* Function Name: Battery_Ground_ReadDataReg
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
uint8 Battery_Ground_ReadDataReg(void) 
{
    return (Battery_Ground_DR & Battery_Ground_MASK) >> Battery_Ground_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Battery_Ground_INTSTAT) 

    /*******************************************************************************
    * Function Name: Battery_Ground_ClearInterrupt
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
    uint8 Battery_Ground_ClearInterrupt(void) 
    {
        return (Battery_Ground_INTSTAT & Battery_Ground_MASK) >> Battery_Ground_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
