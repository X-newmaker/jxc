/*
 * pos.h
 *
 *  Created on: 2023年8月11日
 *      Author: wenxing.ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_POS_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_POS_H_

#include "IQmathlib.h"
typedef struct {
       long  fdb_new;  	  // long
       long  dir_CMD;
       long  fdb_old;   	  // long
       long  fdb_frq;      // long
       long  rpm_max;
       long  K1;
       long  K2;
       long  K3;
       long  speed_rpm;
       long  tmp2;
       long  pulse_ref;
       void (*init)();
       void (*calc)();
       } SPEED_MEAS_POS;

typedef SPEED_MEAS_POS *SPEED_MEAS_POS_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the CMD_MEAS_QEP object.
-----------------------------------------------------------------------------*/
#define SPEED_MEAS_POS_DEFAULTS   { 0, \
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
                               (void (*)(long))pos_frq_Init, \
                               (void (*)(long))pos_frq_calc }
typedef struct {
      float  speed_ref;
      long  pos_sum_ref;
      long  pos_sum_real;
      long  pos_sum_save;
      long  _long_pr_pos_ref;
     float  pr_speed_ref;
     float  float_pr_pos_ref;
     float  pr_pos_save;
       int  pos_sel;
       int  auto_run_en;
       int   rmp_target_value; 	/* Input: Target input (pu) */
      long  rmp_dly_max;		/* Parameter: Maximum delay rate (Q0) - independently with global Q */
	  long  rmp_lo_limit;		/* Parameter: Minimum limit (pu) */
	  long  rmp_hi_limit;		/* Parameter: Maximum limit (pu) */
	  long  rmp_delay_cntl;  /* Variable: Incremental delay (Q0) - independently with global Q */
	  long  rmp_inc_dec_time;//加减时间(ms),指从零速加速到3000rpm或-3000rpm
	  long  rmp_spd_max;
	  long  rmp_pos_loop_ps; //位置环速度采样周期
	  long  rmp_spd_inc;     //加减速速度步长
	   int  rmp_setpt_value;		/* Output: Target output (pu) */
	   int  pos_target_value;
	  long  pos_setpt_value;
	  long  pos_rmp_spd_inc;
	  long  rmp_speed_sync;
	   int  auto_run_mod;
	  long  RemainS;
	  long  position_max;
	   int  Pr_ctrl_start;
	   int  PrRunFinishFlag;
	  long  rmp_setpt_value_sum;
       void (*init)();
       void (*calc)();
       } SPEED_MEAS_PR;

typedef SPEED_MEAS_PR *SPEED_MEAS_PR_handle;
#define SPEED_MEAS_PR_DEFAULTS   { 0, \
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
                               _IQ(-1), \
                          	    _IQ(1), \
                          	        0, \
                          	       100, \
                          	      3000, \
                          	         7, \
                        _IQ(0.0000305), \
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
                                (void (*)(long))Pr_frq_Init, \
                               (void (*)(long))Pr_frq_calc }
/*------------------------------------------------------------------------------
Prototypes for the functions in SPEED_FR.C
------------------------------------------------------------------------------*/
void pos_frq_calc(SPEED_MEAS_POS_handle);
void pos_frq_Init(SPEED_MEAS_POS_handle);

void Pr_frq_calc(SPEED_MEAS_PR_handle);
void Pr_frq_Init(SPEED_MEAS_PR_handle);

void PrSendPulseFinish(void);
void PrRunCtrlCalc(s32 AxiseIncPosition,s16 MotorSpeed);

extern SPEED_MEAS_POS pos;
#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_POS_H_ */
