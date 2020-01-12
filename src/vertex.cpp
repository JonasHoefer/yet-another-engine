//
// Created by jonas on 20.03.18.
//

#include "yae/vertex.hpp"

namespace yae
{
    vertex::vertex(const math::vec<3>& position,
                   const math::vec<2>& texture_coordinate,
                   const math::vec<3>& normal,
                   const math::vec<4>& color)
            : position(position),
              texture_coordinate(texture_coordinate),
              normal(normal),
              color(color) {}
}
