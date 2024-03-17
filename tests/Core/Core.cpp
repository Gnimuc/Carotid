#include "Core.h"
#include <catch2/catch_test_macros.hpp>

using namespace carotid;

TEST_CASE("Core", "[Utility]") {
  carotid::Path projectSrcDir(UNITTEST_PROJECT_DIR);
  auto sanityBin = projectSrcDir / "tests" / "Core" / "f32.bin";

  SECTION("Data loading sanity check") {
    auto result = loadBinaryIntoMatrix<float>(sanityBin, 2, 3);
    REQUIRE(result.has_value());

    auto mat = result.value();
    Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision, 0, ", ", ";\n", "", "", "[", "]");
    INFO("Matrix:\n" << mat.format(OctaveFmt));

    REQUIRE(mat(0, 0) == 1.0f);
    REQUIRE(mat(0, 1) == 2.0f);
    REQUIRE(mat(0, 2) == 3.0f);
    REQUIRE(mat(1, 0) == 4.0f);
    REQUIRE(mat(1, 1) == 5.0f);
    REQUIRE(mat(1, 2) == 6.0f);
  }

  SECTION("Data loading failure check") {
    auto result = loadBinaryIntoMatrix<float>("", 2, 4);
    CAPTURE(result.error().what());
    REQUIRE_FALSE(result.has_value());

    result = loadBinaryIntoMatrix<float>(sanityBin, 2, 4);
    CAPTURE(result.error().what());
    REQUIRE_FALSE(result.has_value());
  }
}