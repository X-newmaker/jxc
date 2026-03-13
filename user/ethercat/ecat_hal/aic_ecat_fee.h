#ifndef AIC_ECAT_FEE_H_
#define AIC_ECAT_FEE_H_
#include <ecat_def.h>

#define ECAT_FEE_SUCCESS          (0)
#define ECAT_FEE_CHECKSUM_ERR     (1)
#define ECAT_FEE_FLASH_ERR        (2)

void AIC_fee_Init(void);
u16 AIC_fee_Read(uint32_t wordaddr);
u16 AIC_fee_Write(uint32_t wordaddr);
u16 AIC_fee_Reload (void);
//void AIC_fee_Store(void);

#endif

