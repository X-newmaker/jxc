/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_DCE_H_
#define INCLUDE_HAL_DCE_H_

typedef enum {
	DCE_CRC = 0x1,
	DCE_SUM = 0x2,
}DCE_MODE_TYP;

typedef enum {
	DCE_DATA_ADDR = 0x0,
	DCE_DATA_INPUT = 0x1,
}DCE_DATA_SEL;
/***************************************************************************
                        Register Description
***************************************************************************/

union DCE_CTL_REG{
	volatile u32 all;
	struct{									//bit description
		volatile u32 CAL_EN:1;				//0 Reserved
		volatile u32 rsvd1:31;				//31:1 Reserved
	}bit;
};

union DCE_CFG_REG{
	volatile u32 all;
	struct{									//bit description
		volatile u32 MODE_SEL:4;			//3:0 	MODE_SEL
		volatile u32 DAT_SRC_SEL:1;			//4 	DAT_SRC_SEL
		volatile u32 rsvd1:27;     			//31:5 	Reserved
	}bit;
};

union DCE_IRQ_EN_REG{
	volatile u32 all;
	struct{                          		//bit description
		volatile u32 CRC_DONE_IEN:1;      	//0 	CRC_DONE_IEN
		volatile u32 SUM_DONE_IEN:1;        //1		SUM_DONE_IEN
		volatile u32 rsvd0:22;				//23:2	Reserved
		volatile u32 ADDR_REQ_ERR_EN:1;		//24	ADDR_REQ_ERR_EN
		volatile u32 ADDR_ALIG_ERR_EN:1;	//25	ADDR_ALIG_ERR_EN
		volatile u32 DATA_LEN_ERR_EN:1;		//26	DATA_LEN_ERR_EN
		volatile u32 rsvd1:5;				//31:27	Reserved
	}bit;
};

union DCE_IRQ_STS_REG{
	volatile u32 all;
	struct{                          		//bit description
		volatile u32 CRC_DONE:1;      		//0 	CRC_DONE
		volatile u32 SUM_DONE:1;       	 	//1		SUM_DONE
		volatile u32 rsvd0:22;				//23:2	Reserved
		volatile u32 ADDR_REQ_ERR:1;		//24	ADDR_REQ_ERR
		volatile u32 ADDR_ALIG_ERR:1;		//25	ADDR_ALIG_ERR
		volatile u32 DATA_LEN_ERR:1;		//26	DATA_LEN_ERR
		volatile u32 rsvd1:5;				//31:27	Reserved
	}bit;
};

union DCE_DATA_LEN_REG{
	volatile u32 all;
	struct{
		volatile u32 DATA_LEN:29;     //28:0 DATA_LEN
		volatile u32 rsvd0:3;        //31:29 Reserved
	}bit;
};

union DCE_CRC_SIZE_REG{
	volatile u32 all;
	struct{
		volatile u32 POLY_SIZE:5;     //4:0 IN_PARA2
		volatile u32 rsvd0:27;        //31:5 Reserved
	}bit;
};

union DCE_CRC_CFG_REG{
	volatile u32 all;
	struct{
		volatile u32 OUT_BIT_IN_WORD_REV:1;     //0		OUT_BIT_IN_WORD_REV
		volatile u32 IN_BIT_IN_BYTE_REV:1;		//1		IN_BIT_IN_BYTE_REV
		volatile u32 IN_BIT_IN_WORD_REV:1;		//2		IN_BIT_IN_WORD_REV
		volatile u32 IN_BYTE_IN_WORD_REV:1;		//3		IN_BYTE_IN_WORD_REV
		volatile u32 rsvd0:28;					//31:4	Reserved
	}bit;
};

struct DCE_REGS{
	union DCE_CTL_REG      	DCE_CTL;     		//offset:0x00
	union DCE_CFG_REG     	DCE_CFG;     		//offset:0x04
	union DCE_IRQ_EN_REG   	DCE_IRQ_EN;  		//offset:0x08
	union DCE_IRQ_STS_REG  	DCE_IRQ_STS;     	//offset:0x0C
	volatile u32      		   	DCE_DATA_ADDR;     	//offset:0x10
	union DCE_DATA_LEN_REG  DCE_DATA_LEN;     	//offset:0x14
	volatile u32 			DCE_CRC_POLY;       //offset:0x18
	union DCE_CRC_SIZE_REG  DCE_CRC_SIZE;    	//offset:0x1C
	volatile u32 RES0[8];							//offset:0x20~0x3C
	volatile u32     			DCE_DATA_INPUT;    	//offset:0x40
	volatile u32 RES1[15];							//offset:0x44~0x7C
	union DCE_CRC_CFG_REG	DCE_CRC_CFG;		//offset:0x80
	volatile u32				DCE_CRC_INIT;		//offset:0x84
	volatile u32				DCE_CRC_XOROUT;		//offset:0x88
	volatile u32 RES2[13];							//offset:0x8C~0xBC
	volatile u32				DCE_CRC_RESULT;		//offset:0xC0
	volatile u32 RES3[31];							//offset:0xC4~0x13C
	volatile u32				DCE_SUM_RESULT;		//offset:0x140
};

void dce_cmu_init(void);
void dce_en(void);
void dce_sel(DCE_MODE_TYP mode, DCE_DATA_SEL sel);
void dce_irq_enable(u32 en);
u32 get_dce_irq_sts(void);
void dce_addr_set(u32 addr);
void dce_data_len_set(u32 len);
void dce_crc_cfg(u32 poly,u32 poly_size,u32 crc_init,u32 crc_xor);
void dce_data_set(u32 data);
void dce_rev_cfg(u32 rev);
u32 dce_get_result(void);
#endif /* INCLUDE_HAL_CORDIC_H_ */
