#include <nabla/constant.hh>
#include <nabla/variable.hh>

#include <gtest/gtest.h>

TEST(constant, diff_by_var)  {
    double val = 3.14;

    nabla::expr::constant v(val);

    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;
    
    nabla::vector<3> vars;

    EXPECT_EQ(val, v(vars));

    EXPECT_EQ(0.0, v.diff(x)(vars));
    EXPECT_EQ(0.0, v.diff(y)(vars));
    EXPECT_EQ(0.0, v.diff(z)(vars));
    EXPECT_EQ(0.0, v.diff(x, x)(vars));
    EXPECT_EQ(0.0, v.diff(x, y)(vars));
    EXPECT_EQ(0.0, v.diff(x, z)(vars));
    EXPECT_EQ(0.0, v.diff(y, x)(vars));
    EXPECT_EQ(0.0, v.diff(y, y)(vars));
    EXPECT_EQ(0.0, v.diff(y, z)(vars));
    EXPECT_EQ(0.0, v.diff(z, x)(vars));
    EXPECT_EQ(0.0, v.diff(z, y)(vars));
    EXPECT_EQ(0.0, v.diff(z, z)(vars));
}

TEST(constant, diff_by_num)  {
    double val = 3.14;

    nabla::expr::constant v(val);
    
    nabla::vector<3> vars;

    EXPECT_EQ(val, v(vars));

    EXPECT_EQ(0.0, v.diff<0>()(vars));
    EXPECT_EQ(0.0, v.diff<1>()(vars));
    EXPECT_EQ(0.0, v.diff<2>()(vars));
    EXPECT_EQ(0.0, v.diff<0>().diff<0>()(vars));
    EXPECT_EQ(0.0, v.diff<0>().diff<1>()(vars));
    EXPECT_EQ(0.0, v.diff<0>().diff<2>()(vars));
    EXPECT_EQ(0.0, v.diff<1>().diff<0>()(vars));
    EXPECT_EQ(0.0, v.diff<1>().diff<1>()(vars));
    EXPECT_EQ(0.0, v.diff<1>().diff<2>()(vars));
    EXPECT_EQ(0.0, v.diff<2>().diff<0>()(vars));
    EXPECT_EQ(0.0, v.diff<2>().diff<1>()(vars));
    EXPECT_EQ(0.0, v.diff<2>().diff<2>()(vars));
}

TEST(constant, params_expanded)  {
    double val = 3.14;

    nabla::expr::constant v(val);

    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;
    
    EXPECT_EQ(val, v(1, 2, 3));

    EXPECT_EQ(0.0, v.diff(x)(1, 2, 3));
    EXPECT_EQ(0.0, v.diff(y)(1, 2, 3));
    EXPECT_EQ(0.0, v.diff(z)(1, 2, 3));
    EXPECT_EQ(0.0, v.diff(x, x)(1, 2, 3));
    EXPECT_EQ(0.0, v.diff(x, y)(1, 2, 3));
    EXPECT_EQ(0.0, v.diff(x, z)(1, 2, 3));
    EXPECT_EQ(0.0, v.diff(y, x)(1, 2, 3));
    EXPECT_EQ(0.0, v.diff(y, y)(1, 2, 3));
    EXPECT_EQ(0.0, v.diff(y, z)(1, 2, 3));
    EXPECT_EQ(0.0, v.diff(z, x)(1, 2, 3));
    EXPECT_EQ(0.0, v.diff(z, y)(1, 2, 3));
    EXPECT_EQ(0.0, v.diff(z, z)(1, 2, 3));
}

TEST(constant, constant_value) {
    nabla::expr::constant c(2);

    EXPECT_EQ(2, nabla::expr::impl::constant_value(c));
    EXPECT_EQ(3, nabla::expr::impl::constant_value(3));
}

