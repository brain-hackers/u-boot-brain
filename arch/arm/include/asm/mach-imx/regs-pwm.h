/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Freescale i.MX28/6SX/6UL/7D LCDIF Register Definitions
 *
 * Copyright (C) 2020 Takumi Sueda <puhitaku@gmail.com>
 *
 * Based on code from LTIB:
 * Copyright 2008-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 */

#ifndef __IMX_REGS_PWM_H__
#define __IMX_REGS_PWM_H__

#ifndef	__ASSEMBLY__
#include <asm/mach-imx/regs-common.h>

#if defined(CONFIG_MX28)
struct mxs_pwm_regs {
	mxs_reg_32(hw_pwm_ctrl)
	mxs_reg_32(hw_pwm_active0)
	mxs_reg_32(hw_pwm_period0)
	mxs_reg_32(hw_pwm_active1)
	mxs_reg_32(hw_pwm_period1)
	mxs_reg_32(hw_pwm_active2)
	mxs_reg_32(hw_pwm_period2)
	mxs_reg_32(hw_pwm_active3)
	mxs_reg_32(hw_pwm_period3)
	mxs_reg_32(hw_pwm_active4)
	mxs_reg_32(hw_pwm_period4)
	mxs_reg_32(hw_pwm_active5)
	mxs_reg_32(hw_pwm_period5)
	mxs_reg_32(hw_pwm_active6)
	mxs_reg_32(hw_pwm_period6)
	mxs_reg_32(hw_pwm_active7)
	mxs_reg_32(hw_pwm_period7)
	mxs_reg_32(hw_pwm_version)
};
#endif
#endif

#define PWM_CTRL_SFTRST				(1 << 31)
#define PWM_CTRL_CLKGATE			(1 << 30)
#define PWM_CTRL_PWM7_PRESENT			(1 << 29)
#define PWM_CTRL_PWM6_PRESENT			(1 << 28)
#define PWM_CTRL_PWM5_PRESENT			(1 << 27)
#define PWM_CTRL_PWM4_PRESENT			(1 << 26)
#define PWM_CTRL_PWM3_PRESENT			(1 << 25)
#define PWM_CTRL_PWM2_PRESENT			(1 << 24)
#define PWM_CTRL_PWM1_PRESENT			(1 << 23)
#define PWM_CTRL_PWM0_PRESENT			(1 << 22)
#define PWM_CTRL_OUTPUT_CUTOFF_EN		(1 << 9)
#define PWM_CTRL_PWM7_ENABLE			(1 << 7)
#define PWM_CTRL_PWM6_ENABLE			(1 << 6)
#define PWM_CTRL_PWM5_ENABLE			(1 << 5)
#define PWM_CTRL_PWM4_ENABLE			(1 << 4)
#define PWM_CTRL_PWM3_ENABLE			(1 << 3)
#define PWM_CTRL_PWM2_ENABLE			(1 << 2)
#define PWM_CTRL_PWM1_ENABLE			(1 << 1)
#define PWM_CTRL_PWM0_ENABLE			(1 << 0)

#define PWM_ACTIVE0_INACTIVE_MASK		(0xffff << 16)
#define PWM_ACTIVE0_INACTIVE_OFFSET		16
#define PWM_ACTIVE0_ACTIVE_MASK			(0xffff << 0)
#define PWM_ACTIVE0_ACTIVE_OFFSET		0

#define PWM_PERIOD0_HSADC_OUT			(1 << 26)
#define PWM_PERIOD0_HSADC_CLK_SEL		(1 << 25)
#define PWM_PERIOD0_MATT_SEL			(1 << 24)
#define PWM_PERIOD0_MATT			(1 << 23)
#define PWM_PERIOD0_CDIV_MASK			(0x7 << 20)
#define PWM_PERIOD0_CDIV_OFFSET			20
#define PWM_PERIOD0_INACTIVE_STATE_MASK		(0x3 << 18)
#define PWM_PERIOD0_INACTIVE_STATE_OFFSET	18
#define PWM_PERIOD0_ACTIVE_STATE_MASK		(0x3 << 16)
#define PWM_PERIOD0_ACTIVE_STATE_OFFSET		16
#define PWM_PERIOD0_PERIOD_MASK			(0xffff << 0)
#define PWM_PERIOD0_PERIOD_OFFSET		0

#define PWM_ACTIVE1_INACTIVE_MASK		(0xffff << 16)
#define PWM_ACTIVE1_INACTIVE_OFFSET		16
#define PWM_ACTIVE1_ACTIVE_MASK			(0xffff << 0)
#define PWM_ACTIVE1_ACTIVE_OFFSET		0

#define PWM_PERIOD1_HSADC_OUT			(1 << 26)
#define PWM_PERIOD1_HSADC_CLK_SEL		(1 << 25)
#define PWM_PERIOD1_MATT_SEL			(1 << 24)
#define PWM_PERIOD1_MATT			(1 << 23)
#define PWM_PERIOD1_CDIV_MASK			(0x7 << 20)
#define PWM_PERIOD1_CDIV_OFFSET			20
#define PWM_PERIOD1_INACTIVE_STATE_MASK		(0x3 << 18)
#define PWM_PERIOD1_INACTIVE_STATE_OFFSET	18
#define PWM_PERIOD1_ACTIVE_STATE_MASK		(0x3 << 16)
#define PWM_PERIOD1_ACTIVE_STATE_OFFSET		16
#define PWM_PERIOD1_PERIOD_MASK			(0xffff << 0)
#define PWM_PERIOD1_PERIOD_OFFSET		0

#define PWM_ACTIVE2_INACTIVE_MASK		(0xffff << 16)
#define PWM_ACTIVE2_INACTIVE_OFFSET		16
#define PWM_ACTIVE2_ACTIVE_MASK			(0xffff << 0)
#define PWM_ACTIVE2_ACTIVE_OFFSET		0

#define PWM_PERIOD2_HSADC_OUT			(1 << 26)
#define PWM_PERIOD2_HSADC_CLK_SEL		(1 << 25)
#define PWM_PERIOD2_MATT_SEL			(1 << 24)
#define PWM_PERIOD2_MATT			(1 << 23)
#define PWM_PERIOD2_CDIV_MASK			(0x7 << 20)
#define PWM_PERIOD2_CDIV_OFFSET			20
#define PWM_PERIOD2_INACTIVE_STATE_MASK		(0x3 << 18)
#define PWM_PERIOD2_INACTIVE_STATE_OFFSET	18
#define PWM_PERIOD2_ACTIVE_STATE_MASK		(0x3 << 16)
#define PWM_PERIOD2_ACTIVE_STATE_OFFSET		16
#define PWM_PERIOD2_PERIOD_MASK			(0xffff << 0)
#define PWM_PERIOD2_PERIOD_OFFSET		0

#define PWM_ACTIVE3_INACTIVE_MASK		(0xffff << 16)
#define PWM_ACTIVE3_INACTIVE_OFFSET		16
#define PWM_ACTIVE3_ACTIVE_MASK			(0xffff << 0)
#define PWM_ACTIVE3_ACTIVE_OFFSET		0

#define PWM_PERIOD3_HSADC_OUT			(1 << 26)
#define PWM_PERIOD3_HSADC_CLK_SEL		(1 << 25)
#define PWM_PERIOD3_MATT_SEL			(1 << 24)
#define PWM_PERIOD3_MATT			(1 << 23)
#define PWM_PERIOD3_CDIV_MASK			(0x7 << 20)
#define PWM_PERIOD3_CDIV_OFFSET			20
#define PWM_PERIOD3_INACTIVE_STATE_MASK		(0x3 << 18)
#define PWM_PERIOD3_INACTIVE_STATE_OFFSET	18
#define PWM_PERIOD3_ACTIVE_STATE_MASK		(0x3 << 16)
#define PWM_PERIOD3_ACTIVE_STATE_OFFSET		16
#define PWM_PERIOD3_PERIOD_MASK			(0xffff << 0)
#define PWM_PERIOD3_PERIOD_OFFSET		0

#define PWM_ACTIVE4_INACTIVE_MASK		(0xffff << 16)
#define PWM_ACTIVE4_INACTIVE_OFFSET		16
#define PWM_ACTIVE4_ACTIVE_MASK			(0xffff << 0)
#define PWM_ACTIVE4_ACTIVE_OFFSET		0

#define PWM_PERIOD4_HSADC_OUT			(1 << 26)
#define PWM_PERIOD4_HSADC_CLK_SEL		(1 << 25)
#define PWM_PERIOD4_MATT_SEL			(1 << 24)
#define PWM_PERIOD4_MATT			(1 << 23)
#define PWM_PERIOD4_CDIV_MASK			(0x7 << 20)
#define PWM_PERIOD4_CDIV_OFFSET			20
#define PWM_PERIOD4_INACTIVE_STATE_MASK		(0x3 << 18)
#define PWM_PERIOD4_INACTIVE_STATE_OFFSET	18
#define PWM_PERIOD4_ACTIVE_STATE_MASK		(0x3 << 16)
#define PWM_PERIOD4_ACTIVE_STATE_OFFSET		16
#define PWM_PERIOD4_PERIOD_MASK			(0xffff << 0)
#define PWM_PERIOD4_PERIOD_OFFSET		0

#define PWM_ACTIVE5_INACTIVE_MASK		(0xffff << 16)
#define PWM_ACTIVE5_INACTIVE_OFFSET		16
#define PWM_ACTIVE5_ACTIVE_MASK			(0xffff << 0)
#define PWM_ACTIVE5_ACTIVE_OFFSET		0

#define PWM_PERIOD5_HSADC_OUT			(1 << 26)
#define PWM_PERIOD5_HSADC_CLK_SEL		(1 << 25)
#define PWM_PERIOD5_MATT_SEL			(1 << 24)
#define PWM_PERIOD5_MATT			(1 << 23)
#define PWM_PERIOD5_CDIV_MASK			(0x7 << 20)
#define PWM_PERIOD5_CDIV_OFFSET			20
#define PWM_PERIOD5_INACTIVE_STATE_MASK		(0x3 << 18)
#define PWM_PERIOD5_INACTIVE_STATE_OFFSET	18
#define PWM_PERIOD5_ACTIVE_STATE_MASK		(0x3 << 16)
#define PWM_PERIOD5_ACTIVE_STATE_OFFSET		16
#define PWM_PERIOD5_PERIOD_MASK			(0xffff << 0)
#define PWM_PERIOD5_PERIOD_OFFSET		0

#define PWM_ACTIVE6_INACTIVE_MASK		(0xffff << 16)
#define PWM_ACTIVE6_INACTIVE_OFFSET		16
#define PWM_ACTIVE6_ACTIVE_MASK			(0xffff << 0)
#define PWM_ACTIVE6_ACTIVE_OFFSET		0

#define PWM_PERIOD6_HSADC_OUT			(1 << 26)
#define PWM_PERIOD6_HSADC_CLK_SEL		(1 << 25)
#define PWM_PERIOD6_MATT_SEL			(1 << 24)
#define PWM_PERIOD6_MATT			(1 << 23)
#define PWM_PERIOD6_CDIV_MASK			(0x7 << 20)
#define PWM_PERIOD6_CDIV_OFFSET			20
#define PWM_PERIOD6_INACTIVE_STATE_MASK		(0x3 << 18)
#define PWM_PERIOD6_INACTIVE_STATE_OFFSET	18
#define PWM_PERIOD6_ACTIVE_STATE_MASK		(0x3 << 16)
#define PWM_PERIOD6_ACTIVE_STATE_OFFSET		16
#define PWM_PERIOD6_PERIOD_MASK			(0xffff << 0)
#define PWM_PERIOD6_PERIOD_OFFSET		0

#define PWM_ACTIVE7_INACTIVE_MASK		(0xffff << 16)
#define PWM_ACTIVE7_INACTIVE_OFFSET		16
#define PWM_ACTIVE7_ACTIVE_MASK			(0xffff << 0)
#define PWM_ACTIVE7_ACTIVE_OFFSET		0

#define PWM_PERIOD7_HSADC_OUT			(1 << 26)
#define PWM_PERIOD7_HSADC_CLK_SEL		(1 << 25)
#define PWM_PERIOD7_MATT_SEL			(1 << 24)
#define PWM_PERIOD7_MATT			(1 << 23)
#define PWM_PERIOD7_CDIV_MASK			(0x7 << 20)
#define PWM_PERIOD7_CDIV_OFFSET			20
#define PWM_PERIOD7_INACTIVE_STATE_MASK		(0x3 << 18)
#define PWM_PERIOD7_INACTIVE_STATE_OFFSET	18
#define PWM_PERIOD7_ACTIVE_STATE_MASK		(0x3 << 16)
#define PWM_PERIOD7_ACTIVE_STATE_OFFSET		16
#define PWM_PERIOD7_PERIOD_MASK			(0xffff << 0)
#define PWM_PERIOD7_PERIOD_OFFSET		0

#endif /* __IMX_REGS_PWM_H__ */
