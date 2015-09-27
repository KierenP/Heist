#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "WeaponStats.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>

struct KeyState{
    bool UpPressed;
    bool DownPressed;
    bool LeftPressed;
    bool RightPressed;
    bool LMBPressed;
};

enum CharacterTypes{
    HUMAN_CHARACTER,
    AI_CHARACTER
};

class Character : public Entity
{
public:
    Character();
	Character(float posX, float posY, sf::Texture texture, CharacterTypes playertID, unsigned int TeamID, WeaponStats weapon, float speed = 0, float health = 0, float direction = 0);
    ~Character();

    sf::Sprite GetSprite() { return mSprite; }
    sf::Texture GetTexture() { return mTexture; }
    float GetSpeed() { return mSpeed; }
    float GetHealth() { return mHealth; }
    float GetDirection() { return mDirection; }
    WeaponStats GetWeapon() { return mWeapon; }
    std::vector<Projectile>& GetProjectiles() { return mProjectiles; }
    sf::Clock GetWeaponClock() { return mWeaponClock; }
    CharacterTypes GetPlayerID() { return mPlayerID; }
    unsigned int GetTeamID() { return mTeamID; }

    void SetSprite(sf::Sprite val) { mSprite = val; }
    void SetTexture(sf::Texture val);
    void SetSpeed(float val) { mSpeed = val; }
    void SetHealth(float val) { mHealth = val; }
    void SetDirection(float val) { mDirection = val; }
    void SetWeapon(WeaponStats val) { mWeapon = val; }
    void SetProjectiles(std::vector<Projectile> val) { mProjectiles = val; }
    void SetWeaponClock(sf::Clock val) { mWeaponClock = val; }
    void SetPlayerID(CharacterTypes val) { mPlayerID = val; }
    void SetTeamID(unsigned int val) { mTeamID = val; }

    void Render(sf::RenderWindow* pTarget);											//Draw the player sprite and its mProjectiles
    void GenerateProjectile();														//Create a new Projectile object push_back it to mProjectiles
    void RemoveProjectile(unsigned int index);										//Remove Projectile at given position in mProjectiles
    void Update(float timeStep, KeyState moveDirection, bool willCollide);			//Update the players mSprite and position, as well as the mProjectiles
	Projectile GetProjectile(unsigned int index) { return mProjectiles.at(index); }	//Return a copy of the Projectile stored in mProjectiles at given index

private:
    void RenderProjectiles(sf::RenderWindow* pTarget);								//Draw each Projectiles in mProjectiles's mSprite
    void UpdateProjectiles(float timeStep);											//Update each Projectiles in mProjectiles's position based off given time since last update
    void UpdateSprite();															//Update the mSprite
    void Move(KeyState moveDirection, float timeStep);								//Move the player in the passed directions

    sf::Sprite mSprite;															
    sf::Texture mTexture;
    float mSpeed;
    float mHealth;
    float mDirection;
    WeaponStats mWeapon;
    std::vector<Projectile> mProjectiles;
    sf::Clock mWeaponClock;
    CharacterTypes mPlayerID;
    unsigned int mTeamID;
};

#endif // CHARACTER_H
