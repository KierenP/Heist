#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "WeaponStats.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>

struct  KeyState{
    bool UpPressed;
    bool DownPressed;
    bool LeftPressed;
    bool RightPressed;
    bool LMBPressed;
};

class Character : public Entity
{
public:
    Character();
    virtual ~Character();

    sf::Sprite GetSprite() { return mSprite; }
    sf::Texture GetTexture() { return mTexture; }
    float GetSpeed() { return mSpeed; }
    float GetHealth() { return mHealth; }
    float GetDirection() { return mDirection; }
    WeaponStats GetWeapon() { return mWeapon; }
    std::vector<Projectile> GetProjectiles() { return mProjectiles; }
    sf::Clock GetWeaponClock() { return mWeaponClock; }

    void SetSprite(sf::Sprite val) { mSprite = val; }
    void SetTexture(sf::Texture val);
    void SetSpeed(float val) { mSpeed = val; }
    void SetHealth(float val) { mHealth = val; }
    void SetDirection(float val) { mDirection = val; }
    void SetWeapon(WeaponStats pWeapon) { mWeapon = pWeapon; }
    void SetProjectiles(std::vector<Projectile> val) { mProjectiles = val; }
    void SetWeaponClock(sf::Clock val) { mWeaponClock = val; }

    void Render(sf::RenderWindow* pTarget);     //Draw the player sprite and the projectiles
    void GenerateProjectile();
    void RemoveProjectile(unsigned int index);
    void Update(float TimeStep, KeyState val, bool WillCollide);  //Update the projectiles positions and the players sprite

private:
    void RenderProjectiles(sf::RenderWindow* pTarget);
    void UpdateProjectiles(float TimeStep);
    void UpdateSprite();
    void Move(KeyState val, float TimeStep);    //Move the player in the pressed directions

    sf::Sprite mSprite;
    sf::Texture mTexture;
    float mSpeed;
    float mHealth;
    float mDirection;
    WeaponStats mWeapon;
    std::vector<Projectile> mProjectiles;
    sf::Clock mWeaponClock;
};

#endif // CHARACTER_H
