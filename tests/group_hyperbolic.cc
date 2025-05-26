#include <nabla/unary_functions.hh>
#include <gtest/gtest.h>

TEST(hyperbolic, test_sinh) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = sinh(x * x + 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,            std::sinh(p(0) * p(0) + 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 2 * p(0) * std::cosh(p(0) * p(0) + 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 4 *        std::cosh(p(0) * p(0) + 4 * p(1)));

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(hyperbolic, test_cosh) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = cosh(x * x + 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,            std::cosh(p(0) * p(0) + 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 2 * p(0) * std::sinh(p(0) * p(0) + 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 4 *        std::sinh(p(0) * p(0) + 4 * p(1)));

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(hyperbolic, test_tanh) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = tanh(x * x + 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,                     std::tanh(p(0) * p(0) + 4 * p(1))    );
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 2 * p(0) / std::pow(std::cosh(p(0) * p(0) + 4 * p(1)), 2));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 4        / std::pow(std::cosh(p(0) * p(0) + 4 * p(1)), 2));

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(hyperbolic, test_asinh) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = asinh(x * x + 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,                        std::asinh(p(0) * p(0) + 4 * p(1))    );
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 2 * p(0) / std::sqrt(1 + std::pow(p(0) * p(0) + 4 * p(1), 2)));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 4        / std::sqrt(1 + std::pow(p(0) * p(0) + 4 * p(1), 2)));

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(hyperbolic, test_acosh) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = acosh(x * x + 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,                    std::acosh(p(0) * p(0) + 4 * p(1))        );
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 2 * p(0) / std::sqrt(std::pow(p(0) * p(0) + 4 * p(1), 2) - 1));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 4        / std::sqrt(std::pow(p(0) * p(0) + 4 * p(1), 2) - 1));

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(hyperbolic, test_atanh) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = atanh(x * x + 4 * y);

    nabla::vector<2> p { 2.0, -1.2 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,               std::atanh(p(0) * p(0) + 4 * p(1))    );
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 2 * p(0) / (1 - std::pow(p(0) * p(0) + 4 * p(1), 2)));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 4        / (1 - std::pow(p(0) * p(0) + 4 * p(1), 2)));

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(hyperbolic, constant_folding) {
    nabla::expr::constant half(0.5);
    nabla::expr::constant two (2.0);

    EXPECT_DOUBLE_EQ(std::sinh (two .value()), sinh (two )());
    EXPECT_DOUBLE_EQ(std::cosh (two .value()), cosh (two )());
    EXPECT_DOUBLE_EQ(std::tanh (two .value()), tanh (two )());
    EXPECT_DOUBLE_EQ(std::asinh(two .value()), asinh(two )());
    EXPECT_DOUBLE_EQ(std::acosh(two .value()), acosh(two )());
    EXPECT_DOUBLE_EQ(std::atanh(half.value()), atanh(half)());

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(sinh (two ))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(cosh (two ))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(tanh (two ))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(asinh(two ))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(acosh(two ))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(atanh(half))>::value));
}

