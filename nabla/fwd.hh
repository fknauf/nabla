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
  }
}

#endif
