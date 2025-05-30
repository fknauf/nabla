cmake_minimum_required(VERSION 3.22)

project(nabla)

file(READ $ENV{HOME}/.vcpkg/vcpkg.path.txt VCPKG_DIR)
include(${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake)

find_package(Armadillo CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -Werror)
include_directories(.)
enable_testing()

add_executable(example example.cc)
target_link_libraries(example PRIVATE Eigen3::Eigen)

add_executable(example-armadillo example.cc)
target_link_libraries(example-armadillo PRIVATE armadillo)
target_compile_definitions(example-armadillo PRIVATE NABLA_BACKEND_ARMADILLO=1)

set(test_sources
    tests/group_chain.cc
    tests/group_conditional.cc
    tests/group_constant.cc
    tests/group_division.cc
    tests/group_explog.cc
    tests/group_exponential.cc
    tests/group_gradient.cc
    tests/group_hessian.cc
    tests/group_hyperbolic.cc
    tests/group_hypot.cc
    tests/group_logarithm.cc
    tests/group_negation.cc
    tests/group_polynomial.cc
    tests/group_power.cc
    tests/group_product.cc
    tests/group_sum.cc
    tests/group_trigonometry.cc
    tests/group_unary_functions.cc
    tests/group_variable.cc
)

add_executable(test-nabla ${test_sources})
target_link_libraries(test-nabla PRIVATE Eigen3::Eigen GTest::gtest GTest::gtest_main)

add_executable(test-nabla-armadillo ${test_sources})
target_link_libraries(test-nabla-armadillo PRIVATE armadillo GTest::gtest GTest::gtest_main)
target_compile_definitions(test-nabla-armadillo PRIVATE NABLA_BACKEND_ARMADILLO=1)

add_test(NAME test-nabla COMMAND test-nabla)
add_test(NAME test-nabla-armadillo COMMAND test-nabla-armadillo)
