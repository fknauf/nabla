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
}

BOOST_AUTO_TEST_SUITE_END()
