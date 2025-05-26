#ifndef INCLUDED_NABLA2_SUM_HH
#define INCLUDED_NABLA2_SUM_HH

#include "fwd.hh"
#include "nabla_base.hh"
#include "negation.hh"
#include "vector.hh"

#include <algorithm>

namespace nabla::expr {
    inline auto operator+(
        constant const &lhs,
        constant const &rhs
    ) -> constant {
        return lhs.value() + rhs.value();
    }
    
    inline auto operator-(
        constant const &lhs,
        constant const &rhs
    ) -> constant {
        return lhs.value() - rhs.value();
    }

    template <typename LHS, typename RHS>
    auto operator+(
        LHS &&lhs,
        RHS &&rhs
    ) -> sum<
        traits::nabla_equivalent<LHS>,
        traits::nabla_equivalent<RHS>
    >
        requires traits::is_regular_nabla_tuple<LHS, RHS>
    {
        return { std::forward<LHS>(lhs), std::forward<RHS>(rhs) };
    }

    template <typename LHS, typename RHS>
    auto operator-(
        LHS &&lhs,
        RHS &&rhs
    ) -> sum<
        traits::nabla_equivalent<LHS>,
        traits::negated_nabla_equivalent<RHS>
    >
        requires traits::is_regular_nabla_tuple<LHS, RHS>
    {
        return std::forward<LHS>(lhs) + -std::forward<RHS>(rhs);
    }

    template <typename LHS, typename RHS>
    class sum:
        public nabla_base<sum<LHS, RHS>>
    {
    public:
        using nabla_base<sum>::diff;
        using nabla_base<sum>::operator();
        static int constexpr dimension =
            std::max(LHS::dimension, RHS::dimension);

        template <typename L, typename R>
        sum(L &&lhs, R &&rhs):
            lhs_(std::forward<L>(lhs)),
            rhs_(std::forward<R>(rhs))
        {}

        template <int N>
        auto diff(variable<N> const &v = {}) const {
            return lhs_.diff(v) + rhs_.diff(v);
        }

        template <int N>
        auto operator()(vector<N> const &vars) const -> double {
            static_assert(N >= dimension, "input value vector too short");
            return lhs_(vars) + rhs_(vars);
        }

    private:
        LHS lhs_;
        RHS rhs_;
    };
}

#endif
