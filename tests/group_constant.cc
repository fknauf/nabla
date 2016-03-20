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
  BOOST_CHECK_EQUAL(0.0, v.diff(x, x)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(x, y)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(x, z)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(y, x)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(y, y)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(y, z)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(z, x)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(z, y)(vars));
  BOOST_CHECK_EQUAL(0.0, v.diff(z, z)(vars));
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

BOOST_AUTO_TEST_CASE( params_expanded )  {
  double val = 3.14;

  nabla::expr::constant v(val);

  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;
  
  BOOST_CHECK_EQUAL(val, v(1, 2, 3));

  BOOST_CHECK_EQUAL(0.0, v.diff(x)(1, 2, 3));
  BOOST_CHECK_EQUAL(0.0, v.diff(y)(1, 2, 3));
  BOOST_CHECK_EQUAL(0.0, v.diff(z)(1, 2, 3));
  BOOST_CHECK_EQUAL(0.0, v.diff(x, x)(1, 2, 3));
  BOOST_CHECK_EQUAL(0.0, v.diff(x, y)(1, 2, 3));
  BOOST_CHECK_EQUAL(0.0, v.diff(x, z)(1, 2, 3));
  BOOST_CHECK_EQUAL(0.0, v.diff(y, x)(1, 2, 3));
  BOOST_CHECK_EQUAL(0.0, v.diff(y, y)(1, 2, 3));
  BOOST_CHECK_EQUAL(0.0, v.diff(y, z)(1, 2, 3));
  BOOST_CHECK_EQUAL(0.0, v.diff(z, x)(1, 2, 3));
  BOOST_CHECK_EQUAL(0.0, v.diff(z, y)(1, 2, 3));
  BOOST_CHECK_EQUAL(0.0, v.diff(z, z)(1, 2, 3));
}

BOOST_AUTO_TEST_CASE( constant_value ) {
  nabla::expr::constant c(2);

  BOOST_CHECK_EQUAL(2, nabla::expr::impl::constant_value(c));
  BOOST_CHECK_EQUAL(3, nabla::expr::impl::constant_value(3));
}

BOOST_AUTO_TEST_SUITE_END()
