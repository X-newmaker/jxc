#ifndef SERVO_DRV_SETTING_H_
#define SERVO_DRV_SETTING_H_
#include "all_inc.h"
//#define USER_MAIN              //"hello word!"字符串打印
//#define EPWM_SYNC_EXAMPLE      //EPWM0/1/2和EPMW3/4/5同步
//#define SPI_E2PROM_EXAMPLE     //SPI_E2PROM读写
//#define ADC_EXAMPLE            //电机电流反馈相电流ADC采样
//#define TAIF_QOUT_EXAMPLE      //绝对式编码器通讯和分频输出
//#define TAIF_READ_EXAMPLE      //读编码器位置和速度显示
//#define TAIF_EXAMPLE_SW_EEPROM //编码器E2PROM读写
//#define EPWM_EXAMPLE           //EPWM固定占空比输出
//#define SDFM_EXAMPLE           //ΣΔ(Sigma-Delta)调试模块
//#define OPEN_LOOP_EXAMPLE      //电机开环运行
//#define CURRENT_LOOP_EXAMPLE   //电流闭环
//#define SPEED_LOOP_EXAMPLE     //速度闭环
//#define POSITION_LOOP_EXAMPLE  //位置闭环
//#define EXAMPLE_ECAT_IO        //EtherCAT I/O通讯测试
//#define EXAMPLE_ECAT_FOE        //EtherCAT FOE例程
//#define EXAMPLE_ECAT_EOE        //EtherCAT EOE例程
//#define EXAMPLE_ECAT_CIA402    //EtherCAT通讯测试
#define ABS_SERVO_EXAMPLE        //产品级伺服全功能软件



#define myPI                    3.14159265358979
#define DSP_CLK                 480            //单位Mhz
#define SYSTEM_FREQUENCY        (DSP_CLK / 2)  //EPWM/SDFM模块的时钟固定为主频的一半
#define SYSTEM_PERIOD           (1.0 / SYSTEM_FREQUENCY)*1000.0 //单位是ns
#define ISR_FREQUENCY           10
#define SDFM_FREQUENCY          20000
#define SPEED_PRESCALE          5      // Speed loop prescaler
#define SPEED_FREQUENCY         (ISR_FREQUENCY/SPEED_PRESCALE)
#define INV_PWM_TICKS           (SYSTEM_FREQUENCY *1000 /ISR_FREQUENCY)
#define INV_PWM_TBPRD           (INV_PWM_TICKS/2)
#define INV_PWM_HALF_TBPRD      (INV_PWM_TICKS/4)
#define SDFM_PWM_TICKS          (SYSTEM_FREQUENCY *1000 /SDFM_FREQUENCY)
#define QEP0_LINENUM            2500
#define QEP0_MAX_POS            (QEP0_LINENUM * 4)
#define QEP0_POLEPAIR           5
#define QEP0_ELEC_MAX           (QEP0_MAX_POS/QEP0_POLEPAIR)
#define QEP0_CAL_ANG            1450
#define ONEWIRE0_INDEX          6

#endif

