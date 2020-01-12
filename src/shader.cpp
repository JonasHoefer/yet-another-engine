//
// Created by jonas on 22.12.2017.
//

#include "yae/gl/shader.hpp"
#include "yae/pil/file_utils.hpp"

#include <vector>
#include <iostream>


namespace yae
{
    namespace gl
    {
        template<GLenum type>
        shader<type>::shader(const char* path)
                : h_shader(glCreateShader(type))
        {
            std::string source = pil::read_file(path);
            const char* p_source = source.c_str();

            glShaderSource(h_shader, 1, &p_source, nullptr);
            glCompileShader(h_shader);


            GLint info_log_length;
            glGetShaderiv(h_shader, GL_INFO_LOG_LENGTH, &info_log_length);
            if (info_log_length > 0)
            {
                std::vector<char> log(static_cast<unsigned long>(info_log_length + 1));
                glGetShaderInfoLog(h_shader, info_log_length, nullptr, &log[0]);
                std::cerr << "[ERROR|OpenGL] Could not compile shader (" << path << "):" << std::endl << log.data()
                          << std::endl;
            }
        }

        template<GLenum type>
        shader<type>::~shader()
        {
            glDeleteShader(h_shader);
        }

        template
        class shader<GL_VERTEX_SHADER>;

        template
        class shader<GL_FRAGMENT_SHADER>;
    }
}
