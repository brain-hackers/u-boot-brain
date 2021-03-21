// SPDX-License-Identifier: GPL-2.0+
/*
 * SHARP PW-SH7
 *
 * (C) Copyright 2020 Takumi Sueda.
 * Author: Takumi Sueda <puhitaku@gmail.com>
 *
 * (C) Copyright 2011 Freescale Semiconductor, Inc.
 * Author: Fabio Estevam <fabio.estevam@freescale.com>
 *
 * Based on m28evk.c:
 * Copyright (C) 2011 Marek Vasut <marek.vasut@gmail.com>
 * on behalf of DENX Software Engineering GmbH
 */

#include <common.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/iomux-mx28.h>
#include <asm/arch/clock.h>
#include <asm/arch/sys_proto.h>
#include <linux/mii.h>
#include <miiphy.h>
#include <netdev.h>
#include <errno.h>

#include "../common/lcd.h"

DECLARE_GLOBAL_DATA_PTR;

/*
 * Functions
 */
int board_early_init_f(void)
{
	/* IO0 clock at 480MHz */
	mxs_set_ioclk(MXC_IOCLK0, 480000);
	/* IO1 clock at 480MHz */
	mxs_set_ioclk(MXC_IOCLK1, 480000);

	/* SSP0 clock at 96MHz */
	mxs_set_sspclk(MXC_SSPCLK0, 96000, 0);
	/* SSP1 clock at 96MHz */
	mxs_set_sspclk(MXC_SSPCLK1, 96000, 0);

#ifdef CONFIG_CMD_USB
	mxs_iomux_setup_pad(MX28_PAD_SSP2_SS1__USB1_OVERCURRENT);
	mxs_iomux_setup_pad(MX28_PAD_AUART2_RX__GPIO_3_8 | MXS_PAD_4MA |
			    MXS_PAD_3V3 | MXS_PAD_NOPULL);
	gpio_direction_output(MX28_PAD_AUART2_RX__GPIO_3_8, 1);
#endif

	return 0;
}

int dram_init(void)
{
	gd->ram_size = PHYS_SDRAM_1_SIZE;
	return 0;
}

int board_init(void)
{
	/* Adress of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;

	return 0;
}

#ifdef CONFIG_CMD_MMC
static int brain_mmc_wp(int id)
{
	return 0;
}

static int brain_mmc_cd(int id)
{
	return 1;
}

int board_mmc_init(bd_t *bis)
{
	mxsmmc_initialize(bis, 0, brain_mmc_wp, brain_mmc_cd);
	mxsmmc_initialize(bis, 1, brain_mmc_wp, brain_mmc_cd);

	/* Turn on the SD*/
	gpio_direction_output(MX28_PAD_SSP2_SS2__GPIO_2_21, 0);
	return 0;
}
#endif

#ifdef CONFIG_VIDEO_MXS
static const lcd_config_t lcd_config = {
	.width = 854,
	.height = 480,
	.flip_x = ILI9805_DISABLE,
	.flip_y = ILI9805_DISABLE,
	.flip_y_gs = ILI9805_ENABLE,
	.transpose = ILI9805_ENABLE,
	.inversion = ILI9805_DISABLE,
	.bgr = ILI9805_DISABLE,
};

lcd_config_t get_lcd_config()
{
	return lcd_config;
}
#endif
