#ifndef INCLUDED_NABLA2_NABLA_BASE_HH
#define INCLUDED_NABLA2_NABLA_BASE_HH

#include "fwd.hh"
#include "nabla_tag.hh"

namespace nabla {
  namespace expr {
    template<typename Derived>
    class nabla_base : public nabla_tag {
    public:
      template<int N, int... O>
      auto diff(variable<N> const &head,
		variable<O> const &... tail) const {
	return static_cast<Derived const &>(*this).diff(head).diff(tail...);
      }
    };
  }
}

#endif
