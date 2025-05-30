#ifndef INCLUDED_NABLA2_CONSTANT_HH
#define INCLUDED_NABLA2_CONSTANT_HH

#include "fwd.hh"
#include "nabla_base.hh"
#include "vector.hh"

#include <cmath>

namespace nabla::expr {
    class constant: public nabla_base<constant> {
    public:
        using nabla_base<constant>::diff;
        using nabla_base<constant>::operator();
        static index_type constexpr dimension = 0;

        constexpr constant(double value) noexcept:
            value_(value) {}

        template <index_type N>
        constant diff(variable<N> const & = {}) const noexcept {
            static_assert(
                N >= dimension,
                "input value vector is shorter than zero elements? O.o"
            );
            return 0;
        }

        template <index_type N> double operator()(vector<N> const &) const {
            return value_;
        }

        // Benutzt in polynomial
        double value() const noexcept { return value_; }

    private:
        double value_;
    };

    namespace impl {
        inline double constant_value(constant const &c) { return c.value(); }

        inline double constant_value(traits::nabla_value auto &&c) { return c; }
    }

    // Arguably a pow function template does not belong here, but this header is
    // included in all of polynomial.hh, exponential.hh and power.hh, all of
    // which want to have it.
    template <typename Base, typename Exponent>
    inline constant pow(Base &&base, Exponent &&exponent)
        requires traits::constant_folding_possible<Base, Exponent>
    {
        return std::pow(
            impl::constant_value(std::forward<Base>(base)),
            impl::constant_value(std::forward<Exponent>(exponent))
        );
    }
}

#endif
