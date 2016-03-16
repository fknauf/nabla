#include <nabla/chain.hh>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( chain )

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

BOOST_AUTO_TEST_SUITE_END()
