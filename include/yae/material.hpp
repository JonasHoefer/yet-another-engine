//
// Created by jonas on 18.03.18.
//

#ifndef YET_ANOTHER_ENGINE_MATERIAL_HPP
#define YET_ANOTHER_ENGINE_MATERIAL_HPP

namespace yae
{
    /**
     * plain old data for materials
     */
    class material
    {
    public:
        /**
         * @brief stores the given data
         *
         * @param diffuse - diffuse map
         * @param specular - specular map
         * @param emission - emission map
         * @param shininess - property of the material
         */
        material(unsigned int diffuse, unsigned int specular, unsigned int emission, float shininess);

    private:
        unsigned int m_diffuse;
        unsigned int m_specular;
        unsigned int m_emission;
        float m_shininess;

    public:
        unsigned int get_diffuse() const;

        unsigned int get_specular() const;

        unsigned int get_emission() const;

        float get_shininess() const;
    };
}

#endif //YET_ANOTHER_ENGINE_MATERIAL_HPP
