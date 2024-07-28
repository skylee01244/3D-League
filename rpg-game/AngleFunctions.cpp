#include <cmath>
#include <SFML/Graphics.hpp>

#include "Headers/AngleFunctions.h"
#include "Headers/Global.h"

float PI = 3.141592653589793116f;

float normalize_degrees(float degrees)
{
    return fmod(360.0f + fmod(degrees, 360.0f), 360.0f);
}

float normalize_radians(float radians)
{
    return fmod(2 * PI + fmod(radians, 2 * PI), 2 * PI);
}

float degrees_to_radians(float degrees)
{
    return PI * normalize_degrees(degrees) / 180.0f;
}

float radians_to_degrees(float radians)
{
    return 180.0f * normalize_radians(radians) / PI;
}

float degrees_difference(float angle1, float angle2)
{
    return 180.0f - fabs(fabs(normalize_degrees(angle1) - normalize_degrees(angle2)) - 180.0f);
}

float radians_difference(float angle1, float angle2)
{
    return PI - fabs(fabs(normalize_radians(angle1) - normalize_radians(angle2)) - PI);
}