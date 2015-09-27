#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include "Entity.h"
#include "FunctionLib.h"
#include <cmath>
#include <SFML/Graphics.hpp>

class Projectile : public Entity
{
public:
    //Construtor and Destructor
    Projectile();
    Projectile(float posX, float posY, float direction, float velocity, float damage, sf::Texture spriteTexture);
    ~Projectile();

    //getters
    float GetVelX() { return mVelX; }
    float GetVelY() { return mVelY; }
    float GetDamage() { return mDamage; }
    sf::Sprite GetSprite() { return mSprite; }
    sf::Texture GetTexture() { return mSpriteTexture; }
    float GetDirection() { return mDirection; }

    //setters
    void SetVelX(float val) { mVelX = val; }
    void SetVelY(float val) { mVelY = val; }
    void SetDamage(float val) { mDamage = val; }
    void SetSprite(sf::Sprite val) { mSprite = val; }
    void SetDirection(float val);
    void SetTexture(sf::Texture val);

    //public member functions
    void Render(sf::RenderWindow* pTarget) { pTarget->draw(mSprite); }               //draw mSprite to screen
    void Update(float timeStep);

private:
    //private member functions
    void UpdateSprite();
    void CalculateVelocities(float direction, float velocity);                    //Based on a direction and a velocity calculate the velocity x and y

    //private member variables
    float mDirection;
    float mVelX, mVelY;
    float mDamage;
    sf::Texture mSpriteTexture;
    sf::Sprite mSprite;
};

#endif // PROJECTILE_H_INCLUDED
