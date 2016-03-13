#ifndef INCLUDED_NABLA2_CHAIN_HH
#define INCLUDED_NABLA2_CHAIN_HH

#include "constant.hh"
#include "nabla_base.hh"
#include "product.hh"
#include "sum.hh"

#include <tuple>
#include <utility>

namespace nabla {
  namespace expr {
    // Mehrdimensionale Kettenregel.
    namespace impl {
      template<typename Outer, typename... Inner>
      std::enable_if_t<traits::is_nabla_expression<Outer>::value && traits::is_nabla_tuple<Inner...>::value,
		       chain<traits::plain_type<Outer>, traits::nabla_equivalent<Inner>...> >
	make_chain(Outer &&outer, Inner&&... inner) {
	return { std::forward<Outer>(outer), std::forward<Inner>(inner)... };
      }

      template<int Direction, int N, int... I, typename O, typename T>
      auto make_chain_diff_term(O &&outer, T &&inners, std::integer_sequence<int, I...>&&) {
	return make_chain(std::forward<O>(outer).template diff<N>(), std::get<I>(std::forward<T>(inners))...) * std::get<N>(std::forward<T>(inners)).template diff<Direction>();
      }

      // TODO: Mit C++17-Fold-Expressions ersetzen, wenn gcc 6 rauskommt.
      template<int Direction, int Dimension, int N>
      struct chain_diff_accumulator {
	template<typename O, typename T>
	static auto accumulate(O &&outer, T &&inners) {
	  return
	    chain_diff_accumulator<Direction, Dimension, N - 1>::accumulate(std::forward<O>(outer), std::forward<T>(inners))
	    + make_chain_diff_term<Direction, N>(std::forward<O>(outer), std::forward<T>(inners), std::make_integer_sequence<int, Dimension>());
	}
      };

      // Stopper
      template<int Direction, int Dimension>
      struct chain_diff_accumulator<Direction, Dimension, 0> {
	template<typename O, typename T>
	  static auto accumulate(O &&outer, T &&inners) {
	  return make_chain_diff_term<Direction, 0>(std::forward<O>(outer), std::forward<T>(inners), std::make_integer_sequence<int, Dimension>());
	}
      };
      
      // Kann bei dimension = 0 passieren
      template<int Direction, int Dimension>
      struct chain_diff_accumulator<Direction, Dimension, -1> {
	template<typename O, typename T>
	  static constant accumulate(O &&outer, T &&inners) {
	  return { 0.0 };
	}
      };
    }
    
    template<typename Outer, typename... Inner>
    class chain : public nabla_base<chain<Outer, Inner...> > {
    public:
      static_assert(Outer::dimension == sizeof...(Inner),
		    "Chain rule: Outer function does not expect the number of arguments given");
      
      using nabla_base<chain>::diff;
      static int constexpr dimension = std::max({ Inner::dimension... });

      template<typename O, typename... I>
      chain(O &&outer, I&&... inners)
	: outer_ (std::forward<O>(outer )   ),
	  inners_(std::forward<I>(inners)...)
      { }

      template<int N>
      auto operator()(vector<N> const &vars) const {
	return eval(vars, std::make_integer_sequence<int, dimension>());
      }

      template<int N>
      auto diff(variable<N> const & = {}) const {
	return impl::chain_diff_accumulator<N, dimension, dimension - 1>::accumulate(outer_, inners_);
      }
      
    private:
      template<int N, int... I>
      auto eval(vector<N> const &vars, std::integer_sequence<int, I...> &&) const {
	return outer_(make_vector(std::get<I>(inners_)(vars)...));
      }

      Outer                outer_;
      std::tuple<Inner...> inners_;
    };
  }
}

#endif
