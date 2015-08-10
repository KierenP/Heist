#include "LevelEntityManager.h"

LevelEntityManager::LevelEntityManager()
{
    //ctor
}

LevelEntityManager::~LevelEntityManager()
{
    //dtor
}

void LevelEntityManager::Update(KeyState pKeyState)
{
    mFrameTime = mFrameClock.restart().asSeconds();

    mPlayer.SetDiretion(ToDegrees(DirectionToPoint(mPlayer.GetPosX(), mPlayer.GetPosY(), sf::Mouse::getPosition(*mpTarget).x, sf::Mouse::getPosition(*mpTarget).y)));

    mPlayer.Update(mFrameTime, pKeyState);
}

void LevelEntityManager::Render()
{
    mTileEngine.Render(mpTarget);
    mPlayer.Render(mpTarget);
}
