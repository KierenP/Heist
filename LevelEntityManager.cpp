#include "LevelEntityManager.h"

LevelEntityManager::LevelEntityManager()
{

}

LevelEntityManager::LevelEntityManager(sf::RenderWindow* pTarget, TileEngine pTileEngine, std::vector<Character*> pPlayers):
        mpTarget(pTarget),
        mTileEngine(pTileEngine),
        mPlayers(pPlayers) {}

LevelEntityManager::~LevelEntityManager()
{
    //dtor
}

void LevelEntityManager::Update(KeyState pKeyState)
{
    mFrameTime = mFrameClock.restart().asSeconds();

    for (int j = 0; j < mPlayers.size(); j++)
    {
        sf::Vector2f NewPlayerPos = GetPlayerNewPosition(*mPlayers[j], pKeyState);
        sf::Vector2f NewPlayerSpritePos = sf::Vector2f(NewPlayerPos.x - mPlayers[j]->GetSprite().getOrigin().x, NewPlayerPos.y - mPlayers[j]->GetSprite().getOrigin().y);

        mPlayers[j]->SetDirection(FunctionLib::ToDegrees(FunctionLib::DirectionToPoint(mPlayers[j]->GetPosX(), mPlayers[j]->GetPosY(), sf::Mouse::getPosition(*mpTarget).x, sf::Mouse::getPosition(*mpTarget).y)));
        mPlayers[j]->Update(mFrameTime, pKeyState, CheckTileSolidColision(FunctionLib::GenerateBoxFromDimentions(NewPlayerSpritePos.x, NewPlayerSpritePos.y, mPlayers[j]->GetTexture().getSize().x, mPlayers[j]->GetTexture().getSize().y)));

        for (unsigned int i = 0; i < mPlayers[j]->GetProjectiles().size(); i++)
        {
            sf::Vector2f NewBulletPos = GetBulletNewPosition(mPlayers[j]->GetProjectiles()[i]);
            sf::Vector2f NewBulletSpritePos = sf::Vector2f(NewBulletPos.x - mPlayers[j]->GetProjectiles()[i].GetSprite().getOrigin().x, NewBulletPos.y - mPlayers[j]->GetProjectiles()[i].GetSprite().getOrigin().y);

            if (CheckTileSolidColision(FunctionLib::GenerateBoxFromDimentions(NewBulletSpritePos.x, NewBulletSpritePos.y, mPlayers[j]->GetProjectiles()[i].GetTexture().getSize().x, mPlayers[j]->GetProjectiles()[i].GetTexture().getSize().y)))
            {
                mPlayers[j]->RemoveProjectile(i);
                i -= 1;                         //what was the nth element is now the (n - 1)th element because all other elements were shifted down when the one was removed
            }
        }
    }
}

sf::Vector2f LevelEntityManager::GetPlayerNewPosition(Character& pPlayer, KeyState pKeyState)
{
    sf::Vector2f NewPlayerPos(pPlayer.GetPosX(), pPlayer.GetPosY());

    if (pKeyState.UpPressed)
        NewPlayerPos.y -= pPlayer.GetSpeed() * mFrameTime;
    if (pKeyState.DownPressed)
        NewPlayerPos.y += pPlayer.GetSpeed() * mFrameTime;
    if (pKeyState.LeftPressed)
        NewPlayerPos.x -= pPlayer.GetSpeed() * mFrameTime;
    if (pKeyState.RightPressed)
        NewPlayerPos.x += pPlayer.GetSpeed() * mFrameTime;

    return NewPlayerPos;
}

sf::Vector2f LevelEntityManager::GetBulletNewPosition(Projectile& pProjectile)
{
    sf::Vector2f NewBulletPos(pProjectile.GetPosX(), pProjectile.GetPosY());

    NewBulletPos.x += pProjectile.GetVelX() * mFrameTime;
    NewBulletPos.y += pProjectile.GetVelY() * mFrameTime;

    return NewBulletPos;
}

void LevelEntityManager::Render()
{
    mTileEngine.Render(mpTarget);   //Order of rendering here is important!

    for (int i = 0; i < mPlayers.size(); i++)
    {
        mPlayers[i]->Render(mpTarget);
    }
}

bool LevelEntityManager::CheckTileSolidColision(std::vector<sf::Vector2f> CornerPoints) const
{
    for (unsigned int i = 0; i < CornerPoints.size(); i++)
    {
        if (mTileEngine.CheckSolid(CornerPoints[i].x, CornerPoints[i].y))
            return true;
    }

    return false;
}
