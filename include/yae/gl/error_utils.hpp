//
// Created by jonas on 14.02.2018.
//

#ifndef YET_ANOTHER_ENGINE_ERROR_UTILS_HPP
#define YET_ANOTHER_ENGINE_ERROR_UTILS_HPP

#include <iostream>
#include <string>

#define GLEW_STATIC

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) exit(0);
#define GL_CALL(x) yae::gl::clear_error();\
    x;\
    ASSERT(yae::gl::check_error(#x, __FILE__, __LINE__));


namespace yae
{
    namespace gl
    {
        /**
         * clears all pending error flags
         */
        static void clear_error()
        {
            while (glGetError() != GL_NO_ERROR);
        }

        static std::string get_error_name(GLenum type)
        {
            switch (type)
            {
                case GL_INVALID_ENUM:
                    return "INVALID_ENUM";

                case GL_INVALID_VALUE:
                    return "INVALID_VALUE";

                case GL_INVALID_OPERATION:
                    return "INVALID_OPERATION";

                case GL_STACK_OVERFLOW:
                    return "STACK_OVERFLOW";

                case GL_STACK_UNDERFLOW:
                    return "STACK_UNDERFLOW";

                case GL_OUT_OF_MEMORY:
                    return "OUT_OF_MEMORY";

                default:
                    return "UNKNOWN ERROR: " + std::to_string(type);
            }
        }

        /**
         * prints all pending errors
         */
        static bool check_error(const char* function = nullptr, const char* file = nullptr, int line = 0)
        {
            bool no_error = true;
            while (GLenum error = glGetError())
            {
                std::cerr << "[ERROR|OpenGL] (" << error << " - " << get_error_name(error) << ") " << function << " " << file << ": " << line << std::endl;
                no_error = false;
            }
            return no_error;
        }
    }
}

#endif //YET_ANOTHER_ENGINE_ERROR_UTILS_HPP
