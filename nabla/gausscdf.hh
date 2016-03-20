#ifndef INCLUDED_NABLA2_GAUSSCDF_HH
#define INCLUDED_NABLA2_GAUSSCDF_HH

#include "unary_functions.hh"

namespace nabla {
  namespace expr {
    template<typename X, typename = std::enable_if_t<traits::is_nabla_expression<X>::value> >
    auto Phi(X &&x) {
      return 0.5 * (1 + erf(std::forward<X>(x) / M_SQRT2));
    }

    template<typename X, typename Mean, typename Sigma, typename = std::enable_if_t<traits::is_nabla_tuple<X, Mean, Sigma>::value> >
    auto gausscdf(X &&x, Mean &&mu, Sigma &&sigma) {
      return Phi((std::forward<X>(x) - std::forward<Mean>(mu)) / std::forward<Sigma>(sigma));
    }
  }
}

#endif
