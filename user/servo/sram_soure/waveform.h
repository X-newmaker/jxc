/*
 * user_io.c
 *
 *  Created on: 2023年8月14日
 *      Author: wen.xuan
 */

#ifndef _SERVO_UARTAPP_H_
#define _SERVO_UARTAPP_H_

typedef struct
{
	u16 start;
	u8  fun;
	u8  len;
	u8  data[21];
	u8  checksum;
}STRUARTAPP;

typedef union
{
	u8 all[26];
	STRUARTAPP bit;
} UNION_UARTAPP;

#define		BYTE0(data)		(*(char *)(&data))			//取低八位
#define		BYTE1(data)		(*((char *)(&data)+1))		//取次低八位
#define		BYTE2(data)		(*((char *)(&data)+2))		//取次高八位
#define		BYTE3(data)		(*((char *)(&data)+3))		//取高八位

void InitUartApp(void);
void UartRTSend(void);
void UartSanf(void);//串口数据扫描监测

#endif /* _SERVO_UARTAPP_H_ */
