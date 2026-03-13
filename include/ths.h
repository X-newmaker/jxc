#define THS_SIZE 0x1000
//0x0000 THS_MCR
#define THS_MCR_THS_EN_Pos (0U)
#define THS_MCR_THS_EN_Msk (1UL << THS_MCR_THS_EN_Pos)
#define THS_MCR_THS_EN THS_MCR_THS_EN_Msk

#define THS_MCR_SEN0_EN_Pos (16U)
#define THS_MCR_SEN0_EN_Msk (1UL << THS_MCR_SEN0_EN_Pos)
#define THS_MCR_SEN0_EN THS_MCR_SEN0_EN_Msk

#define THS_MCR_SEN1_EN_Pos (17U)
#define THS_MCR_SEN1_EN_Msk (1UL << THS_MCR_SEN1_EN_Pos)
#define THS_MCR_SEN1_EN THS_MCR_SEN1_EN_Msk

#define THS_MCR_SEN2_EN_Pos (18U)
#define THS_MCR_SEN2_EN_Msk (1UL << THS_MCR_SEN2_EN_Pos)
#define THS_MCR_SEN2_EN THS_MCR_SEN1_EN_Msk

#define THS_MCR_SEN3_EN_Pos (19U)
#define THS_MCR_SEN3_EN_Msk (1UL << THS_MCR_SEN3_EN_Pos)
#define THS_MCR_SEN3_EN THS_MCR_SEN1_EN_Msk

//0x0004 THS_MINTR
#define THS_MINTR_THS0_INTEN_Pos (0U)
#define THS_MINTR_THS0_INTEN_Msk (1UL << THS_MINTR_THS0_INTEN_Pos)
#define THS_MINTR_THS0_INTEN THS_MINTR_THS0_INTEN_Msk

#define THS_MINTR_THS1_INTEN_Pos (1U)
#define THS_MINTR_THS1_INTEN_Msk (1UL << THS_MINTR_THS1_INTEN_Pos)
#define THS_MINTR_THS1_INTEN THS_MINTR_THS1_INTEN_Msk

#define THS_MINTR_THS2_INTEN_Pos (2U)
#define THS_MINTR_THS2_INTEN_Msk (1UL << THS_MINTR_THS2_INTEN_Pos)
#define THS_MINTR_THS2_INTEN THS_MINTR_THS2_INTEN_Msk

#define THS_MINTR_THS3_INTEN_Pos (3U)
#define THS_MINTR_THS3_INTEN_Msk (1UL << THS_MINTR_THS3_INTEN_Pos)
#define THS_MINTR_THS3_INTEN THS_MINTR_THS3_INTEN_Msk

#define THS_MINTR_THS0_INTF_Pos (16U)
#define THS_MINTR_THS0_INTF_Msk (1UL << THS_MINTR_THS0_INTF_Pos)
#define THS_MINTR_THS0_INTF THS_MINTR_THS0_INTF_Msk

#define THS_MINTR_THS1_INTF_Pos (17U)
#define THS_MINTR_THS1_INTF_Msk (1UL << THS_MINTR_THS1_INTF_Pos)
#define THS_MINTR_THS1_INTF THS_MINTR_THS1_INTF_Msk

#define THS_MINTR_THS2_INTF_Pos (18U)
#define THS_MINTR_THS2_INTF_Msk (1UL << THS_MINTR_THS2_INTF_Pos)
#define THS_MINTR_THS2_INTF THS_MINTR_THS2_INTF_Msk

#define THS_MINTR_THS3_INTF_Pos (19U)
#define THS_MINTR_THS3_INTF_Msk (1UL << THS_MINTR_THS3_INTF_Pos)
#define THS_MINTR_THS3_INTF THS_MINTR_THS3_INTF_Msk

//0x008 THS_NUM
#define THSn_MAX_Pos (0U)	//[2:0]
#define THSn_MAX_Msk (7UL << THSn_MAX_Pos)
#define THSn_MAX THS_MAX_Msk

// 0x100+n*0x20 THSn_CFG
#define THSn_CFG_SSEN_Pos (0U)
#define THSn_CFG_SSEN_Msk (1UL << THSn_CFG_SSEN_Pos)
#define THSn_CFG_SSEN THSn_CFG_SSEN_Msk

#define THSn_CFG_PSEN_Pos (1U)
#define THSn_CFG_PSEN_Msk (1UL << THSn_CFG_PSEN_Pos)
#define THSn_CFG_PSEN THSn_CFG_PSEN_Msk

#define THSn_CFG_CHANNEL_STATE_Pos (2U)
#define THSn_CFG_CHANNEL_STATE_Msk (1UL << THSn_CFG_CHANNEL_STATE_Pos)
#define THSn_CFG_CHANNEL_STATE THSn_CFG_CHANNEL_STATE_Msk

#define THSn_CFG_CMD_TYPE_Pos (3U)
#define THSn_CFG_CMD_TYPE_Msk (1UL << THSn_CFG_CMD_TYPE_Pos)
#define THSn_CFG_CMD_TYPE THSn_CFG_CMD_TYPE_Msk

#define THSn_CFG_ADC_PRI_Pos (4U)
#define THSn_CFG_ADC_PRI_Msk (1UL << THSn_CFG_ADC_PRI_Pos)
#define THSn_CFG_ADC_PRI THSn_CFG_ADC_PRI_Msk

#define THSn_CFG_INVERTED_SELECT_Pos (27U)
#define THSn_CFG_INVERTED_SELECT_Msk (1UL << THSn_CFG_INVERTED_SELECT_Pos)
#define THSn_CFG_INVERTED_SELECT THSn_CFG_INVERTED_SELECT_Msk

// 0x104+n*0x20 THSn_ITV
#define THSn_ITV_DIV_Pos (0U)	//[15:0]
#define THSn_ITV_DIV_Msk (0xFFFFUL << THSn_ITV_ITV_Pos)
#define THSn_ITV_DIV THSn_ITV_ITV_Msk

#define THSn_ITV_ITV_Pos (16U)	//[31:16]
#define THSn_ITV_ITV_Msk (0xFFFFUL << THSn_ITV_ITV_Pos)
#define THSn_ITV_ITV THSn_ITV_ITV_Msk

/*
 * Divide CLK，分频时钟
 * 时钟 (div_clk) 分频系数，单位为 PCLKT (div_clk) = (DIV+1) *T (PCLK)
 *
 * Interval，采样间隔
 * 周期采样的采样间隔，单位为 T(div_clk)，即采样间隔 = ITV* T(div_clk)。
 * 假设 PCLK = 24 MHz，ITV = 0x16E = 366，DIV=65535，采样间隔 = 366 * (65535 + 1) * 41.67 ns = 1 s
 *
 */

// 0x108+n*0x20 THSn_FIL
#define THSn_FIL_FIL_Pos (0U)	//[1:0]
#define THSn_FIL_FIL_Msk (0x3UL << THSn_FIL_FIL_Pos)
#define THSn_FIL_FIL THSn_FIL_FIL_Msk

// 0x10C+n*0x20 THSn_DATA
#define THSn_DATA_DATA_Pos (0U)	//[11:0]
#define THSn_DATA_DATA_Msk (0xFFFUL << THSn_DATA_DATA_Pos)
#define THSn_DATA_DATA THSn_DATA_DATA_Msk

// 0x110+n*0x20 THSn_INT
#define THSn_INT_DRDYIE_Pos (0U)
#define THSn_INT_DRDYIE_Msk (1UL << THSn_INT_DRDYIE_Pos)
#define THSn_INT_DRDYIE THSn_INT_DRDYIE_Msk

#define THSn_INT_DOVWIE_Pos (1U)
#define THSn_INT_DOVWIE_Msk (1UL << THSn_INT_DOVWIE_Pos)
#define THSn_INT_DOVWIE THSn_INT_DOVWIE_Msk

#define THSn_INT_HTAVIE_Pos (8U)
#define THSn_INT_HTAVIE_Msk (1UL << THSn_INT_HTAVIE_Pos)
#define THSn_INT_HTAVIE THSn_INT_HTAVIE_Msk

#define THSn_INT_HTARIE_Pos (9U)
#define THSn_INT_HTARIE_Msk (1UL << THSn_INT_HTARIE_Pos)
#define THSn_INT_HTARIE THSn_INT_HTARIE_Msk

#define THSn_INT_LTAVIE_Pos (10U)
#define THSn_INT_LTAVIE_Msk (1UL << THSn_INT_LTAVIE_Pos)
#define THSn_INT_LTAVIE THSn_INT_LTAVIE_Msk

#define THSn_INT_LTARIE_Pos (11U)
#define THSn_INT_LTARIE_Msk (1UL << THSn_INT_LTARIE_Pos)
#define THSn_INT_LTARIE THSn_INT_LTARIE_Msk

#define THSn_INT_OTPE_Pos (12U)	//[15:12]
#define THSn_INT_OTPE_Msk (0xFUL << THSn_INT_OTPE_Pos)
#define THSn_INT_OTPE THSn_INT_OTPE_Msk

#define THSn_INT_DRDYF_Pos (16U)
#define THSn_INT_DRDYF_Msk (1UL << THSn_INT_DRDYF_Pos)
#define THSn_INT_DRDYF THSn_INT_DRDYF_Msk

#define THSn_INT_DOVWF_Pos (17U)
#define THSn_INT_DOVWF_Msk (1UL << THSn_INT_DOVWF_Pos)
#define THSn_INT_DOVWF THSn_INT_DOVWF_Msk

#define THSn_INT_HTAVF_Pos (24U)
#define THSn_INT_HTAVF_Msk (1UL << THSn_INT_HTAVF_Pos)
#define THSn_INT_HTAVF THSn_INT_HTAVF_Msk

#define THSn_INT_HTARF_Pos (25U)
#define THSn_INT_HTARF_Msk (1UL << THSn_INT_HTARF_Pos)
#define THSn_INT_HTARF THSn_INT_HTARF_Msk

#define THSn_INT_LTAVF_Pos (26U)
#define THSn_INT_LTAVF_Msk (1UL << THSn_INT_LTAVF_Pos)
#define THSn_INT_LTAVF THSn_INT_LTAVF_Msk

#define THSn_INT_LTARF_Pos (27U)
#define THSn_INT_LTARF_Msk (1UL << THSn_INT_LTARF_Pos)
#define THSn_INT_LTARF THSn_INT_LTARF_Msk

#define THSn_INT_OTPF_Pos (28U)
#define THSn_INT_OTPF_Msk (1UL << THSn_INT_OTPF_Pos)
#define THSn_INT_OTPF THSn_INT_OTPF_Msk

//0x114+n*0x20 THSn_HTAV
#define THSn_HTAV_HTAVV_Pos (0U)	//[11:0]
#define THSn_HTAV_HTAVV_Msk (0xFFFUL << THSn_HTAV_HTAVV_Pos)
#define THSn_HTAV_HTAVV THSn_HTAV_HTAVV_Msk

#define THSn_HTAV_HTARV_Pos (16U)	//[27:16]
#define THSn_HTAV_HTARV_Msk (0xFFFUL << THSn_HTAV_HTARV_Pos)
#define THSn_HTAV_HTARV THSn_HTAV_HTARV_Msk

#define THSn_HTAV_HTAE_Pos (31U)
#define THSn_HTAV_HTAE_Msk (1UL << THSn_HTAV_HTAE_Pos)
#define THSn_HTAV_HTAE THSn_HTAV_HTAE_Msk

// 0x118+n*0x20 THSn_LTAV
#define THSn_LTAV_LTAVV_Pos (0U)	//[11:0]
#define THSn_LTAV_LTAVV_Msk (0xFFFUL << THSn_LTAV_LTAVV_Pos)
#define THSn_LTAV_LTAVV THSn_LTAV_LTAVV_Msk

#define THSn_LTAV_LTARV_Pos (16U)	//[27:16]
#define THSn_LTAV_LTARV_Msk (0xFFFUL << THSn_LTAV_LTARV_Pos)
#define THSn_LTAV_LTARV THSn_LTAV_LTARV_Msk

#define THSn_LTAV_LTAE_Pos (31U)
#define THSn_LTAV_LTAE_Msk (1UL << THSn_LTAV_LTAE_Pos)
#define THSn_LTAV_LTAE THSn_LTAV_LTAE_Msk

//0x11C+n*0x20 THSn_OTPV
#define THSn_OTPV_OTPV_Pos (0U)	//[11:0]
#define THSn_OTPV_OTPV_Msk (0xFFFUL << THSn_OTPV_OTPV_Pos)
#define THSn_OTPV_OTPV THSn_OTPV_OTPV_Msk

#define THSn_OTPV_OTPE_Pos (31U)
#define THSn_OTPV_OTPE_Msk (1UL << THSn_OTPV_OTPE_Pos)
#define THSn_OTPV_OTPE THSn_OTPV_OTPE_Msk

typedef struct
{
	u32 THSn_CFG;  //offset:0x100+n*0x20
	u32 THSn_ITV;  //offset:0x104+n*0x20
	u32 THSn_FIL;  //offset:0x108+n*0x20
	u32 THSn_DATA; //offset:0x10C+n*0x20
	u32 THSn_INT;  //offset:0x110+n*0x20
	u32 THSn_HTAV; //offset:0x114+n*0x20
	u32 THSn_LTAV; //offset:0x118+n*0x20
	u32 THSn_OTPV; //offset:0x11C+n*0x20
} THSn_TypeDef;

typedef struct
{
	volatile u32 THS_MCR;   //offset:0x00
	volatile u32 THS_MINTR; //offset:0x04
	volatile u32 THS_NUM;   //offset:0x08
	volatile u32 RES0[61];
	volatile THSn_TypeDef THSn[4]; //offset:0x100
	volatile u32 RES2[927];
	volatile u32 VERSION; //offset:0xFFC
} THS_TypeDef;
