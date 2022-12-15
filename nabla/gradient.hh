#ifndef INCLUDED_NABLA2_GRADIENT_HH
#define INCLUDED_NABLA2_GRADIENT_HH

#include "nabla_tag.hh"
#include "vector.hh"

#include <utility>

namespace nabla {
  namespace impl {
    template<typename Function, int... I>
    auto gradient(Function const &f, vector<sizeof...(I)> const &vars, std::integer_sequence<int, I...>) {
      return make_vector(f.template diff<I>()(vars)...);
    }
  }

  template<traits::nabla_expression Function, int N>
  auto gradient(Function const &f, vector<N> const &vars) {
    return impl::gradient(f, vars, std::make_integer_sequence<int, N>());
  }

  template<traits::nabla_expression Function, traits::nabla_value... Args>
  auto gradient(Function const &f, Args&&... args) {
    return gradient(f, make_vector(std::forward<Args>(args)...));
  }
}

#endif
