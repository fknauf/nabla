#ifndef INCLUDED_NABLA2_EXPONENTIAL_HH
#define INCLUDED_NABLA2_EXPONENTIAL_HH

#include "fwd.hh"

#include "chain.hh"
#include "product.hh"
#include "sum.hh"

#include <cmath>
#include <type_traits>

namespace nabla::expr {
    class exponential:
        public nabla_base<exponential>
    {
    public:
        using nabla_base<exponential>::diff;
        using nabla_base<exponential>::operator();
        static index_type constexpr dimension = 1;

        exponential(constant base):
            base_(base),
            log_base_(std::log(base.value()))
        {}

        template <index_type N>
        [[nodiscard]] auto operator()(vector<N> const &vars) const -> double {
            static_assert(N >= dimension, "input value vector too short");
            return std::pow(base_(vars), vars(0));
        }

        template <index_type N>
        [[nodiscard]] auto diff(variable<N> const & = {}) const {
            if constexpr (N == 0) {
                return log_base_ * (*this);
            } else {
                return constant{0};
            }
        }

    private:
        constant base_;
        constant log_base_;
    };

    template <traits::nabla_variable Exponent>
    [[nodiscard]] auto pow(
        constant base,
        Exponent &&exponent
    ) {
        return impl::make_chain(
            exponential(base),
            std::forward<Exponent>(exponent)
        );
    }
}

#endif
