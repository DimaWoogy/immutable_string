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
  GIVEN("string constructed from empty cstr") {
    string str{""};
    REQUIRE_EMPTY(str);
  }
  GIVEN("string constructed from non-empty cstr with count = 0") {
    string str{"test", 0};
    REQUIRE_EMPTY(str);
  }
  GIVEN("string constructed with same character repeated 0 times") {
    string str{0, '1'};
    REQUIRE_EMPTY(str);
  }
}

SCENARIO("non-empty string construction", "[string]") {
  GIVEN("string constructed from test cstr") {
    string str{"test"};

    REQUIRE(str.size() == 4);
    REQUIRE(std::strcmp(str.c_str(), "test") == 0);
  }
  GIVEN("string constructed from test cstr with count = 2") {
    string str{"test", 2};

    REQUIRE(str.size() == 2);
    REQUIRE(std::strcmp(str.c_str(), "te") == 0);
  }
  GIVEN("string constructed with same character repeated 5 times") {
    string str{5, '1'};

    REQUIRE(str.size() == 5);
    REQUIRE(std::strcmp(str.c_str(), "11111") == 0);
  }
}
