nobase_include_HEADERS = \
  nabla/constant.hh \
  nabla/exponential.hh \
  nabla/fwd.hh \
  nabla/logarithm.hh \
  nabla/nabla.hh \
  nabla/nabla_base.hh \
  nabla/nabla_tag.hh \
  nabla/negation.hh \
  nabla/polynomial.hh \
  nabla/power.hh \
  nabla/product.hh \
  nabla/sum.hh \
  nabla/unary_functions.hh \
  nabla/variable.hh \
  nabla/vector.hh

check_PROGRAMS = tests/test
TESTS          = tests/test

tests_test_SOURCES = \
  tests/test_main.cc \
  tests/group_constant.cc \
  tests/group_variable.cc \
  tests/group_negation.cc \
  tests/group_sum.cc \
  tests/group_product.cc \
  tests/group_division.cc \
  tests/group_chain.cc \
  tests/group_conditional.cc \
  tests/group_polynomial.cc \
  tests/group_exponential.cc \
  tests/group_logarithm.cc \
  tests/group_power.cc \
  tests/group_unary_functions.cc \
  tests/group_trigonometry.cc \
  tests/group_explog.cc \
  tests/group_hyperbolic.cc

# gcc 5 with -std=c++11 complains about Eigen's use of std::bind1st, std::bind2nd,
# -Wno-deprecated-declarations makes it shut up
tests_test_CPPFLAGS = -I $(top_srcdir) \
                      $$(pkg-config --cflags eigen3) -D EIGEN_MPL2_ONLY \
                      -D BOOST_TEST_DYN_LINK \
                      -Wno-deprecated-declarations -Wall -Wextra
tests_test_CXXFLAGS = -g -O0
tests_test_LDADD    = -lboost_unit_test_framework
