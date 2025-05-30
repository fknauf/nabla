#ifndef INCLUDED_NABLA2_POLYNOMIAL_HH
#define INCLUDED_NABLA2_POLYNOMIAL_HH

#include "fwd.hh"

#include "chain.hh"
#include "conditional.hh"
#include "product.hh"

#include <cmath>
#include <type_traits>

namespace nabla::expr {
    template <traits::nabla_variable Base>
    auto pow(Base &&base, constant exponent) {
        return impl::make_chain(polynomial(exponent), std::forward<Base>(base));
    }

    class polynomial: public nabla_base<polynomial> {
    public:
        using nabla_base<polynomial>::diff;
        using nabla_base<polynomial>::operator();
        static index_type constexpr dimension = 1;

        polynomial(constant exponent):
            exponent_(exponent) {}

        template <index_type N>
        auto operator()(vector<N> const &vars) const -> double {
            static_assert(N >= dimension, "input value vector too short");
            return std::pow(vars(0), exponent_(vars));
        }

        template <index_type N>
        auto diff(variable<N> const & = {}) const {
            return diff_dispatch(std::bool_constant<N == 0>());
        }

    private:
        auto diff_dispatch(std::false_type) const -> constant {
            return 0;
        }

        auto diff_dispatch(std::true_type) const {
            return impl::make_conditional(
                [this](auto &&) { return exponent_.value() != 0.0; },
                exponent_ * polynomial(exponent_.value() - 1.0),
                0
            );
        }

        constant exponent_;
    };
}

#endif
