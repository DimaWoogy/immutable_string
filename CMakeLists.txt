project(immutable_string)

cmake_minimum_required(VERSION 3.2)

if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(${immutable_string_SOURCE_DIR}/include)

add_subdirectory(unittests)

enable_testing()
add_test(unittests unittests/unittests)

