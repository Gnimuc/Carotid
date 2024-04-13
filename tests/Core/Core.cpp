#include "Core.h"

#include "carotid/IdentityGenerator.h"

#include <catch2/catch_test_macros.hpp>

using namespace carotid;

TEST_CASE("Core", "[Utility]") {
  const carotid::Path projectSrcDir(UNITTEST_PROJECT_DIR);
  const auto sanityBin = projectSrcDir / "tests" / "Core" / "f32.bin";

  SECTION("Data loading sanity check | Matrix") {
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

  SECTION("Data loading failure check | Matrix") {
    auto result = loadBinaryIntoMatrix<float>("", 2, 4);
    CAPTURE(result.error().what());
    REQUIRE_FALSE(result.has_value());

    result = loadBinaryIntoMatrix<float>(sanityBin, 2, 4);
    CAPTURE(result.error().what());
    REQUIRE_FALSE(result.has_value());
  }

  SECTION("Data loading sanity check | Vector") {
    auto result = loadBinaryIntoVector<float>(sanityBin, 6);
    REQUIRE(result.has_value());

    auto vec = result.value();
    Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision, 0, ", ", ";\n", "", "", "[", "]");
    INFO("Vector:\n" << vec.format(OctaveFmt));

    REQUIRE(vec(0) == 1.0f);
    REQUIRE(vec(1) == 4.0f);
    REQUIRE(vec(2) == 2.0f);
    REQUIRE(vec(3) == 5.0f);
    REQUIRE(vec(4) == 3.0f);
    REQUIRE(vec(5) == 6.0f);
  }

  SECTION("Data loading failure check | Vector") {
    auto result = loadBinaryIntoVector<float>("", 6);
    CAPTURE(result.error().what());
    REQUIRE_FALSE(result.has_value());

    result = loadBinaryIntoVector<float>(sanityBin, 7);
    CAPTURE(result.error().what());
    REQUIRE_FALSE(result.has_value());
  }
}

TEST_CASE("Core", "[IdentityGenerator]") {
  const carotid::Path projectSrcDir(UNITTEST_PROJECT_DIR);
  const auto sanityBin = projectSrcDir / "tests" / "Core" / "f32.bin";

  const auto opts = IdOptions(1);
  IdentityGenerator idGen(opts);
  idGen.loadModelFromBinary(sanityBin, sanityBin, sanityBin);

}