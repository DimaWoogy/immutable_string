#include "catch2/catch.hpp"
#include "immutable_string/string.hpp"

#include <cstring>
#include <type_traits>

using namespace immutable_string;

static_assert(std::is_nothrow_copy_constructible<string>::value,
              "string shall be nothrow copy-constructible");
static_assert(std::is_nothrow_copy_assignable<string>::value,
              "string shall be nothrow copy-assignable");
static_assert(std::is_nothrow_move_constructible<string>::value,
              "string shall be nothrow move-constructible");
static_assert(std::is_nothrow_move_assignable<string>::value,
              "string shall be nothrow move-assignable");

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

SCENARIO("string is copyable without new allocations", "[string]") {
  GIVEN("some test string") {
    string test_str{"test"};

    WHEN("new string is copy-constructed") {
      string new_str{test_str};

      THEN("they point to the same memory") {
        REQUIRE(test_str.data() == new_str.data());
      }
      THEN("they have the same size") {
        REQUIRE(test_str.size() == new_str.size());
      }
    }
    WHEN("new string is created and test string is assigned to it") {
      string new_str;
      new_str = test_str;

      THEN("they point to the same memory") {
        REQUIRE(test_str.data() == new_str.data());
      }
      THEN("they have the same size") {
        REQUIRE(test_str.size() == new_str.size());
      }
    }
  }
}

SCENARIO("string is movable", "[string]") {
  GIVEN("some test string") {
    string test_str{"test"};

    WHEN("new string is move-constructed") {
      string new_str{std::move(test_str)};

      THEN("new string has test string") {
        REQUIRE(std::strcmp(new_str.data(), "test") == 0);
      }
      THEN("test string is unusable and point to nullptr") {
        REQUIRE(test_str.data() == nullptr);
      }
    }
    WHEN("new string is creeated and test string is move-assigned to it") {
      string new_str;
      new_str = std::move(test_str);

      THEN("new string has test string") {
        REQUIRE(std::strcmp(new_str.data(), "test") == 0);
      }
      THEN("test string is unusable and point to nullptr") {
        REQUIRE(test_str.data() == nullptr);
      }
    }
  }
}

SCENARIO("string's element access", "[string]") {
  GIVEN("some test string") {
    string test_str{"abcd"};

    WHEN("accessed pos < size()") {
      THEN("valid character is returned") {
        REQUIRE(test_str.front() == 'a');
        REQUIRE(test_str.at(1) == 'b');
        REQUIRE(test_str[2] == 'c');
        REQUIRE(test_str.back() == 'd');
      }
    }
    WHEN("accessed pos == size()") {
      THEN("at throws") {
        REQUIRE_THROWS_AS(test_str.at(4), std::out_of_range);
      }
      THEN("operator[] returns 0") {
        REQUIRE(test_str[4] == 0);
      }
    }
    WHEN("accessed pos > size()") {
      THEN("at throws") {
        REQUIRE_THROWS_AS(test_str.at(5), std::out_of_range);
        REQUIRE_THROWS_AS(test_str.at(100), std::out_of_range);
      }
    }
  }
}
