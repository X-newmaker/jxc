#include "all_inc.h"
#include "M680x_it.h"
#include "math.h"
// Clarke变换(两相电流采集)
//==========================================
void clarke_cal(clarke_t* p)
{
        p->Alpha = p->As;
        p->Beta = _IQmpy((p->As +_IQmpy2(p->Bs)), _IQ(ONEbySQRT3));     
}
// Clarke变换(三相电流采集)
//==========================================
void clarke_3c_cal(clarke_t* p)
{
        p->Alpha = p->As;
        p->Beta = _IQmpy((p->Bs - p->Cs), _IQ(ONEbySQRT3));
}
// Park变换
//==========================================
void park_cal(park_t* p)
{
        p->Ds = _IQmpy(p->Alpha, p->Cosine) + _IQmpy(p->Beta, p->Sine);
        p->Qs = _IQmpy(p->Beta, p->Cosine) - _IQmpy(p->Alpha, p->Sine);
}

//Park反变换
//==========================================
void ipark_cal(ipark_t* p)
{
        p->Alpha = _IQmpy(p->Ds,p->Cosine) - _IQmpy(p->Qs,p->Sine);		
        p->Beta  = _IQmpy(p->Qs,p->Cosine) + _IQmpy(p->Ds,p->Sine);
}

//SVGEN计算
//==========================================
void svgen_cal(svgen_t* p)
{
	p->tmp1= p->Ubeta;						
	p->tmp2= _IQdiv2(p->Ubeta) + (_IQmpy(_IQ(0.866),p->Ualpha));
    p->tmp3= p->tmp2 - p->tmp1;

	p->VecSector=3;
	p->VecSector=(p->tmp2> 0)?( p->VecSector-1):p->VecSector;
	p->VecSector=(p->tmp3> 0)?( p->VecSector-1):p->VecSector;
	p->VecSector=(p->tmp1< 0)?(7-p->VecSector) :p->VecSector;			

	if (p->VecSector==1 || p->VecSector==4) {     
		p->Ta= p->tmp2;
		p->Tb= p->tmp1-p->tmp3;
		p->Tc=-p->tmp2;
	}

	else if (p->VecSector==2 || p->VecSector==5){
		p->Ta= p->tmp3+p->tmp2;
		p->Tb= p->tmp1;
		p->Tc=-p->tmp1;
	}
	else {
		p->Ta= p->tmp3;
		p->Tb=-p->tmp3;
		p->Tc=-(p->tmp1+p->tmp2);
	}

}


void qep_cal(qep_param_t* p)
{
/* Check the position counter*/
        p->RawTheta = p->QepPos + p->CalibratedAngle;

        if (p->RawTheta < 0)
                p->RawTheta = p->RawTheta + p->QepMax;
        else if (p->RawTheta > p->QepMax)
                p->RawTheta = p->RawTheta - p->QepMax;

        p->temp_ElecTheta = p->RawTheta % p->ElectMax; 
        p->ElecTheta = p->temp_ElecTheta * _IQ(1) / p->ElectMax;

        if (p->ElecTheta > _IQ(1.0))
                p->ElecTheta = p->ElecTheta - _IQ(1.0);

}

void abs_cal(abs_param_t* p)
{
/* Check the position counter*/
        p->RawTheta = p->AbsPos;

        if (p->RawTheta < 0)
                p->RawTheta = p->RawTheta + p->AbsMax;
        else if (p->RawTheta > p->AbsMax)
                p->RawTheta = p->RawTheta - p->AbsMax;

        p->temp_ElecTheta = p->RawTheta % p->ElectMax; 
        p->ElecTheta = p->temp_ElecTheta * _IQ(1) / p->ElectMax;

        if (p->ElecTheta > _IQ(1.0))
                p->ElecTheta = p->ElecTheta - _IQ(1.0);

}

void speed_cal(speed_t* p)
{
        p->Tmp = p->ElecTheta - p->OldElecTheta;
        if (p->Tmp < -_IQ(0.5))
                p->Tmp = p->Tmp + _IQ(1.0);
        else if (p->Tmp > _IQ(0.5))
                p->Tmp = p->Tmp - _IQ(1.0);
        
        if (p->Tmp > _IQ(0.01) || p->Tmp < -_IQ(0.01))
                p->Tmp = p->OldTmp;
        
        p->OldTmp =  p->Tmp;
        p->OldElecTheta = p->ElecTheta;
        p->SpeedRpm = _IQmpy(p->RpmFactor,p->Tmp);
}

// PI计算
void pi_reset(pi_t* p)
{
	p->up = 0;
	p->ui = 0;
	p->Ref = 0;
	p->Fbk = 0;
	p->Out = 0;
}
//==========================================
void pi_cal(pi_t* p)
{
	/* proportional term */
        p->up = p->Ref - p->Fbk;

        /* integral term */
        p->ui = (p->Out == p->v1)?(_IQmpy(p->Ki, p->up)+ p->i1) : p->i1;
        p->i1 = p->ui;

        /* control output */
        p->v1 = _IQmpy(p->Kp, (p->up + p->ui));
        p->Out= iqsat(p->v1, p->Umax, p->Umin);
        //p->w1 = (p->Out == p->v1) ? _IQ(1.0) : _IQ(0.0);


}

// PI计算
//==========================================
void pi_cal_v2(pi_t* p)
{
        /* proportional term */
        p->up = _IQmpy((p->Ref - p->Fbk), p->Kp);

        /* integral term */
        p->ui = (p->Out == p->v1)?(_IQmpy(p->Ki, p->up)+ p->i1) : p->i1;
        p->i1 = p->ui;

        /* control output */
        p->v1 = p->up + p->ui;
        p->Out= iqsat(p->v1, p->Umax, p->Umin);
        //p->w1 = (p->Out == p->v1) ? _IQ(1.0) : _IQ(0.0);

}

// 限幅计算
//==========================================
_iq iqsat(_iq x, _iq max, _iq min)
{
        if (x >= max) 
                x = max;
        else if (x <= min)
                x = min;
        return x;
}

// ramp_control
//==========================================
void rmpcntl_cal(rmpcntl_t* p)
{

        p->Tmp = p->TargetValue - p->SetpointValue;

        if (p->Tmp < 0)
                p->Tmp = -p->Tmp;

        if (p->Tmp >= 2) 
        {
	        p->RampDelayCount++	;
		if (p->RampDelayCount >= p->RampDelayMax)	
		{								
			if (p->TargetValue >= p->SetpointValue)
				p->SetpointValue += 2;
			else						
				p->SetpointValue -= 2;
							
			p->SetpointValue= iqsat(p->SetpointValue,p->RampHighLimit,p->RampLowLimit);	
			p->RampDelayCount = 0;	

		}
        }

        else p->EqualFlag = 0x7FFFFFFF;
}

// ramp_generate
//==========================================
void rmpgen_cal(rmpgen_t* p)
{
        /* Compute the angle rate */
	p->Angle += _IQmpy(p->StepAngleMax,p->Freq);

        /* Saturate the angle rate within (-1,1) */
	if (p->Angle>_IQ(1.0))
		p->Angle -= _IQ(1.0);
	else if (p->Angle<_IQ(-1.0))
		p->Angle += _IQ(1.0);

	p->Out=p->Angle;
}

//==========================================
void rmpgen_2_cal(rmpgen_t* p)
{
        /* Compute the angle rate */
        p->Angle += _IQmpy(p->StepAngleMax,p->Freq);

        /* Saturate the angle rate within (-1,1) */
        if (p->Angle>_IQ(1.0))
                p->Angle -= _IQ(2.0);
        else if (p->Angle<_IQ(-1.0))
                p->Angle += _IQ(2.0);

        p->Out=p->Angle;
}


// SVPWM计算（硬件电流环采用的算法）
//==========================================
void svpwm_cal(svpwm_t* p)
{
	u16 Sector = 0;
	u32 vectime0 = 0;
	u32 vectime1 = 0;
	u32 vectime2 = 0;
	u16 ComValu1 = 0;
	u16 ComValu2 = 0;
	u16 ComValu3 = 0;
	u32 Delta=0;
	_iq TempPhsV;
	_iq TempPhsW;
	_iq Sum=0;

	p->tmp1 = p->Ubeta;                       //U

	TempPhsV  = ((p->Ualpha) * _IQ10(1.7320508))>>10;   // Q10(3^0.5) = 1774
	TempPhsV  = TempPhsV - p->Ubeta;
	p->tmp2   = (TempPhsV>>1);                //V

	TempPhsW  = ((p->Ualpha) * _IQ10(1.7320508))>>10;   // Q10(3^0.5) = 1774
	TempPhsW  = (-1)*TempPhsW - p->Ubeta;
	p->tmp3   = (TempPhsW>>1);                //W

	// 计算扇区
	if (p->tmp1 < 0){
		Sector += 1;
		p->tmp1   =  (-1)*p->tmp1;       //取绝对值运算
	}

	if (p->tmp2 < 0){
		Sector += 2;
		p->tmp2   =  (-1)*p->tmp2;      //取绝对值运算
	}

	if (p->tmp3 < 0){
		Sector += 4;
		p->tmp3   =  (-1)*p->tmp3;       //取绝对值运算
	}

	p->VecSector = Sector;

	switch (p->VecSector){
			case 1:
			case 6:
				vectime1 = p->tmp3;             //Q15表示的电压比值
				vectime2 = p->tmp2;
			break;
			case 2:
			case 5:
				vectime1 = p->tmp1;
				vectime2 = p->tmp3;   //以TB时钟计时的T2
			break;
			case 3:
			case 4:
				vectime1 = p->tmp2;               //-1* 省去，取绝对值
				vectime2 = p->tmp1;    //以TB时钟计时的T2
			break;
			default:
			break;
	}

	vectime1 = (p->TIMECONST * vectime1)>>15;
	vectime1 = (p->PWMPRD * vectime1)>>15;

	vectime2 = (p->TIMECONST * vectime2)>>15;
	vectime2 = (p->PWMPRD * vectime2)>>15;

	Sum = vectime1 + vectime2;

	if (Sum > p->PWMPRD)
	{
		vectime1 = (vectime1 * (u32)p->PWMPRD)/Sum;
		vectime2 = (u32)p->PWMPRD - vectime1;
        if(p->OverMode2En == 0)//默认过调制2区处理
        {
			if(Sum > ((p->PWMPRD *37824)>>15))  //37824 = 1.154 * 32768
			{
				Delta = Sum - ((p->PWMPRD *37824)>>15);

				if(vectime1 > vectime2)
				{
					if(vectime2<Delta)
					{
						vectime2 =0;
						vectime1 = p->PWMPRD;
					}
					else
					{
						vectime1 += Delta;
						vectime2 -= Delta;
					}
				}
				else
				{
					if(vectime1<Delta)
					{
						vectime1 =0;
						vectime2 = p->PWMPRD;
					}
					else
					{
						vectime1 -= Delta;
						vectime2 += Delta;
					}

				}

			}

        }

	}


	vectime0 = p->PWMPRD - vectime1 - vectime2;                           //零矢量作用时间

	switch (p->VecSector){
			case 1:
				ComValu3 = (u16)(vectime0>>1);
				ComValu1 =  ComValu3 + (u16)(vectime1);
				ComValu2 =  ComValu1 + (u16)(vectime2);
			break;
			case 2:
				ComValu2 = (u16)(vectime0>>1);
				ComValu3 =  ComValu2 + (u16)(vectime1);
				ComValu1 =  ComValu3 + (u16)(vectime2);
			break;
			case 3:
				ComValu3 = (u16)(vectime0>>1);
				ComValu2 =  ComValu3 + (u16)(vectime2);
				ComValu1 =  ComValu2 + (u16)(vectime1);
			break;
			case 4:
				ComValu1 = (u16)(vectime0>>1);
				ComValu2 =  ComValu1 + (u16)(vectime1);
				ComValu3 =  ComValu2 + (u16)(vectime2);
			break;
			case 5:
				ComValu1 = (u16)(vectime0>>1);
				ComValu3 =  ComValu1 + (u16)(vectime2);
				ComValu2 =  ComValu3 + (u16)(vectime1);
			break;
			case 6:
				ComValu2 = (u16)(vectime0>>1);
				ComValu1 =  ComValu2 + (u16)(vectime2);
				ComValu3 =  ComValu1 + (u16)(vectime1);
			break;
			default:
			break;
	}

	if (ComValu1 <= p->MINDUTY)
			ComValu1 = p->MINDUTY;
	if (ComValu2 <= p->MINDUTY)
			ComValu2 = p->MINDUTY;
	if (ComValu3 <= p->MINDUTY)
			ComValu3 = p->MINDUTY;

	if (ComValu1  > p->MAXDUTY)
			ComValu1 = p->MAXDUTY;
	if (ComValu2  > p->MAXDUTY)
			ComValu2 = p->MAXDUTY;
	if (ComValu3  > p->MAXDUTY) 
			ComValu3 = p->MAXDUTY;


	p->Ta = ComValu1;
	p->Tb = ComValu2;
	p->Tc = ComValu3;
}

void phase_voltage_cal(phase_vol_t* p)
{
        /* Scale the incomming Modulation functions with the DC bus voltage value*/
        /* and calculate the 3 Phase voltages */
        p->temp      = _IQmpy(p->DcBusVolt,ONE_THIRD);
        p->VphaseA   = _IQmpy(p->temp,(_IQmpy2(p->MfuncV1)-p->MfuncV2-p->MfuncV3));
        p->VphaseB   = _IQmpy(p->temp,(_IQmpy2(p->MfuncV2)-p->MfuncV1-p->MfuncV3));

        if (p->OutOfPhase==0){	  
                p->VphaseA=-p->VphaseA;
  	        p->VphaseB=-p->VphaseB;
        }
        /* Voltage transformation (a,b,c)  ->  (Alpha,Beta)	*/
        p->Valpha = p->VphaseA;
        p->Vbeta = _IQmpy((p->VphaseA + _IQmpy2(p->VphaseB)),INV_SQRT3);
}

void smo_cal(smopos_t* p)
{
        /*	Sliding mode current observer	*/
        p->EstIalpha = _IQmpy(p->Fsmopos,p->EstIalpha) + _IQmpy(p->Gsmopos,(p->Valpha-p->Ealpha-p->Zalpha));
        p->EstIbeta  = _IQmpy(p->Fsmopos,p->EstIbeta)  + _IQmpy(p->Gsmopos,(p->Vbeta -p->Ebeta -p->Zbeta ));

	/*	Current errors	*/
        p->IalphaError = p->EstIalpha - p->Ialpha;
        p->IbetaError  = p->EstIbeta  - p->Ibeta;

	/*  Sliding control calculator	*/
	/* p->Zalpha=p->IalphaError*p->Kslide/p->E0) where E0=0.5 here*/
	p->Zalpha = _IQmpy(iqsat(p->IalphaError,p->E0,-p->E0),_IQmpy2(p->Kslide));
	p->Zbeta  = _IQmpy(iqsat(p->IbetaError ,p->E0,-p->E0),_IQmpy2(p->Kslide));

	/*	Sliding control filter -> back EMF calculator	*/
        p->Ealpha = p->Ealpha + _IQmpy(p->Kslf,(p->Zalpha-p->Ealpha));
        p->Ebeta  = p->Ebeta  + _IQmpy(p->Kslf,(p->Zbeta -p->Ebeta));

	/*	Rotor angle calculator -> Theta = atan(-Ealpha,Ebeta)	*/
        //1/pi = 0.31831
        p->Theta = _IQ( atan2(-p->Ealpha,p->Ebeta)*(0.31831) );
        // p->Theta = _IQ( atan2(p->Ebeta,-p->Ealpha)*(0.31831));
        //-pi~+pi转换为0~2pi
        if (p->Theta < 0){
                p->Theta = p->Theta + _IQ(2.0);
        }
        // 归一化
        p->Theta = p->Theta / 2;
}

void smo_const_cal(smopos_const_t* p)
{
        p->Fsmopos = exp( (-p->Rs/p->Ls)*(p->Ts) );
	// p->Gsmopos = (p->Vb/p->Ib)*(1/p->Rs)*(1-p->Fsmopos);
        p->Gsmopos = (0.33255461)*(1/p->Rs)*(1-p->Fsmopos);
        // p->Gsmopos = (2.4)*(1/p->Rs)*(1-p->Fsmopos);
}
