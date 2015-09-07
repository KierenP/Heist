#include "LevelEntityManager.h"

LevelEntityManager::LevelEntityManager()
{

}

LevelEntityManager::LevelEntityManager(sf::RenderWindow* pTarget, TileEngine pTileEngine, PlayerCharacter pPlayer):
        mpTarget(pTarget),
        mTileEngine(pTileEngine),
        mPlayer(pPlayer) {}

LevelEntityManager::~LevelEntityManager()
{
    //dtor
}

void LevelEntityManager::Update(KeyState pKeyState)
{
    mFrameTime = mFrameClock.restart().asSeconds();

    sf::Vector2f NewPlayerPos = GetPlayerNewPosition(mPlayer, pKeyState);
    sf::Vector2f NewPlayerSpritePos = sf::Vector2f(NewPlayerPos.x - mPlayer.GetSprite().getOrigin().x, NewPlayerPos.y - mPlayer.GetSprite().getOrigin().y);

    mPlayer.SetDiretion(FunctionLib::ToDegrees(FunctionLib::DirectionToPoint(mPlayer.GetPosX(), mPlayer.GetPosY(), sf::Mouse::getPosition(*mpTarget).x, sf::Mouse::getPosition(*mpTarget).y)));
    mPlayer.Update(mFrameTime, pKeyState, CheckTileSolidColision(FunctionLib::GenerateBoxFromDimentions(NewPlayerSpritePos.x, NewPlayerSpritePos.y, mPlayer.GetTexture().getSize().x, mPlayer.GetTexture().getSize().y)));

    for (unsigned int i = 0; i < mPlayer.GetProjectiles().size(); i++)
    {
        sf::Vector2f NewBulletPos = GetBulletNewPosition(mPlayer.GetProjectiles()[i]);
        sf::Vector2f NewBulletSpritePos = sf::Vector2f(NewBulletPos.x - mPlayer.GetProjectiles()[i].GetSprite().getOrigin().x, NewBulletPos.y - mPlayer.GetProjectiles()[i].GetSprite().getOrigin().y);

        if (CheckTileSolidColision(FunctionLib::GenerateBoxFromDimentions(NewBulletSpritePos.x, NewBulletSpritePos.y, mPlayer.GetProjectiles()[i].GetTexture().getSize().x, mPlayer.GetProjectiles()[i].GetTexture().getSize().y)))
        {
            mPlayer.RemoveProjectile(i);
            i -= 1;                         //what was the nth element is now the (n - 1)th element because all other elements were shifted down when the one was removed
        }
    }
}

sf::Vector2f LevelEntityManager::GetPlayerNewPosition(PlayerCharacter& pPlayer, KeyState pKeyState)
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
    mPlayer.Render(mpTarget);
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
