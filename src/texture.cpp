//
// Created by jonas on 28.02.2018.
//

#include "yae/gl/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

namespace yae
{
    namespace gl
    {
        texture::texture(const std::string& file)
                : m_width(0), m_height(0), m_bits_per_pixel(0), m_buffer(nullptr)
        {
            glGenTextures(1, &h_texture);
            glBindTexture(GL_TEXTURE_2D, h_texture);

            stbi_set_flip_vertically_on_load(1);
            m_buffer = stbi_load(file.c_str(), &m_width, &m_height, &m_bits_per_pixel, 4);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer);
            unbind();

            if (m_buffer)
            {
                stbi_image_free(m_buffer);
            }
        }

        texture::~texture()
        {
            glDeleteTextures(1, &h_texture);
        }

        void texture::bind(unsigned int slot) const
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, h_texture);
        }

        void texture::unbind() const
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}
