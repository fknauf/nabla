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
      std::enable_if_t<traits::is_nabla_variable<Outer> && traits::is_nabla_tuple<Inner...>,
                       chain<traits::plain_type<Outer>, traits::nabla_equivalent<Inner>...> >
      make_chain(Outer &&outer, Inner&&... inner) {
        return { std::forward<Outer>(outer), std::forward<Inner>(inner)... };
      }

      template<typename... Inner>
      std::enable_if_t<traits::is_nabla_tuple<Inner...>, constant>
      make_chain(constant const &outer, Inner&&...) {
        return outer;
      }
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
      auto diff(variable<N> const &var = {}) const {
        return diff_dispatch(var, std::make_integer_sequence<int, Outer::dimension>());
      }

    private:
      template<int N, int... I>
      auto eval(vector<N> const &vars, std::integer_sequence<int, I...> const &) const {
        return outer_(make_vector(std::get<I>(inners_)(vars)...));
      }

      template<int N, int Direction, int... I>
      auto chain_diff_term(std::integer_sequence<int, I...> const &) const {
        return impl::make_chain(outer_.template diff<N>(), std::get<I>(inners_)...) * std::get<N>(inners_).template diff<Direction>();
      }

      template<int Direction, int ...I>
      auto diff_dispatch(variable<Direction> const &, std::integer_sequence<int, I...> const &seq) const {
        return (... + chain_diff_term<I, Direction>(seq));
      }

      Outer                outer_;
      std::tuple<Inner...> inners_;
    };
  }
}

#endif
