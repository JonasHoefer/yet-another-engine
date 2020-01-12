//
// Created by jonas on 25.03.18.
//

#include "yae/spot_light.hpp"

namespace yae
{
    spot_light::spot_light(const math::vec<3>& position, const math::vec<3>& direction,
                           float cutoff_angle, float m_outer_cutoff_angle,
                           const math::vec<3>& ambient, const math::vec<3>& diffuse, const math::vec<3>& specular)
            : m_position(position), m_direction(direction),
              m_cutoff_angle(cutoff_angle), m_outer_cutoff_angle(m_outer_cutoff_angle),
              m_ambient(ambient), m_diffuse(diffuse), m_specular(specular) {}

    const math::vec<3>& spot_light::get_position() const
    {
        return m_position;
    }

    const math::vec<3>& spot_light::get_direction() const
    {
        return m_direction;
    }

    float spot_light::get_cutoff_angle() const
    {
        return m_cutoff_angle;
    }

    float spot_light::get_outer_cutoff_angle() const
    {
        return m_outer_cutoff_angle;
    }

    const math::vec<3>& spot_light::get_ambient() const
    {
        return m_ambient;
    }

    const math::vec<3>& spot_light::get_diffuse() const
    {
        return m_diffuse;
    }

    const math::vec<3>& spot_light::get_specular() const
    {
        return m_specular;
    }
}
