#include <nabla/nabla.hh>
#include <boost/test/unit_test.hpp>

namespace {
  double epsilon = 1e-10;
}

BOOST_AUTO_TEST_SUITE( explog )

BOOST_AUTO_TEST_CASE( test_exp ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = exp(2 * x + 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           , std::exp(2 * p(0) + 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 2 * r                        , epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 4 * r                        , epsilon);

  BOOST_CHECK_CLOSE(s        (p(0), p(1)), s        (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p(0), p(1)), s.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p(0), p(1)), s.diff(y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_log ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = log(2 * x + 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           , std::log(2 * p(0) + 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p), 2 / (2 * p(0) + 4 * p(1))    , epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), 4 / (2 * p(0) + 4 * p(1))    , epsilon);

  BOOST_CHECK_CLOSE(s        (p(0), p(1)), s        (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p(0), p(1)), s.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p(0), p(1)), s.diff(y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_exp2 ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = exp2(x * x - 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           , std::pow(2, p(0) * p(0) - 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p),  2 * M_LN2 * p(0) * r              , epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), -4 * M_LN2        * r              , epsilon);

  BOOST_CHECK_CLOSE(s        (p(0), p(1)), s        (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p(0), p(1)), s.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p(0), p(1)), s.diff(y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_expm1 ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = expm1(x * x - 4 * y);

  nabla::vector<2> p { 2.0, 5.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           , std::expm1(p(0) * p(0) - 4 * p(1)), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p),  2 * p(0) * (r + 1)               , epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), -4        * (r + 1)               , epsilon);

  BOOST_CHECK_CLOSE(s        (p(0), p(1)), s        (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p(0), p(1)), s.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p(0), p(1)), s.diff(y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_log10 ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = log10(x * x - 4 * y);

  nabla::vector<2> p { 3.0, 1.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,             std::log10(p(0) * p(0) - 4 * p(1)) , epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p),  2 * p(0) / (M_LN10 * (p(0) * p(0) - 4 * p(1))), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), -4        / (M_LN10 * (p(0) * p(0) - 4 * p(1))), epsilon);

  BOOST_CHECK_CLOSE(s        (p(0), p(1)), s        (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p(0), p(1)), s.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p(0), p(1)), s.diff(y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_log2 ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = log2(x * x - 4 * y);

  nabla::vector<2> p { 3.0, 1.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,             std::log2(p(0) * p(0) - 4 * p(1)) , epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p),  2 * p(0) / (M_LN2 * (p(0) * p(0) - 4 * p(1))), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), -4        / (M_LN2 * (p(0) * p(0) - 4 * p(1))), epsilon);

  BOOST_CHECK_CLOSE(s        (p(0), p(1)), s        (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p(0), p(1)), s.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p(0), p(1)), s.diff(y)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( test_log1p ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();

  auto s = log1p(x * x - 4 * y);

  nabla::vector<2> p { 3.0, 1.0 };

  auto r = s(p);

  BOOST_CHECK_CLOSE(r           ,   std::log1p(p(0) * p(0) - 4 * p(1))    , epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p),  2 * p(0) / (p(0) * p(0) - 4 * p(1) + 1), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p), -4        / (p(0) * p(0) - 4 * p(1) + 1), epsilon);

  BOOST_CHECK_CLOSE(s        (p(0), p(1)), s        (p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(x)(p(0), p(1)), s.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE(s.diff(y)(p(0), p(1)), s.diff(y)(p), epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
