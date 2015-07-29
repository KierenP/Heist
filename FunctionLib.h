#ifndef FUNCTIONLIB_H
#define FUNCTIONLIB_H

//required headers
#include "Entity.h"

//required preprocessor macros
#define _PI 3.14159265

//member functions
float DistanceBetween(float px1, float py1, float px2, float py2);
float DistanceBetween(Entity* pEntity1, Entity* pEntity2);
float ToDegrees(float radians);
float ToRadians(float degrees);
float DirectionToPoint(float ax, float ay, float bx, float by); //returns in radians the angle from a(x, y) to b(x, y)
float DirectionToPoint(Entity* a, Entity* b);                   //returns in radians the angle from a to b

#endif // FUNCTIONLIB_H
