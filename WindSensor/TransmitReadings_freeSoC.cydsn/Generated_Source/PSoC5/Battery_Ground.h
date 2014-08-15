/*******************************************************************************
* File Name: Battery_Ground.h  
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

#if !defined(CY_PINS_Battery_Ground_H) /* Pins Battery_Ground_H */
#define CY_PINS_Battery_Ground_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Battery_Ground_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Battery_Ground__PORT == 15 && ((Battery_Ground__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Battery_Ground_Write(uint8 value) ;
void    Battery_Ground_SetDriveMode(uint8 mode) ;
uint8   Battery_Ground_ReadDataReg(void) ;
uint8   Battery_Ground_Read(void) ;
uint8   Battery_Ground_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Battery_Ground_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Battery_Ground_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Battery_Ground_DM_RES_UP          PIN_DM_RES_UP
#define Battery_Ground_DM_RES_DWN         PIN_DM_RES_DWN
#define Battery_Ground_DM_OD_LO           PIN_DM_OD_LO
#define Battery_Ground_DM_OD_HI           PIN_DM_OD_HI
#define Battery_Ground_DM_STRONG          PIN_DM_STRONG
#define Battery_Ground_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Battery_Ground_MASK               Battery_Ground__MASK
#define Battery_Ground_SHIFT              Battery_Ground__SHIFT
#define Battery_Ground_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Battery_Ground_PS                     (* (reg8 *) Battery_Ground__PS)
/* Data Register */
#define Battery_Ground_DR                     (* (reg8 *) Battery_Ground__DR)
/* Port Number */
#define Battery_Ground_PRT_NUM                (* (reg8 *) Battery_Ground__PRT) 
/* Connect to Analog Globals */                                                  
#define Battery_Ground_AG                     (* (reg8 *) Battery_Ground__AG)                       
/* Analog MUX bux enable */
#define Battery_Ground_AMUX                   (* (reg8 *) Battery_Ground__AMUX) 
/* Bidirectional Enable */                                                        
#define Battery_Ground_BIE                    (* (reg8 *) Battery_Ground__BIE)
/* Bit-mask for Aliased Register Access */
#define Battery_Ground_BIT_MASK               (* (reg8 *) Battery_Ground__BIT_MASK)
/* Bypass Enable */
#define Battery_Ground_BYP                    (* (reg8 *) Battery_Ground__BYP)
/* Port wide control signals */                                                   
#define Battery_Ground_CTL                    (* (reg8 *) Battery_Ground__CTL)
/* Drive Modes */
#define Battery_Ground_DM0                    (* (reg8 *) Battery_Ground__DM0) 
#define Battery_Ground_DM1                    (* (reg8 *) Battery_Ground__DM1)
#define Battery_Ground_DM2                    (* (reg8 *) Battery_Ground__DM2) 
/* Input Buffer Disable Override */
#define Battery_Ground_INP_DIS                (* (reg8 *) Battery_Ground__INP_DIS)
/* LCD Common or Segment Drive */
#define Battery_Ground_LCD_COM_SEG            (* (reg8 *) Battery_Ground__LCD_COM_SEG)
/* Enable Segment LCD */
#define Battery_Ground_LCD_EN                 (* (reg8 *) Battery_Ground__LCD_EN)
/* Slew Rate Control */
#define Battery_Ground_SLW                    (* (reg8 *) Battery_Ground__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Battery_Ground_PRTDSI__CAPS_SEL       (* (reg8 *) Battery_Ground__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Battery_Ground_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Battery_Ground__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Battery_Ground_PRTDSI__OE_SEL0        (* (reg8 *) Battery_Ground__PRTDSI__OE_SEL0) 
#define Battery_Ground_PRTDSI__OE_SEL1        (* (reg8 *) Battery_Ground__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Battery_Ground_PRTDSI__OUT_SEL0       (* (reg8 *) Battery_Ground__PRTDSI__OUT_SEL0) 
#define Battery_Ground_PRTDSI__OUT_SEL1       (* (reg8 *) Battery_Ground__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Battery_Ground_PRTDSI__SYNC_OUT       (* (reg8 *) Battery_Ground__PRTDSI__SYNC_OUT) 


#if defined(Battery_Ground__INTSTAT)  /* Interrupt Registers */

    #define Battery_Ground_INTSTAT                (* (reg8 *) Battery_Ground__INTSTAT)
    #define Battery_Ground_SNAP                   (* (reg8 *) Battery_Ground__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Battery_Ground_H */


/* [] END OF FILE */
