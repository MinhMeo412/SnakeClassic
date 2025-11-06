#include "CustomCursorManager.h"

using namespace ax;

CustomCursorManager::CustomCursorManager() : cursorSprite(nullptr) {}

CustomCursorManager* CustomCursorManager::_instance = nullptr;

CustomCursorManager* CustomCursorManager::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new CustomCursorManager();
    }
    return _instance;
};

void CustomCursorManager::initCursor(ax::Scene* scene)
{
    Director::getInstance()->getGLView()->setCursorVisible(false);

    // Tạo con trỏ sprite và thêm vào scene
    cursorSprite = Sprite::create("Pointer_01.png");
    cursorSprite->setAnchorPoint(Vec2(0.4, 0.7));     // Đặt điểm neo theo sprite với x = 0~1, y= 0~1
    scene->addChild(cursorSprite, 100);

    auto listener = EventListenerMouse::create();
    listener->onMouseMove = AX_CALLBACK_1(CustomCursorManager::updateCursorPosition, this);
    scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, scene);
}

void CustomCursorManager::updateCursorPosition(Event* event)
{
    // Ép kiểu Event thành EventMouse
    EventMouse* mouseEvent = static_cast<EventMouse*>(event);

    // Cập nhật vị trí sprite con trỏ theo vị trí chuột
    cursorSprite->setPosition(mouseEvent->getCursorX(), mouseEvent->getCursorY());
}
