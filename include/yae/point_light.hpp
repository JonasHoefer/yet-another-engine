//
// Created by jonas on 21.03.18.
//

#ifndef YET_ANOTHER_ENGINE_POINT_LIGHT_HPP
#define YET_ANOTHER_ENGINE_POINT_LIGHT_HPP

#include "yae/math/matrix.hpp"

namespace yae {

    /**
     * @brief a light with a point of origin and a reduction of intensity.
     */
    class point_light {
    public:
        point_light(const math::vec<3>& position, const math::vec<3>& ambient, const math::vec<3>& diffuse, const math::vec<3>& specular, float constant, float linear, float quadratic);

    private:
        math::vec<3> m_position;

        math::vec<3> m_ambient;
        math::vec<3> m_diffuse;
        math::vec<3> m_specular;

        /**
         * constants for intensity drop of:
         *                       1.0
         * F_att(d) = --------------------------
         *             K_c + K_l * d + K_q * d²
         */
        float m_constant;
        float m_linear;
        float m_quadratic;


    public:
        const math::vec<3>& get_position() const;

        const math::vec<3>& get_ambient() const;

        const math::vec<3>& get_diffuse() const;

        const math::vec<3>& get_specular() const;

        float get_constant() const;

        float get_linear() const;

        float get_quadratic() const;
    };
}

#endif //YET_ANOTHER_ENGINE_POINT_LIGHT_HPP
