#ifndef INCLUDED_NABLA2_GAUSSCDF_HH
#define INCLUDED_NABLA2_GAUSSCDF_HH

#include "unary_functions.hh"

namespace nabla {
  namespace expr {
    template<traits::nabla_expression X>
    auto Phi(X &&x) {
      return 0.5 * (1 + erf(std::forward<X>(x) / M_SQRT2));
    }

    template<typename X, typename Mean, typename Sigma>
    auto gausscdf(X &&x, Mean &&mu, Sigma &&sigma)
      requires traits::is_nabla_tuple<X, Mean, Sigma>
    {
      return Phi((std::forward<X>(x) - std::forward<Mean>(mu)) / std::forward<Sigma>(sigma));
    }
  }
}

#endif
