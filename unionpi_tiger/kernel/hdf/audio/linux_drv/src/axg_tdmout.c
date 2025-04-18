/*
 * Copyright (c) 2022 Unionman Technology Co., Ltd.
 *
 * HDF is dual licensed: you can use it either under the terms of
 * the GPL, or the BSD license, at your option.
 * See the LICENSE file in the root of this repository for complete details.
 */

#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/regmap.h>
#include "sound/soc.h"
#include "sound/soc-dai.h"

#include "axg_common.h"
#include "axg_tdm_formatter.h"

#define TDMOUT_SINK_OUT_SEL_MAX     2

#define TDMOUT_CTRL0            0x00
#define  TDMOUT_CTRL0_BITNUM_MASK   GENMASK(4, 0)
#define  TDMOUT_CTRL0_BITNUM(x)     ((x) << 0)
#define  TDMOUT_CTRL0_SLOTNUM_MASK  GENMASK(9, 5)
#define  TDMOUT_CTRL0_SLOTNUM(x)    ((x) << 5)
#define  TDMOUT_CTRL0_INIT_BITNUM_MASK  GENMASK(19, 15)
#define  TDMOUT_CTRL0_INIT_BITNUM(x)    ((x) << 15)
#define  TDMOUT_CTRL0_ENABLE        BIT(31)
#define  TDMOUT_CTRL0_RST_OUT       BIT(29)
#define  TDMOUT_CTRL0_RST_IN        BIT(28)
#define TDMOUT_CTRL1            0x04
#define  TDMOUT_CTRL1_TYPE_MASK     GENMASK(6, 4)
#define  TDMOUT_CTRL1_TYPE(x)       ((x) << 4)
#define  SM1_TDMOUT_CTRL1_GAIN_EN   7
#define  TDMOUT_CTRL1_MSB_POS_MASK  GENMASK(12, 8)
#define  TDMOUT_CTRL1_MSB_POS(x)    ((x) << 8)
#define  TDMOUT_CTRL1_SEL_SHIFT     24
#define  TDMOUT_CTRL1_GAIN_EN       26
#define  TDMOUT_CTRL1_WS_INV        BIT(28)
#define TDMOUT_SWAP             0x08
#define TDMOUT_MASK0            0x0c
#define TDMOUT_MASK1            0x10
#define TDMOUT_MASK2            0x14
#define TDMOUT_MASK3            0x18
#define TDMOUT_STAT             0x1c
#define TDMOUT_GAIN0            0x20
#define TDMOUT_GAIN1            0x24
#define TDMOUT_MUTE_VAL         0x28
#define TDMOUT_MUTE0            0x2c
#define TDMOUT_MUTE1            0x30
#define TDMOUT_MUTE2            0x34
#define TDMOUT_MUTE3            0x38
#define TDMOUT_MASK_VAL         0x3c

static const struct regmap_config axg_tdmout_regmap_cfg = {
    .reg_bits   = 32,
    .val_bits   = 32,
    .reg_stride = 4,
    .max_register   = TDMOUT_MASK_VAL,
};

static void axg_tdmout_enable(struct regmap *map)
{
    /* Apply both reset */
    regmap_update_bits(map, TDMOUT_CTRL0,
                       TDMOUT_CTRL0_RST_OUT | TDMOUT_CTRL0_RST_IN, 0);

    /* Clear out reset before in reset */
    regmap_update_bits(map, TDMOUT_CTRL0,
                       TDMOUT_CTRL0_RST_OUT, TDMOUT_CTRL0_RST_OUT);
    regmap_update_bits(map, TDMOUT_CTRL0,
                       TDMOUT_CTRL0_RST_IN, TDMOUT_CTRL0_RST_IN);

    /* Actually enable tdmout */
    regmap_update_bits(map, TDMOUT_CTRL0,
                       TDMOUT_CTRL0_ENABLE, TDMOUT_CTRL0_ENABLE);
}

static void axg_tdmout_disable(struct regmap *map)
{
    regmap_update_bits(map, TDMOUT_CTRL0, TDMOUT_CTRL0_ENABLE, 0);
}

static int axg_tdmout_sink_out_sel(struct regmap *map, unsigned int index)
{
    unsigned int mask, val;

    if (index > TDMOUT_SINK_OUT_SEL_MAX) {
        pr_err("%s, invalid param: index=%u\n", __FUNCTION__, index);
        return -1;
    }

    mask = 0x3 << TDMOUT_CTRL1_SEL_SHIFT;
    val = index << TDMOUT_CTRL1_SEL_SHIFT;
    regmap_update_bits(map, TDMOUT_CTRL1, mask, val);
    pr_info("%s, update_bits: reg=0x%x, mask=0x%x, val=0x%x\n",
            __FUNCTION__, TDMOUT_CTRL1, mask, val);
    return 0;
}

static int axg_tdmout_prepare(struct regmap *map,
                              const struct axg_tdm_formatter_hw *quirks,
                              struct axg_tdm_stream *ts)
{
    unsigned int val, skew = quirks->skew_offset;

    /* Set the stream skew */
    switch (ts->iface->fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
        case SND_SOC_DAIFMT_I2S:
        case SND_SOC_DAIFMT_DSP_A:
            break;
        case SND_SOC_DAIFMT_LEFT_J:
        case SND_SOC_DAIFMT_DSP_B:
            skew += 1;
            break;
        default:
            pr_err("Unsupported format: %u\n",
                   ts->iface->fmt & SND_SOC_DAIFMT_FORMAT_MASK);
            return -EINVAL;
    }

    val = TDMOUT_CTRL0_INIT_BITNUM(skew);

    /* Set the slot width */
    val |= TDMOUT_CTRL0_BITNUM(ts->iface->slot_width - 1);

    /* Set the slot number */
    val |= TDMOUT_CTRL0_SLOTNUM(ts->iface->slots - 1);

    regmap_update_bits(map, TDMOUT_CTRL0,
                       TDMOUT_CTRL0_INIT_BITNUM_MASK |
                           TDMOUT_CTRL0_BITNUM_MASK |
                           TDMOUT_CTRL0_SLOTNUM_MASK,
                       val);

    /* Set the sample width */
    val = TDMOUT_CTRL1_MSB_POS(ts->width - 1);

    /* FIFO data are arranged in chunks of 64bits */
    switch (ts->physical_width) {
        case AXG_BIT_WIDTH8:
            /* 8 samples of 8 bits */
            val |= TDMOUT_CTRL1_TYPE(0);
            break;
        case AXG_BIT_WIDTH16:
            /* 4 samples of 16 bits - right justified */
            val |= TDMOUT_CTRL1_TYPE(2);
            break;
        case AXG_BIT_WIDTH32:
            /* 2 samples of 32 bits - right justified */
            val |= TDMOUT_CTRL1_TYPE(4);
            break;
        default:
            pr_err("Unsupported physical width: %u\n",
                   ts->physical_width);
            return -EINVAL;
    }

    /* If the sample clock is inverted, invert it back for the formatter */
    if (axg_tdm_lrclk_invert(ts->iface->fmt)) {
        val |= TDMOUT_CTRL1_WS_INV;
    }

    regmap_update_bits(map, TDMOUT_CTRL1,
                       (TDMOUT_CTRL1_TYPE_MASK | TDMOUT_CTRL1_MSB_POS_MASK |
                        TDMOUT_CTRL1_WS_INV),
                       val);

    /* Set static swap mask configuration */
    regmap_write(map, TDMOUT_SWAP, 0x76543210);

    return axg_tdm_formatter_set_channel_masks(map, ts, TDMOUT_MASK0);
}

static const struct axg_tdm_formatter_ops axg_tdmout_ops = {
    .sink_out_sel   = axg_tdmout_sink_out_sel,
    .prepare    = axg_tdmout_prepare,
    .enable     = axg_tdmout_enable,
    .disable    = axg_tdmout_disable,
};

static const struct axg_tdm_formatter_driver axg_tdmout_drv = {
    .regmap_cfg = &axg_tdmout_regmap_cfg,
    .ops        = &axg_tdmout_ops,
    .quirks     = &(const struct axg_tdm_formatter_hw) {
        .skew_offset = 1,
    },
};

static const struct axg_tdm_formatter_driver g12a_tdmout_drv = {
    .regmap_cfg = &axg_tdmout_regmap_cfg,
    .ops        = &axg_tdmout_ops,
    .quirks     = &(const struct axg_tdm_formatter_hw) {
        .skew_offset = 2,
    },
};

static const struct axg_tdm_formatter_driver sm1_tdmout_drv = {
    .regmap_cfg = &axg_tdmout_regmap_cfg,
    .ops        = &axg_tdmout_ops,
    .quirks     = &(const struct axg_tdm_formatter_hw) {
        .skew_offset = 2,
    },
};

static const struct of_device_id axg_tdmout_of_match[] = {
    {
        .compatible = "amlogic,axg-tdmout",
        .data = &axg_tdmout_drv,
    }, {
        .compatible = "amlogic,g12a-tdmout",
        .data = &g12a_tdmout_drv,
    }, {
        .compatible = "amlogic,sm1-tdmout",
        .data = &sm1_tdmout_drv,
    }, {}
};
MODULE_DEVICE_TABLE(of, axg_tdmout_of_match);

static struct platform_driver axg_tdmout_pdrv = {
    .probe = axg_tdm_formatter_probe,
    .driver = {
        .name = "axg-tdmout",
        .of_match_table = axg_tdmout_of_match,
    },
};
module_platform_driver(axg_tdmout_pdrv);

