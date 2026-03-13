/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#include <all_inc.h>
#include "flash_drv.h"

cfg_par_t cfg_par_def __attribute__((aligned(16))) = {
	.cfg_use_prt 			=  IST_YES,
	.cfg_freq_32k				=        32*1000,
	.cfg_freq_24m				=   24*1000*1000,
	.cfg_freq_int0				=  480*1000*1000,
	.cfg_freq_int1				= 1200*1000*1000,
	.cfg_freq_fra0				= 1200*1000*1000,
	.cfg_freq_fra1				=  504*1000*1000,
	.cfg_freq_fra2				= 1188*1000*1000,
	.cfg_freq_axi0				=  240*1000*1000,
	.cfg_freq_apb0				=  120*1000*1000,
	.cfg_freq_apb1				=  24*1000*1000,
	.cfg_freq_ahb0				=  240*1000*1000,
	.cfg_freq_cpu				=  480*1000*1000,
	.cfg_freq_res				=  0,
};

static void syscfg_ldo1x_enable(void)
{
	writel(0x06, BASE_SYSCFG+0x28);
}

static void syscfg_ldo1x_disable(void)
{
	writel(0x36, BASE_SYSCFG+0x28);
	writel(0x76, BASE_SYSCFG+0x28);
	writel(0x66, BASE_SYSCFG+0x28);
	writel(0x46, BASE_SYSCFG+0x28);
}

static void syscfg_ldo18_enable(void)
{
	writel(0x07, BASE_SYSCFG+0x24);
	writel(0x17, BASE_SYSCFG+0x24);
}

static void syscfg_ldo18_disable(void)
{
	writel(0x00, BASE_SYSCFG+0x24);
}

static void sid_cali(void)
{
	u32 rval, bg_ctrl, osc24m;

	cmu_mod_enable(CMU_MOD_SYSCFG);
	cmu_mod_enable(CMU_MOD_SID);
	rval = readl(BASE_SID+0x20C);
	osc24m = rval >> 8 & 0x7f;
	bg_ctrl = rval & 0xff;

	if(bg_ctrl != 0x0)
		wrbit(0xff<<8, bg_ctrl<<8, BASE_SYSCFG+0x20);
	if(osc24m != 0x0)
		wrbit(0x7f<<8, osc24m<<8, BASE_CMU+0xa4);
}

static void osc_strength_scale(void)
{
	u32 reg_val;
	reg_val = readl(BASE_CMU+0xA4);
	reg_val &= ~(0x7<<29);
	cmu_auth_writel(reg_val, BASE_CMU+0xA4);
}

void basic_init(void)
{
//	sid_cali();
//	syscfg_ldo1x_disable();
//	syscfg_ldo1x_enable();
//	syscfg_ldo18_disable();
//	syscfg_ldo18_enable();

	cmu_clk_set_freq(CMU_CLK_CPU,  CMU_CLK_24M_FREQ);
	cmu_clk_set_freq(CMU_CLK_INT0, cfg_par_def.cfg_freq_int0);
	cmu_clk_set_freq(CMU_CLK_CPU,  cfg_par_def.cfg_freq_cpu);
	if(cmu_clk_get_freq(CMU_CLK_FRA0) == CMU_CLK_24M_FREQ)
		cmu_clk_set_freq(CMU_CLK_FRA0, cfg_par_def.cfg_freq_fra0);
	cmu_clk_set_freq(CMU_CLK_AXI0,  cfg_par_def.cfg_freq_axi0);

	osc_strength_scale();	//scale osc strength

	hal_efuse_init();
	u32 BROM_SECURE_data = 0x10; //����SD��������
	hal_efuse_write(0x1, BROM_SECURE_data);

	//Initialize gtc module
	init_gtc();

	//Initialize CPU
	init_cpu();

	//Initialize GPIO
	init_gpio();

	//Initialize DMA
	init_dma(0);

	//Initialize UART0(PA0/1) as Upgrade port
	init_uart0_upg();

#if !(defined(MCU_BOOTLOADER) || defined(MCU_UPLOADER))
	set_wri_sw_reboot_r(SW_REBOOT_R_CLR); //APP项目正常启动，清除所有标志。
	set_wri_sw_bapp_fail_times(0);
#endif
}
