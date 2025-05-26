#ifndef INCLUDED_NABLA2_VECTOR_HH
#define INCLUDED_NABLA2_VECTOR_HH

#include "nabla_base.hh"

namespace nabla {
    inline vector<0> make_vector() { return {}; }

    auto make_vector(traits::nabla_value auto &&...data) -> vector<sizeof...(data)> {
#ifdef NABLA_BACKEND_ARMADILLO
        return { static_cast<double>(data)... };
#else
        vector<sizeof...(data)> result;

        typename decltype(result)::Index i = 0;
        for(double d : { static_cast<double>(data)... }) {
            result(i++) = d;
        }

        return result;
#endif
    }
}

#endif
