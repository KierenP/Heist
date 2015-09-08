#ifndef LEVELENTITYMANAGER_H
#define LEVELENTITYMANAGER_H

#include "Character.h"
#include "TileEngine.h"
#include <SFML/Graphics.hpp>

#include <vector>

class LevelEntityManager
{
public:
    LevelEntityManager();
    LevelEntityManager(sf::RenderWindow* pTarget, TileEngine pTileEngine, std::vector<Character*> pPlayers);
    ~LevelEntityManager();

    sf::RenderWindow* GetTarget() { return mpTarget; }
    TileEngine GetTileEngine() { return mTileEngine; }
    std::vector<Character*> GetPlayers() { return mPlayers; }
    Character* GetPlayer(unsigned int index) { return mPlayers[index]; }

    void SetTarget(sf::RenderWindow* val) { mpTarget = val; }
    void SetTileEngine(TileEngine val) { mTileEngine = val; }
    void SetPlayers(std::vector<Character*> val) { mPlayers = val; }

    void Render();
    void Update(KeyState pKeyState);
    void AddPlayer(Character* val) { mPlayers.push_back(val); }

private:
    bool CheckTileSolidColision(std::vector<sf::Vector2f> CornerPoints) const;
    sf::Vector2f GetPlayerNewPosition(Character& pPlayer, KeyState pKeyState);
    sf::Vector2f GetBulletNewPosition(Projectile& pProjectile);
    float GenerateAiDirection(Character* pCharacter, KeyState val);
    KeyState AiMoveDecide(Character* pCharacter);

    sf::RenderWindow* mpTarget;
    TileEngine mTileEngine;
    std::vector<Character*> mPlayers;

    sf::Clock mFrameClock;
    float mFrameTime;
};

#endif // LEVELENTITYMANAGER_H
