/*******************************************************************************
* File Name: Thermocouple_Pos.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Thermocouple_Pos_H) /* Pins Thermocouple_Pos_H */
#define CY_PINS_Thermocouple_Pos_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Thermocouple_Pos_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Thermocouple_Pos__PORT == 15 && ((Thermocouple_Pos__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Thermocouple_Pos_Write(uint8 value) ;
void    Thermocouple_Pos_SetDriveMode(uint8 mode) ;
uint8   Thermocouple_Pos_ReadDataReg(void) ;
uint8   Thermocouple_Pos_Read(void) ;
uint8   Thermocouple_Pos_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Thermocouple_Pos_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Thermocouple_Pos_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Thermocouple_Pos_DM_RES_UP          PIN_DM_RES_UP
#define Thermocouple_Pos_DM_RES_DWN         PIN_DM_RES_DWN
#define Thermocouple_Pos_DM_OD_LO           PIN_DM_OD_LO
#define Thermocouple_Pos_DM_OD_HI           PIN_DM_OD_HI
#define Thermocouple_Pos_DM_STRONG          PIN_DM_STRONG
#define Thermocouple_Pos_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Thermocouple_Pos_MASK               Thermocouple_Pos__MASK
#define Thermocouple_Pos_SHIFT              Thermocouple_Pos__SHIFT
#define Thermocouple_Pos_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Thermocouple_Pos_PS                     (* (reg8 *) Thermocouple_Pos__PS)
/* Data Register */
#define Thermocouple_Pos_DR                     (* (reg8 *) Thermocouple_Pos__DR)
/* Port Number */
#define Thermocouple_Pos_PRT_NUM                (* (reg8 *) Thermocouple_Pos__PRT) 
/* Connect to Analog Globals */                                                  
#define Thermocouple_Pos_AG                     (* (reg8 *) Thermocouple_Pos__AG)                       
/* Analog MUX bux enable */
#define Thermocouple_Pos_AMUX                   (* (reg8 *) Thermocouple_Pos__AMUX) 
/* Bidirectional Enable */                                                        
#define Thermocouple_Pos_BIE                    (* (reg8 *) Thermocouple_Pos__BIE)
/* Bit-mask for Aliased Register Access */
#define Thermocouple_Pos_BIT_MASK               (* (reg8 *) Thermocouple_Pos__BIT_MASK)
/* Bypass Enable */
#define Thermocouple_Pos_BYP                    (* (reg8 *) Thermocouple_Pos__BYP)
/* Port wide control signals */                                                   
#define Thermocouple_Pos_CTL                    (* (reg8 *) Thermocouple_Pos__CTL)
/* Drive Modes */
#define Thermocouple_Pos_DM0                    (* (reg8 *) Thermocouple_Pos__DM0) 
#define Thermocouple_Pos_DM1                    (* (reg8 *) Thermocouple_Pos__DM1)
#define Thermocouple_Pos_DM2                    (* (reg8 *) Thermocouple_Pos__DM2) 
/* Input Buffer Disable Override */
#define Thermocouple_Pos_INP_DIS                (* (reg8 *) Thermocouple_Pos__INP_DIS)
/* LCD Common or Segment Drive */
#define Thermocouple_Pos_LCD_COM_SEG            (* (reg8 *) Thermocouple_Pos__LCD_COM_SEG)
/* Enable Segment LCD */
#define Thermocouple_Pos_LCD_EN                 (* (reg8 *) Thermocouple_Pos__LCD_EN)
/* Slew Rate Control */
#define Thermocouple_Pos_SLW                    (* (reg8 *) Thermocouple_Pos__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Thermocouple_Pos_PRTDSI__CAPS_SEL       (* (reg8 *) Thermocouple_Pos__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Thermocouple_Pos_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Thermocouple_Pos__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Thermocouple_Pos_PRTDSI__OE_SEL0        (* (reg8 *) Thermocouple_Pos__PRTDSI__OE_SEL0) 
#define Thermocouple_Pos_PRTDSI__OE_SEL1        (* (reg8 *) Thermocouple_Pos__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Thermocouple_Pos_PRTDSI__OUT_SEL0       (* (reg8 *) Thermocouple_Pos__PRTDSI__OUT_SEL0) 
#define Thermocouple_Pos_PRTDSI__OUT_SEL1       (* (reg8 *) Thermocouple_Pos__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Thermocouple_Pos_PRTDSI__SYNC_OUT       (* (reg8 *) Thermocouple_Pos__PRTDSI__SYNC_OUT) 


#if defined(Thermocouple_Pos__INTSTAT)  /* Interrupt Registers */

    #define Thermocouple_Pos_INTSTAT                (* (reg8 *) Thermocouple_Pos__INTSTAT)
    #define Thermocouple_Pos_SNAP                   (* (reg8 *) Thermocouple_Pos__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Thermocouple_Pos_H */


/* [] END OF FILE */
