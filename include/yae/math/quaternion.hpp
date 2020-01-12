//
// Created by jonas on 22.09.18.
//

#ifndef YET_ANOTHER_ENGINE_QUATERNION_HPP
#define YET_ANOTHER_ENGINE_QUATERNION_HPP

#include <ostream>
#include <cmath>

#include "matrix.hpp"

namespace yae
{
    namespace math
    {
        template<typename T>
        class quaternion
        {
        public:
            constexpr quaternion() : w(0), xyz() {};

            constexpr quaternion(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}

            constexpr quaternion(T w, const vec<3, T>& xyz) : w(w), xyz(xyz) {}

            T w;

            union
            {
                struct
                {
                    T x, y, z;
                };
                vec<3, T> xyz;
            };

            quaternion<T>& operator+=(const quaternion<T>& other)
            {
                w += other.w;
                xyz += other.xyz;
                return *this;
            }

            quaternion<T>& operator-=(const quaternion<T>& other)
            {
                w -= other.w;
                xyz -= other.xyz;
                return *this;
            }

            quaternion<T>& operator*=(const quaternion<T>& other)
            {
                T new_w = w * other.w - xyz.dot(other.xyz);
                vec<3, T> new_xyz = w * other.xyz + other.w * xyz + xyz.cross(other.xyz);

                w = new_w;
                xyz = new_xyz;

                return *this;
            }

            quaternion<T> operator~() const
            {
                return quaternion(w, -xyz);
            }

            T norm() const
            {
                return std::sqrt(w * w + x * x + y * y + z * z);
            }

            quaternion<T> normalize() const
            {
                T n = norm();
                return quaternion(w / n, x / n, y / n, z / n);
            }

            mat<4, 4, T> as_rotation_matrix() const
            {
                matrix<4, 4, T> m1(
                        w, -z, y, -x,
                        z, w, -x, -y,
                        -y, x, w, -z,
                        x, y, z, w
                );

                matrix<4, 4, T> m2(
                        w, -z, y, x,
                        z, w, -x, y,
                        -y, x, w, z,
                        -x, -y, -z, w
                );

                return m1 * m2;
            }

            friend std::ostream& operator<<(std::ostream& os, const quaternion<T>& q)
            {
                return os << "Q[" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << "]";
            }
        };

        template<typename T>
        quaternion<T> operator*(quaternion<T> lhs, const quaternion<T>& rhs)
        {
            return lhs *= rhs;
        }

        template<typename T>
        quaternion<T> operator+(quaternion<T> lhs, const quaternion<T>& rhs)
        {
            return lhs += rhs;
        }

        template<typename T>
        quaternion<T> operator-(quaternion<T> lhs, const quaternion<T>& rhs)
        {
            return lhs -= rhs;
        }

        constexpr quaternion<long double> operator ""_rl(long double w)
        {
            return quaternion<long double>{w, 0, 0, 0};
        }

        constexpr quaternion<long double> operator ""_il(long double x)
        {
            return quaternion<long double>{0, x, 0, 0};
        }

        constexpr quaternion<long double> operator ""_jl(long double y)
        {
            return quaternion<long double>{0, 0, y, 0};
        }

        constexpr quaternion<long double> operator ""_kl(long double z)
        {
            return quaternion<long double>{0, 0, 0, z};
        }

        constexpr quaternion<double> operator ""_r(long double w)
        {
            return quaternion<double>{static_cast<double>(w), 0, 0, 0};
        }

        constexpr quaternion<double> operator ""_i(long double x)
        {
            return quaternion<double>{0, static_cast<double>(x), 0, 0};
        }

        constexpr quaternion<double> operator ""_j(long double y)
        {
            return quaternion<double>{0, 0, static_cast<double>(y), 0};
        }

        constexpr quaternion<double> operator ""_k(long double z)
        {
            return quaternion<double>{0, 0, 0, static_cast<double>(z)};
        }

        constexpr quaternion<float> operator ""_rf(long double w)
        {
            return quaternion<float>{static_cast<float>(w), 0, 0, 0};
        }

        constexpr quaternion<float> operator ""_if(long double x)
        {
            return quaternion<float>{0, static_cast<float>(x), 0, 0};
        }

        constexpr quaternion<float> operator ""_jf(long double y)
        {
            return quaternion<float>{0, 0, static_cast<float>(y), 0};
        }

        constexpr quaternion<float> operator ""_kf(long double z)
        {
            return quaternion<float>{0, 0, 0, static_cast<float>(z)};
        }

        using quaternion_f = quaternion<float>;
    }
}

#endif //YET_ANOTHER_ENGINE_QUATERNION_HPP
