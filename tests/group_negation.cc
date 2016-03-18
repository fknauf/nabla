#include <nabla/negation.hh>
#include <nabla/variable.hh>

#include <boost/test/unit_test.hpp>

namespace {
  double const epsilon = 1e-7;
}

BOOST_AUTO_TEST_SUITE( negation )

BOOST_AUTO_TEST_CASE( diff_by_var )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = -x;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL(-2, f(vars));

  BOOST_CHECK_EQUAL(-1, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z, z)(vars));

  BOOST_CHECK_CLOSE(f              (vars(0), vars(1)), f              (vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1)), f.diff(x, x, x)(vars), epsilon);
}

BOOST_AUTO_TEST_CASE( diff_by_num )  {
  nabla::expr::variable<0> x;

  auto f = -x;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL(-2, f(vars));

  BOOST_CHECK_EQUAL(-1, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<2>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<0>().diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<0>().diff<1>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<0>().diff<2>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>().diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>().diff<1>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>().diff<2>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<2>().diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<2>().diff<1>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<2>().diff<2>()(vars));

  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1)), f.diff(x, x, x)(vars), epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
