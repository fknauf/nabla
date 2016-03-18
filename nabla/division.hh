#ifndef INCLUDED_NABLA2_DIVISION_HH
#define INCLUDED_NABLA2_DIVISION_HH

#include "fwd.hh"
#include "nabla_base.hh"
#include "product.hh"
#include "sum.hh"
#include "variable.hh"
#include "vector.hh"

#include <algorithm>

namespace nabla {
  namespace expr {
    template<typename LHS, typename RHS>
    std::enable_if_t<traits::is_nabla_pair<LHS, RHS>::value, division<traits::nabla_equivalent<LHS>,
								      traits::nabla_equivalent<RHS>>>
    operator/(LHS &&lhs, RHS &&rhs) {
      return { std::forward<LHS>(lhs), std::forward<RHS>(rhs) };
    }

    template<typename LHS, typename RHS> class division : public nabla_base<division<LHS, RHS>> {
    public:
      using nabla_base<division>::diff;
      using nabla_base<division>::operator();
      static int constexpr dimension = std::max(LHS::dimension, RHS::dimension);

      template<typename L, typename R>
      division(L &&lhs, R &&rhs)
	: lhs_(std::forward<L>(lhs)),
	  rhs_(std::forward<R>(rhs))
      { }

      template<int N> auto diff(variable<N> const &v = {}) const {
	return (lhs_.diff(v) * rhs_ - lhs_ * rhs_.diff(v)) / (rhs_ * rhs_);
      }

      template<int N> auto operator()(vector<N> const &vars) const {
	static_assert(N >= dimension, "input value vector too short");
	return lhs_(vars) / rhs_(vars);
      }
      
    private:
      LHS lhs_;
      RHS rhs_;
    };    
  }
}

#endif
