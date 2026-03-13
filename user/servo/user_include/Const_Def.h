/*
 * Const_Def.h
 *
 *  Created on: 2023年8月11日
 *      Author: wenxing.ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_CONST_DEF_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_CONST_DEF_H_

#define ABS(A)      (((A)>=0) ? (A) : (-(A)))

#define     myPI                 3.14159265358979
#define     GetTime() 	       gtc_get_time(GTC_US)
#define     C_TIME_05MS        500	  //0.5ms对应的定时器1计数值

#define ISR_FREQUENCY1     10.0
#define ISR_FREQUENCY2     12.5
#define ISR_FREQUENCY3     16.0
#define ISR_FREQUENCY4     20.0

#define IQ_MAX             16777216
#define IQ_MIN             -16777216

#define DEBUG_USE_UART0
#define USE_USBD

#define	EEPROM_I2C		//如果使用I2C的
//#define	EEPROM_SPI		//如果使用SPI的

#define PCMD_FILTER_TIME_REF     10000
#define SDFM_USED       1     //SDFM使用开关，设置为1，则使用SDFM，设置为0,则使用片上ADC
#if   (SDFM_USED == 0)//如果没使用SDFM模块，则启用内部PGA
#define	 	ADC_CONNECT_PGA		//ADC+PGA模式
#endif

#define		ADC_REF_MIN			7192	//1799		//ADC REF 最小值
#define		ADC_REF_MAX			9192	//2172		//ADC REF 最大值


#define STOP                 0
#define RUN                  1
#define ERROR                2

#define     MODBUS_485       1
#define     MODBUS_CAN       1

#define     Aixse1_HCL_NUM   0   //单轴使用硬件电流环0
#define     EPMW_CTRL_NUM    9   //位置环/速度环/电流环执行周期定时器
#define     Aixse1_EPWM_U    0
#define     Aixse1_EPWM_V    1
#define     Aixse1_EPWM_W    2
#define     EPWM_SDFM_CLK    6
#define     EPWM_SYNC_HCL    7
#define     EPWM_SYNC_SDFM   8

#define     QEP_PULSE_NUM        2
#define     QOUT_FDB_NUM         0
#define     PGT_NUM              GPT1

#define     HCL_IRS_EN       0
/**************** 键盘显示参数定义******************************************/
#define     DISP_CS             GPIO_GRP_G, 1

#define     DISP_KEY            GPIO_GRP_B, 3
#define     DISP_KDP            GPIO_GRP_B, 1
#define 	E2PROM_CS 			GPIO_GRP_E, 14

#define KEY_DISPLAY_USE_SPI

#ifndef KEY_DISPLAY_USE_SPI
#define     DISP_DAT            GPIO_GRP_B, 5
#define     DISP_CLK            GPIO_GRP_B, 4
#else
extern void key_display_spi_init(void);
#endif

/*******************I/O引脚定义*****************/

#define DI1 GPIO_GRP_D, 27 // 1,SON 伺服使能
#define DI2 GPIO_GRP_D, 26 // 2,CLS 报警清除

#define DO1 GPIO_GRP_D, 24 // SRDY-Z
#define DO2 GPIO_GRP_D, 22 // ALM

/****************板间接口定义******************/
#define 	ioIpmAlarmIn 		GPIO_GRP_E, 18  // 模块报警检测,PRO1
//#define     ioPowerOffIn        GPIO_GRP_E, 19   //掉电检测信号,PRO2
#define     ioPowerHighIn       GPIO_GRP_A, 2   //过压报警检测,PRO3
#define     ioPowerLowIn        GPIO_GRP_A, 9   //欠压报警,PRO4
#define     ioBreakErrIn        GPIO_GRP_A, 3   //制动故障报警,PRO5


//#define ioReLayOut GPIO_GRP_D, 21  // 继电器控制信号

#define ioPWMcsOut GPIO_GRP_E, 20 // PWM波输出片选信号

/**************电机控制方式定义****************/
#define  CTL_Pt                     0 //外部位置模式
#define  CTL_Pr                     1
#define  CTL_Pt_Pr                  9
#define  CTL_PtTi                   10
#define  CTL_PtTiCheck              22
#define  CTL_TorqOpen               20 //力矩开环模式  与 电流反馈、速度反馈等无关

#define  CTL_Si                     2 //内部速度模式，无模拟电压输入，内部参数设定速度大小
#define  CTL_Tt                     3
#define  CTL_Ti                     4 //内部扭矩模式，无模拟电压输入，内部参数设定扭矩大小
#define  CTL_SiCheck                5
#define  CTL_Pt_Psi                 6

#define  CTL_Pr_Si                  8
#define  CTL_Pt_Ti                  17

#define  CTL_Sr                     11 //电机试运行方式
#define  CTL_JOG                    12 //电机寸动方式
#define  CTL_OL                     13 //电机测试方式
#define  CTL_CO1                    14 //编码器调零方式1
#define  CTL_OP                     15 //开环运行方式
#define  CTL_CO2                    16 //编码器调零方式2

#define  CTL_AUTO_Pr                34
#define  CTL_WITHD_TEST             35
#define  CTL_AUTO_TEST              36

/***************伺服报警代码区******************************/
#define SERVO_OK                     0
#define SPEED_HIGH_ERR               1
#define POWER_HIGH_ERR               2
#define POWER_LOW_ERR                3
#define POSITION_OVER_ERR            4
#define ABSA_TEMP_HIGH_ERR           5
#define SPEED_SAT_ERR                6
#define CCWL_CWL_ERR                 7
#define ABSA_BATTERY_ERR             8
#define ENCODE_OFF_ERR               9
#define HOME_BACK_LIMIT             10
#define IPM_ERR                     11
#define CUR_OVER_ERR                12
#define SDFM_OVER_ERR               13
#define POWER_BRAKE_ERR             14
#define POLES_ERR                   15
#define MAIN_POWER_OFF_ERR          16
#define MOTOR_TYPE_ERR              18
#define ABSA_CRC_ERR                19
#define E2PROM_READ_ERR             20
#define CRC_ERR                     21
#define CUR_REF_ERR                 22
#define MOTOR_UVW_ERR               23
#define ABSA_BATTERY_LOW            24
#define CPLD_DATABUS_ERR            26
#define IPM_TEMP_HIGH_ERR           27
#define MOTOR_EMGS_ERR              28
#define LOAD_OVER_ERR               32
#define TR_OVER_ERR                 33
#define CSP_OVER_ERR                34
#define ENCODER_TYPE_ERR            37//编码器型号错误
/************************************************************/
#define P105 5
#define P116 16
#define P159 59
#define P160 60
#define P161 61
#define P200 Pn01_NUM+0
#define P201 Pn01_NUM+1
#define P202 Pn01_NUM+2
#define P210 Pn01_NUM+10
#define P212 Pn01_NUM+12
#define P213 Pn01_NUM+13
#define P214 Pn01_NUM+14
#define P215 Pn01_NUM+15
#define P216 Pn01_NUM+16
#define P220 Pn01_NUM+20
#define P226 Pn01_NUM+26
#define P227 Pn01_NUM+27
#define P229 Pn01_NUM+29
#define P230 Pn01_NUM+30
#define P242 Pn01_NUM+42
#define P240 Pn01_NUM+40
#define P241 Pn01_NUM+41
#define P251 Pn01_NUM+51
#define P252 Pn01_NUM+52
#define P253 Pn01_NUM+53
#define P254 Pn01_NUM+54
#define P258 Pn01_NUM+58
#define P260 Pn01_NUM+60
#define P261 Pn01_NUM+61
#define P262 Pn01_NUM+62


/************************************************************/
#define  Pn00_NUM    (sizeof(PAR_Pn00) / sizeof(PARAMETER_DATA))
#define  Pn01_NUM    (sizeof(PAR_Pn01) / sizeof(PARAMETER_DATA))
#define  Pn02_NUM    (sizeof(PAR_Pn02) / sizeof(PARAMETER_DATA))
#define  Pn03_NUM    (sizeof(PAR_Pn03) / sizeof(PARAMETER_DATA))
#define  Pn04_NUM    (sizeof(PAR_Pn04) / sizeof(PARAMETER_DATA))


#define  Pn_NUM      (sizeof(SERVO_PAR) / sizeof(PARAMETER_DATA))
#define  Def_NUM     (sizeof(SERVO_DEFAULT) / (sizeof(int16_t)))
#define  Fn_NUM_MAX  (sizeof(SERVO_FN) / sizeof(int32_t))
#define  ParDef_Num  124  //默认参数组数

typedef long long			int64;



#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_CONST_DEF_H_ */
