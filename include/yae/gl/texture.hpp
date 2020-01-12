//
// Created by jonas on 28.02.2018.
//

#ifndef YET_ANOTHER_ENGINE_TEXTURE_HPP
#define YET_ANOTHER_ENGINE_TEXTURE_HPP

#include <string>

#define GLEW_STATIC

#include <GL/glew.h>

#include <stb_image.h>

#include "yae/pil/file_utils.hpp"


namespace yae
{
    namespace gl
    {
        class texture
        {
        public:
            explicit texture(const std::string& file);

            ~texture();

        private:
            GLuint h_texture;

            int m_width;
            int m_height;
            int m_bits_per_pixel;
            pil::byte* m_buffer;

        public:
            void bind(unsigned int slot = 0) const;

            void unbind() const;
        };
    }
}

#endif //YET_ANOTHER_ENGINE_TEXTURE_HPP
