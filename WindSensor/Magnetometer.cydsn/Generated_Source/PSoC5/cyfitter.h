#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include <cydevice.h>
#include <cydevice_trm.h>

/* psoc_I2C_IRQ */
#define psoc_I2C_IRQ__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define psoc_I2C_IRQ__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define psoc_I2C_IRQ__INTC_MASK 0x8000u
#define psoc_I2C_IRQ__INTC_NUMBER 15u
#define psoc_I2C_IRQ__INTC_PRIOR_NUM 7u
#define psoc_I2C_IRQ__INTC_PRIOR_REG CYREG_NVIC_PRI_15
#define psoc_I2C_IRQ__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define psoc_I2C_IRQ__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* psoc_I2C_FF */
#define psoc_I2C_FF__ADR CYREG_I2C_ADR
#define psoc_I2C_FF__CFG CYREG_I2C_CFG
#define psoc_I2C_FF__CLK_DIV1 CYREG_I2C_CLK_DIV1
#define psoc_I2C_FF__CLK_DIV2 CYREG_I2C_CLK_DIV2
#define psoc_I2C_FF__CSR CYREG_I2C_CSR
#define psoc_I2C_FF__D CYREG_I2C_D
#define psoc_I2C_FF__MCSR CYREG_I2C_MCSR
#define psoc_I2C_FF__PM_ACT_CFG CYREG_PM_ACT_CFG5
#define psoc_I2C_FF__PM_ACT_MSK 0x04u
#define psoc_I2C_FF__PM_STBY_CFG CYREG_PM_STBY_CFG5
#define psoc_I2C_FF__PM_STBY_MSK 0x04u
#define psoc_I2C_FF__TMOUT_CFG0 CYREG_I2C_TMOUT_CFG0
#define psoc_I2C_FF__TMOUT_CFG1 CYREG_I2C_TMOUT_CFG1
#define psoc_I2C_FF__TMOUT_CSR CYREG_I2C_TMOUT_CSR
#define psoc_I2C_FF__TMOUT_SR CYREG_I2C_TMOUT_SR
#define psoc_I2C_FF__XCFG CYREG_I2C_XCFG

/* SCL_1 */
#define SCL_1__0__MASK 0x10u
#define SCL_1__0__PC CYREG_PRT12_PC4
#define SCL_1__0__PORT 12u
#define SCL_1__0__SHIFT 4
#define SCL_1__AG CYREG_PRT12_AG
#define SCL_1__BIE CYREG_PRT12_BIE
#define SCL_1__BIT_MASK CYREG_PRT12_BIT_MASK
#define SCL_1__BYP CYREG_PRT12_BYP
#define SCL_1__DM0 CYREG_PRT12_DM0
#define SCL_1__DM1 CYREG_PRT12_DM1
#define SCL_1__DM2 CYREG_PRT12_DM2
#define SCL_1__DR CYREG_PRT12_DR
#define SCL_1__INP_DIS CYREG_PRT12_INP_DIS
#define SCL_1__MASK 0x10u
#define SCL_1__PORT 12u
#define SCL_1__PRT CYREG_PRT12_PRT
#define SCL_1__PRTDSI__DBL_SYNC_IN CYREG_PRT12_DBL_SYNC_IN
#define SCL_1__PRTDSI__OE_SEL0 CYREG_PRT12_OE_SEL0
#define SCL_1__PRTDSI__OE_SEL1 CYREG_PRT12_OE_SEL1
#define SCL_1__PRTDSI__OUT_SEL0 CYREG_PRT12_OUT_SEL0
#define SCL_1__PRTDSI__OUT_SEL1 CYREG_PRT12_OUT_SEL1
#define SCL_1__PRTDSI__SYNC_OUT CYREG_PRT12_SYNC_OUT
#define SCL_1__PS CYREG_PRT12_PS
#define SCL_1__SHIFT 4
#define SCL_1__SIO_CFG CYREG_PRT12_SIO_CFG
#define SCL_1__SIO_DIFF CYREG_PRT12_SIO_DIFF
#define SCL_1__SIO_HYST_EN CYREG_PRT12_SIO_HYST_EN
#define SCL_1__SIO_REG_HIFREQ CYREG_PRT12_SIO_REG_HIFREQ
#define SCL_1__SLW CYREG_PRT12_SLW

/* SDA_1 */
#define SDA_1__0__MASK 0x20u
#define SDA_1__0__PC CYREG_PRT12_PC5
#define SDA_1__0__PORT 12u
#define SDA_1__0__SHIFT 5
#define SDA_1__AG CYREG_PRT12_AG
#define SDA_1__BIE CYREG_PRT12_BIE
#define SDA_1__BIT_MASK CYREG_PRT12_BIT_MASK
#define SDA_1__BYP CYREG_PRT12_BYP
#define SDA_1__DM0 CYREG_PRT12_DM0
#define SDA_1__DM1 CYREG_PRT12_DM1
#define SDA_1__DM2 CYREG_PRT12_DM2
#define SDA_1__DR CYREG_PRT12_DR
#define SDA_1__INP_DIS CYREG_PRT12_INP_DIS
#define SDA_1__MASK 0x20u
#define SDA_1__PORT 12u
#define SDA_1__PRT CYREG_PRT12_PRT
#define SDA_1__PRTDSI__DBL_SYNC_IN CYREG_PRT12_DBL_SYNC_IN
#define SDA_1__PRTDSI__OE_SEL0 CYREG_PRT12_OE_SEL0
#define SDA_1__PRTDSI__OE_SEL1 CYREG_PRT12_OE_SEL1
#define SDA_1__PRTDSI__OUT_SEL0 CYREG_PRT12_OUT_SEL0
#define SDA_1__PRTDSI__OUT_SEL1 CYREG_PRT12_OUT_SEL1
#define SDA_1__PRTDSI__SYNC_OUT CYREG_PRT12_SYNC_OUT
#define SDA_1__PS CYREG_PRT12_PS
#define SDA_1__SHIFT 5
#define SDA_1__SIO_CFG CYREG_PRT12_SIO_CFG
#define SDA_1__SIO_DIFF CYREG_PRT12_SIO_DIFF
#define SDA_1__SIO_HYST_EN CYREG_PRT12_SIO_HYST_EN
#define SDA_1__SIO_REG_HIFREQ CYREG_PRT12_SIO_REG_HIFREQ
#define SDA_1__SLW CYREG_PRT12_SLW

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
#define CYDEV_INTR_RISING 0x00008000u
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
