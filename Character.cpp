#include "Character.h"

Character::Character()
{

}

Character::~Character()
{

}

void Character::Render(sf::RenderWindow* pTarget)
{
    pTarget->draw(mSprite);
    RenderProjectiles(pTarget);
}

void Character::RenderProjectiles(sf::RenderWindow* pTarget)
{
    for (unsigned int i = 0; i < mProjectiles.size(); i++)
    {
        mProjectiles[i].Render(pTarget);
    }
}


void Character::RemoveProjectile(unsigned int index)
{
    if (index >= mProjectiles.size())
        return;
    mProjectiles.erase(mProjectiles.begin() + index);
}

void Character::UpdateSprite()
{
    mSprite.setPosition(mPosX, mPosY);
    mSprite.setRotation(mDirection + 90);
}

void Character::UpdateProjectiles(float TimeStep)
{
    for (unsigned int i = 0; i < mProjectiles.size(); i++)
    {
        mProjectiles[i].Update(TimeStep);
    }
}

void Character::Update(float TimeStep, KeyState val, bool WillCollide)
{
    if (!WillCollide)   //LevelEntityManager will pass a true of false wether it is allowed to move
        Move(val, TimeStep);

    UpdateSprite();

    if (val.LMBPressed && mWeaponClock.getElapsedTime().asSeconds() > mWeapon.mFireRate)
    {
        GenerateProjectile();
        mWeaponClock.restart();
    }

    UpdateProjectiles(TimeStep);
}

void Character::Move(KeyState var, float TimeStep)
{
    if (var.UpPressed)
        SetPosY(GetPosY() - GetSpeed() * TimeStep);
    if (var.DownPressed)
        SetPosY(GetPosY() + GetSpeed() * TimeStep);
    if (var.LeftPressed)
        SetPosX(GetPosX() - GetSpeed() * TimeStep);
    if (var.RightPressed)
        SetPosX(GetPosX() + GetSpeed() * TimeStep);
}

void Character::SetTexture(sf::Texture val)
{
    mTexture = val;
    mSprite.setTexture(mTexture);
    mSprite.setOrigin(mTexture.getSize().x / 2, mTexture.getSize().y / 2);  //Set the origin to be the center of the texture so it rotates around the center
    //mSprite.setOrigin(0, 0);
}


void Character::GenerateProjectile()
{
    float RandDir = mDirection + (-1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2)))) * mWeapon.mBulletSpred;         //Random number between 0 and 1 * Spread

    Projectile Temp(mPosX, mPosY, RandDir, mWeapon.mBulletSpeed, mWeapon.mDamage, mWeapon.mBulletTexture);

    mProjectiles.push_back(Temp);
}


