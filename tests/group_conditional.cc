#include <nabla/conditional.hh>
#include <nabla/product.hh>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( conditional )

BOOST_AUTO_TEST_CASE( case_true )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = nabla::expr::impl::make_conditional([](auto &&) { return true; }, x * x, x * y);
  
  nabla::vector<3> vars;
  vars << 3, 4, 5;

  BOOST_CHECK_EQUAL(9, f(vars));

  BOOST_CHECK_EQUAL(6, f.diff(x)(vars));
  BOOST_CHECK_EQUAL(0, f.diff(y)(vars));

  BOOST_CHECK_EQUAL(2, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL(0, f.diff(x, y)(vars));
}

BOOST_AUTO_TEST_CASE( case_false )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = nabla::expr::impl::make_conditional([](auto &&) { return false; }, x * x, x * y);
  
  nabla::vector<3> vars;
  vars << 3, 4, 5;

  BOOST_CHECK_EQUAL(12, f(vars));

  BOOST_CHECK_EQUAL(4, f.diff(x)(vars));
  BOOST_CHECK_EQUAL(3, f.diff(y)(vars));
  BOOST_CHECK_EQUAL(0, f.diff(z)(vars));

  BOOST_CHECK_EQUAL(0, f.diff(x, x)(vars));
  BOOST_CHECK_EQUAL(1, f.diff(x, y)(vars));
  BOOST_CHECK_EQUAL(1, f.diff(y, x)(vars));
  BOOST_CHECK_EQUAL(0, f.diff(y, y)(vars));
}

BOOST_AUTO_TEST_SUITE_END()
