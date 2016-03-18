#include <nabla/polynomial.hh>
#include <nabla/product.hh>
#include <nabla/sum.hh>

#include <boost/test/unit_test.hpp>

namespace {
  double constexpr epsilon = 1e-7;
}

BOOST_AUTO_TEST_SUITE( polynomial )

BOOST_AUTO_TEST_CASE( simple_square )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = pow(x, 2);
  
  nabla::vector<1> vars;
  vars << 3;

  BOOST_CHECK_EQUAL(9, f(vars));

  BOOST_CHECK_EQUAL(6, f.diff(x)(vars));
  BOOST_CHECK_EQUAL(0, f.diff(y)(vars));

  BOOST_CHECK_EQUAL(2, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL(0, f.diff(x, y)(vars));

  BOOST_CHECK_EQUAL(0, f.diff(x, x, x)(vars));
  BOOST_CHECK_EQUAL(0, f.diff(x, x, y)(vars));

  BOOST_CHECK_EQUAL(f        (vars(0)), f        (vars));
  BOOST_CHECK_EQUAL(f.diff(x)(vars(0)), f.diff(x)(vars));
}

BOOST_AUTO_TEST_CASE( simple_real )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = pow(x, 3.5);
  
  nabla::vector<1> vars;
  vars << 3;

  BOOST_CHECK_CLOSE(std::pow(3, 3.5), f(vars), epsilon);

  BOOST_CHECK_CLOSE(3.5 *             std::pow(3, 2.5), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_EQUAL(0                                 , f.diff(y      )(vars));
  BOOST_CHECK_CLOSE(3.5 * 2.5 *       std::pow(3, 1.5), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_EQUAL(0                                 , f.diff(x, y   )(vars));
  BOOST_CHECK_CLOSE(3.5 * 2.5 * 1.5 * std::sqrt(3)    , f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_EQUAL(0                                 , f.diff(x, x, y)(vars));

  BOOST_CHECK_EQUAL(f        (vars(0)), f        (vars));
  BOOST_CHECK_EQUAL(f.diff(x)(vars(0)), f.diff(x)(vars));
}

BOOST_AUTO_TEST_CASE( simple_0 )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = pow(x, 0);
  
  nabla::vector<1> vars;
  vars << 0;

  BOOST_CHECK_CLOSE(1, f(vars), epsilon);

  BOOST_CHECK_CLOSE(0, f.diff(x      )(vars), epsilon);
  BOOST_CHECK_EQUAL(0, f.diff(y      )(vars));
  BOOST_CHECK_CLOSE(0, f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_EQUAL(0, f.diff(x, y   )(vars));
  BOOST_CHECK_CLOSE(0, f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_EQUAL(0, f.diff(x, x, y)(vars));

  BOOST_CHECK_EQUAL(f        (vars(0)), f        (vars));
  BOOST_CHECK_EQUAL(f.diff(x)(vars(0)), f.diff(x)(vars));
}

BOOST_AUTO_TEST_CASE( simple_break )  {
  nabla::expr::variable<0> x;

  auto f = pow(x, 1);
  
  nabla::vector<1> vars;
  vars << 0;

  // Knickstelle in der Ableitung bei 0^0
  BOOST_CHECK_SMALL(   f           (vars), epsilon);
  BOOST_CHECK_CLOSE(1, f.diff(x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(0, f.diff(x, x)(vars), epsilon);

  BOOST_CHECK_EQUAL(f        (vars(0)), f        (vars));
  BOOST_CHECK_EQUAL(f.diff(x)(vars(0)), f.diff(x)(vars));
}

BOOST_AUTO_TEST_CASE( chain )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = pow(y - x, 3);
  
  nabla::vector<2> vars;
  vars << 1, 3;

  BOOST_CHECK_CLOSE(8, f(vars), epsilon);

  BOOST_CHECK_CLOSE(-12, f.diff(x      )(vars), epsilon);
  BOOST_CHECK_EQUAL( 12, f.diff(y      )(vars));
  BOOST_CHECK_CLOSE( 12, f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_EQUAL(-12, f.diff(x, y   )(vars));
  BOOST_CHECK_CLOSE( -6, f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_EQUAL(  6, f.diff(x, x, y)(vars));

  BOOST_CHECK_EQUAL(f        (vars(0), vars(1)), f        (vars));
  BOOST_CHECK_EQUAL(f.diff(x)(vars(0), vars(1)), f.diff(x)(vars));
}

BOOST_AUTO_TEST_CASE( test_polynomial ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = pow(x * y, 4);

  nabla::vector<2> p(2.0, 5.0);

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,     std::pow(p(0) * p(1), 4)             , epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 4 * std::pow(p(0), 3) * std::pow(p(1), 4), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 4 * std::pow(p(0), 4) * std::pow(p(1), 3), epsilon);

  BOOST_CHECK_EQUAL(s        (p(0), p(1)), s        (p));
  BOOST_CHECK_EQUAL(s.diff(x)(p(0), p(1)), s.diff(x)(p));
}

BOOST_AUTO_TEST_CASE( test_polynomial_2 ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = pow(x, 3) - 3 * pow(x, 2) * y + 3 * x * pow(y, 2) - pow(y, 3);

  nabla::vector<2> p(2.0, 5.0);

  auto r = s(p);

  double exv =
    std::pow(p(0), 3)
    - 3 * std::pow(p(0), 2) *          p(1)
    + 3 *          p(0)     * std::pow(p(1), 2)
    - std::pow(p(1), 3);

  double dx = 3 * std::pow(p(0), 2) - 6 * p(0) * p(1) + 3 * std::pow(p(1), 2);

  BOOST_CHECK_CLOSE(r           , exv, epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p),  dx, epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), -dx, epsilon);

  BOOST_CHECK_EQUAL(s        (p(0), p(1)), s        (p));
  BOOST_CHECK_EQUAL(s.diff(x)(p(0), p(1)), s.diff(x)(p));
}

BOOST_AUTO_TEST_CASE( test_degenerated ) {
  auto x = nabla::expr::variable<0>();

  auto s = pow(x, 0);

  nabla::vector<1> p = nabla::vector<1>::Constant(2.0);

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           , 1.0, epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 0.0, epsilon);

  p(0) = 0.0;
  r = s(p);

  BOOST_CHECK_CLOSE(r           , 1.0, epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 0.0, epsilon);

  BOOST_CHECK_EQUAL(s        (p(0)), s        (p));
  BOOST_CHECK_EQUAL(s.diff(x)(p(0)), s.diff(x)(p));
}

BOOST_AUTO_TEST_SUITE_END()
