/*
 * pid_reg3.c
 *
 *  Created on: 2023年8月14日
 *      Author: wenxing.ma
 */

#include "all_inc.h"
#include "pid_reg3.h"
#include "Const_Def.h"
#include "GVAR_DEF.h"


extern PIDREG3 pid1_spd;

int IqPidCnt= 0;
int IqPidFlag = 1;
int SpdPidCnt = 0;
int SpdPidFlag = 1;
int SpdKiUseCnt = 0;
int iqPid_ContrlCmdNew = 0;
int iqPid_ContrlCmdOld = 0;
int spdPid_ContrlCmdNew = 0;
int spdPid_ContrlCmdOld = 0;
void Spd_P_Calc(PIDREG3 *v)
{
	    if(v->motor_speed < v->speed_frq_max && v->motor_speed > v->speed_frq_min)
	    {
			 v->Kp_reg3 = v->Kp3_reg3;
			 v->Ki_reg3 = v->Ki1_reg3;
	    }
	    else
	    {
			 v->Kp_reg3 = v->Kp1_reg3;
			 v->Ki_reg3 = v->Ki1_reg3;
	    }

		v->e_reg3 = (v->pid_ref_reg3+ v->SpeedBefOut) - v->pid_fdb_reg3;
		v->up_reg3 = _IQ24mpy(v->Kp_reg3,v->e_reg3);
		v->uprsat_reg3 = v->up_reg3;//PI调节器

		if (v->uprsat_reg3 >= v->pid_out_max)
		{
			 v->pid_out_reg3 =  v->pid_out_max;
		}
		else if (v->uprsat_reg3 <= v->pid_out_min)
		{
			 v->pid_out_reg3 =  v->pid_out_min;
		}
		else
		{
			 v->pid_out_reg3 = v->uprsat_reg3;
		}
		v->saterr_reg3 = v->pid_out_reg3 - v->uprsat_reg3;
		v->ui_reg3 = 0;
}
void Spd_PID_Calc(PIDREG3 *v)
{
		if(v->e_reg3 > v->pi_ek_max || v->e_reg3 < v->pi_ek_min)
		{
			 v->Kp_reg3 = v->Kp1_reg3;
			 v->Ki_reg3 = v->Ki2_reg3;//PI分离
		}
		else
		{
			 if(v->motor_speed < v->speed_frq_max && v->motor_speed > v->speed_frq_min)
			 {
				 v->Kp_reg3 = v->Kp3_reg3;
				 v->Ki_reg3 = v->Ki1_reg3;
			 }
			 else
			 {
				 v->Kp_reg3 = v->Kp1_reg3;
				 v->Ki_reg3 = v->Ki1_reg3;
			 }
		}

		v->e_reg3 = v->pid_ref_reg3 - v->pid_fdb_reg3;
		if(v->e_reg3 >= _IQ24(1))
		{
			 v->e_reg3 = _IQ24(1);
		}
		else if(v->e_reg3 <= _IQ24(-1))
		{
			 v->e_reg3 = _IQ24(-1);
		}
		v->up_reg3 = _IQ24mpy(v->Kp_reg3,v->e_reg3);
		v->ui_reg3 = v->ui_reg3 + _IQ24mpy(v->Ki_reg3,v->up_reg3) + _IQ24mpy(v->Kc_reg3,v->saterr_reg3);
		if (v->ui_reg3 >= v->pid_out_max)
		  v->ui_reg3 =  v->pid_out_max;
		else if (v->ui_reg3 <= v->pid_out_min)
		  v->ui_reg3 =  v->pid_out_min;

		v->uprsat_reg3 = v->up_reg3 + v->ui_reg3;//PI调节器

		if(v->uprsat_reg3 >= v->pid_out_max)
			v->pid_out_reg3 =  v->pid_out_max;
		else if (v->uprsat_reg3 <= v->pid_out_min)
			v->pid_out_reg3 =  v->pid_out_min;
		else
		v->pid_out_reg3 = v->uprsat_reg3;

		v->saterr_reg3 = v->pid_out_reg3 - v->uprsat_reg3;
}
void pid_reg3_calc(PIDREG3 *v)
{
    long tmp;
    if(v->pid_type == 1)
    {
		v->Kp_reg3 = v->Kp1_reg3;
		v->Ki_reg3 = v->Ki1_reg3;
		v->e_reg3 = v->pid_ref_reg3 - v->pid_fdb_reg3;
		v->up_reg3 = _IQ24mpy(v->Kp_reg3,v->e_reg3);
		v->uprsat_reg3 = v->up_reg3 + v->ui_reg3;
		if (v->uprsat_reg3 >= v->pid_out_max)
		{
			v->pid_out_reg3 =  v->pid_out_max;
		}
		else if (v->uprsat_reg3 <= v->pid_out_min)
		{
			v->pid_out_reg3 =  v->pid_out_min;
		}
		else
		{
			v->pid_out_reg3 = v->uprsat_reg3;
		}
		v->saterr_reg3 = v->pid_out_reg3 - v->uprsat_reg3;
		v->ui_reg3 = v->ui_reg3 + _IQ24mpy(v->Ki_reg3,v->up_reg3);
		if(v->ui_reg3 >= v->pid_out_max)
		{
			v->ui_reg3 = v->pid_out_max;
		}
		else if(v->ui_reg3 <= v->pid_out_min)
		{
			v->ui_reg3 = v->pid_out_min;
		}
		//v->ud_reg3 = _IQ24mpy(v->Kd_reg3,(v->up_reg3 - v->up1_reg3));
		v->up1_reg3 = v->up_reg3;

    }
    else if(v->pid_type == 2)
	{
		if(v->pid_p_sel == 0) //PI
		{
				Spd_PID_Calc(&pid1_spd);
		}
		else if(v->pid_p_sel == 1) //P
		{
			  Spd_P_Calc(&pid1_spd);
		}
		else if(v->pid_p_sel == 2) //PiToP
		{

		}
    }
    else if(v->pid_type == 3)//位置环
    {
        v->up_reg3 = _IQ24mpy(v->Kp_reg3,v->e_reg3);

		v->uprsat_reg3 = v->up_reg3;//P调节器+速度前馈+补偿

		if (v->uprsat_reg3 > v->pid_out_max)
		{
			v->pid_out_reg3 =  v->pid_out_max;
		}
		else if(v->uprsat_reg3 < v->pid_out_min)
		{
			v->pid_out_reg3 =  v->pid_out_min;
		}
		else
		{
			v->pid_out_reg3 = v->uprsat_reg3;
		}
    }
	else if(v->pid_type == 4)//位置前馈
    {
        v->up_reg3 = _IQ24mpy(v->Kp_reg3,v->e_reg3);
		v->uprsat_reg3 = v->up_reg3;//P调节器
        if (v->uprsat_reg3 > v->pid_out_max)
		{
            v->pid_out_reg3 =  v->pid_out_max;
		}
        else if (v->uprsat_reg3 < v->pid_out_min)
		{
            v->pid_out_reg3 =  v->pid_out_min;
		}
        else
		{
            v->pid_out_reg3 = v->uprsat_reg3;
		}
    }
}

void pid_reg3_init(PIDREG3 *v)
{
    v->pid_ref_reg3 = 0;
    v->pid_fdb_reg3 = 0;
	v->e_reg3 = 0;
	v->up_reg3 = 0;
    v->ui_reg3 = 0;
    v->ud_reg3 = 0;
    v->uprsat_reg3 = 0;
    v->pid_out_reg3 = 0;
	v->saterr_reg3 = 0;
    v->up1_reg3 = 0;
    v->motor_speed = 0;
	v->SpeedBefRef = 0;
	v->SpeedAccOut = 0;
    IqPidCnt= 0;
	IqPidFlag = 1;
	SpdPidCnt= 0;
	SpdPidFlag = 1;
	iqPid_ContrlCmdNew = 0;
	iqPid_ContrlCmdOld = 0;
	spdPid_ContrlCmdNew = 0;
	spdPid_ContrlCmdOld = 0;
    SpdKiUseCnt = 0;
}

