//
// Created by jonas on 02.03.2018.
//

#ifndef YET_ANOTHER_ENGINE_VERTEX_DATA_HPP
#define YET_ANOTHER_ENGINE_VERTEX_DATA_HPP

#include <ostream>
#include "yae/math/matrix.hpp"

namespace yae
{
    /**
      * @brief memory layout of a single vertex point
      */
    class vertex
    {
    public:
        vertex(const math::vec<3>& position,
               const math::vec<2>& texture_coordinate,
               const math::vec<3>& normal,
               const math::vec<4>& color = math::vec<4>(1, 0, 0, 1));

    public:
        math::vec<3, float> position;
        math::vec<2, float> texture_coordinate;
        math::vec<3, float> normal;
        math::vec<4, float> color;

    public:
        bool operator==(const vertex& other) const
        {
            return position == other.position &&
                   color == other.color &&
                   texture_coordinate == other.texture_coordinate &&
                   normal == other.normal;
        }

        friend std::ostream& operator<<(std::ostream& os, const vertex& data)
        {
            return os << "vertex["
                      << data.position << "|"
                      << data.normal << "|"
                      << data.color << "|"
                      << data.texture_coordinate << "]";
        }
    };
}

namespace std
{
    template<>
    struct hash<yae::vertex>
    {
        size_t operator()(const yae::vertex& vert) const
        {
            return
                    hash<yae::math::matrix<3, 1, float>>()(vert.position) ^
                    hash<yae::math::matrix<2, 1, float>>()(vert.texture_coordinate) ^
                    hash<yae::math::matrix<3, 1, float>>()(vert.normal) ^
                    hash<yae::math::matrix<4, 1, float>>()(vert.color);
        }
    };
}

#endif //YET_ANOTHER_ENGINE_VERTEX_DATA_HPP
