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

    SetDamage(pDamage);
    SetSprite(pSprite);

    SetPosX(px);
    SetPosY(py);
}

void Projectile::Update(float TimeStep)
{
    mPosX += VelX * TimeStep;
    mPosY += VelY * TimeStep;

    UpdateSprite();
}

void Projectile::UpdateSprite()
{
    mSprite.setPosition(mPosX, mPosY);
}

void Projectile::CalculateVelocities(float pDirection, float pVelocity)
{
    VelX = ToDegrees(cos(ToRadians(pDirection))) * pVelocity;
    VelY = ToDegrees(sin(ToRadians(pDirection))) * pVelocity;
}
