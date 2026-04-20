#ifndef INCLUDED_NABLA2_HYPOT_HH
#define INCLUDED_NABLA2_HYPOT_HH

#include "chain.hpp"
#include "fwd.hpp"
#include "nabla_base.hpp"
#include "unary_functions.hpp"

#include <cmath>
#include <numeric>

namespace nabla::expr {
    template <typename... Inners>
    [[nodiscard]] auto hypot(Inners &&...inners)
        requires traits::is_nabla_tuple<Inners...>
    {
        return sqrt((... + (inners * inners)));
    }
}

#endif
