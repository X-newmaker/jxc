/*
 * Copyright (c) 2020-2021 Artinchip Technology Co., Ltd. All rights reserved.
 *
 * Dehuang Wu <dehuang.wu@artinchip.com>
 */
#ifndef _CE_DRV_H_
#define _CE_DRV_H_

#include "all_inc.h"

#define CE_REG_BASE 0x10020000
#define CE_TSK_ADDR (CE_REG_BASE + 0x008)
#define CE_TSK_CTL (CE_REG_BASE + 0x00C)
#define CE_IRQ_STA (CE_REG_BASE + 0x004)
#define CE_IRQ_CTL (CE_REG_BASE + 0x000)
#define CE_TSK_ERR (CE_REG_BASE + 0x014)
#define CE_TSK_ADDR (CE_REG_BASE + 0x008)
#define CE_TSK_ADDR (CE_REG_BASE + 0x008)



void ce_set_task(u32 addr);
void ce_ctrl_start(u32 alg_tag);
void ce_wait_finish(u32 accel_id);
void ce_pending_clear(u32 accel_id);
void ce_irq_enable(u32 accel_id);
void ce_irq_disable(u32 accel_id);
u32 ce_check_err(u32 accel_id);

#endif

