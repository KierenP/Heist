#include "FunctionLib.h"

float DistanceBetween(float px1, float py1, float px2, float py2)
{
    float DiffX = px1 - px2;
    float DiffY = py1 - py2;

    float DistSqr = DiffX * DiffX + DiffY * DiffY;

    return sqrt(DistSqr);
}

float DistanceBetween(Entity* pEntity1, Entity* pEntity2)
{
    float DiffX = pEntity1->GetPosX() - pEntity2->GetPosX();
    float DiffY = pEntity1->GetPosY() - pEntity2->GetPosY();

    float DistSqr = DiffX * DiffX + DiffY * DiffY;

    return sqrt(DistSqr);
}

float ToDegrees(float radians)
{
    return radians * (180 / _PI);
}

float ToRadians(float degrees)
{
    return degrees * (_PI / 180);
}

float DirectionToPoint(float ax, float ay, float bx, float by)
{
    float DiffX = bx - ax;
    float DiffY = by - ay;

    return atan2(DiffY, DiffX);
}

float DirectionToPoint(Entity* a, Entity* b)
{
    float DiffX = b->GetPosX() - a->GetPosX();
    float DiffY = b->GetPosY() - a->GetPosY();

    return atan2(DiffY, DiffX);
}

