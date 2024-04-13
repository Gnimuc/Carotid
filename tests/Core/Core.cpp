#include "Core.h"

#include "carotid/IdentityGenerator.h"

#include <catch2/catch_test_macros.hpp>

using namespace carotid;

TEST_CASE("File loading", "[Utility]") { // NOLINT(*-use-anonymous-namespace)
  const carotid::Path projectSrcDir(UNITTEST_PROJECT_DIR);
  const auto sanityBin = projectSrcDir / "tests" / "Core" / "f32.bin";

  SECTION("Data loading sanity check | Matrix") {
    auto result = loadBinaryIntoMatrix<float>(sanityBin, 6, 3);
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
    REQUIRE(mat(2, 0) == 7.0f);
    REQUIRE(mat(2, 1) == 8.0f);
    REQUIRE(mat(2, 2) == 9.0f);
    REQUIRE(mat(3, 0) == 10.0f);
    REQUIRE(mat(3, 1) == 11.0f);
    REQUIRE(mat(3, 2) == 12.0f);
    REQUIRE(mat(4, 0) == 13.0f);
    REQUIRE(mat(4, 1) == 14.0f);
    REQUIRE(mat(4, 2) == 15.0f);
    REQUIRE(mat(5, 0) == 16.0f);
    REQUIRE(mat(5, 1) == 17.0f);
    REQUIRE(mat(5, 2) == 18.0f);
  }

  SECTION("Data loading failure check | Matrix") {
    auto result = loadBinaryIntoMatrix<float>("", 2, 3);
    CAPTURE(result.error().what());
    REQUIRE_FALSE(result.has_value());

    result = loadBinaryIntoMatrix<float>(sanityBin, 7, 3);
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
    REQUIRE(vec(2) == 7.0f);
    REQUIRE(vec(3) == 10.0f);
    REQUIRE(vec(4) == 13.0f);
    REQUIRE(vec(5) == 16.0f);
  }

  SECTION("Data loading failure check | Vector") {
    auto result = loadBinaryIntoVector<float>("", 6);
    CAPTURE(result.error().what());
    REQUIRE_FALSE(result.has_value());

    result = loadBinaryIntoVector<float>(sanityBin, 19);
    CAPTURE(result.error().what());
    REQUIRE_FALSE(result.has_value());
  }
}

TEST_CASE("IdentityGenerator", "[IdentityGenerator]") { // NOLINT(*-use-anonymous-namespace)
  const carotid::Path projectSrcDir(UNITTEST_PROJECT_DIR);
  const auto sanityBin = projectSrcDir / "tests" / "Core" / "f32.bin";

  auto opts = IdOptions(3);
  opts.vertexCount = 2;
  IdentityGenerator idGen(opts);
  idGen.loadModelFromBinary(sanityBin, sanityBin, sanityBin);

  SECTION("Validate model") { REQUIRE(idGen.validateModel()); }

  SECTION("Base model generation") {
    const auto baseModel = idGen.generateBaseModel();
    Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision, 0, ", ", ";\n", "", "", "[", "]");
    INFO("Base model:\n" << baseModel.format(OctaveFmt));

    REQUIRE(baseModel(0) == 31.0f);
    REQUIRE(baseModel(1) == 70.0f);
    REQUIRE(baseModel(2) == 109.0f);
    REQUIRE(baseModel(3) == 148.0f);
    REQUIRE(baseModel(4) == 187.0f);
    REQUIRE(baseModel(5) == 226.0f);
  }

  SECTION("Generate model with eigenvalues") {
    auto eigenvals = Vec<float>(idGen.getNumCols());
    eigenvals << 1.0f, 2.0f, 3.0f;
    const auto model = idGen.generateModel(eigenvals);
    Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision, 0, ", ", ";\n", "", "", "[", "]");
    INFO("Model:\n" << model.format(OctaveFmt));

    REQUIRE(model(0) == 15.0f);
    REQUIRE(model(1) == 36.0f);
    REQUIRE(model(2) == 57.0f);
    REQUIRE(model(3) == 78.0f);
    REQUIRE(model(4) == 99.0f);
    REQUIRE(model(5) == 120.0f);
  }
}