# Copyright (c) 2022 Unionman Technology Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

KDIR = $(src)/../../../../../../../../../../out/kernel/src_tmp/linux-5.10

obj-m += iv009_isp_iq.o

iv009_isp_iq-objs += app/soc_iq.o
iv009_isp_iq-objs += src/fw_lib/acamera_math.o \
				src/fw_lib/acamera_logger.o
iv009_isp_iq-objs += src/calibration/acamera_calibrations_static_linear_dummy.o \
				src/calibration/acamera_calibrations_dynamic_fs_lin_dummy.o \
				src/calibration/acamera_calibrations_dynamic_linear_dummy.o \
				src/calibration/acamera_calibrations_static_fs_lin_dummy.o \
				src/calibration/acamera_calibrations_dynamic_linear_imx219.o \
				src/calibration/acamera_get_calibrations_dummy.o
iv009_isp_iq-objs += src/platform/system_timer.o \
				src/platform/system_stdlib.o \
				src/platform/system_log.o

#INCLUDE_DIRS := $(addprefix -I,$(shell find ../ -type d ))

ccflags-y:=-I$(src)/app -I$(src)/inc -I$(src)/app/control -I$(src)/inc/api -I$(src)/inc/isp -I$(src)/inc/sys -I$(src)/src/platform -I$(src)/src/fw  -I$(src)/src/fw_lib -I$(src)/src/calibration -I$(src)/src/driver/sensor -I$(src)/src/driver/lens -I$(KDIR)/include/linux/

ccflags-y += -Wno-declaration-after-statement -Wno-error


