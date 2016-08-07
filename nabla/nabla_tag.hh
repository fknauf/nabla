#ifndef INCLUDED_NABLA2_NABLA_TAG_HH
#define INCLUDED_NABLA2_NABLA_TAG_HH

#include "fwd.hh"

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
    template<typename... T> bool constexpr all(T&&... args) { return (args && ...); }
    template<typename... T> bool constexpr any(T&&... args) { return (args || ...); }

    template<typename    T> using plain_type                  = std::remove_cv_t<std::remove_reference_t<T>>;
    template<typename    T> using is_nabla_expression         = std::is_base_of<expr::nabla_tag, plain_type<T>>;
    template<typename    T> using is_nabla_value_type         = std::is_convertible<plain_type<T>, double>;
    template<typename    T> using is_nabla_compatible         = std::bool_constant<is_nabla_expression<T>::value || is_nabla_value_type<T>::value>;
    template<typename    T> using is_nabla_constant           = std::bool_constant<is_nabla_value_type<T>::value || std::is_same<expr::constant, plain_type<T>>::value>;
    template<typename    T> using is_nabla_variable           = std::bool_constant<is_nabla_expression<T>::value && !is_nabla_constant<T>::value>;

    template<typename    T> using nabla_equivalent            = std::conditional_t<is_nabla_expression<T>::value,                plain_type<T> , expr::constant>;
    template<typename    T> using negated_nabla_equivalent    = std::conditional_t<is_nabla_variable  <T>::value, expr::negation<plain_type<T>>, expr::constant>;

    template<typename... T> using constant_folding_possible   = std::bool_constant<(is_nabla_constant<T>::value && ...)>;
    template<typename... T> using constant_folding_impossible = std::bool_constant<!constant_folding_possible<T...>::value>;

    template<typename... T>
    using is_nabla_tuple = std::bool_constant<any(is_nabla_expression<T>::value...) &&
                                              all(is_nabla_compatible<T>::value...)>;

    template<typename... T>
    using is_regular_nabla_tuple = std::bool_constant<is_nabla_tuple<T...>::value && constant_folding_impossible<T...>::value>;
  }
}

#endif
