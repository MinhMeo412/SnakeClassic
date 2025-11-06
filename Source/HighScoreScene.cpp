#include "HighScoreScene.h"
#include "MainScene.h"
#include "Utils.h"
#include "Score.h"
#include "AudioManager.h"
#include "ui/UITextField.h"
#include "axmol.h"

using namespace ax;

bool HighScoreScene::init()
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

    // Tải danh sách điểm
    auto highScores = Score::loadHighScoresFromFile();

    float offsetY = visibleSize.height / 2 + origin.y + 150;
    for (const auto& entry : highScores)
    {
        auto label = Label::createWithSystemFont(entry.name + ": " + std::to_string(entry.score), "Arial", 24);
        label->setPosition(Vec2(visibleSize.width / 2 + origin.x, offsetY));
        this->addChild(label, 0);
        offsetY -= 30;  // Giảm độ cao cho các label tiếp theo
    }

    offsetY -= 50;

    // Return button
    backButton = Utils::createMenuItem("Button.png", "ButtonPressed.png",
                                       AX_CALLBACK_1(HighScoreScene::scoreReturnCallback, this),
                              Vec2(visibleSize.width / 2 + origin.x, offsetY));

    auto buttonLabel = Label::createWithSystemFont("RETURN", "Arial", 30);
    buttonLabel->setPosition(backButton->getPosition() + Vec2(0, 5));
    buttonLabel->setTextColor(Color4B::BLACK);
    this->addChild(buttonLabel, 1);

    auto menu = Menu::create(backButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0);

    return true;
}


void HighScoreScene::scoreReturnCallback(ax::Object* sender)
{
    AudioManager::getInstance()->playClickEffect();
    auto scene = utils::createInstance<MainScene>();
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

