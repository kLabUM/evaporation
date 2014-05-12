#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include <cydevice.h>
#include <cydevice_trm.h>

/* ADC_DelSig_Ext_CP_Clk */
#define ADC_DelSig_Ext_CP_Clk__CFG0 CYREG_CLKDIST_DCFG0_CFG0
#define ADC_DelSig_Ext_CP_Clk__CFG1 CYREG_CLKDIST_DCFG0_CFG1
#define ADC_DelSig_Ext_CP_Clk__CFG2 CYREG_CLKDIST_DCFG0_CFG2
#define ADC_DelSig_Ext_CP_Clk__CFG2_SRC_SEL_MASK 0x07u
#define ADC_DelSig_Ext_CP_Clk__INDEX 0x00u
#define ADC_DelSig_Ext_CP_Clk__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define ADC_DelSig_Ext_CP_Clk__PM_ACT_MSK 0x01u
#define ADC_DelSig_Ext_CP_Clk__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define ADC_DelSig_Ext_CP_Clk__PM_STBY_MSK 0x01u

/* ADC_DelSig_theACLK */
#define ADC_DelSig_theACLK__CFG0 CYREG_CLKDIST_ACFG0_CFG0
#define ADC_DelSig_theACLK__CFG1 CYREG_CLKDIST_ACFG0_CFG1
#define ADC_DelSig_theACLK__CFG2 CYREG_CLKDIST_ACFG0_CFG2
#define ADC_DelSig_theACLK__CFG2_SRC_SEL_MASK 0x07u
#define ADC_DelSig_theACLK__CFG3 CYREG_CLKDIST_ACFG0_CFG3
#define ADC_DelSig_theACLK__CFG3_PHASE_DLY_MASK 0x0Fu
#define ADC_DelSig_theACLK__INDEX 0x00u
#define ADC_DelSig_theACLK__PM_ACT_CFG CYREG_PM_ACT_CFG1
#define ADC_DelSig_theACLK__PM_ACT_MSK 0x01u
#define ADC_DelSig_theACLK__PM_STBY_CFG CYREG_PM_STBY_CFG1
#define ADC_DelSig_theACLK__PM_STBY_MSK 0x01u

/* ADC_DelSig_DEC */
#define ADC_DelSig_DEC__COHER CYREG_DEC_COHER
#define ADC_DelSig_DEC__CR CYREG_DEC_CR
#define ADC_DelSig_DEC__DR1 CYREG_DEC_DR1
#define ADC_DelSig_DEC__DR2 CYREG_DEC_DR2
#define ADC_DelSig_DEC__DR2H CYREG_DEC_DR2H
#define ADC_DelSig_DEC__GCOR CYREG_DEC_GCOR
#define ADC_DelSig_DEC__GCORH CYREG_DEC_GCORH
#define ADC_DelSig_DEC__GVAL CYREG_DEC_GVAL
#define ADC_DelSig_DEC__OCOR CYREG_DEC_OCOR
#define ADC_DelSig_DEC__OCORH CYREG_DEC_OCORH
#define ADC_DelSig_DEC__OCORM CYREG_DEC_OCORM
#define ADC_DelSig_DEC__OUTSAMP CYREG_DEC_OUTSAMP
#define ADC_DelSig_DEC__OUTSAMPH CYREG_DEC_OUTSAMPH
#define ADC_DelSig_DEC__OUTSAMPM CYREG_DEC_OUTSAMPM
#define ADC_DelSig_DEC__OUTSAMPS CYREG_DEC_OUTSAMPS
#define ADC_DelSig_DEC__PM_ACT_CFG CYREG_PM_ACT_CFG10
#define ADC_DelSig_DEC__PM_ACT_MSK 0x01u
#define ADC_DelSig_DEC__PM_STBY_CFG CYREG_PM_STBY_CFG10
#define ADC_DelSig_DEC__PM_STBY_MSK 0x01u
#define ADC_DelSig_DEC__SHIFT1 CYREG_DEC_SHIFT1
#define ADC_DelSig_DEC__SHIFT2 CYREG_DEC_SHIFT2
#define ADC_DelSig_DEC__SR CYREG_DEC_SR
#define ADC_DelSig_DEC__TRIM__M1 CYREG_FLSHID_CUST_TABLES_DEC_M1
#define ADC_DelSig_DEC__TRIM__M2 CYREG_FLSHID_CUST_TABLES_DEC_M2
#define ADC_DelSig_DEC__TRIM__M3 CYREG_FLSHID_CUST_TABLES_DEC_M3
#define ADC_DelSig_DEC__TRIM__M4 CYREG_FLSHID_CUST_TABLES_DEC_M4
#define ADC_DelSig_DEC__TRIM__M5 CYREG_FLSHID_CUST_TABLES_DEC_M5
#define ADC_DelSig_DEC__TRIM__M6 CYREG_FLSHID_CUST_TABLES_DEC_M6
#define ADC_DelSig_DEC__TRIM__M7 CYREG_FLSHID_CUST_TABLES_DEC_M7
#define ADC_DelSig_DEC__TRIM__M8 CYREG_FLSHID_CUST_TABLES_DEC_M8

/* ADC_DelSig_DSM */
#define ADC_DelSig_DSM__BUF0 CYREG_DSM0_BUF0
#define ADC_DelSig_DSM__BUF1 CYREG_DSM0_BUF1
#define ADC_DelSig_DSM__BUF2 CYREG_DSM0_BUF2
#define ADC_DelSig_DSM__BUF3 CYREG_DSM0_BUF3
#define ADC_DelSig_DSM__CLK CYREG_DSM0_CLK
#define ADC_DelSig_DSM__CR0 CYREG_DSM0_CR0
#define ADC_DelSig_DSM__CR1 CYREG_DSM0_CR1
#define ADC_DelSig_DSM__CR10 CYREG_DSM0_CR10
#define ADC_DelSig_DSM__CR11 CYREG_DSM0_CR11
#define ADC_DelSig_DSM__CR12 CYREG_DSM0_CR12
#define ADC_DelSig_DSM__CR13 CYREG_DSM0_CR13
#define ADC_DelSig_DSM__CR14 CYREG_DSM0_CR14
#define ADC_DelSig_DSM__CR15 CYREG_DSM0_CR15
#define ADC_DelSig_DSM__CR16 CYREG_DSM0_CR16
#define ADC_DelSig_DSM__CR17 CYREG_DSM0_CR17
#define ADC_DelSig_DSM__CR2 CYREG_DSM0_CR2
#define ADC_DelSig_DSM__CR3 CYREG_DSM0_CR3
#define ADC_DelSig_DSM__CR4 CYREG_DSM0_CR4
#define ADC_DelSig_DSM__CR5 CYREG_DSM0_CR5
#define ADC_DelSig_DSM__CR6 CYREG_DSM0_CR6
#define ADC_DelSig_DSM__CR7 CYREG_DSM0_CR7
#define ADC_DelSig_DSM__CR8 CYREG_DSM0_CR8
#define ADC_DelSig_DSM__CR9 CYREG_DSM0_CR9
#define ADC_DelSig_DSM__DEM0 CYREG_DSM0_DEM0
#define ADC_DelSig_DSM__DEM1 CYREG_DSM0_DEM1
#define ADC_DelSig_DSM__MISC CYREG_DSM0_MISC
#define ADC_DelSig_DSM__OUT0 CYREG_DSM0_OUT0
#define ADC_DelSig_DSM__OUT1 CYREG_DSM0_OUT1
#define ADC_DelSig_DSM__REF0 CYREG_DSM0_REF0
#define ADC_DelSig_DSM__REF1 CYREG_DSM0_REF1
#define ADC_DelSig_DSM__REF2 CYREG_DSM0_REF2
#define ADC_DelSig_DSM__REF3 CYREG_DSM0_REF3
#define ADC_DelSig_DSM__RSVD1 CYREG_DSM0_RSVD1
#define ADC_DelSig_DSM__SW0 CYREG_DSM0_SW0
#define ADC_DelSig_DSM__SW2 CYREG_DSM0_SW2
#define ADC_DelSig_DSM__SW3 CYREG_DSM0_SW3
#define ADC_DelSig_DSM__SW4 CYREG_DSM0_SW4
#define ADC_DelSig_DSM__SW6 CYREG_DSM0_SW6
#define ADC_DelSig_DSM__TR0 CYREG_NPUMP_DSM_TR0
#define ADC_DelSig_DSM__TST0 CYREG_DSM0_TST0
#define ADC_DelSig_DSM__TST1 CYREG_DSM0_TST1

/* ADC_DelSig_IRQ */
#define ADC_DelSig_IRQ__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define ADC_DelSig_IRQ__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define ADC_DelSig_IRQ__INTC_MASK 0x20000000u
#define ADC_DelSig_IRQ__INTC_NUMBER 29u
#define ADC_DelSig_IRQ__INTC_PRIOR_NUM 7u
#define ADC_DelSig_IRQ__INTC_PRIOR_REG CYREG_NVIC_PRI_29
#define ADC_DelSig_IRQ__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define ADC_DelSig_IRQ__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* Vaisala_Temp */
#define Vaisala_Temp__0__MASK 0x02u
#define Vaisala_Temp__0__PC CYREG_PRT0_PC1
#define Vaisala_Temp__0__PORT 0u
#define Vaisala_Temp__0__SHIFT 1
#define Vaisala_Temp__AG CYREG_PRT0_AG
#define Vaisala_Temp__AMUX CYREG_PRT0_AMUX
#define Vaisala_Temp__BIE CYREG_PRT0_BIE
#define Vaisala_Temp__BIT_MASK CYREG_PRT0_BIT_MASK
#define Vaisala_Temp__BYP CYREG_PRT0_BYP
#define Vaisala_Temp__CTL CYREG_PRT0_CTL
#define Vaisala_Temp__DM0 CYREG_PRT0_DM0
#define Vaisala_Temp__DM1 CYREG_PRT0_DM1
#define Vaisala_Temp__DM2 CYREG_PRT0_DM2
#define Vaisala_Temp__DR CYREG_PRT0_DR
#define Vaisala_Temp__INP_DIS CYREG_PRT0_INP_DIS
#define Vaisala_Temp__LCD_COM_SEG CYREG_PRT0_LCD_COM_SEG
#define Vaisala_Temp__LCD_EN CYREG_PRT0_LCD_EN
#define Vaisala_Temp__MASK 0x02u
#define Vaisala_Temp__PORT 0u
#define Vaisala_Temp__PRT CYREG_PRT0_PRT
#define Vaisala_Temp__PRTDSI__CAPS_SEL CYREG_PRT0_CAPS_SEL
#define Vaisala_Temp__PRTDSI__DBL_SYNC_IN CYREG_PRT0_DBL_SYNC_IN
#define Vaisala_Temp__PRTDSI__OE_SEL0 CYREG_PRT0_OE_SEL0
#define Vaisala_Temp__PRTDSI__OE_SEL1 CYREG_PRT0_OE_SEL1
#define Vaisala_Temp__PRTDSI__OUT_SEL0 CYREG_PRT0_OUT_SEL0
#define Vaisala_Temp__PRTDSI__OUT_SEL1 CYREG_PRT0_OUT_SEL1
#define Vaisala_Temp__PRTDSI__SYNC_OUT CYREG_PRT0_SYNC_OUT
#define Vaisala_Temp__PS CYREG_PRT0_PS
#define Vaisala_Temp__SHIFT 1
#define Vaisala_Temp__SLW CYREG_PRT0_SLW

/* Vaisala_RH */
#define Vaisala_RH__0__MASK 0x01u
#define Vaisala_RH__0__PC CYREG_PRT0_PC0
#define Vaisala_RH__0__PORT 0u
#define Vaisala_RH__0__SHIFT 0
#define Vaisala_RH__AG CYREG_PRT0_AG
#define Vaisala_RH__AMUX CYREG_PRT0_AMUX
#define Vaisala_RH__BIE CYREG_PRT0_BIE
#define Vaisala_RH__BIT_MASK CYREG_PRT0_BIT_MASK
#define Vaisala_RH__BYP CYREG_PRT0_BYP
#define Vaisala_RH__CTL CYREG_PRT0_CTL
#define Vaisala_RH__DM0 CYREG_PRT0_DM0
#define Vaisala_RH__DM1 CYREG_PRT0_DM1
#define Vaisala_RH__DM2 CYREG_PRT0_DM2
#define Vaisala_RH__DR CYREG_PRT0_DR
#define Vaisala_RH__INP_DIS CYREG_PRT0_INP_DIS
#define Vaisala_RH__LCD_COM_SEG CYREG_PRT0_LCD_COM_SEG
#define Vaisala_RH__LCD_EN CYREG_PRT0_LCD_EN
#define Vaisala_RH__MASK 0x01u
#define Vaisala_RH__PORT 0u
#define Vaisala_RH__PRT CYREG_PRT0_PRT
#define Vaisala_RH__PRTDSI__CAPS_SEL CYREG_PRT0_CAPS_SEL
#define Vaisala_RH__PRTDSI__DBL_SYNC_IN CYREG_PRT0_DBL_SYNC_IN
#define Vaisala_RH__PRTDSI__OE_SEL0 CYREG_PRT0_OE_SEL0
#define Vaisala_RH__PRTDSI__OE_SEL1 CYREG_PRT0_OE_SEL1
#define Vaisala_RH__PRTDSI__OUT_SEL0 CYREG_PRT0_OUT_SEL0
#define Vaisala_RH__PRTDSI__OUT_SEL1 CYREG_PRT0_OUT_SEL1
#define Vaisala_RH__PRTDSI__SYNC_OUT CYREG_PRT0_SYNC_OUT
#define Vaisala_RH__PS CYREG_PRT0_PS
#define Vaisala_RH__SHIFT 0
#define Vaisala_RH__SLW CYREG_PRT0_SLW

/* Miscellaneous */
/* -- WARNING: define names containing LEOPARD or PANTHER are deprecated and will be removed in a future release */
#define CYDEV_DEBUGGING_DPS_SWD_SWV 6
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIG_FASTBOOT_ENABLED 1
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_MEMBER_5B 4u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_DIE_PSOC5LP 4u
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_DIE_PSOC5LP
#define BCLK__BUS_CLK__HZ 24000000U
#define BCLK__BUS_CLK__KHZ 24000U
#define BCLK__BUS_CLK__MHZ 24U
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PANTHER 3u
#define CYDEV_CHIP_DIE_PSOC4A 2u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC5
#define CYDEV_CHIP_JTAG_ID 0x2E123069u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 2u
#define CYDEV_CHIP_MEMBER_5A 3u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_5B
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_5B_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REV_PSOC5LP_PRODUCTION
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_DMA 0
#define CYDEV_CONFIGURATION_ECC 1
#define CYDEV_CONFIGURATION_IMOENABLED CYDEV_CONFIG_FASTBOOT_ENABLED
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD_SWV
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_JTAG_4 1
#define CYDEV_DEBUGGING_DPS_JTAG_5 0
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DEBUGGING_XRES 0
#define CYDEV_DEBUG_ENABLE_MASK 0x20u
#define CYDEV_DEBUG_ENABLE_REGISTER CYREG_MLOGIC_DEBUG
#define CYDEV_DMA_CHANNELS_AVAILABLE 24u
#define CYDEV_ECC_ENABLE 0
#define CYDEV_HEAP_SIZE 0x1000
#define CYDEV_INSTRUCT_CACHE_ENABLED 1
#define CYDEV_INTR_RISING 0x00000000u
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_PROTECTION_ENABLE 0
#define CYDEV_STACK_SIZE 0x4000
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VARIABLE_VDDA 0
#define CYDEV_VDDA 5.0
#define CYDEV_VDDA_MV 5000
#define CYDEV_VDDD 5.0
#define CYDEV_VDDD_MV 5000
#define CYDEV_VDDIO0 5.0
#define CYDEV_VDDIO0_MV 5000
#define CYDEV_VDDIO1 5.0
#define CYDEV_VDDIO1_MV 5000
#define CYDEV_VDDIO2 5.0
#define CYDEV_VDDIO2_MV 5000
#define CYDEV_VDDIO3 5.0
#define CYDEV_VDDIO3_MV 5000
#define CYDEV_VIO0 5
#define CYDEV_VIO0_MV 5000
#define CYDEV_VIO1 5
#define CYDEV_VIO1_MV 5000
#define CYDEV_VIO2 5
#define CYDEV_VIO2_MV 5000
#define CYDEV_VIO3 5
#define CYDEV_VIO3_MV 5000
#define DMA_CHANNELS_USED__MASK0 0x00000000u
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
