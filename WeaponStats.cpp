#include "WeaponStats.h"

WeaponStats GetWeaponStat(WeaponTypes WeaponID)
{
    WeaponStats WeaponIDStats;
    sf::Sprite WeaponIDSprite;
    sf::Texture WeaponIDTexture;

    switch (WeaponID)
    {
        case RifleWeapon:
            WeaponIDTexture.loadFromFile("PlaceHolderPlayer.png");
            WeaponIDStats.mBulletSpeed = 10;
            WeaponIDStats.mDamage = 10;
            WeaponIDStats.mFireRate = 0.2;
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
    }

    WeaponIDSprite.setTexture(WeaponIDTexture);
    WeaponIDSprite.setOrigin(WeaponIDTexture.getSize().x / 2, WeaponIDTexture.getSize().y / 2);
    WeaponIDStats.mBulletSprite = WeaponIDSprite;

    return WeaponIDStats;
}

