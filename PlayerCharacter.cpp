#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
{

}

PlayerCharacter::~PlayerCharacter()
{

}

PlayerCharacter::PlayerCharacter(float pPosX, float pPosY, sf::Texture pTexture, float pSpeed, float pHealth)
{
    SetPosX(pPosX);
    SetPosY(pPosY);
    SetSpeed(pSpeed);
    SetHealth(pHealth);
    SetTexture(pTexture);
}

PlayerCharacter::PlayerCharacter(float pPosX, float pPosY, float pSpeed, float pHealth)
{
    SetPosX(pPosX);
    SetPosY(pPosY);
    SetSpeed(pSpeed);
    SetHealth(pHealth);
}

void PlayerCharacter::SetHealth(float val)
{
    mHealth = val;

    if (mHealth < 0)    //Health should not be less than zero
    {
        mHealth = 0;
    }
}

void PlayerCharacter::SetTexture(sf::Texture val)
{
    mTexture = val;
    mSprite.setTexture(mTexture);
    mSprite.setOrigin(mTexture.getSize().x / 2, mTexture.getSize().y / 2);  //Set the origin to be the center of the texture so it rotates around the center
    //mSprite.setOrigin(0, 0);
}

void PlayerCharacter::Move(KeyState var, float TimeStep)
{
    if (var.UpPressed)
        SetPosY(mPosY -= mSpeed * TimeStep);
    if (var.DownPressed)
        SetPosY(mPosY += mSpeed * TimeStep);
    if (var.LeftPressed)
        SetPosX(mPosX -= mSpeed * TimeStep);
    if (var.RightPressed)
        SetPosX(mPosX += mSpeed * TimeStep);
}

void PlayerCharacter::Render(sf::RenderWindow* pTarget)
{
    pTarget->draw(mSprite);
    RenderProjectiles(pTarget);
}

void PlayerCharacter::UpdateSprite()
{
    mSprite.setPosition(mPosX, mPosY);
    mSprite.setRotation(mDirection + 90);
}

void PlayerCharacter::UpdateProjectiles(float TimeStep)
{
    for (unsigned int i = 0; i < mProjectiles.size(); i++)
    {
        mProjectiles[i].Update(TimeStep);
    }
}

void PlayerCharacter::RenderProjectiles(sf::RenderWindow* pTarget)
{
    for (unsigned int i = 0; i < mProjectiles.size(); i++)
    {
        mProjectiles[i].Render(pTarget);
    }
}

void PlayerCharacter::Update(float TimeStep)
{
    UpdateSprite();
    UpdateProjectiles(TimeStep);
}

void PlayerCharacter::GenerateProjectile()
{
    Projectile Temp(mPosX, mPosY, mDirection, mWeapon.mBulletSpeed, mWeapon.mDamage, mWeapon.mBulletSprite);

    mProjectiles.push_back(Temp);
}
