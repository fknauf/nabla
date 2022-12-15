#ifndef INCLUDED_NABLA2_SUM_HH
#define INCLUDED_NABLA2_SUM_HH

#include "fwd.hh"
#include "nabla_base.hh"
#include "negation.hh"
#include "vector.hh"

#include <algorithm>

namespace nabla {
  namespace expr {
    inline constant operator+(constant const &lhs, constant const &rhs) { return lhs.value() + rhs.value(); }
    inline constant operator-(constant const &lhs, constant const &rhs) { return lhs.value() - rhs.value(); }

    template<typename LHS, typename RHS>
    sum<traits::nabla_equivalent<LHS>,
        traits::nabla_equivalent<RHS>>
    operator+(LHS &&lhs, RHS &&rhs)
      requires traits::is_regular_nabla_tuple<LHS, RHS>
    {
      return { std::forward<LHS>(lhs), std::forward<RHS>(rhs) };
    }

    template<typename LHS, typename RHS>
    sum<traits::nabla_equivalent<LHS>,
        traits::negated_nabla_equivalent<RHS>>
    operator-(LHS &&lhs, RHS &&rhs)
      requires traits::is_regular_nabla_tuple<LHS, RHS>
    {
      return std::forward<LHS>(lhs) + -std::forward<RHS>(rhs);
    }

    template<typename LHS, typename RHS> class sum : public nabla_base<sum<LHS, RHS>> {
    public:
      using nabla_base<sum>::diff;
      using nabla_base<sum>::operator();
      static int constexpr dimension = std::max(LHS::dimension, RHS::dimension);

      template<typename L, typename R>
      sum(L &&lhs, R &&rhs)
        : lhs_(std::forward<L>(lhs)),
          rhs_(std::forward<R>(rhs))
      { }

      template<int N> auto diff(variable<N> const &v = {}) const {
        return lhs_.diff(v) + rhs_.diff(v);
      }

      template<int N> double operator()(vector<N> const &vars) const {
        static_assert(N >= dimension, "input value vector too short");
        return lhs_(vars) + rhs_(vars);
      }

    private:
      LHS lhs_;
      RHS rhs_;
    };
  }
}

#endif
