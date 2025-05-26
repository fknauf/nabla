#include <nabla/nabla.hh>
#include <gtest/gtest.h>

TEST(explog, test_exp) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = exp(2 * x + 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           , std::exp(2 * p(0) + 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 2 * r                        );
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 4 * r                        );

    EXPECT_DOUBLE_EQ(s        (p(0), p(1)), s        (p));
    EXPECT_DOUBLE_EQ(s.diff(x)(p(0), p(1)), s.diff(x)(p));
    EXPECT_DOUBLE_EQ(s.diff(y)(p(0), p(1)), s.diff(y)(p));
}

TEST(explog, test_log) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = log(2 * x + 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           , std::log(2 * p(0) + 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 2 / (2 * p(0) + 4 * p(1))    );
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 4 / (2 * p(0) + 4 * p(1))    );

    EXPECT_DOUBLE_EQ(s        (p(0), p(1)), s        (p));
    EXPECT_DOUBLE_EQ(s.diff(x)(p(0), p(1)), s.diff(x)(p));
    EXPECT_DOUBLE_EQ(s.diff(y)(p(0), p(1)), s.diff(y)(p));
}

TEST(explog, test_exp2) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = exp2(x * x - 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           , std::pow(2, p(0) * p(0) - 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(x)(p),  2 * M_LN2 * p(0) * r              );
    EXPECT_DOUBLE_EQ(s.diff(y)(p), -4 * M_LN2        * r              );

    EXPECT_DOUBLE_EQ(s        (p(0), p(1)), s        (p));
    EXPECT_DOUBLE_EQ(s.diff(x)(p(0), p(1)), s.diff(x)(p));
    EXPECT_DOUBLE_EQ(s.diff(y)(p(0), p(1)), s.diff(y)(p));
}

TEST(explog, test_expm1) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = expm1(x * x - 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           , std::expm1(p(0) * p(0) - 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(x)(p),  2 * p(0) * (r + 1)               );
    EXPECT_DOUBLE_EQ(s.diff(y)(p), -4        * (r + 1)               );

    EXPECT_DOUBLE_EQ(s        (p(0), p(1)), s        (p));
    EXPECT_DOUBLE_EQ(s.diff(x)(p(0), p(1)), s.diff(x)(p));
    EXPECT_DOUBLE_EQ(s.diff(y)(p(0), p(1)), s.diff(y)(p));
}

TEST(explog, test_log10) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = log10(x * x - 4 * y);

    nabla::vector<2> p { 3.0, 1.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,             std::log10(p(0) * p(0) - 4 * p(1)) );
    EXPECT_DOUBLE_EQ(s.diff(x)(p),  2 * p(0) / (M_LN10 * (p(0) * p(0) - 4 * p(1))));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), -4        / (M_LN10 * (p(0) * p(0) - 4 * p(1))));

    EXPECT_DOUBLE_EQ(s        (p(0), p(1)), s        (p));
    EXPECT_DOUBLE_EQ(s.diff(x)(p(0), p(1)), s.diff(x)(p));
    EXPECT_DOUBLE_EQ(s.diff(y)(p(0), p(1)), s.diff(y)(p));
}

TEST(explog, test_log2) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = log2(x * x - 4 * y);

    nabla::vector<2> p { 3.0, 1.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,             std::log2(p(0) * p(0) - 4 * p(1)) );
    EXPECT_DOUBLE_EQ(s.diff(x)(p),  2 * p(0) / (M_LN2 * (p(0) * p(0) - 4 * p(1))));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), -4        / (M_LN2 * (p(0) * p(0) - 4 * p(1))));

    EXPECT_DOUBLE_EQ(s        (p(0), p(1)), s        (p));
    EXPECT_DOUBLE_EQ(s.diff(x)(p(0), p(1)), s.diff(x)(p));
    EXPECT_DOUBLE_EQ(s.diff(y)(p(0), p(1)), s.diff(y)(p));
}

TEST(explog, test_log1p) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = log1p(x * x - 4 * y);

    nabla::vector<2> p { 3.0, 1.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,   std::log1p(p(0) * p(0) - 4 * p(1))    );
    EXPECT_DOUBLE_EQ(s.diff(x)(p),  2 * p(0) / (p(0) * p(0) - 4 * p(1) + 1));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), -4        / (p(0) * p(0) - 4 * p(1) + 1));

    EXPECT_DOUBLE_EQ(s        (p(0), p(1)), s        (p));
    EXPECT_DOUBLE_EQ(s.diff(x)(p(0), p(1)), s.diff(x)(p));
    EXPECT_DOUBLE_EQ(s.diff(y)(p(0), p(1)), s.diff(y)(p));
}

TEST(explog, constant_folding) {
    nabla::expr::constant c(2);

    EXPECT_DOUBLE_EQ(std::exp  (c.value()), exp  (c)());
    EXPECT_DOUBLE_EQ(std::log  (c.value()), log  (c)());
    EXPECT_DOUBLE_EQ(std::exp2 (c.value()), exp2 (c)());
    EXPECT_DOUBLE_EQ(std::expm1(c.value()), expm1(c)());
    EXPECT_DOUBLE_EQ(std::log10(c.value()), log10(c)());
    EXPECT_DOUBLE_EQ(std::log2 (c.value()), log2 (c)());
    EXPECT_DOUBLE_EQ(std::log1p(c.value()), log1p(c)());

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(exp  (c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(log  (c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(exp2 (c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(expm1(c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(log10(c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(log2 (c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(log1p(c))>::value));
}

