/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 * hal_pga.c
 *
 */


#include <all_inc.h>

pga_reg_t* const pga_reg_p = (pga_reg_t*)BASE_PGA;

void pga_cmu_init(void)
{
	cmu_mod_disable(CMU_MOD_PGA);
	gtc_dly_time(1,1);
	cmu_mod_enable(CMU_MOD_PGA);
}

void pga_en(u32 n, u32 en)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_CTL.bit.PGA_EN = en;
		break;
	case 1:
		pga_reg_p->PGA1_CTL.bit.PGA_EN = en;
		break;
	case 2:
		pga_reg_p->PGA2_CTL.bit.PGA_EN = en;
		break;
	case 3:
		pga_reg_p->PGA3_CTL.bit.PGA_EN = en;
		break;
	default:
		break;
	}

}

void pga_inp_en(u32 n, u32 en)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_CTL.bit.PGA_INP_EN = en;
		break;
	case 1:
		pga_reg_p->PGA1_CTL.bit.PGA_INP_EN = en;
		break;
	case 2:
		pga_reg_p->PGA2_CTL.bit.PGA_INP_EN = en;
		break;
	case 3:
		pga_reg_p->PGA3_CTL.bit.PGA_INP_EN = en;
		break;
	default:
		break;
	}
}

void pga_inn_en(u32 n, u32 en)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_CTL.bit.PGA_INN_EN = en;
		break;
	case 1:
		pga_reg_p->PGA1_CTL.bit.PGA_INN_EN = en;
		break;
	case 2:
		pga_reg_p->PGA2_CTL.bit.PGA_INN_EN = en;
		break;
	case 3:
		pga_reg_p->PGA3_CTL.bit.PGA_INN_EN = en;
		break;
	default:
		break;
	}
}

void pga_inres_en(u32 n, u32 en)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_CTL.bit.PGA_IN_RES_EN = en;
		break;
	case 1:
		pga_reg_p->PGA1_CTL.bit.PGA_IN_RES_EN = en;
		break;
	case 2:
		pga_reg_p->PGA2_CTL.bit.PGA_IN_RES_EN = en;
		break;
	case 3:
		pga_reg_p->PGA3_CTL.bit.PGA_IN_RES_EN = en;
		break;
	default:
		break;
	}
}

void pga_r1_en(u32 n, u32 en)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_CTL.bit.PGA_R1_EN = en;
		break;
	case 1:
		pga_reg_p->PGA1_CTL.bit.PGA_R1_EN = en;
		break;
	case 2:
		pga_reg_p->PGA2_CTL.bit.PGA_R1_EN = en;
		break;
	case 3:
		pga_reg_p->PGA3_CTL.bit.PGA_R1_EN = en;
		break;
	default:
		break;
	}
}

void pga_r2_en(u32 n, u32 en)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_CTL.bit.PGA_R2_EN = en;
		break;
	case 1:
		pga_reg_p->PGA1_CTL.bit.PGA_R2_EN = en;
		break;
	case 2:
		pga_reg_p->PGA2_CTL.bit.PGA_R2_EN = en;
		break;
	case 3:
		pga_reg_p->PGA3_CTL.bit.PGA_R2_EN = en;
		break;
	default:
		break;
	}
}

void pga_r4_en(u32 n, u32 en)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_CTL.bit.PGA_R4_EN = en;
		break;
	case 1:
		pga_reg_p->PGA1_CTL.bit.PGA_R4_EN = en;
		break;
	case 2:
		pga_reg_p->PGA2_CTL.bit.PGA_R4_EN = en;
		break;
	case 3:
		pga_reg_p->PGA3_CTL.bit.PGA_R4_EN = en;
		break;
	default:
		break;
	}
}

void pga_flt_en(u32 n, u32 en)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_CTL.bit.PGA_FLT_EN = en;
		break;
	case 1:
		pga_reg_p->PGA1_CTL.bit.PGA_FLT_EN = en;
		break;
	case 2:
		pga_reg_p->PGA2_CTL.bit.PGA_FLT_EN = en;
		break;
	case 3:
		pga_reg_p->PGA3_CTL.bit.PGA_FLT_EN = en;
		break;
	default:
		break;
	}
}

void pga_opmod_sel(u32 n, u32 sel)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_CTL.bit.PGA_OP_MOD = sel;
		break;
	case 1:
		pga_reg_p->PGA1_CTL.bit.PGA_OP_MOD = sel;
		break;
	case 2:
		pga_reg_p->PGA2_CTL.bit.PGA_OP_MOD = sel;
		break;
	case 3:
		pga_reg_p->PGA3_CTL.bit.PGA_OP_MOD = sel;
		break;
	default:
		break;
	}
}

void pga_vcm_en(u32 n, u32 en)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_CTL.bit.PGA_VCM_EN = en;
		break;
	case 1:
		pga_reg_p->PGA1_CTL.bit.PGA_VCM_EN = en;
		break;
	case 2:
		pga_reg_p->PGA2_CTL.bit.PGA_VCM_EN = en;
		break;
	case 3:
		pga_reg_p->PGA3_CTL.bit.PGA_VCM_EN = en;
		break;
	default:
		break;
	}
}

void pga_ncal_set(u32 n, u32 set)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_CTL.bit.PGA_N_CAL = set;
		break;
	case 1:
		pga_reg_p->PGA1_CTL.bit.PGA_N_CAL = set;
		break;
	case 2:
		pga_reg_p->PGA2_CTL.bit.PGA_N_CAL = set;
		break;
	case 3:
		pga_reg_p->PGA3_CTL.bit.PGA_N_CAL = set;
		break;
	default:
		break;
	}
}

void pga_pcal_set(u32 n, u32 set)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_CTL.bit.PGA_P_CAL = set;
		break;
	case 1:
		pga_reg_p->PGA1_CTL.bit.PGA_P_CAL = set;
		break;
	case 2:
		pga_reg_p->PGA2_CTL.bit.PGA_P_CAL = set;
		break;
	case 3:
		pga_reg_p->PGA3_CTL.bit.PGA_P_CAL = set;
		break;
	default:
		break;
	}
}

void pga_r1_set(u32 n, u32 set)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_RES_SET.bit.PGA_R1_SET = set;
		break;
	case 1:
		pga_reg_p->PGA1_RES_SET.bit.PGA_R1_SET = set;
		break;
	case 2:
		pga_reg_p->PGA2_RES_SET.bit.PGA_R1_SET = set;
		break;
	case 3:
		pga_reg_p->PGA3_RES_SET.bit.PGA_R1_SET = set;
		break;
	default:
		break;
	}
}

void pga_r2_set(u32 n, u32 set)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_RES_SET.bit.PGA_R2_SET = set;
		break;
	case 1:
		pga_reg_p->PGA1_RES_SET.bit.PGA_R2_SET = set;
		break;
	case 2:
		pga_reg_p->PGA2_RES_SET.bit.PGA_R2_SET = set;
		break;
	case 3:
		pga_reg_p->PGA3_RES_SET.bit.PGA_R2_SET = set;
		break;
	default:
		break;
	}
}

void pga_r3_set(u32 n, u32 set)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_RES_SET.bit.PGA_R3_SET = set;
		break;
	case 1:
		pga_reg_p->PGA1_RES_SET.bit.PGA_R3_SET = set;
		break;
	case 2:
		pga_reg_p->PGA2_RES_SET.bit.PGA_R3_SET = set;
		break;
	case 3:
		pga_reg_p->PGA3_RES_SET.bit.PGA_R3_SET = set;
		break;
	default:
		break;
	}
}

void pga_r4_set(u32 n, u32 set)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_RES_SET.bit.PGA_R4_SET = set;
		break;
	case 1:
		pga_reg_p->PGA1_RES_SET.bit.PGA_R4_SET = set;
		break;
	case 2:
		pga_reg_p->PGA2_RES_SET.bit.PGA_R4_SET = set;
		break;
	case 3:
		pga_reg_p->PGA3_RES_SET.bit.PGA_R4_SET = set;
		break;
	default:
		break;
	}
}

void pga_rflt_set(u32 n, u32 set)
{
	switch(n) {
	case 0:
		pga_reg_p->PGA0_RES_SET.bit.PGA_RFLT_SET = set;
		break;
	case 1:
		pga_reg_p->PGA1_RES_SET.bit.PGA_RFLT_SET = set;
		break;
	case 2:
		pga_reg_p->PGA2_RES_SET.bit.PGA_RFLT_SET = set;
		break;
	case 3:
		pga_reg_p->PGA3_RES_SET.bit.PGA_RFLT_SET = set;
		break;
	default:
		break;
	}
}

