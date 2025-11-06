
#ifndef __SNAKE_MODEL_H__
#define __SNAKE_MODEL_H__

#include "axmol.h"
#include "Utils.h"

#include <deque>

class SnakeModel
{
public:
    SnakeModel();

    void initSnake(ax::Vec2 startPos, float tileSize);
    bool move(float deltaTime);
    void grow();

    void changeDirection(Direction dir);
    Direction getDirections() const;

    ax::Vec2 getHeadPosition() const;
    bool checkSelfCollision() const;

    void setMoveInterval(float speed);

    const std::deque<ax::Vec2>& getBodyPositions() const;

private:
    std::deque<ax::Vec2> bodyPositions;

    Direction currentDirection;

    float tileSize;

    float elapsedTime = 0.0f;
    //float moveInterval = 0.45f; //default
    float moveInterval = 0.3f; //test

    bool directionChanged = false;
};

#endif // __SNAKE_MODEL_H__
