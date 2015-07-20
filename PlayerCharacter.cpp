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

    if (mHealth < 0)
    {
        mHealth = 0;
    }
}

void PlayerCharacter::SetTexture(sf::Texture val)
{
    mTexture = val;
    mSprite.setTexture(mTexture);
    mSprite.setOrigin(mTexture.getSize().x / 2, mTexture.getSize().y / 2);
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
}

void PlayerCharacter::UpdateSprite()
{
    mSprite.setPosition(mPosX, mPosY);
    mSprite.setRotation(mDirection + 90);
}

