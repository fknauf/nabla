#ifndef INCLUDED_NABLA2_PRODUCT_HH
#define INCLUDED_NABLA2_PRODUCT_HH

#include "fwd.hpp"
#include "nabla_base.hpp"
#include "sum.hpp"
#include "variable.hpp"
#include "vector.hpp"

#include <algorithm>

namespace nabla::expr {
    template <typename LHS, typename RHS>
    class product:
        public nabla_base<product<LHS, RHS>>
    {
    public:
        using nabla_base<product>::diff;
        using nabla_base<product>::operator();
        static index_type constexpr dimension =
            std::max(LHS::dimension, RHS::dimension);

        template <typename L, typename R>
        product(L &&lhs, R &&rhs):
            lhs_(std::forward<L>(lhs)), rhs_(std::forward<R>(rhs)) {}

        template <index_type N>
        [[nodiscard]] auto diff(variable<N> const &v = {}) const {
            return lhs_ * rhs_.diff(v) + lhs_.diff(v) * rhs_;
        }

        template <index_type N>
        [[nodiscard]] auto operator()(vector<N> const &vars) const -> double {
            static_assert(N >= dimension, "input value vector too short");
            return lhs_(vars) * rhs_(vars);
        }

        auto const &lhs() const noexcept { return lhs_; }
        auto const &rhs() const noexcept { return rhs_; }

    private:
        LHS lhs_;
        RHS rhs_;
    };

    [[nodiscard]] inline auto operator*(constant const &lhs, constant const &rhs) -> constant {
        return lhs.value() * rhs.value();
    }

    template <typename LHS, typename RHS>
    [[nodiscard]] auto operator*(
        LHS &&lhs,
        RHS &&rhs
    )
        requires traits::is_regular_nabla_tuple<LHS, RHS>
    {
        // deep constant folding: reform 2 * x * 2 to 4 * x etc.
        if constexpr(traits::is_nabla_constant<LHS> && traits::is_left_hand_constant<product, RHS>) {
            return (lhs * rhs.lhs()) * rhs.rhs();
        } else if constexpr(traits::is_nabla_constant<LHS> && traits::is_right_hand_constant<product, RHS>) {
            return (lhs * rhs.rhs()) * rhs.lhs();
        } else if constexpr(traits::is_left_hand_constant<product, LHS> && traits::is_nabla_constant<RHS>) {
            return (lhs.lhs() * rhs) * lhs.rhs();
        } else if constexpr(traits::is_right_hand_constant<product, LHS> && traits::is_nabla_constant<RHS>) {
            return lhs.lhs() * (lhs.rhs() * rhs);
        } else {
            return 
                product<
                    traits::nabla_equivalent<LHS>,
                    traits::nabla_equivalent<RHS>
                >{
                    std::forward<LHS>(lhs),
                    std::forward<RHS>(rhs)
                };
        }
    }
}

#endif
