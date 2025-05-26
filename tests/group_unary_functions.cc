#include <nabla/nabla.hh>
#include <gtest/gtest.h>

TEST(unary_functions, test_sqrt) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = sqrt(2 * x + 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           , std::sqrt(2 * p(0) + 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 1 / r                         );
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 2 / r                         );

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(unary_functions, test_cbrt) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = cbrt(2 * x + 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           , std::cbrt(2 * p(0) + 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 2 / (3 * r * r)               );
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 4 / (3 * r * r)               );

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(unary_functions, test_cancellation) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = exp(log(2 * x + 4 * y));

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           , 2 * p(0) + 4 * p(1));
    EXPECT_DOUBLE_EQ(s.diff(x)(p), 2                  );
    EXPECT_DOUBLE_EQ(s.diff(y)(p), 4                  );

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(unary_functions, test_combo) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s = exp(sin(x * x) + cos(y * y));

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           , std::exp(std::sin(p(0) * p(0)) + std::cos(p(1) * p(1))));
    EXPECT_DOUBLE_EQ(s.diff(x)(p),  2 * p(0) * std::cos(p(0) * p(0)) * r                  );
    EXPECT_DOUBLE_EQ(s.diff(y)(p), -2 * p(1) * std::sin(p(1) * p(1)) * r                  );

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(unary_functions, test_erf) {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto cdf = erf(x - y);

    nabla::vector<2> p(0.2, 0.5);

    auto result = cdf(p);

    EXPECT_DOUBLE_EQ(std::erf(p(0) - p(1)), result);
    EXPECT_DOUBLE_EQ(  M_2_SQRTPI * std::exp(-std::pow(p(0) - p(1), 2)), cdf.diff(x)(p));
    EXPECT_DOUBLE_EQ(- M_2_SQRTPI * std::exp(-std::pow(p(0) - p(1), 2)), cdf.diff(y)(p));

    EXPECT_DOUBLE_EQ(cdf              (p(0), p(1)), cdf              (p));
    EXPECT_DOUBLE_EQ(cdf.diff(x      )(p(0), p(1)), cdf.diff(x      )(p));
    EXPECT_DOUBLE_EQ(cdf.diff(y      )(p(0), p(1)), cdf.diff(y      )(p));
    EXPECT_DOUBLE_EQ(cdf.diff(x, x   )(p(0), p(1)), cdf.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(cdf.diff(x, y   )(p(0), p(1)), cdf.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(cdf.diff(x, x, x)(p(0), p(1)), cdf.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(cdf.diff(x, x, y)(p(0), p(1)), cdf.diff(x, x, y)(p));
}

TEST(unary_functions, test_erfc) {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;

    auto cdf = erfc(x * x - 4 * y);

    nabla::vector<2> p(0.2, 0.5);

    auto result = cdf(p);

    EXPECT_DOUBLE_EQ(std::erfc(p(0) * p(0) - 4 * p(1)), result);
    EXPECT_DOUBLE_EQ(-2 * M_2_SQRTPI * p(0) * std::exp(-std::pow(p(0) * p(0) - 4 * p(1), 2)), cdf.diff(x)(p));
    EXPECT_DOUBLE_EQ( 4 * M_2_SQRTPI        * std::exp(-std::pow(p(0) * p(0) - 4 * p(1), 2)), cdf.diff(y)(p));

    EXPECT_DOUBLE_EQ(cdf              (p(0), p(1)), cdf              (p));
    EXPECT_DOUBLE_EQ(cdf.diff(x      )(p(0), p(1)), cdf.diff(x      )(p));
    EXPECT_DOUBLE_EQ(cdf.diff(y      )(p(0), p(1)), cdf.diff(y      )(p));
    EXPECT_DOUBLE_EQ(cdf.diff(x, x   )(p(0), p(1)), cdf.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(cdf.diff(x, y   )(p(0), p(1)), cdf.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(cdf.diff(x, x, x)(p(0), p(1)), cdf.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(cdf.diff(x, x, y)(p(0), p(1)), cdf.diff(x, x, y)(p));
}

TEST(unary_functions, phi) {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> mu;
    nabla::expr::variable<2> sigma;

    auto cdf = Phi((x - mu) / sigma);

    nabla::vector<3> p(0.2, 0.5, 0.4);

    auto result = cdf(p);

    EXPECT_NEAR( 0.2266273523768682, result            , 1e-10);
    EXPECT_NEAR( 0.7528435803870109, cdf.diff(x    )(p), 1e-10);
    EXPECT_NEAR(-0.7528435803870109, cdf.diff(mu   )(p), 1e-10);
    EXPECT_NEAR( 0.564632685290258 , cdf.diff(sigma)(p), 1e-10);

    EXPECT_DOUBLE_EQ(cdf               (p(0), p(1), p(2)), cdf               (p));
    EXPECT_DOUBLE_EQ(cdf.diff(x       )(p(0), p(1), p(2)), cdf.diff(x       )(p));
    EXPECT_DOUBLE_EQ(cdf.diff(mu      )(p(0), p(1), p(2)), cdf.diff(mu      )(p));
    EXPECT_DOUBLE_EQ(cdf.diff(x, x    )(p(0), p(1), p(2)), cdf.diff(x, x    )(p));
    EXPECT_DOUBLE_EQ(cdf.diff(x, mu   )(p(0), p(1), p(2)), cdf.diff(x, mu   )(p));
    EXPECT_DOUBLE_EQ(cdf.diff(x, x, x )(p(0), p(1), p(2)), cdf.diff(x, x, x )(p));
    EXPECT_DOUBLE_EQ(cdf.diff(x, x, mu)(p(0), p(1), p(2)), cdf.diff(x, x, mu)(p));
}

TEST(unary_functions, blackscholes) {
    nabla::expr::variable<0> S;
    nabla::expr::variable<1> T;
    nabla::expr::variable<2> sigma;
    nabla::expr::variable<3> r;

    double K = 1.1;
    double q = 0.01;

    auto callbsm =
        exp(-q * T) * S * gausscdf(log(S / K), (q - r - sigma * sigma / 2) * T, sigma * sqrt(T))
      - exp(-r * T) * K * gausscdf(log(S / K), (q - r + sigma * sigma / 2) * T, sigma * sqrt(T));

    auto delta = callbsm.diff(S);
    auto gamma = delta  .diff(S);
    auto theta = callbsm.diff(T);
    auto vega  = callbsm.diff(sigma);
    auto rho   = callbsm.diff(r);

    nabla::vector<4> p(1.02, 91. / 365, 0.4, 0.02);

    auto result = callbsm(p);

    EXPECT_NEAR(0.0509966634606674, result  , 1e-10);
    EXPECT_NEAR(0.394247053086975 , delta(p), 1e-10);
    EXPECT_NEAR(1.8856533851377741, gamma(p), 1e-10);
    EXPECT_NEAR(0.1599480892240612, theta(p), 1e-10);
    EXPECT_NEAR(0.195645889482365 , vega (p), 1e-10);
    EXPECT_NEAR(0.0875433290208555, rho  (p), 1e-10);
}

TEST(unary_functions, test_fabs) {
    auto x = nabla::expr::variable<0>();
    auto y = nabla::expr::variable<1>();

    auto s  = fabs(x * x + 4 * y);
    auto s2 = fabs(x * x - 4 * y);

    nabla::vector<2> p { 2.0, 5.0 };

    auto r = s(p);

    EXPECT_DOUBLE_EQ(r           , std::fabs(p(0) * p(0) + 4 * p(1)));
    EXPECT_DOUBLE_EQ(s.diff(x)(p),  2 * p(0)                        );
    EXPECT_DOUBLE_EQ(s.diff(y)(p),  4                               );

    r = s2(p);

    EXPECT_DOUBLE_EQ(r            , std::fabs(p(0) * p(0) - 4 * p(1)));
    EXPECT_DOUBLE_EQ(s2.diff(x)(p), -2 * p(0)                        );
    EXPECT_DOUBLE_EQ(s2.diff(y)(p),  4                               );

    EXPECT_DOUBLE_EQ(s              (p(0), p(1)), s              (p));
    EXPECT_DOUBLE_EQ(s.diff(x      )(p(0), p(1)), s.diff(x      )(p));
    EXPECT_DOUBLE_EQ(s.diff(y      )(p(0), p(1)), s.diff(y      )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p));
    EXPECT_DOUBLE_EQ(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p));
}

TEST(unary_functions, blackscholes_params_expanded) {
    nabla::expr::variable<0> S;
    nabla::expr::variable<1> T;
    nabla::expr::variable<2> sigma;
    nabla::expr::variable<3> r;

    double K = 1.1;
    double q = 0.01;

    auto callbsm =
        exp(-q * T) * S * gausscdf(log(S / K), (q - r - sigma * sigma / 2) * T, sigma * sqrt(T))
      - exp(-r * T) * K * gausscdf(log(S / K), (q - r + sigma * sigma / 2) * T, sigma * sqrt(T));

    auto delta = callbsm.diff(S);
    auto gamma = delta.diff(S);
    auto theta = callbsm.diff(T);
    auto vega  = callbsm.diff(sigma);
    auto rho   = callbsm.diff(r);

    double vS     = 1.02;
    double vT     = 91. / 365;
    double vsigma = 0.4;
    double vr     = 0.02;
    
    EXPECT_NEAR(0.0509966634606674, callbsm(vS, vT, vsigma, vr), 1e-10);
    EXPECT_NEAR(0.394247053086975 , delta  (vS, vT, vsigma, vr), 1e-10);
    EXPECT_NEAR(1.8856533851377741, gamma  (vS, vT, vsigma, vr), 1e-10);
    EXPECT_NEAR(0.1599480892240612, theta  (vS, vT, vsigma, vr), 1e-10);
    EXPECT_NEAR(0.195645889482365 , vega   (vS, vT, vsigma, vr), 1e-10);
    EXPECT_NEAR(0.0875433290208555, rho    (vS, vT, vsigma, vr), 1e-10);
}

TEST(unary_functions, constant_folding) {
    nabla::expr::constant c(2);

    EXPECT_DOUBLE_EQ(std::sqrt(c.value()), sqrt(c)());
    EXPECT_DOUBLE_EQ(std::cbrt(c.value()), cbrt(c)());
    EXPECT_DOUBLE_EQ(std::erf (c.value()), erf (c)());
    EXPECT_DOUBLE_EQ(std::erfc(c.value()), erfc(c)());
    EXPECT_DOUBLE_EQ(0.5 * (1 + std::erf(c.value() / M_SQRT2)), Phi(c)());

    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(sqrt(c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(cbrt(c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(erf (c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(erfc(c))>::value));
    EXPECT_TRUE((std::is_same<nabla::expr::constant, decltype(Phi (c))>::value));
}

