#ifndef INCLUDED_NABLA2_HESSIAN_HH
#define INCLUDED_NABLA2_HESSIAN_HH

#include "fwd.hh"
#include "gradient.hh"
#include "nabla_tag.hh"
#include "vector.hh"

#include <utility>

namespace nabla {
  namespace impl {
    template<int Dimension, int Row, int Column>
    struct hessian_matrix_builder {
      template<typename Function>
      static void build(matrix<Dimension, Dimension> &dest, Function &&f, vector<Dimension> const &vars) {
	dest(Row, Column) = dest(Column, Row) = f.template diff<Row>().template diff<Column>()(vars);
	hessian_matrix_builder<Dimension, Row, Column + 1>::build(dest, std::forward<Function>(f), vars);
      }
    };

    template<int Dimension, int N>
    struct hessian_matrix_builder<Dimension, N, N> {
      template<typename Function>
      static void build(matrix<Dimension, Dimension> &dest, Function &&f, vector<Dimension> const &vars) {
	dest(N, N) = f.template diff<N>().template diff<N>()(vars);
	hessian_matrix_builder<Dimension, N + 1, 0>::build(dest, std::forward<Function>(f), vars);
      }
    };

    template<int Dimension> struct hessian_matrix_builder<Dimension, Dimension, 0> {
      template<typename Function> static void build(matrix<Dimension, Dimension> &, Function &&, vector<Dimension> const &) { }
    };
  }

  template<typename Function, int N>
  std::enable_if_t<traits::is_nabla_expression<Function>::value, matrix<N, N> >
  hessian(Function &&f, vector<N> const &vars) {
    matrix<N, N> result;
    impl::hessian_matrix_builder<N, 0, 0>::build(result, std::forward<Function>(f), vars);
    return result;
  }

  template<typename Function, typename... Args>
  std::enable_if_t<traits::is_nabla_expression<Function>::value && pack::applies_to_all<traits::is_nabla_value_type, Args...>::value,
		   matrix<sizeof...(Args), sizeof...(Args)> >
  hessian(Function &&f, Args&&... args) {
    return hessian(std::forward<Function>(f), make_vector(std::forward<Args>(args)...));
  }
}

#endif
