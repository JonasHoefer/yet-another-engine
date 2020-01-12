//
// Created by jonas on 22.12.2017.
//

#ifndef YAE_SHADER_HPP
#define YAE_SHADER_HPP

#define GLEW_STATIC

#include <GL/glew.h>

namespace yae
{
    namespace gl
    {
        /**
         * @brief creates a new shader (not shader program) of either type GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
         *
         * @tparam type of the shader
         *
         * This class creates and deletes a shader object, which will read the source from the given file and compile it.
         */
        template<GLenum type>
        class shader
        {
            friend class shader_program;

        public:
            /**
             * @brief reads the source file and compiles the read code
             *
             * @param path to a file containing the source code of the shader
             */
            shader(const char* path); // NOLINT

            /**
             * @brief deletes the shader
             */
            ~shader();

        private:
            /**
             * OpenGL handle for the shader handled by this class
             */
            GLuint h_shader;
        };

        /**
         * typedef for vertex shader
         */
        using vertex_shader = shader<GL_VERTEX_SHADER>;

        /**
         * typedef for fragment shader
         */
        using fragment_shader = shader<GL_FRAGMENT_SHADER>;
    }
}

#endif //YAE_SHADER_HPP
