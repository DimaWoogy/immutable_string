#include "filled_memory_allocator.hpp"

#include "catch2/catch.hpp"
#include "immutable_string/string.hpp"

#include <cstring>

using namespace immutable_string;

#define REQUIRE_EMPTY(STR)    \
  REQUIRE(STR.size() == 0);   \
  REQUIRE(STR.length() == 0); \
  REQUIRE(STR.empty());       \
  REQUIRE(std::strcmp(STR.c_str(), "") == 0);

SCENARIO("empty string construction", "[string]") {
  GIVEN("default-constructed string") {
    string str;
    REQUIRE_EMPTY(str);
  }
  GIVEN("string constructed from empty c_str") {
    string str{""};
    REQUIRE_EMPTY(str);
  }
  GIVEN("string constructed from non-empty c_str with count = 0") {
    string str{"test", 0};
    REQUIRE_EMPTY(str);
  }
}
