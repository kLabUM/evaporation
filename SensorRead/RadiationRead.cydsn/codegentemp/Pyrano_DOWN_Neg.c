/*******************************************************************************
* File Name: Pyrano_DOWN_Neg.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Pyrano_DOWN_Neg.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Pyrano_DOWN_Neg__PORT == 15 && ((Pyrano_DOWN_Neg__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Pyrano_DOWN_Neg_Write
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
void Pyrano_DOWN_Neg_Write(uint8 value) 
{
    uint8 staticBits = (Pyrano_DOWN_Neg_DR & (uint8)(~Pyrano_DOWN_Neg_MASK));
    Pyrano_DOWN_Neg_DR = staticBits | ((uint8)(value << Pyrano_DOWN_Neg_SHIFT) & Pyrano_DOWN_Neg_MASK);
}


/*******************************************************************************
* Function Name: Pyrano_DOWN_Neg_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void Pyrano_DOWN_Neg_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Pyrano_DOWN_Neg_0, mode);
}


/*******************************************************************************
* Function Name: Pyrano_DOWN_Neg_Read
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
*  Macro Pyrano_DOWN_Neg_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pyrano_DOWN_Neg_Read(void) 
{
    return (Pyrano_DOWN_Neg_PS & Pyrano_DOWN_Neg_MASK) >> Pyrano_DOWN_Neg_SHIFT;
}


/*******************************************************************************
* Function Name: Pyrano_DOWN_Neg_ReadDataReg
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
uint8 Pyrano_DOWN_Neg_ReadDataReg(void) 
{
    return (Pyrano_DOWN_Neg_DR & Pyrano_DOWN_Neg_MASK) >> Pyrano_DOWN_Neg_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pyrano_DOWN_Neg_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pyrano_DOWN_Neg_ClearInterrupt
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
    uint8 Pyrano_DOWN_Neg_ClearInterrupt(void) 
    {
        return (Pyrano_DOWN_Neg_INTSTAT & Pyrano_DOWN_Neg_MASK) >> Pyrano_DOWN_Neg_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
