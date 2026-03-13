/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 */

/*
 * gpt.h
 *
 *  Created on: 2023/9/13
 *      Author: guanhua.hu
 */

#ifndef GPT_H_
#define GPT_H_

#include "all_inc.h"

#define GPT_NUM		4
#define OUT_NUM		4
typedef enum gpt_trg_mode_e {
	GPT_TRG_MODE_AUTO		=    0,
	GPT_TRG_MODE_RSI		=    1,
	GPT_TRG_MODE_FALL		=    2,
	GPT_TRG_MODE_BILATERAL		=    3,

}gpt_trg_mode_t;

typedef enum gpt_run_mode_e {
	GPT_RUN_MODE_SINGLE		=    0,
	GPT_RUN_MODE_LOOP		=    1,

}gpt_run_mode_t;


typedef enum gpt_clk_div_e {
	GPT_NS_8			=    120000000,
	GPT_NS_100			=    10000000,
	GPT_US				=    1000000,
	GPT_US_10			=    100000,
	GPT_US_100			=    10000,
	GPT_MS				=    1000,

}gpt_clk_div_t;

typedef enum gpt_cmp_out_e {
	CMP_OUT_LOW			=    0,
	CMP_OUT_HIGH			=    1,
	CMP_OUT_INVERT			=    2,
	CMP_OUT_KEEP			=    3,

}gpt_cmp_out_t;

typedef enum gpt_out_init_e {
	OUT_INIT_LOW			=    0,
	OUT_INIT_HIGH			=    1,

}gpt_out_init_t;

typedef enum gpt_out_en_e {
	OUT_CLOSE			=    0,
	OUT_EN				=    1,

}gpt_out_en_t;

typedef enum gpt_out_num_e {
	OUT_0				=    0,
	OUT_1				=    1,
	OUT_2				=    2,
	OUT_3				=    3,

}gpt_out_num_t;

typedef enum out_cmpx_e {
	CMPA				=    0,
	CMPB				=    1,

}out_cmpx_t;

typedef enum gpt_en_e {
	GPT_CLOSE			=    0,
	GPT_EN				=    1,

}gpt_en_t;

typedef enum gpt_irq_e {
	OUT3_COMPB_IRQ		=	29,
	OUT3_COMPA_IRQ		=	28,
	OUT2_COMPB_IRQ		=	25,
	OUT2_COMPA_IRQ		=	24,
	OUT1_COMPB_IRQ		=	21,
	OUT1_COMPA_IRQ		=	20,
	OUT0_COMPB_IRQ		=	17,
	OUT0_COMPA_IRQ		=	16,
	TRG_IN_IRQ		=	 1,
	CNTR_MAX_IRQ		=	 0,

}gpt_irq_t;

typedef enum gpt_num_e {
	GPT9		=	9,
	GPT8		=	8,
	GPT7		=	7,
	GPT6		=	6,
	GPT5		=	5,
	GPT4		=	4,
	GPT3		=	3,
	GPT2		=	2,
	GPT1		=	1,
	GPT0		=	0,

}gpt_num_t;

void gpt_irq_register(u8 num, cpu_irq_fun_t irqhandle);
void gpt_irq_unregister(u8 num);
s32 init_gpt(gpt_num_t gpt_num,u32 trg_db,gpt_trg_mode_t trg_mode,gpt_run_mode_t run_mode,gpt_clk_div_t div,u32 cntr_val,u32 cntr_max);
s32 init_gpt_out(gpt_num_t gpt_num,u32 out_num,gpt_out_init_t out_init,u32 cmp_val_a,gpt_cmp_out_t cmp_out_a,
                                                                 u32 cmp_val_b,gpt_cmp_out_t cmp_out_b,gpt_out_en_t en);
void gpt_cmu_init(u8 num);
s32 gpt_en(gpt_num_t gpt_num);
s32 gpt_irq_enable(gpt_num_t gpt_num,gpt_irq_t id);
u32 gpt_irq_status(gpt_num_t gpt_num);
s32 gpt_irq_clear(gpt_num_t gpt_num,u32 status);
s32 gpt_irq_disable(gpt_num_t gpt_num,gpt_irq_t id);
s32 gpt_disable(gpt_num_t gpt_num);
u32 gpt_get_time(gpt_num_t gpt_num);
void gpt_set_time(gpt_num_t gpt_num,u32 value);
s32 gpt_irq_enable_all(gpt_num_t gpt_num);
s32 gpt_trg_get_val(gpt_num_t gpt_num);
s32 gpt_db0_point(gpt_num_t gpt_num,u32 point);
s32 gpt_db1_point(gpt_num_t gpt_num,u32 point);
s32 gpt_db1_div(gpt_num_t gpt_num,u32 samp);

#define   GPT_CTL(n)      		(BASE_GPT0 + (n)*0x100 + 0x00)         //General Purpose Timer Control
#define   GPT_CLK(n)        	(BASE_GPT0 + (n)*0x100 + 0x04)         //General Purpose Timer Clock
#define   GPT_IRQ_EN(n)        	(BASE_GPT0 + (n)*0x100 + 0x08)         //Interrupt Request Enable
#define   GPT_IRQ_STA(n)        (BASE_GPT0 + (n)*0x100 + 0x0C)         //Interrupt Request Status
#define   GPT_CNTR_VAL(n)       (BASE_GPT0 + (n)*0x100 + 0x10)         //Counter Value
#define   GPT_CNTR_MAX(n)       (BASE_GPT0 + (n)*0x100 + 0x14)         //Counter Max
#define   GPT_CNTR_CLR(n)       (BASE_GPT0 + (n)*0x100 + 0x1C)         //Counter Clear
#define   GPT_OUT0_CMPA(n)      (BASE_GPT0 + (n)*0x100 + 0x40)         //Output 0 Compare A Register
#define   GPT_OUT1_CMPA(n)      (BASE_GPT0 + (n)*0x100 + 0x50)         //Output 1 Compare A Register
#define   GPT_OUT2_CMPA(n)      (BASE_GPT0 + (n)*0x100 + 0x60)         //Output 2 Compare A Register
#define   GPT_OUT3_CMPA(n)      (BASE_GPT0 + (n)*0x100 + 0x70)         //Output 3 Compare A Register
#define   GPT_OUT0_CMPB(n)      (BASE_GPT0 + (n)*0x100 + 0x44)         //Output 0 Compare B Register
#define   GPT_OUT1_CMPB(n)      (BASE_GPT0 + (n)*0x100 + 0x54)         //Output 1 Compare B Register
#define   GPT_OUT2_CMPB(n)      (BASE_GPT0 + (n)*0x100 + 0x64)         //Output 2 Compare B Register
#define   GPT_OUT3_CMPB(n)      (BASE_GPT0 + (n)*0x100 + 0x74)         //Output 3 Compare B Register
#define   GPT_OUT0_CFG(n)      	(BASE_GPT0 + (n)*0x100 + 0x4C)         //Output 0 Configuration Register
#define   GPT_OUT1_CFG(n)    	(BASE_GPT0 + (n)*0x100 + 0x5C)         //Output 1 Configuration Register
#define   GPT_OUT2_CFG(n)    	(BASE_GPT0 + (n)*0x100 + 0x6C)         //Output 2 Configuration Register
#define   GPT_OUT3_CFG(n)    	(BASE_GPT0 + (n)*0x100 + 0x7C)         //Output 3 Configuration Register
#define   GPT_VERSION(n)     	(BASE_GPT0 + (n)*0x100 + 0xFC)

#endif /* GPT_H_ */


