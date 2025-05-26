#ifndef INCLUDED_NABLA2_FWD_HH
#define INCLUDED_NABLA2_FWD_HH

#ifdef NABLA_BACKEND_ARMADILLO
#include <armadillo>

namespace nabla {
    using index_type = arma::uword;

    template <index_type N> using vector = arma::Col<double>::fixed<N>;
    template <index_type N, index_type O> using matrix = arma::Mat<double>::fixed<N, O>;
}
#else
#include <Eigen/Core>

namespace nabla {
    using index_type = int;
    template <index_type N> using vector = Eigen::Matrix<double, N, 1>;
    template <index_type N, index_type O> using matrix = Eigen::Matrix<double, N, O>;
}
#endif

namespace nabla::expr {
    class tag;
    class constant;
    template <index_type> class variable;
    template <typename Expr> class negation;
    template <typename LHS, typename RHS> class sum;
    template <typename LHS, typename RHS> class product;
    template <typename LHS, typename RHS> class division;

    class polynomial;
    class exponential;
    class logarithm;
    template <typename Base, typename Exponent> class power;

    template <typename Outer, typename... Inner> class chain;
    template <
        typename Condition,
        typename ExprTrue,
        typename ExprFalse,
        index_type MinDimension = 0>
    class conditional;
}

#endif
