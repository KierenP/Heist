#include "WeaponStats.h"

WeaponStats GetWeaponStat(WeaponTypes weaponID)
{
    WeaponStats WeaponIDStats;
    sf::Texture WeaponIDTexture;

	switch (weaponID)
    {
        case RifleWeapon:
            WeaponIDTexture.loadFromFile("Bullet2.png");
            WeaponIDStats.mBulletSpeed = 25;
            WeaponIDStats.mDamage = 10;
            WeaponIDStats.mFireRate = 0.1;
            WeaponIDStats.mBulletSpred = 2;
            break;
        case SMGWeapon:
            WeaponIDTexture.loadFromFile("Bullet2.png");
            WeaponIDStats.mBulletSpeed = 30;
            WeaponIDStats.mDamage = 20;
            WeaponIDStats.mFireRate = 0.05;
            WeaponIDStats.mBulletSpred = 3;
            break;
        case ShotGunWeapon:
            WeaponIDTexture.loadFromFile("Bullet2.png");
            WeaponIDStats.mBulletSpeed = 20;
            WeaponIDStats.mDamage = 20;
            WeaponIDStats.mFireRate = 2;
            WeaponIDStats.mBulletSpred = 5;
            break;
        default:
            break;
    }

    WeaponIDStats.mBulletTexture = WeaponIDTexture;

    return WeaponIDStats;
}

