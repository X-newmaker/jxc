#include <all_inc.h>

volatile struct QEP_REGS Qep0Regs __attribute__((__section__(".qep0reg")));
volatile struct QEP_REGS Qep1Regs __attribute__((__section__(".qep1reg")));
volatile struct QEP_REGS Qep2Regs __attribute__((__section__(".qep2reg")));
volatile struct QEP_REGS Qep3Regs __attribute__((__section__(".qep3reg")));
volatile struct QEP_REGS Qep4Regs __attribute__((__section__(".qep4reg")));
volatile struct QEP_REGS Qep5Regs __attribute__((__section__(".qep5reg")));
volatile struct QEP_REGS Qep6Regs __attribute__((__section__(".qep6reg")));
volatile struct QEP_REGS Qep7Regs __attribute__((__section__(".qep7reg")));
volatile struct QEP_REGS Qep8Regs __attribute__((__section__(".qep8reg")));
volatile struct QEP_REGS Qep9Regs __attribute__((__section__(".qep9reg")));

volatile struct QEP_REGS *QEP[] = {
		&Qep0Regs, &Qep1Regs, &Qep2Regs, &Qep3Regs, &Qep4Regs,
		&Qep5Regs, &Qep6Regs, &Qep7Regs, &Qep8Regs, &Qep9Regs};

static void qep0_null(void){};
static void qep1_null(void){};
static void qep2_null(void){};
static void qep3_null(void){};
static void qep4_null(void){};
static void qep5_null(void){};
static void qep6_null(void){};
static void qep7_null(void){};
static void qep8_null(void){};
static void qep9_null(void){};

cpu_irq_fun_t qep0_irqhandle = qep0_null;
cpu_irq_fun_t qep1_irqhandle = qep1_null;
cpu_irq_fun_t qep2_irqhandle = qep2_null;
cpu_irq_fun_t qep3_irqhandle = qep3_null;
cpu_irq_fun_t qep4_irqhandle = qep4_null;
cpu_irq_fun_t qep5_irqhandle = qep5_null;
cpu_irq_fun_t qep6_irqhandle = qep6_null;
cpu_irq_fun_t qep7_irqhandle = qep7_null;
cpu_irq_fun_t qep8_irqhandle = qep8_null;
cpu_irq_fun_t qep9_irqhandle = qep9_null;


ATTRIBUTE_ISR void QEP0_IRQHandler(void)
{
        qep0_irq_handler();
}

void qep0_irq_handler(void)
{
        qep0_irqhandle();
}

ATTRIBUTE_ISR void QEP1_IRQHandler(void)
{
        qep1_irq_handler();
}

void qep1_irq_handler(void)
{
        qep1_irqhandle();
}

ATTRIBUTE_ISR void QEP2_IRQHandler(void)
{
        qep2_irq_handler();
}

void qep2_irq_handler(void)
{
        qep2_irqhandle();
}

ATTRIBUTE_ISR void QEP3_IRQHandler(void)
{
        qep3_irq_handler();
}

void qep3_irq_handler(void)
{
        qep3_irqhandle();
}

ATTRIBUTE_ISR void QEP4_IRQHandler(void)
{
        qep4_irq_handler();
}

void qep4_irq_handler(void)
{
        qep4_irqhandle();
}

ATTRIBUTE_ISR void QEP5_IRQHandler(void)
{
        qep5_irq_handler();
}

void qep5_irq_handler(void)
{
        qep5_irqhandle();
}

ATTRIBUTE_ISR void QEP6_IRQHandler(void)
{
        qep6_irq_handler();
}

void qep6_irq_handler(void)
{
        qep6_irqhandle();
}

ATTRIBUTE_ISR void QEP7_IRQHandler(void)
{
        qep7_irq_handler();
}

void qep7_irq_handler(void)
{
        qep7_irqhandle();
}

ATTRIBUTE_ISR void QEP8_IRQHandler(void)
{
        qep8_irq_handler();
}

void qep8_irq_handler(void)
{
        qep8_irqhandle();
}

ATTRIBUTE_ISR void QEP9_IRQHandler(void)
{
        qep9_irq_handler();
}

void qep9_irq_handler(void)
{
        qep9_irqhandle();
}

void qep_irq_register(u32 num, cpu_irq_fun_t irqhandle)
{
	switch(num){
    	case 0:
			qep0_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_QEP0);
        break;
    	case 1:
			qep1_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_QEP1);
        break;
    	case 2:
			qep2_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_QEP2);
        break;
    	case 3:
			qep3_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_QEP3);
        break;
    	case 4:
			qep4_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_QEP4);
        break;
    	case 5:
			qep5_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_QEP5);
        break;
    	case 6:
			qep6_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_QEP6);
        break;
    	case 7:
			qep7_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_QEP7);
        break;
    	case 8:
			qep8_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_QEP8);
        break;
    	case 9:
			qep9_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_QEP9);
        break;

    	default:
        break;
	}
}

void qep_irq_unregister(u32 num)
{
	switch(num){
		case 0:
			qep0_irqhandle = qep0_null;
			cpu_irq_disable(CPU_IRQ_QEP0);
		break;
		case 1:
			qep1_irqhandle = qep1_null;
			cpu_irq_disable(CPU_IRQ_QEP1);
		break;
		case 2:
			qep2_irqhandle = qep2_null;
			cpu_irq_disable(CPU_IRQ_QEP2);
		break;
		case 3:
			qep3_irqhandle = qep3_null;
			cpu_irq_disable(CPU_IRQ_QEP3);
		break;
		case 4:
			qep4_irqhandle = qep4_null;
			cpu_irq_disable(CPU_IRQ_QEP4);
		break;
		case 5:
			qep5_irqhandle = qep5_null;
			cpu_irq_disable(CPU_IRQ_QEP5);
		break;
		case 6:
			qep6_irqhandle = qep6_null;
			cpu_irq_disable(CPU_IRQ_QEP6);
		break;
		case 7:
			qep7_irqhandle = qep7_null;
			cpu_irq_disable(CPU_IRQ_QEP7);
		break;
		case 8:
			qep8_irqhandle = qep8_null;
			cpu_irq_disable(CPU_IRQ_QEP8);
		break;
		case 9:
			qep9_irqhandle = qep9_null;
			cpu_irq_disable(CPU_IRQ_QEP9);
		break;

    	default:
        break;
	}
}

void qep_pos_cnt_en(u8 i)
{
        (*QEP[i]).QEP_POS_CNT_CONF.bit.POS_CNT_EN   = 0x1;          
}

void qep_set_linenum(u8 i, u32 line_num)
{
        (*QEP[i]).QEP_POS_CNT_EP   = (line_num * 4 -1);        
}

void qep_set_pos_cnt_mode(u8 i, u32 mode)
{
        (*QEP[i]).QEP_DEC_CONF.bit.QEP_CNT_MOD   = mode;        
}

void qep_set_pos_rst_mode(u8 i, u32 mode)
{
        (*QEP[i]).QEP_POS_CNT_CONF.bit.POS_CNT_RST   = mode;        
}

void qep_set_icap_mode(u8 i, u32 mode)
{
        (*QEP[i]).QEP_POS_CNT_CONF.bit.POS_ICAP_MOD   = mode;        
}

void qep_set_icap_int_en(u8 i)
{
        (*QEP[i]).QEP_INT_EN.bit.POS_ICAP_INT_EN   = 0x1;        
}

void qep_set_a_inflt(u8 i, u32 smp_num, u32 smp_prd)
{
        (*QEP[i]).QEP_IN_FLT1.bit.A_IN_FLT_SEL   = smp_num;
        (*QEP[i]).QEP_IN_FLT1.bit.A_SMP_CTL_PRD  = smp_prd;            
}

void qep_set_b_inflt(u8 i, u32 smp_num, u32 smp_prd)
{
        (*QEP[i]).QEP_IN_FLT1.bit.B_IN_FLT_SEL   = smp_num;
        (*QEP[i]).QEP_IN_FLT1.bit.B_SMP_CTL_PRD  = smp_prd;            
}

void qep_set_i_inflt(u8 i, u32 smp_num, u32 smp_prd)
{
        (*QEP[i]).QEP_IN_FLT2.bit.I_IN_FLT_SEL   = smp_num;
        (*QEP[i]).QEP_IN_FLT2.bit.I_SMP_CTL_PRD  = smp_prd;            
}

void qep_set_inflt_en(u8 i)
{
        (*QEP[i]).QEP_IN_CTL.bit.QEP_IN_FLT_EN   = 0x1;        
}

void qep_set_i_gatea_en(u8 i)
{
        (*QEP[i]).QEP_IN_CTL.bit.QEP_I_GATEA_EN    = 0x1;        
}

void qep_a_src_sel(u8 i,QEP_SRC_TYPE type)
{
	(*QEP[i]).QEP_INSRC.bit.QEP_A_IN_SRC_SEL = type;
}
void qep_b_src_sel(u8 i,QEP_SRC_TYPE type)
{
	(*QEP[i]).QEP_INSRC.bit.QEP_B_IN_SRC_SEL = (type & 0x2F);
}
void qep_i_src_sel(u8 i,QEP_SRC_TYPE type)
{
	(*QEP[i]).QEP_INSRC.bit.QEP_I_IN_SRC_SEL = type;
}
