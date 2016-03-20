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

    inline constant operator+(constant const &lhs, constant const &rhs) { return lhs.value() + rhs.value(); }
    inline constant operator-(constant const &lhs, constant const &rhs) { return lhs.value() - rhs.value(); }
    inline constant operator*(constant const &lhs, constant const &rhs) { return lhs.value() * rhs.value(); }
    inline constant operator/(constant const &lhs, constant const &rhs) { return lhs.value() / rhs.value(); }

    inline constant operator-(constant const &x) { return -x.value(); }

    inline constant pow(constant const &base, constant &exponent) { return std::pow(base.value(), exponent.value()); }
    inline constant log(constant const &x) { return std::log(x.value()); }
  }
}

#endif
