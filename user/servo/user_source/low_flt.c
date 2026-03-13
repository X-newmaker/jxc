/*
 * low_flt.c
 *
 *  Created on: 2023年8月14日
 *      Author: wenxing.ma
 */

#include "all_inc.h"
#include "low_fil.h"
void  low_filter_init(FILTER *v)
{
   v->xn = 0;
   v->yn = 0;
   v->K1 = _IQ(0.25);
}
 void low_filter_calc(FILTER *v)
{
   _iq tmp1;
	 if(v->FliterType == 0)
	 {
		  if(v->K2>_IQ(1))
		  {
			  v->K2 = _IQ(1);
		  }
		  else
		  {
			  v->K2 = v->K1;
		  }
		  v->K3 = _IQ(1)- v->K2;
		  tmp1 = v->xn;
		  tmp1 = _IQmpy(v->K3,v->yn)+_IQmpy(v->K2 ,tmp1);

		  if (tmp1>v->low_pass_max)
		  {
			   v->yn = v->low_pass_max;
		  }
		  else if (tmp1<v->low_pass_min)
		  {
			   v->yn = v->low_pass_min;
		  }
		  else
		  {
			   v->yn = tmp1;
		  }
	  }
	  else if(v->FliterType == 1)
	  {

	  }
}
