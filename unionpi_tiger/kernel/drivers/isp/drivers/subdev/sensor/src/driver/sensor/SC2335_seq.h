/*
*
* SPDX-License-Identifier: GPL-2.0
*
* Copyright (C) 2011-2018 ARM or its affiliates
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; version 2.
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*/
#if !defined(__SC2335_SEQ_H__)
#define __SC2335_SEQ_H__

static acam_reg_t linear_1920_1080_30fps_371Mbps_2lane_10bits[] = {
    {0x0103, 0x01, 0xFF, 1},
    {0x0100, 0x00, 0xFF, 1},
    {0x36e9, 0x80, 0xFF, 1},
    {0x36f9, 0x80, 0xFF, 1},
    {0x301f, 0x14, 0xFF, 1},
    {0x3207, 0x3f, 0xFF, 1},
    {0x3249, 0x0f, 0xFF, 1},
    {0x3253, 0x08, 0xFF, 1},
    {0x3271, 0x00, 0xFF, 1},
    {0x3273, 0x03, 0xFF, 1},
    {0x3301, 0x06, 0xFF, 1},
    {0x3302, 0x09, 0xFF, 1},
    {0x3304, 0x28, 0xFF, 1},
    {0x3306, 0x30, 0xFF, 1},
    {0x330b, 0x94, 0xFF, 1},
    {0x330c, 0x08, 0xFF, 1},
    {0x330d, 0x18, 0xFF, 1},
    {0x330e, 0x14, 0xFF, 1},
    {0x330f, 0x05, 0xFF, 1},
    {0x3310, 0x06, 0xFF, 1},
    {0x3314, 0x96, 0xFF, 1},
    {0x3316, 0x00, 0xFF, 1},
    {0x331e, 0x21, 0xFF, 1},
    {0x332b, 0x08, 0xFF, 1},
    {0x3333, 0x10, 0xFF, 1},
    {0x3338, 0x80, 0xFF, 1},
    {0x333a, 0x04, 0xFF, 1},
    {0x334c, 0x04, 0xFF, 1},
    {0x335f, 0x04, 0xFF, 1},
    {0x3364, 0x17, 0xFF, 1},
    {0x3366, 0x62, 0xFF, 1},
    {0x337c, 0x05, 0xFF, 1},
    {0x337d, 0x09, 0xFF, 1},
    {0x337e, 0x00, 0xFF, 1},
    {0x3390, 0x08, 0xFF, 1},
    {0x3391, 0x18, 0xFF, 1},
    {0x3392, 0x38, 0xFF, 1},
    {0x3393, 0x09, 0xFF, 1},
    {0x3394, 0x20, 0xFF, 1},
    {0x3395, 0x20, 0xFF, 1},
    {0x33a2, 0x07, 0xFF, 1},
    {0x33ac, 0x04, 0xFF, 1},
    {0x33ae, 0x14, 0xFF, 1},
    {0x3614, 0x00, 0xFF, 1},
    {0x3622, 0x16, 0xFF, 1},
    {0x3630, 0x68, 0xFF, 1},
    {0x3631, 0x84, 0xFF, 1},
    {0x3637, 0x20, 0xFF, 1},
    {0x363a, 0x1f, 0xFF, 1},
    {0x363c, 0x0e, 0xFF, 1},
    {0x3670, 0x0e, 0xFF, 1},
    {0x3674, 0xa1, 0xFF, 1},
    {0x3675, 0x9c, 0xFF, 1},
    {0x3676, 0x9e, 0xFF, 1},
    {0x3677, 0x84, 0xFF, 1},
    {0x3678, 0x85, 0xFF, 1},
    {0x3679, 0x87, 0xFF, 1},
    {0x367c, 0x18, 0xFF, 1},
    {0x367d, 0x38, 0xFF, 1},
    {0x367e, 0x08, 0xFF, 1},
    {0x367f, 0x18, 0xFF, 1},
    {0x3690, 0x32, 0xFF, 1},
    {0x3691, 0x32, 0xFF, 1},
    {0x3692, 0x44, 0xFF, 1},
    {0x369c, 0x08, 0xFF, 1},
    {0x369d, 0x38, 0xFF, 1},
    {0x36ea, 0xf5, 0xFF, 1},
    {0x36fa, 0xdf, 0xFF, 1},
    {0x3908, 0x82, 0xFF, 1},
    {0x391f, 0x18, 0xFF, 1},
    {0x3e01, 0xa8, 0xFF, 1},
    {0x3e02, 0x20, 0xFF, 1},
    {0x3f00, 0x0d, 0xFF, 1},
    {0x3f04, 0x02, 0xFF, 1},
    {0x3f05, 0x0e, 0xFF, 1},
    {0x3f09, 0x48, 0xFF, 1},
    {0x4505, 0x0a, 0xFF, 1},
    {0x4509, 0x20, 0xFF, 1},
    {0x481d, 0x0a, 0xFF, 1},
    {0x4827, 0x03, 0xFF, 1},
    {0x5787, 0x10, 0xFF, 1},
    {0x5788, 0x06, 0xFF, 1},
    {0x578a, 0x10, 0xFF, 1},
    {0x578b, 0x06, 0xFF, 1},
    {0x5790, 0x10, 0xFF, 1},
    {0x5791, 0x10, 0xFF, 1},
    {0x5792, 0x00, 0xFF, 1},
    {0x5793, 0x10, 0xFF, 1},
    {0x5794, 0x10, 0xFF, 1},
    {0x5795, 0x00, 0xFF, 1},
    {0x5799, 0x00, 0xFF, 1},
    {0x57c7, 0x10, 0xFF, 1},
    {0x57c8, 0x06, 0xFF, 1},
    {0x57ca, 0x10, 0xFF, 1},
    {0x57cb, 0x06, 0xFF, 1},
    {0x57d1, 0x10, 0xFF, 1},
    {0x57d4, 0x10, 0xFF, 1},
    {0x57d9, 0x00, 0xFF, 1},
    {0x36e9, 0x59, 0xFF, 1},
    {0x36f9, 0x5b, 0xFF, 1},
    //{0x0100, 0x01, 0xFF, 1},

    { 0x0000, 0x0000, 0x0000, 0x0000 },
};

static acam_reg_t settings_context_sc2335[] = {
    //stop sequence - address is 0x0000
    { 0x0000, 0x0000, 0x0000, 0x0000 }
};

static const acam_reg_t *sc2335_seq_table[] = {
        linear_1920_1080_30fps_371Mbps_2lane_10bits,
};

static const acam_reg_t *isp_seq_table[] = {
        settings_context_sc2335,
};

#define SENSOR_SC2335_SEQUENCE_DEFAULT sc2335_seq_table
#define SENSOR_SC2335_ISP_CONTEXT_SEQUENCE isp_seq_table

#define SENSOR_SC2335_SEQUENCE_1080P_30FPS_PREVIEW  0

#define SENSOR_SC2335_CONTEXT_SEQ  0

#endif // __SC2335_SEQ_H__
