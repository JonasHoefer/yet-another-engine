//
// Created by jonas on 21.12.2017.
//

#ifndef YAE_TYPE_UTILS_H
#define YAE_TYPE_UTILS_H

#define GLEW_STATIC

#include <GL/glew.h>

namespace yae
{
    namespace gl
    {
        template<typename T>
        inline GLenum get_gl_type();

        template<>
        inline GLenum get_gl_type<GLfloat>()
        {
            return GL_FLOAT;
        }

        template<>
        inline GLenum get_gl_type<GLuint>()
        {
            return GL_UNSIGNED_INT;
        }

        template<>
        inline GLenum get_gl_type<GLushort>()
        {
            return GL_UNSIGNED_SHORT;
        }

        template<>
        inline GLenum get_gl_type<GLubyte>()
        {
            return GL_UNSIGNED_BYTE;
        }
    }
}

#endif //YAE_TYPE_UTILS_H
