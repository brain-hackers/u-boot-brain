// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mx7ulp-pins.h>
#include <asm/arch/iomux.h>

DECLARE_GLOBAL_DATA_PTR;

#define UART_PAD_CTRL	(PAD_CTL_PUS_UP)

static int count = 0;

int dram_init(void)
{
	gd->ram_size = PHYS_SDRAM_SIZE;

	return 0;
}

static iomux_cfg_t const lpuart4_pads[] = {
	MX7ULP_PAD_PTC3__LPUART4_RX | MUX_PAD_CTRL(UART_PAD_CTRL),
	MX7ULP_PAD_PTC2__LPUART4_TX | MUX_PAD_CTRL(UART_PAD_CTRL),
};

static void setup_iomux_uart(void)
{
	mx7ulp_iomux_setup_multiple_pads(lpuart4_pads,
					 ARRAY_SIZE(lpuart4_pads));
}

int board_early_init_f(void)
{
	setup_iomux_uart();
	count = 0;

	return 0;
}

int misc_init_f(void)
{
	//int base = 0x67800000, i, j, w;
	printf("Hello world from misc_init_f! %d\n", count++);

	/*
	// Memory dump
	// 1024 * 1024 / 16 = 65536
	for (i=0; i<65536; i++) {
		printf("%08x: ", i*16);
		for (j=0; j<4; j++) {
			w = cpu_to_be32(readl(base + 16*i + 4*j));
			printf("%04x %04x ", (w >> 16) & 0xffff, w & 0xffff);
		}
		printf("\n");
	}
	*/

	return 0;
}

int board_init(void)
{
	printf("Hello world from board_init!\n");
	/* address of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;

	return 0;
}
