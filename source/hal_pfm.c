/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 * hal_pfm.c
 *
 */

#include <all_inc.h>

void pfm_cmu_init(void)
{
	cmu_mod_disable(CMU_MOD_PFM);
	gtc_dly_time(1,1);
	cmu_mod_enable(CMU_MOD_PFM);
}

u32 pfm_get_dne_sts(void)
{
    u32 reg_val;
    reg_val = readl(PFM_GLB_STS);
    reg_val &= 0x3f;
    return reg_val;
}

u32 pfm_get_err_sts(void)
{
    u32 reg_val;
    reg_val = readl(PFM_GLB_STS);
    reg_val = (reg_val >> 16);
    reg_val &= 0x3f;
    return reg_val;
}

u32 pfm_get_op_sts(void)
{
    u32 reg_val;
    reg_val = readl(PFM_GLB_STS);
    reg_val = (reg_val >> 24);
    reg_val &= 0x3f;
    return reg_val;
}

void pfm_dne_sts_clr(u32 clr)
{
	writel(clr, PFM_GLB_STS);
}

void pfm_err_sts_clr(u32 clr)
{
	writel((clr<<16), PFM_GLB_STS);
}

void pfm_fltr_irq_en(u32 i, u32 en)
{
    u32 reg_val;
    switch(i){
    	case 0:
			reg_val = readl(PFM_GLB_EN);
			reg_val &= (~(0x1 << 0));
			reg_val |= ((en & 0x1) << 0);
			writel(reg_val, PFM_GLB_EN);
		break;
    	case 1:
			reg_val = readl(PFM_GLB_EN);
			reg_val &= (~(0x1 << 1));
			reg_val |= ((en & 0x1) << 1);
			writel(reg_val, PFM_GLB_EN);
		break;
    	case 2:
			reg_val = readl(PFM_GLB_EN);
			reg_val &= (~(0x1 << 2));
			reg_val |= ((en & 0x1) << 2);
			writel(reg_val, PFM_GLB_EN);
		break;
    	case 3:
			reg_val = readl(PFM_GLB_EN);
			reg_val &= (~(0x1 << 3));
			reg_val |= ((en & 0x1) << 3);
			writel(reg_val, PFM_GLB_EN);
		break;
    	case 4:
			reg_val = readl(PFM_GLB_EN);
			reg_val &= (~(0x1 << 4));
			reg_val |= ((en & 0x1) << 4);
			writel(reg_val, PFM_GLB_EN);
		break;
    	case 5:
			reg_val = readl(PFM_GLB_EN);
			reg_val &= (~(0x1 << 5));
			reg_val |= ((en & 0x1) << 5);
			writel(reg_val, PFM_GLB_EN);
		break;
    }
}


void pfm_fltr_en(u32 i, u32 en)
{
    u32 reg_val;

    reg_val = readl(PFM_FLTR_CTL(i));
    reg_val &= (~(0x1 << 0));
    reg_val |= ((en & 0x1) << 0);
    writel(reg_val, PFM_FLTR_CTL(i));
}

void pfm_fltr_odr_set(u32 i, PFM_ORDER_TYP odr)
{
    u32 reg_val;

    reg_val = readl(PFM_FLTR_CTL(i));
    reg_val &= (~(0x7 << 1));
    reg_val |= ((odr & 0x7) << 1);
    writel(reg_val, PFM_FLTR_CTL(i));
}

void pfm_fltr_coeff_sel(u32 i, u32 sel)
{
    u32 reg_val;

    reg_val = readl(PFM_FLTR_CTL(i));
    reg_val &= (~(0x1 << 4));
    reg_val |= ((sel & 0x1) << 4);
    writel(reg_val, PFM_FLTR_CTL(i));
}

void pfm_fltr_limit_en(u32 i, u32 en)
{
    u32 reg_val;

    reg_val = readl(PFM_FLTR_CTL(i));
    reg_val &= (~(0x1 << 5));
    reg_val |= ((en & 0x1) << 5);
    writel(reg_val, PFM_FLTR_CTL(i));
}

void pfm_fltr_scla_en(u32 i, u32 en)
{
    u32 reg_val;

    reg_val = readl(PFM_FLTR_CTL(i));
    reg_val &= (~(0x1 << 6));
    reg_val |= ((en & 0x1) << 6);
    writel(reg_val, PFM_FLTR_CTL(i));
}

void pfm_fltr_sclb_en(u32 i, u32 en)
{
    u32 reg_val;

    reg_val = readl(PFM_FLTR_CTL(i));
    reg_val &= (~(0x1 << 7));
    reg_val |= ((en & 0x1) << 7);
    writel(reg_val, PFM_FLTR_CTL(i));
}

void pfm_fltr_bpz0_en(u32 i, u32 en)
{
    u32 reg_val;

    reg_val = readl(PFM_FLTR_CTL(i));
    reg_val &= (~(0x1 << 9));
    reg_val |= ((en & 0x1) << 9);
    writel(reg_val, PFM_FLTR_CTL(i));
}

void pfm_fltr_in_src(u32 i, u32 src)
{
    u32 reg_val;

    reg_val = readl(PFM_FLTR_CTL(i));
    reg_val &= (~(0xf << 16));
    reg_val |= ((src & 0xf) << 16);
    writel(reg_val, PFM_FLTR_CTL(i));
}

void pfm_fltr_trg_src(u32 i, u32 src)
{
    u32 reg_val;

    reg_val = readl(PFM_FLTR_CTL(i));
    reg_val &= (~(0xf << 20));
    reg_val |= ((src & 0xf) << 20);
    writel(reg_val, PFM_FLTR_CTL(i));
}

void pfm_fltr_zin_src(u32 i, u32 src)
{
    u32 reg_val;

    reg_val = readl(PFM_FLTR_CTL(i));
    reg_val &= (~(0xf << 24));
    reg_val |= ((src & 0xf) << 24);
    writel(reg_val, PFM_FLTR_CTL(i));
}

void pfm_fltr_yin_src(u32 i, u32 src)
{
    u32 reg_val;

    reg_val = readl(PFM_FLTR_CTL(i));
    reg_val &= (~(0xf << 28));
    reg_val |= ((src & 0xf) << 28);
    writel(reg_val, PFM_FLTR_CTL(i));
}

void pfm_fltr_sw_trg(u32 i)
{
    writel(0x1, PFM_FLTR_TRG(i));
}

void pfm_fltr_sw_rst(u32 i)
{
    writel(0xA1C80000, PFM_FLTR_TRG(i));
}

void pfm_fltr_scla_set(u32 i, u32 set)
{
    u32 reg_val;

    reg_val = readl(PFM_FLTR_SCAL(i));
    reg_val &= (~(0x1f << 0));
    reg_val |= ((set & 0x1f) << 0);
    writel(reg_val, PFM_FLTR_SCAL(i));
}

void pfm_fltr_sclb_set(u32 i, u32 set)
{
    u32 reg_val;

    reg_val = readl(PFM_FLTR_SCAL(i));
    reg_val &= (~(0x1f << 8));
    reg_val |= ((set & 0x1f) << 8);
    writel(reg_val, PFM_FLTR_SCAL(i));
}

void pfm_fltr_input(u32 i, u32 input)
{
	writel(input, PFM_FLTR_DIN(i));
}

s32 pfm_fltr_output(u32 i)
{
	s32 output;
	output = readl(PFM_FLTR_DOUT(i));
	return output;
}

void pfm_fltr_min_h(u32 i, u32 min_h)
{
	writel(min_h, PFM_FLTR_MINH(i));
}

void pfm_fltr_min_l(u32 i, u32 min_l)
{
	writel(min_l, PFM_FLTR_MINL(i));
}

void pfm_fltr_max_h(u32 i, u32 max_h)
{
	writel(max_h, PFM_FLTR_MAXH(i));
}

void pfm_fltr_max_l(u32 i, u32 max_l)
{
	writel(max_l, PFM_FLTR_MAXL(i));
}

void pfm_fltr_fa1_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_FA1(i));
}

void pfm_fltr_fa2_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_FA2(i));
}

void pfm_fltr_fa3_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_FA3(i));
}

void pfm_fltr_fa4_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_FA4(i));
}

void pfm_fltr_fb0_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_FB0(i));
}

void pfm_fltr_fb1_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_FB1(i));
}

void pfm_fltr_fb2_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_FB2(i));
}

void pfm_fltr_fb3_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_FB3(i));
}

void pfm_fltr_fb4_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_FB4(i));
}

void pfm_fltr_sa1_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_SA1(i));
}

void pfm_fltr_sa2_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_SA2(i));
}

void pfm_fltr_sa3_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_SA3(i));
}

void pfm_fltr_sa4_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_SA4(i));
}

void pfm_fltr_sb0_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_SB0(i));
}

void pfm_fltr_sb1_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_SB1(i));
}

void pfm_fltr_sb2_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_SB2(i));
}

void pfm_fltr_sb3_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_SB3(i));
}

void pfm_fltr_sb4_set(u32 i, u32 set)
{
	writel(set, PFM_FLTR_SB4(i));
}



