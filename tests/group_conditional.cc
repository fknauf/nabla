#include <nabla/conditional.hh>
#include <nabla/product.hh>

#include <gtest/gtest.h>

TEST(conditional, case_true)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = nabla::expr::impl::make_conditional([](auto &&) { return true; }, x * x, x * y);
    
    nabla::vector<3> vars;
    vars << 3, 4, 5;

    EXPECT_EQ(9, f(vars));

    EXPECT_EQ(6, f.diff(x)(vars));
    EXPECT_EQ(0, f.diff(y)(vars));

    EXPECT_EQ(2, f.diff(x, x)(vars));
    EXPECT_EQ(0, f.diff(x, y)(vars));
}

TEST(conditional, case_false)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = nabla::expr::impl::make_conditional([](auto &&) { return false; }, x * x, x * y);
    
    nabla::vector<3> vars;
    vars << 3, 4, 5;

    EXPECT_EQ(12, f(vars));

    EXPECT_EQ(4, f.diff(x)(vars));
    EXPECT_EQ(3, f.diff(y)(vars));
    EXPECT_EQ(0, f.diff(z)(vars));

    EXPECT_EQ(0, f.diff(x, x)(vars));
    EXPECT_EQ(1, f.diff(x, y)(vars));
    EXPECT_EQ(1, f.diff(y, x)(vars));
    EXPECT_EQ(0, f.diff(y, y)(vars));
}

TEST(conditional, case_degrade)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = nabla::expr::impl::make_conditional([](auto &&) { return false; }, x, y);
    
    nabla::vector<3> vars;
    vars << 3, 4, 5;

    EXPECT_EQ(4, f(vars));

    EXPECT_EQ(0, f.diff(x)(vars));
    EXPECT_EQ(1, f.diff(y)(vars));
    EXPECT_EQ(0, f.diff(z)(vars));

    EXPECT_EQ(0, f.diff(x, x)(vars));
    EXPECT_EQ(0, f.diff(x, y)(vars));
    EXPECT_EQ(0, f.diff(y, x)(vars));
    EXPECT_EQ(0, f.diff(y, y)(vars));

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(f.diff(x, x))>::value));
}

TEST(conditional, params_expanded)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = nabla::expr::impl::make_conditional([](auto &&) { return true; }, x * x, x * y);

    EXPECT_EQ(9, f(3, 4, 5));

    EXPECT_EQ(6, f.diff(x)(3, 4, 5));
    EXPECT_EQ(0, f.diff(y)(3, 4, 5));

    EXPECT_EQ(2, f.diff(x, x)(3, 4, 5));
    EXPECT_EQ(0, f.diff(x, y)(3, 4, 5));
}

