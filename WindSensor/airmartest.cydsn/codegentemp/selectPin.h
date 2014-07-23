/*******************************************************************************
* File Name: selectPin.h  
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

#if !defined(CY_PINS_selectPin_H) /* Pins selectPin_H */
#define CY_PINS_selectPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "selectPin_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 selectPin__PORT == 15 && ((selectPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    selectPin_Write(uint8 value) ;
void    selectPin_SetDriveMode(uint8 mode) ;
uint8   selectPin_ReadDataReg(void) ;
uint8   selectPin_Read(void) ;
uint8   selectPin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define selectPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define selectPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define selectPin_DM_RES_UP          PIN_DM_RES_UP
#define selectPin_DM_RES_DWN         PIN_DM_RES_DWN
#define selectPin_DM_OD_LO           PIN_DM_OD_LO
#define selectPin_DM_OD_HI           PIN_DM_OD_HI
#define selectPin_DM_STRONG          PIN_DM_STRONG
#define selectPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define selectPin_MASK               selectPin__MASK
#define selectPin_SHIFT              selectPin__SHIFT
#define selectPin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define selectPin_PS                     (* (reg8 *) selectPin__PS)
/* Data Register */
#define selectPin_DR                     (* (reg8 *) selectPin__DR)
/* Port Number */
#define selectPin_PRT_NUM                (* (reg8 *) selectPin__PRT) 
/* Connect to Analog Globals */                                                  
#define selectPin_AG                     (* (reg8 *) selectPin__AG)                       
/* Analog MUX bux enable */
#define selectPin_AMUX                   (* (reg8 *) selectPin__AMUX) 
/* Bidirectional Enable */                                                        
#define selectPin_BIE                    (* (reg8 *) selectPin__BIE)
/* Bit-mask for Aliased Register Access */
#define selectPin_BIT_MASK               (* (reg8 *) selectPin__BIT_MASK)
/* Bypass Enable */
#define selectPin_BYP                    (* (reg8 *) selectPin__BYP)
/* Port wide control signals */                                                   
#define selectPin_CTL                    (* (reg8 *) selectPin__CTL)
/* Drive Modes */
#define selectPin_DM0                    (* (reg8 *) selectPin__DM0) 
#define selectPin_DM1                    (* (reg8 *) selectPin__DM1)
#define selectPin_DM2                    (* (reg8 *) selectPin__DM2) 
/* Input Buffer Disable Override */
#define selectPin_INP_DIS                (* (reg8 *) selectPin__INP_DIS)
/* LCD Common or Segment Drive */
#define selectPin_LCD_COM_SEG            (* (reg8 *) selectPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define selectPin_LCD_EN                 (* (reg8 *) selectPin__LCD_EN)
/* Slew Rate Control */
#define selectPin_SLW                    (* (reg8 *) selectPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define selectPin_PRTDSI__CAPS_SEL       (* (reg8 *) selectPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define selectPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) selectPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define selectPin_PRTDSI__OE_SEL0        (* (reg8 *) selectPin__PRTDSI__OE_SEL0) 
#define selectPin_PRTDSI__OE_SEL1        (* (reg8 *) selectPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define selectPin_PRTDSI__OUT_SEL0       (* (reg8 *) selectPin__PRTDSI__OUT_SEL0) 
#define selectPin_PRTDSI__OUT_SEL1       (* (reg8 *) selectPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define selectPin_PRTDSI__SYNC_OUT       (* (reg8 *) selectPin__PRTDSI__SYNC_OUT) 


#if defined(selectPin__INTSTAT)  /* Interrupt Registers */

    #define selectPin_INTSTAT                (* (reg8 *) selectPin__INTSTAT)
    #define selectPin_SNAP                   (* (reg8 *) selectPin__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_selectPin_H */


/* [] END OF FILE */
