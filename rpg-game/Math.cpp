#include "Math.h"

sf::Vector2f Math::NormaliseVector(sf::Vector2f vector)
{
    float m = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    sf::Vector2f normalisedVector;
    normalisedVector.x = vector.x / m;
    normalisedVector.y = vector.y / m;
    return normalisedVector;
}