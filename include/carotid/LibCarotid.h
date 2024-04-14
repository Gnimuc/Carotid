#ifndef LIBCAROTID_H
#define LIBCAROTID_H

#include "carotid/Platform.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *carotid_context;

typedef enum { carotid_success = 0, carotid_error = 1 } carotid_err;

CAROTID_LINKAGE bool carotid_sanity_check(void);

CAROTID_LINKAGE carotid_context carotid_context_create(uint32_t n_params, carotid_err *err);

CAROTID_LINKAGE void carotid_context_dispose(carotid_context ctx);

CAROTID_LINKAGE void carotid_load_model(carotid_context ctx, const char *model_dir,
                                        carotid_err *err);

CAROTID_LINKAGE uint32_t carotid_get_vertex_count(carotid_context ctx);

CAROTID_LINKAGE uint32_t carotid_get_param_count(carotid_context ctx);

CAROTID_LINKAGE void carotid_update_model(carotid_context ctx, const float *params,
                                          uint32_t len);

CAROTID_LINKAGE void carotid_get_model(carotid_context ctx, float *model, uint32_t len);

CAROTID_LINKAGE void carotid_get_basemodel(carotid_context ctx, float *model, uint32_t len);

#ifdef __cplusplus
}
#endif
#endif
