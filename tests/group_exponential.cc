#include <nabla/exponential.hh>
#include <nabla/product.hh>
#include <nabla/sum.hh>

#include <boost/test/unit_test.hpp>

namespace {
  double constexpr epsilon = 1e-7;
}

BOOST_AUTO_TEST_SUITE( exponential )

BOOST_AUTO_TEST_CASE( simple )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = pow(2, x);
  
  nabla::vector<2> vars;
  vars << 3, 4;

  BOOST_CHECK_CLOSE(8, f(vars), epsilon);

  BOOST_CHECK_CLOSE(                            std::log(2) * 8, f.diff(x      )(vars), epsilon);
  BOOST_CHECK_EQUAL(                                          0, f.diff(y      )(vars));
  BOOST_CHECK_CLOSE(              std::log(2) * std::log(2) * 8, f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_EQUAL(                                          0, f.diff(x, y   )(vars));
  BOOST_CHECK_CLOSE(std::log(2) * std::log(2) * std::log(2) * 8, f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_EQUAL(                                          0, f.diff(x, x, y)(vars));
}

BOOST_AUTO_TEST_CASE( medium )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;

  auto f = pow(2, x - y);
  
  nabla::vector<2> vars;
  vars << 4, 1;

  BOOST_CHECK_CLOSE(8, f(vars), epsilon);

  BOOST_CHECK_CLOSE(                             std::log(2) * 8, f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(                            -std::log(2) * 8, f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(               std::log(2) * std::log(2) * 8, f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(              -std::log(2) * std::log(2) * 8, f.diff(x, y   )(vars), epsilon);
  BOOST_CHECK_CLOSE( std::log(2) * std::log(2) * std::log(2) * 8, f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(-std::log(2) * std::log(2) * std::log(2) * 8, f.diff(x, y, x)(vars), epsilon);
}

BOOST_AUTO_TEST_CASE( complex )  {
  nabla::expr::variable<0> x;
  nabla::expr::variable<1> y;
  nabla::expr::variable<2> z;

  auto f = pow(2, (x - y) * z + x * y - 2);
  
  nabla::vector<3> vars;
  vars << 3, 1, 4;

  BOOST_CHECK_CLOSE(512, f(vars), epsilon);

  double l2 = std::log(2);

  BOOST_CHECK_CLOSE(2560 * l2, f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(-512 * l2, f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(1024 * l2, f.diff(z      )(vars), epsilon);

  BOOST_CHECK_CLOSE(             12800 * l2 * l2, f.diff(x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(  512 * l2 -  2560 * l2 * l2, f.diff(x, y)(vars), epsilon);
  BOOST_CHECK_CLOSE(  512 * l2 +  5120 * l2 * l2, f.diff(x, z)(vars), epsilon);
  BOOST_CHECK_CLOSE(  512 * l2 -  2560 * l2 * l2, f.diff(y, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(               512 * l2 * l2, f.diff(y, y)(vars), epsilon);
  BOOST_CHECK_CLOSE( -512 * l2 -  1024 * l2 * l2, f.diff(y, z)(vars), epsilon);
  BOOST_CHECK_CLOSE(  512 * l2 +  5120 * l2 * l2, f.diff(z, x)(vars), epsilon);
  BOOST_CHECK_CLOSE( -512 * l2 -  1024 * l2 * l2, f.diff(z, y)(vars), epsilon);
  BOOST_CHECK_CLOSE(              2048 * l2 * l2, f.diff(z, z)(vars), epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
