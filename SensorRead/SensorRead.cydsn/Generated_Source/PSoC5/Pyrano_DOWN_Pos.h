/*******************************************************************************
* File Name: Pyrano_DOWN_Pos.h  
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

#if !defined(CY_PINS_Pyrano_DOWN_Pos_H) /* Pins Pyrano_DOWN_Pos_H */
#define CY_PINS_Pyrano_DOWN_Pos_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pyrano_DOWN_Pos_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pyrano_DOWN_Pos__PORT == 15 && ((Pyrano_DOWN_Pos__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pyrano_DOWN_Pos_Write(uint8 value) ;
void    Pyrano_DOWN_Pos_SetDriveMode(uint8 mode) ;
uint8   Pyrano_DOWN_Pos_ReadDataReg(void) ;
uint8   Pyrano_DOWN_Pos_Read(void) ;
uint8   Pyrano_DOWN_Pos_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pyrano_DOWN_Pos_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pyrano_DOWN_Pos_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pyrano_DOWN_Pos_DM_RES_UP          PIN_DM_RES_UP
#define Pyrano_DOWN_Pos_DM_RES_DWN         PIN_DM_RES_DWN
#define Pyrano_DOWN_Pos_DM_OD_LO           PIN_DM_OD_LO
#define Pyrano_DOWN_Pos_DM_OD_HI           PIN_DM_OD_HI
#define Pyrano_DOWN_Pos_DM_STRONG          PIN_DM_STRONG
#define Pyrano_DOWN_Pos_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pyrano_DOWN_Pos_MASK               Pyrano_DOWN_Pos__MASK
#define Pyrano_DOWN_Pos_SHIFT              Pyrano_DOWN_Pos__SHIFT
#define Pyrano_DOWN_Pos_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pyrano_DOWN_Pos_PS                     (* (reg8 *) Pyrano_DOWN_Pos__PS)
/* Data Register */
#define Pyrano_DOWN_Pos_DR                     (* (reg8 *) Pyrano_DOWN_Pos__DR)
/* Port Number */
#define Pyrano_DOWN_Pos_PRT_NUM                (* (reg8 *) Pyrano_DOWN_Pos__PRT) 
/* Connect to Analog Globals */                                                  
#define Pyrano_DOWN_Pos_AG                     (* (reg8 *) Pyrano_DOWN_Pos__AG)                       
/* Analog MUX bux enable */
#define Pyrano_DOWN_Pos_AMUX                   (* (reg8 *) Pyrano_DOWN_Pos__AMUX) 
/* Bidirectional Enable */                                                        
#define Pyrano_DOWN_Pos_BIE                    (* (reg8 *) Pyrano_DOWN_Pos__BIE)
/* Bit-mask for Aliased Register Access */
#define Pyrano_DOWN_Pos_BIT_MASK               (* (reg8 *) Pyrano_DOWN_Pos__BIT_MASK)
/* Bypass Enable */
#define Pyrano_DOWN_Pos_BYP                    (* (reg8 *) Pyrano_DOWN_Pos__BYP)
/* Port wide control signals */                                                   
#define Pyrano_DOWN_Pos_CTL                    (* (reg8 *) Pyrano_DOWN_Pos__CTL)
/* Drive Modes */
#define Pyrano_DOWN_Pos_DM0                    (* (reg8 *) Pyrano_DOWN_Pos__DM0) 
#define Pyrano_DOWN_Pos_DM1                    (* (reg8 *) Pyrano_DOWN_Pos__DM1)
#define Pyrano_DOWN_Pos_DM2                    (* (reg8 *) Pyrano_DOWN_Pos__DM2) 
/* Input Buffer Disable Override */
#define Pyrano_DOWN_Pos_INP_DIS                (* (reg8 *) Pyrano_DOWN_Pos__INP_DIS)
/* LCD Common or Segment Drive */
#define Pyrano_DOWN_Pos_LCD_COM_SEG            (* (reg8 *) Pyrano_DOWN_Pos__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pyrano_DOWN_Pos_LCD_EN                 (* (reg8 *) Pyrano_DOWN_Pos__LCD_EN)
/* Slew Rate Control */
#define Pyrano_DOWN_Pos_SLW                    (* (reg8 *) Pyrano_DOWN_Pos__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pyrano_DOWN_Pos_PRTDSI__CAPS_SEL       (* (reg8 *) Pyrano_DOWN_Pos__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pyrano_DOWN_Pos_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pyrano_DOWN_Pos__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pyrano_DOWN_Pos_PRTDSI__OE_SEL0        (* (reg8 *) Pyrano_DOWN_Pos__PRTDSI__OE_SEL0) 
#define Pyrano_DOWN_Pos_PRTDSI__OE_SEL1        (* (reg8 *) Pyrano_DOWN_Pos__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pyrano_DOWN_Pos_PRTDSI__OUT_SEL0       (* (reg8 *) Pyrano_DOWN_Pos__PRTDSI__OUT_SEL0) 
#define Pyrano_DOWN_Pos_PRTDSI__OUT_SEL1       (* (reg8 *) Pyrano_DOWN_Pos__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pyrano_DOWN_Pos_PRTDSI__SYNC_OUT       (* (reg8 *) Pyrano_DOWN_Pos__PRTDSI__SYNC_OUT) 


#if defined(Pyrano_DOWN_Pos__INTSTAT)  /* Interrupt Registers */

    #define Pyrano_DOWN_Pos_INTSTAT                (* (reg8 *) Pyrano_DOWN_Pos__INTSTAT)
    #define Pyrano_DOWN_Pos_SNAP                   (* (reg8 *) Pyrano_DOWN_Pos__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pyrano_DOWN_Pos_H */


/* [] END OF FILE */
