/*
 * encoder.c
 *
 *  Created on: 2023年8月14日
 *      Author: wenxing.ma
 */
#include "all_inc.h"
#include "M680x_it.h"
#include "math.h"
extern volatile struct HCL_REGS *HCL[];
int64_t  AbsaAxisData64 = 0;
uint16_t encoder_rcr_error_flag = 0;
uint16_t encoder_rcr_error_cnt = 0;
uint16_t encoder_off_error_flag = 0;
uint16_t encoder_off_error_cnt = 0;
int32_t   EncodeLine = 131072;
int32_t   HCL_EncodeLine = 131072;
int32_t   EncodeLine_By_Two = 65536;
int32_t   absa_theta_raw_from_cpld=0;
int32_t   absa_theta_raw=0;
int32_t  encoder_lsw = 0;
uint8_t  ABSA_SHIFT_BIT = 0;
uint32_t ABSA_MASK_BIT = 0;
uint8_t  HCL_ABSA_SHIFT_BIT = 0;
ENCODER encoder1 = ENCODER_DEFAULTS;
static void MS_TAIF_HW_CNT(u32 n);
void QOUT_CNF(u32 n);
static float fenpin_nm_to_q20(void);
static s32 gcd(s32 a,s32 b);      //求最大公约数
static void absa_type_identify(int8_t EncoderId);
extern volatile struct TAIF_REGS Taif0Regs,Taif1Regs;
uint32_t encoder_err_cnt = 0;
extern SERVO_PAR Servo;
extern long ExternSerovN;
extern int32_t ExternSerovM;
extern int32_t EncodeLine;
extern uint16_t g_custom_data[CUSTOM_DATA_COUNT];
extern uint16_t sendflag;
extern int32_t EncodeLine_By_Two;
void qep_pinmux_init(u8 i)
{
	switch (i) {
			case 0:
					gpio_enable(GPIO_GRP_F, 0, 3, GPIO_FUN_6);
					break;
			case 1:
					gpio_enable(GPIO_GRP_F, 3, 3, GPIO_FUN_6);
					break;
			case 2:
					gpio_enable(GPIO_GRP_F, 6, 2, GPIO_FUN_6);
                    break;
			case 3:
					gpio_enable(GPIO_GRP_F, 8, 2, GPIO_FUN_6);
					break;
			default:
			break;
	}
}
#if 0
float fenpin_nm_to_q20(void)
{
	float tmp;
	tmp = (s64)Servo.Pn01.PulseOut.Data*4 * 1048576.0 / EncodeLine;
	return(tmp);
}
s32 gcd(s32 a,s32 b)      //求最大公约数
{
	while(b != 0)
	{
		s32 temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}
#endif
void TAIF_SW_CNF(u32 n)
{
	ta_reset(n);							// 复位
	ta_baudrate_set(n, TA_2P5MHz);			// 波特率
	ta_format_sel(n, T_FORMAT);				// t-format 协议
	ta_rx_align_en(n);						// 数据接收对齐
	//时序参数配置
	ta_t2_set(n, 10);
	ta_t3_set(n, 3);
	ta_t4_set(n, 3);
	ta_t5_set(n, 720);
	ta_t6_set(n, 12000);
	ta_t9_set(n, 100);

	ta_cmdto_irq_en(n);					   //命令超时中断使能
	ta_rxto_irq_en(n);					   //接收数据超时中断使能
	if(n==0)
	Taif0Regs.RX_FLT.bit.IN_FLT_SEL = 0xf; //接收信号滤波，防止方向信号和数据信号有冲突，滤波时间为15/240M = 62.5ns
	else if(n==1)
	Taif1Regs.RX_FLT.bit.IN_FLT_SEL = 0xf; //接收信号滤波，防止方向信号和数据信号有冲突，滤波时间为15/240M = 62.5ns
}

void TAIF_TX_CMD(u32 n,u32 CmdData)
{
     if(CmdData==1)       { ta_ctl(n,T_DTAT_ID0,0x2,T_FIELD_1);} //read single absa
     else if(CmdData==2 ) { ta_ctl(n,T_DTAT_ID3,0x7,T_FIELD_1);} //read mutil absa
     else if(CmdData==3 ) { ta_ctl(n,T_DTAT_ID8,0x2,T_FIELD_1);} //reset single absa
     else if(CmdData==4 ) { ta_ctl(n,T_DTAT_IDC,0x2,T_FIELD_1);} //reset mutil absa
     else if(CmdData==5 ) { ta_ctl(n,T_DTAT_ID7,0x2,T_FIELD_1);} //reset error
     if(CmdData ==2 )//读单圈+多圈数据
     {
    	 tf_dec_abs_sel(n,DF012);//配置单圈数据为DF0/DF1/DF2
    	 tf_dec_abm_sel(n,DF456);//配置多圈数据为DF4/DF5/DF6
     }
     else
     {
    	 tf_dec_abs_sel(n,DF012);//配置单圈数据为DF0/DF1/DF2
     }
}

u32 TAIF_RX(u32 n)
{
	u32 data;
	data = (ta_get_rx_data0(n) & 0xFFFFFF);
	return data;
}

void  MS_TAIF_HW_CNT(u32 n)
{
	ta_reset(n);							// 复位
	ta_baudrate_set(n, TA_2P5MHz);			// 波特率
	ta_format_sel(n, T_FORMAT);				// t-format协议
	ta_hw_err_bp_en(n);					// 硬件模式下crc出错也输出
	ta_rx_align_en(n);						// 数据对齐

	//时序控制参数配置
	ta_t2_set(n, 10);
	ta_t3_set(n, 3);
	ta_t4_set(n, 3);
	ta_t5_set(n, 720);
	ta_t6_set(n, 12000);
	ta_t9_set(n, 30);

	TAIF_TX_CMD(0,Servo.Pn02.AbsaCtrlCmd.Data);//根据参数P2-57选择编码器发送指令

	if(n==0)
	Taif0Regs.RX_FLT.bit.IN_FLT_SEL = 0xf; //接收信号滤波，防止方向信号和数据信号有冲突，滤波时间为15/240M = 62.5ns
	else if(n==1)
	Taif1Regs.RX_FLT.bit.IN_FLT_SEL = 0xf; //接收信号滤波，防止方向信号和数据信号有冲突，滤波时间为15/240M = 62.5ns
	ta_hw_trig_en(n);				    //硬件触发使能
	ta_cmdto_irq_en(n);					    //命令超时中断使能
	ta_rxto_irq_en(n);					    //接收数据超时中断使能
}
#if 0
void QOUT_CNF(u32 n)
{
	float _ftmp;
	u32   _ltmp;
	float _ferr;
	s32   num;
	s32   den;
	s16   common_div;

	//QOUT初始化
	//1、QOUT GPIO PINMUX配置
	//**************************************
	gpio_enable(GPIO_GRP_G, 4, 3, GPIO_FUN_6); // PG4/PG5/PG6 选择QOUT0A/B/Z
	//2、初始配置
	//**************************************//
	qout_clk_en(n);
	qout_pos_src_sel(n, SRC_TA0);//选择TA-IF0作为分频信号源

    qout_sync_sel(n,0x0);
    /*
     * 设置QOUT分频定时器周期，由于QOUT定时器是增计数，而触发编码器通讯定时器是增减计数
     * 因此此处的QOUT定时器周期值=触发编码器通讯定时器周期值的（2倍-1）的关系
     */
    qout_tmr_prd(n,(STR_FUNC_Gvar.System.EpwmInvPeriod - 1));

	qout_a_en(n);                    //使能分频后的A相信号输出
	qout_b_en(n);                    //使能分频后的B相信号输出
	qout_z_en(n);                    //使能分频后的Z相信号输出

	qout_set_in_pulmax(n, EncodeLine); //输入编码器的位置最大值为2^24
	qout_set_line(n, Servo.Pn01.PulseOut.Data);//输出模拟正交编码器的线数，用于产生QOUT_Z的信号
									 //2500表示2500个正交输出信号产生一个Z信号
	_ftmp = fenpin_nm_to_q20();      //计算分频系数的Q20格式
	_ltmp = ceil(_ftmp);             //浮点数向上取值
	_ferr = _ltmp - _ftmp;           //计算误差值

	if(_ferr == 0)                   //误差值为零
	{
		qout_err_cancl_dis(n);       //禁止误差消除
	}
	else
	{
		num = _ferr*10000;               //将误差取整
		den = 10000;                     //分母固定为10000，支持小数点四位的不循环小数
		common_div = gcd(num,den);       //求最大公约数
		qout_err_cancl_en(n);            //使能误差消除
		qout_set_err_thr(n,den/common_div);//设置误差寄存器的分母
		qout_set_err_cv(n,num / common_div);//设置误差寄存器的分子
	}
	qout_set_nm_raito(n, _ltmp);         //n/m采用定点数Q20表示
	qout_set_pul_thr(n, EncodeLine_By_Two);    //设值pul_thr，用于检测输入脉冲的方向，2^24/2
	qout_en(n);                          //使能QOUT模块
}
#endif
void M680X_EV1_ENCODER_Init(ENCODER *p)
{
	//TAIF初始化
	//1、TA0时钟初始化配置
	//**************************************
	ta_cmu_init();

	gtc_dly_time(GTC_MS, 1000);          //延时，防止上电瞬间编码器5V供电不稳定

	//2、TA0管脚初始化配置
	//**************************************
	ta_pinmux_init(0);                   //初始化ENC0的GPIO管脚

	//3、TAP0初始化配置
	//**************************************
	if(encoder_lsw == 0)
	{
	   MS_TAIF_HW_CNT(0);                //硬件自动读取配置
	   gtc_dly_time(GTC_MS, 1);	         //延时，确保通讯成功过，编码器接收寄存器数据已更新
//	   QOUT_CNF(QOUT_FDB_NUM);           //qout分频配置
	}
	else
	{

	   TAIF_SW_CNF(0);                   //软件读取配置
	}
	//*******END*******//
}
void ta_single_reset_cmd(u32 n)
{
	ta_irq_sts_clr(n,0x1);  //写1清除
	ta_ctl(n,T_DTAT_ID8,0x2,T_FIELD_1);//装载编码器复位命令
	ta_cmd_execute(n);//执行编码器复位命令
}
void absa_single_reset(u32 n)//编码器单圈复位
{
	ta_hw_trig_en(n);   //硬件触发禁止
	ta_reset(n);
	ta_cmu_init();
	TAIF_SW_CNF(n);
	ta_tx_col_det_en(n);
	ta_t9_set(n, 100);
	ta_reset(n);
	ta_single_reset_cmd(n);
}
void M680X_EV1_ENCODER_Calc(ENCODER *p)
{
	 s32 absa_theta_tmp;
	 u32 encoder_sts = 0;
	 s32 absa_theta_real;
     s32 absa_theta_raw_old;
     s64 absa_theta_raw_tmp;
     u32 ABS0,ABS1,ABS2,ABS3;
	 if(encoder_lsw == 1)//软件通讯,默认是硬件通讯
	 {
		 TAIF_TX_CMD(0,Servo.Pn02.AbsaCtrlCmd.Data);//根据参数P2-57选择编码器发送指令
		 ta_cmd_execute(0);//执行发送指令
	 }
	 else//编码器通讯硬件触发
	 {
		 TAIF_TX_CMD(0,Servo.Pn02.AbsaCtrlCmd.Data);//根据参数P2-57选择编码器发送指令
	 }
	 p->Absa_RX_DATA0 = ta_get_rx_data0(0);//单圈数据
	 p->Absa_RX_DATA1 = ta_get_rx_data1(0);//多圈数据
	 g_custom_data[sendflag * 4 + 2] = (uint16_t *)p->AbsaSingleData;//position
//	 g_custom_data[sendflag * 4 + 3] = (uint16_t *)p->;//speed

	 if(EncodeLine <= 16777216)//24位以下编码器
	 {
		 p->absa_theta_raw = p->Absa_RX_DATA0 & 0x00ffffff;//单圈数据
		 if(Servo.Pn02.AbsaMutilSw.Data == 1)
		 p->AbsaCircleData = p->Absa_RX_DATA1 & 0x00ffffff;//多圈数据
		 else
		 p->AbsaCircleData = 0;
	 }
	 else//25bit以上编码器
	 {
		 ABS0 = Taif0Regs.RX_DAT0.bit.RXD0 >> 7;//单圈数据
		 ABS1 = Taif0Regs.RX_DAT0.bit.RXD1;
		 ABS2 = Taif0Regs.RX_DAT0.bit.RXD2;
		 ABS3 = Taif0Regs.RX_DAT1.bit.RXD4;
		 p->absa_theta_raw = (ABS3<<17) + (ABS2 << 9) + (ABS1<<1) + ABS0;
		 //HCL最大支持24bit的编码器分辨率，超过24bit时，软件右移到23bit，再写入角度寄存器里面
		 hcl_reg_psrc_set(Aixse1_HCL_NUM,((p->absa_theta_raw >> HCL_ABSA_SHIFT_BIT)&0xffffff));
		 if(Servo.Pn02.AbsaMutilSw.Data == 1)
		 {
			p->AbsaCircleData = (Taif0Regs.RX_DAT1.bit.RXD6 << 8) + Taif0Regs.RX_DAT1.bit.RXD5;//多圈数据
		 }
		 else
		 {
			p->AbsaCircleData = 0;
		 }
	 }
	 if(puwer_up_delay_finish_flag == 1)//判断实际编码器类型与设定是否相符
	 {
		 absa_type_identify(Taif0Regs.RX_DAT0.bit.RXD3);
	 }
	 if(Taif0Regs.RX_TSTS.bit.CRCE == 1)//CRC报错
	 {
		 p->absa_theta_raw = absa_theta_raw_old;
		 encoder_rcr_error_flag = 1;
	 }
	 else
	 {
		 encoder_rcr_error_flag = 0;
	 }


	 p->AbsaSingleData = p->absa_theta_raw;//单圈数据
	 //CRC报警检测
	 if(encoder_rcr_error_flag == 1)
	 {
		 encoder_rcr_error_cnt++;
		 if(encoder_rcr_error_cnt >= 5)//CRC报错超过5次报警
		 {
			 Err.AbsaCrcErrFlag = 1;
			 Err.ServoAlarmFlag = 1;
		 }
	 }
	 else
	 {
		 encoder_rcr_error_cnt = 0;
	 }
	 //断线报警检测
	 if(puwer_up_delay_finish_flag == 1)
	 {
		 if(Taif0Regs.TA_IRQ_STS.bit.IRQ_CMD_RXD_TO == 1
			  ||Taif0Regs.TA_IRQ_STS.bit.IRQ_CMD_TO == 1)
		 {
			 encoder_off_error_flag = 1;
			 Taif0Regs.TA_IRQ_STS.bit.IRQ_CMD_TO = 1;//清除中断标志位
			 Taif0Regs.TA_IRQ_STS.bit.IRQ_CMD_RXD_TO = 1;//清除中断标志位
			 ta_reset(0);
		 }
	 }
	 if(encoder_off_error_flag == 1)
	 {
		 encoder_off_error_cnt++;
		 if(encoder_off_error_cnt >= 5)
		 {
			 Err.EncodeOffFlag = 1;//编码器断线报警
			 Err.ServoAlarmFlag = 1;//伺服报警
		 }
	 }
	 else
	 {
		 encoder_off_error_cnt = 0;
	 }
	 //电角度计算
	 absa_theta_raw_from_cpld = p->absa_theta_raw;
	 p->cal_angle = (Servo.Pn02.ZeroOffset.Data / 3600.0)*EncodeLine;//U相对应的零点偏置角度,除以3600单位是0.1度
	 //设置编码器的初始角度，由于HCL最大支持24bit编码器，因此这个的角度对应的编码器分辨率要用HCL_EncodeLine变量
	 (*HCL[Aixse1_HCL_NUM]).ABS_POS_COMP.bit.VAL = (Servo.Pn02.ZeroOffset.Data / 3600.0)*HCL_EncodeLine;
	 if(p->cal_angle == 0)//说明伺服是用第一种电机调零方式
	 {
		absa_theta_raw_tmp = p->absa_theta_raw;//编码器实际值
	 }
	 else                 //说明伺服是用第二种电机调零的方式
	 {
		absa_theta_raw_tmp = p->absa_theta_raw;//编码器实际值+电角度补偿值
		if(absa_theta_raw_tmp >= p->cal_angle)
		{
			absa_theta_raw_tmp =  absa_theta_raw_tmp - p->cal_angle;
		}
		else
		{
			absa_theta_raw_tmp = EncodeLine +  absa_theta_raw_tmp - p->cal_angle;
		}
	 }
	 p->pole_pairs = Servo.Pn02.Pairs.Data;
     //电角度计算
     absa_theta_tmp = (s64)absa_theta_raw_tmp*(s32)(p->pole_pairs);
	 while(absa_theta_tmp >= EncodeLine)
	 {
		 absa_theta_tmp = absa_theta_tmp - EncodeLine;
		 absa_theta_tmp &= ABSA_MASK_BIT;
	 }
	 p->theta_elec = absa_theta_tmp >> ABSA_SHIFT_BIT;//_IQ16
	 //0~2pi转换成-pi~pi
	 p-> etheta = p->theta_elec;
	 if(p->etheta > 32768)
	 p->etheta = p->etheta - 65536;

	 //speed1.theta_new =  absa_theta_raw_from_cpld;
	 pos.fdb_new = absa_theta_raw_from_cpld;


}
void M680X_EV1_ENCODER_Axis(ENCODER *p)
{
	 int32_t AbsaCircleData_tmp;
	 if( p->AbsaCircleData >= 32767)//判断多圈是否过零
	 {
		 AbsaCircleData_tmp = p->AbsaCircleData - 65536;
	 }
	 else
	 {
		 AbsaCircleData_tmp = p->AbsaCircleData;
	 }
     //不含电子齿轮比
	 p->AbsaAxisData17bit = (int64_t)(AbsaCircleData_tmp*EncodeLine + p->AbsaSingleData);
	 //含电子齿轮比
	 p->AbsaAxisData = (((int64_t)AbsaCircleData_tmp*EncodeLine + p->AbsaSingleData)*ExternSerovM) / ExternSerovN;
	 if(Servo.Pn01.MotorDir.Data ==1 )
	 {
		 p->AbsaAxisData = -p->AbsaAxisData;
	 }
	 /*
	  * 将打包好的32位连续有符号的位置数据拆分位两个16位，便于modbusRTU通讯读取
	 */
	 p->AbsaAxisCurH = (uint16_t)((p->AbsaAxisData & 0xFFFF0000)>>16);
	 p->AbsaAxisCurL = (uint16_t)(p->AbsaAxisData & 0x0000FFFF);

	 //设定机械坐标原点
	 DI_SetAxisOld = DI_SetAxisNew;
	 DI_SetAxisNew = IoDi.DI_SetAxis;
	 /*
	  * 设定机械原点有两种方式:一种通过IO设置，一种通过参数操作设置
	 */
	 if((DI_SetAxisNew == 1 && DI_SetAxisOld == 0) || Servo.Pn01.AutoHomeFlag.Data==2)
	 {
		  if(Servo.Pn01.AutoHomeFlag.Data == 2)//参数操作设置机械原点
		  {
			  Servo.Pn01.AutoHomeFlag.Data = 0;
		  }
		  p->AbsaAxisSaveH = (uint16_t)((p->AbsaAxisData17bit & 0xFFFF0000)>>16);
		  p->AbsaAxisSaveL = (uint16_t)(p->AbsaAxisData17bit & 0x0000FFFF);
		  p->AbsaAxisSave = p->AbsaAxisData17bit;//当前编码器值作为原点
		  p->SetAxisFinishFlag = 1;//机械原点位置保存使能
	 }
}
void M680X_EV1_ENCODER_FenPin(ENCODER *p)
{
;
}
void M680X_EV1_ENCODER_Reset(ENCODER *p)
{
	Servo.Pn02.AbsaCtrlCmd.Data = 5;
}
void encoder_line_sel(int8_t input_data)
{
	int8_t encoder_type;
	encoder_type = input_data;     //P2-58的2位数
	if(encoder_type < 10)//兼容之前版本，防止P2-58=0时，电角度转换退不出while循环
	{
		EncodeLine = 131072;
		Err.EncoderTypeErrFlag = 1;
		Err.ServoAlarmFlag = 1;
	}
	else if(encoder_type <= 24)
	{
		EncodeLine = 2 << (encoder_type-1);
		HCL_EncodeLine = EncodeLine;
		EncodeLine_By_Two = EncodeLine / 2;
		ABSA_MASK_BIT = EncodeLine-1;
		ABSA_SHIFT_BIT = (encoder_type -16);       //转为16位电角度时需要右移的位数
	}
	else if(encoder_type <= 31)
	{
		EncodeLine = 2 << (encoder_type-1);
		HCL_EncodeLine = 8388608-1;      //HCL最大只支持24bit分辨率的编码器，这里用23bit
		EncodeLine_By_Two = EncodeLine / 2;
		ABSA_MASK_BIT = EncodeLine-1;
		ABSA_SHIFT_BIT = (encoder_type -16);      //转为16位电角度时需要右移的位数
		HCL_ABSA_SHIFT_BIT = (encoder_type-23);   //HCL最大支持24bit，编码器分辨率超过24bit时，硬件电流环就用23bit
	}
	else
	{
		EncodeLine = 131072;
		Err.EncoderTypeErrFlag = 1;
		Err.ServoAlarmFlag = 1;
	}
}
static void absa_type_identify(int8_t EncoderId)
{
	//设定的编码器类型和实际读到的类型不一致报警
//	Servo.Pn02.AbsaTypeCmd.Data = EncoderId;
	if(Servo.Pn02.AbsaTypeCmd.Data != EncoderId)
	{
		Err.EncoderTypeErrFlag = 1;
		Err.ServoAlarmFlag = 1;
	}
	//编码器分辨率小于10bit或大于31bit报警
	if(Servo.Pn02.AbsaTypeCmd.Data <= 10 || Servo.Pn02.AbsaTypeCmd.Data >= 31)
	{
		Err.EncoderTypeErrFlag = 1;
		Err.ServoAlarmFlag = 1;
	}
}
