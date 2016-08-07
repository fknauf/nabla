#ifndef INCLUDED_NABLA2_NABLA_BASE_HH
#define INCLUDED_NABLA2_NABLA_BASE_HH

#include "fwd.hh"
#include "nabla_tag.hh"
#include "vector.hh"

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

      template<typename... Values>
      std::enable_if_t<(traits::is_nabla_value_type<traits::plain_type<Values>> && ...), double>
      operator()(Values&&... values) const {
        return self()(make_vector(std::forward<Values>(values)...));
      }

    private:
      Derived const &self() const noexcept { return static_cast<Derived const &>(*this);  }
    };
  }
}

#endif
