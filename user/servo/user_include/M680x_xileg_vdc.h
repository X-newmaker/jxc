/*
 * M680x_xileg_vdc.h
 *
 *  Created on: 2023年8月8日
 *      Author: wenxing.ma
 */

#ifndef M680X_XILEG_VDC_H_
#define M680X_XILEG_VDC_H_
#include "stdint.h"
typedef struct {int32_t  Imeas_a_gain;    /* Parameter: gain for Ia (Q13) */
				int32_t  Imeas_a_offset;  /* Parameter: offset for Ia (Q15) */
				int32_t  Imeas_a;         /* Output: measured Ia (Q15) */
				int32_t  Imeas_b_gain;    /* Parameter: gain for Ib (Q13) */
				int32_t  Imeas_b_offset;  /* Parameter: offset for Ib (Q15) */
				int32_t  Imeas_b;         /* Output: measured Ib (Q15) */
				int32_t  Vdc_meas_gain;   /* Parameter: gain for Vdc (Q13) */
				int32_t  Vdc_meas_offset; /* Parameter: offset for Vdc (Q15) */
				int32_t  Vdc_meas;        /* Output: measured Vdc (Q15) */
                               int32_t  Imeas_c;		  /* Output: computed Ic (Q15) */
				int32_t  Ch_sel;          /* Parameter: ADC channel selection */
				int32_t  _long_sum_ad0;
				int32_t  _long_sum_ad1;
				int32_t  _long_avg_ad0;
				int32_t  _long_avg_ad1;
				int32_t  _int_sum_ad4;
				int32_t  _int_sum_ad5;
				int32_t  _int_avg_ad4;
				int32_t  _int_avg_ad5;
				int32_t  _int_ad_sample;
                                int32_t  _int_spd_cnt;
				int32_t  ad_sample_en;
				int32_t  Imeas_ref_ad0;
				int32_t  Imeas_ref_ad1;
				int32_t  Imeas_ref_ad2;
				int32_t  Imeas_ref_ad3;
				int32_t  Vref_spd_cmd;
				int32_t  Vref_cmd_ch_sel;    /* Parameter: gain for Ia (Q13) */
				int32_t  Vref_high_offset;  /* Parameter: offset for Ia (Q15) */
				int32_t  Vref_high;         /* Output: measured Ia (Q15) */
				int32_t  Vref_high_k;
				int32_t  Vref_cmd_gain;    /* Parameter: gain for Ib (Q13) */
				int32_t  Vref_low_offset;  /* Parameter: offset for Ib (Q15) */
				int32_t  Vref_low;         /* Output: measured Ib (Q15) */
				int32_t  Vref_low_k;
				int32_t  _int_sum_ad2;
				int32_t  _int_sum_ad3;
				int32_t  _int_avg_ad2;
				int32_t  _int_avg_ad3;
				int32_t  _int_sum_ad8;
				int32_t  _int_avg_ad8;
				int32_t  Vref_base2;
				int32_t  Vref_base3;
				int32_t  Vref_spd_cmd_high;
				int32_t  Vref_spd_cmd_low;
				int32_t  Vref_spd_offset_high;
				int32_t  Vref_spd_offset_low;
				int32_t  Vref_spd_pos_gain;
				int32_t  Vref_spd_neg_gain;
				int32_t  _int_cnc_vol_ref;
                                int32_t  _int_cnc_vol_ref_sum;
				  float  _float_speed_ref;
				int32_t  usd_disp_dop_dig;
			        int32_t  spd_disp_time_delay;
				int32_t  _int_cnc_vol_disp;
				  float  _float_speed_ref1;
				int32_t  Vref_auto_offset_cnt;
				int32_t  Vref_auto_offset_sum;
				int32_t  Vref_auto_finish_flag;
				int32_t  Vref_high_sum;
				int32_t  Vref_high_vol;
				int32_t  Vref_low_sum;
				int32_t  Vref_low_vol;
				int32_t  Vref_Tr_cmd;
				int32_t  vol_zero_speed_ref;
				int32_t  vol_zero_Tr_ref;
				int32_t  Vref_Tr_pos_gain;
				int32_t  Vref_Tr_neg_gain;
				int32_t  Vref_Tr_gain;
				int32_t  VrefCalcFinishFlag;
				int32_t  ControlMode;
				  float  SpdInputVol;
				  float  TrInputVol;
				int32_t  _iqSpdInputVol;
				int32_t  _iqTrInputVol;
				int32_t  _iqSpdDispVol;
				int32_t  _iqTrDispVol;
				int32_t  VrefSave;
				int32_t  TrefSave;
                   void (*adc_init)();
                   void (*adc_read)();
                   void (*adc_filter)();
                   void (*adc_calc)();
                } ILEG2DCBUSMEAS;
#define M680X_ILEG2_DCBUS_MEAS_DEFAULTS { 0x1FFF,0x0000,0x0000,                \
                                          0x1FFF,0x0000,0x0000,                \
                                          0x1FFF,0x0000,0x0000,                \
                                          0x0000,0x4210, 0, 0, 0, 0, 0,0,0,0,  \
                                          0,0, 1, 0, 0, 0,0,0,                 \
                                          1,0x0000,0x0000, _IQ(0.625),         \
                                         _IQ(1),0x0000,0x0000, _IQ(0.01923077),\
                                          0, 0, 0, 0, 0, 0,                    \
                                          0, 0, 0, 0, _IQ(1), _IQ(1),0,1,0,0,  \
										  0,0,0,0,0,0, 0,0,0,0,                \
										  0,0,0,0,0,_IQ(1),_IQ(1),_IQ(1),0,0,  \
										  0,0,0,0,0,0,0,0,                     \
                                          (void (*)(long))M680X_ileg2_dcbus_drv_init,   \
                                          (void (*)(long))M680X_ileg2_dcbus_drv_read,   \
                                          (void (*)(long))M680X_ileg2_dcbus_drv_filter, \
                                          (void (*)(long))M680X_ileg2_dcbus_drv_calc,   \
                                         }
#define ILEG2DCBUSMEAS_DEFAULTS M680X_ILEG2_DCBUS_MEAS_DEFAULTS
void M680X_ileg2_dcbus_drv_init(ILEG2DCBUSMEAS *);
void M680X_ileg2_dcbus_drv_read(ILEG2DCBUSMEAS *);
void M680X_ileg2_dcbus_drv_filter(ILEG2DCBUSMEAS *);
void M680X_ileg2_dcbus_drv_calc(ILEG2DCBUSMEAS *);

extern void sdfm_fault_int_enable(uint32_t num);
extern void sdfm_fault_int_clear(uint32_t num);
extern uint32_t sdfm_comp_high_flag_read(uint32_t num);
extern uint32_t sdfm_comp_low_flag_read(uint32_t num);
extern void sdfm_comp_high_flag_clr(uint32_t num);
void sdfm_comp_low_flag_clr(uint32_t num);
extern uint32_t sdfm_num_u;
extern uint32_t sdfm_num_v;
extern ILEG2DCBUSMEAS ilg2_vdc1;
#endif /* M680X_XILEG_VDC_H_ */
