#include <nabla/variable.hh>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( variable )

BOOST_AUTO_TEST_CASE( diff_by_var )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;
  
  nabla::vector<3> vars;
  vars << 1, 2, 3;

  BOOST_CHECK_EQUAL(1, x(vars));
  BOOST_CHECK_EQUAL(2, y(vars));
  BOOST_CHECK_EQUAL(3, z(vars));

  BOOST_CHECK_EQUAL(1, x.diff(x)(vars));
  BOOST_CHECK_EQUAL(1, y.diff(y)(vars));
  BOOST_CHECK_EQUAL(1, z.diff(z)(vars));
  BOOST_CHECK_EQUAL(0, x.diff(y)(vars));
  BOOST_CHECK_EQUAL(0, x.diff(z)(vars));
  BOOST_CHECK_EQUAL(0, x.diff(x, x)(vars));
  BOOST_CHECK_EQUAL(0, x.diff(x, y)(vars));
  BOOST_CHECK_EQUAL(0, x.diff(x, z)(vars));
  BOOST_CHECK_EQUAL(0, x.diff(y, x)(vars));
  BOOST_CHECK_EQUAL(0, x.diff(y, y)(vars));
  BOOST_CHECK_EQUAL(0, x.diff(y, z)(vars));
  BOOST_CHECK_EQUAL(0, x.diff(z, x)(vars));
  BOOST_CHECK_EQUAL(0, x.diff(z, y)(vars));
  BOOST_CHECK_EQUAL(0, x.diff(z, z)(vars));

  BOOST_CHECK_EQUAL(x        (vars(0), vars(1), vars(2)), x        (vars));
  BOOST_CHECK_EQUAL(y        (vars(0), vars(1), vars(2)), y        (vars));
  BOOST_CHECK_EQUAL(z        (vars(0), vars(1), vars(2)), z        (vars));
  BOOST_CHECK_EQUAL(x.diff(x)(vars(0), vars(1), vars(2)), x.diff(x)(vars));
  BOOST_CHECK_EQUAL(x.diff(y)(vars(0), vars(1), vars(2)), x.diff(y)(vars));
}

BOOST_AUTO_TEST_CASE( diff_by_num )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;
  
  nabla::vector<3> vars;
  vars << 1, 2, 3;

  BOOST_CHECK_EQUAL(1, x(vars));
  BOOST_CHECK_EQUAL(2, y(vars));
  BOOST_CHECK_EQUAL(3, z(vars));

  BOOST_CHECK_EQUAL(1, x.diff<0>()(vars));
  BOOST_CHECK_EQUAL(1, y.diff<1>()(vars));
  BOOST_CHECK_EQUAL(1, z.diff<2>()(vars));
  BOOST_CHECK_EQUAL(0, x.diff<1>()(vars));
  BOOST_CHECK_EQUAL(0, x.diff<2>()(vars));
  BOOST_CHECK_EQUAL(0, x.diff<0>().diff<0>()(vars));
  BOOST_CHECK_EQUAL(0, x.diff<0>().diff<1>()(vars));
  BOOST_CHECK_EQUAL(0, x.diff<0>().diff<2>()(vars));
  BOOST_CHECK_EQUAL(0, x.diff<1>().diff<0>()(vars));
  BOOST_CHECK_EQUAL(0, x.diff<1>().diff<1>()(vars));
  BOOST_CHECK_EQUAL(0, x.diff<1>().diff<2>()(vars));
  BOOST_CHECK_EQUAL(0, x.diff<2>().diff<0>()(vars));
  BOOST_CHECK_EQUAL(0, x.diff<2>().diff<1>()(vars));
  BOOST_CHECK_EQUAL(0, x.diff<2>().diff<2>()(vars));

  BOOST_CHECK_EQUAL(x        (vars(0), vars(1), vars(2)), x        (vars));
  BOOST_CHECK_EQUAL(y        (vars(0), vars(1), vars(2)), y        (vars));
  BOOST_CHECK_EQUAL(z        (vars(0), vars(1), vars(2)), z        (vars));
  BOOST_CHECK_EQUAL(x.diff(x)(vars(0), vars(1), vars(2)), x.diff(x)(vars));
  BOOST_CHECK_EQUAL(x.diff(y)(vars(0), vars(1), vars(2)), x.diff(y)(vars));
}

BOOST_AUTO_TEST_SUITE_END()
