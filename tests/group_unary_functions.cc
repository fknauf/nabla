#include <nabla/nabla.hh>
#include <boost/test/unit_test.hpp>

namespace {
  double epsilon = 1e-10;
}

BOOST_AUTO_TEST_SUITE( unary_functions )

BOOST_AUTO_TEST_CASE( test_sqrt ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = sqrt(2 * x + 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           , std::sqrt(2 * p(0) + 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 1 / r                         , epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 2 / r                         , epsilon);
}

BOOST_AUTO_TEST_CASE( test_cbrt ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = cbrt(2 * x + 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           , std::cbrt(2 * p(0) + 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 2 / (3 * r * r)               , epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 4 / (3 * r * r)               , epsilon);
}

BOOST_AUTO_TEST_CASE( test_cancellation ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = exp(log(2 * x + 4 * y));

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           , 2 * p(0) + 4 * p(1), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 2                  , epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 4                  , epsilon);
}

BOOST_AUTO_TEST_CASE( test_combo ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = exp(sin(x * x) + cos(y * y));

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           , std::exp(std::sin(p(0) * p(0)) + std::cos(p(1) * p(1))), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p),  2 * p(0) * std::cos(p(0) * p(0)) * r                  , epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), -2 * p(1) * std::sin(p(1) * p(1)) * r                  , epsilon);
}

BOOST_AUTO_TEST_CASE( test_erf ) {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto cdf = erf(x - y);

  nabla::vector<2> params(0.2, 0.5);

  auto result = cdf(params);

  BOOST_CHECK_CLOSE(std::erf(params(0) - params(1)), result, epsilon);
  BOOST_CHECK_CLOSE(  M_2_SQRTPI * std::exp(-std::pow(params(0) - params(1), 2)), cdf.diff(x)(params), epsilon);
  BOOST_CHECK_CLOSE(- M_2_SQRTPI * std::exp(-std::pow(params(0) - params(1), 2)), cdf.diff(y)(params), epsilon);
}

BOOST_AUTO_TEST_CASE( test_erfc ) {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto cdf = erfc(x * x - 4 * y);

  nabla::vector<2> p(0.2, 0.5);

  auto result = cdf(p);

  BOOST_CHECK_CLOSE(std::erfc(p(0) * p(0) - 4 * p(1)), result, epsilon);
  BOOST_CHECK_CLOSE(-2 * M_2_SQRTPI * p(0) * std::exp(-std::pow(p(0) * p(0) - 4 * p(1), 2)), cdf.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE( 4 * M_2_SQRTPI        * std::exp(-std::pow(p(0) * p(0) - 4 * p(1), 2)), cdf.diff(y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( phi ) {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> mu;
  nabla::expr::variable<2> sigma;

  auto cdf = Phi((x - mu) / sigma);

  nabla::vector<3> params(0.2, 0.5, 0.4);

  auto result = cdf(params);

  BOOST_CHECK_CLOSE( 0.2266273523768682, result                 , epsilon);
  BOOST_CHECK_CLOSE( 0.7528435803870109, cdf.diff(x    )(params), epsilon);
  BOOST_CHECK_CLOSE(-0.7528435803870109, cdf.diff(mu   )(params), epsilon);
  BOOST_CHECK_CLOSE( 0.564632685290258 , cdf.diff(sigma)(params), epsilon);
}

BOOST_AUTO_TEST_CASE( blackscholes ) {
  nabla::expr::variable<0> S;
  nabla::expr::variable<1> T;
  nabla::expr::variable<2> sigma;
  nabla::expr::variable<3> r;

  double K = 1.1;
  double q = 0.01;

  auto callbsm =
      exp(-q * T) * S * gausscdf(log(S / K), (q - r - sigma * sigma / 2) * T, sigma * sqrt(T))
    - exp(-r * T) * K * gausscdf(log(S / K), (q - r + sigma * sigma / 2) * T, sigma * sqrt(T));

  nabla::vector<4> params(1.02, 91. / 365, 0.4, 0.02);

  auto result = callbsm(params);

  BOOST_CHECK_CLOSE(0.0509966634606674, result                     , epsilon);
  BOOST_CHECK_CLOSE(0.394247053086975 , callbsm.diff(S    )(params), epsilon);
  BOOST_CHECK_CLOSE(0.1599480892240612, callbsm.diff(T    )(params), epsilon);
  BOOST_CHECK_CLOSE(0.195645889482365 , callbsm.diff(sigma)(params), epsilon);
  BOOST_CHECK_CLOSE(0.0875433290208555, callbsm.diff(r    )(params), epsilon);
}

BOOST_AUTO_TEST_CASE( test_fabs ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s  = fabs(x * x + 4 * y);
  auto s2 = fabs(x * x - 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           , std::fabs(p(0) * p(0) + 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p),  2 * p(0)                        , epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p),  4                               , epsilon);

  r = s2(p);

  BOOST_CHECK_CLOSE(r            , std::fabs(p(0) * p(0) - 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s2.diff(x)(p), -2 * p(0)                        , epsilon);
  BOOST_CHECK_CLOSE(s2.diff(y)(p),  4                               , epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
