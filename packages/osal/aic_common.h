/*
 * Copyright (c) 2022, Artinchip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __AIC_COMMON_H__
#define __AIC_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef __signed__ char     s8;
typedef unsigned char       u8;

typedef __signed__ short    s16;
typedef unsigned short      u16;

typedef __signed__ int      s32;
typedef unsigned int        u32;

#ifdef ARCH_64BIT
typedef __signed__ long     s64;
typedef unsigned long       u64;
#define FMT_d64             "%ld"
#define FMT_x64             "%lx"
#define BITS_PER_LONG       64
#else
typedef __signed__ long long s64;
typedef unsigned long long   u64;
#define FMT_d64              "%lld"
#define FMT_x64              "%llx"
#define BITS_PER_LONG        32
#endif

typedef u32 dma_addr_t;
typedef u32 phy_addr_t;
typedef unsigned long ulong;
typedef unsigned long ptr_t;

#define U8_MAX  ((u8)~0U)
#define S8_MAX  ((s8)(U8_MAX >> 1))
#define S8_MIN  ((s8)(-S8_MAX - 1))
#define U16_MAX ((u16)~0U)
#define S16_MAX ((s16)(U16_MAX >> 1))
#define S16_MIN ((s16)(-S16_MAX - 1))
#define U32_MAX ((u32)~0U)
#define U32_MIN ((u32)0)
#define S32_MAX ((s32)(U32_MAX >> 1))
#define S32_MIN ((s32)(-S32_MAX - 1))
#define U64_MAX ((u64)~0ULL)
#define S64_MAX ((s64)(U64_MAX >> 1))
#define S64_MIN ((s64)(-S64_MAX - 1))

/* Character code support macros */
#define aic_in_range(c, lo, up)  ((u8)c >= lo && (u8)c <= up)
#define aic_isupper(c)  ((c) >= 'A' && (c) <= 'Z')
#define aic_islower(c)  ((c) >= 'a' && (c) <= 'z')
#define aic_isdigit(c)  ((c) >= '0' && (c) <= '9')
#define aic_isxdigit(c) (aic_isdigit(c) || aic_in_range(c, 'a', 'f') \
                                        || aic_in_range(c, 'A', 'F'))
#define aic_isspace(c)  ((c) == ' ' || (c) == '\f' || (c) == '\n' \
                        || (c) == '\r' || (c) == '\t' || (c) == '\v')

#define aic_convert_tx_dlymode(c, d)  (((c > 4) ? 0 : c) | (d ? 1UL << 14 : 0))

#ifndef CHECK_PARAM
#define CHECK_PARAM(x, ret) \
    do { \
        if (!(x)) { \
            return ret; \
        } \
    } while (0)
#endif

#ifndef CHECK_PARAM_RET
#define CHECK_PARAM_RET(x) \
    do { \
        if (!(x)) { \
            return; \
        } \
    } while (0)
#endif

#ifndef CHECK_RET_WITH_GOTO
#define CHECK_RET_WITH_GOTO(x, label) \
    do { \
        if (!(x)) { \
            pr_err(__FILE__, ", %s()%d failed.", __FUNCTION__, __LINE__); \
            goto label; \
        } \
    } while (0)
#endif

#ifndef CHECK_RET_WITH_RET
#define CHECK_RET_WITH_RET(x, ret) \
    do { \
        if (!(x)) { \
            pr_err(__FILE__, ", %s()%d failed.", __FUNCTION__, __LINE__); \
            return ret; \
        } \
    } while (0)
#endif

/* Exception Dealt With */
#define BUG() do {                                                            \
        printf("BUG: failure at %s:%d/%s()!\n", __FILE__, __LINE__, __func__); \
        while (1) {};                                                         \
    } while (0)

#if (!defined(likely))
#define likely(x)             __builtin_expect((long)!!(x), 1L)
#endif
#if (!defined(unlikely))
#define unlikely(x)           __builtin_expect((long)!!(x), 0L)
#endif

/* IOCTL interface commands */
#ifndef _IOWR
# define _IOWR(x, y, z)     (((x) << 8) | y)
#endif
#ifndef _IOW
# define _IOW(x, y, z)      (((x) << 8) | y)
#endif
#ifndef _IOR
# define _IOR(x, y, z)      (((x) << 8) | y)
#endif
#ifndef _IO
# define _IO(x, y)          (((x) << 8) | y)
#endif

#define ARCH_DMA_MINALIGN   32

#undef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) \
    ({ \
        const typeof(((type *)0)->member) *__mptr = (ptr); \
        (type *)((char *)__mptr - offsetof(type, member)); \
    })

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#ifndef max
#define max(x, y) ({				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(void) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; })
#endif

#ifndef min
#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })
#endif

#define do_div(n, base) \
    ({ \
        unsigned int __base = (base); \
        unsigned int __rem; \
        __rem = ((u64)(n)) % __base; \
        (n)   = ((u64)(n)) / __base; \
        __rem; \
    })

/*
 * Divide positive or negative dividend by positive or negative divisor
 * and round to closest integer. Result is undefined for negative
 * divisors if the dividend variable type is unsigned and for negative
 * dividends if the divisor variable type is unsigned.
 */
#define DIV_ROUND_CLOSEST(x, divisor) \
    ({ \
        typeof(x) __x       = x; \
        typeof(divisor) __d = divisor; \
        (((typeof(x))-1) > 0 || ((typeof(divisor))-1) > 0 || \
         (((__x) > 0) == ((__d) > 0))) ? \
                (((__x) + ((__d) / 2)) / (__d)) : \
                (((__x) - ((__d) / 2)) / (__d)); \
    })
/*
 * Same as above but for u64 dividends. divisor must be a 32-bit
 * number.
 */
#define DIV_ROUND_CLOSEST_ULL(x, divisor) \
    ({ \
        typeof(divisor) __d     = divisor; \
        unsigned long long _tmp = (x) + (__d) / 2; \
        do_div(_tmp, __d); \
        _tmp; \
    })

#define DIV_ROUND_UP(n, d) (((n) + (d)-1) / (d))
#define ROUNDUP(a, b)      ((((a)-1) / (b) + 1) * (b))
#define ROUND(a, b)        (((a) + (b)-1) & ~((b)-1))
#define ROUNDDOWN(a, b)    ((a) & ~((b) - 1))

#define roundup(x, y) (                 \
{                           \
    const typeof(y) __y = y;            \
    (((x) + (__y - 1)) / __y) * __y;        \
}                           \
)
#define rounddown(x, y) (               \
{                           \
    typeof(x) __x = (x);                \
    __x - (__x % (y));              \
}                           \
)

#ifdef ALIGN
#undef ALIGN
#endif
#define __ALIGN_MASK(x,mask)    (((x)+(mask))&~(mask))
#define ALIGN_UP(x,a)           __ALIGN_MASK((x),(typeof(x))(a)-1)
#define ALIGN_DOWN(x, a)        ((x) & (~((typeof(x))(a)-1)))

#define PAD_COUNT(s, pad)   (((s) - 1) / (pad) + 1)
#define PAD_SIZE(s, pad)    (PAD_COUNT(s, pad) * pad)
#define ALLOC_ALIGN_BUFFER_PAD(type, name, size, align, pad)        \
    char __##name[ROUND(PAD_SIZE((size) * sizeof(type), pad), align)  \
              + (align - 1)];                   \
                                    \
    type *name = (type *)ALIGN_UP((uintptr_t)__##name, align)
#define ALLOC_ALIGN_BUFFER(type, name, size, align)     \
    ALLOC_ALIGN_BUFFER_PAD(type, name, size, align, 1)
#define ALLOC_CACHE_ALIGN_BUFFER_PAD(type, name, size, pad)     \
    ALLOC_ALIGN_BUFFER_PAD(type, name, size, ARCH_DMA_MINALIGN, pad)
#define ALLOC_CACHE_ALIGN_BUFFER(type, name, size)          \
    ALLOC_ALIGN_BUFFER(type, name, size, ARCH_DMA_MINALIGN)

#define BANNER1                                         "\n" \
    "     _         _   ___        ___ _     _           \n" \
    "    / \\   _ __| |_|_ _|_ __  / __| |__ (_)_ __     \n"
#define BANNER2                                              \
    "   / _ \\ | '__| __|| || '_ \\| |  | '_ \\| | '_ \\ \n" \
    "  / ___ \\| |  | |_ | || | | | |__| | | | | |_) |   \n"
#define BANNER3                                             \
    " /_/   \\_\\_|   \\__|___|_| |_|\\___|_| |_|_| .__/ \n"\
    "                                         |_|      \n\n"
#define BANNER          BANNER1 BANNER2 BANNER3

#define __va(x) ((void *)((unsigned long) (x)))
#define __pa(x) ((unsigned long) (x))

#ifndef __USED
#define __USED __attribute__((used))
#endif
#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif
#ifndef __PACKED
#define __PACKED __attribute__((packed, aligned(1)))
#endif
#ifndef __PACKED_STRUCT
#define __PACKED_STRUCT struct __attribute__((packed, aligned(1)))
#endif
#ifndef __PACKED_UNION
#define __PACKED_UNION union __attribute__((packed, aligned(1)))
#endif
#ifndef __ALIGNED
#define __ALIGNED(x) __attribute__((aligned(x)))
#endif

#define  ATTRIBUTE_ISR __attribute__ ((interrupt ("machine")))



#ifdef __cplusplus
}
#endif

#endif /* __AIC_COMMON_H__ */
