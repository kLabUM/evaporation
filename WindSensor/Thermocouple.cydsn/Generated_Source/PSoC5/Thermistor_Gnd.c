/*******************************************************************************
* File Name: Thermistor_Gnd.c  
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
#include "Thermistor_Gnd.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Thermistor_Gnd__PORT == 15 && ((Thermistor_Gnd__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Thermistor_Gnd_Write
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
void Thermistor_Gnd_Write(uint8 value) 
{
    uint8 staticBits = (Thermistor_Gnd_DR & (uint8)(~Thermistor_Gnd_MASK));
    Thermistor_Gnd_DR = staticBits | ((uint8)(value << Thermistor_Gnd_SHIFT) & Thermistor_Gnd_MASK);
}


/*******************************************************************************
* Function Name: Thermistor_Gnd_SetDriveMode
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
void Thermistor_Gnd_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Thermistor_Gnd_0, mode);
}


/*******************************************************************************
* Function Name: Thermistor_Gnd_Read
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
*  Macro Thermistor_Gnd_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Thermistor_Gnd_Read(void) 
{
    return (Thermistor_Gnd_PS & Thermistor_Gnd_MASK) >> Thermistor_Gnd_SHIFT;
}


/*******************************************************************************
* Function Name: Thermistor_Gnd_ReadDataReg
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
uint8 Thermistor_Gnd_ReadDataReg(void) 
{
    return (Thermistor_Gnd_DR & Thermistor_Gnd_MASK) >> Thermistor_Gnd_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Thermistor_Gnd_INTSTAT) 

    /*******************************************************************************
    * Function Name: Thermistor_Gnd_ClearInterrupt
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
    uint8 Thermistor_Gnd_ClearInterrupt(void) 
    {
        return (Thermistor_Gnd_INTSTAT & Thermistor_Gnd_MASK) >> Thermistor_Gnd_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
