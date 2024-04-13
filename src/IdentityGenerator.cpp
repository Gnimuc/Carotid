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
  auto [nRows, nCols] = getSize();

  if (const auto avgResult = loadBinaryIntoMatrix<float>(avgModelPath, nRows, nCols)) {
    avgModel = std::move(avgResult.value());
  } else {
    spdlog::error(avgResult.error().what());
  }

  if (const auto eigenvecsResult =
          loadBinaryIntoMatrix<float>(eigenvecsPath, nCols, nCols)) {
    eigenvecs = std::move(eigenvecsResult.value());
  } else {
    spdlog::error(eigenvecsResult.error().what());
  }

  if (const auto eigenvalsResult = loadBinaryIntoVector<float>(eigenvalsPath, nCols)) {
    eigenvals = std::move(eigenvalsResult.value());
  } else {
    spdlog::error(eigenvalsResult.error().what());
  }
}