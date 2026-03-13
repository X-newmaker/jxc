#include "all_inc.h"
#include "M680x_it.h"
#include "servo_drv_setting.h"

typedef enum
{
	ADC0_NUM = 0,
	ADC1_NUM,
	ADC_NUM_MAX,
}ENUM_ADC_NUM;
typedef enum
{
	PGA0_NUM = 0,
	PGA1_NUM,
	PGA2_NUM,
	PGA3_NUM,
	PGA_MAX,
}ENUM_PGA_NUM;

#define		PGA_U	PGA2_NUM		//U相PGA序号
#define		PGA_V	PGA3_NUM		//V相PGA序号

void sdfm_int_enable(uint32_t num);
void sdfm_int_clear(uint32_t num);
static void sdfm_init(u32 num,u32 osr);
static void epwm_sync_out_sel(u32 num,u32 osr);
static void sdfm_sync_source(uint32_t sdfm_num,uint32_t epwm_num);
static void sdfm_ssin_set_th_high(uint32_t num,uint32_t data);
static void sdfm_ssin_set_th_low(uint32_t num,uint32_t data);
static void sdfm_fault_rec_init(uint32_t sdfm_num,uint32_t epwm_num);
static void sdfm_fault_nrec_init(u32 sdfm_num,u32 epwm_num);
static void MX_ADC_Init(void);
static void MX_SDFM_Init(void);
static void ADC_CNF(void);
extern volatile struct ADC_REGS ADC0Regs;
extern volatile struct ADC_REGS ADC1Regs;
extern volatile struct SDFM_REGS SDFMRegs;
extern volatile struct EPWM_REGS *EPWM[];
extern volatile struct HCL_REGS *HCL[];
uint32_t ad_u_disp =0;
uint32_t sdfm_num_u = 0x2;
uint32_t sdfm_num_v = 0x3;
uint32_t motor_adc_sel = 0;
volatile int32_t adc_u[4],adc_v[4];
//u,v相的PGA参数一致 无放大，即GAIN = 1
void PGA_PINMUX(ENUM_PGA_NUM pga_num)
{
	switch(pga_num)
	{
	case PGA0_NUM:
		gpio_enable(GPIO_GRP_A, 0, 2, GPIO_FUN_DIS);
		break;
	case PGA1_NUM:
		gpio_enable(GPIO_GRP_A, 2, 2, GPIO_FUN_DIS);
		break;
	case PGA2_NUM:
		gpio_enable(GPIO_GRP_A, 4, 2, GPIO_FUN_DIS);
		break;
	case PGA3_NUM:
		gpio_enable(GPIO_GRP_A, 6, 2, GPIO_FUN_DIS);
		break;
	default:
		break;
	}
}
void PGA_UV_Init(ENUM_PGA_NUM pga_num)
{
	PGA_PINMUX(pga_num);
	pga_ncal_set(pga_num, 0x80);//
	pga_pcal_set(pga_num, 0x80);

	pga_vcm_en(pga_num,0x1);	//选择内部的VCM做为PGA的VREF输入


	pga_inp_en(pga_num, 0x1);
	pga_inn_en(pga_num, 0x1);
	pga_r1_en(pga_num, 0x1);
	pga_r2_en(pga_num, 0x1);//
	pga_inres_en(pga_num, 0x1);
	pga_r4_en(pga_num, 0x1);//
	pga_opmod_sel(pga_num, 0x1);
	pga_flt_en(pga_num, 0);//0x1);
	//GAIN = r4/r3  =  r2 / r1
	pga_r1_set(pga_num, 0x1);		//R1 set 10k r1 == r3   0:短路 ，1：10K
	pga_r3_set(pga_num, 0x1);		//R2 set 10k  			0:短路 ，1：10K
	//R2=R4 = 20k ; R1=R3=10;
	pga_r2_set(pga_num, 0x1);//0X04);//0X02);//		//R2 set 10k r2 == r4
	pga_r4_set(pga_num, 0x1);//0X04);//0X02);//		//R2 set 10k
	pga_en(pga_num, 0x1);
}
void PGA_Init(void)
{
	cmu_mod_enable(CMU_MOD_PGA);

	PGA_UV_Init(PGA_U);//U相使用PGA2
	PGA_UV_Init(PGA_V);//V相使用PGA3
}

void psadc0_init(void)
{
	adc_init_cfg(ADC0_NUM);
#if (SDFM_USED == 0)//如果硬件是ADC电流采样
	if(HclSwitch.Hcl_EnableSw == 1)//硬件电环使能
	{
	   adc_hcl_en(ADC0_NUM);      //使能硬件电流环读队列0转换值
	   hcl_set_cur_src(0,0);//选择ADC作为电流采样的数据来源
	}
	else
	{
#ifdef ADC_CONNECT_PGA
	adc_smp_rate_set(ADC0_NUM, SMP_RATE_1MHZ);//采样频率为1MHz
	adc_q1_trig_sample_num(ADC0_NUM, SMP_2_NODE);
	adc_q1_node0_set(ADC0_NUM, 0x18+PGA_U);//设置队列1的采样点1为ADC0的U相PGA通道
	adc_q1_node1_set(ADC0_NUM, ADCCH8);//设置队列1的采样点2为ADC0的通道8
	adc_q1_cvra_en(ADC0_NUM);
//	adc_q1_osr_set(ADC0_NUM,1,1);//节点1四倍过采样 0:单点采样 1:2倍  2：4倍
	adc_en(ADC0_NUM);
#else
	adc_smp_rate_set(ADC0_NUM, SMP_RATE_1MHZ);//采样频率为1MHz
	adc_q1_trig_sample_num(ADC0_NUM, SMP_1_NODE);
//	adc_q1_node0_set(0, ADCCH4);//设置队列1的采样点0为ADC0的通道4
//	adc_q1_node1_set(0, ADCCH5);//设置队列1的采样点1为ADC0的通道5
	adc_q1_node0_set(ADC0_NUM, ADCCH8);//设置队列1的采样点2为ADC0的通道8
	adc_q1_cvra_en(ADC0_NUM);
	adc_en(ADC0_NUM);
#endif

	}
#else
	adc_smp_rate_set(ADC0_NUM, SMP_RATE_1MHZ);//采样频率为1MHz
	adc_q1_trig_sample_num(ADC0_NUM, SMP_1_NODE);
//	adc_q1_node0_set(0, ADCCH4);//设置队列1的采样点0为ADC0的通道4
//	adc_q1_node1_set(0, ADCCH5);//设置队列1的采样点1为ADC0的通道5
	adc_q1_node0_set(ADC0_NUM, ADCCH8);//设置队列1的采样点2为ADC0的通道8
	adc_q1_cvra_en(ADC0_NUM);
	adc_en(ADC0_NUM);

	gtc_dly_time(GTC_MS, 1);                    //ADC0校准
	adc_capcalcsr(ADC0_NUM);
	adc_calcsr(ADC0_NUM);
	if(HclSwitch.Hcl_EnableSw == 1)//硬件电环使能
	{
		adc_hcl_en(ADC0_NUM);      //使能硬件电流环读队列0转换值
	}
#endif
}

void psadc1_init(void)
{
#if 1
	adc_init_cfg(0x1);
#if (SDFM_USED == 0)//如果硬件是ADC电流采样
	if(HclSwitch.Hcl_EnableSw == 1)//硬件电环使能
	{
	   adc_hcl_en(1);      //使能硬件电流环读队列0转换值
	   hcl_set_cur_src(0,0);//选择ADC作为电流采样的数据来源
	}
	else
	{
	#ifdef ADC_CONNECT_PGA
		adc_init_cfg(ADC1_NUM);

		adc_smp_rate_set(ADC1_NUM, SMP_RATE_1MHZ);//采样频率为1MHz
		adc_q1_trig_sample_num(ADC1_NUM, SMP_2_NODE);
		adc_q1_node0_set(ADC1_NUM, 0x18+PGA_V);//设置队列1的采样点1为ADC1的V相PGA通道
		adc_q1_node1_set(ADC1_NUM, ADCCH8);//设置队列1的采样点2为ADC0的通道8

		adc_q1_cvra_en(ADC1_NUM);
//		adc_q1_osr_set(ADC1_NUM,1,1);//节点1四倍过采样
		adc_en(ADC1_NUM);

		gtc_dly_time(GTC_MS, 1);                     //ADC1校准
		adc_capcalcsr(ADC1_NUM);
		adc_calcsr(ADC1_NUM);

	#endif

	}
#else
	if(HclSwitch.Hcl_EnableSw == 1)//硬件电环使能
	{
		adc_hcl_en(ADC1_NUM);      //使能硬件电流环读队列0转换值
	}
#endif

#endif
}
static void ADC_CNF(void)
{
	psadc0_init();
	psadc1_init();
#ifdef ADC_CONNECT_PGA
	PGA_Init();
#endif
}


static void MX_ADC_Init(void)
{
	//ADC初始化
	//1、ADC时钟初始化配置
	//**************************************
	adc_cmu_init();

	//2、ADC管脚初始化配置
	//**************************************
	//gpio_enable(GPIO_GRP_A, 8, 1, GPIO_FUN_7);//规划PA0为A/D采样输入
	//3、ADC初始化配置
	//**************************************

	ADC_CNF();

	//4、ADC自动校准
	//**************************************
	//adc_calibration_en(0);
	//adc_calibration_en(1);


}
static void sdfm_fault_rec_init(uint32_t sdfm_num,uint32_t epwm_num)
{
	switch(sdfm_num)
	{
	    case 0:
	    	(*EPWM[epwm_num]).PWM_RCFLT_IN.bit.SDFM0_COL_EN = P_ENABLE;//低位比较中断禁止
	    	(*EPWM[epwm_num]).PWM_RCFLT_IN.bit.SDFM0_COH_EN = P_ENABLE; //高位比较中断使能
	    	(*EPWM[epwm_num]).PWM_FAULT_INT.bit.REC_FAULT_INT_EN = P_ENABLE;//使能EPWM可恢复中断
		break;
	    case 1:
	    	(*EPWM[epwm_num]).PWM_RCFLT_IN.bit.SDFM1_COL_EN = P_ENABLE;//低位比较中断使能
	    	(*EPWM[epwm_num]).PWM_RCFLT_IN.bit.SDFM1_COH_EN = P_ENABLE; //高位比较中断禁止
	    	(*EPWM[epwm_num]).PWM_FAULT_INT.bit.REC_FAULT_INT_EN = P_ENABLE;//使能EPWM可恢复中断
	    break;
	    case 2:
	    	(*EPWM[epwm_num]).PWM_RCFLT_IN.bit.SDFM2_COL_EN = P_ENABLE;//低位比较中断使能
	    	(*EPWM[epwm_num]).PWM_RCFLT_IN.bit.SDFM2_COH_EN = P_ENABLE; //高位比较中断禁止
	    	(*EPWM[epwm_num]).PWM_FAULT_INT.bit.REC_FAULT_INT_EN = P_ENABLE;//使能EPWM可恢复中断
	    break;
	    case 3:
	    	(*EPWM[epwm_num]).PWM_RCFLT_IN.bit.SDFM3_COL_EN = P_ENABLE;//低位比较中断使能
	    	(*EPWM[epwm_num]).PWM_RCFLT_IN.bit.SDFM3_COH_EN = P_ENABLE; //高位比较中断禁止
	    	(*EPWM[epwm_num]).PWM_FAULT_INT.bit.REC_FAULT_INT_EN = P_ENABLE;//使能EPWM可恢复中断
	    break;
	    default:break;
	}
}

static void sdfm_fault_nrec_init(u32 sdfm_num,u32 epwm_num)
{
	switch(sdfm_num)
	{
	    case 0:
	    	(*EPWM[epwm_num]).PWM_NRCFLT_IN.bit.SDFM0_COL_EN = P_ENABLE;//低位比较中断禁止
	    	(*EPWM[epwm_num]).PWM_NRCFLT_IN.bit.SDFM0_COH_EN = P_ENABLE; //高位比较中断使能
	    	(*EPWM[epwm_num]).PWM_FAULT_INT.bit.NREC_FAULT_INT_EN = P_ENABLE;//使能EPWM可不恢复中断
		break;
	    case 1:
	    	(*EPWM[epwm_num]).PWM_NRCFLT_IN.bit.SDFM1_COL_EN = P_ENABLE;//低位比较中断使能
	    	(*EPWM[epwm_num]).PWM_NRCFLT_IN.bit.SDFM1_COH_EN = P_ENABLE; //高位比较中断禁止
	    	(*EPWM[epwm_num]).PWM_FAULT_INT.bit.NREC_FAULT_INT_EN = P_ENABLE;//使能EPWM不可恢复中断
	    break;
	    case 2:
	    	(*EPWM[epwm_num]).PWM_NRCFLT_IN.bit.SDFM2_COL_EN = P_ENABLE;//低位比较中断使能
	    	(*EPWM[epwm_num]).PWM_NRCFLT_IN.bit.SDFM2_COH_EN = P_ENABLE; //高位比较中断禁止
	    	(*EPWM[epwm_num]).PWM_FAULT_INT.bit.NREC_FAULT_INT_EN = P_ENABLE;//使能EPWM不可恢复中断
	    break;
	    case 3:
	    	(*EPWM[epwm_num]).PWM_NRCFLT_IN.bit.SDFM3_COL_EN = P_ENABLE;//低位比较中断使能
	    	(*EPWM[epwm_num]).PWM_NRCFLT_IN.bit.SDFM3_COH_EN = P_ENABLE; //高位比较中断禁止
	    	(*EPWM[epwm_num]).PWM_FAULT_INT.bit.NREC_FAULT_INT_EN = P_ENABLE;//使能EPWM不可恢复中断
	    break;
	    default:break;
	}
}
static void epwm_sync_out_sel(u32 num,u32 osr)
{
    if(osr == 0)
    {
    	/*
		 * 根据手册，同步后，3阶滤波器前两个数据点错误，需要提前 PRD_VAL 配置采集3个周期时间
		 * SINC3 type, OSR = 64 SDFM采集完成时间通过测量是3.2us
		 * 1.6 * 3 = 4.8us; UAV = 4.8us  / 4.1666ns(EPWM时钟周期为240MHz)，这样PRD_VAL中断来后，读取的SDFM数据是最新的数据。
		 */
		(*EPWM[num]).PWM_CNT_AV.bit.CNT_AV = (*EPWM[num]).PWM_CNT_PRDV.bit.PRD_VAL - 1152-240;
    }
    else if(osr == 1)
    {
    	/*
		 * 根据手册，同步后，3阶滤波器前两个数据点错误，需要提前 PRD_VAL 配置采集3个周期时间
		 * SINC3 type, OSR = 64 SDFM采集完成时间通过测量是3.2us
		 * 3.2 * 3 = 9.6us; UAV = 9.6us  / 4.1666ns(EPWM时钟周期为240MHz)，这样PRD_VAL中断来后，读取的SDFM数据是最新的数据。
		 */
		(*EPWM[num]).PWM_CNT_AV.bit.CNT_AV = (*EPWM[num]).PWM_CNT_PRDV.bit.PRD_VAL - 2034-240;

    }
    else if(osr == 2)
    {
    	/*
		 * 根据手册，同步后，3阶滤波器前两个数据点错误，需要提前 PRD_VAL 配置采集3个周期时间
		 * SINC3 type, OSR = 128 SDFM采集完成时间通过测量是6.4us
		 * 6.4 * 3 = 19.2us; 19.2us / 4.1666ns(EPWM时钟周期为240MHz),这样PRD_VAL中断来后，读取的SDFM数据是最新的数据。
		 */
		(*EPWM[num]).PWM_CNT_AV.bit.CNT_AV = (*EPWM[num]).PWM_CNT_PRDV.bit.PRD_VAL - 4608 - 240;

    }
    else if(osr == 3)
	{
    	/*
		 * 根据手册，同步后，3阶滤波器前两个数据点错误，需要提前 PRD_VAL 配置采集3个周期时间
		 * SINC3 type, OSR = 256 SDFM采集完成时间通过测量是12.8us
		 * 12.8 * 3 = 38.4us; 38.4us / 4.1666ns(EPWM时钟周期为240MHz),这样PRD_VAL中断来后，读取的SDFM数据是最新的数据。
		 */
		(*EPWM[num]).PWM_CNT_AV.bit.CNT_AV = (*EPWM[num]).PWM_CNT_PRDV.bit.PRD_VAL - 9216 - 240;

	}
    else
    {
    	/*
		 * 根据手册，同步后，3阶滤波器前两个数据点错误，需要提前 PRD_VAL 配置采集3个周期时间
		 * SINC3 type, OSR = 64 SDFM采集完成时间通过测量是3.2us
		 * 3.2 * 3 = 9.6us; 9.6us / 4.1666ns(EPWM时钟周期为240MHz),这样PRD_VAL中断来后，读取的SDFM数据是最新的数据。
		 */
    	(*EPWM[num]).PWM_CNT_AV.bit.CNT_AV = (*EPWM[num]).PWM_CNT_PRDV.bit.PRD_VAL - 2034-240;
    }


	(*EPWM[num]).PWM_SC_SCTL.bit.SDFM_SYNC_EN = 1; //SDFM同步信号输出使能
	(*EPWM[num]).PWM_SC_SCTL.bit.SDFM_SYNC_SRC = SRC_CNT_UAV;//选择EPWM周期信号作为同步信号
	(*EPWM[num]).PWM_SC_SDIV.bit.SDFM_SYNC_DIV = 1;//同步信号产生一次则对应产生一次有效同步信号

}

static void sdfm_sync_source(uint32_t sdfm_num,uint32_t epwm_num)
{
	switch(sdfm_num)
	{
		case 0:
				SDFMRegs.PSINC_SET0.bit.SYNC_SRC_SEL = epwm_num;
				SDFMRegs.PSINC_SET0.bit.PSINC_SYNC_EN = 0x1;//同步使能
		break;
		case 1:
				SDFMRegs.PSINC_SET1.bit.SYNC_SRC_SEL = epwm_num;
				SDFMRegs.PSINC_SET1.bit.PSINC_SYNC_EN = 0x1;//同步使能
		break;
		case 2:
				SDFMRegs.PSINC_SET2.bit.SYNC_SRC_SEL = epwm_num;
				SDFMRegs.PSINC_SET2.bit.PSINC_SYNC_EN = 0x1;//同步使能
		break;
		case 3:
				SDFMRegs.PSINC_SET3.bit.SYNC_SRC_SEL = epwm_num;
				SDFMRegs.PSINC_SET3.bit.PSINC_SYNC_EN = 0x1;//同步使能
		break;
		default:
		break;
	}
}
static void sdfm_ssin_set_th_high(uint32_t num,uint32_t data)
{
	switch(num)
	{
		case 0:
		   SDFMRegs.SSINC_TH0.bit.HLT = data;   //ssinc0高位比较值

		break;
		case 1:
		   SDFMRegs.SSINC_TH1.bit.HLT = data;   //ssinc1高位比较值

		break;
		case 2:
		   SDFMRegs.SSINC_TH2.bit.HLT = data;    //ssinc2高位比较值

		break;
		case 3:
		   SDFMRegs.SSINC_TH3.bit.HLT = data;    //ssinc3高位比较值

		break;
		default:break;
	}
}

static void sdfm_ssin_set_th_low(uint32_t num,uint32_t data)
{
	switch(num)
	{
		case 0:
		   SDFMRegs.SSINC_TH0.bit.LLT = data;      //ssinc0低位比较值
		break;
		case 1:
		   SDFMRegs.SSINC_TH1.bit.LLT = data;      //ssinc1低位比较值
		break;
		case 2:
		   SDFMRegs.SSINC_TH2.bit.LLT = data;      //ssinc2低位比较值
		break;
		case 3:
		   SDFMRegs.SSINC_TH3.bit.LLT = data;      //ssinc3低位比较值
		break;
		default:break;
	}
}
void sdfm_fault_int_enable(uint32_t num)
{
	switch(num)
	{
		case 0:
		   SDFMRegs.SDFM_INT_EN0.bit.MOD_FAIL_INT_EN = 1;   //调制器异常中断使能
		break;
		case 1:
			SDFMRegs.SDFM_INT_EN1.bit.MOD_FAIL_INT_EN = 1;   //调制器异常中断使能
		break;
		case 2:
			SDFMRegs.SDFM_INT_EN2.bit.MOD_FAIL_INT_EN = 1;   //调制器异常中断使能
		break;
		case 3:
			SDFMRegs.SDFM_INT_EN3.bit.MOD_FAIL_INT_EN = 1;   //调制器异常中断使能
		break;
		default:break;
	}
}
void sdfm_fault_int_clear(uint32_t num)
{
	switch(num)
	{
		case 0:
		   SDFMRegs.SDFM_FLG0.bit.MOD_FAIL_FLG = 1;   //调制器异常中断清除
		break;
		case 1:
			SDFMRegs.SDFM_FLG1.bit.MOD_FAIL_FLG = 1;   //调制器异常中断清除
		break;
		case 2:
			SDFMRegs.SDFM_FLG2.bit.MOD_FAIL_FLG = 1;   //调制器异常中断清除
		break;
		case 3:
			SDFMRegs.SDFM_FLG3.bit.MOD_FAIL_FLG = 1;   //调制器异常中断清除
		break;
		default:break;
	}
}
uint32_t sdfm_comp_high_flag_read(uint32_t num)
{
	uint32_t sdfm_sts;
	switch(num)
	{
		case 0:
			sdfm_sts = SDFMRegs.SDFM_FLG0.bit.COMP_H_FLG;   //SDFM0高位比较状态位
		break;
		case 1:
			sdfm_sts = SDFMRegs.SDFM_FLG1.bit.COMP_H_FLG;  //SDFM1高位比较状态位
		break;
		case 2:
			sdfm_sts = SDFMRegs.SDFM_FLG2.bit.COMP_H_FLG;  //SDFM2高位比较状态位
		break;
		case 3:
			sdfm_sts = SDFMRegs.SDFM_FLG3.bit.COMP_H_FLG;  //SDFM3高位比较状态位
		break;
		default:break;
	}
	return(sdfm_sts);
}

uint32_t sdfm_comp_low_flag_read(uint32_t num)
{
	uint32_t sdfm_sts;
	switch(num)
	{
		case 0:
			sdfm_sts = SDFMRegs.SDFM_FLG0.bit.COMP_L_FLG;   //SDFM0低位比较状态位
		break;
		case 1:
			sdfm_sts = SDFMRegs.SDFM_FLG1.bit.COMP_L_FLG;   //SDFM1低位比较状态位
		break;
		case 2:
			sdfm_sts = SDFMRegs.SDFM_FLG2.bit.COMP_L_FLG;   //SDFM2低位比较状态位
		break;
		case 3:
			sdfm_sts = SDFMRegs.SDFM_FLG3.bit.COMP_L_FLG;   //SDFM3低位比较状态位
		break;
		default:break;
	}
	return(sdfm_sts);
}
void sdfm_comp_high_flag_clr(uint32_t num)
{
	switch(num)
	{
		case 0:
			SDFMRegs.SDFM_FLG0.bit.COMP_H_FLG = 0x01;   //SDFM0高位比较状态位写1清0
		break;
		case 1:
			SDFMRegs.SDFM_FLG1.bit.COMP_H_FLG = 0x01;   //SDFM1高位比较状态位写1清0
		break;
		case 2:
			SDFMRegs.SDFM_FLG2.bit.COMP_H_FLG = 0x01;   //SDFM2高位比较状态位写1清0
		break;
		case 3:
			SDFMRegs.SDFM_FLG3.bit.COMP_H_FLG = 0x01;   //SDFM3高位比较状态位写1清0
		break;
		default:break;
	}
}
void sdfm_comp_low_flag_clr(uint32_t num)
{
	switch(num)
	{
		case 0:
			SDFMRegs.SDFM_FLG0.bit.COMP_L_FLG = 0x01;   //SDFM0低位比较状态位写1清0
		break;
		case 1:
			SDFMRegs.SDFM_FLG1.bit.COMP_L_FLG = 0x01;   //SDFM1低位比较状态位写1清0
		break;
		case 2:
			SDFMRegs.SDFM_FLG2.bit.COMP_L_FLG = 0x01;   //SDFM2低位比较状态位写1清0
		break;
		case 3:
			SDFMRegs.SDFM_FLG3.bit.COMP_L_FLG = 0x01;   //SDFM3低位比较状态位写1清0
		break;
		default:break;
	}
}
static void sdfm_init(u32 num,u32 osr)
{
	sdfm_mod_set(num,SDFM_IN_MOD0);
	if(osr == 0)
	{
		sdfm_psinc_set(num,SINC3, 31);         //SINC3 type, OSR = 64
		sdfm_set_data_shift(num, 0x0);
	}
	else if(osr == 1)
	{
		sdfm_psinc_set(num,SINC3, 63);         //SINC3 type, OSR = 64
		sdfm_set_data_shift(num, 0x3);

	}
	else if(osr == 2)
	{
		sdfm_psinc_set(num,SINC3, 127);         //SINC3 type, OSR = 128
		sdfm_set_data_shift(num, 0x6);

	}
	else if(osr == 3)
	{
		sdfm_psinc_set(num,SINC3, 255);         //SINC3 type, OSR = 256
		sdfm_set_data_shift(num, 0x9);

	}
	else
	{
		sdfm_psinc_set(num,SINC3, 63);         //SINC3 type, OSR = 64
		sdfm_set_data_shift(num, 0x3);
	}
	sdfm_set_data_width(num, WIDTH_16);
	sdfm_ssinc_set(num,SINC2,31);           // SINC2 type,OSR = 32;
	switch(num)
	{
		case 0:
		   SDFMRegs.SSINC_SET0.bit.SFEN = 1;       //ssinc0滤波使能
		   SDFMRegs.SDFM_CTL0.bit.SDIN_CLK_INV = 0;//接3peak时钟极性取反，保证数据都能读到。
		break;
		case 1:
		   SDFMRegs.SSINC_SET1.bit.SFEN = 1;       //ssinc1滤波使能
		   SDFMRegs.SDFM_CTL1.bit.SDIN_CLK_INV = 0;//接3peak时钟极性取反，保证数据都能读到。
		break;
		case 2:
		   SDFMRegs.SSINC_SET2.bit.SFEN = 1;       //ssinc2滤波使能
		   SDFMRegs.SDFM_CTL2.bit.SDIN_CLK_INV = 0;//接3peak时钟极性取反，保证数据都能读到。
		break;
		case 3:
		   SDFMRegs.SSINC_SET3.bit.SFEN = 1;	   //ssinc3滤波使能
		   SDFMRegs.SDFM_CTL3.bit.SDIN_CLK_INV = 0;//接3peak时钟极性取反，保证数据都能读到。
		break;
		default:break;
	}
}

void sdfm_irqhandler_isr(void)
{
	uint32_t sts = 0;
	static int i = 0;

	sts = sdfm_get_irq_sts(sdfm_num_u);

	if((sts & SDFM_DAT_DONE_STS_PEND) == SDFM_DAT_DONE_STS_PEND) {
		sdfm_clr_irq_sts(sdfm_num_u, SDFM_DAT_DONE_STS_PEND);
		i++;
	}
}

void MX_SDFM_Init(void)
{
	//SDFM初始化
	//1、SDFM管脚初始化
	//**************************************
	sdfm_pinmux_init(sdfm_num_u);
	sdfm_pinmux_init(sdfm_num_v);

	//2、SDFM时钟初始化
	//**************************************
	sdfm_cmu_init();

    //使能输出时钟
    gpio_pin_cfg(GPIO_GRP_A,4,1,GPIO_DRV_45R,GPIO_PULL_NONE);//增强SDFM时钟输出的驱动能力
    gpio_pin_cfg(GPIO_GRP_A,6,1,GPIO_DRV_45R,GPIO_PULL_NONE);//增强SDFM时钟输出的驱动能力
    sdfm_clk_div(12);//SDFM模块时钟是240Mhz,12分频后得到20Mhz的采样时钟
    sdfm_clk_out_en(sdfm_num_u);
    sdfm_clk_out_en(sdfm_num_v);

	//3、SDFM配置初始化
	//**************************************
    sdfm_init(sdfm_num_u,Servo.Pn02.SdfmOsr.Data);
    sdfm_init(sdfm_num_v,Servo.Pn02.SdfmOsr.Data);
    //4、SSINC比较配置
	if(HclSwitch.Sdfm_sync_EnableSw == 1)
	{
		epwm_sync_out_sel(EPWM_SYNC_SDFM,Servo.Pn02.SdfmOsr.Data);//选择EPMW8作为SDFM同步转换信号
		sdfm_sync_source(sdfm_num_u,EPWM_SYNC_SDFM); //U相SDFM同步源选择为EPMW5
		sdfm_sync_source(sdfm_num_v,EPWM_SYNC_SDFM); //V相SDFM同步源选择为EPMW5
	}

	sdfm_ssin_set_th_high(sdfm_num_u,1020);//设置U相高位比较值,正向电流保护阈值
	sdfm_ssin_set_th_high(sdfm_num_v,1020);//设置V相高位比较值,正向电流保护阈值
	sdfm_ssin_set_th_low(sdfm_num_u,0);    //设置U相低位比较值,负向电流保护阈值
	sdfm_ssin_set_th_low(sdfm_num_v,0);    //设置V相低位比较值,负向电流保护阈值
//	使能EPWM的SDFM比较中断源
	sdfm_fault_nrec_init(sdfm_num_u,Aixse1_EPWM_U);
	sdfm_fault_nrec_init(sdfm_num_v,Aixse1_EPWM_U);
	sdfm_fault_nrec_init(sdfm_num_u,Aixse1_EPWM_V);
	sdfm_fault_nrec_init(sdfm_num_v,Aixse1_EPWM_V);
	sdfm_fault_nrec_init(sdfm_num_u,Aixse1_EPWM_W);
	sdfm_fault_nrec_init(sdfm_num_v,Aixse1_EPWM_W);

//	sdfm_fault_int_enable(sdfm_num_u);//使能U相SDFM调制器错误中断
//	sdfm_fault_int_enable(sdfm_num_v);//使能V相SDFM调制器错误中断

	//4、SDFM使能
	//**************************************
	sdfm_en(sdfm_num_u);
	sdfm_en(sdfm_num_v);

}
void M680X_ileg2_dcbus_drv_init(ILEG2DCBUSMEAS *p)
{
#if   (SDFM_USED == 1)
	MX_SDFM_Init(); //SDFM模块初始化

#endif
	MX_ADC_Init();  //片上ADC模块初始化
}

void M680X_ileg2_dcbus_drv_read(ILEG2DCBUSMEAS *p)
{
	/*
	 * SDFM转换结果读取
	 */
	if(HclSwitch.Hcl_EnableSw == 0)//软件电流环
	{
#ifdef ADC_CONNECT_PGA
	int32_t dat_q15;
	int32_t adc_result=0;

	do{

	} while ((ADC0Regs.ADC_MSR.bit.Q1_INT) != 0x1);
	adc_u[0] = ADC0Regs.ADC_Q1FDR.bit.DATA & 0x3FFF;	//U
	adc_u[1] = ADC0Regs.ADC_Q1FDR.bit.DATA & 0x3FFF;	//vdc

	adc_v[0] = ADC1Regs.ADC_Q1FDR.bit.DATA & 0x3FFF;//V
	adc_v[1] = ADC1Regs.ADC_Q1FDR.bit.DATA & 0x3FFF;	//vdc

	adc_result = adc_u[0];	//读ADC的U相电流数据
	dat_q15 = -(adc_result - p->Imeas_ref_ad0);
	p->Imeas_a = (dat_q15<<1);//

	adc_result = adc_v[0];	//读ADC的V相电流数据
	dat_q15 = -(adc_result - p->Imeas_ref_ad1);
	p->Imeas_b = (dat_q15<<1);//


	p->Imeas_c = -(p->Imeas_a + p->Imeas_b);

	p->Vdc_meas = (adc_u[1]+adc_v[1])>>1;	//读ADC的母线电压数据

#else
		p->Imeas_a = -((s16)(sdfm_get_data(sdfm_num_u) & 0xffff)- p->Imeas_ref_ad0);
		p->Imeas_b = -((s16)(sdfm_get_data(sdfm_num_v) & 0xffff)- p->Imeas_ref_ad1);
		p->Imeas_c = -(p->Imeas_a + p->Imeas_b);
		do{

		} while ((ADC0Regs.ADC_MSR.bit.Q1_INT) != 0x1);
		p->Vdc_meas = adc_rd_ch_res(0,0x8);
#endif
	}
	else
	{
		/*
		 * 硬件电流环寄存器模式下电流采样值通过软件写入,需要执行hcl_cur_dat_sel(0,1);
		 * 否则硬件电流环时会自动读取SDFM结果寄存器的值
		 */

		if(HclSwitch.SdfmFromRegSw == 1)
		{
			p->Imeas_a = -((s16)(sdfm_get_data(sdfm_num_u) & 0xffff)- p->Imeas_ref_ad0);
			p->Imeas_b = -((s16)(sdfm_get_data(sdfm_num_v) & 0xffff)- p->Imeas_ref_ad1);
			hcl_reg_usrc_set(Aixse1_HCL_NUM,p->Imeas_a);
			hcl_reg_vsrc_set(Aixse1_HCL_NUM,p->Imeas_b);
		}
		/*
		 * 读取母线电压ADC转换值（14bit）
		 * 是哪个转换通道就读哪个
		 */
		 do{

		 } while ((ADC0Regs.ADC_MSR.bit.Q1_INT) != 0x1);
		 p->Vdc_meas = adc_rd_ch_res(0,0x8);
	}



	 adc_fifo1_flush(0);
	 adc_fifo1_flush(1);
	 ADC0Regs.ADC_MSR.bit.Q1_INT = 0x1;	//清除Q1INT状态
}
void M680X_ileg2_dcbus_drv_filter(ILEG2DCBUSMEAS *p)
{
#ifdef ADC_CONNECT_PGA
//	do{
//
//	} while ((ADC0Regs.ADC_MSR.bit.Q1_INT) != 0x1);
	adc_u[0] = ADC0Regs.ADC_Q1FDR.bit.DATA & 0x3FFF;	//U
	adc_u[1] = ADC0Regs.ADC_Q1FDR.bit.DATA & 0x3FFF;	//vdc

	adc_v[0] = ADC1Regs.ADC_Q1FDR.bit.DATA & 0x3FFF;//V
	adc_v[1] = ADC1Regs.ADC_Q1FDR.bit.DATA & 0x3FFF;	//vdc

    p->Imeas_a = adc_u[0];
    p->Imeas_b = adc_v[0];
#else
	p->Imeas_a = (s16)(sdfm_get_data(sdfm_num_u) & 0xffff);
	p->Imeas_b = (s16)(sdfm_get_data(sdfm_num_v) & 0xffff);
#endif
	p->Vdc_meas = adc_rd_ch_res(0,0x8);

	if(p->ad_sample_en == 1)
	{
		p->_int_ad_sample++;
	}
	if(p->_int_ad_sample >=9487)
	{
		p->_long_sum_ad0 += p->Imeas_a;	//读ADC的U相电流数据
		p->_long_sum_ad1 += p->Imeas_b;	//读ADC的W相电流数据
		if(p->_int_ad_sample == 9999)
		{
			 p->ad_sample_en = 0;
			 p->_int_ad_sample = 100;
			 p->_long_avg_ad0 =  p->_long_sum_ad0>>9;
			 p->_long_avg_ad1 =  p->_long_sum_ad1>>9;

			 p->Imeas_ref_ad0 = p->_long_avg_ad0;
			 p->Imeas_ref_ad1 = p->_long_avg_ad1;

#ifdef ADC_CONNECT_PGA
			   if(ilg2_vdc1.Imeas_ref_ad0 <= ADC_REF_MIN || ilg2_vdc1.Imeas_ref_ad0 >= ADC_REF_MAX)
			   {
					Err.MainCurRefErrFlag = 1;
			   }
			   if(ilg2_vdc1.Imeas_ref_ad1 <= ADC_REF_MIN || ilg2_vdc1.Imeas_ref_ad1 >= ADC_REF_MAX)
			   {
					Err.MainCurRefErrFlag = 1;
			   }
#else
			 /*
			  * 检测SDFM转换芯片是否异常，如是否焊、初始偏置电压是否在范围内
			  */
			   //wenxuan
//			 if((p->Imeas_ref_ad0 < -1000) ||(p->Imeas_ref_ad0 >= 1000) ||
//			 	(p->Imeas_ref_ad1 < -1000)|| (p->Imeas_ref_ad1 >= 1000))
//			 {
//				 Err.MainCurRefErrFlag = 1;
//				 Err.ServoAlarmFlag = 1;
//			 }

			 //设置U相SDFM采样偏置电流
			 hcl_sdfm_uoff_set(Aixse1_HCL_NUM,p->Imeas_ref_ad0);
			 //设置V相SDFM采样偏置电流
			 hcl_sdfm_voff_set(Aixse1_HCL_NUM,p->Imeas_ref_ad1);
#endif
		}
	}
	adc_fifo1_flush(0);
	adc_fifo1_flush(1);
	ADC0Regs.ADC_MSR.bit.Q1_INT = 0x1;	//清除Q1INT状态
}
void M680X_ileg2_dcbus_drv_calc(ILEG2DCBUSMEAS *p)
{

}
