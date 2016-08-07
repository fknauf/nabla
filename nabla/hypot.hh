#ifndef INCLUDED_NABLA2_HYPOT_HH
#define INCLUDED_NABLA2_HYPOT_HH

#include "fwd.hh"
#include "chain.hh"
#include "nabla_base.hh"
#include "unary_functions.hh"

#include <cmath>
#include <initializer_list>
#include <numeric>

namespace nabla {
  namespace expr {
    template<int Dimension>
    class mfunc_hypot : public nabla_base<mfunc_hypot<Dimension> > {
    public:
      using nabla_base<mfunc_hypot>::diff;
      using nabla_base<mfunc_hypot>::operator();
      static int constexpr dimension = Dimension;

      template<int N>
      double operator()(vector<N> const &vars) const {
        static_assert(N == dimension, "wrong number of arguments");
        return std::sqrt(vars.squaredNorm());
      }

      template<int N>
      auto diff(variable<N> const &var = {}) const {
        return diff_dispatch(var, std::bool_constant<N < dimension>());
      }

    private:
      template<int N> auto diff_dispatch(variable<N> const &var, std::true_type) const {
        return var / *this;
      }

      template<int N> constant diff_dispatch(variable<N> const &, std::false_type) const {
        return 0.0;
      }
    };

    // TODO: Implement constant folding
    template<typename... Inners, typename = std::enable_if_t<traits::is_regular_nabla_tuple<Inners...>>>
    auto hypot(Inners&&... inners) {
      return impl::make_chain(mfunc_hypot<sizeof...(Inners)>(), std::forward<Inners>(inners)...);
    }

    template<typename... Inners, typename = std::enable_if_t<traits::constant_folding_possible<Inners...>>>
    constant hypot(Inners&&... inners) {
      std::initializer_list<double> values = { [](double x) { return x * x; } (impl::constant_value(std::forward<Inners>(inners)))... };
      return std::sqrt(std::accumulate(begin(values), end(values), 0.0));
    }
  }
}

#endif
