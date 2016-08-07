#ifndef INCLUDED_NABLA2_VECTOR_HH
#define INCLUDED_NABLA2_VECTOR_HH

#include "nabla_tag.hh"
#include <Eigen/Core>

namespace nabla {
  template<int N       > using vector = Eigen::Matrix<double, N, 1>;
  template<int N, int O> using matrix = Eigen::Matrix<double, N, O>;

  inline vector<0> make_vector() { return {}; }

  template<typename... T> auto make_vector(T&&... data) {
    static_assert(traits::all(traits::is_nabla_value_type<T>::value...),
                  "Attempting to make vector from incompatible types");

    vector<sizeof...(T)> result;

    typename decltype(result)::Index i = 0;
    for(double d : { static_cast<double>(data)... }) {
      result(i++) = d;
    }

    return result;
  }
}

#endif
