/*
 * Copyright (c) 2025, Artinchip Technology Co., Ltd
 */
#include <all_inc.h>

volatile struct ADC_REGS ADC0Regs __attribute__((__section__(".adc0reg")));
volatile struct ADC_REGS ADC1Regs __attribute__((__section__(".adc1reg")));

volatile struct ADC_REGS *ADC[] = {&ADC0Regs, &ADC1Regs};

static void adc_null(void){};
cpu_irq_fun_t adc_irqhandle = adc_null;

ATTRIBUTE_ISR void ADC_IRQHandler(void)
{
        adc_irq_handler();
}

void adc_irq_handler(void)
{
        adc_irqhandle();
}

void adc_irq_register(cpu_irq_fun_t irqhandle)
{
        adc_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_ADC);
}

void adc_irq_unregister(void)
{
        adc_irqhandle = adc_null;
        cpu_irq_disable(CPU_IRQ_ADC);
}

void adc_cmu_init(void)
{
	cmu_mod_disable(CMU_MOD_ADC);
	cmu_mod_enable(CMU_MOD_ADC);
//	writel(0x3100, BASE_CMU+0x818);	// release PSADC clk rstn
}

void adc_pinmux_init(u32 pin)
{
	gpio_enable(GPIO_GRP_A, pin, 1, GPIO_FUN_DIS);
}

void adc_fifo1_flush(u32 num)
{
	(*ADC[num]).ADC_Q1FCR.bit.FIFO_FLUSH   = 0x1;
}

void adc_fifo2_flush(u32 num)
{
	(*ADC[num]).ADC_Q2FCR.bit.FIFO_FLUSH   = 0x1;
}

void adc_q1_trig_sample_num(u32 num, u32 smpnum)
{
	(*ADC[num]).ADC_TCR.bit.Q1_TRIG_CNT   = smpnum;
}

void adc_q2_trig_sample_num(u32 num, u32 smpnum)
{
	(*ADC[num]).ADC_TCR.bit.Q2_TRIG_CNT   = smpnum;
}

void adc_q1_node0_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE1.bit.Q1_NODE0   = channel;
}

void adc_q1_node1_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE1.bit.Q1_NODE1   = channel;
}

void adc_q1_node2_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE1.bit.Q1_NODE2   = channel;
}

void adc_q1_node3_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE1.bit.Q1_NODE3   = channel;
}

void adc_q1_node4_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE1A.bit.Q1_NODE4   = channel;
}
void adc_q1_node5_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE1A.bit.Q1_NODE5   = channel;
}
void adc_q1_node6_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE1A.bit.Q1_NODE6   = channel;
}
void adc_q1_node7_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE1A.bit.Q1_NODE7   = channel;
}
void adc_q1_node8_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE1B.bit.Q1_NODE8   = channel;
}
void adc_q1_node9_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE1B.bit.Q1_NODE9   = channel;
}
void adc_q1_node10_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE1B.bit.Q1_NODE10   = channel;
}
void adc_q1_node11_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE1B.bit.Q1_NODE11   = channel;
}
void adc_q2_node0_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE2.bit.Q2_NODE0   = channel;
}
void adc_q2_node1_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE2.bit.Q2_NODE1   = channel;
}
void adc_q2_node2_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE2.bit.Q2_NODE2   = channel;
}
void adc_q2_node3_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE2.bit.Q2_NODE3   = channel;
}
void adc_q2_node4_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE2A.bit.Q2_NODE4   = channel;
}
void adc_q2_node5_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE2A.bit.Q2_NODE5   = channel;
}
void adc_q2_node6_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE2A.bit.Q2_NODE6   = channel;
}
void adc_q2_node7_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE2A.bit.Q2_NODE7   = channel;
}
void adc_q2_node8_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE2B.bit.Q2_NODE8   = channel;
}
void adc_q2_node9_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE2B.bit.Q2_NODE9   = channel;
}
void adc_q2_node10_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE2B.bit.Q2_NODE10   = channel;
}
void adc_q2_node11_set(u32 num, u32 channel)
{
	(*ADC[num]).ADC_NODE2B.bit.Q2_NODE11   = channel;
}
void adc_q1_fifo_th_set(u32 num, u32 th)
{
//	if (th > 14) {
//		printk("ERR: Set Threshold is over designed!!");
//	}
	(*ADC[num]).ADC_Q1FCR.bit.FIFO_DRTH   = th;
}

void adc_q2_fifo_th_set(u32 num, u32 th)
{
//	if (th > 14) {
//		printk("ERR: Set Threshold is over designed!!");
//	}
	(*ADC[num]).ADC_Q2FCR.bit.FIFO_DRTH   = th;
}

void adc_q1_dma_en(u32 num)
{
	(*ADC[num]).ADC_Q1FCR.bit.FIFO_DRQE   = 0x1;
}

void adc_q2_dma_en(u32 num)
{
	(*ADC[num]).ADC_Q2FCR.bit.FIFO_DRQE   = 0x1;
}

void adc_en(u32 num)
{
	(*ADC[num]).ADC_MCR.bit.EN = 0x1;
	/*adc pre-work，ready for calibration*/
	for (int i = 0; i < 8; i++)
	{
		adc_capcalcsr(num);
		adc_calcsr(num);
	}
}

void adc_smp_rate_set(u32 num, u32 smp_rate)
{
	//按照adc_clk = 40MHz， scale_clk = 80Mhz计算，
	//采样率 smp_rate = (ADC_ACQ + 2)*sacle_clk + 15*adc_clk = ((ADC_ACQ + 2)/2 + 15) * adc_clk
	switch (smp_rate) {
	case SMP_RATE_1MHZ:
		(*ADC[num]).ADC_MCR.bit.ADC_ACQ   = 48;
		break;
	case SMP_RATE_500KHZ:
		(*ADC[num]).ADC_MCR.bit.ADC_ACQ   = 128;
		break;
	case SMP_RATE_320KHZ:
		(*ADC[num]).ADC_MCR.bit.ADC_ACQ   = 218;
		break;
	case SMP_RATE_2MHZ:
		(*ADC[num]).ADC_MCR.bit.ADC_ACQ   = 8;
		break;
	default:
		break;
	}
}

void adc_q1_int_en(u32 num)
{
	(*ADC[num]).ADC_MCR.bit.Q1_INTE   = 0x1;
}

void adc_q2_int_en(u32 num)
{
	(*ADC[num]).ADC_MCR.bit.Q2_INTE   = 0x1;
}

void adc_q1_cvra_en(u32 num)
{
	(*ADC[num]).ADC_MCR.bit.Q1_TRIGA   = 0x1;
}

void adc_q2_cvrb_en(u32 num)
{
    (*ADC[num]).ADC_MCR.bit.Q2_TRIGB   = 0x1;
}

void adc_q1_sw_trig(u32 num)
{
    (*ADC[num]).ADC_MCR.bit.Q1_TRIGS   = 0x1;
}

void adc_q2_sw_trig(u32 num)
{
    (*ADC[num]).ADC_MCR.bit.Q2_TRIGS   = 0x1;
}

void adc_hcl_en(u32 num)
{
	(*ADC[num]).ADC_HCL_CTL.bit.HCL_RD_EN   = 0x1;		
}

u32 adc_int_sts(u32 num)
{
        u32 int_sts;
        int_sts = (*ADC[num]).ADC_MSR.all;
        return int_sts;
}

void adc_clr_q1_int(u32 num)
{
	(*ADC[num]).ADC_MSR.bit.Q1_INT = 0x1;
}

void adc_clr_q2_int(u32 num)
{
        (*ADC[num]).ADC_MSR.bit.Q2_INT = 0x1;
}

u32 adc_read_q1(u32 num)
{
        u32 q1_dat;
        q1_dat = ((*ADC[num]).ADC_Q1FDR.all) & 0xFFFF;
        return q1_dat;
}

u32 adc_read_q2(u32 num)
{
        u32 q2_dat;
        q2_dat = ((*ADC[num]).ADC_Q2FDR.all) & 0xFFFF;
        return q2_dat;
}

void adc_cal(u32 num)
{

}

void adc_module_clk_cfg(u32 num)
{
	//ADC工作时钟 = AHB_CLK/(CLK_HC + CLK_LC)
	//这里配置成adc_clk = 40MHz
	(*ADC[num]).ADC_CTL1.bit.CLK_HC = 0x3;
	(*ADC[num]).ADC_CTL1.bit.CLK_LC = 0x1;
	//ADC 模拟工作时钟 = AHB_CLK/(ADC_ANAC_DIV + 1)
	//这里配置成sacle_clk = 80MHz
	(*ADC[num]).ADC_CTL1.bit.ADC_ANAC_DIV = 0x2;
}

void adc_init_cfg(u32 num)
{
	adc_module_clk_cfg(num);
	(*ADC[num]).ADC_CTL.bit.ADC_V165_SEL = 0x1;
	(*ADC[num]).ADC_CTL.bit.EN_VIN_CMP = 0x0;
	(*ADC[num]).ADC_CTL.bit.VCM = 0x8;
	(*ADC[num]).ADC_CTL.bit.BIAS = 0x8;
	(*ADC[num]).ADC_CTL1.bit.ADC_PREAMP_SET   = 0xfff;
	(*ADC[num]).ADC_CTL.bit.EN_CAP_CAL = 0x1;
	(*ADC[num]).ADC_ACQCFG.bit.ADC_CLR_THR   = 0x4;
}

u32 adc_rd_ch_res(u32 num, u32 ch)
{
	u32 dat;
	dat = (*ADC[num]).ADC_RES_CH[ch];
	return dat;
}

void adc_acq1_set(u32 num, u32 acq1)
{
	(*ADC[num]).ADC_ACQCFG.bit.ADC_ACQ1   = acq1;
}

void adc_acq2_set(u32 num, u32 acq2)
{
	(*ADC[num]).ADC_ACQCFG.bit.ADC_ACQ2   = acq2;
}

void adc_acq3_set(u32 num, u32 acq3)
{
	(*ADC[num]).ADC_ACQCFG.bit.ADC_ACQ3   = acq3;
}

void adc_q1_node_smp_set(u32 num, u32 node, u32 smp)
{
	switch(node){
		case 0:
			(*ADC[num]).ADC_NODE1_ACQ.bit.Q1_NODE0_ACQ   = smp;
		break;
		case 1:
			(*ADC[num]).ADC_NODE1_ACQ.bit.Q1_NODE1_ACQ   = smp;
		break;
		case 2:
			(*ADC[num]).ADC_NODE1_ACQ.bit.Q1_NODE2_ACQ   = smp;
		break;
		case 3:
			(*ADC[num]).ADC_NODE1_ACQ.bit.Q1_NODE3_ACQ   = smp;
		break;
		case 4:
			(*ADC[num]).ADC_NODE1_ACQ.bit.Q1_NODE4_ACQ   = smp;
		break;
		case 5:
			(*ADC[num]).ADC_NODE1_ACQ.bit.Q1_NODE5_ACQ   = smp;
		break;
		case 6:
			(*ADC[num]).ADC_NODE1_ACQ.bit.Q1_NODE6_ACQ   = smp;
		break;
		case 7:
			(*ADC[num]).ADC_NODE1_ACQ.bit.Q1_NODE7_ACQ   = smp;
		break;
		case 8:
			(*ADC[num]).ADC_NODE1_ACQ.bit.Q1_NODE8_ACQ   = smp;
		break;
		case 9:
			(*ADC[num]).ADC_NODE1_ACQ.bit.Q1_NODE9_ACQ   = smp;
		break;
		case 10:
			(*ADC[num]).ADC_NODE1_ACQ.bit.Q1_NODE10_ACQ   = smp;
		break;
		case 11:
			(*ADC[num]).ADC_NODE1_ACQ.bit.Q1_NODE1_ACQ   = smp;
		break;
		default:
        break;
	}
}

void adc_q2_node_smp_set(u32 num, u32 node, u32 smp)
{
	switch(node){
		case 0:
			(*ADC[num]).ADC_NODE2_ACQ.bit.Q2_NODE0_ACQ   = smp;
		break;
		case 1:
			(*ADC[num]).ADC_NODE2_ACQ.bit.Q2_NODE1_ACQ   = smp;
		break;
		case 2:
			(*ADC[num]).ADC_NODE2_ACQ.bit.Q2_NODE2_ACQ   = smp;
		break;
		case 3:
			(*ADC[num]).ADC_NODE2_ACQ.bit.Q2_NODE3_ACQ   = smp;
		break;
		case 4:
			(*ADC[num]).ADC_NODE2_ACQ.bit.Q2_NODE4_ACQ   = smp;
		break;
		case 5:
			(*ADC[num]).ADC_NODE2_ACQ.bit.Q2_NODE5_ACQ   = smp;
		break;
		case 6:
			(*ADC[num]).ADC_NODE2_ACQ.bit.Q2_NODE6_ACQ   = smp;
		break;
		case 7:
			(*ADC[num]).ADC_NODE2_ACQ.bit.Q2_NODE7_ACQ   = smp;
		break;
		case 8:
			(*ADC[num]).ADC_NODE2_ACQ.bit.Q2_NODE8_ACQ   = smp;
		break;
		case 9:
			(*ADC[num]).ADC_NODE2_ACQ.bit.Q2_NODE9_ACQ   = smp;
		break;
		case 10:
			(*ADC[num]).ADC_NODE2_ACQ.bit.Q2_NODE10_ACQ   = smp;
		break;
		case 11:
			(*ADC[num]).ADC_NODE2_ACQ.bit.Q2_NODE1_ACQ   = smp;
		break;
		default:
        break;
	}
}

void adc_q1_osr_set(u32 num, u32 node, u32 osr)
{
	switch(node){
		case 0:
			(*ADC[num]).ADC_NODE1_OSR0.bit.Q1_NODE0_OSR   = osr;
		break;
		case 1:
			(*ADC[num]).ADC_NODE1_OSR0.bit.Q1_NODE1_OSR   = osr;
		break;
		case 2:
			(*ADC[num]).ADC_NODE1_OSR0.bit.Q1_NODE2_OSR   = osr;
		break;
		case 3:
			(*ADC[num]).ADC_NODE1_OSR0.bit.Q1_NODE3_OSR   = osr;
		break;
		case 4:
			(*ADC[num]).ADC_NODE1_OSR0.bit.Q1_NODE4_OSR   = osr;
		break;
		case 5:
			(*ADC[num]).ADC_NODE1_OSR0.bit.Q1_NODE5_OSR   = osr;
		break;
		case 6:
			(*ADC[num]).ADC_NODE1_OSR0.bit.Q1_NODE6_OSR   = osr;
		break;
		case 7:
			(*ADC[num]).ADC_NODE1_OSR0.bit.Q1_NODE7_OSR   = osr;
		break;
		case 8:
			(*ADC[num]).ADC_NODE1_OSR1.bit.Q1_NODE8_OSR   = osr;
		break;
		case 9:
			(*ADC[num]).ADC_NODE1_OSR1.bit.Q1_NODE9_OSR   = osr;
		break;
		case 10:
			(*ADC[num]).ADC_NODE1_OSR1.bit.Q1_NODE10_OSR   = osr;
		break;
		case 11:
			(*ADC[num]).ADC_NODE1_OSR1.bit.Q1_NODE11_OSR   = osr;
		break;
		default:
        break;
	}
}

void adc_q2_osr_set(u32 num, u32 node, u32 osr)
{
	switch(node){
		case 0:
			(*ADC[num]).ADC_NODE2_OSR0.bit.Q2_NODE0_OSR   = osr;
		break;
		case 1:
			(*ADC[num]).ADC_NODE2_OSR0.bit.Q2_NODE1_OSR   = osr;
		break;
		case 2:
			(*ADC[num]).ADC_NODE2_OSR0.bit.Q2_NODE2_OSR   = osr;
		break;
		case 3:
			(*ADC[num]).ADC_NODE2_OSR0.bit.Q2_NODE3_OSR   = osr;
		break;
		case 4:
			(*ADC[num]).ADC_NODE2_OSR0.bit.Q2_NODE4_OSR   = osr;
		break;
		case 5:
			(*ADC[num]).ADC_NODE2_OSR0.bit.Q2_NODE5_OSR   = osr;
		break;
		case 6:
			(*ADC[num]).ADC_NODE2_OSR0.bit.Q2_NODE6_OSR   = osr;
		break;
		case 7:
			(*ADC[num]).ADC_NODE2_OSR0.bit.Q2_NODE7_OSR   = osr;
		break;
		case 8:
			(*ADC[num]).ADC_NODE2_OSR1.bit.Q2_NODE8_OSR   = osr;
		break;
		case 9:
			(*ADC[num]).ADC_NODE2_OSR1.bit.Q2_NODE9_OSR   = osr;
		break;
		case 10:
			(*ADC[num]).ADC_NODE2_OSR1.bit.Q2_NODE10_OSR   = osr;
		break;
		case 11:
			(*ADC[num]).ADC_NODE2_OSR1.bit.Q2_NODE11_OSR   = osr;
		break;
		default:
        break;
	}
}


void adc_res_filter_set(u32 num, u32 ch, u32 filt)
{
	switch(ch){
		case 0:
			(*ADC[num]).ADC_RES_FLT0.bit.CH0_FLT_SET   = filt;
		break;
		case 1:
			(*ADC[num]).ADC_RES_FLT0.bit.CH1_FLT_SET   = filt;
		break;
		case 2:
			(*ADC[num]).ADC_RES_FLT0.bit.CH2_FLT_SET   = filt;
		break;
		case 3:
			(*ADC[num]).ADC_RES_FLT0.bit.CH3_FLT_SET   = filt;
		break;
		case 4:
			(*ADC[num]).ADC_RES_FLT0.bit.CH4_FLT_SET   = filt;
		break;
		case 5:
			(*ADC[num]).ADC_RES_FLT0.bit.CH5_FLT_SET   = filt;
		break;
		case 6:
			(*ADC[num]).ADC_RES_FLT0.bit.CH6_FLT_SET   = filt;
		break;
		case 7:
			(*ADC[num]).ADC_RES_FLT0.bit.CH7_FLT_SET   = filt;
		break;

		case 8:
			(*ADC[num]).ADC_RES_FLT1.bit.CH8_FLT_SET   = filt;
		break;
		case 9:
			(*ADC[num]).ADC_RES_FLT1.bit.CH9_FLT_SET   = filt;
		break;
		case 10:
			(*ADC[num]).ADC_RES_FLT1.bit.CH10_FLT_SET   = filt;
		break;
		case 11:
			(*ADC[num]).ADC_RES_FLT1.bit.CH11_FLT_SET   = filt;
		break;
		case 12:
			(*ADC[num]).ADC_RES_FLT1.bit.CH12_FLT_SET   = filt;
		break;
		case 13:
			(*ADC[num]).ADC_RES_FLT1.bit.CH13_FLT_SET   = filt;
		break;
		case 14:
			(*ADC[num]).ADC_RES_FLT1.bit.CH14_FLT_SET   = filt;
		break;
		case 15:
			(*ADC[num]).ADC_RES_FLT1.bit.CH15_FLT_SET   = filt;
		break;

		case 16:
			(*ADC[num]).ADC_RES_FLT2.bit.CH16_FLT_SET   = filt;
		break;
		case 17:
			(*ADC[num]).ADC_RES_FLT2.bit.CH17_FLT_SET   = filt;
		break;
		case 18:
			(*ADC[num]).ADC_RES_FLT2.bit.CH18_FLT_SET   = filt;
		break;
		case 19:
			(*ADC[num]).ADC_RES_FLT2.bit.CH19_FLT_SET   = filt;
		break;
		case 20:
			(*ADC[num]).ADC_RES_FLT2.bit.CH20_FLT_SET   = filt;
		break;
		case 21:
			(*ADC[num]).ADC_RES_FLT2.bit.CH21_FLT_SET   = filt;
		break;
		case 22:
			(*ADC[num]).ADC_RES_FLT2.bit.CH22_FLT_SET   = filt;
		break;
		case 23:
			(*ADC[num]).ADC_RES_FLT2.bit.CH23_FLT_SET   = filt;
		break;
		default:
        break;
	}
}


void adc_off_set(u32 num, u32 ch, u32 offset)
{
	switch(ch){
		case 0:
			(*ADC[num]).ADC_OFF_CH[0].bit.ADC_OFF   = offset;
		break;
		case 1:
			(*ADC[num]).ADC_OFF_CH[1].bit.ADC_OFF   = offset;
		break;
		case 2:
			(*ADC[num]).ADC_OFF_CH[2].bit.ADC_OFF   = offset;
		break;
		case 3:
			(*ADC[num]).ADC_OFF_CH[3].bit.ADC_OFF   = offset;
		break;
		case 4:
			(*ADC[num]).ADC_OFF_CH[4].bit.ADC_OFF   = offset;
		break;
		case 5:
			(*ADC[num]).ADC_OFF_CH[5].bit.ADC_OFF   = offset;
		break;
		case 6:
			(*ADC[num]).ADC_OFF_CH[6].bit.ADC_OFF   = offset;
		break;
		case 7:
			(*ADC[num]).ADC_OFF_CH[7].bit.ADC_OFF   = offset;
		break;

		case 8:
			(*ADC[num]).ADC_OFF_CH[8].bit.ADC_OFF   = offset;
		break;
		case 9:
			(*ADC[num]).ADC_OFF_CH[9].bit.ADC_OFF   = offset;
		break;
		case 10:
			(*ADC[num]).ADC_OFF_CH[10].bit.ADC_OFF   = offset;
		break;
		case 11:
			(*ADC[num]).ADC_OFF_CH[11].bit.ADC_OFF   = offset;
		break;
		case 12:
			(*ADC[num]).ADC_OFF_CH[12].bit.ADC_OFF   = offset;
		break;
		case 13:
			(*ADC[num]).ADC_OFF_CH[13].bit.ADC_OFF   = offset;
		break;
		case 14:
			(*ADC[num]).ADC_OFF_CH[14].bit.ADC_OFF   = offset;
		break;
		case 15:
			(*ADC[num]).ADC_OFF_CH[15].bit.ADC_OFF   = offset;
		break;

		case 16:
			(*ADC[num]).ADC_OFF_CH[16].bit.ADC_OFF   = offset;
		break;
		case 17:
			(*ADC[num]).ADC_OFF_CH[17].bit.ADC_OFF   = offset;
		break;
		case 18:
			(*ADC[num]).ADC_OFF_CH[18].bit.ADC_OFF   = offset;
		break;
		case 19:
			(*ADC[num]).ADC_OFF_CH[19].bit.ADC_OFF   = offset;
		break;
		case 20:
			(*ADC[num]).ADC_OFF_CH[20].bit.ADC_OFF   = offset;
		break;
		case 21:
			(*ADC[num]).ADC_OFF_CH[21].bit.ADC_OFF   = offset;
		break;
		case 22:
			(*ADC[num]).ADC_OFF_CH[22].bit.ADC_OFF   = offset;
		break;
		case 23:
			(*ADC[num]).ADC_OFF_CH[23].bit.ADC_OFF   = offset;
		break;
		default:
        break;
	}
}


void adc_off_en_set(u32 num, u32 ch, u32 en)
{
	switch(ch){
		case 0:
			(*ADC[num]).ADC_OFF_CH[0].bit.ADC_OFF_EN   = en;
		break;
		case 1:
			(*ADC[num]).ADC_OFF_CH[1].bit.ADC_OFF_EN   = en;
		break;
		case 2:
			(*ADC[num]).ADC_OFF_CH[2].bit.ADC_OFF_EN   = en;
		break;
		case 3:
			(*ADC[num]).ADC_OFF_CH[3].bit.ADC_OFF_EN   = en;
		break;
		case 4:
			(*ADC[num]).ADC_OFF_CH[4].bit.ADC_OFF_EN   = en;
		break;
		case 5:
			(*ADC[num]).ADC_OFF_CH[5].bit.ADC_OFF_EN   = en;
		break;
		case 6:
			(*ADC[num]).ADC_OFF_CH[6].bit.ADC_OFF_EN   = en;
		break;
		case 7:
			(*ADC[num]).ADC_OFF_CH[7].bit.ADC_OFF_EN   = en;
		break;

		case 8:
			(*ADC[num]).ADC_OFF_CH[8].bit.ADC_OFF_EN   = en;
		break;
		case 9:
			(*ADC[num]).ADC_OFF_CH[9].bit.ADC_OFF_EN   = en;
		break;
		case 10:
			(*ADC[num]).ADC_OFF_CH[10].bit.ADC_OFF_EN   = en;
		break;
		case 11:
			(*ADC[num]).ADC_OFF_CH[11].bit.ADC_OFF_EN   = en;
		break;
		case 12:
			(*ADC[num]).ADC_OFF_CH[12].bit.ADC_OFF_EN   = en;
		break;
		case 13:
			(*ADC[num]).ADC_OFF_CH[13].bit.ADC_OFF_EN   = en;
		break;
		case 14:
			(*ADC[num]).ADC_OFF_CH[14].bit.ADC_OFF_EN   = en;
		break;
		case 15:
			(*ADC[num]).ADC_OFF_CH[15].bit.ADC_OFF_EN   = en;
		break;

		case 16:
			(*ADC[num]).ADC_OFF_CH[16].bit.ADC_OFF_EN   = en;
		break;
		case 17:
			(*ADC[num]).ADC_OFF_CH[17].bit.ADC_OFF_EN   = en;
		break;
		case 18:
			(*ADC[num]).ADC_OFF_CH[18].bit.ADC_OFF_EN   = en;
		break;
		case 19:
			(*ADC[num]).ADC_OFF_CH[19].bit.ADC_OFF_EN   = en;
		break;
		case 20:
			(*ADC[num]).ADC_OFF_CH[20].bit.ADC_OFF_EN   = en;
		break;
		case 21:
			(*ADC[num]).ADC_OFF_CH[21].bit.ADC_OFF_EN   = en;
		break;
		case 22:
			(*ADC[num]).ADC_OFF_CH[22].bit.ADC_OFF_EN   = en;
		break;
		case 23:
			(*ADC[num]).ADC_OFF_CH[23].bit.ADC_OFF_EN   = en;
		break;
		default:
        break;
	}
}


void adc_off_sgnen_set(u32 num, u32 ch, u32 sgnen)
{
	switch(ch){
		case 0:
			(*ADC[num]).ADC_OFF_CH[0].bit.SIGN_EN   = sgnen;
		break;
		case 1:
			(*ADC[num]).ADC_OFF_CH[1].bit.SIGN_EN   = sgnen;
		break;
		case 2:
			(*ADC[num]).ADC_OFF_CH[2].bit.SIGN_EN   = sgnen;
		break;
		case 3:
			(*ADC[num]).ADC_OFF_CH[3].bit.SIGN_EN   = sgnen;
		break;
		case 4:
			(*ADC[num]).ADC_OFF_CH[4].bit.SIGN_EN   = sgnen;
		break;
		case 5:
			(*ADC[num]).ADC_OFF_CH[5].bit.SIGN_EN   = sgnen;
		break;
		case 6:
			(*ADC[num]).ADC_OFF_CH[6].bit.SIGN_EN   = sgnen;
		break;
		case 7:
			(*ADC[num]).ADC_OFF_CH[7].bit.SIGN_EN   = sgnen;
		break;

		case 8:
			(*ADC[num]).ADC_OFF_CH[8].bit.SIGN_EN   = sgnen;
		break;
		case 9:
			(*ADC[num]).ADC_OFF_CH[9].bit.SIGN_EN   = sgnen;
		break;
		case 10:
			(*ADC[num]).ADC_OFF_CH[10].bit.SIGN_EN   = sgnen;
		break;
		case 11:
			(*ADC[num]).ADC_OFF_CH[11].bit.SIGN_EN   = sgnen;
		break;
		case 12:
			(*ADC[num]).ADC_OFF_CH[12].bit.SIGN_EN   = sgnen;
		break;
		case 13:
			(*ADC[num]).ADC_OFF_CH[13].bit.SIGN_EN   = sgnen;
		break;
		case 14:
			(*ADC[num]).ADC_OFF_CH[14].bit.SIGN_EN   = sgnen;
		break;
		case 15:
			(*ADC[num]).ADC_OFF_CH[15].bit.SIGN_EN   = sgnen;
		break;

		case 16:
			(*ADC[num]).ADC_OFF_CH[16].bit.SIGN_EN   = sgnen;
		break;
		case 17:
			(*ADC[num]).ADC_OFF_CH[17].bit.SIGN_EN   = sgnen;
		break;
		case 18:
			(*ADC[num]).ADC_OFF_CH[18].bit.SIGN_EN   = sgnen;
		break;
		case 19:
			(*ADC[num]).ADC_OFF_CH[19].bit.SIGN_EN   = sgnen;
		break;
		case 20:
			(*ADC[num]).ADC_OFF_CH[20].bit.SIGN_EN   = sgnen;
		break;
		case 21:
			(*ADC[num]).ADC_OFF_CH[21].bit.SIGN_EN   = sgnen;
		break;
		case 22:
			(*ADC[num]).ADC_OFF_CH[22].bit.SIGN_EN   = sgnen;
		break;
		case 23:
			(*ADC[num]).ADC_OFF_CH[23].bit.SIGN_EN   = sgnen;
		break;
		default:
        break;
	}
}

void adc_off_lsbit_set(u32 num, u32 ch, u32 lsbit)
{
	switch(ch){
		case 0:
			(*ADC[num]).ADC_OFF_CH[0].bit.LS_BIT_SET   = lsbit;
		break;
		case 1:
			(*ADC[num]).ADC_OFF_CH[1].bit.LS_BIT_SET   = lsbit;
		break;
		case 2:
			(*ADC[num]).ADC_OFF_CH[2].bit.LS_BIT_SET   = lsbit;
		break;
		case 3:
			(*ADC[num]).ADC_OFF_CH[3].bit.LS_BIT_SET   = lsbit;
		break;
		case 4:
			(*ADC[num]).ADC_OFF_CH[4].bit.LS_BIT_SET   = lsbit;
		break;
		case 5:
			(*ADC[num]).ADC_OFF_CH[5].bit.LS_BIT_SET   = lsbit;
		break;
		case 6:
			(*ADC[num]).ADC_OFF_CH[6].bit.LS_BIT_SET   = lsbit;
		break;
		case 7:
			(*ADC[num]).ADC_OFF_CH[7].bit.LS_BIT_SET   = lsbit;
		break;

		case 8:
			(*ADC[num]).ADC_OFF_CH[8].bit.LS_BIT_SET   = lsbit;
		break;
		case 9:
			(*ADC[num]).ADC_OFF_CH[9].bit.LS_BIT_SET   = lsbit;
		break;
		case 10:
			(*ADC[num]).ADC_OFF_CH[10].bit.LS_BIT_SET   = lsbit;
		break;
		case 11:
			(*ADC[num]).ADC_OFF_CH[11].bit.LS_BIT_SET   = lsbit;
		break;
		case 12:
			(*ADC[num]).ADC_OFF_CH[12].bit.LS_BIT_SET   = lsbit;
		break;
		case 13:
			(*ADC[num]).ADC_OFF_CH[13].bit.LS_BIT_SET   = lsbit;
		break;
		case 14:
			(*ADC[num]).ADC_OFF_CH[14].bit.LS_BIT_SET   = lsbit;
		break;
		case 15:
			(*ADC[num]).ADC_OFF_CH[15].bit.LS_BIT_SET   = lsbit;
		break;

		case 16:
			(*ADC[num]).ADC_OFF_CH[16].bit.LS_BIT_SET   = lsbit;
		break;
		case 17:
			(*ADC[num]).ADC_OFF_CH[17].bit.LS_BIT_SET   = lsbit;
		break;
		case 18:
			(*ADC[num]).ADC_OFF_CH[18].bit.LS_BIT_SET   = lsbit;
		break;
		case 19:
			(*ADC[num]).ADC_OFF_CH[19].bit.LS_BIT_SET   = lsbit;
		break;
		case 20:
			(*ADC[num]).ADC_OFF_CH[20].bit.LS_BIT_SET   = lsbit;
		break;
		case 21:
			(*ADC[num]).ADC_OFF_CH[21].bit.LS_BIT_SET   = lsbit;
		break;
		case 22:
			(*ADC[num]).ADC_OFF_CH[22].bit.LS_BIT_SET   = lsbit;
		break;
		case 23:
			(*ADC[num]).ADC_OFF_CH[23].bit.LS_BIT_SET   = lsbit;
		break;
		default:
        break;
	}
}

void adc_wdog_src_set(u32 num, u32 wdg, u32 src)
{
	switch(wdg){
		case 0:
			(*ADC[num]).ADC_WDG0_CFG.bit.WDG_SRC_SEL   = src;
		break;
		case 1:
			(*ADC[num]).ADC_WDG1_CFG.bit.WDG_SRC_SEL   = src;
		break;
		case 2:
			(*ADC[num]).ADC_WDG2_CFG.bit.WDG_SRC_SEL   = src;
		break;
		default:
        break;
	}
}

void adc_wdog_en_set(u32 num, u32 wdg, u32 en)
{
	switch(wdg){
		case 0:
			(*ADC[num]).ADC_WDG0_CFG.bit.WDG_EN   = en;
		break;
		case 1:
			(*ADC[num]).ADC_WDG1_CFG.bit.WDG_EN   = en;
		break;
		case 2:
			(*ADC[num]).ADC_WDG2_CFG.bit.WDG_EN   = en;
		break;
		default:
        break;
	}
}

void adc_wdog_hlen_set(u32 num, u32 wdg, u32 hlen)
{
	switch(wdg){
		case 0:
			(*ADC[num]).ADC_WDG0_CFG.bit.WDG_HL_EN   = hlen;
		break;
		case 1:
			(*ADC[num]).ADC_WDG1_CFG.bit.WDG_HL_EN   = hlen;
		break;
		case 2:
			(*ADC[num]).ADC_WDG2_CFG.bit.WDG_HL_EN   = hlen;
		break;
		default:
        break;
	}
}

void adc_wdog_llen_set(u32 num, u32 wdg, u32 llen)
{
	switch(wdg){
		case 0:
			(*ADC[num]).ADC_WDG0_CFG.bit.WDG_LL_EN   = llen;
		break;
		case 1:
			(*ADC[num]).ADC_WDG1_CFG.bit.WDG_LL_EN   = llen;
		break;
		case 2:
			(*ADC[num]).ADC_WDG2_CFG.bit.WDG_LL_EN   = llen;
		break;
		default:
        break;
	}
}

void adc_wdog_irqen_set(u32 num, u32 wdg, u32 irqen)
{
	switch(wdg){
		case 0:
			(*ADC[num]).ADC_WDG0_CFG.bit.WDG_IRQ_EN   = irqen;
		break;
		case 1:
			(*ADC[num]).ADC_WDG1_CFG.bit.WDG_IRQ_EN   = irqen;
		break;
		case 2:
			(*ADC[num]).ADC_WDG2_CFG.bit.WDG_IRQ_EN   = irqen;
		break;
		default:
        break;
	}
}

void adc_wdog_pzden_set(u32 num, u32 wdg, u32 pzden)
{
	switch(wdg){
		case 0:
			(*ADC[num]).ADC_WDG0_CFG.bit.WDG_PZD_EN   = pzden;
		break;
		case 1:
			(*ADC[num]).ADC_WDG1_CFG.bit.WDG_PZD_EN   = pzden;
		break;
		case 2:
			(*ADC[num]).ADC_WDG2_CFG.bit.WDG_PZD_EN   = pzden;
		break;
		default:
        break;
	}
}

void adc_wdog_nzden_set(u32 num, u32 wdg, u32 nzden)
{
	switch(wdg){
		case 0:
			(*ADC[num]).ADC_WDG0_CFG.bit.WDG_NZD_EN   = nzden;
		break;
		case 1:
			(*ADC[num]).ADC_WDG1_CFG.bit.WDG_NZD_EN   = nzden;
		break;
		case 2:
			(*ADC[num]).ADC_WDG2_CFG.bit.WDG_NZD_EN   = nzden;
		break;
		default:
        break;
	}
}

void adc_wdog_hil_set(u32 num, u32 wdg, u32 hil)
{
	switch(wdg){
		case 0:
			(*ADC[num]).ADC_WDG0_LVL.bit.WDG_HL_SET   = hil;
		break;
		case 1:
			(*ADC[num]).ADC_WDG1_LVL.bit.WDG_HL_SET   = hil;
		break;
		case 2:
			(*ADC[num]).ADC_WDG2_LVL.bit.WDG_HL_SET   = hil;
		break;
		default:
        break;
	}
}

void adc_wdog_lol_set(u32 num, u32 wdg, u32 lol)
{
	switch(wdg){
		case 0:
			(*ADC[num]).ADC_WDG0_LVL.bit.WDG_LL_SET   = lol;
		break;
		case 1:
			(*ADC[num]).ADC_WDG1_LVL.bit.WDG_LL_SET   = lol;
		break;
		case 2:
			(*ADC[num]).ADC_WDG2_LVL.bit.WDG_LL_SET   = lol;
		break;
		default:
        break;
	}
}

u32 adc_wdog_sts(u32 num)
{
	u32 wdog_sts;
	wdog_sts = (*ADC[num]).ADC_WDG_STA.all;
	return wdog_sts;
}

void adc_hcl_strg_en(u32 num, u32 en)
{
	(*ADC[num]).ADC_HCL_CFG.bit.HCL_SIG_TRG_EN   = en;
}

void adc_hcl_strg_src(u32 num, u32 src)
{
	(*ADC[num]).ADC_HCL_CFG.bit.TRG_HCL_SEL   = src;
}

void adc_hcl_strg_seq(u32 num, u32 seq)
{
	(*ADC[num]).ADC_HCL_CFG.bit.HCL_SEQ_SEL   = seq;
}

void adc_qn_en(u32 num, u32 en)
{
	(*ADC[num]).ADC_QN_MCR.bit.QN_EN   = en;
}

void adc_qn_ovr_en(u32 num, u32 en)
{
	(*ADC[num]).ADC_QN_MCR.bit.QN_OVR   = en;
}

void adc_qn_ps_en(u32 num, u32 en)
{
	(*ADC[num]).ADC_QN_MCR.bit.QN_PS_EN   = en;
}

void adc_qn_reset(u32 num)
{
	(*ADC[num]).ADC_QN_MCR.bit.QN_RST   = 0x1;
}

void adc_qn_intm_set(u32 num, u32 mod)
{
	(*ADC[num]).ADC_QN_MCR.bit.QN_INTM   = mod;
}

void adc_qn_int_en(u32 num, u32 en)
{
	(*ADC[num]).ADC_QN_MCR.bit.QN_INTE   = en;
}

void adc_qn_sw_trg(u32 num)
{
	(*ADC[num]).ADC_QN_MCR.bit.QN_SS_EN   = 0x1;
}

void adc_qn_trg_num(u32 num, u32 trg_num)
{
	(*ADC[num]).ADC_QN_TCR.bit.QN_TRG_NUM   = trg_num;
}

u32 adc_qn_int_sts(u32 num)
{
        u32 int_sts;
        int_sts = (*ADC[num]).ADC_QN_MSR.all;
        return int_sts;
}


void adc_qn_node_src(u32 num, u32 node, u32 src)
{
	switch(node){
		case 0:
			(*ADC[num]).ADC_QN_NODE0.bit.QN_NODE0   = src;
		break;
		case 1:
			(*ADC[num]).ADC_QN_NODE0.bit.QN_NODE1   = src;
		break;
		case 2:
			(*ADC[num]).ADC_QN_NODE0.bit.QN_NODE2   = src;
		break;
		case 3:
			(*ADC[num]).ADC_QN_NODE0.bit.QN_NODE3   = src;
		break;
		case 4:
			(*ADC[num]).ADC_QN_NODE1.bit.QN_NODE4   = src;
		break;
		case 5:
			(*ADC[num]).ADC_QN_NODE1.bit.QN_NODE5   = src;
		break;
		case 6:
			(*ADC[num]).ADC_QN_NODE1.bit.QN_NODE6   = src;
		break;
		case 7:
			(*ADC[num]).ADC_QN_NODE1.bit.QN_NODE7   = src;
		break;

		case 8:
			(*ADC[num]).ADC_QN_NODE2.bit.QN_NODE8   = src;
		break;
		case 9:
			(*ADC[num]).ADC_QN_NODE2.bit.QN_NODE9   = src;
		break;
		case 10:
			(*ADC[num]).ADC_QN_NODE2.bit.QN_NODE10   = src;
		break;
		case 11:
			(*ADC[num]).ADC_QN_NODE2.bit.QN_NODE11   = src;
		break;
		case 12:
			(*ADC[num]).ADC_QN_NODE3.bit.QN_NODE12   = src;
		break;
		case 13:
			(*ADC[num]).ADC_QN_NODE3.bit.QN_NODE13   = src;
		break;
		case 14:
			(*ADC[num]).ADC_QN_NODE3.bit.QN_NODE14   = src;
		break;
		case 15:
			(*ADC[num]).ADC_QN_NODE3.bit.QN_NODE15   = src;
		break;

		case 16:
			(*ADC[num]).ADC_QN_NODE4.bit.QN_NODE16   = src;
		break;
		case 17:
			(*ADC[num]).ADC_QN_NODE4.bit.QN_NODE17   = src;
		break;
		case 18:
			(*ADC[num]).ADC_QN_NODE4.bit.QN_NODE18   = src;
		break;
		case 19:
			(*ADC[num]).ADC_QN_NODE4.bit.QN_NODE19   = src;
		break;
		case 20:
			(*ADC[num]).ADC_QN_NODE5.bit.QN_NODE20   = src;
		break;
		case 21:
			(*ADC[num]).ADC_QN_NODE5.bit.QN_NODE21   = src;
		break;
		case 22:
			(*ADC[num]).ADC_QN_NODE5.bit.QN_NODE22   = src;
		break;
		case 23:
			(*ADC[num]).ADC_QN_NODE5.bit.QN_NODE23   = src;
		break;
		default:
        break;
	}
}


void adc_qn_node_acq(u32 num, u32 node, u32 acq)
{
	switch(node){
		case 0:
			(*ADC[num]).ADC_QN_ACQ0.bit.QN_NODE0_ACQ   = acq;
		break;
		case 1:
			(*ADC[num]).ADC_QN_ACQ0.bit.QN_NODE1_ACQ   = acq;
		break;
		case 2:
			(*ADC[num]).ADC_QN_ACQ0.bit.QN_NODE2_ACQ   = acq;
		break;
		case 3:
			(*ADC[num]).ADC_QN_ACQ0.bit.QN_NODE3_ACQ   = acq;
		break;
		case 4:
			(*ADC[num]).ADC_QN_ACQ0.bit.QN_NODE4_ACQ   = acq;
		break;
		case 5:
			(*ADC[num]).ADC_QN_ACQ0.bit.QN_NODE5_ACQ   = acq;
		break;
		case 6:
			(*ADC[num]).ADC_QN_ACQ0.bit.QN_NODE6_ACQ   = acq;
		break;
		case 7:
			(*ADC[num]).ADC_QN_ACQ0.bit.QN_NODE7_ACQ   = acq;
		break;

		case 8:
			(*ADC[num]).ADC_QN_ACQ0.bit.QN_NODE8_ACQ   = acq;
		break;
		case 9:
			(*ADC[num]).ADC_QN_ACQ0.bit.QN_NODE9_ACQ   = acq;
		break;
		case 10:
			(*ADC[num]).ADC_QN_ACQ0.bit.QN_NODE10_ACQ   = acq;
		break;
		case 11:
			(*ADC[num]).ADC_QN_ACQ0.bit.QN_NODE11_ACQ   = acq;
		break;
		case 12:
			(*ADC[num]).ADC_QN_ACQ1.bit.QN_NODE12_ACQ   = acq;
		break;
		case 13:
			(*ADC[num]).ADC_QN_ACQ1.bit.QN_NODE13_ACQ   = acq;
		break;
		case 14:
			(*ADC[num]).ADC_QN_ACQ1.bit.QN_NODE14_ACQ   = acq;
		break;
		case 15:
			(*ADC[num]).ADC_QN_ACQ1.bit.QN_NODE15_ACQ   = acq;
		break;

		case 16:
			(*ADC[num]).ADC_QN_ACQ1.bit.QN_NODE16_ACQ   = acq;
		break;
		case 17:
			(*ADC[num]).ADC_QN_ACQ1.bit.QN_NODE17_ACQ   = acq;
		break;
		case 18:
			(*ADC[num]).ADC_QN_ACQ1.bit.QN_NODE18_ACQ   = acq;
		break;
		case 19:
			(*ADC[num]).ADC_QN_ACQ1.bit.QN_NODE19_ACQ   = acq;
		break;
		case 20:
			(*ADC[num]).ADC_QN_ACQ1.bit.QN_NODE20_ACQ   = acq;
		break;
		case 21:
			(*ADC[num]).ADC_QN_ACQ1.bit.QN_NODE21_ACQ   = acq;
		break;
		case 22:
			(*ADC[num]).ADC_QN_ACQ1.bit.QN_NODE22_ACQ   = acq;
		break;
		case 23:
			(*ADC[num]).ADC_QN_ACQ1.bit.QN_NODE23_ACQ   = acq;
		break;
		default:
        break;
	}
}

void adc_fifon_flush(u32 num)
{
	(*ADC[num]).ADC_QN_FCR.bit.FIFO_FLUSH   = 0x1;
}

void adc_qn_fifo_th_set(u32 num, u32 th)
{
	(*ADC[num]).ADC_QN_FCR.bit.FIFO_DRTH   = th;
}

void adc_qn_rdyirq_en(u32 num, u32 en)
{
	(*ADC[num]).ADC_QN_FCR.bit.FIFO_RDYIE   = en;
}

u32 adc_read_qn(u32 num)
{
        u32 qn_dat;
        qn_dat = ((*ADC[num]).ADC_QN_FDR.all) & 0xFFFF;
        return qn_dat;
}

//电容自动校准的,降低纹波的干扰
void adc_capcalcsr(u32 num)
{
	volatile u32 capcal_finished =0;
	volatile int autocal_data[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	volatile u32 autocal_tmp[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	u8 cal_mode  = 1;


	(*ADC[num]).ADC_CTL.bit.EN_CAP_CAL=1;

	(*ADC[num]).ADC_CAPCALCSR.bit.CAP_CAL_MODE=cal_mode;

	for (int n = 0; n < 8; n++) {
			(*ADC[num]).ADC_CAPCALCSR.bit.CALEN=1;
		    do {
		            capcal_finished = (*ADC[num]).ADC_CAPCALCSR.bit.CALEN;
		    } while (capcal_finished);
			autocal_tmp[0] = 	(*ADC[num]).ADC_CAPCALCSR.bit.CALVAL;
			for (int i = 0; i < 10; i++) {
				autocal_tmp[1 + i * 2] = (((*ADC[num]).ADC_DCALC[i]) >> 0) & 0xfff;
				autocal_tmp[2 + i * 2] = (((*ADC[num]).ADC_DCALC[i]) >> 16) & 0xfff;
			}

			autocal_data[0] = autocal_data[0] + autocal_tmp[0];
			for (int i = 0; i < 20; i++) {

				if (autocal_tmp[1 + i] > 1024) {
					autocal_data[1 + i] = autocal_data[1 + i] + autocal_tmp[1 + i] - 2048;
				} else {
					autocal_data[1 + i] = autocal_data[1 + i] + autocal_tmp[1 + i];
				}
			}
	}


	for (int i = 0; i < 21; i++) {

		autocal_data[i] = autocal_data[i] / 8;

		if (autocal_data[i] >= 0) {

			autocal_tmp[i] = autocal_data[i];
		} else {
			autocal_tmp[i] = 2048 + autocal_data[i];
		}
	}

		for (int i = 0; i < 10; i++) {
			(*ADC[num]).ADC_DCALC[i]=autocal_tmp[1 + i * 2] | (autocal_tmp[2 + i * 2] << 16);
		}


		(*ADC[num]).ADC_CAPCALCSR.all =0x80000000 | (autocal_tmp[0] << 16 | cal_mode << 4);



}

// Vref影响 线性偏差
void adc_calcsr(u32 num)
{
	volatile u32 offset_cal=0;
	volatile u32 capcal_finished=0;
	(*ADC[num]).ADC_CALCSR.bit.ADC_CAL_SEL   = 1;	// 1:vrefn and vrefp

	(*ADC[num]).ADC_CALCSR.bit.ADC_ACQ   = 0xff;
	for (int n = 0; n < 8; n++) {
		(*ADC[num]).ADC_CALCSR.bit.CAL_EN   = 1;
		do {
				capcal_finished = (*ADC[num]).ADC_CALCSR.bit.CAL_EN;
		} while (capcal_finished);
		offset_cal=offset_cal+(*ADC[num]).ADC_CALCSR.bit.CAL_VAL;
	}
		offset_cal = (offset_cal >> 3);
		(*ADC[num]).ADC_CALCSR.all = 0x80000000 | offset_cal << 16 | 0xff10;
}

void adc_12b_mod_set(u32 num)
{
	(*ADC[num]).ADC_SHIFT.bit.SHIFT   = 0x2;
}

void adc_14b_mod_set(u32 num)
{
	(*ADC[num]).ADC_SHIFT.bit.SHIFT   = 0x0;
}
