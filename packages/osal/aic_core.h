/*
 * Copyright (c) 2022, Artinchip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __AIC_CORE_H__
#define __AIC_CORE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define PLATFORM_LUBANLITE
#define KERNEL_BAREMETAL

#include <all_inc.h>
#include <aic_soc.h>
#include <core_rv32.h>
#include <csi_rv32_gcc.h>
#include <aic_common.h>
#include <aic_errno.h>
#include <aic_list.h>
#include <aic_log.h>
#include <aic_tlsf.h>
#include <aic_osal.h>

#ifdef __cplusplus
}
#endif

#endif /* __AIC_CORE_H__ */
