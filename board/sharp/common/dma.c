#include <common.h>
#include <bootm.h>
#include <asm/mach-imx/dma.h>
#include <asm/arch/sys_proto.h>

void board_quiesce_devices(void) {
	mxs_dma_disable(MXS_DMA_CHANNEL_AHB_APBH_LCDIF);
	mxs_dma_release(MXS_DMA_CHANNEL_AHB_APBH_LCDIF);
	lcdif_power_down();
}
