/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_GPIO_H_
#define INCLUDE_HAL_GPIO_H_

#define GPIO(g,p,s) (GPIO_GRP_##g<<12 | p<<4 | s)
#define GPIO_NONE   (0xffff)

typedef enum gpio_grp_e{
	GPIO_GRP_A		=  0,
	GPIO_GRP_B 		=  1,
	GPIO_GRP_C		=  2,
	GPIO_GRP_D   	=  3,
	GPIO_GRP_E   	=  4,
	GPIO_GRP_F   	=  5,
	GPIO_GRP_G      =  6,
	GPIO_GRP_H      =  7,
	GPIO_GRP_K      =  10,
	GPIO_GRP_N   	=  14,
	GPIO_GRP_P   	= 15,
}gpio_grp_t;

typedef enum gpio_fun_e{
	GPIO_FUN_DIS	=  0,
	GPIO_FUN_IO  	=  1,
	GPIO_FUN_2		=  2,
	GPIO_FUN_3   	=  3,
	GPIO_FUN_4   	=  4,
	GPIO_FUN_5   	=  5,
	GPIO_FUN_6   	=  6,
	GPIO_FUN_7   	=  7,
	GPIO_FUN_8   	=  8,
	GPIO_FUN_I 		= 16,
	GPIO_FUN_O  	= 17,
}gpio_fun_t;

typedef enum gpio_drv_e{
	GPIO_DRV_180R	=  0,
	GPIO_DRV_90R 	=  1,
	GPIO_DRV_60R 	=  2,
	GPIO_DRV_45R 	=  3,
	GPIO_DRV_36R 	=  4,
	GPIO_DRV_30R 	=  5,
	GPIO_DRV_26R 	=  6,
	GPIO_DRV_23R 	=  7,
}gpio_drv_t;

typedef enum gpio_pull_e{
	GPIO_PULL_NONE	=  0,
	GPIO_PULL_DOWN 	=  2,
	GPIO_PULL_UP   	=  3,
}gpio_pull_t;

typedef enum gpio_level_e{
	GPIO_LEVEL_LOW 	=  0,
	GPIO_LEVEL_HIGH	=  1,
}gpio_level_t;

typedef enum gpio_irq_e{
	GPIO_IRQ_FALL 	=  0,
	GPIO_IRQ_RISE	=  1,
	GPIO_IRQ_LOW	=  2,
	GPIO_IRQ_HIGH	=  3,
	GPIO_IRQ_DEDG	=  4,
}gpio_irq_t;

void gpio_a_irq_handler(void);
void gpio_b_irq_handler(void);
void gpio_c_irq_handler(void);
void gpio_d_irq_handler(void);
void gpio_e_irq_handler(void);
void gpio_f_irq_handler(void);
void gpio_g_irq_handler(void);
void gpio_k_irq_handler(void);
void gpio_irq_register(gpio_grp_t num, cpu_irq_fun_t irqhandle);
void gpio_irq_unregister(gpio_grp_t num);

s32 init_gpio(void);
s32 gpio_request(const u16* pin, u32 sel, u32 mask, gpio_drv_t drv, gpio_pull_t pull);
s32 gpio_release(const u16* pin, u32 sel, u32 mask);
s32 gpio_enable(gpio_grp_t grp, u32 pin, u32 num, gpio_fun_t fun);
s32 gpio_disable(gpio_grp_t grp, u32 pin, u32 num);
s32 gpio_pin_cfg(gpio_grp_t grp, u32 pin, u32 num, gpio_drv_t drv, gpio_pull_t pull);
s32 gpio_set_val(gpio_grp_t grp, u32 pin, gpio_level_t level);
gpio_level_t gpio_get_val(gpio_grp_t grp, u32 pin);

s32 gpio_irq_samp(gpio_grp_t grp, u32 cyc);
s32 gpio_irq_mode(gpio_grp_t grp, u32 pin, gpio_irq_t mode);
s32 gpio_irq_enable(gpio_grp_t grp, u32 pin);
s32 gpio_irq_disable(gpio_grp_t grp, u32 pin);
u32 gpio_irq_query(gpio_grp_t grp);
s32 gpio_irq_clear(gpio_grp_t grp, u32 status);

/*通用二级去抖配置*/
s32 gpio_db0_point(gpio_grp_t grp, u32 pin, u32 point);
s32 gpio_db1_point(gpio_grp_t grp, u32 pin, u32 point);
s32 gpio_db1_samp(gpio_grp_t grp, u32 pin, u32 samp);

/*AIC1602P V2 add by yufu.qin*/

s32 gpio_clr(gpio_grp_t grp, u32 pin);
s32 gpio_set(gpio_grp_t grp, u32 pin);
s32 gpio_tog(gpio_grp_t grp, u32 pin);

union gen_in_sta_t {
	u32 dwval;
	struct {
		u32 in_sta		:   32;
	} bits;
};

union gen_out_cfg_t {
	u32 dwval;
	struct {
		u32 out_cfg		:   32;
	} bits;
};

union gen_irq_en_t {
	u32 dwval;
	struct {
		u32 irq_en		:   32;
	} bits;
};

union gen_irq_sta_t {
	u32 dwval;
	struct {
		u32 irq_sta		:   32;
	} bits;
};

union gen_in_samp_t {
	u32 dwval;
	struct {
		u32 in_samp_cyc 	:   28;
		u32 res0		:    4;
	} bits;
};

/*AIC1602P V2 add by yufu.qin*/
union gen_out_clr_t {
	u32 dwval;
	struct {
		u32 out_cfg_clr		:   32;
	} bits;
};

union gen_out_set_t {
	u32 dwval;
	struct {
		u32 out_cfg_set		:   32;
	} bits;
};

union gen_out_tog_t {
	u32 dwval;
	struct {
		u32 out_cfg_tog		:   32;
	} bits;
};


union pin_cfg_t {
	u32 dwval;
	struct {
		u32 pin_fun		:    4;
		u32 pin_drv		:    3;
		u32 res0		:    1;
		u32 pin_pull		:    2;
		u32 res1		:    2;
		u32 gen_irq_mode	:    3;
		u32 res2		:    1;
		u32 gen_ie		:    1;
		u32 gen_oe		:    1;
		u32 spe_ie_force	:    1;
		u32 res3		:    1;
		u32 gen_in_db0_point	:    4;
		u32 gen_in_db1_samp	:    4;
		u32 gen_in_db1_point	:    4;
	} bits;
};


union gpio_res_t {
	u32 dwval;
	struct {
		u32 res0;
	} bits;
};

typedef struct grp_cfg_s {
	volatile union gen_in_sta_t  	gen_in_sta;
	volatile union gen_out_cfg_t	gen_out_cfg;
	volatile union gen_irq_en_t	gen_irq_en;
	volatile union gen_irq_sta_t	gen_irq_sta;

	volatile union gen_out_clr_t	gen_out_clr;
	volatile union gen_out_set_t	gen_out_set;
	volatile union gen_out_tog_t	gen_out_tog;
	union gpio_res_t gpio_res[25];

	volatile union pin_cfg_t	pin_cfg[32];
}grp_cfg_t;

typedef struct gpio_dev_s {
	volatile grp_cfg_t  		grp_cfg[16];
}gpio_dev_t;

#endif /* INCLUDE_HAL_GPIO_H_ */
