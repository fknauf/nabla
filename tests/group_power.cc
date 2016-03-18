#include <nabla/power.hh>
#include <nabla/polynomial.hh>
#include <nabla/product.hh>
#include <nabla/sum.hh>

#include <boost/test/unit_test.hpp>

#include <iostream>

namespace {
  double constexpr epsilon = 1e-7;
}

BOOST_AUTO_TEST_SUITE( power )

BOOST_AUTO_TEST_CASE( simple )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = pow(x, y);
  
  nabla::vector<2> vars;
  vars << 2, 5;

  BOOST_CHECK_CLOSE(32, f(vars), epsilon);

  BOOST_CHECK_CLOSE( 80                   , f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE( 32 * std::log(2)     , f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(160                   , f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE( 80 * std::log(2) + 16, f.diff(x, y   )(vars), epsilon);
  BOOST_CHECK_CLOSE(240                   , f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(160 * std::log(2) + 72, f.diff(x, x, y)(vars), epsilon);

  BOOST_CHECK_CLOSE(f.diff(x, y)   (vars), f.diff(y, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, y)(vars), f.diff(y, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, y)(vars), f.diff(x, y, x)(vars), epsilon);

  BOOST_CHECK_CLOSE(f              (vars(0), vars(1)), f              (vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1)), f.diff(x, x, x)(vars), epsilon);
}

BOOST_AUTO_TEST_CASE( mixed )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = pow(pow(x, 2) * y, pow(y, 2) * x);
  
  nabla::vector<2> p(2., 5.);

  double exv = std::pow(std::pow(p(0), 2) * p(1), std::pow(p(1), 2) * p(0));
  double dx  = exv * std::pow(p(1), 2) * (std::log(p(1)) + 2 * std::log(p(0)) + 2);
  double dy  = exv * p(0) * p(1) * (2 * std::log(p(1)) + 4 * std::log(p(0)) + 1);
  
  BOOST_CHECK_CLOSE(exv, f(p), epsilon);

  BOOST_CHECK_CLOSE(dx, f.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(dy, f.diff(y      )(p), epsilon);

  BOOST_CHECK_CLOSE(9.893089493270056e68, f.diff(x, y)(p), epsilon);

  BOOST_CHECK_CLOSE(f              (p(0), p(1)), f              (p), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(p(0), p(1)), f.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(p(0), p(1)), f.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(p(0), p(1)), f.diff(x, x, x)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_simple ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = pow(x, y);

  nabla::vector<2> p(2.0, 5.0);

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           , std::pow(p(0), p(1))                 , epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), std::pow(p(0), p(1) - 1) * p(1)      , epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), std::pow(p(0), p(1)) * std::log(p(0)), epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_mixed ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = pow(pow(x, 2) * y, pow(y, 2) * x);

  nabla::vector<2> p(2.0, 5.0);

  auto r = s(p);

  double exv = std::pow(std::pow(p(0), 2) * p(1), std::pow(p(1), 2) * p(0));
  double dx  = exv * std::pow(p(1), 2) * (std::log(p(1)) + 2 * std::log(p(0)) + 2);
  double dy  = exv * p(0) * p(1) * (2 * std::log(p(1)) + 4 * std::log(p(0)) + 1);

  BOOST_CHECK_CLOSE(r           , exv, epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), dx , epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), dy , epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
