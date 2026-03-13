/*
 * wdog.c
 */

#include <all_inc.h>

//#define CFG_CPU1_WDOG

#ifndef CFG_CPU1_WDOG
#define BASE_WDOG 	BASE_WDOG0
#else
#define BASE_WDOG	BASE_WDOG1
#endif

wdog_dev_t* const wdog_dev_p = (wdog_dev_t*)(BASE_WDOG);

static void watchdog0_null(void){};
static void watchdog1_null(void){};
cpu_irq_fun_t watchdog0_irqhandle = watchdog0_null;
cpu_irq_fun_t watchdog1_irqhandle = watchdog1_null;

ATTRIBUTE_ISR void WDOG0_IRQHandler(void)
{
        wdog0_irq_handler();
}

void wdog0_irq_handler(void)
{
        watchdog0_irqhandle();
}

ATTRIBUTE_ISR void WDOG1_IRQHandler(void)
{
        wdog1_irq_handler();
}

void wdog1_irq_handler(void)
{
        watchdog1_irqhandle();
}

void wdog_irq_register(u32 num, cpu_irq_fun_t irqhandle)
{
		switch(num){
    	case 0:
			watchdog0_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_WDOG0);
		break;
    	case 1:
			watchdog1_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_WDOG1);
		break;
    	default:
        break;
	}
}

void wdog_irq_unregister(u32 num)
{
		switch(num){
    	case 0:
			watchdog0_irqhandle = watchdog0_null;
			cpu_irq_disable(CPU_IRQ_WDOG0);
		break;
    	case 1:
			watchdog1_irqhandle = watchdog1_null;
			cpu_irq_disable(CPU_IRQ_WDOG1);
		break;
    	default:
        break;
	}
}

void wdog_cmu_init(void)
{
	cmu_mod_disable(CMU_MOD_WDOG);
	cmu_mod_enable(CMU_MOD_WDOG);
}

s32 wdog_op(wdog_op_t op)
{
	switch (op)
	{
	case WDOG_OP_CFG_SW0:
	case WDOG_OP_CFG_SW1:
	case WDOG_OP_CFG_SW2:
	case WDOG_OP_CFG_SW3:
		wdog_dev_p->wdog_op_reg.dwval = 0xA1C5A5A0 | (u8)op;
		wdog_dev_p->wdog_op_reg.dwval = 0xA1CA5A50 | (u8)op;
		break;
	case WDOG_OP_CNT_CLR:
		wdog_dev_p->wdog_op_reg.dwval = 0xA1C55555;
		wdog_dev_p->wdog_op_reg.dwval = 0xA1CAAAAA;
		break;
	case WDOG_OP_WR_EN:
		wdog_dev_p->wdog_op_reg.dwval = 0xA1C99999;
		wdog_dev_p->wdog_op_reg.dwval = 0xA1C66666;
		break;
	default:
		return RET_FALSE;
	}

	return RET_OK;
}

s32 wdog_cfg(u32 id, wdog_cfg_reg_t* cfg)
{
	u32 reg_wr_dis = wdog_dev_p->wdog_ctl_reg.bits.reg_wr_dis;

	if(reg_wr_dis==3)
		return RET_FALSE;
	else if(reg_wr_dis!=0)
		wdog_op(WDOG_OP_WR_EN);

	wdog_dev_p->wdog_cfg_reg[id].wdog_clr_thd_reg = cfg->wdog_clr_thd_reg;
	wdog_dev_p->wdog_cfg_reg[id].wdog_irq_thd_reg = cfg->wdog_irq_thd_reg;
	wdog_dev_p->wdog_cfg_reg[id].wdog_rst_thd_reg = cfg->wdog_rst_thd_reg;

	if(reg_wr_dis!=0)
		wdog_dev_p->wdog_ctl_reg.bits.reg_wr_dis = reg_wr_dis;

	return RET_OK;
}

s32 wdog_enable(u32 dis)
{
	wdog_dev_p->wdog_ctl_reg.bits.cnt_en = 1;
	wdog_dev_p->wdog_ctl_reg.bits.reg_wr_dis = dis;
	wdog_op(WDOG_OP_CNT_CLR);
	return RET_OK;
}

u32 wdog_get_cnt(void)
{
	return wdog_dev_p->wdog_cnt_reg.bits.cnt;
}

s32 wdog_irq_enable(void)
{
	wdog_dev_p->wdog_irq_en_reg.bits.timeout_irq_en = 1;

	return RET_OK;
}

s32 wdog_irq_disable(void)
{
	wdog_dev_p->wdog_irq_en_reg.bits.timeout_irq_en = 0;

	return RET_OK;
}

u32 wdog_irq_query(void)
{
	return wdog_dev_p->wdog_irq_sta_reg.dwval;
}

s32 wdog_irq_clear(u32 status)
{
	if(status)
		wdog_dev_p->wdog_irq_sta_reg.dwval = status;

	return RET_OK;
}

void wdog_set_clr_thd(u32 id, u32 clr_thd)
{
	wdog_dev_p->wdog_cfg_reg[id].wdog_clr_thd_reg = clr_thd;	
}

void wdog_set_irq_thd(u32 id, u32 irq_thd)
{
	wdog_dev_p->wdog_cfg_reg[id].wdog_irq_thd_reg = irq_thd;	
}

void wdog_set_rst_thd(u32 id, u32 rst_thd)
{
	wdog_dev_p->wdog_cfg_reg[id].wdog_rst_thd_reg = rst_thd;	
}

void wdog_expire_now(u32 id)
{
        wdog_set_rst_thd(id, 0);
        wdog_op(WDOG_OP_CNT_CLR);
        wdog_enable(0x1);
}

void wdog_force_reset(void)
{
	wdog_dev_p->wdog_force_rst_reg.dwval = 0xFEDCBA98;
}
