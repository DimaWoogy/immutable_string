#include "catch2/catch.hpp"
#include "immutable_string/string.hpp"

TEST_CASE("string can be created with default constructor", "[string]") {
  immutable_string::string empty_str;
}
