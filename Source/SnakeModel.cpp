#include "SnakeModel.h"
#include "Utils.h"

using namespace ax;


SnakeModel::SnakeModel() : currentDirection(Direction::NONE), tileSize(0) {}


void SnakeModel::initSnake(Vec2 startPos, float tileSize)
{
    this->tileSize = tileSize;
    bodyPositions.clear();
    bodyPositions.push_front(startPos); 

    for (int i = 1; i < 3; ++i)
    {
        Vec2 newPartPos = startPos + Vec2(0, -i * tileSize);
        bodyPositions.push_back(newPartPos);
    }
}


bool SnakeModel::move(float deltaTime)
{
    if (currentDirection == NONE) return false;

    elapsedTime += deltaTime;

    if (elapsedTime >= moveInterval)
    {
        elapsedTime          = 0.0f;
        directionChanged = false;

        Vec2 newHeadPosition = bodyPositions.front();

        switch (currentDirection)
        {
        case UP:
            newHeadPosition.y += tileSize;
            break;
        case DOWN:
            newHeadPosition.y -= tileSize;
            break;
        case LEFT:
            newHeadPosition.x -= tileSize;
            break;
        case RIGHT:
            newHeadPosition.x += tileSize;
            break;
        default:
            break;
        }

        bodyPositions.push_front(newHeadPosition);
        bodyPositions.pop_back();

        return true;
    }

    return false;
}

void SnakeModel::changeDirection(Direction dir)
{

    if ((currentDirection == NONE && dir != DOWN) ||
        (currentDirection == UP && dir != DOWN) ||
        (currentDirection == DOWN && dir != UP) ||
        (currentDirection == LEFT && dir != RIGHT) ||
        (currentDirection == RIGHT && dir != LEFT))
    {
        if (!directionChanged)
        {
            currentDirection = dir;
            directionChanged = true;
        }
    }

}




void SnakeModel::grow()
{
    bodyPositions.push_back(bodyPositions.back());
}

Direction SnakeModel::getDirections() const
{
    return currentDirection;
}

bool SnakeModel::checkSelfCollision() const
{
    Vec2 headPosition = bodyPositions.front();
    for (size_t i = 1; i < bodyPositions.size(); ++i)
    {
        if (bodyPositions[i].distance(headPosition) < tileSize / 2)
        {
            return true;
        }
    }
    return false;
}

Vec2 SnakeModel::getHeadPosition() const
{
    return bodyPositions.empty() ? Vec2::ZERO : bodyPositions.front();
}

const std::deque<Vec2>& SnakeModel::getBodyPositions() const
{
    return bodyPositions;
};

void SnakeModel::setMoveInterval(float speed)
{
    moveInterval = speed;
}
