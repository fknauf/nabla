#include <nabla/negation.hh>
#include <nabla/variable.hh>

#include <gtest/gtest.h>

TEST(negation, diff_by_var)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = -x;
    
    nabla::vector<3> vars = nabla::make_vector(2, 3, 4);

    EXPECT_EQ(-2, f(vars));

    EXPECT_EQ(-1, f.diff(x)(vars));
    EXPECT_EQ( 0, f.diff(y)(vars));
    EXPECT_EQ( 0, f.diff(z)(vars));
    EXPECT_EQ( 0, f.diff(x, x)(vars));
    EXPECT_EQ( 0, f.diff(x, y)(vars));
    EXPECT_EQ( 0, f.diff(x, z)(vars));
    EXPECT_EQ( 0, f.diff(y, x)(vars));
    EXPECT_EQ( 0, f.diff(y, y)(vars));
    EXPECT_EQ( 0, f.diff(y, z)(vars));
    EXPECT_EQ( 0, f.diff(z, x)(vars));
    EXPECT_EQ( 0, f.diff(z, y)(vars));
    EXPECT_EQ( 0, f.diff(z, z)(vars));

    EXPECT_DOUBLE_EQ(f              (vars(0), vars(1)), f              (vars));
    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1)), f.diff(x, x, x)(vars));
}

TEST(negation, diff_by_num)  {
    nabla::expr::variable<0> x;

    auto f = -x;
    
    nabla::vector<3> vars = nabla::make_vector(2, 3, 4);

    EXPECT_EQ(-2, f(vars));

    EXPECT_EQ(-1, f.diff<0>()(vars));
    EXPECT_EQ( 0, f.diff<1>()(vars));
    EXPECT_EQ( 0, f.diff<2>()(vars));
    EXPECT_EQ( 0, f.diff<0>().diff<0>()(vars));
    EXPECT_EQ( 0, f.diff<0>().diff<1>()(vars));
    EXPECT_EQ( 0, f.diff<0>().diff<2>()(vars));
    EXPECT_EQ( 0, f.diff<1>().diff<0>()(vars));
    EXPECT_EQ( 0, f.diff<1>().diff<1>()(vars));
    EXPECT_EQ( 0, f.diff<1>().diff<2>()(vars));
    EXPECT_EQ( 0, f.diff<2>().diff<0>()(vars));
    EXPECT_EQ( 0, f.diff<2>().diff<1>()(vars));
    EXPECT_EQ( 0, f.diff<2>().diff<2>()(vars));

    EXPECT_DOUBLE_EQ(f.diff(x      )(vars(0), vars(1)), f.diff(x      )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x   )(vars(0), vars(1)), f.diff(x, x   )(vars));
    EXPECT_DOUBLE_EQ(f.diff(x, x, x)(vars(0), vars(1)), f.diff(x, x, x)(vars));
}

TEST(negation, constant_folding) {
    nabla::expr::constant c(2);

    auto s = -c;

    EXPECT_EQ(-2, s());
    EXPECT_EQ( 0, s.diff<0>()());

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s          )>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s.diff<0>())>::value));
}
