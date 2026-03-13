/*
 * encoder.h
 *
 *  Created on: 2023年8月11日
 *      Author: wenxing.ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_ENCODER_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_ENCODER_H_

#include "stdint.h"

typedef struct {int64_t theta_elec;     /* Output: Motor Electrical angle (Q15)  */
                int32_t theta_mech;     /* Output: Motor Mechanical Angle (Q15)  */
	            int32_t absa_theta_raw ;
                int16_t pole_pairs;     /* Parameter: Number of pole pairs (Q0)  */
                int16_t index_sync_flag; /* Output: Index sync status (Q0)       */
				int32_t AbsaSingleData;     /* Output: Motor Electrical angle (Q15)  */
                int32_t AbsaCircleData;     /* Output: Motor Mechanical Angle (Q15)  */
	            int32_t AbsaAxisData;
				int32_t AbsaAxisDataS;
	           uint32_t AbsaAxisSaveL;
				int16_t AbsaAxisSaveL1;
                int16_t AbsaAxisSaveL2;
	           uint32_t AbsaAxisSaveH;
				int16_t AbsaAxisSaveH1;
                int16_t AbsaAxisSaveH2;
				int32_t AbsaAxisSave;
				int32_t AbsaAxisCur;
	           uint32_t AbsaAxisCurL;
				int16_t AbsaAxisCurL1;
                int16_t AbsaAxisCurL2;
	           uint32_t AbsaAxisCurH;
				int16_t AbsaAxisCurH1;
                int16_t AbsaAxisCurH2;
               uint32_t Absa_RX_DATA0;
               uint32_t Absa_RX_DATA1;
				int16_t SetAxisFinishFlag;
				int32_t ThetaElecNew;
				int32_t ThetaElecOld;
				int32_t AbsaAxisEk;
				int32_t AbsaAxisEkS;
				int16_t AbsaCodeType;
				int32_t PulseSum;
                int32_t CodeRem;
               uint16_t PulseNum;
               uint16_t PulseTime;
               uint16_t PZOUT;
               uint16_t CodeDir;
                int16_t mech_scaler;
                int32_t AbsaAxisData17bit;
                int32_t HomeAxisCur;
                int32_t cal_angle;
                int32_t etheta;
                void (*init)();     /* Pointer to the init funcion           */
                void (*calc)();     /* Pointer to the calc funtion           */
                void (*Axis)();      /* Pointer to the isr funtion           */
				void (*FenPin)();
				void (*Reset)();
                }  ENCODER;

/*-----------------------------------------------------------------------------
Define a QEP_handle
-----------------------------------------------------------------------------*/
typedef ENCODER *ENCODER_handle;

/*-----------------------------------------------------------------------------
Default initializer for the QEP Object.
-----------------------------------------------------------------------------*/
#define ENCODER_DEFAULTS { 0x0,0x0,0x0,4,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,\
                       0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,512,0,0,0,0,\
                       0x0,0x0, \
                (void (*)(long))M680X_EV1_ENCODER_Init,                \
                (void (*)(long))M680X_EV1_ENCODER_Calc, 				 \
                (void (*)(long))M680X_EV1_ENCODER_Axis,\
                (void (*)(long))M680X_EV1_ENCODER_FenPin,\
				M680X_EV1_ENCODER_Reset}
/*-----------------------------------------------------------------------------
Prototypes for the functions in F28XQEP.C
-----------------------------------------------------------------------------*/



void M680X_EV1_ENCODER_Init(ENCODER_handle);
void M680X_EV1_ENCODER_Calc(ENCODER_handle);
void M680X_EV1_ENCODER_Axis(ENCODER_handle);
void M680X_EV1_ENCODER_FenPin(ENCODER_handle);
void M680X_EV1_ENCODER_Reset(ENCODER_handle);
void ta_single_reset_cmd(u32 n);
void absa_single_reset(u32 n);
extern void qep_pinmux_init(u8 i);
extern void encoder_line_sel(int8_t input_data);
extern int32_t   EncodeLine;
extern int32_t   HCL_EncodeLine;
extern int32_t   EncodeLine_By_Two;
extern int32_t   encoder_lsw;
extern uint8_t   HCL_ABSA_SHIFT_BIT;
extern int32_t   absa_theta_raw_from_cpld;
extern uint16_t  encoder_rcr_error_flag;
extern uint16_t  encoder_rcr_error_cnt;
extern uint16_t  encoder_off_error_flag;
extern uint16_t  encoder_off_error_cnt;
extern ENCODER encoder1;
extern uint8_t   pa_AEncode[11];
extern ENCODER encoder1;
#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_ENCODER_H_ */
