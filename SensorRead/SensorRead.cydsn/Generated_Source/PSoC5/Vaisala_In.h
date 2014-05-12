/*******************************************************************************
* File Name: Vaisala_In.h  
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

#if !defined(CY_PINS_Vaisala_In_H) /* Pins Vaisala_In_H */
#define CY_PINS_Vaisala_In_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vaisala_In_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vaisala_In__PORT == 15 && ((Vaisala_In__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Vaisala_In_Write(uint8 value) ;
void    Vaisala_In_SetDriveMode(uint8 mode) ;
uint8   Vaisala_In_ReadDataReg(void) ;
uint8   Vaisala_In_Read(void) ;
uint8   Vaisala_In_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Vaisala_In_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Vaisala_In_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Vaisala_In_DM_RES_UP          PIN_DM_RES_UP
#define Vaisala_In_DM_RES_DWN         PIN_DM_RES_DWN
#define Vaisala_In_DM_OD_LO           PIN_DM_OD_LO
#define Vaisala_In_DM_OD_HI           PIN_DM_OD_HI
#define Vaisala_In_DM_STRONG          PIN_DM_STRONG
#define Vaisala_In_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Vaisala_In_MASK               Vaisala_In__MASK
#define Vaisala_In_SHIFT              Vaisala_In__SHIFT
#define Vaisala_In_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vaisala_In_PS                     (* (reg8 *) Vaisala_In__PS)
/* Data Register */
#define Vaisala_In_DR                     (* (reg8 *) Vaisala_In__DR)
/* Port Number */
#define Vaisala_In_PRT_NUM                (* (reg8 *) Vaisala_In__PRT) 
/* Connect to Analog Globals */                                                  
#define Vaisala_In_AG                     (* (reg8 *) Vaisala_In__AG)                       
/* Analog MUX bux enable */
#define Vaisala_In_AMUX                   (* (reg8 *) Vaisala_In__AMUX) 
/* Bidirectional Enable */                                                        
#define Vaisala_In_BIE                    (* (reg8 *) Vaisala_In__BIE)
/* Bit-mask for Aliased Register Access */
#define Vaisala_In_BIT_MASK               (* (reg8 *) Vaisala_In__BIT_MASK)
/* Bypass Enable */
#define Vaisala_In_BYP                    (* (reg8 *) Vaisala_In__BYP)
/* Port wide control signals */                                                   
#define Vaisala_In_CTL                    (* (reg8 *) Vaisala_In__CTL)
/* Drive Modes */
#define Vaisala_In_DM0                    (* (reg8 *) Vaisala_In__DM0) 
#define Vaisala_In_DM1                    (* (reg8 *) Vaisala_In__DM1)
#define Vaisala_In_DM2                    (* (reg8 *) Vaisala_In__DM2) 
/* Input Buffer Disable Override */
#define Vaisala_In_INP_DIS                (* (reg8 *) Vaisala_In__INP_DIS)
/* LCD Common or Segment Drive */
#define Vaisala_In_LCD_COM_SEG            (* (reg8 *) Vaisala_In__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vaisala_In_LCD_EN                 (* (reg8 *) Vaisala_In__LCD_EN)
/* Slew Rate Control */
#define Vaisala_In_SLW                    (* (reg8 *) Vaisala_In__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vaisala_In_PRTDSI__CAPS_SEL       (* (reg8 *) Vaisala_In__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vaisala_In_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vaisala_In__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vaisala_In_PRTDSI__OE_SEL0        (* (reg8 *) Vaisala_In__PRTDSI__OE_SEL0) 
#define Vaisala_In_PRTDSI__OE_SEL1        (* (reg8 *) Vaisala_In__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vaisala_In_PRTDSI__OUT_SEL0       (* (reg8 *) Vaisala_In__PRTDSI__OUT_SEL0) 
#define Vaisala_In_PRTDSI__OUT_SEL1       (* (reg8 *) Vaisala_In__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vaisala_In_PRTDSI__SYNC_OUT       (* (reg8 *) Vaisala_In__PRTDSI__SYNC_OUT) 


#if defined(Vaisala_In__INTSTAT)  /* Interrupt Registers */

    #define Vaisala_In_INTSTAT                (* (reg8 *) Vaisala_In__INTSTAT)
    #define Vaisala_In_SNAP                   (* (reg8 *) Vaisala_In__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vaisala_In_H */


/* [] END OF FILE */
