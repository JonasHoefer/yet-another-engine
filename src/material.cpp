//
// Created by jonas on 18.03.18.
//

#include <yae/material.hpp>

namespace yae
{
    material::material(unsigned int diffuse, unsigned int specular, unsigned int emission, float shininess)
            : m_diffuse(diffuse), m_specular(specular), m_emission(emission), m_shininess(shininess) {}

    unsigned int material::get_diffuse() const
    {
        return m_diffuse;
    }

    unsigned int material::get_specular() const
    {
        return m_specular;
    }

    float material::get_shininess() const
    {
        return m_shininess;
    }

    unsigned int material::get_emission() const
    {
        return m_emission;
    }
}
