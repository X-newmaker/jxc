/*
 * speed_fr.h
 *
 *  Created on: 2023年8月11日
 *      Author: wenxing.ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_SPEED_FR_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_SPEED_FR_H_

#include "IQmathlib.h"
typedef struct {
       _iq  speed_raw;
       _iq  theta_elec;
       _iq  theta_new;
       _iq  theta_old;
       _iq  speed_frq;
       _iq  K2;
       _iq  K3;
       _iq  speed_input;
	   _iq  speed_max;
       _iq  speed_rpm;
	   _iq   position_max;
	   _iq  PulseSendMax;
	   _iq SpeedBackKp;
	   _iq SpeedAccNew;
	   _iq SpeedAccOld;
	   _iq SpeedAccEk;
	   _iq SpeedAccOput;
	   _iq SpeedXn;
	   _iq SpeedYn;
	   _iq SpeedYn_1;
       void (*calc)();
       void (*hcl_calc)();
       } SPEED_MEAS_QEP;

typedef SPEED_MEAS_QEP *SPEED_MEAS_QEP_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the SPEED_MEAS_QEP object.
-----------------------------------------------------------------------------*/
#define SPEED_MEAS_QEP_DEFAULTS   { 0, \
                                    0, \
                                    0, \
                                    0, \
                                    0, \
									0, \
                                    0, \
                                    0, \
									47934,\
									50,\
									350,\
                                    28631,\
									16777216,\
									0,\
									0,\
									0,\
									0,\
									0,\
									0,\
									0,\
                               (void (*)(long))speed_frq_calc,\
							   (void (*)(long))hcl_speed_frq_calc,}

/*------------------------------------------------------------------------------
Prototypes for the functions in SPEED_FR.C
------------------------------------------------------------------------------*/
void speed_frq_calc(SPEED_MEAS_QEP_handle);
void hcl_speed_frq_calc(SPEED_MEAS_QEP_handle);
extern SPEED_MEAS_QEP speed1;
#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_SPEED_FR_H_ */
