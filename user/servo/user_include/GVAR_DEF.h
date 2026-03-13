/*
 * GVAR_DEF.h
 *
 *  Created on: 2023年8月11日
 *      Author: wenxing.ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_GVAR_DEF_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_GVAR_DEF_H_

#include "stdint.h"
typedef struct
{
	uint32_t Show :1;
	uint32_t Save :1;//是否可保存
	uint32_t modify:1;//0:不可修改   1:可修改
	uint32_t ponit:5;//5位数码管对应小数点 小数点显示  例如 0x11,seg[4] & seg[0]都将点亮
	uint32_t maxshownums:3;//最大显示数码管位数，例如 0~9为1，999为3，这个跟最大值有关
	uint32_t rsd:21;
}STR_ATTRI_BIT;

typedef union
{
	uint32_t all;
	STR_ATTRI_BIT bit;
}NUION_MENU_ATTRIBUTE;
typedef struct  {	
	int16_t Data;
	int16_t Max;
	int16_t Min;
	int16_t Unit;
	NUION_MENU_ATTRIBUTE attri;//属性
}PARAMETER_DATA;
typedef struct {
  PARAMETER_DATA SoftVerion;            //P0-00
	PARAMETER_DATA HardVerion;            //P0-01
	PARAMETER_DATA ParDefExe;             //P0-02
	PARAMETER_DATA SysReset;              //P0-03
	PARAMETER_DATA AlarmCodeSav1;         //P0-04
	PARAMETER_DATA AlarmCodeSav2;         //P0-05
	PARAMETER_DATA AlarmCodeSav3;         //P0-06
	PARAMETER_DATA AlarmCodeSav4;         //P0-07
	PARAMETER_DATA AlarmCodeSav5;         //P0-08
	
} PAR_Pn00;

typedef struct {
	PARAMETER_DATA ContrlMode;            //P1-00
	PARAMETER_DATA MotorDir;              //P1-01
	PARAMETER_DATA PulseMode;             //p1-02
	PARAMETER_DATA ContrlSource;          //P1-03
	PARAMETER_DATA ServoON;               //P1-04
	PARAMETER_DATA MotorType;             //P1-05
	PARAMETER_DATA N1;                    //P1-06
	PARAMETER_DATA N2;                    //P1-07
	PARAMETER_DATA N3;                    //P1-08
	PARAMETER_DATA N4;                    //P1-09
	PARAMETER_DATA M1;                    //P1-10
	PARAMETER_DATA PulseOut;              //P1-11
	PARAMETER_DATA MotorStopMode;         //P1-12
	PARAMETER_DATA HclOpenLoopMode;       //P1-13
	PARAMETER_DATA HclEnableSw1;         //P1-14
	PARAMETER_DATA HclEnableSw2;           //P1-15 硬件电流环使能开关/SDFM同步使能开关
	PARAMETER_DATA SpdMax;                //P1-16
	PARAMETER_DATA OpenDelaySw;           //P1-17
	PARAMETER_DATA UVWerrorIgore;         //P1-18
	PARAMETER_DATA TorqueLimitSw;         //P1-19
	PARAMETER_DATA TrArriveWorkMode;      //P1-20
	PARAMETER_DATA TempHighErrIgore;      //P1-21
	PARAMETER_DATA PosErrClsMode;         //P1-22
	PARAMETER_DATA CcwCwLimitMode;        //P1-23
	PARAMETER_DATA DIFilterTime;          //P1-24
	PARAMETER_DATA SpdSameMargin;         //P1-25
	PARAMETER_DATA PulseFilterTime;       //P1-26
	PARAMETER_DATA PosEkSw;               //P1-27
	PARAMETER_DATA AutoHomeFlag;          //P1-28
	PARAMETER_DATA HomeMode;              //P1-29
	PARAMETER_DATA HomeHighSpeed;         //P1-30
	PARAMETER_DATA HomeLowSpeed;          //P1-31
	PARAMETER_DATA HomeThirdSpeed;        //P1-32
	PARAMETER_DATA HomeZeroCircle;        //P1-33
	PARAMETER_DATA HomeZeroOffset;        //P1-34
	PARAMETER_DATA SonDelayTime;          //P1-35
	PARAMETER_DATA PosNearWidth;          //P1-36    
	PARAMETER_DATA CoinDelayTime;         //P1-37
	PARAMETER_DATA DI1Ctrl;               //P1-38
	PARAMETER_DATA DI2Ctrl;               //P1-39
	PARAMETER_DATA DI3Ctrl;               //P1-40
	PARAMETER_DATA DI4Ctrl;               //P1-41
	PARAMETER_DATA DI5Ctrl;               //P1-42	
	PARAMETER_DATA DI6Ctrl;               //P1-43
	PARAMETER_DATA DI7Ctrl;               //P1-44
	PARAMETER_DATA DI8Ctrl;               //P1-45
	PARAMETER_DATA DI9Ctrl;               //P1-46
	PARAMETER_DATA DO1Ctrl;               //P1-47
	PARAMETER_DATA DO2Ctrl;               //P1-48
	PARAMETER_DATA DO3Ctrl;               //P1-49
	PARAMETER_DATA DO4Ctrl;               //P1-50
	PARAMETER_DATA DO5Ctrl;               //P1-51
	PARAMETER_DATA ParaLock;              //P1-52
	PARAMETER_DATA RunTimeLimit;          //P1-53
	PARAMETER_DATA HomeNearWidth;         //P1-54
	PARAMETER_DATA HomeAccDecTime;        //P1-55
	PARAMETER_DATA HomeTrLimit;           //P1-56
	PARAMETER_DATA HomeTrArriveDelay;     //P1-57
	PARAMETER_DATA CurOverDelay;          //P1-58
	PARAMETER_DATA CurOverMax;            //P1-59
	PARAMETER_DATA RatedCurrent;          //P1-60
	PARAMETER_DATA CurSampleMax;          //P1-61
	PARAMETER_DATA LoadOverMax;           //P1-62
	PARAMETER_DATA LoadOverTime;          //P1-63
	PARAMETER_DATA DispItem;              //P1-64
} PAR_Pn01;

typedef struct {
	PARAMETER_DATA SpdKp;                 //P2-00
	PARAMETER_DATA SpdKi;                 //P2-01
	PARAMETER_DATA PosKp;                 //P2-02
	PARAMETER_DATA Inertia;               //P2-03
	PARAMETER_DATA SpdBefKp;              //P2-04
	PARAMETER_DATA SpdBefFilterTc;        //P2-05
	PARAMETER_DATA PosEkWarm;             //P2-06
	PARAMETER_DATA SpdKpdff;              //P2-07
	PARAMETER_DATA SpdKpChgValue;         //P2-08
	PARAMETER_DATA SpdKpChgK;             //P2-09
	PARAMETER_DATA SpdKi2;                //P2-10
	PARAMETER_DATA SpdKd;                 //P2-11
	PARAMETER_DATA SpdKiUseTime;          //P2-12
	PARAMETER_DATA CurKp;                 //P2-13
	PARAMETER_DATA CurKi;                 //P2-14
	PARAMETER_DATA CurBackFilterK;        //P2-15
	PARAMETER_DATA SpdBackFilterK;        //P2-16
	PARAMETER_DATA CurBefKp;              //P2-17
	PARAMETER_DATA CurBefFilterTc;        //P2-18
	PARAMETER_DATA SpeedSaveFlag;       //P2-19
	PARAMETER_DATA PidTypeSel;            //P2-20
	PARAMETER_DATA TorqueChgRef;          //P2-21
	PARAMETER_DATA PosErrChgRef;          //P2-22
	PARAMETER_DATA PosCmdFilterSw;        //P2-23
	PARAMETER_DATA PosCmdFilterK;         //P2-24
	PARAMETER_DATA SpdTimeType;           //P2-25
	PARAMETER_DATA SpdIncTime;            //P2-26
	PARAMETER_DATA SpdDecTime;            //P2-27
	PARAMETER_DATA GainChgTime1;          //P2-28
	PARAMETER_DATA BaseFreMax;            //P2-29
	PARAMETER_DATA TorqueLimintK;          //P2-30
	PARAMETER_DATA GainChgWaitTime1;      //P2-31
	PARAMETER_DATA GainChgWaitTime2;      //P2-32
	PARAMETER_DATA IsrFrequency;          //P2-33
	PARAMETER_DATA CM_CSPCmdIncErrCnt;    //P2-34 //CSP位置指令增量过大次数
	PARAMETER_DATA SpeedChgRef;           //P2-35
	PARAMETER_DATA PrIncTime;             //P2-36
	PARAMETER_DATA PrDecTime;             //P2-37
	PARAMETER_DATA MotorRunBrakeSpeedValue; //P2-38
	PARAMETER_DATA AbsaMutilSw;           //P2-39
	PARAMETER_DATA ZeroOffset;            //P2-40
	PARAMETER_DATA Pairs;                 //P2-41
	PARAMETER_DATA Torquek;               //P2-42
	PARAMETER_DATA PrRunMode;             //P2-43
	PARAMETER_DATA SdfmOsr;               //P2-44 SDFM过采样率
	PARAMETER_DATA NotchFilterFre1;       //P2-45
	PARAMETER_DATA NotchAttenu1;          //P2-46
	PARAMETER_DATA NotchFilterFre2;       //P2-47
	PARAMETER_DATA NotchAttenu2;          //P2-48
	PARAMETER_DATA OpposeFrequency1;      //P2-49
	PARAMETER_DATA OpposeFrequency2;      //P2-50
	PARAMETER_DATA IpmAlarmLogic;         //P2-51
	PARAMETER_DATA PowerOffErrorIgore;    //P2-52  16号报警屏蔽参数
	PARAMETER_DATA SpdPidOutLimit;        //P2-53
	PARAMETER_DATA CurPidOutLimit;        //P2-54
	PARAMETER_DATA OpenDelayTime;         //P2-55
	PARAMETER_DATA HoldDelayTime;         //P2-56
	PARAMETER_DATA AbsaCtrlCmd;           //P2-57
	PARAMETER_DATA AbsaTypeCmd;           //P2-58 
	PARAMETER_DATA SYNCPeriodRatio;       //P2-59
	PARAMETER_DATA VadcSampleSw;          //P2-60
	PARAMETER_DATA TmpSampleSw;           //P2-61
	PARAMETER_DATA HclSpdfdbSourceSel;     //P2-62
	PARAMETER_DATA RunLimitDir;           //P2-63
	PARAMETER_DATA AutoTimer1;            //P2-64
	PARAMETER_DATA SpdBackFilterChg1;     //P2-65
	PARAMETER_DATA HomeDelayTime;         //P2-66
	PARAMETER_DATA AbsaPzoutWidth;        //P2-67
	PARAMETER_DATA AbsaPulseNear;         //P2-68
	PARAMETER_DATA AbsaCrcErrCnt;         //P2-69
	PARAMETER_DATA CcwCwEnable;           //P2-70
	PARAMETER_DATA AdcSpdRefMax;          //P2-71
	PARAMETER_DATA AdcTurRefMax;          //P2-72
	PARAMETER_DATA AdcAutoOffset;         //P2-73
	PARAMETER_DATA AdcSpdOffset;          //P2-74
	PARAMETER_DATA AdcSpdFiltType;        //P2-75
	PARAMETER_DATA AdcSpdFiltTime;        //P2-76
	PARAMETER_DATA AutoTimer2;            //P2-77
	PARAMETER_DATA AdcSpdGain;            //P2-78
	PARAMETER_DATA AdcSpdPosGain;         //P2-79
	PARAMETER_DATA AdcSpdNegGain;         //P2-80
	PARAMETER_DATA AdcSpdZeroLimit;       //P2-81
	PARAMETER_DATA AdcCurOffset;          //P2-82
	PARAMETER_DATA AdcCurFiltType;        //P2-83
	PARAMETER_DATA AdcCurFiltTime;        //P2-84
	PARAMETER_DATA TorqueArrtimeRef;      //P2-85,扭矩到达滤波时间
	PARAMETER_DATA AdcCurGain;            //P2-86
	PARAMETER_DATA AdcCurPosGain;         //P2-87
	PARAMETER_DATA AdcCurNegGain;         //P2-88
	PARAMETER_DATA HCLPeriodRatio;       //P2-89
} PAR_Pn02;

typedef struct {
	PARAMETER_DATA CommSlaverNum;        //P3-00
	PARAMETER_DATA CommBaudRate;         //P3-01
	PARAMETER_DATA CommProtocol;         //P3-02
	PARAMETER_DATA Comm0Sel;             //P3-03 //串口0升级和波形打印选择
	PARAMETER_DATA Commt3_5msRef;        //P3-04
	PARAMETER_DATA Commt1_5msRef;        //P3-05
	PARAMETER_DATA CommReplyDelay;       //P3-06
} PAR_Pn03;

typedef struct {
	PARAMETER_DATA JogSpeed;             //P4-00
	PARAMETER_DATA OlSpeed;              //P4-01
	PARAMETER_DATA SrSpeed;              //P4-02
	PARAMETER_DATA OpenVol;              //P4-03
	PARAMETER_DATA OpenSpeed;            //P4-04
	PARAMETER_DATA SpdBackFilter1;       //P4-05
	PARAMETER_DATA SpdBackFilter2;       //P4-06
	PARAMETER_DATA PosTurLimit;          //P4-07
	PARAMETER_DATA TurLimitMinKp;        //P4-08
	PARAMETER_DATA TurLimit1;            //P4-09
	PARAMETER_DATA TurLimit2;            //P4-10
	PARAMETER_DATA TurLimit3;            //P4-11
	PARAMETER_DATA PosOffset1;           //P4-12
	PARAMETER_DATA PosCircle1;           //P4-13
	PARAMETER_DATA PosSpeedRef1;         //P4-14
	PARAMETER_DATA PosOffset2;           //P4-15
	PARAMETER_DATA PosCircle2;           //P4-16
	PARAMETER_DATA PosSpeedRef2;         //P4-17
	PARAMETER_DATA PosOffset3;           //P4-18
	PARAMETER_DATA PosCircle3;           //P4-19
	PARAMETER_DATA PosSpeedRef3;         //P4-20
	PARAMETER_DATA PosOffset4;           //P4-21
	PARAMETER_DATA PosCircle4;           //P4-22
	PARAMETER_DATA PosSpeedRef4;         //P4-23
	PARAMETER_DATA PosOffset5;           //P4-24
	PARAMETER_DATA PosCircle5;           //P4-25
	PARAMETER_DATA PosSpeedRef5;         //P4-26
	PARAMETER_DATA PosOffset6;           //P4-27
	PARAMETER_DATA PosCircle6;           //P4-28
	PARAMETER_DATA PosSpeedRef6;         //P4-29
	PARAMETER_DATA PosOffset7;           //P4-30
	PARAMETER_DATA PosCircle7;           //P4-31
	PARAMETER_DATA PosSpeedRef7;         //P4-32
	PARAMETER_DATA PosOffset8;           //P4-33
	PARAMETER_DATA PosCircle8;           //P4-34
	PARAMETER_DATA PosSpeedRef8;         //P4-35
	PARAMETER_DATA SpdPidKc;             //P4-36
	PARAMETER_DATA IqPidKc;              //P4-37
	PARAMETER_DATA IdPidKc;              //P4-38
	PARAMETER_DATA MotorBrakeMode;       //P4-39
	PARAMETER_DATA MotorBrakeVol;        //P4-40
	PARAMETER_DATA MotorBrakeFre;        //P4-41
	PARAMETER_DATA IgbtHighTmpDelayTime; //P4-42
	PARAMETER_DATA TrArriveTimeRef;      //P4-43
	PARAMETER_DATA SpeedRef1;            //P4-44
	PARAMETER_DATA SpeedRef2;            //P4-45
	PARAMETER_DATA SpeedRef3;            //P4-46
	PARAMETER_DATA SpeedRef4;            //P4-47
	PARAMETER_DATA SpeedRef5;            //P4-48
	PARAMETER_DATA SpeedRef6;            //P4-49
	PARAMETER_DATA SpeedRef7;            //P4-50
	PARAMETER_DATA MainPowerHighVale;    //P4-51
	PARAMETER_DATA MainPowerLowVale;     //P4-52
    PARAMETER_DATA MainPowerHighDelayTime;  //P4-53
	PARAMETER_DATA MainPowerLowDelayTime;   //P4-54
	PARAMETER_DATA MainPowerBarkeDelayTime; //P4-55
	PARAMETER_DATA MainPowerOffDelayTime;   //P4-56
	PARAMETER_DATA HighVolRef;              //P4-57
	PARAMETER_DATA DeadVolValue;            //P4-58
	PARAMETER_DATA DeadTime;                //P4-59
	PARAMETER_DATA PosExecCicleTiem;        //P4-60   
	PARAMETER_DATA SpdExecCicleTiem;        //P4-61
	PARAMETER_DATA AbsaZeroVolRef;          //P4-62
} PAR_Pn04;

typedef struct {
	uint16_t PositionDatah;
	uint16_t PositionDatal;
	uint16_t SpeedDatah;
	uint16_t SpeedDatal;
	uint16_t TorqueDatah;
	uint16_t TorqueDatal;
	uint16_t IoInputData1;
	uint16_t IoInputData2;
	uint16_t IoInputData3;
	uint16_t IoInputData4;
	uint16_t IoInputData5;
	uint16_t IoInputData6;
	uint16_t IoInputData7;
	uint16_t IoInputData8;
	uint16_t IoInputData9;
} SERVO_COMM;
typedef struct {
	int32_t COMM_SON;   //伺服使能位
	int32_t Object6040_ContrlWord;
	int32_t Object6060_ContrlMode;
	int32_t Object607A_PostionTarget;
	int32_t Object60FF_SpeedTarget;
	int32_t Object6071_TorqueTarget;
	int32_t Object607D_SoftMinPostionLimit;
	int32_t Object607D_SoftMaxPostionLimit;
	int32_t Object6065_PosEkWarm;
	int32_t Object6066_PosEkTime;
	int32_t Object6067_PosNearWidth;
	int32_t Object6068_CoinDelayTime;
	int32_t Object606D_SpdSameMargin;
	int32_t Object606E_SpdSameMarginTime;
	int32_t Object606F_SpdZeroLimit;
	int32_t Object6070_SpdZeroLimitTime;
	int32_t Object6080_SpeedMax;
	int32_t Object6073_CurrentMax;
	int32_t Object6075_RatedCurrent;
	int32_t Object6071_TargetTorque;
	int32_t Object6072_TorqueMax;
	int32_t Object6076_RatedTorque;
	int32_t Object605D_MotorStopMode;
	int32_t Object607E_MotorDir;
	int32_t Object6083_SpdIncTime;
	int32_t Object6084_SpdDecTime;
	int32_t Object607C_HomeOffset;
	int32_t Object607F_SpeedProfileMax;
	int32_t Object6080_MaxMotorSpeed;
	int32_t Object6081_RSV;
	int32_t Object6085_MotorEmgs;
	int32_t Object6082_Speedinit;
	int32_t Object6091_Numerator;
	int32_t Object6091_Denominator;
	int32_t Object6098_HomeMode;
	int32_t Object6099_HomeSpeed;
	int32_t Object6041_StateWord;
	int32_t Object603F_ErrCode;
	int32_t Object6062_CommandReal;
	int32_t Object6064_PostionReal;
	int32_t Object606C_SpeedReal;
	int32_t Object6078_CurrentReal;
	int32_t Object6077_TorqueReal;
	int32_t Object6081_PorifSpeed;
	int32_t Object6079_VdcInputVol;
	int32_t Object60FD_InPortState;
	int32_t Object60FE_OutPortState;
	int32_t Object6061_RealMode;
	int32_t Object3601_AbsaSingleData;
	int32_t Object3602_AbsaCircleData;
	int32_t Object3603_AbsaAxisData;
	int32_t Object3604_CmdRef;
	int32_t Object3605_PosErr;
	int32_t Object3606_MotorSpd;
	int32_t Object3607_MotorCur;
	int32_t Object3608_VdcInputVol;
	int32_t Object3609_RunState;
	int32_t Object360A_ErrCode;
	int32_t Object360B_HomePosition;
	int32_t Object360C_SoftMinPostionLimit;
	int32_t Object360D_SoftMaxPostionLimit;
} SERVO_PDO;

typedef struct {
	PAR_Pn00 Pn00;
	PAR_Pn01 Pn01;
	PAR_Pn02 Pn02;
	PAR_Pn03 Pn03;
	PAR_Pn04 Pn04;

} SERVO_PAR;

typedef struct  {
  int16_t ParNum;
	int16_t Data;
}PARAMETER_DEF_DATA;

typedef struct
{  
	  PARAMETER_DEF_DATA Pn01_05;
	  PARAMETER_DEF_DATA Pn01_16;
	  PARAMETER_DEF_DATA Pn01_59;
	  PARAMETER_DEF_DATA Pn01_60;
	  PARAMETER_DEF_DATA Pn01_61;
	  PARAMETER_DEF_DATA Pn02_00;
	  PARAMETER_DEF_DATA Pn02_01;
	  PARAMETER_DEF_DATA Pn02_02;
	  PARAMETER_DEF_DATA Pn02_10;
	  PARAMETER_DEF_DATA Pn02_12;
	  PARAMETER_DEF_DATA Pn02_13;
	  PARAMETER_DEF_DATA Pn02_14;
	  PARAMETER_DEF_DATA Pn02_15;
	  PARAMETER_DEF_DATA Pn02_16;
	  PARAMETER_DEF_DATA Pn02_20;
	  PARAMETER_DEF_DATA Pn02_26;
	  PARAMETER_DEF_DATA Pn02_27;
	  PARAMETER_DEF_DATA Pn02_29;
	  PARAMETER_DEF_DATA Pn02_30;
	  PARAMETER_DEF_DATA Pn02_42;
	  PARAMETER_DEF_DATA Pn02_40;
	  PARAMETER_DEF_DATA Pn02_41;
	  PARAMETER_DEF_DATA Pn02_51;
	  PARAMETER_DEF_DATA Pn02_52;
	  PARAMETER_DEF_DATA Pn02_53;
	  PARAMETER_DEF_DATA Pn02_54;
	  PARAMETER_DEF_DATA Pn02_60;
	  PARAMETER_DEF_DATA Pn02_61;
	  PARAMETER_DEF_DATA Pn02_62;
}SERVO_DEFAULT;

typedef struct {
		int32_t SpeedHighFlag;                   //1号报警overspeed_flag
		int32_t MainPowerHighFlag;               //2号报警ov_flag
		int32_t MainPowerLowFlag;                //3号报警lv_flag
		int32_t PosEkOverErrorFlag;              //4号报警overpos_e_flag
		int32_t PosEkOverAlarmFlag;              //位置超差警告overpos_alarm_flag
		int32_t CcwlCwlErrFlag;                  //7号报警 ccwl_cwl_err_flag
		int32_t ccwl_flag;
		int32_t cwl_flag;
		int32_t EncodeOffFlag;                   //9号报警code_error9
		int32_t IpmAlarmFlag;                    //11号报警fo_flag
		int32_t CurOverFlag;                      //12号报警i_alm_flag
		int32_t LoadOverFlag;                    //32报警,电流二级报警	  
		int32_t AbsaPosAlarmFlag;                //13号报警absa_pos_alm_flag
		int32_t BrakeAlarmFlag;                  //14号报警brake_flag
		int32_t MotorPairErrFlag;                //15号报警pair_err
		int32_t maniPower0ffFlag;                //16号报警mani_circle_off_alm
		int32_t MotorTypeErrFlag;                //18报警code_type
		int32_t MotorEmgsAlarmFlag;              //20号报警		
		int32_t MainPowerHighPs;                 //int32_t mani_circle_high_ps=0;
		int32_t BrakeAlarmPs;                    //mani_circle_brake_ps=0;
		int32_t maniPower0ffPs;                  //mani_circle_off_time=10000;
        int32_t MainPowerLowPs;
        int32_t TempHighPs;
        int32_t TempHighCnt;
        int32_t TempHighFlag;
		int32_t MainPowerHighCnt;                //ov_alm_delay
		int32_t MainPowerLowCnt;                 //lv_alm_delay
		int32_t PosEkOverAlarmCnt;               //overpos_alarm_cnt
		int32_t EncodeOffCnt;                    //absa_crc_err_cnt
		int32_t IpmAlarmCnt;                     //IPM_alm_delayi
		int32_t BrakeAlarmCnt;                   //brake_alm_delay
		int32_t ErrAlarmSave;                    //err_alm_save=0;
		int32_t ErrAlarmSaveEn;                  //err_alm_saveEn=1;
		int32_t MotorCcwCwLimitFlag;             //MotorCcwCwLimitFlag = 0;
		int32_t KaZhiAlarmFlag;                  //KAZHI_alarm_flag = 0;
		int32_t PaperStopFlag;                   //PaperStopFlag = 0; //卡纸标志位，发送回上位机
		int32_t ServoAlarmFlag;                  //伺服报警serr_alm_flag
		int32_t ServoAlarmCansel;                //伺服报警时返回上一级菜单alm_cansel_flag,初始值为1
		int32_t CpldBusErrFlag;
		int32_t ServoHomeErrFlag;
		int32_t MotorUVWErrorFlag;
		int32_t MotorUVWErrorCnt;
		int32_t MotorUVWErrorCnt2;
		int32_t MotorUVWErrorCnt3;
		int32_t MotorUVWErrorEn1;
		int32_t MotorUVWErrorEn2;
		int32_t MotorUVWErrorEn3;
		int32_t MotorRunMaxCur;
        int32_t E2promReadErrFlag;
		int32_t TrArriveErrFlag;
		int32_t AbsaOverHeatFlag;
		int32_t AbsaOverHeatCnt;
		int32_t AbsaBatteryOffFlag;
		int32_t AbsaBatteryLowFlag;
		int32_t AbsaCrcErrFlag;
		int32_t AbsaBatteryOffCnt;
		int32_t AbsaBatteryLowCnt;
		int32_t MainCurRefErrFlag;
		int32_t absa_crc_err_flag;
		int32_t CM_CSPCmdIncErrflag;
		int32_t SdfmOverFlag;
		int32_t EncoderTypeErrFlag;
} SERVO_ERR;

typedef struct{
        uint16_t  CarFreq;            //输出 载波频率,Hz
        uint16_t  ToqFreq;            //输出 转矩环的调节频率,单位Hz  FUN->MTR
        uint16_t  SpdFreq;            //输出 速度环的调节频率,单位Hz  FUN->MTR
        uint16_t  PosFreq;            //输出 位置环的调节频率,单位Hz  等价于 STR_FUNC_Gvar.PosLoopFreq
        uint64_t  RPM2PPPtCoefQ16;    //用于将rpm表示的转速换算到以脉冲每位置环周期(PPPt)为单位的系数
        uint64_t  ExRPM2PPPtCoefQ16;  //用于将rpm表示的转速换算到以脉冲每位置环周期(PPPt)为单位的系数(外环)
         int32_t  EpwmInvPeriod;
         uint16_t ZeroOffset;
}STR_FUNC_SYSTEM;

typedef struct{
    STR_FUNC_SYSTEM         System;                 //FUNC_System 中调度频率和周期变量结构体
}STR_FUNC_GLOBALVARIABLE;
typedef struct {
	    int16_t  Hcl_EnableSw;          //硬件电流环使能开关
	    int16_t  Sdfm_sync_EnableSw;    //SDFM与EPWM同步使能开关
		int16_t  ElecComp_EnableSw;     //电角度补偿使能开关
	    int16_t  DeadComp_EnableSw;     //死区补偿开关
	    int16_t  OverMode2_EnableSw;    //过调制2区使能开关
	    int16_t  VoltCompEnableSw;      //电压补偿开关
	    int16_t  ElecVolCompEnableSw;   //反电动势补偿开关
	    int16_t  SdfmFromRegSw;         //转矩前馈开关
}HCL_SWITCH;
typedef struct {
        int32_t PosFrqLow;                     //pos_cmd_frq_low
	    int32_t PosFrqHigh;                    //pos_cmd_frq_high
        int32_t CmdRefLow;                     //contrl_cmd_frq_low
		int32_t CmdRefHigh;                    //contrl_cmd_frq_high
		int32_t PosErrLow;                     //pos_err_low
		int32_t PosErrHigh;                    //pos_err_high
		int32_t MotorSpd;                      //dp_parameter1_spd
		int32_t MotorSpdSum;                   //Fn.MotorSpd_sum
		int32_t SpdVolRef;                     //_int32_t_spd_vol_ref
		int32_t SpdRpmRef;                     //_int32_t_spd_rpm_ref
		int32_t CurVolRef;                     //_int32_t_i_vol_ref
		int32_t CurAlarmRef;                   //i_alm_1;
	    int32_t TorqueFdb;
		int32_t ThetaIncLow;                   //theta_inc_low;
		int32_t ThetaIncHigh;                  //theta_inc_high
		int32_t ServoAlarmSum;                 //MotorAlarmSum
		int32_t IndexSumPosFrq;
		int32_t IndexSumPosEnable;
		int32_t ImeasAd0Ref;
		int32_t ImeasAd1Ref;
		int32_t UserTimeSum;
		int32_t VdcInputVol;
}SERVO_FN;
typedef struct {
		int32_t DI_SON;        //  1 伺服启动
		int32_t DI_ALRS;       //  2 异常报警清除
		int32_t DI_SHOLD;      //  3 内部速度命令暂停
		int32_t DI_CCWL;       //  4 CCW方向驱动禁止
		int32_t DI_CWL;        //  5 CW方向驱动禁止
		int32_t DI_RIL;        //  6 CCW外部转矩限制
		int32_t DI_FIL;        //  7 CW外部转矩限制
		int32_t DI_CLR;        //  8 脉冲误差量清除
		int32_t DI_LOK;        //  9 零速嵌位
		int32_t DI_SPD1;       //  10 内部速度命令选择1
		int32_t DI_SPD2;       //  11 内部速度命令选择2
		int32_t DI_SPD3;       //  12 内部速度命令选择3
		int32_t DI_MDC;        //  13 控制模式切换
		int32_t DI_INH;        //  14 位置命令禁止
		int32_t DI_SPDINV;     //  15 速度命令反向
		int32_t DI_G_SEL;      //  16 增益切换
		int32_t DI_GN1;        //  17 电子齿轮比分子选择1
		int32_t DI_GN2;        //  18 电子齿轮比分子选择2
		int32_t DI_PTRG ;      //  19 内部位置命令触发
		int32_t DI_PHOLD;      //  20 内部位置命令暂停
		int32_t DI_SHOME;      //  21 开始回到原点
		int32_t DI_ORG1;       //  22 外部参考点1
		int32_t DI_ORG2;       //  23 外部参考点2
		int32_t DI_POS1;       //  24 内部位置命令选择1
		int32_t DI_POS2;       //  25 内部位置命令选择2
		int32_t DI_POS3;       //  26 内部位置命令选择3
		int32_t DI_POS4;       //  27 内部位置命令选择4
		int32_t DI_TRQINV;     //  28 转矩命令反向
		int32_t DI_RS1;        //  29 转矩命令正向选择
		int32_t DI_RS2;        //  30 转矩命令反向选择
		int32_t DI_EMC;        //  31 紧急停止
		int32_t DI_PAUTO;      //  32 内部位置命令自动运行循环启动
		int32_t DI_SPD_CW;     //  33
		int32_t DI_SPD_CCW;    //  34
		int32_t DI_GN3;        //  35 电子齿轮比分子选择2
		int32_t DI_GN4;        //  36 电子齿轮比分子选择2
		int32_t MDP0;          //  37
		int32_t MD0;           //  38
		int32_t MD1;           //  39
		int32_t DI_SetAxis;    //  40
} SERVO_DI;

typedef struct {
	    int32_t SRDY;          //  1 准备好
	    int32_t ALARM;         //  2 伺服报警
	    int32_t ZSPD;          //  3 位置到达
	    int32_t SSPD;          //  4 速度到达
        int32_t TSPD;          //  5 扭矩到达
        int32_t BRKR;          //  6 抱闸
	    int32_t HOME;          //  7 回零完成
	    int32_t CZ;            //  8 Z脉冲
        int32_t RELAY;         //  9 电磁阀
        int32_t BatteryLow;    //  10 电池低压
}SERVO_DO;
#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_GVAR_DEF_H_ */
