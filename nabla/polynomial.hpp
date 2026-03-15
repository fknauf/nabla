#ifndef INCLUDED_NABLA2_POLYNOMIAL_HH
#define INCLUDED_NABLA2_POLYNOMIAL_HH

#include "fwd.hpp"

#include "chain.hpp"
#include "conditional.hpp"
#include "product.hpp"

#include <cmath>
#include <type_traits>

namespace nabla::expr {
    class polynomial: public nabla_base<polynomial> {
    public:
        using nabla_base<polynomial>::diff;
        using nabla_base<polynomial>::operator();
        static index_type constexpr dimension = 1;

        polynomial(constant exponent):
            exponent_(exponent) {}

        template <index_type N>
        [[nodiscard]] auto operator()(vector<N> const &vars) const -> double {
            static_assert(N >= dimension, "input value vector too short");
            return std::pow(vars(0), exponent_(vars));
        }

        template <index_type N>
        [[nodiscard]] auto diff(variable<N> const & = {}) const {
            if constexpr (N == 0) {
                return impl::make_conditional(
                    [cond=exponent_.value() != 0.0](auto &&) { return cond; },
                    exponent_ * polynomial(exponent_.value() - 1.0),
                    constant{0}
                );
            } else {
                return constant{0};
            }
        }

    private:
        constant exponent_;
    };

    template <traits::nabla_variable Base>
    [[nodiscard]] auto pow(Base &&base, constant exponent) {
        return impl::make_chain(polynomial{exponent}, std::forward<Base>(base));
    }
}

#endif
