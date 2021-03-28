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
#ifdef CONFIG_BRAIN_3G_4G
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
#else
const static lcd_regs_t regs_early[] = {
	{ 0x3a, 0, 0 },
		{ 0x55, 1, 0 },
	{ 0xb2, 0, 0 },
		{ 0x45, 1, 0 }, { 0x00, 1, 0 }, { 0xd9, 1, 0 }, { 0x00, 1, 0 },
		{ 0x00, 1, 0 },
	{ 0xb3, 0, 0 },
		{ 0x81, 1, 0 }, { 0x00, 1, 0 }, { 0x01, 1, 0 },
	{ 0xb4, 0, 0 },
		{ 0x00, 1, 0 },
	{ 0xb5, 0, 0 },
		{ 0x02, 1, 0 }, { 0x11, 1, 0 }, { 0x50, 1, 0 }, { 0x00, 1, 0 },
		{ 0x80, 1, 0 }, { 0x45, 1, 0 }, { 0x45, 1, 0 }, { 0x00, 1, 0 },
	{ 0xb6, 0, 0 },
		{ 0x1e, 1, 0 }, { 0x01, 1, 0 }, { 0x90, 1, 0 }, { 0x0a, 1, 0 },
		{ 0x02, 1, 0 }, { 0x58, 1, 0 },
	{ 0xb7, 0, 0 },
		{ 0x2a, 1, 0 }, { 0x91, 1, 0 }, { 0x5c, 1, 0 }, { 0x06, 1, 0 },
		{ 0x08, 1, 0 }, { 0x0c, 1, 0 }, { 0x00, 1, 0 }, { 0x1c, 1, 0 },
		{ 0x06, 1, 0 }, { 0x02, 1, 0 }, { 0x09, 1, 0 },
	{ 0xb9, 0, 0 },
		{ 0x00, 1, 0 }, { 0x32, 1, 0 }, { 0x01, 1, 0 }, { 0x40, 1, 0 },
		{ 0x00, 1, 0 },
	{ 0xc0, 0, 0 },
		{ 0xb7, 1, 0 }, { 0x03, 1, 0 },
	{ 0xc1, 0, 0 },
		{ 0x72, 1, 0 }, { 0x01, 1, 0 },
	{ 0xc2, 0, 0 },
		{ 0x37, 1, 0 }, { 0x2f, 1, 0 }, { 0x0c, 1, 0 },
	{ 0xc3, 0, 0 },
		{ 0x37, 1, 0 }, { 0x03, 1, 0 },
	{ 0xc7, 0, 0 },
		{ 0x01, 1, 0 }, { 0x33, 1, 0 }, { 0x03, 1, 0 },
	{ 0xca, 0, 0 },
		{ 0xbd, 1, 0 }, { 0x17, 1, 0 }, { 0x5b, 1, 0 }, { 0x5b, 1, 0 },
		{ 0x64, 1, 0 }, { 0x11, 1, 0 }, { 0x66, 1, 0 },
	{ 0xde, 0, 0 },
		{ 0x11, 1, 0 }, { 0x00, 1, 0 },
	{ 0xe0, 0, 0 },
		{ 0x24, 1, 0 }, { 0x3f, 1, 0 }, { 0x0e, 1, 0 }, { 0x0e, 1, 0 },
		{ 0x67, 1, 0 }, { 0xee, 1, 0 }, { 0xee, 1, 0 }, { 0xa3, 1, 0 },
		{ 0x04, 1, 0 },
	{ 0xe1, 0, 0 },
		{ 0x24, 1, 0 }, { 0x3f, 1, 0 }, { 0x0f, 1, 0 }, { 0x0e, 1, 0 },
		{ 0x78, 1, 0 }, { 0xee, 1, 0 }, { 0xed, 1, 0 }, { 0x93, 1, 0 },
		{ 0x04, 1, 0 },
	{ 0xe2, 0, 0 },
		{ 0x24, 1, 0 }, { 0x29, 1, 0 }, { 0x14, 1, 0 }, { 0x1c, 1, 0 },
		{ 0x67, 1, 0 }, { 0xdd, 1, 0 }, { 0xdd, 1, 0 }, { 0x97, 1, 0 },
		{ 0x0b, 1, 0 },
	{ 0xe3, 0, 0 },
		{ 0x24, 1, 0 }, { 0x29, 1, 0 }, { 0x14, 1, 0 }, { 0x1c, 1, 0 },
		{ 0x67, 1, 0 }, { 0xdd, 1, 0 }, { 0xdd, 1, 0 }, { 0x97, 1, 0 },
		{ 0x0a, 1, 0 },
	{ 0xe4, 0, 0 },
		{ 0x24, 1, 0 }, { 0x2a, 1, 0 }, { 0x15, 1, 0 }, { 0x1a, 1, 0 },
		{ 0x99, 1, 0 }, { 0xdd, 1, 0 }, { 0xed, 1, 0 }, { 0xa6, 1, 0 },
		{ 0x09, 1, 0 },
	{ 0xe5, 0, 0 },
		{ 0x24, 1, 0 }, { 0x2a, 1, 0 }, { 0x15, 1, 0 }, { 0x1a, 1, 0 },
		{ 0x88, 1, 0 }, { 0xdd, 1, 0 }, { 0xdd, 1, 0 }, { 0x97, 1, 0 },
		{ 0x0c, 1, 0 },
	{ 0x36, 0, 0 }, /* Memory Acess Control */
		{ 0x28, 1, 0 },
	{ 0x2c, 0, 0 }, /* Display On */
		{ 0x00, 1, 0 },
};
#endif
/* clang-format on */

#endif
