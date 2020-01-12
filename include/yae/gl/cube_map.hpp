//
// Created by jonas on 01.04.18.
//

#ifndef YET_ANOTHER_ENGINE_CUBE_MAP_HPP
#define YET_ANOTHER_ENGINE_CUBE_MAP_HPP

#include <array>
#include <vector>

#define GLEW_STATIC

#include <GL/glew.h>

#include <stb_image.h>

namespace yae
{
    namespace gl
    {
        class cube_map
        {
        public:
            explicit cube_map(const std::array<std::string, 6>& images);

            cube_map(const cube_map&) = delete;

            cube_map& operator=(const cube_map&) = delete;

            cube_map(cube_map&& other) noexcept;

            cube_map& operator=(cube_map&& other) noexcept;

            virtual ~cube_map();

        private:
            GLuint h_cube_map;

        public:
            void bind() const;

            void unbind() const;

        private:
            void release();
        };
    }
}

#endif //YET_ANOTHER_ENGINE_CUBE_MAP_HPP
