/*******************************************************************************
* File Name: master.h
* Version 2.40
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the SPI Master Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_master_H)
#define CY_SPIM_master_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component SPI_Master_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define master_INTERNAL_CLOCK             (0u)

#if(0u != master_INTERNAL_CLOCK)
    #include "master_IntClock.h"
#endif /* (0u != master_INTERNAL_CLOCK) */

#define master_MODE                       (1u)
#define master_DATA_WIDTH                 (14u)
#define master_MODE_USE_ZERO              (1u)
#define master_BIDIRECTIONAL_MODE         (0u)

/* Internal interrupt handling */
#define master_TX_BUFFER_SIZE             (4u)
#define master_RX_BUFFER_SIZE             (4u)
#define master_INTERNAL_TX_INT_ENABLED    (0u)
#define master_INTERNAL_RX_INT_ENABLED    (0u)

#define master_SINGLE_REG_SIZE            (8u)
#define master_USE_SECOND_DATAPATH        (master_DATA_WIDTH > master_SINGLE_REG_SIZE)

#define master_FIFO_SIZE                  (4u)
#define master_TX_SOFTWARE_BUF_ENABLED    ((0u != master_INTERNAL_TX_INT_ENABLED) && \
                                                     (master_TX_BUFFER_SIZE > master_FIFO_SIZE))

#define master_RX_SOFTWARE_BUF_ENABLED    ((0u != master_INTERNAL_RX_INT_ENABLED) && \
                                                     (master_RX_BUFFER_SIZE > master_FIFO_SIZE))


/***************************************
*        Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 cntrPeriod;
    #if(CY_UDB_V0)
        uint16 saveSrTxIntMask;
        uint16 saveSrRxIntMask;
    #endif /* (CY_UDB_V0) */

} master_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  master_Init(void)                           ;
void  master_Enable(void)                         ;
void  master_Start(void)                          ;
void  master_Stop(void)                           ;

void  master_EnableTxInt(void)                    ;
void  master_EnableRxInt(void)                    ;
void  master_DisableTxInt(void)                   ;
void  master_DisableRxInt(void)                   ;

void  master_Sleep(void)                          ;
void  master_Wakeup(void)                         ;
void  master_SaveConfig(void)                     ;
void  master_RestoreConfig(void)                  ;

void  master_SetTxInterruptMode(uint8 intSrc)     ;
void  master_SetRxInterruptMode(uint8 intSrc)     ;
uint8 master_ReadTxStatus(void)                   ;
uint8 master_ReadRxStatus(void)                   ;
void  master_WriteTxData(uint16 txData)  \
                                                            ;
uint16 master_ReadRxData(void) \
                                                            ;
uint8 master_GetRxBufferSize(void)                ;
uint8 master_GetTxBufferSize(void)                ;
void  master_ClearRxBuffer(void)                  ;
void  master_ClearTxBuffer(void)                  ;
void  master_ClearFIFO(void)                              ;
void  master_PutArray(const uint16 buffer[], uint8 byteCount) \
                                                            ;

#if(0u != master_BIDIRECTIONAL_MODE)
    void  master_TxEnable(void)                   ;
    void  master_TxDisable(void)                  ;
#endif /* (0u != master_BIDIRECTIONAL_MODE) */

CY_ISR_PROTO(master_TX_ISR);
CY_ISR_PROTO(master_RX_ISR);


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 master_initVar;


/***************************************
*           API Constants
***************************************/

#define master_TX_ISR_NUMBER     ((uint8) (master_TxInternalInterrupt__INTC_NUMBER))
#define master_RX_ISR_NUMBER     ((uint8) (master_RxInternalInterrupt__INTC_NUMBER))

#define master_TX_ISR_PRIORITY   ((uint8) (master_TxInternalInterrupt__INTC_PRIOR_NUM))
#define master_RX_ISR_PRIORITY   ((uint8) (master_RxInternalInterrupt__INTC_PRIOR_NUM))


/***************************************
*    Initial Parameter Constants
***************************************/

#define master_INT_ON_SPI_DONE    ((uint8) (0u   << master_STS_SPI_DONE_SHIFT))
#define master_INT_ON_TX_EMPTY    ((uint8) (0u   << master_STS_TX_FIFO_EMPTY_SHIFT))
#define master_INT_ON_TX_NOT_FULL ((uint8) (0u << \
                                                                           master_STS_TX_FIFO_NOT_FULL_SHIFT))
#define master_INT_ON_BYTE_COMP   ((uint8) (0u  << master_STS_BYTE_COMPLETE_SHIFT))
#define master_INT_ON_SPI_IDLE    ((uint8) (0u   << master_STS_SPI_IDLE_SHIFT))

/* Disable TX_NOT_FULL if software buffer is used */
#define master_INT_ON_TX_NOT_FULL_DEF ((master_TX_SOFTWARE_BUF_ENABLED) ? \
                                                                        (0u) : (master_INT_ON_TX_NOT_FULL))

/* TX interrupt mask */
#define master_TX_INIT_INTERRUPTS_MASK    (master_INT_ON_SPI_DONE  | \
                                                     master_INT_ON_TX_EMPTY  | \
                                                     master_INT_ON_TX_NOT_FULL_DEF | \
                                                     master_INT_ON_BYTE_COMP | \
                                                     master_INT_ON_SPI_IDLE)

#define master_INT_ON_RX_FULL         ((uint8) (0u << \
                                                                          master_STS_RX_FIFO_FULL_SHIFT))
#define master_INT_ON_RX_NOT_EMPTY    ((uint8) (0u << \
                                                                          master_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define master_INT_ON_RX_OVER         ((uint8) (0u << \
                                                                          master_STS_RX_FIFO_OVERRUN_SHIFT))

/* RX interrupt mask */
#define master_RX_INIT_INTERRUPTS_MASK    (master_INT_ON_RX_FULL      | \
                                                     master_INT_ON_RX_NOT_EMPTY | \
                                                     master_INT_ON_RX_OVER)
/* Nubmer of bits to receive/transmit */
#define master_BITCTR_INIT            (((uint8) (master_DATA_WIDTH << 1u)) - 1u)


/***************************************
*             Registers
***************************************/

#if(CY_PSOC3 || CY_PSOC5)
    #define master_TXDATA_REG (* (reg16 *) \
                                                master_BSPIM_sR16_Dp_u0__F0_REG)
    #define master_TXDATA_PTR (  (reg16 *) \
                                                master_BSPIM_sR16_Dp_u0__F0_REG)
    #define master_RXDATA_REG (* (reg16 *) \
                                                master_BSPIM_sR16_Dp_u0__F1_REG)
    #define master_RXDATA_PTR (  (reg16 *) \
                                                master_BSPIM_sR16_Dp_u0__F1_REG)
#else   /* PSOC4 */
    #if(master_USE_SECOND_DATAPATH)
        #define master_TXDATA_REG (* (reg16 *) \
                                          master_BSPIM_sR16_Dp_u0__16BIT_F0_REG)
        #define master_TXDATA_PTR (  (reg16 *) \
                                          master_BSPIM_sR16_Dp_u0__16BIT_F0_REG)
        #define master_RXDATA_REG (* (reg16 *) \
                                          master_BSPIM_sR16_Dp_u0__16BIT_F1_REG)
        #define master_RXDATA_PTR         (  (reg16 *) \
                                          master_BSPIM_sR16_Dp_u0__16BIT_F1_REG)
    #else
        #define master_TXDATA_REG (* (reg8 *) \
                                                master_BSPIM_sR16_Dp_u0__F0_REG)
        #define master_TXDATA_PTR (  (reg8 *) \
                                                master_BSPIM_sR16_Dp_u0__F0_REG)
        #define master_RXDATA_REG (* (reg8 *) \
                                                master_BSPIM_sR16_Dp_u0__F1_REG)
        #define master_RXDATA_PTR (  (reg8 *) \
                                                master_BSPIM_sR16_Dp_u0__F1_REG)
    #endif /* (master_USE_SECOND_DATAPATH) */
#endif     /* (CY_PSOC3 || CY_PSOC5) */

#define master_AUX_CONTROL_DP0_REG (* (reg8 *) \
                                        master_BSPIM_sR16_Dp_u0__DP_AUX_CTL_REG)
#define master_AUX_CONTROL_DP0_PTR (  (reg8 *) \
                                        master_BSPIM_sR16_Dp_u0__DP_AUX_CTL_REG)

#if(master_USE_SECOND_DATAPATH)
    #define master_AUX_CONTROL_DP1_REG  (* (reg8 *) \
                                        master_BSPIM_sR16_Dp_u1__DP_AUX_CTL_REG)
    #define master_AUX_CONTROL_DP1_PTR  (  (reg8 *) \
                                        master_BSPIM_sR16_Dp_u1__DP_AUX_CTL_REG)
#endif /* (master_USE_SECOND_DATAPATH) */

#define master_COUNTER_PERIOD_REG     (* (reg8 *) master_BSPIM_BitCounter__PERIOD_REG)
#define master_COUNTER_PERIOD_PTR     (  (reg8 *) master_BSPIM_BitCounter__PERIOD_REG)
#define master_COUNTER_CONTROL_REG    (* (reg8 *) master_BSPIM_BitCounter__CONTROL_AUX_CTL_REG)
#define master_COUNTER_CONTROL_PTR    (  (reg8 *) master_BSPIM_BitCounter__CONTROL_AUX_CTL_REG)

#define master_TX_STATUS_REG          (* (reg8 *) master_BSPIM_TxStsReg__STATUS_REG)
#define master_TX_STATUS_PTR          (  (reg8 *) master_BSPIM_TxStsReg__STATUS_REG)
#define master_RX_STATUS_REG          (* (reg8 *) master_BSPIM_RxStsReg__STATUS_REG)
#define master_RX_STATUS_PTR          (  (reg8 *) master_BSPIM_RxStsReg__STATUS_REG)

#define master_CONTROL_REG            (* (reg8 *) \
                                      master_BSPIM_BidirMode_SyncCtl_CtrlReg__CONTROL_REG)
#define master_CONTROL_PTR            (  (reg8 *) \
                                      master_BSPIM_BidirMode_SyncCtl_CtrlReg__CONTROL_REG)

#define master_TX_STATUS_MASK_REG     (* (reg8 *) master_BSPIM_TxStsReg__MASK_REG)
#define master_TX_STATUS_MASK_PTR     (  (reg8 *) master_BSPIM_TxStsReg__MASK_REG)
#define master_RX_STATUS_MASK_REG     (* (reg8 *) master_BSPIM_RxStsReg__MASK_REG)
#define master_RX_STATUS_MASK_PTR     (  (reg8 *) master_BSPIM_RxStsReg__MASK_REG)

#define master_TX_STATUS_ACTL_REG     (* (reg8 *) master_BSPIM_TxStsReg__STATUS_AUX_CTL_REG)
#define master_TX_STATUS_ACTL_PTR     (  (reg8 *) master_BSPIM_TxStsReg__STATUS_AUX_CTL_REG)
#define master_RX_STATUS_ACTL_REG     (* (reg8 *) master_BSPIM_RxStsReg__STATUS_AUX_CTL_REG)
#define master_RX_STATUS_ACTL_PTR     (  (reg8 *) master_BSPIM_RxStsReg__STATUS_AUX_CTL_REG)

#if(master_USE_SECOND_DATAPATH)
    #define master_AUX_CONTROLDP1     (master_AUX_CONTROL_DP1_REG)
#endif /* (master_USE_SECOND_DATAPATH) */


/***************************************
*       Register Constants
***************************************/

/* Status Register Definitions */
#define master_STS_SPI_DONE_SHIFT             (0x00u)
#define master_STS_TX_FIFO_EMPTY_SHIFT        (0x01u)
#define master_STS_TX_FIFO_NOT_FULL_SHIFT     (0x02u)
#define master_STS_BYTE_COMPLETE_SHIFT        (0x03u)
#define master_STS_SPI_IDLE_SHIFT             (0x04u)
#define master_STS_RX_FIFO_FULL_SHIFT         (0x04u)
#define master_STS_RX_FIFO_NOT_EMPTY_SHIFT    (0x05u)
#define master_STS_RX_FIFO_OVERRUN_SHIFT      (0x06u)

#define master_STS_SPI_DONE           ((uint8) (0x01u << master_STS_SPI_DONE_SHIFT))
#define master_STS_TX_FIFO_EMPTY      ((uint8) (0x01u << master_STS_TX_FIFO_EMPTY_SHIFT))
#define master_STS_TX_FIFO_NOT_FULL   ((uint8) (0x01u << master_STS_TX_FIFO_NOT_FULL_SHIFT))
#define master_STS_BYTE_COMPLETE      ((uint8) (0x01u << master_STS_BYTE_COMPLETE_SHIFT))
#define master_STS_SPI_IDLE           ((uint8) (0x01u << master_STS_SPI_IDLE_SHIFT))
#define master_STS_RX_FIFO_FULL       ((uint8) (0x01u << master_STS_RX_FIFO_FULL_SHIFT))
#define master_STS_RX_FIFO_NOT_EMPTY  ((uint8) (0x01u << master_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define master_STS_RX_FIFO_OVERRUN    ((uint8) (0x01u << master_STS_RX_FIFO_OVERRUN_SHIFT))

/* TX and RX masks for clear on read bits */
#define master_TX_STS_CLR_ON_RD_BYTES_MASK    (0x09u)
#define master_RX_STS_CLR_ON_RD_BYTES_MASK    (0x40u)

/* StatusI Register Interrupt Enable Control Bits */
/* As defined by the Register map for the AUX Control Register */
#define master_INT_ENABLE     (0x10u) /* Enable interrupt from statusi */
#define master_TX_FIFO_CLR    (0x01u) /* F0 - TX FIFO */
#define master_RX_FIFO_CLR    (0x02u) /* F1 - RX FIFO */
#define master_FIFO_CLR       (master_TX_FIFO_CLR | master_RX_FIFO_CLR)

/* Bit Counter (7-bit) Control Register Bit Definitions */
/* As defined by the Register map for the AUX Control Register */
#define master_CNTR_ENABLE    (0x20u) /* Enable CNT7 */

/* Bi-Directional mode control bit */
#define master_CTRL_TX_SIGNAL_EN  (0x01u)

/* Datapath Auxillary Control Register definitions */
#define master_AUX_CTRL_FIFO0_CLR         (0x01u)
#define master_AUX_CTRL_FIFO1_CLR         (0x02u)
#define master_AUX_CTRL_FIFO0_LVL         (0x04u)
#define master_AUX_CTRL_FIFO1_LVL         (0x08u)
#define master_STATUS_ACTL_INT_EN_MASK    (0x10u)

/* Component disabled */
#define master_DISABLED   (0u)


/***************************************
*       Macros
***************************************/

/* Returns true if componentn enabled */
#define master_IS_ENABLED (0u != (master_TX_STATUS_ACTL_REG & master_INT_ENABLE))

/* Retuns TX status register */
#define master_GET_STATUS_TX(swTxSts) ( (uint8)(master_TX_STATUS_REG | \
                                                          ((swTxSts) & master_TX_STS_CLR_ON_RD_BYTES_MASK)) )
/* Retuns RX status register */
#define master_GET_STATUS_RX(swRxSts) ( (uint8)(master_RX_STATUS_REG | \
                                                          ((swRxSts) & master_RX_STS_CLR_ON_RD_BYTES_MASK)) )


/***************************************
*       Obsolete definitions
***************************************/

/* Following definitions are for version compatibility.
*  They are obsolete in SPIM v2_30.
*  Please do not use it in new projects
*/

#define master_WriteByte   master_WriteTxData
#define master_ReadByte    master_ReadRxData
void  master_SetInterruptMode(uint8 intSrc)       ;
uint8 master_ReadStatus(void)                     ;
void  master_EnableInt(void)                      ;
void  master_DisableInt(void)                     ;

/* Obsolete register names. Not to be used in new designs */
#define master_TXDATA                 (master_TXDATA_REG)
#define master_RXDATA                 (master_RXDATA_REG)
#define master_AUX_CONTROLDP0         (master_AUX_CONTROL_DP0_REG)
#define master_TXBUFFERREAD           (master_txBufferRead)
#define master_TXBUFFERWRITE          (master_txBufferWrite)
#define master_RXBUFFERREAD           (master_rxBufferRead)
#define master_RXBUFFERWRITE          (master_rxBufferWrite)

#define master_COUNTER_PERIOD         (master_COUNTER_PERIOD_REG)
#define master_COUNTER_CONTROL        (master_COUNTER_CONTROL_REG)
#define master_STATUS                 (master_TX_STATUS_REG)
#define master_CONTROL                (master_CONTROL_REG)
#define master_STATUS_MASK            (master_TX_STATUS_MASK_REG)
#define master_STATUS_ACTL            (master_TX_STATUS_ACTL_REG)

#define master_INIT_INTERRUPTS_MASK  (master_INT_ON_SPI_DONE     | \
                                                master_INT_ON_TX_EMPTY     | \
                                                master_INT_ON_TX_NOT_FULL_DEF  | \
                                                master_INT_ON_RX_FULL      | \
                                                master_INT_ON_RX_NOT_EMPTY | \
                                                master_INT_ON_RX_OVER      | \
                                                master_INT_ON_BYTE_COMP)
                                                
/* Following definitions are for version Compatibility.
*  They are obsolete in SPIM v2_40.
*  Please do not use it in new projects
*/

#define master_DataWidth                  (master_DATA_WIDTH)
#define master_InternalClockUsed          (master_INTERNAL_CLOCK)
#define master_InternalTxInterruptEnabled (master_INTERNAL_TX_INT_ENABLED)
#define master_InternalRxInterruptEnabled (master_INTERNAL_RX_INT_ENABLED)
#define master_ModeUseZero                (master_MODE_USE_ZERO)
#define master_BidirectionalMode          (master_BIDIRECTIONAL_MODE)
#define master_Mode                       (master_MODE)
#define master_DATAWIDHT                  (master_DATA_WIDTH)
#define master_InternalInterruptEnabled   (0u)

#define master_TXBUFFERSIZE   (master_TX_BUFFER_SIZE)
#define master_RXBUFFERSIZE   (master_RX_BUFFER_SIZE)

#define master_TXBUFFER       master_txBuffer
#define master_RXBUFFER       master_rxBuffer

#endif /* (CY_SPIM_master_H) */


/* [] END OF FILE */
