/*
 * Copyright (c) 2022, NVIDIA CORPORATION.  All rights reserved.
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

#ifndef NVGPU_GR_CTX_MAPPINGS_H
#define NVGPU_GR_CTX_MAPPINGS_H

struct gk20a;
struct nvgpu_tsg;
struct vm_gk20a;
struct nvgpu_gr_ctx;
struct nvgpu_gr_ctx_mappings;
struct nvgpu_gr_global_ctx_buffer_desc;

/**
 * @brief Create GR ctx buffers mappings for a TSG.
 *
 * @param g [in]		Pointer to GPU driver struct.
 * @param tsg [in]		Pointer to TSG struct.
 * @param vm [in]		Pointer to vm struct.
 *
 * This function allocates the mappings struct for TSG corresponding to
 * given vm.
 *
 * @return mappings struct in case of success, null in case of failure.
 */
struct nvgpu_gr_ctx_mappings *nvgpu_gr_ctx_mappings_create(struct gk20a *g,
				struct nvgpu_tsg *tsg, struct vm_gk20a *vm);

/**
 * @brief Free the GR ctx buffers mappings.
 *
 * @param g [in]		Pointer to GPU driver struct.
 * @param mappings [in]		Pointer to GR ctx buffers mappings struct.
 *
 * This function frees the mappings struct.
 */
void nvgpu_gr_ctx_mappings_free(struct gk20a *g,
				struct nvgpu_gr_ctx_mappings *mappings);

/**
 * @brief Map GR context buffer and store in mappings struct.
 *
 * @param g [in]		Pointer to GPU driver struct.
 * @param ctx [in]		Pointer to GR context struct.
 * @param index [in]		index of the buffer.
 * @param mappings [in]		Pointer to GR context buffer mappings struct.
 *
 * This function will map the GR context buffer at #index in #mappings->vm
 * and stores the mapped address.
 *
 * @return 0 in case of success, < 0 in case of failure.
 */
int nvgpu_gr_ctx_mappings_map_ctx_buffer(struct gk20a *g,
	struct nvgpu_gr_ctx *ctx, u32 index,
	struct nvgpu_gr_ctx_mappings *mappings);

/**
 * @brief Map GR context preemption buffers and store in mappings struct.
 *
 * @param g [in]		Pointer to GPU driver struct.
 * @param ctx [in]		Pointer to GR context struct.
 * @param mappings [in]		Pointer to GR context buffer mappings struct.
 *
 * This function will map the GR context preemption buffers in #mappings->vm
 * and stores the mapped address.
 *
 * @return 0 in case of success, < 0 in case of failure.
 */
int nvgpu_gr_ctx_mappings_map_ctx_preemption_buffers(struct gk20a *g,
	struct nvgpu_gr_ctx *ctx,
	struct nvgpu_gr_ctx_mappings *mappings);

/**
 * @brief Map GR and global context buffers and store in mappings struct.
 *
 * @param g [in]			Pointer to GPU driver struct.
 * @param gr_ctx [in]			Pointer to GR context struct.
 * @param global_ctx_buffer [in]	Pointer global context buffer desc.
 * @param mappings [in]			Pointer to GR context buffer
 *					mappings struct.
 * @param vpr [in]			Indicates if VPR buffer copy is to be
 *					mapped.
 *
 * This function will map the GR and global context buffers in #mappings->vm
 * and stores the mapped address.
 *
 * @return 0 in case of success, < 0 in case of failure.
 */
int nvgpu_gr_ctx_mappings_map_gr_ctx_buffers(struct gk20a *g,
	struct nvgpu_gr_ctx *gr_ctx,
	struct nvgpu_gr_global_ctx_buffer_desc *global_ctx_buffer,
	struct nvgpu_gr_ctx_mappings *mappings,
	bool vpr);

/**
 * @brief Unmap GR and global context buffers and store in mappings struct.
 *
 * @param g [in]			Pointer to GPU driver struct.
 * @param gr_ctx [in]			Pointer to GR context struct.
 * @param global_ctx_buffer [in]	Pointer global context buffer desc.
 * @param mappings [in]			Pointer to GR context buffer
 *					mappings struct.
 *
 * This function will unmap the GR and global context buffers in #mappings->vm.
 */
void nvgpu_gr_ctx_unmap_buffers(struct gk20a *g,
	struct nvgpu_gr_ctx *gr_ctx,
	struct nvgpu_gr_global_ctx_buffer_desc *global_ctx_buffer,
	struct nvgpu_gr_ctx_mappings *mappings);

/**
 * @brief Get global context buffer gpu virtual address.
 *
 * @param mappings [in]		Pointer to GR context buffer
 *				mappings struct.
 * @param index [in]		index of the buffer.
 *
 * This function will get the gpu virtual address of the global context buffer
 * in #mappings.
 *
 * @return gpu virtual address of global context buffer.
 */
u64 nvgpu_gr_ctx_mappings_get_global_ctx_va(struct nvgpu_gr_ctx_mappings *mappings,
	u32 index);

/**
 * @brief Get GR context buffer gpu virtual address.
 *
 * @param mappings [in]		Pointer to GR context buffer
 *				mappings struct.
 * @param index [in]		index of the buffer.
 *
 * This function will get the gpu virtual address of the GR context buffer
 * in #mappings.
 *
 * @return gpu virtual address of GR context buffer.
 */
u64 nvgpu_gr_ctx_mappings_get_ctx_va(struct nvgpu_gr_ctx_mappings *mappings,
	u32 index);

#endif /* NVGPU_GR_CTX_MAPPINGS_H */
