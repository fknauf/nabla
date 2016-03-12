#ifndef INCLUDED_NABLA2_CONSTANT_HH
#define INCLUDED_NABLA2_CONSTANT_HH

#include "nabla_base.hh"
#include "vector.hh"

namespace nabla {
  namespace expr {
    template<int N> class variable;
    
    class constant : public nabla_base<constant> {
    public:
      using nabla_base<constant>::diff;
      static int constexpr dimension = 0;

      constexpr constant(double value) noexcept
	: value_(value) { }

      template<int N>
      constant diff(variable<N> const & = {}) const noexcept {
	return constant(0.0);
      }

      template<int N>
      double operator()(vector<N> const &) const {
	return value_;
      }		    
      
    private:
      double value_;
    };
  }
}

#endif
