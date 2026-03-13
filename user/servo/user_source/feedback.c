/*
 * feedback.c
 *
 *  Created on: 2023年8月14日
 *      Author: wenxing.ma
 */
#include "all_inc.h"
#include "encoder.h"
#include "pos.h"
#include "GVAR_DEF.h"

extern SERVO_PAR Servo;
extern SPEED_MEAS_PR pr1;
extern int contrl_cmd_frq;
extern int32_t EncodeLine;
extern int32_t EncodeLine_By_Two;
long  _iqSpeedMax = 0;
long  PluseSendMax = 0;
float floatTimeMax = 0;
float _floatTimeMax = 0;
long _iqRmpTargetValue = 0;
long _iqRmpSetptValue = 0;
long pos_sum_real_tmp = 0;
long pos_sum_ref_tmp = 0;
int16_t  Dflag  = 0;
int16_t  PrSendPulseOverFlag = 0;
extern int16_t   PTRG_enable;

void pos_frq_Init(SPEED_MEAS_POS *v)
{
	v->fdb_new = 0;
	v->fdb_old = 0;
	v->fdb_frq = 0;
}

void pos_frq_calc(SPEED_MEAS_POS *v)
{
	long tmp1;
	tmp1 = v->fdb_new - v->fdb_old;
	if(tmp1 > EncodeLine_By_Two)
	{
		tmp1 = -(EncodeLine-tmp1);
	}
	if(tmp1 < -EncodeLine_By_Two)
	{
		tmp1 = (EncodeLine+tmp1);
	}
	v->fdb_frq = tmp1;
	v->fdb_old = v->fdb_new;
}
void Pr_frq_Init(SPEED_MEAS_PR *v)
{
	_iqSpeedMax = _IQ24(1.0f / v->rmp_spd_max);
	PluseSendMax = v->position_max*v->rmp_pos_loop_ps;
	if(Servo.Pn02.IsrFrequency.Data == 1)
	{
		_floatTimeMax = (float)v->rmp_pos_loop_ps / (v->rmp_inc_dec_time * 8.0f);
	}
	else
	{
		_floatTimeMax = (float)v->rmp_pos_loop_ps / (v->rmp_inc_dec_time * 10.0f);
	}
}

void Pr_frq_calc(SPEED_MEAS_PR *v)
{

}
void PrSendPulseFinish(void)
{
	pr1.auto_run_en = 0;
    pr1.speed_ref = 0;
    pr1.pos_sum_real = 0;
    pr1.pos_sum_ref = 0;
    pr1.pos_sum_real = 0;
    pr1.rmp_setpt_value = 0;
    pr1.rmp_speed_sync = 0;
    pr1.pr_pos_save = 0;
    pr1.RemainS = 0;

    pr1._long_pr_pos_ref = 0;
    pr1.rmp_setpt_value_sum = 0;
    pr1.rmp_delay_cntl = 0;
    _iqRmpSetptValue = 0;
	PTRG_enable = 0;
}
void PrRunCtrlCalc(s32 AxiseIncPosition,s16 MotorSpeed)
{
	pr1.pos_sum_ref = AxiseIncPosition;
	  //??=(Vref/Vmax)*rmp_pos_loop_ps/(rmp_inc_dec_time * 10.0)
	  if(pr1.auto_run_en == 0)
	  {
				pr1.rmp_target_value = MotorSpeed;
				_iqRmpTargetValue = _IQ24(pr1.rmp_target_value / (float)pr1.rmp_spd_max);
				//pr1.rmp_spd_inc = _IQ24(_IQabs(pr1.rmp_target_value)*_floatTimeMax / (float)pr1.rmp_spd_max);//????? = (???? * ??????)/?????
				pr1.rmp_spd_inc = _IQabs(_iqRmpTargetValue) / (pr1.rmp_inc_dec_time*10);
//				if(pr1.rmp_spd_inc < 0)
//				{
//						pr1.rmp_spd_inc = -pr1.rmp_spd_inc;
//				}
				pr1._long_pr_pos_ref = _IQ24mpy(PluseSendMax,_iqRmpSetptValue);

				if(pr1.rmp_target_value > 0)                       //??????????
				{
						pr1.pos_sum_real += pr1._long_pr_pos_ref;       //??????????
						if(pr1.pos_sum_real >= (pr1.pos_sum_ref / 2))     //??????
						{
								pr1.auto_run_en = 1;
						}
						else
						{
								if(pr1.rmp_speed_sync == 0)
								{
									 pr1.RemainS = pr1.pos_sum_real;
								}
						}
						if(pr1.pos_sum_real > (pr1.pos_sum_ref - pr1._long_pr_pos_ref))
						{
								pr1.auto_run_en = 3;
						}
						if(pr1.pos_sum_real >= pr1.pos_sum_ref)
						{
								pr1.auto_run_en = 5;
						}
				}
				else if(pr1.rmp_target_value < 0)                                             //???????
				{
						pr1.pos_sum_real += pr1._long_pr_pos_ref;      //??????????
						if(pr1.pos_sum_real <= -(pr1.pos_sum_ref / 2))
						{
								pr1.auto_run_en = 1;
						}
						else
						{
								if(pr1.rmp_speed_sync == 0)
								{
									 pr1.RemainS = -pr1.pos_sum_real;//???
								}
						}
						if(pr1.pos_sum_real < -(pr1.pos_sum_ref + pr1._long_pr_pos_ref))
						{
								pr1.auto_run_en = 3;
						}
						if(pr1.pos_sum_real <= -pr1.pos_sum_ref)
						{
								pr1.auto_run_en = 5;
						}
				}
				else
				{
						pr1.auto_run_en = 5;
				}
	  }
	  else if(pr1.auto_run_en == 1)                        //?????
	  {
				pr1.rmp_target_value = MotorSpeed;
				_iqRmpTargetValue = _IQ24(pr1.rmp_target_value / (float)pr1.rmp_spd_max);
				//pr1.rmp_spd_inc = _IQ24(_IQabs(pr1.rmp_target_value)*_floatTimeMax / (float)pr1.rmp_spd_max);//????? = (???? * ??????)/?????
				pr1.rmp_spd_inc = _IQabs(_iqRmpTargetValue) / (pr1.rmp_inc_dec_time*10);
//				if(pr1.rmp_spd_inc < 0)
//				{
//					 pr1.rmp_spd_inc = -pr1.rmp_spd_inc;
//				}
				pr1._long_pr_pos_ref = _IQ24mpy(PluseSendMax,_iqRmpSetptValue);
				if(pr1.rmp_target_value >0)                   //??????????
				{
					 pr1.pos_sum_real += pr1._long_pr_pos_ref;  //??????????
					 if(pr1.pos_sum_real >= (pr1.pos_sum_ref- pr1.RemainS))
					 {
						 pr1.auto_run_en = 2;
					 }
					 if(pr1.pos_sum_real > (pr1.pos_sum_ref-pr1._long_pr_pos_ref))
					 {
						pr1.auto_run_en = 3;
					 }
					 if(pr1.pos_sum_real >= pr1.pos_sum_ref)
					 {
						pr1.auto_run_en = 5;
					 }
				}
				else if(pr1.rmp_target_value < 0)                                          //???????
				{
					 pr1.pos_sum_real += pr1._long_pr_pos_ref;   //??????????
					 if(pr1.pos_sum_real <= -(pr1.pos_sum_ref - pr1.RemainS))
					 {
						 pr1.auto_run_en = 2;
					 }
					 if(pr1.pos_sum_real < -(pr1.pos_sum_ref + pr1._long_pr_pos_ref))
					 {
						pr1.auto_run_en = 3;
					 }
					 if(pr1.pos_sum_real <= -pr1.pos_sum_ref)
					 {
						pr1.auto_run_en = 5;
					 }
				}
				else
				{
					 pr1.auto_run_en = 5;
				}
	  }
	  else if(pr1.auto_run_en == 2)                      //?????
	  {
		   if(pr1.rmp_target_value > 0)                  //??????????
		   {
			   pr1.rmp_target_value = 5;//?????1rpm
			   _iqRmpTargetValue = _IQ24(pr1.rmp_target_value / (float)pr1.rmp_spd_max);
			   pr1._long_pr_pos_ref = _IQ24mpy(PluseSendMax,_iqRmpSetptValue);
			   pr1.pos_sum_real += pr1._long_pr_pos_ref;  //??????????
			   if(pr1.pos_sum_real > (pr1.pos_sum_ref-pr1._long_pr_pos_ref))
			   {
				   pr1.auto_run_en = 3;
			   }
			   if(pr1.pos_sum_real >= pr1.pos_sum_ref)
			   {
				  pr1.auto_run_en = 5;
			   }
		   }
		   else if(pr1.rmp_target_value < 0)                                          //???????
		   {
			   pr1.rmp_target_value = -5;//?????-1rpm
			   _iqRmpTargetValue = _IQ24(pr1.rmp_target_value / (float)pr1.rmp_spd_max);
			   pr1._long_pr_pos_ref = _IQ24mpy(PluseSendMax,_iqRmpSetptValue);
			   pr1.pos_sum_real += pr1._long_pr_pos_ref;//??????????
			   if(pr1.pos_sum_real < -(pr1.pos_sum_ref + pr1._long_pr_pos_ref))
			   {
				    pr1.auto_run_en = 3;
			   }
			   if(pr1.pos_sum_real <= -pr1.pos_sum_ref)
			   {
				    pr1.auto_run_en = 5;
			   }
		   }
		   else
		   {
			   pr1.auto_run_en = 5;
		   }
	  }
	  else if(pr1.auto_run_en == 3)
	  {
		   if(pr1.rmp_target_value > 0)//??????????
		   {
					 pr1._long_pr_pos_ref = 1;
					 pr1.pos_sum_real += pr1._long_pr_pos_ref;//??????????
					 if(pr1.pos_sum_real >= (pr1.pos_sum_ref + 1))
					 {
							pos_sum_real_tmp = pr1.pos_sum_real;
							pos_sum_ref_tmp = pr1.pos_sum_ref;
							PrSendPulseFinish();
					 }
		   }
		   else if(pr1.rmp_target_value < 0)                                       //???????
		   {
					 pr1._long_pr_pos_ref = -1;
					 pr1.pos_sum_real += pr1._long_pr_pos_ref;//??????????
					 if(pr1.pos_sum_real <= -(pr1.pos_sum_ref + 1))
					 {
							PrSendPulseFinish();
					 }
			 }
		   else
		   {
			     pr1.auto_run_en = 5;
		   }
	   }
	   else if(pr1.auto_run_en == 5)
	   {
		   PrSendPulseFinish();
			 Dflag = 1;
	   }
	   contrl_cmd_frq = pr1._long_pr_pos_ref;
	   /*********************?????***************************/
	   if(_iqRmpTargetValue != _iqRmpSetptValue)
	   {
				if(_iqRmpTargetValue > _iqRmpSetptValue)
				{
					 _iqRmpSetptValue += pr1.rmp_spd_inc;
					 //if(pr1.rmp_speed_sync == 0)pr1.RemainS = pr1.pos_sum_real;
					 if(_iqRmpSetptValue > _iqRmpTargetValue)
					 {
						 _iqRmpSetptValue = _iqRmpTargetValue;
						 pr1.rmp_speed_sync = 1;
					 }
				}
				else
				{
						_iqRmpSetptValue -= pr1.rmp_spd_inc;
						//if(pr1.rmp_speed_sync == 0)pr1.RemainS = -pr1.pos_sum_real;//???
						if (_iqRmpSetptValue < _iqRmpTargetValue)
						{
							_iqRmpSetptValue = _iqRmpTargetValue;
								pr1.rmp_speed_sync = 1;
						}
				}
	   }
	   else
	   {
		    _iqRmpSetptValue = _iqRmpTargetValue;
	   }
}


