#include <common.h>

#ifndef __BRAIN_LCD_H__
#define __BRAIN_LCD_H__

typedef struct {
	int width;
	int height;
	int flip_x;
	int flip_y;
	int flip_y_gs;
	int transpose;
	int inversion;
	int bgr;
} lcd_config_t;

lcd_config_t get_lcd_config(void);

#define ILI9805_ENABLE 1
#define ILI9805_DISABLE 0

#define ILI9805_MAC_GS_OFFSET 0 /* Flip Vertical */
#define ILI9805_MAC_SS_OFFSET 1 /* Flip Horizontal */
#define ILI9805_MAC_MH_OFFSET 2 /* Horizontal Refresh Order (h direction) */
#define ILI9805_MAC_BGR_OFFSET 3 /* RGB-BGR Order */
#define ILI9805_MAC_ML_OFFSET 4 /* Vertical Refresh Order (v direction) */
#define ILI9805_MAC_MV_OFFSET 5 /* Row/Column Exchange */
#define ILI9805_MAC_MX_OFFSET 6 /* Column Address Order */
#define ILI9805_MAC_MY_OFFSET 7 /* Row Address Order */

typedef struct {
	uint32_t payload;
	unsigned int data;
	uint32_t delay;
} lcd_regs_t;

/* clang-format off */

const static lcd_regs_t regs_early[] = {
	{ 0xff, 0, 0 }, /* EXTC Command Set Enable */
		{ 0xff, 1, 0 }, { 0x98, 1, 0 }, { 0x05, 1, 0 },
	{ 0xfd, 0, 0 }, /* PFM Type C */
		{ 0x03, 1, 0 }, { 0x13, 1, 0 }, { 0x44, 1, 0 }, { 0x00, 1, 0 },
	{ 0xf8, 0, 0 }, /* PFM Type C */
		{ 0x18, 1, 0 }, { 0x02, 1, 0 }, { 0x02, 1, 0 }, { 0x18, 1, 0 },
		{ 0x02, 1, 0 }, { 0x02, 1, 0 }, { 0x30, 1, 0 }, { 0x01, 1, 0 },
		{ 0x01, 1, 0 }, { 0x30, 1, 0 }, { 0x01, 1, 0 }, { 0x01, 1, 0 },
		{ 0x30, 1, 0 }, { 0x01, 1, 0 }, { 0x01, 1, 0 },
	{ 0xb8, 0, 0 }, /* DBI Type B Interface Setting */
		{ 0x72, 1, 0 },
	{ 0xf1, 0, 0 }, /* Gate Modulation */
		{ 0x00, 1, 0 },
	{ 0xf2, 0, 0 }, /* CR/EQ/PC */
		{ 0x00, 1, 0 }, { 0x58, 1, 0 }, { 0x40, 1, 0 },
	{ 0xfc, 0, 0 }, /* LVGL Voltage Setting? */
		{ 0x04, 1, 0 }, { 0x0f, 1, 0 }, { 0x01, 1, 0 },
	{ 0xeb, 0, 0 }, /* ? */
		{ 0x08, 1, 0 }, { 0x0f, 1, 0 },
	{ 0xe0, 0, 0 }, /* Positive Gamma Control */
		{ 0x0a, 1, 0 }, { 0x23, 1, 0 }, { 0x35, 1, 0 }, { 0x15, 1, 0 },
		{ 0x13, 1, 0 }, { 0x16, 1, 0 }, { 0x0a, 1, 0 }, { 0x06, 1, 0 },
		{ 0x03, 1, 0 }, { 0x06, 1, 0 }, { 0x05, 1, 0 }, { 0x0a, 1, 0 },
		{ 0x08, 1, 0 }, { 0x23, 1, 0 }, { 0x1a, 1, 0 }, { 0x00, 1, 0 },
	{ 0xe1, 0, 0 }, /* Negative Gamma Control */
		{ 0x0a, 1, 0 }, { 0x23, 1, 0 }, { 0x28, 1, 0 }, { 0x10, 1, 0 },
		{ 0x11, 1, 0 }, { 0x16, 1, 0 }, { 0x0b, 1, 0 }, { 0x0a, 1, 0 },
		{ 0x02, 1, 0 }, { 0x05, 1, 0 }, { 0x04, 1, 0 }, { 0x0a, 1, 0 },
		{ 0x08, 1, 0 }, { 0x1d, 1, 0 }, { 0x1a, 1, 0 }, { 0x00, 1, 0 },
	{ 0xc1, 0, 0 }, /* Power Control 1 */
		{ 0x13, 1, 0 }, { 0x28, 1, 0 }, { 0x08, 1, 0 }, { 0x26, 1, 0 },
	{ 0xc7, 0, 0 }, /* VCOM Control */
		{ 0x90, 1, 0 },
	{ 0xb1, 0, 0 }, /* Frame Rate Control */
		{ 0x00, 1, 0 }, { 0x12, 1, 0 }, { 0x14, 1, 0 },
	{ 0xb4, 0, 0 }, /* Display Inversion Control */
		{ 0x02, 1, 0 },
	{ 0xbb, 0, 0 }, /* ? */
		{ 0x14, 1, 0 }, { 0x55, 1, 0 },
	{ 0x3a, 0, 0 }, /* Interface Pixel Format */
		{ 0x55, 1, 0 },
	{ 0xb6, 0, 0 }, /* MCU/RGB Interface Select */
		{ 0x01, 1, 0 }, { 0x80, 1, 0 }, { 0x8f, 1, 0 },
	{ 0x44, 0, 0 }, /* Write Tear Scan Line? */
		{ 0x00, 1, 0 }, { 0x00, 1, 0 },
	{ 0x35, 0, 0 }, /* Tearing Effect Line On */
		{ 0x00, 1, 0 },
};

/* clang-format on */

#endif
