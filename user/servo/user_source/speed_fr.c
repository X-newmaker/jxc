/*
 * speed_fr.c
 *
 *  Created on: 2023年8月14日
 *      Author: wenxing.ma
 */

#include "all_inc.h"
#include "M680x_it.h"

_iq speed_raw_before = 0;
int16_t current_speed_loss_flag = 0;
int32_t current_speed_loss_cnt = 0;

extern int32_t EncodeLine;
extern int32_t EncodeLine_By_Two;
void speed_frq_calc(SPEED_MEAS_QEP *v)
{
   _iq speed_input_old = 0;
   v->speed_raw = v->theta_new - v->theta_old;
   if(v->speed_raw > EncodeLine_By_Two)
   {
	   v->speed_raw = -(EncodeLine - v->speed_raw);
   }
   if(v->speed_raw < -EncodeLine_By_Two)
   {
	   v->speed_raw = (EncodeLine + v->speed_raw);
   }
   if(encoder_rcr_error_flag == 0 || encoder_off_error_flag == 0)//编码器CRC没有错误
   {
      v->speed_input = (long)(v->speed_raw) * v->speed_max;
      speed_input_old = v->speed_input;
   }
   else
   {
	   v->speed_input = speed_input_old;
   }
   v->speed_frq = _IQ24mpy(v->K2,v->speed_frq) + _IQ24mpy(v->K3,v->speed_input);
   v->speed_rpm = _IQ24mpy((int32_t)int_speed_max,v->speed_frq);//速度反馈单位为rpm,单位是0.0001
   if (v->speed_frq > _IQ24(1))
   {
       v->speed_frq = _IQ24(1);
   }
   else if (v->speed_frq< _IQ24(-1))
   {
       v->speed_frq = _IQ24(-1);
   }
   v->theta_old = v->theta_new;

}
void hcl_speed_frq_calc(SPEED_MEAS_QEP *v)
{
	v->speed_frq = _IQ24mpy(v->K2,v->speed_frq) + _IQ24mpy(v->K3,v->speed_input);
	v->speed_rpm = _IQ24mpy((int32_t)int_speed_max,v->speed_frq);//速度反馈单位为rpm,单位是0.0001
	if (v->speed_frq > _IQ24(1))
	{
	   v->speed_frq = _IQ24(1);
	}
	else if (v->speed_frq< _IQ24(-1))
	{
	   v->speed_frq = _IQ24(-1);
	}
}
