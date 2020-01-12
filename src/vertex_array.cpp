//
// Created by jonas on 17.12.2017.
//

#include "yae/gl/vertex_array.hpp"

namespace yae
{
    namespace gl
    {
        vertex_array::vertex_array()
        {
            glGenVertexArrays(1, &h_vao);
            bind();
        }

        vertex_array::~vertex_array()
        {
            glDeleteVertexArrays(1, &h_vao);
        }

        void vertex_array::bind() const
        {
            glBindVertexArray(h_vao);
        }

        void vertex_array::unbind() const
        {
            glBindVertexArray(0);
        }
    }
}
