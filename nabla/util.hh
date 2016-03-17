#ifndef INCLUDED_NABLA2_UTIL_HH
#define INCLUDED_NABLA2_UTIL_HH

#include <type_traits>

namespace nabla {
  namespace expr {
    namespace impl {
      template<bool b> using bool_constant = std::integral_constant<bool, b>;
    }
  }
}

#endif
