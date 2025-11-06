#include "SnakeController.h"

SnakeController::SnakeController(SnakeModel* snakeModel, SnakeUI* snakeUI) : snakeModel(snakeModel), snakeUI(snakeUI) {}

void SnakeController::update(float deltaTime)
{
    if (snakeModel->move(deltaTime))
    {
        snakeUI->updateUI();
    }
}


void SnakeController::handleInput(Direction input)
{
    snakeModel->changeDirection(input);
}
