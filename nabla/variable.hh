#ifndef INCLUDED_NABLA2_VARIABLE_HH
#define INCLUDED_NABLA2_VARIABLE_HH

#include "constant.hh"
#include "nabla_base.hh"

namespace nabla::expr {
    template <index_type N>
    class variable:
        public nabla_base<variable<N>>
    {
    public:
        static_assert(N >= 0, "Variables are numbered starting from 0");

        using nabla_base<variable>::diff;
        using nabla_base<variable>::operator();
        static index_type constexpr dimension = N + 1;

        template <index_type O>
        auto diff(variable<O> const & = {}) const noexcept -> constant {
            return constant(N == O ? 1 : 0);
        }

        template <index_type O>
        auto operator()(vector<O> const &vars) const -> double {
            static_assert(O >= dimension, "input value vector too short");
            return vars(N);
        }
    };
}

#endif
