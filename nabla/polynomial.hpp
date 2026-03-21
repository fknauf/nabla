#ifndef INCLUDED_NABLA2_POLYNOMIAL_HH
#define INCLUDED_NABLA2_POLYNOMIAL_HH

#include "fwd.hpp"

#include "chain.hpp"
#include "product.hpp"

#include <cmath>
#include <type_traits>

namespace nabla::expr {
    namespace impl {
        template<bool available, bool default_value = false>
        class gated_bool {
        public:
            gated_bool(bool value):
                value_ { value }
            {}

            auto operator()() const noexcept {
                return value_;
            }

        private:
            bool value_;
        };

        template<bool default_value>
        struct gated_bool<false, default_value> {
            gated_bool(bool) {}

            auto operator()() const noexcept {
                return default_value;
            }
        };
    }

    template<bool collapsable>
    class polynomial:
        public nabla_base<polynomial<collapsable>>
    {
    public:
        using nabla_base<polynomial<collapsable>>::diff;
        using nabla_base<polynomial<collapsable>>::operator();
        static index_type constexpr dimension = 1;

        polynomial(constant exponent, bool collapsed = false):
            exponent_ { exponent },
            is_collapsed_ { collapsed }
        {}

        template <index_type N>
        [[nodiscard]] auto operator()(vector<N> const &vars) const -> double {
            static_assert(N >= dimension, "input value vector too short");

            if(is_collapsed_()) {
                return 0.0;
            }

            return std::pow(vars(0), exponent_(vars));
        }

        template <index_type N>
        [[nodiscard]] auto diff(variable<N> const & = {}) const {
        if constexpr (N == 0) {
            return exponent_ * polynomial<true>(exponent_.value() - 1.0, is_collapsed_() || exponent_.value() == 0.0);
        } else {
            return constant{0};
        }
    }

    protected:
        constant exponent_;
        [[no_unique_address]] impl::gated_bool<collapsable> is_collapsed_;
    };

    template <traits::nabla_variable Base>
    [[nodiscard]] auto pow(Base &&base, constant exponent) {
        return impl::make_chain(polynomial{exponent}, std::forward<Base>(base));
    }
}

#endif
