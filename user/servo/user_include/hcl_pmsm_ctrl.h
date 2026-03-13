/*
 * hcl_pmsm_ctrl.h
 *
 *  Created on: 2025年4月10日
 *      Author: L
 */

#ifndef USER_SERVO_USER_INCLUDE_HCL_PMSM_CTRL_H_
#define USER_SERVO_USER_INCLUDE_HCL_PMSM_CTRL_H_
typedef struct
{
	uint16_t voltADCAveVal;		//ADC采集到的平均值
	uint16_t voltADCMin;			//母线电压补偿最小值 IQ10
	uint16_t voltADCMax;			//母线电压补偿最大值 IQ10
	uint16_t VoltCompEnableSw;     //电压补偿开关
	int32_t voltCompCoffIQ10;	//母线电压补偿实时值

}STRVOLTCOMP;
typedef struct MOTOR_EXTERN_STRUCT_DEF {
    uint16_t    UnitCoff;                           //电机参数转换系数为10
	uint16_t 	R1;						            //定子相电阻	0.001欧姆
	uint16_t 	R2;						            //转子相电阻	0.001欧姆
	uint16_t 	L0;						            //漏感	单位0.01mH
	uint16_t 	LM;						            //互感	单位0.01mH
	uint16_t 	I0;						            //空载电流单位0.01A
	uint16_t    IoVsFreq;                           //弱磁区反比速度变化的空载电流，只计算它的标么值
	uint16_t 	Rpm;					            //电机转速		 单位1rpm
    uint16_t    RatedComp;	                        //额定转差率       0.01Hz, pu
	uint16_t 	Poles;					            //电机极数
	uint16_t 	L1;						            //定子相电感		 单位0.01mH
	uint16_t 	L2;						            //转子相电感		 单位0.01mH
    uint16_t    RsPm;                               // 同步机定子电阻
	uint16_t 	LD;						            //同步机D轴电感    单位0.01mH
	uint16_t 	LQ;						            //同步机Q轴电感    单位0.01mH
	uint16_t    BemfVolt;                           // 同步机反电动势电压， 可以计算出转子磁链
    uint16_t    BemfVoltApply;
	uint16_t    FluxRotor;                          // 同步机转子磁链  Q12
    uint16_t    ItRated;                            // 额定力矩电流
    uint16_t    FluxLeakCurveGain;
}MOTOR_EXTERN_STRUCT;   //电机扩展信息结构
typedef struct PM_DECOUPLE_DEF{
    int32_t Omeg;   // Q15
    int32_t Isd;    // Q15
    int32_t Isq;    // Q12
    int32_t Isdpu;  // IQ10
    int32_t Isqpu;  // IQ10
	int32_t Is;     // Q12
    int32_t PhiSd;  // Q12      d轴全磁链
    int32_t PhiSq;  // Q12
    int32_t RotVd;  // Q12
    int32_t RotVq;  // Q12
    int32_t EnableDcp;
	//Uint Amp;         // Q12      幅值
	int32_t IsdSet;    // Q12
    int32_t IsqSet;    // Q12
    int32_t PhiSdSet;  // Q12      d轴全磁链设定值
    int32_t PhiSqSet;  // Q12
    int32_t RotVdSet;  // Q12
    int32_t RotVqSet;  // Q12
	int32_t IsqSetMax;
	int32_t EMF;       //Q12    反电动势前馈量
	uint32_t Us;        //Q12    输出电压滤波值
	uint16_t BaseFreRate;
	uint16_t MaxFreRate;
}PM_DECOUPLE;
extern int16_t hcl_reg_update_enable;
extern void MS_Hcl_Init(uint8_t n);
extern void VoltageAveCalc(uint16_t voltAdc);
extern void MS_Hcl_Reg_Update(uint8_t n);
extern void MS_Hcl_Enbale(uint8_t n);
extern void MS_Hcl_Clr(uint8_t n);
#endif /* USER_SERVO_USER_INCLUDE_HCL_PMSM_CTRL_H_ */
