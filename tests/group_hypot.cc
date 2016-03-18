#include <nabla/chain.hh>
#include <nabla/hypot.hh>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( chain )

namespace {
  double epsilon = 1e-7;
}

BOOST_AUTO_TEST_CASE( n1_veclength ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();
  auto z = nabla::expr::variable<2>();

  auto s = hypot(x * y, x * z, 2, y * z);

  nabla::vector<4> p(1.0, -3.0, 2.0, 5.0);

  auto r = s(p);

  double exv = std::sqrt(std::pow(p(0) * p(1), 2)
                         + std::pow(p(0) * p(2), 2)
                         + std::pow(2, 2)
                         + std::pow(p(1) * p(2), 2));

  double dx = p(0) * (p(1) * p(1) + p(2) * p(2)) / exv;
  double dy = p(1) * (p(0) * p(0) + p(2) * p(2)) / exv;
  double dz = p(2) * (p(0) * p(0) + p(1) * p(1)) / exv;

  BOOST_CHECK_CLOSE(exv, r, epsilon);

  BOOST_CHECK_CLOSE(dx, s.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE(dy, s.diff(y)(p), epsilon);
  BOOST_CHECK_CLOSE(dz, s.diff(z)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( starts_with_constant ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();
  auto z = nabla::expr::variable<2>();

  auto s = hypot(2, x * z, 2, y * z);

  nabla::vector<4> p(1.0, -3.0, 2.0, 5.0);

  auto r = s(p);

  double exv = std::sqrt(std::pow(2, 2)
                         + std::pow(p(0) * p(2), 2)
                         + std::pow(2, 2)
                         + std::pow(p(1) * p(2), 2));

  double dx = p(0) * (p(2) * p(2)) / exv;
  double dy = p(1) * (p(2) * p(2)) / exv;
  double dz = p(2) * (p(0) * p(0) + p(1) * p(1)) / exv;

  BOOST_CHECK_CLOSE(exv, r, epsilon);

  BOOST_CHECK_CLOSE(dx, s.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE(dy, s.diff(y)(p), epsilon);
  BOOST_CHECK_CLOSE(dz, s.diff(z)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( ends_with_constant ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();
  auto z = nabla::expr::variable<2>();

  auto s = hypot(x * z, 2, y * z, 2);

  nabla::vector<4> p(1.0, -3.0, 2.0, 5.0);

  auto r = s(p);

  double exv = std::sqrt(std::pow(2, 2)
                         + std::pow(p(0) * p(2), 2)
                         + std::pow(2, 2)
                         + std::pow(p(1) * p(2), 2));

  double dx = p(0) * (p(2) * p(2)) / exv;
  double dy = p(1) * (p(2) * p(2)) / exv;
  double dz = p(2) * (p(0) * p(0) + p(1) * p(1)) / exv;

  BOOST_CHECK_CLOSE(exv, r, epsilon);

  BOOST_CHECK_CLOSE(dx, s.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE(dy, s.diff(y)(p), epsilon);
  BOOST_CHECK_CLOSE(dz, s.diff(z)(p), epsilon);
}

BOOST_AUTO_TEST_CASE( all_constant ) {
  auto x = nabla::expr::variable<0>();
  auto y = nabla::expr::variable<1>();
  auto z = nabla::expr::variable<2>();

  nabla::expr::constant one  (1);
  nabla::expr::constant two  (2);
  nabla::expr::constant three(3);
  nabla::expr::constant four (4);

  auto s = nabla::expr::hypot(one, two, three, four);

  nabla::vector<4> p(1.0, -3.0, 2.0, 5.0);

  auto r = s(p);

  double exv = std::sqrt(1 + 4 + 9 + 16);

  double dx = 0;
  double dy = 0;
  double dz = 0;

  BOOST_CHECK_CLOSE(exv, r, epsilon);

  BOOST_CHECK_CLOSE(dx, s.diff(x)(p), epsilon);
  BOOST_CHECK_CLOSE(dy, s.diff(y)(p), epsilon);
  BOOST_CHECK_CLOSE(dz, s.diff(z)(p), epsilon);

  BOOST_CHECK((std::is_same<nabla::expr::constant, decltype(s.diff(x))>::value));
}

BOOST_AUTO_TEST_SUITE_END()
