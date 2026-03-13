/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_CMU_H_
#define INCLUDE_HAL_CMU_H_

#define CMU_CLK_24M_FREQ			(24000000)
#define CMU_CLK_32K_FREQ			(32000)

#define cmu_min(a, b)				((a)<(b) ? (a) : (b))

#define cmu_pll_out_sel_24m(reg)                cmu_auth_cbit(0x1<<20, reg)
#define cmu_pll_out_sel_pll(reg)                cmu_auth_sbit(0x1<<20, reg)
#define cmu_pll_out_enable(reg)                 cmu_auth_sbit(0x4<<16, reg)
#define cmu_pll_out_disable(reg)                cmu_auth_cbit(0x4<<16, reg)
#define cmu_pll_enable(reg)                     cmu_auth_sbit(0x9<<16, reg)
#define cmu_pll_disable(reg)                    cmu_auth_cbit(0x9<<16, reg)
#define cmu_pll_icp_cfg(reg, icp)               cmu_auth_wrbit(0x1f<<24, icp<<24, reg)
#define cmu_pll_wrbit(m, v, reg)		cmu_auth_wrbit(m, v, reg)

#define CMU_REG_WR_AUTH(reg)			writel(0xA1C00000 | (reg & 0xfff), (reg & 0xfffff000) | 0xFE8)
#define CMU_REG_WR_DIS(reg)			writel(0xD1500000 | (reg & 0xfff), (reg & 0xfffff000) | 0xFE8)
#define cmu_auth_writel(val, reg)	        {CMU_REG_WR_AUTH(reg); writel(val, reg);}
#define cmu_auth_wrbit(msk, val, reg)	        {CMU_REG_WR_AUTH(reg); wrbit(msk, val, reg);}
#define cmu_auth_sbit(val, reg)		        {CMU_REG_WR_AUTH(reg); sbit(val, reg);}
#define cmu_auth_cbit(val, reg)		        {CMU_REG_WR_AUTH(reg); cbit(val, reg);}
#define cmu_bus_clk_sel_24m(reg)		cbit(0x1<<12, reg)
#define cmu_bus_clk_sel_pll(reg)		sbit(0x1<<12, reg)
#define cmu_bus_clk_set_div(reg, div)		wrbit(0x1f, div, reg)
#define cmu_bus_clk_get_sel(reg)		(readl(reg)>>12 & 0x1)
#define cmu_bus_clk_get_div(reg)		(readl(reg) & 0x1f)
#define cmu_clkout_enable(reg)			sbit(0x3<<16, reg)
#define cmu_clkout_disable(reg)			cbit(0x3<<16, reg)
#define cmu_clkout_clk_set_div(reg, div)	wrbit(0xff, div, reg)
#define cmu_clkout_clk_sel(reg, sel)		wrbit(0x3<<12, sel<<12, reg)
#define cmu_cpu_clk_sel_24m(reg)		cmu_auth_wrbit(0xf<<12, 0x0<<12, reg)
#define cmu_cpu_clk_sel_pll(reg, sel)		cmu_auth_wrbit(0xf<<12, sel<<12, reg)
#define cmu_cpu_clk_set_div(reg, div)		cmu_auth_wrbit(0x3f<<0, div<<0, reg)
#define cmu_cpu_set_entry(reg, entry)		writel(entry, reg)
#define cmu_cpu_clk_enable(reg) 		cmu_auth_sbit(0xff<<16, (reg))
#define cmu_cpu_clk_disable(reg)		cmu_auth_cbit(0xff<<16, (reg))
#define cmu_cpu_rst_enable(reg) 		cmu_auth_sbit(0xff<<24, (reg))
#define cmu_cpu_rst_disable(reg)		cmu_auth_cbit(0xff<<24, (reg))
#define cmu_cpu_enable(reg)			cmu_auth_sbit(0x103<<16, (reg))
#define cmu_cpu_disable(reg)			cmu_auth_cbit(0x103<<16, (reg))
#define cmu_cpu_clk_get_sel(reg)		(readl(reg)>>12 & 0xf)
#define cmu_ddr_clk_enable(void)		cmu_auth_sbit(0xffff<<16, REG_CMU_CLK_DDR_CTRL)
#define cmu_ddr_clk_disable(div)		cmu_auth_cbit(0xffff<<16, REG_CMU_CLK_DDR_CTRL)
#define cmu_ddr_clk_set_div(div)		cmu_auth_wrbit(0x3f<<0, div<<0, REG_CMU_CLK_DDR_CTRL)
#define cmu_pwm_clk_set_div(reg, div)		wrbit(0x1f, div, reg)
#define cmu_mod_clk_set_div(reg, div)		wrbit(0xff, div, reg)
#define cmu_mod_clk_sel_src(reg, src)		wrbit(0xf<<12, src<<12, reg)
#define cmu_mod_clk_get_div(reg)		(readl(reg) & 0x3f)
#define cmu_mod_clk_get_status(reg)		(readl(reg) & 0xffff<<16)
#define cmu_mod_clk_enable(reg) 		sbit(0xff<<16, reg)
#define cmu_mod_clk_disable(reg)		cbit(0xff<<16, reg)
#define cmu_mod_rst_release(reg)		sbit(0xff<<24, reg)
#define cmu_mod_rst_hold(reg)			cbit(0xff<<24, reg)
#define cmu_auth_mod_clk_enable(reg) 		cmu_auth_sbit(0xff<<16, reg)
#define cmu_auth_mod_clk_disable(reg)		cmu_auth_cbit(0xff<<16, reg)
#define cmu_auth_mod_rst_release(reg)		cmu_auth_sbit(0xff<<24, reg)
#define cmu_auth_mod_rst_hold(reg)		cmu_auth_cbit(0xff<<24, reg)
#define cmu_auth_mod_clk_set_div(reg, div)	cmu_auth_wrbit(0xff, div, reg)
#define cmu_auth_mod_clk_sel_src(reg, src)	cmu_auth_wrbit(0xf<<12, src<<12, reg)

static inline void cpu_wrbit(u32 cbits, u32 sbits, u32 reg)
{
	u32 rval;
	rval = readl(reg);
	rval &= ~cbits;
	rval |= sbits;
	rval |= 0xAC<<24;
	writel(rval, reg);
}


#define cmu_delay_200us() {volatile u32 i; for(i=0;i<200;i++);}

typedef enum cmu_clk_type_e {
	CMU_CLK_TYPE_OSC		= 0,
	CMU_CLK_TYPE_PLL		,
	CMU_CLK_TYPE_BUS		,
	CMU_CLK_TYPE_CPU		,
	CMU_CLK_TYPE_DISP		,
	CMU_CLK_TYPE_AUD		,
	CMU_CLK_TYPE_PWM		,
	CMU_CLK_TYPE_FDIV		,
}cmu_clk_type_t;

typedef struct cmu_src_clk_s {
	u32 		clk_reg		: 32;
	cmu_clk_type_t	clk_type	:  8;
	u32		clk_para	:  8;
	cmu_clk_id_t	clk_src		:  5;
	u32	        clk_fmax   	: 11;
}cmu_src_clk_t;


typedef struct cmu_mod_clk_s {
	u32		reg		: 32;
	u32		wr_auth		:  1;
	u32		mod_rstn	:  1;
	u32		ahb_clk		:  3;
	u32		apb_clk		:  3;
	u32		axi_clk		:  3;
	cmu_clk_id_t  	spec0_src 	:  5;
	cmu_clk_id_t  	spec1_src 	:  5;
	u32	 	spec_div	:  8;
	u32		res		: 23;
	u32	        spec_fmax   	: 12;
}cmu_mod_clk_t;


typedef enum cmu_pll_sdm_e {
	CMU_PLL_SDM_31500 		=   0,
	CMU_PLL_SDM_32000		=   1,
	CMU_PLL_SDM_32500		=   2,
	CMU_PLL_SDM_33000		=   3,
}cmu_pll_sdm_t;

typedef enum cmu_disp_id_e {
	DISP_SCLK			=   0,
	DISP_PIXCLK	 		=   1,
}cmu_disp_id_t;

s32 cmu_clk_set_freq(cmu_clk_id_t clk_id, u32 freq);
u32 cmu_clk_get_freq(cmu_clk_id_t clk_id);
s32 cmu_pll_set_factor(u32 reg, u32 p, u32 n, u32 m, u32 fmax);
s32 cmu_pll_set_fraction(u32 reg, u32 off_cfg, u32 off_sdm, u32 en, u32 f);
s32 cmu_pll_set_freq(u32 reg, u32 freq, u32 fmax, u8 para);
u32 cmu_pll_get_freq(u32 reg, u8 para);
s32 cmu_pll_wait_locked(u32 reg);
s32 cmu_pll_set_sdm_factor(u32 reg, u32 amp, u32 freq, u32 step, u32 mode, u32 en);
s32 cmu_pll_set_sdm_ppm(u32 reg, u32 off, cmu_pll_sdm_t sdm, u32 ppm);
s32 cmu_pll_set_sdm_hz(u32 reg, u32 off, cmu_pll_sdm_t sdm, u32 hz);
u32 cmu_fdiv_get_freq(cmu_clk_id_t src, u8 para);
s32 cmu_bus_set_factor(u32 reg, cmu_clk_id_t src, u32 clk_sel, u32 div, u32 fmax, u32 dmax);
s32 cmu_bus_set_freq(u32 reg, cmu_clk_id_t src, u32 freq, u32 fmax, u32 dmax);
u32 cmu_bus_get_freq(u32 reg, cmu_clk_id_t src);
s32 cmu_cpu_set_factor(u32 reg, cmu_clk_id_t src, u32 clk_sel, u32 div, u32 fmax, u32 dmax);
s32 cmu_cpu_set_freq(u32 reg, cmu_clk_id_t src, u32 freq, u32 fmax, u32 dmax);
u32 cmu_cpu_get_freq(u32 src, u32 reg);
s32 cmu_ddr_set_freq(u32 freq);
u32 cmu_ddr_get_freq(void);
s32 cmu_disp_set_factor(u32 divn, u32 divm, u32 div3p5);
s32 cmu_disp_set_factor_l(u32 divl);
s32 cmu_disp_set_freq(cmu_disp_id_t id,u32 freq);
u32 cmu_disp_get_freq(u32 reg, cmu_clk_id_t src);
s32 cmu_disp_sclk_set_div(u32 sel, u32 div);
s32 cmu_disp_pixclk_set_div(u32 sel, u32 div, u32 div_3p5);
s32 cmu_aud_set_factor(u32 reg, u32 sel, u32 div, u32 fmax, u32 dmax);
u32 cmu_aud_get_freq(u32 reg, cmu_clk_id_t src);
s32 cmu_pwm_set_freq(u32 reg, u32 src, u32 freq, u32 fmax, u32 dmax);
u32 cmu_pwm_get_freq(u32 reg, u32 src);
s32 cmu_clkout_set_factor(u32 reg, u32 sel, u32 div, u32 dmax);
s32 cmu_clkout_set_freq(u32 reg, u32 sel, u32 freq, u32 dmax);
u32 cmu_clkout_get_freq(u32 reg);
s32 cmu_pll_test_out_factor(u32 sel, u32 div);
s32 cmu_pll_test_out(u32 clk_sel, u32 div);
s32 cmu_pll_clk_out(u32 clk_sel, u32 clkout_id, u32 clkout_div);
s32 cmu_mod_sel_src(cmu_mod_id_t id, u32 src);
s32 cmu_mod_set_div(cmu_mod_id_t id, u32 div);
s32 cmu_mod_set_freq(cmu_mod_id_t id, u32 freq);
u32 cmu_mod_get_freq(cmu_mod_id_t id);
u32 cmu_mod_get_freq_spec0(cmu_mod_id_t id);
u32 cmu_mod_get_freq_spec1(cmu_mod_id_t id);
s32 cmu_mod_get_status(cmu_mod_id_t id);
s32 cmu_mod_enable(cmu_mod_id_t id);
s32 cmu_mod_disable(cmu_mod_id_t id);
s32 cmu_mod_enable_clock_only(cmu_mod_id_t id);
s32 cmu_mod_disable_clock_only(cmu_mod_id_t id);
s32 cmu_mod_reset_release(cmu_mod_id_t mod_id);
s32 cmu_mod_reset_hold(cmu_mod_id_t mod_id);

#define CMU_REG_BIT_MOD_CLK_DIV	(0xff)
#define CMU_REG_BIT_MOD_CLK_EN	(0xf<<16)
#define CMU_REG_BIT_APB_CLK_EN	(1<<20)
#define CMU_REG_BIT_AHB_CLK_EN	(1<<21)
#define CMU_REG_BIT_AXI_CLK_EN	(1<<22)
#define CMU_REG_BIT_MOD_RSTN	(1<<24)
#define CMU_REG_BIT_APB_RSTN	(1<<25)
#define CMU_REG_BIT_AHB_RSTN	(1<<26)
#define CMU_REG_BIT_AXI_RSTN	(1<<27)

#endif /* INCLUDE_HAL_CMU_H_ */
