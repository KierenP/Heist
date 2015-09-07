#include "Projectile.h"

Projectile::Projectile()
{
    sf::Texture MyText;

    CalculateVelocities(0, 0);
    SetDamage(0);
    SetTexture(MyText);
    SetDirection(0);
    SetPosX(0);
    SetPosY(0);
}

Projectile::~Projectile()
{

}

Projectile::Projectile(float px, float py, float pDirection, float pVelocity, float pDamage, sf::Texture mSpriteTexture)
{
    CalculateVelocities(pDirection, pVelocity);

    SetDamage(pDamage);
    SetTexture(mSpriteTexture);
    SetDirection(pDirection);
    SetPosX(px);
    SetPosY(py);
}

void Projectile::Update(float TimeStep)
{
    mPosX += VelX * TimeStep;
    mPosY += VelY * TimeStep;

    UpdateSprite();
}

void Projectile::SetDirection(float pDirection)
{
    mDirection = pDirection;
    mSprite.setRotation(mDirection + 90);
}

void Projectile::SetTexture(sf::Texture pTexture)
{
    mSpriteTexture = pTexture;
    mSprite.setTexture(mSpriteTexture);
    mSprite.setOrigin(mSpriteTexture.getSize().x / 2, mSpriteTexture.getSize().y / 2);
}

void Projectile::UpdateSprite()
{
    mSprite.setTexture(mSpriteTexture);
    mSprite.setPosition(mPosX, mPosY);
}

void Projectile::CalculateVelocities(float pDirection, float pVelocity)
{
    VelX = FunctionLib::ToDegrees(cos(FunctionLib::ToRadians(pDirection))) * pVelocity;
    VelY = FunctionLib::ToDegrees(sin(FunctionLib::ToRadians(pDirection))) * pVelocity;
}
