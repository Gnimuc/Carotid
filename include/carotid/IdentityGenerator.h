#ifndef CAROTID_IDENTITYGENERATOR_H
#define CAROTID_IDENTITYGENERATOR_H

#include "Utility.h"

namespace carotid {

constexpr uint32_t CAROTID_VERTEX_COUNT_LVL1 = 12466;
constexpr uint32_t CAROTID_VERTEX_COUNT_LVL2 = 49751;
constexpr uint32_t CAROTID_VERTEX_COUNT_LVL3 = 198781;

/// IdOptions - Options for the IdentityGenerator class
class IdOptions{

public:
  /// Number of points in the model
  uint32_t vertexCount;

  /// Number of PCA dimensions to use
  uint32_t dim;

public:
  explicit IdOptions(const uint32_t dim) : vertexCount(CAROTID_VERTEX_COUNT_LVL2), dim(dim) {}
};

/// \brief IdentityGenerator - A class for generating shape blendshapes
/// \details This class is used to generate shape blendshapes of a 3DMM model
class IdentityGenerator {

public:
  IdOptions opts;

public:
  [[nodiscard]] explicit IdentityGenerator(const IdOptions opts) : opts(opts) {}

  /// \brief Get the number of rows in the model matrix
  /// \return The number of rows in the model matrix
  inline uint32_t getNumRows() const { return opts.vertexCount * 3; }

  /// \brief Get the number of columns in the model matrix
  /// \return The number of columns in the model matrix
  inline uint32_t getNumCols() const { return opts.dim; }

  /// \brief Get the size of the model matrix
  /// \return The size of the model matrix
  inline std::pair<uint32_t, uint32_t> getSize() const { return {getNumRows(), getNumCols()}; }

  /// \brief Load the model from binary files
  /// \param avgModelPath The path to the average model binary file
  /// \param eigenvecsPath The path to the eigen vectors binary file
  /// \param eigenvalsPath The path to the eigen values binary file
  void loadModelFromBinary(const Path &avgModelPath, const Path &eigenvecsPath, const Path &eigenvalsPath);

private:
  Mat<float> avgModel;
  Mat<float> eigenvecs;
  Vec<float> eigenvals;

};

} // namespace carotid



#endif // CAROTID_IDENTITYGENERATOR_H
