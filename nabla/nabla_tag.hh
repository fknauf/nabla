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
        template <typename... T> bool constexpr all(T &&...args) {
            return (args && ...);
        }
        template <typename... T> bool constexpr any(T &&...args) {
            return (args || ...);
        }

        template <typename T>
        using plain_type = std::remove_cv_t<std::remove_reference_t<T>>;

        template <typename T>
        bool constexpr is_nabla_expression =
            std::is_base_of<expr::nabla_tag, plain_type<T>>::value;
        template <typename T>
        bool constexpr is_nabla_value_type =
            std::is_convertible<plain_type<T>, double>::value;
        template <typename T>
        bool constexpr is_nabla_compatible =
            is_nabla_expression<T> || is_nabla_value_type<T>;
        template <typename T>
        bool constexpr is_nabla_constant =
            is_nabla_value_type<T>
            || std::is_same<expr::constant, plain_type<T>>::value;
        template <typename T>
        bool constexpr is_nabla_variable =
            is_nabla_expression<T> && !is_nabla_constant<T>;

        template <typename T>
        using nabla_equivalent = std::conditional_t<
            is_nabla_expression<T>,
            plain_type<T>,
            expr::constant>;
        template <typename T>
        using negated_nabla_equivalent = std::conditional_t<
            is_nabla_variable<T>,
            expr::negation<plain_type<T>>,
            expr::constant>;

        template <typename... T>
        bool constexpr constant_folding_possible =
            (is_nabla_constant<T> && ...);
        template <typename... T>
        bool constexpr constant_folding_impossible =
            !constant_folding_possible<T...>;

        template <typename... T>
        bool constexpr is_pure_nabla_tuple = all(is_nabla_expression<T>...);
        template <typename... T>
        bool constexpr is_nabla_tuple =
            any(is_nabla_expression<T>...) && all(is_nabla_compatible<T>...);
        template <typename... T>
        bool constexpr is_regular_nabla_tuple =
            is_nabla_tuple<T...> && constant_folding_impossible<T...>;

        template <typename T>
        concept nabla_expression = is_nabla_expression<T>;
        template <typename T>
        concept nabla_value = is_nabla_value_type<T>;
        template <typename T>
        concept nabla_compatible = is_nabla_compatible<T>;
        template <typename T>
        concept nabla_constant = is_nabla_constant<T>;
        template <typename T>
        concept nabla_variable = is_nabla_variable<T>;

        template <typename T>
        concept nabla_function = requires(T f) {
            { f(0.0) } -> std::same_as<double>;
            { f(0, 1.2, 3.f) } -> std::same_as<double>;
        };
    }
}

#endif
