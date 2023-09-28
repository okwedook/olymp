cmake_policy(SET CMP0048 NEW)
project(Olymp)

cmake_minimum_required(VERSION 3.22)

if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 17)
endif()
# set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-O3 -s)
# add_compile_options(-fsanitize=undefined,address -fno-sanitize-recover=all)

enable_testing()
add_subdirectory(../googletest ./gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include(GoogleTest)

include_directories(.)
include_directories(../..)

add_executable(FenwickTreePerformance fenwick_tree_performance.cpp)
target_link_libraries(FenwickTreePerformance gtest gtest_main)
gtest_discover_tests(FenwickTreePerformance EXTRA_ARGS --gtest_repeat=5)
