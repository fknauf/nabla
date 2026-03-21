#ifndef INCLUDED_NABLA2_NEGATION_HH
#define INCLUDED_NABLA2_NEGATION_HH

#include "fwd.hpp"
#include "nabla_base.hpp"
#include "variable.hpp"
#include "vector.hpp"

namespace nabla::expr {
    [[nodiscard]] inline auto operator-(constant const &x) -> constant {
        return -x.value();
    }

    template <traits::nabla_variable Expr>
    [[nodiscard]] auto operator-(Expr &&expr) -> negation<traits::plain_type<Expr>> {
        return { std::forward<Expr>(expr) };
    }

    /**
     * unary negation: -f
     */
    template <typename Expr>
    class negation:
        public nabla_base<negation<Expr>>
    {
    public:
        using nabla_base<negation>::diff;
        using nabla_base<negation>::operator();
        static index_type constexpr dimension = Expr::dimension;

        template <typename E>
        negation(E &&expr):
            expr_(std::forward<E>(expr)) {}

        template <index_type N>
        [[nodiscard]] auto diff(variable<N> const &v = {}) const {
            return -expr_.diff(v);
        }

        template <index_type N>
        [[nodiscard]] auto operator()(vector<N> const &vars) const -> double {
            static_assert(N >= dimension, "input value vector too short");
            return -expr_(vars);
        }

    private:
        Expr expr_;
    };
}

#endif
