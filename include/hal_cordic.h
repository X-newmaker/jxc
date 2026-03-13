/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_CORDIC_H_
#define INCLUDE_HAL_CORDIC_H_

typedef enum{
	Cos = 0,
	Sin,
	Phase,
	Modulus,
	Arctan,
	Cosh,
	Sinh,
	Atanh,
	Square,
	Arctan2,
}COR_FUNC_TYP;

typedef enum{
	iter2 = 1,
	iter4,
	iter6,
	iter8,
	iter10,
	iter12,
	iter14,
	iter16,
	iter18,
	iter20,
	iter22,
	iter24,
}COR_ITER_TYP;

/***************************************************************************
                        Register Description
***************************************************************************/

union COR_CTL_REG{
	volatile u32 all;
	struct{                     //bit description
		volatile u32 rsvd0:1;   //0 Reserved
		volatile u32 COR_FSM_CLR:1;    //1 COR_FSM_CLR
		volatile u32 rsvd1:30;  //31:2 Reserved
	}bit;
};

union COR_STS_REG{
	volatile u32 all;
	struct{                        //bit description
		volatile u32 RDY_FLG:1;   //0 RDY_FLG
		volatile u32 rsvd0:3;     //3:1 Reserved
		volatile u32 COR_FSM:4;     //7:4 COR_FSM
		volatile u32 rsvd1:24;     //31:8 Reserved
	}bit;
};

union COR_INT_EN_REG{
	volatile u32 all;
	struct{                          //bit description
		volatile u32 RDY_IEN:1;      //0 RDY_IEN
		volatile u32 rsvd0:31;        //31:1 Reserved
	}bit;
};

union COR_CFG_REG{
	volatile u32 all;
	struct{
		volatile u32 FUNC_SEL:4;     //3:0 FUNC_SEL
		volatile u32 rsvd0:4;        //7:4 Reserved
		volatile u32 NM_ITER:4;      //11:8 NM_ITER
		volatile u32 rsvd1:4;        //15:12 Reserved
		volatile u32 RD_AUTO_CLR:1;  //16 RD_AUTO_CLR
		volatile u32 rsvd2:2;       //18:17 Reserved
		volatile u32 COR_OUT_FMT:1;	//19 COR_OUT_FMT
		volatile u32 rsvd3:12;			//31:20 Reserved
	}bit;
};

union COR_IN1_REG{
	volatile u32 all;
	struct{
		volatile u32 IN_PARA1:16;     //15:0 IN_PARA1
		volatile u32 rsvd0:16;        //31:16 Reserved
	}bit;
};

union COR_IN2_REG{
	volatile u32 all;
	struct{
		volatile u32 IN_PARA2:16;     //15:0 IN_PARA2
		volatile u32 rsvd0:16;        //31:16 Reserved
	}bit;
};

union COR_OUT1_REG{
	volatile u32 all;
	struct{
		volatile u32 OUT_RES1:32;     //31:0 OUT_RES1
	}bit;
};

union COR_OUT2_REG{
	volatile u32 all;
	struct{
		volatile u32 OUT_RES2:32;     //31:0 OUT_RES2
	}bit;
};

struct COR_REGS{
	union COR_CTL_REG      COR_CTL;     //offset:0x00
	union COR_STS_REG      COR_STS;     //offset:0x04
	union COR_INT_EN_REG   COR_INT_EN;  //offset:0x08
	union COR_CFG_REG      COR_CFG;     //offset:0x0C
	union COR_IN1_REG      COR_IN1;     //offset:0x10
	union COR_IN2_REG      COR_IN2;     //offset:0x14
	volatile u32 RES0[6];                //offset:0x18/1C/20/24/28/2C
	union COR_OUT1_REG     COR_OUT1;    //offset:0x30
	union COR_OUT2_REG     COR_OUT2;    //offset:0x34
};
void cordic_cmu_init(void);
void cordic_cal(COR_FUNC_TYP funsel, COR_ITER_TYP iteration, s16 data1, s16 data2, s32 *result1, s32 *result2);
void cord_set(COR_FUNC_TYP funsel, COR_ITER_TYP iteration);
void cord_cal(s16 data1, s16 data2, s32 *result1, s32 *result2);
void cord_set_dat1(s16 data1);
void cord_set_dat2(s16 data2);
void cord_get_res1(s32 *result1);
void cord_get_res2(s32 *result2);
void cord_out_fmt(u32 fmt);
#endif /* INCLUDE_HAL_CORDIC_H_ */
