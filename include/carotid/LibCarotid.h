#ifndef LIBCNVII_H
#define LIBCNVII_H

#include "cnvii/Platform.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *carotid_context;

typedef enum { carotid_success = 0, carotid_error = 1 } carotid_err;

CAROTID_LINKAGE bool carotid_sanity_check(void);

#ifdef __cplusplus
}
#endif
#endif
