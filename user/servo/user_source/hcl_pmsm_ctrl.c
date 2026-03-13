/*
 * hcl_pmsm_ctrl.c
 *
 *  Created on: 2025年4月10日
 *      Author: wenxing.ma
 */
#include "all_inc.h"
#include "M680x_it.h"
#include "math.h"
int16_t hcl_reg_update_enable = 0;
static void hcl_ovm_comp_init(uint8_t n);
static void hcl_deat_comp_init(uint8_t n);
static void hcl_speed_calc(uint8_t n);
static void hcl_volt_comp_init(uint8_t n);
static void hcl_elec_vol_comp_init(uint8_t n);
static void hcl_elec_thate_comp_init(uint8_t n);
static void hcl_speed_init(uint8_t n);
void MS_Hcl_Reg_Update(uint8_t n);
STRVOLTCOMP strVoltComp = {0};
MOTOR_EXTERN_STRUCT gMotorExtPer = {0};
PM_DECOUPLE gPmDecoup = {0};
extern volatile struct HCL_REGS *HCL[];
void MS_Hcl_Enbale(uint8_t n)
{
	hcl_en(n);
}
void MS_Hcl_Clr(uint8_t n)
{
	hcl_pid_clr(n);//清除电流环PID
	hcl_dis(n);
	(*HCL[n]).FUNC_EN.all |= 0x3e;
}
static void hcl_ovm_comp_init(uint8_t n)
{
	(*HCL[n]).HCL_CFG2.bit.OVM_COMP_EN = 0x1;
	//PRD_OM = ((PWM_PRD)*37824) >> 15
	(*HCL[n]).PRD_OM.bit.VAL = ((STR_FUNC_Gvar.System.EpwmInvPeriod / 2) *37824) >> 15;
}
static void hcl_deat_comp_init(uint8_t n)
{
	hcl_dtcmp_en(n);    //死区补偿打开
	hcl_set_dtcomp(n, Servo.Pn04.DeadVolValue.Data);   //死区补偿值初值为0
	hcl_set_dtflt(n, Servo.Pn04.DeadTime.Data);  //死区补偿滤波系数初始化
}

static void hcl_volt_comp_init(uint8_t n)
{
	(*HCL[n]).HCL_CFG2.bit.VOL_COMP_EN = 0x1;//使能电压补偿功能
	(*HCL[n]).VCOMP_MIN.bit.VAL = _IQ10(0.7);//设置最低电压补偿系数
	(*HCL[n]).VCOMP_MAX.bit.VAL = _IQ10(1.3);//设置最高电压补偿系数
	//母线电压实时采样值
	(*HCL[n]).REG_BUS.bit.VAL = ilg2_vdc1.Vdc_meas;
	//母线电压对应的ADC值的平均值
	(*HCL[n]).AVG_BUS_VAL.bit.VAL = strVoltComp.voltADCAveVal;
	(*HCL[n]).AVG_BUS_Q14.bit.VAL = _IQ14(1.0 / strVoltComp.voltADCAveVal);
}

static void hcl_elec_vol_comp_init(uint8_t n)
{
	float Lb,fb,Ib,Ub;
	int16_t MT_RateCurrent;
	int16_t MT_RateSpd;
	int16_t MT_MaxSpd;
	int16_t MT_StatInductD;
	int16_t MT_StatInductQ;
	int16_t MT_RevEleCoe;
	int16_t MT_RateVolt;
	if(HclSwitch.ElecVolCompEnableSw == 1)
	{
		(*HCL[n]).HCL_CFG2.bit.DCP_MOD_SEL = 0x01;//反电动势补偿使能
	}
	else if(HclSwitch.ElecVolCompEnableSw == 2)
	{
		(*HCL[n]).HCL_CFG2.bit.DCP_MOD_SEL = 0x02;//交叉解耦使能
	}
	if(Servo.Pn01.MotorType.Data == 102)//400W电机
	{
		MT_RateCurrent = 250; //单位0.01A
		MT_RateSpd = 3000;   //单位rpm
		MT_MaxSpd = 6000;   //单位rpm
		MT_StatInductD = 650;   //0.01mH
		MT_StatInductQ = 700;   //0.01mH
		MT_RevEleCoe = 3050;      //0.01V
		MT_RateVolt = 311;   //单位V
	}
	else if(Servo.Pn01.MotorType.Data == 103)//750w电机
	{
		MT_RateCurrent = 420;   //单位0.01A
		MT_RateSpd = 3000;      //单位1rpm
		MT_MaxSpd = 6000;   //单位rpm
		MT_StatInductD = 360;   //0.01mH
		MT_StatInductQ = 370;   //0.01mH
		MT_RevEleCoe = 3500;    //0.01V
		MT_RateVolt = 311;      //单位V
	}
	else if(Servo.Pn01.MotorType.Data == 104)
	{
		MT_RateCurrent = 420;   //单位0.01A
		MT_RateSpd = 3000;      //单位1rpm
		MT_MaxSpd = 6000;   //单位rpm
		MT_StatInductD = 220;   //0.01mH
		MT_StatInductQ = 230;   //0.01mH
		MT_RevEleCoe = 3500;    //0.01V
		MT_RateVolt = 311;      //单位V
	}
	else
	{
		MT_RateCurrent = 250;   //单位0.01A
		MT_RateSpd = 3000;      //单位rpm
		MT_MaxSpd = 6000;   //单位rpm
		MT_StatInductD = 650;   //0.01mH
		MT_StatInductQ = 700;   //0.01mH
		MT_RevEleCoe = 3050;    //0.01V
		MT_RateVolt = 311;      //单位V
	}
	//电感标幺基准值 Lb = Ub /(2 * 3.14 * fb * Ib)  ,Ub =311/sqrt(3),fb = 250Hz,Ib = 4.8A*1.414 ,  Lb =0.02383
	//gMotorExtPer.LD = Ld/Lb * 2^15,  gMotorExtPer.LQ = Lq/Lb * 2^15,
	Ub = (float)MT_RateVolt / sqrt(3);
	Ib = MT_RateCurrent*1.414 / 100.0;//额定电流单位是0.01A
	fb = (s32)(MT_RateSpd * Servo.Pn02.Pairs.Data) / 60.0;
	Lb = Ub / (2*3.14*fb*Ib);
	//gMotorExtPer.LD = 7972;//5638; // 4.1 * 10-3 / 0.02383 * 2^15
	//gMotorExtPer.LQ = 9139;//6463; //4.7 * 10^-3  / 0.02383 * 2^15
	gMotorExtPer.LD = _IQ(MT_StatInductD / (Lb*1000*100));
	gMotorExtPer.LQ = _IQ(MT_StatInductQ / (Lb*1000*100));
	//1.414* 31.5 *  3 /1.732/(311/1.732)  , 2^15, 反电动势31，5V（1000 rpm)为线电压的有效值
	//gMotorExtPer.FluxRotor = 14079;//9957;//17236;///1.414 * 31.5 *  3 /1.732/(311/1.732)
	//gMotorExtPer.FluxRotor = _IQ((1.414*31.5*3/1.732) / (311 / 1.732));
	gMotorExtPer.FluxRotor = _IQ((1.414*MT_RevEleCoe*3) / (MT_RateVolt)/100);//100因为反电动势系数时0.01V
	gPmDecoup.BaseFreRate = fb;
	gPmDecoup.MaxFreRate = (MT_MaxSpd * Servo.Pn02.Pairs.Data) / 60;
	gPmDecoup.Isdpu =  _IQ10((Servo.Pn01.CurSampleMax.Data /1.414 )/MT_RateCurrent);
	gPmDecoup.Isqpu =  _IQ10((Servo.Pn01.CurSampleMax.Data /1.414 )/MT_RateCurrent);

	(*HCL[n]).HCL_CFG2.bit.OMEG_RS = 9;//速度标幺值默认是_IQ24,因此需要右移9位转成_IQ15
	(*HCL[n]).FREDIV_RATE.bit.VAL = _IQ(gPmDecoup.MaxFreRate / gPmDecoup.BaseFreRate);
	(*HCL[n]).LD.bit.VAL = gMotorExtPer.LD;
	(*HCL[n]).LQ.bit.VAL = gMotorExtPer.LQ;
	(*HCL[n]).ISDPU.bit.VAL = gPmDecoup.Isdpu;
	(*HCL[n]).ISQPU.bit.VAL = gPmDecoup.Isqpu;
	(*HCL[n]).FLUX_ROT.bit.VAL = gMotorExtPer.FluxRotor;

}
static void hcl_elec_thate_comp_init(uint8_t n)
{
	(*HCL[n]).HCL_CFG2.bit.POS_COMP_EN = 0x1;//使能电角度补偿功能
	(*HCL[n]).ABS_DA_COMP = _IQ(PWM_T * speed_loop_ps * HCL_EncodeLine / 60.0);
	(*HCL[n]).SPD_CFG.bit.HCL_ENC_RATIO_EN = 0x1;//使能HCL与编码器通讯周期比值字段
	(*HCL[n]).SPD_CFG.bit.HCL_ENC_RATIO = (speed_loop_ps-1);
}
static void hcl_speed_init(uint8_t n)
{
	//速度采样周期内最大的脉冲数
	(*HCL[n]).ABS_MAX_DPOS.bit.VAL = (int64_t)int_speed_max *HCL_EncodeLine / 60.0 * PWM_T*speed_loop_ps;
	//测速方向阈值
	(*HCL[n]).SPD_DIR_THR.bit.VAL = (HCL_EncodeLine / 2);
	/*
	 * 计算AE测速系数0
	 * 2^15 * (速度采样频率) * 60 / ABS_MAX_DPOS
	 */
	(*HCL[n]).AE_SPDMCOFF0 = _IQ15(STR_FUNC_Gvar.System.SpdFreq * 60.0 / HCL_EncodeLine);
	//速度计算的右移位数,用于HCL内部电角度补偿用
	(*HCL[n]).HCL_CFG2.bit.SPD_CAL_RS = (15);
	//计算AE测速系数1 = （计算AE测速系数0 / 最高速度）<< 9
	(*HCL[n]).AE_SPDMCOFF1 = ((*HCL[n]).AE_SPDMCOFF0 / int_speed_max) << 9;
	//速度计算的右移位数,用于作为软件速度环的速度反馈（_IQ24)
	(*HCL[n]).HCL_CFG2.bit.SPD_CAL_RS1 = (0);
	//测速进行4次平均
	(*HCL[n]).SPD_CFG.bit.FLT_TIME = (2);
	//测速间隔，（0+1）次中断进行一次测速
	(*HCL[n]).SPD_CFG.bit.SPD_DEL_NUM = (speed_loop_ps-1);
}
void VoltageAveCalc(uint16_t voltAdc)
{
	static uint16_t valAveCount = 0;
	static uint32_t u_volt_sum = 0;

	if(valAveCount < 1000)
	{
		valAveCount++;
	}
	else if(valAveCount < (1000+256))
	{
		valAveCount++;
		u_volt_sum += voltAdc;
		if(valAveCount == (1000+256))
		{
			strVoltComp.voltADCAveVal = u_volt_sum >> 8;
			hcl_volt_comp_init(Aixse1_HCL_NUM);
		}
	}
	else
	{
		u_volt_sum = 0;
	}
}
void MS_Hcl_Reg_Update(uint8_t n)
{
	hcl_speed_init(n); //初始化与速度计算相关的寄存器
	if(HclSwitch.OverMode2_EnableSw == 1)//打开过调制2区控制模块
	{
		hcl_ovm_comp_init(n);
	}
	else
	{
		(*HCL[n]).HCL_CFG2.bit.OVM_COMP_EN = 0x0;
	}
	if(HclSwitch.DeadComp_EnableSw == 1)//打开死区补偿模块
	{
		hcl_deat_comp_init(n);
	}
	else
	{
		hcl_dtcmp_dis(n);              //死区补偿关闭
	}
	if(HclSwitch.VoltCompEnableSw == 1)//打开电压补偿模块
	{
		hcl_volt_comp_init(n);
	}
	else
	{
		(*HCL[n]).HCL_CFG2.bit.VOL_COMP_EN = 0x0;
	}
	//打开反电势补偿模块或交叉解耦模块
	if(HclSwitch.ElecVolCompEnableSw == 1||HclSwitch.ElecVolCompEnableSw == 2)
	{
		hcl_elec_vol_comp_init(n);
	}
	else
	{
		(*HCL[n]).HCL_CFG2.bit.DCP_MOD_SEL = 0x0;
	}
	if(HclSwitch.ElecComp_EnableSw == 1)//打开电角度补偿模块
	{
		hcl_elec_thate_comp_init(n);
	}
	else
	{
		(*HCL[n]).HCL_CFG2.bit.POS_COMP_EN = 0x0;
	}
}
void MS_Hcl_Init(uint8_t n)
{
	uint32_t HCL_PWM_TBPRD;

	//*******初始化HCL*******//
	hcl_cmu_init();
	//硬件电流环只支持到24位，因此超过24bit可以软件右移到24bit后，再送入角度寄存器

	if(EncodeLine > 16777216)
	{
		hcl_pos_dat_sel(n,1);//硬件电流环角度来源选择寄存器
	}
	else
	{
		hcl_pos_dat_sel(n,0);//硬件电流环角度来源自动获取
	}

	hcl_set_opm(n, HCL_OPM2);//Mode2,电角度选择实测的电角度
	hcl_set_posm(n, TA_POS);//选择绝对式编码器

	hcl_set_udm0(n, 0);     //Mode0 D轴电压，选择mode2则该值无效
	hcl_set_uqm0(n, 1475);  //Mode0 Q轴电压，选择mode2则该值无效

	HCL_PWM_TBPRD = STR_FUNC_Gvar.System.EpwmInvPeriod / 2;

	hcl_set_epwmprd(n, HCL_PWM_TBPRD);//电流环PWM开关周期
	hcl_set_maxduty(n, (HCL_PWM_TBPRD - 5));//设定最大占空比输出
	hcl_set_minduty(n, 5);                  //设定最小占空比输出
	hcl_set_timeconst(n, _IQ(1.0));         //PWM时间常数
	hcl_set_curcal(n, _IQ10(1.0));          //电流增益校正

	//set qaxi-pid
	_iq kp  = _IQ(0.1983);
	_iq ki  = _IQ(0.0244);

	hcl_set_qpidkp(n, kp);//设定电流环Q轴PI调节器kp初值
	hcl_set_qpidki(n, ki);//设定电流环Q轴PI调节器ki初值
	hcl_set_qpidmax(n, _IQ( 0.9));//设定电流环Q轴PI调节器输出最大限幅值初始化
	hcl_set_qpidmin(n, _IQ(-0.9));//设定电流环Q轴PI调节器输出最小限幅值初始化
	hcl_set_intgsep(n, _IQ( 0.9));//0.9
	hcl_set_iqref(n, _IQ(0.0));//设定电流环Q轴PI调节器给定初值为0

	//set daxi-pid
	hcl_set_dpidkp(n, kp);//设定电流环D轴PI调节器kp初值
	hcl_set_dpidki(n, ki);//设定电流环D轴PI调节器ki初值
	hcl_set_dpidmax(n, _IQ( 0.125));//设定电流环D轴PI调节器输出最大限幅值初始化
	hcl_set_dpidmin(n, _IQ(-0.125));//设定电流环D轴PI调节器输出最小限幅值初始化
	hcl_set_idref(n, _IQ(0));//设定电流环D轴PI调节器给定初值为0

	(*HCL[n]).HCL_CFG2.bit.ETHETA_CAL_RS = (9);//电角度右移9位,IQ(15)

#if (SDFM_USED == 1)//如果硬件是SDFM采样
	hcl_set_cur_src(n,1);//选择SDFM作为电流采样的数据来源
	hcl_u_sdfm_src(n,sdfm_num_u);//选择SDFM2采样U相电流
	hcl_v_sdfm_src(n,sdfm_num_v);//选择SDFM3采样V相电流
	hcl_sdfm_gain_set(n,1024);   //设置SDFM数据比例增益_IQ10(1)
	if(HclSwitch.SdfmFromRegSw == 1)//硬件电流环SDFM数据来源通过软件写入寄存器
	{
	   hcl_cur_dat_sel(n,1);//选择寄存器来源
	}
#endif

	hcl_set_theta0(n, 0);//Mode0和Mdde1工作模式下的给定电角度Theta
	hcl_set_absmax(n, (HCL_EncodeLine));//ABS最大位置值(编码器的分辨率)
	hcl_set_abs_elec_max(n, HCL_EncodeLine / Servo.Pn02.Pairs.Data);//ABS最大电角度值,131072(编码器分辨率)/5(极对数)
	hcl_set_abs_elec_fact(n, _IQ24(2/(float)(*HCL[n]).ABS_ELECT_MAX.bit.VAL)); //ABS电角度转换系数 _IQ24( 2/ABS_ELEC_MAX)

	MS_Hcl_Reg_Update(n);   //硬件电流环补偿模块寄存器设置
	hcl_reg_update_enable = 1;
#if (HCL_IRS_EN == 1)
	hcl_doneirq_en(n);//允许电流环完成中断
	hcl_irq_register(HCL_DONE_isr);//注册电流环完成中断服务程序
#endif
	hcl_en(n);              //打开硬件电流环
}
