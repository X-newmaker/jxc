/*
 * hal_xpwm.h
 *
 *  Created on: 2024年12月25日
 *      Author: ziqing.kong
 */

#ifndef INCLUDE_HAL_XPWM_H_
#define INCLUDE_HAL_XPWM_H_

/***************************************************************************
                        Register Description
***************************************************************************/

union XPWM_CONF_REG{
	volatile u32 all;
	struct{                     				//bit description
		volatile u32 XPWM_CNT_EN:1;   			//0 XPWM_CNT_EN
		volatile u32 XPWM_MOD:1;    			//1 XPWM_MOD
		volatile u32 XPWM_UPDATE_MODE:1;		//2 XPWM_UPDATE_MODE
		volatile u32 rsvd0:1;  					//3 Reserved
		volatile u32 XPWM_FIFO_EN:1;			//4 XPWM_FIFO_EN
		volatile u32 rsvd1:1;  					//5 Reserved
		volatile u32 XPWM_DMA_EN:1;				//6 XPWM_DMA_EN
		volatile u32 PUL_LIMIT_EN:1;			//7 PUL_LIMIT_EN
		volatile u32 XPWM_FIFO_TH:8;			//15:8	XPWM_FIFO_TH
		volatile u32 CLK_DIV:10;				//25:16	CLK_DIV
		volatile u32 rsvd2:6;					//31:26 Reserved
	}bit;
};

union XPWM_CH_CONF_REG{
	volatile u32 all;
	struct{                        				//bit description
		volatile u32 XPWM_IMD_UPDT:1;   		//0 XPWM_IMD_UPDT
		volatile u32 XPWM_INV_EN:1;    	 		//1 XPWM_INV_EN
		volatile u32 XPWM_IDLE:1;     			//2 XPWM_IDLE
		volatile u32 XPWM_PUL_STA_POL:1;     	//3 XPWM_PUL_STA_POL
		volatile u32 XPWM_PUL_STA_MODE:1;		//4 XPWM_PUL_STA_MODE
		volatile u32 rsvd0:27;					//31:5 Reserved
	}bit;
};

union XPWM_STS_FLAG_REG{
	volatile u32 all;
	struct{										//bit description
		volatile u32 CNT_ZRO_FLG:1;      		//0 CNT_ZRO_FLG
		volatile u32 CNT_PRD_FLG:1;				//1 CNT_PRD_FLG
		volatile u32 REG_UPDT_FLG:1;			//2 REG_UPDT_FLG
		volatile u32 FIFO_AVAL_FLG:1;			//3 FIFO_AVAL_FLG
		volatile u32 FIFO_UDFL_FLG:1;			//4 FIFO_UDFL_FLG
		volatile u32 FIFO_DVFL_FLG:1;			//5 FIFO_DVFL_FLG
		volatile u32 XPWM_FRC_PUL_FLG:1;		//6 XPWM_FRC_PUL_FLG
		volatile u32 XPWM_PUL_LIMIT_FLG:1;		//7 XPWM_PUL_LIMIT_FLG
		volatile u32 CNT_CMP_FLG:1;				//8 CNT_CMP_FLG
		volatile u32 rsvd0:13;        			//31:9 Reserved
	}bit;
};

union XPWM_INT_EN_REG{
	volatile u32 all;
	struct{										//bit description
		volatile u32 CNT_ZRO_INT_EN:1;      	//0 CNT_ZRO_INT_EN
		volatile u32 CNT_PRD_INT_EN:1;			//1 CNT_PRD_INT_EN
		volatile u32 REG_UPDT_INT_EN:1;			//2 REG_UPDT_INT_EN
		volatile u32 FIFO_AVAL_INT_EN:1;		//3 FIFO_AVAL_INT_EN
		volatile u32 FIFO_UDFL_INT_EN:1;		//4 FIFO_UDFL_INT_EN
		volatile u32 FIFO_DVFL_INT_EN:1;		//5 FIFO_DVFL_INT_EN
		volatile u32 XPWM_FRC_PUL_INT_EN:1;		//6 XPWM_FRC_PUL_INT_EN
		volatile u32 XPWM_PUL_LIMIT_INT_EN:1;	//7 XPWM_PUL_LIMIT_INT_EN
		volatile u32 CNT_CMP_INT_EN:1;			//8 CNT_CMP_FLG
		volatile u32 rsvd0:13;        			//31:9 Reserved
	}bit;
};

union XPWM_FIFO_FLUSH_REG{
	volatile u32 all;
	struct{
		volatile u32 XPWM_FIFO_FLUSH:1;     	//0 XPWM_FIFO_FLUSH
		volatile u32 rsvd0:15;        			//15:1 Reserved
		volatile u32 FIFO_DATA_LEN:8;			//23:16 FIFO_DATA_LEN
		volatile u32 rsvd1:8;					//31:24 Reserved
	}bit;
};

union XPWM_RESUME_REG{
	volatile u32 all;
	struct{
		volatile u32 PUL_RESUME:1;     			//0 PUL_RESUME
		volatile u32 rsvd0:3;        			//3:1 Reserved
		volatile u32 XPWM_PUL_STA_FLUSH:1;		//4 XPWM_PUL_STA_FLUSH
		volatile u32 rsvd1:27;					//31:5 Reserved
	}bit;
};

union XPWM_THR_RS_REG{
	volatile u32 all;
	struct{
		volatile u32 PUL_THR_RS:1;     			//0 PUL_THR_RS
		volatile u32 rsvd0:31;					//31:1 Reserved
	}bit;
};

union XPWM_FIFO_REG{
	volatile u32 all;
	struct{
		volatile u32 FIFO_REG:32;     			//31:0 FIFO_REG
	}bit;
};

union XPWM_PUL_STA_REG{
	volatile u32 all;
	struct{
		volatile u32 PUL_STA:32;     			//31:0 PUL_STA
	}bit;
};

union XPWM_CNT_STA_REG{
	volatile u32 all;
	struct{
		volatile u32 CNT_VAL:32;     			//31:0 CNT_VAL
	}bit;
};

union XPWM_PRD_REG{
	volatile u32 all;
	struct{
		volatile u32 PRD_VAL:32;     			//31:0 PRD_VAL
	}bit;
};

union XPWM_PUL_CNT_REG{
	volatile u32 all;
	struct{
		volatile u32 PUL_CNT:32;     			//31:0 PUL_CNT
	}bit;
};

union XPWM_PUL_THR_REG{
	volatile u32 all;
	struct{
		volatile u32 PUL_THR:32;     			//31:0 PUL_THR
	}bit;
};

union XPWM_CMP_REG{
	volatile u32 all;
	struct{
		volatile u32 CMP_VAL:32;     			//31:0 CMP_VAL
	}bit;
};

struct XPWM_REGS{
	union XPWM_CONF_REG      	XPWM_CONF;			//offset:0x00
	union XPWM_CH_CONF_REG  	XPWM_CH_CONF;		//offset:0x04
	union XPWM_STS_FLAG_REG  	XPWM_STS_FLAG;		//offset:0x08
	union XPWM_INT_EN_REG    	XPWM_INT_EN;		//offset:0x0C
	union XPWM_FIFO_FLUSH_REG   XPWM_FIFO_FLUSH;	//offset:0x10
	union XPWM_RESUME_REG       XPWM_RESUME;		//offset:0x14
	union XPWM_THR_RS_REG		XPWM_THR_RS;		//offset:0x18
	volatile u32 RES0;                				//offset:0x1C
	union XPWM_FIFO_REG     	XPWM_FIFO;    		//offset:0x20
	union XPWM_PUL_STA_REG      XPWM_PUL_STA;    	//offset:0x24
	union XPWM_CNT_STA_REG		XPWM_CNT_STA;		//offset:0x28
	volatile u32 RES1[9];                			//offset:0x2C-0x4C
	union XPWM_PRD_REG			XPWM_PRD;			//offset:0x50
	union XPWM_PUL_CNT_REG		XPWM_PUL_CNT;		//offset:0x54
	union XPWM_PUL_THR_REG		XPWM_PUL_THR;		//offset:0x58
	volatile u32 RES2;                				//offset:0x5C
	union XPWM_CMP_REG			XPWM_CMP;			//offset:0x60
};

void xpwm0_irq_handler(void);
void xpwm0_irq_register(cpu_irq_fun_t irqhandle);
void xpwm0_irq_unregister(void);
void xpwm1_irq_handler(void);
void xpwm1_irq_register(cpu_irq_fun_t irqhandle);
void xpwm1_irq_unregister(void);
void xpwm2_irq_handler(void);
void xpwm2_irq_register(cpu_irq_fun_t irqhandle);
void xpwm2_irq_unregister(void);
void xpwm3_irq_handler(void);
void xpwm3_irq_register(cpu_irq_fun_t irqhandle);
void xpwm3_irq_unregister(void);
void xpwm4_irq_handler(void);
void xpwm4_irq_register(cpu_irq_fun_t irqhandle);
void xpwm4_irq_unregister(void);
void xpwm5_irq_handler(void);
void xpwm5_irq_register(cpu_irq_fun_t irqhandle);
void xpwm5_irq_unregister(void);
void xpwm_cmu_init(u8 num);
void xpwm_clk_div_set(u8 i, u32 div);
void xpwm_fifo_th_set(u8 i, u32 th);
void xpwm_pul_limit_en(u8 i, u32 en);
void xpwm_dma_en(u8 i,u32 en);
void xpwm_fifo_en(u8 i ,u32 en);
void xpwm_update_mode_set(u8 i, u32 mode);
void xpwm_mod_set(u8 i,u32 mode);
void xpwm_cnt_en(u8 i ,u32 en);
void xpwm_idle_set(u8 i, u32 idle);
void xpwm_inv_en(u8 i, u32 en);
void xpwm_imd_updt_en(u8 i, u32 en);
u32 get_xpwm_sts_flag(u8 i);
void xpwm_sts_flag_clr(u8 i,u32 clr);
void xpwm_int_en(u8 i,u32 val);
void xpwm_fifo_flush(u8 i);
void xpwm_resume(u8 i);
void xpwm_pul_sta_flush(u8 i);
void xpwm_pul_restart(u8 i);
void xpwm_fifo_reg(u8 i, u32 data);
u32 get_xpwm_pul_sta(u8 i);
u32 get_xpwm_cnt(u8 i);
void xpwm_prd_set(u8 i,u32 prd);
void xpwm_pul_cnt_set(u8 i, u32 val);
void xpwm_pul_thr_set(u8 i ,u32 val);
void xpwm_cmp_set(u8 i,u32 cmp);



#endif /* INCLUDE_HAL_XPWM_H_ */


