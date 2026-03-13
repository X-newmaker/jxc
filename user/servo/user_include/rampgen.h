/*
 * rampgen.h
 *
 *  Created on: 2023年8月11日
 *      Author: wenxing.ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_RAMPGEN_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_RAMPGEN_H_

#include "IQmathlib.h"
typedef struct { _iq  rmp_freq; 		/* Input: Ramp frequency (pu) */
			     _iq  step_angle_max;	/* Parameter: Maximum step angle (pu) */
			     _iq  angle_rg;			/* Variable: Step angle (pu) */
			     _iq  rmp_gain;			/* Input: Ramp gain (pu) */
			     _iq  rmp_out;  	 	/* Output: Ramp signal (pu) */
			     _iq  rmp_offset;		/* Input: Ramp offset (pu) */
			     _iq  rmp_base;
			     int  rmp_flag;
			     int  rmp_dir;
			  void  (*calc)();	  	    /* Pointer to calculation function */
			   } RAMPGEN;

typedef RAMPGEN *RAMPGEN_handle;
/*------------------------------------------------------------------------------
      Object Initializers
------------------------------------------------------------------------------*/
#define RAMPGEN_DEFAULTS {0,0,0,_IQ(1),0,_IQ(0),0,0,1,\
                         (void (*)(long))rampgen_calc }

/*------------------------------------------------------------------------------
      Funtion prototypes
------------------------------------------------------------------------------*/
void rampgen_calc(RAMPGEN_handle);

#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_RAMPGEN_H_ */
