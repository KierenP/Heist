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

TileEngine::TileEngine(float pPosX, float pPosY, float pTileWidth, float pTileHeight, unsigned int pMapSizeX, unsigned int pMapSizeY, sf::Texture pTileSet, std::vector<std::vector<int> >& pTileIDVec, std::vector<std::vector<bool> >& pSolidStateVec)
{
    LoadFromParam(pPosX, pPosY, pTileWidth, pTileHeight, pMapSizeX, pMapSizeY, pTileSet, pTileIDVec, pSolidStateVec);
}

TileEngine::TileEngine(float pPosX, float pPosY, float pTileWidth, float pTileHeight, unsigned int pMapSizeX, unsigned int pMapSizeY, sf::Texture pTileSet, std::vector<std::vector<Tile> > pTiles)
{
    LoadFromTiles(pPosX, pPosY, pTileWidth, pTileHeight, pMapSizeX, pMapSizeY, pTileSet, pTiles);
}

void TileEngine::LoadFromFile(std::string pFileLocation)
{
    //Load from File
}

void TileEngine::LoadFromParam(float pPosX, float pPosY, float pTileWidth, float pTileHeight, unsigned int pMapSizeX, unsigned int pMapSizeY, sf::Texture pTileSet, std::vector<std::vector<int> >& pTileIDVec, std::vector<std::vector<bool> >& pSolidStateVec)
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

void TileEngine::LoadFromTiles(float pPosX, float pPosY, float pTileWidth, float pTileHeight, unsigned int pMapSizeX, unsigned int pMapSizeY, sf::Texture pTileSet, std::vector<std::vector<Tile> >& pTiles)
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
