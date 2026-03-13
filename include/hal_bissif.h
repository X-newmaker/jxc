/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 */
/*
 * hal_bissif.h
 */

#ifndef INCLUDE_HAL_BISSIF_H_
#define INCLUDE_HAL_BISSIF_H_

typedef enum {
	BISSC = 0x0,
	SSI   = 0x1,
}BISS_TYPE;

typedef enum {
	BISS_10MHz  = 0x0,
	BISS_8MHz  = 0x1,
	BISS_4MHz  = 0x2,
	BISS_2p5MHz  = 0x3,
	BISS_1MHz  = 0x4,
	BISS_400KHz = 0x5,
	BISS_300KHz = 0x6,
	BISS_200KHz = 0x7,
	BISS_100KHz = 0x8,
	BISS_80KHz = 0x9,
}BISS_BR_TYPE;

typedef enum {
	BISS_RXD0 = 0x0,
	BISS_RXD1   = 0x1,
}BISS_DEC_DATA;

/***************************************************************************
                        Register Description
***************************************************************************/
union BISS_STF_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 STF:1;                             //0  Command Execute
                volatile u32 rsvd0:7;							//7:1 Reserved
                volatile u32 fsm_rst:1;							//8 fsm_rst
                volatile u32 rsvd1:22;                          //30:9  Reserved
                volatile u32 cdm:1;							//31 cdm_set
        }bit;
};

union BISS_CPOLY_REG {
        volatile u32  all;
        struct {                                                //bit description
                volatile u32 cpoly:16;                          //15:0 cpoly
                volatile u32 crcinit:16;						//31:16 crc initial value
        }bit;
};

union BISS_SIZE_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 d0size:6;                          //5：0  d0size
                volatile u32 rsvd0:2;				//7：6  Reserved
                volatile u32 d1size:6;                          //13：8  d1size
                volatile u32 rsvd1:2;				//15：14  Reserved
                volatile u32 d2size:6;             //21：16  d2size
                volatile u32 rsvd2:2;				//23：22  Reserved
                volatile u32 crcsize:5;				//28:24 crc data size
                volatile u32 tx_crc_inv_en:1;		//29 tx_crc_inv_en
                volatile u32 rx_crc_inv_en:1;		//30 rx_crc_inv_en
                volatile u32 rsvd3:1;				//31 Reserved
        }bit;
};

union BISS_WDOG_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 wdg:32;                            //31:0 wdg
        }bit;
};

union BISS_MODE_REG {
        volatile u32  all;
        struct {                                    //bit description
                volatile u32 biss_ssi_sel:1;        //0  biss_ssi_sel
                volatile u32 stf_clr_en:1;			//1	 stf_clr_rxd_en
                volatile u32 hw_trg_en:1;			//2  hw_trg_en
                volatile u32 rsvd0:1;				//3  Reserved
                volatile u32 dec_abs_data_en:1;		//4  dec_abs_data_en
                volatile u32 dec_abs_data_sel:1;	//5  dec_abs_data_sel
                volatile u32 dec_abm_data_en:1;		//6  dec_abs_data_en
                volatile u32 dec_abm_data_sel:1;	//7  dec_abs_data_sel
                volatile u32 rsvd1:8;				//15:8  Reserved
                volatile u32 hw_rx_err_bps_en:1;	//16 Hw_rx_err_bps_en
                volatile u32 ssi_grey_en:1;			//17 ssi_grey_en
                volatile u32 rsvd2:14;				//31:17 Reserved
        }bit;
};

union BISS_BR_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 br:4;                              //3:0 BR
                volatile u32 rsvd0:28;				//31:4 Reserved
        }bit;
};

union BISS_STATUS_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 rsvd3:1;                             //0  Reserved
                volatile u32 wodog:1;				//1 wdg
                volatile u32 rsvd0:1;				//2 Reserved
                volatile u32 crc_error:1;			//3 regwerr
                volatile u32 rsvd1:1;				//4 Reserved
                volatile u32 alm:1;					//5 alm
                volatile u32 wrn:1;					//6 wrn
                volatile u32 rsvd2:25;				//31:7 Reserved
        }bit;
};

union BISS_RXD0_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 rxd0:32;                           //31:0 rxd0
        }bit;
};
union BISS_RXD1_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 rxd1:32;                           //31:0 rxd1
        }bit;
};
union BISS_RXD2_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 reg:32;                           //31:0 reg
        }bit;
};

union BISS_RXD_OTH_REG {
		volatile u32  all;
	    struct {                                                 //bit description
				volatile u32 CDS:1;                           	//0 cds
				volatile u32 ALM:1;								//1 alm
				volatile u32 WRN:1;								//2 wrn
				volatile u32 rsvd0:13;							//15:3 Reserved
				volatile u32 CRC:16;							//31:16 crc
	    }bit;
};


union BISS_IRQ_EN_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 end_irq_en:1;                      //0  end_irq_en
                volatile u32 wodog_irq_en:1;					//1 wodog_irq_en
                volatile u32 hw_trig_exit_irq_en:1;				//2 hw_trig_exit_irq_en
                volatile u32 rsvd0:29;							//31:3 Reserved
        }bit;
};

union BISS_IRQ_STS_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 end_irq:1;                         //0  end_irq
                volatile u32 wodog_irq:1;						//1	wodog_irq
                volatile u32 hw_trig_exit:1;					//2 hw_trig_exit
                volatile u32 rsvd0:29;							//31:3 Reserved
        }bit;
};

union BISS_NF_REG {
	volatile u32 all;
	struct {							//bit description
		volatile u32 in_flt_sel:4;			//3:0 in_flt_sel
		volatile u32 in_pre_flt:4;			//7:4 in_pre_flt
		volatile u32 smp_ctl_prd:8;			//15:8 smp_ctl_prd
		volatile u32 rsvd0:16;				//31:16 Reserved
	};
};


union BISS_TR_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 tr:16;                             //15:0 tr
                volatile u32 rsvd0:16;				//31:16 Reserved
        }bit;
};

union BISS_TCAL_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 tcal:16;                           //15:0 tcal
                volatile u32 rsvd0:16;				//31:16 Reserved
        }bit;
};
union BISS_TDLY_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 tdly:12;                           //11:0 tdly
                volatile u32 tdly_en:1;				//12 tdly_en
                volatile u32 cdm_post_en:1;			//13 cdm_post_en
                volatile u32 rsvd0:2;				//15:14 Reserved
                volatile u32 bclk_prd:12;			//27:16 bclk_prd
                volatile u32 bclk_prd_en:1;			//28 bclk_en
                volatile u32 rsvd1:3;				//31:29 Reserved
        }bit;
};
union BISS_TCDM_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 tcdm:16;                           //15:0 tcdm
                volatile u32 rsvd0:16;							//31:16 Reserved
        }bit;
};

union BISS_DEC_ABS_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 dec_abs_data:32;                           //31:0 dec_abs_data
        }bit;
};

union BISS_DEC_ABM_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 dec_abm_data:32;                    //31:0 dec_abm_data
        }bit;
};

struct BISSIF_REGS {
        union   BISS_STF_REG       BISS_STF;            //offset: 0x00
        union   BISS_CPOLY_REG     BISS_CPOLY;          //offset: 0x04
        union   BISS_SIZE_REG      BISS_SIZE;           //offset: 0x08
        volatile u32  RES0;	       					    //offset: 0x0C
        union   BISS_WDOG_REG      BISS_WDOG;           //offset: 0x10
        union   BISS_MODE_REG      BISS_MODE;           //offset: 0x14
        union   BISS_BR_REG        BISS_BR;             //offset: 0x18
        union   BISS_STATUS_REG    BISS_STATUS;         //offset: 0x1C
        union	BISS_RXD0_REG	   BISS_RXD0;           //offset: 0x20
        union	BISS_RXD1_REG	   BISS_RXD1;           //offset: 0x24
        union	BISS_RXD2_REG	   BISS_RXD2;           //offset: 0x28
        union   BISS_RXD_OTH_REG   BISS_RXD_OTH;	    //offset: 0x2C
        union	BISS_IRQ_EN_REG	   BISS_IRQ_EN;         //offset: 0x30
        union	BISS_IRQ_STS_REG   BISS_IRQ_STS;        //offset: 0x34
        volatile u32  RES3[2];                          //offset: 0x38/3C
        union	BISS_NF_REG		   BISS_NF;     		//offset: 0x40
        volatile u32 RES4[7];                           //offset: 0x44~0x5C
        union	BISS_TR_REG		   BISS_TR;     		//offset: 0x60
        union	BISS_TDLY_REG	   BISS_TDLY;           //offset: 0x64
        union	BISS_TCAL_REG	   BISS_TCAL;           //offset: 0x68
        union	BISS_TCDM_REG	   BISS_TCDM;           //offset: 0x6C
        union   BISS_DEC_ABS_REG   BISS_DEC_ABS;		//offset: 0x70
        union   BISS_DEC_ABM_REG   BISS_DEC_ABM;		//offset: 0x74
};

void bissif0_irq_handler(void);
void bissif0_irq_register(cpu_irq_fun_t irqhandle);
void bissif0_irq_unregister(void);
void bissif1_irq_handler(void);
void bissif1_irq_register(cpu_irq_fun_t irqhandle);
void bissif1_irq_unregister(void);
void biss_cmu_init(void);
void biss_syscfg_sel(u8 n);

void biss_stf(u8 n);
void biss_reset(u8 n);
void biss_cdm_set(u8 n,u32 cdm);

void biss_cpoly(u8 n, u32 poly);
void biss_crcinit(u8 n, u32 init);

void biss_d0_size(u8 n,u32 size);
void biss_d1_size(u8 n,u32 size);
void biss_d2_size(u8 n,u32 size);
void biss_crc_size(u8 n,u32 size);

void biss_mode(u8 n, BISS_TYPE type);
void biss_hw_tirg_en(u8 n);
void biss_hw_tirg_dis(u8 n);
void biss_abs_en(u8 n);
void biss_abm_en(u8 n);
void biss_abs_sel(u8 n,BISS_DEC_DATA data);
void biss_abm_sel(u8 n,BISS_DEC_DATA data);

void biss_br(u8 n, BISS_BR_TYPE baud);

void biss_wgd_timer(u32 num, u32 tick_num);
void biss_wgd_int_en(u32 num);
void biss_wgd_clr_int(u32 num);
void biss_end_int_en(u32 num);
void biss_end_clr_int(u32 num);
void biss_hw_exit_int_en(u32 num);
void biss_hw_exit_clr_int(u32 num);

void biss_tr_timing(u8 n,u32 time);
void biss_tcal_timing(u8 n,u32 time);
void biss_tcdm_timing(u8 n,u32 time);
void ssi_grey_en(u8 n, u8 enable);

void biss_set_bclk(u8 n,u32 bclk_prd);
void biss_set_tdly(u8 n,u32 tdly);

u32 biss_get_status(u8 n);
u32 biss_get_rx_data0(u8 n);
u32 biss_get_rx_data1(u8 n);
u32 biss_get_rx_data2(u8 n);
u32 biss_get_rx_crc(u8 n);
u32 biss_get_irq_status(u8 n);
u32 biss_get_abs(u8 n);
u32 biss_get_abm(u8 n);
#endif /* INCLUDE_HAL_BISSIF_H_ */
