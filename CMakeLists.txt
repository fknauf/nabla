cmake_minimum_required(VERSION 3.22)

project(nabla)

find_package(Armadillo CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    add_definitions(-D_USE_MATH_DEFINES)
    add_compile_options(-Wall)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

include_directories(.)
enable_testing()

add_executable(example example.cpp)
target_link_libraries(example PRIVATE Eigen3::Eigen)

add_executable(example-armadillo example.cpp)
target_link_libraries(example-armadillo PRIVATE armadillo)
target_compile_definitions(example-armadillo PRIVATE NABLA_BACKEND_ARMADILLO=1)

set(test_sources
    tests/group_chain.cpp
    tests/group_conditional.cpp
    tests/group_constant.cpp
    tests/group_division.cpp
    tests/group_explog.cpp
    tests/group_exponential.cpp
    tests/group_gradient.cpp
    tests/group_hessian.cpp
    tests/group_hyperbolic.cpp
    tests/group_hypot.cpp
    tests/group_logarithm.cpp
    tests/group_negation.cpp
    tests/group_polynomial.cpp
    tests/group_power.cpp
    tests/group_product.cpp
    tests/group_sum.cpp
    tests/group_trigonometry.cpp
    tests/group_unary_functions.cpp
    tests/group_variable.cpp
)

add_executable(test-nabla ${test_sources})
target_link_libraries(test-nabla PRIVATE Eigen3::Eigen GTest::gtest GTest::gtest_main)

add_executable(test-nabla-armadillo ${test_sources})
target_link_libraries(test-nabla-armadillo PRIVATE armadillo GTest::gtest GTest::gtest_main)
target_compile_definitions(test-nabla-armadillo PRIVATE NABLA_BACKEND_ARMADILLO=1)

add_test(NAME test-nabla COMMAND test-nabla)
add_test(NAME test-nabla-armadillo COMMAND test-nabla-armadillo)
