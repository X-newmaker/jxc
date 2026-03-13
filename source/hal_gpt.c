/*
 * Copyright (c) 2025, Artinchip Technology Co., Ltd
 */

#include <all_inc.h>

static void gpt0_null(void){};
static void gpt1_null(void){};
static void gpt2_null(void){};
static void gpt3_null(void){};

void gpt0_irq_handler(void);
void gpt1_irq_handler(void);
void gpt2_irq_handler(void);
void gpt3_irq_handler(void);
cpu_irq_fun_t gpt0_irqhandle = gpt0_null;
cpu_irq_fun_t gpt1_irqhandle = gpt1_null;
cpu_irq_fun_t gpt2_irqhandle = gpt2_null;
cpu_irq_fun_t gpt3_irqhandle = gpt3_null;

ATTRIBUTE_ISR void GPT0_IRQHandler(void)
{
    gpt0_irq_handler();
}

void gpt0_irq_handler(void)
{
    gpt0_irqhandle();
}

ATTRIBUTE_ISR void GPT1_IRQHandler(void)
{
    gpt1_irq_handler();
}

void gpt1_irq_handler(void)
{
    gpt1_irqhandle();
}

ATTRIBUTE_ISR void GPT2_IRQHandler(void)
{
    gpt2_irq_handler();
}

void gpt2_irq_handler(void)
{
    gpt2_irqhandle();
}

ATTRIBUTE_ISR void GPT3_IRQHandler(void)
{
    gpt3_irq_handler();
}

void gpt3_irq_handler(void)
{
    gpt3_irqhandle();
}

void gpt_irq_register(u8 num, cpu_irq_fun_t irqhandle)
{
        switch(num) {
                case 0:
                        gpt0_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_GPT0);
                        break;
                case 1:
                        gpt1_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_GPT1);
                        break;
                case 2:
                        gpt2_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_GPT2);
                        break;
                case 3:
                        gpt3_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_GPT3);
                        break;
        default:
                        break;
        }
}

void gpt_irq_unregister(u8 num)
{
        switch(num) {
                case 0:
                        gpt0_irqhandle = gpt0_null;
                        cpu_irq_disable(CPU_IRQ_GPT0);
                        break;
                case 1:
                        gpt1_irqhandle = gpt1_null;
                        cpu_irq_disable(CPU_IRQ_GPT1);
                        break;
                case 2:
                        gpt2_irqhandle = gpt2_null;
                        cpu_irq_disable(CPU_IRQ_GPT2);
                        break;
                case 3:
                        gpt3_irqhandle = gpt3_null;
                        cpu_irq_disable(CPU_IRQ_GPT3);
                        break;
        default:
                        break;
        }
}

void gpt_cmu_init(u8 num)
{
	cmu_mod_disable(CMU_MOD_GPT0+num);
	cmu_mod_enable(CMU_MOD_GPT0+num);
}

s32 init_gpt(gpt_num_t gpt_num,u32 trg_db,gpt_trg_mode_t trg_mode,gpt_run_mode_t run_mode,gpt_clk_div_t div,u32 cntr_val,u32 cntr_max)
{
	u32 reg_set;
	u32 source_fre;
	u32 set_div;
	writel(cntr_val,GPT_CNTR_VAL(gpt_num));
	writel(cntr_max-1,GPT_CNTR_MAX(gpt_num));
	source_fre = cmu_mod_get_freq(CMU_MOD_GPT0 + gpt_num);
	set_div = ((source_fre / div) - 1);
	writel(set_div,GPT_CLK(gpt_num));
	reg_set= (trg_db<<12 | trg_mode<<8 | run_mode<<4);
	writel(reg_set,GPT_CTL(gpt_num));
	return RET_OK;
}

s32 init_gpt_out(gpt_num_t gpt_num,u32 out_num,gpt_out_init_t out_init,u32 cmp_val_a,gpt_cmp_out_t cmp_out_a,
                                                                 u32 cmp_val_b,gpt_cmp_out_t cmp_out_b,gpt_out_en_t en)
{
	u32 reg_set;
	reg_set=(cmp_out_b<<12|cmp_out_a<<8|out_init<<4|en);
	writel(cmp_val_a,(GPT_OUT0_CMPA(gpt_num)+(out_num*0x10)));
	writel(cmp_val_b,(GPT_OUT0_CMPB(gpt_num)+(out_num*0x10)));
	writel(reg_set,(GPT_OUT0_CFG(gpt_num)+(out_num*0x10)));
	return RET_OK;
}

s32 gpt_en(gpt_num_t gpt_num)
{
	sbit(1,GPT_CTL(gpt_num));
	return RET_OK;
}

s32 gpt_disable(gpt_num_t gpt_num)
{
	cbit(1<<0,GPT_CTL(gpt_num));
	return RET_OK;
}


s32 gpt_irq_enable(gpt_num_t gpt_num,gpt_irq_t id)
{
	sbit(1<<id,GPT_IRQ_EN(gpt_num));
	return RET_OK;
}

s32 gpt_irq_enable_all(gpt_num_t gpt_num)
{
	writel(0x33330003,GPT_IRQ_EN(gpt_num));
	return RET_OK;
}

u32 gpt_irq_status(gpt_num_t gpt_num)
{
	return readl(GPT_IRQ_STA(gpt_num));
	return RET_OK;
}

s32 gpt_irq_clear(gpt_num_t gpt_num,u32 status)
{
	if(status) {
		writel(status,GPT_IRQ_STA(gpt_num));
	}

	return RET_OK;
}

s32 gpt_irq_disable(gpt_num_t gpt_num,gpt_irq_t id)
{
	cbit(1<<id,GPT_IRQ_EN(gpt_num));
	return RET_OK;
}

u32 gpt_get_time(gpt_num_t gpt_num)
{
	return readl(GPT_CNTR_VAL(gpt_num));
	return RET_OK;
}

void gpt_set_time(gpt_num_t gpt_num,u32 value)
{
	writel(value,GPT_CNTR_VAL(gpt_num));
}

s32 gpt_trg_get_val(gpt_num_t gpt_num)
{
	u32 level;
	level = ((readl(GPT_CTL(gpt_num))&0x10000000)>>28);
	return level;
}

s32 gpt_db0_point(gpt_num_t gpt_num,u32 point)
{

	writel(((point<<12) | ((readl(GPT_CTL(gpt_num)) & (0xffff0fff)))),GPT_CTL(gpt_num));

	return RET_OK;
}

s32 gpt_db1_point(gpt_num_t gpt_num,u32 point)
{

	writel(((point<<16) | ((readl(GPT_CTL(gpt_num)) & (0xfff0ffff)))),GPT_CTL(gpt_num));

	return RET_OK;
}

s32 gpt_db1_div(gpt_num_t gpt_num,u32 samp)
{

	writel(((samp<<20) | ((readl(GPT_CTL(gpt_num)) & (0xff0fffff)))),GPT_CTL(gpt_num));

	return RET_OK;
}

