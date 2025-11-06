#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "axmol.h"
using namespace ax;

class GameMap : public Node
{
public:
    virtual bool init();

    float getTileSize() const;
    Vec2 getMapSize() const;
    Vec2 tileToPixel(const Vec2& tilePos, const Size& tileSize);

    Vec2 getStartPosPixel();
    bool mapCollision(Vec2 headPos, Vec2 startPos);

private:
    ax::Vec2 visibleSize;
    ax::Vec2 origin;
    ax::Rect safeArea;
    ax::Vec2 safeOrigin;

    ax::TMXTiledMap* tileMap;

    ax::Vec2 tileSize; //Size of tile (pixel)
    ax::Vec2 mapSize; //Size of tile map (x tile, y tile)

    ax::Vec2 startPosPixel;
};

#endif // __GAME_MAP_H__
