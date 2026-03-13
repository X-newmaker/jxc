/*
 * bldc_foc.h
 *
 *  Created on: 2025年2月4日
 *      Author: L
 */

#ifndef USER_SERVO_USER_INCLUDE_BLDC_FOC_H_
#define USER_SERVO_USER_INCLUDE_BLDC_FOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#define   true                       1
#define   false                      0
typedef struct {
	float   value;
	int32_t actual_position_new;//当前编码器位置
	int32_t actual_position_old;//上次编码器位置
	int32_t actual_position_cur;//编码器位置增量累加值，既增量绝对位置
	int32_t enable;

}mcl_user_value_t;

extern mcl_user_value_t motor_position;
void motor_function_init(void);

void motor_speed_loop_init(void);

void motor_speed_loop_set(int32_t target_speed);

void motor_postion_loop_init(void);

void motor_position_loop_set(int32_t target_position);

int32_t motor_get_actual_torque(void);

int32_t motor_get_actual_speed(void);

int32_t motor_get_actual_position(void);

void motor_enable(void);

void motor_disable(void);

#ifdef __cplusplus
}
#endif

#endif /* USER_SERVO_USER_INCLUDE_BLDC_FOC_H_ */
