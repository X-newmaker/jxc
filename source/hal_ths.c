/*
 * Copyright (c) 2022-2025, Artinchip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <all_inc.h>

static void LL_THS_Null(void) {};
cpu_irq_fun_t LL_THS_IrqHandleCallBack = LL_THS_Null;

ATTRIBUTE_ISR void THS_IRQHandler(void)
{
    LL_THS_IrqHandleCallBack();
}

void LL_THS_RegisterIrq(cpu_irq_fun_t IrqHandle)
{
    LL_THS_IrqHandleCallBack = IrqHandle;
    cpu_irq_enable(CPU_IRQ_THS);
}

void LL_THS_UnregisterIrq(void)
{
    LL_THS_IrqHandleCallBack = LL_THS_Null;
    cpu_irq_disable(CPU_IRQ_THS);
}

void LL_THS_InitClock(void)
{
    cmu_mod_disable(CMU_MOD_THS);
    for (volatile u32 i = 0; i < 10; i++)
    {
    }
    cmu_mod_enable(CMU_MOD_THS);
}

void THSn_Init(u8 Index)
{
    LL_THS_EnableIrqDrdyie(THS, Index);
    LL_THS_SetFilter(THS, Index, THS_FIL_EIGHT_POINT); // 采样点设置为8
    LL_THS_SetInterval(THS, Index, 0x222);         // 采样时间间隔
    LL_THS_EnableOtpe(THS, Index);

    LL_THS_SetOtpv(THS, Index, 0x730);
}
