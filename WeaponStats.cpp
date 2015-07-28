#include "WeaponStats.h"

void GetWeaponStat(WeaponTypes WeaponID)
{
    WeaponStats WeaponIDStats;
    sf::Sprite WeaponIDSprite;
    sf::Texture WeaponIDTexture;

    switch (WeaponID)
    {
    case RifleWeapon:
        {
            WeaponIDTexture.loadFromFile("<Insert file name here>");
            WeaponIDStats.mBulletSpeed = 500;
            WeaponIDStats.mDamage = 10;
            WeaponIDStats.mFireRate = 0.2;
        }
    case SMGWeapon:
        {
            WeaponIDTexture.loadFromFile("<Insert file name here>");
            WeaponIDStats.mBulletSpeed = 500;
            WeaponIDStats.mDamage = 7;
            WeaponIDStats.mFireRate = 0.1;
        }
    case ShotGunWeapon:
        {
            WeaponIDTexture.loadFromFile("<Insert file name here>");
            WeaponIDStats.mBulletSpeed = 500;
            WeaponIDStats.mDamage = 20;
            WeaponIDStats.mFireRate = 2;
        }
    }

    WeaponIDSprite.setTexture(WeaponIDTexture);
    WeaponIDStats.mBulletSprite = WeaponIDSprite;
}

