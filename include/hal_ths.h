#ifndef __M700x_LL_THS_H
#define __M700x_LL_THS_H


#include "common_type.h"
#include "ths.h"

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define IS_BITMASK_SET(REG, MASK) (((u32)(REG) & (u32)(MASK)) != 0U)
#define THS_BASE 0x11052000UL        /* 0x11052000 - 0x11052FFF, 4 KB      */
#define THS ((THS_TypeDef *)THS_BASE)

void LL_THS_RegisterIrq(cpu_irq_fun_t IrqHandle);
void LL_THS_UnregisterIrq(void);
void LL_THS_InitClock(void);
void THSn_Init(u8 Index);

typedef enum
{
	THS_FIL_NULL_POINT = 0, // 无采样
	THS_FIL_TWO_POINT,      // 两点采样
	THS_FIL_FOUR_POINT,     // 四点采样
	THS_FIL_EIGHT_POINT,    // 八点采样
} ThsFilPoint_TypeDef;

typedef enum
{
	THS_OTPE_OTHERS = 0, 		// 过温保护禁止
	THS_OTPE_IRQ_EN = 0x5, 		// 过温保护中断使能
	THS_OTPE_RESET_EN = 0xA,	// 过温保护复位使能
} ThsOtpe_TypeDef;

// THS 模块使能
__STATIC_INLINE void LL_THS_EnableModule(THS_TypeDef *THSx)
{
    SET_BIT(THSx->THS_MCR, THS_MCR_THS_EN);
}

// THS 模块使能禁止
__STATIC_INLINE void LL_THS_DisableModule(THS_TypeDef *THSx)
{
    CLEAR_BIT(THSx->THS_MCR, THS_MCR_THS_EN);
}

/**
 * @brief THS 传感器使能
 * @param THSx THS模块寄存器指针
 * @param Mask 传感器使能
 *        @arg THS_MCR_SEN0_EN             THS0 传感器使能
 *        @arg THS_MCR_SEN1_EN             THS1 传感器使能
 *        @arg THS_MCR_SEN2_EN             THS2 传感器使能
 *        @arg THS_MCR_SEN3_EN             THS3 传感器使能
 * @retval None
 */
__STATIC_INLINE void LL_THS_Enable(THS_TypeDef *THSx, u32 Mask)
{
    SET_BIT(THSx->THS_MCR, Mask);
}

/**
 * @brief THS 传感器禁止
 * @param THSx THS模块寄存器指针
 * @param Mask 传感器禁止
 *        @arg THS_MCR_SEN0_EN             THS0 传感器禁止
 *        @arg THS_MCR_SEN1_EN             THS1 传感器禁止
 *        @arg THS_MCR_SEN2_EN             THS2 传感器禁止
 *        @arg THS_MCR_SEN3_EN             THS3 传感器禁止
 * @retval None
 */
__STATIC_INLINE void LL_THS_Disable(THS_TypeDef *THSx, u32 Mask)
{
    CLEAR_BIT(THSx->THS_MCR, Mask);
}

/**
 * @brief THS 传感器中断使能
 * @param THSx THS模块寄存器指针
 * @param Mask 传感器中断使能
 *        @arg THS_MINTR_THS0_INTEN             THS0 传感器中断使能
 *        @arg THS_MINTR_THS1_INTEN             THS1 传感器中断使能
 *        @arg THS_MINTR_THS2_INTEN             THS2 传感器中断使能
 *        @arg THS_MINTR_THS3_INTEN             THS3 传感器中断使能
 * @retval None
 */
__STATIC_INLINE void LL_THS_EnableIrq(THS_TypeDef *THSx, u32 IrqMask)
{
    SET_BIT(THSx->THS_MINTR, IrqMask);
}

/**
 * @brief THS 传感器中断禁止
 * @param THSx THS模块寄存器指针
 * @param Mask 传感器中断禁止
 *        @arg THS_MINTR_THS0_INTEN             THS0 传感器中断禁止
 *        @arg THS_MINTR_THS1_INTEN             THS1 传感器中断禁止
 *        @arg THS_MINTR_THS2_INTEN             THS2 传感器中断禁止
 *        @arg THS_MINTR_THS3_INTEN             THS3 传感器中断禁止
 * @retval None
 */
__STATIC_INLINE void LL_THS_DisableIrq(THS_TypeDef *THSx, u32 IrqMask)
{
    CLEAR_BIT(THSx->THS_MINTR, IrqMask);
}

// 获取中断标志
__STATIC_INLINE u32 LL_THS_GetIrqStatusN(THS_TypeDef *THSx)
{
    return READ_REG(THSx->THS_MINTR);
}

// 获取 THS 数量
__STATIC_INLINE u32 LL_THS_GetThsNum(THS_TypeDef *THSx)
{
    return READ_BIT(THSx->THS_NUM, THSn_MAX_Msk);
}

// 温度传感器单点采样使能
__STATIC_INLINE void LL_THS_EnableSigleSampleN(THS_TypeDef *THSx, u8 Index)
{
    SET_BIT(THSx->THSn[Index].THSn_CFG, THSn_CFG_SSEN);
}

// 温度传感器单点采样禁止
__STATIC_INLINE void LL_THS_DIsableSigleSampleN(THS_TypeDef *THSx, u8 Index)
{
    CLEAR_BIT(THSx->THSn[Index].THSn_CFG, THSn_CFG_SSEN);
}

// 温度传感器周期采样使能
__STATIC_INLINE void LL_THS_EnablePeriodicSampleN(THS_TypeDef *THSx, u8 Index)
{
    SET_BIT(THSx->THSn[Index].THSn_CFG, THSn_CFG_PSEN);
}

// 温度传感器周期采样禁止
__STATIC_INLINE void LL_THS_DisablePeriodicSampleN(THS_TypeDef *THSx, u8 Index)
{
    CLEAR_BIT(THSx->THSn[Index].THSn_CFG, THSn_CFG_PSEN);
}

// 获取 THS 工作状态
__STATIC_INLINE u32 LL_THS_GetChannelNState(THS_TypeDef *THSx, u8 Index)
{
	return READ_BIT(THSx->THSn[Index].THSn_CFG, THSn_CFG_CHANNEL_STATE);
}

// 配置被动模式，默认是主动模式
__STATIC_INLINE void LL_THS_SetCmdType(THS_TypeDef *THSx, u8 Index, u32 CmdType)
{
    MODIFY_REG(THSx->THSn[Index].THSn_CFG, THSn_CFG_CMD_TYPE_Msk, CmdType << THSn_CFG_CMD_TYPE_Pos);
}

// 设置周期采样的采样间隔
__STATIC_INLINE void LL_THS_SetInterval(THS_TypeDef *THSx, u8 Index, u32 Itv)
{
    MODIFY_REG(THSx->THSn[Index].THSn_ITV, THSn_ITV_ITV_Msk, (Itv << THSn_ITV_ITV_Pos));
}

// 滤波器配置
__STATIC_INLINE void LL_THS_SetFilter(THS_TypeDef *THSx, u8 Index, ThsFilPoint_TypeDef ThsFil)
{
    MODIFY_REG(THSx->THSn[Index].THSn_FIL, THSn_FIL_FIL_Msk, (ThsFil << THSn_FIL_FIL_Pos));
}

// ADC采样数据获取
__STATIC_INLINE u32 LL_THS_GetData(THS_TypeDef *THSx, u8 Index)
{
    //    return READ_REG(THSx->THSn[Index].THSn_DATA);
    return READ_BIT(THSx->THSn[Index].THSn_DATA, THSn_DATA_DATA);
}

// 使能中断
__STATIC_INLINE void LL_THS_EnableIrq_THSn(THS_TypeDef *THSx, u8 Index, u32 IrqSource)
{
    SET_BIT(THSx->THSn[Index].THSn_INT, IrqSource);
}

// 数据有效中断使能
__STATIC_INLINE void LL_THS_EnableIrqDrdyie(THS_TypeDef *THSx, u8 Index)
{
    SET_BIT(THSx->THSn[Index].THSn_INT, THSn_INT_DRDYIE);
}

// 获取中断状态
__STATIC_INLINE u32 LL_THS_GetIrqStatus(THS_TypeDef *THSx, u8 Index)
{
    return READ_REG(THSx->THSn[Index].THSn_INT);
}

// 清楚中断状态
__STATIC_INLINE void LL_THS_ClearIrqStatus(THS_TypeDef *THSx, u8 Index, u32 IrqSource)
{
    SET_BIT(THSx->THSn[Index].THSn_INT, IrqSource);
}

// 设置过温功能选择
__STATIC_INLINE void LL_THS_SetOtps(THS_TypeDef *THSx, u8 Index, ThsOtpe_TypeDef Otps)
{
	MODIFY_REG(THSx->THSn[Index].THSn_INT, THSn_INT_OTPE_Msk, (Otps << THSn_INT_OTPE_Pos));
}

// 高温警报使能
__STATIC_INLINE void LL_THS_EnableHtav(THS_TypeDef *THSx, u8 Index)
{
    SET_BIT(THSx->THSn[Index].THSn_HTAV, THSn_HTAV_HTAE);
}

// 高温警报解除阈值配置
__STATIC_INLINE void LL_THS_SetHtarv(THS_TypeDef *THSx, u8 Index, u32 Htarv)
{
    MODIFY_REG(THSx->THSn[Index].THSn_HTAV, THSn_HTAV_HTARV_Msk, (Htarv << THSn_HTAV_HTARV_Pos));
}

// 高温警报有效阈值配置
__STATIC_INLINE void LL_THS_SetHtavv(THS_TypeDef *THSx, u8 Index, u32 Htavv)
{
    MODIFY_REG(THSx->THSn[Index].THSn_HTAV, THSn_HTAV_HTAVV_Msk, (Htavv << THSn_HTAV_HTAVV_Pos));
}

// 低温警报使能
__STATIC_INLINE void LL_THS_EnableLtae(THS_TypeDef *THSx, u8 Index)
{
    SET_BIT(THSx->THSn[Index].THSn_LTAV, THSn_LTAV_LTAE);
}

// 低温警报解除阈值配置
__STATIC_INLINE void LL_THS_SetLtarv(THS_TypeDef *THSx, u8 Index, u32 Ltarv)
{
    MODIFY_REG(THSx->THSn[Index].THSn_LTAV, THSn_LTAV_LTARV_Msk, (Ltarv << THSn_LTAV_LTARV_Pos));
}

// 低温警报有效阈值配置
__STATIC_INLINE void LL_THS_SetLtavv(THS_TypeDef *THSx, u8 Index, u32 Ltavv)
{
    MODIFY_REG(THSx->THSn[Index].THSn_LTAV, THSn_LTAV_LTAVV_Msk, (Ltavv << THSn_LTAV_LTAVV_Pos));
}

// 过温保护使能
__STATIC_INLINE void LL_THS_EnableOtpe(THS_TypeDef *THSx, u8 Index)
{
    SET_BIT(THSx->THSn[Index].THSn_OTPV, THSn_OTPV_OTPE);
}

// 过温保护阈值配置
__STATIC_INLINE void LL_THS_SetOtpv(THS_TypeDef *THSx, u8 Index, u32 Otpv)
{
    MODIFY_REG(THSx->THSn[Index].THSn_OTPV, THSn_OTPV_OTPV_Msk, (Otpv << THSn_OTPV_OTPV_Pos));
}

#endif /* __M700x_LL_THS_H */
