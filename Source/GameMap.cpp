#include "GameMap.h"

using namespace ax;

bool GameMap::init()
{
    if (!Node::init())
    {
        return false;
    }

    visibleSize = _director->getVisibleSize();
    origin      = _director->getVisibleOrigin();
    safeArea    = _director->getSafeAreaRect();
    safeOrigin  = safeArea.origin;

    // Create map
    tileMap = TMXTiledMap::create("Map.tmx");
    tileMap->setAnchorPoint(Vec2(0.5, 0.5));
    tileMap->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(tileMap);

    // Red border
    auto drawNode = DrawNode::create();
    Vec2 mapOrigin =
        tileMap->getPosition() - Vec2(tileMap->getContentSize().width / 2, tileMap->getContentSize().height / 2);
    Vec2 mapEnd = mapOrigin + tileMap->getContentSize();

    drawNode->drawRect(mapOrigin, mapEnd, Color4F::RED);
    this->addChild(drawNode);

    tileSize = tileMap->getTileSize();
    mapSize  = tileMap->getMapSize();

    auto startTilePos = Vec2(mapSize.width / 2, mapSize.height / 2);

    startPosPixel = tileToPixel(startTilePos, tileSize) + Vec2(tileSize.width / 2, tileSize.height / 2);

    return true;
}

float GameMap::getTileSize() const
{
    return tileSize.width;
}

Vec2 GameMap::tileToPixel(const Vec2& tilePos, const Size& tileSize)
{
    auto tileMapPosition = tileMap->getPosition();
    float bottomLeftX    = tileMapPosition.width - (mapSize.width * getTileSize() / 2);
    float bottomLeftY    = tileMapPosition.height - (mapSize.height * getTileSize() / 2);
    return Vec2(tilePos.x * tileSize.width, tilePos.y * tileSize.height) + Vec2(bottomLeftX, bottomLeftY);
    AXLOG("%f%f", bottomLeftX, bottomLeftY);
}

Vec2 GameMap::getStartPosPixel()
{
    return startPosPixel;
}

Vec2 GameMap::getMapSize() const
{
    return mapSize;
}

bool GameMap::mapCollision(Vec2 headPos, Vec2 startPos)
{
    auto tileMapPosition = tileMap->getPosition();
    float bottomLeftX    = tileMapPosition.width - (mapSize.width * getTileSize() / 2);
    float bottomLeftY    = tileMapPosition.height - (mapSize.height * getTileSize() / 2);

    int headPosX = (headPos.x - bottomLeftX - 16) / tileSize.width;
    int headPosY = (headPos.y - bottomLeftY - 16) / tileSize.height;

    if (headPosX < 0 || headPosY < 0 || headPosX >= mapSize.x || headPosY >= mapSize.y)
    {
        return true;
    }
    return false;
}
