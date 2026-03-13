/*
 * contrl.h
 *
 *  Created on: 2023年8月11日
 *      Author: wenxing.ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_CONTRL_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_CONTRL_H_
#include "stdint.h"
typedef struct {
	   long cmd_new;
       long dir_CMD;
       long DirCmd;
       long DirNew;
       long DirOld;
       long DirChgCnt;
	   long cmd_err;
	   long cmd_err_sum;
	   long cmd_old;
       long cmd_frq;
       long rpm_max;
       long K1;
       long K2;
       long K3;
       long speed_rpm;
	   long  cmd_filt_cnt;
	   long cmd_filt_sum;
     long  cmd_filt_en;//指令平滑滤波器功能选择
	   long cmd_filt_xn;//位置指令平滑滤波器输入
	   long cmd_filt_out;//位置指令平滑滤波器输入
	   long cmd_filt_yn;//
	   long cmd_filt_yn_next;
	   long cmd_filt_save;//脉冲剩余量保存寄存器
	   long  cmd_filt_k;//位置指令平滑滤波器系数
	   long  cmd_sum_cnt;
	   long  cmd_ref_hz;
	   long  cmd_avg_k;//位置指令平滑滤波器系数
		 long  pr_cmd;
       void (*init)();
       void (*calc)();
       void (*filt)();
       } SPEED_MEAS_CMD;

typedef SPEED_MEAS_CMD *SPEED_MEAS_CMD_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the CMD_MEAS_QEP object.
-----------------------------------------------------------------------------*/
#define SPEED_MEAS_CMD_DEFAULTS   { 0, \
                                    0, \
                                    2, \
								                   	2, \
									                  2, \
									                  0, \
								                  	0, \
								                  	0, \
                                    0, \
                                    0, \
                                    0, \
                                    0, \
                                    0, \
                                    0, \
                                    0, \
									                  0, \
									                  0, \
                                    0, \
									                  0, \
                                    0, \
                                    0, \
                                    0, \
									                  0, \
                                    100, \
									                  0, \
									                  0, \
									                  0,\
																		0,\
                               (void (*)(long))contrl_frq_Init, \
                               (void (*)(long))contrl_frq_calc, \
                               (void (*)(long))contrl_frq_filt}

/*------------------------------------------------------------------------------
Prototypes for the functions in SPEED_FR.C
------------------------------------------------------------------------------*/

void contrl_frq_calc(SPEED_MEAS_CMD_handle);
void contrl_frq_filt(SPEED_MEAS_CMD_handle);
void contrl_frq_Init(SPEED_MEAS_CMD_handle);
extern void DataBusDirOut(void);
extern void DataBusDirIn(void);
extern void CommandAddr(int cmd);
extern void WriteDataBus(unsigned int  data);
extern unsigned int ReadDataBus(void);
extern void IOinputCheck(void);
extern void ServoPowerOn(void);
extern void ServoIDLE(void);
extern void ServoRun(void);
extern void ServoNormalAlarm(void);
extern void ServoBreakeAlarm(void);
extern  long  ReadCmdTimerL1(void);
extern  long  ReadCmdTimerL2(void);
extern  long  ReadCmdTimerH1(void);
extern  long  ReadCmdTimerH2(void);
extern  long ReadCmdTimer(void);
extern  long CpldBusCheck(void);  //检测CPLD的8位数据总线接触是否良好

extern  int16_t LED_PULSE_DISP;
extern  int16_t LED_DIR_DISP;
#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_CONTRL_H_ */
