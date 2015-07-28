#include "Projectile.h"

Projectile::Projectile()
{

}

Projectile::~Projectile()
{

}

Projectile::Projectile(float px, float py, float pDirection, float pVelocity, float pDamage, sf::Sprite pSprite)
{
    CalculateVelocities(pDirection, pVelocity);

    mDamage = pDamage;
    mSprite = pSprite;

    mPosX = px;
    mPosY = py;
}

void Projectile::Update(float TimeStep)
{
    mPosX += VelX * TimeStep;
    mPosY += VelY * TimeStep;
}

void Projectile::UpdateSprite()
{
    mSprite.setPosition(mPosX, mPosY);
}

void Projectile::CalculateVelocities(float pDirection, float pVelocity)
{
    VelX = cos(pDirection) * pVelocity;
    VelY = -sin(pDirection) * pVelocity;
}
