/*
 * mainIint_m680x.c
 *
 *  Created on: 2024年3月29日
 *      Author: L
 */
#include "all_inc.h"
#include "M680x_it.h"
#include "servo_drv_setting.h"
extern volatile struct HCL_REGS *HCL[];
extern volatile struct EPWM_REGS *EPWM[];
extern volatile struct GLB_PWMCS_REGS Glb_Pwmcs_Regs;
extern volatile struct QEP_REGS *QEP[];
extern volatile struct COR_REGS Cor_Regs;
void MS_GPIO_Init(void);
void MS_EPWM_Init(void);
void FAULT_NREC_INIT(uint32_t num);
void MS_PulseCommand_Init(void);
void QEP_CNF(uint32_t n);
void xpwm_timer_2ms_Init(void);
void cordic_cal_int(COR_FUNC_TYP funsel, COR_ITER_TYP iteration, s32 data2);
void IRQHandler_set_prio(void);
void MS_GPIO_Init(void)
{
//	gpio_enable(ioPowerOffIn, 1, GPIO_FUN_I);  //PRO2
	gpio_enable(ioPowerHighIn, 1, GPIO_FUN_I); //PRO3
	gpio_enable(ioPowerLowIn, 1, GPIO_FUN_I);  //PRO4
	gpio_enable(ioBreakErrIn, 1, GPIO_FUN_I);  //PRO5

	gpio_enable(DI1, 1, GPIO_FUN_I);            //SON
	gpio_enable(DI2, 1, GPIO_FUN_I);            //SPD2-SPD11

//	gpio_enable(DISP_KEY, 1, GPIO_FUN_I);  //DISP_KEY
//
//	gpio_enable(DISP_KDP, 1, GPIO_FUN_O);  //DISP_KDP
//	gpio_set_val(DISP_KDP, GPIO_LEVEL_LOW);
#ifndef KEY_DISPLAY_USE_SPI
	gpio_enable(DISP_DAT, 1, GPIO_FUN_O);  //DISP_DAT
	gpio_set_val(DISP_DAT, GPIO_LEVEL_LOW);

	gpio_enable(DISP_CLK, 1, GPIO_FUN_O);  //DISP_CLK
	gpio_set_val(DISP_CLK, GPIO_LEVEL_LOW);
#endif
	gpio_enable(DISP_CS, 1, GPIO_FUN_O);  //DISP_CS
    gpio_set_val(DISP_CS, GPIO_LEVEL_HIGH);

//    gpio_enable(ioReLayOut, 1, GPIO_FUN_O);  //ZDD
//    gpio_set_val(ioReLayOut, GPIO_LEVEL_LOW);

    gpio_enable(E2PROM_CS, 1, GPIO_FUN_O);  //E2PROM_CS
    gpio_set_val(E2PROM_CS, GPIO_LEVEL_HIGH);

    gpio_enable(ioPWMcsOut, 1, GPIO_FUN_O); //PWMCS
    gpio_set_val(ioPWMcsOut, GPIO_LEVEL_HIGH);

    gpio_enable(DO1, 1, GPIO_FUN_O);  //SRDY-Z
    gpio_set_val(DO1, GPIO_LEVEL_LOW);

    gpio_enable(DO2, 1, GPIO_FUN_O);  //ALM
    gpio_set_val(DO2, GPIO_LEVEL_LOW);

}
void FAULT_NREC_INIT(uint32_t num)
{
	(*EPWM[num]).PWM_FAULT_IN.bit.FAULT0_POL      = FAULT_HIGH;   //故障信号极性，高电平正常，低电平异常
	(*EPWM[num]).PWM_FAULT_IN.bit.NREC_FAULT0_EN  = P_ENABLE;     //使能不可恢复的故障信号0
	(*EPWM[num]).PWM_FAULT_INT.bit.NREC_FAULT_INT_EN = P_ENABLE;  //不可恢复故障中断使能
	//滤波的计算方式是采样点 * 采样周期 = 12*(8*2 sysclk)
	Glb_Pwmcs_Regs.PWM_FAULTIN_FLT1.bit.FAULT0_SMP_CTL = 0x8;
	Glb_Pwmcs_Regs.PWM_FAULTIN_FLT1.bit.FAULT0_IN_FLT_SEL = 0xb;
}
void PWM_1ch_UpCnt_CNF(u32 n, u32 period, u32 db)
{
//
	(*EPWM[n]).PWM_CNT_CFG.bit.CNT_PRD_UPDT = IMED; // set Immediate load
	(*EPWM[n]).PWM_CNT_PRDV.bit.PRD_VAL = period-1; // PWM frequency = 1 / period
	(*EPWM[n]).PWM_CNT_PHV.bit.PH_VAL = 0;
	(*EPWM[n]).PWM_CNT_V.bit.CNT_VAL = 0;
	(*EPWM[n]).PWM_CNT_CFG.bit.CNT_MOD   = CNT_UP;
	(*EPWM[n]).PWM_CNT_CFG.bit.CLK_DIV1 = ADIV1;
	(*EPWM[n]).PWM_CNT_CFG.bit.CLK_DIV2 = BDIV1;
//      printk("0x %x \n", (*EPWM[n]).PWM_CNT_CFG);
//
	(*EPWM[n]).PWM_CNT_CFG.bit.CNT_PH_EN    = P_DISABLE;
	(*EPWM[n]).PWM_CNT_CFG.bit.SYNC_OUT = SO_CNTZ; // sync "down-stream"
	//
	//
	(*EPWM[n]).PWM_CNT_AV.bit.CNT_AV = 0; // set duty 0% initially
	(*EPWM[n]).PWM_UPDT_MODE.bit.CMPA_UPDT = IMED;
	//(*EPWM[n]).PWM_UPDT_MODE.bit.CMPA_LP = CNT_ZRO;//立即更新可以不用配置CMPA_LP
	//
	//
	(*EPWM[n]).PWM_A_ACT.bit.ACT_CNT_UAV = ACT_HIGH;
	(*EPWM[n]).PWM_A_ACT.bit.ACT_CNT_DAV = ACT_LOW;
	//
	//
	(*EPWM[n]).PWM_OUT_CONF.bit.BYPASS_SET  = NO_BP;
	(*EPWM[n]).PWM_OUT_CONF.bit.POL_SET = CHA_POST_CHB_NEGT;
	(*EPWM[n]).PWM_OUT_CONF.bit.CH_SET   = CHAB_SEL_PWMA;
	(*EPWM[n]).PWM_RE_DZCTL.bit.RE_DZCTL = db;
	(*EPWM[n]).PWM_FE_DZCTL.bit.FE_DZCTL = db;
}
// ONE PWM Configuration
void PWM_1ch_UpDwnCnt_CNF(uint32_t n, uint32_t period, uint32_t db)
{
	//
	(*EPWM[n]).PWM_CNT_CFG.bit.CNT_PRD_UPDT = IMED; // set Immediate load
	(*EPWM[n]).PWM_CNT_PRDV.bit.PRD_VAL = period / 2; // PWM frequency = 1 / period
	(*EPWM[n]).PWM_CNT_PHV.bit.PH_VAL = 0;
	(*EPWM[n]).PWM_CNT_V.bit.CNT_VAL = 0;
	(*EPWM[n]).PWM_CNT_CFG.bit.CNT_MOD   = CNT_UP_DOWN;
	(*EPWM[n]).PWM_CNT_CFG.bit.CLK_DIV1 = ADIV1;
	(*EPWM[n]).PWM_CNT_CFG.bit.CLK_DIV2 = BDIV1;

	(*EPWM[n]).PWM_CNT_CFG.bit.CNT_PH_EN    = P_DISABLE;
	(*EPWM[n]).PWM_CNT_CFG.bit.SYNC_OUT = SO_CNTZ; // sync "down-stream"

	(*EPWM[n]).PWM_CNT_AV.bit.CNT_AV = 0; // set duty 0% initially
	(*EPWM[n]).PWM_UPDT_MODE.bit.CMPA_UPDT = IMED;
	(*EPWM[n]).PWM_UPDT_MODE.bit.CMPA_LP = CNT_ZRO;

	(*EPWM[n]).PWM_A_ACT.bit.ACT_CNT_UAV = ACT_HIGH;
	(*EPWM[n]).PWM_A_ACT.bit.ACT_CNT_DAV = ACT_LOW;

	(*EPWM[n]).PWM_OUT_CONF.bit.BYPASS_SET  = NO_BP;
	(*EPWM[n]).PWM_OUT_CONF.bit.POL_SET = CHA_POST_CHB_NEGT;
	(*EPWM[n]).PWM_OUT_CONF.bit.CH_SET   = CHAB_SEL_PWMA;
	(*EPWM[n]).PWM_RE_DZCTL.bit.RE_DZCTL = db;
	(*EPWM[n]).PWM_FE_DZCTL.bit.FE_DZCTL = db;
}
void MS_EPWM_Init(void)
{
	//EPWM初始化
	//1、EPWM时钟初始化配置
	//**************************************
	pwmcs_cmu_init();

	//glb_hpwm_dll_ldo_en();					//优先使能LDO

	//2、EPWM0/1/2管脚配置
	//**************************************
	epwm_pinmux_init(Aixse1_EPWM_U);                    //初始化PWM0A/B的GPIO管脚
	epwm_pinmux_init(Aixse1_EPWM_V);                    //初始化PWM1A/B的GPIO管脚
	epwm_pinmux_init(Aixse1_EPWM_W);                    //初始化PWM2A/B的GPIO管脚

	//3、使能EPWM0/1/2时钟
	//**************************************
	epwm_clk_en(EPMW_CTRL_NUM);
	epwm_clk_en(Aixse1_EPWM_U);
	epwm_clk_en(Aixse1_EPWM_V);
	epwm_clk_en(Aixse1_EPWM_W);
	epwm_clk_en(EPWM_SYNC_HCL);	         //用于触发ADC HCL
	epwm_clk_en(EPWM_SDFM_CLK);	         //使能定时器6
	epwm_clk_en(EPWM_SYNC_SDFM);         //用于与SDFM同步
	//4、EPWM硬件初始化配置
	//**************************************
	if(Servo.Pn02.IsrFrequency.Data == 0) //10khz
		STR_FUNC_Gvar.System.EpwmInvPeriod = (SYSTEM_FREQUENCY *1000 /ISR_FREQUENCY1);
	else if(Servo.Pn02.IsrFrequency.Data == 1) //12.5khz
		STR_FUNC_Gvar.System.EpwmInvPeriod = (SYSTEM_FREQUENCY *1000 /ISR_FREQUENCY2);
	else if(Servo.Pn02.IsrFrequency.Data == 2) //16.0khz
		STR_FUNC_Gvar.System.EpwmInvPeriod = (SYSTEM_FREQUENCY *1000 /ISR_FREQUENCY3);
	else if(Servo.Pn02.IsrFrequency.Data == 3) //20.0khz
		STR_FUNC_Gvar.System.EpwmInvPeriod = (SYSTEM_FREQUENCY *1000 /ISR_FREQUENCY4);

	PWM_1ch_UpDwnCnt_CNF(EPMW_CTRL_NUM,STR_FUNC_Gvar.System.EpwmInvPeriod,0);//
	PWM_1ch_UpDwnCnt_CNF(Aixse1_EPWM_U,STR_FUNC_Gvar.System.EpwmInvPeriod,Servo.Pn04.DeadTime.Data);//360-死区时间1.5us左右
	PWM_1ch_UpDwnCnt_CNF(Aixse1_EPWM_V,STR_FUNC_Gvar.System.EpwmInvPeriod,Servo.Pn04.DeadTime.Data);
	PWM_1ch_UpDwnCnt_CNF(Aixse1_EPWM_W,STR_FUNC_Gvar.System.EpwmInvPeriod,Servo.Pn04.DeadTime.Data);
	if(HclSwitch.Hcl_EnableSw == 0)//软件电流环
	{
		PWM_1ch_UpDwnCnt_CNF(EPWM_SYNC_HCL,STR_FUNC_Gvar.System.EpwmInvPeriod/Servo.Pn02.HCLPeriodRatio.Data,0); //设置硬件电流环刷新周期
		PWM_1ch_UpDwnCnt_CNF(EPWM_SDFM_CLK,STR_FUNC_Gvar.System.EpwmInvPeriod,0);//设置同步定时器6周期
		PWM_1ch_UpDwnCnt_CNF(EPWM_SYNC_SDFM,STR_FUNC_Gvar.System.EpwmInvPeriod,0);//设置SDFM同步定时器周期
	}
	else
	{
		PWM_1ch_UpCnt_CNF(EPWM_SYNC_HCL,(STR_FUNC_Gvar.System.EpwmInvPeriod/2)/Servo.Pn02.HCLPeriodRatio.Data,0); //设置硬件电流环刷新周期
		PWM_1ch_UpCnt_CNF(EPWM_SDFM_CLK,(STR_FUNC_Gvar.System.EpwmInvPeriod/2),0);//设置同步定时器6周期
		PWM_1ch_UpCnt_CNF(EPWM_SYNC_SDFM,(STR_FUNC_Gvar.System.EpwmInvPeriod/2),0);//设置SDFM同步定时器周期
	}


	(*EPWM[Aixse1_EPWM_U]).PWM_CNT_CFG.bit.SYNC_OUT     = SYNCIN_OR_SW;
	(*EPWM[Aixse1_EPWM_U]).PWM_CNT_CFG.bit.CNT_PH_EN    = P_ENABLE;
	(*EPWM[Aixse1_EPWM_U]).PWM_CNT_PHV.bit.PH_VAL       = 0;
	(*EPWM[Aixse1_EPWM_U]).PWM_CNT_CFG.bit.CNT_PH_DIR   = DIR_INCR;

	(*EPWM[Aixse1_EPWM_V]).PWM_CNT_CFG.bit.SYNC_OUT     = SYNCIN_OR_SW;
	(*EPWM[Aixse1_EPWM_V]).PWM_CNT_CFG.bit.CNT_PH_EN    = P_ENABLE;
	(*EPWM[Aixse1_EPWM_V]).PWM_CNT_PHV.bit.PH_VAL       = 0;
	(*EPWM[Aixse1_EPWM_V]).PWM_CNT_CFG.bit.CNT_PH_DIR   = DIR_INCR;

	(*EPWM[Aixse1_EPWM_W]).PWM_CNT_CFG.bit.SYNC_OUT     = SYNCIN_OR_SW;
	(*EPWM[Aixse1_EPWM_W]).PWM_CNT_CFG.bit.CNT_PH_EN    = P_ENABLE;
	(*EPWM[Aixse1_EPWM_W]).PWM_CNT_PHV.bit.PH_VAL       = 0;
	(*EPWM[Aixse1_EPWM_W]).PWM_CNT_CFG.bit.CNT_PH_DIR   = DIR_INCR;

	(*EPWM[EPWM_SYNC_HCL]).PWM_CNT_CFG.bit.SYNC_OUT     = SYNCIN_OR_SW;
	(*EPWM[EPWM_SYNC_HCL]).PWM_CNT_CFG.bit.CNT_PH_EN    = P_ENABLE;
	(*EPWM[EPWM_SYNC_HCL]).PWM_CNT_PHV.bit.PH_VAL       = 0;
	(*EPWM[EPWM_SYNC_HCL]).PWM_CNT_CFG.bit.CNT_PH_DIR   = DIR_INCR;

	(*EPWM[EPWM_SDFM_CLK]).PWM_CNT_CFG.bit.SYNC_OUT     = SYNCIN_OR_SW;
	(*EPWM[EPWM_SDFM_CLK]).PWM_CNT_CFG.bit.CNT_PH_EN    = P_ENABLE;
	(*EPWM[EPWM_SDFM_CLK]).PWM_CNT_PHV.bit.PH_VAL       = 0;
	(*EPWM[EPWM_SDFM_CLK]).PWM_CNT_CFG.bit.CNT_PH_DIR   = DIR_INCR;

	(*EPWM[EPWM_SYNC_SDFM]).PWM_CNT_CFG.bit.SYNC_OUT     = SYNCIN_OR_SW;
	(*EPWM[EPWM_SYNC_SDFM]).PWM_CNT_CFG.bit.CNT_PH_EN    = P_ENABLE;
	(*EPWM[EPWM_SYNC_SDFM]).PWM_CNT_PHV.bit.PH_VAL       = 0;
	(*EPWM[EPWM_SYNC_SDFM]).PWM_CNT_CFG.bit.CNT_PH_DIR   = DIR_INCR;
	//配置ADC触发信号
	if(HclSwitch.Hcl_EnableSw == 1)//硬件电流环
	{
		(*EPWM[EPWM_SYNC_HCL]).PWM_ADC_INT_CTL.bit.ADC_CVRA_SEL =   SRC_CNT_PRD;//周期事件触发ADC转换和硬件电流环执行
		(*EPWM[EPWM_SYNC_HCL]).PWM_ADC_INT_PRE.bit.ADC_CVRA_DIV =   SRC_DIV1_OUT;
		(*EPWM[EPWM_SYNC_HCL]).PWM_ADC_INT_CTL.bit.ADC_CVRA_EN  =   P_ENABLE;
	}
	else
	{
		(*EPWM[EPMW_CTRL_NUM]).PWM_ADC_INT_CTL.bit.ADC_CVRA_SEL =   SRC_CNT_PRD;//用于触发ADC的Q1对列转换
	    (*EPWM[EPMW_CTRL_NUM]).PWM_ADC_INT_PRE.bit.ADC_CVRA_DIV =   SRC_DIV1_OUT;
		(*EPWM[EPMW_CTRL_NUM]).PWM_ADC_INT_CTL.bit.ADC_CVRA_EN  =   P_ENABLE;
	}

	//配置中断触发信号
	(*EPWM[EPMW_CTRL_NUM]).PWM_ADC_INT_CTL.bit.PWM_INT_SEL  =   SRC_CNT_PRD;
	(*EPWM[EPMW_CTRL_NUM]).PWM_ADC_INT_PRE.bit.PWM_INT_DIV  =   SRC_DIV1_OUT;
	(*EPWM[EPMW_CTRL_NUM]).PWM_ADC_INT_CTL.bit.PWM_INT_EN   =   P_ENABLE;
    //配置EPWM触发编码器通讯
	if(encoder_lsw == 0)
	{
		(*EPWM[EPMW_CTRL_NUM]).PWM_CVRCD_CTL.bit.PWM_CVRC_EN= 0x1;	//使能CVRC
		(*EPWM[EPMW_CTRL_NUM]).PWM_CVRCD_CTL.bit.PWM_CVRC_SEL= 0x1;	//周期点触发编码器通讯
		(*EPWM[EPMW_CTRL_NUM]).PWM_CVRCD_CTL.bit.PWM_CVRC_DIV = 0x1;//CVRC的频次
	}
	//配置保护动作
	(*EPWM[Aixse1_EPWM_U]).PWM_FAULT_PRTCT.bit.A_FAULT_PRTCT = PROTECT_LOW;
	(*EPWM[Aixse1_EPWM_U]).PWM_FAULT_PRTCT.bit.B_FAULT_PRTCT = PROTECT_LOW;
	(*EPWM[Aixse1_EPWM_V]).PWM_FAULT_PRTCT.bit.A_FAULT_PRTCT = PROTECT_LOW;
	(*EPWM[Aixse1_EPWM_V]).PWM_FAULT_PRTCT.bit.B_FAULT_PRTCT = PROTECT_LOW;
	(*EPWM[Aixse1_EPWM_W]).PWM_FAULT_PRTCT.bit.A_FAULT_PRTCT = PROTECT_LOW;
	(*EPWM[Aixse1_EPWM_W]).PWM_FAULT_PRTCT.bit.B_FAULT_PRTCT = PROTECT_LOW;

	gpio_enable(ioIpmAlarmIn, 1, GPIO_FUN_4);  //PRO1
	//配置过流中断保护
	FAULT_NREC_INIT(Aixse1_EPWM_U);
	FAULT_NREC_INIT(Aixse1_EPWM_V);
	FAULT_NREC_INIT(Aixse1_EPWM_W);
	epwm_fault_irq_register(EPWM_FLT_isr);//注册EPMW错误中断

#if 1 //使能debug hold
	(*EPWM[Aixse1_EPWM_U]).PWM_NRCFLT_IN.bit.DBG_HOLD_EN = P_ENABLE;
	(*EPWM[Aixse1_EPWM_V]).PWM_NRCFLT_IN.bit.DBG_HOLD_EN = P_ENABLE;
	(*EPWM[Aixse1_EPWM_W]).PWM_NRCFLT_IN.bit.DBG_HOLD_EN = P_ENABLE;
#endif
#if 0 //禁止debug hold
	(*EPWM[Aixse1_EPWM_U]).PWM_NRCFLT_IN.bit.DBG_HOLD_EN = P_DISABLE;
	(*EPWM[Aixse1_EPWM_V]).PWM_NRCFLT_IN.bit.DBG_HOLD_EN = P_DISABLE;
	(*EPWM[Aixse1_EPWM_W]).PWM_NRCFLT_IN.bit.DBG_HOLD_EN = P_DISABLE;
#endif

	//使能立即更新补脉冲功能，需要CMPA在立即更新模式下
	 (*EPWM[Aixse1_EPWM_U]).PWM_CNT_CFG.bit.CMPA_IMD_PULEN = P_ENABLE;
	 (*EPWM[Aixse1_EPWM_V]).PWM_CNT_CFG.bit.CMPA_IMD_PULEN = P_ENABLE;
	 (*EPWM[Aixse1_EPWM_W]).PWM_CNT_CFG.bit.CMPA_IMD_PULEN = P_ENABLE;
	 if(HclSwitch.Hcl_EnableSw == 1)
	 {
		//配置HCL占空比更新
		(*EPWM[Aixse1_EPWM_U]).PWM_HCL_UPDT_EN.bit.HCL_DUT_NUM = 0x0;
		(*EPWM[Aixse1_EPWM_U]).PWM_HCL_UPDT_EN.bit.HCL_AXI_SEL = 0x0;
		(*EPWM[Aixse1_EPWM_U]).PWM_HCL_UPDT_EN.bit.HCL_UPDT_EN = 0x1;

		(*EPWM[Aixse1_EPWM_V]).PWM_HCL_UPDT_EN.bit.HCL_DUT_NUM = 0x1;
		(*EPWM[Aixse1_EPWM_V]).PWM_HCL_UPDT_EN.bit.HCL_AXI_SEL = 0x0;
		(*EPWM[Aixse1_EPWM_V]).PWM_HCL_UPDT_EN.bit.HCL_UPDT_EN = 0x1;

		(*EPWM[Aixse1_EPWM_W]).PWM_HCL_UPDT_EN.bit.HCL_DUT_NUM = 0x2;
		(*EPWM[Aixse1_EPWM_W]).PWM_HCL_UPDT_EN.bit.HCL_AXI_SEL = 0x0;
		(*EPWM[Aixse1_EPWM_W]).PWM_HCL_UPDT_EN.bit.HCL_UPDT_EN = 0x1;
	 }
#if 0
	 /*PWM_SO*/
	 Glb_Pwmcs_Regs.SYNC_SRC_IN_SEL.bit.SYNCI0_IN_SRC_SEL = 0x30;     //SI0选择ESC同步信号
	 Glb_Pwmcs_Regs.GLB_EPWM_SYNC_IN_SEL.bit.EPWM0_SYNCO_EN = 0x1; //使能EPWM_SO0输出
	 (*EPWM[EPMW_CTRL_NUM]).PWM_CNT_CFG.bit.SYNC_OUT = 0x0;                    //EPWM0的同步输出信号选择SI0的输入信号
#endif
#if 0//EPWM0~EPWM8和EPWM9同步
	 //设置EPWM0/EPWM1/EPMW2的同步源为外部同步信号0
	Glb_Pwmcs_Regs.GLB_EPWM_SYNC_IN_SEL.bit.EPWM0_SYNC_IN_SEL = 0x0 ;
	//设置EPWM3/EPWM4/EPMW5的同步源为外部同步信号0
	Glb_Pwmcs_Regs.GLB_EPWM_SYNC_IN_SEL.bit.EPWM3_SYNC_IN_SEL = 0x0 ;
	//设置EPWM6/EPWM7/EPMW8的同步源为外部同步信号0
	Glb_Pwmcs_Regs.GLB_EPWM_SYNC_IN_SEL.bit.EPWM6_SYNC_IN_SEL = 0x0 ;
	//设置外部同步信号0源为EPWM9_TO
	Glb_Pwmcs_Regs.SYNC_SRC_IN_SEL.bit.SYNCI0_IN_SRC_SEL = 0xA;
	//设置EPWM9_TO的trig信号为计数到0同步
	(*EPWM[EPMW_CTRL_NUM]).PWM_TRG_OUT.bit.TRIG_SEL = 0x0;

#endif
#if 1//EPWM0~EPWM9同步EtherCAT SYNC0
	//设置EPWM0/EPWM1/EPMW2的同步源为外部同步信号0
	Glb_Pwmcs_Regs.GLB_EPWM_SYNC_IN_SEL.bit.EPWM0_SYNC_IN_SEL = 0x0 ;
	//设置EPWM3/EPWM4/EPMW5的同步源为外部同步信号0
	Glb_Pwmcs_Regs.GLB_EPWM_SYNC_IN_SEL.bit.EPWM3_SYNC_IN_SEL = 0x0 ;
	//设置EPWM6/EPWM7/EPMW8的同步源为外部同步信号0
	Glb_Pwmcs_Regs.GLB_EPWM_SYNC_IN_SEL.bit.EPWM6_SYNC_IN_SEL = 0x0 ;
	//设置EPWM9/EPWM10/EPMW11的同步源为外部同步信号0
	Glb_Pwmcs_Regs.GLB_EPWM_SYNC_IN_SEL.bit.EPWM9_SYNC_IN_SEL = 0x0 ;
	//设置外部同步信号0源为ECAT_SYNC0
	Glb_Pwmcs_Regs.SYNC_SRC_IN_SEL.bit.SYNCI0_IN_SRC_SEL = 0x30;

	(*EPWM[EPMW_CTRL_NUM]).PWM_CNT_CFG.bit.SYNC_OUT     = SYNCIN_OR_SW;
	(*EPWM[EPMW_CTRL_NUM]).PWM_CNT_CFG.bit.CNT_PH_EN    = P_ENABLE;
	(*EPWM[EPMW_CTRL_NUM]).PWM_CNT_PHV.bit.PH_VAL       = 0;
	(*EPWM[EPMW_CTRL_NUM]).PWM_CNT_CFG.bit.CNT_PH_DIR   = DIR_INCR;
#endif
	pwm1.pwm_off(&pwm1);
	epwm_global_en();
	epwm_irq_register(EPMW_CTRL_NUM, EPWM_IRQHandler_isr);
}

void xpwm_timer_init(uint32_t num,uint32_t prd,uint32_t cmp)
{
	xpwm_prd_set(num,prd);
	//xpwm_cmp_set(num,cmp);
	//xpwm_mod_set(num,0x0);				//pwm输出模式
	xpwm_int_en(num,0x2);					//cnt_prd中断使能
}
void xpwm_timer_2ms_Init(void)
{
	 /* 这里采用的硬件资源是XPWM0
	 * XPWM0初始化配置周期为2ms。
	 */
	uint8_t xpwm_num = 0;
	xpwm_cmu_init(xpwm_num);
	xpwm_timer_init(xpwm_num,480000,0);//设置2ms周期值，增计数模式
	xpwm0_irq_register(PWM_IRQHandler_isr);
	xpwm_cnt_en(xpwm_num,0x1);
}
void gpt_timer_Init(u8 gpt_num)
{
	gpt_cmu_init(gpt_num);

	init_gpt(gpt_num,0,GPT_TRG_MODE_AUTO,GPT_RUN_MODE_LOOP,GPT_NS_8,0,0xffffffff); //8.33ns
	gpt_en(gpt_num);
}
#if 0
void QEP_CNF(uint32_t n)
{
	(*QEP[n]).QEP_POS_CNTV = 0;
	(*QEP[n]).QEP_POS_CNT_EP = 0xFFFF;
	(*QEP[n]).QEP_WD_PRDV = 0xFFFF;
	(*QEP[n]).QEP_DEC_CONF.bit.QEP_CNT_MOD = DIR_CNT;
	(*QEP[n]).QEP_IN_CTL.bit.QEP_IN_FLT_EN = Q_ENABLE;
	(*QEP[n]).QEP_IN_FLT1.bit.A_IN_FLT_SEL = 1;     //QEPA滤波采样点设置
	(*QEP[n]).QEP_IN_FLT1.bit.A_SMP_CTL_PRD = 5;    //QEPA滤波采样频率设置
	(*QEP[n]).QEP_IN_FLT1.bit.B_IN_FLT_SEL = 1;     //QEPB滤波采样点设置
	(*QEP[n]).QEP_IN_FLT1.bit.B_SMP_CTL_PRD = 5;    //QEPB滤波采样频率设置
	(*QEP[n]).QEP_POS_CNT_CONF.bit.POS_CNT_EN = Q_DISABLE;   //使能QEP位置计数器开始计数

}

void MS_PulseCommand_Init(void)
{
	//QEP初始化
	//1、QEP3时钟初始化配置
	//**************************************
	qep_clk_en(QEP_PULSE_NUM);

	//2、QEP3管脚初始化配置
	//**************************************
	qep_pinmux_init(QEP_PULSE_NUM);                     //初始化QEP3A/B/I的GPIO管脚

	//3、QEP0初始化配置
	//**************************************
	QEP_CNF(QEP_PULSE_NUM);
}
void MS_PulseCommand_Mode(void)
{
	if(Servo.Pn01.PulseMode.Data == 0
			|| Servo.Pn01.PulseMode.Data == 1
			|| Servo.Pn01.PulseMode.Data == 2
			|| Servo.Pn01.PulseMode.Data == 3)
	{
		(*QEP[QEP_PULSE_NUM]).QEP_DEC_CONF.bit.QEP_CNT_MOD = DIR_CNT;
	}
	else if(Servo.Pn01.PulseMode.Data == 4
			|| Servo.Pn01.PulseMode.Data == 5)
	{
		(*QEP[QEP_PULSE_NUM]).QEP_DEC_CONF.bit.QEP_CNT_MOD = CW_CCW_CNT;
	}
	else
	{
		(*QEP[QEP_PULSE_NUM]).QEP_DEC_CONF.bit.QEP_CNT_MOD = QUAD_CNT;
	}
}
void MS_PulseCommand_Fliter(void)
{
	(*QEP[QEP_PULSE_NUM]).QEP_IN_FLT1.bit.A_SMP_CTL_PRD = Servo.Pn01.PulseFilterTime.Data;//QEPA滤波采样频率设置
	(*QEP[QEP_PULSE_NUM]).QEP_IN_FLT1.bit.B_SMP_CTL_PRD = Servo.Pn01.PulseFilterTime.Data;//QEPB滤波采样频率设置
}
#endif
void cordic_cal_int(COR_FUNC_TYP funsel, COR_ITER_TYP iteration, s32 data2)
{
	cordic_cmu_init();
	Cor_Regs.COR_CFG.bit.FUNC_SEL = funsel;
    Cor_Regs.COR_CFG.bit.NM_ITER = iteration;
    Cor_Regs.COR_IN2.bit.IN_PARA2 = (s16)data2;
}
void IRQHandler_set_prio(void)
{
	clic_irq_set_prio(CPU_IRQ_EPWM_FAULT, PRIO_7);
	clic_irq_set_prio(CPU_IRQ_HCL, PRIO_7);
	clic_irq_set_prio(CPU_IRQ_EPWM9, PRIO_6);
	clic_irq_set_prio(CPU_IRQ_EtherCAT_SYNC0, PRIO_5);
	clic_irq_set_prio(CPU_IRQ_EtherCAT_SYNC1, PRIO_5);
	clic_irq_set_prio(CPU_IRQ_EtherCAT_Reset, PRIO_7);
	clic_irq_set_prio(CPU_IRQ_EtherCAT_PDI, PRIO_5);
	clic_irq_set_prio(CPU_IRQ_UART0, PRIO_3);
	clic_irq_set_prio(CPU_IRQ_UART1, PRIO_2);
	clic_irq_set_prio(CPU_IRQ_PWM0, PRIO_1);
}
