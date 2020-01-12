//
// Created by jonas on 16.02.2018.
//

#ifndef YET_ANOTHER_ENGINE_BUFFER_HPP
#define YET_ANOTHER_ENGINE_BUFFER_HPP

#include <iostream>

#define GLEW_STATIC

#include <GL/glew.h>

#include <array>

namespace yae
{
    namespace gl
    {
        /**
         * @brief an OpenGL array buffer holding data of type T
         *
         * @tparam T of data held by this data
         */
        template<typename T>
        class buffer
        {
        public:
            /**
             * @brief creates a new buffer holding no data
             */
            explicit buffer(unsigned int count)
                    : h_buffer(0)
            {
                glGenBuffers(1, &h_buffer);
                bind();
                glBufferData(GL_ARRAY_BUFFER, count * sizeof(T), nullptr, GL_DYNAMIC_DRAW);
            }

            /**
             * @brief creates a new buffer holding the data from the given array
             *
             * @param data pointer to an array
             * @param count of element after the first one, which should be stored in the buffer
             */
            explicit buffer(const T* data, unsigned long count)
                    : h_buffer(0)
            {
                glGenBuffers(1, &h_buffer);
                bind();
                glBufferData(GL_ARRAY_BUFFER, count * sizeof(T), data, GL_STATIC_DRAW);
            }

            buffer(const buffer<T>&) = delete;

            buffer& operator=(const buffer<T>&) = delete;

            buffer(buffer&& other) noexcept
                    : h_buffer(other.h_buffer)
            {
                other.h_buffer = 0;
            }

            buffer& operator=(buffer&& other) noexcept
            {
                if (this != &other)
                {
                    release();
                    h_buffer = other.h_buffer;
                    other.h_buffer = 0;
                }

                return *this;
            }

            /**
             * @brief deletes the buffer
             */
            ~buffer()
            {
                release();
            }

        private:
            /**
             * OpenGL handle for this buffer
             */
            GLuint h_buffer;

        public:
            /**
             * @brief this buffer will be used for all future operations involving buffers
             *
             * the currently bound buffer object will be unbound
             */
            void bind() const
            {
                glBindBuffer(GL_ARRAY_BUFFER, h_buffer);
            }

            /**
             * @brief unbinds the current buffer
             */
            void unbind() const
            {
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

            /**
             * @brief maps the buffer
             *
             * @return a pointer to the start of the buffer allowing to write in it
             */
            [[nodiscard]] T* map()
            {
                bind();

                auto ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
                if (ptr == nullptr)
                {
                    std::cerr << "[ERROR|OpenGL] Could not map buffer!" << std::endl;
                }

                return static_cast<T*>(ptr);
            }

            /**
             *
             */
            void unmap()
            {
                glUnmapBuffer(GL_ARRAY_BUFFER);
            }

        private:
            void release()
            {
                if (h_buffer)
                {
                    glDeleteBuffers(1, &h_buffer);
                }
            }
        };
    }
}

#endif //YET_ANOTHER_ENGINE_BUFFER_HPP
