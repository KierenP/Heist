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

#endif // FUNCTIONLIB_H
