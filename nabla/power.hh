#ifndef INCLUDED_NABLA2_POW_HH
#define INCLUDED_NABLA2_POW_HH

#include "fwd.hh"
#include "logarithm.hh"
#include "product.hh"
#include "sum.hh"

#include <cmath>

namespace nabla {
  namespace expr {
    template<typename Base, typename Exponent>
    power<traits::plain_type<Base>, traits::plain_type<Exponent>>
    pow(Base &&base, Exponent &&exponent)
      requires traits::is_pure_nabla_tuple<Base, Exponent> &&
      traits::constant_folding_impossible<Base, Exponent>
    {
      return { std::forward<Base>(base), std::forward<Exponent>(exponent) };
    }

    template<typename Base, typename Exponent>
    class power : public nabla_base<power<Base, Exponent> > {
    public:
      using nabla_base<power>::diff;
      using nabla_base<power>::operator();
      static int constexpr dimension = std::max(Base::dimension, Exponent::dimension);

      template<typename B, typename E>
      power(B &&base, E &&exponent)
        : base_    (std::forward<B>(base)),
          exponent_(std::forward<E>(exponent)) { }

      template<int N>
      double operator()(vector<N> const &vars) const {
        static_assert(N >= dimension, "input value vector too short");
        return std::pow(base_(vars), exponent_(vars));
      }

      template<int N>
      auto diff(variable<N> const &var = {}) const {
        return diff_dispatch(var, std::bool_constant<N < dimension>());
      }

    private:
      template<int N> auto diff_dispatch(variable<N> const &var, std::true_type) const {
        return (*this) * (log(base_) * exponent_.diff(var) + exponent_ * base_.diff(var) / base_);
      }

      template<int N> constant diff_dispatch(variable<N> const &, std::false_type) const {
        return 0;
      }

      Base     base_;
      Exponent exponent_;
    };
  }
}

#endif
