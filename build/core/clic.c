/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 *
 */

#include "all_inc.h"
#include "e907.h"
#include "clic.h"


#define CPU_IRQ_NUM	188

static void cpu_irq_null(void) {};
volatile cpu_irq_fun_t clic_irq_vector[CPU_IRQ_NUM] __attribute__((aligned(64)));
clic_dev_t* const clic_dev_p = (clic_dev_t*)(BASE_CPU+0x800000);

s32 init_clic(void)
{
	u32 i;

	clic_dev_p->clic_cfg.bits.nlbits = ((clic_dev_p->clic_info.dwval & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos);

	for (i=0; i<CPU_IRQ_NUM; i++) {
		clic_dev_p->clic_int[i].clic_intip.dbval = 0;
		clic_dev_p->clic_int[i].clic_intattr.bits.shv 	= 1;
		clic_irq_vector[i] = cpu_irq_null;

	}


	return RET_OK;
}

s32 clic_irq_request(cpu_irq_id_t id, cpu_irq_fun_t fun)
{
	if (id >= CPU_IRQ_NUM) {
		printk("clic ERR: ID(%d) requested is outside!\n", id);
		return RET_FALSE;
	}

	clic_irq_vector[id] = fun;

	return RET_OK;
}

s32 clic_irq_free(cpu_irq_id_t id)
{
	if (id >= CPU_IRQ_NUM) {
		printk("clic ERR: ID(%d) freed is outside!\n", id);
		return RET_FALSE;
	}

	clic_irq_vector[id] = cpu_irq_null;

	return RET_OK;
}

s32 clic_irq_enable(cpu_irq_id_t id)
{
	if (id >= CPU_IRQ_NUM) {
		printk("clic ERR: ID(%d) enabled is outside!\n", id);
		return RET_FALSE;
	}

	clic_dev_p->clic_int[id].clic_intie.bits.ie = 1;

	return RET_OK;
}

s32 clic_irq_disable(cpu_irq_id_t id)
{
	if (id >= CPU_IRQ_NUM) {
		printk("clic ERR: ID(%d) disabled is outside!\n", id);
		return RET_FALSE;
	}

	clic_dev_p->clic_int[id].clic_intie.bits.ie = 0;

	return RET_OK;
}

s32 clic_attr_cfg(cpu_irq_id_t id, u32 shv, u32 trig, u32 mode)
{
    clic_dev_p->clic_int[id].clic_intattr.bits.mode = mode;
    clic_dev_p->clic_int[id].clic_intattr.bits.shv = shv;
    clic_dev_p->clic_int[id].clic_intattr.bits.trig = trig;
    //printk("shv:%x trig:%x\n", clic_dev_p->clic_int[id].clic_intattr.bits.shv, clic_dev_p->clic_int[id].clic_intattr.bits.trig);

    return RET_OK;
}

void clic_irq_set_prio(cpu_irq_id_t id, PRI_TYPE priority)
{
    	u8 nlbits = (clic_dev_p->clic_info.dwval & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos;
    	clic_dev_p->clic_int[id].clic_intctl.dbval = (clic_dev_p->clic_int[id].clic_intctl.dbval & (~CLIC_INTCFG_PRIO_Msk)) | (priority << (8 - nlbits));
}

u8 clic_irq_get_prio(cpu_irq_id_t id)
{
	u8 nlbits = (clic_dev_p->clic_info.dwval & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos;	//3
	return clic_dev_p->clic_int[id].clic_intctl.dbval >> (8 - nlbits);
}

void clic_cfg_set(void)
{
	clic_dev_p->clic_cfg.dwval = (((clic_dev_p->clic_info.dwval & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos) << CLIC_CLICCFG_NLBIT_Pos);
}

void clic_get_ip_sts(cpu_irq_id_t id)
{
	printk("clicintip is 0x%x\n",clic_dev_p->clic_int[id].clic_intip.dbval);
	printk("clicintip is 0x%x\n",clic_dev_p->clic_int[id].clic_intie.dbval);
	printk("clicintip is 0x%x\n",clic_dev_p->clic_int[id].clic_intattr.dbval);
	printk("clicintip is 0x%x\n",clic_dev_p->clic_int[id].clic_intctl.dbval);
}

s32 clic_ctl_cfg(cpu_irq_id_t id, u8 prio)
{
    clic_dev_p->clic_int[id].clic_intctl.bits.int_ctl = prio;

    return RET_OK;
}

s32 clic_cfg_nlbits(u8 nlbits)
{
    clic_dev_p->clic_cfg.bits.nlbits = nlbits;

    return RET_OK;
}

s32 clic_ip_clear(cpu_irq_id_t id)
{
    clic_dev_p->clic_int[id].clic_intip.bits.ip = 0;
    return RET_OK;
}
//
s32 cpu_irq_free(cpu_irq_id_t id)               __attribute__((alias("clic_irq_free"    )));
s32 cpu_irq_enable(cpu_irq_id_t id)             __attribute__((alias("clic_irq_enable"  )));
s32 cpu_irq_disable(cpu_irq_id_t id)                __attribute__((alias("clic_irq_disable" )));
s32 cpu_irq_request(cpu_irq_id_t id, cpu_irq_fun_t fun)     __attribute__((alias("clic_irq_request" )));
s32 cpu_irq_mode(cpu_irq_id_t id, u32 shv, u32 trig, u32 mode)  __attribute__((alias("clic_attr_cfg"    )));
s32 cpu_irq_set_nlbits(u8 nlbits)               __attribute__((alias("clic_cfg_nlbits"  )));
s32 cpu_irq_ctl(cpu_irq_id_t id, u8 prio)           __attribute__((alias("clic_ctl_cfg" )));
s32 cpu_irq_clear(cpu_irq_id_t id)              __attribute__((alias("clic_ip_clear"    )));
