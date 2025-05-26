#include <nabla/chain.hh>
#include <nabla/hypot.hh>

#include <gtest/gtest.h>

TEST(hypot, n1_veclength) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();
    auto z = nabla::expr::variable<2>();

    auto s = hypot(x * y, x * z, 2, y * z);

    nabla::vector<4> p(1.0, -3.0, 2.0, 5.0);

    auto r = s(p);

    double exv = std::sqrt(
        std::pow(p(0) * p(1), 2)
        + std::pow(p(0) * p(2), 2)
        + std::pow(2, 2)
        + std::pow(p(1) * p(2), 2)
    );

    double dx = p(0) * (p(1) * p(1) + p(2) * p(2)) / exv;
    double dy = p(1) * (p(0) * p(0) + p(2) * p(2)) / exv;
    double dz = p(2) * (p(0) * p(0) + p(1) * p(1)) / exv;

    EXPECT_DOUBLE_EQ(exv, r);

    EXPECT_DOUBLE_EQ(dx, s.diff(x)(p));
    EXPECT_DOUBLE_EQ(dy, s.diff(y)(p));
    EXPECT_DOUBLE_EQ(dz, s.diff(z)(p));
}

TEST(hypot, starts_with_constant) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();
    auto z = nabla::expr::variable<2>();

    auto s = hypot(2, x * z, 2, y * z);

    nabla::vector<4> p(1.0, -3.0, 2.0, 5.0);

    auto r = s(p);

    double exv = std::sqrt(
        std::pow(2, 2)
        + std::pow(p(0) * p(2), 2)
        + std::pow(2, 2)
        + std::pow(p(1) * p(2), 2)
    );

    double dx = p(0) * (p(2) * p(2)) / exv;
    double dy = p(1) * (p(2) * p(2)) / exv;
    double dz = p(2) * (p(0) * p(0) + p(1) * p(1)) / exv;

    EXPECT_DOUBLE_EQ(exv, r);

    EXPECT_DOUBLE_EQ(dx, s.diff(x)(p));
    EXPECT_DOUBLE_EQ(dy, s.diff(y)(p));
    EXPECT_DOUBLE_EQ(dz, s.diff(z)(p));
}

TEST(hypot, ends_with_constant) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();
    auto z = nabla::expr::variable<2>();

    auto s = hypot(x * z, 2, y * z, 2);

    nabla::vector<4> p(1.0, -3.0, 2.0, 5.0);

    auto r = s(p);

    double exv = std::sqrt(
        std::pow(2, 2)
        + std::pow(p(0) * p(2), 2)
        + std::pow(2, 2)
        + std::pow(p(1) * p(2), 2)
    );

    double dx = p(0) * (p(2) * p(2)) / exv;
    double dy = p(1) * (p(2) * p(2)) / exv;
    double dz = p(2) * (p(0) * p(0) + p(1) * p(1)) / exv;

    EXPECT_DOUBLE_EQ(exv, r);

    EXPECT_DOUBLE_EQ(dx, s.diff(x)(p));
    EXPECT_DOUBLE_EQ(dy, s.diff(y)(p));
    EXPECT_DOUBLE_EQ(dz, s.diff(z)(p));
}

TEST(hypot, all_constant) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();
    auto z = nabla::expr::variable<2>();

    nabla::expr::constant one  (1);
    nabla::expr::constant two  (2);
    nabla::expr::constant three(3);
    nabla::expr::constant four (4);

    auto s = nabla::expr::hypot(one, two, three, four);

    nabla::vector<4> p(1.0, -3.0, 2.0, 5.0);

    auto r = s(p);

    double exv = std::sqrt(1 + 4 + 9 + 16);

    double dx = 0;
    double dy = 0;
    double dz = 0;

    EXPECT_DOUBLE_EQ(exv, r);

    EXPECT_DOUBLE_EQ(dx, s.diff(x)(p));
    EXPECT_DOUBLE_EQ(dy, s.diff(y)(p));
    EXPECT_DOUBLE_EQ(dz, s.diff(z)(p));

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s        )>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s.diff(x))>::value));
}

