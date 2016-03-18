#ifndef INCLUDED_NABLA2_NEGATION_HH
#define INCLUDED_NABLA2_NEGATION_HH

#include "fwd.hh"
#include "nabla_base.hh"
#include "variable.hh"
#include "vector.hh"

namespace nabla {
  namespace expr {
    template<typename Expr>
    std::enable_if_t<traits::is_nabla_expression<Expr>::value, negation<traits::plain_type<Expr> > >
    operator-(Expr &&expr) {
      return { std::forward<Expr>(expr) };
    }
    
    template<typename Expr>
    class negation : public nabla_base<negation<Expr>> {
    public:
      using nabla_base<negation>::diff;
      using nabla_base<negation>::operator();
      static int constexpr dimension = Expr::dimension;

      template<typename E>
      negation(E &&expr) : expr_(std::forward<E>(expr)) { }

      template<int N>
      auto diff(variable<N> const &v = {}) const {
	return -expr_.diff(v);
      }

      template<int N>
      auto operator()(vector<N> const &vars) const {
	return -expr_(vars);
      }
      
    private:
      Expr expr_;
    };
  }
}

#endif
