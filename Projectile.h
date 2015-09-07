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
    Projectile(float px, float py, float pDirection, float pVelocity, float pDamage, sf::Texture pSpriteTexture);    //You can give it a direction and a speed
    ~Projectile();

    //getters
    float GetVelX() { return VelX; }
    float GetVelY() { return VelY; }
    float GetDamage() { return mDamage; }
    sf::Sprite GetSprite() { return mSprite; }
    sf::Texture GetTexture() { return mSpriteTexture; }
    float GetDirection() { return mDirection; }

    //setters
    void SetVelX(float pVelX) { VelX = pVelX; }
    void SetVelY(float pVelY) { VelY = pVelY; }
    void SetDamage(float pDamage) { mDamage = pDamage; }
    void SetSprite(sf::Sprite pSprite) { mSprite = pSprite; }
    void SetDirection(float pDirection);
    void SetTexture(sf::Texture pTexture);

    //public member functions
    void Render(sf::RenderWindow* pTarget) {pTarget->draw(mSprite);}                //draw mSprite to screen
    void Update(float TimeStep);

private:
    //private member functions
    void UpdateSprite();
    void CalculateVelocities(float pDirection, float pVelocity);                    //Based on a direction and a velocity calculate the velocity x and y

    //private member variables
    float mDirection;
    float VelX, VelY;
    float mDamage;
    sf::Texture mSpriteTexture;
    sf::Sprite mSprite;
};

#endif // PROJECTILE_H_INCLUDED
