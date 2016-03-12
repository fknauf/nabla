#include <nabla/sum.hh>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( sum )

BOOST_AUTO_TEST_CASE( var_plus_num )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = x + 1 ;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL( 3, f(vars));

  BOOST_CHECK_EQUAL( 1, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y)(vars));

  BOOST_CHECK_EQUAL( 1, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>()(vars));
  
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(y)(vars));
}

BOOST_AUTO_TEST_CASE( num_plus_var )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = 1 + x;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL( 3, f(vars));

  BOOST_CHECK_EQUAL( 1, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y)(vars));

  BOOST_CHECK_EQUAL( 1, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>()(vars));
  
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(y)(vars));
}

BOOST_AUTO_TEST_CASE( var_plus_var )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = x + z ;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL( 6, f(vars));

  BOOST_CHECK_EQUAL( 1, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y)(vars));
  BOOST_CHECK_EQUAL( 1, f.diff(z)(vars));

  BOOST_CHECK_EQUAL( 1, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>()(vars));
  BOOST_CHECK_EQUAL( 1, f.diff<2>()(vars));
  
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z).diff(z)(vars));
}

BOOST_AUTO_TEST_CASE( var_plus_self )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = x + x;
  
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

BOOST_AUTO_TEST_CASE( var_minus_num )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = x - 1 ;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL( 1, f(vars));

  BOOST_CHECK_EQUAL( 1, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y)(vars));

  BOOST_CHECK_EQUAL( 1, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>()(vars));
  
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(y)(vars));
}

BOOST_AUTO_TEST_CASE( num_minus_var )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = 1 - x;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL(-1, f(vars));

  BOOST_CHECK_EQUAL(-1, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y)(vars));

  BOOST_CHECK_EQUAL(-1, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>()(vars));
  
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(y)(vars));
}

BOOST_AUTO_TEST_CASE( var_minus_var )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = x - z ;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL(-2, f(vars));

  BOOST_CHECK_EQUAL( 1, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y)(vars));
  BOOST_CHECK_EQUAL(-1, f.diff(z)(vars));

  BOOST_CHECK_EQUAL( 1, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>()(vars));
  BOOST_CHECK_EQUAL(-1, f.diff<2>()(vars));
  
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z).diff(z)(vars));
}

BOOST_AUTO_TEST_CASE( var_minus_self )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = x - x;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL( 0, f(vars));

  BOOST_CHECK_EQUAL( 0, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y)(vars));

  BOOST_CHECK_EQUAL( 0, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 0, f.diff<1>()(vars));
  
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(y)(vars));
}

BOOST_AUTO_TEST_CASE( mixed )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = x - z - 2 + y + 5;
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL( 4, f(vars));

  BOOST_CHECK_EQUAL( 1, f.diff(x)(vars));
  BOOST_CHECK_EQUAL( 1, f.diff(y)(vars));
  BOOST_CHECK_EQUAL(-1, f.diff(z)(vars));

  BOOST_CHECK_EQUAL( 1, f.diff<0>()(vars));
  BOOST_CHECK_EQUAL( 1, f.diff<1>()(vars));
  BOOST_CHECK_EQUAL(-1, f.diff<2>()(vars));
  
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x).diff(z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y).diff(z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z).diff(x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z).diff(y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z).diff(z)(vars));
}


BOOST_AUTO_TEST_SUITE_END()
