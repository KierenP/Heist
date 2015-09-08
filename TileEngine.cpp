#include "TileEngine.h"

TileEngine::TileEngine()
{

}

TileEngine::~TileEngine()
{

}

TileEngine::TileEngine(std::string pFileLocation)
{
    LoadFromFile(pFileLocation);
}

TileEngine::TileEngine(float pTileWidth, float pTileHeight, unsigned int pMapSizeX, unsigned int pMapSizeY, sf::Texture pTileSet, std::vector<std::vector<int> >& pTileIDVec, std::vector<std::vector<bool> >& pSolidStateVec, float pPosX, float pPosY)
{
    LoadFromParam(pTileWidth, pTileHeight, pMapSizeX, pMapSizeY, pTileSet, pTileIDVec, pSolidStateVec, pPosX, pPosY);
}

TileEngine::TileEngine(float pTileWidth, float pTileHeight, unsigned int pMapSizeX, unsigned int pMapSizeY, sf::Texture pTileSet, std::vector<std::vector<Tile> > pTiles, float pPosX, float pPosY)
{
    LoadFromTiles(pTileWidth, pTileHeight, pMapSizeX, pMapSizeY, pTileSet, pTiles, pPosX, pPosY);
}

void TileEngine::LoadFromFile(std::string pFileLocation)
{
    //Load from File
}

void TileEngine::LoadFromParam(float pTileWidth, float pTileHeight, unsigned int pMapSizeX, unsigned int pMapSizeY, sf::Texture pTileSet, std::vector<std::vector<int> >& pTileIDVec, std::vector<std::vector<bool> >& pSolidStateVec, float pPosX, float pPosY)
{
    mPosX = pPosX;
    mPosY = pPosY;
    mTileWidth = pTileWidth;
    mTileHeight = pTileHeight;
    mMapSizeX = pMapSizeX;
    mMapSizeY = pMapSizeY;
    mTileSet = pTileSet;

    for (unsigned int i = 0; i < mMapSizeY; i++)
    {
        std::vector<Tile> Row;

        for (unsigned int j = 0; j < mMapSizeX; j++)
        {
            Tile TempTile;

            TempTile.mSolidState = pSolidStateVec[i][j];
            TempTile.mTileSprite.setTexture(mTileSet);
            TempTile.mTileSprite.setTextureRect(sf::IntRect((pTileIDVec[i][j] % static_cast<int>(mTileSet.getSize().x / mTileWidth)) * mTileWidth, static_cast<int>(pTileIDVec[i][j] / (mTileSet.getSize().x / mTileWidth)) * mTileHeight, mTileWidth, mTileHeight));

            Row.push_back(TempTile);
        }

        mTiles.push_back(Row);
    }

    UpdateTileSpritePos();
}

void TileEngine::LoadFromTiles(float pTileWidth, float pTileHeight, unsigned int pMapSizeX, unsigned int pMapSizeY, sf::Texture pTileSet, std::vector<std::vector<Tile> >& pTiles, float pPosX, float pPosY)
{
    mPosX = pPosX;
    mPosY = pPosY;
    mTileWidth = pTileWidth;
    mTileHeight = pTileHeight;
    mMapSizeX = pMapSizeX;
    mMapSizeY = pMapSizeY;
    mTiles = pTiles;
    mTileSet = pTileSet;
}

void TileEngine::Render(sf::RenderWindow* pTarget)
{
    for (unsigned int i = 0; i < mMapSizeY; i++)
    {
        for (unsigned int j = 0; j < mMapSizeX; j++)
        {
            pTarget->draw(mTiles[i][j].mTileSprite);
        }
    }
}

void TileEngine::UpdateTileSpritePos()
{
    for (unsigned int i = 0; i < mMapSizeY; i++)
    {
        for (unsigned int j = 0; j < mMapSizeX; j++)
        {
            mTiles[i][j].mTileSprite.setPosition(mPosX + j * mTileWidth, mPosY + i * mTileHeight);
        }
    }
}

bool TileEngine::CheckSolid(float px, float py) const
{
    float RelX = px - mPosX;
    float RelY = py - mPosY;

    if (RelX < 0 || RelY < 0 || RelX > mMapSizeX * mTileWidth ||  RelY > mMapSizeY * mTileHeight)  //If out of the world, colision = true
        return true;

    int TilesX = static_cast<int>(RelX / mTileWidth);
    int TilesY = static_cast<int>(RelY / mTileHeight);

    if (mTiles[TilesY][TilesX].mSolidState)  //guarenteed not to throw out of range exeption because of previous if statement exclusing out of bounds values
        return true;

    return false;
}

bool TileEngine::CheckLineSolidColision(float ax, float ay, float bx, float by)
{
    //This code is not very commented. Edit or attempt to understant at your own peril

    for (int i = 0; i < mTiles.size(); i++)
    {
        for (int j = 0; j < mTiles[i].size(); j++)
        {
            if (mTiles[i][j].mSolidState)
            {
                std::vector<sf::Vector2f> TilePoints = FunctionLib::GenerateBoxFromDimentions(j * mTileWidth + mPosX, i * mTileHeight + mPosY, mTileWidth, mTileHeight);

                float m = (by - ay) / (bx - ax);     //trying to find equasion of line in form y = mx + b. I have found m

                float b = ay - m*ax;                       //re arange to form b = y - mx, and sub in values for x and y

                std::vector<bool> PointIsAbove;

                for (int k = 0; k < TilePoints.size(); k++)
                {
                    if (TilePoints[k].x * m + b > TilePoints[k].y)
                        PointIsAbove.push_back(false);
                    else
                        PointIsAbove.push_back(true);
                }

                if (!((PointIsAbove[0] == PointIsAbove[1]) && (PointIsAbove[1] == PointIsAbove[2]) && (PointIsAbove[2] == PointIsAbove[3]) && (PointIsAbove[3] == PointIsAbove[0])));
                    return true;
            }
        }
    }

    return false;
}
