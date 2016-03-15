#ifndef INCLUDED_NABLA2_POLYNOMIAL_HH
#define INCLUDED_NABLA2_POLYNOMIAL_HH

#include "fwd.hh"

#include "conditional.hh"
#include "product.hh"
#include <cmath>

namespace nabla {
  namespace expr {
    template<typename Base>
    std::enable_if_t<traits::is_nabla_expression<Base>::value, polynomial<traits::plain_type<Base> > >
    pow(Base &&base, double exponent) {
      return { std::forward<Base>(base), exponent };
    }

    template<typename Base>
    class polynomial : public nabla_base<polynomial<Base> > {
    public:
      using nabla_base<polynomial>::diff;
      static int constexpr dimension = Base::dimension;

      template<typename B>
      polynomial(B &&base, constant exponent)
	: base_(std::forward<B>(base)),
	  exponent_(exponent)
      { }

      template<int N>
      auto operator()(vector<N> const &vars) const {
	return std::pow(base_(vars), exponent_(vars));
      }

      template<int N>
      auto diff(variable<N> const &var = {}) const {
	return impl::make_conditional([=](auto &&) { return exponent_.value() != 0.0; },
				      exponent_ * base_.diff(var) * pow(base_, exponent_.value() - 1.0),
				      0);
      }

    private:
      Base     base_;
      constant exponent_;
    };
  }
}

#endif
