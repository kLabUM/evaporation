#ifndef INCLUDED_CYFITTERIAR_INC
#define INCLUDED_CYFITTERIAR_INC
    INCLUDE cydeviceiar.inc
    INCLUDE cydeviceiar_trm.inc

/* UART_IntClock */
UART_IntClock__CFG0 EQU CYREG_CLKDIST_DCFG0_CFG0
UART_IntClock__CFG1 EQU CYREG_CLKDIST_DCFG0_CFG1
UART_IntClock__CFG2 EQU CYREG_CLKDIST_DCFG0_CFG2
UART_IntClock__CFG2_SRC_SEL_MASK EQU 0x07
UART_IntClock__INDEX EQU 0x00
UART_IntClock__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
UART_IntClock__PM_ACT_MSK EQU 0x01
UART_IntClock__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
UART_IntClock__PM_STBY_MSK EQU 0x01

/* UART_BUART */
UART_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B0_UDB06_07_ACTL
UART_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_REG EQU CYREG_B0_UDB06_07_ST
UART_BUART_sRX_RxBitCounter_ST__MASK_REG EQU CYREG_B0_UDB06_MSK
UART_BUART_sRX_RxBitCounter_ST__MASK_ST_AUX_CTL_REG EQU CYREG_B0_UDB06_MSK_ACTL
UART_BUART_sRX_RxBitCounter_ST__PER_ST_AUX_CTL_REG EQU CYREG_B0_UDB06_MSK_ACTL
UART_BUART_sRX_RxBitCounter_ST__STATUS_AUX_CTL_REG EQU CYREG_B0_UDB06_ACTL
UART_BUART_sRX_RxBitCounter_ST__STATUS_CNT_REG EQU CYREG_B0_UDB06_ST_CTL
UART_BUART_sRX_RxBitCounter_ST__STATUS_CONTROL_REG EQU CYREG_B0_UDB06_ST_CTL
UART_BUART_sRX_RxBitCounter_ST__STATUS_REG EQU CYREG_B0_UDB06_ST
UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB06_07_ACTL
UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_CONTROL_REG EQU CYREG_B0_UDB06_07_CTL
UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_COUNT_REG EQU CYREG_B0_UDB06_07_CTL
UART_BUART_sRX_RxBitCounter__16BIT_COUNT_CONTROL_REG EQU CYREG_B0_UDB06_07_CTL
UART_BUART_sRX_RxBitCounter__16BIT_COUNT_COUNT_REG EQU CYREG_B0_UDB06_07_CTL
UART_BUART_sRX_RxBitCounter__16BIT_MASK_MASK_REG EQU CYREG_B0_UDB06_07_MSK
UART_BUART_sRX_RxBitCounter__16BIT_MASK_PERIOD_REG EQU CYREG_B0_UDB06_07_MSK
UART_BUART_sRX_RxBitCounter__16BIT_PERIOD_MASK_REG EQU CYREG_B0_UDB06_07_MSK
UART_BUART_sRX_RxBitCounter__16BIT_PERIOD_PERIOD_REG EQU CYREG_B0_UDB06_07_MSK
UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB06_ACTL
UART_BUART_sRX_RxBitCounter__CONTROL_REG EQU CYREG_B0_UDB06_CTL
UART_BUART_sRX_RxBitCounter__CONTROL_ST_REG EQU CYREG_B0_UDB06_ST_CTL
UART_BUART_sRX_RxBitCounter__COUNT_REG EQU CYREG_B0_UDB06_CTL
UART_BUART_sRX_RxBitCounter__COUNT_ST_REG EQU CYREG_B0_UDB06_ST_CTL
UART_BUART_sRX_RxBitCounter__MASK_CTL_AUX_CTL_REG EQU CYREG_B0_UDB06_MSK_ACTL
UART_BUART_sRX_RxBitCounter__PERIOD_REG EQU CYREG_B0_UDB06_MSK
UART_BUART_sRX_RxBitCounter__PER_CTL_AUX_CTL_REG EQU CYREG_B0_UDB06_MSK_ACTL
UART_BUART_sRX_RxShifter_u0__16BIT_A0_REG EQU CYREG_B1_UDB06_07_A0
UART_BUART_sRX_RxShifter_u0__16BIT_A1_REG EQU CYREG_B1_UDB06_07_A1
UART_BUART_sRX_RxShifter_u0__16BIT_D0_REG EQU CYREG_B1_UDB06_07_D0
UART_BUART_sRX_RxShifter_u0__16BIT_D1_REG EQU CYREG_B1_UDB06_07_D1
UART_BUART_sRX_RxShifter_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B1_UDB06_07_ACTL
UART_BUART_sRX_RxShifter_u0__16BIT_F0_REG EQU CYREG_B1_UDB06_07_F0
UART_BUART_sRX_RxShifter_u0__16BIT_F1_REG EQU CYREG_B1_UDB06_07_F1
UART_BUART_sRX_RxShifter_u0__A0_A1_REG EQU CYREG_B1_UDB06_A0_A1
UART_BUART_sRX_RxShifter_u0__A0_REG EQU CYREG_B1_UDB06_A0
UART_BUART_sRX_RxShifter_u0__A1_REG EQU CYREG_B1_UDB06_A1
UART_BUART_sRX_RxShifter_u0__D0_D1_REG EQU CYREG_B1_UDB06_D0_D1
UART_BUART_sRX_RxShifter_u0__D0_REG EQU CYREG_B1_UDB06_D0
UART_BUART_sRX_RxShifter_u0__D1_REG EQU CYREG_B1_UDB06_D1
UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG EQU CYREG_B1_UDB06_ACTL
UART_BUART_sRX_RxShifter_u0__F0_F1_REG EQU CYREG_B1_UDB06_F0_F1
UART_BUART_sRX_RxShifter_u0__F0_REG EQU CYREG_B1_UDB06_F0
UART_BUART_sRX_RxShifter_u0__F1_REG EQU CYREG_B1_UDB06_F1
UART_BUART_sRX_RxSts__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B1_UDB06_07_ACTL
UART_BUART_sRX_RxSts__16BIT_STATUS_REG EQU CYREG_B1_UDB06_07_ST
UART_BUART_sRX_RxSts__3__MASK EQU 0x08
UART_BUART_sRX_RxSts__3__POS EQU 3
UART_BUART_sRX_RxSts__4__MASK EQU 0x10
UART_BUART_sRX_RxSts__4__POS EQU 4
UART_BUART_sRX_RxSts__5__MASK EQU 0x20
UART_BUART_sRX_RxSts__5__POS EQU 5
UART_BUART_sRX_RxSts__MASK EQU 0x38
UART_BUART_sRX_RxSts__MASK_REG EQU CYREG_B1_UDB06_MSK
UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG EQU CYREG_B1_UDB06_ACTL
UART_BUART_sRX_RxSts__STATUS_REG EQU CYREG_B1_UDB06_ST
UART_BUART_sTX_TxShifter_u0__16BIT_A0_REG EQU CYREG_B1_UDB04_05_A0
UART_BUART_sTX_TxShifter_u0__16BIT_A1_REG EQU CYREG_B1_UDB04_05_A1
UART_BUART_sTX_TxShifter_u0__16BIT_D0_REG EQU CYREG_B1_UDB04_05_D0
UART_BUART_sTX_TxShifter_u0__16BIT_D1_REG EQU CYREG_B1_UDB04_05_D1
UART_BUART_sTX_TxShifter_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B1_UDB04_05_ACTL
UART_BUART_sTX_TxShifter_u0__16BIT_F0_REG EQU CYREG_B1_UDB04_05_F0
UART_BUART_sTX_TxShifter_u0__16BIT_F1_REG EQU CYREG_B1_UDB04_05_F1
UART_BUART_sTX_TxShifter_u0__A0_A1_REG EQU CYREG_B1_UDB04_A0_A1
UART_BUART_sTX_TxShifter_u0__A0_REG EQU CYREG_B1_UDB04_A0
UART_BUART_sTX_TxShifter_u0__A1_REG EQU CYREG_B1_UDB04_A1
UART_BUART_sTX_TxShifter_u0__D0_D1_REG EQU CYREG_B1_UDB04_D0_D1
UART_BUART_sTX_TxShifter_u0__D0_REG EQU CYREG_B1_UDB04_D0
UART_BUART_sTX_TxShifter_u0__D1_REG EQU CYREG_B1_UDB04_D1
UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG EQU CYREG_B1_UDB04_ACTL
UART_BUART_sTX_TxShifter_u0__F0_F1_REG EQU CYREG_B1_UDB04_F0_F1
UART_BUART_sTX_TxShifter_u0__F0_REG EQU CYREG_B1_UDB04_F0
UART_BUART_sTX_TxShifter_u0__F1_REG EQU CYREG_B1_UDB04_F1
UART_BUART_sTX_TxSts__0__MASK EQU 0x01
UART_BUART_sTX_TxSts__0__POS EQU 0
UART_BUART_sTX_TxSts__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B1_UDB04_05_ACTL
UART_BUART_sTX_TxSts__16BIT_STATUS_REG EQU CYREG_B1_UDB04_05_ST
UART_BUART_sTX_TxSts__1__MASK EQU 0x02
UART_BUART_sTX_TxSts__1__POS EQU 1
UART_BUART_sTX_TxSts__2__MASK EQU 0x04
UART_BUART_sTX_TxSts__2__POS EQU 2
UART_BUART_sTX_TxSts__3__MASK EQU 0x08
UART_BUART_sTX_TxSts__3__POS EQU 3
UART_BUART_sTX_TxSts__MASK EQU 0x0F
UART_BUART_sTX_TxSts__MASK_REG EQU CYREG_B1_UDB04_MSK
UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG EQU CYREG_B1_UDB04_ACTL
UART_BUART_sTX_TxSts__STATUS_REG EQU CYREG_B1_UDB04_ST
UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A0_REG EQU CYREG_B0_UDB07_08_A0
UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A1_REG EQU CYREG_B0_UDB07_08_A1
UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D0_REG EQU CYREG_B0_UDB07_08_D0
UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D1_REG EQU CYREG_B0_UDB07_08_D1
UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB07_08_ACTL
UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F0_REG EQU CYREG_B0_UDB07_08_F0
UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F1_REG EQU CYREG_B0_UDB07_08_F1
UART_BUART_sTX_sCLOCK_TxBitClkGen__A0_A1_REG EQU CYREG_B0_UDB07_A0_A1
UART_BUART_sTX_sCLOCK_TxBitClkGen__A0_REG EQU CYREG_B0_UDB07_A0
UART_BUART_sTX_sCLOCK_TxBitClkGen__A1_REG EQU CYREG_B0_UDB07_A1
UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_D1_REG EQU CYREG_B0_UDB07_D0_D1
UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG EQU CYREG_B0_UDB07_D0
UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG EQU CYREG_B0_UDB07_D1
UART_BUART_sTX_sCLOCK_TxBitClkGen__DP_AUX_CTL_REG EQU CYREG_B0_UDB07_ACTL
UART_BUART_sTX_sCLOCK_TxBitClkGen__F0_F1_REG EQU CYREG_B0_UDB07_F0_F1
UART_BUART_sTX_sCLOCK_TxBitClkGen__F0_REG EQU CYREG_B0_UDB07_F0
UART_BUART_sTX_sCLOCK_TxBitClkGen__F1_REG EQU CYREG_B0_UDB07_F1

/* SBD_reply */
SBD_reply__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
SBD_reply__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
SBD_reply__INTC_MASK EQU 0x01
SBD_reply__INTC_NUMBER EQU 0
SBD_reply__INTC_PRIOR_NUM EQU 7
SBD_reply__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_0
SBD_reply__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
SBD_reply__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0

/* SBD_Rx */
SBD_Rx__0__MASK EQU 0x80
SBD_Rx__0__PC EQU CYREG_PRT3_PC7
SBD_Rx__0__PORT EQU 3
SBD_Rx__0__SHIFT EQU 7
SBD_Rx__AG EQU CYREG_PRT3_AG
SBD_Rx__AMUX EQU CYREG_PRT3_AMUX
SBD_Rx__BIE EQU CYREG_PRT3_BIE
SBD_Rx__BIT_MASK EQU CYREG_PRT3_BIT_MASK
SBD_Rx__BYP EQU CYREG_PRT3_BYP
SBD_Rx__CTL EQU CYREG_PRT3_CTL
SBD_Rx__DM0 EQU CYREG_PRT3_DM0
SBD_Rx__DM1 EQU CYREG_PRT3_DM1
SBD_Rx__DM2 EQU CYREG_PRT3_DM2
SBD_Rx__DR EQU CYREG_PRT3_DR
SBD_Rx__INP_DIS EQU CYREG_PRT3_INP_DIS
SBD_Rx__LCD_COM_SEG EQU CYREG_PRT3_LCD_COM_SEG
SBD_Rx__LCD_EN EQU CYREG_PRT3_LCD_EN
SBD_Rx__MASK EQU 0x80
SBD_Rx__PORT EQU 3
SBD_Rx__PRT EQU CYREG_PRT3_PRT
SBD_Rx__PRTDSI__CAPS_SEL EQU CYREG_PRT3_CAPS_SEL
SBD_Rx__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT3_DBL_SYNC_IN
SBD_Rx__PRTDSI__OE_SEL0 EQU CYREG_PRT3_OE_SEL0
SBD_Rx__PRTDSI__OE_SEL1 EQU CYREG_PRT3_OE_SEL1
SBD_Rx__PRTDSI__OUT_SEL0 EQU CYREG_PRT3_OUT_SEL0
SBD_Rx__PRTDSI__OUT_SEL1 EQU CYREG_PRT3_OUT_SEL1
SBD_Rx__PRTDSI__SYNC_OUT EQU CYREG_PRT3_SYNC_OUT
SBD_Rx__PS EQU CYREG_PRT3_PS
SBD_Rx__SHIFT EQU 7
SBD_Rx__SLW EQU CYREG_PRT3_SLW

/* SBD_Tx */
SBD_Tx__0__MASK EQU 0x40
SBD_Tx__0__PC EQU CYREG_PRT3_PC6
SBD_Tx__0__PORT EQU 3
SBD_Tx__0__SHIFT EQU 6
SBD_Tx__AG EQU CYREG_PRT3_AG
SBD_Tx__AMUX EQU CYREG_PRT3_AMUX
SBD_Tx__BIE EQU CYREG_PRT3_BIE
SBD_Tx__BIT_MASK EQU CYREG_PRT3_BIT_MASK
SBD_Tx__BYP EQU CYREG_PRT3_BYP
SBD_Tx__CTL EQU CYREG_PRT3_CTL
SBD_Tx__DM0 EQU CYREG_PRT3_DM0
SBD_Tx__DM1 EQU CYREG_PRT3_DM1
SBD_Tx__DM2 EQU CYREG_PRT3_DM2
SBD_Tx__DR EQU CYREG_PRT3_DR
SBD_Tx__INP_DIS EQU CYREG_PRT3_INP_DIS
SBD_Tx__LCD_COM_SEG EQU CYREG_PRT3_LCD_COM_SEG
SBD_Tx__LCD_EN EQU CYREG_PRT3_LCD_EN
SBD_Tx__MASK EQU 0x40
SBD_Tx__PORT EQU 3
SBD_Tx__PRT EQU CYREG_PRT3_PRT
SBD_Tx__PRTDSI__CAPS_SEL EQU CYREG_PRT3_CAPS_SEL
SBD_Tx__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT3_DBL_SYNC_IN
SBD_Tx__PRTDSI__OE_SEL0 EQU CYREG_PRT3_OE_SEL0
SBD_Tx__PRTDSI__OE_SEL1 EQU CYREG_PRT3_OE_SEL1
SBD_Tx__PRTDSI__OUT_SEL0 EQU CYREG_PRT3_OUT_SEL0
SBD_Tx__PRTDSI__OUT_SEL1 EQU CYREG_PRT3_OUT_SEL1
SBD_Tx__PRTDSI__SYNC_OUT EQU CYREG_PRT3_SYNC_OUT
SBD_Tx__PS EQU CYREG_PRT3_PS
SBD_Tx__SHIFT EQU 6
SBD_Tx__SLW EQU CYREG_PRT3_SLW

/* Miscellaneous */
/* -- WARNING: define names containing LEOPARD or PANTHER are deprecated and will be removed in a future release */
CYDEV_DEBUGGING_DPS_SWD_SWV EQU 6
CYDEV_CONFIG_UNUSED_IO_AllowButWarn EQU 0
CYDEV_CONFIGURATION_MODE_COMPRESSED EQU 0
CYDEV_CONFIG_FASTBOOT_ENABLED EQU 1
CYDEV_CHIP_REV_PSOC5LP_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_5B_PRODUCTION EQU 0
CYDEV_CHIP_MEMBER_5B EQU 4
CYDEV_CHIP_FAMILY_PSOC5 EQU 3
CYDEV_CHIP_DIE_PSOC5LP EQU 4
CYDEV_CHIP_DIE_EXPECT EQU CYDEV_CHIP_DIE_PSOC5LP
BCLK__BUS_CLK__HZ EQU 24000000
BCLK__BUS_CLK__KHZ EQU 24000
BCLK__BUS_CLK__MHZ EQU 24
CYDEV_CHIP_DIE_ACTUAL EQU CYDEV_CHIP_DIE_EXPECT
CYDEV_CHIP_DIE_LEOPARD EQU 1
CYDEV_CHIP_DIE_PANTHER EQU 3
CYDEV_CHIP_DIE_PSOC4A EQU 2
CYDEV_CHIP_DIE_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_PSOC3 EQU 1
CYDEV_CHIP_FAMILY_PSOC4 EQU 2
CYDEV_CHIP_FAMILY_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_USED EQU CYDEV_CHIP_FAMILY_PSOC5
CYDEV_CHIP_JTAG_ID EQU 0x2E123069
CYDEV_CHIP_MEMBER_3A EQU 1
CYDEV_CHIP_MEMBER_4A EQU 2
CYDEV_CHIP_MEMBER_5A EQU 3
CYDEV_CHIP_MEMBER_UNKNOWN EQU 0
CYDEV_CHIP_MEMBER_USED EQU CYDEV_CHIP_MEMBER_5B
CYDEV_CHIP_REVISION_3A_ES1 EQU 0
CYDEV_CHIP_REVISION_3A_ES2 EQU 1
CYDEV_CHIP_REVISION_3A_ES3 EQU 3
CYDEV_CHIP_REVISION_3A_PRODUCTION EQU 3
CYDEV_CHIP_REVISION_4A_ES0 EQU 17
CYDEV_CHIP_REVISION_4A_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_5A_ES0 EQU 0
CYDEV_CHIP_REVISION_5A_ES1 EQU 1
CYDEV_CHIP_REVISION_5A_PRODUCTION EQU 1
CYDEV_CHIP_REVISION_5B_ES0 EQU 0
CYDEV_CHIP_REVISION_USED EQU CYDEV_CHIP_REVISION_5B_PRODUCTION
CYDEV_CHIP_REV_EXPECT EQU CYDEV_CHIP_REV_PSOC5LP_PRODUCTION
CYDEV_CHIP_REV_LEOPARD_ES1 EQU 0
CYDEV_CHIP_REV_LEOPARD_ES2 EQU 1
CYDEV_CHIP_REV_LEOPARD_ES3 EQU 3
CYDEV_CHIP_REV_LEOPARD_PRODUCTION EQU 3
CYDEV_CHIP_REV_PANTHER_ES0 EQU 0
CYDEV_CHIP_REV_PANTHER_ES1 EQU 1
CYDEV_CHIP_REV_PANTHER_PRODUCTION EQU 1
CYDEV_CHIP_REV_PSOC4A_ES0 EQU 17
CYDEV_CHIP_REV_PSOC4A_PRODUCTION EQU 17
CYDEV_CHIP_REV_PSOC5LP_ES0 EQU 0
CYDEV_CONFIGURATION_COMPRESSED EQU 1
CYDEV_CONFIGURATION_DMA EQU 0
CYDEV_CONFIGURATION_ECC EQU 1
CYDEV_CONFIGURATION_IMOENABLED EQU CYDEV_CONFIG_FASTBOOT_ENABLED
CYDEV_CONFIGURATION_MODE EQU CYDEV_CONFIGURATION_MODE_COMPRESSED
CYDEV_CONFIGURATION_MODE_DMA EQU 2
CYDEV_CONFIGURATION_MODE_UNCOMPRESSED EQU 1
CYDEV_CONFIG_UNUSED_IO EQU CYDEV_CONFIG_UNUSED_IO_AllowButWarn
CYDEV_CONFIG_UNUSED_IO_AllowWithInfo EQU 1
CYDEV_CONFIG_UNUSED_IO_Disallowed EQU 2
CYDEV_DEBUGGING_DPS EQU CYDEV_DEBUGGING_DPS_SWD_SWV
CYDEV_DEBUGGING_DPS_Disable EQU 3
CYDEV_DEBUGGING_DPS_JTAG_4 EQU 1
CYDEV_DEBUGGING_DPS_JTAG_5 EQU 0
CYDEV_DEBUGGING_DPS_SWD EQU 2
CYDEV_DEBUGGING_ENABLE EQU 1
CYDEV_DEBUGGING_XRES EQU 0
CYDEV_DEBUG_ENABLE_MASK EQU 0x20
CYDEV_DEBUG_ENABLE_REGISTER EQU CYREG_MLOGIC_DEBUG
CYDEV_DMA_CHANNELS_AVAILABLE EQU 24
CYDEV_ECC_ENABLE EQU 0
CYDEV_HEAP_SIZE EQU 0x1000
CYDEV_INSTRUCT_CACHE_ENABLED EQU 1
CYDEV_INTR_RISING EQU 0x00000001
CYDEV_PROJ_TYPE EQU 0
CYDEV_PROJ_TYPE_BOOTLOADER EQU 1
CYDEV_PROJ_TYPE_LOADABLE EQU 2
CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER EQU 3
CYDEV_PROJ_TYPE_STANDARD EQU 0
CYDEV_PROTECTION_ENABLE EQU 0
CYDEV_STACK_SIZE EQU 0x4000
CYDEV_USE_BUNDLED_CMSIS EQU 1
CYDEV_VARIABLE_VDDA EQU 0
CYDEV_VDDA_MV EQU 5000
CYDEV_VDDD_MV EQU 5000
CYDEV_VDDIO0_MV EQU 5000
CYDEV_VDDIO1_MV EQU 5000
CYDEV_VDDIO2_MV EQU 5000
CYDEV_VDDIO3_MV EQU 5000
CYDEV_VIO0 EQU 5
CYDEV_VIO0_MV EQU 5000
CYDEV_VIO1 EQU 5
CYDEV_VIO1_MV EQU 5000
CYDEV_VIO2 EQU 5
CYDEV_VIO2_MV EQU 5000
CYDEV_VIO3 EQU 5
CYDEV_VIO3_MV EQU 5000
DMA_CHANNELS_USED__MASK0 EQU 0x00000000
CYDEV_BOOTLOADER_ENABLE EQU 0

#endif /* INCLUDED_CYFITTERIAR_INC */