/*
 * Copyright (c) 2022, Artinchip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <aic_core.h>
#include <hal_cmu.h>
#include "usbh_core.h"
#include "usb_ehci_priv.h"

extern void USBH_IRQHandler(void);

typedef struct aic_ehci_config {
    uint32_t base_addr;
    uint32_t mod_id;
    uint32_t phy_mod_id;
    uint32_t irq_num;
} aic_ehci_config_t;

aic_ehci_config_t config[] = {
    {
        USB_HOST0_BASE,
        CMU_MOD_USB_HOST0,
        CMU_MOD_USB_PHY0,
        USB_HOST0_EHCI_IRQn
    },
};

extern void syscfg_usb_phy0_sw_host(s32 sw);

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    uint32_t val;
    int i = 0;

    for (i=0; i<sizeof(config)/sizeof(aic_ehci_config_t); i++) {
        if (bus->hcd.reg_base == config[i].base_addr)
            break;
    }

    if (i == sizeof(config)/sizeof(aic_ehci_config_t))
        return;

    /* set pin-mux */

    /* set usb0 phy switch: Host/Device */
    if (i == 0)
        syscfg_usb_phy0_sw_host(1);

    /* enable clock */
    cmu_mod_disable(config[i].mod_id);
    cmu_mod_disable(config[i].phy_mod_id);
    aicos_udelay(600);
    cmu_mod_enable(config[i].phy_mod_id);
    cmu_mod_enable(config[i].mod_id);

    /* set phy type: UTMI/ULPI */
    val = readl((volatile void *)(unsigned long)(config[i].base_addr+0x800));
#ifdef FPGA_BOARD_ARTINCHIP
    /* fpga phy type = ULPI */
    writel((val  & ~0x1U), (volatile void *)(unsigned long)(config[i].base_addr+0x800));
#else
    /* board phy type = UTMI */
    writel((val | 0x1), (volatile void *)(unsigned long)(config[i].base_addr+0x800));
#endif

    /* Set AHB2STBUS_INSREG01
        Set EHCI packet buffer IN/OUT threshold (in DWORDs)
        Must increase the OUT threshold to avoid underrun. (FIFO size - 4)
    */
    writel((32 | (127 << 16)), (volatile void *)(unsigned long)(config[i].base_addr+0x94));

    /* register interrupt callback */
    aicos_request_irq(config[i].irq_num, (irq_handler_t)USBH_IRQHandler,
                      0, "usb_host_ehci", bus);
    aicos_irq_enable(config[i].irq_num);
}

uint8_t usbh_get_port_speed(struct usbh_bus *bus, const uint8_t port)
{
    /* Defined by individual manufacturers */
    uint32_t regval;

    regval = EHCI_HCOR->portsc[port-1];
    if ((regval & EHCI_PORTSC_LSTATUS_MASK) == EHCI_PORTSC_LSTATUS_KSTATE)
        return USB_SPEED_LOW;

    if (regval & EHCI_PORTSC_PE)
        return USB_SPEED_HIGH;
    else
        return USB_SPEED_FULL;
}

void usb_ehci_dcache_clean(uintptr_t addr, uint32_t len)
{
    aicos_dcache_clean_range((size_t *)addr, len);
}

void usb_ehci_dcache_invalidate(uintptr_t addr, uint32_t len)
{
    aicos_dcache_invalid_range((size_t *)addr, len);
}

void usb_ehci_dcache_clean_invalidate(uintptr_t addr, uint32_t len)
{
    aicos_dcache_clean_invalid_range((size_t *)addr, len);
}


