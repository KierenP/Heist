#ifndef TILEENGINE_H_INCLUDED
#define TILEENGINE_H_INCLUDED

#include "Entity.h"
#include "SFML/Graphics.hpp"

struct Tile
{
    sf::Sprite mTileSprite;
    bool mSolidState;
};

class TileEngine
{
public:
    TileEngine();                               //Defult ctor
    TileEngine(std::string pFileLocation);      //Generate from a file
    TileEngine(float pPosX, float pPosY, float pTileWidth, float pTileHeight, unsigned int pMapSizeX, unsigned int pMapSizeY, sf::Texture pTileSet, std::vector<std::vector<int> >& pTileIDVec, std::vector<std::vector<bool> >& pSolidStateVec);   //Generate from paramiters
    TileEngine(float pPosX, float pPosY, float pTileWidth, float pTileHeight, unsigned int pMapSizeX, unsigned int pMapSizeY, sf::Texture pTileSet, std::vector<std::vector<Tile> > pTiles);    //Generate from already generated Tile vector
    ~TileEngine();

    //Getters
    float GetPosX() { return mPosX; }
    float GetPosY() { return mPosY; }
    float GetTileWidth() { return mTileWidth; }
    float GetTileHeight() { return mTileHeight; }
    float GetSizeX() { return mMapSizeX; }
    float GetSizeY() { return mMapSizeY; }
    std::vector<std::vector<Tile> >& GetTiles() { return mTiles; }

    //Setters
    void SetPosX(float pPosX) { mPosX = pPosX; }
    void SetPosY(float pPosY) { mPosY = pPosY; }
    void SetTiles(std::vector<std::vector<Tile> >& pTiles) { mTiles = pTiles; }

    //Public member functions
    void LoadFromFile(std::string pFileLocation);
    void LoadFromParam(float pPosX, float pPosY, float pTileWidth, float pTileHeight, unsigned int pMapSizeX, unsigned int pMapSizeY, sf::Texture pTileSet, std::vector<std::vector<int> >& pTileIDVec, std::vector<std::vector<bool> >& pSolidStateVec);
    void LoadFromTiles(float pPosX, float pPosY, float pTileWidth, float pTileHeight, unsigned int pMapSizeX, unsigned int pMapSizeY, sf::Texture pTileSet, std::vector<std::vector<Tile> >& pTiles);
    void Render(sf::RenderWindow* pTarget);

private:
    void UpdateTileSpritePos();

    //Private member variables
    float mPosX, mPosY;                 //Position x and y
    float mTileWidth, mTileHeight;      //Tile width and height in pixles
    unsigned int mMapSizeX, mMapSizeY;  //Map size, in tiles
    sf::Texture mTileSet;
    std::vector<std::vector<Tile> > mTiles;
};

#endif // TILEENGINE_H_INCLUDED
