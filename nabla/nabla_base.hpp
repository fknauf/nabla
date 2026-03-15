#ifndef INCLUDED_NABLA2_NABLA_BASE_HH
#define INCLUDED_NABLA2_NABLA_BASE_HH

#include "fwd.hpp"
#include "nabla_tag.hpp"
#include "vector.hpp"

namespace nabla::expr {
    template <typename Derived>
    class nabla_base:
        public nabla_tag
    {
    public:
        template <index_type N, index_type... O>
        [[nodiscard]]
        auto diff(variable<N> const &head, variable<O> const &...tail) const {
            return self().diff(head).diff(tail...);
        }

        template <typename... Values>
        [[nodiscard]]
        auto operator()(Values &&...values) const -> double
            requires(traits::all(
                traits::is_nabla_value_type<traits::plain_type<Values>>...
            ))
        {
            return self()(make_vector(std::forward<Values>(values)...));
        }

    private:
        [[nodiscard]]
        auto self() const noexcept -> Derived const & {
            return static_cast<Derived const &>(*this);
        }
    };
}

#endif
