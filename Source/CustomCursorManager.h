#ifndef __CUSTOM_CURSOR_MANAGER_H__
#define __CUSTOM_CURSOR_MANAGER_H__

#include "axmol.h"


class CustomCursorManager
{
public:
    static CustomCursorManager* getInstance();

    void initCursor(ax::Scene* scene);

private:
    CustomCursorManager();
    static CustomCursorManager* _instance;
    ax::Sprite* cursorSprite;

    void updateCursorPosition(ax::Event* event);
};

#endif // __CUSTOM_CURSOR_MANAGER_H__
