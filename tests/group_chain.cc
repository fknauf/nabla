#include <nabla/chain.hh>
#include <nabla/hypot.hh>

#include <gtest/gtest.h>

TEST(chain, sym)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = x * x * y;
    auto g = x * x;
    auto h = x + 2 * x * y;

    nabla::expr::chain<decltype(f), decltype(g), decltype(h)> c(f, g, h);
    
    nabla::vector<3> vars;
    vars << 2, 3, 4;

    EXPECT_EQ(224, c(vars));

    EXPECT_EQ(560, c.diff(x)(vars));
    EXPECT_EQ( 64, c.diff(y)(vars));
    EXPECT_EQ(  0, c.diff(z)(vars));

    EXPECT_EQ(160, c.diff(x, y)(vars));
    EXPECT_EQ(160, c.diff(y, x)(vars));
}

TEST(chain, asym)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = x * x * y;
    auto g = x * x + z;
    auto h = x + 2 * x * y;

    nabla::expr::chain<decltype(f), decltype(g), decltype(h)> c(f, g, h);
    
    nabla::vector<3> vars;
    vars << 2, 3, 4;

    EXPECT_EQ( 896, c(vars));

    EXPECT_EQ(1344, c.diff(x)(vars));
    EXPECT_EQ( 256, c.diff(y)(vars));
    EXPECT_EQ( 224, c.diff(z)(vars));

    EXPECT_EQ(384, c.diff(x, y)(vars));
    EXPECT_EQ(384, c.diff(y, x)(vars));
}

TEST(chain, n1_simple) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto a = x;
    auto b = y;

    auto s = nabla::expr::impl::make_chain(
        a + b,
		3 * x + y,
		x + 2 * y
    );

    nabla::vector<2> p(1.0, -3.0);

    auto r = s(p);

    EXPECT_DOUBLE_EQ(4 * p(0) + 3 * p(1), r);

    EXPECT_DOUBLE_EQ(4.0, s.diff(x)(p));
    EXPECT_DOUBLE_EQ(3.0, s.diff(y)(p));
}

TEST(chain, n1_product_rule) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto a = x;
    auto b = y;

    auto s = nabla::expr::impl::make_chain(
        a * b,
		3 * x + y,
		x + 2 * y
    );

    nabla::vector<2> p(1.0, -3.0);

    auto r = s(p);

    EXPECT_DOUBLE_EQ((3 * p(0) + p(1)) * (p(0) + 2 * p(1)), r);

    EXPECT_DOUBLE_EQ(6 * p(0) + 7 * p(1), s.diff(x)(p));
    EXPECT_DOUBLE_EQ(7 * p(0) + 4 * p(1), s.diff(y)(p));
}

TEST(chain, n1_simple_num) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto a = x;
    auto b = y;

    auto s = nabla::expr::impl::make_chain(
        a + b,
		nabla::expr::constant(3),
		nabla::expr::constant(2)
    );

    nabla::vector<2> p(1.0, -3.0);

    auto r = s(p);

    EXPECT_EQ(5, r);

    EXPECT_DOUBLE_EQ(0.0, s.diff(x)(p));
    EXPECT_DOUBLE_EQ(0.0, s.diff(y)(p));
}

TEST(chain, params_expanded)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = x * x * y;
    auto g = x * x;
    auto h = x + 2 * x * y;

    nabla::expr::chain<decltype(f), decltype(g), decltype(h)> c(f, g, h);
    
    EXPECT_EQ(224, c(2, 3, 4));

    EXPECT_EQ(560, c.diff(x)(2, 3, 4));
    EXPECT_EQ( 64, c.diff(y)(2, 3, 4));
    EXPECT_EQ(  0, c.diff(z)(2, 3, 4));

    EXPECT_EQ(160, c.diff(x, y)(2, 3, 4));
    EXPECT_EQ(160, c.diff(y, x)(2, 3, 4));
}

TEST(chain, constant_folding) {
    nabla::expr::constant c(2);

    nabla::expr::variable<0> x;

    auto s = nabla::expr::impl::make_chain(c, x, 2 * x);

    EXPECT_EQ(2, s());
    EXPECT_EQ(0, s.diff(x)());

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s          )>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s.diff<0>())>::value));
}
