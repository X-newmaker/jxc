/*
 * gtc.c
 */


#include <all_inc.h>

gtc_dev_t* const gtc_dev_p = (gtc_dev_t*)BASE_GTC;

s32 init_gtc(void)
{
        int i = 0;
        cmu_mod_disable(CMU_MOD_GTC);
        for(i=0; i<0x10; i++);
	cmu_mod_enable(CMU_MOD_GTC);
//	cmu_mod_enable(322);	//for old bitfile

	gtc_dev_p->gtc_cntcr_reg.bits.en = 0;
	while(gtc_dev_p->gtc_cntcr_reg.bits.en);

	gtc_dev_p->gtc_confg_reg.bits.fdiv = cmu_mod_get_freq(CMU_MOD_GTC)/(4*1000*1000);
	gtc_dev_p->gtc_cntvl_reg.bits.cntvl = 0;
	gtc_dev_p->gtc_cntvh_reg.bits.cntvh = 0;
	gtc_dev_p->gtc_cntcr_reg.bits.en = 1;

	return RET_OK;
}

s32 init_gtc_div(void)
{
	gtc_dev_p->gtc_confg_reg.bits.fdiv = cmu_mod_get_freq(CMU_MOD_GTC)/(4*1000*1000);

	return RET_OK;
}

s32 gtc_set_freq(u32 sel)
{
	gtc_dev_p->gtc_cntcr_reg.bits.fcreq = (sel<2) ? sel : 2;

	return RET_OK;
}

s32 gtc_set_time(gtc_unit_t u,u64 t)
{
	u64 now;

	gtc_dev_p->gtc_cntcr_reg.bits.en = 0;
	while(gtc_dev_p->gtc_cntcr_reg.bits.en);

	switch(u){
	case GTC_US: 	now = t<<2; 		break;
	case GTC_US_100:now = t*400; 		break;
	case GTC_MS: 	now = t*4000;		break;
	case GTC_S:  	now = t*4000000;	break;
	case GTC_M:	now = t*240000000;	break;
	default:	now = t;		break;
	}

	gtc_dev_p->gtc_cntvh_reg.bits.cntvh = now>>32;
	gtc_dev_p->gtc_cntvl_reg.bits.cntvl = now;

	gtc_dev_p->gtc_cntcr_reg.bits.en = 1;
	while(!gtc_dev_p->gtc_cntcr_reg.bits.en);

	return RET_OK;
}

u64 gtc_get_time(gtc_unit_t u)
{
	#if 0
	u32 nowu = gtc_dev_p->gtc_cntvh_reg.dwval;
	u32 nowl = gtc_dev_p->gtc_cntvl_reg.dwval;
	u64 now = ((u64)nowu)<<32 | nowl;
	#else
	u64 now = cpu_get_time();
	#endif

	switch(u){
	case GTC_US: 	now /= 4; 		break;
	case GTC_US_100:now /= 400; 		break;
	case GTC_MS:	now /= 4000;		break;
	case GTC_S:  	now /= 4000000;		break;
	case GTC_M:  	now /= 240000000;	break;
	default:				break;
	}

	return now;
}

s32 gtc_dly_time(gtc_unit_t u,u32 t)
{
	u64 now = gtc_get_time(u);
	volatile u64 time_out = now + t;
	while(gtc_get_time(u)<time_out);

	return RET_OK;
}
