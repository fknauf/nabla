#include <nabla/polynomial.hh>
#include <nabla/product.hh>
#include <nabla/sum.hh>

#include <gtest/gtest.h>

TEST(polynomial, simple_square)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = pow(x, 2);
    
    nabla::vector<1> vars = nabla::make_vector(3);

    EXPECT_EQ(9, f(vars));

    EXPECT_EQ(6, f.diff(x)(vars));
    EXPECT_EQ(0, f.diff(y)(vars));

    EXPECT_EQ(2, f.diff(x, x)(vars));
    EXPECT_EQ(0, f.diff(x, y)(vars));

    EXPECT_EQ(0, f.diff(x, x, x)(vars));
    EXPECT_EQ(0, f.diff(x, x, y)(vars));

    EXPECT_EQ(f        (vars(0)), f        (vars));
    EXPECT_EQ(f.diff(x)(vars(0)), f.diff(x)(vars));
}

TEST(polynomial, simple_real)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = pow(x, 3.5);
    
    nabla::vector<1> vars = nabla::make_vector(3);

    EXPECT_DOUBLE_EQ(std::pow(3, 3.5), f(vars));

    EXPECT_DOUBLE_EQ(3.5 *             std::pow(3, 2.5), f.diff(x      )(vars));
    EXPECT_EQ       (0                                 , f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(3.5 * 2.5 *       std::pow(3, 1.5), f.diff(x, x   )(vars));
    EXPECT_EQ       (0                                 , f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(3.5 * 2.5 * 1.5 * std::sqrt(3)    , f.diff(x, x, x)(vars));
    EXPECT_EQ       (0                                 , f.diff(x, x, y)(vars));

    EXPECT_EQ(f        (vars(0)), f        (vars));
    EXPECT_EQ(f.diff(x)(vars(0)), f.diff(x)(vars));
}

TEST(polynomial, simple_0)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = pow(x, 0);
    
    nabla::vector<1> vars = nabla::make_vector(0);

    EXPECT_DOUBLE_EQ(1, f(vars));

    EXPECT_DOUBLE_EQ(0, f.diff(x      )(vars));
    EXPECT_EQ       (0, f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(0, f.diff(x, x   )(vars));
    EXPECT_EQ       (0, f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(0, f.diff(x, x, x)(vars));
    EXPECT_EQ       (0, f.diff(x, x, y)(vars));

    EXPECT_EQ(f        (vars(0)), f        (vars));
    EXPECT_EQ(f.diff(x)(vars(0)), f.diff(x)(vars));
}

TEST(polynomial, simple_break)  {
    nabla::expr::variable<0> x;

    auto f = pow(x, 1);
    
    nabla::vector<1> vars = nabla::make_vector(0);

    // Knickstelle in der Ableitung bei 0^0
    EXPECT_DOUBLE_EQ(0, f           (vars));
    EXPECT_DOUBLE_EQ(1, f.diff(x   )(vars));
    EXPECT_DOUBLE_EQ(0, f.diff(x, x)(vars));

    EXPECT_EQ(f        (vars(0)), f        (vars));
    EXPECT_EQ(f.diff(x)(vars(0)), f.diff(x)(vars));
}

TEST(polynomial, chain)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = pow(y - x, 3);
    
    nabla::vector<2> vars = nabla::make_vector(1, 3);

    EXPECT_DOUBLE_EQ(8, f(vars));

    EXPECT_DOUBLE_EQ(-12, f.diff(x      )(vars));
    EXPECT_EQ       ( 12, f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ( 12, f.diff(x, x   )(vars));
    EXPECT_EQ       (-12, f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ( -6, f.diff(x, x, x)(vars));
    EXPECT_EQ       (  6, f.diff(x, x, y)(vars));

    EXPECT_EQ(f        (vars(0), vars(1)), f        (vars));
    EXPECT_EQ(f.diff(x)(vars(0), vars(1)), f.diff(x)(vars));
}

TEST(polynomial, test_polynomial) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = pow(x * y, 4);

    nabla::vector<2> p = nabla::make_vector(2.0, 5.0);

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,     std::pow(p(0) * p(1), 4)             );
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 4 * std::pow(p(0), 3) * std::pow(p(1), 4));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 4 * std::pow(p(0), 4) * std::pow(p(1), 3));

    EXPECT_EQ(s        (p(0), p(1)), s        (p));
    EXPECT_EQ(s.diff(x)(p(0), p(1)), s.diff(x)(p));
}

TEST(polynomial, test_polynomial_2) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = pow(x, 3) - 3 * pow(x, 2) * y + 3 * x * pow(y, 2) - pow(y, 3);

    nabla::vector<2> p = nabla::make_vector(2.0, 5.0);

    auto r = s(p);

    double exv =
      std::pow(p(0), 3)
      - 3 * std::pow(p(0), 2) *          p(1)
      + 3 *          p(0)     * std::pow(p(1), 2)
      - std::pow(p(1), 3);

    double dx = 3 * std::pow(p(0), 2) - 6 * p(0) * p(1) + 3 * std::pow(p(1), 2);

    EXPECT_DOUBLE_EQ(r           , exv);
    EXPECT_DOUBLE_EQ(s.diff(x)(p),  dx);
    EXPECT_DOUBLE_EQ(s.diff(y)(p), -dx);

    EXPECT_EQ(s        (p(0), p(1)), s        (p));
    EXPECT_EQ(s.diff(x)(p(0), p(1)), s.diff(x)(p));
}

TEST(polynomial, test_degenerated) {
    auto x = nabla::expr::variable<0>();

    auto s = pow(x, 0);

    nabla::vector<1> p = nabla::make_vector(2.0);

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           , 1.0);
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 0.0);

    p(0) = 0.0;
    r = s(p);

    EXPECT_DOUBLE_EQ(r           , 1.0);
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 0.0);

    EXPECT_EQ(s        (p(0)), s        (p));
    EXPECT_EQ(s.diff(x)(p(0)), s.diff(x)(p));
}

TEST(polynomial, constant_folding) {
    nabla::expr::constant c(3);

    auto s = pow(c, 2);

    EXPECT_EQ(9, s());
    EXPECT_EQ(0, s.diff<0>()());

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s          )>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s.diff<0>())>::value));
}
