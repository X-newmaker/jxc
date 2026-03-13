#ifndef AIC_ECAT_FOE_H_
#define AIC_ECAT_FOE_H_
#include <ecat_def.h>

UINT16 AIC_FoE_Read(UINT16 MBXMEM * pName, UINT16 nameSize, UINT32 password, UINT16 maxBlockSize, UINT16 *pData);
UINT16 AIC_FoE_ReadData(UINT32 offset, UINT16 maxBlockSize, UINT16 *pData);
UINT16 AIC_FoE_Write(UINT16 MBXMEM * pName, UINT16 nameSize, UINT32 password);
UINT16 AIC_FoE_WriteData(UINT16 MBXMEM * pData, UINT16 Size, BOOL bDataFollowing);

#endif

