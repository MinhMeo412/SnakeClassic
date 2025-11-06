#ifndef __SNAKE_CONTROLLER_H__
#define __SNAKE_CONTROLLER_H__

#include "SnakeModel.h"
#include "SnakeUI.h"

class SnakeController
{
public:
    SnakeController(SnakeModel* snakeModel, SnakeUI* snakeUI);

    void update(float dt);
    void handleInput(Direction input);

private:
    SnakeModel* snakeModel;
    SnakeUI* snakeUI;
};

#endif  //__SNAKE_CONTROLLER_H__
