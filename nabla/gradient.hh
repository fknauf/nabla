#ifndef INCLUDED_NABLA2_GRADIENT_HH
#define INCLUDED_NABLA2_GRADIENT_HH

#include "nabla_tag.hh"
#include "vector.hh"

#include <utility>

namespace nabla {
  namespace impl {
    template<typename Function, int... I>
    vector<sizeof...(I)> gradient(Function &&f, vector<sizeof...(I)> const &vars, std::integer_sequence<int, I...> const &) {
      return make_vector(f.template diff<I>()(vars)...);
    }
  }

  template<typename Function, int N>
  vector<N> gradient(Function &&f, vector<N> const &vars) {
    return impl::gradient(std::forward<Function>(f), vars, std::make_integer_sequence<int, N>());
  }

  template<typename Function, typename... Args>
  std::enable_if_t<pack::applies_to_all<traits::is_nabla_value_type, Args...>::value,
		   vector<sizeof...(Args)> >
  gradient(Function &&f, Args&&... args) {
    return gradient(std::forward<Function>(f), make_vector(std::forward<Args>(args)...));
  }
}

#endif

