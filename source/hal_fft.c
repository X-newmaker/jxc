/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 * hal_fft.c
 *
 */


#include <all_inc.h>

volatile struct FFT_REGS FFTRegs __attribute__((__section__(".fftreg")));

void fft_cmu_init(void)
{
	cmu_mod_disable(CMU_MOD_FFT);
	gtc_dly_time(1,1);
	cmu_mod_enable(CMU_MOD_FFT);
}

void fft_sram_syscfg_en(void)
{
	u32 reg_val;
	reg_val = readl(BASE_SYSCFG + 0x160);
	reg_val |= (0x1<<3 | 0xa1c<<20);
	writel(reg_val, (BASE_SYSCFG + 0x160));
}

void fft_sram_syscfg_dis(void)
{
	u32 reg_val;
	reg_val = readl(BASE_SYSCFG + 0x160);
	reg_val &= (~(0x1<<3));
	reg_val |= 0xa1c<<20;
	writel(reg_val, (BASE_SYSCFG + 0x160));
}

void fft_reset(void)
{
	FFTRegs.FFT_CTL.bit.SFT_RST = 0x1;
}

void fft_en(void)
{
	FFTRegs.FFT_CTL.bit.CAL_EN = 0x1;
}
u32 fft_get_irq_sts(void)
{
	u32 sts;
	sts = (FFTRegs.FFT_STS.all)&0xffff;
	return sts;
}
u32 fft_get_done_cnt(void)
{
	u32 cnt;
	cnt = FFTRegs.FFT_STS.bit.CMD_DONE_CNT;
	return cnt;
}
void fft_clr_irq_sts(u32 clr_sts)
{
	FFTRegs.FFT_STS.all = clr_sts;
}
void fft_irq_enable(u32 irq_en)
{
	FFTRegs.FFT_INT_EN.all = irq_en;
}
void fft_sram_own_en(FFT_SRAM_TYP sram_type)
{
	switch(sram_type)
	{
		case SRAM_B0:
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B0_CFG = 0x1;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B1_CFG = 0x0;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B2_CFG = 0x0;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B3_CFG = 0x0;
			break;
		case SRAM_B0_B1:
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B0_CFG = 0x1;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B1_CFG = 0x1;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B2_CFG = 0x0;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B3_CFG = 0x0;
			break;
		case SRAM_B0_B1_B2_B3:
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B0_CFG = 0x1;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B1_CFG = 0x1;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B2_CFG = 0x1;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B3_CFG = 0x1;
			break;
		default:
			break;
	}
}

void fft_sram_own_dis(FFT_SRAM_TYP sram_type)
{
	switch(sram_type)
	{
		case SRAM_B0:
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B0_CFG = 0x0;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B1_CFG = 0x0;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B2_CFG = 0x0;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B3_CFG = 0x0;
			break;
		case SRAM_B0_B1:
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B0_CFG = 0x0;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B1_CFG = 0x0;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B2_CFG = 0x0;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B3_CFG = 0x0;
			break;
		case SRAM_B0_B1_B2_B3:
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B0_CFG = 0x0;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B1_CFG = 0x0;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B2_CFG = 0x0;
			FFTRegs.FFT_SRAM_CFG.bit.SRAM_B3_CFG = 0x0;
			break;
		default:
			break;
	}
}

void fft_sram_baseaddr_set(u32 addr)
{
	FFTRegs.FFT_SRAM_BASE = addr;
}
void nxt_cmd_en(void)
{
	FFTRegs.FFT_OP_CTL.bit.NXT_CMD_EN = 0x1;
}
void nxt_cmd_dis(void)
{
	FFTRegs.FFT_OP_CTL.bit.NXT_CMD_EN = 0x0;
}
void nxt_cmd_addr(u32 addr)
{
	FFTRegs.FFT_OP_CTL.bit.NXT_CMD_ADDR = addr;
}

void abs_out_enable(u32 en)
{
	FFTRegs.FFT_OP_CMD.bit.ABS_OUT_EN = en;
}
void fft_outd_type(FFT_OUTD_TYP type)
{
	FFTRegs.FFT_OP_CMD.bit.OUTD_TYP = type;
}
void fft_ind_type (FFT_IND_TYP type)
{
	FFTRegs.FFT_OP_CMD.bit.IND_TYP = type;
}
void fft_float_out_cvr(FFT_FLOAT_OUT_TYP cvr)
{
	FFTRegs.FFT_OP_CMD.bit.FLOAT_OUT_CVR = cvr;
}
void fft_float_in_cvr(FFT_FLOAT_IN_TYP cvr)
{
	FFTRegs.FFT_OP_CMD.bit.FLOAT_IN_CVR = cvr;
}

void ifft_en(void)
{
	FFTRegs.FFT_CFG.bit.IFFT_EN = 0x1;
}
void ifft_dis(void)
{
	FFTRegs.FFT_CFG.bit.IFFT_EN = 0x0;
}
void fft_len(FFT_LEN_TYP len)
{
	FFTRegs.FFT_CFG.bit.FFT_LEN = len;
}

void fft_inbuf(u32 addr)
{
	FFTRegs.FFT_INBUF = addr;
}
void fft_outbuf(u32 addr)
{
	FFTRegs.FFT_OUTBUF = addr;
}
