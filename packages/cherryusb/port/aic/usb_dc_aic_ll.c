/*
 * Copyright (c) 2022, Artinchip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <aic_core.h>
#include "usbd_core.h"
#include "usb_dc_aic_reg.h"

extern irqreturn_t USBD_IRQHandler(int irq, void * data);

uint32_t usbd_clk;
static unsigned char dma_sync_buffer[CACHE_LINE_SIZE] __attribute__((aligned(CACHE_LINE_SIZE)));

void usb_dc_sync_dma(void)
{
    asm volatile("sw t0, (%0)" : : "r"(dma_sync_buffer));
    csi_dcache_clean_range((phy_addr_t)(ptr_t)dma_sync_buffer, CACHE_LINE_SIZE);
}

#define SYSCFG_USB0_CFG                 0x40C
#define SYSCFG_USB0_HOST_MODE           0
#define SYSCFG_USB0_DEVICE_MODE         1

void syscfg_usb_phy0_sw_host(s32 sw)
{
    if (sw)
        writel(SYSCFG_USB0_HOST_MODE, SYSCFG_BASE + SYSCFG_USB0_CFG);
    else
        writel(SYSCFG_USB0_DEVICE_MODE, SYSCFG_BASE + SYSCFG_USB0_CFG);
}

void usb_dc_low_level_init(void)
{
    /* set usb0 phy switch: Host/Device */
#ifdef AIC_USING_USB0_DEVICE
    syscfg_usb_phy0_sw_host(0);
#endif
    /* set pin-mux */

    /* enable clock */
	cmu_mod_enable_clock_only(CONFIG_USB_AIC_DC_PHY_MOD);
	cmu_mod_enable_clock_only(CONFIG_USB_AIC_DC_MOD);
    aicos_udelay(600);
    cmu_mod_reset_hold(CONFIG_USB_AIC_DC_PHY_MOD);
    cmu_mod_reset_hold(CONFIG_USB_AIC_DC_MOD);
    aicos_udelay(600);
    cmu_mod_reset_release(CONFIG_USB_AIC_DC_PHY_MOD);
    cmu_mod_reset_release(CONFIG_USB_AIC_DC_MOD);
    aicos_udelay(600);

    usbd_clk = 200000000;

    /* register interrupt callback */
    aicos_request_irq(CONFIG_USB_AIC_DC_IRQ_NUM, USBD_IRQHandler,
                      0, "usb_device", NULL);
    aicos_irq_enable(CONFIG_USB_AIC_DC_IRQ_NUM);
}

