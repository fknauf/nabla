#ifndef INCLUDED_NABLA2_GAUSSCDF_HH
#define INCLUDED_NABLA2_GAUSSCDF_HH

#include "unary_functions.hh"

namespace nabla {
  namespace expr {
    template<typename X>
    auto Phi(X const &x) {
      return 0.5 * (1 + erf(x / M_SQRT2));
    }

    template<typename X, typename Mean, typename Sigma>
    auto gausscdf(X const &x, Mean const &mu, Sigma const &sigma) {
      return Phi((x - mu) / sigma);
    }
  }
}

#endif
