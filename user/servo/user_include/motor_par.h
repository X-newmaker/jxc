/*
 * motor_par.h
 *
 *  Created on: 2025年4月29日
 *      Author: L
 */

#ifndef USER_SERVO_USER_INCLUDE_MOTOR_PAR_H_
#define USER_SERVO_USER_INCLUDE_MOTOR_PAR_H_
typedef struct{
    uint16_t RsdMotorModel;       //P1-05 电机型号代码
    uint16_t RateVolt;            // 额定电压
    uint16_t RatePower;           // 额定功率
    uint16_t RateCurrent;         // 额定电流
    uint16_t RateToq;             // 额定转矩
    uint16_t MaxToq;              // 最大转矩
    uint16_t RateSpd;             // 额定转速
    uint16_t MaxSpd;              // 最大转速
    uint16_t Inertia;             // 转动惯量
}STR_MOTRORPARA;

#endif /* USER_SERVO_USER_INCLUDE_MOTOR_PAR_H_ */
