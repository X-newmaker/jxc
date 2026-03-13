/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#include <all_inc.h>

volatile struct QOUT_REGS Qout0Regs __attribute__((__section__(".qout0reg")));
volatile struct QOUT_REGS Qout1Regs __attribute__((__section__(".qout1reg")));

volatile struct QOUT_REGS *QOUT[] = {
		&Qout0Regs, &Qout1Regs};

static void qout0_null(void){};
static void qout1_null(void){};
cpu_irq_fun_t qout0_irqhandle = qout0_null;
cpu_irq_fun_t qout1_irqhandle = qout1_null;

ATTRIBUTE_ISR void QOUT0_IRQHandler(void)
{
        qout0_irq_handler();
}

void qout0_irq_handler(void)
{
        qout0_irqhandle();
}

ATTRIBUTE_ISR void QOUT1_IRQHandler(void)
{
        qout1_irq_handler();
}

void qout1_irq_handler(void)
{
        qout1_irqhandle();
}

void qout_irq_register(u32 num, cpu_irq_fun_t irqhandle)
{
	switch(num){
    	case 0:
			qout0_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_QOUT0);
        break;
    	case 1:
			qout1_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_QOUT1);
        break;

    	default:
        break;
	}
}

void qout_irq_unregister(u32 num)
{
	switch(num){
    	case 0:
			qout0_irqhandle = qout0_null;
			cpu_irq_disable(CPU_IRQ_QOUT0);
		break;
    	case 1:
			qout1_irqhandle = qout1_null;
			cpu_irq_disable(CPU_IRQ_QOUT1);
		break;

    	default:
        break;
	}
}

void qout_err_cancl_en(u8 i)
{
        (*QOUT[i]).QOUT_CTL.bit.ERR_CANCL_EN = 0x1;       
}

void qout_err_cancl_dis(u8 i)
{
        (*QOUT[i]).QOUT_CTL.bit.ERR_CANCL_EN = 0x0;       
}

void qout_en(u8 i)
{
        (*QOUT[i]).QOUT_CTL.bit.GLB_EN = 0x1;       
}

void qout_dis(u8 i)
{
        (*QOUT[i]).QOUT_CTL.bit.GLB_EN = 0x0;       
}

void qout_pos_src_sel(u8 i, QOUT_SRC_TYPE src)
{
        (*QOUT[i]).QOUT_CFG.bit.POS_SRC_SEL = src;       
}

void qout_tmr_int_en(u8 i)
{
        (*QOUT[i]).QOUT_INT_EN.bit.TMR_INT_EN = 0x1;       
}

void qout_tmr_int_dis(u8 i)
{
        (*QOUT[i]).QOUT_INT_EN.bit.TMR_INT_EN = 0x0;       
}

void qout_pul_ovfl_int_en(u8 i)
{
        (*QOUT[i]).QOUT_INT_EN.bit.PUL_OVFL_INT_EN = 0x1;       
}

void qout_pul_ovfl_int_dis(u8 i)
{
        (*QOUT[i]).QOUT_INT_EN.bit.PUL_OVFL_INT_EN = 0x0;       
}

u32 qout_get_sts(u8 i)
{
        u32 sts;
        sts = (*QOUT[i]).QOUT_STS.all;
        return sts;
}

void qout_a_en(u8 i)
{
        (*QOUT[i]).QOUT_ABZ.bit.A_EN = 0x1;       
}

void qout_b_en(u8 i)
{
        (*QOUT[i]).QOUT_ABZ.bit.B_EN = 0x1;       
}

void qout_z_en(u8 i)
{
        (*QOUT[i]).QOUT_ABZ.bit.Z_EN = 0x1;       
}

void qout_a_inv_en(u8 i)
{
        (*QOUT[i]).QOUT_ABZ.bit.A_INV_EN = 0x1;       
}

void qout_b_inv_en(u8 i)
{
        (*QOUT[i]).QOUT_ABZ.bit.B_INV_EN = 0x1;       
}

void qout_z_inv_en(u8 i)
{
        (*QOUT[i]).QOUT_ABZ.bit.Z_INV_EN = 0x1;       
}

void qout_set_in_pulmax(u8 i, u32 max)
{
        (*QOUT[i]).QOUT_PUL_MAX.bit.PUL_MAX = (max & 0xFFFFFF);       
}

void qout_set_nm_raito(u8 i, u32 nm_ratio)
{
        (*QOUT[i]).QOUT_N_M_DIV.bit.N_M_DIV = (nm_ratio & 0x1FFFFF);
}

void qout_set_line(u8 i, u32 line)
{
        (*QOUT[i]).QOUT_LINE_NUM.bit.LINE_NUM = (line & 0x3FFFFF);       
}

void qout_set_pul_thr(u8 i, u32 pul_thr)
{
        (*QOUT[i]).QOUT_PUL_THR.bit.PUL_THR = (pul_thr & 0xFFFFFF);       
}

void qout_set_err_thr(u8 i, u32 err_thr)
{
        (*QOUT[i]).QOUT_ERR_CNCL_TH.bit.ERR_CNCL_TH = (err_thr & 0xFFFFF);       
}

void qout_set_err_cv(u8 i, u32 err_cv)
{
        (*QOUT[i]).QOUT_ERR_CNCL.bit.ERR_CNCL_V = (err_cv & 0xFFFFF);       
}

void qout_set_sw_mode(u8 i)
{
        (*QOUT[i]).QOUT_CFG.bit.OP_MOD = 0x1;
}

void qout_set_sw_pulse_prd(u8 i, u32 prd)
{
        (*QOUT[i]).QOUT_SW_PUL_PRD.bit.SW_PUL_PRD = prd;
}

void qout_set_sw_pulse_dir(u8 i, QOUT_SW_DIR_TYP dir)
{
        (*QOUT[i]).QOUT_PUL_DIR.bit.SW_DIR = dir;
}

void qout_set_sw_pulse_num(u8 i, u32 num)
{
        (*QOUT[i]).QOUT_PUL_DIR.bit.SW_NUM_SET = num & 0x3FF;
}

void qout_ded_pos_data(u8 i, u32 num)
{
	(*QOUT[i]).QOUT_DED_POS_DATA.bit.DED_POS_DATA = num;
}

void qout_z_ext(u8 i, u8 edg, u32 time)
{
	(*QOUT[i]).QOUT_ABZ.bit.Z_EXT_EN = 0x1;
	(*QOUT[i]).QOUT_ABZ.bit.Z_EXT_EDG_SET = edg;
	(*QOUT[i]).QOUT_ABZ.bit.T_ZEXT = time;
}

void qout_prd_link_sel(u8 i,QOUT_LINK_TYPE sel)
{
	(*QOUT[i]).QOUT_CTL.bit.QOUT_TMR_PRD_LINK = sel;
}

//注意qout定时同步使能，需保证QOUT_TMR_PRD的值小于等于同步信号的周期，否则会出现少脉冲的现象
void qout_sync_sel(u8 i, u8 sel)
{
	(*QOUT[i]).QOUT_CFG.bit.QOUT_TMR_SYNC_EN = 0x1;
	(*QOUT[i]).QOUT_CFG.bit.QOUT_TMR_SYNC_SEL = sel;
}
void qout_sync_dis(u8 i)
{
	(*QOUT[i]).QOUT_CFG.bit.QOUT_TMR_SYNC_EN = 0x0;
}
void qout_tmr_prd(u8 i,u32 tmr_prd)
{
	(*QOUT[i]).QOUT_TMR_PRD.bit.QOUT_TMR_PRD = tmr_prd;
}
