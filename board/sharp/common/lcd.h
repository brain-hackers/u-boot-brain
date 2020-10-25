#include <common.h>

#ifndef __BRAIN_LCD_H__
#define __BRAIN_LCD_H__

typedef struct {
	uint32_t	payload;
	unsigned int	data;
	uint32_t		delay;
} lcd_regs_t;

typedef struct {
	int flip_x;
	int flip_y;
	int transpose;
    int inversion;
    int bgr;
} lcd_config_t;

lcd_config_t get_lcd_config(void);

#define ILI9805_ENABLE 1
#define ILI9805_DISABLE 0

#define ILI9805_MAC_GS_OFFSET	0 /* Flip Vertical */
#define ILI9805_MAC_SS_OFFSET	1 /* Flip Horizontal */
#define ILI9805_MAC_MH_OFFSET	2 /* Horizontal Refresh Order (h direction) */
#define ILI9805_MAC_BGR_OFFSET	3 /* RGB-BGR Order */
#define ILI9805_MAC_ML_OFFSET	4 /* Vertical Refresh Order (v direction) */
#define ILI9805_MAC_MV_OFFSET	5 /* Row/Column Exchange */
#define ILI9805_MAC_MX_OFFSET	6 /* Column Address Order */
#define ILI9805_MAC_MY_OFFSET	7 /* Row Address Order */

#endif
