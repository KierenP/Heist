#include "TileEngine.h"

TileEngine::TileEngine()
{

}

TileEngine::TileEngine(std::string pFileLocation)
{
    LoadFromFile(pFileLocation);
}

TileEngine::TileEngine(float pPosX, float pPosY, float pTileWidth, float pTileHeight, sf::Texture pTileSet, std::vector<std::vector<int> >& pTileIDVec, std::vector<std::vector<bool> >& pSolidStateVec)
{
    LoadFromParam(pPosX, pPosY, pTileWidth, pTileHeight, pTileSet, pTileIDVec, pSolidStateVec);
}

TileEngine::TileEngine(float pPosX, float pPosY, float pTileWidth, float pTileHeight, sf::Texture pTileSet, std::vector<std::vector<Tile> > pTiles)
{
    LoadFromTiles(pPosX, pPosY, pTileWidth, pTileHeight, pTileSet, pTiles);
}

void TileEngine::LoadFromFile(std::string pFileLocation)
{
    //Load from File
}

void TileEngine::LoadFromParam(float pPosX, float pPosY, float pTileWidth, float pTileHeight, sf::Texture pTileSet, std::vector<std::vector<int> >& pTileIDVec, std::vector<std::vector<bool> >& pSolidStateVec)
{
    mPosX = pPosX;
    mPosY = pPosY;
    mTileWidth = pTileWidth;
    mTileHeight = pTileHeight;
    mMapSizeX = pTileHeight;
    mMapSizeY = pTileHeight;

    for (unsigned int i = 0; i < mMapSizeY; i++)
    {
        for (unsigned int j = 0; j < mMapSizeX; j++)
        {
            //Generate tiles ;)
        }
    }
}

void TileEngine::LoadFromTiles(float pPosX, float pPosY, float pTileWidth, float pTileHeight, sf::Texture pTileSet, std::vector<std::vector<Tile> >& pTiles)
{
    mPosX = pPosX;
    mPosY = pPosY;
    mTileWidth = pTileWidth;
    mTileHeight = pTileHeight;
    mMapSizeX = pTileHeight;
    mMapSizeY = pTileHeight;
    mTiles = pTiles;
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
