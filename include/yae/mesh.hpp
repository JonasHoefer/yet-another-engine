//
// Created by jonas on 20.03.18.
//

#ifndef YET_ANOTHER_ENGINE_MESH_HPP
#define YET_ANOTHER_ENGINE_MESH_HPP

#include <vector>
#include <iostream>


#include <tiny_obj_loader.h>

#include "vertex.hpp"


namespace yae {
    /**
     * @brief a mesh containing vertices and incidces
     */
    class mesh {
    public:
        /**
         * @brief constructs a new mesh from an obj file
         *
         * @param path to an obj file
         */
        explicit mesh(const std::string& path);

    private:
        /**
         * vertex points
         */
        std::vector<vertex> m_vertices;

        /**
         * indices for index based rendering
         */
        std::vector<unsigned int> m_indices;

    public:
        /**
         * @brief getter for a vector containing all vertex points
         *
         * @return all vertex points
         */
        const std::vector<vertex> get_vertices() const;

        /**
         * @brief getter for a vector containing indices corresponding to the vertex points
         *
         * @return indices for vertex points
         */
        const std::vector<unsigned int>& get_indices() const;
    };
}

#endif //YET_ANOTHER_ENGINE_MESH_HPP
