#ifndef INCLUDED_NABLA2_GAUSSCDF_HH
#define INCLUDED_NABLA2_GAUSSCDF_HH

#include "unary_functions.hh"

namespace nabla::expr {
    template <traits::nabla_expression X>
    [[nodiscard]] auto Phi(X &&x) {
        return 0.5 * (1 + erf(std::forward<X>(x) / M_SQRT2));
    }

    template <typename X, typename Mean, typename Sigma>
    [[nodiscard]] auto gausscdf(X &&x, Mean &&mu, Sigma &&sigma)
        requires traits::is_nabla_tuple<X, Mean, Sigma>
    {
        return Phi(
            (std::forward<X>(x) - std::forward<Mean>(mu))
            / std::forward<Sigma>(sigma)
        );
    }

    template<typename X>
    [[nodiscard]] auto phi(X &&x) 
        requires traits::is_nabla_expression<X>
    {
        return (1 / std::sqrt(2 * M_PI)) * exp(-(std::forward<X>(x) * std::forward<X>(x)) / 2);
    }

    template <typename X, typename Mean, typename Sigma>
    [[nodiscard]] auto gausspdf(X &&x, Mean &&mu, Sigma &&sigma)
        requires traits::is_nabla_tuple<X, Mean, Sigma>
    {
        return phi((std::forward<X>(x) - std::forward<Mean>(mu)) / std::forward<Sigma>(sigma))
            / std::forward<Sigma>(sigma);
    }
}

#endif
