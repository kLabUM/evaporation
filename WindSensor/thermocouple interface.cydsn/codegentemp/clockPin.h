/*******************************************************************************
* File Name: clockPin.h  
* Version 2.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_clockPin_H) /* Pins clockPin_H */
#define CY_PINS_clockPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "clockPin_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 clockPin__PORT == 15 && ((clockPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    clockPin_Write(uint8 value) ;
void    clockPin_SetDriveMode(uint8 mode) ;
uint8   clockPin_ReadDataReg(void) ;
uint8   clockPin_Read(void) ;
uint8   clockPin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define clockPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define clockPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define clockPin_DM_RES_UP          PIN_DM_RES_UP
#define clockPin_DM_RES_DWN         PIN_DM_RES_DWN
#define clockPin_DM_OD_LO           PIN_DM_OD_LO
#define clockPin_DM_OD_HI           PIN_DM_OD_HI
#define clockPin_DM_STRONG          PIN_DM_STRONG
#define clockPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define clockPin_MASK               clockPin__MASK
#define clockPin_SHIFT              clockPin__SHIFT
#define clockPin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define clockPin_PS                     (* (reg8 *) clockPin__PS)
/* Data Register */
#define clockPin_DR                     (* (reg8 *) clockPin__DR)
/* Port Number */
#define clockPin_PRT_NUM                (* (reg8 *) clockPin__PRT) 
/* Connect to Analog Globals */                                                  
#define clockPin_AG                     (* (reg8 *) clockPin__AG)                       
/* Analog MUX bux enable */
#define clockPin_AMUX                   (* (reg8 *) clockPin__AMUX) 
/* Bidirectional Enable */                                                        
#define clockPin_BIE                    (* (reg8 *) clockPin__BIE)
/* Bit-mask for Aliased Register Access */
#define clockPin_BIT_MASK               (* (reg8 *) clockPin__BIT_MASK)
/* Bypass Enable */
#define clockPin_BYP                    (* (reg8 *) clockPin__BYP)
/* Port wide control signals */                                                   
#define clockPin_CTL                    (* (reg8 *) clockPin__CTL)
/* Drive Modes */
#define clockPin_DM0                    (* (reg8 *) clockPin__DM0) 
#define clockPin_DM1                    (* (reg8 *) clockPin__DM1)
#define clockPin_DM2                    (* (reg8 *) clockPin__DM2) 
/* Input Buffer Disable Override */
#define clockPin_INP_DIS                (* (reg8 *) clockPin__INP_DIS)
/* LCD Common or Segment Drive */
#define clockPin_LCD_COM_SEG            (* (reg8 *) clockPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define clockPin_LCD_EN                 (* (reg8 *) clockPin__LCD_EN)
/* Slew Rate Control */
#define clockPin_SLW                    (* (reg8 *) clockPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define clockPin_PRTDSI__CAPS_SEL       (* (reg8 *) clockPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define clockPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) clockPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define clockPin_PRTDSI__OE_SEL0        (* (reg8 *) clockPin__PRTDSI__OE_SEL0) 
#define clockPin_PRTDSI__OE_SEL1        (* (reg8 *) clockPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define clockPin_PRTDSI__OUT_SEL0       (* (reg8 *) clockPin__PRTDSI__OUT_SEL0) 
#define clockPin_PRTDSI__OUT_SEL1       (* (reg8 *) clockPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define clockPin_PRTDSI__SYNC_OUT       (* (reg8 *) clockPin__PRTDSI__SYNC_OUT) 


#if defined(clockPin__INTSTAT)  /* Interrupt Registers */

    #define clockPin_INTSTAT                (* (reg8 *) clockPin__INTSTAT)
    #define clockPin_SNAP                   (* (reg8 *) clockPin__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_clockPin_H */


/* [] END OF FILE */
