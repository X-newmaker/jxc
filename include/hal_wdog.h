/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_WDOG_H_
#define INCLUDE_HAL_WDOG_H_

typedef enum wdog_op_e{
	WDOG_OP_CFG_SW0 =  0,
	WDOG_OP_CFG_SW1 =  1,
	WDOG_OP_CFG_SW2 =  2,
	WDOG_OP_CFG_SW3 =  3,
	WDOG_OP_CNT_CLR	=  4,
	WDOG_OP_WR_EN 	=  5,
}wdog_op_t;

typedef struct wdog_cfg_reg_s {
	u32 wdog_clr_thd_reg;
	u32 wdog_irq_thd_reg;
	u32 wdog_rst_thd_reg;
	u32 wodg_res_thd_reg;
}wdog_cfg_reg_t;

void wdog0_irq_handler(void);
void wdog1_irq_handler(void);
void wdog_irq_register(u32 num, cpu_irq_fun_t irqhandle);
void wdog_irq_unregister(u32 num);
s32 wdog_enable(u32 dis);
s32 wdog_cfg(u32 id, wdog_cfg_reg_t* cfg);
void wdog_cmu_init(void);
s32 wdog_op(wdog_op_t op);
u32 wdog_get_cnt(void);
s32 wdog_irq_enable(void);
s32 wdog_irq_disable(void);
u32 wdog_irq_query(void);
s32 wdog_irq_clear(u32 status);
void wdog_set_clr_thd(u32 id, u32 clr_thd);
void wdog_set_irq_thd(u32 id, u32 irq_thd);
void wdog_set_rst_thd(u32 id, u32 rst_thd);
void wdog_expire_now(u32 id);
void wdog_force_reset(void);

typedef union wdog_ctl_reg_u {
	u32 dwval;
	struct {
		u32 cnt_en		:   1;
		u32 dbg_cnt_continue	:   1;
		u32 res0 		:  26;
		u32 reg_wr_dis		:   2;
		u32 res1 		:   2;
	} bits;
}wdog_ctl_reg_t;

typedef union wdog_cnt_reg_u {
	u32 dwval;
	struct {
		u32 cnt			:  32;
	} bits;
}wdog_cnt_reg_t;

typedef union wdog_irq_en_reg_u {
	u32 dwval;
	struct {
		u32 timeout_irq_en	:   1;
		u32 res0 		:  31;
	} bits;
}wdog_irq_en_reg_t;

typedef union wdog_irq_sta_reg_u {
	u32 dwval;
	struct {
		u32 timeout_irq_sta	:   1;
		u32 res0 		:  31;
	} bits;
}wdog_irq_sta_reg_t;

typedef union wdog_op_reg_u {
	u32 dwval;
	struct {
		u32 op 			:  32;
	} bits;
}wdog_op_reg_t;

typedef union wdog_ver_reg_u {
	u32 dwval;
	struct {
		u32 version 		:  32;
	} bits;
}wdog_ver_reg_t;

typedef union wdog_res_reg_u {
	u32 dwval;
	struct {
		u32 res0;
	} bits;
}wdog_res_reg_t;

typedef union wdog_force_rst_reg_u {
	u32 dwval;
	struct {
		u32 key 		:  32;
	} bits;
}wdog_force_rst_reg_t;

typedef union wdog_rst_sel_reg_u {
	u32 dwval;
	struct {
		u32 rst_sel		:   1;
		u32 res0 		:  31;
	} bits;
}wdog_rst_sel_reg_t;

typedef struct wdog_dev_s {
	volatile wdog_ctl_reg_t		wdog_ctl_reg;
	volatile wdog_cnt_reg_t 	wdog_cnt_reg;
	volatile wdog_irq_en_reg_t 	wdog_irq_en_reg;
	volatile wdog_irq_sta_reg_t 	wdog_irq_sta_reg;	wdog_res_reg_t wdog_res010[1];
	volatile wdog_force_rst_reg_t 	wdog_force_rst_reg;	wdog_res_reg_t wdog_res018[2];
	volatile wdog_rst_sel_reg_t 	wdog_rst_sel_reg;	wdog_res_reg_t wdog_res024[7];
	volatile wdog_cfg_reg_t 	wdog_cfg_reg[4];	wdog_res_reg_t wdog_res080[26];
	volatile wdog_op_reg_t		wdog_op_reg;		wdog_res_reg_t wdog_res0ec[964];
	volatile wdog_ver_reg_t		wdog_ver_reg;
}wdog_dev_t;


#endif /* INCLUDE_HAL_WDOG_H_ */
