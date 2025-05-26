#include <nabla/variable.hh>

#include <gtest/gtest.h>

TEST(variable, diff_by_var)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;
    
    nabla::vector<3> vars = nabla::make_vector(1, 2, 3);

    EXPECT_EQ(1, x(vars));
    EXPECT_EQ(2, y(vars));
    EXPECT_EQ(3, z(vars));

    EXPECT_EQ(1, x.diff(x)(vars));
    EXPECT_EQ(1, y.diff(y)(vars));
    EXPECT_EQ(1, z.diff(z)(vars));
    EXPECT_EQ(0, x.diff(y)(vars));
    EXPECT_EQ(0, x.diff(z)(vars));
    EXPECT_EQ(0, x.diff(x, x)(vars));
    EXPECT_EQ(0, x.diff(x, y)(vars));
    EXPECT_EQ(0, x.diff(x, z)(vars));
    EXPECT_EQ(0, x.diff(y, x)(vars));
    EXPECT_EQ(0, x.diff(y, y)(vars));
    EXPECT_EQ(0, x.diff(y, z)(vars));
    EXPECT_EQ(0, x.diff(z, x)(vars));
    EXPECT_EQ(0, x.diff(z, y)(vars));
    EXPECT_EQ(0, x.diff(z, z)(vars));

    EXPECT_EQ(x        (vars(0), vars(1), vars(2)), x        (vars));
    EXPECT_EQ(y        (vars(0), vars(1), vars(2)), y        (vars));
    EXPECT_EQ(z        (vars(0), vars(1), vars(2)), z        (vars));
    EXPECT_EQ(x.diff(x)(vars(0), vars(1), vars(2)), x.diff(x)(vars));
    EXPECT_EQ(x.diff(y)(vars(0), vars(1), vars(2)), x.diff(y)(vars));
}

TEST(variable, diff_by_num)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;
    
    nabla::vector<3> vars = nabla::make_vector(1, 2, 3);

    EXPECT_EQ(1, x(vars));
    EXPECT_EQ(2, y(vars));
    EXPECT_EQ(3, z(vars));

    EXPECT_EQ(1, x.diff<0>()(vars));
    EXPECT_EQ(1, y.diff<1>()(vars));
    EXPECT_EQ(1, z.diff<2>()(vars));
    EXPECT_EQ(0, x.diff<1>()(vars));
    EXPECT_EQ(0, x.diff<2>()(vars));
    EXPECT_EQ(0, x.diff<0>().diff<0>()(vars));
    EXPECT_EQ(0, x.diff<0>().diff<1>()(vars));
    EXPECT_EQ(0, x.diff<0>().diff<2>()(vars));
    EXPECT_EQ(0, x.diff<1>().diff<0>()(vars));
    EXPECT_EQ(0, x.diff<1>().diff<1>()(vars));
    EXPECT_EQ(0, x.diff<1>().diff<2>()(vars));
    EXPECT_EQ(0, x.diff<2>().diff<0>()(vars));
    EXPECT_EQ(0, x.diff<2>().diff<1>()(vars));
    EXPECT_EQ(0, x.diff<2>().diff<2>()(vars));

    EXPECT_EQ(x        (vars(0), vars(1), vars(2)), x        (vars));
    EXPECT_EQ(y        (vars(0), vars(1), vars(2)), y        (vars));
    EXPECT_EQ(z        (vars(0), vars(1), vars(2)), z        (vars));
    EXPECT_EQ(x.diff(x)(vars(0), vars(1), vars(2)), x.diff(x)(vars));
    EXPECT_EQ(x.diff(y)(vars(0), vars(1), vars(2)), x.diff(y)(vars));
}
