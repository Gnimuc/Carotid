#ifndef CAROTID_UTILITY_H
#define CAROTID_UTILITY_H

#include <Eigen/Dense>
#include <fstream>

namespace carotid {

using Path = std::filesystem::path;

template <typename T>
using Mat = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;

template <typename T>
[[nodiscard]] Mat<T> loadBinaryIntoMatrix(const Path &filename, int rows, int cols) {
  std::ifstream in(filename, std::ios::binary);
  if (!in.is_open()) {
    throw std::runtime_error("Cannot open file: " + filename.string());
  }

  Mat<T> mat(rows, cols);

  in.read(reinterpret_cast<char *>(mat.data()), rows * cols * sizeof(T));
  in.close();

  return mat;
}

} // namespace carotid

#endif // CAROTID_UTILITY_H
