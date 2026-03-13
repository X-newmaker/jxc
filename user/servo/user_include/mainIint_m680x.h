/*
 * mainIint_m680x.h
 *
 *  Created on: 2024年3月29日
 *      Author: L
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_MAINIINT_M680X_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_MAINIINT_M680X_H_

extern void InitSysCtrl(void);
//extern void MS_PulseCommand_Mode(void);
extern void MS_GPIO_Init(void);
extern void MS_EPWM_Init(void);
extern void MS_PulseCommand_Init(void);
extern void QEP_CNF(uint32_t n);
extern void SDFM_CLK_20MHZ_Init(void);
extern void SDFM_CLK_10MHZ_Init(void);
extern void xpwm_timer_2ms_Init(void);
void gpt_timer_Init(u8 gpt_num);
extern void cordic_cal_int(COR_FUNC_TYP funsel, COR_ITER_TYP iteration, s32 data2);
extern void IRQHandler_set_prio(void);
#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_MAINIINT_M680X_H_ */
