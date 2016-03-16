#include <nabla/logarithm.hh>
#include <nabla/product.hh>
#include <nabla/sum.hh>

#include <boost/test/unit_test.hpp>

namespace {
  double constexpr epsilon = 1e-7;
}

BOOST_AUTO_TEST_SUITE( logarithm )

BOOST_AUTO_TEST_CASE( simple )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = log(x);
  
  nabla::vector<2> vars;
  vars << 3, 4;

  BOOST_CHECK_CLOSE(std::log(3), f(vars), epsilon);

  BOOST_CHECK_CLOSE( 1. /  3, f.diff(x      )(vars), epsilon);
  BOOST_CHECK_EQUAL(       0, f.diff(y      )(vars));
  BOOST_CHECK_CLOSE(-1. /  9, f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_EQUAL(       0, f.diff(x, y   )(vars));
  BOOST_CHECK_CLOSE( 2. / 27, f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_EQUAL(       0, f.diff(x, x, y)(vars));
}

BOOST_AUTO_TEST_CASE( square )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = log(x);
  auto g = log(x * x);
  
  nabla::vector<2> vars;
  vars << 3, 4;

  BOOST_CHECK_CLOSE(std::log(3), f(vars), epsilon);

  BOOST_CHECK_CLOSE(2 * f.diff(x      )(vars), g.diff(x      )(vars), epsilon);
  BOOST_CHECK_EQUAL(2 * f.diff(y      )(vars), g.diff(y      )(vars));
  BOOST_CHECK_CLOSE(2 * f.diff(x, x   )(vars), g.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_EQUAL(2 * f.diff(x, y   )(vars), g.diff(x, y   )(vars));
  BOOST_CHECK_CLOSE(2 * f.diff(x, x, x)(vars), g.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_EQUAL(2 * f.diff(x, x, y)(vars), g.diff(x, x, y)(vars));
}

BOOST_AUTO_TEST_CASE( sum )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = log(x + 2 * y);
  
  nabla::vector<2> vars;
  vars << 3, 4;

  BOOST_CHECK_CLOSE(std::log(11), f(vars), epsilon);

  BOOST_CHECK_CLOSE( 1. /   11, f.diff(x      )(vars), epsilon);
  BOOST_CHECK_EQUAL( 2. /   11, f.diff(y      )(vars));
  BOOST_CHECK_CLOSE(-1. /  121, f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_EQUAL(-2. /  121, f.diff(x, y   )(vars));
  BOOST_CHECK_CLOSE( 2. / 1331, f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_EQUAL( 4. / 1331, f.diff(x, x, y)(vars));
}

BOOST_AUTO_TEST_SUITE_END()
