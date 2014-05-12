/*******************************************************************************
* File Name: SW_In_Pos.h  
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

#if !defined(CY_PINS_SW_In_Pos_H) /* Pins SW_In_Pos_H */
#define CY_PINS_SW_In_Pos_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SW_In_Pos_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SW_In_Pos__PORT == 15 && ((SW_In_Pos__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    SW_In_Pos_Write(uint8 value) ;
void    SW_In_Pos_SetDriveMode(uint8 mode) ;
uint8   SW_In_Pos_ReadDataReg(void) ;
uint8   SW_In_Pos_Read(void) ;
uint8   SW_In_Pos_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SW_In_Pos_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SW_In_Pos_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SW_In_Pos_DM_RES_UP          PIN_DM_RES_UP
#define SW_In_Pos_DM_RES_DWN         PIN_DM_RES_DWN
#define SW_In_Pos_DM_OD_LO           PIN_DM_OD_LO
#define SW_In_Pos_DM_OD_HI           PIN_DM_OD_HI
#define SW_In_Pos_DM_STRONG          PIN_DM_STRONG
#define SW_In_Pos_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SW_In_Pos_MASK               SW_In_Pos__MASK
#define SW_In_Pos_SHIFT              SW_In_Pos__SHIFT
#define SW_In_Pos_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SW_In_Pos_PS                     (* (reg8 *) SW_In_Pos__PS)
/* Data Register */
#define SW_In_Pos_DR                     (* (reg8 *) SW_In_Pos__DR)
/* Port Number */
#define SW_In_Pos_PRT_NUM                (* (reg8 *) SW_In_Pos__PRT) 
/* Connect to Analog Globals */                                                  
#define SW_In_Pos_AG                     (* (reg8 *) SW_In_Pos__AG)                       
/* Analog MUX bux enable */
#define SW_In_Pos_AMUX                   (* (reg8 *) SW_In_Pos__AMUX) 
/* Bidirectional Enable */                                                        
#define SW_In_Pos_BIE                    (* (reg8 *) SW_In_Pos__BIE)
/* Bit-mask for Aliased Register Access */
#define SW_In_Pos_BIT_MASK               (* (reg8 *) SW_In_Pos__BIT_MASK)
/* Bypass Enable */
#define SW_In_Pos_BYP                    (* (reg8 *) SW_In_Pos__BYP)
/* Port wide control signals */                                                   
#define SW_In_Pos_CTL                    (* (reg8 *) SW_In_Pos__CTL)
/* Drive Modes */
#define SW_In_Pos_DM0                    (* (reg8 *) SW_In_Pos__DM0) 
#define SW_In_Pos_DM1                    (* (reg8 *) SW_In_Pos__DM1)
#define SW_In_Pos_DM2                    (* (reg8 *) SW_In_Pos__DM2) 
/* Input Buffer Disable Override */
#define SW_In_Pos_INP_DIS                (* (reg8 *) SW_In_Pos__INP_DIS)
/* LCD Common or Segment Drive */
#define SW_In_Pos_LCD_COM_SEG            (* (reg8 *) SW_In_Pos__LCD_COM_SEG)
/* Enable Segment LCD */
#define SW_In_Pos_LCD_EN                 (* (reg8 *) SW_In_Pos__LCD_EN)
/* Slew Rate Control */
#define SW_In_Pos_SLW                    (* (reg8 *) SW_In_Pos__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SW_In_Pos_PRTDSI__CAPS_SEL       (* (reg8 *) SW_In_Pos__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SW_In_Pos_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SW_In_Pos__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SW_In_Pos_PRTDSI__OE_SEL0        (* (reg8 *) SW_In_Pos__PRTDSI__OE_SEL0) 
#define SW_In_Pos_PRTDSI__OE_SEL1        (* (reg8 *) SW_In_Pos__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SW_In_Pos_PRTDSI__OUT_SEL0       (* (reg8 *) SW_In_Pos__PRTDSI__OUT_SEL0) 
#define SW_In_Pos_PRTDSI__OUT_SEL1       (* (reg8 *) SW_In_Pos__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SW_In_Pos_PRTDSI__SYNC_OUT       (* (reg8 *) SW_In_Pos__PRTDSI__SYNC_OUT) 


#if defined(SW_In_Pos__INTSTAT)  /* Interrupt Registers */

    #define SW_In_Pos_INTSTAT                (* (reg8 *) SW_In_Pos__INTSTAT)
    #define SW_In_Pos_SNAP                   (* (reg8 *) SW_In_Pos__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SW_In_Pos_H */


/* [] END OF FILE */
