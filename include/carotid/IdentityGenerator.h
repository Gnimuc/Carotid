#ifndef CAROTID_IDENTITYGENERATOR_H
#define CAROTID_IDENTITYGENERATOR_H

#include "Utility.h"

namespace carotid {

constexpr uint32_t CAROTID_SPATIAL_DIMENSIONS = 3;

constexpr uint32_t CAROTID_VERTEX_COUNT_LVL1 = 12466;
constexpr uint32_t CAROTID_VERTEX_COUNT_LVL2 = 49751;
constexpr uint32_t CAROTID_VERTEX_COUNT_LVL3 = 198781;

/// IdOptions - Options for the IdentityGenerator class
class IdOptions {

public:
  /// Number of points in the model
  uint32_t vertexCount;

  /// Number of PCA dimensions to use
  uint32_t dim;

public:
  explicit IdOptions(const uint32_t dim)
      : vertexCount(CAROTID_VERTEX_COUNT_LVL2), dim(dim) {}
};

/// \brief IdentityGenerator - A class for generating shape blendshapes
/// \details This class is used to generate shape blendshapes of a 3DMM model
class IdentityGenerator {

public:
  IdOptions opts;

public:
  [[nodiscard]] explicit IdentityGenerator(const IdOptions opts) : opts(opts) {}

  /// \brief Get the number of rows in the egienvector matrix
  /// \return The number of rows in the egienvector matrix
  inline uint32_t getNumRows() const {
    return CAROTID_SPATIAL_DIMENSIONS * opts.vertexCount;
  }

  /// \brief Get the number of columns in the egienvector matrix
  /// \return The number of columns in the egienvector matrix
  inline uint32_t getNumCols() const { return opts.dim; }

  /// \brief Get the size of the eigenvector matrix
  /// \return The size of the eigenvector matrix
  inline std::pair<uint32_t, uint32_t> getSize() const {
    return {getNumRows(), getNumCols()};
  }

  /// \brief Load the model from binary files
  /// \param avgModelPath The path to the average model binary file
  /// \param eigenvecsPath The path to the eigen vectors binary file
  /// \param eigenvalsPath The path to the eigen values binary file
  void loadModelFromBinary(const Path &avgModelPath, const Path &eigenvecsPath,
                           const Path &eigenvalsPath);

  /// \brief Validate the model
  /// \return True if the model is valid, false otherwise
  [[nodiscard]] bool validateModel() const;

  /// \brief Generate the base model
  /// \return The base model
  [[nodiscard]] Vec<float> generateBaseModel() const;

  /// \brief Generate the model with the given eigenvalues
  /// \param eigenvals The eigenvalues to use
  /// \return The model with the given eigenvalues
  [[nodiscard]] Vec<float> generateModel(const Vec<float> &eigenvals) const;

private:
  Vec<float> avgModel;
  Mat<float> eigenvecs;
  Vec<float> eigenvals;
};

} // namespace carotid

#endif // CAROTID_IDENTITYGENERATOR_H
