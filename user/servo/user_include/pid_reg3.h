/*
 * pid_reg3.h
 *
 *  Created on: 2023年8月11日
 *      Author: wenxing.ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_PID_REG3_H_
#define EXAMPLE_SVO_EXAMPLE_PID_REG3_H_

#include "IQmathlib.h"
typedef struct {  _iq  pid_ref_reg3;   	/* Input: Reference input  */
				  _iq  pid_fdb_reg3;   	/* Input: Feedback input  */
				  _iq  e_reg3;			/* Variable: Error    */
				  _iq  Kp_reg3;			/* Parameter: Proportional gain  */
	                           _iq  Ki_reg3;			/* Parameter: Integral gain   */
				  _iq  Kc_reg3;			/* Parameter: Integral correction gain  */
				  _iq  Kd_reg3; 		/* Parameter: Derivative gain   */
				  _iq  Kp1_reg3;
				  _iq  Kp2_reg3;
				  _iq  Kp3_reg3;
				  _iq  Ki1_reg3;
				  _iq  Ki2_reg3;
				  _iq  up_reg3;			/* Variable: Proportional output  */
				  _iq  ui_reg3;			/* Variable: Integral output    */
				  _iq  ud_reg3;			/* Variable: Derivative output    */
				  _iq  uprsat_reg3; 	/* Variable: Pre-saturated output  */
				  _iq  pid_out_reg3;   	/* Output: PID output    */
				  _iq  saterr_reg3;		/* Variable: Saturated difference */
				  _iq  up1_reg3;		/* History: Previous proportional output  */
		 	 	  _iq  pid_type;
				  _iq  pid_p_sel;
		 	 	  _iq  motor_speed;
				  _iq  SpeedBefRef;
				  _iq  SpeedBefOut;
				  _iq  SpeedAccOut;
				  _iq  pi_ek_max;
		 	 	  _iq  pi_ek_min;
		 	 	  _iq  speed_frq_max;
		 	 	  _iq  speed_frq_min;
                  _iq  pid_out_max;		/* Parameter: Maximum output    */
				  _iq  pid_out_min;		/* Parameter: Minimum output    */
				  _iq  pi_away_flag;
		 	 	   void  (*init)();
		 	 	   void  (*calc)();	  	/* Pointer to calculation function */
				 } PIDREG3;

typedef PIDREG3 *PIDREG3_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the PIDREG3 object.
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
Default initalizer for the PIDREG3 object.
-----------------------------------------------------------------------------*/
#define PIDREG3_DEFAULTS { 0, \
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
                           0, \
                           0, \
                           0, \
                           0, \
                           0, \
                           0, \
                    _IQ(0.1), \
              	   _IQ(-0.1), \
              		_IQ(0.1), \
              	   _IQ(-0.1), \
              		  _IQ(1), \
              		 _IQ(-1), \
				           0, \
						   (void (*)(long))pid_reg3_init,\
                           (void (*)(long))pid_reg3_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in PIDREG3.C
------------------------------------------------------------------------------*/


void pid_reg3_init(PIDREG3_handle);
void pid_reg3_calc(PIDREG3_handle);

#endif /* EXAMPLE_SVO_EXAMPLE_PID_REG3_H_ */
