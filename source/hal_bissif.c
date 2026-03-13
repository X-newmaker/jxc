/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 */
/*
 * hal_bissif.c
 */

#include <all_inc.h>
volatile struct BISSIF_REGS Bissif0Regs __attribute__((__section__(".bissif0reg")));
volatile struct BISSIF_REGS Bissif1Regs __attribute__((__section__(".bissif1reg")));

volatile struct BISSIF_REGS *BISSIF[] = {&Bissif0Regs, &Bissif1Regs};

static void bissif0_null(void){};
static void bissif1_null(void){};
cpu_irq_fun_t bissif0_irqhandle = bissif0_null;
cpu_irq_fun_t bissif1_irqhandle = bissif1_null;

ATTRIBUTE_ISR void BISSIF0_IRQHandler(void)
{
        bissif0_irq_handler();
}

void bissif0_irq_handler(void)
{
        bissif0_irqhandle();
}

void bissif0_irq_register(cpu_irq_fun_t irqhandle)
{
        bissif0_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_BISS0_IF);
}

void bissif0_irq_unregister(void)
{
        bissif0_irqhandle = bissif0_null;
        cpu_irq_disable(CPU_IRQ_BISS0_IF);
}

ATTRIBUTE_ISR void BISSIF1_IRQHandler(void)
{
        bissif1_irq_handler();
}

void bissif1_irq_handler(void)
{
        bissif1_irqhandle();
}

void bissif1_irq_register(cpu_irq_fun_t irqhandle)
{
        bissif1_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_BISS1_IF);
}

void bissif1_irq_unregister(void)
{
        bissif1_irqhandle = bissif1_null;
        cpu_irq_disable(CPU_IRQ_BISS1_IF);
}

void biss_cmu_init(void)
{
        cmu_mod_disable(CMU_MOD_BISS_IF);
        cmu_mod_set_freq(CMU_MOD_BISS_IF, 240*1000*1000);
        cmu_mod_enable(CMU_MOD_BISS_IF);
}

void biss_syscfg_sel(u8 n)
{
        switch (n) {
                case 0:
                        writel(0x3, 0x180001F4);
                        break;
                case 1:
                        writel(0x30000, 0x180001F4);
                        break;

                default:
                break;
        }
}

void biss_stf(u8 n)
{
	(*BISSIF[n]).BISS_STF.bit.STF = 0x1;
}

void biss_reset(u8 n)
{
	(*BISSIF[n]).BISS_STF.bit.fsm_rst = 0x1;
}

void biss_cdm_set(u8 n,u32 cdm)
{
	(*BISSIF[n]).BISS_STF.bit.cdm = cdm;
}

void biss_cpoly(u8 n, u32 poly)
{
	(*BISSIF[n]).BISS_CPOLY.bit.cpoly = poly;
}

void biss_crcinit(u8 n, u32 init)
{
	(*BISSIF[n]).BISS_CPOLY.bit.crcinit = init;
}

void biss_d0_size(u8 n,u32 size)
{
	(*BISSIF[n]).BISS_SIZE.bit.d0size = size;
}
void biss_d1_size(u8 n,u32 size)
{
	(*BISSIF[n]).BISS_SIZE.bit.d1size = size;
}
void biss_d2_size(u8 n,u32 size)
{
	(*BISSIF[n]).BISS_SIZE.bit.d2size = size;
}

void biss_crc_size(u8 n,u32 size)
{
	(*BISSIF[n]).BISS_SIZE.bit.crcsize = size;
}

void biss_mode(u8 n, BISS_TYPE type)
{
	(*BISSIF[n]).BISS_MODE.bit.biss_ssi_sel = type;
}

void biss_hw_tirg_en(u8 n)
{
	(*BISSIF[n]).BISS_MODE.bit.hw_trg_en = 0x1;
}

void biss_hw_tirg_dis(u8 n)
{
	(*BISSIF[n]).BISS_MODE.bit.hw_trg_en = 0x0;
}

void biss_abs_en(u8 n)
{
	(*BISSIF[n]).BISS_MODE.bit.dec_abs_data_en = 0x1;
}
void biss_abm_en(u8 n)
{
	(*BISSIF[n]).BISS_MODE.bit.dec_abm_data_en = 0x1;
}
void biss_abs_sel(u8 n,BISS_DEC_DATA data)
{
	(*BISSIF[n]).BISS_MODE.bit.dec_abs_data_sel = data;
}
void biss_abm_sel(u8 n,BISS_DEC_DATA data)
{
	(*BISSIF[n]).BISS_MODE.bit.dec_abm_data_sel = data;
}

void biss_br(u8 n, BISS_BR_TYPE baud)
{
	(*BISSIF[n]).BISS_BR.bit.br = baud;
}

/*
 * 根据biss的cmu时钟配置，
 * 触发看门狗中断的时间配置
 *	 240 * 100 * 100
 * */
void biss_wgd_timer(u32 num, u32 tick_num)
{
	(*BISSIF[num]).BISS_WDOG.all = tick_num;
}

/*使能BISS看门狗中断*/
void biss_wgd_int_en(u32 num)
{
	(*BISSIF[num]).BISS_IRQ_EN.bit.wodog_irq_en = 0x1;
}

void biss_wgd_clr_int(u32 num)
{
	(*BISSIF[num]).BISS_IRQ_STS.bit.wodog_irq = 0x1;
}

void biss_end_int_en(u32 num)
{
	(*BISSIF[num]).BISS_IRQ_EN.bit.end_irq_en = 0x1;
}

void biss_end_clr_int(u32 num)
{
	(*BISSIF[num]).BISS_IRQ_STS.bit.end_irq = 0x1;
}

void biss_hw_exit_int_en(u32 num)
{
	(*BISSIF[num]).BISS_IRQ_EN.bit.hw_trig_exit_irq_en = 0x1;
}

void biss_hw_exit_clr_int(u32 num)
{
	(*BISSIF[num]).BISS_IRQ_STS.bit.hw_trig_exit = 0x1;
}


// 12 * time * tsys_clk
void biss_tr_timing(u8 n,u32 time)
{
	(*BISSIF[n]).BISS_TR.bit.tr = time;
}

void biss_tcal_timing(u8 n,u32 time)
{
	(*BISSIF[n]).BISS_TCAL.bit.tcal = time;
}
void biss_tcdm_timing(u8 n,u32 time)
{
	(*BISSIF[n]).BISS_TCDM.bit.tcdm = time;
}
void ssi_grey_en(u8 n,u8 enable)
{
	(*BISSIF[n]).BISS_MODE.bit.ssi_grey_en = enable;
}

void biss_set_bclk(u8 n,u32 bclk_prd)
{
	(*BISSIF[n]).BISS_TDLY.bit.bclk_prd_en = 0x1;
	(*BISSIF[n]).BISS_TDLY.bit.bclk_prd = bclk_prd;
}

void biss_set_tdly(u8 n,u32 tdly)
{
	(*BISSIF[n]).BISS_TDLY.bit.tdly_en = 0x1;
	(*BISSIF[n]).BISS_TDLY.bit.tdly = tdly;
}

u32 biss_get_status(u8 n)
{
	u32 status;
	status = (*BISSIF[n]).BISS_STATUS.all;
	return status;
}
u32 biss_get_rx_data0(u8 n)
{
	u32 rxdata0;
	rxdata0 = (*BISSIF[n]).BISS_RXD0.all;
	return rxdata0;
}
u32 biss_get_rx_data1(u8 n)
{
	u32 rxdata1;
	rxdata1 = (*BISSIF[n]).BISS_RXD1.all;
	return rxdata1;
}
u32 biss_get_rx_data2(u8 n)
{
	u32 rxdata2;
	rxdata2 = (*BISSIF[n]).BISS_RXD2.all;
	return rxdata2;
}

u32 biss_get_rx_crc(u8 n)
{
	u32 crcdata;
	crcdata = (*BISSIF[n]).BISS_RXD_OTH.bit.CRC;
	return crcdata;
}

u32 biss_get_irq_status(u8 n)
{
	u32 status;
	status = (*BISSIF[n]).BISS_IRQ_STS.all;
	return status;
}

u32 biss_get_abs(u8 n)
{
	u32 abs_data;
	abs_data = (*BISSIF[n]).BISS_DEC_ABS.all;
	return abs_data;
}
u32 biss_get_abm(u8 n)
{
	u32 abm_data;
	abm_data = (*BISSIF[n]).BISS_DEC_ABM.all;
	return abm_data;
}

