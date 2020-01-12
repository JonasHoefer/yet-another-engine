//
// Created by jonas on 15.03.18.
//

#include <yae/math/matrix.hpp>
#include <yae/math/transform.hpp>
#include <yae/math/quaternion.hpp>

#include <yae/gl/vertex_array.hpp>
#include <yae/gl/index_buffer.hpp>
#include <yae/gl/shader_program.hpp>
#include <yae/gl/texture.hpp>
#include <yae/gl/error_utils.hpp>

#include <yae/vertex.hpp>
#include <yae/window.hpp>
#include <yae/mesh.hpp>
#include <yae/skybox.hpp>

#include <algorithm>

#define PI 3.14159265f

using yae::math::operator ""_i;


using yae::math::vec;
using yae::math::mat;
using yae::math::quaternion_f;

int main()
{
    yae::window window("Test Window", 1280, 720);

    mat<4> model_matrix = yae::math::identity<4>();
    mat<4> view_matrix = yae::math::look_at(yae::math::vec<3>(1.0f, 2.0f, 2.0f), yae::math::vec<3>(), yae::math::vec<3>(0.0f, 1.0f, 0.0f));
    mat<4> projection_matrix = yae::math::perspective(window.get_width(), window.get_height(), 45, 0.1f, 1000.0f);

    {
        yae::skybox skybox("cube_maps/stormydays/");

        yae::mesh model("model/cube2.obj");
        yae::material material(0, 1, 2, 32.0f);

        // lights
        yae::point_light point_light(vec<3>(0, -2.5, 0), vec<3>(0.2f, 0.2f, 0.2f), vec<3>(0.5f, 0.5f, 0.5f), vec<3>(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
        yae::directional_light dir_light(vec<3>(-0.2f, -0.1f, -0.3f), vec<3>(0.2f, 0.2f, 0.2f), vec<3>(0.5f, 0.5f, 0.5f), vec<3>(1.0f, 1.0f, 1.0f));

        // yae::spot_light spot_light_one(vec<3>(-4, 0, 0), vec<3>(4, 0, 0), yae::math::to_radians(12.5), yae::math::to_radians(17.5), vec<3>(0.2f, 0.2f, 0.2f), vec<3>(0.5f, 0.5f, 0.5f), vec<3>(1.0f, 1.0f, 1.0f));
        yae::spot_light spot_light_one(vec<3>(-4, 0, 0), vec<3>(4, 0, 0), yae::math::to_radians(12.5), yae::math::to_radians(17.5), vec<3>(), vec<3>(1, 0, 0), vec<3>(1.0f, 1.0f, 1.0f));
        yae::spot_light spot_light_two(vec<3>(4, 0, 0), vec<3>(-4, 0, 0), yae::math::to_radians(12.5), yae::math::to_radians(17.5), vec<3>(), vec<3>(0, 0, 1), vec<3>(1.0f, 1.0f, 1.0f));

        // buffer
        yae::gl::vertex_array vao;
        yae::gl::index_buffer<GLuint> ibo(model.get_indices().data(), static_cast<GLuint>(model.get_indices().size()));
        yae::gl::buffer<yae::vertex> vbo(model.get_vertices().data(), model.get_vertices().size());


        // vertex layout for shader
        vao.push_layout<0, GLfloat>(&yae::vertex::position, vbo);
        vao.push_layout<1, GLfloat>(&yae::vertex::normal, vbo);
        vao.push_layout<2, GLfloat>(&yae::vertex::texture_coordinate, vbo);


        // shader and uniforms
        yae::gl::shader_program shader("shader/shader.vert", "shader/shader.frag");
        shader.bind();

        shader.set_uniform_material("u_material", material);

        shader.set_uniform_directional_light("u_directional_light", dir_light);
        shader.set_uniform_point_light("u_point_lights", point_light, 0);
        shader.set_uniform_spot_light("u_spot_lights", spot_light_one, 0);
        shader.set_uniform_spot_light("u_spot_lights", spot_light_two, 1);

        shader.set_uniform_mat4("projection", projection_matrix);
        shader.set_uniform_mat4("view", view_matrix);
        shader.set_uniform_mat4("model", model_matrix);


        yae::gl::texture specular_map("textures/container_specular.png");
        yae::gl::texture diffuse_map("textures/container.png");
        //yae::gl::texture emission_map("textures/matrix.jpg");

        diffuse_map.bind(0);
        specular_map.bind(1);
        // emission_map.bind(2);


        double pos = 0;
        double camY = 0.0;
        double radius = 15.0;

        quaternion_f rotation(1, 0, 0, 0);

        double lastTime = glfwGetTime();
        int frames = 0;

        while (!window.should_close())
        {
            frames++;
            if (glfwGetTime() - lastTime >= 1.0)
            {
                std::string title = "FPS: " + std::to_string(frames);
                glfwSetWindowTitle(window.p_window, title.c_str());
                frames = 0;
                lastTime += 1.0;
            }


            window.clear();

            skybox.render(view_matrix, projection_matrix);

            // scene
            shader.bind();
            vao.bind();

            double camX = sin(pos) * radius;
            double camZ = cos(pos) * radius;
            view_matrix = yae::math::look_at(vec<3>(camX, sin(camY) * radius, camZ), vec<3>(0.0, 0.0, 0.0), vec<3>(0.0, 1.0, 0.0));

            shader.set_uniform_vec3("u_view_position", vec<3>(camX, camY, camZ));

            if (glfwGetKey(window.p_window, GLFW_KEY_LEFT) == GLFW_PRESS)
            {
                pos -= 0.1;
            }
            else if (glfwGetKey(window.p_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            {
                pos += 0.1;
            }
            else if (glfwGetKey(window.p_window, GLFW_KEY_UP) == GLFW_PRESS)
            {
                camY += 0.1;
            }
            else if (glfwGetKey(window.p_window, GLFW_KEY_DOWN) == GLFW_PRESS)
            {
                camY -= 0.1;
            }
            if (glfwGetKey(window.p_window, GLFW_KEY_Q) == GLFW_PRESS)
            {
                radius += 0.1;
            }
            else if (glfwGetKey(window.p_window, GLFW_KEY_E) == GLFW_PRESS)
            {
                radius -= 0.1;
            }

            projection_matrix = yae::math::perspective(window.get_width(), window.get_height(), 45, 0.1f, 1000.0f);


            if (glfwGetKey(window.p_window, GLFW_KEY_R) == GLFW_PRESS)
            {
                quaternion_f q;
                q.xyz = -vec<3>(camX, sin(camY) * radius, camZ) * std::sin(0.001f);
                q.w = std::cos(0.001f);
                rotation *= q.normalize();
            }


            model_matrix = rotation.as_rotation_matrix();

            shader.set_uniform_mat4("projection", projection_matrix);
            shader.set_uniform_mat4("view", view_matrix);
            shader.set_uniform_mat4("model", model_matrix);

            ibo.draw();

            window.update();

            yae::gl::check_error();
        }
    }
    return 0;
}
