#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

enum MoveDirections {
    Up,
    Down,
    Left,
    Right
};

class PlayerCharacter : public Entity
{
public:
    PlayerCharacter();
    PlayerCharacter(float pPosX, float pPosY, float pSpeed, float pHealth) :  Entity(pPosX, pPosY), mSpeed(pSpeed), mHealth(pHealth) {}
    ~PlayerCharacter();

    //Getters
    float GetSpeed() { return mSpeed; }
    float GetHealth() {return mHealth; }
    sf::Sprite GetSprite() { return mSprite; }

    //Setters
    void SetSpeed(float val) { mSpeed = val; }
    void SetHealth(float val);
    void SetSprite(sf::Sprite val) { mSprite = val; }

    //Member Functions
    void Move(MoveDirections val, float TimeStep);
    void Render(sf::RenderWindow* pTarget);

private:
    sf::Sprite mSprite;
    sf::Texture mTexture;

    float mSpeed;
    float mHealth;
};

#endif // PLAYERCHARACTER_H
