/*
 * Copyright (c) 2020-2022, NVIDIA CORPORATION.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef ZBC_GA10B_H
#define ZBC_GA10B_H

#include <nvgpu/types.h>

struct gk20a;
struct nvgpu_gr_zbc_table_indices;
struct nvgpu_gr_zbc;

void ga10b_gr_zbc_init_table_indices(struct gk20a *g,
			struct nvgpu_gr_zbc_table_indices *zbc_indices);
void ga10b_gr_zbc_add_color(struct gk20a *g,
			struct nvgpu_gr_zbc_entry *color_val, u32 index);
void ga10b_gr_zbc_load_static_table(struct gk20a *g,
					struct nvgpu_gr_zbc *zbc);
#ifndef CONFIG_NVGPU_NON_FUSA
#define NVGPU_ZBC_SET_COLOR_ATTR(tbl, ind, i)				\
{									\
	(tbl)[ind].color_ds[0] = (NVGPU_ZBC_CL_DS_R_##i);		\
	(tbl)[ind].color_ds[1] = (NVGPU_ZBC_CL_DS_G_##i);		\
	(tbl)[ind].color_ds[2] = (NVGPU_ZBC_CL_DS_B_##i);		\
	(tbl)[ind].color_ds[3] = (NVGPU_ZBC_CL_DS_A_##i);		\
	(tbl)[ind].color_l2[0] = (NVGPU_ZBC_CL_L2_R_##i);		\
	(tbl)[ind].color_l2[1] = (NVGPU_ZBC_CL_L2_G_##i);		\
	(tbl)[ind].color_l2[2] = (NVGPU_ZBC_CL_L2_B_##i);		\
	(tbl)[ind].color_l2[3] = (NVGPU_ZBC_CL_L2_A_##i);		\
	(tbl)[ind].format = (NVGPU_ZBC_CL_FMT_##i);			\
	(tbl)[ind].ref_cnt = nvgpu_safe_add_u32((tbl)[ind].ref_cnt, 1U);\
	ind = nvgpu_safe_add_u32(ind, 1U);				\
}

#define NVGPU_ZBC_CL_DS_R_1		0x00000000U
#define NVGPU_ZBC_CL_DS_G_1		0x00000000U
#define NVGPU_ZBC_CL_DS_B_1		0x00000000U
#define NVGPU_ZBC_CL_DS_A_1		0x3f800000U
#define NVGPU_ZBC_CL_L2_R_1		0xff000000U
#define NVGPU_ZBC_CL_L2_G_1		0xff000000U
#define NVGPU_ZBC_CL_L2_B_1		0xff000000U
#define NVGPU_ZBC_CL_L2_A_1		0xff000000U
#define NVGPU_ZBC_CL_FMT_1		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_2		0x00000000U
#define NVGPU_ZBC_CL_DS_G_2		0x00000000U
#define NVGPU_ZBC_CL_DS_B_2		0x00000000U
#define NVGPU_ZBC_CL_DS_A_2		0x00000000U
#define NVGPU_ZBC_CL_L2_R_2		0x00000000U
#define NVGPU_ZBC_CL_L2_G_2		0x00000000U
#define NVGPU_ZBC_CL_L2_B_2		0x00000000U
#define NVGPU_ZBC_CL_L2_A_2		0x00000000U
#define NVGPU_ZBC_CL_FMT_2		GR_ZBC_TRANSPARENT_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_3		0x3f800000U
#define NVGPU_ZBC_CL_DS_G_3		0x3f800000U
#define NVGPU_ZBC_CL_DS_B_3		0x3f800000U
#define NVGPU_ZBC_CL_DS_A_3		0x3f800000U
#define NVGPU_ZBC_CL_L2_R_3		0xffffffffU
#define NVGPU_ZBC_CL_L2_G_3		0xffffffffU
#define NVGPU_ZBC_CL_L2_B_3		0xffffffffU
#define NVGPU_ZBC_CL_L2_A_3		0xffffffffU
#define NVGPU_ZBC_CL_FMT_3		GR_ZBC_SOLID_WHITE_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_4		0x001a8000U
#define NVGPU_ZBC_CL_DS_G_4		0x001b8000U
#define NVGPU_ZBC_CL_DS_B_4		0x001c8000U
#define NVGPU_ZBC_CL_DS_A_4		0x001d8000U
#define NVGPU_ZBC_CL_L2_R_4		0x001e8000U
#define NVGPU_ZBC_CL_L2_G_4		0x001f8000U
#define NVGPU_ZBC_CL_L2_B_4		0x00218000U
#define NVGPU_ZBC_CL_L2_A_4		0x00228000U
#define NVGPU_ZBC_CL_FMT_4		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_5		0xbadfU
#define NVGPU_ZBC_CL_DS_G_5		0x00238000U
#define NVGPU_ZBC_CL_DS_B_5		0x00248000U
#define NVGPU_ZBC_CL_DS_A_5		0x00258000U
#define NVGPU_ZBC_CL_L2_R_5		0x00268000U
#define NVGPU_ZBC_CL_L2_G_5		0x00278000U
#define NVGPU_ZBC_CL_L2_B_5		0x00288000U
#define NVGPU_ZBC_CL_L2_A_5		0x00298000U
#define NVGPU_ZBC_CL_FMT_5		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_6		0x002a8000U
#define NVGPU_ZBC_CL_DS_G_6		0x002b8000U
#define NVGPU_ZBC_CL_DS_B_6		0x002c8000U
#define NVGPU_ZBC_CL_DS_A_6		0x002d8000U
#define NVGPU_ZBC_CL_L2_R_6		0x002e8000U
#define NVGPU_ZBC_CL_L2_G_6		0x002f8000U
#define NVGPU_ZBC_CL_L2_B_6		0x00318000U
#define NVGPU_ZBC_CL_L2_A_6		0xbadf0U
#define NVGPU_ZBC_CL_FMT_6		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_7		0x00328000U
#define NVGPU_ZBC_CL_DS_G_7		0x00338000U
#define NVGPU_ZBC_CL_DS_B_7		0x00348000U
#define NVGPU_ZBC_CL_DS_A_7		0x00358000U
#define NVGPU_ZBC_CL_L2_R_7		0x00368000U
#define NVGPU_ZBC_CL_L2_G_7		0x00378000U
#define NVGPU_ZBC_CL_L2_B_7		0x00388000U
#define NVGPU_ZBC_CL_L2_A_7		0x00398000U
#define NVGPU_ZBC_CL_FMT_7		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_8		0x003a8000U
#define NVGPU_ZBC_CL_DS_G_8		0x003b8000U
#define NVGPU_ZBC_CL_DS_B_8		0x003c8000U
#define NVGPU_ZBC_CL_DS_A_8		0x003d8000U
#define NVGPU_ZBC_CL_L2_R_8		0x003e8000U
#define NVGPU_ZBC_CL_L2_G_8		0x003f8000U
#define NVGPU_ZBC_CL_L2_B_8		0x00418000U
#define NVGPU_ZBC_CL_L2_A_8		0x00428000U
#define NVGPU_ZBC_CL_FMT_8		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_9		0x00438000U
#define NVGPU_ZBC_CL_DS_G_9		0x00448000U
#define NVGPU_ZBC_CL_DS_B_9		0x00458000U
#define NVGPU_ZBC_CL_DS_A_9		0x00468000U
#define NVGPU_ZBC_CL_L2_R_9		0x00478000U
#define NVGPU_ZBC_CL_L2_G_9		0x00488000U
#define NVGPU_ZBC_CL_L2_B_9		0x00498000U
#define NVGPU_ZBC_CL_L2_A_9		0x004a8000U
#define NVGPU_ZBC_CL_FMT_9		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_10		0x004b8000U
#define NVGPU_ZBC_CL_DS_G_10		0x004c8000U
#define NVGPU_ZBC_CL_DS_B_10		0x004d8000U
#define NVGPU_ZBC_CL_DS_A_10		0x004e8000U
#define NVGPU_ZBC_CL_L2_R_10		0x004f8000U
#define NVGPU_ZBC_CL_L2_G_10		0x00518000U
#define NVGPU_ZBC_CL_L2_B_10		0x00528000U
#define NVGPU_ZBC_CL_L2_A_10		0x00538000U
#define NVGPU_ZBC_CL_FMT_10		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_11		0x00548000U
#define NVGPU_ZBC_CL_DS_G_11		0x00558000U
#define NVGPU_ZBC_CL_DS_B_11		0x00568000U
#define NVGPU_ZBC_CL_DS_A_11		0x00578000U
#define NVGPU_ZBC_CL_L2_R_11		0x00588000U
#define NVGPU_ZBC_CL_L2_G_11		0x00598000U
#define NVGPU_ZBC_CL_L2_B_11		0x005a8000U
#define NVGPU_ZBC_CL_L2_A_11		0x005b8000U
#define NVGPU_ZBC_CL_FMT_11		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_12		0x005c8000U
#define NVGPU_ZBC_CL_DS_G_12		0x005d8000U
#define NVGPU_ZBC_CL_DS_B_12		0x005e8000U
#define NVGPU_ZBC_CL_DS_A_12		0x005f8000U
#define NVGPU_ZBC_CL_L2_R_12		0x00618000U
#define NVGPU_ZBC_CL_L2_G_12		0x00628000U
#define NVGPU_ZBC_CL_L2_B_12		0x00638000U
#define NVGPU_ZBC_CL_L2_A_12		0x00648000U
#define NVGPU_ZBC_CL_FMT_12		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_13		0x00658000U
#define NVGPU_ZBC_CL_DS_G_13		0x00668000U
#define NVGPU_ZBC_CL_DS_B_13		0x00678000U
#define NVGPU_ZBC_CL_DS_A_13		0x00688000U
#define NVGPU_ZBC_CL_L2_R_13		0x00698000U
#define NVGPU_ZBC_CL_L2_G_13		0x006a8000U
#define NVGPU_ZBC_CL_L2_B_13		0x006b8000U
#define NVGPU_ZBC_CL_L2_A_13		0x006c8000U
#define NVGPU_ZBC_CL_FMT_13		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_14		0x006d8000U
#define NVGPU_ZBC_CL_DS_G_14		0x006e8000U
#define NVGPU_ZBC_CL_DS_B_14		0x006f8000U
#define NVGPU_ZBC_CL_DS_A_14		0x00718000U
#define NVGPU_ZBC_CL_L2_R_14		0x00728000U
#define NVGPU_ZBC_CL_L2_G_14		0x00738000U
#define NVGPU_ZBC_CL_L2_B_14		0x00748000U
#define NVGPU_ZBC_CL_L2_A_14		0x00758000U
#define NVGPU_ZBC_CL_FMT_14		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_15		0xbadfU
#define NVGPU_ZBC_CL_DS_G_15		0x00768000U
#define NVGPU_ZBC_CL_DS_B_15		0x00778000U
#define NVGPU_ZBC_CL_DS_A_15		0x00788000U
#define NVGPU_ZBC_CL_L2_R_15		0xbadfU
#define NVGPU_ZBC_CL_L2_G_15		0x00798000U
#define NVGPU_ZBC_CL_L2_B_15		0x007a8000U
#define NVGPU_ZBC_CL_L2_A_15		0x007b8000U
#define NVGPU_ZBC_CL_FMT_15		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_16		0x007c8000U
#define NVGPU_ZBC_CL_DS_G_16		0x007d8000U
#define NVGPU_ZBC_CL_DS_B_16		0x007e8000U
#define NVGPU_ZBC_CL_DS_A_16		0x007f8000U
#define NVGPU_ZBC_CL_L2_R_16		0x00818000U
#define NVGPU_ZBC_CL_L2_G_16		0x00828000U
#define NVGPU_ZBC_CL_L2_B_16		0x00838000U
#define NVGPU_ZBC_CL_L2_A_16		0x00848000U
#define NVGPU_ZBC_CL_FMT_16		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_17		0x00858000U
#define NVGPU_ZBC_CL_DS_G_17		0x00868000U
#define NVGPU_ZBC_CL_DS_B_17		0x00878000U
#define NVGPU_ZBC_CL_DS_A_17		0x00888000U
#define NVGPU_ZBC_CL_L2_R_17		0x00898000U
#define NVGPU_ZBC_CL_L2_G_17		0x008a8000U
#define NVGPU_ZBC_CL_L2_B_17		0x008b8000U
#define NVGPU_ZBC_CL_L2_A_17		0x008c8000U
#define NVGPU_ZBC_CL_FMT_17		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_18		0x008d8000U
#define NVGPU_ZBC_CL_DS_G_18		0x008e8000U
#define NVGPU_ZBC_CL_DS_B_18		0x008f8000U
#define NVGPU_ZBC_CL_DS_A_18		0x00918000U
#define NVGPU_ZBC_CL_L2_R_18		0x00928000U
#define NVGPU_ZBC_CL_L2_G_18		0x00938000U
#define NVGPU_ZBC_CL_L2_B_18		0x00948000U
#define NVGPU_ZBC_CL_L2_A_18		0x00958000U
#define NVGPU_ZBC_CL_FMT_18		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_19		0x00968000U
#define NVGPU_ZBC_CL_DS_G_19		0x00978000U
#define NVGPU_ZBC_CL_DS_B_19		0x00988000U
#define NVGPU_ZBC_CL_DS_A_19		0x00998000U
#define NVGPU_ZBC_CL_L2_R_19		0x009a8000U
#define NVGPU_ZBC_CL_L2_G_19		0x009b8000U
#define NVGPU_ZBC_CL_L2_B_19		0x009c8000U
#define NVGPU_ZBC_CL_L2_A_19		0x009d8000U
#define NVGPU_ZBC_CL_FMT_19		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_20		0x009e8000U
#define NVGPU_ZBC_CL_DS_G_20		0x009f8000U
#define NVGPU_ZBC_CL_DS_B_20		0x00a18000U
#define NVGPU_ZBC_CL_DS_A_20		0x00a28000U
#define NVGPU_ZBC_CL_L2_R_20		0x00a38000U
#define NVGPU_ZBC_CL_L2_G_20		0x00a48000U
#define NVGPU_ZBC_CL_L2_B_20		0x00a58000U
#define NVGPU_ZBC_CL_L2_A_20		0x00a68000U
#define NVGPU_ZBC_CL_FMT_20		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_21		0x00a78000U
#define NVGPU_ZBC_CL_DS_G_21		0x00a88000U
#define NVGPU_ZBC_CL_DS_B_21		0x00a98000U
#define NVGPU_ZBC_CL_DS_A_21		0x00aa8000U
#define NVGPU_ZBC_CL_L2_R_21		0x00ab8000U
#define NVGPU_ZBC_CL_L2_G_21		0x00ac8000U
#define NVGPU_ZBC_CL_L2_B_21		0x00ad8000U
#define NVGPU_ZBC_CL_L2_A_21		0x00b18000U
#define NVGPU_ZBC_CL_FMT_21		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_22		0x00b28000U
#define NVGPU_ZBC_CL_DS_G_22		0x00b38000U
#define NVGPU_ZBC_CL_DS_B_22		0x00b48000U
#define NVGPU_ZBC_CL_DS_A_22		0x00b58000U
#define NVGPU_ZBC_CL_L2_R_22		0x00b68000U
#define NVGPU_ZBC_CL_L2_G_22		0x00b78000U
#define NVGPU_ZBC_CL_L2_B_22		0x00b88000U
#define NVGPU_ZBC_CL_L2_A_22		0x00b98000U
#define NVGPU_ZBC_CL_FMT_22		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_23		0x00ba8000U
#define NVGPU_ZBC_CL_DS_G_23		0x00bb8000U
#define NVGPU_ZBC_CL_DS_B_23		0x00bc8000U
#define NVGPU_ZBC_CL_DS_A_23		0x00bd8000U
#define NVGPU_ZBC_CL_L2_R_23		0x00be8000U
#define NVGPU_ZBC_CL_L2_G_23		0x00bf8000U
#define NVGPU_ZBC_CL_L2_B_23		0x00c18000U
#define NVGPU_ZBC_CL_L2_A_23		0x00c28000U
#define NVGPU_ZBC_CL_FMT_23		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_24		0x00c38000U
#define NVGPU_ZBC_CL_DS_G_24		0x00c48000U
#define NVGPU_ZBC_CL_DS_B_24		0x00c58000U
#define NVGPU_ZBC_CL_DS_A_24		0x00c68000U
#define NVGPU_ZBC_CL_L2_R_24		0x00c78000U
#define NVGPU_ZBC_CL_L2_G_24		0x00c88000U
#define NVGPU_ZBC_CL_L2_B_24		0x00c98000U
#define NVGPU_ZBC_CL_L2_A_24		0x00ca8000U
#define NVGPU_ZBC_CL_FMT_24		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_25		0x00cb8000U
#define NVGPU_ZBC_CL_DS_G_25		0x00cc8000U
#define NVGPU_ZBC_CL_DS_B_25		0x00cd8000U
#define NVGPU_ZBC_CL_DS_A_25		0x00d18000U
#define NVGPU_ZBC_CL_L2_R_25		0x00d28000U
#define NVGPU_ZBC_CL_L2_G_25		0x00d18000U
#define NVGPU_ZBC_CL_L2_B_25		0x00d28000U
#define NVGPU_ZBC_CL_L2_A_25		0x00d38000U
#define NVGPU_ZBC_CL_FMT_25		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_26		0x00d48000U
#define NVGPU_ZBC_CL_DS_G_26		0x00d58000U
#define NVGPU_ZBC_CL_DS_B_26		0x00d68000U
#define NVGPU_ZBC_CL_DS_A_26		0x00d78000U
#define NVGPU_ZBC_CL_L2_R_26		0x00d88000U
#define NVGPU_ZBC_CL_L2_G_26		0x00d98000U
#define NVGPU_ZBC_CL_L2_B_26		0x00da8000U
#define NVGPU_ZBC_CL_L2_A_26		0x00db8000U
#define NVGPU_ZBC_CL_FMT_26		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_27		0x00dc8000U
#define NVGPU_ZBC_CL_DS_G_27		0x00dd8000U
#define NVGPU_ZBC_CL_DS_B_27		0x00de8000U
#define NVGPU_ZBC_CL_DS_A_27		0x00df8000U
#define NVGPU_ZBC_CL_L2_R_27		0x00e18000U
#define NVGPU_ZBC_CL_L2_G_27		0x00e28000U
#define NVGPU_ZBC_CL_L2_B_27		0x00e38000U
#define NVGPU_ZBC_CL_L2_A_27		0x00e48000U
#define NVGPU_ZBC_CL_FMT_27		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_28		0x00e58000U
#define NVGPU_ZBC_CL_DS_G_28		0x00e68000U
#define NVGPU_ZBC_CL_DS_B_28		0x00e78000U
#define NVGPU_ZBC_CL_DS_A_28		0x00e88000U
#define NVGPU_ZBC_CL_L2_R_28		0x00e98000U
#define NVGPU_ZBC_CL_L2_G_28		0x00ea8000U
#define NVGPU_ZBC_CL_L2_B_28		0x00eb8000U
#define NVGPU_ZBC_CL_L2_A_28		0x00ec8000U
#define NVGPU_ZBC_CL_FMT_28		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_29		0x00f18000U
#define NVGPU_ZBC_CL_DS_G_29		0x00f28000U
#define NVGPU_ZBC_CL_DS_B_29		0x00f38000U
#define NVGPU_ZBC_CL_DS_A_29		0x00f48000U
#define NVGPU_ZBC_CL_L2_R_29		0x00f58000U
#define NVGPU_ZBC_CL_L2_G_29		0x00f68000U
#define NVGPU_ZBC_CL_L2_B_29		0x00f78000U
#define NVGPU_ZBC_CL_L2_A_29		0x00f88000U
#define NVGPU_ZBC_CL_FMT_29		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_CL_DS_R_30		0x0ae18000U
#define NVGPU_ZBC_CL_DS_G_30		0x0ae28000U
#define NVGPU_ZBC_CL_DS_B_30		0x0ae38000U
#define NVGPU_ZBC_CL_DS_A_30		0x0ae48000U
#define NVGPU_ZBC_CL_L2_R_30		0xbae18000U
#define NVGPU_ZBC_CL_L2_G_30		0xbae28000U
#define NVGPU_ZBC_CL_L2_B_30		0xbae38000U
#define NVGPU_ZBC_CL_L2_A_30		0xbae48000U
#define NVGPU_ZBC_CL_FMT_30		GR_ZBC_SOLID_BLACK_COLOR_FMT

#define NVGPU_ZBC_SET_DEPTH_ATTR(tbl, i)			\
{								\
	(tbl).depth = (NVGPU_ZBC_DPTH_##i);			\
	(tbl).format = (NVGPU_ZBC_DPTH_FMT_##i);		\
	(tbl).ref_cnt = nvgpu_safe_add_u32((tbl).ref_cnt, 1U);	\
}

#define NVGPU_ZBC_DPTH_1		0x3f800000U
#define NVGPU_ZBC_DPTH_FMT_1		GR_ZBC_Z_FMT_VAL_FP32
#define NVGPU_ZBC_DPTH_2		0U
#define NVGPU_ZBC_DPTH_FMT_2		GR_ZBC_Z_FMT_VAL_FP32

#define NVGPU_ZBC_SET_STENCIL_ATTR(tbl, i)			\
{								\
	(tbl).stencil = (NVGPU_ZBC_SCIL_##i);			\
	(tbl).format = (NVGPU_ZBC_SCIL_FMT_##i);		\
	(tbl).ref_cnt = nvgpu_safe_add_u32((tbl).ref_cnt, 1U);	\
}

#define NVGPU_ZBC_SCIL_1		0x00000000U
#define NVGPU_ZBC_SCIL_FMT_1		GR_ZBC_STENCIL_CLEAR_FMT_U8
#define NVGPU_ZBC_SCIL_2		0x00000001U
#define NVGPU_ZBC_SCIL_FMT_2		GR_ZBC_STENCIL_CLEAR_FMT_U8
#define NVGPU_ZBC_SCIL_3		0xffU
#define NVGPU_ZBC_SCIL_FMT_3		GR_ZBC_STENCIL_CLEAR_FMT_U8
#define NVGPU_ZBC_SCIL_4		0x3f800000U
#define NVGPU_ZBC_SCIL_FMT_4		GR_ZBC_STENCIL_CLEAR_FMT_U8
#define NVGPU_ZBC_SCIL_5		0x0ae28000U
#define NVGPU_ZBC_SCIL_FMT_5		GR_ZBC_STENCIL_CLEAR_FMT_U8
#endif
#endif /* ZBC_GA10B_H */
