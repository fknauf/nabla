#include <nabla/power.hh>
#include <nabla/polynomial.hh>
#include <nabla/product.hh>
#include <nabla/sum.hh>

#include <gtest/gtest.h>

#include <iostream>

TEST(power, simple)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = pow(x, y);
    
    nabla::vector<2> vars { 2., 5. };

    EXPECT_DOUBLE_EQ(32, f(vars));

    EXPECT_DOUBLE_EQ( 80                   , f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ( 32 * std::log(2)     , f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(160                   , f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ( 80 * std::log(2) + 16, f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(240                   , f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(160 * std::log(2) + 72, f.diff(x, x, y)(vars));

    EXPECT_DOUBLE_EQ(f.diff(x, y)   (vars), f.diff(y, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars), f.diff(y, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars), f.diff(x, y, x)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1)), f.diff(x, x, x)(vars));
}

TEST(power, mixed)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = pow(pow(x, 2) * y, pow(y, 2) * x);
    
    nabla::vector<2> p { 2., 5. };

    double exv = std::pow(std::pow(p(0), 2) * p(1), std::pow(p(1), 2) * p(0));
    double dx  = exv * std::pow(p(1), 2) * (std::log(p(1)) + 2 * std::log(p(0)) + 2);
    double dy  = exv * p(0) * p(1) * (2 * std::log(p(1)) + 4 * std::log(p(0)) + 1);
    
    EXPECT_DOUBLE_EQ(exv, f(p));

    EXPECT_DOUBLE_EQ(dx, f.diff(x)(p));
    EXPECT_DOUBLE_EQ(dy, f.diff(y)(p));

    EXPECT_NEAR(9.893089493270056e68, f.diff(x, y)(p), 1e56);

    EXPECT_DOUBLE_EQ(f              (p(0), p(1)), f              (p));
    EXPECT_DOUBLE_EQ(f.diff(x      )(p(0), p(1)), f.diff(x      )(p));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(p(0), p(1)), f.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(p(0), p(1)), f.diff(x, x, x)(p));
}

TEST(power, test_simple) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = pow(x, y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           , std::pow(p(0), p(1))                 );
    EXPECT_DOUBLE_EQ(s.diff(x)(p), std::pow(p(0), p(1) - 1) * p(1)      );
    EXPECT_DOUBLE_EQ(s.diff(y)(p), std::pow(p(0), p(1)) * std::log(p(0)));

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
}

TEST(power, test_mixed) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = pow(pow(x, 2) * y, pow(y, 2) * x);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    double exv = std::pow(std::pow(p(0), 2) * p(1), std::pow(p(1), 2) * p(0));
    double dx  = exv * std::pow(p(1), 2) * (std::log(p(1)) + 2 * std::log(p(0)) + 2);
    double dy  = exv * p(0) * p(1) * (2 * std::log(p(1)) + 4 * std::log(p(0)) + 1);

    EXPECT_DOUBLE_EQ(r           , exv);
    EXPECT_DOUBLE_EQ(s.diff(x)(p), dx );
    EXPECT_DOUBLE_EQ(s.diff(y)(p), dy);

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
}

TEST(power, constant_folding) {
    nabla::expr::constant c(2);

    auto s = pow(c, c);

    EXPECT_EQ(4, s());
    EXPECT_EQ(0, s.diff<0>()());

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s          )>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s.diff<0>())>::value));
}

