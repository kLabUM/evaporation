/*******************************************************************************
* File Name: SBD_reply.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_SBD_reply_H)
#define CY_ISR_SBD_reply_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void SBD_reply_Start(void);
void SBD_reply_StartEx(cyisraddress address);
void SBD_reply_Stop(void);

CY_ISR_PROTO(SBD_reply_Interrupt);

void SBD_reply_SetVector(cyisraddress address);
cyisraddress SBD_reply_GetVector(void);

void SBD_reply_SetPriority(uint8 priority);
uint8 SBD_reply_GetPriority(void);

void SBD_reply_Enable(void);
uint8 SBD_reply_GetState(void);
void SBD_reply_Disable(void);

void SBD_reply_SetPending(void);
void SBD_reply_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the SBD_reply ISR. */
#define SBD_reply_INTC_VECTOR            ((reg32 *) SBD_reply__INTC_VECT)

/* Address of the SBD_reply ISR priority. */
#define SBD_reply_INTC_PRIOR             ((reg8 *) SBD_reply__INTC_PRIOR_REG)

/* Priority of the SBD_reply interrupt. */
#define SBD_reply_INTC_PRIOR_NUMBER      SBD_reply__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable SBD_reply interrupt. */
#define SBD_reply_INTC_SET_EN            ((reg32 *) SBD_reply__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the SBD_reply interrupt. */
#define SBD_reply_INTC_CLR_EN            ((reg32 *) SBD_reply__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the SBD_reply interrupt state to pending. */
#define SBD_reply_INTC_SET_PD            ((reg32 *) SBD_reply__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the SBD_reply interrupt. */
#define SBD_reply_INTC_CLR_PD            ((reg32 *) SBD_reply__INTC_CLR_PD_REG)


#endif /* CY_ISR_SBD_reply_H */


/* [] END OF FILE */
