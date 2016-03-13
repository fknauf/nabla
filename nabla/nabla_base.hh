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
	return self().diff(head).diff(tail...);
      }

      /*     
      template<typename... Inner>
      std::enable_if_t<traits::is_nabla_tuple<Inner...>::value,
		       chain<Derived, traits::nabla_equivalent<Inner>...>>
	operator()(Inner&&... inner) const {
	return { self(), std::forward<Inner>(inner)... };
      }
      */
      
    private:
      Derived const &self() const noexcept { return static_cast<Derived const &>(*this);  }
    };
  }
}

#endif
