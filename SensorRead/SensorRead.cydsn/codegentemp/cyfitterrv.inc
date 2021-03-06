    IF :LNOT::DEF:INCLUDED_CYFITTERRV_INC
INCLUDED_CYFITTERRV_INC EQU 1
    GET cydevicerv.inc
    GET cydevicerv_trm.inc

; ADC_DelSig_Ext_CP_Clk
ADC_DelSig_Ext_CP_Clk__CFG0 EQU CYREG_CLKDIST_DCFG0_CFG0
ADC_DelSig_Ext_CP_Clk__CFG1 EQU CYREG_CLKDIST_DCFG0_CFG1
ADC_DelSig_Ext_CP_Clk__CFG2 EQU CYREG_CLKDIST_DCFG0_CFG2
ADC_DelSig_Ext_CP_Clk__CFG2_SRC_SEL_MASK EQU 0x07
ADC_DelSig_Ext_CP_Clk__INDEX EQU 0x00
ADC_DelSig_Ext_CP_Clk__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
ADC_DelSig_Ext_CP_Clk__PM_ACT_MSK EQU 0x01
ADC_DelSig_Ext_CP_Clk__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
ADC_DelSig_Ext_CP_Clk__PM_STBY_MSK EQU 0x01

; ADC_DelSig_theACLK
ADC_DelSig_theACLK__CFG0 EQU CYREG_CLKDIST_ACFG0_CFG0
ADC_DelSig_theACLK__CFG1 EQU CYREG_CLKDIST_ACFG0_CFG1
ADC_DelSig_theACLK__CFG2 EQU CYREG_CLKDIST_ACFG0_CFG2
ADC_DelSig_theACLK__CFG2_SRC_SEL_MASK EQU 0x07
ADC_DelSig_theACLK__CFG3 EQU CYREG_CLKDIST_ACFG0_CFG3
ADC_DelSig_theACLK__CFG3_PHASE_DLY_MASK EQU 0x0F
ADC_DelSig_theACLK__INDEX EQU 0x00
ADC_DelSig_theACLK__PM_ACT_CFG EQU CYREG_PM_ACT_CFG1
ADC_DelSig_theACLK__PM_ACT_MSK EQU 0x01
ADC_DelSig_theACLK__PM_STBY_CFG EQU CYREG_PM_STBY_CFG1
ADC_DelSig_theACLK__PM_STBY_MSK EQU 0x01

; ADC_DelSig_DEC
ADC_DelSig_DEC__COHER EQU CYREG_DEC_COHER
ADC_DelSig_DEC__CR EQU CYREG_DEC_CR
ADC_DelSig_DEC__DR1 EQU CYREG_DEC_DR1
ADC_DelSig_DEC__DR2 EQU CYREG_DEC_DR2
ADC_DelSig_DEC__DR2H EQU CYREG_DEC_DR2H
ADC_DelSig_DEC__GCOR EQU CYREG_DEC_GCOR
ADC_DelSig_DEC__GCORH EQU CYREG_DEC_GCORH
ADC_DelSig_DEC__GVAL EQU CYREG_DEC_GVAL
ADC_DelSig_DEC__OCOR EQU CYREG_DEC_OCOR
ADC_DelSig_DEC__OCORH EQU CYREG_DEC_OCORH
ADC_DelSig_DEC__OCORM EQU CYREG_DEC_OCORM
ADC_DelSig_DEC__OUTSAMP EQU CYREG_DEC_OUTSAMP
ADC_DelSig_DEC__OUTSAMPH EQU CYREG_DEC_OUTSAMPH
ADC_DelSig_DEC__OUTSAMPM EQU CYREG_DEC_OUTSAMPM
ADC_DelSig_DEC__OUTSAMPS EQU CYREG_DEC_OUTSAMPS
ADC_DelSig_DEC__PM_ACT_CFG EQU CYREG_PM_ACT_CFG10
ADC_DelSig_DEC__PM_ACT_MSK EQU 0x01
ADC_DelSig_DEC__PM_STBY_CFG EQU CYREG_PM_STBY_CFG10
ADC_DelSig_DEC__PM_STBY_MSK EQU 0x01
ADC_DelSig_DEC__SHIFT1 EQU CYREG_DEC_SHIFT1
ADC_DelSig_DEC__SHIFT2 EQU CYREG_DEC_SHIFT2
ADC_DelSig_DEC__SR EQU CYREG_DEC_SR
ADC_DelSig_DEC__TRIM__M1 EQU CYREG_FLSHID_CUST_TABLES_DEC_M1
ADC_DelSig_DEC__TRIM__M2 EQU CYREG_FLSHID_CUST_TABLES_DEC_M2
ADC_DelSig_DEC__TRIM__M3 EQU CYREG_FLSHID_CUST_TABLES_DEC_M3
ADC_DelSig_DEC__TRIM__M4 EQU CYREG_FLSHID_CUST_TABLES_DEC_M4
ADC_DelSig_DEC__TRIM__M5 EQU CYREG_FLSHID_CUST_TABLES_DEC_M5
ADC_DelSig_DEC__TRIM__M6 EQU CYREG_FLSHID_CUST_TABLES_DEC_M6
ADC_DelSig_DEC__TRIM__M7 EQU CYREG_FLSHID_CUST_TABLES_DEC_M7
ADC_DelSig_DEC__TRIM__M8 EQU CYREG_FLSHID_CUST_TABLES_DEC_M8

; ADC_DelSig_DSM
ADC_DelSig_DSM__BUF0 EQU CYREG_DSM0_BUF0
ADC_DelSig_DSM__BUF1 EQU CYREG_DSM0_BUF1
ADC_DelSig_DSM__BUF2 EQU CYREG_DSM0_BUF2
ADC_DelSig_DSM__BUF3 EQU CYREG_DSM0_BUF3
ADC_DelSig_DSM__CLK EQU CYREG_DSM0_CLK
ADC_DelSig_DSM__CR0 EQU CYREG_DSM0_CR0
ADC_DelSig_DSM__CR1 EQU CYREG_DSM0_CR1
ADC_DelSig_DSM__CR10 EQU CYREG_DSM0_CR10
ADC_DelSig_DSM__CR11 EQU CYREG_DSM0_CR11
ADC_DelSig_DSM__CR12 EQU CYREG_DSM0_CR12
ADC_DelSig_DSM__CR13 EQU CYREG_DSM0_CR13
ADC_DelSig_DSM__CR14 EQU CYREG_DSM0_CR14
ADC_DelSig_DSM__CR15 EQU CYREG_DSM0_CR15
ADC_DelSig_DSM__CR16 EQU CYREG_DSM0_CR16
ADC_DelSig_DSM__CR17 EQU CYREG_DSM0_CR17
ADC_DelSig_DSM__CR2 EQU CYREG_DSM0_CR2
ADC_DelSig_DSM__CR3 EQU CYREG_DSM0_CR3
ADC_DelSig_DSM__CR4 EQU CYREG_DSM0_CR4
ADC_DelSig_DSM__CR5 EQU CYREG_DSM0_CR5
ADC_DelSig_DSM__CR6 EQU CYREG_DSM0_CR6
ADC_DelSig_DSM__CR7 EQU CYREG_DSM0_CR7
ADC_DelSig_DSM__CR8 EQU CYREG_DSM0_CR8
ADC_DelSig_DSM__CR9 EQU CYREG_DSM0_CR9
ADC_DelSig_DSM__DEM0 EQU CYREG_DSM0_DEM0
ADC_DelSig_DSM__DEM1 EQU CYREG_DSM0_DEM1
ADC_DelSig_DSM__MISC EQU CYREG_DSM0_MISC
ADC_DelSig_DSM__OUT0 EQU CYREG_DSM0_OUT0
ADC_DelSig_DSM__OUT1 EQU CYREG_DSM0_OUT1
ADC_DelSig_DSM__REF0 EQU CYREG_DSM0_REF0
ADC_DelSig_DSM__REF1 EQU CYREG_DSM0_REF1
ADC_DelSig_DSM__REF2 EQU CYREG_DSM0_REF2
ADC_DelSig_DSM__REF3 EQU CYREG_DSM0_REF3
ADC_DelSig_DSM__RSVD1 EQU CYREG_DSM0_RSVD1
ADC_DelSig_DSM__SW0 EQU CYREG_DSM0_SW0
ADC_DelSig_DSM__SW2 EQU CYREG_DSM0_SW2
ADC_DelSig_DSM__SW3 EQU CYREG_DSM0_SW3
ADC_DelSig_DSM__SW4 EQU CYREG_DSM0_SW4
ADC_DelSig_DSM__SW6 EQU CYREG_DSM0_SW6
ADC_DelSig_DSM__TR0 EQU CYREG_NPUMP_DSM_TR0
ADC_DelSig_DSM__TST0 EQU CYREG_DSM0_TST0
ADC_DelSig_DSM__TST1 EQU CYREG_DSM0_TST1

; ADC_DelSig_IRQ
ADC_DelSig_IRQ__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
ADC_DelSig_IRQ__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
ADC_DelSig_IRQ__INTC_MASK EQU 0x20000000
ADC_DelSig_IRQ__INTC_NUMBER EQU 29
ADC_DelSig_IRQ__INTC_PRIOR_NUM EQU 7
ADC_DelSig_IRQ__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_29
ADC_DelSig_IRQ__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
ADC_DelSig_IRQ__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0

; Vaisala_Temp
Vaisala_Temp__0__MASK EQU 0x02
Vaisala_Temp__0__PC EQU CYREG_PRT0_PC1
Vaisala_Temp__0__PORT EQU 0
Vaisala_Temp__0__SHIFT EQU 1
Vaisala_Temp__AG EQU CYREG_PRT0_AG
Vaisala_Temp__AMUX EQU CYREG_PRT0_AMUX
Vaisala_Temp__BIE EQU CYREG_PRT0_BIE
Vaisala_Temp__BIT_MASK EQU CYREG_PRT0_BIT_MASK
Vaisala_Temp__BYP EQU CYREG_PRT0_BYP
Vaisala_Temp__CTL EQU CYREG_PRT0_CTL
Vaisala_Temp__DM0 EQU CYREG_PRT0_DM0
Vaisala_Temp__DM1 EQU CYREG_PRT0_DM1
Vaisala_Temp__DM2 EQU CYREG_PRT0_DM2
Vaisala_Temp__DR EQU CYREG_PRT0_DR
Vaisala_Temp__INP_DIS EQU CYREG_PRT0_INP_DIS
Vaisala_Temp__LCD_COM_SEG EQU CYREG_PRT0_LCD_COM_SEG
Vaisala_Temp__LCD_EN EQU CYREG_PRT0_LCD_EN
Vaisala_Temp__MASK EQU 0x02
Vaisala_Temp__PORT EQU 0
Vaisala_Temp__PRT EQU CYREG_PRT0_PRT
Vaisala_Temp__PRTDSI__CAPS_SEL EQU CYREG_PRT0_CAPS_SEL
Vaisala_Temp__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT0_DBL_SYNC_IN
Vaisala_Temp__PRTDSI__OE_SEL0 EQU CYREG_PRT0_OE_SEL0
Vaisala_Temp__PRTDSI__OE_SEL1 EQU CYREG_PRT0_OE_SEL1
Vaisala_Temp__PRTDSI__OUT_SEL0 EQU CYREG_PRT0_OUT_SEL0
Vaisala_Temp__PRTDSI__OUT_SEL1 EQU CYREG_PRT0_OUT_SEL1
Vaisala_Temp__PRTDSI__SYNC_OUT EQU CYREG_PRT0_SYNC_OUT
Vaisala_Temp__PS EQU CYREG_PRT0_PS
Vaisala_Temp__SHIFT EQU 1
Vaisala_Temp__SLW EQU CYREG_PRT0_SLW

; Vaisala_RH
Vaisala_RH__0__MASK EQU 0x01
Vaisala_RH__0__PC EQU CYREG_PRT0_PC0
Vaisala_RH__0__PORT EQU 0
Vaisala_RH__0__SHIFT EQU 0
Vaisala_RH__AG EQU CYREG_PRT0_AG
Vaisala_RH__AMUX EQU CYREG_PRT0_AMUX
Vaisala_RH__BIE EQU CYREG_PRT0_BIE
Vaisala_RH__BIT_MASK EQU CYREG_PRT0_BIT_MASK
Vaisala_RH__BYP EQU CYREG_PRT0_BYP
Vaisala_RH__CTL EQU CYREG_PRT0_CTL
Vaisala_RH__DM0 EQU CYREG_PRT0_DM0
Vaisala_RH__DM1 EQU CYREG_PRT0_DM1
Vaisala_RH__DM2 EQU CYREG_PRT0_DM2
Vaisala_RH__DR EQU CYREG_PRT0_DR
Vaisala_RH__INP_DIS EQU CYREG_PRT0_INP_DIS
Vaisala_RH__LCD_COM_SEG EQU CYREG_PRT0_LCD_COM_SEG
Vaisala_RH__LCD_EN EQU CYREG_PRT0_LCD_EN
Vaisala_RH__MASK EQU 0x01
Vaisala_RH__PORT EQU 0
Vaisala_RH__PRT EQU CYREG_PRT0_PRT
Vaisala_RH__PRTDSI__CAPS_SEL EQU CYREG_PRT0_CAPS_SEL
Vaisala_RH__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT0_DBL_SYNC_IN
Vaisala_RH__PRTDSI__OE_SEL0 EQU CYREG_PRT0_OE_SEL0
Vaisala_RH__PRTDSI__OE_SEL1 EQU CYREG_PRT0_OE_SEL1
Vaisala_RH__PRTDSI__OUT_SEL0 EQU CYREG_PRT0_OUT_SEL0
Vaisala_RH__PRTDSI__OUT_SEL1 EQU CYREG_PRT0_OUT_SEL1
Vaisala_RH__PRTDSI__SYNC_OUT EQU CYREG_PRT0_SYNC_OUT
Vaisala_RH__PS EQU CYREG_PRT0_PS
Vaisala_RH__SHIFT EQU 0
Vaisala_RH__SLW EQU CYREG_PRT0_SLW

; Miscellaneous
; -- WARNING: define names containing LEOPARD or PANTHER are deprecated and will be removed in a future release
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
DMA_CHANNELS_USED__MASK0 EQU 0x00000000
CYDEV_BOOTLOADER_ENABLE EQU 0
    ENDIF
    END
