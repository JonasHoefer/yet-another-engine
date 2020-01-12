//
// Created by jonas on 22.09.18.
//

#include <iostream>

#include "yae/math/matrix.hpp"
#include "yae/math/quaternion.hpp"
#include "yae/math/transform.hpp"

#define PI 3.14159265f

using yae::math::operator ""_rf;
using yae::math::operator ""_if;
using yae::math::operator ""_jf;
using yae::math::operator ""_kf;

using yae::math::vec;
using yae::math::mat;
using yae::math::quaternion;

int main()
{
    vec<3> pVec(3, 1, 0);
    quaternion<float> P(0, pVec);
    quaternion<float> R(std::cos(PI / 4), 0, std::sin(PI / 4), 0);
    quaternion<float> RC = ~R;

    for (int i = 0; i < 4; ++i)
    {
        std::cout << R << " * " << P << " * " << RC << " = " << (RC * P * R) << std::endl;
        P = (RC * P * R);
    }
}
