#ifndef INCLUDED_NABLA2_LOGARITHM_HH
#define INCLUDED_NABLA2_LOGARITHM_HH

#include "chain.hh"
#include "division.hh"
#include "fwd.hh"

namespace nabla::expr {
    template <traits::nabla_variable Expr>
    auto log(Expr &&expr) {
        return impl::make_chain(logarithm(), std::forward<Expr>(expr));
    }

    inline auto log(constant const &x) -> constant {
        return std::log(x.value());
    }

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
            return diff_dispatch(var, std::bool_constant<N == 0>());
        }

    private:
        template <index_type N>
        auto diff_dispatch(variable<N> const &x, std::true_type) const {
            static_assert(N == 0, "N must be zero here, or the check in diff is bogus.");
            return 1 / x;
        }

        template <index_type N>
        auto diff_dispatch(variable<N> const &, std::false_type) const -> constant {
            return 0.0;
        }
    };
}

#endif
