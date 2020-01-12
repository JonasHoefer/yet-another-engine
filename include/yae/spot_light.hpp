//
// Created by jonas on 25.03.18.
//

#ifndef YET_ANOTHER_ENGINE_SPOT_LIGHT_HPP
#define YET_ANOTHER_ENGINE_SPOT_LIGHT_HPP

#include "yae/math/matrix.hpp"

namespace yae
{
    /**
     * a light with a direction and an angle defining which areas are lit
     */
    class spot_light
    {
    public:
        spot_light(const math::vec<3>& position, const math::vec<3>& direction, float cutoff_angle, float m_outer_cutoff_angle, const math::vec<3>& ambient, const math::vec<3>& diffuse, const math::vec<3>& specular);

    private:
        math::vec<3> m_position;
        math::vec<3> m_direction;
        float m_cutoff_angle;
        float m_outer_cutoff_angle;

        math::vec<3> m_ambient;
        math::vec<3> m_diffuse;
        math::vec<3> m_specular;

    public:
        const math::vec<3>& get_position() const;

        const math::vec<3>& get_direction() const;

        float get_cutoff_angle() const;

        float get_outer_cutoff_angle() const;

        const math::vec<3>& get_ambient() const;

        const math::vec<3>& get_diffuse() const;

        const math::vec<3>& get_specular() const;
    };
}

#endif //YET_ANOTHER_ENGINE_SPOT_LIGHT_HPP
