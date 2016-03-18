#include <nabla/nabla.hh>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( gradient )

namespace {
  double const epsilon = 1e-7;
}

BOOST_AUTO_TEST_CASE ( simple ) {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = x - y;

  auto g = nabla::gradient(f, 2, 3, 4);

  BOOST_CHECK_EQUAL(g(0),  1);
  BOOST_CHECK_EQUAL(g(1), -1);
  BOOST_CHECK_EQUAL(g(2),  0);
}

BOOST_AUTO_TEST_CASE ( complex ) {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = pow(sin(x + y) * cos(z * z), 2) + 10;

  auto g = nabla::gradient(f, 2, 3, 4);

  BOOST_CHECK_CLOSE(g(0),   2 * std::cos( 5) * std::sin( 5) * std::pow(std::cos(16), 2), epsilon);
  BOOST_CHECK_CLOSE(g(1),   2 * std::cos( 5) * std::sin( 5) * std::pow(std::cos(16), 2), epsilon);
  BOOST_CHECK_CLOSE(g(2), -16 * std::cos(16) * std::sin(16) * std::pow(std::sin( 5), 2), epsilon);
}

BOOST_AUTO_TEST_CASE ( complex_vecparam ) {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = pow(sin(x + y) * cos(z * z), 2) + 10;

  nabla::vector<3> vars { 2, 3, 4 };
  
  auto g = nabla::gradient(f, vars);

  BOOST_CHECK_CLOSE(g(0),   2 * std::cos( 5) * std::sin( 5) * std::pow(std::cos(16), 2), epsilon);
  BOOST_CHECK_CLOSE(g(1),   2 * std::cos( 5) * std::sin( 5) * std::pow(std::cos(16), 2), epsilon);
  BOOST_CHECK_CLOSE(g(2), -16 * std::cos(16) * std::sin(16) * std::pow(std::sin( 5), 2), epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
