#include "WeaponStats.h"

WeaponStats GetWeaponStat(WeaponTypes WeaponID)
{
    WeaponStats WeaponIDStats;
    sf::Sprite WeaponIDSprite;
    sf::Texture WeaponIDTexture;

    switch (WeaponID)
    {
    case RifleWeapon:
        {
            WeaponIDTexture.loadFromFile("PlaceHolderPlayer.png");
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
    WeaponIDSprite.setOrigin(WeaponIDTexture.getSize().x / 2, WeaponIDTexture.getSize().y / 2);
    WeaponIDStats.mBulletSprite = WeaponIDSprite;

    return WeaponIDStats;
}

