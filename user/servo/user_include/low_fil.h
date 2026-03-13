/*
 * low_fil.h
 *
 *  Created on: 2023年8月11日
 *      Author: wenxing.ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_LOW_FIL_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_LOW_FIL_H_

#include "IQmathlib.h"
typedef struct {  _iq   xn;
                  _iq   yn;
				  _iq   K1;         	/* Parameter: Constant for differentiator (Q21) - independently with global Q */
                  _iq   K2;         		/* Parameter: Constant for low-pass filter (pu) */
                  _iq   K3;         		/* Parameter: Constant for low-pass filter (pu) */
		 	 	  _iq  low_pass_max;
		 	 	  _iq  low_pass_min;
				  int   FliterType;
 	 	 	      void  (*init)();
		 	 	  void  (*calc)();
				 } FILTER;

typedef FILTER *FILTER_handle;

#define FILTER_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
                          0, \
                   16777216, \
                  -16777216, \
					      0, \
                          (void (*)(long))low_filter_init,\
                          (void (*)(long))low_filter_calc }
void low_filter_init(FILTER_handle);
void low_filter_calc(FILTER_handle);

#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_LOW_FIL_H_ */
