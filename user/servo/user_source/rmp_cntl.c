/*
 * rmp_cntl.c
 *
 *  Created on: 2023年8月14日
 *      Author: wenxing.ma
 */

#include "all_inc.h"
#include "rmp_cntl.h"
#include "GVAR_DEF.h"
int32_t  setpt_value_tmp = 0;
int32_t  target_value_tmp = 0;
int32_t  rmp_spd_inc_before = 0;
int32_t  target_value_before = 0;
extern int16_t   int_speed_max;
extern SERVO_PAR Servo;

void spd_rmp_cntl_init(SPD_RMPCNTL *v)
{
	v->target_value = 0; //加减时间为零时直接等于目标速度
	v->setpt_value = 0;
	v->rmp_spd_inc = 0;
	v->rmp_delay_cntl = 1;
	v->rmp_dly_max = 10;
	rmp_spd_inc_before = 0;
	target_value_before = 0;
	setpt_value_tmp = 0;
}
void spd_rmp_cntl_calc(SPD_RMPCNTL *v)
{
	target_value_tmp = _IQ24(v->target_value / (float)v->rmp_spd_max);
	if(target_value_tmp != setpt_value_tmp)
	{
		if(target_value_tmp == 0)//目标速度等于零时减速
		{
			if(target_value_tmp > setpt_value_tmp)//负向减速，3000代表电机额定转速为3000转/min
			{
				if(Servo.Pn02.SpdDecTime.Data != 0)
				{
					v->rmp_spd_inc = _IQ24(3000 / (float)v->rmp_spd_max) / (Servo.Pn02.SpdDecTime.Data*10);
				}
				else
				{
					v->rmp_spd_inc = _IQ24(3000 / (float)v->rmp_spd_max);
				}
				setpt_value_tmp += v->rmp_spd_inc;
				if(setpt_value_tmp >= target_value_tmp)
				{
				 setpt_value_tmp = target_value_tmp;
				}
			}
			else if(target_value_tmp < setpt_value_tmp)//正向减速
			{
				if(Servo.Pn02.SpdDecTime.Data != 0)
				{
				    v->rmp_spd_inc = _IQ24(3000 / (float)v->rmp_spd_max) / (Servo.Pn02.SpdDecTime.Data*10);
				}
				else
				{
					v->rmp_spd_inc = _IQ24(3000 / (float)v->rmp_spd_max);
				}
				setpt_value_tmp -= v->rmp_spd_inc;
				if (setpt_value_tmp <= target_value_tmp)
				{
				    setpt_value_tmp = target_value_tmp;
				}
			}
		}
		else if(target_value_tmp > 0)//目标速度>0
		{
			if(target_value_tmp > setpt_value_tmp)//正向加速
			{
				if(Servo.Pn02.SpdIncTime.Data != 0)
				{
				    v->rmp_spd_inc = _IQ24(3000 / (float)v->rmp_spd_max) / (Servo.Pn02.SpdIncTime.Data*10);
				}
				else
				{
					v->rmp_spd_inc = _IQ24(3000 / (float)v->rmp_spd_max);
				}
				setpt_value_tmp += v->rmp_spd_inc;
				if(setpt_value_tmp >= target_value_tmp)
				{
				 setpt_value_tmp = target_value_tmp;
				}
			}
			else if(target_value_tmp < setpt_value_tmp)//正向减速
			{
				if(Servo.Pn02.SpdDecTime.Data != 0)
				{
				    v->rmp_spd_inc = _IQ24(3000 / (float)v->rmp_spd_max) / (Servo.Pn02.SpdDecTime.Data*10);
				}
				else
				{
					v->rmp_spd_inc = _IQ24(3000 / (float)v->rmp_spd_max);
				}
				setpt_value_tmp -= v->rmp_spd_inc;
				if (setpt_value_tmp <= target_value_tmp)
				{
				 setpt_value_tmp = target_value_tmp;
				}
			}
		}
		else if(target_value_tmp < 0)
		{
			if(target_value_tmp > setpt_value_tmp)//负向减速
			{
				if(Servo.Pn02.SpdDecTime.Data != 0)
				{
				    v->rmp_spd_inc = _IQ24(3000 / (float)v->rmp_spd_max) / (Servo.Pn02.SpdDecTime.Data*10);
				}
				else
				{
					v->rmp_spd_inc = _IQ24(3000 / (float)v->rmp_spd_max);
				}
				setpt_value_tmp += v->rmp_spd_inc;
				if(setpt_value_tmp >= target_value_tmp)
				{
				 setpt_value_tmp = target_value_tmp;
				}
			}
			else if(target_value_tmp < setpt_value_tmp)//负向加速
			{
				if(Servo.Pn02.SpdIncTime.Data != 0)
				{
				    v->rmp_spd_inc = _IQ24(3000 / (float)v->rmp_spd_max) / (Servo.Pn02.SpdIncTime.Data*10);
				}
				else
				{
					v->rmp_spd_inc = _IQ24(3000 / (float)v->rmp_spd_max);
				}
				setpt_value_tmp -= v->rmp_spd_inc;
				if (setpt_value_tmp <= target_value_tmp)
				{
					 setpt_value_tmp = target_value_tmp;
				}
			}
		}
	}
	else
	{
		setpt_value_tmp = target_value_tmp;
		v->rmp_delay_cntl = 1;
	}
	v->setpt_value = setpt_value_tmp;
}
