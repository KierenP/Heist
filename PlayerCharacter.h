#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Entity.h"
#include <SFML/Graphics.hpp>


enum MoveDirections {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class PlayerCharacter : public Entity
{
public:
    PlayerCharacter();
    PlayerCharacter(float pPosX, float pPosY, float pSpeed = 0, float pHealth = 0);
    PlayerCharacter(float pPosX, float pPosY, sf::Texture pTexture, float pSpeed = 0, float pHealth = 0);
    ~PlayerCharacter();

    //Getters
    float GetSpeed() { return mSpeed; }
    float GetHealth() {return mHealth; }
    sf::Sprite GetSprite() { return mSprite; }
    sf::Texture GetTexture() { return mTexture; }

    //Setters
    void SetSpeed(float val) { mSpeed = val; }
    void SetHealth(float val);
    void SetSprite(sf::Sprite val) { mSprite = val; }
    void SetTexture(sf::Texture val);

    //Member Functions
    void Move(MoveDirections val, float TimeStep);
    void Render(sf::RenderWindow* pTarget);
    void UpdateSprite();

private:
    sf::Sprite mSprite;
    sf::Texture mTexture;

    float mSpeed;
    float mHealth;
};

#endif // PLAYERCHARACTER_H
