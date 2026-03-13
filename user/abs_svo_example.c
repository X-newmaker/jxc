#include <aic_ecat_eeprom_emulation.h>
#include <flash_drv.h>
#include "all_inc.h"
#include "M680x_it.h"
#include "cia402appl.h"
#include "aic_ecat_cfg.h"
#include "aic_ecat_hw.h"
#include "aic_ecat_phy.h"
#include "applInterface.h"
#include "ecat_def.h"
#include "servo_drv_setting.h"
#include "ecatslv.h"

extern volatile struct HCL_REGS *HCL[];
#ifdef ABS_SERVO_EXAMPLE
UINT16 CiA402_Init(void);
void CiA402_DeallocateAxis(void);
static void ecat_main(void);
static void MS_Ecat_Init(void);
extern int usbd_ep_start_write(const uint8_t ep, const uint8_t *data, uint32_t data_len);
extern volatile struct GLB_PWMCS_REGS Glb_Pwmcs_Regs;
extern int cdc_acm_init(void);
static void ecat_main(void)
{
	HW_Init();

	MainInit();

	/*Initialize Axes structures*/
	CiA402_Init();

	/*Create basic mapping*/
	APPL_GenerateMapping(&nPdInputSize,&nPdOutputSize);
#if 0
	bRunApplication = TRUE;

	do
	{
		MainLoop();
	} while (bRunApplication == TRUE);

	CiA402_DeallocateAxis();
#endif
}

static void MS_Ecat_Init(void)
{
	s32 ret = RET_OK;
	ecat_init();                                        //ecat config and init pinmux、clock、heap and interruption

	gtc_dly_time(GTC_MS, 200);                          //wait for ecat init

	ret = ecat_check_eeprom_loading();                  //check eeprom
//	if(ret != RET_OK) {
//		   //return RET_FALSE;
//	}

	ecat_phy_reset_cfg(1);                              //release phy reset

	gtc_dly_time(GTC_MS, PHY_RESET_OUT_DLY_TIME);       //wait for phy ready

	ret = ecat_phy_init();                              //check phy id and config led mode
//	if(ret != RET_OK) {
//			return RET_FALSE;
//	}

	ecat_timer_init();                                  //start timer for ecat

	ENABLE_ESC_INT();                                   //enable pdi irq
	ecat_main();                                 //ecat stack runing
}
static u16 read_data[10] = {0};
uint16_t sendflag = 0;
void InitSysCtrl(void)
{
	//系统初始化
	basic_init();
//	e907_prediction_enable(); //打开预取功能
//	e907_l1_icache_enable();  //打开指令缓存功能
//	e907_l1_dcache_enable();  //打开数据缓存功能
	e907_irq_disable();               //全局中断禁止
	/*不需要用IDTCM和DTCM功能时,m7000t.ld文件TCM文件夹配置路径可以
	 * 指向tcm_code文件夹，该文件夹的tcm_function.c文件仅有一个执行一个空操作的函数
	 * 该函数在初始化时调用，后面可不需要调用
	 */
	MS_GPIO_Init();                   //通用IO初始化化
	gtc_dly_time(GTC_US, 1000);      //上电延时
	flash_init();                    //foe 读写flash初始化
#ifdef EEPROM_SPI
	spi_init_e2prom();                //spi读写E2PROM模块初始化
#else
	i2c_init_e2prom();                //I2C读写E2PROM模块初始化
#endif

#if 0
	//测试spi eeprom 读写数据正常
	//	Servo.Pn00.ParDefExe.Data = 1;
	//	Servo.Pn01.MotorType.Data = 140;
	//	MotorParDefExe();
		static u16 write_data[10] = {1,2,3,4,5,6,7,8,9,0};


		while(1)
		{
			write_e2prom(eeprom_dev_num,0,write_data[0]);
			write_e2prom(eeprom_dev_num,2,write_data[1]);
			write_e2prom(eeprom_dev_num,4,write_data[2]);
			write_e2prom(eeprom_dev_num,6,write_data[3]);
			write_e2prom(eeprom_dev_num,8,write_data[4]);

			read_data[0] = read_e2prom(eeprom_dev_num,0);
			read_data[1] = read_e2prom(eeprom_dev_num,2);
			read_data[2] = read_e2prom(eeprom_dev_num,4);
			read_data[3] = read_e2prom(eeprom_dev_num,6);
			read_data[4] = read_e2prom(eeprom_dev_num,8);
			read_data[5]++;
		}
	#endif
//		InitScia();                       //modbusRTU串口初始化
		//MODBUS_485设置为0，可以打印信息
#ifdef KEY_DISPLAY_USE_SPI
//	key_display_spi_init();
#endif
	MS_ParaInit();                    //伺服参数初始化

//	Servo.Pn01.ContrlMode.Data = 15;
//	Servo.Pn01.ServoON.Data = 1;
//	Servo.Pn04.OpenVol.Data = 0xa0;
#if 0
	Servo.Pn01.ContrlMode.Data = 20;
//	Servo.Pn01.ServoON.Data = 1;
	Servo.Pn04.OpenVol.Data = 0x06;
#endif
//	Servo.Pn03.Comm0Sel.Data = 1;

	if(Servo.Pn03.Comm0Sel.Data == 1)
	{
		InitUartApp();            //初始化UART0,用于串口波形打印数据
	}

//	else
//	{
//		init_uart0_upg();         //初始化UART0,用于软件升级或打印数据
//	}

	MS_EPWM_Init();                   //EPWM模块初始化
	InitECTCSP();                     //初始化CSP
	ECTCSPMaxSpeedUpdate();           //CSP最大速度限制，运行更新
	xpwm_timer_2ms_Init();            //2ms定时器初始化
	gpt_timer_Init(PGT_NUM);	  	  //8.33ns计时器，用来测量代码执行时间
	ilg2_vdc1.adc_init(&ilg2_vdc1);   //电流采样模块初始化
//	MS_PulseCommand_Init();           //脉冲指令接收模块初始化
	cordic_cal_int(Sin,iter24,0x7fff);//三角函数加速器模块初始化
	if(Servo.Pn03.Comm0Sel.Data == 0)//串口0打印输出
	{
	InitScia();                       //modbusRTU串口初始化
	}
	encoder1.init(&encoder1);         //编码器读写模块初始化
    MS_Ecat_Init();                   //初始化EtherCAT

	if(HclSwitch.Hcl_EnableSw == 1)   //硬件电流环使能开关
	{
	   MS_Hcl_Init(Aixse1_HCL_NUM);  //硬件电流环初始化
	}
	motor_para_cala( );               //再执行一次参数计算和初始化
	motor_para_init( );
	IRQHandler_set_prio();            //中断优先级设置
	e907_irq_enable();          //全局中断使能
#ifdef USE_USBD
    /* USB pin-mux */
    gpio_pin_cfg(GPIO_GRP_G, 19, 2,  GPIO_DRV_45R, GPIO_PULL_NONE);
    gpio_enable(GPIO_GRP_G, 19, 2, GPIO_FUN_2);
    //aic_tlsf_heap_init();//该函数已在void ecat_init(void)过，此处可以不用再初始化
    cdc_acm_init();
#endif
}
u8 usb_uart_SendBuf[10] ={0};
s32 main(void)	               //RET_OK
{
	u64 m_BaseTime,m_DetaTime;
	InitSysCtrl();             //系统硬件初始化
	m_BaseTime = GetTime();
	for(;;)
	{

		m_DetaTime = GetTime() - m_BaseTime;
		if(m_DetaTime >= C_TIME_05MS)	//判断0.5MS周期
		{
			m_BaseTime = GetTime();
			motor_para_cala();

			   //电流环环带宽测试模式下，串口波形打印发送才在此定时器中断里面发送
			   if(Servo.Pn03.Comm0Sel.Data == 1)
			   {
					UartRTSend();        //发送数据到第三方波形打印软件
			   }

#ifdef USE_USBD //以下为USB发送数据给上位机的测试数据，1s发送一次
			static u16 count = 0,index = 0;
			if(count < 2000)
			{
				count++;
			}
			else
			{//测试USB虚拟串口
				count = 0;
				usb_uart_SendBuf[0] = 0x30+(index/10000);
				usb_uart_SendBuf[1] = 0x30+(index/1000%10);
				usb_uart_SendBuf[2] = 0x30+(index/100 %10);
				usb_uart_SendBuf[3] = 0x30+(index/10  %10);
				usb_uart_SendBuf[4] = 0x30+(index      %10);
				usb_uart_SendBuf[5] = '\r';
				usb_uart_SendBuf[6] = '\n';
				usbd_ep_start_write(0x81, usb_uart_SendBuf, 7);
				index++;
			}
#endif
		}
		MS_DISPLAY();
		if(sendflag == 15)//数据读取15次得到60个数据导入新数据重置标志位
		{
			sendflag = 0;
		}
		else
		{
			sendflag++;
		}
		//示波器发送标志位
		if(Servo.Pn03.Comm0Sel.Data == 0)//串口0打印输出
		{
			SciDeal();	   //串口通讯处理
		//printk("hello world!");
		//uart_transmit_char(modbus_uart_no,sci_data);
	    //printk("%d,%d,%d\n\r",(*HCL[0]).POS_RAW.bit.VAL,encoder1.absa_theta_raw,(*HCL[0]).ELECT_OUT.bit.VAL);
        //printk("%d,%d\n\r",(s16)(*HCL[0]).NODB_PDIU.bit.VAL,(s16)(*HCL[0]).NODB_PDIV.bit.VAL);
		//printk("%d,%d\n\r",(s16)ilg2_vdc1.Imeas_a,(s16)ilg2_vdc1.Imeas_b);
		//printk("%d\n\r",motor_position.actual_position_cur);
		}
         CSP_main_loop();
         MainLoop();   //EtherCAT主循环
	}
	return RET_OK;
}
#endif
