//
// Created by jonas on 21.03.18.
//

#include "yae/point_light.hpp"

namespace yae
{
    point_light::point_light(const math::vec<3>& position,
                             const math::vec<3>& ambient, const math::vec<3>& diffuse, const math::vec<3>& specular,
                             float constant, float linear, float quadratic)
            : m_position(position),
              m_ambient(ambient), m_diffuse(diffuse), m_specular(specular),
              m_constant(constant), m_linear(linear), m_quadratic(quadratic) {}

    const math::vec<3>& point_light::get_position() const
    {
        return m_position;
    }

    const math::vec<3>& point_light::get_ambient() const
    {
        return m_ambient;
    }

    const math::vec<3>& point_light::get_diffuse() const
    {
        return m_diffuse;
    }

    const math::vec<3>& point_light::get_specular() const
    {
        return m_specular;
    }

    float point_light::get_constant() const
    {
        return m_constant;
    }

    float point_light::get_linear() const
    {
        return m_linear;
    }

    float point_light::get_quadratic() const
    {
        return m_quadratic;
    }
}
