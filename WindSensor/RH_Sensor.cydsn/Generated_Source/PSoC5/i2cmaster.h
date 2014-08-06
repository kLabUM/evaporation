/*******************************************************************************
* File Name: i2cmaster.h
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

#if !defined(CY_I2C_i2cmaster_H)
#define CY_I2C_i2cmaster_H

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

#define i2cmaster_IMPLEMENTATION     (1u)
#define i2cmaster_MODE               (2u)
#define i2cmaster_ENABLE_WAKEUP      (0u)
#define i2cmaster_ADDR_DECODE        (1u)
#define i2cmaster_UDB_INTRN_CLOCK    (0u)


/* I2C implementation enum */
#define i2cmaster_UDB    (0x00u)
#define i2cmaster_FF     (0x01u)

#define i2cmaster_FF_IMPLEMENTED     (i2cmaster_FF  == i2cmaster_IMPLEMENTATION)
#define i2cmaster_UDB_IMPLEMENTED    (i2cmaster_UDB == i2cmaster_IMPLEMENTATION)

#define i2cmaster_UDB_INTRN_CLOCK_ENABLED    (i2cmaster_UDB_IMPLEMENTED && \
                                                     (0u != i2cmaster_UDB_INTRN_CLOCK))
/* I2C modes enum */
#define i2cmaster_MODE_SLAVE                 (0x01u)
#define i2cmaster_MODE_MASTER                (0x02u)
#define i2cmaster_MODE_MULTI_MASTER          (0x06u)
#define i2cmaster_MODE_MULTI_MASTER_SLAVE    (0x07u)
#define i2cmaster_MODE_MULTI_MASTER_MASK     (0x04u)

#define i2cmaster_MODE_SLAVE_ENABLED         (0u != (i2cmaster_MODE_SLAVE  & i2cmaster_MODE))
#define i2cmaster_MODE_MASTER_ENABLED        (0u != (i2cmaster_MODE_MASTER & i2cmaster_MODE))
#define i2cmaster_MODE_MULTI_MASTER_ENABLED  (0u != (i2cmaster_MODE_MULTI_MASTER_MASK & \
                                                            i2cmaster_MODE))
#define i2cmaster_MODE_MULTI_MASTER_SLAVE_ENABLED    (i2cmaster_MODE_MULTI_MASTER_SLAVE == \
                                                             i2cmaster_MODE)

/* Address detection enum */
#define i2cmaster_SW_DECODE      (0x00u)
#define i2cmaster_HW_DECODE      (0x01u)

#define i2cmaster_SW_ADRR_DECODE             (i2cmaster_SW_DECODE == i2cmaster_ADDR_DECODE)
#define i2cmaster_HW_ADRR_DECODE             (i2cmaster_HW_DECODE == i2cmaster_ADDR_DECODE)

/* Wakeup enabled */
#define i2cmaster_WAKEUP_ENABLED             (0u != i2cmaster_ENABLE_WAKEUP)

/* Adds bootloader APIs to component */
#define i2cmaster_BOOTLOADER_INTERFACE_ENABLED   (i2cmaster_MODE_SLAVE_ENABLED && \
                                                            ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_i2cmaster) || \
                                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)))

/* Timeout functionality */
#define i2cmaster_TIMEOUT_ENABLE             (0u)
#define i2cmaster_TIMEOUT_SCL_TMOUT_ENABLE   (0u)
#define i2cmaster_TIMEOUT_SDA_TMOUT_ENABLE   (0u)
#define i2cmaster_TIMEOUT_PRESCALER_ENABLE   (0u)
#define i2cmaster_TIMEOUT_IMPLEMENTATION     (0u)

/* Convert to boolean */
#define i2cmaster_TIMEOUT_ENABLED            (0u != i2cmaster_TIMEOUT_ENABLE)
#define i2cmaster_TIMEOUT_SCL_TMOUT_ENABLED  (0u != i2cmaster_TIMEOUT_SCL_TMOUT_ENABLE)
#define i2cmaster_TIMEOUT_SDA_TMOUT_ENABLED  (0u != i2cmaster_TIMEOUT_SDA_TMOUT_ENABLE)
#define i2cmaster_TIMEOUT_PRESCALER_ENABLED  (0u != i2cmaster_TIMEOUT_PRESCALER_ENABLE)

/* Timeout implementation enum. */
#define i2cmaster_TIMEOUT_UDB    (0x00u)
#define i2cmaster_TIMEOUT_FF     (0x01u)

#define i2cmaster_TIMEOUT_FF_IMPLEMENTED     (i2cmaster_TIMEOUT_FF  == \
                                                        i2cmaster_TIMEOUT_IMPLEMENTATION)
#define i2cmaster_TIMEOUT_UDB_IMPLEMENTED    (i2cmaster_TIMEOUT_UDB == \
                                                        i2cmaster_TIMEOUT_IMPLEMENTATION)

#define i2cmaster_TIMEOUT_FF_ENABLED         (i2cmaster_TIMEOUT_ENABLED && \
                                                     i2cmaster_TIMEOUT_FF_IMPLEMENTED && \
                                                     CY_PSOC5LP)

#define i2cmaster_TIMEOUT_UDB_ENABLED        (i2cmaster_TIMEOUT_ENABLED && \
                                                     i2cmaster_TIMEOUT_UDB_IMPLEMENTED)

#define i2cmaster_EXTERN_I2C_INTR_HANDLER    (0u)
#define i2cmaster_EXTERN_TMOUT_INTR_HANDLER  (0u)

#define i2cmaster_INTERN_I2C_INTR_HANDLER    (0u == i2cmaster_EXTERN_I2C_INTR_HANDLER)
#define i2cmaster_INTERN_TMOUT_INTR_HANDLER  (0u == i2cmaster_EXTERN_TMOUT_INTR_HANDLER)


/***************************************
*       Type defines
***************************************/

/* Structure to save registers before go to sleep */
typedef struct
{
    uint8 enableState;

    #if(i2cmaster_FF_IMPLEMENTED)
        uint8 xcfg;
        uint8 cfg;

        #if(i2cmaster_MODE_SLAVE_ENABLED)
            uint8 addr;
        #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */

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

            #if(i2cmaster_MODE_SLAVE_ENABLED)
                uint8 addr;
            #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */
        #endif     /* (CY_UDB_V0) */

    #endif /* (i2cmaster_FF_IMPLEMENTED) */

    #if(i2cmaster_TIMEOUT_ENABLED)
        uint16 tmoutCfg;
        uint8  tmoutIntr;

        #if(i2cmaster_TIMEOUT_PRESCALER_ENABLED && CY_UDB_V0)
            uint8 tmoutPrd;
        #endif /* (i2cmaster_TIMEOUT_PRESCALER_ENABLED && CY_UDB_V0) */

    #endif /* (i2cmaster_TIMEOUT_ENABLED) */

} i2cmaster_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void i2cmaster_Init(void)                            ;
void i2cmaster_Enable(void)                          ;

void i2cmaster_Start(void)                           ;
void i2cmaster_Stop(void)                            ;

#define i2cmaster_EnableInt()        CyIntEnable      (i2cmaster_ISR_NUMBER)
#define i2cmaster_DisableInt()       CyIntDisable     (i2cmaster_ISR_NUMBER)
#define i2cmaster_ClearPendingInt()  CyIntClearPending(i2cmaster_ISR_NUMBER)
#define i2cmaster_SetPendingInt()    CyIntSetPending  (i2cmaster_ISR_NUMBER)

void i2cmaster_SaveConfig(void)                      ;
void i2cmaster_Sleep(void)                           ;
void i2cmaster_RestoreConfig(void)                   ;
void i2cmaster_Wakeup(void)                          ;

/* I2C Master functions prototypes */
#if(i2cmaster_MODE_MASTER_ENABLED)
    /* Read and Clear status functions */
    uint8 i2cmaster_MasterStatus(void)                ;
    uint8 i2cmaster_MasterClearStatus(void)           ;

    /* Interrupt based operation functions */
    uint8 i2cmaster_MasterWriteBuf(uint8 slaveAddress, uint8 * wrData, uint8 cnt, uint8 mode) \
                                                            ;
    uint8 i2cmaster_MasterReadBuf(uint8 slaveAddress, uint8 * rdData, uint8 cnt, uint8 mode) \
                                                            ;
    uint8 i2cmaster_MasterGetReadBufSize(void)       ;
    uint8 i2cmaster_MasterGetWriteBufSize(void)      ;
    void  i2cmaster_MasterClearReadBuf(void)         ;
    void  i2cmaster_MasterClearWriteBuf(void)        ;

    /* Manual operation functions */
    uint8 i2cmaster_MasterSendStart(uint8 slaveAddress, uint8 R_nW) \
                                                            ;
    uint8 i2cmaster_MasterSendRestart(uint8 slaveAddress, uint8 R_nW) \
                                                            ;
    uint8 i2cmaster_MasterSendStop(void)             ;
    uint8 i2cmaster_MasterWriteByte(uint8 theByte)   ;
    uint8 i2cmaster_MasterReadByte(uint8 acknNak)    ;

    /* This fake function use as workaround */
    void  i2cmaster_Workaround(void)                 ;

#endif /* (i2cmaster_MODE_MASTER_ENABLED) */

/* I2C Slave functions prototypes */
#if(i2cmaster_MODE_SLAVE_ENABLED)
    /* Read and Clear status functions */
    uint8 i2cmaster_SlaveStatus(void)                ;
    uint8 i2cmaster_SlaveClearReadStatus(void)       ;
    uint8 i2cmaster_SlaveClearWriteStatus(void)      ;

    void  i2cmaster_SlaveSetAddress(uint8 address)   ;

    /* Interrupt based operation functions */
    void  i2cmaster_SlaveInitReadBuf(uint8 * rdBuf, uint8 bufSize) \
                                                            ;
    void  i2cmaster_SlaveInitWriteBuf(uint8 * wrBuf, uint8 bufSize) \
                                                            ;
    uint8 i2cmaster_SlaveGetReadBufSize(void)        ;
    uint8 i2cmaster_SlaveGetWriteBufSize(void)       ;
    void  i2cmaster_SlaveClearReadBuf(void)          ;
    void  i2cmaster_SlaveClearWriteBuf(void)         ;

    /* Communication bootloader I2C Slave APIs */
    #if defined(CYDEV_BOOTLOADER_IO_COMP) && (i2cmaster_BOOTLOADER_INTERFACE_ENABLED)
        /* Physical layer functions */
        void     i2cmaster_CyBtldrCommStart(void) CYSMALL \
                                                            ;
        void     i2cmaster_CyBtldrCommStop(void)  CYSMALL \
                                                            ;
        void     i2cmaster_CyBtldrCommReset(void) CYSMALL \
                                                            ;
        cystatus i2cmaster_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) \
                                                        CYSMALL ;
        cystatus i2cmaster_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)  CYSMALL \
                                                            ;

        #if(CYDEV_BOOTLOADER_IO_COMP == CyBtldr_i2cmaster)
            #define CyBtldrCommStart    i2cmaster_CyBtldrCommStart
            #define CyBtldrCommStop     i2cmaster_CyBtldrCommStop
            #define CyBtldrCommReset    i2cmaster_CyBtldrCommReset
            #define CyBtldrCommWrite    i2cmaster_CyBtldrCommWrite
            #define CyBtldrCommRead     i2cmaster_CyBtldrCommRead
        #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_i2cmaster) */

        /* Size of Read/Write buffers for I2C bootloader  */
        #define i2cmaster_BTLDR_SIZEOF_READ_BUFFER   (0x80u)
        #define i2cmaster_BTLDR_SIZEOF_WRITE_BUFFER  (0x80u)
        #define i2cmaster_MIN_UNT16(a, b)            ( ((uint16)(a) < (b)) ? ((uint16) (a)) : ((uint16) (b)) )
        #define i2cmaster_WAIT_1_MS                  (1u)

    #endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (i2cmaster_BOOTLOADER_INTERFACE_ENABLED) */

#endif /* (i2cmaster_MODE_SLAVE_ENABLED) */

/* I2C interrupt handler */
CY_ISR_PROTO(i2cmaster_ISR);
#if((i2cmaster_FF_IMPLEMENTED) || (i2cmaster_WAKEUP_ENABLED))
    CY_ISR_PROTO(i2cmaster_WAKEUP_ISR);
#endif /* ((i2cmaster_FF_IMPLEMENTED) || (i2cmaster_WAKEUP_ENABLED)) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 i2cmaster_initVar;


/***************************************
*   Initial Parameter Constants
***************************************/

#define i2cmaster_DATA_RATE          (100u)
#define i2cmaster_DEFAULT_ADDR       (8u)
#define i2cmaster_I2C_PAIR_SELECTED  (0u)

/* I2C pair enum */
#define i2cmaster_I2C_PAIR_ANY   (0x01u) /* Any pins for I2C */
#define i2cmaster_I2C_PAIR0      (0x01u) /* I2C0: (SCL = P12[4]) && (SCL = P12[5]) */
#define i2cmaster_I2C_PAIR1      (0x02u) /* I2C1: (SCL = P12[0]) && (SDA = P12[1]) */

#define i2cmaster_I2C1_SIO_PAIR  (i2cmaster_I2C_PAIR1 == i2cmaster_I2C_PAIR_SELECTED)
#define i2cmaster_I2C0_SIO_PAIR  (i2cmaster_I2C_PAIR0 == i2cmaster_I2C_PAIR_SELECTED)


/***************************************
*            API Constants
***************************************/

/* Master/Slave control constants */
#define i2cmaster_READ_XFER_MODE     (0x01u) /* Read */
#define i2cmaster_WRITE_XFER_MODE    (0x00u) /* Write */
#define i2cmaster_ACK_DATA           (0x01u) /* Send ACK */
#define i2cmaster_NAK_DATA           (0x00u) /* Send NAK */
#define i2cmaster_OVERFLOW_RETURN    (0xFFu) /* Senf on bus in case of overflow */

#if(i2cmaster_MODE_MASTER_ENABLED)
    /* "Mode" constants for MasterWriteBuf() or MasterReadBuf() function */
    #define i2cmaster_MODE_COMPLETE_XFER     (0x00u) /* Full transfer with Start and Stop */
    #define i2cmaster_MODE_REPEAT_START      (0x01u) /* Begin with a ReStart instead of a Start */
    #define i2cmaster_MODE_NO_STOP           (0x02u) /* Complete the transfer without a Stop */

    /* Master status */
    #define i2cmaster_MSTAT_CLEAR            (0x00u) /* Clear (init) status value */

    #define i2cmaster_MSTAT_RD_CMPLT         (0x01u) /* Read complete */
    #define i2cmaster_MSTAT_WR_CMPLT         (0x02u) /* Write complete */
    #define i2cmaster_MSTAT_XFER_INP         (0x04u) /* Master transfer in progress */
    #define i2cmaster_MSTAT_XFER_HALT        (0x08u) /* Transfer is halted */

    #define i2cmaster_MSTAT_ERR_MASK         (0xF0u) /* Mask for all errors */
    #define i2cmaster_MSTAT_ERR_SHORT_XFER   (0x10u) /* Master NAKed before end of packet */
    #define i2cmaster_MSTAT_ERR_ADDR_NAK     (0x20u) /* Slave did not ACK */
    #define i2cmaster_MSTAT_ERR_ARB_LOST     (0x40u) /* Master lost arbitration during communication */
    #define i2cmaster_MSTAT_ERR_XFER         (0x80u) /* Error during transfer */

    /* Master API returns */
    #define i2cmaster_MSTR_NO_ERROR          (0x00u) /* Function complete without error */
    #define i2cmaster_MSTR_BUS_BUSY          (0x01u) /* Bus is busy, process not started */
    #define i2cmaster_MSTR_NOT_READY         (0x02u) /* Master not Master on the bus or */
                                                            /*  Slave operation in progress */
    #define i2cmaster_MSTR_ERR_LB_NAK        (0x03u) /* Last Byte Naked */
    #define i2cmaster_MSTR_ERR_ARB_LOST      (0x04u) /* Master lost arbitration during communication */
    #define i2cmaster_MSTR_ERR_ABORT_START_GEN  (0x05u) /* Master did not generate Start, the Slave */
                                                               /* was addressed before */

#endif /* (i2cmaster_MODE_MASTER_ENABLED) */

#if(i2cmaster_MODE_SLAVE_ENABLED)
    /* Slave Status Constants */
    #define i2cmaster_SSTAT_RD_CMPLT     (0x01u) /* Read transfer complete */
    #define i2cmaster_SSTAT_RD_BUSY      (0x02u) /* Read transfer in progress */
    #define i2cmaster_SSTAT_RD_ERR_OVFL  (0x04u) /* Read overflow Error */
    #define i2cmaster_SSTAT_RD_MASK      (0x0Fu) /* Read Status Mask */
    #define i2cmaster_SSTAT_RD_NO_ERR    (0x00u) /* Read no Error */

    #define i2cmaster_SSTAT_WR_CMPLT     (0x10u) /* Write transfer complete */
    #define i2cmaster_SSTAT_WR_BUSY      (0x20u) /* Write transfer in progress */
    #define i2cmaster_SSTAT_WR_ERR_OVFL  (0x40u) /* Write overflow Error */
    #define i2cmaster_SSTAT_WR_MASK      (0xF0u) /* Write Status Mask  */
    #define i2cmaster_SSTAT_WR_NO_ERR    (0x00u) /* Write no Error */

    #define i2cmaster_SSTAT_RD_CLEAR     (0x0Du) /* Read Status clear */
    #define i2cmaster_SSTAT_WR_CLEAR     (0xD0u) /* Write Status Clear */

#endif /* (i2cmaster_MODE_SLAVE_ENABLED) */


/***************************************
*       I2C state machine constants
***************************************/

/* Default slave address states */
#define  i2cmaster_SM_IDLE           (0x10u) /* Default state - IDLE */
#define  i2cmaster_SM_EXIT_IDLE      (0x00u) /* Pass master and slave processing and go to IDLE */

/* Slave mode states */
#define  i2cmaster_SM_SLAVE          (i2cmaster_SM_IDLE) /* Any Slave state */
#define  i2cmaster_SM_SL_WR_DATA     (0x11u) /* Master writes data to slzve  */
#define  i2cmaster_SM_SL_RD_DATA     (0x12u) /* Master reads data from slave */

/* Master mode states */
#define  i2cmaster_SM_MASTER         (0x40u) /* Any master state */

#define  i2cmaster_SM_MSTR_RD        (0x08u) /* Any master read state          */
#define  i2cmaster_SM_MSTR_RD_ADDR   (0x49u) /* Master sends address with read */
#define  i2cmaster_SM_MSTR_RD_DATA   (0x4Au) /* Master reads data              */

#define  i2cmaster_SM_MSTR_WR        (0x04u) /* Any master read state           */
#define  i2cmaster_SM_MSTR_WR_ADDR   (0x45u) /* Master sends address with write */
#define  i2cmaster_SM_MSTR_WR_DATA   (0x46u) /* Master writes data              */

#define  i2cmaster_SM_MSTR_HALT      (0x60u) /* Master waits for ReStart */

#define i2cmaster_CHECK_SM_MASTER    (0u != (i2cmaster_SM_MASTER & i2cmaster_state))
#define i2cmaster_CHECK_SM_SLAVE     (0u != (i2cmaster_SM_SLAVE  & i2cmaster_state))


/***************************************
*              Registers
***************************************/

#if(i2cmaster_FF_IMPLEMENTED)
    /* Fixed Function registers */
    #define i2cmaster_XCFG_REG           (* (reg8 *) i2cmaster_I2C_FF__XCFG)
    #define i2cmaster_XCFG_PTR           (  (reg8 *) i2cmaster_I2C_FF__XCFG)

    #define i2cmaster_ADDR_REG           (* (reg8 *) i2cmaster_I2C_FF__ADR)
    #define i2cmaster_ADDR_PTR           (  (reg8 *) i2cmaster_I2C_FF__ADR)

    #define i2cmaster_CFG_REG            (* (reg8 *) i2cmaster_I2C_FF__CFG)
    #define i2cmaster_CFG_PTR            (  (reg8 *) i2cmaster_I2C_FF__CFG)

    #define i2cmaster_CSR_REG            (* (reg8 *) i2cmaster_I2C_FF__CSR)
    #define i2cmaster_CSR_PTR            (  (reg8 *) i2cmaster_I2C_FF__CSR)

    #define i2cmaster_DATA_REG           (* (reg8 *) i2cmaster_I2C_FF__D)
    #define i2cmaster_DATA_PTR           (  (reg8 *) i2cmaster_I2C_FF__D)

    #define i2cmaster_MCSR_REG           (* (reg8 *) i2cmaster_I2C_FF__MCSR)
    #define i2cmaster_MCSR_PTR           (  (reg8 *) i2cmaster_I2C_FF__MCSR)

    #define i2cmaster_ACT_PWRMGR_REG     (* (reg8 *) i2cmaster_I2C_FF__PM_ACT_CFG)
    #define i2cmaster_ACT_PWRMGR_PTR     (  (reg8 *) i2cmaster_I2C_FF__PM_ACT_CFG)
    #define i2cmaster_ACT_PWR_EN         (  (uint8)  i2cmaster_I2C_FF__PM_ACT_MSK)

    #define i2cmaster_STBY_PWRMGR_REG    (* (reg8 *) i2cmaster_I2C_FF__PM_STBY_CFG)
    #define i2cmaster_STBY_PWRMGR_PTR    (  (reg8 *) i2cmaster_I2C_FF__PM_STBY_CFG)
    #define i2cmaster_STBY_PWR_EN        (  (uint8)  i2cmaster_I2C_FF__PM_STBY_MSK)

    #define i2cmaster_PWRSYS_CR1_REG     (* (reg8 *) CYREG_PWRSYS_CR1)
    #define i2cmaster_PWRSYS_CR1_PTR     (  (reg8 *) CYREG_PWRSYS_CR1)

    /* Clock divider register depends on silicon */
    #if(CY_PSOC5A)
        #define i2cmaster_CLKDIV_REG     (* (reg8 *) i2cmaster_I2C_FF__CLK_DIV)
        #define i2cmaster_CLKDIV_PTR     (  (reg8 *) i2cmaster_I2C_FF__CLK_DIV)

    #else
        #define i2cmaster_CLKDIV1_REG    (* (reg8 *) i2cmaster_I2C_FF__CLK_DIV1)
        #define i2cmaster_CLKDIV1_PTR    (  (reg8 *) i2cmaster_I2C_FF__CLK_DIV1)

        #define i2cmaster_CLKDIV2_REG    (* (reg8 *) i2cmaster_I2C_FF__CLK_DIV2)
        #define i2cmaster_CLKDIV2_PTR    (  (reg8 *) i2cmaster_I2C_FF__CLK_DIV2)

    #endif /* (CY_PSOC5A) */

#else
    /* UDB implementation registers */
    #define i2cmaster_CFG_REG    (* (reg8 *) \
                                           i2cmaster_bI2C_UDB_SyncCtl_CtrlReg__CONTROL_REG)
    #define i2cmaster_CFG_PTR    (  (reg8 *) \
                                           i2cmaster_bI2C_UDB_SyncCtl_CtrlReg__CONTROL_REG)

    #define i2cmaster_CSR_REG        (* (reg8 *) i2cmaster_bI2C_UDB_StsReg__STATUS_REG)
    #define i2cmaster_CSR_PTR        (  (reg8 *) i2cmaster_bI2C_UDB_StsReg__STATUS_REG)

    #define i2cmaster_INT_MASK_REG   (* (reg8 *) i2cmaster_bI2C_UDB_StsReg__MASK_REG)
    #define i2cmaster_INT_MASK_PTR   (  (reg8 *) i2cmaster_bI2C_UDB_StsReg__MASK_REG)

    #define i2cmaster_INT_ENABLE_REG (* (reg8 *) i2cmaster_bI2C_UDB_StsReg__STATUS_AUX_CTL_REG)
    #define i2cmaster_INT_ENABLE_PTR (  (reg8 *) i2cmaster_bI2C_UDB_StsReg__STATUS_AUX_CTL_REG)

    #define i2cmaster_DATA_REG       (* (reg8 *) i2cmaster_bI2C_UDB_Shifter_u0__A0_REG)
    #define i2cmaster_DATA_PTR       (  (reg8 *) i2cmaster_bI2C_UDB_Shifter_u0__A0_REG)

    #define i2cmaster_GO_REG         (* (reg8 *) i2cmaster_bI2C_UDB_Shifter_u0__F1_REG)
    #define i2cmaster_GO_PTR         (  (reg8 *) i2cmaster_bI2C_UDB_Shifter_u0__F1_REG)

    #define i2cmaster_MCLK_PRD_REG   (* (reg8 *) i2cmaster_bI2C_UDB_Master_ClkGen_u0__D0_REG)
    #define i2cmaster_MCLK_PRD_PTR   (  (reg8 *) i2cmaster_bI2C_UDB_Master_ClkGen_u0__D0_REG)

    #define i2cmaster_MCLK_CMP_REG   (* (reg8 *) i2cmaster_bI2C_UDB_Master_ClkGen_u0__D1_REG)
    #define i2cmaster_MCLK_CMP_PTR   (  (reg8 *) i2cmaster_bI2C_UDB_Master_ClkGen_u0__D1_REG)

    #if(i2cmaster_MODE_SLAVE_ENABLED)
        #define i2cmaster_ADDR_REG       (* (reg8 *) i2cmaster_bI2C_UDB_Shifter_u0__D0_REG)
        #define i2cmaster_ADDR_PTR       (  (reg8 *) i2cmaster_bI2C_UDB_Shifter_u0__D0_REG)

        #define i2cmaster_PERIOD_REG     (* (reg8 *) i2cmaster_bI2C_UDB_Slave_BitCounter__PERIOD_REG)
        #define i2cmaster_PERIOD_PTR     (  (reg8 *) i2cmaster_bI2C_UDB_Slave_BitCounter__PERIOD_REG)

        #define i2cmaster_COUNTER_REG    (* (reg8 *) i2cmaster_bI2C_UDB_Slave_BitCounter__COUNT_REG)
        #define i2cmaster_COUNTER_PTR    (  (reg8 *) i2cmaster_bI2C_UDB_Slave_BitCounter__COUNT_REG)

        #define i2cmaster_COUNTER_AUX_CTL_REG  (* (reg8 *) \
                                                        i2cmaster_bI2C_UDB_Slave_BitCounter__CONTROL_AUX_CTL_REG)
        #define i2cmaster_COUNTER_AUX_CTL_PTR  (  (reg8 *) \
                                                        i2cmaster_bI2C_UDB_Slave_BitCounter__CONTROL_AUX_CTL_REG)

    #endif /* (i2cmaster_MODE_SLAVE_ENABLED) */

#endif /* (i2cmaster_FF_IMPLEMENTED) */


/***************************************
*        Registers Constants
***************************************/

/* i2cmaster_I2C_IRQ */
#define i2cmaster_ISR_NUMBER     ((uint8) i2cmaster_I2C_IRQ__INTC_NUMBER)
#define i2cmaster_ISR_PRIORITY   ((uint8) i2cmaster_I2C_IRQ__INTC_PRIOR_NUM)

/* I2C Slave Data Register */
#define i2cmaster_SLAVE_ADDR_MASK    (0x7Fu)
#define i2cmaster_SLAVE_ADDR_SHIFT   (0x01u)
#define i2cmaster_DATA_MASK          (0xFFu)
#define i2cmaster_READ_FLAG          (0x01u)

#define i2cmaster_FF_RESET_DELAY     (0x02u)

#if(i2cmaster_FF_IMPLEMENTED)
    /* XCFG I2C Extended Configuration Register */
    #define i2cmaster_XCFG_CLK_EN        (0x80u) /* Enable gated clock to block */
    #define i2cmaster_XCFG_I2C_ON        (0x40u) /* Enable I2C as wake up source*/
    #define i2cmaster_XCFG_RDY_TO_SLEEP  (0x20u) /* I2C ready go to sleep */
    #define i2cmaster_XCFG_FORCE_NACK    (0x10u) /* Force NACK all incomming transactions */
    #define i2cmaster_XCFG_NO_BC_INT     (0x08u) /* No interrupt on byte complete */
    #define i2cmaster_XCFG_BUF_MODE      (0x02u) /* Enable buffer mode */
    #define i2cmaster_XCFG_HDWR_ADDR_EN  (0x01u) /* Enable Hardware address match */

    /* CFG I2C Configuration Register */
    #define i2cmaster_CFG_SIO_SELECT     (0x80u) /* Pin Select for SCL/SDA lines */
    #define i2cmaster_CFG_PSELECT        (0x40u) /* Pin Select */
    #define i2cmaster_CFG_BUS_ERR_IE     (0x20u) /* Bus Error Interrupt Enable */
    #define i2cmaster_CFG_STOP_IE        (0x10u) /* Enable Interrupt on STOP condition */
    #define i2cmaster_CFG_CLK_RATE_MSK   (0x0Cu) /* Clock rate select  **CHECK**  */
    #define i2cmaster_CFG_CLK_RATE_100   (0x00u) /* Clock rate select 100K */
    #define i2cmaster_CFG_CLK_RATE_400   (0x04u) /* Clock rate select 400K */
    #define i2cmaster_CFG_CLK_RATE_050   (0x08u) /* Clock rate select 50K  */
    #define i2cmaster_CFG_CLK_RATE_RSVD  (0x0Cu) /* Clock rate select Invalid */
    #define i2cmaster_CFG_EN_MSTR        (0x02u) /* Enable Master operation */
    #define i2cmaster_CFG_EN_SLAVE       (0x01u) /* Enable Slave operation */

    #define i2cmaster_CFG_CLK_RATE_LESS_EQUAL_50 (0x04u) /* Clock rate select <= 50kHz */
    #define i2cmaster_CFG_CLK_RATE_GRATER_50     (0x00u) /* Clock rate select > 50kHz */

    /* CSR I2C Control and Status Register */
    #define i2cmaster_CSR_BUS_ERROR      (0x80u) /* Active high when bus error has occured */
    #define i2cmaster_CSR_LOST_ARB       (0x40u) /* Set to 1 if lost arbitration in host mode */
    #define i2cmaster_CSR_STOP_STATUS    (0x20u) /* Set if Stop has been detected */
    #define i2cmaster_CSR_ACK            (0x10u) /* ACK response */
    #define i2cmaster_CSR_NAK            (0x00u) /* NAK response */
    #define i2cmaster_CSR_ADDRESS        (0x08u) /* Set in firmware 0 = status bit, 1 Address is slave */
    #define i2cmaster_CSR_TRANSMIT       (0x04u) /* Set in firmware 1 = transmit, 0 = receive */
    #define i2cmaster_CSR_LRB            (0x02u) /* Last received bit */
    #define i2cmaster_CSR_LRB_ACK        (0x00u) /* Last received bit was an ACK */
    #define i2cmaster_CSR_LRB_NAK        (0x02u) /* Last received bit was an NAK */
    #define i2cmaster_CSR_BYTE_COMPLETE  (0x01u) /* Informs that last byte has been sent */
    #define i2cmaster_CSR_STOP_GEN       (0x00u) /* Generate a stop condition */
    #define i2cmaster_CSR_RDY_TO_RD      (0x00u) /* Set to recieve mode */

    /* MCSR I2C Master Control and Status Register */
    #define i2cmaster_MCSR_STOP_GEN      (0x10u) /* Firmware sets this bit to initiate a Stop condition */
    #define i2cmaster_MCSR_BUS_BUSY      (0x08u) /* Status bit, Set at Start and cleared at Stop condition */
    #define i2cmaster_MCSR_MSTR_MODE     (0x04u) /* Status bit, Set at Start and cleared at Stop condition */
    #define i2cmaster_MCSR_RESTART_GEN   (0x02u) /* Firmware sets this bit to initiate a ReStart condition */
    #define i2cmaster_MCSR_START_GEN     (0x01u) /* Firmware sets this bit to initiate a Start condition */

    /* CLK_DIV I2C Clock Divide Factor Register */
    #define i2cmaster_CLK_DIV_MSK    (0x07u) /* Status bit, Set at Start and cleared at Stop condition */
    #define i2cmaster_CLK_DIV_1      (0x00u) /* Divide input clock by  1 */
    #define i2cmaster_CLK_DIV_2      (0x01u) /* Divide input clock by  2 */
    #define i2cmaster_CLK_DIV_4      (0x02u) /* Divide input clock by  4 */
    #define i2cmaster_CLK_DIV_8      (0x03u) /* Divide input clock by  8 */
    #define i2cmaster_CLK_DIV_16     (0x04u) /* Divide input clock by 16 */
    #define i2cmaster_CLK_DIV_32     (0x05u) /* Divide input clock by 32 */
    #define i2cmaster_CLK_DIV_64     (0x06u) /* Divide input clock by 64 */

    /* PWRSYS_CR1 to handle Sleep */
    #define i2cmaster_PWRSYS_CR1_I2C_REG_BACKUP  (0x04u) /* Enables, power to I2C regs while sleep */

#else
    /* CONTROL REG bits location */
    #define i2cmaster_CTRL_START_SHIFT           (7u)
    #define i2cmaster_CTRL_STOP_SHIFT            (6u)
    #define i2cmaster_CTRL_RESTART_SHIFT         (5u)
    #define i2cmaster_CTRL_NACK_SHIFT            (4u)
    #define i2cmaster_CTRL_ANY_ADDRESS_SHIFT     (3u)
    #define i2cmaster_CTRL_TRANSMIT_SHIFT        (2u)
    #define i2cmaster_CTRL_ENABLE_MASTER_SHIFT   (1u)
    #define i2cmaster_CTRL_ENABLE_SLAVE_SHIFT    (0u)
    #define i2cmaster_CTRL_START_MASK            ((uint8) (0x01u << i2cmaster_CTRL_START_SHIFT))
    #define i2cmaster_CTRL_STOP_MASK             ((uint8) (0x01u << i2cmaster_CTRL_STOP_SHIFT))
    #define i2cmaster_CTRL_RESTART_MASK          ((uint8) (0x01u << i2cmaster_CTRL_RESTART_SHIFT))
    #define i2cmaster_CTRL_NACK_MASK             ((uint8) (0x01u << i2cmaster_CTRL_NACK_SHIFT))
    #define i2cmaster_CTRL_ANY_ADDRESS_MASK      ((uint8) (0x01u << i2cmaster_CTRL_ANY_ADDRESS_SHIFT))
    #define i2cmaster_CTRL_TRANSMIT_MASK         ((uint8) (0x01u << i2cmaster_CTRL_TRANSMIT_SHIFT))
    #define i2cmaster_CTRL_ENABLE_MASTER_MASK    ((uint8) (0x01u << i2cmaster_CTRL_ENABLE_MASTER_SHIFT))
    #define i2cmaster_CTRL_ENABLE_SLAVE_MASK     ((uint8) (0x01u << i2cmaster_CTRL_ENABLE_SLAVE_SHIFT))

    /* STATUS REG bits location */
    #define i2cmaster_STS_LOST_ARB_SHIFT         (6u)
    #define i2cmaster_STS_STOP_SHIFT             (5u)
    #define i2cmaster_STS_BUSY_SHIFT             (4u)
    #define i2cmaster_STS_ADDR_SHIFT             (3u)
    #define i2cmaster_STS_MASTER_MODE_SHIFT      (2u)
    #define i2cmaster_STS_LRB_SHIFT              (1u)
    #define i2cmaster_STS_BYTE_COMPLETE_SHIFT    (0u)
    #define i2cmaster_STS_LOST_ARB_MASK          ((uint8) (0x01u << i2cmaster_STS_LOST_ARB_SHIFT))
    #define i2cmaster_STS_STOP_MASK              ((uint8) (0x01u << i2cmaster_STS_STOP_SHIFT))
    #define i2cmaster_STS_BUSY_MASK              ((uint8) (0x01u << i2cmaster_STS_BUSY_SHIFT))
    #define i2cmaster_STS_ADDR_MASK              ((uint8) (0x01u << i2cmaster_STS_ADDR_SHIFT))
    #define i2cmaster_STS_MASTER_MODE_MASK       ((uint8) (0x01u << i2cmaster_STS_MASTER_MODE_SHIFT))
    #define i2cmaster_STS_LRB_MASK               ((uint8) (0x01u << i2cmaster_STS_LRB_SHIFT))
    #define i2cmaster_STS_BYTE_COMPLETE_MASK     ((uint8) (0x01u << i2cmaster_STS_BYTE_COMPLETE_SHIFT))

    /* AUX_CTL bits definition */
    #define i2cmaster_COUNTER_ENABLE_MASK        (0x20u) /* Enable 7-bit counter     */
    #define i2cmaster_INT_ENABLE_MASK            (0x10u) /* Enable intr from statusi */
    #define i2cmaster_CNT7_ENABLE                (i2cmaster_COUNTER_ENABLE_MASK)
    #define i2cmaster_INTR_ENABLE                (i2cmaster_INT_ENABLE_MASK)

#endif /* (i2cmaster_FF_IMPLEMENTED) */


/***************************************
*        Marco
***************************************/

/* ACK and NACK for data and address checks */
#define i2cmaster_CHECK_ADDR_ACK(csr)    ((i2cmaster_CSR_LRB_ACK | i2cmaster_CSR_ADDRESS) == \
                                                 ((i2cmaster_CSR_LRB    | i2cmaster_CSR_ADDRESS) &  \
                                                  (csr)))


#define i2cmaster_CHECK_ADDR_NAK(csr)    ((i2cmaster_CSR_LRB_NAK | i2cmaster_CSR_ADDRESS) == \
                                                 ((i2cmaster_CSR_LRB    | i2cmaster_CSR_ADDRESS) &  \
                                                  (csr)))

#define i2cmaster_CHECK_DATA_ACK(csr)    (0u == ((csr) & i2cmaster_CSR_LRB_NAK))

/* MCSR conditions check */
#define i2cmaster_CHECK_BUS_FREE(mcsr)       (0u == ((mcsr) & i2cmaster_MCSR_BUS_BUSY))
#define i2cmaster_CHECK_MASTER_MODE(mcsr)    (0u != ((mcsr) & i2cmaster_MCSR_MSTR_MODE))

/* CSR conditions check */
#define i2cmaster_WAIT_BYTE_COMPLETE(csr)    (0u == ((csr) & i2cmaster_CSR_BYTE_COMPLETE))
#define i2cmaster_WAIT_STOP_COMPLETE(csr)    (0u == ((csr) & (i2cmaster_CSR_BYTE_COMPLETE | \
                                                                     i2cmaster_CSR_STOP_STATUS)))
#define i2cmaster_CHECK_BYTE_COMPLETE(csr)   (0u != ((csr) & i2cmaster_CSR_BYTE_COMPLETE))
#define i2cmaster_CHECK_STOP_STS(csr)        (0u != ((csr) & i2cmaster_CSR_STOP_STATUS))
#define i2cmaster_CHECK_LOST_ARB(csr)        (0u != ((csr) & i2cmaster_CSR_LOST_ARB))
#define i2cmaster_CHECK_ADDRESS_STS(csr)     (0u != ((csr) & i2cmaster_CSR_ADDRESS))

/* Software start and end of transaction check */
#define i2cmaster_CHECK_RESTART(mstrCtrl)    (0u != ((mstrCtrl) & i2cmaster_MODE_REPEAT_START))
#define i2cmaster_CHECK_NO_STOP(mstrCtrl)    (0u != ((mstrCtrl) & i2cmaster_MODE_NO_STOP))

/* Send read or write completion depends on state */
#define i2cmaster_GET_MSTAT_CMPLT ((0u != (i2cmaster_state & i2cmaster_SM_MSTR_RD)) ? \
                                                 (i2cmaster_MSTAT_RD_CMPLT) : (i2cmaster_MSTAT_WR_CMPLT))

/* Returns 7-bit slave address and used for software address match */
#define i2cmaster_GET_SLAVE_ADDR(dataReg)   (((dataReg) >> i2cmaster_SLAVE_ADDR_SHIFT) & \
                                                                  i2cmaster_SLAVE_ADDR_MASK)

#if(i2cmaster_FF_IMPLEMENTED)
    /* Check enable of module */
    #define i2cmaster_I2C_ENABLE_REG     (i2cmaster_ACT_PWRMGR_REG)
    #define i2cmaster_IS_I2C_ENABLE(reg) (0u != ((reg) & i2cmaster_ACT_PWR_EN))
    #define i2cmaster_IS_ENABLED         (0u != (i2cmaster_ACT_PWRMGR_REG & i2cmaster_ACT_PWR_EN))

    #define i2cmaster_CHECK_PWRSYS_I2C_BACKUP    (0u != (i2cmaster_PWRSYS_CR1_I2C_REG_BACKUP & \
                                                                i2cmaster_PWRSYS_CR1_REG))

    /* Check start condition generation */
    #define i2cmaster_CHECK_START_GEN(mcsr)  ((0u != ((mcsr) & i2cmaster_MCSR_START_GEN)) && \
                                                     (0u == ((mcsr) & i2cmaster_MCSR_MSTR_MODE)))

    #define i2cmaster_CLEAR_START_GEN        do{ \
                                                        i2cmaster_MCSR_REG &=                                   \
                                                                           ((uint8) ~i2cmaster_MCSR_START_GEN); \
                                                    }while(0)

    /* Stop interrupt */
    #define i2cmaster_ENABLE_INT_ON_STOP     do{ \
                                                        i2cmaster_CFG_REG |= i2cmaster_CFG_STOP_IE; \
                                                    }while(0)

    #define i2cmaster_DISABLE_INT_ON_STOP    do{ \
                                                        i2cmaster_CFG_REG &=                                 \
                                                                           ((uint8) ~i2cmaster_CFG_STOP_IE); \
                                                    }while(0)

    /* Transmit data */
    #define i2cmaster_TRANSMIT_DATA          do{ \
                                                        i2cmaster_CSR_REG = i2cmaster_CSR_TRANSMIT; \
                                                    }while(0)

    #define i2cmaster_ACK_AND_TRANSMIT       do{ \
                                                        i2cmaster_CSR_REG = (i2cmaster_CSR_ACK |      \
                                                                                    i2cmaster_CSR_TRANSMIT); \
                                                    }while(0)

    #define i2cmaster_NAK_AND_TRANSMIT       do{ \
                                                        i2cmaster_CSR_REG = i2cmaster_CSR_NAK; \
                                                    }while(0)

    /* Special case: udb needs to ack, ff needs to nak */
    #define i2cmaster_ACKNAK_AND_TRANSMIT    do{ \
                                                        i2cmaster_CSR_REG  = (i2cmaster_CSR_NAK |      \
                                                                                     i2cmaster_CSR_TRANSMIT); \
                                                    }while(0)
    /* Receive data */
    #define i2cmaster_ACK_AND_RECEIVE        do{ \
                                                        i2cmaster_CSR_REG = i2cmaster_CSR_ACK; \
                                                    }while(0)

    #define i2cmaster_NAK_AND_RECEIVE        do{ \
                                                        i2cmaster_CSR_REG = i2cmaster_CSR_NAK; \
                                                    }while(0)

    #define i2cmaster_READY_TO_READ          do{ \
                                                        i2cmaster_CSR_REG = i2cmaster_CSR_RDY_TO_RD; \
                                                    }while(0)

    /* Master condition generation */
    #define i2cmaster_GENERATE_START         do{ \
                                                        i2cmaster_MCSR_REG = i2cmaster_MCSR_START_GEN; \
                                                    }while(0)

    #if(CY_PSOC5A)
        #define i2cmaster_GENERATE_RESTART \
                        do{ \
                            i2cmaster_MCSR_REG = i2cmaster_MCSR_RESTART_GEN; \
                            i2cmaster_CSR_REG  = i2cmaster_CSR_NAK;          \
                        }while(0)

        #define i2cmaster_GENERATE_STOP      do{ \
                                                        i2cmaster_CSR_REG = i2cmaster_CSR_STOP_GEN; \
                                                    }while(0)

    #else   /* PSoC3 ES3 handlees zero lenght packets */
        #define i2cmaster_GENERATE_RESTART \
                        do{ \
                            i2cmaster_MCSR_REG = (i2cmaster_MCSR_RESTART_GEN | \
                                                         i2cmaster_MCSR_STOP_GEN);    \
                            i2cmaster_CSR_REG  = i2cmaster_CSR_TRANSMIT;       \
                        }while(0)

        #define i2cmaster_GENERATE_STOP \
                        do{ \
                            i2cmaster_MCSR_REG = i2cmaster_MCSR_STOP_GEN; \
                            i2cmaster_CSR_REG  = i2cmaster_CSR_TRANSMIT;  \
                        }while(0)
    #endif /* (CY_PSOC5A) */

    /* Master manual APIs compatible defines */
    #define i2cmaster_GENERATE_RESTART_MANUAL    i2cmaster_GENERATE_RESTART
    #define i2cmaster_GENERATE_STOP_MANUAL       i2cmaster_GENERATE_STOP
    #define i2cmaster_TRANSMIT_DATA_MANUAL       i2cmaster_TRANSMIT_DATA
    #define i2cmaster_READY_TO_READ_MANUAL       i2cmaster_READY_TO_READ
    #define i2cmaster_ACK_AND_RECEIVE_MANUAL     i2cmaster_ACK_AND_RECEIVE

#else

    /* Masks to enalbe interrupts from Status register */
    #define i2cmaster_STOP_IE_MASK           (i2cmaster_STS_STOP_MASK)
    #define i2cmaster_BYTE_COMPLETE_IE_MASK  (i2cmaster_STS_BYTE_COMPLETE_MASK)

    /* FF compatibility: CSR gegisters definitions */
    #define i2cmaster_CSR_LOST_ARB       (i2cmaster_STS_LOST_ARB_MASK)
    #define i2cmaster_CSR_STOP_STATUS    (i2cmaster_STS_STOP_MASK)
    #define i2cmaster_CSR_BUS_ERROR      (0x00u)
    #define i2cmaster_CSR_ADDRESS        (i2cmaster_STS_ADDR_MASK)
    #define i2cmaster_CSR_TRANSMIT       (i2cmaster_CTRL_TRANSMIT_MASK)
    #define i2cmaster_CSR_LRB            (i2cmaster_STS_LRB_MASK)
    #define i2cmaster_CSR_LRB_NAK        (i2cmaster_STS_LRB_MASK)
    #define i2cmaster_CSR_LRB_ACK        (0x00u)
    #define i2cmaster_CSR_BYTE_COMPLETE  (i2cmaster_STS_BYTE_COMPLETE_MASK)

    /* FF compatibility: MCSR gegisters definitions */
    #define i2cmaster_MCSR_REG           (i2cmaster_CSR_REG)   /* UDB incoporates master and slave regs */
    #define i2cmaster_MCSR_BUS_BUSY      (i2cmaster_STS_BUSY_MASK)       /* Is bus is busy              */
    #define i2cmaster_MCSR_START_GEN     (i2cmaster_CTRL_START_MASK)     /* Generate Sart condition     */
    #define i2cmaster_MCSR_RESTART_GEN   (i2cmaster_CTRL_RESTART_MASK)   /* Generates RESTART condition */
    #define i2cmaster_MCSR_MSTR_MODE     (i2cmaster_STS_MASTER_MODE_MASK)/* Define if active Master     */

    /* Data to write into TX FIFO to release FSM */
    #define i2cmaster_RELEASE_FSM         (0x00u)
    
    /* Check enable of module */
    #define i2cmaster_I2C_ENABLE_REG     (i2cmaster_CFG_REG)
    #define i2cmaster_IS_I2C_ENABLE(reg) ((0u != ((reg) & i2cmaster_ENABLE_MASTER)) || \
                                                 (0u != ((reg) & i2cmaster_ENABLE_SLAVE)))

    #define i2cmaster_IS_ENABLED         (0u != (i2cmaster_CFG_REG & i2cmaster_ENABLE_MS))

    /* Check start condition generation */
    #define i2cmaster_CHECK_START_GEN(mcsr)  ((0u != (i2cmaster_CFG_REG &        \
                                                             i2cmaster_MCSR_START_GEN)) \
                                                    &&                                         \
                                                    (0u == ((mcsr) & i2cmaster_MCSR_MSTR_MODE)))

    #define i2cmaster_CLEAR_START_GEN        do{ \
                                                        i2cmaster_CFG_REG &=                 \
                                                        ((uint8) ~i2cmaster_MCSR_START_GEN); \
                                                    }while(0)


    /* Stop interrupt */
    #define i2cmaster_ENABLE_INT_ON_STOP     do{ \
                                                       i2cmaster_INT_MASK_REG |= i2cmaster_STOP_IE_MASK; \
                                                    }while(0)

    #define i2cmaster_DISABLE_INT_ON_STOP    do{ \
                                                        i2cmaster_INT_MASK_REG &=                               \
                                                                             ((uint8) ~i2cmaster_STOP_IE_MASK); \
                                                    }while(0)


    /* Transmit data */
    #define i2cmaster_TRANSMIT_DATA      do{ \
                                                    i2cmaster_CFG_REG = (i2cmaster_CTRL_TRANSMIT_MASK | \
                                                                                i2cmaster_CTRL_DEFAULT);       \
                                                    i2cmaster_GO_REG  = i2cmaster_RELEASE_FSM;          \
                                                }while(0)

    #define i2cmaster_ACK_AND_TRANSMIT   i2cmaster_TRANSMIT_DATA


    #define i2cmaster_NAK_AND_TRANSMIT   do{ \
                                                    i2cmaster_CFG_REG = (i2cmaster_CTRL_NACK_MASK     | \
                                                                                i2cmaster_CTRL_TRANSMIT_MASK | \
                                                                                i2cmaster_CTRL_DEFAULT);       \
                                                    i2cmaster_GO_REG  =  i2cmaster_RELEASE_FSM;         \
                                                }while(0)

    /* Receive data */
    #define i2cmaster_READY_TO_READ      do{ \
                                                    i2cmaster_CFG_REG = i2cmaster_CTRL_DEFAULT; \
                                                    i2cmaster_GO_REG  =  i2cmaster_RELEASE_FSM; \
                                                }while(0)

    #define i2cmaster_ACK_AND_RECEIVE    i2cmaster_READY_TO_READ

    #define i2cmaster_NAK_AND_RECEIVE    do{ \
                                                    i2cmaster_CFG_REG = (i2cmaster_CTRL_NACK_MASK | \
                                                                                i2cmaster_CTRL_DEFAULT);   \
                                                    i2cmaster_GO_REG  =  i2cmaster_RELEASE_FSM;     \
                                                }while(0)

    /* Master condition generation */
    #define i2cmaster_GENERATE_START     do{ \
                                                    i2cmaster_CFG_REG = (i2cmaster_CTRL_START_MASK | \
                                                                                 i2cmaster_CTRL_DEFAULT);   \
                                                    i2cmaster_GO_REG  =  i2cmaster_RELEASE_FSM;      \
                                                }while(0)

    #define i2cmaster_GENERATE_RESTART   do{ \
                                                    i2cmaster_CFG_REG = (i2cmaster_CTRL_RESTART_MASK | \
                                                                                i2cmaster_CTRL_NACK_MASK    | \
                                                                                i2cmaster_CTRL_DEFAULT);      \
                                                    i2cmaster_GO_REG  =  i2cmaster_RELEASE_FSM;        \
                                                }while(0)


    #define i2cmaster_GENERATE_STOP      do{ \
                                                    i2cmaster_CFG_REG = (i2cmaster_CTRL_NACK_MASK | \
                                                                                i2cmaster_CTRL_STOP_MASK | \
                                                                                i2cmaster_CTRL_DEFAULT);   \
                                                    i2cmaster_GO_REG  =  i2cmaster_RELEASE_FSM;     \
                                                }while(0)

    /* Master manual APIs compatible defines */
    /* These defines wait while byte complete is cleared after command issued */
    #define i2cmaster_GENERATE_RESTART_MANUAL    \
                                        do{             \
                                            i2cmaster_GENERATE_RESTART;                                    \
                                            while(i2cmaster_CHECK_BYTE_COMPLETE(i2cmaster_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define i2cmaster_GENERATE_STOP_MANUAL   \
                                        do{         \
                                            i2cmaster_GENERATE_STOP;                                       \
                                            while(i2cmaster_CHECK_BYTE_COMPLETE(i2cmaster_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define i2cmaster_TRANSMIT_DATA_MANUAL   \
                                        do{         \
                                            i2cmaster_TRANSMIT_DATA;                                       \
                                            while(i2cmaster_CHECK_BYTE_COMPLETE(i2cmaster_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define i2cmaster_READY_TO_READ_MANUAL   \
                                        do{         \
                                            i2cmaster_READY_TO_READ;      \
                                            while(i2cmaster_CHECK_BYTE_COMPLETE(i2cmaster_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define i2cmaster_ACK_AND_RECEIVE_MANUAL \
                                        do{         \
                                            i2cmaster_ACK_AND_RECEIVE;                                     \
                                            while(i2cmaster_CHECK_BYTE_COMPLETE(i2cmaster_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)
#endif /* (i2cmaster_FF_IMPLEMENTED) */

/* Comon for FF and UDB: used to release bus after lost arb */
#define i2cmaster_BUS_RELEASE    i2cmaster_READY_TO_READ


/***************************************
*     Default register init constants
***************************************/

#define i2cmaster_DISABLE    (0u)
#define i2cmaster_ENABLE     (1u)

#if(i2cmaster_FF_IMPLEMENTED)
    /* i2cmaster_XCFG_REG: bits definition */
    #define i2cmaster_DEFAULT_XCFG_HW_ADDR_EN ((i2cmaster_HW_ADRR_DECODE) ? \
                                                        (i2cmaster_XCFG_HDWR_ADDR_EN) : (0u))

    #define i2cmaster_DEFAULT_XCFG_I2C_ON    ((i2cmaster_WAKEUP_ENABLED) ? \
                                                        (i2cmaster_XCFG_I2C_ON) : (0u))


    #define i2cmaster_DEFAULT_CFG_SIO_SELECT ((i2cmaster_I2C1_SIO_PAIR) ? \
                                                        (i2cmaster_CFG_SIO_SELECT) : (0u))


    /* i2cmaster_CFG_REG: bits definition */
    #define i2cmaster_DEFAULT_CFG_PSELECT    ((i2cmaster_WAKEUP_ENABLED) ? \
                                                        (i2cmaster_CFG_PSELECT) : (0u))

    #define i2cmaster_DEFAULT_CLK_RATE0  ((i2cmaster_DATA_RATE <= 50u) ?        \
                                                    (i2cmaster_CFG_CLK_RATE_050) :     \
                                                    ((i2cmaster_DATA_RATE <= 100u) ?   \
                                                        (i2cmaster_CFG_CLK_RATE_100) : \
                                                        (i2cmaster_CFG_CLK_RATE_400)))

    #define i2cmaster_DEFAULT_CLK_RATE1  ((i2cmaster_DATA_RATE <= 50u) ?           \
                                                 (i2cmaster_CFG_CLK_RATE_LESS_EQUAL_50) : \
                                                 (i2cmaster_CFG_CLK_RATE_GRATER_50))

    #define i2cmaster_DEFAULT_CLK_RATE   ((CY_PSOC5A) ? (i2cmaster_DEFAULT_CLK_RATE0) : \
                                                               (i2cmaster_DEFAULT_CLK_RATE1))


    #define i2cmaster_ENABLE_MASTER      ((i2cmaster_MODE_MASTER_ENABLED) ? \
                                                 (i2cmaster_CFG_EN_MSTR) : (0u))

    #define i2cmaster_ENABLE_SLAVE       ((i2cmaster_MODE_SLAVE_ENABLED) ? \
                                                 (i2cmaster_CFG_EN_SLAVE) : (0u))

    #define i2cmaster_ENABLE_MS      (i2cmaster_ENABLE_MASTER | i2cmaster_ENABLE_SLAVE)


    /* i2cmaster_DEFAULT_XCFG_REG */
    #define i2cmaster_DEFAULT_XCFG   (i2cmaster_XCFG_CLK_EN         | \
                                             i2cmaster_DEFAULT_XCFG_I2C_ON | \
                                             i2cmaster_DEFAULT_XCFG_HW_ADDR_EN)

    /* i2cmaster_DEFAULT_CFG_REG */
    #define i2cmaster_DEFAULT_CFG    (i2cmaster_DEFAULT_CFG_SIO_SELECT | \
                                             i2cmaster_DEFAULT_CFG_PSELECT    | \
                                             i2cmaster_DEFAULT_CLK_RATE       | \
                                             i2cmaster_ENABLE_MASTER          | \
                                             i2cmaster_ENABLE_SLAVE)

    /*i2cmaster_DEFAULT_DIVIDE_FACTOR_REG */
    #define i2cmaster_DEFAULT_DIVIDE_FACTOR  ((CY_PSOC5A) ? ((uint8) 4u) : ((uint16) 15u))

#else
    /* i2cmaster_CFG_REG: bits definition  */
    #define i2cmaster_ENABLE_MASTER  ((i2cmaster_MODE_MASTER_ENABLED) ? \
                                             (i2cmaster_CTRL_ENABLE_MASTER_MASK) : (0u))

    #define i2cmaster_ENABLE_SLAVE   ((i2cmaster_MODE_SLAVE_ENABLED) ? \
                                             (i2cmaster_CTRL_ENABLE_SLAVE_MASK) : (0u))

    #define i2cmaster_ENABLE_MS      (i2cmaster_ENABLE_MASTER | i2cmaster_ENABLE_SLAVE)


    #define i2cmaster_DEFAULT_CTRL_ANY_ADDR   ((i2cmaster_HW_ADRR_DECODE) ? \
                                                      (0u) : (i2cmaster_CTRL_ANY_ADDRESS_MASK))

    /* i2cmaster_DEFAULT_CFG_REG */
    #define i2cmaster_DEFAULT_CFG    (i2cmaster_DEFAULT_CTRL_ANY_ADDR)

    /* All CTRL default bits to be used in macro */
    #define i2cmaster_CTRL_DEFAULT   (i2cmaster_DEFAULT_CTRL_ANY_ADDR | i2cmaster_ENABLE_MS)

    /* Master clock generator: d0 and d1 */
    #define i2cmaster_MCLK_PERIOD_VALUE  (0x0Fu)
    #define i2cmaster_MCLK_COMPARE_VALUE (0x08u)

    /* Slave bit-counter: contorol period */
    #define i2cmaster_PERIOD_VALUE       (0x07u)

    /* i2cmaster_DEFAULT_INT_MASK */
    #define i2cmaster_DEFAULT_INT_MASK   (i2cmaster_BYTE_COMPLETE_IE_MASK)

    /* i2cmaster_DEFAULT_MCLK_PRD_REG */
    #define i2cmaster_DEFAULT_MCLK_PRD   (i2cmaster_MCLK_PERIOD_VALUE)

    /* i2cmaster_DEFAULT_MCLK_CMP_REG */
    #define i2cmaster_DEFAULT_MCLK_CMP   (i2cmaster_MCLK_COMPARE_VALUE)

    /* i2cmaster_DEFAULT_PERIOD_REG */
    #define i2cmaster_DEFAULT_PERIOD     (i2cmaster_PERIOD_VALUE)

#endif /* (i2cmaster_FF_IMPLEMENTED) */


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from I2C 3.20
 */
 
#define i2cmaster_SSTAT_RD_ERR       (0x08u)
#define i2cmaster_SSTAT_WR_ERR       (0x80u)
#define i2cmaster_MSTR_SLAVE_BUSY    (i2cmaster_MSTR_NOT_READY)
#define i2cmaster_MSTAT_ERR_BUF_OVFL (0x80u)
#define i2cmaster_SSTAT_RD_CMPT      (i2cmaster_SSTAT_RD_CMPLT)
#define i2cmaster_SSTAT_WR_CMPT      (i2cmaster_SSTAT_WR_CMPLT)
#define i2cmaster_MODE_MULTI_MASTER_ENABLE    (i2cmaster_MODE_MULTI_MASTER_MASK)
#define i2cmaster_DATA_RATE_50       (50u)
#define i2cmaster_DATA_RATE_100      (100u)
#define i2cmaster_DEV_MASK           (0xF0u)
#define i2cmaster_SM_SL_STOP         (0x14u)
#define i2cmaster_SM_MASTER_IDLE     (0x40u)
#define i2cmaster_HDWR_DECODE        (0x01u)

#endif /* CY_I2C_i2cmaster_H */


/* [] END OF FILE */
