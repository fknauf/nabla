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
      std::enable_if_t<traits::is_nabla_variable<Outer>::value && traits::is_nabla_tuple<Inner...>::value,
		       chain<traits::plain_type<Outer>, traits::nabla_equivalent<Inner>...> >
      make_chain(Outer &&outer, Inner&&... inner) {
	return { std::forward<Outer>(outer), std::forward<Inner>(inner)... };
      }

      template<typename... Inner>
      std::enable_if_t<traits::is_nabla_tuple<Inner...>::value, constant>
      make_chain(constant const &outer, Inner&&...) {
	return outer;
      }

      template<int Direction, int N, int... I, typename O, typename T>
      auto make_chain_diff_term(O const &outer, T const &inners, std::integer_sequence<int, I...> const &) {
	return make_chain(outer.template diff<N>(), std::get<I>(inners)...) * std::get<N>(inners).template diff<Direction>();
      }

      // TODO: Mit C++17-Fold-Expressions ersetzen, wenn gcc 6 rauskommt.
      template<int Direction, int N>
      struct chain_diff_accumulator {
	template<typename O, typename T>
	static auto accumulate(O const &outer, T const &inners) {
	  return accumulate_dispatch(outer, inners, std::is_same<constant, std::tuple_element_t<N, traits::plain_type<T> > >());
	}
	  
	template<typename O, typename T>
	static auto accumulate_dispatch(O const &outer, T const &inners, std::true_type) {
	  return
	    chain_diff_accumulator<Direction, N - 1>::accumulate(outer, inners);
	}

	template<typename O, typename T>
	static auto accumulate_dispatch(O const &outer, T const &inners, std::false_type) {
	  return
	    accumulate_dispatch(outer, inners, std::true_type())
	    + make_chain_diff_term<Direction, N>(outer, inners, std::make_integer_sequence<int, traits::plain_type<O>::dimension>());
	}
      };

      // Stopper
      template<int Direction>
      struct chain_diff_accumulator<Direction, 0> {
	template<typename O, typename T>
	static auto accumulate(O const &outer, T const &inners) {
	  return accumulate_dispatch(outer, inners, std::is_same<constant, std::tuple_element_t<0, traits::plain_type<T> > >());
	}

	template<typename O, typename T>
	static constant accumulate_dispatch(O const &, T const &, std::true_type) {
	  return 0;
	}
	
	template<typename O, typename T>
	static auto accumulate_dispatch(O const &outer, T const &inners, std::false_type) {
	  return make_chain_diff_term<Direction, 0>(outer, inners, std::make_integer_sequence<int, traits::plain_type<O>::dimension>());
	}
      };
      
      // Kann bei dimension = 0 passieren
      template<int Direction>
      struct chain_diff_accumulator<Direction, -1> {
	template<typename O, typename T>
	static constant accumulate(O const &, T const &) {
	  return 0;
	}
      };
    }
    
    template<typename Outer, typename... Inner>
    class chain : public nabla_base<chain<Outer, Inner...> > {
    public:
      static_assert(Outer::dimension <= sizeof...(Inner),
		    "Chain rule: Outer function expects more arguments than are given");
      
      using nabla_base<chain>::diff;
      using nabla_base<chain>::operator();
      static int constexpr dimension = std::max({ Inner::dimension... });

      template<typename O, typename... I>
      chain(O &&outer, I&&... inners)
	: outer_ (std::forward<O>(outer )   ),
	  inners_(std::forward<I>(inners)...)
      { }

      template<int N>
      double operator()(vector<N> const &vars) const {
	static_assert(N >= dimension, "input value vector too short");
	return eval(vars, std::make_integer_sequence<int, Outer::dimension>());
      }

      template<int N>
      auto diff(variable<N> const & = {}) const {
	return impl::chain_diff_accumulator<N, Outer::dimension - 1>::accumulate(outer_, inners_);
      }
      
    private:
      template<int N, int... I>
      auto eval(vector<N> const &vars, std::integer_sequence<int, I...> const &) const {
	return outer_(make_vector(std::get<I>(inners_)(vars)...));
      }

      Outer                outer_;
      std::tuple<Inner...> inners_;
    };
  }
}

#endif
