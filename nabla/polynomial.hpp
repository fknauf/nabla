#ifndef INCLUDED_NABLA2_POLYNOMIAL_HH
#define INCLUDED_NABLA2_POLYNOMIAL_HH

#include "fwd.hpp"

#include "chain.hpp"
#include "product.hpp"

#include <cmath>
#include <type_traits>

namespace nabla::expr {
    namespace impl {
        /** 
         * Zero-cost flag. We don't want to waste compute to check a flag or memory for
         * the flag when we know the value at compile time, and this gives us a way to
         * have a flag or not have it depending on that compile-time information.
         */
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

    /**
     * Represents a single polynomial term, i.e. x^constant.
     *
     * The only complication here is that polynomials collapse to zero in
     * differentiation when the exponent is 0, and that the naive differentiation
     * 0 * x^-1 is numerically unstable at x == 0. So we need to handle that special
     * case. We use the gated bool from above to make this zero-cost for the source
     * function, where we know no differentiation (and therefore no collapse) has
     * happened yet.
     */
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
            has_collapsed_ { collapsed }
        {}

        template <index_type N>
        [[nodiscard]] auto operator()(vector<N> const &vars) const -> double {
            static_assert(N >= dimension, "input value vector too short");

            if(has_collapsed_()) {
                return 0.0;
            }

            return std::pow(vars(0), exponent_(vars));
        }

        template <index_type N>
        [[nodiscard]] auto diff(variable<N> const & = {}) const {
        if constexpr (N == 0) {
            return exponent_ * polynomial<true>(exponent_.value() - 1.0, has_collapsed_() || exponent_.value() == 0.0);
        } else {
            return constant{0};
        }
    }

    protected:
        constant exponent_;

        #ifdef _MSC_VER
        [[msvc::no_unique_address]]
        #else
        [[no_unique_address]]
        #endif
        impl::gated_bool<collapsable> has_collapsed_;
    };

    template <traits::nabla_variable Base>
    [[nodiscard]] auto pow(Base &&base, constant exponent) {
        return impl::make_chain(polynomial{exponent}, std::forward<Base>(base));
    }
}

#endif
