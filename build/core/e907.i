
#ifndef __E907_I__
#define __E907_I__

#define	E907_MEXSTATUS_SPUSHEN		(1<< 16)

#define	E907_MSTATUS_MIE		(1<< 3)
#define	E907_MSTATUS_MPIE		(1<< 7)
#define	E907_MSTATUS_MPP  		(3<<11)
#define	E907_MSTATUS_FS  		(3<<13)
#define	E907_MSTATUS_XS  		(3<<15)
#define	E907_MSTATUS_MPRV  		(1<<17)

#define	E907_MXSTATUS_PMDU		(1<<10)
#define	E907_MXSTATUS_PMDM		(1<<13)
#define	E907_MXSTATUS_MM		(1<<15)
#define	E907_MXSTATUS_THEADISAEE	(1<<22)
#define	E907_MXSTATUS_PM		(3<<30)

#define E907_MHCR_IE			(1<<0)
#define E907_MHCR_DE			(1<<1)
#define E907_MHCR_WB			(1<<2)
#define E907_MHCR_WA			(1<<3)
#define E907_MHCR_RS			(1<<4)
#define E907_MHCR_BPE  			(1<<5)
#define E907_MHCR_BTB  			(1<<12)

#define E907_MHINT_DPLD			(1<<2)
#define E907_MHINT_AMR			(3<<3)
#define E907_MHINT_PREF_N		(3<<13)
#define E907_MHINT_AEE			(1<<20)
#define E907_MHINT_PCFIFO_FREEZE	(1<<24)

#define E907_ICACHE_LINESIZE		(0x20)
#define E907_DCACHE_LINESIZE		(0x20)

#endif
