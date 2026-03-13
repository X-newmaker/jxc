/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 */
#include <all_inc.h>
volatile struct TAIF_REGS Taif0Regs __attribute__((__section__(".taif0reg")));
volatile struct TAIF_REGS Taif1Regs __attribute__((__section__(".taif1reg")));

volatile struct TAIF_REGS *TAIF[] = {&Taif0Regs, &Taif1Regs};

static void taif0_null(void){};
static void taif1_null(void){};
cpu_irq_fun_t taif0_irqhandle = taif0_null;
cpu_irq_fun_t taif1_irqhandle = taif1_null;

ATTRIBUTE_ISR void TAIF0_IRQHandler(void)
{
        taif0_irq_handler();
}

void taif0_irq_handler(void)
{
        taif0_irqhandle();
}

void taif0_irq_register(cpu_irq_fun_t irqhandle)
{
        taif0_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_TA0_IF);
}

void taif0_irq_unregister(void)
{
        taif0_irqhandle = taif0_null;
        cpu_irq_disable(CPU_IRQ_TA0_IF);
}

ATTRIBUTE_ISR void TAIF1_IRQHandler(void)
{
        taif1_irq_handler();
}

void taif1_irq_handler(void)
{
        taif1_irqhandle();
}

void taif1_irq_register(cpu_irq_fun_t irqhandle)
{
        taif1_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_TA1_IF);
}

void taif1_irq_unregister(void)
{
        taif1_irqhandle = taif1_null;
        cpu_irq_disable(CPU_IRQ_TA1_IF);
}

void ta_cmu_init(void)
{
        cmu_mod_disable(CMU_MOD_TA_IF);
        cmu_mod_set_freq(CMU_MOD_TA_IF, 240*1000*1000);
        cmu_mod_enable(CMU_MOD_TA_IF);
}

void ta_syscfg_sel(u8 n)
{
	u32 reg_val;
        switch (n) {
                case 0:
                		reg_val = readl(0x180001F4);
                		reg_val &= (~(0x3<<0));
                		reg_val |= (0x2<<0);
                        writel(reg_val, 0x180001F4);
                        break;
                case 1:
                		reg_val = readl(0x180001F4);
                	    reg_val &= (~(0x3<<16));
                	    reg_val |= (0x2<<16);
                        writel(reg_val, 0x180001F4);
                        break;

                default:
                break;
        }
}

void ta_pinmux_init(u8 n)
{
	switch (n) {
			case 0:
					gpio_enable(GPIO_GRP_F, 0, 2, GPIO_FUN_6);
					writel(0x2, 0x180001F4);
					break;
			case 1:
					gpio_enable(GPIO_GRP_F, 3, 2, GPIO_FUN_6);
					writel(0x20000, 0x180001F4);
					break;

			default:
			break;
	}
}

void ta_reset(u8 n)
{
	(*TAIF[n]).CMD_EXC.bit.DBG_RST = 0x36;
}

void ta_cmd_execute(u32 n)
{
	(*TAIF[n]).CMD_EXC.bit.CMD_EXC = 0x1;
}

void ta_baudrate_set(u8 n, TA_BAUD_TYPE baud)
{
	(*TAIF[n]).COM_CTL.bit.BDRATE_SET = baud;
}

void ta_format_sel(u8 n, TA_FORMAT_TYPE format)
{
	(*TAIF[n]).COM_CTL.bit.FORMAT_SEL = format;
}

void ta_hw_err_bp_en(u8 n)
{
	(*TAIF[n]).COM_CTL.bit.HW_RX_ERR_BPS_EN = 0x1;
}
void ta_hw_err_bp_dis(u8 n)
{
	(*TAIF[n]).COM_CTL.bit.HW_RX_ERR_BPS_EN = 0x0;
}
void ta_hw_trig_en(u8 n)
{
	(*TAIF[n]).COM_CTL.bit.HW_TRG_EN = 0x1;
}

void ta_hw_trig_dis(u8 n)
{
	(*TAIF[n]).COM_CTL.bit.HW_TRG_EN = 0x0;
}

void ta_tx_col_det_en(u8 n)
{
    (*TAIF[n]).COM_CTL.bit.TX_COL_DET_EN = 0x1;
}
void ta_tx_col_det_dis(u8 n)
{
    (*TAIF[n]).COM_CTL.bit.TX_COL_DET_EN = 0x0;
}
void ta_stf_clr_rxd_enable(u8 n,u32 enable)
{
	(*TAIF[n]).COM_CTL.bit.STF_CLR_RXD_EN = enable;
}

void ta_done_irq_en(u8 n)
{
	(*TAIF[n]).TA_IRQ_EN.bit.IRQ_CMD_DONE_EN = 0x1;
}

void ta_cmdto_irq_en(u8 n)
{
	(*TAIF[n]).TA_IRQ_EN.bit.IRQ_CMD_TO_EN = 0x1;
}

void ta_rxto_irq_en(u8 n)
{
	(*TAIF[n]).TA_IRQ_EN.bit.IRQ_CMD_RXD_TO_EN = 0x1;
}

void ta_hw_trig_exit_irq_en(u8 n)
{
	(*TAIF[n]).TA_IRQ_EN.bit.IRQ_HW_TRIG_EXIT_EN = 0x1;
}

void ta_done_irq_clr(u8 n)
{
	(*TAIF[n]).TA_IRQ_STS.bit.IRQ_CMD_DONE = 0x1;
}

void ta_cmdto_irq_clr(u8 n)
{
	(*TAIF[n]).TA_IRQ_STS.bit.IRQ_CMD_TO = 0x1;
}

void ta_rxto_irq_clr(u8 n)
{
	(*TAIF[n]).TA_IRQ_STS.bit.IRQ_CMD_RXD_TO = 0x1;
}

void ta_hw_trig_exit_irq_clr(u8 n)
{
	(*TAIF[n]).TA_IRQ_STS.bit.IRQ_HW_TRIG_EXIT = 0x1;
}

void ta_xfmt_txf_clr(u8 n)
{
	(*TAIF[n]).TA_IRQ_STS.bit.IRQ_XFMT_TXF = 0x1;
}

void ta_xfmt_txf_uovf(u8 n)
{
	(*TAIF[n]).TA_IRQ_STS.bit.IRQ_XFMT_TXF_UOVF = 0x1;
}

void ta_xfmt_txf_dovf(u8 n)
{
	(*TAIF[n]).TA_IRQ_STS.bit.IRQ_XFMT_TXF_DOVF = 0x1;
}

void ta_xfmt_rxf_clr(u8 n)
{
	(*TAIF[n]).TA_IRQ_STS.bit.IRQ_XFMT_RXF = 0x1;
}

void ta_xfmt_rxf_uovf(u8 n)
{
	(*TAIF[n]).TA_IRQ_STS.bit.IRQ_XFMT_RXF_UOVF = 0x1;
}

void ta_xfmt_rxf_dovf(u8 n)
{
	(*TAIF[n]).TA_IRQ_STS.bit.IRQ_XFMT_RXF_DOVF = 0x1;
}
void ta_rx_align_en(u32 n)
{
	(*TAIF[n]).BCLK.bit.RX_ALIGN_EN = 0x1;	
}

void ta_t2_set(u32 n, u16 t2)
{
	(*TAIF[n]).T2.bit.VAL = t2;	
}

void ta_t3_set(u32 n, u16 t3)
{
	(*TAIF[n]).T3.bit.VAL = t3;	
}

void ta_t4_set(u32 n, u16 t4)
{
	(*TAIF[n]).T4.bit.VAL = t4;	
}

void ta_t5_set(u32 n, u16 t5)
{
	(*TAIF[n]).T5.bit.VAL = t5;	
}

void ta_t6_set(u32 n, u16 t6)
{
	(*TAIF[n]).T6.bit.VAL = t6;	
}

void ta_t9_set(u32 n, u16 t9)
{
	(*TAIF[n]).T9.bit.VAL = t9;	
}

void ta_tcol_set(u32 n, u16 tcol)
{
	(*TAIF[n]).TCOL.bit.VAL = tcol;	
}

void ta_ctl(u32 n,TA_TDATAID_TYPE id,u32 dfnum,TA_TFIELD_NUM_TYPE field)
{
        (*TAIF[n]).TX_CTL.bit.ID = id;
        (*TAIF[n]).TX_CTL.bit.DFNUM = dfnum & 0x7;
        (*TAIF[n]).TX_CTL.bit.TX_FLD_NUM = field;
}

void ta_adf(u32 n,u32 busy,u32 adf)
{
        (*TAIF[n]).TX_ADF.bit.TXAD = adf;
        (*TAIF[n]).TX_ADF.bit.BUSY = busy;
}
void ta_edf(u32 n,u32 edf)
{
        (*TAIF[n]).TX_EDF.bit.TXED = edf;
}

u32 ta_get_sts(u32 n)
{
        u32 irq_sts;
        irq_sts = (*TAIF[n]).STS.all;
        return irq_sts;
}

u32 ta_get_rx_data0(u32 n)
{
        u32 rxdata0;
        rxdata0 = (*TAIF[n]).RX_DAT0.all;
        return rxdata0;
}

u32 ta_get_rx_data1(u32 n)
{
        u32 rxdata1;
        rxdata1 = (*TAIF[n]).RX_DAT1.all;
        return rxdata1;
}
u32 ta_get_rx_tsts(u32 n)
{
        u32 sts;
        sts = (*TAIF[n]).RX_TSTS.all;
        return sts;
}
u32 ta_get_rx_tdat(u32 n)
{
        u32 rxdata1;
        rxdata1 = (*TAIF[n]).RX_TDAT.all;
        return rxdata1;
}

void tf_dec_abs_sel(u32 n,TF_DEC_SEL sel)
{
	(*TAIF[n]).RX_TDEC.bit.TF_ABS_DEC_EN = 0x1;
	(*TAIF[n]).RX_TDEC.bit.DEC_TF_ABS_SEL = sel;
}
void tf_dec_abm_sel(u32 n,TF_DEC_SEL sel)
{
	(*TAIF[n]).RX_TDEC.bit.TF_ABM_DEC_EN = 0x1;
	(*TAIF[n]).RX_TDEC.bit.DEC_TF_ABM_SEL = sel;
}

//ea: encoder address
void ta_cdf(u32 n,u32 ea,u32 cc,u32 mdf0,u32 mdf1,u32 mdf2)
{
	(*TAIF[n]).TX_DATA.bit.CDF_EA = ea;
	(*TAIF[n]).TX_DATA.bit.CDF_CC = cc;
	(*TAIF[n]).TX_DATA.bit.MDF0_DATA = mdf0;
	(*TAIF[n]).TX_DATA.bit.MDF1_DATA = mdf1;
	(*TAIF[n]).TX_DATA.bit.MDF2_DATA = mdf2;
}

//ea:编码器地址， cc: TX CDF命令代码，rxfield：接收域数量

void ta_format_ctl(u32 n,TA_AFIELD_TX_TYPE txfiled,TA_AFIELD_RX_TYPE rxfield)
{
	(*TAIF[n]).FORMT_CTL.bit.TXFNUM = txfiled;
	(*TAIF[n]).FORMT_CTL.bit.RXFNUM = rxfield;
}
u32 ta_get_arx_d0(u32 n)
{
        u32 rxdata0;
        rxdata0 = (*TAIF[n]).RX_D0.all;
        return rxdata0;
}

u32 ta_get_arx_d1(u32 n)
{
        u32 rxdata1;
        rxdata1 = (*TAIF[n]).RX_D1.all;
        return rxdata1;
}

u32 ta_get_arx_if(u32 n)
{
        u32 rxdata0;
        rxdata0 = (*TAIF[n]).RX_D0.bit.RXIF;
        return rxdata0;
}

u32 ta_get_arx_df0(u32 n)
{
        u32 rxdata0;
        rxdata0 = (*TAIF[n]).RX_D0.bit.RXDF0;
        return rxdata0;
}

u32 ta_get_arx_df1(u32 n)
{
        u32 rxdata0;
        rxdata0 = (*TAIF[n]).RX_D1.bit.RXDF1;
        return rxdata0;
}

u32 ta_get_arx_df2(u32 n)
{
        u32 rxdata0;
        rxdata0 = (*TAIF[n]).RX_D1.bit.RXDF2;
        return rxdata0;
}

u32 ta_get_rx_asts(u32 n)
{
        u32 sts;
        sts = (*TAIF[n]).RX_ASTS.all;
        return sts;
}

void af_abs_pos_set(u8 n, u32 startbit, u32 size)
{
	(*TAIF[n]).RX_ADEC_CFG.bit.AF_ABS_DEC_EN = 0x1;
	(*TAIF[n]).RX_ADEC_CFG.bit.AF_ABS_DEC_ST_BIT = startbit;
	(*TAIF[n]).RX_ADEC_CFG.bit.AF_ABS_DEC_BIT_NUM = size;
}

void af_abm_pos_set(u8 n, u32 startbit, u32 size)
{
	(*TAIF[n]).RX_ADEC_CFG.bit.AF_ABM_DEC_EN = 0x1;
	(*TAIF[n]).RX_ADEC_CFG.bit.AF_ABM_DEC_ST_BIT = startbit;
	(*TAIF[n]).RX_ADEC_CFG.bit.AF_ABM_DEC_BIT_NUM = size;
}

u32 ta_get_abs_pos(u32 n)
{
	u32 abs;
	abs = (*TAIF[n]).DEC_ABS.bit.DEC_ABS_DAT;
	return abs;
}
u32 ta_get_abm_pos(u32 n)
{
	u32 abm;
	abm = (*TAIF[n]).DEC_ABM.bit.DEC_ABM_DAT;
	return abm;
}

u32 ta_get_irq_sts(u32 n)
{
    u32 irq_sts;
    irq_sts = (*TAIF[n]).TA_IRQ_STS.all;
    return irq_sts;
}

void ta_irq_sts_clr(u32 n, u32 data)
{
	(*TAIF[n]).TA_IRQ_STS.all = data;
}

u32 ta_get_rx_adf(u32 n)
{
	u32 adf;
	adf=(*TAIF[n]).RX_TDAT.bit.ADF;
	return adf;
}
u32 ta_get_rx_edf(u32 n)
{
	u32 edf;
	edf=(*TAIF[n]).RX_TDAT.bit.EDF;
	return edf;
}

void ta_xf_tx_len(u8 n, u32 len)
{
	(*TAIF[n]).XFMT_CFG1.bit.XFMT_TXC_LEN = len;
}
void ta_xf_rx_len(u8 n, u32 len)
{
	(*TAIF[n]).XFMT_CFG1.bit.XFMT_RXC_LEN = len;
}
void ta_xf_txfifo_en(u8 n)
{
	(*TAIF[n]).XFMT_CFG1.bit.XFMT_TXFIFO_EN = 0x1;
}
void ta_xf_txfifo_dis(u8 n)
{
	(*TAIF[n]).XFMT_CFG1.bit.XFMT_TXFIFO_EN = 0x0;
}
void ta_xf_txfifo_irq_en(u8 n)
{
	(*TAIF[n]).XFMT_CFG1.bit.XFMT_TXFIFO_IRQ_EN = 0x1;
}
void ta_xf_txfifo_drq_en(u8 n)
{
	(*TAIF[n]).XFMT_CFG1.bit.XFMT_TXFIFO_DRQ_EN = 0x1;
}
void ta_xf_rxfifo_en(u8 n)
{
	(*TAIF[n]).XFMT_CFG1.bit.XFMT_RXFIFO_EN = 0x1;
}
void ta_xf_rxfifo_dis(u8 n)
{
	(*TAIF[n]).XFMT_CFG1.bit.XFMT_RXFIFO_EN = 0x0;
}
void ta_xf_rxfifo_irq_en(u8 n)
{
	(*TAIF[n]).XFMT_CFG1.bit.XFMT_RXFIFO_IRQ_EN = 0x1;
}
void ta_xf_rxfifo_drq_en(u8 n)
{
	(*TAIF[n]).XFMT_CFG1.bit.XFMT_RXFIFO_DRQ_EN = 0x1;
}
void ta_xf_txfifo_th(u8 n,u32 th)
{
	(*TAIF[n]).XFMT_CFG1.bit.TXFIFO_TH = th;
}
void ta_xf_rxfifo_th(u8 n,u32 th)
{
	(*TAIF[n]).XFMT_CFG1.bit.RXFIFO_TH = th;
}

void ta_xf_tx_num(u8 n,u32 num)
{
	(*TAIF[n]).XFMT_CFG2.bit.XFMT_TXC_NUM = num;
}
void ta_xf_rx_num(u8 n,u32 num)
{
	(*TAIF[n]).XFMT_CFG2.bit.XFMT_RXC_NUM = num;
}
void ta_xf_txfifo_uovf_irq_en(u8 n)
{
	(*TAIF[n]).XFMT_CFG2.bit.XFMT_TXFIFO_UOVF_IRQ_EN = 0x1;
}
void ta_xf_txfifo_dovf_irq_en(u8 n)
{
	(*TAIF[n]).XFMT_CFG2.bit.XFMT_TXFIFO_DOVF_IRQ_EN = 0x1;
}
void ta_xf_rxfifo_uovf_irq_en(u8 n)
{
	(*TAIF[n]).XFMT_CFG2.bit.XFMT_RXFIFO_UOVF_IRQ_EN = 0x1;
}
void ta_xf_rxfifo_dovf_irq_en(u8 n)
{
	(*TAIF[n]).XFMT_CFG2.bit.XFMT_RXFIFO_DOVF_IRQ_EN = 0x1;
}

void ta_xf_xcmd(u8 n, u32 num, u32 cmd)
{
	(*TAIF[n]).XFMT_CMD[num].bit.XCMD= cmd;
}
u32 ta_xf_xdat(u8 n, u32 num)
{
	u32 data;
	data = (*TAIF[n]).XFMT_DAT[num].bit.XDAT;
	return data;
}
