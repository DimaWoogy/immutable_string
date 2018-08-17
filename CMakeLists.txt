project(immutable_string)

cmake_minimum_required(VERSION 3.2)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})

if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(${immutable_string_SOURCE_DIR}/include)

add_subdirectory(unittests)

enable_testing()
add_test(unittests unittests/unittests)

