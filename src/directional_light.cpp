//
// Created by jonas on 21.03.18.
//

#include "yae/directional_light.hpp"

namespace yae
{

    directional_light::directional_light(const math::vec<3>& direction, const math::vec<3>& ambient,
                                         const math::vec<3>& diffuse, const math::vec<3>& specular)
            : m_direction(direction), m_ambient(ambient), m_diffuse(diffuse), m_specular(specular) {}

    const math::vec<3>& directional_light::get_direction() const
    {
        return m_direction;
    }

    const math::vec<3>& directional_light::get_ambient() const
    {
        return m_ambient;
    }

    const math::vec<3>& directional_light::get_diffuse() const
    {
        return m_diffuse;
    }

    const math::vec<3>& directional_light::get_specular() const
    {
        return m_specular;
    }
}
