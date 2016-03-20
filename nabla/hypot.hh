#ifndef INCLUDED_NABLA2_HYPOT_HH
#define INCLUDED_NABLA2_HYPOT_HH

#include "fwd.hh"
#include "chain.hh"
#include "nabla_base.hh"
#include "unary_functions.hh"

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
	return diff_dispatch(var, impl::bool_constant<N < dimension>());
      }

    private:
      template<int N> auto diff_dispatch(variable<N> const &var, std::true_type) const {
	return var / *this;
      }

      template<int N> constant diff_dispatch(variable<N> const &, std::false_type) const {
	return 0.0;
      }
    };

    template<typename... Inners>
    std::enable_if_t<traits::is_nabla_tuple<Inners...>::value,
		     chain<mfunc_hypot<sizeof...(Inners)>,
			   traits::nabla_equivalent<Inners>...> >
    hypot(Inners&&... inners) {
      return { mfunc_hypot<sizeof...(Inners)>(), std::forward<Inners>(inners)... };
    }
  }
}

#endif
