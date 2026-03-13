/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 */
/*
 * hal_endatif.h
 */

#ifndef INCLUDE_HAL_ENDATIF_H_
#define INCLUDE_HAL_ENDATIF_H_

typedef enum {
	EDT_TX_TYPE1 = 0x0,
	EDT_TX_TYPE2 = 0x1,
}EDT_TX_TYPE;

typedef enum {
	EDT_RX_TYPE1 = 0x0,
	EDT_RX_TYPE2 = 0x1,
	EDT_RX_TYPE3 = 0x2,
}EDT_RX_TYPE;

typedef enum {
	EDT_1bit = 0x0,
	EDT_2bit = 0x1,
}EDT_RX_ERR_WIDTH;

typedef enum {
	EDT_disable = 0x0,
	EDT_enable = 0x1,
}EDT_EN;

typedef enum {
	EDT_16MHz  = 0x0,
	EDT_8MHz  = 0x1,
	EDT_4MHz  = 0x2,
	EDT_2MHz  = 0x3,
	EDT_1MHz  = 0x4,
	EDT_200KHz = 0x5,
	EDT_100KHz = 0x6,
}EDT_CLOCK_FRE;
/***************************************************************************
                        Register Description
***************************************************************************/
union ENDAT_STRB_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 strb:1;							//0 strb
		volatile u32 rsvd0:7;							//7:1 Reserved
		volatile u32 fsm_rst:1;							//4 fsm_rst
		volatile u32 rsvd1:23;							//31:9 Reserved
	}bit;
};

union ENDAT_CFG1_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 tx_type:2;							//1:0 tx_type
		volatile u32 rx_type:2;							//3:2 rx_type
		volatile u32 rx_err_width:1;					//4 rx_err_width
		volatile u32 ainf2_rx_en:1;						//5 ainf2_rx_en
		volatile u32 ainf1_rx_en:1;						//6 ainf1_rx_en
		volatile u32 hw_trig_en:1;						//7 hw_trig_en
		volatile u32 rsvd0:1;							//8 Reserved
		volatile u32 FTclk:3;							//11:9 FTclk
		volatile u32 Hw_rx_err_bps_en:1;				//12 Hw_rx_err_bps_en
		volatile u32 crc_inv:1;							//13 crc_inv
		volatile u32 start_bit_type:1;					//14 start_bit_type
		volatile u32 rsvd1:1;							//15 Reserved
		volatile u32 DWL:6;								//21:16	DWL
		volatile u32 rsvd2:10;							//31:22 Reserved
	}bit;
};

union ENDAT_CFG2_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 swap_tx_cmd_en:1;					//0 swap_tx_cmd_en
		volatile u32 swap_tx_mrs_en:1;					//1 swap_tx_mrs_en
		volatile u32 swap_tx_data_en:1;					//2 swap_tx_data_en
		volatile u32 rsvd0:5;							//7:3 Reserved
		volatile u32 swap_rx_mrs_en:1;					//8 swap_rx_mrs_en
		volatile u32 swap_rx_data_en:1;					//9 swap_rx_data_en
		volatile u32 swap_adif_ack_rx_en:1;				//10 swap_adif_ack_rx_en
		volatile u32 swap_adif_adr_rx_en:1;				//11 swap_adif_adr_rx_en
		volatile u32 swap_adif_data_rx_en:1;			//12 swap_adif_data_rx_en
		volatile u32 swap_abs_rx_en:1;					//13 swap_abs_rx_en
		volatile u32 rsvd1:18;							//31:14 Reserved
	}bit;
};

union ENDAT_CFG3_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 wdg:28;							//27:0 wdg
		volatile u32 wdg_en:1;							//28 wdg_en
		volatile u32 rsvd0:2;							//30:29 Reserved
		volatile u32 busy_bypass:1;						//31 busy_bypass
	};
};

union ENDAT_INTE_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 rxend_irq_en:1;					//0 rxend_irq_en
		volatile u32 wdg_irq_en:1;						//1 wdg_irq_en
		volatile u32 hw_tirg_exit_irq_en:1;				//2 hw_tirg_exit_irq_en
		volatile u32 rsvd0:29;							//31:3 Reserved
	}bit;
};

union ENDAT_STAT_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 rxend:1;							//0 rxend
		volatile u32 wdg:1;								//1 wdg
		volatile u32 hw_trig_exit:1;					//2 hw_trig_exit
		volatile u32 rsvd0:15;							//17:3 Reserved
		volatile u32 if_idl:1;							//18 if_idl
		volatile u32 rsvd1:13;							//31:19 Reserved
	}bit;
};

union ENDAT_DEC_CFG_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 stf_clr:1;							//0 stf_clr
		volatile u32 dec_abs_data_en:1;					//1 dec_abs_data_en
		volatile u32 dec_abm_data_en:1;					//2 dec_abm_data_en
		volatile u32 rsvd0:1;							//3 Reserved
		volatile u32 abs_dec_st_bit:6;					//9:4 abs_dec_st_bit
		volatile u32 rsvd1:2;							//11:10 Reserved
		volatile u32 abs_dec_bit_num:4;					//15:12 abs_dec_bit_num
		volatile u32 abm_dec_st_bit:6;					//21:16 abm_dec_st_bit
		volatile u32 rsvd2:2;							//11:10 Reserved
		volatile u32 abm_dec_bit_num:4;					//27:24 abm_dec_bit_num
		volatile u32 rsvd3:4;							//31:28 Reserved
	}bit;
};

union ENDAT_BCLK_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 bclk_prd:12;						//11:0 bclk_prd
		volatile u32 rsvd0:4;							//15:12 Reserved
		volatile u32 bclk_pre_en:1;						//16 bclk_pre_en
		volatile u32 rsvd1:15;							//31:17 Reserved
	};
};

union ENDAT_RXSMP_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 cp:12;								//11:0 cp
		volatile u32 rsvd0:4;							//15:12 Reserved
		volatile u32 tdly_en:1;							//16 tdly_en
		volatile u32 rx_smp_edg:1;						//16 rx_smp_edg
		volatile u32 rsvd1:14;							//31:18 Reserved
	}bit;
};

union ENDAT_RXDAT_STAT_REG {
	volatile u32 all;
	struct {											//bit description
		volatile u32 rsvd0:8;							//7:0 Reserved
		volatile u32 err1:1;							//8 err1
		volatile u32 err2:1;							//9 err2
		volatile u32 crc1:1;							//10 crc1
		volatile u32 crc2:1;							//11 crc2
		volatile u32 crc3:1;							//12 crc3
		volatile u32 crc4:1;							//13 crc4
		volatile u32 mrsadr:1;							//14 mrsadr
		volatile u32 busy:1;							//15 busy
		volatile u32 rm:1;								//16 rm
		volatile u32 wrn:1;								//17 wrn
		volatile u32 rsvd1:14;							//31:18 Reserved
	}bit;
};

union ENDAT_TX_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 data:16;							//15:0 data
		volatile u32 mrs:8;								//23:16 mrs
		volatile u32 mode:6;							//29:24 mode
		volatile u32 rsvd0:2;							//31:30 Reserved
	}bit;
};

union ENDAT_RECV1L_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 rxd1:32;							//31:0 rxd1
	}bit;
};

union ENDAT_RECV1U_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 rxd1:16;							//15:0 rxd1
		volatile u32 rxcrc:5;							//20:16 rxcrc
		volatile u32 rxerr1:1;							//21 rxerr1
		volatile u32 rxerr2:1;							//22 rxerr2
		volatile u32 rsvd0:9;							//31:23 Reserved
	}bit;
};

union ENDAT_RECV2_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 rxd2:24;							//23:0 rxd3
		volatile u32 rxcrc2:5;							//28:24 rxcrc2
		volatile u32 rsvd0:3;							//31:29 Reserved
	}bit;
};

union ENDAT_RECV3_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 rxd3:24;							//23:0 rxd3
		volatile u32 rxcrc3:5;							//28:24 rxcrc3
		volatile u32 rsvd0:3;							//31:29 Reserved
	}bit;
};

union ENDAT_ABS_POS_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 abs_pos:32;						//31:0 abs_pos
	}bit;
};

union ENDAT_ABM_POS_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 abm_pos:32;						//31:0 abm_pos
	}bit;
};

union ENDAT_RECV4_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 rxd4:16;							//15:0 rxd4
		volatile u32 mrs:8;								//23:16 mrs
		volatile u32 crc:5;								//28:24 mode
		volatile u32 rsvd0:3;							//31:29 Reserved
	}bit;
};

union ENDAT_RX_FLT_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 in_flt_sel:4;						//3:0 in_flt_sel
		volatile u32 in_pre_flt:4;						//7:4 in_pre_flt
		volatile u32 smp_ctl_prd:8;						//15:8 smp_ctl_prd
		volatile u32 rsvd0:16;							//31:16 Reserved
	}bit;
};

union ENDAT_TR_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 rsvd0:16;								//15:0 Reserved
		volatile u32 tm:16;									//31:16 tm
	}bit;
};

union ENDAT_TST_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 tst:16;							//15:0 tst
		volatile u32 rsvd0:16;							//31:16 Reserved
	}bit;
};

union ENDAT_TRT_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 trt:16;							//15:0 trt
		volatile u32 tst_pos:16;						//31:16 tst_pos
	}bit;
};

struct ENDATIF_REGS {
	union	ENDAT_STRB_REG			ENDAT_STRB;				//offset: 0x00
	union	ENDAT_CFG1_REG			ENDAT_CFG1;				//offset: 0x04
	union	ENDAT_CFG2_REG			ENDAT_CFG2;				//offset: 0x08
	union	ENDAT_CFG3_REG			ENDAT_CFG3;				//offset: 0x0c
	union	ENDAT_INTE_REG			ENDAT_INTE;				//offset: 0x10
	union	ENDAT_STAT_REG			ENDAT_STAT;				//offset: 0x14
	union	ENDAT_DEC_CFG_REG		ENDAT_DEC_CFG;			//offset: 0x18
	volatile u32 RES0;										//offset: 0x1c
	union	ENDAT_BCLK_REG			ENDAT_BCLK;				//offset: 0x20
	union	ENDAT_RXSMP_REG			ENDAT_RXSMP;			//offset: 0x24
	union	ENDAT_RXDAT_STAT_REG	ENDAT_RXDAT_STAT;		//offset: 0x28
	volatile u32 RES1;									//offset: 0x2c
	union	ENDAT_TX_REG		ENDAT_TX;				//offset: 0x30
	volatile u32 RES2[3];								//offset: 0x34~0x3C
	union	ENDAT_RECV1L_REG	ENDAT_RECV1L;			//offset: 0x40
	union	ENDAT_RECV1U_REG	ENDAT_RECV1U;			//offset: 0x44
	union	ENDAT_RECV2_REG		ENDAT_RECV2;			//offset: 0x48
	union	ENDAT_RECV3_REG		ENDAT_RECV3;			//offset: 0x4C
	union	ENDAT_ABS_POS_REG	ENDAT_ABS_POS;			//offset: 0x50
	union	ENDAT_ABM_POS_REG	ENDAT_ABM_POS;			//offset: 0x54
	union	ENDAT_RECV4_REG		ENDAT_RECV4;			//offset: 0x58
	volatile u32 RES3[1];								//offset: 0x5C
	union	ENDAT_RX_FLT_REG	ENDAT_RX_FLT;			//offset: 0x60
	union	ENDAT_TR_REG		ENDAT_TR;				//offset: 0x64
	union	ENDAT_TST_REG		ENDAT_TST;				//offset: 0x68
	union	ENDAT_TRT_REG		ENDAT_TRT;				//offset: 0x6c
};

void edtif0_irq_handler(void);
void edtif0_irq_register(cpu_irq_fun_t irqhandle);
void edtif0_irq_unregister(void);
void edtif1_irq_handler(void);
void edtif1_irq_register(cpu_irq_fun_t irqhandle);
void edtif1_irq_unregister(void);
void endat_cmu_init(void);
void endat_syscfg_sel(u8 n);
void edt_strb(u8 n);
void edt_rst(u8 n);
void edt_hw_trig_en(u8 n);
void edt_hw_trig_dis(u8 n);
void edt_tx_type(u8 n,EDT_TX_TYPE type);
void edt_rx_type(u8 n,EDT_RX_TYPE type);
void edt_rx_err_bit(u8 n,EDT_RX_ERR_WIDTH width);
void edt_tx_cfg(u8 n, u32 data, u32 mrs, u32 mode);
void edt_clk_cfg(u8 n, EDT_CLOCK_FRE clk);
void edt_tm_time(u8 n, u32 time);
void edt_tst_time(u8 n, u32 time);
void edt_rx_data_size(u8 n, u32 size);
void edt_abs_pos_set(u8 n, u32 startbit, u32 size);
void edt_abm_pos_set(u8 n, u32 startbit, u32 size);
void edt_ainf1_rx_en(u8 n,EDT_EN en);
void edt_ainf2_rx_en(u8 n,EDT_EN en);
u32 edt_get_rxend(u8 n);
u32 edt_get_recv1l(u8 n);
u32 edt_get_recv1u(u8 n);
u32 edt_get_crc1(u8 n);
void edt_stat_clr(u8 n);
void edt_wdg_timer(u8 n, u32 tick_num);
void edt_wdg_int_en(u8 n);
void edt_wdg_clr_int(u8 n);
u32 edt_get_wdg_sta(u8 n);
u32 edt_get_abs(u8 n);
u32 edt_get_abm(u8 n);

void edt_hw_trig_exit_int_en(u8 n);
void edt_hw_trig_exit_clr_int(u8 n);
u32 edt_get_hw_trig_exit_sta(u8 n);

void edt_stf_clr_rxd_en(u8 n);
void edt_stf_clr_rxd_dis(u8 n);
#endif /* INCLUDE_HAL_ENDATIF_H_ */
