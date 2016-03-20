#include <nabla/unary_functions.hh>
#include <boost/test/unit_test.hpp>

namespace {
  double epsilon = 1e-10;
}

BOOST_AUTO_TEST_SUITE( hyperbolic )

BOOST_AUTO_TEST_CASE( test_sinh ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = sinh(x * x + 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,            std::sinh(p(0) * p(0) + 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 2 * p(0) * std::cosh(p(0) * p(0) + 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 4 *        std::cosh(p(0) * p(0) + 4 * p(1)), epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(p(0), p(1)), s.diff(y      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_cosh ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = cosh(x * x + 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,            std::cosh(p(0) * p(0) + 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 2 * p(0) * std::sinh(p(0) * p(0) + 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 4 *        std::sinh(p(0) * p(0) + 4 * p(1)), epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(p(0), p(1)), s.diff(y      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_tanh ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = tanh(x * x + 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,                     std::tanh(p(0) * p(0) + 4 * p(1))    , epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 2 * p(0) / std::pow(std::cosh(p(0) * p(0) + 4 * p(1)), 2), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 4        / std::pow(std::cosh(p(0) * p(0) + 4 * p(1)), 2), epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(p(0), p(1)), s.diff(y      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_asinh ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = asinh(x * x + 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,                        std::asinh(p(0) * p(0) + 4 * p(1))    , epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 2 * p(0) / std::sqrt(1 + std::pow(p(0) * p(0) + 4 * p(1), 2)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 4        / std::sqrt(1 + std::pow(p(0) * p(0) + 4 * p(1), 2)), epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(p(0), p(1)), s.diff(y      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_acosh ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = acosh(x * x + 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,                    std::acosh(p(0) * p(0) + 4 * p(1))        , epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 2 * p(0) / std::sqrt(std::pow(p(0) * p(0) + 4 * p(1), 2) - 1), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 4        / std::sqrt(std::pow(p(0) * p(0) + 4 * p(1), 2) - 1), epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(p(0), p(1)), s.diff(y      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_atanh ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = atanh(x * x + 4 * y);

  nabla::vector<2> p { 2.0, -1.2 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,               std::atanh(p(0) * p(0) + 4 * p(1))    , epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 2 * p(0) / (1 - std::pow(p(0) * p(0) + 4 * p(1), 2)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 4        / (1 - std::pow(p(0) * p(0) + 4 * p(1), 2)), epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(p(0), p(1)), s.diff(y      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( constant_folding ) {
  nabla::expr::constant half(0.5);
  nabla::expr::constant two (2.0);

  BOOST_CHECK_CLOSE(std::sinh (two .value()), sinh (two )(), epsilon);
  BOOST_CHECK_CLOSE(std::cosh (two .value()), cosh (two )(), epsilon);
  BOOST_CHECK_CLOSE(std::tanh (two .value()), tanh (two )(), epsilon);
  BOOST_CHECK_CLOSE(std::asinh(two .value()), asinh(two )(), epsilon);
  BOOST_CHECK_CLOSE(std::acosh(two .value()), acosh(two )(), epsilon);
  BOOST_CHECK_CLOSE(std::atanh(half.value()), atanh(half)(), epsilon);

  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(sinh (two ))>::value));
  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(cosh (two ))>::value));
  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(tanh (two ))>::value));
  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(asinh(two ))>::value));
  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(acosh(two ))>::value));
  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(atanh(half))>::value));
}

BOOST_AUTO_TEST_SUITE_END()
