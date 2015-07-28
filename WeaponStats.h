#ifndef WEAPONSTATS_H_INCLUDED
#define WEAPONSTATS_H_INCLUDED

#include <SFML/Graphics.hpp>

struct WeaponStats
{
    float mDamage;
    float mBulletSpeed;
    float mFireRate;
    sf::Sprite mBulletSprite;
};

enum WeaponTypes
{
    RifleWeapon,
    SMGWeapon,
    ShotGunWeapon,
};

void GetWeaponStat(WeaponTypes WeaponID);


#endif // WEAPONSTATS_H_INCLUDED
