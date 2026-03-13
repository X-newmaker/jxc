/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 * hal_pga.c
 *
 */

#include <all_inc.h>
volatile struct RDC_REGS RDCRegs  __attribute__((__section__(".rdcreg")));

void rdc_cmu_init(void)
{
	cmu_mod_disable(CMU_MOD_RDC);
	gtc_dly_time(1,1);
	cmu_mod_enable(CMU_MOD_RDC);
}

void rdc_adc_dat_mode(u8 mode)
{
	RDCRegs.RDC_CTL.bit.RDC_DAT_MOD = mode;
}

void rdc_en(u8 en)
{
	RDCRegs.RDC_CTL.bit.RDC_EN = en;
}

void rcd_cal_trg(void)
{
	RDCRegs.RDC_CAL_TRG.bit.TRG_SET = 0x1;
}

void rdc_usin_off_set(u32 set)
{
	RDCRegs.RDC_USIN_OFF.bit.USIN_OFF = set;
}

void rdc_ucos_off_set(u32 set)
{
	RDCRegs.RDC_UCOS_OFF.bit.UCOS_OFF = set;
}

void rdc_usin_gain_set(u32 set)
{
	RDCRegs.RDC_USIN_G.bit.USIN_G = set;
}

void rdc_ucos_gain_set(u32 set)
{
	RDCRegs.RDC_UCOS_G.bit.UCOS_G = set;
}

void rdc_usin_reg_set(u32 set)
{
	RDCRegs.RDC_REG_USIN.bit.REG_USIN = set;
}

void rdc_ucos_reg_set(u32 set)
{
	RDCRegs.RDC_REG_UCOS.bit.REG_UCOS = set;
}

u32 rdc_get_theta(void)
{
	u32 val;
	val = RDCRegs.RDC_THETA_RDC.all ;
	return val;
}
