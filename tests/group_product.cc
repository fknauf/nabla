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
  
  BOOST_CHECK_EQUAL( 0, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));
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
  
  BOOST_CHECK_EQUAL( 0, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));
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
  
  BOOST_CHECK_EQUAL( 0, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 1, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 1, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));
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
  
  BOOST_CHECK_EQUAL( 2, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));
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
  
  BOOST_CHECK_EQUAL(24, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));
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
  
  BOOST_CHECK_EQUAL( 4, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 2, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 2, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));
}

BOOST_AUTO_TEST_CASE( n1_simple ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = 2.0 * x * y;

  nabla::vector<2> values { 3.0, 4.0 };

  auto r = s(values);

  BOOST_CHECK_EQUAL(24.0, r);
  BOOST_CHECK_EQUAL( 8.0, s.diff(x)(values));
  BOOST_CHECK_EQUAL( 6.0, s.diff(y)(values));
}

BOOST_AUTO_TEST_CASE( n1_squares ) {
  auto x = nabla::expr::variable<0>();

  auto s = 2.0 * x * x;

  nabla::vector<1> values = nabla::vector<1>::Constant(3.0);

  auto r = s(values);

  BOOST_CHECK_EQUAL(18.0, r);
  BOOST_CHECK_EQUAL(12.0, s.diff(x)(values));
}

BOOST_AUTO_TEST_CASE( n1_mixed_polynomial ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = 2.0 * x * x * y;

  nabla::vector<2> values { 3.0, 4.0 };

  auto r = s(values);

  BOOST_CHECK_EQUAL(72.0, r);
  BOOST_CHECK_EQUAL(48.0, s.diff(x)(values));
  BOOST_CHECK_EQUAL(18.0, s.diff(y)(values));
}

BOOST_AUTO_TEST_SUITE_END()
