/*
 * Copyright (c) 2011-2021, NVIDIA CORPORATION.  All rights reserved.
 *
 * GK20A Graphics
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
#ifndef GK20A_H
#define GK20A_H

/**
 * @mainpage
 *
 * NVGPU Design Documentation
 * ==========================
 *
 * Welcome to the nvgpu unit design documentation. The following pages document
 * the major top level units within nvgpu-common:
 *
 *   - @ref unit-ce
 *   - @ref unit-mm
 *   - @ref unit-common-bus
 *   - @ref unit-fifo
 *   - @ref unit-gr
 *   - @ref unit-fb
 *   - @ref unit-devctl
 *   - @ref unit-sdl
 *   - @ref unit-init
 *   - @ref unit-qnx_init
 *   - @ref unit-falcon
 *   - @ref unit-os_utils
 *   - @ref unit-acr
 *   - @ref unit-cg
 *   - @ref unit-pmu
 *   - @ref unit-common-priv-ring
 *   - @ref unit-common-nvgpu
 *   - @ref unit-common-ltc
 *   - @ref unit-common-utils
 *   - @ref unit-common-netlist
 *   - @ref unit-mc
 *   - Etc, etc.
 *
 * NVGPU Software Unit Design Documentation
 * ========================================
 *
 * For each top level unit, a corresponding Unit Test Specification is
 * available in the @ref NVGPU-SWUTS
 *
 * nvgpu-driver Level Requirements Table
 * =====================================
 *
 * ...
 */

struct gk20a;
struct nvgpu_acr;
struct nvgpu_fifo;
struct nvgpu_channel;
struct nvgpu_gr;
struct nvgpu_fbp;
struct sim_nvgpu;
struct nvgpu_ce_app;
struct gk20a_ctxsw_trace;
struct nvgpu_mem_alloc_tracker;
struct nvgpu_profiler_object;
struct nvgpu_debug_context;
struct nvgpu_clk_pll_debug_data;
struct nvgpu_nvhost_dev;
struct nvgpu_netlist_vars;
struct netlist_av64_list;
#ifdef CONFIG_NVGPU_FECS_TRACE
struct nvgpu_gr_fecs_trace;
#endif
struct nvgpu_cpu_time_correlation_sample;
#ifdef CONFIG_NVGPU_CLK_ARB
struct nvgpu_clk_arb;
#endif
struct nvgpu_setup_bind_args;
struct boardobjgrp;
struct boardobjgrp_pmu_cmd;
struct boardobjgrpmask;
struct nvgpu_sgt;
struct nvgpu_channel_hw_state;
struct nvgpu_mem;
struct gk20a_cs_snapshot_client;
struct dbg_session_gk20a;
struct nvgpu_dbg_reg_op;
struct gk20a_cs_snapshot;
struct _resmgr_context;
struct nvgpu_gpfifo_entry;
struct vm_gk20a_mapping_batch;
struct pmu_pg_stats_data;
struct clk_domains_mon_status_params;
struct nvgpu_cic_mon;
struct nvgpu_cic_rm;
#ifdef CONFIG_NVGPU_GSP_SCHEDULER
struct nvgpu_gsp;
#endif

enum nvgpu_flush_op;
enum gk20a_mem_rw_flag;
enum nvgpu_nvlink_minion_dlcmd;
enum nvgpu_profiler_pm_resource_type;
enum nvgpu_profiler_pm_reservation_scope;

#include <nvgpu/lock.h>
#include <nvgpu/thread.h>
#include <nvgpu/utils.h>

#include <nvgpu/mm.h>
#include <nvgpu/as.h>
#include <nvgpu/log.h>
#include <nvgpu/kref.h>
#include <nvgpu/pmu.h>
#include <nvgpu/atomic.h>
#include <nvgpu/barrier.h>
#include <nvgpu/rwsem.h>
#include <nvgpu/nvlink.h>
#include <nvgpu/nvlink_link_mode_transitions.h>
#include <nvgpu/ecc.h>
#include <nvgpu/channel.h>
#include <nvgpu/tsg.h>
#include <nvgpu/sec2/sec2.h>
#include <nvgpu/cbc.h>
#include <nvgpu/ltc.h>
#include <nvgpu/worker.h>
#ifdef CONFIG_NVGPU_DGPU
#include <nvgpu/bios.h>
#endif
#include <nvgpu/semaphore.h>
#include <nvgpu/fifo.h>
#include <nvgpu/sched.h>
#ifdef CONFIG_TEGRA_HV_MANAGER
#include <nvgpu/ipa_pa_cache.h>
#endif
#include <nvgpu/mig.h>

#include <nvgpu/gpu_ops.h>

#include "hal/clk/clk_gk20a.h"

/**
 * @addtogroup unit-common-nvgpu
 * @{
 */

#ifdef CONFIG_DEBUG_FS
struct railgate_stats {
	unsigned long last_rail_gate_start;
	unsigned long last_rail_gate_complete;
	unsigned long last_rail_ungate_start;
	unsigned long last_rail_ungate_complete;
	unsigned long total_rail_gate_time_ms;
	unsigned long total_rail_ungate_time_ms;
	unsigned long railgating_cycle_count;
};
#endif

/**
 * @defgroup NVGPU_COMMON_NVGPU_DEFINES
 *
 * GPU litters defines.
 */

/**
 * @ingroup NVGPU_COMMON_NVGPU_DEFINES
 * @{
 */

/** Number of gpcs. */
#define GPU_LIT_NUM_GPCS	0
/** Number of pes per gpc. */
#define GPU_LIT_NUM_PES_PER_GPC 1
/** Number of zcull banks. */
#define GPU_LIT_NUM_ZCULL_BANKS 2
/** Number of tpcs per gpc. */
#define GPU_LIT_NUM_TPC_PER_GPC 3
/** Number of SMs per tpc. */
#define GPU_LIT_NUM_SM_PER_TPC  4
/** Number of fbps. */
#define GPU_LIT_NUM_FBPS	5
/** Gpc base address. */
#define GPU_LIT_GPC_BASE	6
/** Gpc stride. */
#define GPU_LIT_GPC_STRIDE	7
/** Gpc shared base offset. */
#define GPU_LIT_GPC_SHARED_BASE 8
/** Tpc's base offset in gpc. */
#define GPU_LIT_TPC_IN_GPC_BASE 9
/** Tpc's stride in gpc. */
#define GPU_LIT_TPC_IN_GPC_STRIDE 10
/** Tpc's shared base offset in gpc. */
#define GPU_LIT_TPC_IN_GPC_SHARED_BASE 11
/** Ppc's base offset in gpc. */
#define GPU_LIT_PPC_IN_GPC_BASE	12
/** Ppc's stride in gpc. */
#define GPU_LIT_PPC_IN_GPC_STRIDE 13
/** Ppc's shared base offset in gpc. */
#define GPU_LIT_PPC_IN_GPC_SHARED_BASE 14
/** Rop base offset. */
#define GPU_LIT_ROP_BASE	15
/** Rop stride. */
#define GPU_LIT_ROP_STRIDE	16
/** Rop shared base offset. */
#define GPU_LIT_ROP_SHARED_BASE 17
/** Number of host engines. */
#define GPU_LIT_HOST_NUM_ENGINES 18
/** Number of host pbdma. */
#define GPU_LIT_HOST_NUM_PBDMA	19
/** LTC stride. */
#define GPU_LIT_LTC_STRIDE	20
/** LTS stride. */
#define GPU_LIT_LTS_STRIDE	21
/** Number of fbpas. */
#define GPU_LIT_NUM_FBPAS	22
/** Fbpa stride. */
#define GPU_LIT_FBPA_STRIDE	23
/** Fbpa base offset. */
#define GPU_LIT_FBPA_BASE	24
/** Fbpa shared base offset. */
#define GPU_LIT_FBPA_SHARED_BASE 25
/** Sm pri stride. */
#define GPU_LIT_SM_PRI_STRIDE	26
/** Smpc pri base offset. */
#define GPU_LIT_SMPC_PRI_BASE		27
/** Smpc pri shared base offset. */
#define GPU_LIT_SMPC_PRI_SHARED_BASE	28
/** Smpc pri unique base offset. */
#define GPU_LIT_SMPC_PRI_UNIQUE_BASE	29
/** Smpc pri stride. */
#define GPU_LIT_SMPC_PRI_STRIDE		30
/** Twod class. */
#define GPU_LIT_TWOD_CLASS	31
/** Threed class. */
#define GPU_LIT_THREED_CLASS	32
/** Compute class. */
#define GPU_LIT_COMPUTE_CLASS	33
/** Gpfifo class. */
#define GPU_LIT_GPFIFO_CLASS	34
/** I2m class. */
#define GPU_LIT_I2M_CLASS	35
/** Dma copy class. */
#define GPU_LIT_DMA_COPY_CLASS	36
/** Gpc priv stride. */
#define GPU_LIT_GPC_PRIV_STRIDE	37
/** @cond DOXYGEN_SHOULD_SKIP_THIS */
#define GPU_LIT_PERFMON_PMMGPCTPCA_DOMAIN_START 38
#define GPU_LIT_PERFMON_PMMGPCTPCB_DOMAIN_START 39
#define GPU_LIT_PERFMON_PMMGPCTPC_DOMAIN_COUNT  40
#define GPU_LIT_PERFMON_PMMFBP_LTC_DOMAIN_START 41
#define GPU_LIT_PERFMON_PMMFBP_LTC_DOMAIN_COUNT 42
#define GPU_LIT_PERFMON_PMMFBP_ROP_DOMAIN_START 43
#define GPU_LIT_PERFMON_PMMFBP_ROP_DOMAIN_COUNT 44
#define GPU_LIT_SM_UNIQUE_BASE			45
#define GPU_LIT_SM_SHARED_BASE			46
#define GPU_LIT_GPC_ADDR_WIDTH			47
#define GPU_LIT_TPC_ADDR_WIDTH			48
#define GPU_LIT_MAX_RUNLISTS_SUPPORTED		49
#define GPU_LIT_NUM_LTC_LTS_SETS		50
#define GPU_LIT_NUM_LTC_LTS_WAYS		51
#define GPU_LIT_ROP_IN_GPC_BASE			52
#define GPU_LIT_ROP_IN_GPC_SHARED_BASE		53
#define GPU_LIT_ROP_IN_GPC_PRI_SHARED_IDX	54
#define GPU_LIT_ROP_IN_GPC_STRIDE		55

/** @endcond */

/** Macro to get litter values corresponding to the litter defines. */
#define nvgpu_get_litter_value(g, v) ((g)->ops.get_litter_value((g), v))

/**
 * @}
 */

/** @cond DOXYGEN_SHOULD_SKIP_THIS */
/* MAX_TPC_PG_CONFIGS describes the maximum number of
 * valid confiurations we can have for the TPC mask. The valid
 * mask is used by SW to write to NV_FUSE_OPT_CTRL_GPC_TPC
 * register to powergate the TPC in each GPC
 *
 * MAX_GPC_FBP_FS_CONFIGS describes the maximum number of
 * valid confiurations we can have for the GPC and FBP mask.
 * The valid mask is used by SW to write to NV_FUSE_OPT_CTRL_GPC
 * NV_FUSE_OPT_CTRL_FBP registers to powergate the GPC and
 * floorsweep FBP
 */
#define MAX_TPC_PG_CONFIGS      9
#define MAX_GPC_FBP_FS_CONFIGS	3

struct nvgpu_gpfifo_userdata {
	struct nvgpu_gpfifo_entry nvgpu_user *entries;
	struct _resmgr_context *context;
};

enum nvgpu_event_id_type {
	NVGPU_EVENT_ID_BPT_INT = 0,
	NVGPU_EVENT_ID_BPT_PAUSE = 1,
	NVGPU_EVENT_ID_BLOCKING_SYNC = 2,
	NVGPU_EVENT_ID_CILP_PREEMPTION_STARTED = 3,
	NVGPU_EVENT_ID_CILP_PREEMPTION_COMPLETE = 4,
	NVGPU_EVENT_ID_GR_SEMAPHORE_WRITE_AWAKEN = 5,
	NVGPU_EVENT_ID_MAX = 6,
};
/** @endcond */

/**
 * @brief HW version info read from the HW.
 */
struct nvgpu_gpu_params {
	/** GPU architecture ID */
	u32 gpu_arch;
	/** GPU implementation ID */
	u32 gpu_impl;
	/** GPU revision ID */
	u32 gpu_rev;
	/** sm version */
	u32 sm_arch_sm_version;
	/** sm instruction set */
	u32 sm_arch_spa_version;
	/** total number of physical warps possible on an SM. */
	u32 sm_arch_warp_count;
};

/**
 * @brief The GPU superstructure.
 *
 * This structure describes the GPU. There is a unique \a gk20a struct for each
 * GPU in the system. This structure includes many state variables used
 * throughout the driver. It also contains the #gpu_ops HALs.
 *
 * Whenever possible, units should keep their data within their own sub-struct
 * and not in the main gk20a struct.
 */
struct gk20a {
	/**
	 * @brief Free data in the struct allocated during its creation.
	 *
	 * @param g [in]	The GPU superstructure
	 *
	 * This does not free all of the memory in the structure as many of the
	 * units allocate private data, and those units are responsible for
	 * freeing that data. \a gfree should be called after all of the units
	 * have had the opportunity to free their private data.
	 */
	void (*gfree)(struct gk20a *g);

	/** Starting virtual address of mapped bar0 io region. */
	uintptr_t regs;
	u64 regs_size;
	u64 regs_bus_addr;

	/** Starting virtual address of mapped bar1 io region. */
	uintptr_t bar1;

	/** Starting virtual address of usermode registers io region. */
	uintptr_t usermode_regs;
	u64 usermode_regs_bus_addr;

	uintptr_t regs_saved;
	uintptr_t bar1_saved;
	uintptr_t usermode_regs_saved;

	/**
	 * Handle to access nvhost APIs.
	 */
	struct nvgpu_nvhost_dev *nvhost;

	/**
	 * Used by <nvgpu/errata.h>. Do not access directly!
	 */
	unsigned long *errata_flags;

	/**
	 * Used by <nvgpu/enabled.h>. Do not access directly!
	 */
	unsigned long *enabled_flags;

	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	/** Used by Linux module to keep track of driver usage */
	nvgpu_atomic_t usage_count;
	/** @endcond */

	/** Used by common.init unit to track users of the driver */
	struct nvgpu_ref refcount;

	/** Name of the gpu. */
	const char *name;

	/** Is the GPU ready to be used? */
	u32 power_on_state;

	/** Is the GPU probe complete? */
	bool probe_done;

#ifdef CONFIG_NVGPU_DGPU
	bool gpu_reset_done;
#endif
#ifdef CONFIG_PM
	bool suspended;
#endif
	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	bool sw_ready;
	/** @endcond */

	/** Flag to indicate that quiesce framework is initialized. */
	bool sw_quiesce_init_done;
	/** Flag to indicate that system is transitioning to quiesce state. */
	bool sw_quiesce_pending;
	/** Condition variable on which quiesce thread waits. */
	struct nvgpu_cond sw_quiesce_cond;
	/** Quiesce thread id. */
	struct nvgpu_thread sw_quiesce_thread;
	/**
	 * Struct having callback and it's arguments. The callback gets called
	 * when BUG() is hit by the code.
	 */
	struct nvgpu_bug_cb sw_quiesce_bug_cb;

	/** An entry into list of callbacks to be called when BUG() is hit. */
	struct nvgpu_list_node bug_node;

	/** Controls which messages are logged */
	u64 log_mask;
	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	u32 log_trace;

	struct nvgpu_mutex static_pg_lock;
	/** @endcond */

	/** Stored HW version info */
	struct nvgpu_gpu_params params;

#ifdef CONFIG_NVGPU_DETERMINISTIC_CHANNELS
	/**
	 * Guards access to hardware when usual gk20a_{busy,idle} are skipped
	 * for submits and held for channel lifetime but dropped for an ongoing
	 * gk20a_do_idle().
	 */
	struct nvgpu_rwsem deterministic_busy;
#endif
	/** Pointer to struct containing netlist data of ucodes. */
	struct nvgpu_netlist_vars *netlist_vars;
	/** Flag to indicate initialization status of netlists. */
	bool netlist_valid;

	/** Struct holding the pmu falcon software state. */
	struct nvgpu_falcon pmu_flcn;
	/** Struct holding the fecs falcon software state. */
	struct nvgpu_falcon fecs_flcn;
	/** Struct holding the gpccs falcon software state. */
	struct nvgpu_falcon gpccs_flcn;
	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	struct nvgpu_falcon nvdec_flcn;
	struct nvgpu_falcon minion_flcn;
	struct nvgpu_falcon gsp_flcn;
	struct clk_gk20a clk;
	/** @endcond */
	/** Top level struct maintaining fifo unit's software state. */
	struct nvgpu_fifo fifo;
	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	struct nvgpu_nvlink_dev nvlink;
	/** @endcond */
	/** Pointer to struct maintaining multiple GR instance's software state. */
	struct nvgpu_gr *gr;
	u32 num_gr_instances;
	/** Pointer to struct maintaining fbp unit's software state. */
	struct nvgpu_fbp *fbp;
#ifdef CONFIG_NVGPU_SIM
	struct sim_nvgpu *sim;
#endif
	struct nvgpu_device_list *devs;
	/** Top level struct maintaining MM unit's software state. */
	struct mm_gk20a mm;
	/** Pointer to struct maintaining PMU unit's software state. */
	struct nvgpu_pmu *pmu;
	/** Pointer to struct maintaining ACR unit's software state. */
	struct nvgpu_acr *acr;
#ifdef CONFIG_NVGPU_GSP_SCHEDULER
	/** Pointer to struct maintaining GSP unit's software state. */
	struct nvgpu_gsp *gsp;
#endif
	/** Top level struct maintaining ECC unit's software state. */
	struct nvgpu_ecc ecc;
	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	struct pmgr_pmupstate *pmgr_pmu;
	struct nvgpu_sec2 sec2;
	/** @endcond */
#ifdef CONFIG_NVGPU_CHANNEL_TSG_SCHEDULING
	struct nvgpu_sched_ctrl sched_ctrl;
#endif

#ifdef CONFIG_DEBUG_FS
	struct railgate_stats pstats;
#endif
	/** Global default timeout for use throughout driver */
	u32 poll_timeout_default;
	/** User disabled timeouts */
	bool timeouts_disabled_by_user;

	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	unsigned int ch_wdt_init_limit_ms;
	/** @endcond */
	/**
	 * Timeout after which ctxsw timeout interrupt (if enabled by s/w) will
	 * be triggered by h/w if context fails to context switch.
	 */
	u32 ctxsw_timeout_period_ms;
	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	u32 ctxsw_wdt_period_us;

	struct nvgpu_mutex power_lock;
	/** @endcond */

	/** Lock to protect accessing \a power_on_state. */
	struct nvgpu_spinlock power_spinlock;

	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	/** Channel priorities */
	u32 tsg_timeslice_low_priority_us;
	u32 tsg_timeslice_medium_priority_us;
	u32 tsg_timeslice_high_priority_us;
	u32 tsg_timeslice_min_us;
	u32 tsg_timeslice_max_us;
	u32 tsg_dbg_timeslice_max_us;
	bool runlist_interleave;
	/** @endcond */

	/** Lock serializing CG an PG programming for various units */
	struct nvgpu_mutex cg_pg_lock;
	/** SLCG setting read from the platform data */
	bool slcg_enabled;
	/** BLCG setting read from the platform data */
	bool blcg_enabled;
	/** ELCG setting read from the platform data */
	bool elcg_enabled;
	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	bool elpg_enabled;
	bool aelpg_enabled;
	bool can_elpg;
	bool mscg_enabled;
	bool forced_idle;
	bool allow_all;
	/** @endcond */

	/** Ptimer source frequency. */
	u32 ptimer_src_freq;

	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	int railgate_delay;
	u8 ldiv_slowdown_factor;
	unsigned int aggressive_sync_destroy_thresh;
	bool aggressive_sync_destroy;
	/** @endcond */

	/** Is LS PMU supported? */
	bool support_ls_pmu;

	/** Is this a virtual GPU? */
	bool is_virtual;

	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	bool has_cde;

	u32 emc3d_ratio;
	/** @endcond */

	/**
	 * A group of semaphore pools. One for each channel.
	 */
	struct nvgpu_semaphore_sea *sema_sea;

#ifdef CONFIG_NVGPU_DEBUGGER
	/* held while manipulating # of debug/profiler sessions present */
	/* also prevents debug sessions from attaching until released */
	struct nvgpu_mutex dbg_sessions_lock;
	int dbg_powergating_disabled_refcount; /*refcount for pg disable */
	/*refcount for timeout disable */
	nvgpu_atomic_t timeouts_disabled_refcount;

	/* must have dbg_sessions_lock before use */
	struct nvgpu_dbg_reg_op *dbg_regops_tmp_buf;
	u32 dbg_regops_tmp_buf_ops;

	/* For perfbuf mapping */
	struct {
		struct dbg_session_gk20a *owner;
		u64 offset;
	} perfbuf;

	bool mmu_debug_ctrl;
	u32 mmu_debug_mode_refcnt;
#endif /* CONFIG_NVGPU_DEBUGGER */

#ifdef CONFIG_NVGPU_PROFILER
	struct nvgpu_list_node profiler_objects;
	struct nvgpu_pm_resource_reservations *pm_reservations;
	nvgpu_atomic_t hwpm_refcount;

	u32 num_sys_perfmon;
	u32 num_gpc_perfmon;
	u32 num_fbp_perfmon;
#endif

#ifdef CONFIG_NVGPU_FECS_TRACE
	struct gk20a_ctxsw_trace *ctxsw_trace;
	struct nvgpu_gr_fecs_trace *fecs_trace;
#endif

#ifdef CONFIG_NVGPU_CYCLESTATS
	struct nvgpu_mutex		cs_lock;
	struct gk20a_cs_snapshot	*cs_data;
#endif

	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	/* Called after all references to driver are gone. Unused in safety */
	void (*remove_support)(struct gk20a *g);

	u64 pg_ingating_time_us;
	u64 pg_ungating_time_us;
	u32 pg_gating_cnt;
	/** @endcond */

	/** GPU address-space identifier. */
	struct gk20a_as as;

	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	struct nvgpu_mutex client_lock;
	int client_refcount; /* open channels and ctrl nodes */
	/** @endcond */

	/** The HAL function pointers */
	struct gpu_ops ops;

	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	/*used for change of enum zbc update cmd id from ver 0 to ver1*/
	u8 pmu_ver_cmd_id_zbc_table_update;
	/** @endcond */

	/** Top level struct managing interrupt handling. */
	struct nvgpu_mc mc;

	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	/*
	 * The deductible memory size for max_comptag_mem (in MBytes)
	 * Usually close to memory size that running system is taking
	*/
	u32 comptag_mem_deduct;

#ifdef CONFIG_NVGPU_COMPRESSION
	u32 max_comptag_mem; /* max memory size (MB) for comptag */
#endif

	u32 ltc_streamid;

	struct nvgpu_cbc *cbc;
	struct nvgpu_ltc *ltc;
	/** @endcond */

	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	struct nvgpu_channel_worker {
		struct nvgpu_worker worker;

#ifdef CONFIG_NVGPU_CHANNEL_WDT
		u32 watchdog_interval;
		struct nvgpu_timeout timeout;
#endif
	} channel_worker;

	struct nvgpu_clk_arb_worker {
		struct nvgpu_worker worker;
	} clk_arb_worker;
	/** @endcond */

	struct {
		/** @cond DOXYGEN_SHOULD_SKIP_THIS */
		void (*open)(struct nvgpu_channel *ch);
		/** @endcond */
		/** Os specific callback called at channel closure. */
		void (*close)(struct nvgpu_channel *ch, bool force);
		/** @cond DOXYGEN_SHOULD_SKIP_THIS */
		void (*work_completion_signal)(struct nvgpu_channel *ch);
		void (*work_completion_cancel_sync)(struct nvgpu_channel *ch);
		bool (*os_fence_framework_inst_exists)(struct nvgpu_channel *ch);
		int (*init_os_fence_framework)(
			struct nvgpu_channel *ch, const char *fmt, ...);
		void (*signal_os_fence_framework)(struct nvgpu_channel *ch,
				struct nvgpu_fence_type *fence);
		void (*destroy_os_fence_framework)(struct nvgpu_channel *ch);
		int (*copy_user_gpfifo)(struct nvgpu_gpfifo_entry *dest,
				struct nvgpu_gpfifo_userdata userdata,
				u32 start, u32 length);
		/** @endcond */
		/** Os specific callback to allocate usermode buffers. */
		int (*alloc_usermode_buffers)(struct nvgpu_channel *c,
			struct nvgpu_setup_bind_args *args);
		/** Os specific callback to free usermode buffers. */
		void (*free_usermode_buffers)(struct nvgpu_channel *c);
	} os_channel;

	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	/* Used by Linux OS Layer */
	struct gk20a_scale_profile *scale_profile;
	unsigned long last_freq;
	/** @endcond */

#ifdef CONFIG_NVGPU_NON_FUSA
	u32 tpc_fs_mask_user;
	u32 fecs_feature_override_ecc_val;
#endif

	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	u32 tpc_pg_mask;
	bool can_tpc_powergate;
	u32 fbp_mask;
	bool can_fbp_fs;
	u32 gpc_mask;
	bool can_gpc_fs;

	u32 valid_tpc_mask[MAX_TPC_PG_CONFIGS];
	u32 valid_gpc_fbp_fs_mask[MAX_GPC_FBP_FS_CONFIGS];

	struct nvgpu_bios *bios;
	bool bios_is_init;

	struct nvgpu_clk_arb *clk_arb;

	struct nvgpu_mutex clk_arb_enable_lock;

	nvgpu_atomic_t clk_arb_global_nr;

	struct nvgpu_ce_app *ce_app;

	bool ltc_intr_en_illegal_compstat;
	/** @endcond */

	/** Are we currently running on a FUSA device configuration? */
	bool is_fusa_sku;

	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	/* PCI device identifier */
	u16 pci_vendor_id, pci_device_id;
	u16 pci_subsystem_vendor_id, pci_subsystem_device_id;
	u16 pci_class;
	u8 pci_revision;

	/**
	 * The per-device identifier. The iGPUs without a PDI will use
	 * the SoC PDI if one exists. Zero if neither exists.
	 */
	u64 per_device_identifier;

	/*
	 * PCI power management: i2c device index, port and address for
	 * INA3221.
	 */
	u32 ina3221_dcb_index;
	u32 ina3221_i2c_address;
	u32 ina3221_i2c_port;
	bool hardcode_sw_threshold;

	/* PCIe power states. */
	bool xve_l0s;
	bool xve_l1;

	/* Current warning temp in sfxp24.8 */
	s32 curr_warn_temp;

#if defined(CONFIG_PCI_MSI)
	/* Check if msi is enabled */
	bool msi_enabled;
#endif
#ifdef CONFIG_NVGPU_TRACK_MEM_USAGE
	struct nvgpu_mem_alloc_tracker *vmallocs;
	struct nvgpu_mem_alloc_tracker *kmallocs;
#endif

	/* memory training sequence and mclk switch scripts */
	u32 mem_config_idx;

	u64 dma_memory_used;
	/** @endcond */

#if defined(CONFIG_TEGRA_GK20A_NVHOST)
	/** Full syncpoint aperture base memory address. */
	u64		syncpt_unit_base;
	/** Full syncpoint aperture size. */
	size_t		syncpt_unit_size;
	/** Each syncpoint aperture size */
	u32		syncpt_size;
#endif
	/** Full syncpoint aperture. */
	struct nvgpu_mem syncpt_mem;

	/** @cond DOXYGEN_SHOULD_SKIP_THIS */
	struct nvgpu_list_node boardobj_head;
	struct nvgpu_list_node boardobjgrp_head;

	struct nvgpu_mem pdb_cache_errata_mem;
	/** @endcond */

#ifdef CONFIG_NVGPU_DGPU
	u16 dgpu_max_clk;
#endif

	/** Max SM diversity configuration count. */
	u32 max_sm_diversity_config_count;

	/**  Multi Instance GPU information. */
	struct nvgpu_mig mig;

	/** Pointer to struct storing CIC-MON's data */
	struct nvgpu_cic_mon *cic_mon;

	/** Pointer to struct storing CIC-RM's data */
	struct nvgpu_cic_rm *cic_rm;
#ifdef CONFIG_TEGRA_HV_MANAGER
	/** Cache to store IPA to PA translations. */
	struct nvgpu_ipa_pa_cache ipa_pa_cache;
#endif
};

/**
 * @brief Check if watchdog and context switch timeouts are enabled.
 *
 * @param g [in]	The GPU superstucture.
 *
 * @return timeouts enablement status
 * @retval True  always for safety or if these timeouts are actually enabled on
 *               other builds.
 * @retval False never for safety or if these timeouts are actually disabled on
 *               other builds.
 */
static inline bool nvgpu_is_timeouts_enabled(struct gk20a *g)
{
#ifdef CONFIG_NVGPU_DEBUGGER
	return nvgpu_atomic_read(&g->timeouts_disabled_refcount) == 0;
#else
	return true;
#endif
}

/** Minimum poll delay value in us */
#define POLL_DELAY_MIN_US	10U
/** Maximum poll delay value in us */
#define POLL_DELAY_MAX_US	200U

/**
 * @brief Get the global poll timeout value
 *
 * @param g [in]	The GPU superstucture.
 *
 * @return The value of the global poll timeout value in us.
 * @retval NVGPU_DEFAULT_POLL_TIMEOUT_MS for safety as timeout is always
 *         enabled.
 */
static inline u32 nvgpu_get_poll_timeout(struct gk20a *g)
{
	return nvgpu_is_timeouts_enabled(g) ?
		g->poll_timeout_default : U32_MAX;
}

/** IO Resource in the device tree for BAR0 */
#define GK20A_BAR0_IORESOURCE_MEM	0U
/** IO Resource in the device tree for BAR1 */
#define GK20A_BAR1_IORESOURCE_MEM	1U
/** IO Resource in the device tree for SIM mem */
#define GK20A_SIM_IORESOURCE_MEM	2U

#ifdef CONFIG_NVGPU_VPR
int gk20a_do_idle(void *_g);
int gk20a_do_unidle(void *_g);
#endif

#ifdef CONFIG_PM
int gk20a_do_idle(void *_g);
int gk20a_do_unidle(void *_g);
#endif

/**
 * Constructs unique and compact GPUID from nvgpu_gpu_characteristics
 * arch/impl fields.
 */
#define GK20A_GPUID(arch, impl) ((u32) ((arch) | (impl)))

/** gk20a HW version */
#define GK20A_GPUID_GK20A   0x000000EAU
/** gm20b HW version */
#define GK20A_GPUID_GM20B   0x0000012BU
/** gm20b.b HW version */
#define GK20A_GPUID_GM20B_B 0x0000012EU
/** gp10b HW version */
#define NVGPU_GPUID_GP10B   0x0000013BU
/** gv11b HW version */
#define NVGPU_GPUID_GV11B   0x0000015BU
/** gv100 HW version */
#define NVGPU_GPUID_GV100   0x00000140U
/** tu104 HW version */
#define NVGPU_GPUID_TU104   0x00000164U
/** ga100 HW Version */
#define NVGPU_GPUID_GA100   0x00000170U
/** ga10b HW version */
#define NVGPU_GPUID_GA10B   0x0000017BU

/**
 * @}
 */

#endif /* GK20A_H */
