/*
 * m680xpwm.h
 *
 *  Created on: 2023年8月11日
 *      Author: wenxing.ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_M680XPWM_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_M680XPWM_H_

#include "IQmathlib.h"

typedef struct {
	              _iq Mfunc_p;             /* Input: Period scaler (Q15)                */
                  _iq Mfunc_c1;             /* Input: PWM 1&2 Duty cycle ratio (Q15)       */
                  _iq Mfunc_c2;             /* Input: PWM 3&4 Duty cycle ratio (Q15)       */
                  _iq Mfunc_c3;             /* Input: PWM 5&6 Duty cycle ratio (Q15)       */
	             void (*pwm_init)();
                 void (*pwm_on)();         /* Pointer to the init function               */
	             void (*pwm_off)();        /* Pointer to the init function               */
                 void (*pwm_update)();     /* Pointer to the update function             */
               } PWMGEN ;


typedef PWMGEN *PWMGEN_handle;


#define F28X_EV1_FC_PWM_GEN { 0x7FFF, \
                              0x4000, \
                              0x4000, \
                              0x4000, \
	                          (void (*)(long))M680X_EV1_PWM_Init,  \
                              (void (*)(long))M680X_EV1_PWM_On,    \
							  (void (*)(long))M680X_EV1_PWM_Off,   \
                              (void (*)(long))M680X_EV1_PWM_Update \
                             }
#define PWMGEN_DEFAULTS 	F28X_EV1_FC_PWM_GEN
void M680X_EV1_PWM_Init(PWMGEN_handle);
void M680X_EV1_PWM_On(PWMGEN_handle);
void M680X_EV1_PWM_Off(PWMGEN_handle);
void M680X_EV1_PWM_Update(PWMGEN_handle);

#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_M680XPWM_H_ */
