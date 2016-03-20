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
    template<typename    T> using is_nabla_compatible      = expr::impl::bool_constant<is_nabla_expression<T>::value || is_nabla_value_type<T>::value>;
    template<typename    T> using nabla_equivalent         = std::conditional_t<is_nabla_expression<T>::value,                plain_type<T> , expr::constant>;
    template<typename    T> using negated_nabla_equivalent = std::conditional_t<is_nabla_expression<T>::value, expr::negation<plain_type<T>>, expr::constant>;
    
    template<typename    T> using is_nabla_constant        = std::integral_constant<bool, is_nabla_value_type<T>::value || std::is_same<expr::constant, T>::value>;
    template<typename    T> using is_nabla_variable        = std::integral_constant<bool, is_nabla_expression<T>::value && !is_nabla_constant<T>::value>;

    template<typename... T> using constant_folding_possible   = pack::applies_to_all<is_nabla_constant, T...>;
    template<typename... T> using constant_folding_impossible = std::integral_constant<bool, !constant_folding_possible<T...>::value>;
    
    template<typename... T>
    using is_nabla_tuple = expr::impl::bool_constant<pack::applies_to_any<                is_nabla_expression,                                       T...>::value &&
						     pack::applies_to_all<pack::or_reduce<is_nabla_expression, is_nabla_value_type>::template trait, T...>::value>;

    template<typename... T>
    using is_regular_nabla_tuple = std::integral_constant<bool, is_nabla_tuple<T...>::value && constant_folding_impossible<T...>::value>;
  }
}

#endif
