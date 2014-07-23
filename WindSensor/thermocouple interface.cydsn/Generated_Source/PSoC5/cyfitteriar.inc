#ifndef INCLUDED_CYFITTERIAR_INC
#define INCLUDED_CYFITTERIAR_INC
    INCLUDE cydeviceiar.inc
    INCLUDE cydeviceiar_trm.inc

/* LCD_LCDPort */
LCD_LCDPort__0__MASK EQU 0x01
LCD_LCDPort__0__PC EQU CYREG_PRT2_PC0
LCD_LCDPort__0__PORT EQU 2
LCD_LCDPort__0__SHIFT EQU 0
LCD_LCDPort__1__MASK EQU 0x02
LCD_LCDPort__1__PC EQU CYREG_PRT2_PC1
LCD_LCDPort__1__PORT EQU 2
LCD_LCDPort__1__SHIFT EQU 1
LCD_LCDPort__2__MASK EQU 0x04
LCD_LCDPort__2__PC EQU CYREG_PRT2_PC2
LCD_LCDPort__2__PORT EQU 2
LCD_LCDPort__2__SHIFT EQU 2
LCD_LCDPort__3__MASK EQU 0x08
LCD_LCDPort__3__PC EQU CYREG_PRT2_PC3
LCD_LCDPort__3__PORT EQU 2
LCD_LCDPort__3__SHIFT EQU 3
LCD_LCDPort__4__MASK EQU 0x10
LCD_LCDPort__4__PC EQU CYREG_PRT2_PC4
LCD_LCDPort__4__PORT EQU 2
LCD_LCDPort__4__SHIFT EQU 4
LCD_LCDPort__5__MASK EQU 0x20
LCD_LCDPort__5__PC EQU CYREG_PRT2_PC5
LCD_LCDPort__5__PORT EQU 2
LCD_LCDPort__5__SHIFT EQU 5
LCD_LCDPort__6__MASK EQU 0x40
LCD_LCDPort__6__PC EQU CYREG_PRT2_PC6
LCD_LCDPort__6__PORT EQU 2
LCD_LCDPort__6__SHIFT EQU 6
LCD_LCDPort__AG EQU CYREG_PRT2_AG
LCD_LCDPort__AMUX EQU CYREG_PRT2_AMUX
LCD_LCDPort__BIE EQU CYREG_PRT2_BIE
LCD_LCDPort__BIT_MASK EQU CYREG_PRT2_BIT_MASK
LCD_LCDPort__BYP EQU CYREG_PRT2_BYP
LCD_LCDPort__CTL EQU CYREG_PRT2_CTL
LCD_LCDPort__DM0 EQU CYREG_PRT2_DM0
LCD_LCDPort__DM1 EQU CYREG_PRT2_DM1
LCD_LCDPort__DM2 EQU CYREG_PRT2_DM2
LCD_LCDPort__DR EQU CYREG_PRT2_DR
LCD_LCDPort__INP_DIS EQU CYREG_PRT2_INP_DIS
LCD_LCDPort__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
LCD_LCDPort__LCD_EN EQU CYREG_PRT2_LCD_EN
LCD_LCDPort__MASK EQU 0x7F
LCD_LCDPort__PORT EQU 2
LCD_LCDPort__PRT EQU CYREG_PRT2_PRT
LCD_LCDPort__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
LCD_LCDPort__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
LCD_LCDPort__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
LCD_LCDPort__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
LCD_LCDPort__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
LCD_LCDPort__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
LCD_LCDPort__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
LCD_LCDPort__PS EQU CYREG_PRT2_PS
LCD_LCDPort__SHIFT EQU 0
LCD_LCDPort__SLW EQU CYREG_PRT2_SLW

/* clock */
clock__CFG0 EQU CYREG_CLKDIST_DCFG0_CFG0
clock__CFG1 EQU CYREG_CLKDIST_DCFG0_CFG1
clock__CFG2 EQU CYREG_CLKDIST_DCFG0_CFG2
clock__CFG2_SRC_SEL_MASK EQU 0x07
clock__INDEX EQU 0x00
clock__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
clock__PM_ACT_MSK EQU 0x01
clock__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
clock__PM_STBY_MSK EQU 0x01

/* master_BSPIM */
master_BSPIM_BitCounter__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B1_UDB07_08_ACTL
master_BSPIM_BitCounter__16BIT_CONTROL_CONTROL_REG EQU CYREG_B1_UDB07_08_CTL
master_BSPIM_BitCounter__16BIT_CONTROL_COUNT_REG EQU CYREG_B1_UDB07_08_CTL
master_BSPIM_BitCounter__16BIT_COUNT_CONTROL_REG EQU CYREG_B1_UDB07_08_CTL
master_BSPIM_BitCounter__16BIT_COUNT_COUNT_REG EQU CYREG_B1_UDB07_08_CTL
master_BSPIM_BitCounter__16BIT_MASK_MASK_REG EQU CYREG_B1_UDB07_08_MSK
master_BSPIM_BitCounter__16BIT_MASK_PERIOD_REG EQU CYREG_B1_UDB07_08_MSK
master_BSPIM_BitCounter__16BIT_PERIOD_MASK_REG EQU CYREG_B1_UDB07_08_MSK
master_BSPIM_BitCounter__16BIT_PERIOD_PERIOD_REG EQU CYREG_B1_UDB07_08_MSK
master_BSPIM_BitCounter__CONTROL_AUX_CTL_REG EQU CYREG_B1_UDB07_ACTL
master_BSPIM_BitCounter__CONTROL_REG EQU CYREG_B1_UDB07_CTL
master_BSPIM_BitCounter__CONTROL_ST_REG EQU CYREG_B1_UDB07_ST_CTL
master_BSPIM_BitCounter__COUNT_REG EQU CYREG_B1_UDB07_CTL
master_BSPIM_BitCounter__COUNT_ST_REG EQU CYREG_B1_UDB07_ST_CTL
master_BSPIM_BitCounter__MASK_CTL_AUX_CTL_REG EQU CYREG_B1_UDB07_MSK_ACTL
master_BSPIM_BitCounter__PER_CTL_AUX_CTL_REG EQU CYREG_B1_UDB07_MSK_ACTL
master_BSPIM_BitCounter__PERIOD_REG EQU CYREG_B1_UDB07_MSK
master_BSPIM_BitCounter_ST__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B1_UDB07_08_ACTL
master_BSPIM_BitCounter_ST__16BIT_STATUS_REG EQU CYREG_B1_UDB07_08_ST
master_BSPIM_BitCounter_ST__MASK_REG EQU CYREG_B1_UDB07_MSK
master_BSPIM_BitCounter_ST__MASK_ST_AUX_CTL_REG EQU CYREG_B1_UDB07_MSK_ACTL
master_BSPIM_BitCounter_ST__PER_ST_AUX_CTL_REG EQU CYREG_B1_UDB07_MSK_ACTL
master_BSPIM_BitCounter_ST__STATUS_AUX_CTL_REG EQU CYREG_B1_UDB07_ACTL
master_BSPIM_BitCounter_ST__STATUS_CNT_REG EQU CYREG_B1_UDB07_ST_CTL
master_BSPIM_BitCounter_ST__STATUS_CONTROL_REG EQU CYREG_B1_UDB07_ST_CTL
master_BSPIM_BitCounter_ST__STATUS_REG EQU CYREG_B1_UDB07_ST
master_BSPIM_RxStsReg__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B1_UDB04_05_ACTL
master_BSPIM_RxStsReg__16BIT_STATUS_REG EQU CYREG_B1_UDB04_05_ST
master_BSPIM_RxStsReg__4__MASK EQU 0x10
master_BSPIM_RxStsReg__4__POS EQU 4
master_BSPIM_RxStsReg__5__MASK EQU 0x20
master_BSPIM_RxStsReg__5__POS EQU 5
master_BSPIM_RxStsReg__6__MASK EQU 0x40
master_BSPIM_RxStsReg__6__POS EQU 6
master_BSPIM_RxStsReg__MASK EQU 0x70
master_BSPIM_RxStsReg__MASK_REG EQU CYREG_B1_UDB04_MSK
master_BSPIM_RxStsReg__STATUS_AUX_CTL_REG EQU CYREG_B1_UDB04_ACTL
master_BSPIM_RxStsReg__STATUS_REG EQU CYREG_B1_UDB04_ST
master_BSPIM_sR16_Dp_u0__16BIT_A0_REG EQU CYREG_B1_UDB04_05_A0
master_BSPIM_sR16_Dp_u0__16BIT_A1_REG EQU CYREG_B1_UDB04_05_A1
master_BSPIM_sR16_Dp_u0__16BIT_D0_REG EQU CYREG_B1_UDB04_05_D0
master_BSPIM_sR16_Dp_u0__16BIT_D1_REG EQU CYREG_B1_UDB04_05_D1
master_BSPIM_sR16_Dp_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B1_UDB04_05_ACTL
master_BSPIM_sR16_Dp_u0__16BIT_F0_REG EQU CYREG_B1_UDB04_05_F0
master_BSPIM_sR16_Dp_u0__16BIT_F1_REG EQU CYREG_B1_UDB04_05_F1
master_BSPIM_sR16_Dp_u0__A0_A1_REG EQU CYREG_B1_UDB04_A0_A1
master_BSPIM_sR16_Dp_u0__A0_REG EQU CYREG_B1_UDB04_A0
master_BSPIM_sR16_Dp_u0__A1_REG EQU CYREG_B1_UDB04_A1
master_BSPIM_sR16_Dp_u0__D0_D1_REG EQU CYREG_B1_UDB04_D0_D1
master_BSPIM_sR16_Dp_u0__D0_REG EQU CYREG_B1_UDB04_D0
master_BSPIM_sR16_Dp_u0__D1_REG EQU CYREG_B1_UDB04_D1
master_BSPIM_sR16_Dp_u0__DP_AUX_CTL_REG EQU CYREG_B1_UDB04_ACTL
master_BSPIM_sR16_Dp_u0__F0_F1_REG EQU CYREG_B1_UDB04_F0_F1
master_BSPIM_sR16_Dp_u0__F0_REG EQU CYREG_B1_UDB04_F0
master_BSPIM_sR16_Dp_u0__F1_REG EQU CYREG_B1_UDB04_F1
master_BSPIM_sR16_Dp_u1__16BIT_A0_REG EQU CYREG_B1_UDB05_06_A0
master_BSPIM_sR16_Dp_u1__16BIT_A1_REG EQU CYREG_B1_UDB05_06_A1
master_BSPIM_sR16_Dp_u1__16BIT_D0_REG EQU CYREG_B1_UDB05_06_D0
master_BSPIM_sR16_Dp_u1__16BIT_D1_REG EQU CYREG_B1_UDB05_06_D1
master_BSPIM_sR16_Dp_u1__16BIT_DP_AUX_CTL_REG EQU CYREG_B1_UDB05_06_ACTL
master_BSPIM_sR16_Dp_u1__16BIT_F0_REG EQU CYREG_B1_UDB05_06_F0
master_BSPIM_sR16_Dp_u1__16BIT_F1_REG EQU CYREG_B1_UDB05_06_F1
master_BSPIM_sR16_Dp_u1__A0_A1_REG EQU CYREG_B1_UDB05_A0_A1
master_BSPIM_sR16_Dp_u1__A0_REG EQU CYREG_B1_UDB05_A0
master_BSPIM_sR16_Dp_u1__A1_REG EQU CYREG_B1_UDB05_A1
master_BSPIM_sR16_Dp_u1__D0_D1_REG EQU CYREG_B1_UDB05_D0_D1
master_BSPIM_sR16_Dp_u1__D0_REG EQU CYREG_B1_UDB05_D0
master_BSPIM_sR16_Dp_u1__D1_REG EQU CYREG_B1_UDB05_D1
master_BSPIM_sR16_Dp_u1__DP_AUX_CTL_REG EQU CYREG_B1_UDB05_ACTL
master_BSPIM_sR16_Dp_u1__F0_F1_REG EQU CYREG_B1_UDB05_F0_F1
master_BSPIM_sR16_Dp_u1__F0_REG EQU CYREG_B1_UDB05_F0
master_BSPIM_sR16_Dp_u1__F1_REG EQU CYREG_B1_UDB05_F1
master_BSPIM_TxStsReg__0__MASK EQU 0x01
master_BSPIM_TxStsReg__0__POS EQU 0
master_BSPIM_TxStsReg__1__MASK EQU 0x02
master_BSPIM_TxStsReg__1__POS EQU 1
master_BSPIM_TxStsReg__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B1_UDB05_06_ACTL
master_BSPIM_TxStsReg__16BIT_STATUS_REG EQU CYREG_B1_UDB05_06_ST
master_BSPIM_TxStsReg__2__MASK EQU 0x04
master_BSPIM_TxStsReg__2__POS EQU 2
master_BSPIM_TxStsReg__3__MASK EQU 0x08
master_BSPIM_TxStsReg__3__POS EQU 3
master_BSPIM_TxStsReg__4__MASK EQU 0x10
master_BSPIM_TxStsReg__4__POS EQU 4
master_BSPIM_TxStsReg__MASK EQU 0x1F
master_BSPIM_TxStsReg__MASK_REG EQU CYREG_B1_UDB05_MSK
master_BSPIM_TxStsReg__STATUS_AUX_CTL_REG EQU CYREG_B1_UDB05_ACTL
master_BSPIM_TxStsReg__STATUS_REG EQU CYREG_B1_UDB05_ST

/* dataPin */
dataPin__0__MASK EQU 0x08
dataPin__0__PC EQU CYREG_PRT3_PC3
dataPin__0__PORT EQU 3
dataPin__0__SHIFT EQU 3
dataPin__AG EQU CYREG_PRT3_AG
dataPin__AMUX EQU CYREG_PRT3_AMUX
dataPin__BIE EQU CYREG_PRT3_BIE
dataPin__BIT_MASK EQU CYREG_PRT3_BIT_MASK
dataPin__BYP EQU CYREG_PRT3_BYP
dataPin__CTL EQU CYREG_PRT3_CTL
dataPin__DM0 EQU CYREG_PRT3_DM0
dataPin__DM1 EQU CYREG_PRT3_DM1
dataPin__DM2 EQU CYREG_PRT3_DM2
dataPin__DR EQU CYREG_PRT3_DR
dataPin__INP_DIS EQU CYREG_PRT3_INP_DIS
dataPin__LCD_COM_SEG EQU CYREG_PRT3_LCD_COM_SEG
dataPin__LCD_EN EQU CYREG_PRT3_LCD_EN
dataPin__MASK EQU 0x08
dataPin__PORT EQU 3
dataPin__PRT EQU CYREG_PRT3_PRT
dataPin__PRTDSI__CAPS_SEL EQU CYREG_PRT3_CAPS_SEL
dataPin__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT3_DBL_SYNC_IN
dataPin__PRTDSI__OE_SEL0 EQU CYREG_PRT3_OE_SEL0
dataPin__PRTDSI__OE_SEL1 EQU CYREG_PRT3_OE_SEL1
dataPin__PRTDSI__OUT_SEL0 EQU CYREG_PRT3_OUT_SEL0
dataPin__PRTDSI__OUT_SEL1 EQU CYREG_PRT3_OUT_SEL1
dataPin__PRTDSI__SYNC_OUT EQU CYREG_PRT3_SYNC_OUT
dataPin__PS EQU CYREG_PRT3_PS
dataPin__SHIFT EQU 3
dataPin__SLW EQU CYREG_PRT3_SLW

/* clockPin */
clockPin__0__MASK EQU 0x20
clockPin__0__PC EQU CYREG_PRT3_PC5
clockPin__0__PORT EQU 3
clockPin__0__SHIFT EQU 5
clockPin__AG EQU CYREG_PRT3_AG
clockPin__AMUX EQU CYREG_PRT3_AMUX
clockPin__BIE EQU CYREG_PRT3_BIE
clockPin__BIT_MASK EQU CYREG_PRT3_BIT_MASK
clockPin__BYP EQU CYREG_PRT3_BYP
clockPin__CTL EQU CYREG_PRT3_CTL
clockPin__DM0 EQU CYREG_PRT3_DM0
clockPin__DM1 EQU CYREG_PRT3_DM1
clockPin__DM2 EQU CYREG_PRT3_DM2
clockPin__DR EQU CYREG_PRT3_DR
clockPin__INP_DIS EQU CYREG_PRT3_INP_DIS
clockPin__LCD_COM_SEG EQU CYREG_PRT3_LCD_COM_SEG
clockPin__LCD_EN EQU CYREG_PRT3_LCD_EN
clockPin__MASK EQU 0x20
clockPin__PORT EQU 3
clockPin__PRT EQU CYREG_PRT3_PRT
clockPin__PRTDSI__CAPS_SEL EQU CYREG_PRT3_CAPS_SEL
clockPin__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT3_DBL_SYNC_IN
clockPin__PRTDSI__OE_SEL0 EQU CYREG_PRT3_OE_SEL0
clockPin__PRTDSI__OE_SEL1 EQU CYREG_PRT3_OE_SEL1
clockPin__PRTDSI__OUT_SEL0 EQU CYREG_PRT3_OUT_SEL0
clockPin__PRTDSI__OUT_SEL1 EQU CYREG_PRT3_OUT_SEL1
clockPin__PRTDSI__SYNC_OUT EQU CYREG_PRT3_SYNC_OUT
clockPin__PS EQU CYREG_PRT3_PS
clockPin__SHIFT EQU 5
clockPin__SLW EQU CYREG_PRT3_SLW

/* selectPin */
selectPin__0__MASK EQU 0x10
selectPin__0__PC EQU CYREG_PRT3_PC4
selectPin__0__PORT EQU 3
selectPin__0__SHIFT EQU 4
selectPin__AG EQU CYREG_PRT3_AG
selectPin__AMUX EQU CYREG_PRT3_AMUX
selectPin__BIE EQU CYREG_PRT3_BIE
selectPin__BIT_MASK EQU CYREG_PRT3_BIT_MASK
selectPin__BYP EQU CYREG_PRT3_BYP
selectPin__CTL EQU CYREG_PRT3_CTL
selectPin__DM0 EQU CYREG_PRT3_DM0
selectPin__DM1 EQU CYREG_PRT3_DM1
selectPin__DM2 EQU CYREG_PRT3_DM2
selectPin__DR EQU CYREG_PRT3_DR
selectPin__INP_DIS EQU CYREG_PRT3_INP_DIS
selectPin__LCD_COM_SEG EQU CYREG_PRT3_LCD_COM_SEG
selectPin__LCD_EN EQU CYREG_PRT3_LCD_EN
selectPin__MASK EQU 0x10
selectPin__PORT EQU 3
selectPin__PRT EQU CYREG_PRT3_PRT
selectPin__PRTDSI__CAPS_SEL EQU CYREG_PRT3_CAPS_SEL
selectPin__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT3_DBL_SYNC_IN
selectPin__PRTDSI__OE_SEL0 EQU CYREG_PRT3_OE_SEL0
selectPin__PRTDSI__OE_SEL1 EQU CYREG_PRT3_OE_SEL1
selectPin__PRTDSI__OUT_SEL0 EQU CYREG_PRT3_OUT_SEL0
selectPin__PRTDSI__OUT_SEL1 EQU CYREG_PRT3_OUT_SEL1
selectPin__PRTDSI__SYNC_OUT EQU CYREG_PRT3_SYNC_OUT
selectPin__PS EQU CYREG_PRT3_PS
selectPin__SHIFT EQU 4
selectPin__SLW EQU CYREG_PRT3_SLW

/* Miscellaneous */
BCLK__BUS_CLK__HZ EQU 24000000
BCLK__BUS_CLK__KHZ EQU 24000
BCLK__BUS_CLK__MHZ EQU 24
CYDEV_CHIP_DIE_LEOPARD EQU 1
CYDEV_CHIP_DIE_PANTHER EQU 4
CYDEV_CHIP_DIE_PSOC4A EQU 2
CYDEV_CHIP_DIE_PSOC5LP EQU 5
CYDEV_CHIP_DIE_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_PSOC3 EQU 1
CYDEV_CHIP_FAMILY_PSOC4 EQU 2
CYDEV_CHIP_FAMILY_PSOC5 EQU 3
CYDEV_CHIP_FAMILY_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_USED EQU CYDEV_CHIP_FAMILY_PSOC5
CYDEV_CHIP_JTAG_ID EQU 0x2E123069
CYDEV_CHIP_MEMBER_3A EQU 1
CYDEV_CHIP_MEMBER_4A EQU 2
CYDEV_CHIP_MEMBER_4D EQU 3
CYDEV_CHIP_MEMBER_5A EQU 4
CYDEV_CHIP_MEMBER_5B EQU 5
CYDEV_CHIP_MEMBER_UNKNOWN EQU 0
CYDEV_CHIP_MEMBER_USED EQU CYDEV_CHIP_MEMBER_5B
CYDEV_CHIP_DIE_EXPECT EQU CYDEV_CHIP_MEMBER_USED
CYDEV_CHIP_DIE_ACTUAL EQU CYDEV_CHIP_DIE_EXPECT
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
CYDEV_CHIP_REV_PSOC5LP_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_3A_ES1 EQU 0
CYDEV_CHIP_REVISION_3A_ES2 EQU 1
CYDEV_CHIP_REVISION_3A_ES3 EQU 3
CYDEV_CHIP_REVISION_3A_PRODUCTION EQU 3
CYDEV_CHIP_REVISION_4A_ES0 EQU 17
CYDEV_CHIP_REVISION_4A_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4D_ES0 EQU 0
CYDEV_CHIP_REVISION_4D_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_5A_ES0 EQU 0
CYDEV_CHIP_REVISION_5A_ES1 EQU 1
CYDEV_CHIP_REVISION_5A_PRODUCTION EQU 1
CYDEV_CHIP_REVISION_5B_ES0 EQU 0
CYDEV_CHIP_REVISION_5B_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_USED EQU CYDEV_CHIP_REVISION_5B_PRODUCTION
CYDEV_CHIP_REV_EXPECT EQU CYDEV_CHIP_REVISION_USED
CYDEV_CONFIG_FASTBOOT_ENABLED EQU 1
CYDEV_CONFIG_UNUSED_IO_AllowButWarn EQU 0
CYDEV_CONFIG_UNUSED_IO EQU CYDEV_CONFIG_UNUSED_IO_AllowButWarn
CYDEV_CONFIG_UNUSED_IO_AllowWithInfo EQU 1
CYDEV_CONFIG_UNUSED_IO_Disallowed EQU 2
CYDEV_CONFIGURATION_COMPRESSED EQU 1
CYDEV_CONFIGURATION_DMA EQU 0
CYDEV_CONFIGURATION_ECC EQU 1
CYDEV_CONFIGURATION_IMOENABLED EQU CYDEV_CONFIG_FASTBOOT_ENABLED
CYDEV_CONFIGURATION_MODE_COMPRESSED EQU 0
CYDEV_CONFIGURATION_MODE EQU CYDEV_CONFIGURATION_MODE_COMPRESSED
CYDEV_CONFIGURATION_MODE_DMA EQU 2
CYDEV_CONFIGURATION_MODE_UNCOMPRESSED EQU 1
CYDEV_DEBUG_ENABLE_MASK EQU 0x20
CYDEV_DEBUG_ENABLE_REGISTER EQU CYREG_MLOGIC_DEBUG
CYDEV_DEBUGGING_DPS_Disable EQU 3
CYDEV_DEBUGGING_DPS_JTAG_4 EQU 1
CYDEV_DEBUGGING_DPS_JTAG_5 EQU 0
CYDEV_DEBUGGING_DPS_SWD EQU 2
CYDEV_DEBUGGING_DPS_SWD_SWV EQU 6
CYDEV_DEBUGGING_DPS EQU CYDEV_DEBUGGING_DPS_SWD_SWV
CYDEV_DEBUGGING_ENABLE EQU 1
CYDEV_DEBUGGING_XRES EQU 0
CYDEV_DMA_CHANNELS_AVAILABLE EQU 24
CYDEV_ECC_ENABLE EQU 0
CYDEV_HEAP_SIZE EQU 0x1000
CYDEV_INSTRUCT_CACHE_ENABLED EQU 1
CYDEV_INTR_RISING EQU 0x00000000
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
CYIPBLOCK_ARM_CM3_VERSION EQU 0
CYIPBLOCK_P3_ANAIF_VERSION EQU 0
CYIPBLOCK_P3_CAN_VERSION EQU 0
CYIPBLOCK_P3_CAPSENSE_VERSION EQU 0
CYIPBLOCK_P3_COMP_VERSION EQU 0
CYIPBLOCK_P3_DECIMATOR_VERSION EQU 0
CYIPBLOCK_P3_DFB_VERSION EQU 0
CYIPBLOCK_P3_DMA_VERSION EQU 0
CYIPBLOCK_P3_DRQ_VERSION EQU 0
CYIPBLOCK_P3_DSM_VERSION EQU 0
CYIPBLOCK_P3_EMIF_VERSION EQU 0
CYIPBLOCK_P3_I2C_VERSION EQU 0
CYIPBLOCK_P3_LCD_VERSION EQU 0
CYIPBLOCK_P3_LPF_VERSION EQU 0
CYIPBLOCK_P3_OPAMP_VERSION EQU 0
CYIPBLOCK_P3_PM_VERSION EQU 0
CYIPBLOCK_P3_SCCT_VERSION EQU 0
CYIPBLOCK_P3_TIMER_VERSION EQU 0
CYIPBLOCK_P3_USB_VERSION EQU 0
CYIPBLOCK_P3_VIDAC_VERSION EQU 0
CYIPBLOCK_P3_VREF_VERSION EQU 0
CYIPBLOCK_S8_GPIO_VERSION EQU 0
CYIPBLOCK_S8_IRQ_VERSION EQU 0
CYIPBLOCK_S8_SAR_VERSION EQU 0
CYIPBLOCK_S8_SIO_VERSION EQU 0
CYIPBLOCK_S8_UDB_VERSION EQU 0
DMA_CHANNELS_USED__MASK0 EQU 0x00000000
CYDEV_BOOTLOADER_ENABLE EQU 0

#endif /* INCLUDED_CYFITTERIAR_INC */