#ifndef INCLUDED_NABLA2_CHAIN_HH
#define INCLUDED_NABLA2_CHAIN_HH

#include "constant.hh"
#include "nabla_base.hh"
#include "product.hh"
#include "sum.hh"

#include <tuple>
#include <utility>

namespace nabla::expr {
    // Mehrdimensionale Kettenregel.
    namespace impl {
        template <traits::nabla_variable Outer, typename... Inner>
        auto make_chain(
            Outer &&outer,
            Inner &&...inner
        ) -> chain<traits::plain_type<Outer>, traits::nabla_equivalent<Inner>...>
            requires traits::is_nabla_tuple<Inner...>
        {
            return {
                std::forward<Outer>(outer),
                std::forward<Inner>(inner)...
            };
        }

        template <typename... Inner>
        auto make_chain(
            constant const &outer,
            Inner &&...
        ) -> constant
            requires traits::is_nabla_tuple<Inner...>
        {
            return outer;
        }
    }

    template <typename Outer, typename... Inner>
    class chain: public nabla_base<chain<Outer, Inner...>> {
    public:
        static_assert(
            Outer::dimension <= sizeof...(Inner),
            "Chain rule: Outer function expects more arguments than are given"
        );

        using nabla_base<chain>::diff;
        using nabla_base<chain>::operator();
        static index_type constexpr dimension = std::max({ Inner::dimension... });

        template <typename O, typename... I>
        chain(
            O &&outer,
            I &&...inners
        ):
            outer_ { std::forward<O>(outer) },
            inners_ { std::forward<I>(inners)... }
        {}

        template <index_type N>
        auto operator()(vector<N> const &vars) const -> double {
            static_assert(N >= dimension, "input value vector too short");
            return eval(
                vars,
                std::make_integer_sequence<index_type, Outer::dimension>()
            );
        }

        template <index_type N>
        auto diff(variable<N> const &var = {}) const {
            return diff_dispatch(
                var,
                std::make_integer_sequence<index_type, Outer::dimension>()
            );
        }

    private:
        template <index_type N, index_type... I>
        auto eval(
            vector<N> const &vars,
            std::integer_sequence<index_type, I...> const &
        ) const {
            return outer_(make_vector(std::get<I>(inners_)(vars)...));
        }

        template <index_type N, index_type Direction, index_type... I>
        auto chain_diff_term(std::integer_sequence<index_type, I...> const &) const {
            return impl::make_chain(outer_.template diff<N>(), std::get<I>(inners_)...)
                   * std::get<N>(inners_).template diff<Direction>();
        }

        template <index_type Direction, index_type... I>
        auto diff_dispatch(
            variable<Direction> const &,
            std::integer_sequence<index_type, I...> const &seq
        ) const {
            return (... + chain_diff_term<I, Direction>(seq));
        }

        Outer outer_;
        std::tuple<Inner...> inners_;
    };
}

#endif
