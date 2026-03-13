#ifndef AIC_ECAT_HW_H_
#define AIC_ECAT_HW_H_

#include "ecatappl.h"
#include "esc.h"

typedef union
{
    unsigned int    Word;
    unsigned char    Byte[4];
} UBYTETOWORD;

typedef union
{
    UINT8           Byte[2];
    UINT16          Word;
} UALEVENT;

#define ECAT_PORT0_GRP                  GPIO_GRP_C
#define ECAT_PORT0_PIN_START            0
#define ECAT_PORT0_PIN_SUM              15
#define ECAT_PORT0_PIN_FUN              GPIO_FUN_6

#define ECAT_PORT1_GRP                  GPIO_GRP_D
#define ECAT_PORT1_PIN_START            0
#define ECAT_PORT1_PIN_SUM              15
#define ECAT_PORT1_PIN_FUN              GPIO_FUN_6

#define ECAT_PORT2_GRP                  GPIO_GRP_D
#define ECAT_PORT2_PIN_START            15
#define ECAT_PORT2_PIN_SUM              15
#define ECAT_PORT2_PIN_FUN              GPIO_FUN_5

#define ECAT_EEPROM_GRP                 GPIO_GRP_G
#define ECAT_EEPROM_PIN_START           10
#define ECAT_EEPROM_PIN_SUM             2
#define ECAT_EEPROM_PIN_FUN             GPIO_FUN_6

#define ECAT_MI_GRP                     GPIO_GRP_C
#define ECAT_MI_PIN_START               16
#define ECAT_MI_PIN_SUM                 3
#define ECAT_MI_PIN_FUN                 GPIO_FUN_6
#define ECAT_MI_PIN_DRV                 GPIO_DRV_26R

#define ECAT_PHY_CLK_GRP                GPIO_GRP_C
#define ECAT_PHY_CLK_PIN_START          15
#define ECAT_PHY_CLK_PIN_SUM            1
#define ECAT_PHY_CLK_PIN_FUN            GPIO_FUN_6
#define ECAT_PHY_CLK_PIN_DRV            GPIO_DRV_26R

#define ECAT_SYNC0_GRP                  GPIO_GRP_E
#define ECAT_SYNC0_PIN_START            17
#define ECAT_SYNC0_PIN_SUM              1
#define ECAT_SYNC0_PIN_FUN              GPIO_FUN_5

#define ECAT_LED_GRP GPIO_GRP_E
#define ECAT_LED_PIN_START 21
#define ECAT_LED_PIN_SUM 3
#define ECAT_LED_PIN_FUN GPIO_FUN_5

//#define ECAT_SYNC1_GRP                  GPIO_GRP_A
//#define ECAT_SYNC1_PIN_START            26
//#define ECAT_SYNC1_PIN_SUM              1
//#define ECAT_SYNC1_PIN_FUN              GPIO_FUN_3
//
//#define ECAT_LATCH0_GRP                 GPIO_GRP_A
//#define ECAT_LATCH0_PIN_START           25
//#define ECAT_LATCH0_PIN_SUM             1
//#define ECAT_LATCH0_PIN_FUN             GPIO_FUN_3
//
//#define ECAT_LATCH1_GRP                 GPIO_GRP_A
//#define ECAT_LATCH1_PIN_START           24
//#define ECAT_LATCH1_PIN_SUM             1
//#define ECAT_LATCH1_PIN_FUN             GPIO_FUN_3


#define ECAT_GPT                        0
#define ECAT_TIMER_INC_P_MS             1

#define ECAT_EEPROM_ECAT_ACCESS 0
#define ECAT_EEPROM_PDI_ACCESS  1

#define RET_ECAT_EEPROM_ACCESS_SUCCESS    0
#define RET_ECAT_EEPROM_ACCESS_FAILED     1
#define RET_ECAT_EEPROM_ACCESS_NOALLOW    2

void ecat_pdi_irq_enable(void);
void ecat_pdi_irq_disable(void);
u32 ecat_get_timer(void);
void ecat_clear_timer(void);

#define DISABLE_ESC_INT()            ecat_pdi_irq_disable()/**< \brief Disable external interrupts*/
#define ENABLE_ESC_INT()             ecat_pdi_irq_enable()/**< \brief Enable external interrupts*/
#define HW_GetTimer()                ecat_get_timer() /**< \brief Access to the hardware timer*/
#define HW_ClearTimer()              ecat_clear_timer() /**< \brief Clear the hardware timer*/

#define HW_EscReadWord(WordValue, Address) HW_EscRead(((MEM_ADDR *)&(WordValue)),((UINT16)(Address)),2) /**< \brief 16Bit ESC read access*/
#define HW_EscReadDWord(DWordValue, Address) HW_EscRead(((MEM_ADDR *)&(DWordValue)),((UINT16)(Address)),4) /**< \brief 32Bit ESC read access*/
#define HW_EscReadMbxMem(pData,Address,Len) HW_EscRead(((MEM_ADDR *)(pData)),((UINT16)(Address)),(Len)) /**< \brief The mailbox data is stored in the local uC memory therefore the default read function is used.*/

#define HW_EscReadWordIsr(WordValue, Address) HW_EscReadIsr(((MEM_ADDR *)&(WordValue)),((UINT16)(Address)),2) /**< \brief Interrupt specific 16Bit ESC read access*/
#define HW_EscReadDWordIsr(DWordValue, Address) HW_EscReadIsr(((MEM_ADDR *)&(DWordValue)),((UINT16)(Address)),4) /**< \brief Interrupt specific 32Bit ESC read access*/

#define HW_EscWriteWord(WordValue, Address) HW_EscWrite(((MEM_ADDR *)&(WordValue)),((UINT16)(Address)),2) /**< \brief 16Bit ESC write access*/
#define HW_EscWriteDWord(DWordValue, Address) HW_EscWrite(((MEM_ADDR *)&(DWordValue)),((UINT16)(Address)),4) /**< \brief 32Bit ESC write access*/
#define HW_EscWriteMbxMem(pData,Address,Len) HW_EscWrite(((MEM_ADDR *)(pData)),((UINT16)(Address)),(Len)) /**< \brief The mailbox data is stored in the local uC memory therefore the default write function is used.*/

#define HW_EscWriteWordIsr(WordValue, Address) HW_EscWriteIsr(((MEM_ADDR *)&(WordValue)),((UINT16)(Address)),2) /**< \brief Interrupt specific 16Bit ESC write access*/
#define HW_EscWriteDWordIsr(DWordValue, Address) HW_EscWriteIsr(((MEM_ADDR *)&(DWordValue)),((UINT16)(Address)),4) /**< \brief Interrupt specific 32Bit ESC write access*/


UINT8 HW_Init(void);
void HW_Release(void);
UINT16 HW_GetALEventRegister(void);

UINT16 HW_GetALEventRegister_Isr(void);

void HW_SetLed(UINT8 RunLed,UINT8 ErrLed);

void HW_EscRead( MEM_ADDR * pData, UINT16 Address, UINT16 Len );
void HW_EscReadIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len );

void HW_EscWrite( MEM_ADDR *pData, UINT16 Address, UINT16 Len );
void HW_EscWriteIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len );

void ecat_init(void);
UINT16 MainInit(void);
void MainLoop(void);
void ecat_timer_init(void);
s32 ecat_check_eeprom_loading(void);

s32 ecat_eeprom_access_switch(u8 sel);
s32 ecat_eeprom_read(u32 waddr, u32 wlen, u16 *wdata);
s32 ecat_eeprom_write(u32 waddr, u32 wlen, const u16 *wdata);

#endif
