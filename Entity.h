#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
public:
    Entity();
    ~Entity();

    //Getters
    float GetPosX() { return PosX; }
    float GetPosY() { return PosY; }

    //Setters
    void SetPosX(float val) { PosX = val; }
    void SetPosY(float val) { PosY = val; }

    //Member functions
    float DistanceToPoint(float px, float py);
    float DistanceToPoint(Entity* pEntity);

    float DirectionToPoint(float px, float py);
    float DirectionToPoint(Entity* pEntity);

private:
    float PosX;
    float PosY;
};

#endif ENTITY_H
