/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2011 Takumi Sueda.
 * Author: Takumi Sueda <puhitaku@gmail.com>
 *
 * (C) Copyright 2011 Freescale Semiconductor, Inc.
 * Author: Fabio Estevam <fabio.estevam@freescale.com>
 *
 * Based on m28evk.h:
 * Copyright (C) 2011 Marek Vasut <marek.vasut@gmail.com>
 * on behalf of DENX Software Engineering GmbH
 */
#ifndef __CONFIGS_PWSH2_H__
#define __CONFIGS_PWSH2_H__

/* System configurations */
#define CONFIG_MACH_TYPE	MACH_TYPE_MX28EVK

/* Memory configuration */
#define PHYS_SDRAM_1			0x40000000	/* Base address */
#define PHYS_SDRAM_1_SIZE		0x8000000	/* Max 128 MB RAM */
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1

/* Environment */
#define CONFIG_ENV_SIZE			(16 * 1024)
#define CONFIG_ENV_OVERWRITE

/* Environment is in MMC */
#if defined(CONFIG_CMD_MMC) && defined(CONFIG_ENV_IS_IN_MMC)
#define CONFIG_ENV_OFFSET		(256 * 1024)
#define CONFIG_SYS_MMC_ENV_DEV		0
#endif

/* USB */
#ifdef	CONFIG_CMD_USB
#define CONFIG_EHCI_MXS_PORT1
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#endif

/* Framebuffer support */
#ifdef CONFIG_VIDEO
#define CONFIG_VIDEO_MXS
#define CONFIG_VIDEO_MXS_MODE_SYSTEM
#define CONFIG_VIDEO_LOGO
#define CONFIG_VIDEO_BMP_LOGO
#define CONFIG_HIDE_LOGO_VERSION
#define CONFIG_SPLASH_SCREEN
#define CONFIG_BMP_16BPP
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_VIDEO_BMP_GZIP
#define CONFIG_SYS_VIDEO_LOGO_MAX_SIZE	(512 << 10)
#define CONFIG_VIDEO_FONT_6X11
#define LCD_BPP LCD_COLOR16
#endif

/* Boot Linux */
#define CONFIG_BOOTFILE		"uImage"
#define CONFIG_LOADADDR		0x42000000
#define CONFIG_SYS_LOAD_ADDR	CONFIG_LOADADDR

/* Extra Environment */
#define CONFIG_EXTRA_ENV_SETTINGS \
	"stdin=serial\0" \
	"stdout=serial,vga\0" \
	"stderr=serial,vga\0" \
	"videomode=video=ctfb:x:800,y:480,depth:16,pclk:30857,le:0,ri:0,up:0,lo:0,hs:0,vs:0,sync:0,vmode:0\0" \
	"bootdelay=0\0" \
	"image=zImage\0" \
	"console_mainline=ttyAMA0\0" \
	"fdt_file=imx28-pwsh2.dtb\0" \
	"fdt_addr=0x41000000\0" \
	"boot_fdt=try\0" \
	"mmcdev=1\0" \
	"mmcpart=1\0" \
	"mmcroot=/dev/mmcblk1p2 rw rootwait\0" \
	"mmcargs=setenv bootargs console=${console_mainline},${baudrate} console=tty1 " \
		"root=${mmcroot} fbcon=font:ProFont6x11\0" \
	"loadimage=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image}\0" \
	"loadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"run mmcargs; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if run loadfdt; then " \
				"bootz ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0" \

#define CONFIG_BOOTCOMMAND \
	"mmc dev ${mmcdev}; if mmc rescan; then " \
		"if run loadimage; then " \
			"run mmcboot; " \
		"else run netboot; " \
		"fi; " \
	"else run netboot; fi"

/* The rest of the configuration is shared */
#include <configs/mxs.h>

#endif /* __CONFIGS_PWSH2_H__ */
