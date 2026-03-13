/*
 * gpio.c
 */

#include <all_inc.h>

gpio_dev_t* const gpio_dev_p = (gpio_dev_t*)BASE_GPIO;

static void gpioa_null(void){};
static void gpiob_null(void){};
static void gpioc_null(void){};
static void gpiod_null(void){};
static void gpioe_null(void){};
static void gpiof_null(void){};
static void gpiog_null(void){};
static void gpiok_null(void){};
cpu_irq_fun_t gpio_a_irqhandle = gpioa_null;
cpu_irq_fun_t gpio_b_irqhandle = gpiob_null;
cpu_irq_fun_t gpio_c_irqhandle = gpioc_null;
cpu_irq_fun_t gpio_d_irqhandle = gpiod_null;
cpu_irq_fun_t gpio_e_irqhandle = gpioe_null;
cpu_irq_fun_t gpio_f_irqhandle = gpiof_null;
cpu_irq_fun_t gpio_g_irqhandle = gpiog_null;
cpu_irq_fun_t gpio_k_irqhandle = gpiok_null;

ATTRIBUTE_ISR void GPIO_A_IRQHandler(void)
{
        gpio_a_irq_handler();
}

void gpio_a_irq_handler(void)
{
        gpio_a_irqhandle();
}

ATTRIBUTE_ISR void GPIO_B_IRQHandler(void)
{
        gpio_b_irq_handler();
}

void gpio_b_irq_handler(void)
{
        gpio_b_irqhandle();
}

ATTRIBUTE_ISR void GPIO_C_IRQHandler(void)
{
        gpio_c_irq_handler();
}

void gpio_c_irq_handler(void)
{
        gpio_c_irqhandle();
}

ATTRIBUTE_ISR void GPIO_D_IRQHandler(void)
{
        gpio_d_irq_handler();
}

void gpio_d_irq_handler(void)
{
        gpio_d_irqhandle();
}

ATTRIBUTE_ISR void GPIO_E_IRQHandler(void)
{
        gpio_e_irq_handler();
}

void gpio_e_irq_handler(void)
{
        gpio_e_irqhandle();
}

ATTRIBUTE_ISR void GPIO_F_IRQHandler(void)
{
        gpio_f_irq_handler();
}

void gpio_f_irq_handler(void)
{
        gpio_f_irqhandle();
}

ATTRIBUTE_ISR void GPIO_G_IRQHandler(void)
{
        gpio_g_irq_handler();
}

void gpio_g_irq_handler(void)
{
        gpio_g_irqhandle();
}

ATTRIBUTE_ISR void GPIO_K_IRQHandler(void)
{
        gpio_k_irq_handler();
}

void gpio_k_irq_handler(void)
{
        gpio_k_irqhandle();
}

void gpio_irq_register(gpio_grp_t num, cpu_irq_fun_t irqhandle)
{
        switch(num){
                case GPIO_GRP_A:
                        gpio_a_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_GPA);
                        break;
                case GPIO_GRP_B:
                        gpio_b_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_GPB);
                        break;
                case GPIO_GRP_C:
                        gpio_c_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_GPC);
                        break;
                case GPIO_GRP_D:
                        gpio_d_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_GPD);
                        break;
                case GPIO_GRP_E:
                        gpio_e_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_GPE);
                        break;
                case GPIO_GRP_F:
                        gpio_f_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_GPF);
                        break;
                case GPIO_GRP_G:
                        gpio_g_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_GPG);
                        break;
                case GPIO_GRP_K:
                        gpio_k_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_GPK);
                        break;
		default:
                        break;               
        }
}

void gpio_irq_unregister(gpio_grp_t num)
{
        switch(num){
                case GPIO_GRP_A:
                        gpio_a_irqhandle = gpioa_null;
                        cpu_irq_disable(CPU_IRQ_GPA);
                        break;
                case GPIO_GRP_B:
                        gpio_b_irqhandle = gpiob_null;
                        cpu_irq_disable(CPU_IRQ_GPB);
                        break;
                case GPIO_GRP_C:
                        gpio_c_irqhandle = gpioc_null;
                        cpu_irq_disable(CPU_IRQ_GPC);
                        break;
                case GPIO_GRP_D:
                        gpio_d_irqhandle = gpiod_null;
                        cpu_irq_disable(CPU_IRQ_GPD);
                        break;
                case GPIO_GRP_E:
                        gpio_e_irqhandle = gpioe_null;
                        cpu_irq_disable(CPU_IRQ_GPE);
                        break;
                case GPIO_GRP_F:
                        gpio_f_irqhandle = gpiof_null;
                        cpu_irq_disable(CPU_IRQ_GPF);
                        break;
                case GPIO_GRP_G:
                        gpio_g_irqhandle = gpiog_null;
                        cpu_irq_disable(CPU_IRQ_GPG);
                        break;
                case GPIO_GRP_K:
                        gpio_k_irqhandle = gpiok_null;
                        cpu_irq_disable(CPU_IRQ_GPK);
                        break;
                default:
                        break;               
        }
}

s32 init_gpio(void)
{
        int i = 0;
        cmu_mod_disable(CMU_MOD_GPIO);
        for(i=0; i<0x10; i++);
        cmu_mod_enable(CMU_MOD_GPIO);

	return RET_OK;
}

s32 gpio_request(const u16* pin, u32 sel, u32 mask, gpio_drv_t drv, gpio_pull_t pull)
{
	u32 n = *pin;
	u16 v,g,p,s,i;

	if(sel>=*(pin+1))
		return RET_FALSE;

	for(i=0; i<n; i++)
	{
		if(mask>>i & 1)
			continue;

		v = *(pin+sel*n+i+2);
		if(v==GPIO_NONE)
			continue;

		g = v >> 12 & 0xf;
		p = v >> 4  & 0x1f;
		s = v & 0xf;

		gpio_dev_p->grp_cfg[g].pin_cfg[p].bits.pin_fun = s;
		gpio_dev_p->grp_cfg[g].pin_cfg[p].bits.pin_drv = drv;
		gpio_dev_p->grp_cfg[g].pin_cfg[p].bits.pin_pull = pull;
	}

	return RET_OK;
}

s32 gpio_release(const u16* pin, u32 sel, u32 mask)
{
	u32 n = *pin;
	u16 v,g,p,i;

	if(sel>=*(pin+1))
		return RET_FALSE;

	for(i=0; i<n; i++)
	{
		if(mask>>i & 1)
			continue;

		v = *(pin+sel*n+i+2);
		if(v==GPIO_NONE)
			continue;

		g = v >> 12 & 0xf;
		p = v >> 4  & 0x1f;

		gpio_dev_p->grp_cfg[g].pin_cfg[p].bits.pin_fun = GPIO_FUN_DIS;
		gpio_dev_p->grp_cfg[g].pin_cfg[p].bits.pin_drv = 0;
		gpio_dev_p->grp_cfg[g].pin_cfg[p].bits.pin_pull = GPIO_PULL_NONE;
	}

	return RET_OK;
}

s32 gpio_enable(gpio_grp_t grp, u32 pin, u32 num, gpio_fun_t fun)
{
	u32 i;

	for(i=0; i<num; i++)	{
		gpio_dev_p->grp_cfg[grp].pin_cfg[(pin+i)&0x1f].bits.gen_ie = (fun == GPIO_FUN_IO || fun == GPIO_FUN_I);
		gpio_dev_p->grp_cfg[grp].pin_cfg[(pin+i)&0x1f].bits.gen_oe = (fun == GPIO_FUN_IO || fun == GPIO_FUN_O);
		gpio_dev_p->grp_cfg[grp].pin_cfg[(pin+i)&0x1f].bits.pin_fun = (fun<16) ? fun : 1;
	}

	return RET_OK;
}

s32 gpio_disable(gpio_grp_t grp, u32 pin, u32 num)
{
	u32 i;

	for(i=0; i<num; i++)	{
		gpio_dev_p->grp_cfg[grp].pin_cfg[(pin+i)&0x1f].bits.pin_fun = 0;
	}

	return RET_OK;
}

s32 gpio_pin_cfg(gpio_grp_t grp, u32 pin, u32 num, gpio_drv_t drv, gpio_pull_t pull)
{
	u32 i;

	for(i=0; i<num; i++)	{
		gpio_dev_p->grp_cfg[grp].pin_cfg[(pin+i)&0x1f].bits.pin_drv = drv;
		gpio_dev_p->grp_cfg[grp].pin_cfg[(pin+i)&0x1f].bits.pin_pull = pull;
	}

	return RET_OK;
}

s32 gpio_set_val(gpio_grp_t grp, u32 pin, gpio_level_t level)
{
	if(level == GPIO_LEVEL_HIGH)
		gpio_dev_p->grp_cfg[grp].gen_out_cfg.bits.out_cfg |= 1<<(pin&0x1f);
	else
		gpio_dev_p->grp_cfg[grp].gen_out_cfg.bits.out_cfg &= ~(1<<(pin&0x1f));

	return RET_OK;
}

gpio_level_t gpio_get_val(gpio_grp_t grp, u32 pin)
{
	if(gpio_dev_p->grp_cfg[grp].gen_in_sta.bits.in_sta & 1<<(pin&0x1f))
		return GPIO_LEVEL_HIGH;
	else
		return GPIO_LEVEL_LOW;
}

/*通用输入一级去抖采样点数，0-15个AHB时钟*/
s32 gpio_db0_point(gpio_grp_t grp, u32 pin, u32 point)
{
	gpio_dev_p->grp_cfg[grp].pin_cfg[pin&0x1f].bits.gen_in_db0_point = point;

	return RET_OK;
}

/*通用输入二级去抖采样点数，0-15个采样周期*/
s32 gpio_db1_point(gpio_grp_t grp, u32 pin, u32 point)
{
	gpio_dev_p->grp_cfg[grp].pin_cfg[pin&0x1f].bits.gen_in_db1_point = point;

	return RET_OK;
}

/*通用输入二级去抖采样周期，采样周期为2^(SAMP+1)个AHB时钟*/
s32 gpio_db1_samp(gpio_grp_t grp, u32 pin, u32 samp)
{
	gpio_dev_p->grp_cfg[grp].pin_cfg[pin&0x1f].bits.gen_in_db1_samp = samp;

	return RET_OK;
}

s32 gpio_irq_mode(gpio_grp_t grp, u32 pin, gpio_irq_t mode)
{
	gpio_dev_p->grp_cfg[grp].pin_cfg[pin&0x1f].bits.gen_irq_mode = mode;

	return RET_OK;
}

s32 gpio_irq_enable(gpio_grp_t grp, u32 pin)
{
	gpio_dev_p->grp_cfg[grp].gen_irq_en.bits.irq_en |= 1<<(pin&0x1f);

	return RET_OK;
}

s32 gpio_irq_disable(gpio_grp_t grp, u32 pin)
{
	gpio_dev_p->grp_cfg[grp].gen_irq_en.bits.irq_en &= ~(1<<(pin&0x1f));

	return RET_OK;
}

u32 gpio_irq_query(gpio_grp_t grp)
{
	return gpio_dev_p->grp_cfg[grp].gen_irq_sta.bits.irq_sta;
}

s32 gpio_irq_clear(gpio_grp_t grp, u32 status)
{
	if(status)
		gpio_dev_p->grp_cfg[grp].gen_irq_sta.dwval = status;

	return RET_OK;
}

s32 gpio_clr(gpio_grp_t grp, u32 pin)
{
	gpio_dev_p->grp_cfg[grp].gen_out_clr.bits.out_cfg_clr |= 1<<(pin&0x1f);
	return RET_OK;
}

s32 gpio_set(gpio_grp_t grp, u32 pin)
{
	gpio_dev_p->grp_cfg[grp].gen_out_set.bits.out_cfg_set |= 1<<(pin&0x1f);
	return RET_OK;
}

s32 gpio_tog(gpio_grp_t grp, u32 pin)
{
	gpio_dev_p->grp_cfg[grp].gen_out_tog.bits.out_cfg_tog |= 1<<(pin&0x1f);
	return RET_OK;
}

