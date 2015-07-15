#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "DrawableEntity.h"
#include <SFML/Graphics.hpp>
#include <cmath>

/*
    Class to represent a player controlled character.

    >> Included getteres and setteres of all private variables.
    >> MoveDirection moves the player in its set direction (mDirection) * Speed per second (Speed) * seconds past since last frame (Timestep)
    >> Render draws the mSprite object to the object pointed to by the passed sf::RenderWindow*
*/

enum MoveDirections {
    Up,
    Down,
    Left,
    Right
};

class PlayerCharacter// : public DrawableEntity (Class is still work in progress)
{
public:
    PlayerCharacter();
    PlayerCharacter(float pPosX, float pPosY, float pSpeed, float pHealth) :  mPosX(pPosX), mPosY(pPosY), mSpeed(pSpeed), mHealth(pHealth) {}

    ~PlayerCharacter();

    //Getters
    float GetPosX() { return mPosX; }
    float GetPosY() { return mPosY; }
    float GetSpeed() { return mSpeed; }
    float GetHealth() {return mHealth; }
    //sf::Sprite GetSprite() { return mSprite; }

    //Setters
    void SetPosX(float val) { mPosX = val; }
    void SetPosY(float val) { mPosY = val; }
    void SetSpeed(float val) { mSpeed = val; }
    void SetHealth(float val);
    //void SetSprite(sf::Sprite val) { mSprite = val; }

    //Member Functions
    void Move(MoveDirections val, float TimeStep);
    //void Render(sf::RenderWindow* pTarget);

private:
    sf::Sprite mSprite;
    //sf::Texture mTexture;

    float mPosX;
    float mPosY;
    float mSpeed;
    float mHealth;
};

#endif // PLAYERCHARACTER_H
