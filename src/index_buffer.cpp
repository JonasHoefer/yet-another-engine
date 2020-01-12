//
// Created by jonas on 21.12.2017.
//

#include <yae/gl/index_buffer.hpp>

#include "yae/gl/index_buffer.hpp"

namespace yae
{
    namespace gl
    {
        template<typename T>
        index_buffer<T>::index_buffer(const T* data, GLuint count)
                : m_count(count)
        {
            glGenBuffers(1, &h_ibo);
            bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), data, GL_STATIC_DRAW);
        }

        template<typename T>
        index_buffer<T>::index_buffer()
        {
            glGenBuffers(1, &h_ibo);
            bind();
        }

        template<typename T>
        index_buffer<T>::index_buffer(index_buffer<T>&& other) noexcept
                : h_ibo(other.h_ibo), m_count(other.m_count)
        {
            other.h_ibo = 0;
        }

        template<typename T>
        index_buffer<T>& index_buffer<T>::operator=(index_buffer<T>&& other) noexcept
        {
            if (this != &other)
            {
                release();
                h_ibo = other.h_ibo;
                other.h_ibo = 0;

            }
            return *this;
        }

        template<typename T>
        index_buffer<T>::~index_buffer()
        {
            release();
        }

        template<typename T>
        void index_buffer<T>::bind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, h_ibo);
        }

        template<typename T>
        void index_buffer<T>::unbind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        template<typename T>
        GLuint index_buffer<T>::get_count() const
        {
            return m_count;
        }

        template<typename T>
        void index_buffer<T>::draw()
        {
            draw(m_count);
        }

        template<typename T>
        void index_buffer<T>::draw(GLuint count)
        {
            glDrawElements(GL_TRIANGLES, count, get_gl_type<T>(), nullptr);
        }

        template<typename T>
        void index_buffer<T>::set_data(const T* data, GLuint count)
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), data, GL_STATIC_DRAW);
        }

        template<typename T>
        void index_buffer<T>::release()
        {
            if (h_ibo)
            {
                glDeleteBuffers(1, &h_ibo);
            }
        }
    }
}

template
class yae::gl::index_buffer<GLuint>;

template
class yae::gl::index_buffer<GLushort>;

template
class yae::gl::index_buffer<GLubyte>;
