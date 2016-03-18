#ifndef INCLUDED_NABLA2_NABLA_TAG_HH
#define INCLUDED_NABLA2_NABLA_TAG_HH

#include "fwd.hh"
#include "util.hh"

#include <pack/traits.hh>
#include <type_traits>
#include <utility>

namespace nabla {
  namespace expr {
    class nabla_tag {
    protected:
      ~nabla_tag() = default;
    };
  }

  namespace traits {
    template<typename    T> using plain_type               = std::remove_cv_t<std::remove_reference_t<T>>;
    template<typename    T> using is_nabla_expression      = std::is_base_of<expr::nabla_tag, plain_type<T>>;
    template<typename    T> using is_nabla_value_type      = std::is_convertible<plain_type<T>, double>;
    template<typename    T> using nabla_equivalent         = std::conditional_t<is_nabla_expression<T>::value,                plain_type<T> , expr::constant>;
    template<typename    T> using negated_nabla_equivalent = std::conditional_t<is_nabla_expression<T>::value, expr::negation<plain_type<T>>, expr::constant>;

    template<typename... T>
    using is_nabla_tuple = expr::impl::bool_constant<pack::applies_to_any<                is_nabla_expression,                                       T...>::value &&
						     pack::applies_to_all<pack::or_reduce<is_nabla_expression, is_nabla_value_type>::template trait, T...>::value>;

    template<typename LHS, typename RHS>
    using is_nabla_pair = is_nabla_tuple<LHS, RHS>;
  }
}

#endif
