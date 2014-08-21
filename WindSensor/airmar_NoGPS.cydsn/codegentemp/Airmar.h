/*******************************************************************************
* File Name: Airmar.h
* Version 2.30
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_Airmar_H)
#define CY_UART_Airmar_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define Airmar_RX_ENABLED                     (1u)
#define Airmar_TX_ENABLED                     (1u)
#define Airmar_HD_ENABLED                     (0u)
#define Airmar_RX_INTERRUPT_ENABLED           (0u)
#define Airmar_TX_INTERRUPT_ENABLED           (0u)
#define Airmar_INTERNAL_CLOCK_USED            (1u)
#define Airmar_RXHW_ADDRESS_ENABLED           (0u)
#define Airmar_OVER_SAMPLE_COUNT              (8u)
#define Airmar_PARITY_TYPE                    (0u)
#define Airmar_PARITY_TYPE_SW                 (0u)
#define Airmar_BREAK_DETECT                   (0u)
#define Airmar_BREAK_BITS_TX                  (13u)
#define Airmar_BREAK_BITS_RX                  (13u)
#define Airmar_TXCLKGEN_DP                    (1u)
#define Airmar_USE23POLLING                   (1u)
#define Airmar_FLOW_CONTROL                   (0u)
#define Airmar_CLK_FREQ                       (0u)
#define Airmar_TXBUFFERSIZE                   (4u)
#define Airmar_RXBUFFERSIZE                   (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#ifdef Airmar_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Airmar_CONTROL_REG_REMOVED            (0u)
#else
    #define Airmar_CONTROL_REG_REMOVED            (1u)
#endif /* End Airmar_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct Airmar_backupStruct_
{
    uint8 enableState;

    #if(Airmar_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End Airmar_CONTROL_REG_REMOVED */
    #if( (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) )
        uint8 rx_period;
        #if (CY_UDB_V0)
            uint8 rx_mask;
            #if (Airmar_RXHW_ADDRESS_ENABLED)
                uint8 rx_addr1;
                uint8 rx_addr2;
            #endif /* End Airmar_RXHW_ADDRESS_ENABLED */
        #endif /* End CY_UDB_V0 */
    #endif  /* End (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED)*/

    #if(Airmar_TX_ENABLED)
        #if(Airmar_TXCLKGEN_DP)
            uint8 tx_clk_ctr;
            #if (CY_UDB_V0)
                uint8 tx_clk_compl;
            #endif  /* End CY_UDB_V0 */
        #else
            uint8 tx_period;
        #endif /*End Airmar_TXCLKGEN_DP */
        #if (CY_UDB_V0)
            uint8 tx_mask;
        #endif  /* End CY_UDB_V0 */
    #endif /*End Airmar_TX_ENABLED */
} Airmar_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void Airmar_Start(void) ;
void Airmar_Stop(void) ;
uint8 Airmar_ReadControlRegister(void) ;
void Airmar_WriteControlRegister(uint8 control) ;

void Airmar_Init(void) ;
void Airmar_Enable(void) ;
void Airmar_SaveConfig(void) ;
void Airmar_RestoreConfig(void) ;
void Airmar_Sleep(void) ;
void Airmar_Wakeup(void) ;

/* Only if RX is enabled */
#if( (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) )

    #if(Airmar_RX_INTERRUPT_ENABLED)
        void  Airmar_EnableRxInt(void) ;
        void  Airmar_DisableRxInt(void) ;
        CY_ISR_PROTO(Airmar_RXISR);
    #endif /* Airmar_RX_INTERRUPT_ENABLED */

    void Airmar_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void Airmar_SetRxAddress1(uint8 address) ;
    void Airmar_SetRxAddress2(uint8 address) ;

    void  Airmar_SetRxInterruptMode(uint8 intSrc) ;
    uint8 Airmar_ReadRxData(void) ;
    uint8 Airmar_ReadRxStatus(void) ;
    uint8 Airmar_GetChar(void) ;
    uint16 Airmar_GetByte(void) ;
    uint8 Airmar_GetRxBufferSize(void)
                                                            ;
    void Airmar_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define Airmar_GetRxInterruptSource   Airmar_ReadRxStatus

#endif /* End (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) */

/* Only if TX is enabled */
#if(Airmar_TX_ENABLED || Airmar_HD_ENABLED)

    #if(Airmar_TX_INTERRUPT_ENABLED)
        void Airmar_EnableTxInt(void) ;
        void Airmar_DisableTxInt(void) ;
        CY_ISR_PROTO(Airmar_TXISR);
    #endif /* Airmar_TX_INTERRUPT_ENABLED */

    void Airmar_SetTxInterruptMode(uint8 intSrc) ;
    void Airmar_WriteTxData(uint8 txDataByte) ;
    uint8 Airmar_ReadTxStatus(void) ;
    void Airmar_PutChar(uint8 txDataByte) ;
    void Airmar_PutString(const char8 string[]) ;
    void Airmar_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void Airmar_PutCRLF(uint8 txDataByte) ;
    void Airmar_ClearTxBuffer(void) ;
    void Airmar_SetTxAddressMode(uint8 addressMode) ;
    void Airmar_SendBreak(uint8 retMode) ;
    uint8 Airmar_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define Airmar_PutStringConst         Airmar_PutString
    #define Airmar_PutArrayConst          Airmar_PutArray
    #define Airmar_GetTxInterruptSource   Airmar_ReadTxStatus

#endif /* End Airmar_TX_ENABLED || Airmar_HD_ENABLED */

#if(Airmar_HD_ENABLED)
    void Airmar_LoadRxConfig(void) ;
    void Airmar_LoadTxConfig(void) ;
#endif /* End Airmar_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Airmar) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    Airmar_CyBtldrCommStart(void) CYSMALL ;
    void    Airmar_CyBtldrCommStop(void) CYSMALL ;
    void    Airmar_CyBtldrCommReset(void) CYSMALL ;
    cystatus Airmar_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus Airmar_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Airmar)
        #define CyBtldrCommStart    Airmar_CyBtldrCommStart
        #define CyBtldrCommStop     Airmar_CyBtldrCommStop
        #define CyBtldrCommReset    Airmar_CyBtldrCommReset
        #define CyBtldrCommWrite    Airmar_CyBtldrCommWrite
        #define CyBtldrCommRead     Airmar_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Airmar) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define Airmar_BYTE2BYTE_TIME_OUT (25u)

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define Airmar_SET_SPACE                              (0x00u)
#define Airmar_SET_MARK                               (0x01u)

/* Status Register definitions */
#if( (Airmar_TX_ENABLED) || (Airmar_HD_ENABLED) )
    #if(Airmar_TX_INTERRUPT_ENABLED)
        #define Airmar_TX_VECT_NUM            (uint8)Airmar_TXInternalInterrupt__INTC_NUMBER
        #define Airmar_TX_PRIOR_NUM           (uint8)Airmar_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Airmar_TX_INTERRUPT_ENABLED */
    #if(Airmar_TX_ENABLED)
        #define Airmar_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define Airmar_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define Airmar_TX_STS_FIFO_FULL_SHIFT         (0x02u)
        #define Airmar_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* Airmar_TX_ENABLED */
    #if(Airmar_HD_ENABLED)
        #define Airmar_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define Airmar_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define Airmar_TX_STS_FIFO_FULL_SHIFT         (0x05u)  /*needs MD=0*/
        #define Airmar_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* Airmar_HD_ENABLED */
    #define Airmar_TX_STS_COMPLETE            (uint8)(0x01u << Airmar_TX_STS_COMPLETE_SHIFT)
    #define Airmar_TX_STS_FIFO_EMPTY          (uint8)(0x01u << Airmar_TX_STS_FIFO_EMPTY_SHIFT)
    #define Airmar_TX_STS_FIFO_FULL           (uint8)(0x01u << Airmar_TX_STS_FIFO_FULL_SHIFT)
    #define Airmar_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << Airmar_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (Airmar_TX_ENABLED) || (Airmar_HD_ENABLED)*/

#if( (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) )
    #if(Airmar_RX_INTERRUPT_ENABLED)
        #define Airmar_RX_VECT_NUM            (uint8)Airmar_RXInternalInterrupt__INTC_NUMBER
        #define Airmar_RX_PRIOR_NUM           (uint8)Airmar_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Airmar_RX_INTERRUPT_ENABLED */
    #define Airmar_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define Airmar_RX_STS_BREAK_SHIFT             (0x01u)
    #define Airmar_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define Airmar_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define Airmar_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define Airmar_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define Airmar_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define Airmar_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define Airmar_RX_STS_MRKSPC           (uint8)(0x01u << Airmar_RX_STS_MRKSPC_SHIFT)
    #define Airmar_RX_STS_BREAK            (uint8)(0x01u << Airmar_RX_STS_BREAK_SHIFT)
    #define Airmar_RX_STS_PAR_ERROR        (uint8)(0x01u << Airmar_RX_STS_PAR_ERROR_SHIFT)
    #define Airmar_RX_STS_STOP_ERROR       (uint8)(0x01u << Airmar_RX_STS_STOP_ERROR_SHIFT)
    #define Airmar_RX_STS_OVERRUN          (uint8)(0x01u << Airmar_RX_STS_OVERRUN_SHIFT)
    #define Airmar_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << Airmar_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define Airmar_RX_STS_ADDR_MATCH       (uint8)(0x01u << Airmar_RX_STS_ADDR_MATCH_SHIFT)
    #define Airmar_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << Airmar_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define Airmar_RX_HW_MASK                     (0x7Fu)
#endif /* End (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) */

/* Control Register definitions */
#define Airmar_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define Airmar_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define Airmar_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define Airmar_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define Airmar_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define Airmar_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define Airmar_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define Airmar_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define Airmar_CTRL_HD_SEND               (uint8)(0x01u << Airmar_CTRL_HD_SEND_SHIFT)
#define Airmar_CTRL_HD_SEND_BREAK         (uint8)(0x01u << Airmar_CTRL_HD_SEND_BREAK_SHIFT)
#define Airmar_CTRL_MARK                  (uint8)(0x01u << Airmar_CTRL_MARK_SHIFT)
#define Airmar_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << Airmar_CTRL_PARITY_TYPE0_SHIFT)
#define Airmar_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << Airmar_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define Airmar_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define Airmar_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define Airmar_SEND_BREAK                         (0x00u)
#define Airmar_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define Airmar_REINIT                             (0x02u)
#define Airmar_SEND_WAIT_REINIT                   (0x03u)

#define Airmar_OVER_SAMPLE_8                      (8u)
#define Airmar_OVER_SAMPLE_16                     (16u)

#define Airmar_BIT_CENTER                         (Airmar_OVER_SAMPLE_COUNT - 1u)

#define Airmar_FIFO_LENGTH                        (4u)
#define Airmar_NUMBER_OF_START_BIT                (1u)
#define Airmar_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation*/
#define Airmar_TXBITCTR_BREAKBITS8X   ((Airmar_BREAK_BITS_TX * Airmar_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation*/
#define Airmar_TXBITCTR_BREAKBITS ((Airmar_BREAK_BITS_TX * Airmar_OVER_SAMPLE_COUNT) - 1u)

#define Airmar_HALF_BIT_COUNT   \
                            (((Airmar_OVER_SAMPLE_COUNT / 2u) + (Airmar_USE23POLLING * 1u)) - 2u)
#if (Airmar_OVER_SAMPLE_COUNT == Airmar_OVER_SAMPLE_8)
    #define Airmar_HD_TXBITCTR_INIT   (((Airmar_BREAK_BITS_TX + \
                            Airmar_NUMBER_OF_START_BIT) * Airmar_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define Airmar_RXBITCTR_INIT  ((((Airmar_BREAK_BITS_RX + Airmar_NUMBER_OF_START_BIT) \
                            * Airmar_OVER_SAMPLE_COUNT) + Airmar_HALF_BIT_COUNT) - 1u)


#else /* Airmar_OVER_SAMPLE_COUNT == Airmar_OVER_SAMPLE_16 */
    #define Airmar_HD_TXBITCTR_INIT   ((8u * Airmar_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount=16 */
    #define Airmar_RXBITCTR_INIT      (((7u * Airmar_OVER_SAMPLE_COUNT) - 1u) + \
                                                      Airmar_HALF_BIT_COUNT)
#endif /* End Airmar_OVER_SAMPLE_COUNT */
#define Airmar_HD_RXBITCTR_INIT                   Airmar_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 Airmar_initVar;
#if( Airmar_TX_ENABLED && (Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH))
    extern volatile uint8 Airmar_txBuffer[Airmar_TXBUFFERSIZE];
    extern volatile uint8 Airmar_txBufferRead;
    extern uint8 Airmar_txBufferWrite;
#endif /* End Airmar_TX_ENABLED */
#if( ( Airmar_RX_ENABLED || Airmar_HD_ENABLED ) && \
     (Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH) )
    extern volatile uint8 Airmar_rxBuffer[Airmar_RXBUFFERSIZE];
    extern volatile uint8 Airmar_rxBufferRead;
    extern volatile uint8 Airmar_rxBufferWrite;
    extern volatile uint8 Airmar_rxBufferLoopDetect;
    extern volatile uint8 Airmar_rxBufferOverflow;
    #if (Airmar_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 Airmar_rxAddressMode;
        extern volatile uint8 Airmar_rxAddressDetected;
    #endif /* End EnableHWAddress */
#endif /* End Airmar_RX_ENABLED */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define Airmar__B_UART__AM_SW_BYTE_BYTE 1
#define Airmar__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define Airmar__B_UART__AM_HW_BYTE_BY_BYTE 3
#define Airmar__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define Airmar__B_UART__AM_NONE 0

#define Airmar__B_UART__NONE_REVB 0
#define Airmar__B_UART__EVEN_REVB 1
#define Airmar__B_UART__ODD_REVB 2
#define Airmar__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define Airmar_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define Airmar_NUMBER_OF_STOP_BITS    (1u)

#if (Airmar_RXHW_ADDRESS_ENABLED)
    #define Airmar_RXADDRESSMODE      (0u)
    #define Airmar_RXHWADDRESS1       (0u)
    #define Airmar_RXHWADDRESS2       (0u)
    /* Backward compatible define */
    #define Airmar_RXAddressMode      Airmar_RXADDRESSMODE
#endif /* End EnableHWAddress */

#define Airmar_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << Airmar_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << Airmar_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << Airmar_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << Airmar_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << Airmar_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << Airmar_RX_STS_BREAK_SHIFT) \
                                        | (0 << Airmar_RX_STS_OVERRUN_SHIFT))

#define Airmar_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << Airmar_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << Airmar_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << Airmar_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << Airmar_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef Airmar_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Airmar_CONTROL_REG \
                            (* (reg8 *) Airmar_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define Airmar_CONTROL_PTR \
                            (  (reg8 *) Airmar_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End Airmar_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Airmar_TX_ENABLED)
    #define Airmar_TXDATA_REG          (* (reg8 *) Airmar_BUART_sTX_TxShifter_u0__F0_REG)
    #define Airmar_TXDATA_PTR          (  (reg8 *) Airmar_BUART_sTX_TxShifter_u0__F0_REG)
    #define Airmar_TXDATA_AUX_CTL_REG  (* (reg8 *) Airmar_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Airmar_TXDATA_AUX_CTL_PTR  (  (reg8 *) Airmar_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Airmar_TXSTATUS_REG        (* (reg8 *) Airmar_BUART_sTX_TxSts__STATUS_REG)
    #define Airmar_TXSTATUS_PTR        (  (reg8 *) Airmar_BUART_sTX_TxSts__STATUS_REG)
    #define Airmar_TXSTATUS_MASK_REG   (* (reg8 *) Airmar_BUART_sTX_TxSts__MASK_REG)
    #define Airmar_TXSTATUS_MASK_PTR   (  (reg8 *) Airmar_BUART_sTX_TxSts__MASK_REG)
    #define Airmar_TXSTATUS_ACTL_REG   (* (reg8 *) Airmar_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define Airmar_TXSTATUS_ACTL_PTR   (  (reg8 *) Airmar_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(Airmar_TXCLKGEN_DP)
        #define Airmar_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) Airmar_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Airmar_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) Airmar_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Airmar_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) Airmar_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define Airmar_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) Airmar_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define Airmar_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) Airmar_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Airmar_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) Airmar_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Airmar_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Airmar_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Airmar_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Airmar_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Airmar_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) Airmar_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define Airmar_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) Airmar_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* Airmar_TXCLKGEN_DP */

#endif /* End Airmar_TX_ENABLED */

#if(Airmar_HD_ENABLED)

    #define Airmar_TXDATA_REG             (* (reg8 *) Airmar_BUART_sRX_RxShifter_u0__F1_REG )
    #define Airmar_TXDATA_PTR             (  (reg8 *) Airmar_BUART_sRX_RxShifter_u0__F1_REG )
    #define Airmar_TXDATA_AUX_CTL_REG     (* (reg8 *) Airmar_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define Airmar_TXDATA_AUX_CTL_PTR     (  (reg8 *) Airmar_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Airmar_TXSTATUS_REG           (* (reg8 *) Airmar_BUART_sRX_RxSts__STATUS_REG )
    #define Airmar_TXSTATUS_PTR           (  (reg8 *) Airmar_BUART_sRX_RxSts__STATUS_REG )
    #define Airmar_TXSTATUS_MASK_REG      (* (reg8 *) Airmar_BUART_sRX_RxSts__MASK_REG )
    #define Airmar_TXSTATUS_MASK_PTR      (  (reg8 *) Airmar_BUART_sRX_RxSts__MASK_REG )
    #define Airmar_TXSTATUS_ACTL_REG      (* (reg8 *) Airmar_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Airmar_TXSTATUS_ACTL_PTR      (  (reg8 *) Airmar_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End Airmar_HD_ENABLED */

#if( (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) )
    #define Airmar_RXDATA_REG             (* (reg8 *) Airmar_BUART_sRX_RxShifter_u0__F0_REG )
    #define Airmar_RXDATA_PTR             (  (reg8 *) Airmar_BUART_sRX_RxShifter_u0__F0_REG )
    #define Airmar_RXADDRESS1_REG         (* (reg8 *) Airmar_BUART_sRX_RxShifter_u0__D0_REG )
    #define Airmar_RXADDRESS1_PTR         (  (reg8 *) Airmar_BUART_sRX_RxShifter_u0__D0_REG )
    #define Airmar_RXADDRESS2_REG         (* (reg8 *) Airmar_BUART_sRX_RxShifter_u0__D1_REG )
    #define Airmar_RXADDRESS2_PTR         (  (reg8 *) Airmar_BUART_sRX_RxShifter_u0__D1_REG )
    #define Airmar_RXDATA_AUX_CTL_REG     (* (reg8 *) Airmar_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Airmar_RXBITCTR_PERIOD_REG    (* (reg8 *) Airmar_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Airmar_RXBITCTR_PERIOD_PTR    (  (reg8 *) Airmar_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Airmar_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Airmar_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Airmar_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Airmar_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Airmar_RXBITCTR_COUNTER_REG   (* (reg8 *) Airmar_BUART_sRX_RxBitCounter__COUNT_REG )
    #define Airmar_RXBITCTR_COUNTER_PTR   (  (reg8 *) Airmar_BUART_sRX_RxBitCounter__COUNT_REG )

    #define Airmar_RXSTATUS_REG           (* (reg8 *) Airmar_BUART_sRX_RxSts__STATUS_REG )
    #define Airmar_RXSTATUS_PTR           (  (reg8 *) Airmar_BUART_sRX_RxSts__STATUS_REG )
    #define Airmar_RXSTATUS_MASK_REG      (* (reg8 *) Airmar_BUART_sRX_RxSts__MASK_REG )
    #define Airmar_RXSTATUS_MASK_PTR      (  (reg8 *) Airmar_BUART_sRX_RxSts__MASK_REG )
    #define Airmar_RXSTATUS_ACTL_REG      (* (reg8 *) Airmar_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Airmar_RXSTATUS_ACTL_PTR      (  (reg8 *) Airmar_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) */

#if(Airmar_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define Airmar_INTCLOCK_CLKEN_REG     (* (reg8 *) Airmar_IntClock__PM_ACT_CFG)
    #define Airmar_INTCLOCK_CLKEN_PTR     (  (reg8 *) Airmar_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define Airmar_INTCLOCK_CLKEN_MASK    Airmar_IntClock__PM_ACT_MSK
#endif /* End Airmar_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(Airmar_TX_ENABLED)
    #define Airmar_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End Airmar_TX_ENABLED */

#if(Airmar_HD_ENABLED)
    #define Airmar_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End Airmar_HD_ENABLED */

#if( (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) )
    #define Airmar_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) */


/***************************************
* Renamed global variables or defines
* for backward compatible
***************************************/

#define Airmar_initvar                    Airmar_initVar

#define Airmar_RX_Enabled                 Airmar_RX_ENABLED
#define Airmar_TX_Enabled                 Airmar_TX_ENABLED
#define Airmar_HD_Enabled                 Airmar_HD_ENABLED
#define Airmar_RX_IntInterruptEnabled     Airmar_RX_INTERRUPT_ENABLED
#define Airmar_TX_IntInterruptEnabled     Airmar_TX_INTERRUPT_ENABLED
#define Airmar_InternalClockUsed          Airmar_INTERNAL_CLOCK_USED
#define Airmar_RXHW_Address_Enabled       Airmar_RXHW_ADDRESS_ENABLED
#define Airmar_OverSampleCount            Airmar_OVER_SAMPLE_COUNT
#define Airmar_ParityType                 Airmar_PARITY_TYPE

#if( Airmar_TX_ENABLED && (Airmar_TXBUFFERSIZE > Airmar_FIFO_LENGTH))
    #define Airmar_TXBUFFER               Airmar_txBuffer
    #define Airmar_TXBUFFERREAD           Airmar_txBufferRead
    #define Airmar_TXBUFFERWRITE          Airmar_txBufferWrite
#endif /* End Airmar_TX_ENABLED */
#if( ( Airmar_RX_ENABLED || Airmar_HD_ENABLED ) && \
     (Airmar_RXBUFFERSIZE > Airmar_FIFO_LENGTH) )
    #define Airmar_RXBUFFER               Airmar_rxBuffer
    #define Airmar_RXBUFFERREAD           Airmar_rxBufferRead
    #define Airmar_RXBUFFERWRITE          Airmar_rxBufferWrite
    #define Airmar_RXBUFFERLOOPDETECT     Airmar_rxBufferLoopDetect
    #define Airmar_RXBUFFER_OVERFLOW      Airmar_rxBufferOverflow
#endif /* End Airmar_RX_ENABLED */

#ifdef Airmar_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Airmar_CONTROL                Airmar_CONTROL_REG
#endif /* End Airmar_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Airmar_TX_ENABLED)
    #define Airmar_TXDATA                 Airmar_TXDATA_REG
    #define Airmar_TXSTATUS               Airmar_TXSTATUS_REG
    #define Airmar_TXSTATUS_MASK          Airmar_TXSTATUS_MASK_REG
    #define Airmar_TXSTATUS_ACTL          Airmar_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(Airmar_TXCLKGEN_DP)
        #define Airmar_TXBITCLKGEN_CTR        Airmar_TXBITCLKGEN_CTR_REG
        #define Airmar_TXBITCLKTX_COMPLETE    Airmar_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define Airmar_TXBITCTR_PERIOD        Airmar_TXBITCTR_PERIOD_REG
        #define Airmar_TXBITCTR_CONTROL       Airmar_TXBITCTR_CONTROL_REG
        #define Airmar_TXBITCTR_COUNTER       Airmar_TXBITCTR_COUNTER_REG
    #endif /* Airmar_TXCLKGEN_DP */
#endif /* End Airmar_TX_ENABLED */

#if(Airmar_HD_ENABLED)
    #define Airmar_TXDATA                 Airmar_TXDATA_REG
    #define Airmar_TXSTATUS               Airmar_TXSTATUS_REG
    #define Airmar_TXSTATUS_MASK          Airmar_TXSTATUS_MASK_REG
    #define Airmar_TXSTATUS_ACTL          Airmar_TXSTATUS_ACTL_REG
#endif /* End Airmar_HD_ENABLED */

#if( (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) )
    #define Airmar_RXDATA                 Airmar_RXDATA_REG
    #define Airmar_RXADDRESS1             Airmar_RXADDRESS1_REG
    #define Airmar_RXADDRESS2             Airmar_RXADDRESS2_REG
    #define Airmar_RXBITCTR_PERIOD        Airmar_RXBITCTR_PERIOD_REG
    #define Airmar_RXBITCTR_CONTROL       Airmar_RXBITCTR_CONTROL_REG
    #define Airmar_RXBITCTR_COUNTER       Airmar_RXBITCTR_COUNTER_REG
    #define Airmar_RXSTATUS               Airmar_RXSTATUS_REG
    #define Airmar_RXSTATUS_MASK          Airmar_RXSTATUS_MASK_REG
    #define Airmar_RXSTATUS_ACTL          Airmar_RXSTATUS_ACTL_REG
#endif /* End  (Airmar_RX_ENABLED) || (Airmar_HD_ENABLED) */

#if(Airmar_INTERNAL_CLOCK_USED)
    #define Airmar_INTCLOCK_CLKEN         Airmar_INTCLOCK_CLKEN_REG
#endif /* End Airmar_INTERNAL_CLOCK_USED */

#define Airmar_WAIT_FOR_COMLETE_REINIT    Airmar_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_Airmar_H */


/* [] END OF FILE */
