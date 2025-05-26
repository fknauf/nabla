#include <nabla/sum.hh>

#include <gtest/gtest.h>

TEST(sum, var_plus_num)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = x + 1 ;
    
    nabla::vector<3> vars = nabla::make_vector(2, 3, 4);

    EXPECT_EQ( 3, f(vars));

    EXPECT_EQ( 1, f.diff(x)(vars));
    EXPECT_EQ( 0, f.diff(y)(vars));

    EXPECT_EQ( 1, f.diff<0>()(vars));
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

TEST(sum, num_plus_var)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = 1 + x;
    
    nabla::vector<3> vars = nabla::make_vector(2, 3, 4);

    EXPECT_EQ( 3, f(vars));

    EXPECT_EQ( 1, f.diff(x)(vars));
    EXPECT_EQ( 0, f.diff(y)(vars));

    EXPECT_EQ( 1, f.diff<0>()(vars));
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

TEST(sum, var_plus_var)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = x + z ;
    
    nabla::vector<3> vars = nabla::make_vector(2, 3, 4);

    EXPECT_EQ( 6, f(vars));

    EXPECT_EQ( 1, f.diff(x)(vars));
    EXPECT_EQ( 0, f.diff(y)(vars));
    EXPECT_EQ( 1, f.diff(z)(vars));

    EXPECT_EQ( 1, f.diff<0>()(vars));
    EXPECT_EQ( 0, f.diff<1>()(vars));
    EXPECT_EQ( 1, f.diff<2>()(vars));
    
    EXPECT_EQ( 0, f.diff(x, x)(vars));
    EXPECT_EQ( 0, f.diff(x, y)(vars));
    EXPECT_EQ( 0, f.diff(x, z)(vars));
    EXPECT_EQ( 0, f.diff(y, x)(vars));
    EXPECT_EQ( 0, f.diff(y, y)(vars));
    EXPECT_EQ( 0, f.diff(y, z)(vars));
    EXPECT_EQ( 0, f.diff(z, x)(vars));
    EXPECT_EQ( 0, f.diff(z, y)(vars));
    EXPECT_EQ( 0, f.diff(z, z)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1), vars(2)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars));
}

TEST(sum, var_plus_self)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = x + x;
    
    nabla::vector<3> vars = nabla::make_vector(2, 3, 4);

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

TEST(sum, var_minus_num)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = x - 1 ;
    
    nabla::vector<3> vars = nabla::make_vector(2, 3, 4);

    EXPECT_EQ( 1, f(vars));

    EXPECT_EQ( 1, f.diff(x)(vars));
    EXPECT_EQ( 0, f.diff(y)(vars));

    EXPECT_EQ( 1, f.diff<0>()(vars));
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

TEST(sum, num_minus_var)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = 1 - x;
    
    nabla::vector<3> vars = nabla::make_vector(2, 3, 4);

    EXPECT_EQ(-1, f(vars));

    EXPECT_EQ(-1, f.diff(x)(vars));
    EXPECT_EQ( 0, f.diff(y)(vars));

    EXPECT_EQ(-1, f.diff<0>()(vars));
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

TEST(sum, var_minus_var)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = x - z ;
    
    nabla::vector<3> vars = nabla::make_vector(2, 3, 4);

    EXPECT_EQ(-2, f(vars));

    EXPECT_EQ( 1, f.diff(x)(vars));
    EXPECT_EQ( 0, f.diff(y)(vars));
    EXPECT_EQ(-1, f.diff(z)(vars));

    EXPECT_EQ( 1, f.diff<0>()(vars));
    EXPECT_EQ( 0, f.diff<1>()(vars));
    EXPECT_EQ(-1, f.diff<2>()(vars));
    
    EXPECT_EQ( 0, f.diff(x, x)(vars));
    EXPECT_EQ( 0, f.diff(x, y)(vars));
    EXPECT_EQ( 0, f.diff(x, z)(vars));
    EXPECT_EQ( 0, f.diff(y, x)(vars));
    EXPECT_EQ( 0, f.diff(y, y)(vars));
    EXPECT_EQ( 0, f.diff(y, z)(vars));
    EXPECT_EQ( 0, f.diff(z, x)(vars));
    EXPECT_EQ( 0, f.diff(z, y)(vars));
    EXPECT_EQ( 0, f.diff(z, z)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1), vars(2)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars));
}

TEST(sum, var_minus_self)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = x - x;
    
    nabla::vector<3> vars = nabla::make_vector(2, 3, 4);

    EXPECT_EQ( 0, f(vars));

    EXPECT_EQ( 0, f.diff(x)(vars));
    EXPECT_EQ( 0, f.diff(y)(vars));

    EXPECT_EQ( 0, f.diff<0>()(vars));
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

TEST(sum, mixed)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = x - z - 2 + y + 5;
    
    nabla::vector<3> vars = nabla::make_vector(2, 3, 4);

    EXPECT_EQ( 4, f(vars));

    EXPECT_EQ( 1, f.diff(x)(vars));
    EXPECT_EQ( 1, f.diff(y)(vars));
    EXPECT_EQ(-1, f.diff(z)(vars));

    EXPECT_EQ( 1, f.diff<0>()(vars));
    EXPECT_EQ( 1, f.diff<1>()(vars));
    EXPECT_EQ(-1, f.diff<2>()(vars));
    
    EXPECT_EQ( 0, f.diff(x, x)(vars));
    EXPECT_EQ( 0, f.diff(x, y)(vars));
    EXPECT_EQ( 0, f.diff(x, z)(vars));
    EXPECT_EQ( 0, f.diff(y, x)(vars));
    EXPECT_EQ( 0, f.diff(y, y)(vars));
    EXPECT_EQ( 0, f.diff(y, z)(vars));
    EXPECT_EQ( 0, f.diff(z, x)(vars));
    EXPECT_EQ( 0, f.diff(z, y)(vars));
    EXPECT_EQ( 0, f.diff(z, z)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1), vars(2)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars));
}

TEST(sum, simple_n1) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = 2.0 + x - y;

    nabla::vector<2> values { 1.0, -3.0 };

    auto r = s(values);

    EXPECT_EQ( 6.0, r);
    EXPECT_EQ( 1.0, s.diff(x)(values));
    EXPECT_EQ(-1.0, s.diff(y)(values));

    EXPECT_DOUBLE_EQ(s              (values(0), values(1)), s              (values));
    EXPECT_DOUBLE_EQ(s.diff(x      )(values(0), values(1)), s.diff(x      )(values));
    EXPECT_DOUBLE_EQ(s.diff(y      )(values(0), values(1)), s.diff(y      )(values));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(values(0), values(1)), s.diff(x, x   )(values));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(values(0), values(1)), s.diff(x, y   )(values));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(values(0), values(1)), s.diff(x, x, x)(values));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(values(0), values(1)), s.diff(x, x, y)(values));
}

TEST(sum, constant_folding_plus) {
    nabla::expr::constant c(1);

    auto s = c + 2;

    EXPECT_EQ(3, s());
    EXPECT_EQ(0, s.diff<0>()());

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s          )>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s.diff<0>())>::value));
}

TEST(sum, constant_folding_minus) {
    nabla::expr::constant c(2);

    auto s = c - 1;

    EXPECT_EQ(1, s());
    EXPECT_EQ(0, s.diff<0>()());

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s          )>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s.diff<0>())>::value));
}

