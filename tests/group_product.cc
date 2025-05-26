#include <nabla/product.hh>

#include <gtest/gtest.h>

TEST(product, var_times_num)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = x * 2 ;
    
    nabla::vector<3> vars;
    vars << 2, 3, 4;

    EXPECT_EQ( 4, f(vars));

    EXPECT_EQ( 2, f.diff(x)(vars));
    EXPECT_EQ( 0, f.diff(y)(vars));

    EXPECT_EQ( 2, f.diff<0>()(vars));
    EXPECT_EQ( 0, f.diff<1>()(vars));
    
    EXPECT_EQ( 0, f.diff(x, x)(vars));
    EXPECT_EQ( 0, f.diff(x, y)(vars));
    EXPECT_EQ( 0, f.diff(y, x)(vars));
    EXPECT_EQ( 0, f.diff(y, y)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1), vars(2)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars));
}

TEST(product, num_times_var)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = 2 * x;
    
    nabla::vector<3> vars;
    vars << 2, 3, 4;

    EXPECT_EQ( 4, f(vars));

    EXPECT_EQ( 2, f.diff(x)(vars));
    EXPECT_EQ( 0, f.diff(y)(vars));

    EXPECT_EQ( 2, f.diff<0>()(vars));
    EXPECT_EQ( 0, f.diff<1>()(vars));
    
    EXPECT_EQ( 0, f.diff(x, x)(vars));
    EXPECT_EQ( 0, f.diff(x, y)(vars));
    EXPECT_EQ( 0, f.diff(y, x)(vars));
    EXPECT_EQ( 0, f.diff(y, y)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1), vars(2)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars));
}

TEST(product, var_times_var)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = x * y ;
    
    nabla::vector<3> vars;
    vars << 2, 3, 4;

    EXPECT_EQ( 6, f(vars));

    EXPECT_EQ( 3, f.diff(x)(vars));
    EXPECT_EQ( 2, f.diff(y)(vars));
    EXPECT_EQ( 0, f.diff(z)(vars));

    EXPECT_EQ( 3, f.diff<0>()(vars));
    EXPECT_EQ( 2, f.diff<1>()(vars));
    EXPECT_EQ( 0, f.diff<2>()(vars));
    
    EXPECT_EQ( 0, f.diff(x, x)(vars));
    EXPECT_EQ( 1, f.diff(x, y)(vars));
    EXPECT_EQ( 1, f.diff(y, x)(vars));
    EXPECT_EQ( 0, f.diff(y, y)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1), vars(2)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars));
}

TEST(product, var_square)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = x * x ;
    
    nabla::vector<3> vars;
    vars << 3, 4, 5;

    EXPECT_EQ( 9, f(vars));

    EXPECT_EQ( 6, f.diff(x)(vars));
    EXPECT_EQ( 0, f.diff(y)(vars));

    EXPECT_EQ( 6, f.diff<0>()(vars));
    EXPECT_EQ( 0, f.diff<1>()(vars));
    
    EXPECT_EQ( 2, f.diff(x, x)(vars));
    EXPECT_EQ( 0, f.diff(x, y)(vars));
    EXPECT_EQ( 0, f.diff(y, x)(vars));
    EXPECT_EQ( 0, f.diff(y, y)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1), vars(2)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars));
}

TEST(product, var_cube)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = x * x * x;
    
    nabla::vector<3> vars;
    vars << 4, 5, 6;

    EXPECT_EQ(64, f(vars));

    EXPECT_EQ(48, f.diff(x)(vars));
    EXPECT_EQ( 0, f.diff(y)(vars));

    EXPECT_EQ(48, f.diff<0>()(vars));
    EXPECT_EQ( 0, f.diff<1>()(vars));
    
    EXPECT_EQ(24, f.diff(x, x)(vars));
    EXPECT_EQ( 0, f.diff(x, y)(vars));
    EXPECT_EQ( 0, f.diff(y, x)(vars));
    EXPECT_EQ( 0, f.diff(y, y)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1), vars(2)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars));
}

TEST(product, dist)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = 2 * (x + y) * x;
    
    nabla::vector<3> vars;
    vars << 3, 4, 5;

    EXPECT_EQ(42, f(vars));

    EXPECT_EQ(20, f.diff(x)(vars));
    EXPECT_EQ( 6, f.diff(y)(vars));
    EXPECT_EQ( 0, f.diff(z)(vars));

    EXPECT_EQ(20, f.diff<0>()(vars));
    EXPECT_EQ( 6, f.diff<1>()(vars));
    EXPECT_EQ( 0, f.diff<2>()(vars));
    
    EXPECT_EQ( 4, f.diff(x, x)(vars));
    EXPECT_EQ( 2, f.diff(x, y)(vars));
    EXPECT_EQ( 2, f.diff(y, x)(vars));
    EXPECT_EQ( 0, f.diff(y, y)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1), vars(2)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars));
}

TEST(product, n1_simple) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = 2.0 * x * y;

    nabla::vector<2> values { 3.0, 4.0 };

    auto r = s(values);

    EXPECT_EQ(24.0, r);
    EXPECT_EQ( 8.0, s.diff(x)(values));
    EXPECT_EQ( 6.0, s.diff(y)(values));

    EXPECT_DOUBLE_EQ(s              (values(0), values(1)), s              (values));
    EXPECT_DOUBLE_EQ(s.diff(x      )(values(0), values(1)), s.diff(x      )(values));
    EXPECT_DOUBLE_EQ(s.diff(y      )(values(0), values(1)), s.diff(y      )(values));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(values(0), values(1)), s.diff(x, x   )(values));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(values(0), values(1)), s.diff(x, y   )(values));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(values(0), values(1)), s.diff(x, x, x)(values));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(values(0), values(1)), s.diff(x, x, y)(values));
}

TEST(product, n1_squares) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<0>();

    auto s = 2.0 * x * x;

    nabla::vector<1> values = nabla::vector<1>::Constant(3.0);

    auto r = s(values);

    EXPECT_EQ(18.0, r);
    EXPECT_EQ(12.0, s.diff(x)(values));

    EXPECT_DOUBLE_EQ(s              (values(0)), s              (values));
    EXPECT_DOUBLE_EQ(s.diff(x      )(values(0)), s.diff(x      )(values));
    EXPECT_DOUBLE_EQ(s.diff(y      )(values(0)), s.diff(y      )(values));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(values(0)), s.diff(x, x   )(values));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(values(0)), s.diff(x, y   )(values));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(values(0)), s.diff(x, x, x)(values));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(values(0)), s.diff(x, x, y)(values));
}

TEST(product, n1_mixed_polynomial) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = 2.0 * x * x * y;

    nabla::vector<2> values { 3.0, 4.0 };

    auto r = s(values);

    EXPECT_EQ(72.0, r);
    EXPECT_EQ(48.0, s.diff(x)(values));
    EXPECT_EQ(18.0, s.diff(y)(values));

    EXPECT_DOUBLE_EQ(s              (values(0), values(1)), s              (values));
    EXPECT_DOUBLE_EQ(s.diff(x      )(values(0), values(1)), s.diff(x      )(values));
    EXPECT_DOUBLE_EQ(s.diff(y      )(values(0), values(1)), s.diff(y      )(values));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(values(0), values(1)), s.diff(x, x   )(values));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(values(0), values(1)), s.diff(x, y   )(values));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(values(0), values(1)), s.diff(x, x, x)(values));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(values(0), values(1)), s.diff(x, x, y)(values));
}

TEST(product, constant_folding) {
    nabla::expr::constant c(2);

    auto s = c * 3;

    EXPECT_EQ(6, s());
    EXPECT_EQ(0, s.diff<0>()());

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s          )>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s.diff<0>())>::value));
}


