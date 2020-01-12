//
// Created by jonas on 01.04.18.
//

#include "yae/gl/cube_map.hpp"
#include <iostream>
#include <yae/gl/cube_map.hpp>


namespace yae
{
    namespace gl
    {
        cube_map::cube_map(const std::array<std::string, 6>& images)
        {
            glGenTextures(1, &h_cube_map);
            bind();

            int width, height, nrChannels;
            unsigned char* data;
            for (GLuint i = 0; i < images.size(); i++)
            {
                data = stbi_load(images[i].c_str(), &width, &height, &nrChannels, 0);
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        }

        cube_map::cube_map(cube_map&& other) noexcept
                : h_cube_map(other.h_cube_map)
        {
            other.h_cube_map = 0;
        }

        cube_map& cube_map::operator=(cube_map&& other) noexcept
        {
            if (this != &other)
            {
                release();
                h_cube_map = other.h_cube_map;
                other.h_cube_map = 0;
            }

            return *this;
        }

        cube_map::~cube_map()
        {
            release();
        }

        void cube_map::bind() const
        {
            glBindTexture(GL_TEXTURE_CUBE_MAP, h_cube_map);
        }

        void cube_map::unbind() const
        {
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        }

        void cube_map::release()
        {
            if (h_cube_map)
            {
                glDeleteTextures(1, &h_cube_map);
            }
        }
    }
}
