#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Character.h"
#include <SFML/Graphics.hpp>
#include <vector>

class PlayerCharacter : public Character
{
public:
    //Constructor and Destructor
    PlayerCharacter();
    PlayerCharacter(float pPosX, float pPosY, float pSpeed = 0, float pHealth = 0);
    PlayerCharacter(float pPosX, float pPosY, sf::Texture pTexture, float pSpeed = 0, float pHealth = 0);
    ~PlayerCharacter();

    //Well, i desided to make a new class called Character, that both AiCharacter (To be written) and
    //PlayerCharacter could inherit from, encapsulating the common propeties
    //only issue, PlayerCharacter has *no* unique characteristics. Like, everything a player character can do
    //the ai can do also, so this class is empty atm. Yea...
};

#endif // PLAYERCHARACTER_H
