cmake_policy(SET CMP0048 NEW)
project(Olymp)

cmake_minimum_required(VERSION 3.22)

if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 17)
endif()
# set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion)
# add_compile_options(-fsanitize=undefined,address -fno-sanitize-recover=all)

enable_testing()
add_subdirectory(../googletest ./gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include(GoogleTest)

include_directories(.)
include_directories(../..)

add_executable(CountPrimesTest count_primes_test.cpp)
add_executable(FenwickTreeTest fenwick_tree_test.cpp)
add_executable(GeneralTreapTest general_treap_test.cpp)
add_executable(GeneratePrimesTest generate_primes_test.cpp)

target_link_libraries(CountPrimesTest gtest gtest_main)
target_link_libraries(FenwickTreeTest gtest gtest_main)
target_link_libraries(GeneralTreapTest gtest gtest_main)
target_link_libraries(GeneratePrimesTest gtest gtest_main)

gtest_discover_tests(CountPrimesTest)
gtest_discover_tests(FenwickTreeTest)
gtest_discover_tests(GeneralTreapTest)
gtest_discover_tests(GeneratePrimesTest)
