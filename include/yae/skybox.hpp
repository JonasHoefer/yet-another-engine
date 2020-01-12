//
// Created by jonas on 24.08.18.
//

#ifndef YET_ANOTHER_ENGINE_SKYBOX_HPP
#define YET_ANOTHER_ENGINE_SKYBOX_HPP

#include "yae/math/matrix.hpp"
#include "gl/vertex_array.hpp"
#include "gl/cube_map.hpp"
#include "gl/shader_program.hpp"

namespace yae
{
    class skybox
    {
    public:
        explicit skybox(const std::array<std::string, 6>& textures);

        explicit skybox(const std::string& path, const std::string& type = "png");

    private:
        gl::vertex_array m_vao;
        gl::buffer<math::vec<3, GLfloat>> m_vbo;
        gl::shader_program m_shader;
        gl::cube_map m_cube_map;

    public:
        void render(math::mat<4> view, math::mat<4> projection);


    private:
        static std::array<math::vec<3, GLfloat>, 36> vertices;
    };
}

#endif //YET_ANOTHER_ENGINE_SKYBOX_HPP
