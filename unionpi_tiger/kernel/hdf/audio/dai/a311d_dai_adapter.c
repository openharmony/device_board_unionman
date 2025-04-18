/*
 * Copyright (c) 2022 Unionman Technology Co., Ltd.
 *
 * HDF is dual licensed: you can use it either under the terms of
 * the GPL, or the BSD license, at your option.
 * See the LICENSE file in the root of this repository for complete details.
 */

#include "audio_core.h"
#include "osal_io.h"
#include "audio_dai_base.h"
#include "audio_driver_log.h"

#include "a311d_dai_ops.h"

#define HDF_LOG_TAG a311d_dai_adapter

struct AudioDaiOps g_daiDeviceOps = {
    .HwParams   = A311DDaiHwParams,
    .Trigger    = A311DDaiTrigger,
    .Startup    = A311DDaiStartup,
};

struct DaiData g_daiData = {
    .DaiInit    = A311DDeviceInit,
    .Read       = A311DDeviceReadReg,
    .Write      = A311DDeviceWriteReg,
    .ops        = &g_daiDeviceOps,
};

/* HdfDriverEntry implementations */
static int32_t DaiDriverBind(struct HdfDeviceObject *device)
{
    struct DaiHost *daiHost = NULL;
    AUDIO_DRIVER_LOG_DEBUG("entry!");

    if (device == NULL) {
        AUDIO_DRIVER_LOG_ERR("input para is NULL.");
        return HDF_FAILURE;
    }

    daiHost = (struct DaiHost *)OsalMemCalloc(sizeof(*daiHost));
    if (daiHost == NULL) {
        AUDIO_DRIVER_LOG_ERR("malloc host fail!");
        return HDF_FAILURE;
    }

    daiHost->device = device;
    device->service = &daiHost->service;
    g_daiData.daiInitFlag = false;

    AUDIO_DRIVER_LOG_DEBUG("success!");
    return HDF_SUCCESS;
}

static int32_t DaiGetServiceName(const struct HdfDeviceObject *device)
{
    int32_t ret;
    const struct DeviceResourceNode *node = NULL;
    struct DeviceResourceIface *drsOps = NULL;

    AUDIO_DRIVER_LOG_DEBUG("entry!");

    if (device == NULL) {
        AUDIO_DRIVER_LOG_ERR("input para is nullptr.");
        return HDF_FAILURE;
    }

    node = device->property;
    if (node == NULL) {
        AUDIO_DRIVER_LOG_ERR("drs node is nullptr.");
        return HDF_FAILURE;
    }
    drsOps = DeviceResourceGetIfaceInstance(HDF_CONFIG_SOURCE);
    if (drsOps == NULL || drsOps->GetString == NULL) {
        AUDIO_DRIVER_LOG_ERR("invalid drs ops fail!");
        return HDF_FAILURE;
    }

    ret = drsOps->GetString(node, "serviceName", &g_daiData.drvDaiName, 0);
    if (ret != HDF_SUCCESS) {
        AUDIO_DRIVER_LOG_ERR("read serviceName fail!");
        return ret;
    }

    AUDIO_DRIVER_LOG_DEBUG("success!");
    return HDF_SUCCESS;
}

static int32_t DaiDriverInit(struct HdfDeviceObject *device)
{
    int32_t ret = 0;
    AUDIO_DRIVER_LOG_DEBUG("entry!");
    if (device == NULL) {
        AUDIO_DRIVER_LOG_ERR("device is nullptr.");
        return HDF_ERR_INVALID_OBJECT;
    }

    if (DaiGetConfigInfo(device, &g_daiData) != HDF_SUCCESS) {
        AUDIO_DRIVER_LOG_ERR("get dai data fail.");
        return HDF_FAILURE;
    }

    if (DaiGetServiceName(device) != HDF_SUCCESS) {
        AUDIO_DRIVER_LOG_ERR("get service name fail.");
        return HDF_FAILURE;
    }

    OsalMutexInit(&g_daiData.mutex);

    ret = AudioSocRegisterDai(device, &g_daiData);
    if (ret != HDF_SUCCESS) {
        AUDIO_DRIVER_LOG_ERR("register dai fail.");
        return ret;
    }

    AUDIO_DRIVER_LOG_DEBUG("success.\n");
    return HDF_SUCCESS;
}

static void DaiDriverRelease(struct HdfDeviceObject *device)
{
    struct DaiHost *daiHost;
    AUDIO_DRIVER_LOG_DEBUG("entry!");
    if (device == NULL) {
        AUDIO_DRIVER_LOG_ERR("device is NULL");
        return;
    }

    OsalMutexDestroy(&g_daiData.mutex);

    daiHost = (struct DaiHost *)device->service;
    if (daiHost == NULL) {
        AUDIO_DRIVER_LOG_ERR("daiHost is NULL");
        return;
    }
    OsalMemFree(daiHost);
    AUDIO_DRIVER_LOG_DEBUG("success!");
}

/* HdfDriverEntry definitions */
struct HdfDriverEntry g_daiDriverEntry = {
    .moduleVersion  = 1,
    .moduleName     = "DAI_A311D",
    .Bind           = DaiDriverBind,
    .Init           = DaiDriverInit,
    .Release        = DaiDriverRelease,
};
HDF_INIT(g_daiDriverEntry);
