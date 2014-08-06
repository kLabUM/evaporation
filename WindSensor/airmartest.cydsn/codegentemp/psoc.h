/*******************************************************************************
* File Name: psoc.h
* Version 3.30
*
* Description:
*  This file provides constants and parameter values for the I2C component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_I2C_psoc_H)
#define CY_I2C_psoc_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check if required defines such as CY_PSOC5LP are available in cy_boot */
#if !defined (CY_PSOC5LP)
    #error Component I2C_v3_30 requires cy_boot v3.10 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define psoc_IMPLEMENTATION     (1u)
#define psoc_MODE               (2u)
#define psoc_ENABLE_WAKEUP      (0u)
#define psoc_ADDR_DECODE        (1u)
#define psoc_UDB_INTRN_CLOCK    (0u)


/* I2C implementation enum */
#define psoc_UDB    (0x00u)
#define psoc_FF     (0x01u)

#define psoc_FF_IMPLEMENTED     (psoc_FF  == psoc_IMPLEMENTATION)
#define psoc_UDB_IMPLEMENTED    (psoc_UDB == psoc_IMPLEMENTATION)

#define psoc_UDB_INTRN_CLOCK_ENABLED    (psoc_UDB_IMPLEMENTED && \
                                                     (0u != psoc_UDB_INTRN_CLOCK))
/* I2C modes enum */
#define psoc_MODE_SLAVE                 (0x01u)
#define psoc_MODE_MASTER                (0x02u)
#define psoc_MODE_MULTI_MASTER          (0x06u)
#define psoc_MODE_MULTI_MASTER_SLAVE    (0x07u)
#define psoc_MODE_MULTI_MASTER_MASK     (0x04u)

#define psoc_MODE_SLAVE_ENABLED         (0u != (psoc_MODE_SLAVE  & psoc_MODE))
#define psoc_MODE_MASTER_ENABLED        (0u != (psoc_MODE_MASTER & psoc_MODE))
#define psoc_MODE_MULTI_MASTER_ENABLED  (0u != (psoc_MODE_MULTI_MASTER_MASK & \
                                                            psoc_MODE))
#define psoc_MODE_MULTI_MASTER_SLAVE_ENABLED    (psoc_MODE_MULTI_MASTER_SLAVE == \
                                                             psoc_MODE)

/* Address detection enum */
#define psoc_SW_DECODE      (0x00u)
#define psoc_HW_DECODE      (0x01u)

#define psoc_SW_ADRR_DECODE             (psoc_SW_DECODE == psoc_ADDR_DECODE)
#define psoc_HW_ADRR_DECODE             (psoc_HW_DECODE == psoc_ADDR_DECODE)

/* Wakeup enabled */
#define psoc_WAKEUP_ENABLED             (0u != psoc_ENABLE_WAKEUP)

/* Adds bootloader APIs to component */
#define psoc_BOOTLOADER_INTERFACE_ENABLED   (psoc_MODE_SLAVE_ENABLED && \
                                                            ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_psoc) || \
                                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)))

/* Timeout functionality */
#define psoc_TIMEOUT_ENABLE             (0u)
#define psoc_TIMEOUT_SCL_TMOUT_ENABLE   (0u)
#define psoc_TIMEOUT_SDA_TMOUT_ENABLE   (0u)
#define psoc_TIMEOUT_PRESCALER_ENABLE   (0u)
#define psoc_TIMEOUT_IMPLEMENTATION     (0u)

/* Convert to boolean */
#define psoc_TIMEOUT_ENABLED            (0u != psoc_TIMEOUT_ENABLE)
#define psoc_TIMEOUT_SCL_TMOUT_ENABLED  (0u != psoc_TIMEOUT_SCL_TMOUT_ENABLE)
#define psoc_TIMEOUT_SDA_TMOUT_ENABLED  (0u != psoc_TIMEOUT_SDA_TMOUT_ENABLE)
#define psoc_TIMEOUT_PRESCALER_ENABLED  (0u != psoc_TIMEOUT_PRESCALER_ENABLE)

/* Timeout implementation enum. */
#define psoc_TIMEOUT_UDB    (0x00u)
#define psoc_TIMEOUT_FF     (0x01u)

#define psoc_TIMEOUT_FF_IMPLEMENTED     (psoc_TIMEOUT_FF  == \
                                                        psoc_TIMEOUT_IMPLEMENTATION)
#define psoc_TIMEOUT_UDB_IMPLEMENTED    (psoc_TIMEOUT_UDB == \
                                                        psoc_TIMEOUT_IMPLEMENTATION)

#define psoc_TIMEOUT_FF_ENABLED         (psoc_TIMEOUT_ENABLED && \
                                                     psoc_TIMEOUT_FF_IMPLEMENTED && \
                                                     CY_PSOC5LP)

#define psoc_TIMEOUT_UDB_ENABLED        (psoc_TIMEOUT_ENABLED && \
                                                     psoc_TIMEOUT_UDB_IMPLEMENTED)

#define psoc_EXTERN_I2C_INTR_HANDLER    (0u)
#define psoc_EXTERN_TMOUT_INTR_HANDLER  (0u)

#define psoc_INTERN_I2C_INTR_HANDLER    (0u == psoc_EXTERN_I2C_INTR_HANDLER)
#define psoc_INTERN_TMOUT_INTR_HANDLER  (0u == psoc_EXTERN_TMOUT_INTR_HANDLER)


/***************************************
*       Type defines
***************************************/

/* Structure to save registers before go to sleep */
typedef struct
{
    uint8 enableState;

    #if(psoc_FF_IMPLEMENTED)
        uint8 xcfg;
        uint8 cfg;

        #if(psoc_MODE_SLAVE_ENABLED)
            uint8 addr;
        #endif /* (psoc_MODE_SLAVE_ENABLED) */

        #if(CY_PSOC5A)
            uint8 clkDiv;
        #else
            uint8 clkDiv1;
            uint8 clkDiv2;
        #endif /* (CY_PSOC5A) */

    #else
        uint8 control;

        #if(CY_UDB_V0)
            uint8 intMask;

            #if(psoc_MODE_SLAVE_ENABLED)
                uint8 addr;
            #endif /* (psoc_MODE_SLAVE_ENABLED) */
        #endif     /* (CY_UDB_V0) */

    #endif /* (psoc_FF_IMPLEMENTED) */

    #if(psoc_TIMEOUT_ENABLED)
        uint16 tmoutCfg;
        uint8  tmoutIntr;

        #if(psoc_TIMEOUT_PRESCALER_ENABLED && CY_UDB_V0)
            uint8 tmoutPrd;
        #endif /* (psoc_TIMEOUT_PRESCALER_ENABLED && CY_UDB_V0) */

    #endif /* (psoc_TIMEOUT_ENABLED) */

} psoc_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void psoc_Init(void)                            ;
void psoc_Enable(void)                          ;

void psoc_Start(void)                           ;
void psoc_Stop(void)                            ;

#define psoc_EnableInt()        CyIntEnable      (psoc_ISR_NUMBER)
#define psoc_DisableInt()       CyIntDisable     (psoc_ISR_NUMBER)
#define psoc_ClearPendingInt()  CyIntClearPending(psoc_ISR_NUMBER)
#define psoc_SetPendingInt()    CyIntSetPending  (psoc_ISR_NUMBER)

void psoc_SaveConfig(void)                      ;
void psoc_Sleep(void)                           ;
void psoc_RestoreConfig(void)                   ;
void psoc_Wakeup(void)                          ;

/* I2C Master functions prototypes */
#if(psoc_MODE_MASTER_ENABLED)
    /* Read and Clear status functions */
    uint8 psoc_MasterStatus(void)                ;
    uint8 psoc_MasterClearStatus(void)           ;

    /* Interrupt based operation functions */
    uint8 psoc_MasterWriteBuf(uint8 slaveAddress, uint8 * wrData, uint8 cnt, uint8 mode) \
                                                            ;
    uint8 psoc_MasterReadBuf(uint8 slaveAddress, uint8 * rdData, uint8 cnt, uint8 mode) \
                                                            ;
    uint8 psoc_MasterGetReadBufSize(void)       ;
    uint8 psoc_MasterGetWriteBufSize(void)      ;
    void  psoc_MasterClearReadBuf(void)         ;
    void  psoc_MasterClearWriteBuf(void)        ;

    /* Manual operation functions */
    uint8 psoc_MasterSendStart(uint8 slaveAddress, uint8 R_nW) \
                                                            ;
    uint8 psoc_MasterSendRestart(uint8 slaveAddress, uint8 R_nW) \
                                                            ;
    uint8 psoc_MasterSendStop(void)             ;
    uint8 psoc_MasterWriteByte(uint8 theByte)   ;
    uint8 psoc_MasterReadByte(uint8 acknNak)    ;

    /* This fake function use as workaround */
    void  psoc_Workaround(void)                 ;

#endif /* (psoc_MODE_MASTER_ENABLED) */

/* I2C Slave functions prototypes */
#if(psoc_MODE_SLAVE_ENABLED)
    /* Read and Clear status functions */
    uint8 psoc_SlaveStatus(void)                ;
    uint8 psoc_SlaveClearReadStatus(void)       ;
    uint8 psoc_SlaveClearWriteStatus(void)      ;

    void  psoc_SlaveSetAddress(uint8 address)   ;

    /* Interrupt based operation functions */
    void  psoc_SlaveInitReadBuf(uint8 * rdBuf, uint8 bufSize) \
                                                            ;
    void  psoc_SlaveInitWriteBuf(uint8 * wrBuf, uint8 bufSize) \
                                                            ;
    uint8 psoc_SlaveGetReadBufSize(void)        ;
    uint8 psoc_SlaveGetWriteBufSize(void)       ;
    void  psoc_SlaveClearReadBuf(void)          ;
    void  psoc_SlaveClearWriteBuf(void)         ;

    /* Communication bootloader I2C Slave APIs */
    #if defined(CYDEV_BOOTLOADER_IO_COMP) && (psoc_BOOTLOADER_INTERFACE_ENABLED)
        /* Physical layer functions */
        void     psoc_CyBtldrCommStart(void) CYSMALL \
                                                            ;
        void     psoc_CyBtldrCommStop(void)  CYSMALL \
                                                            ;
        void     psoc_CyBtldrCommReset(void) CYSMALL \
                                                            ;
        cystatus psoc_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) \
                                                        CYSMALL ;
        cystatus psoc_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)  CYSMALL \
                                                            ;

        #if(CYDEV_BOOTLOADER_IO_COMP == CyBtldr_psoc)
            #define CyBtldrCommStart    psoc_CyBtldrCommStart
            #define CyBtldrCommStop     psoc_CyBtldrCommStop
            #define CyBtldrCommReset    psoc_CyBtldrCommReset
            #define CyBtldrCommWrite    psoc_CyBtldrCommWrite
            #define CyBtldrCommRead     psoc_CyBtldrCommRead
        #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_psoc) */

        /* Size of Read/Write buffers for I2C bootloader  */
        #define psoc_BTLDR_SIZEOF_READ_BUFFER   (0x80u)
        #define psoc_BTLDR_SIZEOF_WRITE_BUFFER  (0x80u)
        #define psoc_MIN_UNT16(a, b)            ( ((uint16)(a) < (b)) ? ((uint16) (a)) : ((uint16) (b)) )
        #define psoc_WAIT_1_MS                  (1u)

    #endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (psoc_BOOTLOADER_INTERFACE_ENABLED) */

#endif /* (psoc_MODE_SLAVE_ENABLED) */

/* I2C interrupt handler */
CY_ISR_PROTO(psoc_ISR);
#if((psoc_FF_IMPLEMENTED) || (psoc_WAKEUP_ENABLED))
    CY_ISR_PROTO(psoc_WAKEUP_ISR);
#endif /* ((psoc_FF_IMPLEMENTED) || (psoc_WAKEUP_ENABLED)) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 psoc_initVar;


/***************************************
*   Initial Parameter Constants
***************************************/

#define psoc_DATA_RATE          (100u)
#define psoc_DEFAULT_ADDR       (8u)
#define psoc_I2C_PAIR_SELECTED  (0u)

/* I2C pair enum */
#define psoc_I2C_PAIR_ANY   (0x01u) /* Any pins for I2C */
#define psoc_I2C_PAIR0      (0x01u) /* I2C0: (SCL = P12[4]) && (SCL = P12[5]) */
#define psoc_I2C_PAIR1      (0x02u) /* I2C1: (SCL = P12[0]) && (SDA = P12[1]) */

#define psoc_I2C1_SIO_PAIR  (psoc_I2C_PAIR1 == psoc_I2C_PAIR_SELECTED)
#define psoc_I2C0_SIO_PAIR  (psoc_I2C_PAIR0 == psoc_I2C_PAIR_SELECTED)


/***************************************
*            API Constants
***************************************/

/* Master/Slave control constants */
#define psoc_READ_XFER_MODE     (0x01u) /* Read */
#define psoc_WRITE_XFER_MODE    (0x00u) /* Write */
#define psoc_ACK_DATA           (0x01u) /* Send ACK */
#define psoc_NAK_DATA           (0x00u) /* Send NAK */
#define psoc_OVERFLOW_RETURN    (0xFFu) /* Senf on bus in case of overflow */

#if(psoc_MODE_MASTER_ENABLED)
    /* "Mode" constants for MasterWriteBuf() or MasterReadBuf() function */
    #define psoc_MODE_COMPLETE_XFER     (0x00u) /* Full transfer with Start and Stop */
    #define psoc_MODE_REPEAT_START      (0x01u) /* Begin with a ReStart instead of a Start */
    #define psoc_MODE_NO_STOP           (0x02u) /* Complete the transfer without a Stop */

    /* Master status */
    #define psoc_MSTAT_CLEAR            (0x00u) /* Clear (init) status value */

    #define psoc_MSTAT_RD_CMPLT         (0x01u) /* Read complete */
    #define psoc_MSTAT_WR_CMPLT         (0x02u) /* Write complete */
    #define psoc_MSTAT_XFER_INP         (0x04u) /* Master transfer in progress */
    #define psoc_MSTAT_XFER_HALT        (0x08u) /* Transfer is halted */

    #define psoc_MSTAT_ERR_MASK         (0xF0u) /* Mask for all errors */
    #define psoc_MSTAT_ERR_SHORT_XFER   (0x10u) /* Master NAKed before end of packet */
    #define psoc_MSTAT_ERR_ADDR_NAK     (0x20u) /* Slave did not ACK */
    #define psoc_MSTAT_ERR_ARB_LOST     (0x40u) /* Master lost arbitration during communication */
    #define psoc_MSTAT_ERR_XFER         (0x80u) /* Error during transfer */

    /* Master API returns */
    #define psoc_MSTR_NO_ERROR          (0x00u) /* Function complete without error */
    #define psoc_MSTR_BUS_BUSY          (0x01u) /* Bus is busy, process not started */
    #define psoc_MSTR_NOT_READY         (0x02u) /* Master not Master on the bus or */
                                                            /*  Slave operation in progress */
    #define psoc_MSTR_ERR_LB_NAK        (0x03u) /* Last Byte Naked */
    #define psoc_MSTR_ERR_ARB_LOST      (0x04u) /* Master lost arbitration during communication */
    #define psoc_MSTR_ERR_ABORT_START_GEN  (0x05u) /* Master did not generate Start, the Slave */
                                                               /* was addressed before */

#endif /* (psoc_MODE_MASTER_ENABLED) */

#if(psoc_MODE_SLAVE_ENABLED)
    /* Slave Status Constants */
    #define psoc_SSTAT_RD_CMPLT     (0x01u) /* Read transfer complete */
    #define psoc_SSTAT_RD_BUSY      (0x02u) /* Read transfer in progress */
    #define psoc_SSTAT_RD_ERR_OVFL  (0x04u) /* Read overflow Error */
    #define psoc_SSTAT_RD_MASK      (0x0Fu) /* Read Status Mask */
    #define psoc_SSTAT_RD_NO_ERR    (0x00u) /* Read no Error */

    #define psoc_SSTAT_WR_CMPLT     (0x10u) /* Write transfer complete */
    #define psoc_SSTAT_WR_BUSY      (0x20u) /* Write transfer in progress */
    #define psoc_SSTAT_WR_ERR_OVFL  (0x40u) /* Write overflow Error */
    #define psoc_SSTAT_WR_MASK      (0xF0u) /* Write Status Mask  */
    #define psoc_SSTAT_WR_NO_ERR    (0x00u) /* Write no Error */

    #define psoc_SSTAT_RD_CLEAR     (0x0Du) /* Read Status clear */
    #define psoc_SSTAT_WR_CLEAR     (0xD0u) /* Write Status Clear */

#endif /* (psoc_MODE_SLAVE_ENABLED) */


/***************************************
*       I2C state machine constants
***************************************/

/* Default slave address states */
#define  psoc_SM_IDLE           (0x10u) /* Default state - IDLE */
#define  psoc_SM_EXIT_IDLE      (0x00u) /* Pass master and slave processing and go to IDLE */

/* Slave mode states */
#define  psoc_SM_SLAVE          (psoc_SM_IDLE) /* Any Slave state */
#define  psoc_SM_SL_WR_DATA     (0x11u) /* Master writes data to slzve  */
#define  psoc_SM_SL_RD_DATA     (0x12u) /* Master reads data from slave */

/* Master mode states */
#define  psoc_SM_MASTER         (0x40u) /* Any master state */

#define  psoc_SM_MSTR_RD        (0x08u) /* Any master read state          */
#define  psoc_SM_MSTR_RD_ADDR   (0x49u) /* Master sends address with read */
#define  psoc_SM_MSTR_RD_DATA   (0x4Au) /* Master reads data              */

#define  psoc_SM_MSTR_WR        (0x04u) /* Any master read state           */
#define  psoc_SM_MSTR_WR_ADDR   (0x45u) /* Master sends address with write */
#define  psoc_SM_MSTR_WR_DATA   (0x46u) /* Master writes data              */

#define  psoc_SM_MSTR_HALT      (0x60u) /* Master waits for ReStart */

#define psoc_CHECK_SM_MASTER    (0u != (psoc_SM_MASTER & psoc_state))
#define psoc_CHECK_SM_SLAVE     (0u != (psoc_SM_SLAVE  & psoc_state))


/***************************************
*              Registers
***************************************/

#if(psoc_FF_IMPLEMENTED)
    /* Fixed Function registers */
    #define psoc_XCFG_REG           (* (reg8 *) psoc_I2C_FF__XCFG)
    #define psoc_XCFG_PTR           (  (reg8 *) psoc_I2C_FF__XCFG)

    #define psoc_ADDR_REG           (* (reg8 *) psoc_I2C_FF__ADR)
    #define psoc_ADDR_PTR           (  (reg8 *) psoc_I2C_FF__ADR)

    #define psoc_CFG_REG            (* (reg8 *) psoc_I2C_FF__CFG)
    #define psoc_CFG_PTR            (  (reg8 *) psoc_I2C_FF__CFG)

    #define psoc_CSR_REG            (* (reg8 *) psoc_I2C_FF__CSR)
    #define psoc_CSR_PTR            (  (reg8 *) psoc_I2C_FF__CSR)

    #define psoc_DATA_REG           (* (reg8 *) psoc_I2C_FF__D)
    #define psoc_DATA_PTR           (  (reg8 *) psoc_I2C_FF__D)

    #define psoc_MCSR_REG           (* (reg8 *) psoc_I2C_FF__MCSR)
    #define psoc_MCSR_PTR           (  (reg8 *) psoc_I2C_FF__MCSR)

    #define psoc_ACT_PWRMGR_REG     (* (reg8 *) psoc_I2C_FF__PM_ACT_CFG)
    #define psoc_ACT_PWRMGR_PTR     (  (reg8 *) psoc_I2C_FF__PM_ACT_CFG)
    #define psoc_ACT_PWR_EN         (  (uint8)  psoc_I2C_FF__PM_ACT_MSK)

    #define psoc_STBY_PWRMGR_REG    (* (reg8 *) psoc_I2C_FF__PM_STBY_CFG)
    #define psoc_STBY_PWRMGR_PTR    (  (reg8 *) psoc_I2C_FF__PM_STBY_CFG)
    #define psoc_STBY_PWR_EN        (  (uint8)  psoc_I2C_FF__PM_STBY_MSK)

    #define psoc_PWRSYS_CR1_REG     (* (reg8 *) CYREG_PWRSYS_CR1)
    #define psoc_PWRSYS_CR1_PTR     (  (reg8 *) CYREG_PWRSYS_CR1)

    /* Clock divider register depends on silicon */
    #if(CY_PSOC5A)
        #define psoc_CLKDIV_REG     (* (reg8 *) psoc_I2C_FF__CLK_DIV)
        #define psoc_CLKDIV_PTR     (  (reg8 *) psoc_I2C_FF__CLK_DIV)

    #else
        #define psoc_CLKDIV1_REG    (* (reg8 *) psoc_I2C_FF__CLK_DIV1)
        #define psoc_CLKDIV1_PTR    (  (reg8 *) psoc_I2C_FF__CLK_DIV1)

        #define psoc_CLKDIV2_REG    (* (reg8 *) psoc_I2C_FF__CLK_DIV2)
        #define psoc_CLKDIV2_PTR    (  (reg8 *) psoc_I2C_FF__CLK_DIV2)

    #endif /* (CY_PSOC5A) */

#else
    /* UDB implementation registers */
    #define psoc_CFG_REG    (* (reg8 *) \
                                           psoc_bI2C_UDB_SyncCtl_CtrlReg__CONTROL_REG)
    #define psoc_CFG_PTR    (  (reg8 *) \
                                           psoc_bI2C_UDB_SyncCtl_CtrlReg__CONTROL_REG)

    #define psoc_CSR_REG        (* (reg8 *) psoc_bI2C_UDB_StsReg__STATUS_REG)
    #define psoc_CSR_PTR        (  (reg8 *) psoc_bI2C_UDB_StsReg__STATUS_REG)

    #define psoc_INT_MASK_REG   (* (reg8 *) psoc_bI2C_UDB_StsReg__MASK_REG)
    #define psoc_INT_MASK_PTR   (  (reg8 *) psoc_bI2C_UDB_StsReg__MASK_REG)

    #define psoc_INT_ENABLE_REG (* (reg8 *) psoc_bI2C_UDB_StsReg__STATUS_AUX_CTL_REG)
    #define psoc_INT_ENABLE_PTR (  (reg8 *) psoc_bI2C_UDB_StsReg__STATUS_AUX_CTL_REG)

    #define psoc_DATA_REG       (* (reg8 *) psoc_bI2C_UDB_Shifter_u0__A0_REG)
    #define psoc_DATA_PTR       (  (reg8 *) psoc_bI2C_UDB_Shifter_u0__A0_REG)

    #define psoc_GO_REG         (* (reg8 *) psoc_bI2C_UDB_Shifter_u0__F1_REG)
    #define psoc_GO_PTR         (  (reg8 *) psoc_bI2C_UDB_Shifter_u0__F1_REG)

    #define psoc_MCLK_PRD_REG   (* (reg8 *) psoc_bI2C_UDB_Master_ClkGen_u0__D0_REG)
    #define psoc_MCLK_PRD_PTR   (  (reg8 *) psoc_bI2C_UDB_Master_ClkGen_u0__D0_REG)

    #define psoc_MCLK_CMP_REG   (* (reg8 *) psoc_bI2C_UDB_Master_ClkGen_u0__D1_REG)
    #define psoc_MCLK_CMP_PTR   (  (reg8 *) psoc_bI2C_UDB_Master_ClkGen_u0__D1_REG)

    #if(psoc_MODE_SLAVE_ENABLED)
        #define psoc_ADDR_REG       (* (reg8 *) psoc_bI2C_UDB_Shifter_u0__D0_REG)
        #define psoc_ADDR_PTR       (  (reg8 *) psoc_bI2C_UDB_Shifter_u0__D0_REG)

        #define psoc_PERIOD_REG     (* (reg8 *) psoc_bI2C_UDB_Slave_BitCounter__PERIOD_REG)
        #define psoc_PERIOD_PTR     (  (reg8 *) psoc_bI2C_UDB_Slave_BitCounter__PERIOD_REG)

        #define psoc_COUNTER_REG    (* (reg8 *) psoc_bI2C_UDB_Slave_BitCounter__COUNT_REG)
        #define psoc_COUNTER_PTR    (  (reg8 *) psoc_bI2C_UDB_Slave_BitCounter__COUNT_REG)

        #define psoc_COUNTER_AUX_CTL_REG  (* (reg8 *) \
                                                        psoc_bI2C_UDB_Slave_BitCounter__CONTROL_AUX_CTL_REG)
        #define psoc_COUNTER_AUX_CTL_PTR  (  (reg8 *) \
                                                        psoc_bI2C_UDB_Slave_BitCounter__CONTROL_AUX_CTL_REG)

    #endif /* (psoc_MODE_SLAVE_ENABLED) */

#endif /* (psoc_FF_IMPLEMENTED) */


/***************************************
*        Registers Constants
***************************************/

/* psoc_I2C_IRQ */
#define psoc_ISR_NUMBER     ((uint8) psoc_I2C_IRQ__INTC_NUMBER)
#define psoc_ISR_PRIORITY   ((uint8) psoc_I2C_IRQ__INTC_PRIOR_NUM)

/* I2C Slave Data Register */
#define psoc_SLAVE_ADDR_MASK    (0x7Fu)
#define psoc_SLAVE_ADDR_SHIFT   (0x01u)
#define psoc_DATA_MASK          (0xFFu)
#define psoc_READ_FLAG          (0x01u)

#define psoc_FF_RESET_DELAY     (0x02u)

#if(psoc_FF_IMPLEMENTED)
    /* XCFG I2C Extended Configuration Register */
    #define psoc_XCFG_CLK_EN        (0x80u) /* Enable gated clock to block */
    #define psoc_XCFG_I2C_ON        (0x40u) /* Enable I2C as wake up source*/
    #define psoc_XCFG_RDY_TO_SLEEP  (0x20u) /* I2C ready go to sleep */
    #define psoc_XCFG_FORCE_NACK    (0x10u) /* Force NACK all incomming transactions */
    #define psoc_XCFG_NO_BC_INT     (0x08u) /* No interrupt on byte complete */
    #define psoc_XCFG_BUF_MODE      (0x02u) /* Enable buffer mode */
    #define psoc_XCFG_HDWR_ADDR_EN  (0x01u) /* Enable Hardware address match */

    /* CFG I2C Configuration Register */
    #define psoc_CFG_SIO_SELECT     (0x80u) /* Pin Select for SCL/SDA lines */
    #define psoc_CFG_PSELECT        (0x40u) /* Pin Select */
    #define psoc_CFG_BUS_ERR_IE     (0x20u) /* Bus Error Interrupt Enable */
    #define psoc_CFG_STOP_IE        (0x10u) /* Enable Interrupt on STOP condition */
    #define psoc_CFG_CLK_RATE_MSK   (0x0Cu) /* Clock rate select  **CHECK**  */
    #define psoc_CFG_CLK_RATE_100   (0x00u) /* Clock rate select 100K */
    #define psoc_CFG_CLK_RATE_400   (0x04u) /* Clock rate select 400K */
    #define psoc_CFG_CLK_RATE_050   (0x08u) /* Clock rate select 50K  */
    #define psoc_CFG_CLK_RATE_RSVD  (0x0Cu) /* Clock rate select Invalid */
    #define psoc_CFG_EN_MSTR        (0x02u) /* Enable Master operation */
    #define psoc_CFG_EN_SLAVE       (0x01u) /* Enable Slave operation */

    #define psoc_CFG_CLK_RATE_LESS_EQUAL_50 (0x04u) /* Clock rate select <= 50kHz */
    #define psoc_CFG_CLK_RATE_GRATER_50     (0x00u) /* Clock rate select > 50kHz */

    /* CSR I2C Control and Status Register */
    #define psoc_CSR_BUS_ERROR      (0x80u) /* Active high when bus error has occured */
    #define psoc_CSR_LOST_ARB       (0x40u) /* Set to 1 if lost arbitration in host mode */
    #define psoc_CSR_STOP_STATUS    (0x20u) /* Set if Stop has been detected */
    #define psoc_CSR_ACK            (0x10u) /* ACK response */
    #define psoc_CSR_NAK            (0x00u) /* NAK response */
    #define psoc_CSR_ADDRESS        (0x08u) /* Set in firmware 0 = status bit, 1 Address is slave */
    #define psoc_CSR_TRANSMIT       (0x04u) /* Set in firmware 1 = transmit, 0 = receive */
    #define psoc_CSR_LRB            (0x02u) /* Last received bit */
    #define psoc_CSR_LRB_ACK        (0x00u) /* Last received bit was an ACK */
    #define psoc_CSR_LRB_NAK        (0x02u) /* Last received bit was an NAK */
    #define psoc_CSR_BYTE_COMPLETE  (0x01u) /* Informs that last byte has been sent */
    #define psoc_CSR_STOP_GEN       (0x00u) /* Generate a stop condition */
    #define psoc_CSR_RDY_TO_RD      (0x00u) /* Set to recieve mode */

    /* MCSR I2C Master Control and Status Register */
    #define psoc_MCSR_STOP_GEN      (0x10u) /* Firmware sets this bit to initiate a Stop condition */
    #define psoc_MCSR_BUS_BUSY      (0x08u) /* Status bit, Set at Start and cleared at Stop condition */
    #define psoc_MCSR_MSTR_MODE     (0x04u) /* Status bit, Set at Start and cleared at Stop condition */
    #define psoc_MCSR_RESTART_GEN   (0x02u) /* Firmware sets this bit to initiate a ReStart condition */
    #define psoc_MCSR_START_GEN     (0x01u) /* Firmware sets this bit to initiate a Start condition */

    /* CLK_DIV I2C Clock Divide Factor Register */
    #define psoc_CLK_DIV_MSK    (0x07u) /* Status bit, Set at Start and cleared at Stop condition */
    #define psoc_CLK_DIV_1      (0x00u) /* Divide input clock by  1 */
    #define psoc_CLK_DIV_2      (0x01u) /* Divide input clock by  2 */
    #define psoc_CLK_DIV_4      (0x02u) /* Divide input clock by  4 */
    #define psoc_CLK_DIV_8      (0x03u) /* Divide input clock by  8 */
    #define psoc_CLK_DIV_16     (0x04u) /* Divide input clock by 16 */
    #define psoc_CLK_DIV_32     (0x05u) /* Divide input clock by 32 */
    #define psoc_CLK_DIV_64     (0x06u) /* Divide input clock by 64 */

    /* PWRSYS_CR1 to handle Sleep */
    #define psoc_PWRSYS_CR1_I2C_REG_BACKUP  (0x04u) /* Enables, power to I2C regs while sleep */

#else
    /* CONTROL REG bits location */
    #define psoc_CTRL_START_SHIFT           (7u)
    #define psoc_CTRL_STOP_SHIFT            (6u)
    #define psoc_CTRL_RESTART_SHIFT         (5u)
    #define psoc_CTRL_NACK_SHIFT            (4u)
    #define psoc_CTRL_ANY_ADDRESS_SHIFT     (3u)
    #define psoc_CTRL_TRANSMIT_SHIFT        (2u)
    #define psoc_CTRL_ENABLE_MASTER_SHIFT   (1u)
    #define psoc_CTRL_ENABLE_SLAVE_SHIFT    (0u)
    #define psoc_CTRL_START_MASK            ((uint8) (0x01u << psoc_CTRL_START_SHIFT))
    #define psoc_CTRL_STOP_MASK             ((uint8) (0x01u << psoc_CTRL_STOP_SHIFT))
    #define psoc_CTRL_RESTART_MASK          ((uint8) (0x01u << psoc_CTRL_RESTART_SHIFT))
    #define psoc_CTRL_NACK_MASK             ((uint8) (0x01u << psoc_CTRL_NACK_SHIFT))
    #define psoc_CTRL_ANY_ADDRESS_MASK      ((uint8) (0x01u << psoc_CTRL_ANY_ADDRESS_SHIFT))
    #define psoc_CTRL_TRANSMIT_MASK         ((uint8) (0x01u << psoc_CTRL_TRANSMIT_SHIFT))
    #define psoc_CTRL_ENABLE_MASTER_MASK    ((uint8) (0x01u << psoc_CTRL_ENABLE_MASTER_SHIFT))
    #define psoc_CTRL_ENABLE_SLAVE_MASK     ((uint8) (0x01u << psoc_CTRL_ENABLE_SLAVE_SHIFT))

    /* STATUS REG bits location */
    #define psoc_STS_LOST_ARB_SHIFT         (6u)
    #define psoc_STS_STOP_SHIFT             (5u)
    #define psoc_STS_BUSY_SHIFT             (4u)
    #define psoc_STS_ADDR_SHIFT             (3u)
    #define psoc_STS_MASTER_MODE_SHIFT      (2u)
    #define psoc_STS_LRB_SHIFT              (1u)
    #define psoc_STS_BYTE_COMPLETE_SHIFT    (0u)
    #define psoc_STS_LOST_ARB_MASK          ((uint8) (0x01u << psoc_STS_LOST_ARB_SHIFT))
    #define psoc_STS_STOP_MASK              ((uint8) (0x01u << psoc_STS_STOP_SHIFT))
    #define psoc_STS_BUSY_MASK              ((uint8) (0x01u << psoc_STS_BUSY_SHIFT))
    #define psoc_STS_ADDR_MASK              ((uint8) (0x01u << psoc_STS_ADDR_SHIFT))
    #define psoc_STS_MASTER_MODE_MASK       ((uint8) (0x01u << psoc_STS_MASTER_MODE_SHIFT))
    #define psoc_STS_LRB_MASK               ((uint8) (0x01u << psoc_STS_LRB_SHIFT))
    #define psoc_STS_BYTE_COMPLETE_MASK     ((uint8) (0x01u << psoc_STS_BYTE_COMPLETE_SHIFT))

    /* AUX_CTL bits definition */
    #define psoc_COUNTER_ENABLE_MASK        (0x20u) /* Enable 7-bit counter     */
    #define psoc_INT_ENABLE_MASK            (0x10u) /* Enable intr from statusi */
    #define psoc_CNT7_ENABLE                (psoc_COUNTER_ENABLE_MASK)
    #define psoc_INTR_ENABLE                (psoc_INT_ENABLE_MASK)

#endif /* (psoc_FF_IMPLEMENTED) */


/***************************************
*        Marco
***************************************/

/* ACK and NACK for data and address checks */
#define psoc_CHECK_ADDR_ACK(csr)    ((psoc_CSR_LRB_ACK | psoc_CSR_ADDRESS) == \
                                                 ((psoc_CSR_LRB    | psoc_CSR_ADDRESS) &  \
                                                  (csr)))


#define psoc_CHECK_ADDR_NAK(csr)    ((psoc_CSR_LRB_NAK | psoc_CSR_ADDRESS) == \
                                                 ((psoc_CSR_LRB    | psoc_CSR_ADDRESS) &  \
                                                  (csr)))

#define psoc_CHECK_DATA_ACK(csr)    (0u == ((csr) & psoc_CSR_LRB_NAK))

/* MCSR conditions check */
#define psoc_CHECK_BUS_FREE(mcsr)       (0u == ((mcsr) & psoc_MCSR_BUS_BUSY))
#define psoc_CHECK_MASTER_MODE(mcsr)    (0u != ((mcsr) & psoc_MCSR_MSTR_MODE))

/* CSR conditions check */
#define psoc_WAIT_BYTE_COMPLETE(csr)    (0u == ((csr) & psoc_CSR_BYTE_COMPLETE))
#define psoc_WAIT_STOP_COMPLETE(csr)    (0u == ((csr) & (psoc_CSR_BYTE_COMPLETE | \
                                                                     psoc_CSR_STOP_STATUS)))
#define psoc_CHECK_BYTE_COMPLETE(csr)   (0u != ((csr) & psoc_CSR_BYTE_COMPLETE))
#define psoc_CHECK_STOP_STS(csr)        (0u != ((csr) & psoc_CSR_STOP_STATUS))
#define psoc_CHECK_LOST_ARB(csr)        (0u != ((csr) & psoc_CSR_LOST_ARB))
#define psoc_CHECK_ADDRESS_STS(csr)     (0u != ((csr) & psoc_CSR_ADDRESS))

/* Software start and end of transaction check */
#define psoc_CHECK_RESTART(mstrCtrl)    (0u != ((mstrCtrl) & psoc_MODE_REPEAT_START))
#define psoc_CHECK_NO_STOP(mstrCtrl)    (0u != ((mstrCtrl) & psoc_MODE_NO_STOP))

/* Send read or write completion depends on state */
#define psoc_GET_MSTAT_CMPLT ((0u != (psoc_state & psoc_SM_MSTR_RD)) ? \
                                                 (psoc_MSTAT_RD_CMPLT) : (psoc_MSTAT_WR_CMPLT))

/* Returns 7-bit slave address and used for software address match */
#define psoc_GET_SLAVE_ADDR(dataReg)   (((dataReg) >> psoc_SLAVE_ADDR_SHIFT) & \
                                                                  psoc_SLAVE_ADDR_MASK)

#if(psoc_FF_IMPLEMENTED)
    /* Check enable of module */
    #define psoc_I2C_ENABLE_REG     (psoc_ACT_PWRMGR_REG)
    #define psoc_IS_I2C_ENABLE(reg) (0u != ((reg) & psoc_ACT_PWR_EN))
    #define psoc_IS_ENABLED         (0u != (psoc_ACT_PWRMGR_REG & psoc_ACT_PWR_EN))

    #define psoc_CHECK_PWRSYS_I2C_BACKUP    (0u != (psoc_PWRSYS_CR1_I2C_REG_BACKUP & \
                                                                psoc_PWRSYS_CR1_REG))

    /* Check start condition generation */
    #define psoc_CHECK_START_GEN(mcsr)  ((0u != ((mcsr) & psoc_MCSR_START_GEN)) && \
                                                     (0u == ((mcsr) & psoc_MCSR_MSTR_MODE)))

    #define psoc_CLEAR_START_GEN        do{ \
                                                        psoc_MCSR_REG &=                                   \
                                                                           ((uint8) ~psoc_MCSR_START_GEN); \
                                                    }while(0)

    /* Stop interrupt */
    #define psoc_ENABLE_INT_ON_STOP     do{ \
                                                        psoc_CFG_REG |= psoc_CFG_STOP_IE; \
                                                    }while(0)

    #define psoc_DISABLE_INT_ON_STOP    do{ \
                                                        psoc_CFG_REG &=                                 \
                                                                           ((uint8) ~psoc_CFG_STOP_IE); \
                                                    }while(0)

    /* Transmit data */
    #define psoc_TRANSMIT_DATA          do{ \
                                                        psoc_CSR_REG = psoc_CSR_TRANSMIT; \
                                                    }while(0)

    #define psoc_ACK_AND_TRANSMIT       do{ \
                                                        psoc_CSR_REG = (psoc_CSR_ACK |      \
                                                                                    psoc_CSR_TRANSMIT); \
                                                    }while(0)

    #define psoc_NAK_AND_TRANSMIT       do{ \
                                                        psoc_CSR_REG = psoc_CSR_NAK; \
                                                    }while(0)

    /* Special case: udb needs to ack, ff needs to nak */
    #define psoc_ACKNAK_AND_TRANSMIT    do{ \
                                                        psoc_CSR_REG  = (psoc_CSR_NAK |      \
                                                                                     psoc_CSR_TRANSMIT); \
                                                    }while(0)
    /* Receive data */
    #define psoc_ACK_AND_RECEIVE        do{ \
                                                        psoc_CSR_REG = psoc_CSR_ACK; \
                                                    }while(0)

    #define psoc_NAK_AND_RECEIVE        do{ \
                                                        psoc_CSR_REG = psoc_CSR_NAK; \
                                                    }while(0)

    #define psoc_READY_TO_READ          do{ \
                                                        psoc_CSR_REG = psoc_CSR_RDY_TO_RD; \
                                                    }while(0)

    /* Master condition generation */
    #define psoc_GENERATE_START         do{ \
                                                        psoc_MCSR_REG = psoc_MCSR_START_GEN; \
                                                    }while(0)

    #if(CY_PSOC5A)
        #define psoc_GENERATE_RESTART \
                        do{ \
                            psoc_MCSR_REG = psoc_MCSR_RESTART_GEN; \
                            psoc_CSR_REG  = psoc_CSR_NAK;          \
                        }while(0)

        #define psoc_GENERATE_STOP      do{ \
                                                        psoc_CSR_REG = psoc_CSR_STOP_GEN; \
                                                    }while(0)

    #else   /* PSoC3 ES3 handlees zero lenght packets */
        #define psoc_GENERATE_RESTART \
                        do{ \
                            psoc_MCSR_REG = (psoc_MCSR_RESTART_GEN | \
                                                         psoc_MCSR_STOP_GEN);    \
                            psoc_CSR_REG  = psoc_CSR_TRANSMIT;       \
                        }while(0)

        #define psoc_GENERATE_STOP \
                        do{ \
                            psoc_MCSR_REG = psoc_MCSR_STOP_GEN; \
                            psoc_CSR_REG  = psoc_CSR_TRANSMIT;  \
                        }while(0)
    #endif /* (CY_PSOC5A) */

    /* Master manual APIs compatible defines */
    #define psoc_GENERATE_RESTART_MANUAL    psoc_GENERATE_RESTART
    #define psoc_GENERATE_STOP_MANUAL       psoc_GENERATE_STOP
    #define psoc_TRANSMIT_DATA_MANUAL       psoc_TRANSMIT_DATA
    #define psoc_READY_TO_READ_MANUAL       psoc_READY_TO_READ
    #define psoc_ACK_AND_RECEIVE_MANUAL     psoc_ACK_AND_RECEIVE

#else

    /* Masks to enalbe interrupts from Status register */
    #define psoc_STOP_IE_MASK           (psoc_STS_STOP_MASK)
    #define psoc_BYTE_COMPLETE_IE_MASK  (psoc_STS_BYTE_COMPLETE_MASK)

    /* FF compatibility: CSR gegisters definitions */
    #define psoc_CSR_LOST_ARB       (psoc_STS_LOST_ARB_MASK)
    #define psoc_CSR_STOP_STATUS    (psoc_STS_STOP_MASK)
    #define psoc_CSR_BUS_ERROR      (0x00u)
    #define psoc_CSR_ADDRESS        (psoc_STS_ADDR_MASK)
    #define psoc_CSR_TRANSMIT       (psoc_CTRL_TRANSMIT_MASK)
    #define psoc_CSR_LRB            (psoc_STS_LRB_MASK)
    #define psoc_CSR_LRB_NAK        (psoc_STS_LRB_MASK)
    #define psoc_CSR_LRB_ACK        (0x00u)
    #define psoc_CSR_BYTE_COMPLETE  (psoc_STS_BYTE_COMPLETE_MASK)

    /* FF compatibility: MCSR gegisters definitions */
    #define psoc_MCSR_REG           (psoc_CSR_REG)   /* UDB incoporates master and slave regs */
    #define psoc_MCSR_BUS_BUSY      (psoc_STS_BUSY_MASK)       /* Is bus is busy              */
    #define psoc_MCSR_START_GEN     (psoc_CTRL_START_MASK)     /* Generate Sart condition     */
    #define psoc_MCSR_RESTART_GEN   (psoc_CTRL_RESTART_MASK)   /* Generates RESTART condition */
    #define psoc_MCSR_MSTR_MODE     (psoc_STS_MASTER_MODE_MASK)/* Define if active Master     */

    /* Data to write into TX FIFO to release FSM */
    #define psoc_RELEASE_FSM         (0x00u)
    
    /* Check enable of module */
    #define psoc_I2C_ENABLE_REG     (psoc_CFG_REG)
    #define psoc_IS_I2C_ENABLE(reg) ((0u != ((reg) & psoc_ENABLE_MASTER)) || \
                                                 (0u != ((reg) & psoc_ENABLE_SLAVE)))

    #define psoc_IS_ENABLED         (0u != (psoc_CFG_REG & psoc_ENABLE_MS))

    /* Check start condition generation */
    #define psoc_CHECK_START_GEN(mcsr)  ((0u != (psoc_CFG_REG &        \
                                                             psoc_MCSR_START_GEN)) \
                                                    &&                                         \
                                                    (0u == ((mcsr) & psoc_MCSR_MSTR_MODE)))

    #define psoc_CLEAR_START_GEN        do{ \
                                                        psoc_CFG_REG &=                 \
                                                        ((uint8) ~psoc_MCSR_START_GEN); \
                                                    }while(0)


    /* Stop interrupt */
    #define psoc_ENABLE_INT_ON_STOP     do{ \
                                                       psoc_INT_MASK_REG |= psoc_STOP_IE_MASK; \
                                                    }while(0)

    #define psoc_DISABLE_INT_ON_STOP    do{ \
                                                        psoc_INT_MASK_REG &=                               \
                                                                             ((uint8) ~psoc_STOP_IE_MASK); \
                                                    }while(0)


    /* Transmit data */
    #define psoc_TRANSMIT_DATA      do{ \
                                                    psoc_CFG_REG = (psoc_CTRL_TRANSMIT_MASK | \
                                                                                psoc_CTRL_DEFAULT);       \
                                                    psoc_GO_REG  = psoc_RELEASE_FSM;          \
                                                }while(0)

    #define psoc_ACK_AND_TRANSMIT   psoc_TRANSMIT_DATA


    #define psoc_NAK_AND_TRANSMIT   do{ \
                                                    psoc_CFG_REG = (psoc_CTRL_NACK_MASK     | \
                                                                                psoc_CTRL_TRANSMIT_MASK | \
                                                                                psoc_CTRL_DEFAULT);       \
                                                    psoc_GO_REG  =  psoc_RELEASE_FSM;         \
                                                }while(0)

    /* Receive data */
    #define psoc_READY_TO_READ      do{ \
                                                    psoc_CFG_REG = psoc_CTRL_DEFAULT; \
                                                    psoc_GO_REG  =  psoc_RELEASE_FSM; \
                                                }while(0)

    #define psoc_ACK_AND_RECEIVE    psoc_READY_TO_READ

    #define psoc_NAK_AND_RECEIVE    do{ \
                                                    psoc_CFG_REG = (psoc_CTRL_NACK_MASK | \
                                                                                psoc_CTRL_DEFAULT);   \
                                                    psoc_GO_REG  =  psoc_RELEASE_FSM;     \
                                                }while(0)

    /* Master condition generation */
    #define psoc_GENERATE_START     do{ \
                                                    psoc_CFG_REG = (psoc_CTRL_START_MASK | \
                                                                                 psoc_CTRL_DEFAULT);   \
                                                    psoc_GO_REG  =  psoc_RELEASE_FSM;      \
                                                }while(0)

    #define psoc_GENERATE_RESTART   do{ \
                                                    psoc_CFG_REG = (psoc_CTRL_RESTART_MASK | \
                                                                                psoc_CTRL_NACK_MASK    | \
                                                                                psoc_CTRL_DEFAULT);      \
                                                    psoc_GO_REG  =  psoc_RELEASE_FSM;        \
                                                }while(0)


    #define psoc_GENERATE_STOP      do{ \
                                                    psoc_CFG_REG = (psoc_CTRL_NACK_MASK | \
                                                                                psoc_CTRL_STOP_MASK | \
                                                                                psoc_CTRL_DEFAULT);   \
                                                    psoc_GO_REG  =  psoc_RELEASE_FSM;     \
                                                }while(0)

    /* Master manual APIs compatible defines */
    /* These defines wait while byte complete is cleared after command issued */
    #define psoc_GENERATE_RESTART_MANUAL    \
                                        do{             \
                                            psoc_GENERATE_RESTART;                                    \
                                            while(psoc_CHECK_BYTE_COMPLETE(psoc_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define psoc_GENERATE_STOP_MANUAL   \
                                        do{         \
                                            psoc_GENERATE_STOP;                                       \
                                            while(psoc_CHECK_BYTE_COMPLETE(psoc_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define psoc_TRANSMIT_DATA_MANUAL   \
                                        do{         \
                                            psoc_TRANSMIT_DATA;                                       \
                                            while(psoc_CHECK_BYTE_COMPLETE(psoc_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define psoc_READY_TO_READ_MANUAL   \
                                        do{         \
                                            psoc_READY_TO_READ;      \
                                            while(psoc_CHECK_BYTE_COMPLETE(psoc_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define psoc_ACK_AND_RECEIVE_MANUAL \
                                        do{         \
                                            psoc_ACK_AND_RECEIVE;                                     \
                                            while(psoc_CHECK_BYTE_COMPLETE(psoc_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)
#endif /* (psoc_FF_IMPLEMENTED) */

/* Comon for FF and UDB: used to release bus after lost arb */
#define psoc_BUS_RELEASE    psoc_READY_TO_READ


/***************************************
*     Default register init constants
***************************************/

#define psoc_DISABLE    (0u)
#define psoc_ENABLE     (1u)

#if(psoc_FF_IMPLEMENTED)
    /* psoc_XCFG_REG: bits definition */
    #define psoc_DEFAULT_XCFG_HW_ADDR_EN ((psoc_HW_ADRR_DECODE) ? \
                                                        (psoc_XCFG_HDWR_ADDR_EN) : (0u))

    #define psoc_DEFAULT_XCFG_I2C_ON    ((psoc_WAKEUP_ENABLED) ? \
                                                        (psoc_XCFG_I2C_ON) : (0u))


    #define psoc_DEFAULT_CFG_SIO_SELECT ((psoc_I2C1_SIO_PAIR) ? \
                                                        (psoc_CFG_SIO_SELECT) : (0u))


    /* psoc_CFG_REG: bits definition */
    #define psoc_DEFAULT_CFG_PSELECT    ((psoc_WAKEUP_ENABLED) ? \
                                                        (psoc_CFG_PSELECT) : (0u))

    #define psoc_DEFAULT_CLK_RATE0  ((psoc_DATA_RATE <= 50u) ?        \
                                                    (psoc_CFG_CLK_RATE_050) :     \
                                                    ((psoc_DATA_RATE <= 100u) ?   \
                                                        (psoc_CFG_CLK_RATE_100) : \
                                                        (psoc_CFG_CLK_RATE_400)))

    #define psoc_DEFAULT_CLK_RATE1  ((psoc_DATA_RATE <= 50u) ?           \
                                                 (psoc_CFG_CLK_RATE_LESS_EQUAL_50) : \
                                                 (psoc_CFG_CLK_RATE_GRATER_50))

    #define psoc_DEFAULT_CLK_RATE   ((CY_PSOC5A) ? (psoc_DEFAULT_CLK_RATE0) : \
                                                               (psoc_DEFAULT_CLK_RATE1))


    #define psoc_ENABLE_MASTER      ((psoc_MODE_MASTER_ENABLED) ? \
                                                 (psoc_CFG_EN_MSTR) : (0u))

    #define psoc_ENABLE_SLAVE       ((psoc_MODE_SLAVE_ENABLED) ? \
                                                 (psoc_CFG_EN_SLAVE) : (0u))

    #define psoc_ENABLE_MS      (psoc_ENABLE_MASTER | psoc_ENABLE_SLAVE)


    /* psoc_DEFAULT_XCFG_REG */
    #define psoc_DEFAULT_XCFG   (psoc_XCFG_CLK_EN         | \
                                             psoc_DEFAULT_XCFG_I2C_ON | \
                                             psoc_DEFAULT_XCFG_HW_ADDR_EN)

    /* psoc_DEFAULT_CFG_REG */
    #define psoc_DEFAULT_CFG    (psoc_DEFAULT_CFG_SIO_SELECT | \
                                             psoc_DEFAULT_CFG_PSELECT    | \
                                             psoc_DEFAULT_CLK_RATE       | \
                                             psoc_ENABLE_MASTER          | \
                                             psoc_ENABLE_SLAVE)

    /*psoc_DEFAULT_DIVIDE_FACTOR_REG */
    #define psoc_DEFAULT_DIVIDE_FACTOR  ((CY_PSOC5A) ? ((uint8) 4u) : ((uint16) 15u))

#else
    /* psoc_CFG_REG: bits definition  */
    #define psoc_ENABLE_MASTER  ((psoc_MODE_MASTER_ENABLED) ? \
                                             (psoc_CTRL_ENABLE_MASTER_MASK) : (0u))

    #define psoc_ENABLE_SLAVE   ((psoc_MODE_SLAVE_ENABLED) ? \
                                             (psoc_CTRL_ENABLE_SLAVE_MASK) : (0u))

    #define psoc_ENABLE_MS      (psoc_ENABLE_MASTER | psoc_ENABLE_SLAVE)


    #define psoc_DEFAULT_CTRL_ANY_ADDR   ((psoc_HW_ADRR_DECODE) ? \
                                                      (0u) : (psoc_CTRL_ANY_ADDRESS_MASK))

    /* psoc_DEFAULT_CFG_REG */
    #define psoc_DEFAULT_CFG    (psoc_DEFAULT_CTRL_ANY_ADDR)

    /* All CTRL default bits to be used in macro */
    #define psoc_CTRL_DEFAULT   (psoc_DEFAULT_CTRL_ANY_ADDR | psoc_ENABLE_MS)

    /* Master clock generator: d0 and d1 */
    #define psoc_MCLK_PERIOD_VALUE  (0x0Fu)
    #define psoc_MCLK_COMPARE_VALUE (0x08u)

    /* Slave bit-counter: contorol period */
    #define psoc_PERIOD_VALUE       (0x07u)

    /* psoc_DEFAULT_INT_MASK */
    #define psoc_DEFAULT_INT_MASK   (psoc_BYTE_COMPLETE_IE_MASK)

    /* psoc_DEFAULT_MCLK_PRD_REG */
    #define psoc_DEFAULT_MCLK_PRD   (psoc_MCLK_PERIOD_VALUE)

    /* psoc_DEFAULT_MCLK_CMP_REG */
    #define psoc_DEFAULT_MCLK_CMP   (psoc_MCLK_COMPARE_VALUE)

    /* psoc_DEFAULT_PERIOD_REG */
    #define psoc_DEFAULT_PERIOD     (psoc_PERIOD_VALUE)

#endif /* (psoc_FF_IMPLEMENTED) */


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from I2C 3.20
 */
 
#define psoc_SSTAT_RD_ERR       (0x08u)
#define psoc_SSTAT_WR_ERR       (0x80u)
#define psoc_MSTR_SLAVE_BUSY    (psoc_MSTR_NOT_READY)
#define psoc_MSTAT_ERR_BUF_OVFL (0x80u)
#define psoc_SSTAT_RD_CMPT      (psoc_SSTAT_RD_CMPLT)
#define psoc_SSTAT_WR_CMPT      (psoc_SSTAT_WR_CMPLT)
#define psoc_MODE_MULTI_MASTER_ENABLE    (psoc_MODE_MULTI_MASTER_MASK)
#define psoc_DATA_RATE_50       (50u)
#define psoc_DATA_RATE_100      (100u)
#define psoc_DEV_MASK           (0xF0u)
#define psoc_SM_SL_STOP         (0x14u)
#define psoc_SM_MASTER_IDLE     (0x40u)
#define psoc_HDWR_DECODE        (0x01u)

#endif /* CY_I2C_psoc_H */


/* [] END OF FILE */
