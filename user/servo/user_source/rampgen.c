/*
 * rampgen.c
 *
 *  Created on: 2023年8月14日
 *      Author: wenxing.ma
 */

#include "all_inc.h"
#include "M680x_it.h"

#include "servo_drv_setting.h"
void rampgen_calc(RAMPGEN *v)
{
	s32 theta;

	v->angle_rg += _IQmpy(v->step_angle_max,v->rmp_freq);
	if(Servo.Pn01.ContrlMode.Data == CTL_WITHD_TEST)
	{
		if (v->angle_rg>_IQ(1))
		  v->angle_rg -= _IQ(1);
		else if (v->angle_rg<_IQ(-1))
		  v->angle_rg += _IQ(1);
	}
	else
	{
		if (v->angle_rg > 32768)
		  v->angle_rg -= 65536;
		else if (v->angle_rg < -32768)
		  v->angle_rg += 65536;
	}

    v->rmp_out = v->angle_rg;

}
