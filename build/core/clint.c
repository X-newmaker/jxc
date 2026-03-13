
#include "all_inc.h"
#include "clint.h"

s32 clint_msip_cfg(u64 val)
{
	writel(val & 1,			E907_CLINT_MSIP0	);

	return RET_OK;
}

s32 clint_mtime_cfg(u64 val)
{
	writel(val & 0xffffffff, 	E907_CLINT_MTIMECMPL0	);
	writel(val >> 32,		E907_CLINT_MTIMECMPH0	);

	return RET_OK;
}

u64 clint_mtime_get(void)
{
	u32 mtimelo, mtimehi;

	mtimelo = readl(E907_CLINT_MTIMELO);
	mtimehi = readl(E907_CLINT_MTIMEHI);

	return ((u64)mtimehi<<32 | mtimelo);
}
