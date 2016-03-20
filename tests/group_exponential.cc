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

  BOOST_CHECK_CLOSE(f              (vars(0), vars(1)), f              (vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(y      )(vars(0), vars(1)), f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, y   )(vars(0), vars(1)), f.diff(x, y   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1)), f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, y)(vars(0), vars(1)), f.diff(x, x, y)(vars), epsilon);
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

  BOOST_CHECK_CLOSE(f              (vars(0), vars(1)), f              (vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(y      )(vars(0), vars(1)), f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, y   )(vars(0), vars(1)), f.diff(x, y   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1)), f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, y)(vars(0), vars(1)), f.diff(x, x, y)(vars), epsilon);
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

  BOOST_CHECK_CLOSE(f              (vars(0), vars(1), vars(2)), f              (vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x      )(vars(0), vars(1), vars(2)), f.diff(x      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(y      )(vars(0), vars(1), vars(2)), f.diff(y      )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x   )(vars(0), vars(1), vars(2)), f.diff(x, x   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, y   )(vars(0), vars(1), vars(2)), f.diff(x, y   )(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, x)(vars(0), vars(1), vars(2)), f.diff(x, x, x)(vars), epsilon);
  BOOST_CHECK_CLOSE(f.diff(x, x, y)(vars(0), vars(1), vars(2)), f.diff(x, x, y)(vars), epsilon);
}

BOOST_AUTO_TEST_CASE( test_trivial ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = pow(2, x * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           , std::pow(2.0, p(0) * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), p(1) * std::log(2) * r    , epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), p(0) * std::log(2) * r    , epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(p(0), p(1)), s.diff(y      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_stacked ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = pow(2, pow(1.5, x * y));

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  double exv = std::pow(2, std::pow(1.5, p(0) * p(1)));

  double dx = p(1) * std::log(2) * std::log(1.5) * std::pow(1.5, p(0) * p(1)) * exv;
  double dy = p(0) * std::log(2) * std::log(1.5) * std::pow(1.5, p(0) * p(1)) * exv;

  BOOST_CHECK_CLOSE(r           , exv, epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), dx , epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), dy , epsilon);

  BOOST_CHECK_CLOSE(s              (p(0), p(1)), s              (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x      )(p(0), p(1)), s.diff(x      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y      )(p(0), p(1)), s.diff(y      )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x   )(p(0), p(1)), s.diff(x, x   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, y   )(p(0), p(1)), s.diff(x, y   )(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, x)(p(0), p(1)), s.diff(x, x, x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x, x, y)(p(0), p(1)), s.diff(x, x, y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( constant_folding ) {
  nabla::expr::constant c(3);

  auto s = pow(2, c);

  BOOST_CHECK_EQUAL(8, s());
  BOOST_CHECK_EQUAL(0, s.diff<0>()());

  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(s          )>::value));
  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(s.diff<0>())>::value));
}

BOOST_AUTO_TEST_SUITE_END()
