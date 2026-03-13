/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_COMMON_CFG_H_
#define INCLUDE_COMMON_CFG_H_


typedef struct cfg_par_s {
	com_ist_t cfg_use_prt				:  1;
	com_ist_t cfg_use_cpu_perdiction		:  1;
	com_ist_t cfg_use_cpu_vfp			:  1;
	com_ist_t cfg_use_cpu_icache			:  1;
	com_ist_t cfg_use_cpu_dcache			:  1;
	com_ist_t cfg_use_cpu_mmu			:  1;
	com_ist_t cfg_use_cpu_wbcache			:  1;
	com_ist_t cfg_use_cpu_walloc			:  1;
	com_ist_t cfg_use_heap				:  1;
	com_ist_t cfg_use_irq 				:  1;
	com_ist_t cfg_use_gtc 				:  1;
	com_ist_t cfg_use_cmu 				:  1;
	com_ist_t cfg_use_dma 				:  1;
	com_ist_t cfg_use_ddr 				:  1;
	com_ist_t cfg_use_gpio				:  1;
	u32 cfg_use_res 				:  6;
	cpu_mode_t cfg_cpu_mode				:  3;
	ddr_type_t cfg_ddr_type				:  2;
	psram_type_t cfg_psram_type			:  2;
	psram_num_t cfg_psram_num			:  1;
	dma_type_t cfg_dma_type                         :  3;
	u32 cfg_freq_32k;
	u32 cfg_freq_24m;
	u32 cfg_freq_int0;
	u32 cfg_freq_int1;
	u32 cfg_freq_fra0;
	u32 cfg_freq_fra1;
	u32 cfg_freq_fra2;
	u32 cfg_freq_fra3;
	u32 cfg_freq_fra4;
	u32 cfg_freq_fra5;
	u32 cfg_freq_fra6;
	u32 cfg_freq_fra7;
	u32 cfg_freq_fra8;
	u32 cfg_freq_axi0;
	u32 cfg_freq_ahb0;
	u32 cfg_freq_apb0;
	u32 cfg_freq_apb1;
	u32 cfg_freq_apb2;
	u32 cfg_freq_cpu;
	u32 cfg_freq_sc_cpu;
	u32 cfg_freq_se_cpu;
	u32 cfg_freq_ddr2;
	u32 cfg_freq_ddr3;
	u32 cfg_freq_prcm_fra0;
	u32 cfg_freq_prcm_fra1;
	u32 cfg_freq_sp_cpu;
	u32 cfg_freq_prcm_axi;
	u32 cfg_freq_prcm_ahb0;
	u32 cfg_freq_prcm_apb0;
	u32 cfg_freq_r_int;
	u32 cfg_freq_r_axi;
	u32 cfg_freq_r_ahb0;
	u32 cfg_freq_r_apb0;
	u32 cfg_freq_res;
}cfg_par_t;

extern cfg_par_t cfg_par_def;
extern void basic_init(void);
extern s32 main(void);

#define SPICLK_SRC_RCOSC_SYS	( 100000000)
#define SPICLK_SRC_RCOSC_NDFC   ( 100000000)

#endif /* INCLUDE_COMMON_CFG_H_ */
