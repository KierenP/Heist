#include "LevelEntityManager.h"
#include <iostream>


LevelEntityManager::LevelEntityManager()
{

}

LevelEntityManager::LevelEntityManager(sf::RenderWindow* pTarget, TileEngine pTileEngine, std::vector<Character> pPlayers, std::vector<sf::Vector2f> spawnpoints) :
        mRenderTarget(pTarget),
        mTileEngine(pTileEngine),
        mPlayerVec(pPlayers),
		mSpawnPoints(spawnpoints) {}

LevelEntityManager::~LevelEntityManager()
{

}

void LevelEntityManager::Update(KeyState pKeyState)
{
    mFrameTime = mFrameClock.restart().asSeconds();

    for (unsigned int j = 0; j < mPlayerVec.size(); j++)
    {
        KeyState MoveDirection;                 //Will either be filled with the *actial* key state, for the player controlled character, or will be made up for the AI controlled characters
        float Direction;                        //Will either be the direction to mouse for the player character or where the AI should face

        switch (mPlayerVec.at(j).GetPlayerID())
        {
        case HUMAN_CHARACTER:
            MoveDirection = pKeyState;							//Give to the player the actial state of the keys
			Direction = FunctionLib::ToDegrees(FunctionLib::DirectionToPoint(mPlayerVec.at(j).GetPosX(), mPlayerVec.at(j).GetPosY(), static_cast<float>(sf::Mouse::getPosition(*mRenderTarget).x), static_cast<float>(sf::Mouse::getPosition(*mRenderTarget).y)));
            break;
        case AI_CHARACTER:										//if Ai
            MoveDirection = AiMoveDecide(&mPlayerVec.at(j));	//Generate the direction the AI should move
            Direction = FunctionLib::ToDegrees(GenerateAiDirection(&mPlayerVec.at(j), MoveDirection));
            break;
        }

        sf::Vector2f NewPlayerPos = GetPlayerNewPosition(mPlayerVec.at(j), MoveDirection);
        sf::Vector2f NewPlayerSpritePos = sf::Vector2f(NewPlayerPos.x - mPlayerVec.at(j).GetSprite().getOrigin().x, NewPlayerPos.y - mPlayerVec.at(j).GetSprite().getOrigin().y);

        mPlayerVec.at(j).SetDirection(Direction);

		if (mPlayerVec.at(j).GetPlayerID() == HUMAN_CHARACTER)
			mPlayerVec.at(j).Update(mFrameTime, MoveDirection, CheckTileSolidColision(FunctionLib::GenerateBoxFromDimentions(NewPlayerSpritePos.x, NewPlayerSpritePos.y, static_cast<float>(mPlayerVec.at(j).GetTexture().getSize().x), static_cast<float>(mPlayerVec.at(j).GetTexture().getSize().y))));
		else
			mPlayerVec.at(j).Update(mFrameTime, MoveDirection, false);	//AI characters as of now do not collide with solid tiles. 

        if (mPlayerVec.at(j).GetHealth() < 0)
        {
            mPlayerVec.at(j).SetHealth(100);
            mPlayerVec.at(j).SetPosX(mSpawnPoints[mPlayerVec.at(j).GetTeamID()].x);
            mPlayerVec.at(j).SetPosY(mSpawnPoints[mPlayerVec.at(j).GetTeamID()].y);
        }

		CheckBulletColisions(mPlayerVec[j]);
    }
}

void LevelEntityManager::CheckBulletColisions(Character& player)
{
	for (int i = 0; i < player.GetProjectiles().size(); i++)
	{
		sf::Vector2f NewBulletPos = GetBulletNewPosition(player.GetProjectile(i));
		sf::Vector2f NewBulletSpritePos = sf::Vector2f(NewBulletPos.x - player.GetProjectile(i).GetSprite().getOrigin().x, NewBulletPos.y - player.GetProjectile(i).GetSprite().getOrigin().y);

		//Bullet to tile colisions
		if (CheckTileSolidColision(FunctionLib::GenerateBoxFromDimentions(NewBulletSpritePos.x, NewBulletSpritePos.y, static_cast<float>(player.GetProjectile(i).GetTexture().getSize().x), static_cast<float>(player.GetProjectile(i).GetTexture().getSize().y))))
		{
			player.RemoveProjectile(i);
			i -= 1;									 //what was the nth element is now the (n - 1)th element because all other elements were shifted down when the one was removed
		}

		//bullet to player colisions
		for (unsigned int k = 0; k < mPlayerVec.size(); k++)
		{
			if (mPlayerVec[k].GetTeamID() != player.GetTeamID())	
			{
				if (NewBulletPos.x > (mPlayerVec[k].GetPosX() - mPlayerVec[k].GetSprite().getTexture()->getSize().x / 2) && NewBulletPos.x < (mPlayerVec[k].GetPosX() + mPlayerVec.at(k).GetTexture().getSize().x / 2))    //Lines up x-wise
				{
					if (NewBulletPos.y >(mPlayerVec[k].GetPosY() - mPlayerVec[k].GetSprite().getTexture()->getSize().y / 2) && NewBulletPos.y < (mPlayerVec[k].GetPosY() + mPlayerVec.at(k).GetTexture().getSize().x / 2))   //lines up y-wise
					{   //Colision :D
						mPlayerVec[k].SetHealth(mPlayerVec[k].GetHealth() - player.GetProjectile(i).GetDamage());
						player.RemoveProjectile(i);
						i -= 1;						//what was the nth element is now the (n - 1)th element because all other elements were shifted down when the one was removed, hence i -= 1 to correct this.
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
	std::vector<Character*> CharactersInSight;                 
	std::vector<float> Distance;

	for (unsigned int i = 0; i < mPlayerVec.size(); i++)
	{
		if (pCharacter->GetTeamID() != mPlayerVec.at(i).GetTeamID())	
		{
			if (!(mTileEngine.CheckLineSolidColision(pCharacter->GetPosX(), pCharacter->GetPosY(), mPlayerVec.at(i).GetPosX(), mPlayerVec.at(i).GetPosY())))
			{
				CharactersInSight.push_back(&mPlayerVec[i]);
				Distance.push_back(FunctionLib::DistanceBetween(pCharacter->GetPosX(), pCharacter->GetPosY(), mPlayerVec.at(i).GetPosX(), mPlayerVec.at(i).GetPosY()));
			}
		}
	}

	float Angle;
	float Xdif;
	float Ydif;

	if (CharactersInSight.size() != 0)
	{
		Character* ClosestCharacter = CharactersInSight[std::min_element(Distance.begin(), Distance.end()) - Distance.begin()];

		Xdif = ClosestCharacter->GetPosX() - pCharacter->GetPosX();
		Ydif = ClosestCharacter->GetPosY() - pCharacter->GetPosY();
	}
	else    //No los, go in direction of movement
	{
		Xdif = val.RightPressed - val.LeftPressed;
		Ydif = val.DownPressed - val.UpPressed;
	}

	Angle = atan2f(Ydif, Xdif);

	return Angle;
}

void LevelEntityManager::InitialiseTiles(std::vector<std::vector<Tile> >& vec, unsigned int TargetTileX, unsigned int TargetTileY)
{
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		for (unsigned int j = 0; j < vec.at(i).size(); j++)
		{
			vec.at(i).at(j).h = (abs(static_cast<int>(TargetTileX)-static_cast<int>(j)) + abs(static_cast<int>(TargetTileY)-static_cast<int>(i))) * 10.f;  //G value is the distance you must move X from target to tile, and Y, * 1
			vec.at(i).at(j).g = 0;
			vec.at(i).at(j).f = vec.at(i).at(j).g + vec.at(i).at(j).h;
			vec.at(i).at(j).x = j;
			vec.at(i).at(j).y = i;
			vec.at(i).at(j).Closed = false;
		}
	}
}

void LevelEntityManager::CheckNeibours(std::vector<Tile>& OpenList, std::vector<std::vector<Tile> >& Tiles, unsigned int LowestF)
{
	std::vector<Tile> Neibours;

	if (OpenList[LowestF].x + 1 < Tiles[0].size())
		Neibours.push_back(Tiles[OpenList[LowestF].y][OpenList[LowestF].x + 1]);

	if (OpenList[LowestF].x - 1 >= 0)
		Neibours.push_back(Tiles[OpenList[LowestF].y][OpenList[LowestF].x - 1]);

	if (OpenList[LowestF].y + 1 < Tiles.size())
		Neibours.push_back(Tiles[OpenList[LowestF].y + 1][OpenList[LowestF].x]);

	if (OpenList[LowestF].y - 1 >= 0)
		Neibours.push_back(Tiles[OpenList[LowestF].y - 1][OpenList[LowestF].x]);

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
	}
}

KeyState LevelEntityManager::AiMoveDecide(Character* pCharacter)
{
	KeyState ClosestMoveDirection;

	float lowestG = -1;

    std::vector<std::vector<Tile> > Tiles = mTileEngine.GetTiles();

	for (int iPlayer = 0; iPlayer < mPlayerVec.size(); iPlayer++)
	{
		KeyState MoveDirection;

		if (pCharacter->GetTeamID() != mPlayerVec[iPlayer].GetTeamID())
		{
			float TargetX = mPlayerVec[iPlayer].GetPosX();
			float TargetY = mPlayerVec[iPlayer].GetPosY();

			unsigned int TargetTileX = int((TargetX - mTileEngine.GetPosX()) / mTileEngine.GetTileWidth());
			unsigned int TargetTileY = int((TargetY - mTileEngine.GetPosY()) / mTileEngine.GetTileHeight());

			float StartX = pCharacter->GetPosX();
			float StartY = pCharacter->GetPosY();

			unsigned int StartTileX = int((StartX - mTileEngine.GetPosX()) / mTileEngine.GetTileWidth());
			unsigned int StartTileY = int((StartY - mTileEngine.GetPosY()) / mTileEngine.GetTileHeight());

			InitialiseTiles(Tiles, TargetTileX, TargetTileY);

			bool HasFoundTarget = CalculatePath(Tiles, TargetTileX, TargetTileY, StartTileX, StartTileY);

			if (HasFoundTarget)
			{
				MoveDirection = GenerateKeyStateFromPath(Tiles, StartTileX, StartTileY, TargetTileX, TargetTileY, StartX, StartY);

				AllignKeyStateToGrid(MoveDirection, StartTileX, StartTileY, StartX, StartY);

				if (Tiles[TargetTileY][TargetTileX].g < lowestG || lowestG == -1)	//If lowestG is -1, there has not been a path found before this, so this must be the closest
				{	
					ClosestMoveDirection = MoveDirection;
					lowestG = Tiles[TargetTileY][TargetTileX].g;
				}
			}
		}
	}

	ClosestMoveDirection.LMBPressed = GenerateLMBState(pCharacter);
    return ClosestMoveDirection;
}

bool LevelEntityManager::CalculatePath(std::vector<std::vector<Tile> >& Tiles, unsigned int TargetTileX, unsigned int TargetTileY, unsigned int StartTileX, unsigned int StartTileY)
{
	std::vector<Tile> OpenList;

	OpenList.push_back(Tiles[StartTileY][StartTileX]);  //Add starting tile to open

	for (unsigned int iterationCount = 0; iterationCount < mTileEngine.GetMapSizeX() * mTileEngine.GetMapSizeY(); iterationCount++)
	{
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

		CheckNeibours(OpenList, Tiles, LowestF);

		//Now update F values
		for (unsigned int i = 0; i < OpenList.size(); i++)
		{
			OpenList.at(i).f = OpenList.at(i).g + OpenList.at(i).h;
			Tiles[OpenList.at(i).y][OpenList.at(i).x] = OpenList.at(i);
		}

		Tiles[CurrentTileY][CurrentTileX].Closed = true;
		OpenList.erase(OpenList.begin() + LowestF);

		if (CurrentTileX == TargetTileX && CurrentTileY == TargetTileY)
		{
			return true;
		}

		if (OpenList.size() == 0)
			break;
	}

	return false;
}

bool LevelEntityManager::GenerateLMBState(Character* pCharacter)
{
	for (unsigned int i = 0; i < mPlayerVec.size(); i++)
	{
		if (pCharacter->GetTeamID() != mPlayerVec.at(i).GetTeamID())  //if the guy is not on the same team
		{
			if (!(mTileEngine.CheckLineSolidColision(pCharacter->GetPosX(), pCharacter->GetPosY(), mPlayerVec.at(i).GetPosX(), mPlayerVec.at(i).GetPosY())))
			{
				return true;
			}
		}
	}
	return false;
}

void LevelEntityManager::AllignKeyStateToGrid(KeyState& MoveDirection, unsigned int StartTileX, unsigned int StartTileY, unsigned int StartX, unsigned int StartY)
{
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
		int TargetY = (StartTileY + 0.5) * mTileEngine.GetTileHeight();

		if (StartY < TargetY - 4)
			MoveDirection.DownPressed = true;
		if (StartY > TargetY + 4)
			MoveDirection.UpPressed = true;
	}

	if (AllignHorisontal)
	{
		int TargetX = (StartTileX + 0.5) * mTileEngine.GetTileWidth();

		if (StartX < TargetX - 4)
			MoveDirection.RightPressed = true;
		if (StartX > TargetX + 4)
			MoveDirection.LeftPressed = true;
	}
}

KeyState LevelEntityManager::GenerateKeyStateFromPath(std::vector<std::vector<Tile> >& Tiles, unsigned int StartTileX, unsigned int StartTileY, unsigned int TargetTileX, unsigned int TargetTileY, float StartX, float StartY)
{
	KeyState MoveDirection;

	int BaseTileX = TargetTileX;
	int BaseTileY = TargetTileY;
	int ParentTileX = BaseTileX;
	int ParentTileY = BaseTileY;

	MoveDirection.LeftPressed = false;
	MoveDirection.RightPressed = false;
	MoveDirection.UpPressed = false;
	MoveDirection.DownPressed = false;

	for (int i = 0; i < 100; i++)
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

	return MoveDirection;
}

void LevelEntityManager::SetSpawnPoint(unsigned int index, sf::Vector2f point)
{
    if (index < mSpawnPoints.size())
        mSpawnPoints[index] = point;
    else
        mSpawnPoints.push_back(point);
}

void LevelEntityManager::GenerateDustTestLevel()
{
	unsigned int pTileWidth = 32; 
	unsigned int pTileHeight = 32; 
	unsigned int pMapSizeX = 30;
	unsigned int pMapSizeY = 30; 
	sf::Texture pTileSet;
	float pPosX = 0;
	float pPosY = 0;

	pTileSet.loadFromFile("DustTileSet.png");

	std::vector<std::vector<int> > pTileIDVec = 
	{
		{ 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76 },
		{ 76, 35, 35, 35, 35, 35, 35, 35, 76, 62, 63, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 62, 63, 76 },
		{ 76, 35, 35, 35, 35, 35, 35, 35, 76, 67, 68, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 67, 68, 76 },
		{ 76, 35, 35, 35, 35, 35, 35, 35, 76, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 76 },
		{ 76, 35, 35, 35, 35, 35, 35, 35, 76, 10, 10, 10, 10, 10, 10, 10, 10, 76, 76, 76, 76, 76, 76, 76, 76, 76, 10, 10, 10, 76 },
		{ 76, 35, 35, 35, 35, 35, 35, 35, 76, 10, 10, 10, 10, 11, 11, 10, 11, 76, 62, 63, 10, 11, 11, 62, 63, 76, 10, 10, 10, 76 },
		{ 76, 35, 35, 35, 35, 35, 35, 35, 76, 10, 10, 10, 10, 11, 10, 11, 11, 76, 67, 68, 10, 10, 10, 67, 68, 76, 10, 10, 10, 76 },
		{ 76, 35, 35, 35, 35, 35, 35, 34, 76, 10, 10, 10, 10, 10, 10, 11, 10, 76, 11, 10, 10, 10, 10, 10, 10, 76, 10, 10, 10, 76 },
		{ 76, 76, 76, 76, 31, 32, 76, 76, 76, 10, 10, 10, 10, 10, 10, 11, 11, 76, 11, 10, 10, 10, 10, 10, 10, 76, 10, 10, 10, 76 },
		{ 76, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11, 11, 76, 10, 10, 10, 76 },
		{ 76, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 10, 11, 10, 76, 10, 10, 10, 76 },
		{ 76, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 10, 10, 11, 11, 11, 11, 10, 10, 62, 63, 11, 10, 10, 10, 76, 10, 10, 10, 76 },
		{ 76, 76, 76, 76, 76, 76, 76, 10, 10, 76, 76, 76, 76, 76, 62, 63, 11, 10, 10, 67, 68, 11, 10, 10, 10, 76, 10, 10, 10, 76 },
		{ 76, 62, 63, 10, 10, 10, 10, 10, 10, 10, 10, 62, 63, 76, 67, 68, 10, 11, 10, 10, 11, 10, 10, 10, 10, 76, 10, 10, 10, 76 },
		{ 76, 67, 68, 10, 10, 10, 10, 10, 10, 10, 10, 67, 68, 76, 62, 63, 10, 11, 11, 10, 11, 10, 10, 10, 10, 76, 10, 10, 10, 76 },
		{ 76, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 11, 11, 76, 67, 68, 10, 11, 11, 10, 11, 10, 10, 10, 10, 76, 10, 10, 10, 76 },
		{ 76, 10, 10, 10, 11, 10, 10, 10, 10, 10, 10, 11, 10, 76, 62, 63, 62, 63, 11, 10, 11, 10, 11, 62, 63, 76, 10, 10, 10, 76 },
		{ 76, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 11, 10, 76, 67, 68, 67, 68, 10, 11, 10, 10, 11, 67, 68, 76, 10, 10, 10, 76 },
		{ 76, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, 11, 10, 76, 10, 11, 11, 10, 10, 11, 76, 76, 76, 76, 76, 76, 10, 10, 10, 76 },
		{ 76, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, 11, 10, 76, 11, 11, 10, 11, 10, 11, 10, 10, 10, 11, 10, 10, 10, 10, 10, 76 },
		{ 76, 10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 11, 10, 76, 11, 10, 11, 11, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 76 },
		{ 76, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 76, 11, 11, 11, 11, 10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, 76 },
		{ 76, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 76, 11, 11, 11, 10, 10, 10, 10, 11, 76, 76, 76, 76, 76, 76, 76, 76 },
		{ 76, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 10, 10, 76, 62, 63, 10, 10, 10, 10, 10, 11, 76, 35, 35, 35, 35, 35, 35, 76 },
		{ 76, 10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, 10, 76, 67, 68, 10, 10, 10, 10, 10, 10, 29, 35, 35, 35, 35, 35, 35, 76 },
		{ 76, 10, 10, 10, 10, 10, 10, 10, 10, 11, 10, 10, 10, 76, 76, 76, 76, 76, 76, 76, 11, 10, 31, 35, 35, 35, 35, 35, 35, 76 },
		{ 76, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 10, 10, 10, 10, 11, 11, 11, 11, 10, 10, 76, 35, 35, 35, 35, 35, 35, 76 },
		{ 76, 62, 63, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 10, 10, 10, 11, 11, 10, 76, 35, 35, 35, 35, 35, 35, 76 },
		{ 76, 67, 68, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 76, 35, 35, 35, 35, 35, 35, 76 },
		{ 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76 }
	};

	std::vector<std::vector<bool> > pTileSolidState = 
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			pTileIDVec[i][j]--;
		}
	}

	mTileEngine.LoadFromParam(pTileWidth, pTileHeight, pMapSizeX, pMapSizeY, pTileSet, pTileIDVec, pTileSolidState, pPosX, pPosY);
}
