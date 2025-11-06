#include "SaveScoreScene.h"
#include "Utils.h"
#include "Score.h"
#include "HighScoreScene.h"
#include "AudioManager.h"
#include "ui/UITextField.h"

using namespace ax;

int SaveScoreScene::highScore = 0;

ax::Scene* SaveScoreScene::createScene(int score)
{
    auto scene = SaveScoreScene::create();

    highScore = score;

    return scene;
}

bool SaveScoreScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    visibleSize = _director->getVisibleSize();
    origin      = _director->getVisibleOrigin();
    safeArea    = _director->getSafeAreaRect();
    safeOrigin  = safeArea.origin;

    setupMouseListener();
    enableCustomCursor();

    // label info
    auto label = Label::createWithSystemFont("Nhập tên của bạn:", "Arial", 24);
    label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 50));
    this->addChild(label, 0);

    // TextField for playername
    textField = ui::TextField::create("Tên của bạn", "Arial", 24);
    textField->setPosition(Director::getInstance()->getVisibleSize() / 2);
    textField->setMaxLength(20);
    this->addChild(textField, 0);

    // Tạo MenuItem với Sprite và callback
    saveButton = Utils::createMenuItem("Button.png", "ButtonPressed.png", [this](ax::Object* sender) {                               
        std::string playerName = std::string(textField->getString());  
        Score::addHighScoreToFile(highScore, playerName);
        AudioManager::getInstance()->playClickEffect();
        auto scene = utils::createInstance<HighScoreScene>();
        _director->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50));

    auto buttonLabel = Label::createWithSystemFont("SAVE", "Arial", 30);
    buttonLabel->setPosition(saveButton->getPosition() + Vec2(0,5));
    buttonLabel->setTextColor(Color4B::BLACK);
    this->addChild(buttonLabel, 1);

    auto menu = ax::Menu::create(saveButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0);

    return true;
}

