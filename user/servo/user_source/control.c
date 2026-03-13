/*
 * control.c
 *
 *  Created on: 2023年8月14日
 *      Author: wenxing.ma
 */
#include "all_inc.h"
#include "M680x_it.h"

/****************板间接口定义******************/
void contrl_frq_Init(SPEED_MEAS_CMD *v)
{
    v->cmd_new = 0;
    v->cmd_old = 0;
    v->cmd_frq = 0;
	v->cmd_filt_cnt = 0;
	v->cmd_filt_xn = 0;
	v->cmd_filt_yn = 0;
	v->cmd_filt_yn_next = 0;
	v->cmd_filt_out = 0;
	v->pr_cmd = 0;
}

void contrl_frq_calc(SPEED_MEAS_CMD *v)
{
   long tmp1;
   long cmd_frq_old = 0;
   //v->cmd_new = ExPulseTimer3Cnt;
   tmp1 =v->cmd_new - v->cmd_old;
   if(tmp1 > 32767 )   //减计数
   {
	   tmp1 = tmp1 - 65536;
   }
   if(tmp1 < -32767 )  //增计数
   {
       tmp1 =tmp1  + 65536;
   }
   if(encoder_rcr_error_flag == 0 || encoder_off_error_flag == 0)//编码器CRC没有错误
   {
       v->cmd_frq = tmp1;
       cmd_frq_old = tmp1;
   }
   else
   {
	   v->cmd_frq = cmd_frq_old;
   }
   v->cmd_old = v->cmd_new;
}

void contrl_frq_filt(SPEED_MEAS_CMD *v)
{
   if(v->cmd_filt_en == 1)
   {
	   if(v->cmd_filt_k > 10000)
	   {
			 v->cmd_filt_k = 10000;
	   }
	   if(v->cmd_filt_k < 1)
	   {
			 v->cmd_filt_k = 1;
	   }
	   v->cmd_filt_yn = v->cmd_filt_yn_next +  (long)((v->cmd_filt_k*(v->cmd_filt_xn - v->cmd_filt_yn_next)+ v->cmd_filt_save)/10000.0);
	   v->cmd_filt_out = v->cmd_filt_yn;
	   v->cmd_filt_save =  (long)((v->cmd_filt_k*(v->cmd_filt_xn - v->cmd_filt_yn_next)+ v->cmd_filt_save)%10000);
	   v->cmd_filt_yn_next =  v->cmd_filt_out;
   }
   else
   {
	   v->cmd_filt_out = v->cmd_filt_xn;
   }
}

