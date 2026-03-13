/*
 * hal_xpwm.c
 *
 *  Created on: 2024年12月25日
 *      Author: ziqing.kong
 */
#include <all_inc.h>

volatile struct XPWM_REGS XPWM0Regs __attribute__((__section__(".xpwm0reg")));
volatile struct XPWM_REGS XPWM1Regs __attribute__((__section__(".xpwm1reg")));
volatile struct XPWM_REGS XPWM2Regs __attribute__((__section__(".xpwm2reg")));
volatile struct XPWM_REGS XPWM3Regs __attribute__((__section__(".xpwm3reg")));
volatile struct XPWM_REGS XPWM4Regs __attribute__((__section__(".xpwm4reg")));
volatile struct XPWM_REGS XPWM5Regs __attribute__((__section__(".xpwm5reg")));

volatile struct XPWM_REGS *XPWM[] = {
		&XPWM0Regs, &XPWM1Regs, &XPWM2Regs,
        &XPWM3Regs, &XPWM4Regs, &XPWM5Regs};

static void xpwm0_null(void){};
static void xpwm1_null(void){};
static void xpwm2_null(void){};
static void xpwm3_null(void){};
static void xpwm4_null(void){};
static void xpwm5_null(void){};
cpu_irq_fun_t xpwm0_irqhandle = xpwm0_null;
cpu_irq_fun_t xpwm1_irqhandle = xpwm1_null;
cpu_irq_fun_t xpwm2_irqhandle = xpwm2_null;
cpu_irq_fun_t xpwm3_irqhandle = xpwm3_null;
cpu_irq_fun_t xpwm4_irqhandle = xpwm4_null;
cpu_irq_fun_t xpwm5_irqhandle = xpwm5_null;

ATTRIBUTE_ISR void XPWM0_IRQHandler(void)
{
        xpwm0_irq_handler();
}

void xpwm0_irq_handler(void)
{
        xpwm0_irqhandle();
}

void xpwm0_irq_register(cpu_irq_fun_t irqhandle)
{
        xpwm0_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_PWM0);
}

void xpwm0_irq_unregister(void)
{
        xpwm0_irqhandle = xpwm0_null;
        cpu_irq_disable(CPU_IRQ_PWM0);
}

ATTRIBUTE_ISR void XPWM1_IRQHandler(void)
{
        xpwm1_irq_handler();
}

void xpwm1_irq_handler(void)
{
        xpwm1_irqhandle();
}

void xpwm1_irq_register(cpu_irq_fun_t irqhandle)
{
        xpwm1_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_PWM1);
}

void xpwm1_irq_unregister(void)
{
        xpwm1_irqhandle = xpwm0_null;
        cpu_irq_disable(CPU_IRQ_PWM1);
}

ATTRIBUTE_ISR void XPWM2_IRQHandler(void)
{
        xpwm2_irq_handler();
}

void xpwm2_irq_handler(void)
{
        xpwm2_irqhandle();
}

void xpwm2_irq_register(cpu_irq_fun_t irqhandle)
{
        xpwm2_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_PWM2);
}

void xpwm2_irq_unregister(void)
{
        xpwm2_irqhandle = xpwm2_null;
        cpu_irq_disable(CPU_IRQ_PWM2);
}

ATTRIBUTE_ISR void XPWM3_IRQHandler(void)
{
        xpwm3_irq_handler();
}

void xpwm3_irq_handler(void)
{
        xpwm3_irqhandle();
}

void xpwm3_irq_register(cpu_irq_fun_t irqhandle)
{
        xpwm3_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_PWM3);
}

void xpwm3_irq_unregister(void)
{
        xpwm3_irqhandle = xpwm3_null;
        cpu_irq_disable(CPU_IRQ_PWM3);
}

ATTRIBUTE_ISR void XPWM4_IRQHandler(void)
{
        xpwm4_irq_handler();
}

void xpwm4_irq_handler(void)
{
        xpwm4_irqhandle();
}

void xpwm4_irq_register(cpu_irq_fun_t irqhandle)
{
        xpwm4_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_PWM4);
}

void xpwm4_irq_unregister(void)
{
        xpwm4_irqhandle = xpwm4_null;
        cpu_irq_disable(CPU_IRQ_PWM4);
}

ATTRIBUTE_ISR void XPWM5_IRQHandler(void)
{
        xpwm5_irq_handler();
}

void xpwm5_irq_handler(void)
{
        xpwm5_irqhandle();
}

void xpwm5_irq_register(cpu_irq_fun_t irqhandle)
{
        xpwm5_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_PWM5);
}

void xpwm5_irq_unregister(void)
{
        xpwm5_irqhandle = xpwm5_null;
        cpu_irq_disable(CPU_IRQ_PWM5);
}

void xpwm_cmu_init(u8 num)
{
        cmu_mod_disable(CMU_MOD_PWM0 + num);
        cmu_mod_enable(CMU_MOD_PWM0 + num);
}

void xpwm_clk_div_set(u8 i, u32 div)
{
	(*XPWM[i]).XPWM_CONF.bit.CLK_DIV = div;
}

void xpwm_fifo_th_set(u8 i, u32 th)
{
	(*XPWM[i]).XPWM_CONF.bit.XPWM_FIFO_TH = th;
}

void xpwm_pul_limit_en(u8 i, u32 en)
{
	(*XPWM[i]).XPWM_CONF.bit.PUL_LIMIT_EN = en;
}

void xpwm_dma_en(u8 i,u32 en)
{
	(*XPWM[i]).XPWM_CONF.bit.XPWM_DMA_EN = en;
}

void xpwm_fifo_en(u8 i ,u32 en)
{
	(*XPWM[i]).XPWM_CONF.bit.XPWM_FIFO_EN = en;
}

void xpwm_update_mode_set(u8 i, u32 mode)
{
	(*XPWM[i]).XPWM_CONF.bit.XPWM_UPDATE_MODE = mode;
}

void xpwm_mod_set(u8 i,u32 mode)
{
	(*XPWM[i]).XPWM_CONF.bit.XPWM_MOD = mode;
}

void xpwm_cnt_en(u8 i ,u32 en)
{
	(*XPWM[i]).XPWM_CONF.bit.XPWM_CNT_EN = en;
}

void xpwm_idle_set(u8 i, u32 idle)
{
	(*XPWM[i]).XPWM_CH_CONF.bit.XPWM_IDLE = idle;
}

void xpwm_inv_en(u8 i, u32 en)
{
	(*XPWM[i]).XPWM_CH_CONF.bit.XPWM_INV_EN = en;
}

void xpwm_imd_updt_en(u8 i, u32 en)
{
	(*XPWM[i]).XPWM_CH_CONF.bit.XPWM_IMD_UPDT = en;
}

u32 get_xpwm_sts_flag(u8 i)
{
	u32 sts;
	sts = (*XPWM[i]).XPWM_STS_FLAG.all;
	return sts;
}

void xpwm_sts_flag_clr(u8 i,u32 clr)
{
	(*XPWM[i]).XPWM_STS_FLAG.all = clr;
}

void xpwm_int_en(u8 i,u32 val)
{
	(*XPWM[i]).XPWM_INT_EN.all = val;
}

void xpwm_fifo_flush(u8 i)
{
	(*XPWM[i]).XPWM_FIFO_FLUSH.bit.XPWM_FIFO_FLUSH = 0x1;
}

void xpwm_resume(u8 i)
{
	(*XPWM[i]).XPWM_RESUME.bit.PUL_RESUME = 0x1;
}

void xpwm_pul_sta_flush(u8 i)
{
	(*XPWM[i]).XPWM_RESUME.bit.XPWM_PUL_STA_FLUSH = 0x1;
}
void xpwm_pul_restart(u8 i)
{
	(*XPWM[i]).XPWM_THR_RS.bit.PUL_THR_RS = 0x1;
}
void xpwm_fifo_reg(u8 i, u32 data)
{
	(*XPWM[i]).XPWM_FIFO.all = data;
}
u32 get_xpwm_pul_sta(u8 i)
{
	u32 cnt;
	cnt = (*XPWM[i]).XPWM_PUL_STA.all;
	return cnt;
}
u32 get_xpwm_cnt(u8 i)
{
	u32 cnt;
	cnt = (*XPWM[i]).XPWM_CNT_STA.all;
	return cnt;
}
void xpwm_prd_set(u8 i,u32 prd)
{
	(*XPWM[i]).XPWM_PRD.bit.PRD_VAL = prd;
}
void xpwm_pul_cnt_set(u8 i, u32 val)
{
	(*XPWM[i]).XPWM_PUL_CNT.bit.PUL_CNT = val;
}
void xpwm_pul_thr_set(u8 i ,u32 val)
{
	(*XPWM[i]).XPWM_PUL_THR.bit.PUL_THR = val;
}
void xpwm_cmp_set(u8 i,u32 cmp)
{
	(*XPWM[i]).XPWM_CMP.bit.CMP_VAL = cmp;
}

