#include "carotid/LibCarotid.h"
#include "carotid/IdentityGenerator.h"

bool carotid_sanity_check(void) { return true; }

carotid_context carotid_context_create(const uint32_t n_params, carotid_err *err) {
  *err = carotid_success;
  auto ptr = std::make_unique<carotid::IdentityGenerator>(carotid::IdOptions(n_params));
  if (!ptr)
    *err = carotid_error;

  return ptr.release();
}

void carotid_context_dispose(carotid_context ctx) {
  delete static_cast<carotid::IdentityGenerator *>(ctx);
}

void carotid_load_model(carotid_context ctx, const char *model_dir, carotid_err *err) {
  const auto avg = carotid::Path(model_dir) / "avg.bin";
  const auto vecs = carotid::Path(model_dir) / "vecs.bin";
  const auto vals = carotid::Path(model_dir) / "vals.bin";
  auto *idgen = static_cast<carotid::IdentityGenerator *>(ctx);
  idgen->loadModelFromBinary(avg, vecs, vals);
  if (!idgen->validateModel())
    *err = carotid_error;
}

uint32_t carotid_get_vertex_count(carotid_context ctx) {
  return static_cast<carotid::IdentityGenerator *>(ctx)->opts.vertexCount;
}

uint32_t carotid_get_param_count(carotid_context ctx) {
  return static_cast<carotid::IdentityGenerator *>(ctx)->opts.dim;
}

void carotid_update_model(carotid_context ctx, const float *params, uint32_t len) {
  auto *idgen = static_cast<carotid::IdentityGenerator *>(ctx);
  for (auto &x : idgen->cur_params) {
    x = *params++;
    if (--len == 0)
      break;
  }
  idgen->cur_model = idgen->generateModel(idgen->cur_params);
}

void carotid_get_model(carotid_context ctx, float *model, uint32_t len) {
  for (const auto &x : static_cast<carotid::IdentityGenerator *>(ctx)->cur_model) {
    *model++ = x;
    if (--len == 0)
      break;
  }
}

void carotid_get_basemodel(carotid_context ctx, float *model, uint32_t len) {
  for (const auto &x :
       static_cast<carotid::IdentityGenerator *>(ctx)->generateBaseModel()) {
    *model++ = x;
    if (--len == 0)
      break;
  }
}