/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_GTC_H_
#define INCLUDE_HAL_GTC_H_

#include <all_inc.h>

typedef enum gtc_unit_e{
	GTC_US_D4			=    0,
	GTC_US				=    1,
	GTC_US_100			=    2,
	GTC_MS				=    3,
	GTC_S		 		=    4,
	GTC_M				=    5,
}gtc_unit_t;

s32 init_gtc(void);
s32 init_gtc_div(void);
s32 gtc_set_freq(u32 sel);
s32 gtc_set_time(gtc_unit_t u,u64 t);
u64 gtc_get_time(gtc_unit_t u);
s32 gtc_dly_time(gtc_unit_t u,u32 t);

union gtc_cntcr_reg_t {
	u32 dwval;
	struct {
		u32 en			:   1;
		u32 res0		:   7;
		u32 fcreq		:   2;
		u32 res1		:  22;
	} bits;
};

union gtc_cntsr_reg_t {
	u32 dwval;
	struct {                                //bit description
		u32 res0 : 1;                   //0     Reserved
		u32 hdbg : 1;                   //1     GTC_HDBG
		u32 res1 : 6;                   //7:2   Reserved
		u32 fcck : 2;                   //9:8   GTC_FCACK
		u32 res2 : 22;                  //31:10 Reserved
	} bits;
};

union gtc_cntvl_reg_t {
	u32 dwval;
	struct {                                //bit description
		u32 cntvl : 32;                 //31:0  GTC_CNTVL
	} bits;
};

union gtc_cntvh_reg_t {
	u32 dwval;
	struct {                                //bit description
		u32 cntvh : 20;                 //19:0  GTC_CNTVH
		u32 res0 : 12;                  //31:20 Reserved
	} bits;
};

union gtc_cntfid_reg_t {
	u32 dwval;
	struct {                                //bit description
		u32 cntfid : 32;                //31:0  GTC_CNTFID0
	} bits;
};

union gtc_confg_reg_t {
	u32 dwval;
	struct {                                //bit description
		u32 srst : 1;                   //0     GTC_SRST
		u32 res0 : 7;                   //7:1   Reserved
		u32 fdiv : 5;                   //12:8  GTC_FDIV
		u32 res1 : 19;                  //31:13 Reserved
	} bits;
};

union gtc_cntid_reg_t {
	u32 dwval;
	struct {                                //bit description
		u32 cntid : 32;                 //31:0  GTC_CNTID
	} bits;
};

union gtc_res_t {
	u32 dwval;
	struct {                                //bit description
		u32 res0;                       //31:0 Reserved
	} bits;
};

typedef struct gtc_dev_s {
	volatile union gtc_cntcr_reg_t  gtc_cntcr_reg;
	volatile union gtc_cntsr_reg_t  gtc_cntsr_reg;
	volatile union gtc_cntvl_reg_t	gtc_cntvl_reg;
	volatile union gtc_cntvh_reg_t	gtc_cntvh_reg;			union gtc_res_t gtc_res010[4];
	volatile union gtc_cntfid_reg_t	gtc_cntfid_reg[4];		union gtc_res_t gtc_res030[36];
	volatile union gtc_confg_reg_t	gtc_confg_reg;			union gtc_res_t gtc_res0c4[963];
	volatile union gtc_cntfid_reg_t	gtc_cntid_reg[12];
	volatile union gtc_cntvl_reg_t	gtc_ro_cntvl_reg;
	volatile union gtc_cntvh_reg_t	gtc_ro_cntvh_reg;
}gtc_dev_t;


#endif /* INCLUDE_HAL_GTC_H_ */
