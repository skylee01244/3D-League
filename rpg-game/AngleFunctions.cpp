#include <cmath>
#include <SFML/Graphics.hpp>

#include "Headers/AngleFunctions.h"
#include "Headers/Global.h"

namespace {
    constexpr float PI = 3.14159265358979323846f;
    constexpr float CIRCLE = 360.0f;
}


// Normalize [0, 360)
float normalize_degrees(float degrees)
{
    return std::fmod(CIRCLE + std::fmod(degrees, CIRCLE), CIRCLE);
}
// Normalize [0, 2pi)
float normalize_radians(float radians)
{
    return std::fmod(2.0f * PI + std::fmod(radians, 2.0f * PI), 2.0f * PI);
}

float degrees_to_radians(float degrees)
{
    return normalize_degrees(degrees) * (PI / 180.0f);
}

float radians_to_degrees(float radians)
{
    return normalize_radians(radians) * (180.0f / PI);
}

float degrees_difference(float angle1, float angle2)
{
    float diff = std::fabs(normalize_degrees(angle1) - normalize_degrees(angle2));
    return std::fmin(diff, CIRCLE - diff);
}

float radians_difference(float angle1, float angle2)
{
    float diff = std::fabs(normalize_radians(angle1) - normalize_radians(angle2));
    return std::fmin(diff, 2.0f * PI - diff);
}