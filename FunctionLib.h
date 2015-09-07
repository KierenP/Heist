#ifndef FUNCTIONLIB_H
#define FUNCTIONLIB_H

#include "Entity.h"
#include "SFML/Graphics.hpp"

const float _PI = 3.14f;

namespace FunctionLib
{
    float DistanceBetween(float px1, float py1, float px2, float py2);
    float DistanceBetween(Entity& pEntity1, Entity& pEntity2);
    float ToDegrees(float radians);
    float ToRadians(float degrees);
    float DirectionToPoint(float ax, float ay, float bx, float by); //returns in radians the angle from a(x, y) to b(x, y)
    float DirectionToPoint(Entity& a, Entity& b);                   //returns in radians the angle from a to b

    std::vector<sf::Vector2f> GenerateBoxFromSprite(sf::Sprite& pSprite);
    std::vector<sf::Vector2f> GenerateBoxFromDimentions(float px, float py, float width, float height);
}

#endif // FUNCTIONLIB_H
