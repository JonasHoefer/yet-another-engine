//
// Created by jonas on 24.02.2018.
//

#include "yae/gl/shader_program.hpp"
#include <vector>
#include <iostream>
#include <yae/gl/shader_program.hpp>


namespace yae
{
    namespace gl
    {
#define INDEX(x) ((x) >= 0 ? ("[" + std::to_string(x) + "]") : "")

        shader_program::shader_program(const vertex_shader& vertex_shader, const fragment_shader& fragment_shader)
                : h_program(glCreateProgram())
        {
            glAttachShader(h_program, vertex_shader.h_shader);
            glAttachShader(h_program, fragment_shader.h_shader);

            glLinkProgram(h_program);

            glDetachShader(h_program, vertex_shader.h_shader);
            glDetachShader(h_program, fragment_shader.h_shader);


            GLint info_log_length;
            glGetProgramiv(h_program, GL_INFO_LOG_LENGTH, &info_log_length);
            if (info_log_length > 0)
            {
                std::vector<char> log(static_cast<unsigned long>(info_log_length + 1));
                glGetProgramInfoLog(h_program, info_log_length, nullptr, &log[0]);
                std::cerr << "[ERROR|OpenGL] Could not link shader program:" << std::endl << log.data() << std::endl;
            }
        }

        shader_program::shader_program(shader_program&& other) noexcept
                : h_program(other.h_program)
        {
            other.h_program = 0;
        }

        shader_program& shader_program::operator=(shader_program&& other) noexcept
        {
            if (this != &other)
            {
                release();
                h_program = other.h_program;
                other.h_program = 0;
            }

            return *this;
        }

        shader_program::~shader_program()
        {
            unbind();
            release();
        }

        void shader_program::bind() const
        {
            glUseProgram(h_program);
        }

        void shader_program::unbind() const
        {
            glUseProgram(0);
        }

        void shader_program::set_uniform_mat4(const std::string& name, const math::mat<4, 4, GLfloat>& matrix)
        {
            glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, matrix.data());
        }

        void shader_program::set_uniform_vec3(const std::string& name, const math::vec<3, GLfloat>& vector)
        {
            glUniform3fv(get_uniform_location(name), 1, vector.data());
        }

        void shader_program::set_uniform_float(const std::string& name, float value)
        {
            glUniform1f(get_uniform_location(name), value);
        }

        void shader_program::set_uniform_int(const std::string& name, int value)
        {
            glUniform1i(get_uniform_location(name), value);
        }

        void shader_program::set_uniform_material(const std::string& name, const material& material)
        {
            set_uniform_int(name + ".diffuse", material.get_diffuse());
            set_uniform_int(name + ".specular", material.get_specular());
            set_uniform_int(name + ".emission", material.get_emission());
            set_uniform_float(name + ".shininess", material.get_shininess());
        }

        void shader_program::set_uniform_point_light(const std::string& name, const point_light& light, int array_index)
        {
            set_uniform_vec3(name + INDEX(array_index) + ".position", light.get_position());
            set_uniform_vec3(name + INDEX(array_index) + ".ambient", light.get_ambient());
            set_uniform_vec3(name + INDEX(array_index) + ".diffuse", light.get_diffuse());
            set_uniform_vec3(name + INDEX(array_index) + ".specular", light.get_specular());
            set_uniform_float(name + INDEX(array_index) + ".constant", light.get_constant());
            set_uniform_float(name + INDEX(array_index) + ".linear", light.get_linear());
            set_uniform_float(name + INDEX(array_index) + ".quadratic", light.get_quadratic());
        }

        void shader_program::set_uniform_directional_light(const std::string& name, const directional_light& light)
        {
            set_uniform_vec3(name + ".direction", light.get_direction());
            set_uniform_vec3(name + ".ambient", light.get_ambient());
            set_uniform_vec3(name + ".diffuse", light.get_diffuse());
            set_uniform_vec3(name + ".specular", light.get_specular());
        }

        void shader_program::set_uniform_spot_light(const std::string& name, const spot_light& light, int array_index)
        {
            set_uniform_vec3(name + INDEX(array_index) + ".position", light.get_position());
            set_uniform_vec3(name + INDEX(array_index) + ".direction", light.get_direction());
            set_uniform_vec3(name + INDEX(array_index) + ".ambient", light.get_ambient());
            set_uniform_vec3(name + INDEX(array_index) + ".diffuse", light.get_diffuse());
            set_uniform_vec3(name + INDEX(array_index) + ".specular", light.get_specular());
            set_uniform_float(name + INDEX(array_index) + ".cutoff_angle", std::cos(light.get_cutoff_angle()));
            set_uniform_float(name + INDEX(array_index) + ".outer_cutoff_angle", std::cos(light.get_outer_cutoff_angle()));
        }

        GLint shader_program::get_uniform_location(const std::string& name)
        {
            if (m_location_cache.count(name) > 0)
            {
                return m_location_cache[name];
            }

            GLint location = glGetUniformLocation(h_program, name.data());
            if (location == -1)
            {
                std::cerr << "[WARNING|OpenGL] Uniform variable not found: '" << name << "'" << std::endl;
            }
            else
            {
                m_location_cache[name] = location;
            }

            return location;
        }

        void shader_program::release()
        {
            if (h_program)
            {
                glDeleteProgram(h_program);
            }
        }
    }
}
