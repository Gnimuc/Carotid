#ifndef CAROTID_UTILITY_H
#define CAROTID_UTILITY_H

#include <Eigen/Dense>
#include <expected>
#include <filesystem>
#include <fstream>

namespace carotid {

using Path = std::filesystem::path;

template <typename T>
using Mat = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;

template <typename T>
using Vec = Eigen::Matrix<T, Eigen::Dynamic, 1>;

template <typename T>
[[nodiscard]] std::expected<Mat<T>, std::ios_base::failure>
loadBinaryIntoMatrix(const Path &filename, int rows, int cols) {
  std::ifstream in(filename, std::ios::binary);
  if (!in.is_open()) {
    return std::unexpected(
        std::ios_base::failure("File not found or could not be opened.",
                               std::make_error_code(std::errc::io_error)));
  }

  Mat<T> mat(rows, cols);

  in.read(reinterpret_cast<char *>(mat.data()), rows * cols * sizeof(T));
  if (!in) {
    return std::unexpected(std::ios_base::failure(
        "Failed to read the entire file.", std::make_error_code(std::errc::io_error)));
  }

  return mat;
}

template <typename T>
[[nodiscard]] std::expected<Vec<T>, std::ios_base::failure>
loadBinaryIntoVector(const Path &filename, int n) {
  std::ifstream in(filename, std::ios::binary);
  if (!in.is_open()) {
    return std::unexpected(
        std::ios_base::failure("File not found or could not be opened.",
                               std::make_error_code(std::errc::io_error)));
  }

  Vec<T> vec(n);

  in.read(reinterpret_cast<char *>(vec.data()), n * sizeof(T));
  if (!in) {
    return std::unexpected(std::ios_base::failure(
        "Failed to read the entire file.", std::make_error_code(std::errc::io_error)));
  }

  return vec;
}

} // namespace carotid

#endif // CAROTID_UTILITY_H
