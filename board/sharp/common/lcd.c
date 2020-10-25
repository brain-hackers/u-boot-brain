#include <common.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/iomux-mx28.h>
#include <asm/arch/clock.h>
#include <asm/arch/sys_proto.h>
#include <linux/mii.h>
#include <errno.h>

#include "lcd.h"

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_VIDEO_MXS

static lcd_regs_t regs_early[] = {
	{ 0xff, 0, 0 }, /* EXTC Command Set Enable */
		{ 0xff, 1, 0 }, { 0x98, 1, 0 }, { 0x05, 1, 0 },
	{ 0xfd, 0, 0 }, /* PFM Type C */
		{ 0x03, 1, 0 }, { 0x13, 1, 0 }, { 0x44, 1, 0 }, { 0x00, 1, 0 },
	{ 0xf8, 0, 0 }, /* PFM Type C */
		{ 0x18, 1, 0 }, { 0x02, 1, 0 }, { 0x02, 1, 0 }, { 0x18, 1, 0 },
		{ 0x02, 1, 0 }, { 0x02, 1, 0 }, { 0x30, 1, 0 },  { 0x01, 1, 0 },
		{ 0x01, 1, 0 }, { 0x30, 1, 0 }, { 0x01, 1, 0 },  { 0x01, 1, 0 },
		{ 0x30, 1, 0 }, { 0x01, 1, 0 },  { 0x01, 1, 0 },
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

static lcd_regs_t regs_late[] = {
	{ 0x11, 0, 120 }, /* Sleep Out */
	{ 0x29, 0, 20 }, /* Display On */
	{ 0x2a, 0, 0 }, /* Column Address Set */
		{ 0x00, 1, 0 }, { 0x00, 1, 0 }, { 0x03, 1, 0 }, { 0x1f, 1, 0 },
	{ 0x2b, 0, 0 }, /* Page Address Set */
		{ 0x00, 1, 0 }, { 0x00, 1, 0 }, { 0x01, 1, 0 }, { 0xdf, 1, 0 },
	{ 0x2c, 0, 0 }, /* Memory Write*/
};

static int mxsfb_write_byte(uint32_t payload, const unsigned int data)
{
	struct mxs_lcdif_regs *regs = (struct mxs_lcdif_regs *)MXS_LCDIF_BASE;
	const unsigned int timeout = 0x10000;

	if (mxs_wait_mask_clr(&regs->hw_lcdif_ctrl_reg, LCDIF_CTRL_RUN, timeout))
		return -ETIMEDOUT;

	writel((1 << LCDIF_TRANSFER_COUNT_V_COUNT_OFFSET) |
	       (1 << LCDIF_TRANSFER_COUNT_H_COUNT_OFFSET),
	       &regs->hw_lcdif_transfer_count);

	writel(LCDIF_CTRL_DATA_SELECT | LCDIF_CTRL_RUN,
	       &regs->hw_lcdif_ctrl_clr);

	if (data)
		writel(LCDIF_CTRL_DATA_SELECT, &regs->hw_lcdif_ctrl_set);

	writel(LCDIF_CTRL_RUN, &regs->hw_lcdif_ctrl_set);

	if (mxs_wait_mask_clr(&regs->hw_lcdif_lcdif_stat_reg, 1 << 29,
	    timeout))
		return -ETIMEDOUT;

	writel(payload, &regs->hw_lcdif_data);
	return mxs_wait_mask_clr(&regs->hw_lcdif_ctrl_reg, LCDIF_CTRL_RUN,
				 timeout);
}

void mxsfb_system_setup(void)
{
	struct mxs_lcdif_regs *lcdif = (struct mxs_lcdif_regs *)MXS_LCDIF_BASE;
	struct mxs_clkctrl_regs *xtal = (struct mxs_clkctrl_regs *)MXS_CLKCTRL_BASE;
	struct mxs_pwm_regs *pwm = (struct mxs_pwm_regs *)MXS_PWM_BASE;
	int i, j;
	uint32_t valid_data;

	uint8_t ili9805_mac = 0;
	lcd_config_t config = get_lcd_config();

	valid_data = readl(&lcdif->hw_lcdif_ctrl1) & LCDIF_CTRL1_BYTE_PACKING_FORMAT_MASK;
	writel(0x3 << LCDIF_CTRL1_BYTE_PACKING_FORMAT_OFFSET,
		&lcdif->hw_lcdif_ctrl1);

	/* Switch the LCDIF into System-Mode */
	writel(LCDIF_CTRL_LCDIF_MASTER | LCDIF_CTRL_DOTCLK_MODE |
	       LCDIF_CTRL_BYPASS_COUNT, &lcdif->hw_lcdif_ctrl_clr);
	writel(LCDIF_CTRL_VSYNC_MODE, &lcdif->hw_lcdif_ctrl_set);
	writel(LCDIF_VDCTRL3_VSYNC_ONLY, &lcdif->hw_lcdif_vdctrl3_set);

	writel((0x01 << LCDIF_TIMING_CMD_HOLD_OFFSET) |
	       (0x01 << LCDIF_TIMING_CMD_SETUP_OFFSET) |
	       (0x01 << LCDIF_TIMING_DATA_HOLD_OFFSET) |
	       (0x01 << LCDIF_TIMING_DATA_SETUP_OFFSET),
	       &lcdif->hw_lcdif_timing);

	/* Enable LCD Controller */
	gpio_direction_output(MX28_PAD_GPMI_ALE__GPIO_0_26, 1);
	gpio_direction_output(MX28_PAD_GPMI_CLE__GPIO_0_27, 1);
	gpio_direction_output(MX28_PAD_ENET_CLK__GPIO_4_16, 1);
	mdelay(20);

	for (i = 0; i < ARRAY_SIZE(regs_early); i++) {
		mxsfb_write_byte(regs_early[i].payload, regs_early[i].data);
		if (regs_early[i].delay)
			mdelay(regs_early[i].delay);
	}

	if (config.flip_x) {
		ili9805_mac |= 1 << ILI9805_MAC_MX_OFFSET;
	}

	if (config.flip_y) {
		ili9805_mac |= 1 << ILI9805_MAC_MY_OFFSET;
	}

	if (config.transpose) {
		ili9805_mac |= 1 << ILI9805_MAC_MV_OFFSET;
	}

	if (config.bgr) {
		ili9805_mac |= 1 << ILI9805_MAC_BGR_OFFSET;
	}

	mxsfb_write_byte(0x36, 0);	/* Memory Access Control */
	mxsfb_write_byte(ili9805_mac, 1);

	if (config.inversion) {
		mxsfb_write_byte(0x21, 0);	/* Display Inversion On */
	}

	for (i = 0; i < ARRAY_SIZE(regs_late); i++) {
		mxsfb_write_byte(regs_late[i].payload, regs_late[i].data);
		if (regs_late[i].delay)
			mdelay(regs_late[i].delay);
	}

	/* Fill black */
	for (i = 0; i < 480; i++) {
		for (j = 0; j < 800; j++) {
			mxsfb_write_byte(0, 1);
		}
	}

	writel(valid_data, &lcdif->hw_lcdif_ctrl1);

	writel(LCDIF_CTRL_LCDIF_MASTER | LCDIF_CTRL_DATA_SELECT,
	       &lcdif->hw_lcdif_ctrl_set);

	/* Turn on backlight */
	writel(CLKCTRL_XTAL_PWM_CLK24M_GATE, &xtal->hw_clkctrl_xtal_clr);
	mdelay(1);
	writel(PWM_CTRL_SFTRST, &pwm->hw_pwm_ctrl_clr);
	writel(PWM_CTRL_CLKGATE, &pwm->hw_pwm_ctrl_clr);

	writel(PWM_CTRL_PWM0_ENABLE | PWM_CTRL_PWM1_ENABLE, &pwm->hw_pwm_ctrl_clr);

	writel((0x005a << PWM_ACTIVE0_INACTIVE_OFFSET) |
	       (0x0000 << PWM_ACTIVE0_ACTIVE_OFFSET), &pwm->hw_pwm_active0_set);

	writel((0x00f0 << PWM_ACTIVE1_INACTIVE_OFFSET) |
	       (0x0000 << PWM_ACTIVE1_ACTIVE_OFFSET), &pwm->hw_pwm_active1_set);

	writel((0x1 << PWM_PERIOD0_CDIV_OFFSET) |
	       (0x2 << PWM_PERIOD0_INACTIVE_STATE_OFFSET) |
	       (0x3 << PWM_PERIOD0_ACTIVE_STATE_OFFSET) |
	       (0x01f3 << PWM_PERIOD0_PERIOD_OFFSET), &pwm->hw_pwm_period0_set);

	writel((0x0 << PWM_PERIOD1_CDIV_OFFSET) |
	       (0x3 << PWM_PERIOD1_INACTIVE_STATE_OFFSET) |
	       (0x3 << PWM_PERIOD1_ACTIVE_STATE_OFFSET) |
	       (0x07cf << PWM_PERIOD1_PERIOD_OFFSET), &pwm->hw_pwm_period1_set);

	writel(PWM_CTRL_PWM0_ENABLE | PWM_CTRL_PWM1_ENABLE, &pwm->hw_pwm_ctrl_set);
}
#endif
