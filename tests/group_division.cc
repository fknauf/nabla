#include <nabla/division.hh>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( division )

BOOST_AUTO_TEST_CASE( var_div_num )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = x / 2;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL(1  , f(vars));

  BOOST_CHECK_EQUAL(0.5, f.diff(x)(vars));
  BOOST_CHECK_EQUAL(0  , f.diff(y)(vars));

  BOOST_CHECK_EQUAL(0.5, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL(0  , f.diff<1>()(vars));
  
  BOOST_CHECK_EQUAL(0  , f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL(0  , f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL(0  , f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL(0  , f.diff(y).diff(y)(vars));
}

BOOST_AUTO_TEST_CASE( num_div_var )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = 2 / x;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL( 1   , f(vars));

  BOOST_CHECK_EQUAL(-0.5 , f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 0   , f.diff(y)(vars));

  BOOST_CHECK_EQUAL(-0.5 , f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0   , f.diff<1>()(vars));
  
  BOOST_CHECK_EQUAL( 0.5 , f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0   , f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0   , f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0   , f.diff(y).diff(y)(vars));

  BOOST_CHECK_EQUAL(-0.75, f.diff(x).diff(x).diff(x)(vars));
}

BOOST_AUTO_TEST_CASE( var_div_var )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = x / z;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL(0.5 , f(vars));

  BOOST_CHECK_EQUAL( 0.25 , f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 0    , f.diff(y)(vars));
  BOOST_CHECK_EQUAL(-0.125, f.diff(z)(vars));

  BOOST_CHECK_EQUAL( 0.25 , f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0    , f.diff<1>()(vars));
  BOOST_CHECK_EQUAL(-0.125, f.diff<2>()(vars));
  
  BOOST_CHECK_EQUAL( 0    , f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0    , f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0    , f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0    , f.diff(y).diff(y)(vars));

  BOOST_CHECK_EQUAL( 0.0625   , f.diff(z).diff(z)(vars));
  BOOST_CHECK_EQUAL( 0.03125  , f.diff(z).diff(z).diff(x)(vars));
  BOOST_CHECK_EQUAL(-0.0234375, f.diff(z).diff(z).diff(x).diff(z)(vars));
}

BOOST_AUTO_TEST_SUITE_END()
