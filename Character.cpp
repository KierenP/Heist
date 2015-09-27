#include "Character.h"

Character::Character()
{

}

Character::~Character()
{

}

Character::Character(float posX, float posY, sf::Texture texture, CharacterTypes playertID, unsigned int TeamID, WeaponStats weapon, float speed, float health, float direction)
{
	SetPosX(posX);
	SetPosY(posY);
	SetTexture(texture);
	SetPlayerID(playertID);
	SetTeamID(TeamID);
	SetWeapon(weapon);
	SetSpeed(speed);
	SetHealth(health);
	SetDirection(direction);
}

void Character::Render(sf::RenderWindow* pTarget)
{
	mSprite.setTexture(mTexture);	//This *should* not be nessisary, but is.
    pTarget->draw(mSprite);
    RenderProjectiles(pTarget);
}

void Character::RenderProjectiles(sf::RenderWindow* pTarget)
{
	for (unsigned int iProjectile = 0; iProjectile < mProjectiles.size(); iProjectile++)
    {
		mProjectiles[iProjectile].Render(pTarget);
    }
}

void Character::RemoveProjectile(unsigned int index)
{
    if (index >= mProjectiles.size())					//Saftey check that the index in in bounds of array. No need to check for < 0, because index is unsigned (always positive)
        return;
    mProjectiles.erase(mProjectiles.begin() + index);
}

void Character::UpdateSprite()
{
    mSprite.setPosition(GetPosX(), GetPosY());
    mSprite.setRotation(mDirection + 90);
}

void Character::UpdateProjectiles(float timeStep)
{
	for (unsigned int iProjectile = 0; iProjectile < mProjectiles.size(); iProjectile++)
    {
		mProjectiles[iProjectile].Update(timeStep);
    }
}

void Character::Update(float timeStep, KeyState val, bool willCollide)
{
	if (!willCollide)   //LevelEntityManager will pass a true of false wether it is allowed to move
		Move(val, timeStep);

    UpdateSprite();

    if (val.LMBPressed && mWeaponClock.getElapsedTime().asSeconds() > mWeapon.mFireRate)
    {
        GenerateProjectile();
        mWeaponClock.restart();
    }

	UpdateProjectiles(timeStep);
}

void Character::Move(KeyState var, float TimeStep)
{
    if (var.UpPressed)
        SetPosY(GetPosY() - mSpeed * TimeStep);
    if (var.DownPressed)
		SetPosY(GetPosY() + mSpeed * TimeStep);
    if (var.LeftPressed)
		SetPosX(GetPosX() - mSpeed * TimeStep);
    if (var.RightPressed)
		SetPosX(GetPosX() + mSpeed * TimeStep);
}

void Character::SetTexture(sf::Texture val)
{
    mTexture = val;
    mSprite.setTexture(mTexture);
	mSprite.setOrigin(static_cast<float>(mTexture.getSize().x / 2), static_cast<float>(mTexture.getSize().y / 2));  //Set the origin to be the center of the texture so it rotates around the center
}


void Character::GenerateProjectile()
{
    float RandDir = mDirection + (-1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2)))) * mWeapon.mBulletSpred;         //Random number between (-1 and +1 * Spread)

    Projectile Temp(GetPosX(), GetPosY(), RandDir, mWeapon.mBulletSpeed, mWeapon.mDamage, mWeapon.mBulletTexture);

    mProjectiles.push_back(Temp);
}


