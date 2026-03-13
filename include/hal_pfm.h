/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_PFM_H_
#define INCLUDE_HAL_PFM_H_

#define PFM_BASE                              BASE_PFM

#define PFM_FLTR0_STS						(0x1 << 0)
#define PFM_FLTR1_STS						(0x1 << 1)
#define PFM_FLTR2_STS						(0x1 << 2)
#define PFM_FLTR3_STS						(0x1 << 3)
#define PFM_FLTR4_STS						(0x1 << 4)
#define PFM_FLTR5_STS						(0x1 << 5)

typedef enum {
		PFM_1_ORDER    = 0,
		PFM_2_ORDER,
		PFM_3_ORDER,
		PFM_4_ORDER,
} PFM_ORDER_TYP;

//*******************************************PFM**************************************************//
#define PFM_GLB_STS 							(PFM_BASE + 0x00)           		//
#define PFM_GLB_EN								(PFM_BASE + 0x04)           		//
#define PFM_GLB_CFG								(PFM_BASE + 0x08)           		//

#define PFM_FLTR_CTL(i)                         (PFM_BASE + (0x100 * (i+1)) + 0x0)	//
#define PFM_FLTR_TRG(i)                         (PFM_BASE + (0x100 * (i+1)) + 0x4)	//
#define PFM_FLTR_SCAL(i)                        (PFM_BASE + (0x100 * (i+1)) + 0x8)	//
#define PFM_FLTR_DIN(i)                         (PFM_BASE + (0x100 * (i+1)) + 0xc)	//
#define PFM_FLTR_DOUT(i)                        (PFM_BASE + (0x100 * (i+1)) + 0x10)	//
#define PFM_FLTR_MINH(i)                        (PFM_BASE + (0x100 * (i+1)) + 0x14)	//
#define PFM_FLTR_MINL(i)                        (PFM_BASE + (0x100 * (i+1)) + 0x18)	//
#define PFM_FLTR_MAXH(i)                        (PFM_BASE + (0x100 * (i+1)) + 0x1c)	//
#define PFM_FLTR_MAXL(i)                        (PFM_BASE + (0x100 * (i+1)) + 0x20)	//
#define PFM_FLTR_FA1(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x50)	//
#define PFM_FLTR_FA2(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x54)	//
#define PFM_FLTR_FA3(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x58)	//
#define PFM_FLTR_FA4(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x5c)	//
#define PFM_FLTR_FB0(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x60)	//
#define PFM_FLTR_FB1(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x64)	//
#define PFM_FLTR_FB2(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x68)	//
#define PFM_FLTR_FB3(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x6c)	//
#define PFM_FLTR_FB4(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x70)	//
#define PFM_FLTR_SA1(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x74)	//
#define PFM_FLTR_SA2(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x78)	//
#define PFM_FLTR_SA3(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x7c)	//
#define PFM_FLTR_SA4(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x80)	//
#define PFM_FLTR_SB0(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x84)	//
#define PFM_FLTR_SB1(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x88)	//
#define PFM_FLTR_SB2(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x8C)	//
#define PFM_FLTR_SB3(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x90)	//
#define PFM_FLTR_SB4(i)                        	(PFM_BASE + (0x100 * (i+1)) + 0x94)	//

#define PFM_VER                                 (PFM_BASE + 0xFFC)

void pfm_cmu_init(void);
u32 pfm_get_dne_sts(void);
u32 pfm_get_err_sts(void);
u32 pfm_get_op_sts(void);
void pfm_dne_sts_clr(u32 clr);
void pfm_err_sts_clr(u32 clr);
void pfm_fltr_irq_en(u32 i, u32 en);
void pfm_fltr_en(u32 i, u32 en);
void pfm_fltr_odr_set(u32 i, PFM_ORDER_TYP odr);
void pfm_fltr_coeff_sel(u32 i, u32 sel);
void pfm_fltr_limit_en(u32 i, u32 en);
void pfm_fltr_scla_en(u32 i, u32 en);
void pfm_fltr_sclb_en(u32 i, u32 en);
void pfm_fltr_bpz0_en(u32 i, u32 en);
void pfm_fltr_in_src(u32 i, u32 src);
void pfm_fltr_trg_src(u32 i, u32 src);
void pfm_fltr_zin_src(u32 i, u32 src);
void pfm_fltr_yin_src(u32 i, u32 src);
void pfm_fltr_sw_trg(u32 i);
void pfm_fltr_sw_rst(u32 i);
void pfm_fltr_scla_set(u32 i, u32 set);
void pfm_fltr_sclb_set(u32 i, u32 set);
void pfm_fltr_input(u32 i, u32 input);
s32 pfm_fltr_output(u32 i);
void pfm_fltr_min_h(u32 i, u32 min_h);
void pfm_fltr_min_l(u32 i, u32 min_l);
void pfm_fltr_max_h(u32 i, u32 max_h);
void pfm_fltr_max_l(u32 i, u32 max_l);
void pfm_fltr_fa1_set(u32 i, u32 set);
void pfm_fltr_fa2_set(u32 i, u32 set);
void pfm_fltr_fa3_set(u32 i, u32 set);
void pfm_fltr_fa4_set(u32 i, u32 set);
void pfm_fltr_fb0_set(u32 i, u32 set);
void pfm_fltr_fb1_set(u32 i, u32 set);
void pfm_fltr_fb2_set(u32 i, u32 set);
void pfm_fltr_fb3_set(u32 i, u32 set);
void pfm_fltr_fb4_set(u32 i, u32 set);
void pfm_fltr_sa1_set(u32 i, u32 set);
void pfm_fltr_sa2_set(u32 i, u32 set);
void pfm_fltr_sa3_set(u32 i, u32 set);
void pfm_fltr_sa4_set(u32 i, u32 set);
void pfm_fltr_sb0_set(u32 i, u32 set);
void pfm_fltr_sb1_set(u32 i, u32 set);
void pfm_fltr_sb2_set(u32 i, u32 set);
void pfm_fltr_sb3_set(u32 i, u32 set);
void pfm_fltr_sb4_set(u32 i, u32 set);


#endif /* INCLUDE_HAL_PFM_H_ */
