/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_PBUS_H_
#define INCLUDE_HAL_PBUS_H_

#include <all_inc.h>
/***************************************************************************
                        Register Description
***************************************************************************/
typedef enum pubs_clk_div {
	HCLK_D2 = 1,
	HCLK_D4 = 2,
	HCLK_D8 = 3,
	HCLK_D16 = 0
}pubs_clk_div_t;

typedef enum pubs_signal_pol {
	PBUS_LOW = 0,
	PBUS_HIGH = 1
}pubs_signal_pol_t;

typedef enum pubs_work_mode {
	PBUS_CPU_DIR = 0,
	PBUS_DMA_DIR = 1,
	PBUS_DMA_FIFO_READ = 2,
	PBUS_DMA_FIFO_WRITE = 3
}pubs_work_mode_t;

typedef enum pubs_mode {
	MANU_MODE = 0,
	PBUS_ADDR_DATA_SHARE = 1,		//1: 地址/数据总线
	PBUS_ADDR_DATA_SPLIT = 2,		//2: 地址+数据总线
	PBUS_I8080 = 3,
	PBUS_I6800 = 4
}pubs_mode_t;

typedef enum pubs_data_width {
	PBUS_DATA_X16 = 0,				//0: 16 位数据总线
	PBUS_DATA_X8 = 1				//1: 8 位数据总线
}pubs_data_width_t;

union pbus_cfg_t {
	u32 dwval;
	struct {						//bit description
		u32 clk_div		:  2;		//1:0   CLK_DIV
		u32 clk_oe		:  1;		//2		CLK_OE
		u32 clk_pol		:  1;		//3		CLK_POL
		u32 ncs_pol		:  1;		//4		NCS_POL
		u32 nadv_pol	:  1;		//5		NADV_POL
		u32 nwe_pol		:  1;		//6		NWE_POL
		u32 noe_pol		:  1;		//7		NOE_POL
		u32 work_mode	:  2;		//9:8	WORK_MODE
		u32 res0		:  2;
		u32 addr_bus_en		:  1;	//12	ADDR_BUS_EN
		u32 ncs_check_dat_en	:  1;	//13	NCS_CHECK_DAT_EN
		u32 manu_addr_from_fifo	:  1;	//14	MANU_ADDR_FROM_FIFO
		u32 manu_addr_incr	:  1;	//15	MANU_ADDR_INCR
		u32 pbus_mode		:  3;	//18:16	PBUS_MODE
		u32 pbus_data_width	:  1;	//19	PBUS_DATA_WIDTH
		u32 pbus_cs_sel		:  1;
		u32 res1		: 11;
	} bits;
};

union pbus_ctl_t {
	u32 dwval;
	struct {
		u32 pbus_clr	:  1;	//0	PBUS_CLR
		u32 res		:  31;
	} bits;
};

union pbus_fifo_cfg_t {
	u32 dwval;
	struct {
		u32 pbus_thr	:  5;	//4：0	FIFO_THR
		u32 res		:  27;
	} bits;
};

union pbus_fifo_sta_t {
	u32 dwval;
	struct {
		u32 fifo_empty	:  1;	//0	FIFO_EMPTY
		u32 fifo_full	:  1;	//1	FIFO_FULL
		u32 fifo_dlen	:  10;	//6：2
		u32 res0	:  4;
		u32 pbus_busy	:  1;
		u32 res1	:  15;
	} bits;
};

union pbus_tim_ncs_t {
	u32 dwval;
	struct {
		u32 ncs_pre	:  4;	//3:0	NCS PRE
		u32 res		:  4;
		u32 ncs_pha	:  20;	//27:8	NCS_PHA
		u32 ncs_post	:  4;	//31:28	NCS_POST
	} bits;
};

union pbus_tim_nadv_t {
	u32 dwval;
	struct {
		u32 nadv_pre	:  4;	//3:0	NADV_PRE
		u32 res0	:  4;
		u32 nadv_pha	:  4;	//11:8	NADV_PHA
		u32 res1	:  20;
	} bits;
};

union pbus_tim_nwe_t {
	u32 dwval;
	struct {
		u32 nwe_pre	:  4;		//3:0	NWE_PRE
		u32 res0	:  4;
		u32 nwe_pha0	:  4;	//11:8	NWE_PHA0
		u32 res1	:  4;
		u32 nwe_wait	:  4;	//19:16	NWE_WAIT
		u32 res2	:  4;
		u32 nwe_pha1	:  4;	//27:24	NWE_PHA1
		u32 res3	:  4;
	} bits;
};

union pbus_tim_noe_t {
	u32 dwval;
	struct {
		u32 noe_pre	:  4;		//3:0	NOE_PRE
		u32 res0	:  4;
		u32 noe_pha0	:  4;	//11:8	NOE_PHA0
		u32 res1	:  4;
		u32 noe_wait	:  4;	//19:16	NOE_WAIT
		u32 res2	:  4;
		u32 noe_pha1	:  4;	//27:24	NOE_PHA1
		u32 res3	:  4;
	} bits;
};

union pbus_tim_dat_t {
	u32 dwval;
	struct {
		u32 dat_pre	:  4;		//3:0	DAT_PRE
		u32 res0	:  4;
		u32 dat_pha0	:  4;	//11:8	DAT_PHA0
		u32 res1	:  4;
		u32 dat_wait	:  4;	//19:16	DAT_WAIT
		u32 res2	:  4;
		u32 dat_pha1	:  4;	//27:24	DAT_PHA1
		u32 res3	:  4;
	} bits;
};

union pbus_tim_adr_t {
	u32 dwval;
	struct {
		u32 adr_pre	:  4;		//3:0	ADR_PRE
		u32 res0	:  4;
		u32 adr_pha	:  4;		//11:8	ADR_PHA
		u32 res1	:  20;
	} bits;
};

union pbus_irq_en_t {
	u32 dwval;
	struct {
		u32 fifo_irq_en	:  1;	//0	FIFO_IRQ_EN
		u32 res		:  31;
	} bits;
};

union pbus_irq_sta_t {
	u32 dwval;
	struct {
		u32 fifo_irq_sta	:  1;	//0	FIFO_IRQ_STA
		u32 res			:  31;
	} bits;
};

union pbus_val_set_t {
	u32 dwval;
	struct {
		u32 ncs_idle_value	:  1;	//0		NCS IDLE VALUE
		u32 ncs_pre_value	:  1;	//1		NCS PRE VALUE
		u32 ncs_pha_value	:  1;	//2		NCS PHA VALUE
		u32 ncs_post_value	:  1;	//3		NCS POST VALUE
		u32 res0		:  4;
		u32 nadv_idle_value	:  1;	//8		NADV IDLE VALUE
		u32 nadv_pre_value	:  1;	//9		NADV PRE VALUE
		u32 nadv_pha_value	:  1;	//10	NADV PHA VALUE
		u32 res1		:  5;
		u32 nwe_idle_value	:  1;	//16	NWE IDLE VALUE
		u32 nwe_pre_value	:  1;	//17	NWE PRE VALUE
		u32 nwe_pha0_value	:  1;	//18	NWE PHA0 VALUE
		u32 nwe_wait_value	:  1;	//19	NWE WAIT VALUE
		u32 nwe_pha1_value	:  1;	//20	NWE PHA1 VALUE
		u32 res2		:  3;
		u32 noe_idle_value	:  1;	//24	NOE IDLE VALUE
		u32 noe_pre_value	:  1;	//25	NOE PRE VALUE
		u32 noe_pha0_value	:  1;	//26	NOE PHA0 VALUE
		u32 noe_wait_value	:  1;	//27	NOE WAIT VALUE
		u32 noe_pha1_value	:  1;	//28	NOE PHA1 VALUE
		u32 res3		:  3;
	} bits;
};

union pbus_data_num_t {
	u32 dwval;
	struct {
		u32 data_num	:  10;		//9:0	DATA_NUM
		u32 res		:  22;
	} bits;
};

union pbus_start_t {
	u32 dwval;
	struct {
		u32 dma_start	:  1;		//0		DMA_START
		u32 res		:  31;
	} bits;
};

union pbus_address_t {
	u32 dwval;
	struct {
		u32 address	:  16;		//15:0		PBUS_Address
		u32 res		:  16;
	} bits;
};

union pbus_data_t {
	u32 dwval;
	struct {
		u32 data	:  32;		//15:0		PBUS_DATA
	} bits;
};

typedef struct pbus_dev_s {
	volatile union pbus_cfg_t 	pbus_cfg;	//offset: 0x00
	volatile union pbus_ctl_t 	pbus_ctl;	//offset: 0x04
	volatile union pbus_fifo_cfg_t 	pbus_fifo_cfg;	//offset: 0x08
	volatile union pbus_fifo_sta_t 	pbus_fifo_sta;	//offset: 0x0C
	volatile union pbus_tim_ncs_t 	pbus_tim_ncs;	//offset: 0x10
	volatile union pbus_tim_nadv_t 	pbus_tim_nadv;	//offset: 0x14
	volatile union pbus_tim_nwe_t 	pbus_tim_nwe;	//offset: 0x18
	volatile union pbus_tim_noe_t 	pbus_tim_noe;	//offset: 0x1C
	volatile union pbus_tim_dat_t 	pbus_tim_dat;	//offset: 0x20
	volatile union pbus_tim_adr_t 	pbus_tim_adr;	//offset: 0x24
	volatile union pbus_irq_en_t 	pbus_irq_en;	//offset: 0x28
	volatile union pbus_irq_sta_t 	pbus_irq_sta;	//offset: 0x2C
	volatile union pbus_val_set_t 	pbus_val_set;	//offset: 0x30
	volatile union pbus_data_num_t 	pbus_data_num;	//offset: 0x34
	volatile union pbus_start_t 	pbus_start;		//offset: 0x38
	volatile union pbus_address_t 	pbus_address;	//offset: 0x3C
	volatile union pbus_data_t 	pbus_data;			//offset: 0x40
}pbus_dev_t;

void pbus_clk_set(pubs_clk_div_t div);
void pbus_clk_out_en(void);
void pbus_clk_pol(pubs_signal_pol_t pol);
void pbus_ncs_pol(pubs_signal_pol_t pol);
void pbus_nadv_pol(pubs_signal_pol_t pol);
void pbus_nwe_pol(pubs_signal_pol_t pol);
void pbus_noe_pol(pubs_signal_pol_t pol);
void pbus_work_mode(pubs_work_mode_t mode);
void pbus_addr_bus_en(void);
void pbus_check_dat_en(void);
void pbus_manu_addr_from_fifo(void);
void pbus_manu_addr_incr(void);
void pbus_mode(pubs_mode_t mode);
void pbus_data_width(pubs_data_width_t width);
void pbus_clr(void);
void pbus_fifo_cfg(u32 level);
void pbus_cs_sel(u32 sel);
s32 pbus_fifo_empty_sta(void);
s32 pbus_fifo_full_sta(void);
s32 pbus_fifo_dlen_sta(void);
s32 pbus_sta(void);
void pbus_tim_ncs(u32 pre, u32 pha, u32 post);
void pbus_tim_nadv(u32 pre, u32 pha);
void pbus_tim_nwe(u32 pre, u32 pha0, u32 wait, u32 pha1);
void pbus_tim_noe(u32 pre, u32 pha0, u32 wait, u32 pha1);
void pbus_tim_dat(u32 pre, u32 pha0, u32 wait, u32 pha1);
void pbus_tim_adr(u32 pre, u32 pha);
void pbus_irq_en(void);
s32 pbus_irq_sta(void);
void pbus_ncs_val_set(u32 idle, u32 pre, u32 pha, u32 post);
void pbus_nadv_val_set(u32 idle, u32 pre, u32 pha);
void pbus_nwe_val_set(u32 idle, u32 pre, u32 pha0, u32 wait, u32 pha1);
void pbus_noe_val_set(u32 idle, u32 pre, u32 pha0, u32 wait, u32 pha1);
void pbus_data_num(u32 num);
void pbus_start(void);
void pbus_address(u32 address);
s32 pbus_read_data(void);

void pbus_cmu_init(void);
#endif /* INCLUDE_HAL_PBUS_H_ */
