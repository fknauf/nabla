#ifndef INCLUDED_NABLA2_HYPOT_HH
#define INCLUDED_NABLA2_HYPOT_HH

#include "chain.hh"
#include "fwd.hh"
#include "nabla_base.hh"
#include "unary_functions.hh"

#include <cmath>
#include <numeric>

namespace nabla::expr {
    template <typename... Inners>
    auto hypot(Inners &&...inners)
        requires traits::is_nabla_tuple<Inners...>
    {
        return sqrt((... + (std::forward<Inners>(inners) * std::forward<Inners>(inners))));
    }
}

#endif
