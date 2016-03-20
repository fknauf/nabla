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

  template<typename Function, int N, typename = std::enable_if_t<traits::is_nabla_expression<Function>::value> >
  auto gradient(Function const &f, vector<N> const &vars) {
    return impl::gradient(f, vars, std::make_integer_sequence<int, N>());
  }

  template<typename Function,
	   typename... Args,
	   typename = std::enable_if_t<traits::is_nabla_expression<Function>::value &&
				       pack::applies_to_all<traits::is_nabla_value_type, Args...>::value> >
  auto gradient(Function const &f, Args&&... args) {
    return gradient(f, make_vector(std::forward<Args>(args)...));
  }
}

#endif

