/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 */
/*
 * hal_endatif.c
 */

#include <all_inc.h>
volatile struct ENDATIF_REGS Endatif0Regs __attribute__((__section__(".edtif0reg")));
volatile struct ENDATIF_REGS Endatif1Regs __attribute__((__section__(".edtif1reg")));

volatile struct ENDATIF_REGS *ENDATIF[] = {&Endatif0Regs, &Endatif1Regs};

static void edtif0_null(void){};
static void edtif1_null(void){};
cpu_irq_fun_t edtif0_irqhandle = edtif0_null;
cpu_irq_fun_t edtif1_irqhandle = edtif1_null;

ATTRIBUTE_ISR void EDTIF0_IRQHandler(void)
{
        edtif0_irq_handler();
}

void edtif0_irq_handler(void)
{
        edtif0_irqhandle();
}

void edtif0_irq_register(cpu_irq_fun_t irqhandle)
{
        edtif0_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_EDT0_IF);
}

void edtif0_irq_unregister(void)
{
        edtif0_irqhandle = edtif0_null;
        cpu_irq_disable(CPU_IRQ_EDT0_IF);
}

ATTRIBUTE_ISR void EDTIF1_IRQHandler(void)
{
        edtif1_irq_handler();
}

void edtif1_irq_handler(void)
{
        edtif1_irqhandle();
}

void edtif1_irq_register(cpu_irq_fun_t irqhandle)
{
        edtif1_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_EDT1_IF);
}

void edtif1_irq_unregister(void)
{
        edtif1_irqhandle = edtif1_null;
        cpu_irq_disable(CPU_IRQ_EDT1_IF);
}
void endat_cmu_init(void)
{
        cmu_mod_disable(CMU_MOD_EDT_IF);
        cmu_mod_set_freq(CMU_MOD_EDT_IF, 240*1000*1000);
        cmu_mod_enable(CMU_MOD_EDT_IF);
}

void endat_syscfg_sel(u8 n)
{
        switch (n) {
                case 0:
                        writel(0x1, 0x180001F4);
                        break;
                case 1:
                        writel(0x10000, 0x180001F4);
                        break;

                default:
                break;
        }
}

void edt_strb(u8 n)
{
	(*ENDATIF[n]).ENDAT_STRB.bit.strb = 0x1;
}

void edt_rst(u8 n)
{
	(*ENDATIF[n]).ENDAT_STRB.bit.fsm_rst = 0x1;
}

void edt_hw_trig_en(u8 n)
{
	(*ENDATIF[n]).ENDAT_CFG1.bit.hw_trig_en = 0x1;
}

void edt_hw_trig_dis(u8 n)
{
	(*ENDATIF[n]).ENDAT_CFG1.bit.hw_trig_en = 0x0;
}

void edt_tx_type(u8 n,EDT_TX_TYPE type)
{
	(*ENDATIF[n]).ENDAT_CFG1.bit.tx_type = type;
}

void edt_rx_type(u8 n,EDT_RX_TYPE type)
{
	(*ENDATIF[n]).ENDAT_CFG1.bit.rx_type = type;
}

void edt_rx_err_bit(u8 n,EDT_RX_ERR_WIDTH width)
{
	(*ENDATIF[n]).ENDAT_CFG1.bit.rx_err_width = width;
}

void edt_tx_cfg(u8 n, u32 data, u32 mrs, u32 mode)
{
	(*ENDATIF[n]).ENDAT_TX.bit.data = data;
	(*ENDATIF[n]).ENDAT_TX.bit.mrs = mrs;
	(*ENDATIF[n]).ENDAT_TX.bit.mode = mode;
}

void edt_clk_cfg(u8 n, EDT_CLOCK_FRE clk)
{
	(*ENDATIF[n]).ENDAT_CFG1.bit.FTclk = clk;
}

void edt_tm_time(u8 n, u32 time)
{
	(*ENDATIF[n]).ENDAT_TR.bit.tm = time;
}

void edt_tst_time(u8 n, u32 time)
{
	(*ENDATIF[n]).ENDAT_TST.bit.tst = time;
}

void edt_rx_data_size(u8 n, u32 size)
{
	(*ENDATIF[n]).ENDAT_CFG1.bit.DWL = size;
}

void edt_abs_pos_set(u8 n, u32 startbit, u32 size)
{
	(*ENDATIF[n]).ENDAT_DEC_CFG.bit.dec_abs_data_en = 0x1;
	(*ENDATIF[n]).ENDAT_DEC_CFG.bit.abs_dec_st_bit = startbit;
	(*ENDATIF[n]).ENDAT_DEC_CFG.bit.abs_dec_bit_num = size;
}

void edt_abm_pos_set(u8 n, u32 startbit, u32 size)
{
	(*ENDATIF[n]).ENDAT_DEC_CFG.bit.dec_abm_data_en = 0x1;
	(*ENDATIF[n]).ENDAT_DEC_CFG.bit.abm_dec_st_bit = startbit;
	(*ENDATIF[n]).ENDAT_DEC_CFG.bit.abm_dec_bit_num = size;
}

void edt_ainf1_rx_en(u8 n,EDT_EN en)
{
	(*ENDATIF[n]).ENDAT_CFG1.bit.ainf1_rx_en = en;
}

void edt_ainf2_rx_en(u8 n,EDT_EN en)
{
	(*ENDATIF[n]).ENDAT_CFG1.bit.ainf2_rx_en = en;
}

u32 edt_get_rxend(u8 n)
{
	return (*ENDATIF[n]).ENDAT_STAT.bit.rxend;
}

u32 edt_get_recv1l(u8 n)
{
	return (*ENDATIF[n]).ENDAT_RECV1L.all;
}
u32 edt_get_recv1u(u8 n)
{
	return (*ENDATIF[n]).ENDAT_RECV1U.all;
}
u32 edt_get_crc1(u8 n)
{
	return (*ENDATIF[n]).ENDAT_RXDAT_STAT.bit.crc1;
}

void edt_stat_clr(u8 n)
{
	(*ENDATIF[n]).ENDAT_STAT.bit.rxend = 0x1;
}

//使能看门狗，配置时间
void edt_wdg_timer(u8 n, u32 tick_num)
{
	(*ENDATIF[n]).ENDAT_CFG3.wdg_en = 0x1;
	(*ENDATIF[n]).ENDAT_CFG3.wdg = tick_num;
}

/*使能endat看门狗中断*/
void edt_wdg_int_en(u8 n)
{
	(*ENDATIF[n]).ENDAT_INTE.bit.wdg_irq_en = 0x1;
}

void edt_wdg_clr_int(u8 n)
{
	(*ENDATIF[n]).ENDAT_STAT.bit.wdg = 0x1;
}

u32 edt_get_wdg_sta(u8 n)
{
	return (*ENDATIF[n]).ENDAT_STAT.bit.wdg;
}

u32 edt_get_abs(u8 n)
{
	return (*ENDATIF[n]).ENDAT_ABS_POS.bit.abs_pos;
}

u32 edt_get_abm(u8 n)
{
	return (*ENDATIF[n]).ENDAT_ABM_POS.bit.abm_pos;
}

void edt_hw_trig_exit_int_en(u8 n)
{
	(*ENDATIF[n]).ENDAT_INTE.bit.hw_tirg_exit_irq_en = 0x1;
}
void edt_hw_trig_exit_clr_int(u8 n)
{
	(*ENDATIF[n]).ENDAT_STAT.bit.hw_trig_exit = 0x1;
}

u32 edt_get_hw_trig_exit_sta(u8 n)
{
	return (*ENDATIF[n]).ENDAT_STAT.bit.hw_trig_exit;
}

void edt_stf_clr_rxd_en(u8 n)
{
	(*ENDATIF[n]).ENDAT_DEC_CFG.bit.stf_clr = 0x1;
}
void edt_stf_clr_rxd_dis(u8 n)
{
	(*ENDATIF[n]).ENDAT_DEC_CFG.bit.stf_clr = 0x0;
}
