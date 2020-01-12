//
// Created by jonas on 24.08.18.
//

#include <yae/skybox.hpp>

#include "yae/skybox.hpp"

namespace yae
{
    skybox::skybox(const std::array<std::string, 6>& textures)
            : m_vbo(vertices.data(), vertices.size()), m_shader("shader/skybox.vert", "shader/skybox.frag"), m_cube_map(textures)
    {
        m_vao.bind();
        m_vbo.bind();
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    skybox::skybox(const std::string& path, const std::string& type) : skybox(std::array<std::string, 6>({path + "rt." + type, path + "lf." + type, path + "up." + type, path + "dn." + type, path + "bk." + type, path + "ft." + type})) {}

    void skybox::render(math::mat<4> view, math::mat<4> projection)
    {
        view[3][0] = 0.0f;
        view[3][1] = 0.0f;
        view[3][2] = 0.0f;
        view[3][3] = 1.0f;
        view[0][3] = 0.0f;
        view[1][3] = 0.0f;
        view[2][3] = 0.0f;  // remove translation => center cube => always around camera

        glDepthMask(GL_FALSE);
        m_shader.bind();
        m_shader.set_uniform_mat4("view", view);
        m_shader.set_uniform_mat4("projection", projection);
        m_vao.bind();
        m_cube_map.bind();
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glDepthMask(GL_TRUE);
    }

    std::array<math::vec<3, GLfloat>, 36> skybox::vertices = {
            math::vec<3, GLfloat>(-1.0f, 1.0f, -1.0f),
            math::vec<3, GLfloat>(-1.0f, -1.0f, -1.0f),
            math::vec<3, GLfloat>(1.0f, -1.0f, -1.0f),
            math::vec<3, GLfloat>(1.0f, -1.0f, -1.0f),
            math::vec<3, GLfloat>(1.0f, 1.0f, -1.0f),
            math::vec<3, GLfloat>(-1.0f, 1.0f, -1.0f),

            math::vec<3, GLfloat>(-1.0f, -1.0f, 1.0f),
            math::vec<3, GLfloat>(-1.0f, -1.0f, -1.0f),
            math::vec<3, GLfloat>(-1.0f, 1.0f, -1.0f),
            math::vec<3, GLfloat>(-1.0f, 1.0f, -1.0f),
            math::vec<3, GLfloat>(-1.0f, 1.0f, 1.0f),
            math::vec<3, GLfloat>(-1.0f, -1.0f, 1.0f),

            math::vec<3, GLfloat>(1.0f, -1.0f, -1.0f),
            math::vec<3, GLfloat>(1.0f, -1.0f, 1.0f),
            math::vec<3, GLfloat>(1.0f, 1.0f, 1.0f),
            math::vec<3, GLfloat>(1.0f, 1.0f, 1.0f),
            math::vec<3, GLfloat>(1.0f, 1.0f, -1.0f),
            math::vec<3, GLfloat>(1.0f, -1.0f, -1.0f),

            math::vec<3, GLfloat>(-1.0f, -1.0f, 1.0f),
            math::vec<3, GLfloat>(-1.0f, 1.0f, 1.0f),
            math::vec<3, GLfloat>(1.0f, 1.0f, 1.0f),
            math::vec<3, GLfloat>(1.0f, 1.0f, 1.0f),
            math::vec<3, GLfloat>(1.0f, -1.0f, 1.0f),
            math::vec<3, GLfloat>(-1.0f, -1.0f, 1.0f),

            math::vec<3, GLfloat>(-1.0f, 1.0f, -1.0f),
            math::vec<3, GLfloat>(1.0f, 1.0f, -1.0f),
            math::vec<3, GLfloat>(1.0f, 1.0f, 1.0f),
            math::vec<3, GLfloat>(1.0f, 1.0f, 1.0f),
            math::vec<3, GLfloat>(-1.0f, 1.0f, 1.0f),
            math::vec<3, GLfloat>(-1.0f, 1.0f, -1.0f),

            math::vec<3, GLfloat>(-1.0f, -1.0f, -1.0f),
            math::vec<3, GLfloat>(-1.0f, -1.0f, 1.0f),
            math::vec<3, GLfloat>(1.0f, -1.0f, -1.0f),
            math::vec<3, GLfloat>(1.0f, -1.0f, -1.0f),
            math::vec<3, GLfloat>(-1.0f, -1.0f, 1.0f),
            math::vec<3, GLfloat>(1.0f, -1.0f, 1.0f)
    };
}
