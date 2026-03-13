
#ifndef __PLIC_H__
#define __PLIC_H__

#include "common_type.h"

#define CLIC_INFO_CLICINTCTLBITS_Pos           21U
#define CLIC_INFO_CLICINTCTLBITS_Msk           (0xFUL << CLIC_INFO_CLICINTCTLBITS_Pos)

#define CLIC_INTIP_IP_Pos                      0U                                    /*!< CLIC INTIP: IP Position */
#define CLIC_INTIP_IP_Msk                      (0x1UL << CLIC_INTIP_IP_Pos)          /*!< CLIC INTIP: IP Mask */

#define CLIC_INTIE_IE_Pos                      0U                                    /*!< CLIC INTIE: IE Position */
#define CLIC_INTIE_IE_Msk                      (0x1UL << CLIC_INTIE_IE_Pos)          /*!< CLIC INTIE: IE Mask */

#define CLIC_INTIE_T_Pos                       7U                                    /*!< CLIC INTIE: T Position */
#define CLIC_INTIE_T_Msk                       (0x1UL << CLIC_INTIE_T_Pos)           /*!< CLIC INTIE: T Mask */

#define CLIC_INTATTR_TRIG_Pos                  1U                                    /*!< CLIC INTATTR: TRIG Position */
#define CLIC_INTATTR_TRIG_Msk                  (0x3UL << CLIC_INTATTR_TRIG_Pos)      /*!< CLIC INTATTR: TRIG Mask */

#define CLIC_INTATTR_SHV_Pos                   0U                                    /*!< CLIC INTATTR: SHV Position */
#define CLIC_INTATTR_SHV_Msk                   (0x1UL << CLIC_INTATTR_SHV_Pos)       /*!< CLIC INTATTR: SHV Mask */

#define CLIC_INTCFG_NVBIT_Pos                  5U                                    /*!< CLIC INTCFG: NVBIT Position */
#define CLIC_INTCFG_NVBIT_Msk                  (0x1UL << CLIC_INTCFG_NVBIT_Pos)      /*!< CLIC INTCFG: NVBIT Mask */

#define CLIC_INTCFG_PRIO_Pos                   3U                                    /*!< CLIC INTCFG: INTCFG Position */
#define CLIC_INTCFG_PRIO_Msk                   (0x1FUL << CLIC_INTCFG_PRIO_Pos)       /*!< CLIC INTCFG: INTCFG Mask */

#define CLIC_CLICCFG_NVBIT_Pos                 0U                                    /*!< CLIC CLICCFG: NVBIT Position */
#define CLIC_CLICCFG_NVBIT_Msk                 (0x1UL << CLIC_CLICCFG_NVBIT_Pos)     /*!< CLIC CLICCFG: NVBIT Mask */

#define CLIC_CLICCFG_NLBIT_Pos                 1U                                    /*!< CLIC CLICCFG: NLBIT Position */
#define CLIC_CLICCFG_NLBIT_Msk                 (0xFUL << CLIC_CLICCFG_NLBIT_Pos)     /*!< CLIC CLICCFG: NLBIT Mask */

#define CLIC_CLICCFG_NMBIT_Pos                 5U                                    /*!< CLIC CLICCFG: NMBIT Position */
#define CLIC_CLICCFG_NMBIT_Msk                 (0x3UL << CLIC_CLICCFG_NMBIT_Pos)     /*!< CLIC CLICCFG: NMBIT Mask */

s32 init_clic(void);

union clic_cfg_t {
	u32 dwval;
	struct {
		u32 nvbits			:   1;
		u32 nlbits			:   4;
		u32 nmbits 			:   2;
		u32 res0 			:  25;
	} bits;
};

union clic_info_t {
	u32 dwval;
	struct {
		u32 num_interrupt		:  13;
		u32 version			:   8;
		u32 clic_ctlbits 		:   4;
		u32 res0 			:   7;
	} bits;
};

union mint_thresh_t {
	u32 dwval;
	struct {
		u32 res0			:  24;
		u32 mth 			:   8;
	} bits;
};

union clic_res_t {
	u32 dwval;
	struct {
		u32 res0;
	} bits;
};

union clic_intip_t {
	u8 dbval;
	struct {
		u8 ip				:   1;
		u8 res0				:   7;
	} bits;
};

union clic_intie_t {
	u8 dbval;
	struct {
		u8 ie				:   1;
		u8 res0				:   7;
	} bits;
};

union clic_intattr_t {
	u8 dbval;
	struct {
		u8 shv				:   1;
		u8 trig				:   2;
		u8 res0				:   3;
		u8 mode 			:   2;
	} bits;
};

union clic_intctl_t {
	u8 dbval;
	struct {
		u8 int_const			:   3;
		u8 int_ctl			:   5;
	} bits;
};

typedef struct clic_int_s {
	volatile union clic_intip_t 		clic_intip;
	volatile union clic_intie_t 		clic_intie;
	volatile union clic_intattr_t 		clic_intattr;
	volatile union clic_intctl_t 		clic_intctl;
}clic_int_t;

typedef struct clic_dev_s {
	volatile union clic_cfg_t   		clic_cfg;
	volatile union clic_info_t 		clic_info;
	volatile union mint_thresh_t 		mint_thresh;			union clic_res_t clic_res000c[1021];
	volatile       clic_int_t		clic_int[256];
}clic_dev_t;

#endif
