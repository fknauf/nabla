#include <nabla/chain.hh>
#include <nabla/hypot.hh>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( chain )

namespace {
  double epsilon = 1e-7;
}

BOOST_AUTO_TEST_CASE( sym )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = x * x * y;
  auto g = x * x;
  auto h = x + 2 * x * y;

  nabla::expr::chain<decltype(f), decltype(g), decltype(h)> c(f, g, h);
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL(224, c(vars));

  BOOST_CHECK_EQUAL(560, c.diff(x)(vars));
  BOOST_CHECK_EQUAL( 64, c.diff(y)(vars));
  BOOST_CHECK_EQUAL(  0, c.diff(z)(vars));

  BOOST_CHECK_EQUAL(160, c.diff(x, y)(vars));
  BOOST_CHECK_EQUAL(160, c.diff(y, x)(vars));
}

BOOST_AUTO_TEST_CASE( asym )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = x * x * y;
  auto g = x * x + z;
  auto h = x + 2 * x * y;

  nabla::expr::chain<decltype(f), decltype(g), decltype(h)> c(f, g, h);
  
  nabla::vector<3> vars;
  vars << 2, 3, 4;

  BOOST_CHECK_EQUAL( 896, c(vars));

  BOOST_CHECK_EQUAL(1344, c.diff(x)(vars));
  BOOST_CHECK_EQUAL( 256, c.diff(y)(vars));
  BOOST_CHECK_EQUAL( 224, c.diff(z)(vars));

  BOOST_CHECK_EQUAL(384, c.diff(x, y)(vars));
  BOOST_CHECK_EQUAL(384, c.diff(y, x)(vars));
}

BOOST_AUTO_TEST_CASE( n1_simple ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto a = x;
  auto b = y;

  auto s = nabla::expr::impl::make_chain(a + b,
					 3 * x + y,
					 x + 2 * y);

  nabla::vector<2> p(1.0, -3.0);

  auto r = s(p);

  BOOST_CHECK_CLOSE(4 * p(0) + 3 * p(1), r, epsilon);

  BOOST_CHECK_CLOSE(4.0, s.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE(3.0, s.diff(y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( n1_product_rule ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto a = x;
  auto b = y;

  auto s = nabla::expr::impl::make_chain(a * b,
					 3 * x + y,
					 x + 2 * y);

  nabla::vector<2> p(1.0, -3.0);

  auto r = s(p);

  BOOST_CHECK_CLOSE((3 * p(0) + p(1)) * (p(0) + 2 * p(1)), r, epsilon);

  BOOST_CHECK_CLOSE(6 * p(0) + 7 * p(1), s.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE(7 * p(0) + 4 * p(1), s.diff(y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( n1_simple_num ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto a = x;
  auto b = y;

  auto s = nabla::expr::impl::make_chain(a + b,
					 nabla::expr::constant(3),
					 nabla::expr::constant(2));

  nabla::vector<2> p(1.0, -3.0);

  auto r = s(p);

  BOOST_CHECK_EQUAL(5, r);

  BOOST_CHECK_CLOSE(0.0, s.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE(0.0, s.diff(y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( params_expanded )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = x * x * y;
  auto g = x * x;
  auto h = x + 2 * x * y;

  nabla::expr::chain<decltype(f), decltype(g), decltype(h)> c(f, g, h);
  
  BOOST_CHECK_EQUAL(224, c(2, 3, 4));

  BOOST_CHECK_EQUAL(560, c.diff(x)(2, 3, 4));
  BOOST_CHECK_EQUAL( 64, c.diff(y)(2, 3, 4));
  BOOST_CHECK_EQUAL(  0, c.diff(z)(2, 3, 4));

  BOOST_CHECK_EQUAL(160, c.diff(x, y)(2, 3, 4));
  BOOST_CHECK_EQUAL(160, c.diff(y, x)(2, 3, 4));
}

BOOST_AUTO_TEST_CASE(constant_folding) {
  nabla::expr::constant c(2);

  nabla::expr::variable<0> x;

  auto s = nabla::expr::impl::make_chain(c, x, 2 * x);

  BOOST_CHECK_EQUAL(2, s());
  BOOST_CHECK_EQUAL(0, s.diff(x)());

  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(s          )>::value));
  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(s.diff<0>())>::value));
}

BOOST_AUTO_TEST_SUITE_END()
