#include <nabla/nabla.hh>
#include <gtest/gtest.h>

#include <iostream>

TEST(hessian, simple) {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = pow(x - y, 2);

    auto h = nabla::hessian(f, 2, 3);

    EXPECT_DOUBLE_EQ( 2, h(0, 0));
    EXPECT_DOUBLE_EQ(-2, h(0, 1));
    EXPECT_DOUBLE_EQ(-2, h(1, 0));
    EXPECT_DOUBLE_EQ( 2, h(1, 1));
}

TEST(hessian, complex) {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = pow(sin(x - 2 * y) * cos(z * z), 2) + 10;

    auto h = nabla::hessian(f, 2, 3, 4);

    EXPECT_NEAR(-0.2668795609662459, h(0, 0), 1e-10);
    EXPECT_NEAR( 0.5337591219324918, h(0, 1), 1e-10);
    EXPECT_NEAR( 4.364468275957035 , h(0, 2), 1e-10);
    EXPECT_EQ  (            h(0, 1), h(1, 0)       );
    EXPECT_NEAR(-1.067518243864983 , h(1, 1), 1e-10);
    EXPECT_NEAR(-8.728936551914071 , h(1, 2), 1e-10);
    EXPECT_EQ  (            h(0, 2), h(2, 0)       );
    EXPECT_EQ  (            h(1, 2), h(2, 1)       );
    EXPECT_NEAR(-61.79024409251047 , h(2, 2), 1e-10);
}

TEST(hessian, complex_vecparam) {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = pow(sin(x - 2 * y) * cos(z * z), 2) + 10;

    nabla::vector<3> vars { 2, 3, 4 };
    
    auto h = nabla::hessian(f, vars);

    EXPECT_NEAR(-0.2668795609662459, h(0, 0), 1e-10);
    EXPECT_NEAR( 0.5337591219324918, h(0, 1), 1e-10);
    EXPECT_NEAR( 4.364468275957035 , h(0, 2), 1e-10);
    EXPECT_EQ  (            h(0, 1), h(1, 0)       );
    EXPECT_NEAR(-1.067518243864983 , h(1, 1), 1e-10);
    EXPECT_NEAR(-8.728936551914071 , h(1, 2), 1e-10);
    EXPECT_EQ  (            h(0, 2), h(2, 0)       );
    EXPECT_EQ  (            h(1, 2), h(2, 1)       );
    EXPECT_NEAR(-61.79024409251047 , h(2, 2), 1e-10);
}
