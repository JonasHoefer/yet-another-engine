//
// Created by jonas on 17.12.2017.
//

#ifndef YAE_VERTEX_ARRAY_HPP
#define YAE_VERTEX_ARRAY_HPP

#include "buffer.hpp"
#include "type_utils.h"

namespace yae
{
    namespace gl
    {
        /**
         * @brief a wrapper class for gl vertex array
         */
        class vertex_array
        {
        public:
            /**
             * @brief creates a new vertex array
             */
            explicit vertex_array();

            /**
             * deletes the vertex array
             */
            virtual ~vertex_array();

        private:
            /**
             * handle
             */
            GLuint h_vao;

        public:
            template<GLuint index, typename ComponentType, typename T, typename U>
            void push_layout(U T::* a, const buffer<T>& buffer, const GLboolean normalized = GL_FALSE) const
            {
                const auto offset = reinterpret_cast<std::ptrdiff_t>(&(reinterpret_cast<T const volatile*>(NULL)->*a));

                bind();
                buffer.bind();
                glEnableVertexAttribArray(index);
                glVertexAttribPointer(index, sizeof(U) / sizeof(ComponentType), get_gl_type<ComponentType>(),
                                      normalized, sizeof(T), reinterpret_cast<GLvoid*>(offset));
            }

            /**
             * @brief binds this vertex array
             *
             * Only one vertex array can be bound at one time. As a result the previous vertex array will be unbound.
             */
            void bind() const;

            /**
             * @brief unbinds the current vertex array
             */
            void unbind() const;
        };
    }
}

#endif //YAE_VERTEX_ARRAY_HPP
