#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include <cydevice.h>
#include <cydevice_trm.h>

/* UART_Wind_IntClock */
#define UART_Wind_IntClock__CFG0 CYREG_CLKDIST_DCFG2_CFG0
#define UART_Wind_IntClock__CFG1 CYREG_CLKDIST_DCFG2_CFG1
#define UART_Wind_IntClock__CFG2 CYREG_CLKDIST_DCFG2_CFG2
#define UART_Wind_IntClock__CFG2_SRC_SEL_MASK 0x07u
#define UART_Wind_IntClock__INDEX 0x02u
#define UART_Wind_IntClock__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define UART_Wind_IntClock__PM_ACT_MSK 0x04u
#define UART_Wind_IntClock__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define UART_Wind_IntClock__PM_STBY_MSK 0x04u

/* UART_SBD_IntClock */
#define UART_SBD_IntClock__CFG0 CYREG_CLKDIST_DCFG1_CFG0
#define UART_SBD_IntClock__CFG1 CYREG_CLKDIST_DCFG1_CFG1
#define UART_SBD_IntClock__CFG2 CYREG_CLKDIST_DCFG1_CFG2
#define UART_SBD_IntClock__CFG2_SRC_SEL_MASK 0x07u
#define UART_SBD_IntClock__INDEX 0x01u
#define UART_SBD_IntClock__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define UART_SBD_IntClock__PM_ACT_MSK 0x02u
#define UART_SBD_IntClock__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define UART_SBD_IntClock__PM_STBY_MSK 0x02u

/* UART_Wind_BUART */
#define UART_Wind_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB06_07_ACTL
#define UART_Wind_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_REG CYREG_B0_UDB06_07_ST
#define UART_Wind_BUART_sRX_RxBitCounter_ST__MASK_REG CYREG_B0_UDB06_MSK
#define UART_Wind_BUART_sRX_RxBitCounter_ST__MASK_ST_AUX_CTL_REG CYREG_B0_UDB06_MSK_ACTL
#define UART_Wind_BUART_sRX_RxBitCounter_ST__PER_ST_AUX_CTL_REG CYREG_B0_UDB06_MSK_ACTL
#define UART_Wind_BUART_sRX_RxBitCounter_ST__STATUS_AUX_CTL_REG CYREG_B0_UDB06_ACTL
#define UART_Wind_BUART_sRX_RxBitCounter_ST__STATUS_CNT_REG CYREG_B0_UDB06_ST_CTL
#define UART_Wind_BUART_sRX_RxBitCounter_ST__STATUS_CONTROL_REG CYREG_B0_UDB06_ST_CTL
#define UART_Wind_BUART_sRX_RxBitCounter_ST__STATUS_REG CYREG_B0_UDB06_ST
#define UART_Wind_BUART_sRX_RxBitCounter__16BIT_CONTROL_AUX_CTL_REG CYREG_B0_UDB06_07_ACTL
#define UART_Wind_BUART_sRX_RxBitCounter__16BIT_CONTROL_CONTROL_REG CYREG_B0_UDB06_07_CTL
#define UART_Wind_BUART_sRX_RxBitCounter__16BIT_CONTROL_COUNT_REG CYREG_B0_UDB06_07_CTL
#define UART_Wind_BUART_sRX_RxBitCounter__16BIT_COUNT_CONTROL_REG CYREG_B0_UDB06_07_CTL
#define UART_Wind_BUART_sRX_RxBitCounter__16BIT_COUNT_COUNT_REG CYREG_B0_UDB06_07_CTL
#define UART_Wind_BUART_sRX_RxBitCounter__16BIT_MASK_MASK_REG CYREG_B0_UDB06_07_MSK
#define UART_Wind_BUART_sRX_RxBitCounter__16BIT_MASK_PERIOD_REG CYREG_B0_UDB06_07_MSK
#define UART_Wind_BUART_sRX_RxBitCounter__16BIT_PERIOD_MASK_REG CYREG_B0_UDB06_07_MSK
#define UART_Wind_BUART_sRX_RxBitCounter__16BIT_PERIOD_PERIOD_REG CYREG_B0_UDB06_07_MSK
#define UART_Wind_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG CYREG_B0_UDB06_ACTL
#define UART_Wind_BUART_sRX_RxBitCounter__CONTROL_REG CYREG_B0_UDB06_CTL
#define UART_Wind_BUART_sRX_RxBitCounter__CONTROL_ST_REG CYREG_B0_UDB06_ST_CTL
#define UART_Wind_BUART_sRX_RxBitCounter__COUNT_REG CYREG_B0_UDB06_CTL
#define UART_Wind_BUART_sRX_RxBitCounter__COUNT_ST_REG CYREG_B0_UDB06_ST_CTL
#define UART_Wind_BUART_sRX_RxBitCounter__MASK_CTL_AUX_CTL_REG CYREG_B0_UDB06_MSK_ACTL
#define UART_Wind_BUART_sRX_RxBitCounter__PERIOD_REG CYREG_B0_UDB06_MSK
#define UART_Wind_BUART_sRX_RxBitCounter__PER_CTL_AUX_CTL_REG CYREG_B0_UDB06_MSK_ACTL
#define UART_Wind_BUART_sRX_RxShifter_u0__16BIT_A0_REG CYREG_B1_UDB05_06_A0
#define UART_Wind_BUART_sRX_RxShifter_u0__16BIT_A1_REG CYREG_B1_UDB05_06_A1
#define UART_Wind_BUART_sRX_RxShifter_u0__16BIT_D0_REG CYREG_B1_UDB05_06_D0
#define UART_Wind_BUART_sRX_RxShifter_u0__16BIT_D1_REG CYREG_B1_UDB05_06_D1
#define UART_Wind_BUART_sRX_RxShifter_u0__16BIT_DP_AUX_CTL_REG CYREG_B1_UDB05_06_ACTL
#define UART_Wind_BUART_sRX_RxShifter_u0__16BIT_F0_REG CYREG_B1_UDB05_06_F0
#define UART_Wind_BUART_sRX_RxShifter_u0__16BIT_F1_REG CYREG_B1_UDB05_06_F1
#define UART_Wind_BUART_sRX_RxShifter_u0__A0_A1_REG CYREG_B1_UDB05_A0_A1
#define UART_Wind_BUART_sRX_RxShifter_u0__A0_REG CYREG_B1_UDB05_A0
#define UART_Wind_BUART_sRX_RxShifter_u0__A1_REG CYREG_B1_UDB05_A1
#define UART_Wind_BUART_sRX_RxShifter_u0__D0_D1_REG CYREG_B1_UDB05_D0_D1
#define UART_Wind_BUART_sRX_RxShifter_u0__D0_REG CYREG_B1_UDB05_D0
#define UART_Wind_BUART_sRX_RxShifter_u0__D1_REG CYREG_B1_UDB05_D1
#define UART_Wind_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG CYREG_B1_UDB05_ACTL
#define UART_Wind_BUART_sRX_RxShifter_u0__F0_F1_REG CYREG_B1_UDB05_F0_F1
#define UART_Wind_BUART_sRX_RxShifter_u0__F0_REG CYREG_B1_UDB05_F0
#define UART_Wind_BUART_sRX_RxShifter_u0__F1_REG CYREG_B1_UDB05_F1
#define UART_Wind_BUART_sRX_RxSts__16BIT_STATUS_AUX_CTL_REG CYREG_B1_UDB06_07_ACTL
#define UART_Wind_BUART_sRX_RxSts__16BIT_STATUS_REG CYREG_B1_UDB06_07_ST
#define UART_Wind_BUART_sRX_RxSts__3__MASK 0x08u
#define UART_Wind_BUART_sRX_RxSts__3__POS 3
#define UART_Wind_BUART_sRX_RxSts__4__MASK 0x10u
#define UART_Wind_BUART_sRX_RxSts__4__POS 4
#define UART_Wind_BUART_sRX_RxSts__5__MASK 0x20u
#define UART_Wind_BUART_sRX_RxSts__5__POS 5
#define UART_Wind_BUART_sRX_RxSts__MASK 0x38u
#define UART_Wind_BUART_sRX_RxSts__MASK_REG CYREG_B1_UDB06_MSK
#define UART_Wind_BUART_sRX_RxSts__STATUS_AUX_CTL_REG CYREG_B1_UDB06_ACTL
#define UART_Wind_BUART_sRX_RxSts__STATUS_REG CYREG_B1_UDB06_ST
#define UART_Wind_BUART_sTX_TxShifter_u0__16BIT_A0_REG CYREG_B0_UDB02_03_A0
#define UART_Wind_BUART_sTX_TxShifter_u0__16BIT_A1_REG CYREG_B0_UDB02_03_A1
#define UART_Wind_BUART_sTX_TxShifter_u0__16BIT_D0_REG CYREG_B0_UDB02_03_D0
#define UART_Wind_BUART_sTX_TxShifter_u0__16BIT_D1_REG CYREG_B0_UDB02_03_D1
#define UART_Wind_BUART_sTX_TxShifter_u0__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB02_03_ACTL
#define UART_Wind_BUART_sTX_TxShifter_u0__16BIT_F0_REG CYREG_B0_UDB02_03_F0
#define UART_Wind_BUART_sTX_TxShifter_u0__16BIT_F1_REG CYREG_B0_UDB02_03_F1
#define UART_Wind_BUART_sTX_TxShifter_u0__A0_A1_REG CYREG_B0_UDB02_A0_A1
#define UART_Wind_BUART_sTX_TxShifter_u0__A0_REG CYREG_B0_UDB02_A0
#define UART_Wind_BUART_sTX_TxShifter_u0__A1_REG CYREG_B0_UDB02_A1
#define UART_Wind_BUART_sTX_TxShifter_u0__D0_D1_REG CYREG_B0_UDB02_D0_D1
#define UART_Wind_BUART_sTX_TxShifter_u0__D0_REG CYREG_B0_UDB02_D0
#define UART_Wind_BUART_sTX_TxShifter_u0__D1_REG CYREG_B0_UDB02_D1
#define UART_Wind_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG CYREG_B0_UDB02_ACTL
#define UART_Wind_BUART_sTX_TxShifter_u0__F0_F1_REG CYREG_B0_UDB02_F0_F1
#define UART_Wind_BUART_sTX_TxShifter_u0__F0_REG CYREG_B0_UDB02_F0
#define UART_Wind_BUART_sTX_TxShifter_u0__F1_REG CYREG_B0_UDB02_F1
#define UART_Wind_BUART_sTX_TxShifter_u0__MSK_DP_AUX_CTL_REG CYREG_B0_UDB02_MSK_ACTL
#define UART_Wind_BUART_sTX_TxShifter_u0__PER_DP_AUX_CTL_REG CYREG_B0_UDB02_MSK_ACTL
#define UART_Wind_BUART_sTX_TxSts__0__MASK 0x01u
#define UART_Wind_BUART_sTX_TxSts__0__POS 0
#define UART_Wind_BUART_sTX_TxSts__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB05_06_ACTL
#define UART_Wind_BUART_sTX_TxSts__16BIT_STATUS_REG CYREG_B0_UDB05_06_ST
#define UART_Wind_BUART_sTX_TxSts__1__MASK 0x02u
#define UART_Wind_BUART_sTX_TxSts__1__POS 1
#define UART_Wind_BUART_sTX_TxSts__2__MASK 0x04u
#define UART_Wind_BUART_sTX_TxSts__2__POS 2
#define UART_Wind_BUART_sTX_TxSts__3__MASK 0x08u
#define UART_Wind_BUART_sTX_TxSts__3__POS 3
#define UART_Wind_BUART_sTX_TxSts__MASK 0x0Fu
#define UART_Wind_BUART_sTX_TxSts__MASK_REG CYREG_B0_UDB05_MSK
#define UART_Wind_BUART_sTX_TxSts__STATUS_AUX_CTL_REG CYREG_B0_UDB05_ACTL
#define UART_Wind_BUART_sTX_TxSts__STATUS_REG CYREG_B0_UDB05_ST
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A0_REG CYREG_B0_UDB03_04_A0
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A1_REG CYREG_B0_UDB03_04_A1
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D0_REG CYREG_B0_UDB03_04_D0
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D1_REG CYREG_B0_UDB03_04_D1
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB03_04_ACTL
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F0_REG CYREG_B0_UDB03_04_F0
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F1_REG CYREG_B0_UDB03_04_F1
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__A0_A1_REG CYREG_B0_UDB03_A0_A1
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__A0_REG CYREG_B0_UDB03_A0
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__A1_REG CYREG_B0_UDB03_A1
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__D0_D1_REG CYREG_B0_UDB03_D0_D1
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG CYREG_B0_UDB03_D0
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG CYREG_B0_UDB03_D1
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__DP_AUX_CTL_REG CYREG_B0_UDB03_ACTL
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__F0_F1_REG CYREG_B0_UDB03_F0_F1
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__F0_REG CYREG_B0_UDB03_F0
#define UART_Wind_BUART_sTX_sCLOCK_TxBitClkGen__F1_REG CYREG_B0_UDB03_F1

/* UART_SBD_BUART */
#define UART_SBD_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_AUX_CTL_REG CYREG_B1_UDB07_08_ACTL
#define UART_SBD_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_REG CYREG_B1_UDB07_08_ST
#define UART_SBD_BUART_sRX_RxBitCounter_ST__MASK_REG CYREG_B1_UDB07_MSK
#define UART_SBD_BUART_sRX_RxBitCounter_ST__MASK_ST_AUX_CTL_REG CYREG_B1_UDB07_MSK_ACTL
#define UART_SBD_BUART_sRX_RxBitCounter_ST__PER_ST_AUX_CTL_REG CYREG_B1_UDB07_MSK_ACTL
#define UART_SBD_BUART_sRX_RxBitCounter_ST__STATUS_AUX_CTL_REG CYREG_B1_UDB07_ACTL
#define UART_SBD_BUART_sRX_RxBitCounter_ST__STATUS_CNT_REG CYREG_B1_UDB07_ST_CTL
#define UART_SBD_BUART_sRX_RxBitCounter_ST__STATUS_CONTROL_REG CYREG_B1_UDB07_ST_CTL
#define UART_SBD_BUART_sRX_RxBitCounter_ST__STATUS_REG CYREG_B1_UDB07_ST
#define UART_SBD_BUART_sRX_RxBitCounter__16BIT_CONTROL_AUX_CTL_REG CYREG_B1_UDB07_08_ACTL
#define UART_SBD_BUART_sRX_RxBitCounter__16BIT_CONTROL_CONTROL_REG CYREG_B1_UDB07_08_CTL
#define UART_SBD_BUART_sRX_RxBitCounter__16BIT_CONTROL_COUNT_REG CYREG_B1_UDB07_08_CTL
#define UART_SBD_BUART_sRX_RxBitCounter__16BIT_COUNT_CONTROL_REG CYREG_B1_UDB07_08_CTL
#define UART_SBD_BUART_sRX_RxBitCounter__16BIT_COUNT_COUNT_REG CYREG_B1_UDB07_08_CTL
#define UART_SBD_BUART_sRX_RxBitCounter__16BIT_MASK_MASK_REG CYREG_B1_UDB07_08_MSK
#define UART_SBD_BUART_sRX_RxBitCounter__16BIT_MASK_PERIOD_REG CYREG_B1_UDB07_08_MSK
#define UART_SBD_BUART_sRX_RxBitCounter__16BIT_PERIOD_MASK_REG CYREG_B1_UDB07_08_MSK
#define UART_SBD_BUART_sRX_RxBitCounter__16BIT_PERIOD_PERIOD_REG CYREG_B1_UDB07_08_MSK
#define UART_SBD_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG CYREG_B1_UDB07_ACTL
#define UART_SBD_BUART_sRX_RxBitCounter__CONTROL_REG CYREG_B1_UDB07_CTL
#define UART_SBD_BUART_sRX_RxBitCounter__CONTROL_ST_REG CYREG_B1_UDB07_ST_CTL
#define UART_SBD_BUART_sRX_RxBitCounter__COUNT_REG CYREG_B1_UDB07_CTL
#define UART_SBD_BUART_sRX_RxBitCounter__COUNT_ST_REG CYREG_B1_UDB07_ST_CTL
#define UART_SBD_BUART_sRX_RxBitCounter__MASK_CTL_AUX_CTL_REG CYREG_B1_UDB07_MSK_ACTL
#define UART_SBD_BUART_sRX_RxBitCounter__PERIOD_REG CYREG_B1_UDB07_MSK
#define UART_SBD_BUART_sRX_RxBitCounter__PER_CTL_AUX_CTL_REG CYREG_B1_UDB07_MSK_ACTL
#define UART_SBD_BUART_sRX_RxShifter_u0__16BIT_A0_REG CYREG_B1_UDB04_05_A0
#define UART_SBD_BUART_sRX_RxShifter_u0__16BIT_A1_REG CYREG_B1_UDB04_05_A1
#define UART_SBD_BUART_sRX_RxShifter_u0__16BIT_D0_REG CYREG_B1_UDB04_05_D0
#define UART_SBD_BUART_sRX_RxShifter_u0__16BIT_D1_REG CYREG_B1_UDB04_05_D1
#define UART_SBD_BUART_sRX_RxShifter_u0__16BIT_DP_AUX_CTL_REG CYREG_B1_UDB04_05_ACTL
#define UART_SBD_BUART_sRX_RxShifter_u0__16BIT_F0_REG CYREG_B1_UDB04_05_F0
#define UART_SBD_BUART_sRX_RxShifter_u0__16BIT_F1_REG CYREG_B1_UDB04_05_F1
#define UART_SBD_BUART_sRX_RxShifter_u0__A0_A1_REG CYREG_B1_UDB04_A0_A1
#define UART_SBD_BUART_sRX_RxShifter_u0__A0_REG CYREG_B1_UDB04_A0
#define UART_SBD_BUART_sRX_RxShifter_u0__A1_REG CYREG_B1_UDB04_A1
#define UART_SBD_BUART_sRX_RxShifter_u0__D0_D1_REG CYREG_B1_UDB04_D0_D1
#define UART_SBD_BUART_sRX_RxShifter_u0__D0_REG CYREG_B1_UDB04_D0
#define UART_SBD_BUART_sRX_RxShifter_u0__D1_REG CYREG_B1_UDB04_D1
#define UART_SBD_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG CYREG_B1_UDB04_ACTL
#define UART_SBD_BUART_sRX_RxShifter_u0__F0_F1_REG CYREG_B1_UDB04_F0_F1
#define UART_SBD_BUART_sRX_RxShifter_u0__F0_REG CYREG_B1_UDB04_F0
#define UART_SBD_BUART_sRX_RxShifter_u0__F1_REG CYREG_B1_UDB04_F1
#define UART_SBD_BUART_sRX_RxSts__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB04_05_ACTL
#define UART_SBD_BUART_sRX_RxSts__16BIT_STATUS_REG CYREG_B0_UDB04_05_ST
#define UART_SBD_BUART_sRX_RxSts__3__MASK 0x08u
#define UART_SBD_BUART_sRX_RxSts__3__POS 3
#define UART_SBD_BUART_sRX_RxSts__4__MASK 0x10u
#define UART_SBD_BUART_sRX_RxSts__4__POS 4
#define UART_SBD_BUART_sRX_RxSts__5__MASK 0x20u
#define UART_SBD_BUART_sRX_RxSts__5__POS 5
#define UART_SBD_BUART_sRX_RxSts__MASK 0x38u
#define UART_SBD_BUART_sRX_RxSts__MASK_REG CYREG_B0_UDB04_MSK
#define UART_SBD_BUART_sRX_RxSts__STATUS_AUX_CTL_REG CYREG_B0_UDB04_ACTL
#define UART_SBD_BUART_sRX_RxSts__STATUS_REG CYREG_B0_UDB04_ST
#define UART_SBD_BUART_sTX_TxShifter_u0__16BIT_A0_REG CYREG_B0_UDB06_07_A0
#define UART_SBD_BUART_sTX_TxShifter_u0__16BIT_A1_REG CYREG_B0_UDB06_07_A1
#define UART_SBD_BUART_sTX_TxShifter_u0__16BIT_D0_REG CYREG_B0_UDB06_07_D0
#define UART_SBD_BUART_sTX_TxShifter_u0__16BIT_D1_REG CYREG_B0_UDB06_07_D1
#define UART_SBD_BUART_sTX_TxShifter_u0__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB06_07_ACTL
#define UART_SBD_BUART_sTX_TxShifter_u0__16BIT_F0_REG CYREG_B0_UDB06_07_F0
#define UART_SBD_BUART_sTX_TxShifter_u0__16BIT_F1_REG CYREG_B0_UDB06_07_F1
#define UART_SBD_BUART_sTX_TxShifter_u0__A0_A1_REG CYREG_B0_UDB06_A0_A1
#define UART_SBD_BUART_sTX_TxShifter_u0__A0_REG CYREG_B0_UDB06_A0
#define UART_SBD_BUART_sTX_TxShifter_u0__A1_REG CYREG_B0_UDB06_A1
#define UART_SBD_BUART_sTX_TxShifter_u0__D0_D1_REG CYREG_B0_UDB06_D0_D1
#define UART_SBD_BUART_sTX_TxShifter_u0__D0_REG CYREG_B0_UDB06_D0
#define UART_SBD_BUART_sTX_TxShifter_u0__D1_REG CYREG_B0_UDB06_D1
#define UART_SBD_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG CYREG_B0_UDB06_ACTL
#define UART_SBD_BUART_sTX_TxShifter_u0__F0_F1_REG CYREG_B0_UDB06_F0_F1
#define UART_SBD_BUART_sTX_TxShifter_u0__F0_REG CYREG_B0_UDB06_F0
#define UART_SBD_BUART_sTX_TxShifter_u0__F1_REG CYREG_B0_UDB06_F1
#define UART_SBD_BUART_sTX_TxShifter_u0__MSK_DP_AUX_CTL_REG CYREG_B0_UDB06_MSK_ACTL
#define UART_SBD_BUART_sTX_TxShifter_u0__PER_DP_AUX_CTL_REG CYREG_B0_UDB06_MSK_ACTL
#define UART_SBD_BUART_sTX_TxSts__0__MASK 0x01u
#define UART_SBD_BUART_sTX_TxSts__0__POS 0
#define UART_SBD_BUART_sTX_TxSts__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB07_08_ACTL
#define UART_SBD_BUART_sTX_TxSts__16BIT_STATUS_REG CYREG_B0_UDB07_08_ST
#define UART_SBD_BUART_sTX_TxSts__1__MASK 0x02u
#define UART_SBD_BUART_sTX_TxSts__1__POS 1
#define UART_SBD_BUART_sTX_TxSts__2__MASK 0x04u
#define UART_SBD_BUART_sTX_TxSts__2__POS 2
#define UART_SBD_BUART_sTX_TxSts__3__MASK 0x08u
#define UART_SBD_BUART_sTX_TxSts__3__POS 3
#define UART_SBD_BUART_sTX_TxSts__MASK 0x0Fu
#define UART_SBD_BUART_sTX_TxSts__MASK_REG CYREG_B0_UDB07_MSK
#define UART_SBD_BUART_sTX_TxSts__STATUS_AUX_CTL_REG CYREG_B0_UDB07_ACTL
#define UART_SBD_BUART_sTX_TxSts__STATUS_REG CYREG_B0_UDB07_ST
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A0_REG CYREG_B0_UDB07_08_A0
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A1_REG CYREG_B0_UDB07_08_A1
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D0_REG CYREG_B0_UDB07_08_D0
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D1_REG CYREG_B0_UDB07_08_D1
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB07_08_ACTL
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F0_REG CYREG_B0_UDB07_08_F0
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F1_REG CYREG_B0_UDB07_08_F1
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__A0_A1_REG CYREG_B0_UDB07_A0_A1
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__A0_REG CYREG_B0_UDB07_A0
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__A1_REG CYREG_B0_UDB07_A1
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__D0_D1_REG CYREG_B0_UDB07_D0_D1
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG CYREG_B0_UDB07_D0
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG CYREG_B0_UDB07_D1
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__DP_AUX_CTL_REG CYREG_B0_UDB07_ACTL
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__F0_F1_REG CYREG_B0_UDB07_F0_F1
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__F0_REG CYREG_B0_UDB07_F0
#define UART_SBD_BUART_sTX_sCLOCK_TxBitClkGen__F1_REG CYREG_B0_UDB07_F1

/* master_BSPIM */
#define master_BSPIM_BitCounter_ST__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB02_03_ACTL
#define master_BSPIM_BitCounter_ST__16BIT_STATUS_REG CYREG_B0_UDB02_03_ST
#define master_BSPIM_BitCounter_ST__MASK_REG CYREG_B0_UDB02_MSK
#define master_BSPIM_BitCounter_ST__MASK_ST_AUX_CTL_REG CYREG_B0_UDB02_MSK_ACTL
#define master_BSPIM_BitCounter_ST__PER_ST_AUX_CTL_REG CYREG_B0_UDB02_MSK_ACTL
#define master_BSPIM_BitCounter_ST__STATUS_AUX_CTL_REG CYREG_B0_UDB02_ACTL
#define master_BSPIM_BitCounter_ST__STATUS_CNT_REG CYREG_B0_UDB02_ST_CTL
#define master_BSPIM_BitCounter_ST__STATUS_CONTROL_REG CYREG_B0_UDB02_ST_CTL
#define master_BSPIM_BitCounter_ST__STATUS_REG CYREG_B0_UDB02_ST
#define master_BSPIM_BitCounter__16BIT_CONTROL_AUX_CTL_REG CYREG_B0_UDB02_03_ACTL
#define master_BSPIM_BitCounter__16BIT_CONTROL_CONTROL_REG CYREG_B0_UDB02_03_CTL
#define master_BSPIM_BitCounter__16BIT_CONTROL_COUNT_REG CYREG_B0_UDB02_03_CTL
#define master_BSPIM_BitCounter__16BIT_COUNT_CONTROL_REG CYREG_B0_UDB02_03_CTL
#define master_BSPIM_BitCounter__16BIT_COUNT_COUNT_REG CYREG_B0_UDB02_03_CTL
#define master_BSPIM_BitCounter__16BIT_MASK_MASK_REG CYREG_B0_UDB02_03_MSK
#define master_BSPIM_BitCounter__16BIT_MASK_PERIOD_REG CYREG_B0_UDB02_03_MSK
#define master_BSPIM_BitCounter__16BIT_PERIOD_MASK_REG CYREG_B0_UDB02_03_MSK
#define master_BSPIM_BitCounter__16BIT_PERIOD_PERIOD_REG CYREG_B0_UDB02_03_MSK
#define master_BSPIM_BitCounter__CONTROL_AUX_CTL_REG CYREG_B0_UDB02_ACTL
#define master_BSPIM_BitCounter__CONTROL_REG CYREG_B0_UDB02_CTL
#define master_BSPIM_BitCounter__CONTROL_ST_REG CYREG_B0_UDB02_ST_CTL
#define master_BSPIM_BitCounter__COUNT_REG CYREG_B0_UDB02_CTL
#define master_BSPIM_BitCounter__COUNT_ST_REG CYREG_B0_UDB02_ST_CTL
#define master_BSPIM_BitCounter__MASK_CTL_AUX_CTL_REG CYREG_B0_UDB02_MSK_ACTL
#define master_BSPIM_BitCounter__PERIOD_REG CYREG_B0_UDB02_MSK
#define master_BSPIM_BitCounter__PER_CTL_AUX_CTL_REG CYREG_B0_UDB02_MSK_ACTL
#define master_BSPIM_RxStsReg__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB03_04_ACTL
#define master_BSPIM_RxStsReg__16BIT_STATUS_REG CYREG_B0_UDB03_04_ST
#define master_BSPIM_RxStsReg__4__MASK 0x10u
#define master_BSPIM_RxStsReg__4__POS 4
#define master_BSPIM_RxStsReg__5__MASK 0x20u
#define master_BSPIM_RxStsReg__5__POS 5
#define master_BSPIM_RxStsReg__6__MASK 0x40u
#define master_BSPIM_RxStsReg__6__POS 6
#define master_BSPIM_RxStsReg__MASK 0x70u
#define master_BSPIM_RxStsReg__MASK_REG CYREG_B0_UDB03_MSK
#define master_BSPIM_RxStsReg__STATUS_AUX_CTL_REG CYREG_B0_UDB03_ACTL
#define master_BSPIM_RxStsReg__STATUS_REG CYREG_B0_UDB03_ST
#define master_BSPIM_TxStsReg__0__MASK 0x01u
#define master_BSPIM_TxStsReg__0__POS 0
#define master_BSPIM_TxStsReg__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB00_01_ACTL
#define master_BSPIM_TxStsReg__16BIT_STATUS_REG CYREG_B0_UDB00_01_ST
#define master_BSPIM_TxStsReg__1__MASK 0x02u
#define master_BSPIM_TxStsReg__1__POS 1
#define master_BSPIM_TxStsReg__2__MASK 0x04u
#define master_BSPIM_TxStsReg__2__POS 2
#define master_BSPIM_TxStsReg__3__MASK 0x08u
#define master_BSPIM_TxStsReg__3__POS 3
#define master_BSPIM_TxStsReg__4__MASK 0x10u
#define master_BSPIM_TxStsReg__4__POS 4
#define master_BSPIM_TxStsReg__MASK 0x1Fu
#define master_BSPIM_TxStsReg__MASK_REG CYREG_B0_UDB00_MSK
#define master_BSPIM_TxStsReg__STATUS_AUX_CTL_REG CYREG_B0_UDB00_ACTL
#define master_BSPIM_TxStsReg__STATUS_REG CYREG_B0_UDB00_ST
#define master_BSPIM_sR16_Dp_u0__16BIT_A0_REG CYREG_B0_UDB00_01_A0
#define master_BSPIM_sR16_Dp_u0__16BIT_A1_REG CYREG_B0_UDB00_01_A1
#define master_BSPIM_sR16_Dp_u0__16BIT_D0_REG CYREG_B0_UDB00_01_D0
#define master_BSPIM_sR16_Dp_u0__16BIT_D1_REG CYREG_B0_UDB00_01_D1
#define master_BSPIM_sR16_Dp_u0__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB00_01_ACTL
#define master_BSPIM_sR16_Dp_u0__16BIT_F0_REG CYREG_B0_UDB00_01_F0
#define master_BSPIM_sR16_Dp_u0__16BIT_F1_REG CYREG_B0_UDB00_01_F1
#define master_BSPIM_sR16_Dp_u0__A0_A1_REG CYREG_B0_UDB00_A0_A1
#define master_BSPIM_sR16_Dp_u0__A0_REG CYREG_B0_UDB00_A0
#define master_BSPIM_sR16_Dp_u0__A1_REG CYREG_B0_UDB00_A1
#define master_BSPIM_sR16_Dp_u0__D0_D1_REG CYREG_B0_UDB00_D0_D1
#define master_BSPIM_sR16_Dp_u0__D0_REG CYREG_B0_UDB00_D0
#define master_BSPIM_sR16_Dp_u0__D1_REG CYREG_B0_UDB00_D1
#define master_BSPIM_sR16_Dp_u0__DP_AUX_CTL_REG CYREG_B0_UDB00_ACTL
#define master_BSPIM_sR16_Dp_u0__F0_F1_REG CYREG_B0_UDB00_F0_F1
#define master_BSPIM_sR16_Dp_u0__F0_REG CYREG_B0_UDB00_F0
#define master_BSPIM_sR16_Dp_u0__F1_REG CYREG_B0_UDB00_F1
#define master_BSPIM_sR16_Dp_u1__16BIT_A0_REG CYREG_B0_UDB01_02_A0
#define master_BSPIM_sR16_Dp_u1__16BIT_A1_REG CYREG_B0_UDB01_02_A1
#define master_BSPIM_sR16_Dp_u1__16BIT_D0_REG CYREG_B0_UDB01_02_D0
#define master_BSPIM_sR16_Dp_u1__16BIT_D1_REG CYREG_B0_UDB01_02_D1
#define master_BSPIM_sR16_Dp_u1__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB01_02_ACTL
#define master_BSPIM_sR16_Dp_u1__16BIT_F0_REG CYREG_B0_UDB01_02_F0
#define master_BSPIM_sR16_Dp_u1__16BIT_F1_REG CYREG_B0_UDB01_02_F1
#define master_BSPIM_sR16_Dp_u1__A0_A1_REG CYREG_B0_UDB01_A0_A1
#define master_BSPIM_sR16_Dp_u1__A0_REG CYREG_B0_UDB01_A0
#define master_BSPIM_sR16_Dp_u1__A1_REG CYREG_B0_UDB01_A1
#define master_BSPIM_sR16_Dp_u1__D0_D1_REG CYREG_B0_UDB01_D0_D1
#define master_BSPIM_sR16_Dp_u1__D0_REG CYREG_B0_UDB01_D0
#define master_BSPIM_sR16_Dp_u1__D1_REG CYREG_B0_UDB01_D1
#define master_BSPIM_sR16_Dp_u1__DP_AUX_CTL_REG CYREG_B0_UDB01_ACTL
#define master_BSPIM_sR16_Dp_u1__F0_F1_REG CYREG_B0_UDB01_F0_F1
#define master_BSPIM_sR16_Dp_u1__F0_REG CYREG_B0_UDB01_F0
#define master_BSPIM_sR16_Dp_u1__F1_REG CYREG_B0_UDB01_F1

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

/* SBD_reply */
#define SBD_reply__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define SBD_reply__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define SBD_reply__INTC_MASK 0x01u
#define SBD_reply__INTC_NUMBER 0u
#define SBD_reply__INTC_PRIOR_NUM 1u
#define SBD_reply__INTC_PRIOR_REG CYREG_NVIC_PRI_0
#define SBD_reply__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define SBD_reply__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* selectPin */
#define selectPin__0__MASK 0x08u
#define selectPin__0__PC CYREG_PRT12_PC3
#define selectPin__0__PORT 12u
#define selectPin__0__SHIFT 3
#define selectPin__AG CYREG_PRT12_AG
#define selectPin__BIE CYREG_PRT12_BIE
#define selectPin__BIT_MASK CYREG_PRT12_BIT_MASK
#define selectPin__BYP CYREG_PRT12_BYP
#define selectPin__DM0 CYREG_PRT12_DM0
#define selectPin__DM1 CYREG_PRT12_DM1
#define selectPin__DM2 CYREG_PRT12_DM2
#define selectPin__DR CYREG_PRT12_DR
#define selectPin__INP_DIS CYREG_PRT12_INP_DIS
#define selectPin__MASK 0x08u
#define selectPin__PORT 12u
#define selectPin__PRT CYREG_PRT12_PRT
#define selectPin__PRTDSI__DBL_SYNC_IN CYREG_PRT12_DBL_SYNC_IN
#define selectPin__PRTDSI__OE_SEL0 CYREG_PRT12_OE_SEL0
#define selectPin__PRTDSI__OE_SEL1 CYREG_PRT12_OE_SEL1
#define selectPin__PRTDSI__OUT_SEL0 CYREG_PRT12_OUT_SEL0
#define selectPin__PRTDSI__OUT_SEL1 CYREG_PRT12_OUT_SEL1
#define selectPin__PRTDSI__SYNC_OUT CYREG_PRT12_SYNC_OUT
#define selectPin__PS CYREG_PRT12_PS
#define selectPin__SHIFT 3
#define selectPin__SIO_CFG CYREG_PRT12_SIO_CFG
#define selectPin__SIO_DIFF CYREG_PRT12_SIO_DIFF
#define selectPin__SIO_HYST_EN CYREG_PRT12_SIO_HYST_EN
#define selectPin__SIO_REG_HIFREQ CYREG_PRT12_SIO_REG_HIFREQ
#define selectPin__SLW CYREG_PRT12_SLW

/* clockPin */
#define clockPin__0__MASK 0x10u
#define clockPin__0__PC CYREG_PRT0_PC4
#define clockPin__0__PORT 0u
#define clockPin__0__SHIFT 4
#define clockPin__AG CYREG_PRT0_AG
#define clockPin__AMUX CYREG_PRT0_AMUX
#define clockPin__BIE CYREG_PRT0_BIE
#define clockPin__BIT_MASK CYREG_PRT0_BIT_MASK
#define clockPin__BYP CYREG_PRT0_BYP
#define clockPin__CTL CYREG_PRT0_CTL
#define clockPin__DM0 CYREG_PRT0_DM0
#define clockPin__DM1 CYREG_PRT0_DM1
#define clockPin__DM2 CYREG_PRT0_DM2
#define clockPin__DR CYREG_PRT0_DR
#define clockPin__INP_DIS CYREG_PRT0_INP_DIS
#define clockPin__LCD_COM_SEG CYREG_PRT0_LCD_COM_SEG
#define clockPin__LCD_EN CYREG_PRT0_LCD_EN
#define clockPin__MASK 0x10u
#define clockPin__PORT 0u
#define clockPin__PRT CYREG_PRT0_PRT
#define clockPin__PRTDSI__CAPS_SEL CYREG_PRT0_CAPS_SEL
#define clockPin__PRTDSI__DBL_SYNC_IN CYREG_PRT0_DBL_SYNC_IN
#define clockPin__PRTDSI__OE_SEL0 CYREG_PRT0_OE_SEL0
#define clockPin__PRTDSI__OE_SEL1 CYREG_PRT0_OE_SEL1
#define clockPin__PRTDSI__OUT_SEL0 CYREG_PRT0_OUT_SEL0
#define clockPin__PRTDSI__OUT_SEL1 CYREG_PRT0_OUT_SEL1
#define clockPin__PRTDSI__SYNC_OUT CYREG_PRT0_SYNC_OUT
#define clockPin__PS CYREG_PRT0_PS
#define clockPin__SHIFT 4
#define clockPin__SLW CYREG_PRT0_SLW

/* isr_Wind */
#define isr_Wind__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define isr_Wind__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define isr_Wind__INTC_MASK 0x02u
#define isr_Wind__INTC_NUMBER 1u
#define isr_Wind__INTC_PRIOR_NUM 0u
#define isr_Wind__INTC_PRIOR_REG CYREG_NVIC_PRI_1
#define isr_Wind__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define isr_Wind__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* dataPin */
#define dataPin__0__MASK 0x40u
#define dataPin__0__PC CYREG_PRT4_PC6
#define dataPin__0__PORT 4u
#define dataPin__0__SHIFT 6
#define dataPin__AG CYREG_PRT4_AG
#define dataPin__AMUX CYREG_PRT4_AMUX
#define dataPin__BIE CYREG_PRT4_BIE
#define dataPin__BIT_MASK CYREG_PRT4_BIT_MASK
#define dataPin__BYP CYREG_PRT4_BYP
#define dataPin__CTL CYREG_PRT4_CTL
#define dataPin__DM0 CYREG_PRT4_DM0
#define dataPin__DM1 CYREG_PRT4_DM1
#define dataPin__DM2 CYREG_PRT4_DM2
#define dataPin__DR CYREG_PRT4_DR
#define dataPin__INP_DIS CYREG_PRT4_INP_DIS
#define dataPin__LCD_COM_SEG CYREG_PRT4_LCD_COM_SEG
#define dataPin__LCD_EN CYREG_PRT4_LCD_EN
#define dataPin__MASK 0x40u
#define dataPin__PORT 4u
#define dataPin__PRT CYREG_PRT4_PRT
#define dataPin__PRTDSI__CAPS_SEL CYREG_PRT4_CAPS_SEL
#define dataPin__PRTDSI__DBL_SYNC_IN CYREG_PRT4_DBL_SYNC_IN
#define dataPin__PRTDSI__OE_SEL0 CYREG_PRT4_OE_SEL0
#define dataPin__PRTDSI__OE_SEL1 CYREG_PRT4_OE_SEL1
#define dataPin__PRTDSI__OUT_SEL0 CYREG_PRT4_OUT_SEL0
#define dataPin__PRTDSI__OUT_SEL1 CYREG_PRT4_OUT_SEL1
#define dataPin__PRTDSI__SYNC_OUT CYREG_PRT4_SYNC_OUT
#define dataPin__PS CYREG_PRT4_PS
#define dataPin__SHIFT 6
#define dataPin__SLW CYREG_PRT4_SLW

/* Wind_Rx */
#define Wind_Rx__0__MASK 0x01u
#define Wind_Rx__0__PC CYREG_PRT3_PC0
#define Wind_Rx__0__PORT 3u
#define Wind_Rx__0__SHIFT 0
#define Wind_Rx__AG CYREG_PRT3_AG
#define Wind_Rx__AMUX CYREG_PRT3_AMUX
#define Wind_Rx__BIE CYREG_PRT3_BIE
#define Wind_Rx__BIT_MASK CYREG_PRT3_BIT_MASK
#define Wind_Rx__BYP CYREG_PRT3_BYP
#define Wind_Rx__CTL CYREG_PRT3_CTL
#define Wind_Rx__DM0 CYREG_PRT3_DM0
#define Wind_Rx__DM1 CYREG_PRT3_DM1
#define Wind_Rx__DM2 CYREG_PRT3_DM2
#define Wind_Rx__DR CYREG_PRT3_DR
#define Wind_Rx__INP_DIS CYREG_PRT3_INP_DIS
#define Wind_Rx__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define Wind_Rx__LCD_EN CYREG_PRT3_LCD_EN
#define Wind_Rx__MASK 0x01u
#define Wind_Rx__PORT 3u
#define Wind_Rx__PRT CYREG_PRT3_PRT
#define Wind_Rx__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define Wind_Rx__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define Wind_Rx__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define Wind_Rx__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define Wind_Rx__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define Wind_Rx__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define Wind_Rx__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define Wind_Rx__PS CYREG_PRT3_PS
#define Wind_Rx__SHIFT 0
#define Wind_Rx__SLW CYREG_PRT3_SLW

/* Wind_Tx */
#define Wind_Tx__0__MASK 0x02u
#define Wind_Tx__0__PC CYREG_PRT3_PC1
#define Wind_Tx__0__PORT 3u
#define Wind_Tx__0__SHIFT 1
#define Wind_Tx__AG CYREG_PRT3_AG
#define Wind_Tx__AMUX CYREG_PRT3_AMUX
#define Wind_Tx__BIE CYREG_PRT3_BIE
#define Wind_Tx__BIT_MASK CYREG_PRT3_BIT_MASK
#define Wind_Tx__BYP CYREG_PRT3_BYP
#define Wind_Tx__CTL CYREG_PRT3_CTL
#define Wind_Tx__DM0 CYREG_PRT3_DM0
#define Wind_Tx__DM1 CYREG_PRT3_DM1
#define Wind_Tx__DM2 CYREG_PRT3_DM2
#define Wind_Tx__DR CYREG_PRT3_DR
#define Wind_Tx__INP_DIS CYREG_PRT3_INP_DIS
#define Wind_Tx__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define Wind_Tx__LCD_EN CYREG_PRT3_LCD_EN
#define Wind_Tx__MASK 0x02u
#define Wind_Tx__PORT 3u
#define Wind_Tx__PRT CYREG_PRT3_PRT
#define Wind_Tx__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define Wind_Tx__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define Wind_Tx__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define Wind_Tx__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define Wind_Tx__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define Wind_Tx__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define Wind_Tx__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define Wind_Tx__PS CYREG_PRT3_PS
#define Wind_Tx__SHIFT 1
#define Wind_Tx__SLW CYREG_PRT3_SLW

/* SBD_Rx */
#define SBD_Rx__0__MASK 0x80u
#define SBD_Rx__0__PC CYREG_PRT3_PC7
#define SBD_Rx__0__PORT 3u
#define SBD_Rx__0__SHIFT 7
#define SBD_Rx__AG CYREG_PRT3_AG
#define SBD_Rx__AMUX CYREG_PRT3_AMUX
#define SBD_Rx__BIE CYREG_PRT3_BIE
#define SBD_Rx__BIT_MASK CYREG_PRT3_BIT_MASK
#define SBD_Rx__BYP CYREG_PRT3_BYP
#define SBD_Rx__CTL CYREG_PRT3_CTL
#define SBD_Rx__DM0 CYREG_PRT3_DM0
#define SBD_Rx__DM1 CYREG_PRT3_DM1
#define SBD_Rx__DM2 CYREG_PRT3_DM2
#define SBD_Rx__DR CYREG_PRT3_DR
#define SBD_Rx__INP_DIS CYREG_PRT3_INP_DIS
#define SBD_Rx__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define SBD_Rx__LCD_EN CYREG_PRT3_LCD_EN
#define SBD_Rx__MASK 0x80u
#define SBD_Rx__PORT 3u
#define SBD_Rx__PRT CYREG_PRT3_PRT
#define SBD_Rx__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define SBD_Rx__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define SBD_Rx__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define SBD_Rx__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define SBD_Rx__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define SBD_Rx__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define SBD_Rx__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define SBD_Rx__PS CYREG_PRT3_PS
#define SBD_Rx__SHIFT 7
#define SBD_Rx__SLW CYREG_PRT3_SLW

/* SBD_Tx */
#define SBD_Tx__0__MASK 0x40u
#define SBD_Tx__0__PC CYREG_PRT3_PC6
#define SBD_Tx__0__PORT 3u
#define SBD_Tx__0__SHIFT 6
#define SBD_Tx__AG CYREG_PRT3_AG
#define SBD_Tx__AMUX CYREG_PRT3_AMUX
#define SBD_Tx__BIE CYREG_PRT3_BIE
#define SBD_Tx__BIT_MASK CYREG_PRT3_BIT_MASK
#define SBD_Tx__BYP CYREG_PRT3_BYP
#define SBD_Tx__CTL CYREG_PRT3_CTL
#define SBD_Tx__DM0 CYREG_PRT3_DM0
#define SBD_Tx__DM1 CYREG_PRT3_DM1
#define SBD_Tx__DM2 CYREG_PRT3_DM2
#define SBD_Tx__DR CYREG_PRT3_DR
#define SBD_Tx__INP_DIS CYREG_PRT3_INP_DIS
#define SBD_Tx__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define SBD_Tx__LCD_EN CYREG_PRT3_LCD_EN
#define SBD_Tx__MASK 0x40u
#define SBD_Tx__PORT 3u
#define SBD_Tx__PRT CYREG_PRT3_PRT
#define SBD_Tx__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define SBD_Tx__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define SBD_Tx__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define SBD_Tx__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define SBD_Tx__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define SBD_Tx__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define SBD_Tx__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define SBD_Tx__PS CYREG_PRT3_PS
#define SBD_Tx__SHIFT 6
#define SBD_Tx__SLW CYREG_PRT3_SLW

/* clock */
#define clock__CFG0 CYREG_CLKDIST_DCFG0_CFG0
#define clock__CFG1 CYREG_CLKDIST_DCFG0_CFG1
#define clock__CFG2 CYREG_CLKDIST_DCFG0_CFG2
#define clock__CFG2_SRC_SEL_MASK 0x07u
#define clock__INDEX 0x00u
#define clock__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define clock__PM_ACT_MSK 0x01u
#define clock__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define clock__PM_STBY_MSK 0x01u

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
#define CYDEV_INTR_RISING 0x00008003u
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