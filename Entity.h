#ifndef ENTITY_H
#define ENTITY_H

/*

	This has become so simple, that it might very well be redundant. All it does, is be inherited by all "things" to give them all the same interface,
	but that interface is so simple it looses meaning and purpose. Im not going to remove this class at the moment (26-9-15) but will look into removing it in the future

*/

class Entity
{
public:
    Entity(float px = 0, float py = 0) : mPosX(px), mPosY(py) {}
    virtual ~Entity() {}  

    float GetPosX() const { return mPosX; }
    float GetPosY() const { return mPosY; }

    void SetPosX(float val) { mPosX = val; }
    void SetPosY(float val) { mPosY = val; }

private:
    float mPosX;
    float mPosY;
};

#endif //ENTITY_H
