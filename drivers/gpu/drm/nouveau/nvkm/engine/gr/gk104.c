/*
 * Copyright 2013 Red Hat Inc.
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
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#include "gf100.h"
#include "gk104.h"
#include "ctxgf100.h"

#include <nvif/class.h>

/*******************************************************************************
 * PGRAPH register lists
 ******************************************************************************/

const struct gf100_gr_init
gk104_gr_init_main_0[] = {
	{ 0x400080,   1, 0x04, 0x003083c2 },
	{ 0x400088,   1, 0x04, 0x0001ffe7 },
	{ 0x40008c,   1, 0x04, 0x00000000 },
	{ 0x400090,   1, 0x04, 0x00000030 },
	{ 0x40013c,   1, 0x04, 0x003901f7 },
	{ 0x400140,   1, 0x04, 0x00000100 },
	{ 0x400144,   1, 0x04, 0x00000000 },
	{ 0x400148,   1, 0x04, 0x00000110 },
	{ 0x400138,   1, 0x04, 0x00000000 },
	{ 0x400130,   2, 0x04, 0x00000000 },
	{ 0x400124,   1, 0x04, 0x00000002 },
	{}
};

static const struct gf100_gr_init
gk104_gr_init_ds_0[] = {
	{ 0x405844,   1, 0x04, 0x00ffffff },
	{ 0x405850,   1, 0x04, 0x00000000 },
	{ 0x405900,   1, 0x04, 0x0000ff34 },
	{ 0x405908,   1, 0x04, 0x00000000 },
	{ 0x405928,   2, 0x04, 0x00000000 },
	{}
};

static const struct gf100_gr_init
gk104_gr_init_sked_0[] = {
	{ 0x407010,   1, 0x04, 0x00000000 },
	{}
};

static const struct gf100_gr_init
gk104_gr_init_cwd_0[] = {
	{ 0x405b50,   1, 0x04, 0x00000000 },
	{}
};

static const struct gf100_gr_init
gk104_gr_init_gpc_unk_1[] = {
	{ 0x418d00,   1, 0x04, 0x00000000 },
	{ 0x418d28,   2, 0x04, 0x00000000 },
	{ 0x418f00,   1, 0x04, 0x00000000 },
	{ 0x418f08,   1, 0x04, 0x00000000 },
	{ 0x418f20,   2, 0x04, 0x00000000 },
	{ 0x418e00,   1, 0x04, 0x00000060 },
	{ 0x418e08,   1, 0x04, 0x00000000 },
	{ 0x418e1c,   2, 0x04, 0x00000000 },
	{}
};

const struct gf100_gr_init
gk104_gr_init_tpccs_0[] = {
	{ 0x419d0c,   1, 0x04, 0x00000000 },
	{ 0x419d10,   1, 0x04, 0x00000014 },
	{}
};

const struct gf100_gr_init
gk104_gr_init_pe_0[] = {
	{ 0x41980c,   1, 0x04, 0x00000010 },
	{ 0x419844,   1, 0x04, 0x00000000 },
	{ 0x419850,   1, 0x04, 0x00000004 },
	{ 0x419854,   2, 0x04, 0x00000000 },
	{}
};

static const struct gf100_gr_init
gk104_gr_init_l1c_0[] = {
	{ 0x419c98,   1, 0x04, 0x00000000 },
	{ 0x419ca8,   1, 0x04, 0x00000000 },
	{ 0x419cb0,   1, 0x04, 0x01000000 },
	{ 0x419cb4,   1, 0x04, 0x00000000 },
	{ 0x419cb8,   1, 0x04, 0x00b08bea },
	{ 0x419c84,   1, 0x04, 0x00010384 },
	{ 0x419cbc,   1, 0x04, 0x28137646 },
	{ 0x419cc0,   2, 0x04, 0x00000000 },
	{ 0x419c80,   1, 0x04, 0x00020232 },
	{}
};

static const struct gf100_gr_init
gk104_gr_init_sm_0[] = {
	{ 0x419e00,   1, 0x04, 0x00000000 },
	{ 0x419ea0,   1, 0x04, 0x00000000 },
	{ 0x419ee4,   1, 0x04, 0x00000000 },
	{ 0x419ea4,   1, 0x04, 0x00000100 },
	{ 0x419ea8,   1, 0x04, 0x00000000 },
	{ 0x419eb4,   4, 0x04, 0x00000000 },
	{ 0x419edc,   1, 0x04, 0x00000000 },
	{ 0x419f00,   1, 0x04, 0x00000000 },
	{ 0x419f74,   1, 0x04, 0x00000555 },
	{}
};

const struct gf100_gr_init
gk104_gr_init_be_0[] = {
	{ 0x40880c,   1, 0x04, 0x00000000 },
	{ 0x408850,   1, 0x04, 0x00000004 },
	{ 0x408910,   9, 0x04, 0x00000000 },
	{ 0x408950,   1, 0x04, 0x00000000 },
	{ 0x408954,   1, 0x04, 0x0000ffff },
	{ 0x408958,   1, 0x04, 0x00000034 },
	{ 0x408984,   1, 0x04, 0x00000000 },
	{ 0x408988,   1, 0x04, 0x08040201 },
	{ 0x40898c,   1, 0x04, 0x80402010 },
	{}
};

const struct gf100_gr_pack
gk104_gr_pack_mmio[] = {
	{ gk104_gr_init_main_0 },
	{ gf100_gr_init_fe_0 },
	{ gf100_gr_init_pri_0 },
	{ gf100_gr_init_rstr2d_0 },
	{ gf119_gr_init_pd_0 },
	{ gk104_gr_init_ds_0 },
	{ gf100_gr_init_scc_0 },
	{ gk104_gr_init_sked_0 },
	{ gk104_gr_init_cwd_0 },
	{ gf119_gr_init_prop_0 },
	{ gf108_gr_init_gpc_unk_0 },
	{ gf100_gr_init_setup_0 },
	{ gf100_gr_init_crstr_0 },
	{ gf108_gr_init_setup_1 },
	{ gf100_gr_init_zcull_0 },
	{ gf119_gr_init_gpm_0 },
	{ gk104_gr_init_gpc_unk_1 },
	{ gf100_gr_init_gcc_0 },
	{ gk104_gr_init_tpccs_0 },
	{ gf119_gr_init_tex_0 },
	{ gk104_gr_init_pe_0 },
	{ gk104_gr_init_l1c_0 },
	{ gf100_gr_init_mpc_0 },
	{ gk104_gr_init_sm_0 },
	{ gf117_gr_init_pes_0 },
	{ gf117_gr_init_wwdx_0 },
	{ gf117_gr_init_cbm_0 },
	{ gk104_gr_init_be_0 },
	{ gf100_gr_init_fe_1 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_main_0[] = {
	{ 0x4041f0, 1, 0x00004046 },
	{ 0x409890, 1, 0x00000045 },
	{ 0x4098b0, 1, 0x0000007f },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_rstr2d_0[] = {
	{ 0x4078c0, 1, 0x00000042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_unk_0[] = {
	{ 0x406000, 1, 0x00004044 },
	{ 0x405860, 1, 0x00004042 },
	{ 0x40590c, 1, 0x00004042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gcc_0[] = {
	{ 0x408040, 1, 0x00004044 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_sked_0[] = {
	{ 0x407000, 1, 0x00004044 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_unk_1[] = {
	{ 0x405bf0, 1, 0x00004044 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_ctxctl_0[] = {
	{ 0x41a890, 1, 0x00000042 },
	{ 0x41a8b0, 1, 0x0000007f },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_unk_0[] = {
	{ 0x418500, 1, 0x00004042 },
	{ 0x418608, 1, 0x00004042 },
	{ 0x418688, 1, 0x00004042 },
	{ 0x418718, 1, 0x00000042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_esetup_0[] = {
	{ 0x418828, 1, 0x00000044 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_tpbus_0[] = {
	{ 0x418bbc, 1, 0x00004042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_zcull_0[] = {
	{ 0x418970, 1, 0x00004042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_tpconf_0[] = {
	{ 0x418c70, 1, 0x00004042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_unk_1[] = {
	{ 0x418cf0, 1, 0x00004042 },
	{ 0x418d70, 1, 0x00004042 },
	{ 0x418f0c, 1, 0x00004042 },
	{ 0x418e0c, 1, 0x00004042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_gcc_0[] = {
	{ 0x419020, 1, 0x00004042 },
	{ 0x419038, 1, 0x00000042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_ffb_0[] = {
	{ 0x418898, 1, 0x00000042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_tex_0[] = {
	{ 0x419a40, 9, 0x00004042 },
	{ 0x419acc, 1, 0x00004047 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_poly_0[] = {
	{ 0x419868, 1, 0x00000042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_l1c_0[] = {
	{ 0x419ccc, 3, 0x00000042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_unk_2[] = {
	{ 0x419c70, 1, 0x00004045 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_mp_0[] = {
	{ 0x419fd0, 1, 0x00004043 },
	{ 0x419fd8, 1, 0x00004049 },
	{ 0x419fe0, 2, 0x00004042 },
	{ 0x419ff0, 1, 0x00004046 },
	{ 0x419ff8, 1, 0x00004042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_gpc_ppc_0[] = {
	{ 0x41be28, 1, 0x00000042 },
	{ 0x41bfe8, 1, 0x00004042 },
	{ 0x41bed0, 1, 0x00004042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_rop_zrop_0[] = {
	{ 0x408810, 2, 0x00004042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_rop_0[] = {
	{ 0x408a80, 6, 0x00004042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_rop_crop_0[] = {
	{ 0x4089a8, 1, 0x00004042 },
	{ 0x4089b0, 1, 0x00000042 },
	{ 0x4089b8, 1, 0x00004042 },
	{}
};

const struct nvkm_therm_clkgate_init
gk104_clkgate_blcg_init_pxbar_0[] = {
	{ 0x13c820, 1, 0x0001007f },
	{ 0x13cbe0, 1, 0x00000042 },
	{}
};

static const struct nvkm_therm_clkgate_pack
gk104_clkgate_pack[] = {
	{ gk104_clkgate_blcg_init_main_0 },
	{ gk104_clkgate_blcg_init_rstr2d_0 },
	{ gk104_clkgate_blcg_init_unk_0 },
	{ gk104_clkgate_blcg_init_gcc_0 },
	{ gk104_clkgate_blcg_init_sked_0 },
	{ gk104_clkgate_blcg_init_unk_1 },
	{ gk104_clkgate_blcg_init_gpc_ctxctl_0 },
	{ gk104_clkgate_blcg_init_gpc_unk_0 },
	{ gk104_clkgate_blcg_init_gpc_esetup_0 },
	{ gk104_clkgate_blcg_init_gpc_tpbus_0 },
	{ gk104_clkgate_blcg_init_gpc_zcull_0 },
	{ gk104_clkgate_blcg_init_gpc_tpconf_0 },
	{ gk104_clkgate_blcg_init_gpc_unk_1 },
	{ gk104_clkgate_blcg_init_gpc_gcc_0 },
	{ gk104_clkgate_blcg_init_gpc_ffb_0 },
	{ gk104_clkgate_blcg_init_gpc_tex_0 },
	{ gk104_clkgate_blcg_init_gpc_poly_0 },
	{ gk104_clkgate_blcg_init_gpc_l1c_0 },
	{ gk104_clkgate_blcg_init_gpc_unk_2 },
	{ gk104_clkgate_blcg_init_gpc_mp_0 },
	{ gk104_clkgate_blcg_init_gpc_ppc_0 },
	{ gk104_clkgate_blcg_init_rop_zrop_0 },
	{ gk104_clkgate_blcg_init_rop_0 },
	{ gk104_clkgate_blcg_init_rop_crop_0 },
	{ gk104_clkgate_blcg_init_pxbar_0 },
	{}
};

/*******************************************************************************
 * PGRAPH engine/subdev functions
 ******************************************************************************/

void
gk104_gr_init_rop_active_fbps(struct gf100_gr *gr)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	const u32 fbp_count = nvkm_rd32(device, 0x120074);
	nvkm_mask(device, 0x408850, 0x0000000f, fbp_count); /* zrop */
	nvkm_mask(device, 0x408958, 0x0000000f, fbp_count); /* crop */
}

void
gk104_gr_init_ppc_exceptions(struct gf100_gr *gr)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	int gpc, ppc;

	for (gpc = 0; gpc < gr->gpc_nr; gpc++) {
		for (ppc = 0; ppc < gr->ppc_nr[gpc]; ppc++) {
			if (!(gr->ppc_mask[gpc] & (1 << ppc)))
				continue;
			nvkm_wr32(device, PPC_UNIT(gpc, ppc, 0x038), 0xc0000000);
		}
	}
}

int
gk104_gr_init(struct gf100_gr *gr)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	const u32 magicgpc918 = DIV_ROUND_UP(0x00800000, gr->tpc_total);
	u32 data[TPC_MAX / 8] = {};
	u8  tpcnr[GPC_MAX];
	int gpc, tpc, rop;
	int i;

	gr->func->init_gpc_mmu(gr);

	gf100_gr_mmio(gr, gr->func->mmio);
	if (gr->func->clkgate_pack)
		nvkm_therm_clkgate_init(gr->base.engine.subdev.device->therm,
					gr->func->clkgate_pack);

	nvkm_wr32(device, GPC_UNIT(0, 0x3018), 0x00000001);

	memset(data, 0x00, sizeof(data));
	memcpy(tpcnr, gr->tpc_nr, sizeof(gr->tpc_nr));
	for (i = 0, gpc = -1; i < gr->tpc_total; i++) {
		do {
			gpc = (gpc + 1) % gr->gpc_nr;
		} while (!tpcnr[gpc]);
		tpc = gr->tpc_nr[gpc] - tpcnr[gpc]--;

		data[i / 8] |= tpc << ((i % 8) * 4);
	}

	nvkm_wr32(device, GPC_BCAST(0x0980), data[0]);
	nvkm_wr32(device, GPC_BCAST(0x0984), data[1]);
	nvkm_wr32(device, GPC_BCAST(0x0988), data[2]);
	nvkm_wr32(device, GPC_BCAST(0x098c), data[3]);

	for (gpc = 0; gpc < gr->gpc_nr; gpc++) {
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0914),
			  gr->screen_tile_row_offset << 8 | gr->tpc_nr[gpc]);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0910), 0x00040000 |
							 gr->tpc_total);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0918), magicgpc918);
	}

	nvkm_wr32(device, GPC_BCAST(0x3fd4), magicgpc918);
	nvkm_wr32(device, GPC_BCAST(0x08ac), nvkm_rd32(device, 0x100800));

	gr->func->init_rop_active_fbps(gr);

	nvkm_wr32(device, 0x400500, 0x00010001);

	nvkm_wr32(device, 0x400100, 0xffffffff);
	nvkm_wr32(device, 0x40013c, 0xffffffff);

	nvkm_wr32(device, 0x409ffc, 0x00000000);
	nvkm_wr32(device, 0x409c14, 0x00003e3e);
	nvkm_wr32(device, 0x409c24, 0x000f0001);
	nvkm_wr32(device, 0x404000, 0xc0000000);
	nvkm_wr32(device, 0x404600, 0xc0000000);
	nvkm_wr32(device, 0x408030, 0xc0000000);
	nvkm_wr32(device, 0x404490, 0xc0000000);
	nvkm_wr32(device, 0x406018, 0xc0000000);
	nvkm_wr32(device, 0x407020, 0x40000000);
	nvkm_wr32(device, 0x405840, 0xc0000000);
	nvkm_wr32(device, 0x405844, 0x00ffffff);
	nvkm_mask(device, 0x419cc0, 0x00000008, 0x00000008);
	nvkm_mask(device, 0x419eb4, 0x00001000, 0x00001000);

	gr->func->init_ppc_exceptions(gr);

	for (gpc = 0; gpc < gr->gpc_nr; gpc++) {
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0420), 0xc0000000);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0900), 0xc0000000);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x1028), 0xc0000000);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0824), 0xc0000000);
		for (tpc = 0; tpc < gr->tpc_nr[gpc]; tpc++) {
			nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x508), 0xffffffff);
			nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x50c), 0xffffffff);
			nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x224), 0xc0000000);
			nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x48c), 0xc0000000);
			nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x084), 0xc0000000);
			nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x644), 0x001ffffe);
			nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x64c), 0x0000000f);
		}
		nvkm_wr32(device, GPC_UNIT(gpc, 0x2c90), 0xffffffff);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x2c94), 0xffffffff);
	}

	for (rop = 0; rop < gr->rop_nr; rop++) {
		nvkm_wr32(device, ROP_UNIT(rop, 0x144), 0xc0000000);
		nvkm_wr32(device, ROP_UNIT(rop, 0x070), 0xc0000000);
		nvkm_wr32(device, ROP_UNIT(rop, 0x204), 0xffffffff);
		nvkm_wr32(device, ROP_UNIT(rop, 0x208), 0xffffffff);
	}

	nvkm_wr32(device, 0x400108, 0xffffffff);
	nvkm_wr32(device, 0x400138, 0xffffffff);
	nvkm_wr32(device, 0x400118, 0xffffffff);
	nvkm_wr32(device, 0x400130, 0xffffffff);
	nvkm_wr32(device, 0x40011c, 0xffffffff);
	nvkm_wr32(device, 0x400134, 0xffffffff);

	nvkm_wr32(device, 0x400054, 0x34ce3464);

	gf100_gr_zbc_init(gr);

	return gf100_gr_init_ctxctl(gr);
}

#include "fuc/hubgk104.fuc3.h"

static struct gf100_gr_ucode
gk104_gr_fecs_ucode = {
	.code.data = gk104_grhub_code,
	.code.size = sizeof(gk104_grhub_code),
	.data.data = gk104_grhub_data,
	.data.size = sizeof(gk104_grhub_data),
};

#include "fuc/gpcgk104.fuc3.h"

static struct gf100_gr_ucode
gk104_gr_gpccs_ucode = {
	.code.data = gk104_grgpc_code,
	.code.size = sizeof(gk104_grgpc_code),
	.data.data = gk104_grgpc_data,
	.data.size = sizeof(gk104_grgpc_data),
};

static const struct gf100_gr_func
gk104_gr = {
	.init = gk104_gr_init,
	.init_gpc_mmu = gf100_gr_init_gpc_mmu,
	.init_rop_active_fbps = gk104_gr_init_rop_active_fbps,
	.init_ppc_exceptions = gk104_gr_init_ppc_exceptions,
	.mmio = gk104_gr_pack_mmio,
	.fecs.ucode = &gk104_gr_fecs_ucode,
	.gpccs.ucode = &gk104_gr_gpccs_ucode,
	.rops = gf100_gr_rops,
	.ppc_nr = 1,
	.grctx = &gk104_grctx,
	.clkgate_pack = gk104_clkgate_pack,
	.sclass = {
		{ -1, -1, FERMI_TWOD_A },
		{ -1, -1, KEPLER_INLINE_TO_MEMORY_A },
		{ -1, -1, KEPLER_A, &gf100_fermi },
		{ -1, -1, KEPLER_COMPUTE_A },
		{}
	}
};

int
gk104_gr_new(struct nvkm_device *device, int index, struct nvkm_gr **pgr)
{
	return gf100_gr_new_(&gk104_gr, device, index, pgr);
}
