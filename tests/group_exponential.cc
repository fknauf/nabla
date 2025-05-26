#include <nabla/exponential.hh>
#include <nabla/product.hh>
#include <nabla/sum.hh>

#include <gtest/gtest.h>

TEST(exponential, simple)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = pow(2, x);
    
    nabla::vector<2> vars;
    vars << 3, 4;

    EXPECT_DOUBLE_EQ(8, f(vars));

    EXPECT_DOUBLE_EQ(                            std::log(2) * 8, f.diff(x      )(vars));
    EXPECT_EQ       (                                          0, f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(              std::log(2) * std::log(2) * 8, f.diff(x, x   )(vars));
    EXPECT_EQ       (                                          0, f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(std::log(2) * std::log(2) * std::log(2) * 8, f.diff(x, x, x)(vars));
    EXPECT_EQ       (                                          0, f.diff(x, x, y)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1)), f.diff(x, x, y)(vars));
}

TEST(exponential, medium)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = pow(2, x - y);
    
    nabla::vector<2> vars;
    vars << 4, 1;

    EXPECT_DOUBLE_EQ(8, f(vars));

    EXPECT_DOUBLE_EQ(                             std::log(2) * 8, f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(                            -std::log(2) * 8, f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(               std::log(2) * std::log(2) * 8, f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(              -std::log(2) * std::log(2) * 8, f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ( std::log(2) * std::log(2) * std::log(2) * 8, f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(-std::log(2) * std::log(2) * std::log(2) * 8, f.diff(x, y, x)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1)), f.diff(x, x, y)(vars));
}

TEST(exponential, complex)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = pow(2, (x - y) * z + x * y - 2);
    
    nabla::vector<3> vars;
    vars << 3, 1, 4;

    EXPECT_DOUBLE_EQ(512, f(vars));

    double l2 = std::log(2);

    EXPECT_DOUBLE_EQ(2560 * l2, f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(-512 * l2, f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(1024 * l2, f.diff(z      )(vars));

    EXPECT_DOUBLE_EQ(             12800 * l2 * l2, f.diff(x, x)(vars));
    EXPECT_DOUBLE_EQ(  512 * l2 -  2560 * l2 * l2, f.diff(x, y)(vars));
    EXPECT_DOUBLE_EQ(  512 * l2 +  5120 * l2 * l2, f.diff(x, z)(vars));
    EXPECT_DOUBLE_EQ(  512 * l2 -  2560 * l2 * l2, f.diff(y, x)(vars));
    EXPECT_DOUBLE_EQ(               512 * l2 * l2, f.diff(y, y)(vars));
    EXPECT_DOUBLE_EQ( -512 * l2 -  1024 * l2 * l2, f.diff(y, z)(vars));
    EXPECT_DOUBLE_EQ(  512 * l2 +  5120 * l2 * l2, f.diff(z, x)(vars));
    EXPECT_DOUBLE_EQ( -512 * l2 -  1024 * l2 * l2, f.diff(z, y)(vars));
    EXPECT_DOUBLE_EQ(              2048 * l2 * l2, f.diff(z, z)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1), vars(2)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars));
}

TEST(exponential, test_trivial) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = pow(2, x * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           , std::pow(2.0, p(0) * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(x)(p), p(1) * std::log(2) * r    );
    EXPECT_DOUBLE_EQ(s.diff(y)(p), p(0) * std::log(2) * r    );

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(exponential, test_stacked) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = pow(2, pow(1.5, x * y));

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    double exv = std::pow(2, std::pow(1.5, p(0) * p(1)));

    double dx = p(1) * std::log(2) * std::log(1.5) * std::pow(1.5, p(0) * p(1)) * exv;
    double dy = p(0) * std::log(2) * std::log(1.5) * std::pow(1.5, p(0) * p(1)) * exv;

    EXPECT_DOUBLE_EQ(r           , exv);
    EXPECT_DOUBLE_EQ(s.diff(x)(p), dx );
    EXPECT_DOUBLE_EQ(s.diff(y)(p), dy);

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(exponential, constant_folding) {
    nabla::expr::constant c(3);

    auto s = pow(2, c);

    EXPECT_EQ(8, s());
    EXPECT_EQ(0, s.diff<0>()());

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s          )>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s.diff<0>())>::value));
}

