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
/*
void PlayerCharacter::SetHealth(float val)
{
    mHealth = val;

    if (mHealth < 0)    //Health should not be less than zero
    {
        mHealth = 0;
    }
}
*/

