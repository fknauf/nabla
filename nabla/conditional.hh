#ifndef INCLUDED_NABLA2_CONDITIONAL_HH
#define INCLUDED_NABLA2_CONDITIONAL_HH

#include "fwd.hh"

#include "nabla_base.hh"
#include "util.hh"
#include "variable.hh"
#include "vector.hh"

#include <algorithm>

namespace nabla {
  namespace expr {
    namespace impl {
      template<typename Condition, typename ExprTrue, typename ExprFalse>
      conditional<traits::plain_type<Condition>, traits::nabla_equivalent<ExprTrue>, traits::nabla_equivalent<ExprFalse> >
      make_conditional(Condition &&condition, ExprTrue &&expr_true, ExprFalse &&expr_false) {
	return { condition, expr_true, expr_false };
      }

      template<int MinDimension, typename Condition, typename ExprTrue, typename ExprFalse>
      conditional<traits::plain_type<Condition>, traits::nabla_equivalent<ExprTrue>, traits::nabla_equivalent<ExprFalse>, MinDimension >
      make_conditional_with_min_dimension(Condition &&condition, ExprTrue &&expr_true, ExprFalse &&expr_false) {
	return { condition, expr_true, expr_false };
      }
    }
    
    template<typename Condition,
	     typename ExprTrue,
	     typename ExprFalse,
	     int      MinDimension>
    class conditional : public nabla_base<conditional<Condition, ExprTrue, ExprFalse, MinDimension> > {
    public:
      using nabla_base<conditional>::diff;
      static int constexpr dimension = std::max(MinDimension, std::max(ExprTrue::dimension, ExprFalse::dimension));

      template<typename C, typename T, typename F>
      conditional(C &&condition, T &&expr_true, F &&expr_false)
	: condition_ (std::forward<C>(condition )),
	  expr_true_ (std::forward<T>(expr_true )),
	  expr_false_(std::forward<F>(expr_false))
      { }

      template<int N>
      auto operator()(vector<N> const &vars) const {
	return condition_(vars) ? expr_true_(vars) : expr_false_(vars);
      }

      template<int N>
      auto diff(variable<N> const &var = {}) const {
	return diff_dispatch(var, impl::bool_constant<(N < dimension) && (!std::is_same<constant, ExprTrue >::value ||
									  !std::is_same<constant, ExprFalse>::value)>());
      }
      
    private:
      template<int N>
      auto diff_dispatch(variable<N> const &var, std::true_type) const {
	return impl::make_conditional(condition_, expr_true_.diff(var), expr_false_.diff(var));
      }

      template<int N>
      constant diff_dispatch(variable<N> const &, std::false_type) const {
	return 0;
      }
      
      Condition condition_;
      ExprTrue  expr_true_;
      ExprFalse expr_false_;
    };
  }
}

#endif
