//
// Created by jonas on 29.09.18.
//

#ifndef YET_ANOTHER_ENGINE_TRANSFORM_HPP
#define YET_ANOTHER_ENGINE_TRANSFORM_HPP

#include "matrix.hpp"

namespace yae
{
    namespace math
    {

        /**
         * @brief creates a translation matrix
         *
         * @param x distance in x direction
         * @param y distance in y direction
         * @param z distance in z direction
         *
         * @return a new translation matrix
         */
        inline mat<4, 4, float> translate(float x, float y, float z)
        {
            return mat<4>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1);
        }

        /**
         * @brief creates a matrix for a perspective projections
         *
         * @param width of the viewport
         * @param height of the viewport
         * @param fov field of view in degree
         * @param far the far clipping plane
         * @param near the near clipping plane
         *
         * @return a matrix for perspective projection with the given parameters
         */
        inline mat<4, 4, float> perspective(unsigned int width, unsigned int height, int fov, float near, float far)
        {
            float ration = width / static_cast<float>(height);
            float tan_fov_h = static_cast<float>(tan((fov * M_PI / 180.0) / 2.0));

            return mat<4>(
                    1 / (ration * tan_fov_h), 0, 0, 0,
                    0, 1 / tan_fov_h, 0, 0,
                    0, 0, (near - far) / (far - near), -1,
                    0, 0, -2 * far * near / (far - near), 0
            );
        }

        /**
         * @brief creates a new matrix which will rotate vertices
         *
         * @param angle of rotation
         * @param axis around which will be rotated
         *
         * @return a matrix rotating which rotates given vectors by the given angles around the given axis
         */
        inline mat<4, 4, float> rotation(double angle, const vec<3, float>& axis)
        {
            mat<4, 4, float> mat(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
            float r = static_cast<float>(angle * M_PI / 180.0);
            float c = std::cos(r);
            float s = std::sin(r);
            float omc = 1.0f - c;

            float x = axis[0];
            float y = axis[1];
            float z = axis[2];

            mat[0][0] = x * omc + c;
            mat[0][1] = y * x * omc + z * s;
            mat[0][2] = x * z * omc - y * s;

            mat[1][0] = x * y * omc - z * s;
            mat[1][1] = y * omc + c;
            mat[1][2] = y * z * omc + x * s;

            mat[2][0] = x * z * omc + y * s;
            mat[2][1] = y * z * omc - x * s;
            mat[2][2] = z * omc + c;

            return mat;
        }

        inline mat<4, 4, float> look_at(const vec<3>& position, const vec<3>& target, const vec<3>& up)
        {
            vec<3> camera_direction = (position - target).normalize();
            vec<3> camera_right = up.cross(camera_direction).normalize();
            vec<3> camera_up = camera_direction.cross(camera_right);

            return mat<4>(
                    camera_right[0], camera_up[0], camera_direction[0], 0,
                    camera_right[1], camera_up[1], camera_direction[1], 0,
                    camera_right[2], camera_up[2], camera_direction[2], 0,
                    0, 0, 0, 1)
                   * translate(-position[0], -position[1], -position[2]);
        }

        template<size_t size, typename T= float>
        inline mat<size, size, T> identity()
        {
            mat<size, size, T> result;
            for (size_t i = 0; i < size; ++i)
                result[i][i] = 1;
            return result;
        }

        inline float to_radians(double degree)
        {
            return static_cast<float>((M_PI / 180.0) * degree);
        }
    }
}

#endif //YET_ANOTHER_ENGINE_TRANSFORM_HPP
