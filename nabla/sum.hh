#ifndef INCLUDED_NABLA2_SUM_HH
#define INCLUDED_NABLA2_SUM_HH

#include "fwd.hh"
#include "nabla_tag.hh"
#include "negation.hh"
#include "vector.hh"

#include <algorithm>

namespace nabla {
  namespace expr {
    template<typename LHS, typename RHS>
    std::enable_if_t<traits::is_nabla_pair<LHS, RHS>::value, sum<traits::nabla_equivalent<LHS>,
								 traits::nabla_equivalent<RHS>>>
    operator+(LHS &&lhs, RHS &&rhs) {
      return { std::forward<LHS>(lhs), std::forward<RHS>(rhs) };
    }
    
    template<typename LHS, typename RHS>
    std::enable_if_t<traits::is_nabla_pair<LHS, RHS>::value, sum<traits::nabla_equivalent<LHS>,
								 traits::negated_nabla_equivalent<RHS>>>
    operator-(LHS &&lhs, RHS &&rhs) {
      return std::forward<LHS>(lhs) + -std::forward<RHS>(rhs);
    }
    
    template<typename LHS, typename RHS> class sum : public nabla_tag {
    public:
      static int constexpr dimension = std::max(LHS::dimension, RHS::dimension);

      template<typename L, typename R>
      sum(L &&lhs, R &&rhs)
	: lhs_(std::forward<L>(lhs)),
	  rhs_(std::forward<R>(rhs))
      { }

      template<int N> auto diff(variable<N> const &v = {}) const {
	return lhs_.diff(v) + rhs_.diff(v);
      }

      template<int N> auto operator()(vector<N> const &vars) const {
	return lhs_(vars) + rhs_(vars);
      }
      
    private:
      LHS lhs_;
      RHS rhs_;
    };
  }
}

#endif
