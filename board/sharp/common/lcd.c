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

static int mxsfb_write_byte(uint32_t payload, const unsigned int data)
{
	struct mxs_lcdif_regs *regs = (struct mxs_lcdif_regs *)MXS_LCDIF_BASE;
	const unsigned int timeout = 0x10000;

	if (mxs_wait_mask_clr(&regs->hw_lcdif_ctrl_reg, LCDIF_CTRL_RUN,
				timeout))
		return -ETIMEDOUT;

	writel((1 << LCDIF_TRANSFER_COUNT_V_COUNT_OFFSET) |
				(1 << LCDIF_TRANSFER_COUNT_H_COUNT_OFFSET),
			&regs->hw_lcdif_transfer_count);

	writel(LCDIF_CTRL_DATA_SELECT | LCDIF_CTRL_RUN,
			&regs->hw_lcdif_ctrl_clr);

	if (data)
		writel(LCDIF_CTRL_DATA_SELECT, &regs->hw_lcdif_ctrl_set);

	writel(LCDIF_CTRL_RUN, &regs->hw_lcdif_ctrl_set);

	if (mxs_wait_mask_clr(&regs->hw_lcdif_lcdif_stat_reg, 1 << 29, timeout))
		return -ETIMEDOUT;

	writel(payload, &regs->hw_lcdif_data);
	return mxs_wait_mask_clr(&regs->hw_lcdif_ctrl_reg, LCDIF_CTRL_RUN,
				timeout);
}

void mxsfb_system_setup(void)
{
	struct mxs_lcdif_regs *lcdif = (struct mxs_lcdif_regs *)MXS_LCDIF_BASE;
	struct mxs_clkctrl_regs *xtal =
		(struct mxs_clkctrl_regs *)MXS_CLKCTRL_BASE;
	struct mxs_pwm_regs *pwm = (struct mxs_pwm_regs *)MXS_PWM_BASE;

#ifdef CONFIG_BRAIN_3G_4G
	int i, j;
	uint8_t ili9805_mac = 0;
#else
	int i;
#endif
	uint32_t valid_data;

	lcd_config_t config = get_lcd_config();

	valid_data = readl(&lcdif->hw_lcdif_ctrl1) &
			LCDIF_CTRL1_BYTE_PACKING_FORMAT_MASK;
	writel(0x3 << LCDIF_CTRL1_BYTE_PACKING_FORMAT_OFFSET,
			&lcdif->hw_lcdif_ctrl1);

	/* Switch the LCDIF into System-Mode */
	writel(LCDIF_CTRL_LCDIF_MASTER | LCDIF_CTRL_DOTCLK_MODE |
				LCDIF_CTRL_BYPASS_COUNT,
			&lcdif->hw_lcdif_ctrl_clr);
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

#ifdef CONFIG_BRAIN_2G
	/* Reset LCD Controller */
	writel(LCDIF_CTRL1_RESET, &lcdif->hw_lcdif_ctrl1_set);
	mdelay(30);
	writel(LCDIF_CTRL1_RESET, &lcdif->hw_lcdif_ctrl1_clr);
	mdelay(30);
	writel(LCDIF_CTRL1_RESET, &lcdif->hw_lcdif_ctrl1_set);
	mdelay(30);
#endif

	for (i = 0; i < ARRAY_SIZE(regs_early); i++) {
		mxsfb_write_byte(regs_early[i].payload, regs_early[i].data);
		if (regs_early[i].delay)
			mdelay(regs_early[i].delay);
	}

#ifdef CONFIG_BRAIN_3G_4G
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

	if (config.flip_y_gs) {
		ili9805_mac |= 1 << ILI9805_MAC_GS_OFFSET;
	}

	mxsfb_write_byte(0x36, 0); /* Memory Access Control */
	mxsfb_write_byte(ili9805_mac, 1);

	if (config.inversion) {
		mxsfb_write_byte(0x21, 0); /* Display Inversion On */
	}
#endif

	mxsfb_write_byte(0x11, 0); /* Sleep Out */
	mdelay(120);

#ifdef CONFIG_BRAIN_2G
	mxsfb_write_byte(0x34, 0);
	mdelay(30);
#endif

	mxsfb_write_byte(0x29, 0); /* Display On */
	mdelay(20);

	mxsfb_write_byte(0x2a, 0); /* Column Address Set */

	mxsfb_write_byte(0x00, 1); /* Start Column in 2 Bytes */
	mxsfb_write_byte(0x00, 1);

#ifdef CONFIG_BRAIN_3G_4G
	mxsfb_write_byte((config.width & 0xff00) >> 8, 1); /* End Column in 2 Bytes */
	mxsfb_write_byte((config.width & 0x00ff) >> 0, 1);
#else
	mxsfb_write_byte((config.height & 0xff00) >> 8, 1); /* End Column in 2 Bytes */
	mxsfb_write_byte((config.height & 0x00ff) >> 0, 1);
#endif

	mxsfb_write_byte(0x2b, 0); /* Page Address Set */

	mxsfb_write_byte(0x00, 1); /* Start Page in 2 Bytes */
	mxsfb_write_byte(0x00, 1);

#ifdef CONFIG_BRAIN_3G_4G
	mxsfb_write_byte((config.height & 0xff00) >> 8, 1); /* End Page in 2 Bytes */
	mxsfb_write_byte((config.height & 0x00ff) >> 0, 1);
#else
	mxsfb_write_byte((config.width & 0xff00) >> 8, 1); /* End Page in 2 Bytes */
	mxsfb_write_byte((config.width & 0x00ff) >> 0, 1);
#endif

	mxsfb_write_byte(0x2c, 0); /* Memory Write */

#ifdef CONFIG_BRAIN_3G_4G
	/* Fill black */
	for (i = 0; i < config.height; i++) {
		for (j = 0; j < config.width; j++) {
			mxsfb_write_byte(0, 1);
		}
	}
#endif

#ifdef CONFIG_BRAIN_3G_4G
	writel(valid_data, &lcdif->hw_lcdif_ctrl1);
#else
	writel(valid_data | LCDIF_CTRL1_RESET, &lcdif->hw_lcdif_ctrl1);
#endif

	writel(LCDIF_CTRL_LCDIF_MASTER | LCDIF_CTRL_DATA_SELECT,
			&lcdif->hw_lcdif_ctrl_set);

	/* Turn on backlight */
	writel(CLKCTRL_XTAL_PWM_CLK24M_GATE, &xtal->hw_clkctrl_xtal_clr);
	mdelay(1);
	writel(PWM_CTRL_SFTRST, &pwm->hw_pwm_ctrl_clr);
	writel(PWM_CTRL_CLKGATE, &pwm->hw_pwm_ctrl_clr);

	writel(PWM_CTRL_PWM0_ENABLE | PWM_CTRL_PWM1_ENABLE,
			&pwm->hw_pwm_ctrl_clr);

	writel((0x005a << PWM_ACTIVE0_INACTIVE_OFFSET) |
				(0x0000 << PWM_ACTIVE0_ACTIVE_OFFSET),
			&pwm->hw_pwm_active0_set);

	writel((0x00f0 << PWM_ACTIVE1_INACTIVE_OFFSET) |
				(0x0000 << PWM_ACTIVE1_ACTIVE_OFFSET),
			&pwm->hw_pwm_active1_set);

	writel((0x1 << PWM_PERIOD0_CDIV_OFFSET) |
				(0x2 << PWM_PERIOD0_INACTIVE_STATE_OFFSET) |
				(0x3 << PWM_PERIOD0_ACTIVE_STATE_OFFSET) |
				(0x01f3 << PWM_PERIOD0_PERIOD_OFFSET),
			&pwm->hw_pwm_period0_set);

	writel((0x0 << PWM_PERIOD1_CDIV_OFFSET) |
				(0x3 << PWM_PERIOD1_INACTIVE_STATE_OFFSET) |
				(0x3 << PWM_PERIOD1_ACTIVE_STATE_OFFSET) |
				(0x07cf << PWM_PERIOD1_PERIOD_OFFSET),
			&pwm->hw_pwm_period1_set);

	writel(PWM_CTRL_PWM0_ENABLE | PWM_CTRL_PWM1_ENABLE,
			&pwm->hw_pwm_ctrl_set);
}
#endif
