#include <nabla/nabla.hh>
#include <gtest/gtest.h>

TEST(gradient, simple) {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = x - y;

    auto g = nabla::gradient(f, 2, 3, 4);

    EXPECT_EQ(g(0),  1);
    EXPECT_EQ(g(1), -1);
    EXPECT_EQ(g(2),  0);
}

TEST(gradient, complex) {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = pow(sin(x + y) * cos(z * z), 2) + 10;

    auto g = nabla::gradient(f, 2, 3, 4);

    EXPECT_DOUBLE_EQ(g(0),   2 * std::cos( 5) * std::sin( 5) * std::pow(std::cos(16), 2));
    EXPECT_DOUBLE_EQ(g(1),   2 * std::cos( 5) * std::sin( 5) * std::pow(std::cos(16), 2));
    EXPECT_DOUBLE_EQ(g(2), -16 * std::cos(16) * std::sin(16) * std::pow(std::sin( 5), 2));
}

TEST(gradient, complex_vecparam) {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = pow(sin(x + y) * cos(z * z), 2) + 10;

    nabla::vector<3> vars { 2, 3, 4 };
    
    auto g = nabla::gradient(f, vars);

    EXPECT_DOUBLE_EQ(g(0),   2 * std::cos( 5) * std::sin( 5) * std::pow(std::cos(16), 2));
    EXPECT_DOUBLE_EQ(g(1),   2 * std::cos( 5) * std::sin( 5) * std::pow(std::cos(16), 2));
    EXPECT_DOUBLE_EQ(g(2), -16 * std::cos(16) * std::sin(16) * std::pow(std::sin( 5), 2));
}

