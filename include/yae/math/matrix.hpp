//
// Created by jonas on 08.09.18.
//

#ifndef YET_ANOTHER_ENGINE_MATRIX_HPP
#define YET_ANOTHER_ENGINE_MATRIX_HPP

#include <ostream>
#include <cmath>

namespace yae
{
    namespace math
    {
        /**
         * @brief a matrix in column major order
         *
         * @tparam height of the matrix
         * @tparam width of the matrix
         * @tparam T data type used by the matrix
         */
        template<unsigned int height, unsigned int width, typename T>
        class matrix
        {
        public:
            /**
             * @tparam Args variadic template for initialization
             * @param args elements which should be stored in this matrix
             */
            template<typename... Args>
            constexpr explicit matrix(Args&& ... args) noexcept : m_data{static_cast<T>(args)...} {}

            /**
             * @brief creates a null matrix
             */
            matrix() : m_data{} {}

        private:
            union
            {
                T m_data[width * height];
                matrix<height, 1, T> m_columns[width];
            };

        public:
            /**
             * @brief scalar multiplication
             *
             * @param scalar with which all elements of the matrix will be multiplied
             * @return this matrix after the multiplication
             */
            matrix<height, width, T>& operator*=(const T& scalar)
            {
                for (T& element : m_data)
                    element *= scalar;
                return *this;
            }

            /**
             * @brief scalar division
             *
             * @param scalar with which all elements of the matrix will be divided
             * @return this matrix after the division
             */
            matrix<height, width, T>& operator/=(const T& scalar)
            {
                for (T& element : m_data)
                    element /= scalar;
                return *this;
            }

            /**
             * @brief component wise addition
             *
             * @param other another matrix with the same size
             * @return this matrix after the addition
             */
            matrix<height, width, T>& operator+=(const matrix<height, width, T>& other)
            {
                for (size_t i = 0; i < width * height; ++i)
                {
                    m_data[i] += other.m_data[i];
                }
                return this;
            }

            /**
             * @brief component wise subtraction
             *
             * @param other another matrix with the same size
             * @return this matrix after the subtraction
             */
            matrix<height, width, T>& operator-=(const matrix<height, width, T>& other)
            {
                for (size_t i = 0; i < width * height; ++i)
                {
                    m_data[i] -= other.m_data[i];
                }
                return this;
            }

            /**
             * implemented using == operator of the template type T
             *
             * @param other another matrix of same size and type
             * @return true if all components are equal
             */
            bool operator==(const matrix<height, width, T>& other)
            {
                for (size_t i = 0; i < width * height; ++i)
                {
                    if (m_data[i] != other.m_data[i])
                    {
                        return false;
                    }
                }
                return true;
            }

            /**
             * implemented using != operator of the template type T
             *
             * @param other another matrix of same size and type
             * @return true if not all elements are equal
             */
            bool operator!=(const matrix<height, width, T>& other)
            {
                for (size_t i = 0; i < width * height; ++i)
                {
                    if (m_data[i] != other.m_data[i])
                    {
                        return true;
                    }
                }
                return false;
            }

            /**
             * @param index of the column
             * @return reference to the column at the given index
             */
            matrix<height, 1, T>& operator[](unsigned int index)
            {
                return m_columns[index];
            }

            /**
             * @param index of the column
             * @return const reference to the column at the given index
             */
            const matrix<height, 1, T>& operator[](unsigned int index) const
            {
                return m_columns[index];
            }

            /**
             * @brief since this class only contains an array to store it's elements 'm_data' equals 'this'
             *
             * @return pointer to the data of this matrix
             */
            T* data()
            {
                return m_data;
            }

            /**
             * @brief since this class only contains an array to store it's elements 'm_data' equals 'this'
             *
             * @return const pointer to the data of this matrix
             */
            const T* data() const
            {
                return m_data;
            }

            friend std::ostream& operator<<(std::ostream& os, const matrix<height, width, T>& matrix)
            {
                os << "mat" << height << width << "[" << matrix.m_data[0];
                for (size_t i = 1; i < height * width; ++i)
                    os << ", " << matrix.m_data[i];
                return os << "]";
            }
        };

        /**
         * @brief a simple column vector, implemented as a specialization of a m cross n matrix
         *
         * @tparam components amount of vector components
         * @tparam T data type used by the matrix
         */
        template<unsigned int components, typename T>
        class matrix<components, 1, T>
        {
        public:
            /**
             * @tparam Args variadic template for initialization
             * @param args components which should be stored in this vector
             */
            template<typename... Args>
            constexpr explicit matrix(Args&& ... args) noexcept : m_data{static_cast<T>(args)...} {}

            /**
             * @brief creates a null matrix
             */
            matrix() : m_data{} {}

        private:
            T m_data[components];

        public:
            /**
             * @brief scalar multiplication
             *
             * @param scalar with which all elements of the vector will be multiplied
             * @return this vector after the multiplication
             */
            matrix<components, 1, T>& operator*=(const T& scalar)
            {
                for (T& component : m_data)
                    component *= scalar;
                return *this;
            }

            /**
             * @brief scalar division
             *
             * @param scalar with which all elements of the vector will be divided
             * @return this vector after the division
             */
            matrix<components, 1, T>& operator/=(const T& scalar)
            {
                for (T& component : m_data)
                    component /= scalar;
                return *this;
            }

            /**
             * @brief component wise addition
             *
             * @param other another vector with the same size
             * @return this vector after the addition
             */
            matrix<components, 1, T>& operator+=(const matrix<components, 1, T>& other)
            {
                for (size_t i = 0; i < components; ++i)
                {
                    m_data[i] += other.m_data[i];
                }
                return *this;
            }

            /**
             * @brief component wise subtraction
             *
             * @param other another vector with the same size
             * @return this vector after the subtraction
             */
            matrix<components, 1, T>& operator-=(const matrix<components, 1, T>& other)
            {
                for (size_t i = 0; i < components; ++i)
                {
                    m_data[i] -= other.m_data[i];
                }
                return *this;
            }

            matrix<components, 1, T> operator-() const
            {
                matrix<components, 1, T> vec;
                for (size_t i = 0; i < components; ++i)
                {
                    vec.m_data[i] = -m_data[i];
                }
                return vec;
            }

            /**
             * implemented using == operator of the template type T
             *
             * @param other another vector with same size and type
             * @return true if all components are equal
             */
            bool operator==(const matrix<components, 1, T>& other) const
            {
                for (size_t i = 0; i < components; ++i)
                {
                    if (m_data[i] != other.m_data[i])
                    {
                        return false;
                    }
                }
                return true;
            }

            /**
             * implemented using != operator of the template type T
             *
             * @param other another vector of same size and type
             * @return true if not all elements are equal
             */
            bool operator!=(const matrix<components, 1, T>& other)
            {
                for (size_t i = 0; i < components; ++i)
                {
                    if (m_data[i] != other.m_data[i])
                    {
                        return true;
                    }
                }
                return false;
            }

            /**
             * @brief dot product
             *
             * @tparam U type
             * @param other vector with same number of components
             * @return the dot product of the two vectors
             */
            template<typename U = T>
            std::common_type_t<T, U> dot(const matrix<components, 1, U>& other) const
            {
                std::common_type_t<T, U> result{};
                for (size_t i = 0; i < components; ++i)
                    result += m_data[i] * other.m_data[i];
                return result;
            }

            /**
             * @brief cross product
             */
            template<typename V, typename U = matrix<3, 1, std::common_type_t<T, V>>>
            auto cross(const matrix<3, 1, V>& other) const -> std::enable_if_t<components == 3, U>
            {
                return matrix(
                        m_data[1] * other.m_data[2] - m_data[2] * other.m_data[1],
                        m_data[2] * other.m_data[0] - m_data[0] * other.m_data[2],
                        m_data[0] * other.m_data[1] - m_data[1] * other.m_data[0]
                );
            }

            T norm() const
            {
                T norm{};
                for (const T& element : m_data)
                    norm += element * element;
                return std::sqrt(norm);
            }

            matrix<components, 1, T> normalize() const
            {
                return *this / norm();
            }

            /**
             * @param index of the element
             * @return reference to the element at the given index
             */
            T& operator[](unsigned int index)
            {
                return m_data[index];
            }

            /**
             * @param index of the element
             * @return reference to the element at the given index
             */
            const T& operator[](unsigned int index) const
            {
                return m_data[index];
            }

            /**
             * @brief since this class only contains an array to store it's elements 'm_data' equals 'this'
             *
             * @return pointer to the data of this matrix
             */
            T* data()
            {
                return m_data;
            }

            /**
             * @brief since this class only contains an array to store it's elements 'm_data' equals 'this'
             *
             * @return const pointer to the data of this matrix
             */
            const T* data() const
            {
                return m_data;
            }

            friend std::ostream& operator<<(std::ostream& os, const matrix<components, 1, T>& vec)
            {
                os << "vec" << components << "[" << vec.m_data[0];
                for (size_t i = 1; i < components; ++i)
                    os << ", " << vec.m_data[i];
                return os << "]";
            }
        };

        template<typename T, unsigned int width, unsigned int height>
        matrix<height, width, T> operator+(matrix<height, width, T> lhs, const matrix<height, width, T>& rhs)
        {
            return lhs += rhs;
        }

        template<typename T, unsigned int width, unsigned int height>
        matrix<height, width, T> operator-(matrix<height, width, T> lhs, const matrix<height, width, T>& rhs)
        {
            return lhs -= rhs;
        }

        template<typename T, unsigned int height, unsigned int width>
        matrix<height, width, T> operator*(matrix<height, width, T> matrix, const T& scalar)
        {
            return matrix *= scalar;
        }

        template<typename T, unsigned int height, unsigned int width>
        matrix<height, width, T> operator*(const T& scalar, matrix <height, width, T> matrix)
        {
            return matrix *= scalar;
        }

        template<typename T, unsigned int height, unsigned int width>
        matrix<height, width, T> operator/(matrix<height, width, T> matrix, const T& scalar)
        {
            return matrix /= scalar;
        }

        template<typename T, typename U, unsigned int width, unsigned int height, unsigned int identical>
        matrix<height, width, std::common_type_t<T, U>> operator*(const matrix <height, identical, T>& lhs, const matrix <identical, width, U>& rhs)
        {
            matrix<height, width, std::common_type_t<T, U>> result;
            for (size_t y = 0; y < height; ++y)
            {
                for (size_t x = 0; x < width; ++x)
                {
                    for (size_t i = 0; i < identical; ++i)
                    {
                        result.data()[y + height * x] += lhs.data()[i * height + y] * rhs.data()[i + identical * x];
                    }
                }
            }
            return result;
        }

        template<unsigned int components, typename T = float>
        using vec = matrix<components, 1, T>;

        template<unsigned int height, unsigned int width = height, typename T = float>
        using mat = matrix<height, width, T>;
    }
}

namespace std
{
    template<unsigned int height, unsigned int width, typename T>
    struct hash<yae::math::matrix<height, width, T>>
    {
        size_t operator()(const yae::math::matrix<height, width, T>& mat) const
        {
            size_t result = 0;
            for (int i = 0; i < height * width; ++i)
            {
                result = ((result >> 1) ^ hash<T>()(mat.data()[i])) << 1;
            }
            return result;
        }
    };
}

#endif //YET_ANOTHER_ENGINE_MATRIX_HPP
