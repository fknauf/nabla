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
  
  BOOST_CHECK_EQUAL(0  , f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL(0  , f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL(0  , f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL(0  , f.diff(y, y)(vars));
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
  
  BOOST_CHECK_EQUAL( 0.5 , f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0   , f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0   , f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0   , f.diff(y, y)(vars));

  BOOST_CHECK_EQUAL(-0.75, f.diff(x, x, x)(vars));
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
  
  BOOST_CHECK_EQUAL( 0    , f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0    , f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0    , f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0    , f.diff(y, y)(vars));

  BOOST_CHECK_EQUAL( 0.0625   , f.diff(z, z      )(vars));
  BOOST_CHECK_EQUAL( 0.03125  , f.diff(z, z, x   )(vars));
  BOOST_CHECK_EQUAL(-0.0234375, f.diff(z, z, x, z)(vars));
}

BOOST_AUTO_TEST_CASE( simple ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = x / 2;

  nabla::vector<2> values(3.0, 4.0);

  auto r = s(values);

  BOOST_CHECK_EQUAL(1.5, r);
  BOOST_CHECK_EQUAL(0.5, s.diff(x)(values));
  BOOST_CHECK_EQUAL(0.0, s.diff(y)(values));
}

BOOST_AUTO_TEST_CASE( simple_inv ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = 4.5 / x;

  nabla::vector<2> values(3.0, 4.0);

  auto r = s(values);

  BOOST_CHECK_EQUAL( 1.5, r);
  BOOST_CHECK_EQUAL(-0.5, s.diff(x)(values));
  BOOST_CHECK_EQUAL( 0.0, s.diff(y)(values));
}

BOOST_AUTO_TEST_CASE( twovar ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = x / y;

  nabla::vector<2> values(3.0, 4.0);

  auto r = s(values);

  BOOST_CHECK_EQUAL( 0.75  , r);
  BOOST_CHECK_EQUAL( 0.25  , s.diff(x)(values));
  BOOST_CHECK_EQUAL(-0.1875, s.diff(y)(values));
}

BOOST_AUTO_TEST_CASE( twovar_plus_constant ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = x / y / 0.5;

  nabla::vector<2> values(3.0, 4.0);

  auto r = s(values);

  BOOST_CHECK_EQUAL( 1.5  , r);
  BOOST_CHECK_EQUAL( 0.5  , s.diff(x)(values));
  BOOST_CHECK_EQUAL(-0.375, s.diff(y)(values));
}

BOOST_AUTO_TEST_SUITE_END()
