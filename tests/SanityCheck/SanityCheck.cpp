#include "SanityCheck.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Sanity Check", "[trivial]") { REQUIRE(carotid_sanity_check() == true); }