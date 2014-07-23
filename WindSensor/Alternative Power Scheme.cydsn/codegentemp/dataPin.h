/*******************************************************************************
* File Name: dataPin.h  
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

#if !defined(CY_PINS_dataPin_H) /* Pins dataPin_H */
#define CY_PINS_dataPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "dataPin_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 dataPin__PORT == 15 && ((dataPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    dataPin_Write(uint8 value) ;
void    dataPin_SetDriveMode(uint8 mode) ;
uint8   dataPin_ReadDataReg(void) ;
uint8   dataPin_Read(void) ;
uint8   dataPin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define dataPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define dataPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define dataPin_DM_RES_UP          PIN_DM_RES_UP
#define dataPin_DM_RES_DWN         PIN_DM_RES_DWN
#define dataPin_DM_OD_LO           PIN_DM_OD_LO
#define dataPin_DM_OD_HI           PIN_DM_OD_HI
#define dataPin_DM_STRONG          PIN_DM_STRONG
#define dataPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define dataPin_MASK               dataPin__MASK
#define dataPin_SHIFT              dataPin__SHIFT
#define dataPin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define dataPin_PS                     (* (reg8 *) dataPin__PS)
/* Data Register */
#define dataPin_DR                     (* (reg8 *) dataPin__DR)
/* Port Number */
#define dataPin_PRT_NUM                (* (reg8 *) dataPin__PRT) 
/* Connect to Analog Globals */                                                  
#define dataPin_AG                     (* (reg8 *) dataPin__AG)                       
/* Analog MUX bux enable */
#define dataPin_AMUX                   (* (reg8 *) dataPin__AMUX) 
/* Bidirectional Enable */                                                        
#define dataPin_BIE                    (* (reg8 *) dataPin__BIE)
/* Bit-mask for Aliased Register Access */
#define dataPin_BIT_MASK               (* (reg8 *) dataPin__BIT_MASK)
/* Bypass Enable */
#define dataPin_BYP                    (* (reg8 *) dataPin__BYP)
/* Port wide control signals */                                                   
#define dataPin_CTL                    (* (reg8 *) dataPin__CTL)
/* Drive Modes */
#define dataPin_DM0                    (* (reg8 *) dataPin__DM0) 
#define dataPin_DM1                    (* (reg8 *) dataPin__DM1)
#define dataPin_DM2                    (* (reg8 *) dataPin__DM2) 
/* Input Buffer Disable Override */
#define dataPin_INP_DIS                (* (reg8 *) dataPin__INP_DIS)
/* LCD Common or Segment Drive */
#define dataPin_LCD_COM_SEG            (* (reg8 *) dataPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define dataPin_LCD_EN                 (* (reg8 *) dataPin__LCD_EN)
/* Slew Rate Control */
#define dataPin_SLW                    (* (reg8 *) dataPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define dataPin_PRTDSI__CAPS_SEL       (* (reg8 *) dataPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define dataPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) dataPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define dataPin_PRTDSI__OE_SEL0        (* (reg8 *) dataPin__PRTDSI__OE_SEL0) 
#define dataPin_PRTDSI__OE_SEL1        (* (reg8 *) dataPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define dataPin_PRTDSI__OUT_SEL0       (* (reg8 *) dataPin__PRTDSI__OUT_SEL0) 
#define dataPin_PRTDSI__OUT_SEL1       (* (reg8 *) dataPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define dataPin_PRTDSI__SYNC_OUT       (* (reg8 *) dataPin__PRTDSI__SYNC_OUT) 


#if defined(dataPin__INTSTAT)  /* Interrupt Registers */

    #define dataPin_INTSTAT                (* (reg8 *) dataPin__INTSTAT)
    #define dataPin_SNAP                   (* (reg8 *) dataPin__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_dataPin_H */


/* [] END OF FILE */
