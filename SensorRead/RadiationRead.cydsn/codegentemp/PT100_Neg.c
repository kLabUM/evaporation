/*******************************************************************************
* File Name: PT100_Neg.c  
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
#include "PT100_Neg.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 PT100_Neg__PORT == 15 && ((PT100_Neg__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: PT100_Neg_Write
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
void PT100_Neg_Write(uint8 value) 
{
    uint8 staticBits = (PT100_Neg_DR & (uint8)(~PT100_Neg_MASK));
    PT100_Neg_DR = staticBits | ((uint8)(value << PT100_Neg_SHIFT) & PT100_Neg_MASK);
}


/*******************************************************************************
* Function Name: PT100_Neg_SetDriveMode
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
void PT100_Neg_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PT100_Neg_0, mode);
}


/*******************************************************************************
* Function Name: PT100_Neg_Read
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
*  Macro PT100_Neg_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PT100_Neg_Read(void) 
{
    return (PT100_Neg_PS & PT100_Neg_MASK) >> PT100_Neg_SHIFT;
}


/*******************************************************************************
* Function Name: PT100_Neg_ReadDataReg
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
uint8 PT100_Neg_ReadDataReg(void) 
{
    return (PT100_Neg_DR & PT100_Neg_MASK) >> PT100_Neg_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PT100_Neg_INTSTAT) 

    /*******************************************************************************
    * Function Name: PT100_Neg_ClearInterrupt
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
    uint8 PT100_Neg_ClearInterrupt(void) 
    {
        return (PT100_Neg_INTSTAT & PT100_Neg_MASK) >> PT100_Neg_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
