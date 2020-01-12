//
// Created by jonas on 21.12.2017.
//

#ifndef YAE_INDEX_BUFFER_HPP
#define YAE_INDEX_BUFFER_HPP

#include "type_utils.h"

namespace yae
{
    namespace gl
    {
        /**
         * @brief a buffer storing indices
         *
         * @tparam T the type which is used to store the indices. Possible are GLubyte, GLushort and GLuint
         */
        template<typename T>
        class index_buffer
        {
        public:
            /**
             * @brief constructs a new buffer from an array containing indices
             *
             * @param count number of indices
             * @param data pointer to the first element in the array
             */
            index_buffer(const T* data, GLuint count);

            /**
             * @brief constructs a new index buffer containing no data
             */
            index_buffer();

            /**
             * can't be copied only referenced and moved
             */
            index_buffer(const index_buffer<T>&) = delete;

            /**
             * can't be copied only referenced and moved
             */
            index_buffer<T>& operator=(const index_buffer<T>&) = delete;

            /**
             * moves the responsibility of managing the underlying ELEMENT_ARRAY_BUFFER from the given instance to this one
             *
             * @param other another index buffer instance which will be moved
             */
            index_buffer(index_buffer<T>&& other) noexcept;

            /**
             * moves the responsibility of managing the underlying ELEMENT_ARRAY_BUFFER from the given instance to this one
             *
             * @param other another index buffer instance which will be moved
             */
            index_buffer<T>& operator=(index_buffer<T>&& other) noexcept;

            /**
             * deletes the index buffer
             */
            ~index_buffer();

        private:
            /**
             * OpenGL handle for this index buffer
             */
            GLuint h_ibo = 0;

            /**
             * number of indices
             */
            GLuint m_count = 0;

        public:
            /**
             * @brief this index buffer will be used for future operations
             *
             * the currently bound index buffer will be unbound
             */
            void bind() const;

            /**
             * @brief unbinds the current index buffer
             */
            void unbind() const;

            /**
             * @return the amount of indices stored in this buffer
             */
            GLuint get_count() const;

            /**
             * @brief draws vertices from a currently bound buffer using the indices stored in this buffer
             *
             * @see yae::gl::buffer
             *
             * If another index buffer it's bound it's data will be used BUT this buffers count and data type.
             * This buffer isn't rebound each draw call for performance reasons.
             */
            void draw();

            /**
             * @brief draws vertices from a currently bound buffer using the indices stored in this buffer
             *
             * @param count the amount of indices which will be drawn
             *
             * @see yae::gl::buffer
             *
             * If another index buffer it's bound it's data will be used BUT this buffers count and data type.
             * This buffer isn't rebound each draw call for performance reasons.
             */
            void draw(GLuint count);

            /**
             * @brief allows to change the data stored in the buffer
             *
             * This buffer has to be bound in order for this function to effect this buffer.
             */
            void set_data(const T* data, GLuint count);

        private:
            /**
             * if this instance manages a buffer, the buffer will be freed
             */
            void release();
        };
    }
}

#endif //YAE_INDEX_BUFFER_HPP
