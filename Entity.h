#ifndef ENTITY_H
#define ENTITY_H

#include <cmath>

class Entity
{
public:
    Entity();
    Entity(float px, float py) : mPosX(px), mPosY(py) {}
    ~Entity();

    //Getters
    float GetPosX() { return mPosX; }
    float GetPosY() { return mPosY; }

    //Setters
    void SetPosX(float val) { mPosX = val; }
    void SetPosY(float val) { mPosY = val; }

    //Member Functions
    float DirectionToPoint(float px, float py);
    float DirectionToPoint(Entity* pEntity);

protected:
    float mPosX;
    float mPosY;
};

#endif //ENTITY_H
