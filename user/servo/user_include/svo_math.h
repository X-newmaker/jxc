/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_SVO_MATH_H_
#define INCLUDE_SVO_MATH_H_

typedef struct clarke_s{
		_iq  As;  		// Input: phase-a stator variable
		_iq  Bs;		// Input: phase-b stator variable
		_iq  Cs;		// Input: phase-c stator variable  
		_iq  Alpha;		// Output: stationary d-axis stator variable 
		_iq  Beta;		// Output: stationary q-axis stator variable
} clarke_t;

#define CLARKE_DEFAULT {0,0,0,0,0}
#define  ONEbySQRT3   0.57735026918963    /* 1/sqrt(3) */

typedef struct park_s{  
		_iq  Alpha;  		// Input: stationary d-axis stator variable 
		_iq  Beta;	 	// Input: stationary q-axis stator variable 
		_iq  Ds;			// Output: rotating d-axis stator variable 
		_iq  Qs;			// Output: rotating q-axis stator variable
		_iq  Sine;
		_iq  Cosine; 	 
} park_t;

#define PARK_DEFAULT {0,0,0,0,0,0}


typedef struct ipark_s{  
		_iq  Alpha;  		// Output: stationary d-axis stator variable
		_iq  Beta;		// Output: stationary q-axis stator variable
		_iq  Ds;			// Input: rotating d-axis stator variable
		_iq  Qs;			// Input: rotating q-axis stator variable
		_iq  Sine;		// Input: Sine term
		_iq  Cosine;		// Input: Cosine term
} ipark_t;	            

#define IPARK_DEFAULT {0, 0, 0, 0, 0, 0}

typedef struct svgen_s{
		_iq  Ualpha; 			// Input: reference alpha-axis phase voltage 
		_iq  Ubeta;			// Input: reference beta-axis phase voltage 
		_iq  Ta;				// Output: reference phase-a switching function		
		_iq  Tb;				// Output: reference phase-b switching function 
		_iq  Tc;				// Output: reference phase-c switching function
		_iq  tmp1;			// Variable: temp variable
		_iq  tmp2;			// Variable: temp variable
		_iq  tmp3;			// Variable: temp variable
		u16 VecSector;		// Space vector sector
} svgen_t;

#define SVGEN_DEFAULT { 0,0,0,0,0 }  

typedef struct qep_param_s{
		_iq ElecTheta;        // Output: Motor Electrical angle (Q15)
                u16 QepPeriod;       // Output: Capture period of QEP signal in number of EQEP capture timer (QCTMR) period  (Q0)
		u32 QepPos;
		u32 QepMax;
		u32 ElectMax;
                u32 RawTheta;        // Variable: Raw angle from EQEP Postiion counter (Q0)
		u32 temp_ElecTheta;
                u16 LineEncoder;     // Parameter: Number of line encoder (Q0) 
                u16 PolePairs;       // Parameter: Number of pole pairs (Q0) 
                u32 CalibratedAngle; // Parameter: Raw angular offset between encoder index and phase a (Q0)
} qep_param_t;

#define QEP_PARA_DEFAULT { 0,0,0,0,0,0,0,0,0,0}  

typedef struct abs_param_s{
		_iq ElecTheta;        // Output: Motor Electrical angle (Q15)               
		u32 AbsPos;
		u32 AbsMax;
		u32 ElectMax;
                u32 RawTheta;        // Variable: Raw angle from EQEP Postiion counter (Q0)
		u32 temp_ElecTheta;
                u16 PolePairs;       // Parameter: Number of pole pairs (Q0) 
} abs_param_t;

#define ABS_PARA_DEFAULT { 0,0,0,0,0,0,0}  

typedef struct speed_s{
       		_iq ElecTheta;  		// Input: Electrical angle (pu) 
       		_iq OldElecTheta;   	// History: Electrical angle at previous step (pu)
       		_iq RpmFactor;      // Parameter: Base speed in rpm (Q0) - independently with global Q
       		u32 SpeedRpm;      // Output : Speed in rpm  (Q0) - independently with global Q
       		_iq Tmp;				//Variable: Temp variable
		_iq OldTmp;
} speed_t;   	
#define SPEED_DEFAULT { 0,0,0,0,0,0}  

typedef struct 	svpwm_s{ 
	    _iq  Ualpha; 		//  二相静止坐标系alpha-轴
		_iq  Ubeta;		    //  二相静止坐标系beta-轴
		u16  Ta;		    //  三相矢量占空比Ta
		u16  Tb;		    //  三相矢量占空比Tb
		u16  Tc;		    //  三相矢量占空比Tc
		_iq  tmp1;		    //  三相静止坐标系的电压temp1
		_iq  tmp2;		    //  三相静止坐标系的电压temp2
		_iq  tmp3;		    //  三相静止坐标系的电压temp3
		u16  VecSector;		//  矢量空间扇区号
	  _iq15  TIMECONST;
		u32  PWMPRD;
		u32  MAXDUTY;
		u32  MINDUTY;
		u16  OverMode2En;   //  2区过调制使能
} svpwm_t;

#define SVPWM_DEFAULT {0,0,0,0,0,0,0,0,0,0,0,0,0,0}

typedef struct pi_s{
                _iq  Ref;                       // Input: reference set-point
                _iq  Fbk;                       // Input: feedback
                _iq  Out;                       // Output: controller output
                _iq  Kp;                                // Parameter: proportional loop gain
                _iq  Ki;                            // Parameter: integral gain
                _iq  Umax;                      // Parameter: upper saturation limit
                _iq  Umin;                      // Parameter: lower saturation limit
                _iq  up;                                // Data: proportional term
                _iq  ui;                                // Data: integral term
                _iq  v1;                                // Data: pre-saturated controller output
                _iq  i1;                                // Data: integrator storage: ui(k-1)
                _iq  w1;                                // Data: saturation record: [u(k-1) - v(k-1)]
                _iq  SaturaFlag;
                _iq  Comp;
} pi_t;

#define PI_DEFAULT {\
                0,\
                0,\
                0,\
                _IQ(1.0),\
                _IQ(0.0),\
                _IQ(1.0),\
                _IQ(-1.0),\
                _IQ(0.0),\
                _IQ(0.0),\
                _IQ(0.0),\
                _IQ(0.0),\
                _IQ(1.0),\
				 0,\
				 0 \
}

typedef struct rmpcntl_s{
	_iq    	TargetValue; 	// Input: Target input (pu)
	u32    	RampDelayMax;	// Parameter: Maximum delay rate (Q0) - independently with global Q			
	_iq    	RampLowLimit;	// Parameter: Minimum limit (pu)				  
	_iq    	RampHighLimit;	// Parameter: Maximum limit (pu)
	u32    	RampDelayCount; // Variable: Incremental delay (Q0) - independently with global Q	
	_iq    	SetpointValue;	// Output: Target output (pu)				 
	u32    	EqualFlag;		// Output: Flag output (Q0) - independently with global Q
	_iq    	Tmp;			// Variable: Temp variable
} rmpcntl_t;

#define RMPCNTL_DEFAULT {0,5,_IQ(-1),_IQ(1),0,0,0,0}

typedef struct rmpgen_s{
	_iq  	Freq; 		// Input: Ramp frequency (pu) 	
	_iq  	StepAngleMax;	// Parameter: Maximum step angle (pu)		
	_iq  	Angle;		// Variable: Step angle (pu)					  
	_iq  	Gain;			// Input: Ramp gain (pu)
	_iq  	Out;  	 	// Output: Ramp signal (pu) 	
	_iq  	Offset;		// Input: Ramp offset (pu) 	
} rmpgen_t;

#define RMPGEN_DEFAULT {0,0,_IQ(-1),_IQ(1),_IQ(-1),_IQ(1)}

typedef struct phase_vol_s{
	_iq  DcBusVolt;		// Input: DC-bus voltage (pu)
	_iq  MfuncV1;  		// Input: Modulation voltage phase A (pu)
	_iq  MfuncV2;		// Input: Modulation voltage phase B (pu)	
	_iq  MfuncV3;		// Input: Modulation voltage phase C (pu) 
        u16 OutOfPhase; 	// Parameter: Out of Phase adjustment (0 or 1) (Q0) - independently with global Q
	_iq  VphaseA;		// Output: Phase voltage phase A (pu)
	_iq  VphaseB;		// Output: Phase voltage phase B (pu) 
	_iq  VphaseC;		// Output: Phase voltage phase C (pu) 
	_iq  Valpha;		// Output: Stationary d-axis phase voltage (pu)
	_iq  Vbeta;  		// Output: Stationary q-axis phase voltage (pu)
	_iq  temp;		// Variable: temp variable
} phase_vol_t;

#define PHASEVOLTAGE_DEFAULT {0,0,0,0,1,0,0,0,0,0}

#define ONE_THIRD  _IQ(0.33333333333333)
#define TWO_THIRD  _IQ(0.66666666666667)
#define INV_SQRT3  _IQ(0.57735026918963)

typedef struct smopos_s{
	_iq  Valpha;   		// Input: Stationary alfa-axis stator voltage 
	_iq  Ealpha;   		// Variable: Stationary alfa-axis back EMF 
	_iq  Zalpha;      	// Output: Stationary alfa-axis sliding control 
	_iq  Gsmopos;    	// Parameter: Motor dependent control gain 
	_iq  EstIalpha;  	 // Variable: Estimated stationary alfa-axis stator current 
	_iq  Fsmopos;    	// Parameter: Motor dependent plant matrix 
	_iq  Vbeta;   		// Input: Stationary beta-axis stator voltage 
	_iq  Ebeta;  		// Variable: Stationary beta-axis back EMF 
	_iq  Zbeta;      	// Output: Stationary beta-axis sliding control 
	_iq  EstIbeta;    	// Variable: Estimated stationary beta-axis stator current 
	_iq  Ialpha;  		// Input: Stationary alfa-axis stator current 
	_iq  IalphaError; 	// Variable: Stationary alfa-axis current error                 
	_iq  Kslide;     	// Parameter: Sliding control gain 
	_iq  Ibeta;  		// Input: Stationary beta-axis stator current 
	_iq  IbetaError;  	// Variable: Stationary beta-axis current error                 
	_iq  Kslf;       	// Parameter: Sliding control filter gain 
	_iq  Theta;     	// Output: Compensated rotor angle
	_iq  E0;		// Parameter: 0.5 
} smopos_t;

#define SMOPOS_DEFAULT {0,0,0,0,0,0,0,0,0,0, \
			0,0,0,0,0,0,0,_IQ(0.5)}

typedef struct smopos_const_s{
	float  Rs; 		// Input: Stator resistance (ohm) 
	float  Ls;		// Input: Stator inductance (H) 	  			      
	float  Ib; 		// Input: Base phase current (amp) 
	float  Vb;		// Input: Base phase voltage (volt) 
	float  Ts;		// Input: Sampling period in sec 
	float  Fsmopos;		// Output: constant using in observed current calculation 
	float  Gsmopos;		// Output: constant using in observed current calculation 
} smopos_const_t;
#define SMOPOS_CONST_DEFAULT {0,0,0,0,0,0,0}


void clarke_cal(clarke_t* p);
void clarke_3c_cal(clarke_t* p);
void park_cal(park_t* p);
void ipark_cal(ipark_t* p);
void svgen_cal(svgen_t* p);
void qep_cal(qep_param_t* p);
void abs_cal(abs_param_t* p);
void speed_cal(speed_t* p);
void pi_reset(pi_t* p);
void pi_cal(pi_t* p);
void pi_cal_v2(pi_t* p);
_iq iqsat(_iq x, _iq max, _iq min);
void rmpcntl_cal(rmpcntl_t* p);
void rmpgen_cal(rmpgen_t* p);
void rmpgen_2_cal(rmpgen_t* p);
void svpwm_cal(svpwm_t* p_svpwm);
void phase_voltage_cal(phase_vol_t* p);
void smo_cal(smopos_t* p);
void smo_const_cal(smopos_const_t* p);

#endif /* INCLUDE_SVO_MATH_H_ */

