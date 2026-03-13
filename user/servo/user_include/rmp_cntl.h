/*
 * rmp_cntl.h
 *
 *  Created on: 2023年8月11日
 *      Author: wenxing.ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_RMP_CNTL_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_RMP_CNTL_H_

#include "stdint.h"
#include "IQmathlib.h"
typedef struct { int32_t   target_value; 	/* Input: Target input (pu) */
				 int16_t   rmp_dly_max;		/* Parameter: Maximum delay rate (Q0) - independently with global Q */
				 int32_t   rmp_delay_cntl;  /* Variable: Incremental delay (Q0) - independently with global Q */
				 int32_t   rmp_inc_dec_time;//加减时间(ms),指从零速加速到3000rpm或-3000rpm
				 int32_t   rmp_spd_max;
				 int32_t   rmp_spd_loop_ps; //速度环速度采样周期
				 int32_t   rmp_spd_inc;     //加减速速度步长
				 int32_t   setpt_value;		/* Output: Target output (pu) */
		  	  	 void  (*init)();
		  	  	 void  (*calc)();	  	/* Po_iqer to calculation function */
				 } SPD_RMPCNTL;

typedef SPD_RMPCNTL *SPD_RMPCNTL_handle;

#define SPD_RMPCNTL_DEFAULTS { 0, \
                            10, \
                          	1, \
                          	100, \
                          	3000, \
                          	7, \
                          	0, \
                          	0, \
                          	(void (*)(long))spd_rmp_cntl_init,\
                   			(void (*)(long))spd_rmp_cntl_calc }


void spd_rmp_cntl_init(SPD_RMPCNTL_handle);
void spd_rmp_cntl_calc(SPD_RMPCNTL_handle);
extern int32_t  setpt_value_tmp;
#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_RMP_CNTL_H_ */
