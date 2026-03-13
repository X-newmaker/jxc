/*
 * esc_csp.c
 *
 *  Created on: 2025年2月8日
 *      Author: L
 */

#include "all_inc.h"
#include "M680x_it.h"


#include "applInterface.h"
#include "aic_ecat_cfg.h"
#include "coeappl.h"
#include "ecat_def.h"
#include "cia402appl.h"
extern TCiA402Axis       LocalAxes[MAX_AXES];
STR_ECTCSPVAR STR_ECTCSPVar = {4,1000,262140,1048576,0,0,0,0,0,0,0,0,3,0,0}; //
static int32_t preInterpltPoint =0;//上次插补位置，用来求位置变化量--指令单位
STR_ECTCSPPOSREF                 STR_ECTCSPPosRef;
STR_ACC_FACTOR                   STR_Acc_Factor;
STR_VELOCITYENCODER_FACTOR       STR_VelEnc_Factor;
STR_VELOCITY_FACTOR              STR_Vel_Factor;
STR_POSITION_FACTOR              STR_Pos_Factor;
STR_POSITION_FACTOR_INVERSE      STR_Pos_Factor_Inverse;
STR_FUNC_GLOBALVARIABLE          STR_FUNC_Gvar;
uint16_t ExcCnt = 0;

int64_t CSPPosRef(STR_ECTCSPPOSREF *p,int64_t CmdInput);
void CSPClear(void);
void preInterpltPointUpdata(void);

/*******************************************************************************
  函数名: void InitECTCSP(void)

  输入:   无
  输出:   无
  子函数:无
  描述:  插补模式下,初始化插补变量清零
********************************************************************************/
void InitECTCSP(void)
{
	STR_ECTCSPVar.SYNCPeriodRatio= Servo.Pn02.SYNCPeriodRatio.Data;//默认值500us对应1个位置环周期
	CSPClear();
	preInterpltPointUpdata();
}

/*******************************************************************************
  函数名: void ECTCSPUpdata(void)

  输入:
  输出:
  子函数:无
  描述:
********************************************************************************/
void ECTCSPUpdata(void)
{
	preInterpltPointUpdata();
    //CSPClear();
}
/*******************************************************************************
  函数名: void CANopenFactorUpdate(void)
  输入:   无
  输出:
  子函数: 无
  描述:   转换因子实时更新
********************************************************************************/
void FactorUpdate(void)
{
    //6091只更新值，不进行计算，在计算驱动器位置指令处，要进行余数运算，以保证位置指令精度
	//6091h：position factor，指令单位/s-->p
    STR_Pos_Factor.PosFactor6091_Numerator           = ExternSerovN;
    STR_Pos_Factor.PosFactor6091_Denominator         = ExternSerovM;

    STR_Pos_Factor_Inverse.PosFactor6091_Numerator   = ExternSerovN;
    STR_Pos_Factor_Inverse.PosFactor6091_Denominator = ExternSerovM;

    //Vel_VelEncoder6094Q12：Velocity encoder factor，指令单位/s-->p/s 转化成驱动器速度指令---速度控制 10000*rpm
    STR_VelEnc_Factor.VelEncoder6094_Numerator = ExternSerovN;
    STR_VelEnc_Factor.VelEncoder6094_Denominator = ExternSerovM;

    //6095h：Velocity factor 1，rpm-->user velocity unit
    //6095_Inverse:6095倒数，user velocity unit-->rpm
    STR_Vel_Factor.VelFactor6095_Numerator = ExternSerovN;
    STR_Vel_Factor.VelFactor6095_Denominator = ExternSerovM;


    //Vel_AccFactor6097Q14：Acceleration factor，user acceleration unit--p/s2 转化成驱动器每个控制周期的速度指令增量--速度控制 10000*rpm
    STR_Acc_Factor.AccFactor6097_Numerator = ExternSerovN;
    STR_Acc_Factor.AccFactor6097_Denominator = ExternSerovM;


}
/*******************************************************************************
  函数名:  uint64_t UserAccUnit2Incps2Unit(STR_ACC_FACTOR *accFactor,Uint32 accInput)
  输入:    STR_Factors.Pos_AccFactor6097Q14;
  参数：
  输出:    Result
  描述:    将用户加速度单位转化成驱动器单位:p/位置环控制周期  Q16      6097
********************************************************************************/
uint64_t UserAccUnit2Incps2Unit(STR_ACC_FACTOR *accFactor,uint32_t accInput)
{
	uint64_t  ResultQ16 = 0;
	uint64_t  Temp = 0;
	uint64_t Temp111 = 0;

    if (accFactor->AccFactor6097_Denominator == 0)	  //当分母为零时退出该程序，返回的位置指令为零
    {
        return 0;
    }
    accFactor->InPut = accInput;

    //为保证精度，必须调整计算顺序
	// 计算电机最大速度对应的每s插补周期脉冲个数 Q16

	Temp = (uint64_t)int_speed_max * STR_FUNC_Gvar.System.RPM2PPPtCoefQ16;
    Temp = Temp>> 16;
    Temp = Temp *(uint64_t)STR_FUNC_Gvar.System.PosFreq * STR_FUNC_Gvar.System.PosFreq;
    Temp111 = (uint64_t)accFactor->InPut * (uint64_t)accFactor->AccFactor6097_Numerator/(uint64_t)accFactor->AccFactor6097_Denominator;
    if(Temp111>Temp)Temp111 = Temp;

    Temp = (uint64_t)STR_FUNC_Gvar.System.PosFreq * STR_FUNC_Gvar.System.PosFreq;
    ResultQ16 = (Temp111<<10)/Temp;
    ResultQ16 = ResultQ16<<6;
    if(ResultQ16==0)ResultQ16 =1;//一个位置环至少一个脉冲，因此齿轮比为1时，对应的6083最小值为16000000

    return ResultQ16;
}

/*******************************************************************************
  函数名:  Uint64 UserAccUnit2Rpmps2Unit(STR_FACTORS *accFactor,Uint32 accInput)
  输入:    STR_Factors.Vel_AccFactor6097Q14;
  参数：
  输出:    ResultQ10
  描述:    将用户加速度单位转化成驱动器速度控制中的加速度单位:10000*rpm/速度环周期 Q10 6097
********************************************************************************/
uint64_t UserAccUnit2Rpmps2Unit(STR_ACC_FACTOR *accFactor,uint32_t accInput)
{
	uint64_t  ResultQ10 = 0;
	uint64_t  Temp = 0;
//    Uint64 Temp111 = 0;
	uint64_t MaxSpdDelta = 0;

    if (accFactor->AccFactor6097_Denominator == 0)	  //当分母为零时退出该程序，返回的位置指令为零
    {
        return 0;
    }
    accFactor->InPut = accInput;

    if(accFactor->InPut==0)accFactor->InPut = 1;

    MaxSpdDelta = (uint64_t)int_speed_max * 10000L * EncodeLine<<1;

    Temp = (60L * 10000L<<1)/STR_FUNC_Gvar.System.SpdFreq;
    Temp = Temp * (uint64_t)accFactor->AccFactor6097_Numerator/(uint64_t)accFactor->AccFactor6097_Denominator;//31457280~7

    Temp = Temp * (uint64_t)accFactor->InPut;
    //为了保证精度，必须扩大到2^16，以兼容23位编码器

    if(Temp>MaxSpdDelta)Temp = MaxSpdDelta;
    Temp = Temp<<15;
    ResultQ10 = Temp/(uint64_t)EncodeLine;
    if(ResultQ10==0)ResultQ10=1;

    return ResultQ10;
}
/*******************************************************************************
  函数名:   int32 UserVelUnit2RpmUnit(STR_VELOCITYENCODER_FACTOR *velFactor,int64 velInput)
  输入:
            STR_Vel_Factor_Vel.InPut;
            STR_Vel_Factor_Vel.VelEncoder6094_Numerator
            STR_Vel_Factor_Vel.VelEncoder6094_Denominator
  参数：
  输出:    Result
  描述:    将用户速度单位转化成驱动器速度单位:rpm*10000         6094
********************************************************************************/
int32_t UserVelUnit2RpmUnit(STR_VELOCITYENCODER_FACTOR *velFactor,int64_t velInput)
{
    int64  Result = 0;
    int32_t Temp111 = 0;

    if (velFactor->VelEncoder6094_Denominator == 0)	  //当分母为零时退出该程序，返回的位置指令为零
    {
        return 0;
    }

    velFactor->InPut = velInput;

    velFactor->VelEncoder6094Q20 =(int64_t)(((((uint64_t)60 * 10000L << 20) / EncodeLine) *
		                                    (int64_t)velFactor->VelEncoder6094_Numerator) /
		                                    (int64_t)velFactor->VelEncoder6094_Denominator);

    Result = velFactor->InPut * velFactor->VelEncoder6094Q20 >> 20;

    Temp111 = (int32_t)int_speed_max * 10000L;

    if(Result>Temp111)Result = Temp111;
    else
    {
        Temp111 = - Temp111;
        if(Result < Temp111)Result = Temp111;
    }

    return (int32_t)Result;
}
/*******************************************************************************
  函数名:   int64 UserVelUnit2IncpsUnit(STR_VELOCITYENCODER_FACTOR *velFactor,Uint32 velInput)
  输入:     STR_Vel_Factor_Pos.InPut;
            STR_Vel_Factor_Pos.VelEncoder6094_Numerator
            STR_Vel_Factor_Pos.VelEncoder6094_Denominator

  参数：
  输出:    Result
  描述:    将用户速度指令单位转化成驱动器位置指令单位:p/位置环控制周期  6094
********************************************************************************/
int64 UserVelUnit2IncpsUnit(STR_VELOCITYENCODER_FACTOR *velFactor,uint32_t velInput)
{
    int64_t  ResultQ16 = 0;
//    Uint64 Temp111 = 0;

    if (velFactor->VelEncoder6094_Denominator == 0)	  //当分母为零时退出该程序，返回的位置指令为零
    {
        return 0;
    }
    velFactor->InPut = velInput;

    //为保证精度，必须调整计算顺序
    ResultQ16 = (((uint64_t)velFactor->InPut<<12)/(uint64_t)STR_FUNC_Gvar.System.PosFreq)
                * (uint64_t)velFactor->VelEncoder6094_Numerator
                /(uint64_t)velFactor->VelEncoder6094_Denominator;

    ResultQ16 = ResultQ16<<4;

    return ResultQ16;
}
/*******************************************************************************
  函数名:  int32 Rpm2UserVel(STR_VELOCITY_FACTOR *velFactor,int32 velInput)
  输入:    STR_Pos_Factor.InPut;                    //位置因子前输入量
           STR_Pos_Factor.PosRemainder;            //位置因子计算余数
           STR_Pos_Factor.PosFactor6091_Numerator;
           STR_Pos_Factor.PosFactor6091_Denominator;
  参数：
  输出:    Result
  描述:    将驱动器速度单位(rpm)转化成用户速度单位,只在反馈的时候用   6095
********************************************************************************/
int32_t Rpm2UserVel(STR_VELOCITY_FACTOR *velFactor,int32_t velInput)
{
    int32_t  Result    = 0;
    int32_t Temp111 = 0;


    if (velFactor->VelFactor6095_Denominator == 0)	  //当分母为零时退出该程序，返回的速度为零
    {
        return 0;
    }

	velFactor->VelFactor6095Q14 =(uint64_t)velFactor->VelFactor6095_Numerator * (((uint64_t)EncodeLine << 14)/(uint64_t)60L)
								 /((uint64_t)velFactor->VelFactor6095_Denominator);

	//接收输入指令
    velFactor->InPut = velInput;

    //计算用户速度反馈
    Result =(int32_t)((int64)velFactor->InPut * velFactor->VelFactor6095Q14 >> 14);

    return Result;
}

/*******************************************************************************
  函数名:  int64 UserPosUnit2IncpUnit(STR_POSITION_FACTOR *posFactor,int32 posInput)
  输入:    STR_Pos_Factor.InPut;                    //位置因子前输入量
  参数：
  输出:    Result
  描述:    将用户位置转化成驱动器目标位置     6091
********************************************************************************/
int64_t UserPosUnit2IncpUnit(STR_POSITION_FACTOR *posFactor,int32_t posInput)
{
	int64_t  Sum    = 0; //位置指令计算中间变量
	int64_t  Result = 0;
	int64_t  Temp   = 0;

    if (posFactor->PosFactor6091_Denominator == 0)	  //当分母为零时退出该程序，返回的位置指令为零
    {
        return 0;
    }

	//接收输入指令
    posFactor->InPut = posInput;

    /*计算放大后的位置指令加上上次计算的余数*/
    Sum = ((int64_t)posFactor->InPut) * ((int64_t)posFactor->PosFactor6091_Numerator);
    Sum += (int64_t)posFactor->PosRemainder;

    /*计算乘以位置转换因子后的位置指令*/
    Result = (Sum / posFactor->PosFactor6091_Denominator);

    /*计算余数*/
    Temp = Result * posFactor->PosFactor6091_Denominator;
    posFactor->PosRemainder = Sum - Temp;

    return Result;
}

/*******************************************************************************
  函数名:  int32 IncpUnit2UserPosUnit(STR_POSITION_FACTOR_INVERSE *posFactor,int32 posInput)
  输入:    STR_Pos_Factor_Inverse.InPut;                    //位置因子前输入量
  参数：
  输出:    Result
  描述:    将驱动器位置转化为用户位置，仅在位置显示用    1/6091
********************************************************************************/
int32_t IncpUnit2UserPosUnit(STR_POSITION_FACTOR_INVERSE *posFactorinverse,int64_t posInput)
{
	int32_t  Result    = 0;
	int64_t Temp111 = 0;

    if(posFactorinverse->PosFactor6091_Numerator == 0)   //当分子为零时退出该程序，返回的位置指令为零
    {
        return 0;
    }

	//接收输入指令
    posFactorinverse->InPut = posInput;

	Temp111 = (int64)posFactorinverse->InPut * posFactorinverse->PosFactor6091_Denominator;

	Temp111 = Temp111 / posFactorinverse->PosFactor6091_Numerator;

	Result  = (int32_t)Temp111;

    return Result;
}
/*******************************************************************************
  函数名: void ECTCSPMaxSpeedUpdate(void)

  输入:
  输出:
  子函数:无
  描述:  CSP最大限速计算
********************************************************************************/
void ECTCSPMaxSpeedUpdate(void)
{
	int32_t MotorMaxSpeed =0;
	int64_t  Temp = 0;
    //速度限制
    MotorMaxSpeed = Rpm2UserVel(&STR_Vel_Factor,(int32_t)int_speed_max);//最大的速度对应的(p/s)
    STR_ECTCSPVar.MaxInterpltPosCmd = (UserVelUnit2IncpsUnit(&STR_VelEnc_Factor,MotorMaxSpeed))>>16;//位置环周期对应的最大脉冲增量值
	Temp = STR_ECTCSPVar.MaxInterpltPosCmd + (STR_ECTCSPVar.MaxInterpltPosCmd / 50);  //最大速度判断留点余量
	STR_ECTCSPVar.MaxDeltaTarPos = 	Temp * (int64_t)STR_ECTCSPVar.SYNCPeriodRatio;    //通讯周期对应的最大脉冲增量值

}


/*******************************************************************************
  函数名: void preInterpltPointUpdata(void)

  输入:
  输出:
  子函数:无
  描述:  计算初始插补位置-指令单位
********************************************************************************/
void preInterpltPointUpdata(void)
{
    int64_t PosTemp = 0;
    PosTemp = motor_position.actual_position_cur;
	preInterpltPoint = IncpUnit2UserPosUnit(&STR_Pos_Factor_Inverse,PosTemp);

}

/*******************************************************************************
  函数名: WriteCSPFIFO(void)
  输入:
  输出:   无
  子函数:无
  描述:  中断写入插补数据
********************************************************************************/
void WriteCSPFIFO(int32_t CSP_TargetPos)
{
    int64_t Temp64 = 0;
	if(STR_ECTCSPVar.CSPRunFlag == 0)
	{
		ECTCSPUpdata();
		STR_ECTCSPVar.LatchPos = preInterpltPoint;
		STR_ECTCSPVar.CSPRunFlag = 1;
	}

	STR_ECTCSPVar.TargetPos = CSP_TargetPos;        //主站发送给从的目标位置
	STR_ECTCSPVar.InterpltPoint = CSP_TargetPos;
    Temp64 = (int32_t)(STR_ECTCSPVar.TargetPos - STR_ECTCSPVar.LatchPos);//计算前后两次位置增量
    STR_ECTCSPVar.LatchPos = STR_ECTCSPVar.TargetPos;
	Temp64 = Temp64 * (int64_t)STR_Pos_Factor.PosFactor6091_Numerator / (int64_t)STR_Pos_Factor.PosFactor6091_Denominator;

	if((ABS(Temp64) >= STR_ECTCSPVar.MaxDeltaTarPos))//判断CSP位置指令增量是否过大
	{
		STR_ECTCSPVar.P_overspeedcnt++;
		if(STR_ECTCSPVar.P_overspeedcnt >= Servo.Pn02.CM_CSPCmdIncErrCnt.Data)//CSP位置指令增量过大次数
		{
			STR_ECTCSPVar.P_overspeedcnt = Servo.Pn02.CM_CSPCmdIncErrCnt.Data;
			Err.CM_CSPCmdIncErrflag = 1;
			Err.ServoAlarmFlag = 1;
		}
	}
	else
	{
		STR_ECTCSPVar.P_overspeedcnt = 0;
	}
}
/*******************************************************************************
  函数名: CSPPointCal(void)

  输入:
  输出:   无
  子函数:无
  描述:  计算位置指令增量-编码器单位 ，同时在指令端进行软件位置限制判断
********************************************************************************/
void CSPPointCal(void)
{
    int32_t userDeltPos=0;
    int32_t temp=0;

    userDeltPos = STR_ECTCSPVar.InterpltPoint;
    temp = userDeltPos - preInterpltPoint;
	STR_ECTCSPVar.InterpltDltRef = UserPosUnit2IncpUnit(&STR_Pos_Factor,temp);
    preInterpltPoint = userDeltPos;

}
/*******************************************************************************
  函数名:  int32_t ECTCSPPosCmd(void)
  输入:
  参数：
  输出:
  描述:    完成插补计算，输出位置指令，调度应该在位置环
********************************************************************************/
int32_t ECTCSPPosCmd(void)
{
    STR_ECTCSPPOSREF *pInterplt = &STR_ECTCSPPosRef;
    TCiA402Axis *pCiA402Axis;
	int32_t  MaxInterpltPos=0;
	int32_t temp3 = 0;
	pCiA402Axis = &LocalAxes[0];
    //if((DeviceControlVar.OEMStatus != STATUS_OPERENABLE) || (STR_FUNC_Gvar.MonitorFlag.bit.ESMState!=1))
	if((pCiA402Axis->i16State & STATE_OPERATION_ENABLED) != STATE_OPERATION_ENABLED)
    {
        //ip mode inactive
        CSPClear();
        //drive follow the command value
        //ObjectDictionaryStandard.DeviceControl.StatusWord.bit.OperationModeSpecific1 = 0;
        pCiA402Axis->Objects.objStatusWord &= ~STATUSWORD_MANUFACTORSPECIFIC;
        return 0;
    }

    //ObjectDictionaryStandard.DeviceControl.StatusWord.bit.OperationModeSpecific1 = 1;//drive follow the command value
    pCiA402Axis->Objects.objStatusWord |= STATUSWORD_MANUFACTORSPECIFIC;
    if(STR_ECTCSPVar.CSPRunFlag == 1)
    {
        if(ExcCnt >1)
        {
            ExcCnt--;
            temp3 = STR_ECTCSPPosRef.PosRefAve;
        }
        else
        {
            ExcCnt = STR_ECTCSPVar.SYNCPeriodRatio;
			CSPPointCal();
			STR_ECTCSPPosRef.PosRefAve = CSPPosRef(pInterplt,STR_ECTCSPVar.InterpltDltRef);
            temp3 = STR_ECTCSPPosRef.PosRefAve;
        }

    }
    else
    {
        temp3 = 0;
    }

    STR_ECTCSPVar.InterpltIncPer = temp3;

    //位置指令1的跳变补偿
    if(STR_ECTCSPVar.RefPosRemainder>0)
    {
        if(STR_ECTCSPVar.InterpltIncPer>=0)
        {
            STR_ECTCSPVar.InterpltIncPer = STR_ECTCSPVar.InterpltIncPer +1;
            STR_ECTCSPVar.RefPosRemainder = STR_ECTCSPVar.RefPosRemainder - 1;
        }
    }
    else if(STR_ECTCSPVar.RefPosRemainder<0)
    {
        if(STR_ECTCSPVar.InterpltIncPer<=0)
        {
            STR_ECTCSPVar.InterpltIncPer = STR_ECTCSPVar.InterpltIncPer -1;
            STR_ECTCSPVar.RefPosRemainder = STR_ECTCSPVar.RefPosRemainder + 1;
        }
    }

    //速度限制---不超过6000rpm
	MaxInterpltPos = STR_ECTCSPVar.MaxInterpltPosCmd + STR_ECTCSPVar.MaxInterpltPosCmd / 50;

    //速度限制---不超过6000rpm
    if(STR_ECTCSPVar.InterpltIncPer >=MaxInterpltPos)
    {

        STR_ECTCSPVar.RefPosRemainder += STR_ECTCSPVar.InterpltIncPer - MaxInterpltPos;
        STR_ECTCSPVar.InterpltIncPer = MaxInterpltPos;

    }
    else if((STR_ECTCSPVar.InterpltIncPer + MaxInterpltPos)<=0)
    {
        STR_ECTCSPVar.RefPosRemainder += STR_ECTCSPVar.InterpltIncPer + MaxInterpltPos;
        STR_ECTCSPVar.InterpltIncPer = -MaxInterpltPos;
    }

    return STR_ECTCSPVar.InterpltIncPer;
}
/*******************************************************************************
  函数名:  void IPClear(void)
  输入:
  参数：
  输出:
  描述:    插补清除函数
********************************************************************************/
void CSPClear(void)
{
	STR_ECTCSPVar.OTLatchPosCmd = 0;
	STR_ECTCSPVar.P_overspeedcnt=0;
	STR_ECTCSPVar.RefPosRemainder = 0;
	STR_ECTCSPVar.InterpltDltRef = 0;
	STR_ECTCSPVar.CSPRunFlag = 0;

	ExcCnt = 0;
}
/*******************************************************************************
  函数名:  CSPPosRef(STR_ECTCSPPOSREF *p,int64_t CmdInput)
  输入:    CmdInput	       //插补位移
  输出:    PosRefAve        //平均位置指令
  描述:    对位置指令进行均分计算
********************************************************************************/
int64_t CSPPosRef(STR_ECTCSPPOSREF *p,int64_t CmdInput)
{
    if (STR_ECTCSPVar.SYNCPeriodRatio == 0)	  //当同步周期为0时，退出程序，返回0
    {
        return 0;
    }

    p->InPut= CmdInput;    //该同步周期要执行的位置指令总数

    p->PosRefAve = (p->InPut +  STR_ECTCSPVar.RefPosRemainder) / (int64_t)STR_ECTCSPVar.SYNCPeriodRatio;

    STR_ECTCSPVar.RefPosRemainder = (p->InPut +  STR_ECTCSPVar.RefPosRemainder) % (int64_t)STR_ECTCSPVar.SYNCPeriodRatio;
    return (p->PosRefAve);
}
void CSP_main_loop(void)
{
	ECTCSPMaxSpeedUpdate();           //CSP最大速度限制，运行更新
}

