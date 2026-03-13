/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */

#include <all_inc.h>


extern const cmu_src_clk_t cmu_src_clk[];
extern const cmu_mod_clk_t cmu_mod_clk[];

s32 cmu_clk_set_freq(cmu_clk_id_t clk_id, u32 freq)
{
	u8 id = (u8)clk_id;
	cmu_clk_type_t clk_type = cmu_src_clk[id].clk_type;
	cmu_clk_id_t src = cmu_src_clk[id].clk_src;
	u32 reg = cmu_src_clk[id].clk_reg;
	u16 fmax = cmu_src_clk[id].clk_fmax;
	u8 para = cmu_src_clk[id].clk_para;

	switch(clk_type) {
	case CMU_CLK_TYPE_PLL:		cmu_pll_set_freq(reg, freq, fmax, para);	break;
	case CMU_CLK_TYPE_BUS:	 	cmu_bus_set_freq(reg, src, freq, fmax, para);	break;
	case CMU_CLK_TYPE_CPU:	 	cmu_cpu_set_freq(reg, src, freq, fmax, para);	break;
	case CMU_CLK_TYPE_DISP:				;				break;
	case CMU_CLK_TYPE_AUD:				;				break;
	case CMU_CLK_TYPE_PWM:	 	cmu_pwm_set_freq(reg, src, freq, fmax, para);	break;
	default:
 		return RET_FALSE;
	}

	return RET_OK;
}

u32 cmu_clk_get_freq(cmu_clk_id_t clk_id)
{
	u8 id = (u8)clk_id;
	cmu_clk_type_t clk_type = cmu_src_clk[id].clk_type;
	cmu_clk_id_t src = cmu_src_clk[id].clk_src;
	u32 reg = cmu_src_clk[id].clk_reg;
	u32 para = cmu_src_clk[id].clk_para;
	u32 freq = 0;
	if(clk_id == CMU_CLK_DIS)
		return freq;

	switch(clk_type) {
	case CMU_CLK_TYPE_OSC:		freq = reg;					break;
	case CMU_CLK_TYPE_FDIV:     freq = cmu_fdiv_get_freq(src, para);    break;
	case CMU_CLK_TYPE_PLL:		freq = cmu_pll_get_freq(reg, para);		break;
	case CMU_CLK_TYPE_BUS:		freq = cmu_bus_get_freq(reg, src);		break;
	case CMU_CLK_TYPE_CPU:		freq = cmu_cpu_get_freq(reg, src);		break;
	case CMU_CLK_TYPE_DISP:		freq = cmu_disp_get_freq(reg, src);		break;
	case CMU_CLK_TYPE_AUD:		freq = cmu_aud_get_freq(reg, src);		break;
	case CMU_CLK_TYPE_PWM:		freq = cmu_pwm_get_freq(reg, src);		break;
	default: 			freq = 0;
	}
	return freq;
}

static s32 cmu_pll_int_cint_fix(u32 reg)
{

	return RET_OK;
}

s32 cmu_pll_set_factor(u32 reg, u32 p, u32 n, u32 m, u32 fmax)
{
	cmu_pll_int_cint_fix(reg);
	cmu_pll_wrbit(0xffff, n<<8 | m<<4 | p, reg);

	return RET_OK;
}

s32 cmu_pll_set_fraction(u32 reg, u32 off_cfg, u32 off_sdm, u32 en, u32 f)
{
	if(en) {
		writel(0x1<<20 | f, reg+off_cfg);
		writel(0x7<<29, reg+off_sdm);
		cmu_pll_icp_cfg(reg, 0);
	} else {
		writel(0, reg+off_cfg);
		writel(0, reg+off_sdm);
		cmu_pll_icp_cfg(reg, 8);
	}

	return RET_OK;
}

s32 cmu_pll_set_freq(u32 reg, u32 freq, u32 fmax, u8 para)
{
	u32 clk_sel = (freq==CMU_CLK_24M_FREQ) ? 0 : 1;
	u32 clk_24m,p,m,n,f;
	u64 d;
	volatile u32 i;
	u32 off_cfg, off_sdm;

	m = 0;


	cmu_pll_out_sel_24m(reg);
	if(clk_sel==0)
		return RET_OK;


	cmu_pll_out_disable(reg);
	cmu_pll_disable(reg);
	p = (freq % (CMU_CLK_24M_FREQ/(m+1))) ? 1: 0;
	n = (freq*(m+1))/(CMU_CLK_24M_FREQ/(p+1)) - 1;
	cmu_pll_set_factor(reg, p, n, m, fmax);
	if(para) {

		off_cfg = (para & 0xf) << 3;
		off_sdm = (para & 0xf0) >> 1;

		d = (freq*(m+1))%(CMU_CLK_24M_FREQ/(p+1));
		f = d*0x1ffff/(CMU_CLK_24M_FREQ/(p+1));
		cmu_pll_set_fraction(reg, off_cfg, off_sdm, d, f);
	}
	cmu_pll_enable(reg);
	cmu_pll_wait_locked(reg);
	cmu_pll_out_enable(reg);
	cmu_pll_out_sel_pll(reg);

	return RET_OK;
}

u32 cmu_pll_get_freq(u32 reg, u8 para)
{
	u32 rval;
	u32 p,n,m;
	u32 freq;
	u64 f;
	u32 off_cfg;

	if((readl(reg) >> 20 & 1)==0)
		return CMU_CLK_24M_FREQ;

	rval = readl(reg);
	p = rval>>0 & 0x1;
	m = rval>>4 & 0x3;
	n = rval>>8 & 0xff;
	freq = CMU_CLK_24M_FREQ/(p+1)*(n+1)/(m+1);
	if(para) {

		off_cfg = (para & 0xf) << 3;

		rval = readl(reg+off_cfg);
		f = (rval>>20 & 0x1)*(rval>>0 & 0x1ffff);
		freq = CMU_CLK_24M_FREQ*(n+1+f/0x1ffff)/(p+1)/(m+1);
	}

	return freq;
}

s32 cmu_pll_wait_locked(u32 reg)
{


	cmu_delay_200us();

	return RET_OK;
}


s32 cmu_pll_set_sdm_factor(u32 reg, u32 amp, u32 freq, u32 step, u32 mode, u32 en)
{
	if(en)
		cmu_pll_icp_cfg(reg, 0);

	writel(en<<31 | mode<<29 | step<<20 | freq<<17 | amp, reg);
	return RET_OK;
}

s32 cmu_pll_set_sdm_ppm(u32 reg, u32 off, cmu_pll_sdm_t sdm, u32 ppm)
{
	u32 rval, n, p, max, bot, step, freq;

	freq = 	sdm==CMU_PLL_SDM_31500 ? 31500 :
		sdm==CMU_PLL_SDM_32000 ? 32000 :
		sdm==CMU_PLL_SDM_32500 ? 32500 : 33000;

	rval = readl(reg);
	p = rval>>0 & 0x1;
	n = rval>>8 & 0xff;

	max = 1000000/(n+1);
	bot = ppm<max ? 0x20000-(u64)ppm*0x20000/max : 0;
	step = (u64)(0x20000-bot)*2*freq/24000000;

	if(step>511)
		step = 511;

	cmu_pll_wrbit(0x1f<<24, 0x0<<24, reg);
	cmu_pll_set_sdm_factor(reg+off, bot, sdm, step, 2, 1);
	return RET_OK;
}

s32 cmu_pll_set_sdm_hz(u32 reg, u32 off, cmu_pll_sdm_t sdm, u32 hz)
{
	u32 rval, n, p, in, bot, step, freq;

	freq = 	sdm==CMU_PLL_SDM_31500 ? 31500 :
		sdm==CMU_PLL_SDM_32000 ? 32000 :
		sdm==CMU_PLL_SDM_32500 ? 32500 : 33000;

	rval = readl(reg);
	p = rval>>0 & 0x1;

	in = 24000000/(p+1);
	bot = hz<in ? 0x20000-(u64)hz*0x20000/in : 0;
	step = (u64)(0x20000-bot)*2*freq/24000000;

	if(step>511)
		step = 511;

	cmu_pll_set_sdm_factor(reg+off, bot, sdm, step, 2, 1);
	return RET_OK;
}

u32 cmu_fdiv_get_freq(cmu_clk_id_t src, u8 para)
{
	u32 freq, div;

	freq =  cmu_clk_get_freq(src);
	div = para;

	return (freq/div);
}

s32 cmu_bus_set_factor(u32 reg, cmu_clk_id_t src, u32 clk_sel, u32 div, u32 fmax, u32 dmax)
{
	u32 freq;

	if(div > dmax)
		return RET_FALSE;

	cmu_bus_clk_set_div(reg, div);

	if(clk_sel == 0)
		cmu_bus_clk_sel_24m(reg);
	else
		cmu_bus_clk_sel_pll(reg);

	return RET_OK;
}

s32 cmu_bus_set_freq(u32 reg, cmu_clk_id_t src, u32 freq, u32 fmax, u32 dmax)
{
	u32 clk_sel = (freq == CMU_CLK_24M_FREQ) ? 0 : 1;
	u32 div;

	cmu_bus_clk_sel_24m(reg);
	if(clk_sel==0)
		return RET_OK;


	div = (cmu_clk_get_freq(src)+freq/2)/freq - 1;
	if(div > dmax)
		return RET_FALSE;

	cmu_bus_clk_set_div(reg, div);
	cmu_bus_clk_sel_pll(reg);
	return RET_OK;
}

u32 cmu_bus_get_freq(u32 reg, cmu_clk_id_t src)
{
	u32 freq;
	if(cmu_bus_clk_get_sel(reg)==0)
		return CMU_CLK_24M_FREQ;

	freq = cmu_clk_get_freq(src) / (cmu_bus_clk_get_div(reg) +1);
	return freq;
}

s32 cmu_cpu_set_factor(u32 reg, cmu_clk_id_t src, u32 clk_sel, u32 div, u32 fmax, u32 dmax)
{
	u32 freq;

	cmu_cpu_clk_sel_24m(reg);
	if(clk_sel==0)
		return RET_OK;

	if(div > dmax)
		return RET_FALSE;

	cmu_cpu_clk_set_div(reg, div);
	cmu_cpu_clk_sel_pll(reg, clk_sel);
	return RET_OK;
}

s32 cmu_cpu_set_freq(u32 reg, cmu_clk_id_t src, u32 freq, u32 fmax, u32 dmax)
{
	u32 div;

	cmu_cpu_clk_sel_24m(reg);
	if(freq==CMU_CLK_24M_FREQ)
		return RET_OK;

	div = (cmu_clk_get_freq(src)+freq/2)/freq - 1;
	if(div > dmax)
		return RET_FALSE;

	cmu_cpu_clk_set_div(reg, div);
	cmu_cpu_clk_sel_pll(reg, 1);

	return RET_OK;
}

u32 cmu_cpu_get_freq(u32 reg, cmu_clk_id_t src)
{
	u32 clk_sel = cmu_cpu_clk_get_sel(reg);
	u32 rval = readl(reg);
	u32 div, freq;



	if(clk_sel==0) {
		return CMU_CLK_24M_FREQ;
	} else if(clk_sel==2) {

	} else if(clk_sel==3) {

	} else { }

	div = rval & 0x1f;
	freq = cmu_clk_get_freq(src) / (div +1);

	return freq;
}

s32 cmu_disp_sclk_set_div(u32 sel, u32 div)
{


	u32 div_n=0, temp=div+1;
	while(temp>1) {
		temp /= 2;
		div_n++;
	}
	wrbit(0x7, div_n, REG_CMU_CLK_DISP);
	return RET_OK;

}

s32 cmu_disp_pixclk_set_div(u32 sel, u32 div, u32 div_3p5)
{

	u32 div_l=0, div_m, temp=div+1, temp_div=1;
	if(div_3p5) {
		wrbit(0x1ff<<4, 0x1<<12, REG_CMU_CLK_DISP);	//div3.5
		return RET_OK;
	}
	if(div>255)
		return RET_FALSE;
	while(temp>32) {
		temp /= 2;
		div_l++;
		temp_div *=2;
	}
	div_m = (div+1) / temp_div;
	wrbit(0x1ff<<4, div_l<<10 | (div_m-1)<<4, REG_CMU_CLK_DISP);
	return RET_OK;

}

s32 cmu_disp_set_factor(u32 divn, u32 divm, u32 div3p5)
{
	u32 rval;
	rval = readl(REG_CMU_CLK_DISP);
	rval &= ~(0x1<<12 | 0x1f<<4 | 0x7);
	rval |= (div3p5<<12 | divm<<4 | divn);
	writel(rval, REG_CMU_CLK_DISP);
	return RET_OK;
}

s32 cmu_disp_set_factor_l(u32 divl)
{
	u32 rval;
	rval = readl(REG_CMU_CLK_DISP);
	rval &= ~(0x3<<10);
	rval |= (divl<<10);
	writel(rval, REG_CMU_CLK_DISP);
	return RET_OK;
}

s32 cmu_disp_set_freq(cmu_disp_id_t id,u32 freq)
{
	return RET_OK;
}

u32 cmu_disp_get_freq(u32 reg, cmu_clk_id_t src)
{

	cmu_clk_id_t id = (src==CMU_CLK_SCLK) ? CMU_CLK_PIXCLK : CMU_CLK_SCLK;
	u32 rval,l,m,n,d3p5;
	u32 pow,m2,freq;

	rval = readl(REG_CMU_CLK_DISP);
	n = (rval >> 0)  & 0x7;
	m = (rval >> 4)  & 0x1f;
	l = (rval >> 10) & 0x3;
	d3p5 = (rval >> 12) & 0x3;
	pow = 1;
	while(n>0) {pow*=2;n--;}

	freq = cmu_clk_get_freq(CMU_CLK_FRA2) / pow;

	if(id==CMU_CLK_PIXCLK) {
		pow = 1;	while(l>0) {pow*=2;l--;}
		m2 = d3p5 ? 7 : pow*(m+1)*2;
		freq = freq*2/m2;
	}

	return freq;

}

s32 cmu_aud_set_factor(u32 reg, u32 sel, u32 div, u32 fmax, u32 dmax)
{

	return RET_OK;
}

u32 cmu_aud_get_freq(u32 reg, cmu_clk_id_t src)
{

	u32 rval = readl(reg);
	u32 div = rval>>0 & 0x3f;
	u32 freq = cmu_clk_get_freq(src) / (div+1);
	return freq;


	return 0;
}

s32 cmu_pwm_set_freq(u32 reg, u32 src, u32 freq, u32 fmax, u32 dmax)
{
	u32 div;


	div = (cmu_clk_get_freq(src)+freq/2)/freq - 1;
	if(div > dmax) {
		cmu_pwm_clk_set_div(reg, dmax);
		return RET_FALSE;
	}

	cmu_pwm_clk_set_div(reg, div);
	return RET_OK;
}

u32 cmu_pwm_get_freq(u32 reg, u32 src)
{
	u32 div = readl(reg) & 0x1f;
	u32 freq;

	div = readl(reg) & 0x1f;
	freq = cmu_clk_get_freq(src)/(div+1);
	return freq;
}

s32 cmu_clkout_set_factor(u32 reg, u32 sel, u32 div, u32 dmax)
{
	cmu_clkout_clk_sel(reg, sel);
	cmu_clkout_clk_set_div(reg, cmu_min(div,dmax));
	return RET_OK;
}

s32 cmu_clkout_set_freq(u32 reg, u32 sel, u32 freq, u32 dmax)
{
	cmu_clk_id_t clk_src = 	sel==0 ? CMU_CLK_INT1 :
				sel==1 ? CMU_CLK_FRA1 :
				sel==2 ? CMU_CLK_FRA2 : CMU_CLK_INT1;
	u32 div = cmu_clk_get_freq(clk_src)/freq;

	cmu_clkout_clk_sel(reg, sel);
	cmu_clkout_clk_set_div(reg, cmu_min(div,dmax));
	return RET_OK;
}

u32 cmu_clkout_get_freq(u32 reg)
{
	u32 rval = readl(reg);
	u32 sel = rval >> 12 & 0x3;
	u32 div = rval >> 0 & 0xff;


	cmu_clk_id_t clk_src = 	sel==0 ? CMU_CLK_INT1 :
				sel==1 ? CMU_CLK_FRA1 :
				sel==2 ? CMU_CLK_FRA2 : CMU_CLK_INT1;
	u32 freq = cmu_clk_get_freq(clk_src) / (div+1);

	return freq;
}

s32 cmu_pll_test_out_factor(u32 sel, u32 div)
{
	u32 rval;
	rval = readl(REG_CMU_PLL_COM);
	rval &= ~(0xff<<4);
	rval |= sel<<8;
	rval |= div<<6;
	rval |= 0x3<<4;
	writel(rval, REG_CMU_PLL_COM);


	return RET_OK;
}

s32 cmu_pll_test_out(u32 clk_sel, u32 div)
{
	u32 rval, clk_div;


	clk_div = div>=8 ?	3 :
		  div>=4 ?	2 :
		  div>=2 ?	1 : 0;

	cmu_pll_test_out_factor(clk_sel, clk_div);



	return RET_OK;
}

s32 cmu_pll_clk_out(u32 clk_sel, u32 clkout_id, u32 clkout_div)
{
	// cmu_clkout_set_factor(clkout_id, clk_sel, clkout_div-1);
	cmu_clkout_enable(clkout_id);
	gpio_enable(GPIO_GRP_C, 6, 1, GPIO_FUN_7);
	gpio_pin_cfg(GPIO_GRP_C,6,1,GPIO_DRV_60R,GPIO_PULL_NONE);

	return RET_OK;
}

s32 cmu_mod_set_div(cmu_mod_id_t mod_id, u32 div)
{
	cmu_clk_id_t src;
	u32 id = (u32)mod_id;
	u32 reg, freq, fmax, dmax;
	s32 ret = RET_OK;

	dmax = cmu_mod_clk[id].spec_div;
	if(div > dmax)
		ret = RET_FALSE;

 	src = cmu_mod_clk[id].spec0_src;

	if(ret == RET_FALSE)
		div = dmax;
	// if(cmu_src_clk[src].clk_type == CMU_CLK_TYPE_PWM) {
	// 	reg = cmu_src_clk[src].clk_reg;
	// 	cmu_pwm_clk_set_div(reg, div);
	// } else
	//{
		reg = cmu_mod_clk[id].reg;
		if(cmu_mod_clk[id].wr_auth) {
			cmu_auth_mod_clk_set_div(reg, div);
		}
		else {
			cmu_mod_clk_set_div(reg, div);
		}

	//}
	return ret;
}

s32 cmu_mod_set_freq(cmu_mod_id_t mod_id, u32 freq)
{
	cmu_clk_id_t src;
	u32 id = (u32)mod_id;
	u32 reg, fmax, div, dmax;
	s32 ret = RET_OK;


 	src = cmu_mod_clk[id].spec0_src;
	if(src == CMU_CLK_DIS)
		ret = RET_FALSE;

	dmax = cmu_mod_clk[id].spec_div;

	div = (cmu_clk_get_freq(src)+freq/2)/freq - 1;
	if(div > dmax)
		ret = RET_FALSE;

	if(ret == RET_FALSE)
		div = dmax;

	reg = cmu_mod_clk[id].reg;
	if(cmu_mod_clk[id].wr_auth) {
		cmu_auth_mod_clk_set_div(reg, div);
	}
	else {
		cmu_mod_clk_set_div(reg, div);
	}


	return ret;
}

u32 cmu_mod_get_freq(cmu_mod_id_t mod_id)
{
	u32 id = (u32)mod_id;
	u32 reg = cmu_mod_clk[id].reg;
	cmu_clk_id_t clk_src = 	(cmu_mod_clk[id].spec0_src!=CMU_CLK_DIS) ? cmu_mod_clk[id].spec0_src :
				(cmu_mod_clk[id].axi_clk) ? CMU_CLK_AXI0 :
				(cmu_mod_clk[id].ahb_clk) ? CMU_CLK_AHB0 :

				(cmu_mod_clk[id].apb_clk==1) ? CMU_CLK_APB0 :
				(cmu_mod_clk[id].apb_clk==2) ? CMU_CLK_APB1 :

								CMU_CLK_DIS;
	u32 div = cmu_mod_clk_get_div(reg);

	return cmu_clk_get_freq(clk_src) / (div+1);
}

u32 cmu_mod_get_freq_spec0(cmu_mod_id_t mod_id)
{
	u32 id = (u32)mod_id;
	u32 reg = cmu_mod_clk[id].reg;
	cmu_clk_id_t clk_src = cmu_mod_clk[id].spec0_src;
	u32 div = cmu_mod_clk_get_div(reg);
	return cmu_clk_get_freq(clk_src) / (div+1);
}

u32 cmu_mod_get_freq_spec1(cmu_mod_id_t mod_id)
{
	u32 id = (u32)mod_id;
	u32 reg = cmu_mod_clk[id].reg;
	cmu_clk_id_t clk_src = cmu_mod_clk[id].spec1_src;
	u32 div = cmu_mod_clk_get_div(reg);
	if (clk_src == CMU_CLK_PIXCLK)		div = 0;
	return cmu_clk_get_freq(clk_src) / (div+1);
}

s32 cmu_mod_get_status(cmu_mod_id_t mod_id)
{
	u32 id = (u32)mod_id;
	u32 reg = cmu_mod_clk[id].reg;
	if(cmu_mod_clk_get_status(reg))
		return RET_OK;
	return RET_FALSE;
}

s32 cmu_mod_enable(cmu_mod_id_t mod_id)
{
	u32 id = (u32)mod_id;
	u32 reg = cmu_mod_clk[id].reg;


	if(cmu_mod_clk[id].wr_auth) {
		cmu_auth_mod_clk_enable(reg);
		cmu_auth_mod_rst_release(reg);
	} else {
		cmu_mod_clk_enable(reg);
		cmu_mod_rst_release(reg);
	}

	return RET_OK;
}

s32 cmu_mod_disable(cmu_mod_id_t mod_id)
{
	u32 id = (u32)mod_id;
	u32 reg = cmu_mod_clk[id].reg;

	if(cmu_mod_clk[id].wr_auth) {
		cmu_auth_mod_rst_hold(reg);
		cmu_auth_mod_clk_disable(reg);
	} else {
		cmu_mod_rst_hold(reg);
		cmu_mod_clk_disable(reg);
	}
	return RET_OK;
}

s32 cmu_mod_enable_clock_only(cmu_mod_id_t mod_id)
{
	u32 id = (u32)mod_id;
	u32 reg = cmu_mod_clk[id].reg;
	cmu_mod_clk_enable(reg);
	return RET_OK;
}

s32 cmu_mod_disable_clock_only(cmu_mod_id_t mod_id)
{
	u32 id = (u32)mod_id;
	u32 reg = cmu_mod_clk[id].reg;
	cmu_mod_clk_disable(reg);
	return RET_OK;
}

s32 cmu_mod_reset_release(cmu_mod_id_t mod_id)
{
	u32 id = (u32)mod_id;
	u32 reg = cmu_mod_clk[id].reg;
	cmu_mod_rst_release(reg);
	return RET_OK;
}

s32 cmu_mod_reset_hold(cmu_mod_id_t mod_id)
{
	u32 id = (u32)mod_id;
	u32 reg = cmu_mod_clk[id].reg;
	cmu_mod_rst_hold(reg);
	return RET_OK;
}
