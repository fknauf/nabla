#include <nabla/logarithm.hh>
#include <nabla/product.hh>
#include <nabla/sum.hh>

#include <gtest/gtest.h>

TEST(logarithm, simple)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = log(x);
    
    nabla::vector<2> vars;
    vars << 3, 4;

    EXPECT_DOUBLE_EQ(std::log(3), f(vars));

    EXPECT_DOUBLE_EQ( 1. /  3, f.diff(x      )(vars));
    EXPECT_EQ       (       0, f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(-1. /  9, f.diff(x, x   )(vars));
    EXPECT_EQ       (       0, f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ( 2. / 27, f.diff(x, x, x)(vars));
    EXPECT_EQ       (       0, f.diff(x, x, y)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1)), f.diff(x, x, y)(vars));
}

TEST(logarithm, square)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = log(x);
    auto g = log(x * x);
    
    nabla::vector<2> vars;
    vars << 3, 4;

    EXPECT_DOUBLE_EQ(std::log(3), f(vars));

    EXPECT_DOUBLE_EQ(2 * f.diff(x      )(vars), g.diff(x      )(vars));
    EXPECT_EQ       (2 * f.diff(y      )(vars), g.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(2 * f.diff(x, x   )(vars), g.diff(x, x   )(vars));
    EXPECT_EQ       (2 * f.diff(x, y   )(vars), g.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(2 * f.diff(x, x, x)(vars), g.diff(x, x, x)(vars));
    EXPECT_EQ       (2 * f.diff(x, x, y)(vars), g.diff(x, x, y)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1)), f.diff(x, x, y)(vars));
}

TEST(logarithm, sum)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = log(x + 2 * y);
    
    nabla::vector<2> vars;
    vars << 3, 4;

    EXPECT_DOUBLE_EQ(std::log(11), f(vars));

    EXPECT_DOUBLE_EQ( 1. /   11, f.diff(x      )(vars));
    EXPECT_EQ       ( 2. /   11, f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(-1. /  121, f.diff(x, x   )(vars));
    EXPECT_EQ       (-2. /  121, f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ( 2. / 1331, f.diff(x, x, x)(vars));
    EXPECT_EQ       ( 4. / 1331, f.diff(x, x, y)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1)), f.diff(x, x, y)(vars));
}

TEST(logarithm, constant_folding) {
    nabla::expr::constant c(2);

    auto s = log(c);

    EXPECT_EQ(std::log(2), s());
    EXPECT_EQ(0, s.diff<0>()());

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s          )>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s.diff<0>())>::value));
}
