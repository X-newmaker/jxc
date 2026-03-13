/*
 * ledcode.h
 *
 *  Created on: 2023年8月11日
 *      Author: wenxing.ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_LEDCODE_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_LEDCODE_H_
#include "stdint.h"
#define DISP_ZERO      0x3F
#define DISP_ONE       0x06
#define DISP_TWO      0x5B
#define DISP_THREE   0x4F
#define DISP_FOUR    0x66
#define DISP_FIVE      0x6D
#define DISP_SIX        0x7D
#define DISP_SEVEN  0x07
#define DISP_EIGHT   0x7F
#define DISP_NINE    0x6F

#define DISP_A      0x77
#define DISP_B      0x7C
#define DISP_C      0x39
#define DISP_D      0x5E
#define DISP_E      0x79
#define DISP_F      0x71

#define DISP_H      0x76
#define DISP_I      0x06
#define DISP_J      0x1E
#define DISP_L      0x38

#define DISP_N      0x54
#define DISP_O      0x5C
#define DISP_P      0x73
#define DISP_Q      0x67
#define DISP_R      0x50
#define DISP_S      0x6D
#define DISP_T      0x78
#define DISP_U      0x3E
#define DISP_W      0x7E
#define		COMMON_SEG_NEGATIVE		1		//共阴数码管



#define DISP_HENG        0x40

typedef enum
{
	KEY_NULL	= 0,	//无效按键值
    KEY_UP      = 1,    //up	键值
    KEY_SET     = 2,    //set	键值
    KEY_DOWN    = 3,    //donw	键值
    KEY_SHIFT   = 4,    //shift	键值  //在第一层菜单时候，shift可以减小的方式 如：P3->P2组，cancel是递增的方式，如P2->P3
    KEY_MODE    = 5,    //cancel键值  //在第一层菜单时候，shift可以减小的方式 如：P3->P2组，cancel是递增的方式，如P2->P3
	KEY_MAX		= 6,

}KEYVALUE;

 //按键通信读回的值
#define		KEYDATA_CANCEL		0x3c	//CANCEL 	11 1100
#define		KEYDATA_UP			0x3a		//UP	11 1010
#define		KEYDATA_DOWN		0x36		//DOWN	11 0110
#define		KEYDATA_SHIFT		0x2e		//SHIFT 10 1110
#define		KEYDATA_SET			0x1e		//SET   01 1110

#define		KEYMSK_SIGN			0x3e

#define     KEYDATA_MAX         0x3c		//最大值，主要用于判断是否有有效按键
#define     KEYDATA_MIN         0x1e		//最小值，主要用于判断是否有有效按键

//以下宏与----菜单显示---结构相关
#define		SHOW		((u32)1<<0)		//显示
#define		NSHOW		(0)		//不显示

#define		SAVE		((u32)1<<1)		//保存
#define		NSAVE		(0)		//不保存

#define		MDIFY		((u32)1<<2)		//可修改
#define		NMDIFY		(0)		//不可修改

#define		PTS00000		((u32)0x0<<3)		//不需要小数点
#define		PTS00001		((u32)0x1<<3)		//小数点  bit00001
#define		PTS00010		((u32)0x2<<3)		//小数点  bit00010
#define		PTS00011		((u32)0x3<<3)		//小数点  bit00011
#define		PTS00100		((u32)0x4<<3)		//小数点  bit00100
#define		PTS00101		((u32)0x5<<3)		//小数点  bit00101
#define		PTS00110		((u32)0x6<<3)		//小数点  bit00110
#define		PTS00111		((u32)0x7<<3)		//小数点  bit00111
#define		PTS01000		((u32)0x8<<3)		//小数点  bit01000
#define		PTS01001		((u32)0x9<<3)		//小数点  bit01001
#define		PTS01010		((u32)0xA<<3)		//小数点  bit01010
#define		PTS01011		((u32)0xB<<3)		//小数点  bit01011
#define		PTS01100		((u32)0xC<<3)		//小数点  bit01100
#define		PTS01101		((u32)0xD<<3)		//小数点  bit01101
#define		PTS01110		((u32)0xE<<3)		//小数点  bit01110
#define		PTS01111		((u32)0xF<<3)		//小数点  bit01111
#define		PTS10000		((u32)0x10<<3)		//小数点  bit10000
#define		PTS10001		((u32)0x11<<3)		//小数点  bit10001
#define		PTS10010		((u32)0x12<<3)		//小数点  bit10010
#define		PTS10011		((u32)0x13<<3)		//小数点  bit10011
#define		PTS10100		((u32)0x14<<3)		//小数点  bit10100
#define		PTS10101		((u32)0x15<<3)		//小数点  bit10101
#define		PTS10110		((u32)0x16<<3)		//小数点  bit10110
#define		PTS10111		((u32)0x17<<3)		//小数点  bit10111
#define		PTS11000		((u32)0x18<<3)		//小数点  bit11000
#define		PTS11001		((u32)0x19<<3)		//小数点  bit11001
#define		PTS11010		((u32)0x1A<<3)		//小数点  bit11010
#define		PTS11011		((u32)0x1B<<3)		//小数点  bit11011
#define		PTS11100		((u32)0x1C<<3)		//小数点  bit11100
#define		PTS11101		((u32)0x1D<<3)		//小数点  bit11101
#define		PTS11110		((u32)0x1E<<3)		//小数点  bit11110
#define		PTS11111		((u32)0x1F<<3)		//小数点  bit11111

#define		DISP_NUM0		((u32)0<<8)			//显示 0位
#define		DISP_NUM1		((u32)1<<8)			//显示 1位
#define		DISP_NUM2		((u32)2<<8)			//显示 2位
#define		DISP_NUM3		((u32)3<<8)			//显示 3位
#define		DISP_NUM4		((u32)4<<8)			//显示 4位
#define		DISP_NUM5		((u32)5<<8)			//显示 5位
//以上宏与----菜单显示---结构相关
/************************************************************/
#define DISP_HENG        0x40
#define DISP_NULL        0x00
#define	SEG_POINT	     0x80		//数码管显示小数点
extern int16_t Jog_no_key_cnt;
extern KEYVALUE key_code;
extern int16_t led_num;
extern int16_t Jr_flag;
extern int16_t disp_mod;
extern int16_t layer;
extern int16_t layer1no;
extern int16_t layer2dpno;
extern int16_t layer1pano;
extern int16_t key_code_3s;
extern int16_t MotorParDefCnt;
extern int16_t key_delay_tick;
extern int16_t ParaNum;
extern int16_t ParaTotal;
extern int16_t Par0Num;
extern int16_t Par1Num;
extern int16_t Par2Num;
extern int16_t Par3Num;
extern int16_t Par4Num;
extern int16_t logo_disp_cnt;
extern int16_t logo_disp_delay;
extern int16_t PamodiEnable;
extern PARAMETER_DATA ParaIint[];
extern int16_t svo_alm1[32];
extern int16_t data_buffer[12];
extern uint16_t led_buffer[6];

extern void key_display(void);
extern void MS_DISPLAY(void);
extern void DefDispItem(int16_t DpLayerItem);
extern void dp_parameter_disp(int16_t DispData[12]);
extern void InitSpiDisp(void);
extern void GenFreq250HzFunc(uint16_t freq);
extern void GenFreq20HzFunc(uint16_t freq);
u8 key_display_spitx_rx(u32 index,u16 data);

#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_LEDCODE_H_ */
