/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 * hal_cap.c
 *
 */

#include <all_inc.h>

volatile struct CAP_REGS Cap0Regs  __attribute__((__section__(".cap0reg")));
volatile struct CAP_REGS Cap1Regs  __attribute__((__section__(".cap1reg")));
volatile struct CAP_REGS Cap2Regs  __attribute__((__section__(".cap2reg")));
volatile struct CAP_REGS Cap3Regs  __attribute__((__section__(".cap3reg")));
volatile struct CAP_REGS Cap4Regs  __attribute__((__section__(".cap4reg")));
volatile struct CAP_REGS Cap5Regs  __attribute__((__section__(".cap5reg")));

volatile struct CAP_REGS *CAP[] = {&Cap0Regs, &Cap1Regs, &Cap2Regs, 
                                &Cap3Regs, &Cap4Regs, &Cap5Regs};

static void cap0_null(void){};
static void cap1_null(void){};
static void cap2_null(void){};
static void cap3_null(void){};
static void cap4_null(void){};
static void cap5_null(void){};
cpu_irq_fun_t cap0_irqhandle = cap0_null;
cpu_irq_fun_t cap1_irqhandle = cap1_null;
cpu_irq_fun_t cap2_irqhandle = cap2_null;
cpu_irq_fun_t cap3_irqhandle = cap3_null;
cpu_irq_fun_t cap4_irqhandle = cap4_null;
cpu_irq_fun_t cap5_irqhandle = cap5_null;

ATTRIBUTE_ISR void CAP0_IRQHandler(void)
{
        cap0_irq_handler();
}

void cap0_irq_handler(void)
{
        cap0_irqhandle();
}

ATTRIBUTE_ISR void CAP1_IRQHandler(void)
{
        cap1_irq_handler();
}

void cap1_irq_handler(void)
{
        cap1_irqhandle();
}

ATTRIBUTE_ISR void CAP2_IRQHandler(void)
{
        cap2_irq_handler();
}

void cap2_irq_handler(void)
{
        cap2_irqhandle();
}

ATTRIBUTE_ISR void CAP3_IRQHandler(void)
{
        cap3_irq_handler();
}

void cap3_irq_handler(void)
{
        cap3_irqhandle();
}

ATTRIBUTE_ISR void CAP4_IRQHandler(void)
{
        cap4_irq_handler();
}

void cap4_irq_handler(void)
{
        cap4_irqhandle();
}

ATTRIBUTE_ISR void CAP5_IRQHandler(void)
{
        cap5_irq_handler();
}

void cap5_irq_handler(void)
{
        cap5_irqhandle();
}

void cap_irq_register(u32 num, cpu_irq_fun_t irqhandle)
{
	switch(num){
    	case 0:
    		cap0_irqhandle = irqhandle;
            cpu_irq_enable(CPU_IRQ_CAP0);
            break;
    	case 1:
    		cap1_irqhandle = irqhandle;
            cpu_irq_enable(CPU_IRQ_CAP1);
            break;
    	case 2:
    		cap2_irqhandle = irqhandle;
            cpu_irq_enable(CPU_IRQ_CAP2);
            break;
    	case 3:
    		cap3_irqhandle = irqhandle;
            cpu_irq_enable(CPU_IRQ_CAP3);
            break;
    	case 4:
    		cap4_irqhandle = irqhandle;
            cpu_irq_enable(CPU_IRQ_CAP4);
            break;
    	case 5:
    		cap5_irqhandle = irqhandle;
            cpu_irq_enable(CPU_IRQ_CAP5);
            break;
    	default:
                break;
	}

}

void cap_irq_unregister(u32 num)
{
	switch(num){
		case 0:
			cap0_irqhandle = cap0_null;
			cpu_irq_disable(CPU_IRQ_CAP0);
			break;
		case 1:
			cap1_irqhandle = cap1_null;
			cpu_irq_disable(CPU_IRQ_CAP1);
			break;
		case 2:
			cap2_irqhandle = cap2_null;
			cpu_irq_disable(CPU_IRQ_CAP2);
			break;
		case 3:
			cap3_irqhandle = cap3_null;
			cpu_irq_disable(CPU_IRQ_CAP3);
			break;
		case 4:
			cap4_irqhandle = cap4_null;
			cpu_irq_disable(CPU_IRQ_CAP4);
			break;
		case 5:
			cap5_irqhandle = cap5_null;
			cpu_irq_disable(CPU_IRQ_CAP5);
			break;
		default:
                break;
	}

}

void cap_en(u8 i)
{
    (*CAP[i]).CAP_CONF2.bit.CNT_EN = 0x1;
}

void cap_mode(u8 i , CAP_MOD mod)
{
    (*CAP[i]).CAP_CONF2.bit.CAP_MOD_SEL = mod;
}

u32 cap_get_cnt(u8 i)
{
    return (*CAP[i]).CAP_CNT_V;
}

void cap_em_control(u8 n,u32 ctl)
{
	(*CAP[n]).CAP_CONF1.bit.CAP_EN_CTL = ctl;
}

void cap_dma_en(u8 n)
{
	(*CAP[n]).CAP_DMA_CFG.bit.DMA_EN = 0x1;
}

void cap_dma_dis(u8 n)
{
	(*CAP[n]).CAP_DMA_CFG.bit.DMA_EN = 0x0;
}

void cap_dma_src(u8 n,u32 event)
{
	(*CAP[n]).CAP_DMA_CFG.bit.DMA_REQ_SRC_SEL = event;
}
