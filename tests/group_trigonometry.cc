#include <nabla/unary_functions.hh>
#include <boost/test/unit_test.hpp>

namespace {
  double epsilon = 1e-10;
}

BOOST_AUTO_TEST_SUITE( trigonometry )

BOOST_AUTO_TEST_CASE( test_sin ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = sin(2 * x + 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,     std::sin(2 * p(0) + 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 2 * std::cos(2 * p(0) + 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 4 * std::cos(2 * p(0) + 4 * p(1)), epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(p(0), p(1)), s.diff(y      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_cos ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = cos(2 * x + 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,      std::cos(2 * p(0) + 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 2 * -std::sin(2 * p(0) + 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 4 * -std::sin(2 * p(0) + 4 * p(1)), epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(p(0), p(1)), s.diff(y      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_tan ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = tan(2 * x - 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,               std::tan(2 * p(0) - 4 * p(1))    , epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p),  2 / std::pow(std::cos(4 * p(1) - 2 * p(0)), 2), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), -4 / std::pow(std::cos(4 * p(1) - 2 * p(0)), 2), epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(p(0), p(1)), s.diff(y      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_asin ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = asin(x * x + y);

  nabla::vector<2> p { 0.7, 0.1 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,                         std::asin(p(0) * p(0) + p(1))    , epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 2 * p(0) / std::sqrt(1 - std::pow(p(0) * p(0) + p(1), 2)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 1        / std::sqrt(1 - std::pow(p(0) * p(0) + p(1), 2)), epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(p(0), p(1)), s.diff(y      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_acos ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = acos(x * x + y);

  nabla::vector<2> p { 0.7, 0.1 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,                          std::acos(p(0) * p(0) + p(1))    , epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), -2 * p(0) / std::sqrt(1 - std::pow(p(0) * p(0) + p(1), 2)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), -1        / std::sqrt(1 - std::pow(p(0) * p(0) + p(1), 2)), epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(p(0), p(1)), s.diff(y      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_atan ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = atan(x * x + y);

  nabla::vector<2> p { 0.7, 0.1 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,                std::atan(p(0) * p(0) + p(1))    , epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 2 * p(0) / (1 + std::pow(p(0) * p(0) + p(1), 2)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 1        / (1 + std::pow(p(0) * p(0) + p(1), 2)), epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(p(0), p(1)), s.diff(y      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( constant_folding ) {
  nabla::expr::constant c(0.5);

  BOOST_CHECK_CLOSE(std::sin (c.value()), sin (c)(), epsilon);
  BOOST_CHECK_CLOSE(std::cos (c.value()), cos (c)(), epsilon);
  BOOST_CHECK_CLOSE(std::tan (c.value()), tan (c)(), epsilon);
  BOOST_CHECK_CLOSE(std::acos(c.value()), acos(c)(), epsilon);
  BOOST_CHECK_CLOSE(std::asin(c.value()), asin(c)(), epsilon);
  BOOST_CHECK_CLOSE(std::atan(c.value()), atan(c)(), epsilon);

  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(sin (c))>::value));
  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(cos (c))>::value));
  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(tan (c))>::value));
  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(acos(c))>::value));
  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(asin(c))>::value));
  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(atan(c))>::value));
}

BOOST_AUTO_TEST_SUITE_END()
