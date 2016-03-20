#ifndef INCLUDED_NABLA2_POLYNOMIAL_HH
#define INCLUDED_NABLA2_POLYNOMIAL_HH

#include "fwd.hh"

#include "chain.hh"
#include "conditional.hh"
#include "product.hh"

#include <cmath>
#include <type_traits>

namespace nabla {
  namespace expr {
    template<typename Base>
    std::enable_if_t<traits::is_nabla_expression<Base>::value, chain<polynomial, traits::plain_type<Base> > >
    pow(Base &&base, constant exponent) {
      return { polynomial(exponent), std::forward<Base>(base) };
    }

    class polynomial : public nabla_base<polynomial> {
    public:
      using nabla_base<polynomial>::diff;
      using nabla_base<polynomial>::operator();
      static int constexpr dimension = 1;

      polynomial(constant exponent)
	: exponent_(exponent)
      { }

      template<int N>
      double operator()(vector<N> const &vars) const {
	static_assert(N >= dimension, "input value vector too short");
	return std::pow(vars(0), exponent_(vars));
      }

      template<int N>
      auto diff(variable<N> const & = {}) const {
	return diff_dispatch(impl::bool_constant<N == 0>());
      }

    private:
      constant diff_dispatch(std::false_type) const {
	return 0;
      }
      
      auto diff_dispatch(std::true_type) const {
	return impl::make_conditional([=](auto &&) { return exponent_.value() != 0.0; },
				      exponent_ * polynomial(exponent_.value() - 1.0),
				      0);
      }
      
      constant exponent_;
    };
  }
}

#endif
