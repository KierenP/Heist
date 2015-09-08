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
        KeyState MoveDirection;                 //Will either be filled with the *actial* key state, for the player controlled character, or will be made up for the AI controlled characters
        float Direction;                        //Will either be the direction to mouse for the player character or where the AI should face

        switch (mPlayers[j]->GetPlayerID())
        {
        case PlayerCharacter:
            MoveDirection = pKeyState;          //Give to the player the actial state of the keys
            Direction = FunctionLib::ToDegrees(FunctionLib::DirectionToPoint(mPlayers[j]->GetPosX(), mPlayers[j]->GetPosY(), sf::Mouse::getPosition(*mpTarget).x, sf::Mouse::getPosition(*mpTarget).y));
            break;
        case AiCharacter:    //if not player, must be Ai
            MoveDirection = AiMoveDecide(mPlayers[j]);   //Generate the direction the AI should move
            Direction = FunctionLib::ToDegrees(GenerateAiDirection(mPlayers[j], MoveDirection));
            break;
        }

        sf::Vector2f NewPlayerPos = GetPlayerNewPosition(*mPlayers[j], MoveDirection);
        sf::Vector2f NewPlayerSpritePos = sf::Vector2f(NewPlayerPos.x - mPlayers[j]->GetSprite().getOrigin().x, NewPlayerPos.y - mPlayers[j]->GetSprite().getOrigin().y);

        mPlayers[j]->SetDirection(Direction);
        mPlayers[j]->Update(mFrameTime, MoveDirection, CheckTileSolidColision(FunctionLib::GenerateBoxFromDimentions(NewPlayerSpritePos.x, NewPlayerSpritePos.y, mPlayers[j]->GetTexture().getSize().x, mPlayers[j]->GetTexture().getSize().y)));

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

float LevelEntityManager::GenerateAiDirection(Character* pCharacter, KeyState val) //Based of a direction a Ai is going to be moving, what is the angle it should face to move in that direction
{
    float MinDistance = 999999;         //I dont have a better way of doing this
    unsigned int ClosestIndex = -1;     //I can test weither this is still -1 after below for loops, and if so, there was noone in a LOS

    for (int i = 0; i < mPlayers.size(); i++)
    {
        if (pCharacter->GetTeamId() != mPlayers[i]->GetTeamId())  //if the guy is not on the same team
        {
            if (!(mTileEngine.CheckLineSolidColision(pCharacter->GetPosX(), pCharacter->GetPosY(), mPlayers[i]->GetPosX(), mPlayers[i]->GetPosY())))
            {
                if (FunctionLib::DistanceBetween(pCharacter->GetPosX(), pCharacter->GetPosY(), mPlayers[i]->GetPosX(), mPlayers[i]->GetPosY()) < MinDistance)   //is he closer than any others?
                {
                    ClosestIndex = i;   //it is now recoreded that mPlayers[i] is the new closest
                    MinDistance = FunctionLib::DistanceBetween(pCharacter->GetPosX(), pCharacter->GetPosY(), mPlayers[ClosestIndex]->GetPosX(), mPlayers[ClosestIndex]->GetPosY());   //and his distance is recorded
                }
            }
        }
    }

    float Angle;

    if (ClosestIndex != -1) //it was set to somthing above, there is a LOS
    {
        float Xdif = mPlayers[ClosestIndex]->GetPosX() - pCharacter->GetPosX();
        float Ydif = mPlayers[ClosestIndex]->GetPosY() - pCharacter->GetPosY();

        Angle = atan2f(Ydif, Xdif);
    }
    else    //No los, go in direction of movement
    {
        float Xdif = -(val.LeftPressed) + val.RightPressed;
        float Ydif = -(val.UpPressed) + val.DownPressed;

        Angle = FunctionLib::ToRadians(135);//atan2f(Ydif, Xdif);
    }
    return Angle;
}

KeyState LevelEntityManager::AiMoveDecide(Character* pCharacter)
{
    /*

        This is the *big* function.

        Given a Ai controlled player, pCharacter, and a team it is on, pCharacter->PlayerID, deside what direction the player should move.

        Do somthing along the lines of:

            - Find the closest player who is not of the same team
            - Find the direction to move to that player (A* algorithm)
            - Return this direction

        The direction must be returned in this form:

        /////////////////////////////////////////////////////////////////////////////////////////

        KeyState MoveDirection;

        MoveDirecton.LeftPressed = true;    <- If the Ai should move left
        MoveDirecton.RightPressed = true;   <- If the Ai should move Right
        MoveDirecton.UpPressed = true;      <- If the Ai should move Up
        MoveDirecton.DownPressed = true;    <- If the Ai should move Down

        return MoveDirection;

        /////////////////////////////////////////////////////////////////////////////////////////

    */

    //Test code below, should cause Ai players to just move to the left

    KeyState MoveDirection;

    MoveDirection.LMBPressed = false;

    MoveDirection.LeftPressed = false;
    MoveDirection.DownPressed = false;
    MoveDirection.RightPressed = false;
    MoveDirection.UpPressed = false;

    return MoveDirection;
}
