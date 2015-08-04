#ifndef TILEENGINE_H_INCLUDED
#define TILEENGINE_H_INCLUDED

#include "Entity.h"

struct Tile
{
    sf::Sprite mTileSprite;
    bool mSolidState;
};

class TileEngine;
{
public:
    TileEngine();                               //Defult ctor
    TileEngine(string pFileLocation);           //Generate from a file
    TileEngine(float pPosX, float pPoxY, float pTileWidth, float pTileHeight, sf::Texture pTileSet, vector<vector<int>> pTileIDVec, vector<vector<bool>> pSolidStateVec);   //Generate from paramiters
    TileEngine(vector<vector<Tile>> pTiles);    //Generate from already generated Tile vector

    float GetPosX() { return mPosX; }
    float GetPosY() { return mPosY; }
    vector<vector<Tile>>& GetTiles() { return mTiles; }
    //TODO: Add other getters and setters!

    bool LoadFromFile(string pFileLocation);
    bool LoadFromParam()

private:
    float mPosX, mPoxY;                 //Position x and y
    float mTileWidth, mTileHeight;      //Tile width and height in pixles
    float mMapSizeX, mMapSizeY;         //Map size, in tiles
    vector<vector<Tile>> mTiles;
};

#endif // TILEENGINE_H_INCLUDED
