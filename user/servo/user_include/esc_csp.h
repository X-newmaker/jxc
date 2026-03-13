/*
 * esc_csp.h
 *
 *  Created on: 2025年2月8日
 *      Author: L
 */

#ifndef USER_SERVO_USER_INCLUDE_ESC_CSP_H_
#define USER_SERVO_USER_INCLUDE_ESC_CSP_H_
#ifdef  __cplusplus                     //C++和C语言可兼容要求
extern "C" {
#endif
#include "all_inc.h"
#include "M680x_it.h"

#define GetSYNCTime_1MHzClk()    (*TIM10_CNT)      //系统时钟频率1MHz

typedef struct
{
    uint32_t   SYNCPeriodRatio;//同步周期与插补周期的比值
    uint32_t   SYNCPeriod;	//同步周期，单位ns
	 int32_t   MaxInterpltPosCmd;//最大位置指令限制
	 int64_t   MaxDeltaTarPos;//最大位置指令增量
	 int32_t   InterpltPoint;//插补目标位置
     int64_t   InterpltDltRef; //本段位置指令增量--编码器单位
	 int64_t   InterpltSumRef;//当前未发送的位置指令
     int32_t   InterpltIncPer;    //每次位置环的位置指令
     int64_t   RefPosRemainder;//细分后的位置指令余数
	 int32_t   OTLatchPosCmd;    //超程记录的限位方向的多发的位置指令
	 int32_t   TargetPos;        //当前指令位置值
	 int32_t   LatchPos;         //上一周期指令位置值
	 uint8_t   OTDeal;
     uint8_t   CSPRunFlag;//
	uint16_t   P_overspeedcnt;
     int32_t   PosLoopCnt;//
      int8_t   ESMState;
}STR_ECTCSPVAR;

typedef struct{
    int64_t   InPut;                    //本同步周期输入位置指令总数
    int64_t   PosRefAve;
}STR_ECTCSPPOSREF;

typedef struct{
	uint32_t InPut;
	uint32_t AccFactor6097_Numerator;
	uint32_t AccFactor6097_Denominator;
	uint64_t Vel_AccFactor6097Q14;	     //6097
	uint64_t Pos_AccFactor6097Q14;
}STR_ACC_FACTOR;

typedef struct{

	int64_t   InPut;                        //速度编码器因子转换前速度指令(用户单位)
	uint32_t  VelEncoder6094_Numerator;
	uint32_t  VelEncoder6094_Denominator;   //6094 用户速度--驱动器速度
    int64_t   VelEncoder6094Q20;
}STR_VELOCITYENCODER_FACTOR;

typedef struct{
	int32_t   InPut;                      //速度转换因子前速度反馈(10000*rpm)
	uint32_t  VelFactor6095_Numerator;
	uint32_t  VelFactor6095_Denominator;  //6095倒数，用户速度单位-->rpm
	uint64_t  VelFactor6095Q14;           //6095,rpm-->用户速度单位
}STR_VELOCITY_FACTOR;

typedef struct{
	int32_t   InPut;                      //位置转换因子前位置给定(增量)
    int64_t   PosRemainder;               //位置转换因子计算的余数
   uint32_t   PosFactor6091_Numerator;
   uint32_t   PosFactor6091_Denominator;
}STR_POSITION_FACTOR;

typedef struct{
	int64_t   InPut;                      //位置转换因子前绝对位置反馈
   uint32_t   PosFactor6091_Numerator;
   uint32_t   PosFactor6091_Denominator;
    uint64_t  PosFactor6091_InverseQ16;   //6091倒数，用于计算用户位置反馈
}STR_POSITION_FACTOR_INVERSE;

extern STR_ECTCSPVAR STR_ECTCSPVar;
extern STR_FUNC_GLOBALVARIABLE          STR_FUNC_Gvar;

extern void WriteCSPFIFO(int32_t CSP_TargetPos); //计算插补位置指令,SYNC 时调用
extern void ECTCSPUpdata(void);//参数更新
extern void InitECTCSP(void); //参数复位
extern void CSPClear(void);
extern void ECTCSPMaxSpeedUpdate(void);
extern void CSPPointCal(void);
extern void FactorUpdate(void);
extern int32_t ECTCSPPosCmd(void);
extern void CSP_main_loop(void);
#ifdef __cplusplus
}
#endif /* extern "C" */


#endif /* USER_SERVO_USER_INCLUDE_ESC_CSP_H_ */
