#include <nabla/nabla.hh>
#include <boost/test/unit_test.hpp>

#include <iostream>

BOOST_AUTO_TEST_SUITE( hessian )

namespace {
  double const epsilon = 1e-7;
}

BOOST_AUTO_TEST_CASE ( simple ) {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = pow(x - y, 2);

  auto h = nabla::hessian(f, 2, 3);

  std::cout << h << std::endl;

  BOOST_CHECK_CLOSE( 2, h(0, 0), epsilon);
  BOOST_CHECK_CLOSE(-2, h(0, 1), epsilon);
  BOOST_CHECK_CLOSE(-2, h(1, 0), epsilon);
  BOOST_CHECK_CLOSE( 2, h(1, 1), epsilon);
}

BOOST_AUTO_TEST_CASE ( complex ) {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = pow(sin(x - 2 * y) * cos(z * z), 2) + 10;

  auto h = nabla::hessian(f, 2, 3, 4);

  BOOST_CHECK_CLOSE(-0.2668795609662459, h(0, 0), epsilon);
  BOOST_CHECK_CLOSE( 0.5337591219324918, h(0, 1), epsilon);
  BOOST_CHECK_CLOSE( 4.364468275957035 , h(0, 2), epsilon);
  BOOST_CHECK_EQUAL(            h(0, 1), h(1, 0)         );
  BOOST_CHECK_CLOSE(-1.067518243864983 , h(1, 1), epsilon);
  BOOST_CHECK_CLOSE(-8.728936551914071 , h(1, 2), epsilon);
  BOOST_CHECK_EQUAL(            h(0, 2), h(2, 0)         );
  BOOST_CHECK_EQUAL(            h(1, 2), h(2, 1)         );
  BOOST_CHECK_CLOSE(-61.79024409251047 , h(2, 2), epsilon);
}

BOOST_AUTO_TEST_CASE ( complex_vecparam ) {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = pow(sin(x - 2 * y) * cos(z * z), 2) + 10;

  nabla::vector<3> vars { 2, 3, 4 };
  
  auto h = nabla::hessian(f, vars);

  BOOST_CHECK_CLOSE(-0.2668795609662459, h(0, 0), epsilon);
  BOOST_CHECK_CLOSE( 0.5337591219324918, h(0, 1), epsilon);
  BOOST_CHECK_CLOSE( 4.364468275957035 , h(0, 2), epsilon);
  BOOST_CHECK_EQUAL(            h(0, 1), h(1, 0)         );
  BOOST_CHECK_CLOSE(-1.067518243864983 , h(1, 1), epsilon);
  BOOST_CHECK_CLOSE(-8.728936551914071 , h(1, 2), epsilon);
  BOOST_CHECK_EQUAL(            h(0, 2), h(2, 0)         );
  BOOST_CHECK_EQUAL(            h(1, 2), h(2, 1)         );
  BOOST_CHECK_CLOSE(-61.79024409251047 , h(2, 2), epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
