#ifndef INCLUDED_NABLA2_LOGARITHM_HH
#define INCLUDED_NABLA2_LOGARITHM_HH

#include "chain.hh"
#include "division.hh"
#include "fwd.hh"

namespace nabla::expr {
    // natural logarithm, naturally.
    class logarithm:
        public nabla_base<logarithm>
    {
    public:
        using nabla_base<logarithm>::diff;
        using nabla_base<logarithm>::operator();
        static index_type constexpr dimension = 1;

        template <index_type N>
        auto operator()(vector<N> const &vars) const -> double {
            static_assert(N >= dimension, "input value vector too short");
            return std::log(vars(0));
        }

        template <index_type N>
        auto diff(variable<N> const &var = {}) const {
            if constexpr (N == 0) {
                return 1 / var;
            } else {
                return constant{0};
            }
        }
    };

    template <traits::nabla_variable Expr>
    auto log(Expr &&expr) {
        return impl::make_chain(logarithm(), std::forward<Expr>(expr));
    }

    inline auto log(constant const &x) -> constant {
        return std::log(x.value());
    }
}

#endif
