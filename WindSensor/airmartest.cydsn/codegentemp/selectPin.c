/*******************************************************************************
* File Name: selectPin.c  
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
#include "selectPin.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 selectPin__PORT == 15 && ((selectPin__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: selectPin_Write
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
void selectPin_Write(uint8 value) 
{
    uint8 staticBits = (selectPin_DR & (uint8)(~selectPin_MASK));
    selectPin_DR = staticBits | ((uint8)(value << selectPin_SHIFT) & selectPin_MASK);
}


/*******************************************************************************
* Function Name: selectPin_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  selectPin_DM_STRONG     Strong Drive 
*  selectPin_DM_OD_HI      Open Drain, Drives High 
*  selectPin_DM_OD_LO      Open Drain, Drives Low 
*  selectPin_DM_RES_UP     Resistive Pull Up 
*  selectPin_DM_RES_DWN    Resistive Pull Down 
*  selectPin_DM_RES_UPDWN  Resistive Pull Up/Down 
*  selectPin_DM_DIG_HIZ    High Impedance Digital 
*  selectPin_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void selectPin_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(selectPin_0, mode);
}


/*******************************************************************************
* Function Name: selectPin_Read
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
*  Macro selectPin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 selectPin_Read(void) 
{
    return (selectPin_PS & selectPin_MASK) >> selectPin_SHIFT;
}


/*******************************************************************************
* Function Name: selectPin_ReadDataReg
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
uint8 selectPin_ReadDataReg(void) 
{
    return (selectPin_DR & selectPin_MASK) >> selectPin_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(selectPin_INTSTAT) 

    /*******************************************************************************
    * Function Name: selectPin_ClearInterrupt
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
    uint8 selectPin_ClearInterrupt(void) 
    {
        return (selectPin_INTSTAT & selectPin_MASK) >> selectPin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
