#ifndef INCLUDED_NABLA2_HESSIAN_HH
#define INCLUDED_NABLA2_HESSIAN_HH

#include "fwd.hh"
#include "gradient.hh"
#include "nabla_tag.hh"
#include "vector.hh"

#include <utility>

namespace nabla {
    namespace impl {
        template <int Dimension, int Row, int Column>
        struct hessian_matrix_builder {
            template <typename Function>
            static auto build(
                matrix<Dimension, Dimension> &dest,
                Function const &f,
                vector<Dimension> const &vars
            ) -> void {
                dest(Row, Column) = dest(Column, Row) = f.template diff<Row>().template diff<Column>()(vars);
                hessian_matrix_builder<Dimension, Row, Column + 1>::build(dest, f, vars);
            }
        };

        template <int Dimension, int N>
        struct hessian_matrix_builder<Dimension, N, N> {
            template <typename Function>
            static auto build(
                matrix<Dimension, Dimension> &dest,
                Function const &f,
                vector<Dimension> const &vars
            ) -> void {
                dest(N, N) = f.template diff<N>().template diff<N>()(vars);
                hessian_matrix_builder<Dimension, N + 1, 0>::build(dest, f, vars);
            }
        };

        template <int Dimension>
        struct hessian_matrix_builder<Dimension, Dimension, 0> {
            template <typename Function>
            static auto build(
                matrix<Dimension, Dimension> &,
                Function const &,
                vector<Dimension> const &
            ) -> void { }
        };
    }

    template <traits::nabla_expression Function, int N>
    auto hessian(Function const &f, vector<N> const &vars) {
        matrix<N, N> result;
        impl::hessian_matrix_builder<N, 0, 0>::build(result, f, vars);
        return result;
    }

    template <traits::nabla_expression Function, traits::nabla_value... Args>
    auto hessian(Function const &f, Args &&...args) {
        return hessian(f, make_vector(std::forward<Args>(args)...));
    }
}

#endif
