#ifndef INCLUDED_NABLA2_CONDITIONAL_HH
#define INCLUDED_NABLA2_CONDITIONAL_HH

#include "fwd.hh"

#include "nabla_base.hh"
#include "variable.hh"
#include "vector.hh"

#include <algorithm>

namespace nabla::expr {
    namespace impl {
        template <
            typename Condition,
            typename ExprTrue,
            typename ExprFalse
        >
        auto make_conditional(
            Condition &&condition,
            ExprTrue &&expr_true,
            ExprFalse &&expr_false
        ) -> conditional<
            traits::plain_type<Condition>,
            traits::nabla_equivalent<ExprTrue>,
            traits::nabla_equivalent<ExprFalse>
        > {
            return {
                std::forward<Condition>(condition),
                std::forward<ExprTrue>(expr_true),
                std::forward<ExprFalse>(expr_false)
            };
        }

        template <
            index_type MinDimension,
            typename Condition,
            typename ExprTrue,
            typename ExprFalse
        >
        auto make_conditional_with_min_dimension(
            Condition &&condition,
            ExprTrue &&expr_true,
            ExprFalse &&expr_false
        ) -> conditional<
            traits::plain_type<Condition>,
            traits::nabla_equivalent<ExprTrue>,
            traits::nabla_equivalent<ExprFalse>,
            MinDimension
        > {
            return {
                std::forward<Condition>(condition),
                std::forward<ExprTrue>(expr_true),
                std::forward<ExprFalse>(expr_false)
            };
        }
    }

    template <
        typename Condition,
        typename ExprTrue,
        typename ExprFalse,
        index_type MinDimension
    >
    class conditional:
        public nabla_base<conditional<Condition, ExprTrue, ExprFalse, MinDimension>>
    {
    public:
        using nabla_base<conditional>::diff;
        using nabla_base<conditional>::operator();
        static index_type constexpr dimension = std::max(
            MinDimension,
            std::max(ExprTrue::dimension, ExprFalse::dimension)
        );

        template <typename C, typename T, typename F>
        conditional(
            C &&condition,
            T &&expr_true,
            F &&expr_false
        ):
            condition_(std::forward<C>(condition)),
            expr_true_(std::forward<T>(expr_true)),
            expr_false_(std::forward<F>(expr_false))
        {}

        template <index_type N>
        auto operator()(vector<N> const &vars) const -> double {
            static_assert(N >= dimension, "input value vector too short");
            return condition_(vars) ? expr_true_(vars) : expr_false_(vars);
        }

        template <index_type N>
        auto diff(variable<N> const &var = {}) const {
            if constexpr (
                N < dimension
                && (!std::is_same_v<constant, ExprTrue> || !std::is_same_v<constant, ExprFalse>)
            ) {
                return impl::make_conditional(
                    condition_,
                    expr_true_.diff(var),
                    expr_false_.diff(var)
                );
            } else {
                return constant{0};
            }
        }

    private:
        Condition condition_;
        ExprTrue expr_true_;
        ExprFalse expr_false_;
    };
}

#endif
