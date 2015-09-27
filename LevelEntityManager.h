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
    LevelEntityManager(sf::RenderWindow* pTarget, TileEngine newTileEngine, std::vector<Character> players);
    ~LevelEntityManager();

    sf::RenderWindow* GetRenderTarget() { return mRenderTarget; }
    TileEngine& GetTileEngine() { return mTileEngine; }
    std::vector<Character>& GetPlayerVec() { return mPlayerVec; }
    Character GetpPlayer(unsigned int index) { return mPlayerVec[index]; }
    std::vector<sf::Vector2f> GetSpawnPoints() { return mSpawnPoints; }

    void SetTarget(sf::RenderWindow* val) { mRenderTarget = val; }
    void SetTileEngine(TileEngine val) { mTileEngine = val; }
    void SetPlayers(std::vector<Character> val) { mPlayerVec = val; }

    void Render();
    void Update(KeyState pKeyState);
    void AddPlayer(Character val) { mPlayerVec.push_back(val); }
    void SetSpawnPoint(unsigned int index, sf::Vector2f point);

private:
    bool CheckTileSolidColision(std::vector<sf::Vector2f> cornerPoints) const;
    sf::Vector2f GetPlayerNewPosition(Character& Player, KeyState moveDirection);
    sf::Vector2f GetBulletNewPosition(Projectile& projectile);
    float GenerateAiDirection(Character* pCharacter, KeyState moveDirection);
    KeyState AiMoveDecide(Character* pCharacter);

    sf::RenderWindow* mRenderTarget;
    TileEngine mTileEngine;
    std::vector<Character> mPlayerVec;
    sf::View mGameView;
    sf::Clock mFrameClock;
    float mFrameTime;
    std::vector<sf::Vector2f> mSpawnPoints;
};

#endif // LEVELENTITYMANAGER_H
