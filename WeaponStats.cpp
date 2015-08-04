#include "WeaponStats.h"

WeaponStats GetWeaponStat(WeaponTypes WeaponID)
{
    WeaponStats WeaponIDStats;
    sf::Texture WeaponIDTexture;

    switch (WeaponID)
    {
        case RifleWeapon:
            WeaponIDTexture.loadFromFile("Bullet.png");
            WeaponIDStats.mBulletSpeed = 25;
            WeaponIDStats.mDamage = 10;
            WeaponIDStats.mFireRate = 0.1;
            WeaponIDStats.mBulletSpred = 5;
            break;
        case SMGWeapon:
            WeaponIDTexture.loadFromFile("<Insert file name here>");
            WeaponIDStats.mBulletSpeed = 20;
            WeaponIDStats.mDamage = 7;
            WeaponIDStats.mFireRate = 0.05;
            break;
        case ShotGunWeapon:
            WeaponIDTexture.loadFromFile("<Insert file name here>");
            WeaponIDStats.mBulletSpeed = 20;
            WeaponIDStats.mDamage = 20;
            WeaponIDStats.mFireRate = 2;
            break;
        default:
            break;
    }

    WeaponIDStats.mBulletTexture = WeaponIDTexture;

    return WeaponIDStats;
}

