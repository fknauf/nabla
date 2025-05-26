#ifndef INCLUDED_NABLA2_EXPONENTIAL_HH
#define INCLUDED_NABLA2_EXPONENTIAL_HH

#include "fwd.hh"

#include "chain.hh"
#include "product.hh"
#include "sum.hh"

#include <cmath>
#include <type_traits>

namespace nabla::expr {
    template <traits::nabla_variable Exponent>
    auto pow(constant base, Exponent &&exponent) {
        return impl::make_chain(
            exponential(base),
            std::forward<Exponent>(exponent)
        );
    }

    class exponential:
        public nabla_base<exponential>
    {
    public:
        using nabla_base<exponential>::diff;
        using nabla_base<exponential>::operator();
        static int constexpr dimension = 1;

        exponential(constant base):
            base_(base),
            log_base_(std::log(base.value()))
        {}

        template <int N>
        auto operator()(vector<N> const &vars) const -> double {
            static_assert(N >= dimension, "input value vector too short");
            return std::pow(base_(vars), vars(0));
        }

        template <int N>
        auto diff(variable<N> const & = {}) const {
            return diff_dispatch(std::bool_constant<N == 0>());
        }

    private:
        constant diff_dispatch(std::false_type) const { return 0; }

        auto diff_dispatch(std::true_type) const { return log_base_ * (*this); }

        constant base_;
        constant log_base_;
    };
}

#endif
