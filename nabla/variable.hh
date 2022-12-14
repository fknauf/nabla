#ifndef INCLUDED_NABLA2_VARIABLE_HH
#define INCLUDED_NABLA2_VARIABLE_HH

#include "constant.hh"
#include "nabla_base.hh"

namespace nabla {
  namespace expr {
    template<int N>
    class variable : public nabla_base<variable<N>> {
    public:
      static_assert(N >= 0, "Variables are numbered starting from 0");
      
      using nabla_base<variable>::diff;
      using nabla_base<variable>::operator();
      static int constexpr dimension = N + 1;

      template<int O>
      constant diff(variable<O> const & = {}) const noexcept {
	return constant(N == O ? 1 : 0);
      }

      template<int O>
      double operator()(vector<O> const &vars) const {
	static_assert(O >= dimension, "input value vector too short");
	return vars(N);
      }
    };
  }
}

#endif

