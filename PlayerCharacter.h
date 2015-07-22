#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Entity.h"
#include <SFML/Graphics.hpp>


struct  KeyState{
    bool UpPressed;
    bool DownPressed;
    bool LeftPressed;
    bool RightPressed;
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
    float GetDirection() { return mDirection; }

    //Setters
    void SetSpeed(float val) { mSpeed = val; }
    void SetHealth(float val);
    void SetSprite(sf::Sprite val) { mSprite = val; }
    void SetTexture(sf::Texture val);
    void SetDiretion(float val) { mDirection = val; }

    //Member Functions
    void Move(KeyState val, float TimeStep);
    void Render(sf::RenderWindow* pTarget);
    void UpdateSprite();

private:
    sf::Sprite mSprite;
    sf::Texture mTexture;

    float mSpeed;
    float mHealth;
    float mDirection;
};

#endif // PLAYERCHARACTER_H
