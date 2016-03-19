#ifndef INCLUDED_NABLA2_UNARY_FUNCTIONS_HH
#define INCLUDED_NABLA2_UNARY_FUNCTIONS_HH

#include "fwd.hh"

#include "chain.hh"
#include "conditional.hh"
#include "division.hh"
#include "exponential.hh"
#include "logarithm.hh"
#include "polynomial.hh"
#include "power.hh"
#include "product.hh"
#include "sum.hh"
#include "util.hh"

#include <cmath>

namespace nabla {
  namespace expr {
#define NABLA_DECLARE_UNARY_FUNCTION(name, expr_val, expr_diff)         \
    class ufunc_ ## name;                                               \
                                                                        \
    template<typename Expr>                                             \
    std::enable_if_t<traits::is_nabla_expression<Expr>::value,          \
                     chain<ufunc_ ## name, traits::plain_type<Expr> > > \
    name(Expr &&expr) {                                                 \
      return { ufunc_ ## name(), std::forward<Expr>(expr) };            \
    }                                                                   \
                                                                        \
    inline constant name(constant const &expr) {                        \
      double x = expr.value();                                          \
      static_cast<void>(x);                                             \
      return expr_val;                                                  \
    }                                                                   \
                                                                        \
    class ufunc_ ## name : public nabla_base<ufunc_ ## name> {          \
    public:                                                             \
      using nabla_base<ufunc_ ## name>::diff;                           \
      using nabla_base<ufunc_ ## name>::operator();                     \
      static int constexpr dimension = 1;                               \
                                                                        \
      template<int N>                                                   \
      auto operator()(vector<N> const &vars) const {                    \
        static_assert(N > 0, "Unary function " #name                    \
                      " requires an argument for evaluation");          \
        double x = vars(0);                                             \
        return (expr_val);                                              \
      }                                                                 \
                                                                        \
      template<int N>                                                   \
      auto diff(variable<N> const &var = {}) const {                    \
        return diff_dispatch(var, impl::bool_constant<N == 0>());       \
      }                                                                 \
                                                                        \
    private:                                                            \
      template<int N>                                                   \
      auto diff_dispatch(variable<N> const &x, std::true_type) const {  \
        auto &y = *this;                                                \
        static_cast<void>(x);                                           \
        static_cast<void>(y);                                           \
        return (expr_diff);                                             \
      }                                                                 \
                                                                        \
      template<int N>                                                   \
      constant diff_dispatch(variable<N> const &, std::false_type) const { \
        return 0;                                                       \
      }                                                                 \
    };

    NABLA_DECLARE_UNARY_FUNCTION(exp  , std::exp  (x), y)
    NABLA_DECLARE_UNARY_FUNCTION(exp2 , std::exp2 (x), M_LN2 * y)
    NABLA_DECLARE_UNARY_FUNCTION(expm1, std::expm1(x), y + 1)
    NABLA_DECLARE_UNARY_FUNCTION(log10, std::log10(x), 1 / (x * M_LN10))
    NABLA_DECLARE_UNARY_FUNCTION(log1p, std::log1p(x), 1 / (x + 1))
    NABLA_DECLARE_UNARY_FUNCTION(log2 , std::log2 (x), 1 / (x * M_LN2))

    NABLA_DECLARE_UNARY_FUNCTION(sin , std::sin (x),  cos(x))
    NABLA_DECLARE_UNARY_FUNCTION(cos , std::cos (x), -sin(x))
    NABLA_DECLARE_UNARY_FUNCTION(tan , std::tan (x),  1 / (cos(x) * cos(x)))

    NABLA_DECLARE_UNARY_FUNCTION(asin, std::asin(x),  1 / sqrt(1 - x * x))
    NABLA_DECLARE_UNARY_FUNCTION(acos, std::acos(x), -1 / sqrt(1 - x * x))
    NABLA_DECLARE_UNARY_FUNCTION(atan, std::atan(x), 1 / (1 + x * x))

    NABLA_DECLARE_UNARY_FUNCTION(sinh, std::sinh(x), cosh(x))
    NABLA_DECLARE_UNARY_FUNCTION(cosh, std::cosh(x), sinh(x))
    NABLA_DECLARE_UNARY_FUNCTION(tanh, std::tanh(x), 1 / (cosh(x) * cosh(x)))

    NABLA_DECLARE_UNARY_FUNCTION(asinh, std::asinh(x), 1 / sqrt(x * x + 1))
    NABLA_DECLARE_UNARY_FUNCTION(acosh, std::acosh(x), 1 / sqrt(x * x - 1))
    NABLA_DECLARE_UNARY_FUNCTION(atanh, std::atanh(x), 1 / (1 - x * x))

    NABLA_DECLARE_UNARY_FUNCTION(sqrt, std::sqrt(x), 0.5 / y)
    NABLA_DECLARE_UNARY_FUNCTION(cbrt, std::cbrt(x), 1 / (3 * y * y))

    NABLA_DECLARE_UNARY_FUNCTION(fabs, std::fabs(x), impl::make_conditional_with_min_dimension<1>([](auto &&vars) { return vars(0) >= 0; }, 1, -1))

    NABLA_DECLARE_UNARY_FUNCTION(erf , std::erf (x),  M_2_SQRTPI * exp(-x * x))
    NABLA_DECLARE_UNARY_FUNCTION(erfc, std::erfc(x), -M_2_SQRTPI * exp(-x * x))

#undef NABLA_DECLARE_UNARY_FUNCTION
  }
}

#endif
