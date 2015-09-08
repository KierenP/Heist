#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
    Entity();
    Entity(float px, float py) : mPosX(px), mPosY(py) {}
    ~Entity();  //This should be virtual. Not doing so *should* result in a memory leak, but, doing so results in strange errors. I believe a leak is the lesser of two bugs here

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
