//
// Created by jonas on 24.02.2018.
//

#ifndef YET_ANOTHER_ENGINE_SHADER_PROGRAM_HPP
#define YET_ANOTHER_ENGINE_SHADER_PROGRAM_HPP

#include <map>
#include <string>

#include "yae/gl/shader.hpp"
#include "yae/material.hpp"
#include "yae/directional_light.hpp"
#include "yae/point_light.hpp"
#include "yae/spot_light.hpp"


namespace yae
{
    namespace gl
    {
        /**
         * @brief a shader program (actual shader)
         *
         * This class links together multiple shader objects to create a shader program.
         * Represents an actual shader, which can be used by the application.
         */
        class shader_program
        {
        public:
            /**
             * @brief links a fragment and a vertex shader
             *
             * @param vertex_shader a vertex shader
             * @param fragment_shader a fragment shader
             *
             * Creates a minimal shader program by linking a vertex and a fragment shader. Those two kinds of shader are
             * necessary to create a working shader program. The vertex and fragment shader can be deleted after the
             * creation of the shader program.
             */
            shader_program(const vertex_shader& vertex_shader, const fragment_shader& fragment_shader);

            /**
             * can't be copied only referenced and moved
             */
            shader_program(const shader_program&) = delete;

            /**
             * can't be copied only referenced and moved
             */
            shader_program& operator=(const shader_program&) = delete;

            /**
             * moves the responsibility of managing the underlying shader program from the given instance to this one
             *
             * @param other another shader_program object which should be moved
             */
            shader_program(shader_program&& other) noexcept;

            /**
             * moves the responsibility of managing the underlying shader program from the given instance to this one
             *
             * @param other another shader_program obejct which should be moved
             */
            shader_program& operator=(shader_program&& other) noexcept;

            /**
             * deletes the shader program
             */
            ~shader_program();

        private:
            /**
             * the OpenGL handle for this shader program
             */
            GLuint h_program;

            /**
             * caches uniform variable handles since lookups are expensive
             */
            std::map<std::string, GLint> m_location_cache;

        public:
            /**
             * @brief allows to set uniform variables of type mat4
             *
             * @param name of the uniform variable
             * @param matrix the matrix which will be send to the GPU
             */
            void set_uniform_mat4(const std::string& name, const math::mat<4, 4, GLfloat>& matrix);

            /**
             * @brief allows to set a uniform float variable
             *
             * @param name of the uniform variable
             * @param value of the variable
             */
            void set_uniform_float(const std::string& name, float value);

            /**
             * @brief allows to set a uniform vec3 variable
             *
             * @param name of the uniform variable
             * @param value of the variable
             */
            void set_uniform_vec3(const std::string& name, const math::vec<3, GLfloat>& value);

            /**
             * @brief allows to set a uniform int variable
             *
             * @param name of the uniform variable
             * @param value of the variable
             */
            void set_uniform_int(const std::string& name, int value);

            /**
             * @brief allows to set a uniform material struct
             *
             * @param name of the uniform variable
             * @param material which will be send to the gpu
             */
            void set_uniform_material(const std::string& name, const material& material);

            /**
             * @brief allows to set a uniform point light struct
             *
             * @param name of the uniform variable
             * @param light which will be send to the gpu
             * @param array_index optional, if a positive value is given an array element will be set
             */
            void set_uniform_point_light(const std::string& name, const point_light& light, int array_index = -1);

            /**
             * @brief allows to set a uniform directional light struct
             *
             * @param name of the uniform variable
             * @param light which will be send to the gpu
             */
            void set_uniform_directional_light(const std::string& name, const directional_light& light);

            /**
             * @brief allows to set a uniform spot light struct
             *
             * @param name of the uniform variable
             * @param light which will be send to the gpu
             * @param array_index optional, if a positive value is given an array element will be set
             */
            void set_uniform_spot_light(const std::string& name, const spot_light& light, int array_index = -1);

            /**
             * @brief this shader program will be used for future shader operations
             *
             * The currently bound shader program will be unbound.
             */
            void bind() const;

            /**
             * @brief unbinds the current shader
             */
            void unbind() const;

        private:
            /**
             * @brief searches the uniform location corresponding to a variable name
             *
             * @param name of a uniform variable
             *
             * @return the location handle
             *
             * The location is cached for future look ups.
             */
            GLint get_uniform_location(const std::string& name);

            /**
             * deletes the shader program
             */
            void release();
        };
    }
}

#endif //YET_ANOTHER_ENGINE_SHADER_PROGRAM_HPP
