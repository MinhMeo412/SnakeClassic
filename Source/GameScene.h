#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "axmol.h"
#include "Utils.h"
#include "SceneBase.h"
#include "GameMap.h"
#include "SnakeModel.h"
#include "SnakeUI.h"
#include "SnakeController.h"
#include "Food.h"

class GameScene : public SceneBase
{
public:
    virtual bool init();

    void spawnFood();

    void update(float dt);
private:
    ax::Vec2 visibleSize;
    ax::Vec2 origin;
    ax::Rect safeArea;
    ax::Vec2 safeOrigin;

    GameMap* gameMap;
    SnakeModel* snakeLogic;
    SnakeUI* snakeUI;
    SnakeController* snakeController;
    Food* food;
    int score;
    Label* scoreLabel;

    

    void checkCollisions();
    void updateScore();
    void initKeyboardListener();

    Vec2 getRandomPosition();
};

#endif // __GAME_SCENE_H__
