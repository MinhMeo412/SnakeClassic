#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include "axmol.h"
#include "CustomCursorManager.h"

class SceneBase : public ax::Scene
{
public:
    bool init() override;

protected:
    virtual void onMouseDown(ax::Event* event);
    virtual void onMouseUp(ax::Event* event);
    virtual void onMouseMove(ax::Event* event);
    virtual void onMouseScroll(ax::Event* event);

    void setupMouseListener();
    void enableCustomCursor();

private:
    ax::EventListenerMouse* mouseListener;

    ax::Vec2 visibleSize;
    ax::Vec2 origin;
    ax::Rect safeArea;
    ax::Vec2 safeOrigin;
};

#endif  //__SCENE_BASE_H__
