#include <nabla/product.hh>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( product )

BOOST_AUTO_TEST_CASE( var_times_num )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = x * 2 ;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL( 4, f(vars));

  BOOST_CHECK_EQUAL( 2, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y)(vars));

  BOOST_CHECK_EQUAL( 2, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>()(vars));
  
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(y)(vars));
}

BOOST_AUTO_TEST_CASE( num_times_var )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = 2 * x;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL( 4, f(vars));

  BOOST_CHECK_EQUAL( 2, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y)(vars));

  BOOST_CHECK_EQUAL( 2, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>()(vars));
  
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(y)(vars));
}

BOOST_AUTO_TEST_CASE( var_times_var )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = x * y ;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL( 6, f(vars));

  BOOST_CHECK_EQUAL( 3, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 2, f.diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z)(vars));

  BOOST_CHECK_EQUAL( 3, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 2, f.diff<1>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<2>()(vars));
  
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 1, f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 1, f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(y)(vars));
}

BOOST_AUTO_TEST_CASE( var_square )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = x * x ;
  
  nabla::vector<3> vars;
  vars << 3, 4, 5;

  BOOST_CHECK_EQUAL( 9, f(vars));

  BOOST_CHECK_EQUAL( 6, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y)(vars));

  BOOST_CHECK_EQUAL( 6, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>()(vars));
  
  BOOST_CHECK_EQUAL( 2, f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(y)(vars));
}

BOOST_AUTO_TEST_CASE( var_cube )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = x * x * x;
  
  nabla::vector<3> vars;
  vars << 4, 5, 6;

  BOOST_CHECK_EQUAL(64, f(vars));

  BOOST_CHECK_EQUAL(48, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y)(vars));

  BOOST_CHECK_EQUAL(48, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>()(vars));
  
  BOOST_CHECK_EQUAL(24, f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(y)(vars));
}

BOOST_AUTO_TEST_CASE( dist )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = 2 * (x + y) * x;
  
  nabla::vector<3> vars;
  vars << 3, 4, 5;

  BOOST_CHECK_EQUAL(42, f(vars));

  BOOST_CHECK_EQUAL(20, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 6, f.diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z)(vars));

  BOOST_CHECK_EQUAL(20, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 6, f.diff<1>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<2>()(vars));
  
  BOOST_CHECK_EQUAL( 4, f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 2, f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 2, f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(y)(vars));
}

BOOST_AUTO_TEST_SUITE_END()
