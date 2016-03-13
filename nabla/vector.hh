#ifndef INCLUDED_NABLA2_VECTOR_HH
#define INCLUDED_NABLA2_VECTOR_HH

#include "nabla_tag.hh"
#include <pack/traits.hh>
#include <Eigen/Core>

namespace nabla {
  template<int N       > using vector = Eigen::Matrix<double, N, 1>;
  template<int N, int O> using matrix = Eigen::Matrix<double, N, O>;

  template<typename... T> auto make_vector(T&&... data) {
    static_assert(pack::applies_to_all<traits::is_nabla_value_type, T...>::value,
		  "Attempting to make vector from incompatible types");

    vector<sizeof...(T)> result;

    typename decltype(result)::Index i = 0;
    for(auto &&d : { data... }) {
      result(i++) = d;
    }

    return result;
  }
}

#endif
