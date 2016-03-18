#include <nabla/sum.hh>

#include <boost/test/unit_test.hpp>

namespace {
  double const epsilon = 1e-7;
}

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
  
  BOOST_CHECK_EQUAL( 0, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));

  BOOST_CHECK_CLOSE(f              (vars(0), vars(1), vars(2)), f              (vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars), epsilon);
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
  
  BOOST_CHECK_EQUAL( 0, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));

  BOOST_CHECK_CLOSE(f              (vars(0), vars(1), vars(2)), f              (vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars), epsilon);
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
  
  BOOST_CHECK_EQUAL( 0, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z, z)(vars));

  BOOST_CHECK_CLOSE(f              (vars(0), vars(1), vars(2)), f              (vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars), epsilon);
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
  
  BOOST_CHECK_EQUAL( 0, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));

  BOOST_CHECK_CLOSE(f              (vars(0), vars(1), vars(2)), f              (vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars), epsilon);
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
  
  BOOST_CHECK_EQUAL( 0, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));

  BOOST_CHECK_CLOSE(f              (vars(0), vars(1), vars(2)), f              (vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars), epsilon);
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
  
  BOOST_CHECK_EQUAL( 0, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));

  BOOST_CHECK_CLOSE(f              (vars(0), vars(1), vars(2)), f              (vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars), epsilon);
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
  
  BOOST_CHECK_EQUAL( 0, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z, z)(vars));

  BOOST_CHECK_CLOSE(f              (vars(0), vars(1), vars(2)), f              (vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars), epsilon);
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
  
  BOOST_CHECK_EQUAL( 0, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));

  BOOST_CHECK_CLOSE(f              (vars(0), vars(1), vars(2)), f              (vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars), epsilon);
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
  
  BOOST_CHECK_EQUAL( 0, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(x, z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(y, z)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z, x)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z, y)(vars));
  BOOST_CHECK_EQUAL( 0, f.diff(z, z)(vars));

  BOOST_CHECK_CLOSE(f              (vars(0), vars(1), vars(2)), f              (vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars), epsilon);
}

BOOST_AUTO_TEST_CASE( simple_n1 ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = 2.0 + x - y;

  nabla::vector<2> values(1.0, -3.0);

  auto r = s(values);

  BOOST_CHECK_EQUAL( 6.0, r);
  BOOST_CHECK_EQUAL( 1.0, s.diff(x)(values));
  BOOST_CHECK_EQUAL(-1.0, s.diff(y)(values));

  BOOST_CHECK_CLOSE(s              (values(0), values(1)), s              (values), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(values(0), values(1)), s.diff(x      )(values), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(values(0), values(1)), s.diff(y      )(values), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(values(0), values(1)), s.diff(x, x   )(values), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(values(0), values(1)), s.diff(x, y   )(values), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(values(0), values(1)), s.diff(x, x, x)(values), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(values(0), values(1)), s.diff(x, x, y)(values), epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
