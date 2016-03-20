#ifndef INCLUDED_NABLA2_CONSTANT_HH
#define INCLUDED_NABLA2_CONSTANT_HH

#include "fwd.hh"
#include "nabla_base.hh"
#include "vector.hh"

#include <cmath>

namespace nabla {
  namespace expr {
    class constant : public nabla_base<constant> {
    public:
      using nabla_base<constant>::diff;
      using nabla_base<constant>::operator();
      static int constexpr dimension = 0;

      constexpr constant(double value) noexcept
	: value_(value) { }

      template<int N>
      constant diff(variable<N> const & = {}) const noexcept {
	static_assert(N >= dimension, "input value vector is shorter than zero elements? O.o");
	return 0;
      }

      template<int N>
      double operator()(vector<N> const &) const {
	return value_;
      }		    

      // Benutzt in polynomial
      double value() const noexcept { return value_; }

    private:
      double value_;
    };

    namespace impl {
      inline double constant_value(constant const &c) { return c.value(); }

      template<typename T, typename = std::enable_if_t<traits::is_nabla_value_type<T>::value> >
      double constant_value(T &&c) {
	return c;
      }
    }

    // Arguably this does not belong here, but this is included in all of
    // polynomial.hh, exponential.hh and power.hh.
    template<typename Base,
	     typename Exponent,
	     typename = std::enable_if_t<traits::constant_folding_possible<Base, Exponent>::value> >
    inline constant pow(Base &&base, Exponent &&exponent) {
      return std::pow(impl::constant_value(std::forward<Base>    (base    )),
		      impl::constant_value(std::forward<Exponent>(exponent)));
    }
  }
}

#endif
