/*******************************************************************************
* File Name: SW_In_Pos.c  
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
#include "SW_In_Pos.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 SW_In_Pos__PORT == 15 && ((SW_In_Pos__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: SW_In_Pos_Write
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
void SW_In_Pos_Write(uint8 value) 
{
    uint8 staticBits = (SW_In_Pos_DR & (uint8)(~SW_In_Pos_MASK));
    SW_In_Pos_DR = staticBits | ((uint8)(value << SW_In_Pos_SHIFT) & SW_In_Pos_MASK);
}


/*******************************************************************************
* Function Name: SW_In_Pos_SetDriveMode
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
void SW_In_Pos_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(SW_In_Pos_0, mode);
}


/*******************************************************************************
* Function Name: SW_In_Pos_Read
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
*  Macro SW_In_Pos_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SW_In_Pos_Read(void) 
{
    return (SW_In_Pos_PS & SW_In_Pos_MASK) >> SW_In_Pos_SHIFT;
}


/*******************************************************************************
* Function Name: SW_In_Pos_ReadDataReg
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
uint8 SW_In_Pos_ReadDataReg(void) 
{
    return (SW_In_Pos_DR & SW_In_Pos_MASK) >> SW_In_Pos_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SW_In_Pos_INTSTAT) 

    /*******************************************************************************
    * Function Name: SW_In_Pos_ClearInterrupt
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
    uint8 SW_In_Pos_ClearInterrupt(void) 
    {
        return (SW_In_Pos_INTSTAT & SW_In_Pos_MASK) >> SW_In_Pos_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
