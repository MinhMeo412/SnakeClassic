#include "SplashScene.h"
#include "Utils.h"
#include "MainScene.h"

using namespace ax;

bool SplashScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = _director->getVisibleSize();
    auto origin      = _director->getVisibleOrigin();
    auto safeArea    = _director->getSafeAreaRect();
    auto safeOrigin  = safeArea.origin;

    // Tạo một layer background màu (sẽ thay bằng tên game)
    auto background = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
    background->setPosition(0 + origin.x, 0 + origin.y);
    this->addChild(background); 

    this->scheduleOnce(AX_SCHEDULE_SELECTOR(SplashScene::goToMainScene), DISPLAY_TIME_HELLO_SCENE);

    return true;
}

void SplashScene::goToMainScene(float dt)
{
    auto scene = utils::createInstance<MainScene>();
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
