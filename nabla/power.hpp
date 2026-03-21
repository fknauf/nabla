#ifndef INCLUDED_NABLA2_POW_HH
#define INCLUDED_NABLA2_POW_HH

#include "fwd.hpp"
#include "logarithm.hpp"
#include "product.hpp"
#include "sum.hpp"

#include <cmath>

namespace nabla::expr {
    /**
     * Generic exponentiation: f^g
     */
    template <typename Base, typename Exponent>
    class power:
        public nabla_base<power<Base, Exponent>>
    {
    public:
        using nabla_base<power>::diff;
        using nabla_base<power>::operator();
        static index_type constexpr dimension =
            std::max(Base::dimension, Exponent::dimension);

        template <typename B, typename E>
        power(B &&base, E &&exponent):
            base_(std::forward<B>(base)),
            exponent_(std::forward<E>(exponent)) {}

        template <index_type N>
        [[nodiscard]] auto operator()(vector<N> const &vars) const -> double {
            static_assert(N >= dimension, "input value vector too short");
            return std::pow(base_(vars), exponent_(vars));
        }

        template <index_type N>
        [[nodiscard]] auto diff(variable<N> const &var = {}) const {
            if constexpr (N < dimension) {
                return (*this)
                       * (log(base_) * exponent_.diff(var)
                          + exponent_ * base_.diff(var) / base_);
            } else {
                return constant{0};
            }
        }

    private:
        Base base_;
        Exponent exponent_;
    };

    template <typename Base, typename Exponent>
    auto pow(
        Base &&base,
        Exponent &&exponent
    ) -> power<traits::plain_type<Base>, traits::plain_type<Exponent>>
        requires traits::is_pure_nabla_tuple<Base, Exponent>
                 && traits::constant_folding_impossible<Base, Exponent>
    {
        return { std::forward<Base>(base), std::forward<Exponent>(exponent) };
    }
}

#endif
