/*******************************************************************************
* File Name: Vaisala_RH.h  
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

#if !defined(CY_PINS_Vaisala_RH_H) /* Pins Vaisala_RH_H */
#define CY_PINS_Vaisala_RH_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vaisala_RH_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vaisala_RH__PORT == 15 && ((Vaisala_RH__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Vaisala_RH_Write(uint8 value) ;
void    Vaisala_RH_SetDriveMode(uint8 mode) ;
uint8   Vaisala_RH_ReadDataReg(void) ;
uint8   Vaisala_RH_Read(void) ;
uint8   Vaisala_RH_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Vaisala_RH_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Vaisala_RH_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Vaisala_RH_DM_RES_UP          PIN_DM_RES_UP
#define Vaisala_RH_DM_RES_DWN         PIN_DM_RES_DWN
#define Vaisala_RH_DM_OD_LO           PIN_DM_OD_LO
#define Vaisala_RH_DM_OD_HI           PIN_DM_OD_HI
#define Vaisala_RH_DM_STRONG          PIN_DM_STRONG
#define Vaisala_RH_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Vaisala_RH_MASK               Vaisala_RH__MASK
#define Vaisala_RH_SHIFT              Vaisala_RH__SHIFT
#define Vaisala_RH_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vaisala_RH_PS                     (* (reg8 *) Vaisala_RH__PS)
/* Data Register */
#define Vaisala_RH_DR                     (* (reg8 *) Vaisala_RH__DR)
/* Port Number */
#define Vaisala_RH_PRT_NUM                (* (reg8 *) Vaisala_RH__PRT) 
/* Connect to Analog Globals */                                                  
#define Vaisala_RH_AG                     (* (reg8 *) Vaisala_RH__AG)                       
/* Analog MUX bux enable */
#define Vaisala_RH_AMUX                   (* (reg8 *) Vaisala_RH__AMUX) 
/* Bidirectional Enable */                                                        
#define Vaisala_RH_BIE                    (* (reg8 *) Vaisala_RH__BIE)
/* Bit-mask for Aliased Register Access */
#define Vaisala_RH_BIT_MASK               (* (reg8 *) Vaisala_RH__BIT_MASK)
/* Bypass Enable */
#define Vaisala_RH_BYP                    (* (reg8 *) Vaisala_RH__BYP)
/* Port wide control signals */                                                   
#define Vaisala_RH_CTL                    (* (reg8 *) Vaisala_RH__CTL)
/* Drive Modes */
#define Vaisala_RH_DM0                    (* (reg8 *) Vaisala_RH__DM0) 
#define Vaisala_RH_DM1                    (* (reg8 *) Vaisala_RH__DM1)
#define Vaisala_RH_DM2                    (* (reg8 *) Vaisala_RH__DM2) 
/* Input Buffer Disable Override */
#define Vaisala_RH_INP_DIS                (* (reg8 *) Vaisala_RH__INP_DIS)
/* LCD Common or Segment Drive */
#define Vaisala_RH_LCD_COM_SEG            (* (reg8 *) Vaisala_RH__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vaisala_RH_LCD_EN                 (* (reg8 *) Vaisala_RH__LCD_EN)
/* Slew Rate Control */
#define Vaisala_RH_SLW                    (* (reg8 *) Vaisala_RH__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vaisala_RH_PRTDSI__CAPS_SEL       (* (reg8 *) Vaisala_RH__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vaisala_RH_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vaisala_RH__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vaisala_RH_PRTDSI__OE_SEL0        (* (reg8 *) Vaisala_RH__PRTDSI__OE_SEL0) 
#define Vaisala_RH_PRTDSI__OE_SEL1        (* (reg8 *) Vaisala_RH__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vaisala_RH_PRTDSI__OUT_SEL0       (* (reg8 *) Vaisala_RH__PRTDSI__OUT_SEL0) 
#define Vaisala_RH_PRTDSI__OUT_SEL1       (* (reg8 *) Vaisala_RH__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vaisala_RH_PRTDSI__SYNC_OUT       (* (reg8 *) Vaisala_RH__PRTDSI__SYNC_OUT) 


#if defined(Vaisala_RH__INTSTAT)  /* Interrupt Registers */

    #define Vaisala_RH_INTSTAT                (* (reg8 *) Vaisala_RH__INTSTAT)
    #define Vaisala_RH_SNAP                   (* (reg8 *) Vaisala_RH__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vaisala_RH_H */


/* [] END OF FILE */
