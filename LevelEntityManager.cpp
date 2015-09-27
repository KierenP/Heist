#include "LevelEntityManager.h"
#include <iostream>


LevelEntityManager::LevelEntityManager()
{
    //GameView.setCenter(1000, 1000);
    //GameView.setSize(1920, 1080);
    //GameView.setViewport(sf::FloatRect(0, 0, 1920, 1080));
    //mpTarget->setView(GameView);
}

LevelEntityManager::LevelEntityManager(sf::RenderWindow* pTarget, TileEngine pTileEngine, std::vector<Character> pPlayers):
        mRenderTarget(pTarget),
        mTileEngine(pTileEngine),
        mPlayerVec(pPlayers) {}

LevelEntityManager::~LevelEntityManager()
{
    //dtor
}

void LevelEntityManager::Update(KeyState pKeyState)
{
    mFrameTime = mFrameClock.restart().asSeconds();

    /*for (int i = 0; i < mPlayerVec.size(); i++)
    {
        if (mPlayerVec.at(i)->GetPlayerID() == PlayerCharacter)
        {
            GameView.setCenter(mPlayerVec.at(i)->GetPosX(), mPlayerVec.at(i)->GetPosY());
            GameView.setSize(1920, 1080);
            GameView.setViewport(sf::FloatRect(0, 0, 1, 1));
            mpTarget->setView(GameView);
        }
    }*/

    mSpawnPoints[0].x = rand() % 500 + mTileEngine.GetPosX();
    mSpawnPoints[0].y = rand() % 500 + mTileEngine.GetPosY();
    mSpawnPoints[1].x = rand() % 500 + mTileEngine.GetPosX();
    mSpawnPoints[1].y = rand() % 500 + mTileEngine.GetPosY();

    for (unsigned int j = 0; j < mPlayerVec.size(); j++)
    {
        KeyState MoveDirection;                 //Will either be filled with the *actial* key state, for the player controlled character, or will be made up for the AI controlled characters
        float Direction;                        //Will either be the direction to mouse for the player character or where the AI should face

        switch (mPlayerVec.at(j).GetPlayerID())
        {
        case HUMAN_CHARACTER:
            MoveDirection = pKeyState;                  //Give to the player the actial state of the keys
			Direction = FunctionLib::ToDegrees(FunctionLib::DirectionToPoint(mPlayerVec.at(j).GetPosX(), mPlayerVec.at(j).GetPosY(), static_cast<float>(sf::Mouse::getPosition(*mRenderTarget).x), static_cast<float>(sf::Mouse::getPosition(*mRenderTarget).y)));
            break;
        case AI_CHARACTER:                              //if not player, must be Ai
            MoveDirection = AiMoveDecide(&mPlayerVec.at(j));   //Generate the direction the AI should move
            Direction = FunctionLib::ToDegrees(GenerateAiDirection(&mPlayerVec.at(j), MoveDirection));
            break;
        }

        sf::Vector2f NewPlayerPos = GetPlayerNewPosition(mPlayerVec.at(j), MoveDirection);
        sf::Vector2f NewPlayerSpritePos = sf::Vector2f(NewPlayerPos.x - mPlayerVec.at(j).GetSprite().getOrigin().x, NewPlayerPos.y - mPlayerVec.at(j).GetSprite().getOrigin().y);

        mPlayerVec.at(j).SetDirection(Direction);

		if (mPlayerVec.at(j).GetPlayerID() == HUMAN_CHARACTER)
			mPlayerVec.at(j).Update(mFrameTime, MoveDirection, CheckTileSolidColision(FunctionLib::GenerateBoxFromDimentions(NewPlayerSpritePos.x, NewPlayerSpritePos.y, static_cast<float>(mPlayerVec.at(j).GetTexture().getSize().x), static_cast<float>(mPlayerVec.at(j).GetTexture().getSize().y))));
		else
			mPlayerVec.at(j).Update(mFrameTime, MoveDirection, false);

        if (mPlayerVec.at(j).GetHealth() < 0)
        {
            mPlayerVec.at(j).SetHealth(100);
            mPlayerVec.at(j).SetPosX(mSpawnPoints[mPlayerVec.at(j).GetTeamID()].x);
            mPlayerVec.at(j).SetPosY(mSpawnPoints[mPlayerVec.at(j).GetTeamID()].y);
        }

        for (unsigned int i = 0; i < mPlayerVec.at(j).GetProjectiles().size(); i++)
        {
            sf::Vector2f NewBulletPos = GetBulletNewPosition(mPlayerVec.at(j).GetProjectile(i));
            sf::Vector2f NewBulletSpritePos = sf::Vector2f(NewBulletPos.x - mPlayerVec.at(j).GetProjectile(i).GetSprite().getOrigin().x, NewBulletPos.y - mPlayerVec.at(j).GetProjectile(i).GetSprite().getOrigin().y);

			if (CheckTileSolidColision(FunctionLib::GenerateBoxFromDimentions(NewBulletSpritePos.x, NewBulletSpritePos.y, static_cast<float>(mPlayerVec.at(j).GetProjectile(i).GetTexture().getSize().x), static_cast<float>(mPlayerVec.at(j).GetProjectile(i).GetTexture().getSize().y))))
            {
                mPlayerVec.at(j).RemoveProjectile(i);
                i -= 1;                         //what was the nth element is now the (n - 1)th element because all other elements were shifted down when the one was removed
            }

            for (unsigned int k = 0; k < mPlayerVec.size(); k++)
            {
                if (k != j) //Not comparing a person to his own bullets
                {
					if (NewBulletPos.x > (mPlayerVec[k].GetPosX() - mPlayerVec[k].GetSprite().getTexture()->getSize().x / 2) && NewBulletPos.x < (mPlayerVec[k].GetPosX() + mPlayerVec.at(k).GetTexture().getSize().x / 2))    //Lines up x-wise
                    {
						if (NewBulletPos.y >(mPlayerVec[k].GetPosY() - mPlayerVec[k].GetSprite().getTexture()->getSize().y / 2) && NewBulletPos.y < (mPlayerVec[k].GetPosY() + mPlayerVec.at(k).GetTexture().getSize().x / 2))   //lines up y-wise
                        {   //Colision :D
                            if (mPlayerVec[k].GetTeamID() != mPlayerVec.at(j).GetTeamID())
                            {
                                mPlayerVec[k].SetHealth(mPlayerVec[k].GetHealth() - mPlayerVec.at(j).GetProjectile(i).GetDamage());
                            }

                            mPlayerVec.at(j).RemoveProjectile(i);
                        }
                    }
                }
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
    mTileEngine.Render(mRenderTarget);   //Order of rendering here is important!

    for (unsigned int i = 0; i < mPlayerVec.size(); i++)
    {
        mPlayerVec.at(i).Render(mRenderTarget);
    }
}

bool LevelEntityManager::CheckTileSolidColision(std::vector<sf::Vector2f> CornerPoints) const
{
    for (unsigned int i = 0; i < CornerPoints.size(); i++)
    {
        if (mTileEngine.CheckSolid(CornerPoints.at(i).x, CornerPoints.at(i).y))
            return true;
    }

    return false;
}

float LevelEntityManager::GenerateAiDirection(Character* pCharacter, KeyState val) //Based of a direction a Ai is going to be moving, what is the angle it should face to move in that direction
{
    float MinDistance = 999999;         //I dont have a better way of doing this
    int ClosestIndex = -1;              //I can test weither this is still -1 after below for loops, and if so, there was noone in a LOS

    for (unsigned int i = 0; i < mPlayerVec.size(); i++)
    {
        if (pCharacter->GetTeamID() != mPlayerVec.at(i).GetTeamID())  //if the guy is not on the same team
        {
            if (!(mTileEngine.CheckLineSolidColision(pCharacter->GetPosX(), pCharacter->GetPosY(), mPlayerVec.at(i).GetPosX(), mPlayerVec.at(i).GetPosY())))
            {
                if (FunctionLib::DistanceBetween(pCharacter->GetPosX(), pCharacter->GetPosY(), mPlayerVec.at(i).GetPosX(), mPlayerVec.at(i).GetPosY()) < MinDistance)   //is he closer than any others?
                {
                    ClosestIndex = i;   //it is now recoreded that mPlayerVec.at(i) is the new closest
                    MinDistance = FunctionLib::DistanceBetween(pCharacter->GetPosX(), pCharacter->GetPosY(), mPlayerVec[ClosestIndex].GetPosX(), mPlayerVec[ClosestIndex].GetPosY());   //and his distance is recorded
                }
            }
        }
    }

    float Angle;

    if (ClosestIndex != -1) //it was set to somthing above, there is a LOS
    {
        float Xdif = mPlayerVec[ClosestIndex].GetPosX() - pCharacter->GetPosX();
        float Ydif = mPlayerVec[ClosestIndex].GetPosY() - pCharacter->GetPosY();

        Angle = atan2f(Ydif, Xdif);
    }
    else    //No los, go in direction of movement
    {
		int Xdif = val.RightPressed - val.LeftPressed;
		int Ydif = val.DownPressed - val.UpPressed;

		Angle = FunctionLib::ToDegrees(atan2f(static_cast<float>(Ydif), static_cast<float>(Xdif)));
    }

	return Angle;

	/*float MinDistance = 999999;         
	int ClosestIndex = -1;

	for (unsigned int i = 0; i < mPlayerVec.size(); i++)
	{
		if (pCharacter->GetTeamID() != mPlayerVec.at(i).GetTeamID())  //if the guy is not on the same team
		{	
			ClosestIndex = i;   //it is now recoreded that mPlayerVec.at(i) is the new closest
			MinDistance = FunctionLib::DistanceBetween(pCharacter->GetPosX(), pCharacter->GetPosY(), mPlayerVec[ClosestIndex].GetPosX(), mPlayerVec[ClosestIndex].GetPosY());   //and his distance is recorded
		}
	}

	float Angle = 0;

	if (ClosestIndex != -1)
	{
		float Xdif = mPlayerVec[ClosestIndex].GetPosX() - pCharacter->GetPosX();
		float Ydif = mPlayerVec[ClosestIndex].GetPosY() - pCharacter->GetPosY();

		Angle = atan2f(Ydif, Xdif);
	}

    return Angle;*/
}

KeyState LevelEntityManager::AiMoveDecide(Character* pCharacter)
{
    KeyState MoveDirection;

    std::vector<std::vector<Tile> > Tiles = mTileEngine.GetTileVec();
    std::vector<Tile> OpenList;

    float TargetX = mPlayerVec[0].GetPosX();
    float TargetY = mPlayerVec[0].GetPosY();

	unsigned int TargetTileX = int((TargetX - mTileEngine.GetPosX()) / mTileEngine.GetTileWidth());
	unsigned int TargetTileY = int((TargetY - mTileEngine.GetPosY()) / mTileEngine.GetTileHeight());

    float StartX = pCharacter->GetPosX();
    float StartY = pCharacter->GetPosY();

	unsigned int StartTileX = int((StartX - mTileEngine.GetPosX()) / mTileEngine.GetTileWidth());
	unsigned int StartTileY = int((StartY - mTileEngine.GetPosY()) / mTileEngine.GetTileHeight());

    for (unsigned int i = 0; i < Tiles.size(); i++)
    {
        for (unsigned int j = 0; j < Tiles.at(i).size(); j++)
        {
            //Just makin sure its all, 'setup', This step may not be nessisary but saftey 1st!

			Tiles.at(i).at(j).h = (abs(static_cast<int>(TargetTileX) - static_cast<int>(j)) + abs(static_cast<int>(TargetTileY) - static_cast<int>(i))) * 10.f;  //G value is the distance you must move X from target to tile, and Y, * 1
            Tiles.at(i).at(j).g = 0;  //This will be changed later
            Tiles.at(i).at(j).f = Tiles.at(i).at(j).g + Tiles.at(i).at(j).h;  //same here
            Tiles.at(i).at(j).x = j;
            Tiles.at(i).at(j).y = i;
            Tiles.at(i).at(j).Closed = false;
        }
    }

    OpenList.push_back(Tiles[StartTileY][StartTileX]);  //Add starting tile to open

    bool HasFoundTarget = false;

    for (unsigned int index = 0; index < mTileEngine.GetSizeX() * mTileEngine.GetSizeY(); index++)
    {
        std::vector<Tile> Neibours;

        unsigned LowestF = 0;   //LowestF is the position in the array OpenList of the tile with the lowest F value

        for (unsigned int j = 0; j < OpenList.size(); j++)
        {
            if (OpenList.at(j).f <= OpenList[LowestF].f)
            {
                LowestF = j;
            }
        }

		int CurrentTileX = OpenList[LowestF].x;
		int CurrentTileY = OpenList[LowestF].y;

        //Add its 4 neibours to the Testing List

        if (CurrentTileX + 1 < Tiles[0].size())
            Neibours.push_back(Tiles[CurrentTileY][CurrentTileX + 1]);

        if (CurrentTileX - 1 >= 0)
            Neibours.push_back(Tiles[CurrentTileY][CurrentTileX - 1]);

        if (CurrentTileY + 1 < Tiles.size())
            Neibours.push_back(Tiles[CurrentTileY + 1][CurrentTileX]);

        if (CurrentTileY - 1 >= 0)
            Neibours.push_back(Tiles[CurrentTileY - 1][CurrentTileX]);


        for (unsigned int i = 0; i < Neibours.size(); i++)
        {
			if (!(Neibours.at(i).Closed || Neibours.at(i).mSolidState))
            {
                bool IsInOpen = false;

                for (unsigned int j = 0; j < OpenList.size(); j++)
                {
                    if (OpenList.at(j).x == Neibours.at(i).x && OpenList.at(j).y == Neibours.at(i).y)
                    {
                        IsInOpen = true;

                        if (OpenList[LowestF].g + 10 < Neibours.at(i).g)  //if true, better path found
                        {
                            Neibours.at(i).g = OpenList[LowestF].g + 10;
                            Neibours.at(i).Parent = &OpenList[LowestF];
                        }
                    }
                }

                if (!IsInOpen)
                {
                    Neibours.at(i).g = OpenList[LowestF].g + 10;
                    Neibours.at(i).Parent = &Tiles[OpenList[LowestF].y][OpenList[LowestF].x];
                    OpenList.push_back(Neibours.at(i));
                }
            }

            //Neibour eiher added to open list now or not
        }

        //Now update F values

        for (unsigned int i = 0; i < OpenList.size(); i++)
        {
            OpenList.at(i).f = OpenList.at(i).g + OpenList.at(i).h;
            Tiles[OpenList.at(i).y][OpenList.at(i).x].Parent = OpenList.at(i).Parent;
        }

        //We are all set for next iteration

        Tiles[CurrentTileY][CurrentTileX].Closed = true;
        OpenList.erase(OpenList.begin() + LowestF);

        if (CurrentTileX == TargetTileX && CurrentTileY == TargetTileY)
        {
            HasFoundTarget = true;
			break;
        }


        if (OpenList.size() == 0)
            break;
    }

    MoveDirection.LeftPressed = false;
    MoveDirection.RightPressed = false;
    MoveDirection.UpPressed = false;
    MoveDirection.DownPressed = false;
    MoveDirection.LMBPressed = false;

    if (HasFoundTarget)
    {
        int BaseTileX = TargetTileX;
		int BaseTileY = TargetTileY;
		int ParentTileX = BaseTileX;
		int ParentTileY = BaseTileY;

        for (int i = 0; i < 1000; i++)
        {
            if (ParentTileX == StartTileX && ParentTileY == StartTileY)    //Parent is the starting one!
            {
                if (ParentTileX - BaseTileX > 0)
                    MoveDirection.LeftPressed = true;

                if (ParentTileX - BaseTileX < 0)
                    MoveDirection.RightPressed = true;

                if (ParentTileX - BaseTileX == 0)
                {
                    MoveDirection.RightPressed = false;
                    MoveDirection.LeftPressed = false;
                }

                if (ParentTileY - BaseTileY < 0)
                    MoveDirection.DownPressed = true;

                if (ParentTileY - BaseTileY > 0)
                    MoveDirection.UpPressed = true;

                if (ParentTileY - BaseTileY == 0)
                {
                    MoveDirection.UpPressed = false;
                    MoveDirection.DownPressed = false;
                }

                MoveDirection.LMBPressed = false;
                break;
            }
            else
            {
                BaseTileX = ParentTileX;
                BaseTileY = ParentTileY;
            }

			ParentTileX = Tiles[BaseTileY][BaseTileX].Parent->x;
			ParentTileY = Tiles[BaseTileY][BaseTileX].Parent->y;
        }
    }

	bool AllignVertical = false;
	bool AllignHorisontal = false;

	if (MoveDirection.LeftPressed || MoveDirection.RightPressed)
	{
		AllignVertical = true;
	}

	if (MoveDirection.UpPressed || MoveDirection.DownPressed)
	{
		AllignHorisontal = true;
	}

	if (AllignVertical)
	{
		TargetY = (StartTileY + 0.5) * mTileEngine.GetTileHeight();

		if (StartY < TargetY - 1)
			MoveDirection.DownPressed = true;
		if (StartY > TargetY + 1)
			MoveDirection.UpPressed = true;
	}

	if (AllignHorisontal)
	{
		TargetX = (StartTileX + 0.5) * mTileEngine.GetTileWidth();

		if (StartX < TargetX - 1)
			MoveDirection.RightPressed = true;
		if (StartX > TargetX + 1)
			MoveDirection.LeftPressed = true;
	}

    return MoveDirection;
}

void LevelEntityManager::SetSpawnPoint(unsigned int index, sf::Vector2f point)
{
    if (index < mSpawnPoints.size())
        mSpawnPoints[index] = point;
    else
        mSpawnPoints.push_back(point);
}
