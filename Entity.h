#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
    Entity();
    Entity(float px, float py) : mPosX(px), mPosY(py) {}
    virtual ~Entity();

    //Getters
    float GetPosX() const { return mPosX; }
    float GetPosY() const { return mPosY; }

    //Setters
    void SetPosX(float val) { mPosX = val; }
    void SetPosY(float val) { mPosY = val; }

protected:
    float mPosX;
    float mPosY;
};

#endif //ENTITY_H
