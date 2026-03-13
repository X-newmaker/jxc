/*
 * Copyright (c) 2020-2021 Artinchip Technology Co., Ltd. All rights reserved.
 *
 * Dehuang Wu <dehuang.wu@artinchip.com>
 */

#include <ce_drv.h>
#include "all_inc.h"

void ce_set_task(u32 addr)
{
	writel(addr, CE_TSK_ADDR);
}

void ce_ctrl_start(u32 alg_tag)
{
	writel((alg_tag) | (1UL << 31), CE_TSK_CTL);
}

void ce_wait_finish(u32 accel_id)
{

	/* Interrupt should be disabled, so here check and wait tmo */
	while ((readl(CE_IRQ_STA) & (0x01 << accel_id)) == 0) {
		continue;
	}
}

void ce_pending_clear(u32 accel_id)
{
	u32 reg_val;

	reg_val = readl(CE_IRQ_STA);
	if ((reg_val & (0x01 << accel_id)) == (0x01 << accel_id)) {
		reg_val &= ~(0x0f);
		reg_val |= (0x01 << accel_id);
	}
	writel(reg_val, CE_IRQ_STA);
}

void ce_irq_enable(u32 accel_id)
{
	int val = readl(CE_IRQ_CTL);

	val |= (0x1 << accel_id);
	writel(val, CE_IRQ_CTL);
}

void ce_irq_disable(u32 accel_id)
{
	int val = readl(CE_IRQ_CTL);

	val &= ~(1 << accel_id);
	writel(val, CE_IRQ_CTL);
}

u32 ce_check_err(u32 accel_id)
{
	return ((readl(CE_TSK_ERR) >> (8 * accel_id)) & 0xFF);
}

#if 0
void dump_regs(void)
{
	u32 i, *p = (u32 *)0x10020000;

	for (i = 0; i < 10; i++) {
		printk("0x%x = 0x%x\n", p, *p);
		p++;
	}
}
#endif

void ce_init(void)
{
	volatile u32 usepll;

	cmu_mod_disable(CMU_MOD_CE);
	cmu_mod_set_div(CMU_MOD_CE, 5); /* 1200/(5+1) = 200MHz */
	cmu_mod_enable(CMU_MOD_CE);
	/* Disable all interrupt */
	writel(0, CE_IRQ_CTL);
	/* Clear interrupt status */
	writel(0xf, CE_IRQ_STA);
	writel(0xffffffff, CE_TSK_ERR);
}

void ce_exit(void)
{
	cmu_mod_disable(CMU_MOD_CE);
}
