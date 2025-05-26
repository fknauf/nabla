#include <nabla/unary_functions.hh>
#include <gtest/gtest.h>

TEST(trigonometry, test_sin) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = sin(2 * x + 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,     std::sin(2 * p(0) + 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 2 * std::cos(2 * p(0) + 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 4 * std::cos(2 * p(0) + 4 * p(1)));

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(trigonometry, test_cos) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = cos(2 * x + 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,      std::cos(2 * p(0) + 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 2 * -std::sin(2 * p(0) + 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 4 * -std::sin(2 * p(0) + 4 * p(1)));

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(trigonometry, test_tan) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = tan(2 * x - 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,               std::tan(2 * p(0) - 4 * p(1))    );
    EXPECT_DOUBLE_EQ(s.diff(x)(p),  2 / std::pow(std::cos(4 * p(1) - 2 * p(0)), 2));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), -4 / std::pow(std::cos(4 * p(1) - 2 * p(0)), 2));

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(trigonometry, test_asin) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = asin(x * x + y);

    nabla::vector<2> p { 0.7, 0.1 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,                         std::asin(p(0) * p(0) + p(1))    );
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 2 * p(0) / std::sqrt(1 - std::pow(p(0) * p(0) + p(1), 2)));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 1        / std::sqrt(1 - std::pow(p(0) * p(0) + p(1), 2)));

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(trigonometry, test_acos) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = acos(x * x + y);

    nabla::vector<2> p { 0.7, 0.1 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,                          std::acos(p(0) * p(0) + p(1))    );
    EXPECT_DOUBLE_EQ(s.diff(x)(p), -2 * p(0) / std::sqrt(1 - std::pow(p(0) * p(0) + p(1), 2)));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), -1        / std::sqrt(1 - std::pow(p(0) * p(0) + p(1), 2)));

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(trigonometry, test_atan) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = atan(x * x + y);

    nabla::vector<2> p { 0.7, 0.1 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           ,                std::atan(p(0) * p(0) + p(1))    );
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 2 * p(0) / (1 + std::pow(p(0) * p(0) + p(1), 2)));
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 1        / (1 + std::pow(p(0) * p(0) + p(1), 2)));

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(trigonometry, constant_folding) {
    nabla::expr::constant c(0.5);

    EXPECT_DOUBLE_EQ(std::sin (c.value()), sin (c)());
    EXPECT_DOUBLE_EQ(std::cos (c.value()), cos (c)());
    EXPECT_DOUBLE_EQ(std::tan (c.value()), tan (c)());
    EXPECT_DOUBLE_EQ(std::acos(c.value()), acos(c)());
    EXPECT_DOUBLE_EQ(std::asin(c.value()), asin(c)());
    EXPECT_DOUBLE_EQ(std::atan(c.value()), atan(c)());

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(sin (c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(cos (c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(tan (c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(acos(c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(asin(c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(atan(c))>::value));
}

