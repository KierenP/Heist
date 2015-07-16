#ifndef DRAWABLEENTITY_H
#define DRAWABLEENTITY_H

/*
    15/7: Disregard this class, it is currently a work in progress, and now after reaseaching what I aim to achieve needs major refactoring. pns club
*/


class DrawableEntity
{
public:
    DrawableEntity();
    ~DrawableEntity();

    float GetPosX() { return PosX; }
    float GetPosY() { return PosY; }

    void SetPosX(float val) { PosX = val; }
    void SetPosY(float val) { PosY = val; }

private:
    float PosX;
    float PosY;
};

#endif DRAWABLEENTITY_H
