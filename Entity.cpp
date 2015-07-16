#include "DrawableEntity.h"


Entity::Entity()
{

}

Entity::~Entity()
{

}

float Entity::DistanceToPoint(float px, float py)
{
    float DiffX = px - mPosX;
    float DiffY = py - mPosY;

    float DistSqr = DiffX * DiffX + DiffY * DiffY;

    return sqrt(DistSqr);
}

float Entity::DistanceToPoint(Entity* pEntity)
{
    float DiffX = pEntity->GetPosX() - mPosX;
    float DiffY = pEntity->GetPosY() - mPosY;

    float DistSqr = DiffX * DiffX + DiffY * DiffY;

    return sqrt(DistSqr);
}

float Entity::DirectionToPoint(float px, float py)
{
    float DiffX = px - mPosX;
    float DiffY = py - mPosY;

    return atan2(DiffY, DiffX) * 180 / 3.14159; //convert from radians to degrees
}

float Entity::DirectionToPoint(Entity* pEntity)
{
    float DiffX = pEntity->GetPosX() - mPosX;
    float DiffY = pEntity->GetPosY() - mPosY;

    return atan2(DiffY, DiffX) * 180 / 3.14159; //convert from radians to degrees
}
