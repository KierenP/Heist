#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
{

}

PlayerCharacter::~PlayerCharacter()
{

}

void PlayerCharacter::SetHealth(float val)
{
    mHealth = val;

    if (mHealth < 0)
    {
        mHealth = 0;
    }
}

void PlayerCharacter::Move(MoveDirections var, float TimeStep)
{
    if (var == Up)
        mPosY -= mSpeed * TimeStep;
    if (var == Down)
        mPosY += mSpeed * TimeStep;
    if (var == Left)
        mPosX -= mSpeed * TimeStep;
    if (var == Right)
        mPosX += mSpeed * TimeStep;
}

void PlayerCharacter::Render(sf::RenderWindow* pTarget)
{
    pTarget->draw(mSprite);
}

