#include "MainScene.h"
#include "Utils.h"
#include "CustomCursorManager.h"
#include "GameScene.h"
#include "HighScoreScene.h"
#include "AudioManager.h"

using namespace ax;

bool MainScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    visibleSize = _director->getVisibleSize();
    origin      = _director->getVisibleOrigin();
    safeArea    = _director->getSafeAreaRect();
    safeOrigin  = safeArea.origin;

    setupMouseListener();
    enableCustomCursor();
    createMainSceneItems();

    scheduleUpdate();

    return true;
}

void MainScene::createMainSceneItems()
{
    // Title
    auto titleSprite = Sprite::create("SnakeGame.png");
    titleSprite->setPosition(visibleSize.width / 2 + origin.x,
                             visibleSize.height - titleSprite->getContentSize().height / 2);
    titleSprite->setScale(0.8f);
    this->addChild(titleSprite);

    // Menu item position setup
    float itemSpacing = 120.0f;
    int itemOrderNum  = 0;
    float centerX     = safeOrigin.x + visibleSize.width / 2;
    float centerY     = safeOrigin.y + visibleSize.height / 2;

    // Tạo SpriteSheet từ file .plist
    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile("MenuItems.plist", "MenuItems.png");

    // Tạo các sprite từ sprite sheet
    auto playSprite        = Sprite::createWithSpriteFrameName("./PlayGame");
    auto playPressedSprite = Sprite::createWithSpriteFrameName("./PlayGamePressed");

    auto scoreSprite        = Sprite::createWithSpriteFrameName("./Score");
    auto scorePressedSprite = Sprite::createWithSpriteFrameName("./ScorePressed");

    auto exitSprite        = Sprite::createWithSpriteFrameName("./Exit");
    auto exitPressedSprite = Sprite::createWithSpriteFrameName("./ExitPressed");

    // Play button
    playItem =
        Utils::createMenuItem(playSprite, playPressedSprite, AX_CALLBACK_1(MainScene::menuPlayGameCallback, this),
                              Vec2(centerX, centerY - itemOrderNum++ * itemSpacing));

    // High Score button
    scoreItem =
        Utils::createMenuItem(scoreSprite, scorePressedSprite, AX_CALLBACK_1(MainScene::menuHighScoreCallback, this),
                              Vec2(centerX, centerY - itemOrderNum++ * itemSpacing));

    // Exit button
    exitItem = Utils::createMenuItem(exitSprite, exitPressedSprite, AX_CALLBACK_1(MainScene::menuCloseCallback, this),
                                     Vec2(centerX, centerY - itemOrderNum++ * itemSpacing));
    
    // Button border
    borderSprite = Sprite::createWithSpriteFrameName("./Border");
    borderSprite->setVisible(false);
    this->addChild(borderSprite, 2);

    // create menu, it's an autorelease object
    auto menu = Menu::create(playItem, scoreItem, exitItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void MainScene::onMouseMove(ax::Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    Vec2 mousePos = Vec2(e->getCursorX(), e->getCursorY());

    // Kiểm tra xem con trỏ nằm trên nút
    bool isHovering = false;

    if (playItem->getBoundingBox().containsPoint(mousePos))
    {
        borderSprite->setPosition(playItem->getPosition());
        isHovering = true;
    }
    else if (scoreItem->getBoundingBox().containsPoint(mousePos))
    {
        borderSprite->setPosition(scoreItem->getPosition());
        isHovering = true;
    }
    else if (exitItem->getBoundingBox().containsPoint(mousePos))
    {
        borderSprite->setPosition(exitItem->getPosition());
        isHovering = true;
    }

    // Hiển thị viền
    borderSprite->setVisible(isHovering);
}

void MainScene::update(float delta) {}

void MainScene::menuPlayGameCallback(ax::Object* sender)
{
    AudioManager::getInstance()->playClickEffect();
    auto scene = utils::createInstance<GameScene>();
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainScene::menuHighScoreCallback(ax::Object* sender)
{
    AudioManager::getInstance()->playClickEffect();
    auto scene = utils::createInstance<HighScoreScene>();
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainScene::menuCloseCallback(ax::Object* sender)
{
    AudioManager::getInstance()->playClickEffect();
    _director->end();
}
