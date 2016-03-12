#include <nabla/constant.hh>
#include <nabla/variable.hh>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( constant )

BOOST_AUTO_TEST_CASE( diff_by_var )  {
  double val = 3.14;

  nabla::expr::constant v(val);

  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;
  
  nabla::vector<3> vars;

  BOOST_CHECK_EQUAL(val, v(vars));

  BOOST_CHECK_EQUAL(0.0, v.diff(x)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(y)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(z)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(x).diff(z)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(y).diff(y)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(y).diff(z)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(z).diff(x)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(z).diff(y)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(z).diff(z)(vars));
}

BOOST_AUTO_TEST_CASE( diff_by_num )  {
  double val = 3.14;

  nabla::expr::constant v(val);
  
  nabla::vector<3> vars;

  BOOST_CHECK_EQUAL(val, v(vars));

  BOOST_CHECK_EQUAL(0.0, v.diff<0>()(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff<1>()(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff<2>()(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff<0>().diff<0>()(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff<0>().diff<1>()(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff<0>().diff<2>()(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff<1>().diff<0>()(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff<1>().diff<1>()(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff<1>().diff<2>()(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff<2>().diff<0>()(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff<2>().diff<1>()(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff<2>().diff<2>()(vars));
}

BOOST_AUTO_TEST_SUITE_END()
