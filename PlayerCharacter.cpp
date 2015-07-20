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
}

void PlayerCharacter::Move(MoveDirections var, float TimeStep)
{
    if (var == UP)
        SetPosY(mPosY -= mSpeed * TimeStep);
    if (var == DOWN)
        SetPosY(mPosY += mSpeed * TimeStep);
    if (var == LEFT)
        SetPosX(mPosX -= mSpeed * TimeStep);
    if (var == RIGHT)
        SetPosX(mPosX += mSpeed * TimeStep);
}

void PlayerCharacter::Render(sf::RenderWindow* pTarget)
{
    pTarget->draw(mSprite);
}

void PlayerCharacter::UpdateSprite()
{
    mSprite.setPosition(mPosX, mPosY);
}

