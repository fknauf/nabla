#ifndef INCLUDED_NABLA2_EXPONENTIAL_HH
#define INCLUDED_NABLA2_EXPONENTIAL_HH

#include "fwd.hh"

#include "chain.hh"
#include "product.hh"
#include "sum.hh"
#include "util.hh"

#include <cmath>
#include <type_traits>

namespace nabla {
  namespace expr {
    template<typename Exponent>
    std::enable_if_t<traits::is_nabla_expression<Exponent>::value, chain<exponential, traits::plain_type<Exponent> > >
    pow(constant base, Exponent &&exponent) {
      return { exponential(base), std::forward<Exponent>(exponent) };
    }

    class exponential : public nabla_base<exponential> {
    public:
      using nabla_base<exponential>::diff;
      using nabla_base<exponential>::operator();
      static int constexpr dimension = 1;
      
      exponential(constant base)
	: base_    (base),
	  log_base_(std::log(base.value()))
      { }

      template<int N>
      double operator()(vector<N> const &vars) const {
	static_assert(N >= dimension, "input value vector too short");
	return std::pow(base_(vars), vars(0));
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
	return log_base_ * (*this);
      }

      constant base_;
      constant log_base_;
    };
  }
}

#endif
