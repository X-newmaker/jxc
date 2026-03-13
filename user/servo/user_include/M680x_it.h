/*
 * M680x_it.h
 *
 *  Created on: 2023年8月10日
 *      Author: wenxing.ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_M680X_IT_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_M680X_IT_H_

#include "stdint.h"
#include "string.h"
#include "IQmathlib.h"
#include "rampgen.h"
#include "svo_math.h"
#include "contrl.h"
#include "Const_Def.h"
#include "e2prom.h"
#include "encoder.h"
#include "GVAR_DEF.h"
#include "ledcode.h"
#include "low_fil.h"
#include "m680xpwm.h"
#include "mainIint_m680x.h"
#include "modbusRTU.h"
#include "M680x_xileg_vdc.h"
#include "pid_reg3.h"
#include "pos.h"
#include "rampgen.h"
#include "rmp_cntl.h"
#include "speed_fr.h"
#include "user_io.h"
#include "waveform.h"
#include "Const_Def.h"
#include "bldc_foc.h"
#include "esc_csp.h"
#include "hcl_pmsm_ctrl.h"
extern void HCL_DONE_isr(void);
extern void EPWM_IRQHandler_isr(void);
extern void PWM_IRQHandler_isr(void);
extern void EPWM_FLT_isr(void);
extern void WDOG_IRQ_isr(void);

extern int16_t   g_PosRefUpdateFlag;
extern int16_t   _iqsin_value;
extern int16_t   _iqcos_value;
extern int16_t   speed_loop_ps;
extern int16_t   speed_loop_count;
extern int16_t   position_loop_ps;
extern int16_t   position_loop_count;
extern int16_t   speed_disp_ol;
extern int16_t   TimeData[];
extern int16_t   TimeSaveFlag;
extern int32_t   TimeSaveCnt;
extern int32_t   pos_ek_err;
extern int32_t   ExternSerovN;
extern int32_t   ExternSerovM;
extern int64_t   pos_sum_ek_out;
extern int16_t   ParSaveEnable;
extern int32_t   power_up_delay;
extern int32_t   power_up_delay_ps;
extern int16_t   puwer_up_delay_finish_flag;
extern int16_t   ServoRunState;
extern int32_t   int_speed_max;
extern int16_t   speed_spd;
extern int64_t   run_start_time;
extern int64_t   run_end_time;
extern int32_t   run_irq_time;

extern  float    PWM_T;
extern  float    Vq_testing;
extern  float    Iq_testing;
extern  float    speed_ref;
extern int16_t   speed_disp_sr;
extern int16_t   speed_disp_jr;
extern int16_t   speed_disp_ol_flag;

extern  FILTER   spd_fil1;
extern  FILTER   spd_fil2;
extern  FILTER   spd_fil3;
extern  FILTER   park_de_fil1;
extern  FILTER   park_qe_fil1;
extern  FILTER   pos_bef_fil1;
extern  ILEG2DCBUSMEAS ilg2_vdc1;



extern  PIDREG3 pid1_id;
extern  PIDREG3 pid1_iq;
extern  PIDREG3 pid1_spd;
extern  PIDREG3 pid1_pos;
extern  SPEED_MEAS_PR  pr1;
extern  PIDREG3 pid1_fdb_bef;

extern  PWMGEN pwm1;
extern  SPEED_MEAS_POS pos;
extern  SPEED_MEAS_QEP speed1;
extern  SPEED_MEAS_CMD contrl;
extern  SPEED_MEAS_CMD cmd_hz;
extern  SPD_RMPCNTL spd_rc1;

extern  pi_t pi_spd1;
extern  pi_t pi_id1;
extern  pi_t pi_iq1;

extern  clarke_t clark1;
extern  park_t park1;
extern  ipark_t ipark1;
extern  svpwm_t svpwm1;
extern  abs_param_t abs_param1;
extern  speed_t abs_speed1;
extern  rmpcntl_t rmp1;
extern  wdog_cfg_reg_t wdog1;
extern  RAMPGEN rg1;
extern  SERVO_PAR Servo;
extern  SERVO_ERR Err;
extern  SERVO_DI  IoDi;
extern  SERVO_DO  IoDo;
extern  SERVO_FN  Fn;
extern  SERVO_PDO EscPdo;
extern  HCL_SWITCH HclSwitch;
extern  SERVO_COMM ServoCommData;
extern  void MS_SpeedLoop(_iq SpdPidInput);
extern  void MS_CurLoop(_iq IqPidInput );
extern  void MS_DcbusClac(void);
extern  void motor_para_real_cala(void);
extern  void MS_CurrentOverCheck(void);
extern  void MS_DispMotorSpeed(void);
extern  void MS_ResetCheck(void);
extern  void motor_para_init(void);
extern  void MS_ParaInit(void);
extern  void motor_para_cala(void);
extern  void LdFromParaIint(void);
extern  void MS_RUN(void);
extern  void MS_STOP(void);
extern  void MS_ERROR(void);
extern  void MS_CO(void);
extern  void ioPinOutput(void);
extern  void cordic_cal_user(s32 data1, _iq *result1,_iq *result2);

extern uint16_t g_custom_data[CUSTOM_DATA_COUNT];
extern uint16_t sendflag;
#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_M680X_IT_H_ */
