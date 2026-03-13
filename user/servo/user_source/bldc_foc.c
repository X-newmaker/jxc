/*
 * bldc_foc.c
 *
 *  Created on: 2025年2月4日
 *      Author: L
 */
#include "all_inc.h"
#include "M680x_it.h"

mcl_user_value_t motor_speed = {0,0,0,0,0};
mcl_user_value_t motor_position = {0,0,0,0,0};
mcl_user_value_t motor_torque = {0,0,0,0,0};
void motor_torque_loop_init(void)
{
	if (motor_position.enable) {
		motor_position.enable = false;
	}
	motor_torque.enable = true;
	motor_speed.enable = false;
}
void motor_speed_loop_init(void)
{
    if (motor_position.enable) {
        motor_position.enable = false;
    }
    motor_speed.enable = true;
}
void motor_torque_loop_set(int32_t target_torque,int32_t max_motor_speed)
{
	Servo.Pn01.ContrlMode.Data = CTL_Ti; //速度模式
	Servo.Pn01.ContrlSource.Data = 2;    //指令来源选择EtherCAT
	EscPdo.Object6071_TargetTorque = target_torque;//接收扭矩指令数据，单位是0.1%
	EscPdo.Object6080_MaxMotorSpeed = max_motor_speed;//最大运行速度，单位是rpm
	EscPdo.Object607F_SpeedProfileMax = max_motor_speed;
}
void motor_speed_loop_set(int32_t target_speed)
{
	Servo.Pn01.ContrlMode.Data = CTL_Si; //速度模式
	Servo.Pn01.ContrlSource.Data = 2;    //指令来源选择EtherCAT
	//EscPdo.Object60FF_SpeedTarget = target_speed;
    EscPdo.Object60FF_SpeedTarget = (int64_t)target_speed * 60 / EncodeLine;//设置伺服的速度
}

void motor_postion_loop_init(void)
{


}

void motor_position_loop_set(int32_t target_position)
{
    Servo.Pn01.ContrlMode.Data = CTL_Pt; //位置模式
//    Servo.Pn01.ServoON.Data = 1;
	Servo.Pn01.ContrlSource.Data = 2;    //指令来源选择EtherCAT
	EscPdo.Object607A_PostionTarget = target_position;//设置伺服的位置
	EscPdo.Object60FF_SpeedTarget = Servo.Pn02.PosCmdFilterSw.Data;
	if(STR_ECTCSPVar.SYNCPeriodRatio >=1 )//sync0中断周期小于位置环周期，则不接收位置指令
	{
		WriteCSPFIFO(EscPdo.Object607A_PostionTarget);//计算位置指令增量
	}
}
int32_t motor_get_actual_torque(void)
{
	/* 额定电流单位是0.1A
	 * 转矩系数单位是0.001
	 * 扭矩单位是0.01N.m
	 * 扭矩反馈单位是:0.1%
	 */
	int32_t tmp;
	tmp = (Fn.TorqueFdb * 1000) / ((int32_t)Servo.Pn01.RatedCurrent.Data * Servo.Pn02.Torquek.Data / 100);

    return tmp;
}
int32_t motor_get_actual_speed(void)
{
	g_custom_data[sendflag * 4 + 3]= speed1.speed_rpm;
    return (int64_t)(speed1.speed_rpm) * EncodeLine / 60 ;//速度反馈单位是pulse/s
}
/*
 * 计算每一个周期的位置增量
 */

int32_t motor_get_actual_position(void)
{
	int32_t tmp;
    if(motor_position.enable == false)
    {
    	motor_position.enable = true;
    	motor_speed.enable = false;
		motor_position.actual_position_new = encoder1.absa_theta_raw;
		motor_position.actual_position_old = encoder1.absa_theta_raw;
    }
	motor_position.actual_position_new = encoder1.absa_theta_raw;
	tmp = motor_position.actual_position_new - motor_position.actual_position_old;

	if(tmp > EncodeLine_By_Two){
		tmp = -(EncodeLine-tmp);
	}
	if(tmp < -EncodeLine_By_Two){
		tmp = (EncodeLine+tmp);
	}
	motor_position.actual_position_old = motor_position.actual_position_new;
	motor_position.actual_position_cur += tmp; //对位置增量进行累加

    return (int32_t)(motor_position.actual_position_cur);
}


void motor_enable(void)
{
	EscPdo.COMM_SON = 1; //伺服使能
}

void motor_disable(void)
{
	EscPdo.COMM_SON = 0;//伺服停止
}

