#ifndef INCLUDED_NABLA2_FWD_HH
#define INCLUDED_NABLA2_FWD_HH

namespace nabla {
  namespace expr {
    class tag;
    class constant;
    template<int> class variable;
    template<typename Expr> class negation;
    template<typename LHS, typename RHS> class sum;
    template<typename LHS, typename RHS> class product;
    template<typename LHS, typename RHS> class division;

    class polynomial;
    class exponential;
    class logarithm;
    template<typename Base, typename Exponent> class power;
    
    template<typename Outer, typename... Inner> class chain;
    template<typename Condition, typename ExprTrue, typename ExprFalse> class conditional;
  }
}

#endif
