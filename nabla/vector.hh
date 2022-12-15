#ifndef INCLUDED_NABLA2_VECTOR_HH
#define INCLUDED_NABLA2_VECTOR_HH

#include "nabla_tag.hh"
#include <Eigen/Core>

namespace nabla {
  template<int N       > using vector = Eigen::Matrix<double, N, 1>;
  template<int N, int O> using matrix = Eigen::Matrix<double, N, O>;

  inline vector<0> make_vector() { return {}; }

  auto make_vector(traits::nabla_value auto&&... data) {
    vector<sizeof...(data)> result;

    typename decltype(result)::Index i = 0;
    for(double d : { static_cast<double>(data)... }) {
      result(i++) = d;
    }

    return result;
  }
}

#endif
