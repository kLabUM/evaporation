/*******************************************************************************
* File Name: Pyrgeo_DOWN_Neg.h  
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

#if !defined(CY_PINS_Pyrgeo_DOWN_Neg_H) /* Pins Pyrgeo_DOWN_Neg_H */
#define CY_PINS_Pyrgeo_DOWN_Neg_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pyrgeo_DOWN_Neg_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pyrgeo_DOWN_Neg__PORT == 15 && ((Pyrgeo_DOWN_Neg__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pyrgeo_DOWN_Neg_Write(uint8 value) ;
void    Pyrgeo_DOWN_Neg_SetDriveMode(uint8 mode) ;
uint8   Pyrgeo_DOWN_Neg_ReadDataReg(void) ;
uint8   Pyrgeo_DOWN_Neg_Read(void) ;
uint8   Pyrgeo_DOWN_Neg_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pyrgeo_DOWN_Neg_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pyrgeo_DOWN_Neg_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pyrgeo_DOWN_Neg_DM_RES_UP          PIN_DM_RES_UP
#define Pyrgeo_DOWN_Neg_DM_RES_DWN         PIN_DM_RES_DWN
#define Pyrgeo_DOWN_Neg_DM_OD_LO           PIN_DM_OD_LO
#define Pyrgeo_DOWN_Neg_DM_OD_HI           PIN_DM_OD_HI
#define Pyrgeo_DOWN_Neg_DM_STRONG          PIN_DM_STRONG
#define Pyrgeo_DOWN_Neg_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pyrgeo_DOWN_Neg_MASK               Pyrgeo_DOWN_Neg__MASK
#define Pyrgeo_DOWN_Neg_SHIFT              Pyrgeo_DOWN_Neg__SHIFT
#define Pyrgeo_DOWN_Neg_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pyrgeo_DOWN_Neg_PS                     (* (reg8 *) Pyrgeo_DOWN_Neg__PS)
/* Data Register */
#define Pyrgeo_DOWN_Neg_DR                     (* (reg8 *) Pyrgeo_DOWN_Neg__DR)
/* Port Number */
#define Pyrgeo_DOWN_Neg_PRT_NUM                (* (reg8 *) Pyrgeo_DOWN_Neg__PRT) 
/* Connect to Analog Globals */                                                  
#define Pyrgeo_DOWN_Neg_AG                     (* (reg8 *) Pyrgeo_DOWN_Neg__AG)                       
/* Analog MUX bux enable */
#define Pyrgeo_DOWN_Neg_AMUX                   (* (reg8 *) Pyrgeo_DOWN_Neg__AMUX) 
/* Bidirectional Enable */                                                        
#define Pyrgeo_DOWN_Neg_BIE                    (* (reg8 *) Pyrgeo_DOWN_Neg__BIE)
/* Bit-mask for Aliased Register Access */
#define Pyrgeo_DOWN_Neg_BIT_MASK               (* (reg8 *) Pyrgeo_DOWN_Neg__BIT_MASK)
/* Bypass Enable */
#define Pyrgeo_DOWN_Neg_BYP                    (* (reg8 *) Pyrgeo_DOWN_Neg__BYP)
/* Port wide control signals */                                                   
#define Pyrgeo_DOWN_Neg_CTL                    (* (reg8 *) Pyrgeo_DOWN_Neg__CTL)
/* Drive Modes */
#define Pyrgeo_DOWN_Neg_DM0                    (* (reg8 *) Pyrgeo_DOWN_Neg__DM0) 
#define Pyrgeo_DOWN_Neg_DM1                    (* (reg8 *) Pyrgeo_DOWN_Neg__DM1)
#define Pyrgeo_DOWN_Neg_DM2                    (* (reg8 *) Pyrgeo_DOWN_Neg__DM2) 
/* Input Buffer Disable Override */
#define Pyrgeo_DOWN_Neg_INP_DIS                (* (reg8 *) Pyrgeo_DOWN_Neg__INP_DIS)
/* LCD Common or Segment Drive */
#define Pyrgeo_DOWN_Neg_LCD_COM_SEG            (* (reg8 *) Pyrgeo_DOWN_Neg__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pyrgeo_DOWN_Neg_LCD_EN                 (* (reg8 *) Pyrgeo_DOWN_Neg__LCD_EN)
/* Slew Rate Control */
#define Pyrgeo_DOWN_Neg_SLW                    (* (reg8 *) Pyrgeo_DOWN_Neg__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pyrgeo_DOWN_Neg_PRTDSI__CAPS_SEL       (* (reg8 *) Pyrgeo_DOWN_Neg__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pyrgeo_DOWN_Neg_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pyrgeo_DOWN_Neg__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pyrgeo_DOWN_Neg_PRTDSI__OE_SEL0        (* (reg8 *) Pyrgeo_DOWN_Neg__PRTDSI__OE_SEL0) 
#define Pyrgeo_DOWN_Neg_PRTDSI__OE_SEL1        (* (reg8 *) Pyrgeo_DOWN_Neg__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pyrgeo_DOWN_Neg_PRTDSI__OUT_SEL0       (* (reg8 *) Pyrgeo_DOWN_Neg__PRTDSI__OUT_SEL0) 
#define Pyrgeo_DOWN_Neg_PRTDSI__OUT_SEL1       (* (reg8 *) Pyrgeo_DOWN_Neg__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pyrgeo_DOWN_Neg_PRTDSI__SYNC_OUT       (* (reg8 *) Pyrgeo_DOWN_Neg__PRTDSI__SYNC_OUT) 


#if defined(Pyrgeo_DOWN_Neg__INTSTAT)  /* Interrupt Registers */

    #define Pyrgeo_DOWN_Neg_INTSTAT                (* (reg8 *) Pyrgeo_DOWN_Neg__INTSTAT)
    #define Pyrgeo_DOWN_Neg_SNAP                   (* (reg8 *) Pyrgeo_DOWN_Neg__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pyrgeo_DOWN_Neg_H */


/* [] END OF FILE */
