#ifndef INCLUDED_NABLA2_LOGARITHM_HH
#define INCLUDED_NABLA2_LOGARITHM_HH

#include "fwd.hh"
#include "chain.hh"
#include "division.hh"

namespace nabla {
  namespace expr {
    template<typename Expr, typename = std::enable_if_t<traits::is_nabla_variable<Expr>::value> >
    auto log(Expr &&expr) {
      return impl::make_chain(logarithm(), std::forward<Expr>(expr));
    }

    inline constant log(constant const &x) { return std::log(x.value()); }

    // natural logarithm, naturally.
    class logarithm : public nabla_base<logarithm> {
    public:
      using nabla_base<logarithm>::diff;
      using nabla_base<logarithm>::operator();
      static int constexpr dimension = 1;

      template<int N>
      double operator()(vector<N> const &vars) const {
        static_assert(N >= dimension, "input value vector too short");
        return std::log(vars(0));
      }

      template<int N>
      auto diff(variable<N> const &var = {}) const {
        return diff_dispatch(var, std::bool_constant<N == 0>());
      }

    private:
      template<int N>
      auto diff_dispatch(variable<N> const &x, std::true_type) const {
        static_assert(N == 0, "N must be zero here, or the check in diff is bogus.");
        return 1 / x;
      }

      template<int N>
      constant diff_dispatch(variable<N> const &, std::false_type) const {
        return 0.0;
      }
    };
  }
}

#endif
