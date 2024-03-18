#include <complex>
#include "framework/MathUtility.h"

namespace ly
{
    const float PI = 3.1415926535;

    sf::Vector2f RotationToVector(float rotation)
    {
        float radians = DegreesToRadians(rotation);
        return {std::cos(radians), std::sin(radians)};
    }

    float DegreesToRadians(float degrees)
    {
        return degrees * (PI / 180.f);
    }

    float RadiansToDegrees(float radians)
    {
        return radians * (180.f / PI);
    }
}