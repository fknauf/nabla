#include <nabla/division.hpp>
#include <nabla/product.hpp>

#include <gtest/gtest.h>

TEST(division, var_div_num)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = x / 2;
    
    nabla::vector<3> vars = nabla::make_vector(2, 3, 4);

    EXPECT_EQ(1  , f(vars));

    EXPECT_EQ(0.5, f.diff(x)(vars));
    EXPECT_EQ(0  , f.diff(y)(vars));

    EXPECT_EQ(0.5, f.diff<0>()(vars));
    EXPECT_EQ(0  , f.diff<1>()(vars));
    
    EXPECT_EQ(0  , f.diff(x, x)(vars));
    EXPECT_EQ(0  , f.diff(x, y)(vars));
    EXPECT_EQ(0  , f.diff(y, x)(vars));
    EXPECT_EQ(0  , f.diff(y, y)(vars));
}

TEST(division, num_div_var)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto f = 2 / x;
    
    nabla::vector<3> vars = nabla::make_vector(2, 3, 4);

    EXPECT_EQ( 1   , f(vars));

    EXPECT_EQ(-0.5 , f.diff(x)(vars));
    EXPECT_EQ( 0   , f.diff(y)(vars));

    EXPECT_EQ(-0.5 , f.diff<0>()(vars));
    EXPECT_EQ( 0   , f.diff<1>()(vars));
    
    EXPECT_EQ( 0.5 , f.diff(x, x)(vars));
    EXPECT_EQ( 0   , f.diff(x, y)(vars));
    EXPECT_EQ( 0   , f.diff(y, x)(vars));
    EXPECT_EQ( 0   , f.diff(y, y)(vars));

    EXPECT_EQ(-0.75, f.diff(x, x, x)(vars));
}

TEST(division, var_div_var)  {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    auto f = x / z;
    
    nabla::vector<3> vars = nabla::make_vector(2, 3, 4);

    EXPECT_EQ(0.5 , f(vars));

    EXPECT_EQ( 0.25 , f.diff(x)(vars));
    EXPECT_EQ( 0    , f.diff(y)(vars));
    EXPECT_EQ(-0.125, f.diff(z)(vars));

    EXPECT_EQ( 0.25 , f.diff<0>()(vars));
    EXPECT_EQ( 0    , f.diff<1>()(vars));
    EXPECT_EQ(-0.125, f.diff<2>()(vars));
    
    EXPECT_EQ( 0    , f.diff(x, x)(vars));
    EXPECT_EQ( 0    , f.diff(x, y)(vars));
    EXPECT_EQ( 0    , f.diff(y, x)(vars));
    EXPECT_EQ( 0    , f.diff(y, y)(vars));

    EXPECT_EQ( 0.0625   , f.diff(z, z      )(vars));
    EXPECT_EQ( 0.03125  , f.diff(z, z, x   )(vars));
    EXPECT_EQ(-0.0234375, f.diff(z, z, x, z)(vars));
}

TEST(division, simple) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = x / 2;

    nabla::vector<2> values = nabla::make_vector(3.0, 4.0);

    auto r = s(values);

    EXPECT_EQ(1.5, r);
    EXPECT_EQ(0.5, s.diff(x)(values));
    EXPECT_EQ(0.0, s.diff(y)(values));
}

TEST(division, simple_inv) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = 4.5 / x;

    nabla::vector<2> values = nabla::make_vector(3.0, 4.0);

    auto r = s(values);

    EXPECT_EQ( 1.5, r);
    EXPECT_EQ(-0.5, s.diff(x)(values));
    EXPECT_EQ( 0.0, s.diff(y)(values));
}

TEST(division, twovar) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = x / y;

    nabla::vector<2> values = nabla::make_vector(3.0, 4.0);

    auto r = s(values);

    EXPECT_EQ( 0.75  , r);
    EXPECT_EQ( 0.25  , s.diff(x)(values));
    EXPECT_EQ(-0.1875, s.diff(y)(values));
}

TEST(division, twovar_plus_constant) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = x / y / 0.5;

    nabla::vector<2> values = nabla::make_vector(3.0, 4.0);

    auto r = s(values);

    EXPECT_EQ( 1.5  , r);
    EXPECT_EQ( 0.5  , s.diff(x)(values));
    EXPECT_EQ(-0.375, s.diff(y)(values));
}

TEST(division, params_expanded) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = x / y / 0.5;

    auto r = s(3, 4);

    EXPECT_EQ( 1.5  , r);
    EXPECT_EQ( 0.5  , s.diff(x)(3, 4));
    EXPECT_EQ(-0.375, s.diff(y)(3, 4));
}

TEST(division, constant_folding) {
    nabla::expr::constant c(5);

    auto s = c / 2;

    EXPECT_EQ(2.5, s());
    EXPECT_EQ(0  , s.diff<0>()());

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s          )>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(s.diff<0>())>::value));
}

TEST(division, mixed_deep_constant_folding) {
    using nabla::expr::division;
    using nabla::expr::product;
    using nabla::expr::constant;

    auto x = nabla::expr::variable<0>{};
    auto y = nabla::expr::variable<1>{};

    auto f1 = (4 * x) / (2 * y);
    auto f2 = (4 * x) / (y * 2);
    auto f3 = (x * 4) / (2 * y);
    auto f4 = (x * 4) / (y * 2);

    EXPECT_EQ(1, f1(1, 2));
    EXPECT_EQ(1, f2(1, 2));
    EXPECT_EQ(1, f3(1, 2));
    EXPECT_EQ(1, f4(1, 2));

    EXPECT_TRUE((std::is_same_v<division<product<constant, decltype(x)>, decltype(y)>, decltype(f1)>));
    EXPECT_TRUE((std::is_same_v<division<product<constant, decltype(x)>, decltype(y)>, decltype(f2)>));
    EXPECT_TRUE((std::is_same_v<division<product<decltype(x), constant>, decltype(y)>, decltype(f3)>));
    EXPECT_TRUE((std::is_same_v<division<product<decltype(x), constant>, decltype(y)>, decltype(f4)>));

    auto g1 = (4 / x) / (2 * y);
    auto g2 = (4 / x) / (y * 2);
    auto g3 = (x / 4) / (2 * y);
    auto g4 = (x / 4) / (y * 2);

    EXPECT_EQ(1, g1(1, 2));
    EXPECT_EQ(1, g2(1, 2));
    EXPECT_EQ(0.0625, g3(1, 2));
    EXPECT_EQ(0.0625, g4(1, 2));

    EXPECT_TRUE((std::is_same_v<division<constant, product<decltype(x), decltype(y)>>, decltype(g1)>));
    EXPECT_TRUE((std::is_same_v<division<constant, product<decltype(x), decltype(y)>>, decltype(g2)>));
    EXPECT_TRUE((std::is_same_v<division<decltype(x), product<constant, decltype(y)>>, decltype(g3)>));
    EXPECT_TRUE((std::is_same_v<division<decltype(x), product<constant, decltype(y)>>, decltype(g4)>));

    auto h1 = (4 * x) / (2 / y);
    auto h2 = (4 * x) / (y / 2);
    auto h3 = (x * 4) / (2 / y);
    auto h4 = (x * 4) / (y / 2);

    EXPECT_EQ(4, h1(1, 2));
    EXPECT_EQ(4, h2(1, 2));
    EXPECT_EQ(4, h3(1, 2));
    EXPECT_EQ(4, h4(1, 2));

    EXPECT_TRUE((std::is_same_v<product <product<constant, decltype(x)>, decltype(y)>, decltype(h1)>));
    EXPECT_TRUE((std::is_same_v<division<product<constant, decltype(x)>, decltype(y)>, decltype(h2)>));
    EXPECT_TRUE((std::is_same_v<product <product<decltype(x), constant>, decltype(y)>, decltype(h3)>));
    EXPECT_TRUE((std::is_same_v<division<product<decltype(x), constant>, decltype(y)>, decltype(h4)>));

    auto i1 = (4 / x) / (2 / y);
    auto i2 = (4 / x) / (y / 2);
    auto i3 = (x / 4) / (2 / y);
    auto i4 = (x / 4) / (y / 2);

    EXPECT_EQ(4, i1(1, 2));
    EXPECT_EQ(4, i2(1, 2));
    EXPECT_EQ(0.25, i3(1, 2));
    EXPECT_EQ(0.25, i4(1, 2));

    EXPECT_TRUE((std::is_same_v<division<product<constant, decltype(y)>, decltype(x)>, decltype(i1)>));
    EXPECT_TRUE((std::is_same_v<division<constant, product<decltype(x), decltype(y)>>, decltype(i2)>));
    EXPECT_TRUE((std::is_same_v<division<product<decltype(x), decltype(y)>, constant>, decltype(i3)>));
    EXPECT_TRUE((std::is_same_v<division<decltype(x), product<constant, decltype(y)>>, decltype(i4)>));
}
