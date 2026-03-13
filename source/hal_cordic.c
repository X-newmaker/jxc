
#include <all_inc.h>

volatile struct COR_REGS Cor_Regs __attribute__((__section__(".cordicreg")));

void cordic_cmu_init(void)
{
		int i = 0;
        cmu_mod_disable(CMU_MOD_CORDIC);
        for(i=0; i<0x10; i++);
        cmu_mod_enable(CMU_MOD_CORDIC);
}
/**
 *
 * @param funsel 函数选择
 * @param iteration 迭代次数选择，迭代次数越高结果越准确
 * @param data1 输入参数1
 * @param data2 输入参数2
 * @param result1 输出结果1
 * @param result2 输出结果2
 */
void cordic_cal(COR_FUNC_TYP funsel, COR_ITER_TYP iteration, s16 data1, s16 data2, s32 *result1, s32 *result2)
{
	Cor_Regs.COR_CFG.bit.FUNC_SEL = funsel;
	Cor_Regs.COR_CFG.bit.NM_ITER = iteration;

	Cor_Regs.COR_IN2.bit.IN_PARA2 = data2;
	Cor_Regs.COR_IN1.bit.IN_PARA1 = data1;
    *result2 =  (s32)Cor_Regs.COR_OUT2.bit.OUT_RES2;
    *result1 =  (s32)Cor_Regs.COR_OUT1.bit.OUT_RES1;

}

void cord_set(COR_FUNC_TYP funsel, COR_ITER_TYP iteration)
{
        Cor_Regs.COR_CFG.bit.FUNC_SEL = funsel;
        Cor_Regs.COR_CFG.bit.NM_ITER = iteration;
}

void cord_cal(s16 data1, s16 data2, s32 *result1, s32 *result2)
{
        Cor_Regs.COR_IN2.bit.IN_PARA2 = data2;
        Cor_Regs.COR_IN1.bit.IN_PARA1 = data1;
        *result2 =  (s32)Cor_Regs.COR_OUT2.bit.OUT_RES2;
        *result1 =  (s32)Cor_Regs.COR_OUT1.bit.OUT_RES1;
}

void cord_set_dat1(s16 data1)
{
        Cor_Regs.COR_IN1.bit.IN_PARA1 = data1;
}

void cord_set_dat2(s16 data2)
{
        Cor_Regs.COR_IN2.bit.IN_PARA2 = data2;
}

void cord_get_res1(s32 *result1)
{
        *result1 =  (s32)Cor_Regs.COR_OUT1.bit.OUT_RES1;
}

void cord_get_res2(s32 *result2)
{
        *result2 =  (s32)Cor_Regs.COR_OUT2.bit.OUT_RES2;
}

void cord_out_fmt(u32 fmt)
{
	 Cor_Regs.COR_CFG.bit.COR_OUT_FMT = fmt;
}

