/// \file IdentityGenerator.cpp
/// \brief IdentityGenerator Implmentation
///
#include "carotid/IdentityGenerator.h"
#include "carotid/Utility.h"
#include "spdlog/spdlog.h"

using namespace carotid;

void IdentityGenerator::loadModelFromBinary(const Path &avgModelPath,
                                            const Path &eigenvecsPath,
                                            const Path &eigenvalsPath) {
  const auto [nRows, nCols] = getSize();

  if (const auto avgResult = loadBinaryIntoVector<float>(avgModelPath, nRows)) {
    avgModel = std::move(avgResult.value());
  } else {
    spdlog::error(avgResult.error().what());
  }

  if (const auto eigenvecsResult =
          loadBinaryIntoMatrix<float>(eigenvecsPath, nRows, nCols)) {
    eigenvecs = std::move(eigenvecsResult.value());
  } else {
    spdlog::error(eigenvecsResult.error().what());
  }

  if (const auto eigenvalsResult = loadBinaryIntoVector<float>(eigenvalsPath, nCols)) {
    eigenvals = std::move(eigenvalsResult.value());
  } else {
    spdlog::error(eigenvalsResult.error().what());
  }

  cur_model = avgModel;
  cur_params = eigenvals;
}

bool IdentityGenerator::validateModel() const {
  return avgModel.size() == getNumRows() && eigenvecs.rows() == getNumRows() &&
         eigenvecs.cols() == getNumCols() && eigenvals.size() == getNumCols() &&
         cur_model.size() == getNumRows() && cur_params.size() == getNumCols();
}

Vec<float> IdentityGenerator::generateBaseModel() const {
  return avgModel + eigenvecs * eigenvals;
}

Vec<float> IdentityGenerator::generateModel(const Vec<float> &eigenvals) const {
  return avgModel + eigenvecs * eigenvals;
}
