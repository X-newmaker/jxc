#ifndef __CLINT_H__
#define __CLINT_H__

#include "common_type.h"
#include "common_mmp.h"

s32 clint_msip_cfg(u64 val);
s32 clint_mtime_cfg(u64 val);
s32 clint_ssip_cfg(u64 val);
s32 clint_stime_cfg(u64 val);
u64 clint_mtime_get(void);

#define BASE_E907_CLINT		(BASE_CPU)

typedef enum e907_clint_offset_e {
	E907_CLINT_MSIP0		= BASE_E907_CLINT + 0x0000,
	E907_CLINT_MTIMECMPL0		= BASE_E907_CLINT + 0x4000,
	E907_CLINT_MTIMECMPH0		= BASE_E907_CLINT + 0x4004,
	E907_CLINT_MTIMELO		= BASE_E907_CLINT + 0xBFF8,
	E907_CLINT_MTIMEHI		= BASE_E907_CLINT + 0xBFFC,
}e907_clint_offset_t;

#endif
