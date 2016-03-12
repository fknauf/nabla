#ifndef INCLUDED_NABLA2_VECTOR_HH
#define INCLUDED_NABLA2_VECTOR_HH

#include <Eigen/Core>

namespace nabla {
  template<int N       > using vector = Eigen::Matrix<double, N, 1>;
  template<int N, int O> using matrix = Eigen::Matrix<double, N, O>;
}

#endif
