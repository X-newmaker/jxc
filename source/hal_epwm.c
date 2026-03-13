
#include <all_inc.h>

volatile struct EPWM_REGS EPwm0Regs  __attribute__((__section__(".epwm0reg")));
volatile struct EPWM_REGS EPwm1Regs  __attribute__((__section__(".epwm1reg")));
volatile struct EPWM_REGS EPwm2Regs  __attribute__((__section__(".epwm2reg")));
volatile struct EPWM_REGS EPwm3Regs  __attribute__((__section__(".epwm3reg")));
volatile struct EPWM_REGS EPwm4Regs  __attribute__((__section__(".epwm4reg")));
volatile struct EPWM_REGS EPwm5Regs  __attribute__((__section__(".epwm5reg")));
volatile struct EPWM_REGS EPwm6Regs  __attribute__((__section__(".epwm6reg")));
volatile struct EPWM_REGS EPwm7Regs  __attribute__((__section__(".epwm7reg")));
volatile struct EPWM_REGS EPwm8Regs  __attribute__((__section__(".epwm8reg")));
volatile struct EPWM_REGS EPwm9Regs  __attribute__((__section__(".epwm9reg")));
volatile struct EPWM_REGS EPwm10Regs __attribute__((__section__(".epwm10reg")));
volatile struct EPWM_REGS EPwm11Regs __attribute__((__section__(".epwm11reg")));

volatile struct EPWM_REGS *EPWM[] = {
		&EPwm0Regs, &EPwm1Regs, &EPwm2Regs,
                &EPwm3Regs, &EPwm4Regs, &EPwm5Regs,
		&EPwm6Regs, &EPwm7Regs, &EPwm8Regs,
                &EPwm9Regs, &EPwm10Regs, &EPwm11Regs};

static void epwm0_null(void){};
static void epwm1_null(void){};
static void epwm2_null(void){};
static void epwm3_null(void){};
static void epwm4_null(void){};
static void epwm5_null(void){};
static void epwm6_null(void){};
static void epwm7_null(void){};
static void epwm8_null(void){};
static void epwm9_null(void){};
static void epwm10_null(void){};
static void epwm11_null(void){};
static void epwm_fault_null(void){};
cpu_irq_fun_t epwm0_irqhandle = epwm0_null;
cpu_irq_fun_t epwm1_irqhandle = epwm1_null;
cpu_irq_fun_t epwm2_irqhandle = epwm2_null;
cpu_irq_fun_t epwm3_irqhandle = epwm3_null;
cpu_irq_fun_t epwm4_irqhandle = epwm4_null;
cpu_irq_fun_t epwm5_irqhandle = epwm5_null;
cpu_irq_fun_t epwm6_irqhandle = epwm6_null;
cpu_irq_fun_t epwm7_irqhandle = epwm7_null;
cpu_irq_fun_t epwm8_irqhandle = epwm8_null;
cpu_irq_fun_t epwm9_irqhandle = epwm9_null;
cpu_irq_fun_t epwm10_irqhandle = epwm10_null;
cpu_irq_fun_t epwm11_irqhandle = epwm11_null;
cpu_irq_fun_t epwm_fault_irqhandle = epwm_fault_null;

ATTRIBUTE_ISR void EPWM0_IRQHandler(void)
{
        epwm0_irq_handler();
}
void epwm0_irq_handler(void)
{
        epwm0_irqhandle();
}
ATTRIBUTE_ISR void EPWM1_IRQHandler(void)
{
        epwm1_irq_handler();
}
void epwm1_irq_handler(void)
{
        epwm1_irqhandle();
}
ATTRIBUTE_ISR void EPWM2_IRQHandler(void)
{
        epwm2_irq_handler();
}
void epwm2_irq_handler(void)
{
        epwm2_irqhandle();
}
ATTRIBUTE_ISR void EPWM3_IRQHandler(void)
{
        epwm3_irq_handler();
}
void epwm3_irq_handler(void)
{
        epwm3_irqhandle();
}
ATTRIBUTE_ISR void EPWM4_IRQHandler(void)
{
        epwm4_irq_handler();
}
void epwm4_irq_handler(void)
{
        epwm4_irqhandle();
}
ATTRIBUTE_ISR void EPWM5_IRQHandler(void)
{
        epwm5_irq_handler();
}
void epwm5_irq_handler(void)
{
        epwm5_irqhandle();
}
ATTRIBUTE_ISR void EPWM6_IRQHandler(void)
{
        epwm6_irq_handler();
}
void epwm6_irq_handler(void)
{
        epwm6_irqhandle();
}
ATTRIBUTE_ISR void EPWM7_IRQHandler(void)
{
        epwm7_irq_handler();
}
void epwm7_irq_handler(void)
{
        epwm7_irqhandle();
}
ATTRIBUTE_ISR void EPWM8_IRQHandler(void)
{
        epwm8_irq_handler();
}
void epwm8_irq_handler(void)
{
        epwm8_irqhandle();
}
ATTRIBUTE_ISR void EPWM9_IRQHandler(void)
{
        epwm9_irq_handler();
}
void epwm9_irq_handler(void)
{
        epwm9_irqhandle();
}
ATTRIBUTE_ISR void EPWM10_IRQHandler(void)
{
        epwm10_irq_handler();
}
void epwm10_irq_handler(void)
{
        epwm10_irqhandle();
}
ATTRIBUTE_ISR void EPWM11_IRQHandler(void)
{
        epwm11_irq_handler();
}
void epwm11_irq_handler(void)
{
        epwm11_irqhandle();
}


ATTRIBUTE_ISR void EPWM_FAULT_IRQHandler(void)
{
        epwm_fault_irq_handler();
}
void epwm_fault_irq_handler(void)
{
        epwm_fault_irqhandle();
}

void epwm_irq_register(u32 num, cpu_irq_fun_t irqhandle)
{
	switch(num){
		case 0:
			epwm0_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_EPWM0);
			break;
		case 1:
			epwm1_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_EPWM1);
			break;
		case 2:
			epwm2_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_EPWM2);
			break;
		case 3:
			epwm3_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_EPWM3);
			break;
		case 4:
			epwm4_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_EPWM4);
			break;
		case 5:
			epwm5_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_EPWM5);
			break;
		case 6:
			epwm6_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_EPWM6);
			break;
		case 7:
			epwm7_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_EPWM7);
			break;
		case 8:
			epwm8_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_EPWM8);
			break;
		case 9:
			epwm9_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_EPWM9);
			break;
		case 10:
			epwm10_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_EPWM10);
			break;
		case 11:
			epwm11_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_EPWM11);
			break;
    	default:
                break;
	}
}

void epwm_irq_unregister(u32 num)
{
	switch(num){
		case 0:
	        epwm0_irqhandle = epwm0_null;
	        cpu_irq_disable(CPU_IRQ_EPWM0);
			break;
		case 1:
	        epwm1_irqhandle = epwm1_null;
	        cpu_irq_disable(CPU_IRQ_EPWM1);
			break;
		case 2:
	        epwm2_irqhandle = epwm2_null;
	        cpu_irq_disable(CPU_IRQ_EPWM2);
			break;
		case 3:
	        epwm3_irqhandle = epwm3_null;
	        cpu_irq_disable(CPU_IRQ_EPWM3);
			break;
		case 4:
	        epwm4_irqhandle = epwm4_null;
	        cpu_irq_disable(CPU_IRQ_EPWM4);
			break;
		case 5:
	        epwm5_irqhandle = epwm5_null;
	        cpu_irq_disable(CPU_IRQ_EPWM5);
			break;
		case 6:
	        epwm6_irqhandle = epwm6_null;
	        cpu_irq_disable(CPU_IRQ_EPWM6);
			break;
		case 7:
	        epwm7_irqhandle = epwm7_null;
	        cpu_irq_disable(CPU_IRQ_EPWM7);
			break;
		case 8:
	        epwm8_irqhandle = epwm8_null;
	        cpu_irq_disable(CPU_IRQ_EPWM8);
			break;
		case 9:
	        epwm9_irqhandle = epwm9_null;
	        cpu_irq_disable(CPU_IRQ_EPWM9);
			break;
		case 10:
	        epwm10_irqhandle = epwm10_null;
	        cpu_irq_disable(CPU_IRQ_EPWM10);
			break;
		case 11:
	        epwm11_irqhandle = epwm11_null;
	        cpu_irq_disable(CPU_IRQ_EPWM11);
			break;
    	default:
                break;
	}

}

void epwm_fault_irq_register(cpu_irq_fun_t irqhandle)
{
        epwm_fault_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_EPWM_FAULT);
}

void epwm_fault_irq_unregister(void)
{
        epwm_fault_irqhandle = epwm_fault_null;
        cpu_irq_disable(CPU_IRQ_EPWM_FAULT);
}

void epwm_comp_ch_init(u8 i, u32 prd, u32 dz)
{
        (*EPWM[i]).PWM_CNT_PRDV.bit.PRD_VAL            = prd; 
        (*EPWM[i]).PWM_CNT_PHV.bit.PH_VAL              = 0;        
        (*EPWM[i]).PWM_CNT_AV.bit.CNT_AV               = 0;
        (*EPWM[i]).PWM_CNT_BV.bit.CNT_BV               = 0;

        (*EPWM[i]).PWM_CNT_CFG.bit.CLK_DIV1            = ADIV2;
        (*EPWM[i]).PWM_CNT_CFG.bit.CLK_DIV2            = BDIV1;
        (*EPWM[i]).PWM_CNT_CFG.bit.CNT_MOD             = CNT_UP_DOWN;
        (*EPWM[i]).PWM_CNT_CFG.bit.CNT_PH_EN           = 0x1;
        (*EPWM[i]).PWM_CNT_CFG.bit.CNT_PH_DIR          = DIR_INCR;
        (*EPWM[i]).PWM_CNT_CFG.bit.CNT_PRD_UPDT        = IMED;
        (*EPWM[i]).PWM_CNT_CFG.bit.SYNC_OUT            = SO_CNTZ;

        (*EPWM[i]).PWM_UPDT_MODE.bit.CMPA_UPDT         = SHAD;        
        (*EPWM[i]).PWM_UPDT_MODE.bit.CMPA_LP           = CNT_Z_OR_P;
 
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_UAV           = ACT_LOW; 
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_DAV           = ACT_HIGH; 

        (*EPWM[i]).PWM_OUT_CONF.bit.BYPASS_SET         = NO_BP; 
        (*EPWM[i]).PWM_OUT_CONF.bit.POL_SET            = CHA_POST_CHB_NEGT;
        (*EPWM[i]).PWM_OUT_CONF.bit.CH_SET             = CHAB_SEL_PWMA;

        (*EPWM[i]).PWM_RE_DZCTL.bit.RE_DZCTL           = dz;
        (*EPWM[i]).PWM_FE_DZCTL.bit.FE_DZCTL           = dz;

}

void epwm_interrupt_init(u8 i, u32 src)
{

        (*EPWM[i]).PWM_ADC_INT_CTL.bit.PWM_INT_SEL        = src;
        (*EPWM[i]).PWM_ADC_INT_PRE.bit.PWM_INT_DIV        = SRC_DIV1_OUT;
        (*EPWM[i]).PWM_ADC_INT_CTL.bit.PWM_INT_EN         = 0x1;

}

void epwm_cvra_init(u8 i, u32 src)
{

        (*EPWM[i]).PWM_ADC_INT_CTL.bit.ADC_CVRA_SEL       = src;
        (*EPWM[i]).PWM_ADC_INT_PRE.bit.ADC_CVRA_DIV       = SRC_DIV1_OUT;
        (*EPWM[i]).PWM_ADC_INT_CTL.bit.ADC_CVRA_EN        = 0x1;

}

void epwm_cvrb_init(u8 i, u32 src)
{

        (*EPWM[i]).PWM_ADC_INT_CTL.bit.ADC_CVRB_SEL       = src;
        (*EPWM[i]).PWM_ADC_INT_PRE.bit.ADC_CVRB_DIV       = SRC_DIV1_OUT;
        (*EPWM[i]).PWM_ADC_INT_CTL.bit.ADC_CVRB_EN        = 0x1;

}

void epwm_bldc_init(u8 i, u16 periodmax)
{
        (*EPWM[i]).PWM_CNT_CFG.bit.SYNC_OUT             = SYNCIN_OR_SW;
        (*EPWM[i]).PWM_CNT_CFG.bit.CNT_PH_EN            = P_DISABLE;
        (*EPWM[i]).PWM_CNT_CFG.bit.CNT_PRD_UPDT         = IMED;        
        (*EPWM[i]).PWM_CNT_CFG.bit.CNT_MOD              = CNT_UP; 
        (*EPWM[i]).PWM_CNT_CFG.bit.CLK_DIV1             = ADIV1;
        (*EPWM[i]).PWM_CNT_CFG.bit.CLK_DIV2             = BDIV1;
        (*EPWM[i]).PWM_CNT_CFG.bit.CNT_PH_DIR           = DIR_INCR;

        (*EPWM[i]).PWM_CNT_PRDV.bit.PRD_VAL             = periodmax;
        (*EPWM[i]).PWM_CNT_PHV.bit.PH_VAL               = 0;

        (*EPWM[i]).PWM_UPDT_MODE.bit.CMPA_LP            = CNT_ZRO;
        (*EPWM[i]).PWM_UPDT_MODE.bit.CMPB_LP            = CNT_ZRO;                
        (*EPWM[i]).PWM_UPDT_MODE.bit.CMPA_UPDT          = SHAD; 
        (*EPWM[i]).PWM_UPDT_MODE.bit.CMPB_UPDT          = SHAD;

        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_UAV            = ACT_HIGH;
        (*EPWM[i]).PWM_OUT_CONF.bit.BYPASS_SET          = BP_CHA_AND_CHB;    
}


void epwm_bldc_pwm_ch_set(u8 i, u16 cmpa)
{
        (*EPWM[i]).PWM_SW_CT_ACT.bit.AACT_SW_CT = CTACT_NONE0;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_UAV = ACT_HIGH;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_Z = ACT_LOW;
        (*EPWM[i]).PWM_CNT_AV.bit.CNT_AV = cmpa;
        (*EPWM[i]).PWM_SW_CT_ACT.bit.BACT_SW_CT = CTACT_LOW;

}

void epwm_bldc_on_ch_set(u8 i)
{
        (*EPWM[i]).PWM_SW_CT_ACT.bit.AACT_SW_CT = CTACT_LOW;
        (*EPWM[i]).PWM_SW_CT_ACT.bit.BACT_SW_CT = CTACT_HIGH;
}

void epwm_bldc_off_ch_set(u8 i)
{
        (*EPWM[i]).PWM_SW_CT_ACT.bit.AACT_SW_CT = CTACT_LOW;
        (*EPWM[i]).PWM_SW_CT_ACT.bit.BACT_SW_CT = CTACT_LOW;
}

void epwm_set_pul_num(u8 i, u32 tx_num)
{
        (*EPWM[i]).PWM_PUL_OUT_NUM = tx_num;
}

void epwm_set_prd(u8 i, u32 prd)
{
        (*EPWM[i]).PWM_CNT_PRDV.bit.PRD_VAL = (prd & 0xFFFF);
}

void epwm_pul_out_en(u8 i)
{
        (*EPWM[i]).PWM_PUL_OUT.bit.PUL_OUT_EN = P_ENABLE;
}

void epwm_pul_out_dis(u8 i)
{
        (*EPWM[i]).PWM_PUL_OUT.bit.PUL_OUT_EN = P_DISABLE;
}

void epwm_set_swct_act(u8 i, u32 src, SW_CT_TYPE a_act, SW_CT_TYPE b_act)
{
        (*EPWM[i]).PWM_SW_ACT.bit.SW_CT_UPDT = src;
        (*EPWM[i]).PWM_SW_CT_ACT.bit.AACT_SW_CT = a_act;
        (*EPWM[i]).PWM_SW_CT_ACT.bit.BACT_SW_CT = b_act;
}

void epwm_set_quad_out_typ0(u8 i)
{
        //Pulse A lead Pulse B
        //set A action
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_Z   = ACT_HIGH;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_PRD = ACT_LOW;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_UAV = ACT_NONE;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_DAV = ACT_NONE;
        //set B action
        (*EPWM[i]).PWM_B_ACT.bit.ACT_CNT_Z   = ACT_LOW;
        (*EPWM[i]).PWM_B_ACT.bit.ACT_CNT_PRD = ACT_NONE;
        (*EPWM[i]).PWM_B_ACT.bit.ACT_CNT_UAV = ACT_HIGH;
        (*EPWM[i]).PWM_B_ACT.bit.ACT_CNT_DAV = ACT_LOW;
}

void epwm_set_quad_out_typ1(u8 i)
{
        //Pulse B Lead Pulse A
        //set B action
        (*EPWM[i]).PWM_B_ACT.bit.ACT_CNT_Z   = ACT_HIGH;
        (*EPWM[i]).PWM_B_ACT.bit.ACT_CNT_PRD = ACT_LOW;
        (*EPWM[i]).PWM_B_ACT.bit.ACT_CNT_UAV = ACT_NONE;
        (*EPWM[i]).PWM_B_ACT.bit.ACT_CNT_DAV = ACT_NONE;
        //set B action
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_Z   = ACT_LOW;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_PRD = ACT_NONE;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_UAV = ACT_HIGH;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_DAV = ACT_LOW;
}

void epwm_set_pul_dir_l(u8 i)
{
        //set A action (PULSE)
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_Z   = ACT_LOW;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_PRD = ACT_NONE;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_UAV = ACT_HIGH;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_DAV = ACT_LOW;
        //set B action (DIR = Low)
        epwm_set_swct_act(i, 0x4, NONE_SW_CT, SW_CT_LOW);
}

void epwm_set_pul_dir_h(u8 i)
{
        //set A action (PULSE)
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_Z   = ACT_LOW;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_PRD = ACT_NONE;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_UAV = ACT_HIGH;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_DAV = ACT_LOW;
        //set B action (DIR = High)
        epwm_set_swct_act(i, 0x4, NONE_SW_CT, SW_CT_HIGH);
}

void epwm_set_pul_cw(u8 i)
{
        //set A action (CW PULSE)
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_Z   = ACT_HIGH;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_PRD = ACT_LOW;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_UAV = ACT_NONE;
        (*EPWM[i]).PWM_A_ACT.bit.ACT_CNT_DAV = ACT_NONE;
        //set B action (Low)
        epwm_set_swct_act(i, 0x4, NONE_SW_CT, SW_CT_LOW);
}

void epwm_set_pul_ccw(u8 i)
{
        //set B action (CCW PULSE)
        (*EPWM[i]).PWM_B_ACT.bit.ACT_CNT_Z   = ACT_HIGH;
        (*EPWM[i]).PWM_B_ACT.bit.ACT_CNT_PRD = ACT_LOW;
        (*EPWM[i]).PWM_B_ACT.bit.ACT_CNT_UAV = ACT_NONE;
        (*EPWM[i]).PWM_B_ACT.bit.ACT_CNT_DAV = ACT_NONE;
        //set A action (Low)
        epwm_set_swct_act(i, 0x4, SW_CT_LOW, NONE_SW_CT);
}

void epwm_int_clr(u8 i)
{
        (*EPWM[i]).PWM_EVNT_CLR.bit.PWM_INT_CLR = 0x1;
}

void epwm_link_none(u8 i)
{
	switch(i) {
		case 0x0:
			(*EPWM[i]).PWM_LINK_CTL.all = 0x0;
			break;
		case 0x1:
			(*EPWM[i]).PWM_LINK_CTL.all = 0x1111111;
			break;
		case 0x2:
			(*EPWM[i]).PWM_LINK_CTL.all = 0x2222222;
			break;
		case 0x3:
			(*EPWM[i]).PWM_LINK_CTL.all = 0x3333333;
			break;
		case 0x4:
			(*EPWM[i]).PWM_LINK_CTL.all = 0x4444444;
			break;
		case 0x5:
			(*EPWM[i]).PWM_LINK_CTL.all = 0x5555555;
			break;
		case 0x6:
			(*EPWM[i]).PWM_LINK_CTL.all = 0x6666666;
			break;
		case 0x7:
			(*EPWM[i]).PWM_LINK_CTL.all = 0x7777777;
			break;
		case 0x8:
			(*EPWM[i]).PWM_LINK_CTL.all = 0x8888888;
			break;
		case 0x9:
			(*EPWM[i]).PWM_LINK_CTL.all = 0x9999999;
			break;
		case 0xa:
			(*EPWM[i]).PWM_LINK_CTL.all = 0xaaaaaaa;
			break;
		case 0xb:
			(*EPWM[i]).PWM_LINK_CTL.all = 0xbbbbbbb;
			break;
		default:
		break;
	}
}
