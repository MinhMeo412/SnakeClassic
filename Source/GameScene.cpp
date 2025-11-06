#include "GameScene.h"
#include "Utils.h"
#include "SaveScoreScene.h"
#include "AudioManager.h"

using namespace ax;

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    visibleSize = _director->getVisibleSize();
    origin      = _director->getVisibleOrigin();
    safeArea    = _director->getSafeAreaRect();
    safeOrigin  = safeArea.origin;

    enableCustomCursor();

    // Map
    gameMap = utils::createInstance<GameMap>();
    this->addChild(gameMap, 0);

    // Score
    score      = 0;
    scoreLabel = Label::createWithSystemFont("Score: " + std::to_string(score), "Arial", 24);
    scoreLabel->setDimensions(150, 25);
    scoreLabel->setHorizontalAlignment(TextHAlignment::LEFT);
    scoreLabel->setVerticalAlignment(TextVAlignment::CENTER);
    scoreLabel->setPosition(200, 670);
    this->addChild(scoreLabel, 9);

    // Snake
    snakeLogic = new SnakeModel();
    snakeLogic->initSnake(gameMap->getStartPosPixel(), gameMap->getTileSize());
    snakeUI = SnakeUI::create(snakeLogic);
    this->addChild(snakeUI, 2);

    snakeController = new SnakeController(snakeLogic, snakeUI);

    // Food (first time spawn)
    spawnFood();

    // KeyboardHandle
    initKeyboardListener();

    scheduleUpdate();

    return true;
}

void GameScene::spawnFood()
{
    if (food)
    {
        this->removeChild(food);
    }

    food = Food::create();

    food->setPosition(getRandomPosition());
    this->addChild(food, 1);
}

Vec2 GameScene::getRandomPosition()
{
    Vec2 randomPos;
    bool positionValid = false;

    while (!positionValid)
    {
        int x     = random(0, static_cast<int>(gameMap->getMapSize().width) - 1);
        int y     = random(0, static_cast<int>(gameMap->getMapSize().height) - 1);
        randomPos = gameMap->tileToPixel(Vec2(x, y), Size(gameMap->getTileSize(), gameMap->getTileSize())) +
                    Vec2(gameMap->getTileSize() / 2, gameMap->getTileSize() / 2);
        positionValid = true;

        for (const auto& pos : snakeLogic->getBodyPositions())
        {
            if (pos.equals(randomPos))
            {
                positionValid = false;
                break;
            }
        }
    }

    return randomPos;
}

void GameScene::update(float dt)
{
    snakeController->update(dt);
    
    checkCollisions();
}

void GameScene::checkCollisions()
{
    Vec2 headPos = snakeLogic->getHeadPosition();
    if (headPos.equals(food->getPosition()))
    {
        AudioManager::getInstance()->playEatEffect();
        snakeLogic->grow();
        updateScore();
        switch (score)
        {
            case 10:
            snakeLogic->setMoveInterval(0.4);
                break;
            case 30:
                snakeLogic->setMoveInterval(0.35);
                break;
            case 50:
                snakeLogic->setMoveInterval(0.3);
                break;
            case 100:
                snakeLogic->setMoveInterval(0.25);
                break;
            case 200:
                snakeLogic->setMoveInterval(0.2);
                break;
            case 300:
                snakeLogic->setMoveInterval(0.15);
                break;
            case 400:
                snakeLogic->setMoveInterval(0.1);
                break;
            case 500:
                snakeLogic->setMoveInterval(0.05);
                break;
            default:
                break;
        }
        spawnFood();
    }

    if (snakeLogic->checkSelfCollision()  || gameMap->mapCollision(headPos, gameMap->getStartPosPixel()))
    {
        AudioManager::getInstance()->playHitEffect();
        Director::getInstance()->replaceScene(SaveScoreScene::createScene(score));
    }
}

void GameScene::updateScore()
{
    score++;
    scoreLabel->setString("Score: " + std::to_string(score));
}

void GameScene::initKeyboardListener()
{
    auto keyboardListener = EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        Direction newDirection = Direction::NONE;

        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            newDirection = Direction::UP;
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            newDirection = Direction::DOWN;
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            newDirection = Direction::LEFT;
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            newDirection = Direction::RIGHT;
            break;
        default:
            break;
        }

        // Cập nhật hướng cho SnakeLogic
        if (newDirection != Direction::NONE)
        {
            snakeController->handleInput(newDirection);
        }
    };

    // Thêm listener vào event dispatcher
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}
