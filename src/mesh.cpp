//
// Created by jonas on 20.03.18.
//

#include <yae/mesh.hpp>
#include <unordered_map>

#define TINYOBJLOADER_IMPLEMENTATION

#include <tiny_obj_loader.h>


namespace yae
{
    mesh::mesh(const std::string& path)
    {
        tinyobj::attrib_t vertex_attributes;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string error_string;

        if (!tinyobj::LoadObj(&vertex_attributes, &shapes, &materials, &error_string, path.c_str()))
        {
            std::cerr << "[TinyObjLoader|ERROR] Could not load file (" << path << "): " << error_string << std::endl;
        }

        std::unordered_map<vertex, unsigned int> vertices;

        for (tinyobj::shape_t shape : shapes)
        {
            for (tinyobj::index_t index : shape.mesh.indices)
            {
                math::vec<3> position(vertex_attributes.vertices[3 * index.vertex_index + 0],
                                      vertex_attributes.vertices[3 * index.vertex_index + 1],
                                      vertex_attributes.vertices[3 * index.vertex_index + 2]);

                math::vec<3> normal(vertex_attributes.normals[3 * index.normal_index + 0],
                                    vertex_attributes.normals[3 * index.normal_index + 1],
                                    vertex_attributes.normals[3 * index.normal_index + 2]);

                math::vec<2> tex_coord(vertex_attributes.texcoords[2 * index.texcoord_index + 0],
                                       vertex_attributes.texcoords[2 * index.texcoord_index + 1]);

                vertex vert(position, tex_coord, normal);
                if (vertices.count(vert) == 0)
                {
                    vertices[vert] = static_cast<unsigned int>(vertices.size());
                    m_vertices.push_back(vert);
                }

                m_indices.push_back(vertices[vert]);
            }
        }
    }

    const std::vector<vertex> mesh::get_vertices() const
    {
        return m_vertices;
    }

    const std::vector<unsigned int>& mesh::get_indices() const
    {
        return m_indices;
    }
}
