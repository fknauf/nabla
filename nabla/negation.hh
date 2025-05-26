#ifndef INCLUDED_NABLA2_NEGATION_HH
#define INCLUDED_NABLA2_NEGATION_HH

#include "fwd.hh"
#include "nabla_base.hh"
#include "variable.hh"
#include "vector.hh"

namespace nabla::expr {
    inline auto operator-(constant const &x) -> constant {
        return -x.value();
    }

    template <traits::nabla_variable Expr>
    auto operator-(Expr &&expr) -> negation<traits::plain_type<Expr>> {
        return { std::forward<Expr>(expr) };
    }

    template <typename Expr>
    class negation:
        public nabla_base<negation<Expr>>
    {
    public:
        using nabla_base<negation>::diff;
        using nabla_base<negation>::operator();
        static int constexpr dimension = Expr::dimension;

        template <typename E>
        negation(E &&expr):
            expr_(std::forward<E>(expr)) {}

        template <int N>
        auto diff(variable<N> const &v = {}) const {
            return -expr_.diff(v);
        }

        template <int N>
        auto operator()(vector<N> const &vars) const -> double {
            static_assert(N >= dimension, "input value vector too short");
            return -expr_(vars);
        }

    private:
        Expr expr_;
    };
}

#endif
