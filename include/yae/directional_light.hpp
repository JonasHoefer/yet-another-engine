//
// Created by jonas on 21.03.18.
//

#ifndef YET_ANOTHER_ENGINE_DIRECTIONAL_LIGHT_HPP
#define YET_ANOTHER_ENGINE_DIRECTIONAL_LIGHT_HPP

#include "yae/math/matrix.hpp"

namespace yae
{
    /**
     * @brief light source with parallel beams
     *
     * Far away light sources have nearly parallel rays. This class can be used to simulate this effect.
     */
    class directional_light
    {
    public:
        /**
         * @brief creates a new directional light source
         *
         * @param direction from the light source
         * @param ambient - property of the light
         * @param diffuse - property of the light
         * @param specular - property of the light
         */
        directional_light(const math::vec<3>& direction, const math::vec<3>& ambient, const math::vec<3>& diffuse, const math::vec<3>& specular);

    private:
        math::vec<3> m_direction;
        math::vec<3> m_ambient;
        math::vec<3> m_diffuse;
        math::vec<3> m_specular;

    public:
        const math::vec<3>& get_direction() const;

        const math::vec<3>& get_ambient() const;

        const math::vec<3>& get_diffuse() const;

        const math::vec<3>& get_specular() const;
    };
}

#endif //YET_ANOTHER_ENGINE_DIRECTIONAL_LIGHT_HPP
